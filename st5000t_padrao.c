/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRONICOS                                  *
; Modulo: ST_MAIN                                                        *
; Funcao: MODULO PRINCIPAL DE CONTROLE ST9600R0   						 *
; 		Registrador Portatil de Grandezas Eletricas						 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 01/08/2003                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/
#define TECNOFLUX FALSE


#include <18F6722.H>
#device *=16 ADC=10
#if (TECNOFLUX == TRUE)
	#use delay(clock=20000000, restart_wdt)
	#fuses HS,WDT128,NOPROTECT,PUT,BROWNOUT, NOLVP
#else
	#use delay(clock=40000000, restart_wdt)
	#fuses H4,WDT128,NOPROTECT,PUT,BROWNOUT, NOLVP
#endif
//#opt 10

// definicoes de tipo de equipamento a ser compilado
// Vamos tentar manter os mesmos fontes para toda a linha nova, st50xxT, xt53xxT, st94xxR, st96xxR, st91xxr, st8x00C.
#define st5000t					true
#define st5030t					false
#define st5300t					false
#define st5330t					false
#define st8x00c					false
#define st9100r					false
#define st9200r					false
#define st9230r					false
#define st9400r					false
#define st9430r					false
#define st9600r					false
#define st_prog					false
#define st8100c					false
#define st8200c					false
#define st8300c					false
#define st8500c					false

#define st5x					true
#define st94					false
#define st92					false
#define com_regs				false
#define com_display 			false
#define portatil 				false
#define monofasico 				false
#define CONTROLADOR 			false
#define com_menu				false
#define disp_7seg				false
#define disp_lcd 				false
#define com_rep 				false
#define com_modbus				true


#define home_system				false

#define cristal_10MHz			true
#define st5000c_rev12			false
#define com_saida_pulsos		false
#define com_consumo_aparente	false
#define teste_edison			false

#define com_relogio				false

#define funcao_505 				false
#define fixa_modb				false

#define	tc_fixo					true
#define calcular_tc				false


// define tipo de sensor de energia
#define ad_microchip			true
#define chip_cs5460a			false
#define ade7754					false
#define sames_9904 				false


#define aju_time				false

#define teste_painel			false

#define teste_digita_texto		false
#define tratar_localizacao		false

#define com_485  				true


#define rev_11 					false
#define painel_6 				false
#define painel_12				true
#define cpu_rev1011				true

#define feira					false
#define printa 					false
#define IFG						false
#define IFG_128 				false
#define se_com_flex 			false

#define padrao_referencia		true

#if (padrao_referencia == true)
	#define com_consumo			false
	#define com_cht				false
	#define endereco_padrao		true
#else
	#define com_consumo			true
	#define com_cht				true
	#define endereco_padrao		false
#endif


#define teste_vag 				false
#define com_alarme_demanda 		false

#define protocolo_abb			false
#define teste_protocolo_abb 	false
		
#define com_time_funciona		false

#define teste_home_system		false
#define teste_regs				false

#define debugar					false
#define teste_calc_delta		false
#define com_alarme				true
#define teste_cht				false
#define teste_consumo			false
#define fixar_parametro			false
#define prog_defasagem			false
#define GEBRAS					false
#define com_gestal				false
#define endereco_via_serial		false
#define versao_hsnet_calibra	false
#define buffer_fixo				false
#define VALORES_FIXOS_MAX		false

#define Magmattec				true
#define novo_cht				false


#include "st_main.c"


// fim st5000.c
