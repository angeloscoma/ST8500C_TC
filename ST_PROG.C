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
//#opt 10

//#priority int_timer3, int_ext, int_rda, int_timer1, int_ext1		//INT_TIMER3, INT_EXT, INT_RDA, INT_TIMER1, INT_EXT1

// definicoes de tipo de equipamento a ser compilado
// Vamos tentar manter os mesmos fontes para toda a linha nova, st50xxT, xt53xxT, st94xxR, st96xxR, st91xxr, st8x00C.
#define st5000t							false
#define st5030t							false
#define st5300t							false
#define st5330t							false
#define st8x00c							false
#define st9100r							false
#define st9200r							false
#define st9230r							false
#define st9400r							false
#define st9430r							false
#define st9600r							false
#define st_prog							true
#define st8100c							false
#define st8200c							false
#define st8300c							false
#define st8500c							false

#define home_system						false

#define cristal_10MHz					false
#define com_consumo_aparente			false
#define prog_defasagem					false
#define GEBRAS							false
#define padrao_referencia				false

#define st5x							false
#define st92							false
#define st94							false
#define com_regs						false
#define com_display 					true
#define portatil 						false
#define monofasico 						false
#define CONTROLADOR 					false
#define com_menu						true
#define com_rep							false
#define disp_7seg						false
#define disp_lcd						true
#define	com_modbus						true

#define sa9904							false
#define funcao_505 						false
#define ad_microchip					true
#define com_relogio						false
#define ade7754							false
#define chip_cs5460a					false

#define fixa_modb 						true
#define aju_time						false
#define com_cht							false
#define com_consumo						false


#define tc_fixo 						true
#define calcular_tc						false

#define com_485							true
#define IFG								false
#define teste_vag						false
#define sames_9904						false
#define com_time_funciona				false
#define feira 							false
#define printa							false
#define com_alarme_demanda				false
#define protocolo_abb					false
#define se_com_flex						false

#define NRO_MAXIMO_BANCOS_CAPACITOR		16
#define MAIOR_BANCO_POSSIVEL			250
#define NRO_SEQUENCIAS					20

#define novo_REP						true

#define teste_digita_texto				false
#define tratar_localizacao				false

#define teste_home_system				false
#define simula_rep						true

#define AUTOSET 						false
#define teste_regs 						false

#define debugar							false
#define controle_por_fase				false
#define com_alarme						false
#define com_gestal						false
#define viercon							false
#define versao_pci_st96					false
#define teste_consumo					false
#define teste_cht						false
#define teste_edison					false
#define versao_hsnet_calibra			false
#define fixar_parametro					false

#define novo_cht						false
#define debug_cht						false
#define buffer_fixo						false
#define VALORES_FIXOS_MAX				false
#define Magmattec						false

#include "st_main.c"

// fim st5000.c
