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

#include <18F4620.H>
#device *=16 ADC=10
#use delay(clock=40000000, restart_wdt)
#fuses H4, WDT4096, NOPROTECT, BROWNOUT, BORV43, NOLVP, MCLR, NOIESO, NOFCMEN, NOSTVREN, NOXINST
//#fuses H4, WDT4096, NOPROTECT, BROWNOUT, BORV43, NOLVP, MCLR, DEBUG, NOIESO, NOFCMEN, NOSTVREN, NOXINST
//#fuses H4,WDT4096,NOPROTECT,PUT,BROWNOUT, BORV43, NOLVP, MCLR, STVREN
#opt 9

// definicoes de tipo de equipamento a ser compilado
// Vamos tentar manter os mesmos fontes para toda a linha nova, st50xxT, xt53xxT, st94xxR, st96xxR, st91xxr, st8x00C.
#define st5000t		false
#define st5030t		false
#define st5300t		false
#define st5330t		false
#define st8x00c		false
#define st9100r		false
#define st9400r		false
#define st9430r		false
#define st9600r		false
#define st_prog		false
#define st8610c		true
#define st8620c		false
#define st8600c		false


#define st5x		false
#define st94		false
#define com_regs	false
#define com_display false
#define portatil 	false
#define monofasico 	true
#define CONTROLADOR true
#define com_menu	true
#define disp_7seg	true
#define disp_lcd	false


#define com_relogio		false

#define funcao_505 	false
#define fixa_modb	false

#define	tc_fixo		true
#define calcular_tc	false

//#define painel_6	true

// define tipo de sensor de energia
#define ad_interno_10bits	true
#define ad_microchip	false
#define chip_cs5460a	false
#define ade7754			false
#define sames_9904 		false

#define aju_time		false

#define com_485  		false

//#define teste_painel	false

#define teste_digita_texto	false
#define tratar_localizacao	false
#define com_cht			false
#define com_consumo		false

#define pci_r01  false

#define teste_carga	true

#define NRO_SEQUENCIAS		22
#define NRO_MAXIMO_BANCOS_CAPACITOR	12


#if (teste_carga == true)
	#include "st_main_teste_carga.c"
#else
	#include "st_main.c"
#endif	


// fim st8410_4620.c
