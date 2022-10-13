//--------------------------------------------------------------------------------------
// Modelo (PIC16F876)
// Version 1.00 - 01.07.2006
//-------------------------------------------------------------------------------------

//----------------------------------------------
#include "modelo.h"
#include <string.h>

// next defines the model and version number  //
//-----------------------------------------------------------//
#define VERS_MAJOR 1
#define VERS_MINOR 0
#define VERS_PATCH 0
#define DEV_MODEL  "MOD"

//-------------------------------------------------
// External variables and functions of the protocol
//-------------------------------------------------
#define SPEED     	19200
#define RXBUF_SIZE	15
#define TXBUF_SIZE	15
#define PIN_DIR485	PIN_C5
#define PIN_TX485	   PIN_C6
#define PIN_RX485	   PIN_C7
#include "hsnet.c"

// default HsNet address max is 100 //
//-----------------------------------------------------------//
#define DEFHSNETADR 100


// next defines are for timming purposes //
//-----------------------------------------------------------//
#define RATE      CPUCLOCK/4000000
#define DIV1MS    RATE*4     // watch dog must be 72ms -> at 4MHZ int_rtcc is 256uS

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

#define RMP 62           // read module parameters
#define WMP 72           // write module parameters

#define WOM 55
#define WUN 56
#define RSENS 22
#define WSENS 60

// variables and defines for write EEProm                    //
//-----------------------------------------------------------//

enum { EEP_CRCLOW=0, EEP_CRCHIGH, EEP_HSNETADR, EEP_HSNETADRE, EEP_SENS, EEP_LASTPAR };
#define EEP_OFFSET   50
#include "eeprom.c"

int   Count_1ms=DIV1MS;
int   InitFlag=1;
int   Par1,Par2,Par3,Par4;

/*************************************/
void My_Timer_1ms()
{
}

/******************************************/
#int_RTCC
RTCC_isr()
{
   Count_1ms--;
   if( !Count_1ms )           // 1ms is here
   {
      Count_1ms=DIV1MS;
      Net_Timer_1ms();
      My_Timer_1ms();
   }
}

/*************************************/
read_pars()
{
   TxBuf[1]=FP_Indutivo;
   TxBuf[2]=FP_Capacitivo;
   TxBuf[3]=V_Alta;
   TxBuf[4]=V_Baixa;
   TxBuf[5]=I_Alta;
   TxBuf[6]=I_Baixa;
   TxBuf[7]=CHV_Alta;
   TxBuf[8]=CHI_Alta;
   TxBuf[9]=TC;
   TxBuf[10]=TP;
   Txlen=11;
}

/*************************************/
write_pars()
{
   FP_Indutivo=RxBuf[1];
   FP_Capacitivo=RxBuf[2];
   V_Alta=RxBuf[3];
   V_Baixa=RxBuf[4];
   I_Alta=RxBuf[5];
   I_Baixa=RxBuf[6];
   CHV_Alta=RxBuf[7];
   CHI_Alta=RxBuf[8];
   TC=RxBuf[9];
   TP=RxBuf[10];
}

/*************************************/
read_vals(int cmd )
{
   if( cmd == 0 )
   {
      TxBuf[1]=PA_F1&0x00FF;        //low byte of PAF1
      TxBuf[2]=PA_F1>>8;            //high byte of PAF1
      TxBuf[3]=PA_F2&0x00FF;        //low byte of PAF2
      TxBuf[4]=PA_F2>>8;            //high byte of PAF2
      TxBuf[5]=PA_F3&0x00FF;        //low byte of PAF3
      TxBuf[6]=PA_F3>>8;            //high byte of PAF3

      TxBuf[7]=PR_F1&0x00FF;        //low byte of PRF1
      TxBuf[8]=PR_F1>>8;            //high byte of PRF1
      TxBuf[9]=PR_F2&0x00FF;        //low byte of PRF2
      TxBuf[10]=PR_F2>>8;           //high byte of PRF2
      TxBuf[11]=PR_F3&0x00FF;       //low byte of PRF3
      TxBuf[12]=PR_F3>>8;           //high byte of PRF3

      TxBuf[13]=PP_F1&0x00FF;      //low byte of PPF1
      TxBuf[14]=PP_F1>>8;          //high byte of PPF1
      TxBuf[15]=PP_F2&0x00FF;      //low byte of PPF2
      TxBuf[16]=PP_F2>>8;          //high byte of PPF2
      TxBuf[17]=PP_F3&0x00FF;      //low byte of PPF3
      TxBuf[18]=PP_F3>>8;          //high byte of PPF3
      Txlen=19;                                       
   }
   else if( cmd == 1 )
   {
      TxBuf[1]=CA&0x000000FF;       //LSB byte of CONSUMO ATIVO
      TxBuf[2]=(CA>>8)&0x000000FF;  //byte#2 of CONSUMO ATIVO
      TxBuf[3]=(CA>>16)&0x000000FF; //byte#3 of CONSUMO ATIVO
      TxBuf[4]=(CA>>24)&0x000000FF; //MSB of CONSUMO ATIVO

      TxBuf[5]=CR&0x000000FF;       //LSB byte of CONSUMO REATIVO
      TxBuf[6]=(CR>>8)&0x000000FF;  //byte#2 of CONSUMO REATIVO
      TxBuf[7]=(CR>>16)&0x000000FF; //byte#3 of CONSUMO REATIVO
      TxBuf[8]=(CR>>24)&0x000000FF; //MSB of CONSUMO REATIVO

      TxBuf[9]=TA&0x00FF;           //low byte of TA
      TxBuf[10]=TA>>8;              //high byte of TA

      TxBuf[11]=TR&0x00FF;          //low byte of TR
      TxBuf[12]=TR>>8;              //high byte of TR

      TxBuf[13]=TP&0x00FF;          //low byte of TP
      TxBuf[14]=TP>>8;              //high byte of TP
      Txlen=15;                                       
   }
}

/*************************************/
void proc_rcv()
{
      if( !Net_Waiting() )
         return;

      Txlen=1;
      if( InitFlag )
      {
         InitFlag=0;
         TxBuf[0]=CMD_INI;
      }
      else
      {
         TxBuf[0]=RxBuf[0];
         switch ( RxBuf[0] )
         {
   /*******************************************************************************/
   /*                           READ CALLS                                        */
   /*******************************************************************************/
            case RAS:               //10 - read all status
               TxBuf[1]=V_F1&0x00FF;        //low byte of VF1
               TxBuf[2]=V_F1>>8;            //high byte of VF1
               TxBuf[3]=V_F2&0x00FF;        //low byte of VF2
               TxBuf[4]=V_F2>>8;            //high byte of VF2
               TxBuf[5]=V_F3&0x00FF;        //low byte of VF3
               TxBuf[6]=V_F3>>8;            //high byte of VF3

               TxBuf[7]=I_F1&0x00FF;        //low byte of IF1
               TxBuf[8]=I_F1>>8;            //high byte of IF1
               TxBuf[9]=I_F2&0x00FF;        //low byte of IF2
               TxBuf[10]=I_F2>>8;           //high byte of IF2
               TxBuf[11]=I_F3&0x00FF;       //low byte of IF3
               TxBuf[12]=I_F3>>8;           //high byte of IF3

               TxBuf[13]=FP_F1&0x00FF;      //low byte of FPF1
               TxBuf[14]=FP_F1>>8;          //high byte of FPF1
               TxBuf[15]=FP_F2&0x00FF;      //low byte of FPF2
               TxBuf[16]=FP_F2>>8;          //high byte of FPF2
               TxBuf[17]=FP_F3&0x00FF;      //low byte of FPF3
               TxBuf[18]=FP_F3>>8;          //high byte of FPF3
               Txlen=19;                                       
               break;

            case RIS:               //12 - ler valor de uma(s) ENTRADA(s)
               read_vals(RxBuf[1]);
               break;

            case RMP:              //62 - ler parametros do módulo
               read_pars();
               break;

   /*******************************************************************************/
   /*                           WRITE CALLS                                       */
   /*******************************************************************************/
            case WUN: //56                   /* write unit */
               Rele=RxBuf[1];
               break;

            case WMP:                       //72 - write parametros do módulo
               write_pars();
               break;

   /*******************************************************************************/
   /*                           HSNET CALLS                                       */
   /*******************************************************************************/
            case CMD_WDA:
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

            case CMD_RDA:
               TxBuf[1]=read_eeprom(EEP_HSNETADR);
               TxBuf[2]=read_eeprom(EEP_HSNETADRE);
               Txlen=3;
               break;

            case CMD_RSV:
               Txlen=4;
               TxBuf[1]=VERS_MAJOR;
               TxBuf[2]=VERS_MINOR;
               TxBuf[3]=VERS_PATCH;
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
      net_send();
}


/*************************************/
void proc_apl()
{

}

/*************************************/
void main()
{
   setup_adc_ports( ALL_ANALOG );
   setup_adc(ADC_CLOCK_DIV_32);

   setup_counters(RTCC_INTERNAL,WDT_72MS);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   enable_interrupts(INT_RTCC);
   enable_interrupts(global);
   Net_Init( (int16)read_eeprom(EEP_HSNETADR)+(int16)read_eeprom(EEP_HSNETADRE) );
   for(;;)
   {
      proc_apl();
      proc_rcv();
   }
}
