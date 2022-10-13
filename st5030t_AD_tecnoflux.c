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
#define TECNOFLUX true


#include <18F6720.H>
#device *=16 ADC=10
#if (TECNOFLUX == TRUE)
	#use delay(clock=20000000, restart_wdt)
#else
	#use delay(clock=24000000, restart_wdt)
#endif
#fuses HS,WDT128,NOPROTECT,PUT,BROWNOUT, NOLVP
//#opt 10

// definicoes de tipo de equipamento a ser compilado
// Vamos tentar manter os mesmos fontes para toda a linha nova, st50xxT, xt53xxT, st94xxR, st96xxR, st91xxr, st8x00C.
#define st5000t		false
#define st5030t		true
#define st5300t		false
#define st5330t		false
#define st8x00c		false
#define st9100r		false
#define st9200r		false
#define st9230r		false
#define st9400r		false
#define st9430r		false
#define st9600r		false
#define st_prog		false
#define st8100c		false
#define st8200c		false
#define st8300c		false
#define st8500c		false


#define st5x		true
#define st94		false
#define st92		false
#define com_regs	true
#define com_display false
#define portatil 	false
#define monofasico 	false
#define CONTROLADOR false
#define com_menu	false
#define disp_7seg	false
#define disp_lcd 	false
#define com_rep 	false
#define home_system	false
#define com_modbus	true



#define com_relogio		true

#define funcao_505 	false
#define fixa_modb	false

#define	tc_fixo		true
#define calcular_tc	false


// define tipo de sensor de energia
#define ad_microchip	true
#define chip_cs5460a	false
#define ade7754			false
#define sames_9904 		false


#define aju_time		false

#define teste_painel	false

#define teste_digita_texto	false
#define tratar_localizacao	false

#define com_485  		true

#define com_cht			true
#define com_consumo		true

#define painel_6  		false
#define painel_12 		true
#define cpu_rev1011		true

#define se_com_flex 		false
#define padrao_referencia	false
#define endereco_padrao		false
#define feira 				false
#define printa 				false
#define IFG					false
#define com_alarme_demanda 	false
#define teste_vag 			false
#define com_time_funciona	false
#define protocolo_abb		true
#define teste_protocolo_abb	false
#define teste_home_system	false
#define teste_cht_vag 		false
#define debugar				false
#define teste_calc_delta	false#define com_alarme			true#define teste_cht			false#define teste_consumo		false#define fixar_parametro		false#define teste_regs 			false
					

#include "st_main.c"


// fim st5000.c
