/*;**********************************************************************
; Empresa: Sultech Sistemas Eletrônicos                                 *
; Modulo: Teste SST25VF040												*
; Funcao: Acesso à memória flash										*
; Responsavel: Edison Valério											*
; Inicio: 09/06/2008                                                    *
;************************************************************************/

#include <18F6720.H>
#device *=16 ADC=10
#use delay(clock=24000000, restart_wdt)
#fuses HS,WDT128,NOPROTECT,PUT,BROWNOUT, NOLVP

#define FLASH_CLK	PIN_C3
#define FLASH_SI	PIN_C5
#define FLASH_SO	PIN_C4
#define FLASH_CE	PIN_B3
#define Flash_Hold	PIN_G0
#define Flash_WP	PIN_G0

#define valor_timer1  65536 - (30000)	// 10 ms
										// (0,010/(8/24000000)) = 3000
										// calculo: 65536-30000
#use fast_io (D)

#include "C:\Arquivos de programas\PICC\drivers\math.H"
#include "C:\Arquivos de programas\PICC\drivers\stdio.H"
#include "C:\Arquivos de programas\PICC\drivers\stdlib.h"
#include "25VF040.C"
//#include "verifica_vf.c"

short ler_flash;
char conta;

#INT_TIMER1
void Temporizador(void)
{   
	set_timer1(valor_timer1);
	conta++;
	if (conta > 4){
		output_toggle(PIN_C0);
		conta = 0;
		ler_flash = 1;
	}
}

void main(void){

	//			 76543210
	set_tris_a(0b11111111);
	set_tris_b(0b11111111);
	set_tris_c(0b10010000);
	set_tris_d(0b00000000);
	set_tris_e(0b00000011);
	set_tris_g(0b11111110);
		
	setup_timer_1(T1_INTERNAL|T1_DIV_BY_2);
	set_timer1(valor_timer1);
	enable_interrupts(INT_TIMER1);

//	setup_timer_2(T2_DISABLED,0,1);
//	setup_timer_3(T3_DISABLED,0,1);
//	setup_timer_4(T4_DISABLED,0,1);
	
	ext_int_edge(0,H_TO_L);
	enable_interrupts(INT_EXT);
	ext_int_edge(1,H_TO_L);
	enable_interrupts(INT_EXT1);
	
	setup_wdt(WDT_ON);
	restart_wdt();

	setup_spi(SPI_MASTER | SPI_L_TO_H | SPI_CLK_DIV_16);

	setup_adc_ports(AN0_TO_AN4 | VSS_VDD);
	setup_adc(ADC_CLOCK_INTERNAL);
	
	enable_interrupts(GLOBAL);
	
	ler_flash = 0;
	conta = 0;
	
	while(true){
		restart_wdt();
		if (ler_flash == 1){
			Le_Hardware();
			ler_flash = 0;
		}
	}
}

