/*************************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_MAIN                                                        *
; Funcao: MODULO PRINCIPAL DE CONTROLE ST9600R0   						 *
; 		  Registrador Portátil de Grandezas Elétricas Trifásico          *
; Responsavel: VAGNER SANTOS											 *
; Modificado : VAGNER SANTOS                                             *
; Inicio: 01/08/2003                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/

//#include "C:\Arquivos de programas\PICC\devices\18F6720.H"
#include "E:\Arquivos de programas\PICC\devices\18F6722.H"
//#include <18F6722.H>
#device *=16 ADC=10
#use delay(clock=24000000, restart_wdt)
#fuses HS,WDT128,NOPROTECT,PUT,BROWNOUT, NOLVP
//#opt 11

//#priority int_timer3, int_ext, int_rda, int_timer1, int_ext1		//INT_TIMER3, INT_EXT, INT_RDA, INT_TIMER1, INT_EXT1

// definicoes de tipo de equipamento a ser compilado
// Vamos tentar manter os mesmos fontes para toda a linha nova, st50xxT, xt53xxT, st94xxR, st96xxR, st91xxr, st8x00C.
#define st5000t					false
#define st5030t					false
#define st5300t					false
#define st5330t					false
#define ST8100C					false
#define ST8200C					false
#define ST8300C					false
#define ST8500C					false
#define st8x00c					false
#define st8610c					false
#define st8620c					false
#define st8600c					false
#define st9100r					false
#define st9200r					false
#define st9230r					false
#define st9400r					false
#define st9430r					false
#define st9600r					true
#define st9600e					false
#define st_prog					false


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

#define SST25VF080 				true
#define	SST25LF080 				false
#define cristal_10MHz			false

#define tratar_localizacao		true

#define com_485  				false

#define com_cht					true
#define com_consumo				true
#define com_demanda 			true
#define com_gestal 				true
#define GEBRAS					false

#define versao_pci_st96			6

#define teste_vag				false
#define teste_cht_vag			false
#define teste_coletas			false
#define teste_home_system		false

#define com_modbus				true
#define protocolo_abb			false
#define home_system				false
#define com_alarme_demanda		false
#define com_time_funciona		false
#define ponteira_kyoritsu		false

#define com_consumo_aparente	false
#define prog_defasagem			false
#define padrao_referencia		false

#define st5000c_rev12			false

#define se_com_flex				true
#define flex_engro				true

#if (se_com_flex == true)
	#define tc_fixo 			true
#else
	#define tc_fixo 			false
#endif

#define IFG						false
#define teste_baud_115			false

#define feira  					false
#define printa 					false
#define teste_edison			false

#define debugar 				false
#define com_alarme 				false
#define teste_cht 				false
#define teste_consumo 			false
#define versao_hsnet_calibra 	false
#define teste_regs				false
#define fixar_parametro			false

#define selecao_pt_auto 		true

/// clientes
#define viercon 				false
#define sazi 					false
#define correia					true

#define novo_cht				true
#define debug_cht				false

#define buffer_fixo				false
#define VALORES_FIXOS_MAX		false

#include "st_main.c"

/// A T E N C A O   RESOLVER A EXIBICÃO DE CONSUMOS E DEMANDAS QUANDO TC FIXO EM ST_EXIB.C ***********************

// fim st5000.c
