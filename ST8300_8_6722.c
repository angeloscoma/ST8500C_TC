/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETR�NICOS                                  *
; Modulo: ST_MAIN                                                        *
; Funcao: MODULO PRINCIPAL DE CONTROLE ST9600R0   						 *
; 		Registrador Port�til de Grandezas El�tricas Trif�sico            *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 01/08/2003                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/

#include <18F6722.H>
#device *=16 ADC=10
#use delay(clock=40000000, restart_wdt)
#fuses H4,WDT128,NOPROTECT,PUT,BROWNOUT, NOLVP

//#opt 10

// definicoes de tipo de equipamento a ser compilado
// Vamos tentar manter os mesmos fontes para toda a linha nova, st50xxT, xt53xxT, st94xxR, st96xxR, st91xxr, st8x00C.
#define st5000t					false
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
#define st8300c					true
#define st8500c					false

#define st5x					false
#define st94					false
#define st92					false
#define com_regs				true
#define portatil 				false
#define monofasico 				false
#define CONTROLADOR 			true
#define com_menu				true
#define com_rep					false
#define com_modbus				true
#define home_system				false
#define protocolo_abb			false
#define com_gestal 				false
#define com_alarme				true

#define	SST25LF080				false
#define	SST25VF080				true

#define com_consumo_aparente	false
#define padrao_referencia		false

#if (com_menu == true)
	#define com_display 		true
	#define disp_7seg			false
	#define disp_lcd			true
#else
	#define com_display 		false
	#define disp_7seg			false
	#define disp_lcd			false
#endif

#define com_relogio				true

#define funcao_505 				false
#define fixa_modb				false

#define	tc_fixo					true
#define calcular_tc				false


//#define painel_6	true

// define tipo de sensor de energia
#define ad_microchip			false
#define chip_cs5460a			false
#define ade7754					false
#define sames_9904 				false

#define aju_time				false
#define com_485  				true

//#define teste_painel			false

#define teste_digita_texto		false
#define tratar_localizacao		false
#define com_cht					true
#define com_consumo				true
#define com_demanda				false
#define com_time_funciona		false
#define rotacionar 				true
#define prog_defasagem			true

//#define pci_r01 true
#define rev_01					true

#define feira 					false
#define printa					false
#define IFG						false

#define se_com_flex				false

#define teste_vag 				false
#define com_alarme_demanda 		false
#define AUTOSET					false
#define DESLIGA_F5				true

#define teste_cht_vag			false
#define teste_home_system		false
#define teste_regs				false

#define debugar					false
#define teste_cht				false
#define teste_consumo			false
#define fixar_parametro			false
#define teste_calc_delta 		false
#define versao_hsnet_calibra	false
#define controle_por_fase 		false
#define GEBRAS					false

#define MAIOR_BANCO_POSSIVEL		250		//  (Q1 ,  250/2 = 125KVAR
#define NRO_MAXIMO_BANCOS_CAPACITOR	8
#define NRO_SEQUENCIAS				22

#define debug_cht				false
#define novo_cht				false
#define buffer_fixo				false
#define VALORES_FIXOS_MAX		false
#define Magmattec				true
#define teste_edison			false
#define MALA_FEIRA				false

#include "st_main.c"


// fim st8600.c