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
#opt 9

// definicoes de tipo de equipamento a ser compilado
// Vamos tentar manter os mesmos fontes para toda a linha nova, st50xxT, xt53xxT, st94xxR, st96xxR, st91xxr, st8x00C.
#define st5000t		false
#define st5030t		false
#define st5300t		false
#define st5330t		false
#define st8x00c		false
#define st9100r		false
#define ST9200R		false
#define ST9230R		false
#define st9400r		false
#define st9430r		false
#define st9600r		false
#define st_prog		false
#define st8100c		true
#define st8200c		false
#define st8300c		false
#define st8500c		false

#define home_system	false


#define st5x		false
#define st94		false
#define st92		false
#define com_regs	true
#define com_display false
#define portatil 	false
#define monofasico 	true
#define CONTROLADOR true
#define com_menu	true
#define disp_7seg	true
#define disp_lcd	false
#define com_rep 	false
#define com_modbus	true
#define com_alarme	true

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
#define com_cht			true
#define com_consumo		false

#define com_alarme_demanda	false
#define com_time_funciona false
#define rotacionar true

#define bancos_12 false


#define pci_st8200		2


#define se_com_flex	false


#define MAIOR_BANCO_POSSIVEL	250		//  (Q1 ,  250/2 = 125KVAR
#define NRO_MAXIMO_BANCOS_CAPACITOR	12
#define NRO_SEQUENCIAS	22

#define feira false
#define printa 			false

#define IFG 	false

#define simula_forno	false
#define teste_vag 		false

#define AUTOSET false
#define DESLIGA_F5	TRUE

#define protocolo_abb	FALSE

#define teste_cht_vag	false
#define teste_home_system	false
#define teste_regs		false

#define debugar		false
#define teste_cht 		false
#define teste_consumo	false
#define fixar_parametro	false

#define teste_calc_delta	false
#define teste_aciona_rele	false
#define controle_por_fase 	false
#define versao_hsnet_calibra false
#define com_gestal	true
#define prog_defasagem	false
#define GEBRAS false

#include "st_main.c"


// fim st8410_6722.c
