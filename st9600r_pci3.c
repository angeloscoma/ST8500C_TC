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
#fuses H4,WDT128,NOPROTECT,PUT,BROWNOUT, NOLVP
//#opt 11

//#priority int_timer3, int_ext, int_rda, int_timer1, int_ext1		//INT_TIMER3, INT_EXT, INT_RDA, INT_TIMER1, INT_EXT1

// definicoes de tipo de equipamento a ser compilado
// Vamos tentar manter os mesmos fontes para toda a linha nova, st50xxT, xt53xxT, st94xxR, st96xxR, st91xxr, st8x00C.
#define st5000t					false
#define st5030t					false
#define st5300t					false
#define st5330t					false
#define st8x00c					false
#define st8100c					false
#define st8200c					false
#define st8300c					false
#define st9100r					false
#define st9200r					false
#define st9230r					false
#define st9400r					false
#define st9430r					false
#define st9600r					true
#define st9600e					false
#define st_prog					false
#define st8500c					false

#define st5x					false
#define st94					false
#define st92					false
#define com_regs				true
#define com_display 			true
#define portatil 				true
#define monofasico 				false
#define CONTROLADOR 			false
#define com_menu				true
#define disp_7seg				false
#define disp_lcd  				true
#define com_modbus				true
#define home_system				false
#define com_gestal				false
#define GEBRAS					false


#define funcao_505 				true
#define ad_microchip			true
#define com_relogio				true
#define ade7754					false
#define chip_cs5460a			false
#define sames_9904 				false

#define fixa_modb 				true
#define aju_time				false

#define com_rep					false
#define simula_rep				false


#define tratar_localizacao		true
//#define tratar_sensores_corrente	false

#define com_485  				false

#define com_cht					true
#define com_consumo				true
#define com_demanda 			true



#define versao_pci_st96			3

#define se_com_flex				false

#if (se_com_flex == true)
	#define tc_fixo 			true
#else
	#define tc_fixo 			false
	#define viercon				false
	#define sazi				false
#endif

#define IFG						false
#define teste_baud_115			false

#define feira  					false
#define printa 					false

#define teste_vag 				false

#define com_alarme_demanda 		false
#define com_time_funciona 		false

#define protocolo_abb 			false
#define ponteira_kyoritsu		false
#define teste_cht_vag 			false
#define teste_home_system 		false
#define teste_regs				false
#define teste_coletas			false

#define debugar					false
#define teste_calc_delta 		false

#define com_alarme				true
#define teste_cht 				false
#define teste_consumo			false
#define fixar_parametro 		false
#define versao_hsnet_calibra 	false

#define SST25VF040				true
#define SST25VF080				false
#define SST25LF080				false
#define debug_cht				false
#define novo_cht				true
#define com_consumo_aparente	false
#define VALORES_FIXOS_MAX		false
#define prog_defasagem			false
#define st5000c_rev12			false
#define teste_edison			false
#define padrao_referencia		false
#define buffer_fixo				false
#define cristal_10MHz			true

#include "st_main.c"

#if (tc_fixo == true)
	#error /// A T E N C A O   RESOLVER A EXIBICÃO DE CONSUMOS E DEMANDAS QUANDO TC FIXO EM ST_EXIB.C ***********************
	
#endif

// fim st5000.c
