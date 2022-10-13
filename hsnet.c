///////////////////////////////////////////////////////////////////////////
////                                                                   ////
////   HSNET - RS485 protocol for HS-HomeSystems (C) 2001 MultiSoft    ////
////                                                                   ////
///////////////////////////////////////////////////////////////////////////
// Version 1.00 - 01.01.2002 - criação
// Version 1.01 - 13.04.2004 - alterado o tempo do NET_WAIT_PIN_DIR485 de 5 para 2
// Version 1.02 - 13.05.2004 - alterado o tempo do NET_WAIT_PIN_DIR485 de 2 para 3 (DOS nao gostou do 2. vou tentar 3)
// Version 1.03 - 15.07.2004 - opcoes para gerenciamento do starhub (unificacão do codigo hubnet)
// Version 1.04 - 01.03.2005 - eliminado o endereço 127/255 de broadcast
// Version 1.05 - 03.03.2005 - endereço extendido com 126 + segundo byte de endereço
// Version 1.06 - 21.04.2005 - bug na detecção da passagem do Rxstate de 1 para 2 ou 3 (podia ficar sempre em 1 )
// Version 1.07 - 20.06.2005 - opcao para 0 2420/6520/6720
// Version 1.08 - 11.12.2005 - opcao para funcionar sem PINO de direcao para RS485 (alterado para o lighthub RS232)
// Version 1.09 - 10.02.2005 - chamada Output_bit foi transformada para minusculo output_bit (compilador novo)
// versão 1.10 - 15.07.2006 - adaptação para rodar dentro do ST5000T - Sultech By Vagner santos
//------------------------------------------------------------------------------------------------------------------------
//   STX=2 EOT=255
//
//   Um byte de endereço...:  <STX><ADR><LEN><BLK_1>...<BLK_LEN><CRC_L><CRC_H><EOT>
//   Dois bytes de endereço:  <STX><126><ADR><LEN><BLK_1>...<BLK_LEN><CRC_L><CRC_H><EOT>
//
//--------------------------------------------------------------------------------------------------------


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

int Net_Init(int16);	// Must be called to start the protocol
void Net_Stop();			// Must be called to stop the protocol
int  Net_Waiting();			// Must be called to test a request arrived
void Net_Send();			// Must be called to send a answer to master
void Net_Timer_1ms(void);	// Must be called by the timer interrupt routine every 1ms
void write_par( int , int );


//char nbuf_rx[16];
//char nbrx = 0;
//char passo_hsnet;


#include "hsnet.h"
#include "hsnet_eeprom.c"

#ifdef HUBNET
	// this is used by starhub
	int   NetSts=0;
	int1  NetTxSts=0;
	int1  NetRxSts=0;
	int1  NetCrcSts=0;
	
	/*************************************/
	int Net_Sts()
	{
	  	int   ret=0;
		if( NetSts > 0)
	   		{
	      	ret=NetSts;
	      	NetSts=0;
	   		}
	   	return(ret);
	}
	
	/*************************************/
	int Net_Tx_Sts()
	{
	   	int   ret=0;
	
		if( NetTxSts > 0)
	   		{
	      	ret=1;
	      	NetTxSts=0;
	   		}
	   return(ret);
	}
	
	/*************************************/
	int Net_Rx_Sts()
	{
	   	int   ret=0;
	
		if( NetRxSts > 0)
	   		{
	      	ret=1;
	      	NetRxSts=0;
	   		}
	   return(ret);
	}
	
	/*************************************/
	int Net_Crc_Sts()
	{
	   	int   ret=0;
	
		if( NetCrcSts > 0)
	   		{
	      	ret=1;
	      	NetCrcSts=0;
	   		}
	   return(ret);
	}
#endif

/*************************************/
int Net_Init(int16 myaddr)
{
	NetAddress = read_eeprom(EEP_HSNETADR);
	if (NetAddress == 255){
		write_par(EEP_HSNETADR, 100);
		write_par(EEP_HSNETADRE, 0);
		myaddr = 100;
		}
	NetAddress = myaddr;
	output_low( PIN_DIR485 );	// direction of 485 to rcv
	TxTimeout = 10;				// Start TX timer
   	NetWaiting = 0;
	delay_ms(7);
	delay_us(500);

	if (TxTimeout <= 3)
		{
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
			{
			getc(hsnet);
			}

		enable_interrupts(INT_RDA);
		return (1);
		}
	return (0);
}

#ifdef WITH_NETSTOP
/*************************************/
void Net_Stop(void)
{
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
int Net_Waiting(void)
{
	if (NetWaiting)
		{
		TxProcessing = 1;	// Started the processing of the answer
		return (1);
		}
	return (0);
}

/*************************************/
void Net_Send(void)
{
	TxProcessing = 0;	// Finished the processing of the answer

	if (NetInit && !TxAbort)
		{
		TxTimeout = 0;		// Stop TX timer
		TxValid = 1;		// Now TxBuf has a valid content
		TxAbort = 1;		// Don't send another answer before a new request
		if (RxState == RXSTATE_IDLE && TxState == TXSTATE_IDLE && NetWaiting)
			{
			/*  The master still waits for an answer */
			output_high( PIN_DIR485 );
			TxWaitPin = NET_WAIT_PIN_DIR485;
			}
		}
	NetWaiting = 0;
}

/*************************************/
void Net_Timer_1ms(void)
{
	if (TxWaitPin)
		{
		TxWaitPin--;
		if (TxWaitPin == 0)
			{
			TxState = 0;
			enable_interrupts(INT_TBE); // Initiate transmission
			}
		}

	if (TxTimeout)
		{
		TxTimeout--;
		if (TxTimeout == 0)
			{
			NetWaiting = 0;		// Cancel any pending sending of answer
			fled_tx = 1;
			fled_rx = 1;
			}
		}

	if (RxTimeout)
		{
		RxTimeout--;
		if (RxTimeout == 0)
			{
			RxState = RXSTATE_IDLE;		// Cancel any block reception
//			nbrx = 0;
			fled_tx = 1;
			fled_rx = 1;
			
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
void ComputeCrc(int8 ch)
{
	int8 i;
	int16 ch16;

	ch16 = ch;
	ch16 = ch << 8;
	NetCrc = NetCrc ^ ch16;
	for (i = 0 ; i < 8 ; ++i)
		{
		if (NetCrc & 0x8000)
			{
			NetCrc = NetCrc << 1;
			NetCrc = NetCrc ^ 0x1021;
			}
		else
			{
			NetCrc = NetCrc << 1;
			}
		}
}

//char nbuftx[32];
//char ptr_nbuftx;
/*************************************/
#int_TBE
void TBE_isr(){
	int8 ch;

	fled_tx = 0;
	fled_rx = 1;

	switch (TxState){
		case 0:{
			putc(STX, hsnet);
			NetCrc = 0xffff;
			TxState = 1;
//			nbuftx[0] = STX;
			break;
			}
		case 1:{
			ch = NetSync ? 0x80 : 0;
			putc(ch, hsnet);
			ComputeCrc(ch);
			TxState = 2;
//			nbuftx[1] = ch;
			break;
			}
		case 2:{
			NetTstLen = TxValid ? TxLen : 0;
//			nbuftx[2] = NetTstLen;
			putc(NetTstLen, hsnet);
			ComputeCrc(NetTstLen);
			NetCont = 0;
			TxState = 3;
			break;
			}
		case 3:{
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
			putc(ch, hsnet);
//			nbuftx[3] = ch;
			break;
			}
		case 4:{
			ch = NetCrc & 0xff;
			putc(ch, hsnet);
//			nbuftx[4] = ch;
			TxState = 5;
			break;
			}
		case 5:{
			putc(0xff, hsnet);
//			nbuftx[5] = 0xff;
			TxState = TXSTATE_IDLE;
			break;
			}
		default:{
			disable_interrupts(INT_TBE);
			output_low( PIN_DIR485 );
			fled_tx = 1;
			fled_rx = 1;
			break;
			}
		}
	}

/*************************************/
#int_RDA
void RDA_isr()
{
	int8 ch;
	ch = getc(hsnet);

//	if (nbrx > 14){
//		nbrx = 0;
//		}
//	nbuf_rx[nbrx++] = ch;

	RxTimeout = NET_RECEIVE_TIMEOUT;	// Start RX timer for next char

	switch (RxState){
   		case RXSTATE_IDLE:  // Esperando STX	
	   		{
   			if (ch != STX){
   				RxTimeout = 0;		// Stop RX timer
   				}
   			else{
   				NetCrc = 0xffff;
   				RxForMe = 0;
   				RxOverRun = TxProcessing;
   				RxState = 1;
   				}
   			break;
   			}
   		case 1:            // Esperando SYNC + ADDR
   			{
         	RxSync = bit_test( ch, 7 );
         	RcvAddress=(ch & 0x7F);
   			RxState=3;
         	if(RcvAddress == 126){
    			RxState=2;
    			}
         	else if (RcvAddress == NetAddress){
   				RxForMe=1;
//				fled_tx = 1;
//				fled_rx = 0;
   				}

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
			}
   		case 2:          // Esperando ADDR extension
   			{
         	RcvAddress += ch;
         	if (RcvAddress == NetAddress){
   				RxForMe = 1;
   				}							//Alterado em 15.04.2008 BUG protocolo extendido
			RxState = 3;
         	ComputeCrc(ch);
   			break;
   			}

   		case 3:          // Esperando block length
   			{
	   		NetTstLen = ch;
   			if (RxForMe && !RxOverRun)
   				{
   				RxLen = ch;
   				}
	   		ComputeCrc(ch);
   			NetCont = 0;
   			RxState = 4;
	   		break;
			}
	   	case 4:          // Esperando block content
	   		{
   			if (NetCont < NetTstLen)
   				{
   				if (NetCont < sizeof(RxBuf))
   					{
	   				if (RxForMe && !RxOverRun)
	   					{
	   					RxBuf[NetCont++] = ch;
	   					}
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
	   		}

	   	case 5:          // Esperando CRC
	   		{
	   		RxTimeout = 0;		// Stop RX timer
   			RxCrc += ch;
   			
			//SOMENTE DURANTE A DEPURAÇÃO 
			/*if (RxCrc == 0x0000){
				RxCrc = NetCrc;
				}
			RxCrc = NetCrc;
			RxForMe = 1;*/
			// ATE AQUI

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
						#if (debug_hsnet == true)
//							fprintf(debug,"\r\n SendSyncBlock! \r\n");
//							debug_count = 1;
						#endif

sendBlockNow:
	   					output_high( PIN_DIR485 );
	   					TxWaitPin = NET_WAIT_PIN_DIR485;
						#if (debug_hsnet == true)
//							fprintf(debug,"\r\n SendBlockNow! \r\n");
//							debug_count = 2;
						#endif
	   					
	   					
//						TxState = 1;
   						}
   					else if (RxSync == NetSync)
   						{
   						/* The master requires the last answer again */
   						if (TxProcessing)
   							{
	   						/* The application is still processing the last request.
   							   Nothing to do - must stay quiet. */
							#if (debug_hsnet == true)
//								fprintf(debug,"\r\n TxProcessing! \r\n");
								debug_count = 3;
							#endif
   							}
	   					else if (!TxValid)
	   						{
   							/* Don't have valid answer to send again then sends
   						   	an empty block */
							#if (debug_hsnet == true)
//								fprintf(debug,"\r\n TxValid! \r\n");
								debug_count = 4;
							#endif
   							goto sendSyncBlock;
   							}
   						else
   							{
	   						/* Send the last answer again */
							#if (debug_hsnet == true)
//								fprintf(debug,"\r\n TxSyncAgain! \r\n");
								debug_count = 5;
							#endif
   							goto sendBlockNow;
   							}
						}
   					else
   						{
   						/* The master sended a new request to this device */
	   					if (RxOverRun)
   							{
   							/* The application is still processing a request.
   							   However, the master already sent another request
   							   so aborts all. */
							#if (debug_hsnet == true)
//								fprintf(debug,"\r\n RxOverRun! \r\n");
								debug_count = 6;
							#endif
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
					#if (debug_hsnet == true)
						debug_count = 7;
					#endif
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
	fled_tx = 1;
	fled_rx = 0;
}
