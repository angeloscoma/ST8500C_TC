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
#include <18F6722.H>
#device *=16 ADC=10
#use delay(clock=1843200, restart_wdt)
#fuses XT,WDT128,NOPROTECT,PUT,BROWNOUT, NOLVP


#use rs232(baud = 2400, xmit=PIN_C6, rcv=PIN_C7, parity=N, bits=8, errors, stream = modbus)  
#use rs232(baud = 110, xmit=PIN_G1, rcv=PIN_G2, parity=N, bits=8, errors, stream = rep)  

#ignore_warnings 202, 203, 215
//#ignore_warnings 202,203,204


/* definição de hardware = ios */

/* equates */

#define CR	13
#define LF  10



/* DECLARACAO DE FUNCOES */
void main(void);

// Includes 
//#include <stdio.h>

//#include "st8610port.c"

#define CS_DISP		PIN_E1
#define CSIO1		PIN_E3
#define CSIO2		PIN_E4
#define CSIO3		PIN_E5
#define CSIO4		PIN_E6



struct DEF_SAIDA2
{
	short SD1 : 1;
	short SD2 : 1;
	short SD3 : 1;
	short SD4 : 1;
	short SD5 : 1;
	short SD6 : 1;
	short SD7 : 1;
	short SD8 : 1;
}SAIDA2;

struct DEF_SAIDA3
{
	short SD9 : 1;
	short SD10 : 1;
	short SD11 : 1;
	short SD12 : 1;
	short SD13 : 1;
	short SD14 : 1;
	short SD15 : 1;
	short SD16 : 1;
}SAIDA3;


#define valor_timer1  65536 - 1250			// 10 milisegundo
					// (0,010/(8/1000000)) = 1250
					// calculo: 65536-50000


/* Definicao das variaveis	de tratamento da comunicacao serial */
char ptrrx;
char retrx;
char numbrx;
char output_01;
char delay_rep;

#define TAM_RX  30

char buf_rx[TAM_RX+4];





void inic_rx()
{
	ptrrx = 0;
	retrx = 0;
	delay_ms(10);
	
}



/*
#INT_RDA
void serial(void)
{
	buf_rx[ptrrx++] = getc(modbus);   
	numbrx++;
	delay_rep = 2;
	
}
*/

#INT_TIMER1		//a cada 10 ms
void temporizador(void)
{   
	set_timer1(valor_timer1);
	if (delay_rep != 0)
		{
		delay_rep--;
		if (delay_rep == 0)
			{
			numbrx = 0;
			ptrrx = 0;
			retrx = 0;
			}
		}
}

#zero_ram
void main(void)
{
//	setup_oscillator( OSC_1MHZ | OSC_INTRC | OSC_STATE_STABLE);
	
	disable_interrupts(GLOBAL);

		//			 76543210
		set_tris_a(0b11101111);
		set_tris_b(0b11100011);
		set_tris_c(0b10010000);
		set_tris_d(0b00000000);
		set_tris_e(0b00000011);

		output_high (CSIO1);
		output_high (CSIO4);
	
		output_01 = saida2;
		output_low(CSIO2);
		output_d(output_01);
		output_high(CSIO2);

		output_01 = saida3;
		output_low(CSIO3);
		output_d(output_01);
		output_high(CSIO3);



/* define funcionamento do temporizador 1 */
/* define funcionamento do temporizador 1 */
	setup_timer_1(T1_INTERNAL|T1_DIV_BY_2);
	set_timer1(valor_timer1);
	enable_interrupts(INT_TIMER1);
	
	disable_interrupts(INT_TIMER3);

	inic_rx();

	set_uart_speed (2400, modbus);
	set_uart_speed (110, rep);

/* define funcionamento da uart */
//	enable_interrupts(INT_RDA);
	
/* define funcionamento da watchdog */
	setup_wdt(WDT_ON);
	restart_wdt();

	enable_interrupts(GLOBAL);

	numbrx = 0;
	ptrrx = 0;
	retrx = 0;
	while(TRUE) 
		{
		restart_wdt();
		
		switch(ptrrx)
			{
			case 0:
				{
				buf_rx[0] = getc(modbus);   
				numbrx = 1;
				break;
				}
			case 1:
				{
				buf_rx[1] = getc(modbus);   
				numbrx = 2;
				break;
				}
			case 2:
				{
				buf_rx[2] = getc(modbus);   
				numbrx = 3;
				break;
				}
			case 3:
				{
				buf_rx[3] = getc(modbus);   
				numbrx = 4;
				break;
				}
			case 4:
				{
				buf_rx[4] = getc(modbus);   
				numbrx = 5;
				break;
				}
			case 5:
				{
				buf_rx[5] = getc(modbus);   
				numbrx = 6;
				break;
				}
			case 6:
				{
				buf_rx[6] = getc(modbus);   
				numbrx = 7;
				break;
				}
			case 7:
				{
				buf_rx[7] = getc(modbus);   
				numbrx = 8;
				break;
				}
			}

		ptrrx++;   
		delay_rep = 2;
		
		if (numbrx == 8)
			{
//			disable_interrupts(INT_RDA);
//126,19,23,0,0,0,0,122
/*
			buf_rx[0] = 126;
			buf_rx[1] = 19;
			buf_rx[2] = 23;
			buf_rx[3] = 0;
			buf_rx[4] = 0;
			buf_rx[5] = 0;
			buf_rx[6] = 0;
			buf_rx[7] = 122;
*/

			buf_rx[8] = 0;	
			buf_rx[8] ^= buf_rx[0];
			buf_rx[8] ^= buf_rx[1];
			buf_rx[8] ^= buf_rx[2];
			buf_rx[8] ^= buf_rx[3];
			buf_rx[8] ^= buf_rx[4];
			buf_rx[8] ^= buf_rx[5];
			buf_rx[8] ^= buf_rx[6];

			buf_rx[8] = ~buf_rx[8];

			if (buf_rx[8] == buf_rx[7])
				{			
				buf_rx[10] = buf_rx[0];
				buf_rx[11] = buf_rx[1];
				buf_rx[12] = buf_rx[2];
				buf_rx[13] = buf_rx[3];
				buf_rx[14] = buf_rx[4];
				buf_rx[15] = buf_rx[5];
				buf_rx[16] = buf_rx[6];
				buf_rx[17] = buf_rx[7];
				ptrrx = 0;
				retrx = 0;
				numbrx = 0;
	//			enable_interrupts(INT_RDA);
				
				
				putc(buf_rx[10], rep);
				delay_us(10);
				putc(buf_rx[11], rep);
				delay_us(10);
				putc(buf_rx[12], rep);
				delay_us(10);
				putc(buf_rx[13], rep);
				delay_us(10);
				putc(buf_rx[14], rep);
				delay_us(10);
				putc(buf_rx[15], rep);
				delay_us(10);
				putc(buf_rx[16], rep);
				delay_us(10);
				putc(buf_rx[17], rep);

				output_01 = ptrrx;
				output_low(CSIO2);
				output_d(output_01);
				output_high(CSIO2);
				
				}
			else
				{
				buf_rx[10] = buf_rx[0];
				buf_rx[11] = buf_rx[1];
				buf_rx[12] = buf_rx[2];
				buf_rx[13] = buf_rx[3];
				buf_rx[14] = buf_rx[4];
				buf_rx[15] = buf_rx[5];
				buf_rx[16] = buf_rx[6];
				buf_rx[17] = buf_rx[7];
				
				
	//			enable_interrupts(INT_RDA);
				
				
				putc(buf_rx[10], rep);
				delay_us(10);
				putc(buf_rx[11], rep);
				delay_us(10);
				putc(buf_rx[12], rep);
				delay_us(10);
				putc(buf_rx[13], rep);
				delay_us(10);
				putc(buf_rx[14], rep);
				delay_us(10);
				putc(buf_rx[15], rep);
				delay_us(10);
				putc(buf_rx[16], rep);
				delay_us(10);
				putc(buf_rx[17], rep);
					
				ptrrx = 0;
				retrx = 0;
				numbrx = 0;

				output_01 = 0xf0;
				output_low(CSIO2);
				output_d(output_01);
				output_high(CSIO2);
				
				}
			}
		else
			{
			if (numbrx > 8)
				{
				ptrrx = 0;
				retrx = 0;
				numbrx = 0;
				}		
				
			output_01 = ptrrx;
			output_low(CSIO2);
			output_d(output_01);
			output_high(CSIO2);
						
			}

			
		}

}

// fim st8410_6722.c
