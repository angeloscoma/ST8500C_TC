//***********************************************************************
// Empresa: Sultech Sistemas Eletrônicos								*
// Módulo: Configuração													*
// Função: Definir o funcionamento do equipamento						*
// Responsável: Edison Valério Nunes Junior								*
// Modificado: Edison Valério Nunes Junior								*
// Inicio: 01/08/2003													*
// Revisão: Edison Valério Nunes Junior									*
//***********************************************************************

#include <18F67K22.H>
#device *=16 ADC=12
#use delay(clock=40000000, restart_wdt)
#fuses HSH,WDT128,NOPROTECT,PUT,BROWNOUT,SOSC_DIG,RTCOSC_INT

// definicoes de tipo de equipamento a ser compilado
// Vamos tentar manter os mesmos fontes para toda a linha nova, st50xxT, xt53xxT, st94xxR, st96xxR, st91xxr, st8x00C.
#define st5000t						false
#define st5030t						false
#define st5300t						false
#define st5330t						false
#define st8x00c						false
#define st9100r						false
#define st9200r						false
#define st9230r						false
#define st9400r						false
#define st9430r						false
#define st9600r						false
#define st_prog						false
#define st8100c						false
#define st8200c						false
#define st8300c						false
#define st8500c						true

#define st5x						false
#define st94						false
#define st92						false
#define com_regs					true
#define portatil 					false
#define monofasico 					false
#define CONTROLADOR 				true
#define com_menu					true
#define com_rep						false
#define com_modbus 					true
#define home_system 				false
#define com_alarme					true
#define com_tc						true
#define instantaneo					false

#if (com_menu == true)
	#define com_display 			true
	#define disp_7seg				false
	#define disp_lcd				true
#else
	#define com_display 			false
	#define disp_7seg				false
	#define disp_lcd				false
#endif

#define com_relogio					true
#define SST25LF080					false
#define SST25VF080					true

#define com_consumo_aparente		false
#define padrao_referencia 			false
#define teste_edison				false

#define funcao_505 					false
#define fixa_modb					false

#define	tc_fixo						true
#define calcular_tc					false

//#define painel_6					true

// define tipo de sensor de energia
#define ad_microchip				false
#define chip_cs5460a				false
#define ade7754						false
#define sames_9904 					false

#define aju_time					false

#define com_485  					true

//#define teste_painel				false

#define teste_digita_texto			false
#define tratar_localizacao			false
#define com_cht						false
#if (com_tc == true)
	#define com_consumo				true
	#define com_demanda 			true
#else
	#define com_consumo				false
	#define com_demanda 			false
#endif
#define com_alarme_demanda			true
#define com_time_funciona 			false
#define AUTOSET 					false
#define DESLIGA_F5					true
#define rotacionar					false

#define rev_01						true

#define feira 						false
#define printa						false

#define se_com_flex					false
#define pci_mono					false

#define MAXIMA_CARGA_TOTAL			250*16		// 250kW * 16 Bancos = 4000kW
#define MAXIMA_CARGA				250			// 250kW / Banco
#define CARGA_INSTALADA_MAX			65000		// 4000kW / 0,05 = 80000kW -> O total de cargas controladas corresponde
#define NRO_MAXIMO_CARGAS			16			// a pelo menos 5% da carga instalada. Porém temos o limite int16 (65535)

#define simula_forno				false


#define controle_demanda			true
#define protocolo_abb				false
#define teste_cht_vag 				false
#define teste_home_system 			false
#define teste_regs					false

#define debugar						false
#define teste_consumo				false
#define fixar_parametro				false
#define controle_por_fase 			false
#define versao_hsnet_calibra 		false
#define com_gestal 					true
#define GEBRAS						false
#define prog_defasagem 				true
#define novo_cht					false
#define MALA_FEIRA					false
#define buffer_fixo					false
#define VALORES_FIXOS_MAX			false
#define Magmattec					true
#define CCA							false

#include "st_main.c"


// fim st8600.c
