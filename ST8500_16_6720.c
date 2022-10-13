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
//#use delay(clock=24000000)
#fuses HS,WDT128,NOPROTECT,PUT,BROWNOUT, NOLVP


//#opt 10

// definicoes de tipo de equipamento a ser compilado
// Vamos tentar manter os mesmos fontes para toda a linha nova, st50xxT, xt53xxT, st94xxR, st96xxR, st91xxr, st8x00C.
#define st5000t		false
#define st5030t		false
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
#define st8500c		true


#define st5x		false
#define st94		false
#define st92		false
#define com_regs	true
#define portatil 	false
#define monofasico 	false
#define CONTROLADOR true
#define com_menu	true
#define com_rep		true
#define com_modbus 	true
#define home_system false
#define com_alarme	true
#define com_tc 		false




#if (com_menu == true)
	#define com_display true
	#define disp_7seg	false
	#define disp_lcd	true
#else
	#define com_display false
	#define disp_7seg	false
	#define disp_lcd	false
#endif

#define com_relogio		true

#define funcao_505 	false
#define fixa_modb	false

#define	tc_fixo		true
#define calcular_tc	false

//#define painel_6	true

// define tipo de sensor de energia
#define ad_microchip	false
#define chip_cs5460a	false
#define ade7754			false
#define sames_9904 		false

#define aju_time		false

#define com_485  		true

//#define teste_painel	false

#define teste_digita_texto	false
#define tratar_localizacao	false
#define com_cht				false
#define com_consumo			false
#define com_alarme_demanda	true
#define com_time_funciona 	false
#define AUTOSET 			false
#define DESLIGA_F5			true
#define rotacionar			false


//#define pci_r01 true
#define rev_01	true

#define feira 	false
#define printa	false
#define IFG		false

#define se_com_flex	false
#define pci_mono	false


#define MAXIMA_CARGA_TOTAL	250*16
#define MAXIMA_CARGA		250

#define NRO_MAXIMO_CARGAS	16

#define teste_vag	false
#define simula_forno	false


#define controle_demanda	true
#define protocolo_abb		false


#define teste_cht_vag 	false
#define teste_home_system false
#define teste_regs		false

#define debugar			false
#define teste_consumo	false
#define fixar_parametro	false

#define teste_calc_delta false
#define controle_por_fase false
#define versao_hsnet_calibra false
#define com_gestal	true
#define GEBRAS		false
#define prog_defasagem	false

#define cristal_10MHz			false
#define SST25VF080				false
#define SST25LF080				false
#define SST25VF040				true
#define com_consumo_aparente	false
#define novo_cht				false
#define padrao_referencia		false
#define teste_edison			false


#include "st_main.c"


// fim st8600.c
