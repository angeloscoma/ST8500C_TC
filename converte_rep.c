/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_MAIN                                                        *
; Funcao: MODULO PRINCIPAL DE CONTROLE ST9600R0   						 *
; 		Registrador Portátil de Grandezas Elétricas Trifásico            *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 01/08/2003                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/
#include <18F1220.H>
#device *=16 ADC=10
#use delay(clock=1843200,RESTART_WDT)
#fuses XT,WDT128,NOPROTECT,PUT,BROWNOUT, NOLVP


#use rs232(baud = 110, xmit=PIN_B1,  rcv=PIN_B4,RESTART_WDT,  parity=N, bits=8, errors, stream = rep)  
#use rs232(baud = 2400, xmit=PIN_B0,  RESTART_WDT, parity=N, bits=8, errors, stream = sultech)  


#ignore_warnings 202, 203, 215
//#ignore_warnings 202,203,204

#define calcula_rep false
#define rep_int	false
#define word int16
/* definição de hardware = ios */

/* equates */

#define CR	13
#define LF  10

const char cequipo[11] = "CREP-V1.02";


/* DECLARACAO DE FUNCOES */
void main(void);


/* Definicao das variaveis	de tratamento da comunicacao serial */
char ptrrx;
char delay_rep;

char morder;
char morder_rda;
char recebeu_rep;

word time_out_rst;

#define TAM_RX  32

char buf_rx[TAM_RX+4];
char buf_rx_tmp[TAM_RX+4];
//						  01234567890





#define valor_timer1  65536 - 23040			// 100 milisegundo
					// (0,100/(8/1843200)) = 23040


#INT_RDA
void serial(void)
{
	buf_rx[ptrrx++] = getc(rep);   
	delay_rep = 1;
	time_out_rst = 0;
	morder_rda = 1;
	if (ptrrx > 7)
		{
		recebeu_rep = 1;
		ptrrx = 0;
		
		buf_rx_tmp[0] = buf_rx[0];
		buf_rx_tmp[1] = buf_rx[1];
		buf_rx_tmp[2] = buf_rx[2];
		buf_rx_tmp[3] = buf_rx[3];
		buf_rx_tmp[4] = buf_rx[4];
		buf_rx_tmp[5] = buf_rx[5];
		buf_rx_tmp[6] = buf_rx[6];
		buf_rx_tmp[7] = buf_rx[7];
/*		
		buf_rx_tmp[0] = 161;
		buf_rx_tmp[1] = 129;
		buf_rx_tmp[2] = 146;
		buf_rx_tmp[3] = 0;
		buf_rx_tmp[4] = 0;
		buf_rx_tmp[5] = 0;
		buf_rx_tmp[6] = 0;
		buf_rx_tmp[7] = 77;
*/		
		}
}

#INT_TIMER1		//a cada 100 ms
void temporizador(void)
{   
	set_timer1(valor_timer1);
	morder = 1;
	time_out_rst++;
	if (delay_rep != 0)
		{
		delay_rep--;
		}
	else
		{
		ptrrx = 0;
		}
}


#zero_ram
void main(void)
{
//	setup_oscillator( OSC_1MHZ | OSC_INTRC | OSC_STATE_STABLE, 31);
	
	disable_interrupts(GLOBAL);

		//			 76543210
	set_tris_a(0b11111111);
	set_tris_b(0b11111100);

	setup_wdt(WDT_ON);
	restart_wdt();

/* define funcionamento do temporizador 1 */
	setup_timer_1(T1_INTERNAL|T1_DIV_BY_2);
	set_timer1(valor_timer1);
	enable_interrupts(INT_TIMER1);
	
	set_uart_speed (110, rep);
	set_uart_speed (2400, sultech);
	
/* define funcionamento da watchdog */
	time_out_rst = cequipo[ptrrx];			// somente para constar o nome e versão no arquivo hex

	ptrrx = 0;
	time_out_rst = 0;

/* define funcionamento da uart */
	enable_interrupts(INT_RDA);

	enable_interrupts(GLOBAL);

	
	while(TRUE) 
		{
		if ((morder == 1) && (morder_rda == 1))
			{
			morder = 0;
			morder_rda = 0;
			restart_wdt();
			}
		if (time_out_rst > 120)
			{
			reset_cpu();
			}
			
		if (recebeu_rep == 1)
			{
			recebeu_rep = 0;
			disable_interrupts(INT_RDA);
			disable_interrupts(INT_TIMER1);
			putc(buf_rx_tmp[0], sultech);
			putc(buf_rx_tmp[1], sultech);
			putc(buf_rx_tmp[2], sultech);
			putc(buf_rx_tmp[3], sultech);
			putc(buf_rx_tmp[4], sultech);
			putc(buf_rx_tmp[5], sultech);
			putc(buf_rx_tmp[6], sultech);
			putc(buf_rx_tmp[7], sultech);
			enable_interrupts(INT_TIMER1);
			enable_interrupts(INT_RDA);
			ptrrx = 0;
			delay_rep = 1;
			}
	
			
		}

}


