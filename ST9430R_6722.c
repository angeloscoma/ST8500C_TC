/************************************************************************
; Empresa: Sultech Sistemas Eletrônicos									*
; Modulo: Medidor Registrador de Grandezas Elétricas Trifásico			*
; Funcao: Definição de Funcionamento									*
; Responsável: Edison Valério											*
; Modificado ; Edison Valério											*
; Inicio: 01/08/2003													*
;************************************************************************/

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
#define st9430r					true
#define st9600r					false
#define st_prog					false
#define st8100c					false
#define st8200c					false
#define st8300c					false
#define st8500c					false

#define home_system				false

#define st5x					false
#define st94					true
#define st92					false
#define com_regs				true
#define SST25VF080				true
#define SST25LF080				false
#define cristal_10MHz			true
#define com_display 			false
#define portatil 				false
#define monofasico 				false
#define CONTROLADOR 			false
#define com_menu				true
#define disp_7seg				true
#define disp_lcd				false
#define com_rep					false
#define com_modbus				true

#define com_relogio				true
#define com_alarme				true

#define funcao_505 				true
#define fixa_modb				false

#define se_com_flex 			false

#define	tc_fixo					true
#define calcular_tc				false

//#define painel_6				true

// define tipo de sensor de energia
#define ad_microchip			true
#define chip_cs5460a			false
#define ade7754					false
#define sames_9904 				false
#define com_time_funciona		true

#define aju_time				false

//#define teste_painel			false

#define teste_digita_texto		false
#define tratar_localizacao		false

#define com_485  				true

#define com_cht					true
#define com_consumo				true
#define com_consumo_aparente	false
#define com_demanda				true
#define com_alarme_demanda		true

#define padrao_referencia		false

#define feira 					false
#define printa 					false
#define teste_vag				false
#define IFG 					false

#define rev_pci_st94 	13

#define protocolo_abb			true
#define com_gestal				true
#define teste_cht_vag			false
#define teste_home_system		false
#define teste_regs				false
#define teste_cht				false
#define debugar					false
#define versao_hsnet_calibra	false
#define fixar_parametro			false
#define teste_consumo			false
#define teste_protocolo_abb		false

#define prog_defasagem			false
#define GEBRAS					false
#define com_maximos				false
	
#define COR_CRITICA				40
#define COR_CRITICA_SOMA		9000		//3500
#define Magmattec				true
#define buffer_fixo				false
#define VALORES_FIXOS_MAX		true
#define novo_cht				true
#define debug_cht				false
#define teste_edison			false

#include "st_main.c"


// fim st9400_ad.c
