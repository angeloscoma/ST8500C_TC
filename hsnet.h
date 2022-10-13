//--------------------------------------------------------------------------------------
// Modelo (PIC16F876)
// Version 1.00 - 01.07.2006
//-------------------------------------------------------------------------------------

//----------------------------------------------
#include <string.h>

// next defines the model and version number  //
//-----------------------------------------------------------//
#define VERS_MAJOR (cequipo[9] - 48)
#define VERS_MINOR (cequipo[11] - 48)
#define VERS_PATCH (cequipo[12] - 48)
#define DEV_MODEL  "ST50"

//-------------------------------------------------
// External variables and functions of the protocol
//-------------------------------------------------
#define SPEED			19200
#define RXBUF_SIZE		64
#define TXBUF_SIZE		64
#define PIN_DIR485		PIN_F7	//direcao
#define PIN_TX485		PIN_C6
#define PIN_RX485		PIN_C7

// default HsNet address max is 100 //
//-----------------------------------------------------------//
#define DEFHSNETADR 100


// next defines are for timming purposes //
//-----------------------------------------------------------//
#define RATE      CPUCLOCK/4000000

// next defines are all for protocol  //
//-----------------------------------------------------------//
#define CMD_RDA   0xFF// Read device address
#define CMD_RDM   0xFE// Read device model
#define CMD_RSV   0xFD// Read software version
#define CMD_WDA   0xEF// Write device address
#define CMD_WRA   0xEE// Reset device address
#define CMD_WRD   0xED// Reset device
#define CMD_INV   0xEA// Comando Inválido
#define CMD_INI   0xEE// Dispositivo Inicializado

// next defines the RS485 function calls  //
//-----------------------------------------------------------//
#define RAS 10
#define ROM 11
#define RIS 12
#define RMP 62           // read module parameters
#define WMP 72           // write module parameters

#define WOM 55
#define WUN 56
#define RSENS 22
#define WSENS 60


// variables and defines for write EEProm                    //
//-----------------------------------------------------------//

enum { EEP_CRCLOW = 0, EEP_CRCHIGH, EEP_HSNETADR, EEP_HSNETADRE, EEP_SENS, EEP_LASTPAR };
#define EEP_OFFSET   990

int   Count_1ms = 4;
int   InitFlag=0;
int   Par1,Par2,Par3,Par4;
int8  RxBuf[RXBUF_SIZE];		
int8  RxLen = 0;

int8  TxBuf[TXBUF_SIZE];
int8  TxLen = 0;

//-------------------------------------------------
// Internal variables and functions of the protocol
//-------------------------------------------------

#define NET_WAIT_PIN_DIR485		3
#define NET_MASTER_WAIT			50		// msec
#define NET_ANSWER_TIMEOUT		NET_MASTER_WAIT - NET_WAIT_PIN_DIR485
#define NET_RECEIVE_TIMEOUT		3		// era 3 msec(26/06/07 - vagner)msec

#define RXSTATE_IDLE		0
#define TXSTATE_IDLE		99
#define STX					2
#define EOT					255

#define RCSTA				0xFAB        // port in memory map
#define CREN				4            // bit number in port
#define OERR				1            // bit number in port


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



/*************************************/
void read_pars(void)
{
   TxBuf[1]=ala_fp_ind;
   TxBuf[2]=ala_fp_cap;
   TxBuf[3]=ala_ten_a;
   TxBuf[4]=ala_ten_b;
   TxBuf[5]=ala_sc;
   TxBuf[6]=ala_subc;
   TxBuf[7]=ala_chtt;
   TxBuf[8]=ala_chtc;
   TxBuf[9]=make8(valor_tc, 0);
   TxBuf[10]=make8(valor_tc, 1);
   TxBuf[11]=make8(valor_tp, 0);
   TxBuf[12]=make8(valor_tp, 1);
   TxBuf[13]=tem_alarme;
   Txlen=14;
}

/*************************************/
void write_pars(void)
{
   ala_fp_ind=RxBuf[1];
   ala_fp_cap=RxBuf[2];
   ala_ten_a=RxBuf[3];
   ala_ten_b=RxBuf[4];
   ala_sc=RxBuf[5];
   ala_subc=RxBuf[6];
   ala_chtt=RxBuf[7];
   ala_chtc=RxBuf[8];
   valor_tc = make16(RxBuf[10],RxBuf[9]);
   valor_tp = make16(RxBuf[12],RxBuf[11]);
   salva_programa();
 
}

/*************************************/
word converte_tc(word valor)
{
	float aux_f1;
	aux_f1 = 0;
	aux_f1 = (float)(valor);
	aux_f1 = (float)(aux_f1 * mul_tc);
	aux_w1 = (word)(aux_f1);
	return(valor);
}

/*************************************/
void read_vals(int cmd )
{
   	if( cmd == 0 )
  		{
		aux_w1 = converte_tc(pot_ativa_r);
	    TxBuf[1] = aux_w1 & 0x00FF;        //low byte of PAF1
	    TxBuf[2] = aux_w1 >> 8;            //high byte of PAF1
		aux_w1 = converte_tc(pot_ativa_s);
	    TxBuf[3] = aux_w1 & 0x00FF;        //low byte of PAF2
	    TxBuf[4] = aux_w1 >> 8;            //high byte of PAF2
		aux_w1 = converte_tc(pot_ativa_t);
	    TxBuf[5] = aux_w1 & 0x00FF;        //low byte of PAF3
	    TxBuf[6] = aux_w1 >> 8;            //high byte of PAF3
	
   		aux_w1 = converte_tc(pot_reativa_r);
		TxBuf[7] = aux_w1 & 0x00FF;        //low byte of PRF1
	    TxBuf[8] = aux_w1 >> 8;            //high byte of PRF1
   		aux_w1 = converte_tc(pot_reativa_s);
	    TxBuf[9] = aux_w1 & 0x00FF;        //low byte of PRF2
	    TxBuf[10] = aux_w1 >> 8;           //high byte of PRF2
   		aux_w1 = converte_tc(pot_reativa_t);
	   	TxBuf[11] = aux_w1 & 0x00FF;       //low byte of PRF3
	    TxBuf[12] = aux_w1 >> 8;           //high byte of PRF3
	
   		aux_w1 = converte_tc(pot_aparente_r);
	    TxBuf[13] = aux_w1 & 0x00FF;      //low byte of PPF1
	    TxBuf[14] = aux_w1 >> 8;          //high byte of PPF1
   		aux_w1 = converte_tc(pot_aparente_s);
	    TxBuf[15] = aux_w1 & 0x00FF;      //low byte of PPF2
	    TxBuf[16] = aux_w1 >> 8;          //high byte of PPF2
   		aux_w1 = converte_tc(pot_aparente_t);
	    TxBuf[17] = aux_w1 & 0x00FF;      //low byte of PPF3
	    TxBuf[18] = aux_w1 >> 8;          //high byte of PPF3
	    Txlen=19;                                       
   		}
   	else if( cmd == 1 )
   		{
	      TxBuf[1]=consumo_ati&0x000000FF;       //LSB byte of CONSUMO ATIVO
	      TxBuf[2]=(consumo_ati>>8)&0x000000FF;  //byte#2 of CONSUMO ATIVO
	      TxBuf[3]=(consumo_ati>>16)&0x000000FF; //byte#3 of CONSUMO ATIVO
	      TxBuf[4]=(consumo_ati>>24)&0x000000FF; //MSB of CONSUMO ATIVO
	
	      TxBuf[5]=consumo_reati & 0x000000FF;       //LSB byte of CONSUMO REATIVO
	      TxBuf[6]=(consumo_reati >> 8) & 0x000000FF;  //byte#2 of CONSUMO REATIVO
	      TxBuf[7]=(consumo_reati >> 16) & 0x000000FF; //byte#3 of CONSUMO REATIVO
	      TxBuf[8]=(consumo_reati >> 24) & 0x000000FF; //MSB of CONSUMO REATIVO
	
		  aux_l1 = pot_ativa_r;
		  aux_l1 += pot_ativa_s + pot_ativa_t;
		  aux_w1 = (aux_l1) / 32;
	      TxBuf[9]=aux_w1&0x00FF;           //low byte of TA
	      TxBuf[10]=aux_w1>>8;              //high byte of TA
	
		  aux_l1 = pot_reativa_r;
		  aux_l1 += pot_reativa_s + pot_reativa_t;
		  aux_w1 = (aux_l1) / 32;
	      TxBuf[11]=aux_w1&0x00FF;           //low byte of TR
	      TxBuf[12]=aux_w1>>8;              //high byte of TR
	
		  aux_l1 = pot_aparente_r;
		  aux_l1 += pot_aparente_s + pot_aparente_t;
		  aux_w1 = (aux_l1) / 32;
	      TxBuf[13]=aux_w1&0x00FF;           //low byte of TP
	      TxBuf[14]=aux_w1>>8;              //high byte of TP
	
	      Txlen=15;                                       
   		}

}



/*************************************/
void trata_hsnet()
{
	if( !Net_Waiting() )
    	{    
	    return;
	    }

//	passo_hsnet = 4;

	Txlen=1;

	if( InitFlag ){
		InitFlag=0;
		TxBuf[0]=CMD_INI;
//		passo_hsnet = 5;
	}
	else{
//		passo_hsnet = 6;
		TxBuf[0]=RxBuf[0];
		switch ( RxBuf[0] ){
			/*******************************************************************************/
			/*                           READ CALLS                                        */
			/*******************************************************************************/
            case RAS:               //10 - read all status
            	{
				ContHSnet = TEMPO_HSNET;			// Plano B - CIEE: Se o contador chegar a zero, acontece um reset micro.
 
               	TxBuf[1]=make8(tensao_r, 0);  		//low byte of VF1
               	TxBuf[2]=make8(tensao_r, 1); 		//high byte of VF1
               	TxBuf[3]=tensao_s&0x00FF;       	//low byte of VF2
               	TxBuf[4]=tensao_s>>8;           	//high byte of VF2
               	TxBuf[5]=tensao_t&0x00FF;       	//low byte of VF3
               	TxBuf[6]=tensao_t>>8;           	//high byte of VF3
				
				
				aux_w1 = converte_tc(corrente_r);
               	TxBuf[7]=aux_w1&0x00FF;        //low byte of IF1
               	TxBuf[8]=aux_w1>>8;            //high byte of IF1
				aux_w1 = converte_tc(corrente_s);
               	TxBuf[9]=aux_w1&0x00FF;        //low byte of IF2
               	TxBuf[10]=aux_w1>>8;           //high byte of IF2
				aux_w1 = converte_tc(corrente_t);
               	TxBuf[11]=aux_w1&0x00FF;       //low byte of IF3
               	TxBuf[12]=aux_w1>>8;           //high byte of IF3

               	TxBuf[13]=fator_pot_r&0x00FF;      //low byte of FPF1
               	TxBuf[14]=fator_pot_r>>8;          //high byte of FPF1
               	TxBuf[15]=fator_pot_s&0x00FF;      //low byte of FPF2
               	TxBuf[16]=fator_pot_s>>8;          //high byte of FPF2
               	TxBuf[17]=fator_pot_t&0x00FF;      //low byte of FPF3
               	TxBuf[18]=fator_pot_t>>8;          //high byte of FPF3
               	Txlen=19;                                       
               	break;
				}
            case RIS:               //12 - ler valor de uma(s) ENTRADA(s)
            	{
               	read_vals(RxBuf[1]);
                break;
               	}

            case RMP:              //62 - ler parametros do módulo
            	{
               	read_pars();
                break;
                }

			/*******************************************************************************/
			/*                           WRITE CALLS                                       */
			/*******************************************************************************/
            case WUN: //56                   /* write unit */
            	{
               if (RxBuf[1] == 1)
               		{
   		 	    	output_high(alarme);
		 	    	tem_alarme = 1;
					tem_comando_alarme = 1;
					fled_alarme = 0;
					status_flags = 13;
					}
	           else
	           		{
		           	output_low(alarme);
		 	    	tem_alarme = 0;
					tem_comando_alarme = 1;
					fled_alarme = 1;
					}
				break;
				}

            case WMP:                       //72 - write parametros do módulo
            	{
               	write_pars();
               	break;
               	}

			/*******************************************************************************/
			/*                           HSNET CALLS                                       */
			/*******************************************************************************/
            case CMD_WDA:
            	{
	            TxBuf[1]=0;
	            if( RxLen == 2 && RxBuf[1] > 0 && RxBuf[1] < 126 )
	            	{	
	               	NetAddress=RxBuf[1];
	               	TxBuf[1]=RxBuf[1];
	               	write_par( EEP_HSNETADR, RxBuf[1] );
	               	write_par( EEP_HSNETADRE, 0 );
	               	Txlen=2;
	            	}
	            else if( RxLen == 3 && RxBuf[1] == 126 )
	            	{
	              	NetAddress=(int16)126+(int16)RxBuf[2];
	               	TxBuf[1]=126;
	               	TxBuf[2]=RxBuf[2];
	               	write_par( EEP_HSNETADR,  126 );
	               	write_par( EEP_HSNETADRE, RxBuf[2] );
	               	Txlen=3;
	            	}
	            break;
	          	}

            case CMD_RDA:
               TxBuf[1]=read_eeprom(EEP_HSNETADR);
               TxBuf[2]=read_eeprom(EEP_HSNETADRE);
               Txlen=3;
               break;

            case CMD_RSV:
               Txlen=4;
               TxBuf[1] = VERS_MAJOR;
               TxBuf[2] = VERS_MINOR;
               TxBuf[3] = VERS_PATCH;
               break;
            case CMD_RDM:
               strcpy( &TxBuf[1], DEV_MODEL );
               Txlen = 7;
               break;
            default:
               TxBuf[0]=CMD_INV;
               break;
			}
		}
		Net_Send();
//		passo_hsnet = 9;
}
