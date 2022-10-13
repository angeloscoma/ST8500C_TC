//-------------------------------------------------------------------------------------------------------
//   STX=2 EOT=255
//   Um byte de endereço...:  <STX><ADR><LEN><BLK_1>...<BLK_LEN><CRC_L><CRC_H><EOT>
//   Dois bytes de endereço:  <STX><126><ADR><LEN><BLK_1>...<BLK_LEN><CRC_L><CRC_H><EOT>
//-------------------------------------------------------------------------------------------------------


//-------------------------------------------------
// External variables and functions of the protocol
// that must be in the main program
// Example:
// #define RXBUF_SIZE	10
// #define TXBUF_SIZE	10
// #define PIN_DIR485	PIN_C5
// #define PIN_TX485	PIN_C6
// #define PIN_RX485	PIN_C7
// #include "..\hsnet\hsnet.c"
//-------------------------------------------------

#use rs232(baud=SPEED,parity=N,xmit=PIN_TX485,rcv=PIN_RX485)

int8  RxBuf[RXBUF_SIZE];
int8  RxLen = 0;

int8  TxBuf[TXBUF_SIZE];
int8  TxLen = 0;

int8	Net_Init(int16 myaddr);	// Must be called to start the protocol
void Net_Stop();			// Must be called to stop the protocol
int8  Net_Waiting();			// Must be called to test a request arrived
void Net_Send();			// Must be called to send a answer to master
void Net_Timer_1ms(void);	// Must be called by the timer interrupt routine every 1ms

//-------------------------------------------------
// Internal variables and functions of the protocol
//-------------------------------------------------

#define NET_WAIT_PIN_DIR485		3										// msec
#define NET_MASTER_WAIT			50										// msec
#define NET_ANSWER_TIMEOUT		NET_MASTER_WAIT - NET_WAIT_PIN_DIR485
#define NET_RECEIVE_TIMEOUT		3										// msec

#define RXSTATE_IDLE			0
#define TXSTATE_IDLE			99
#define STX						2
#define EOT						255

#if DEFINED PPP18F2420 || DEFINED PIC_18F6520 || DEFINED PIC_18F6720  //define processador PPP pois com PIC da erro do compilador - default é o 16F876
   #define RCSTA				0xFAB        // port in memory map
   #define CREN					4            // bit number in port
   #define OERR					1            // bit number in port
#else
   #define RCSTA				0x18         // port in memory map
   #define CREN					4            // bit number in port
   #define OERR					1            // bit number in port
#endif


int16 NetCrc;
int16 RxCrc;

int16 NetAddress;
int16 RcvAddress;

int8  NetTstLen;
int8  NetCont;
int8  RxTstLen;
int8  RxState = RXSTATE_IDLE;
int8  RxTimeout = 0;
int8  TxWaitPin = 0;
int8  TxState = TXSTATE_IDLE;
int8  TxTimeout = 0;

int1  NetSync = 0;
int1  NetInit = 0;
int1  RxOverRun = 0;
int1  RxSync;
int1  RxForMe;
int1  TxProcessing = 0;
int1  TxValid = 0;
int1  TxAbort = 0;
int1  NetWaiting = 0;		// Must be tested by the application (read only variable)

#ifdef HUBNET
// this is used by starhub
int   NetSts=0;
int1  NetTxSts=0;
int1  NetRxSts=0;
int1  NetCrcSts=0;

/*************************************/
int Net_Sts(){
	int   ret=0;
	if( NetSts > 0){
		ret=NetSts;
		NetSts=0;
	}
	return(ret);
}

/*************************************/
int Net_Tx_Sts(){
	int   ret=0;
	if( NetTxSts > 0){
		ret=1;
		NetTxSts=0;
	}
	return(ret);
}

/*************************************/
int Net_Rx_Sts(){
	int   ret=0;
	if( NetRxSts > 0){
		ret=1;
		NetRxSts=0;
	}
	return(ret);
}

/*************************************/
int Net_Crc_Sts(){
	int   ret=0;
	if( NetCrcSts > 0){
		ret=1;
		NetCrcSts=0;
	}
	return(ret);
}
#endif


/*************************************/
int Net_Init(int16 myaddr){
	NetAddress = myaddr;
	#ifdef  PIN_DIR485
		output_low( PIN_DIR485 );   // direction of 485 to rcv
	#endif
	TxTimeout = 10;		       // Start TX timer
	NetWaiting = 0;
	delay_ms(7);
	delay_us(500);

	if (TxTimeout <= 3){
		/* Timer is running ok */
		TxTimeout = 0;		// Stop TX timer
		NetInit = 1;
		RxState = RXSTATE_IDLE;
		TxState = TXSTATE_IDLE;
		#asm
			BCF RCSTA, CREN
			BSF RCSTA, CREN
		#endasm

		while ( kbhit() )
			getc();

		enable_interrupts(INT_RDA);
		return (1);
	}
	return (0);
}

#ifdef WITH_NETSTOP
/*************************************/
void Net_Stop(void){
	// Stop interruptions
	disable_interrupts(INT_RDA);
	disable_interrupts(INT_TBE);

	// Stop timers
	TxWaitPin = 0;
	TxTimeout = 0;
	RxTimeout = 0;

	// All states in idle
	RxState = RXSTATE_IDLE;
	TxState = TXSTATE_IDLE;
	NetWaiting = 0;
	TxProcessing = 0;
	NetInit = 0;
}
#endif

/*************************************/
int Net_Waiting(void){
	if (NetWaiting){
		TxProcessing = 1;	// Started the processing of the answer
		return (1);
	}
	return (0);
}

/*************************************/
void Net_Send(void){
	TxProcessing = 0;	// Finished the processing of the answer
	if (NetInit && !TxAbort){
		TxTimeout = 0;		// Stop TX timer
		TxValid = 1;		// Now TxBuf has a valid content
		TxAbort = 1;		// Don't send another answer before a new request
		if (RxState == RXSTATE_IDLE && TxState == TXSTATE_IDLE && NetWaiting){
			/*  The master still waits for an answer */
			#ifdef  PIN_DIR485
				output_high( PIN_DIR485 );
			#endif
//			NetWaiting = 0;
			TxWaitPin = NET_WAIT_PIN_DIR485;
		}
	}
	NetWaiting = 0;
}

/*************************************/
void Net_Timer_1ms(void){
	if (TxWaitPin){
		TxWaitPin--;
		if (TxWaitPin == 0){
			TxState = 0;
			enable_interrupts(INT_TBE); // Initiate transmission
		}
	}

	if (TxTimeout){
		TxTimeout--;
		if (TxTimeout == 0){
			NetWaiting = 0;		// Cancel any pending sending of answer
		}
	}

	if (RxTimeout){
		RxTimeout--;
		if (RxTimeout == 0){
			RxState = RXSTATE_IDLE;		// Cancel any block reception
		}
	}
	#asm
		BTFSS RCSTA,OERR
		GOTO NOOERR
		BCF RCSTA, CREN         //clear overrun status
		BSF RCSTA, CREN
NOOERR:
	#endasm
}

/*************************************
A few things to know:
1) The word NetCrc should be initialized to 0xFFFF.
2) You call this function once for each byte to be checked.
*/
void ComputeCrc(int8 ch){
	int8 i;
	int16 ch16;

	ch16 = ch;
	ch16 = ch << 8;
	NetCrc = NetCrc ^ ch16;
	for (i = 0 ; i < 8 ; ++i){
		if (NetCrc & 0x8000){
			NetCrc = NetCrc << 1;
			NetCrc = NetCrc ^ 0x1021;
		}
		else{
			NetCrc = NetCrc << 1;
		}
	}
}

/*************************************/
#int_TBE
void TBE_isr(){
	int8 ch;

	switch (TxState){
		default:
			disable_interrupts(INT_TBE);
			#ifdef  PIN_DIR485
				output_low( PIN_DIR485 );
			#endif
			break;
		case 0:
			putc(STX);
			NetCrc = 0xffff;
			TxState = 1;
			break;
	
		case 1:
			ch = NetSync ? 0x80 : 0;
			putc(ch);
			ComputeCrc(ch);
			TxState = 2;
			break;
	
		case 2:
			NetTstLen = TxValid ? TxLen : 0;
			putc(NetTstLen);
			ComputeCrc(NetTstLen);
			NetCont = 0;
			TxState = 3;
			break;
	
		case 3:
			if (NetCont < NetTstLen){
				if (NetCont >= sizeof(TxBuf)){
					ch = 0;
				}
				else{
					ch = TxBuf[NetCont++];
					ComputeCrc(ch);
				}
			}
			else{
				ch = NetCrc >> 8;
				TxState = 4;
			}
			putc(ch);
			break;
	
		case 4:
			ch = NetCrc & 0xff;
	    	putc(ch);
			TxState = 5;
			break;
	
		case 5:
			putc(0xff);
			TxState = TXSTATE_IDLE;
			break;
	}
}

/*************************************/
#int_RDA
void RDA_isr(){
	int8 ch;

	ch = getc();

	RxTimeout = NET_RECEIVE_TIMEOUT;	// Start RX timer for next char

	switch (RxState){
	   	case RXSTATE_IDLE:  // Esperando STX
	   		if (ch != STX)
	   			RxTimeout = 0;		// Stop RX timer
	   		else
	   		{
	   			NetCrc = 0xffff;
	   			RxForMe = 0;
	   			RxOverRun = TxProcessing;
	   			RxState = 1;
	   		}
	   		break;

	   	case 1:            // Esperando SYNC + ADDR
	         RxSync=bit_test( ch, 7 );
	         RcvAddress=(ch&0x7F);
	   		RxState=3;
	         if(RcvAddress == 126)
	    			RxState=2;
	         else if (RcvAddress == NetAddress)
	   			RxForMe=1;
	
	         ComputeCrc(ch);
#ifdef HUBNET
         if( RcvAddress==0 )
         {
               NetRxSts=1;
               NetSts=2;
         }
         else
         {
               NetTxSts=1;
               NetSts=1;
         }
#endif
   		break;

   	case 2:          // Esperando ADDR extension
         RcvAddress += ch;
         if (RcvAddress == NetAddress)
         {
   			RxForMe = 1;
      		RxState = 3;
   		}
         ComputeCrc(ch);
   		break;

   	case 3:          // Esperando block length
   		NetTstLen = ch;
   		if (RxForMe && !RxOverRun)
   			RxLen = ch;
   		ComputeCrc(ch);
   		NetCont = 0;
   		RxState = 4;
   		break;

   	case 4:          // Esperando block content
   		if (NetCont < NetTstLen)
   		{
   			if (NetCont < sizeof(RxBuf))
   			{
   				if (RxForMe && !RxOverRun)
   					RxBuf[NetCont++] = ch;
   				ComputeCrc(ch);
   			}
   		}
   		else
   		{
   			RxCrc = ch;
   			RxCrc <<= 8;
   			RxState = 5;
   		}
   		break;

   	case 5:          // Esperando CRC
   		RxTimeout = 0;		// Stop RX timer
   		RxCrc += ch;
   		if (RxCrc == NetCrc)
   		{
   			/* A valid block arrived */
   			if (RxForMe)
   			{
   				if (RxLen == 0)
   				{
   					/* An empty block is for to re-synchronize the protocol and
   					   the answer must be a empty block too. */
   				  sendSyncBlock:
   					NetWaiting = 0;
   					NetSync = 0;
   					TxAbort = 1;
   					TxValid = 0;

   				  sendBlockNow:
#ifdef  PIN_DIR485
   					output_high( PIN_DIR485 );
#endif
   					TxWaitPin = NET_WAIT_PIN_DIR485;
   				}
   				else if (RxSync == NetSync)
   				{
   					/* The master requires the last answer again */
   					if (TxProcessing)
   						/* The application is still processing the last request.
   						   Nothing to do - must stay quiet. */
   						;
   					else if (!TxValid)
   						/* Don't have valid answer to send again then sends
   						   an empty block */
   						goto sendSyncBlock;
   					else
   						/* Send the last answer again */
   						goto sendBlockNow;
   				}
   				else
   				{
   					/* The master sended a new request to this device */
   					if (RxOverRun)
   					{
   						/* The application is still processing a request.
   						   However, the master already sent another request
   						   so aborts all. */
   						goto sendSyncBlock;
   					}
   					NetSync = RxSync;
   					NetWaiting = 1;
   					TxValid = 0;
   					TxAbort = 0;
   					TxTimeout = NET_ANSWER_TIMEOUT;	// Start TX timer
   				}
   			}
   			else
   			{
   				/* The master already polling another device then don't send
   				   any pending answer (only after a new request) */
   				NetWaiting = 0;
   			}
   		}
#ifdef HUBNET
         else
         {
            NetSts=3;
            NetCrcSts=1;
         }
#endif
   		RxState = RXSTATE_IDLE;
   		break;
   }
}
