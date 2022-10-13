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
#use delay(clock=40000000, restart_wdt)
#fuses H4, WDT4096, NOPROTECT, BROWNOUT,  NOLVP, MCLR, NOIESO, NOFCMEN, NOSTVREN, NOXINST
//#fuses H4, WDT4096, NOPROTECT, BROWNOUT, BORV43, NOLVP, MCLR, DEBUG, NOIESO, NOFCMEN, NOSTVREN, NOXINST
//#fuses H4,WDT4096,NOPROTECT,PUT,BROWNOUT, BORV43, NOLVP, MCLR, STVREN

//#priority int_timer3, int_ext, int_rda, int_timer1, int_ext1		//INT_TIMER3, INT_EXT, INT_RDA, INT_TIMER1, INT_EXT1

// definicoes de tipo de equipamento a ser compilado
// Vamos tentar manter os mesmos fontes para toda a linha nova, st50xxT, xt53xxT, st94xxR, st96xxR, st91xxr, st8x00C.
#define st5000t			false
#define st5030t			false
#define st5300t			false
#define st5330t			false
#define st8x00c			false
#define st9100r			false
#define st9400r			false
#define st9430r			false
#define st9600r			true
#define st_prog			false
#define st8610c			false
#define st8620c			false
#define st8600c			false


#define st5x		false
#define st94		false
#define com_regs	true
#define com_display true
#define portatil 	true
#define monofasico 	false
#define CONTROLADOR false
#define com_menu	true
#define disp_7seg	false


#define funcao_505 		true
#define ad_microchip	true
#define com_relogio		true
#define ade7754			false
#define chip_cs5460a	false
#define sames_9904 		false

#define fixa_modb 		true
#define aju_time		false


#define tc_fixo 	false

#define tratar_localizacao	true
//#define tratar_sensores_corrente	false

#define com_485  		false

#define com_cht			true
#define com_consumo		true

#define rev_11 false
#define pci_r04	true

#define teste_baud_115	false

#include "st_main.c"


// fim st5000.c
