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

#include <18F6720.H>
#device *=16 ADC=10
#use delay(clock=24000000, restart_wdt)
#fuses HS,WDT128,NOPROTECT,PUT,BROWNOUT, NOLVP

//#priority INT_EXT2

//#opt 10

// definicoes de tipo de equipamento a ser compilado
// Vamos tentar manter os mesmos fontes para toda a linha nova, st50xxT, xt53xxT, st94xxR, st96xxR, st91xxr, st8x00C.
#define st5000t			false
#define st5030t			true
#define st5300t			false
#define st5330t			false
#define st8x00c			false
#define st9100r			false
#define st9400r			false
#define st9430r			false
#define st9600r			false

#define com_relogio		true

#define funcao_505 false

#define	tc_fixo		true
#define calcular_tc	false

#define painel_6	true
#define fixa_modb	false

// define tipo de sensor de energia
#define ad_microchip	false
#define chip_cs5460a	false

#define ade7754			true
#define aju_time		false


#include "st_main.c"


// fim st5000.c
