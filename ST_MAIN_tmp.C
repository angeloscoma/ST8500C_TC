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

#if (st5000t == true)
	#use rs232(baud=19200, xmit=PIN_C6, rcv=PIN_C7, restart_wdt, parity=N, bits=8, errors, stream = modbus)  
#else
	#use rs232(baud=19200, xmit=PIN_C6, rcv=PIN_C7, restart_wdt, parity=N, bits=8, errors, stream = modbus)  
#endif

#if (st_prog == true)
	#use rs232(baud=19200, xmit=PIN_G1, rcv=PIN_G2, restart_wdt, parity=N, bits=8, errors, stream = sultech)  
#endif

#ignore_warnings 203
//#ignore_warnings 202,203,204

#priority Timer3

/* definição de hardware = ios */

/* equates */

#define CR	13
#define LF  10


#define valor_timer1  65536 - 30000			// 10 milisegundo
							// (0,010/(8/24000000)) = 3000
							// calculo: 65536-30000


#define INTS_PER_SECOND (100)

#if ((st5000t == 1) || (st5030t == 1))
	#define valor_timer3_2 64790	// para 64 amostras
	#define valor_timer3_2_60HZ 64790	// para 64 amostras
	#define valor_timer3_2_50HZ 64598	// para 64 amostras
#else
	#define valor_timer3_2 64790	// para 64 amostras
	#define valor_timer3_2_60HZ 64790	// para 64 amostras
	#define valor_timer3_2_50HZ 64598	// para 64 amostras
#endif
							
							// 60HZ
							// calculo: 65536-(0,0002604/(8/24000000)),  = "64756" p/ 260us / 24mhz   
							// onde 0,000260 é intervalo entre ints do timer 1 
							// para 260us 64756 p/ 64 amostras por senoide em 24MHZ
							// 50HZ
							// calculo: 65536-(0,0003125/(8/24000000)),  = "64756" p/ 312,5us / 24mhz   
							// onde 0,0003125 é intervalo entre ints do timer 1 
							// para 312,5us 64598 p/ 64 amostras por senoide em 24MHZ



#define valor_timer3_CHT_60HZ 65119 + 23	// este timer faz as leituras analogicas de tensao e corrente em 8 bits pelo ad interno 
							// como vão ser 120 pontos o intervalo deve ser 1/freq / 120 = 0,000138889
							// em 24mhz 65536 - (0,000138889/(8/24000000)) = 65119						;64984

#define valor_timer3_CHT_50HZ 65036 + 23	// este timer faz as leituras analogicas de tensao e corrente em 8 bits pelo ad interno 
							// como vão ser 120 pontos o intervalo deve ser 1/freq / 120 = 0,000138889
							// em 24mhz 65536 - (0,000166666/(8/24000000)) = 65036						;64984



#if ((st5000T == true) || (st5030T == true) || (st5300T == true) || (st5330T == true))
	#define st5x	true
//	#define st5x	false
#else
	#define st5x	false
//	#define st5x	true
#endif
#if ((st9400R == true) || (st9430r == true))
	#define st94	true
#else
	#define st94	false
#endif

#if ((st5030T == true) || (st5330T == true) || (st9600r == true) || (st9100r == true) || (st9430r == true))
	#define com_regs    true
#else
	#define com_regs	false
#endif

#if ((st9600r == true) || (st9100r == true) || (st8x00c == true) || (st_prog == true))
	#define com_display true
#else	
	#define com_display false
#endif

#if ((st9600r == true) || (st9100r == true))
	#define portatil TRUE
#else	
	#define portatil false
#endif
#if (st9100r == true)
	#define monofasico true
#else
	#define monofasico false
#endif	

// definicoes para inclusao de modulos para testes 

#define teste_cht		false
#define com_modbus		true
#if (st5x == true) 
	#define com_menu	false
#else
	#if ((st5000T == true) || (st5030T == true) || (st5300T == true) || (st5330T == true))
		#define com_menu	false
	#else
		#define com_menu	true
	#endif
#endif
#define com_alarme		true
#define feira			false
#define teste_consumo	false
#define fixar_parametro	false
#define teste_regs		false


#if (st5x == true)
//	#use fast_io (C)
	#use fast_io (D)
	#use fast_io (E)
#endif
#if (st94 == true)
//	#use fast_io (C)
	#use fast_io (D)
	#use fast_io (E)
#endif
#if ((st9600r == true) || st9100r == true))
	#use fast_io (D)
	#use fast_io (G)
	#use fast_io (E)
#endif
#if (st_prog == true))
//	#use fast_io (D)
	#use fast_io (G)
	#use fast_io (E)
#endif


#define word int16

// CONTROLE DE REVISOES 



/* DECLARACAO DE FUNCOES */
void main( void );
void pulsa_wdt(void);
void trata_virada_500ms(void);
void trata_virada_segundo(void);
void trata_virada_minuto(void);
void trata_virada_dia(void);
void trata_virada_mes(void);

#define debugar	true

// Includes 
#include <math.h>
#include <stdio.h>

#include "st_flag.c"
#include "st_vars.c"
#if (st9600r == true)
	#include "st96port.c"
#endif	
#if (st_prog == true)
	#include "stprog_port.c"
#endif
#if (st9100r == true)
	#include "st91port.c"
#endif	
#if ((st5300T == true) || (st5330T == true))
	#include "st53port.c"
#endif	
#if ((st5000T == true) || (st5030T == true))
	#include "st50port.c"
#endif	
#if ((ST9400R == true) || (ST9430R == true))
	#include "st94port.c"
#endif	

#include "st_e2p.h"
#include "st_e2p.c"
#include "st_prot.c"	//prototipos de funcoes
#include "st_tabs.c"
#if (com_cht == true)
//	#include "seno_120.c"
#endif
#include "st_mens.c"
#if (st5x == true)
	#include "st50_led.c"
#endif
#if (chip_cs5460a == true)
	#include "cs5460a.c"
#endif	
#if (ad_microchip == true)
	#include "mcp3208.c"
#endif
#if (ade7754 == true)
	#include "ade7754.c"
	#include "spi_ade7754.c"
#endif
#if (com_relogio == true)
	#include "ds1302.c"
#endif
#include "st_conf.c"
#include "st_roti.c"
#include "st_rota.c"
#include "st_deci.c"
#include "st_vali.c"
#if (com_regs == true)
	#include "sst25vfxxx.c"
#endif	
#if ((st9600r == true) || (st9100r == true) || (st_prog == true))
	#include "lcd_16x4.c"
#endif	
#if (com_regs == true)
	#include "st_regs.c"
	#include "st_ocor.c"
	#if (com_cht == true)
		#include "st_rcht.c"
	#endif		
#endif
#if (com_cht == true)
	#if (ade7754 == true)
		#include "st_ccht_7754.c"
	#else
		#include "st_ccht.c"
	#endif
#endif

#if (st_prog == true)
	#include "stprog_deci.c"
#endif

#if (com_menu == true)
	#if (st9100r == true)
		#include "st91menu.c"
	#elif (st94 == true)
		#include "st94menu.c"
	#elif (st_prog == true)
		#include "stprog_menu.c"
//		#include "st_menu.c"
	#else
		#include "st_menu.c"
	#endif
#endif
#if (chip_cs5460a == true)
	#if (st9600r == true)
		#include "st96ints.c"
		#include "st96calc.c"
		#include "st96pots.c"
	#endif
	#if ((st5000T == true) || (st5030T == true))
		#include "st50ints.c"
		#include "st50calc.c"
		#include "st50addr.c"
		#include "st50pots.c"
	#endif
#endif
#if (ad_microchip == true)
	#if (st9100r == true)
		#include "st91ints.c"
		#include "st91calc.c"
		#include "st91pots.c"
	#else
		#include "st_ints.c"
		#include "st_calc.c"
		#include "st_pots.c"
		#if ((st5000T == true) || (st5030T == true))
			#include "st50addr.c"
		#endif
	#endif
#endif
#if (ade7754 == true)
	#if (st9100r == true)
		#include "st91_ints_7754.c"
		#include "st91calc_7754.c"
		#include "st91pots.c"
	#else
		#include "st_ints_7754.c"
		#include "st_calc_7754.c"
		#include "st_pots_7754.c"
		#if ((st5000T == true) || (st5030T == true))
			#include "st50addr.c"
		#endif
	#endif
#endif
#include "tensao_ff.c"
#include "tensao_alta.c"
#include "tensao_tri.c"
#include "kvar_req.c"
#include "calcfreq.c"
#include "calcfptotal.c"


#if (com_consumo == true)
	#include "st_cons.c"
#endif
#if (funcao_505 == true)
	#include "st_505.c"
#endif
#if (com_modbus == true)
	#include "st_modb.c"
#endif	


#if (st_prog == true)
	#zero_ram
#endif
void main(void)
{
//	disable_interrupts(GLOBAL);

#if ((st5300t == 1) || (st5330t == 1))
	//			 76543210
	set_tris_b(0b11100111);
//	set_tris_c(0b10100000);
	set_tris_d(0b00000100);
	set_tris_e(0x11110000);
	set_tris_f(0b01111111);
	set_tris_g(0b11111000);
#elif (st_prog == 1)
	//			 76543210
	set_tris_b(0b11111111);
	set_tris_c(0b10100000);
	set_tris_d(0b11111111);
	set_tris_e(0b00000000);
	set_tris_f(0b01111011);
	set_tris_g(0b11111100);
	output_e(255);
	output_g(255);
#elif ((st5000t == 1) || (st5030t == 1))
	//		    	 76543210
	#if (ad_microchip == true)
		set_tris_b(0b11111111);
		set_tris_c(0b10010000);
		set_tris_d(0b00000100);
		set_tris_e(0b00000000);
		set_tris_f(0b11111111);
		set_tris_g(0b11111110);
		output_high(ADE7754_CS);
		output_high(ADE7754_RST);
		output_high(MCP3208_CS);

	#elif (ade7754 == true))
		set_tris_b(0b11111111);
		set_tris_c(0b10010000);
		set_tris_d(0b00000100);
		set_tris_e(0b00000000);
		set_tris_f(0b11111111);
		set_tris_g(0b11110110);
		output_high(ADE7754_CS);
		output_high(ADE7754_RST);
		output_high(MCP3208_CS);
	#else
		set_tris_b(0b11111111);
		set_tris_c(0b10010000);
		set_tris_d(0b01000000);
		set_tris_e(0b00000000);
		set_tris_f(0b11111111);
		set_tris_g(0b11111110);
	#endif
#elif ((st9400r == true) || (st9430r == true))
	//			 76543210
	set_tris_b(0b01101111);
	set_tris_c(0b10010000);
	set_tris_d(0b00000000);
	set_tris_e(0b00000001);
	set_tris_f(0b00101111);
	set_tris_g(0b11100000);
	output_high(MCP3208_CS);
	output_high(MCP3208_CLK);
	output_high(MCP3208_CS);
	output_high(MCP3208_DOUT);

#elif (st9600r == true)
	//			 76543210
	set_tris_b(0b01101111);
//	set_tris_c(0b10100000);
	set_tris_d(0b00000000);
	set_tris_e(0b00000001);
	set_tris_f(0b00101111);
	set_tris_g(0b11100000);
#elif (st9100r == 1)
	//			 76543210
	set_tris_b(0b11101111);
//	set_tris_c(0b10100000);
	set_tris_d(0b00000000);
	set_tris_e(0b00000001);
	set_tris_f(0b00101111);
	set_tris_g(0b11100000);
#endif	


#if (chip_cs5460a == true)
	output_low(CS5460A_RST);
	output_high(CS5460A_CS_R);
	output_high(CS5460A_CS_S);
	output_high(CS5460A_CS_T);
#else
	output_high(CS5460A_CS_R);
	output_high(CS5460A_CS_S);
	output_high(CS5460A_CS_T);
#endif	
#if (st_prog == true)
	SAIDA1=0;
	SAIDA2=0;
	wr_saida1();
	wr_saida2();
#endif
#if (com_485 == true)
	output_low(direcao);
#endif	
   	output_low(MCP3208_CLK);

/* define funcionamento do temporizador 1 */
	setup_timer_1(T1_INTERNAL|T1_DIV_BY_2);
	set_timer1(valor_timer1);
	enable_interrupts(INT_TIMER1);

	setup_timer_3(T1_INTERNAL|T3_DIV_BY_2);
	set_timer3(valor_timer3_2_60HZ);
	enable_interrupts(INT_TIMER3);


/* define funcionamento da uart */
	baud_rate =  read_word(ee_baud_rate);
#if (st_prog == true)
	baud_rate = 19200;
	write_word(ee_baud_rate, 19200);
#endif
	seta_baud_rate();
	enable_interrupts(INT_RDA);
#if (st_prog == true)
	enable_interrupts(INT_RDA2);
#endif
#if (ade7754 == true)
	ext_int_edge(2,H_TO_L);
	enable_interrupts(INT_EXT2);

	ext_int_edge(3,H_TO_L);
	enable_interrupts(INT_EXT3);
#endif

#if (ad_microchip == true)
	#if ((st9430r == true) || ( st9400r == true))
		ext_int_edge(2,H_TO_L);
		enable_interrupts(INT_EXT2);
	#else
		ext_int_edge(0,H_TO_L);
		enable_interrupts(INT_EXT);
	#endif
	ext_int_edge(1,H_TO_L);
	enable_interrupts(INT_EXT1);
#endif
#if (chip_cs5460a == true)
	ext_int_edge(2,H_TO_L);
	enable_interrupts(INT_EXT2);
//	ext_int_edge(3,H_TO_L);
//	enable_interrupts(INT_EXT3);
#endif
#if (com_display == true)
    setup_timer_2(T2_DIV_BY_4, 127, 1);
	setup_ccp1(ccp_pwm);
	set_pwm1_duty(0);	
#endif

#if (st94 == true)
//	enable_interrupts(INT_EEPROM);
#endif

/* define funcionamento da watchdog */
	setup_wdt(WDT_ON);
	restart_wdt();

#if (st5x == true)
//	setup_adc_ports(ANALOG_AN0_TO_AN9 | VSS_VDD);
	setup_adc_ports(ALL_ANALOG | VSS_VDD);
#else
	setup_adc_ports(ANALOG_AN0_TO_AN7 | VSS_VDD);
#endif	
	setup_adc(ADC_CLOCK_INTERNAL);

#if (st5030t == 1))
	#if (teste_painel == true)
		tudodenovo:
			output_high(led_alarme);
			output_high(led_tx);
			output_high(led_rx);
			output_high(led_tc_r);
			output_high(led_tc_s);
			output_high(led_tc_t);
			output_high(led_erro);
			output_high(led_ok);
			
			output_low(led_alarme);
			delay_ms(250);
			output_high(led_alarme);
			output_low(led_tx);
			delay_ms(250);
			output_high(led_tx);
			output_low(led_rx);
			delay_ms(250);
			output_high(led_rx);
			output_low(led_tc_r);
			delay_ms(250);
			output_high(led_tc_r);
			output_low(led_tc_s);
			delay_ms(250);
			output_high(led_tc_s);
			output_low(led_tc_t);
			delay_ms(250);
			output_high(led_tc_t);
			output_low(led_erro);
			delay_ms(250);
			output_high(led_erro);
			delay_ms(250);
			output_low(led_ok);
			delay_ms(250);
			output_high(led_ok);
			goto tudodenovo;
	#endif
#endif
		
	enable_interrupts(GLOBAL);

#if ((st9600r == true) || (st_prog == true))
	{
	inic_dis();
	limpa_display();
	}
#endif
#if (st94 == true)
	{
	limpa_linha(1);
	limpa_linha(2);
	limpa_linha(3);
	}
#endif
	tx_buffer = 0;

#if ((st5x == true) || (st94 == true) || (st_prog == true))

		#if (com_485 == true)
			output_high(direcao);
			delay_ms(1);
		#endif
		switch ( restart_cause() )
		   {
	      	case WDT_TIMEOUT:
		    	{
	         	fprintf(modbus,"\r\nRestarted processor because of watchdog timeout!!!!\r\n");
	         	break;
	    	  	}
			case NORMAL_POWER_UP:
		      	{
	         	fprintf(modbus,"\r\nNormal power up!!!!\r\n");
	         	break;
	    	  	}	
	      	default:
	      	  	{
	         	fprintf(modbus,"\r\nAnormal Reset!!!!\r\n");
	         	break;
		      	}
	   		}

		if (var_mem != 67)
			{
			fprintf(modbus,"\r\nReset Frio!!!!\r\n");
			}
		else
			{
			fprintf(modbus,"\r\nReset Quente!!!!\r\n");
			}
		fprintf(modbus,"%u:%u:%u  %u,%u",hora,minuto,segundo,var_mem,passo_main);
		fprintf(modbus,"\r\n");
		#if (com_485 == true)
			output_low(direcao);
			delay_ms(1);
		#endif

#endif

#if (com_regs == true)
/* inicializa o canal SPI */
   	output_low(FLASH_SI);
   	output_low(FLASH_CLK);
   	output_high(FLASH1_CE);
	#if ((st9600r == true) || (st9100r == true) || (st_prog == true))
	   	output_high(FLASH2_CE);
	   	output_high(FLASH3_CE);
	   	output_high(FLASH4_CE);
	#endif   	
   	aux_b1 = input(FLASH_SO);

	setup_spi(SPI_MASTER | SPI_L_TO_H | SPI_CLK_DIV_16);

	FLASH_CE_High();
	Unhold();

#endif


#if (st5x == true)
	output_high(led_ok);
	output_high(led_tx);
	output_high(led_rx);
	output_high(led_alarme);
	#if ((st5000t == 1) || (st5030t == 1))
		output_high(led_tc_r);
		output_high(led_tc_s);
		output_high(led_tc_t);
	#endif
#endif


#if (chip_cs5460a == true)
 	reset_cs5460();
	inic_cs5640();
#endif

	write_byte(ee_passo_main, passo_main);

	le_config();	// Le configuracoes
	inicializa_variaveis();	//inicializa variaveis
	inicializa_programa();

#if ((st9600r == true) || (st94 == true) || (st_prog == true))
	mensagem_inicial();
#endif


#if (chip_cs5460a == true)
	config_cs5460();
#endif

#if (ade7754 == true)
	acao_ade7754 = 0;
#endif

	if (var_mem != 67)
		{
#if (com_regs == true)
		le_hardware();
#endif		
		var_mem = 67;
		}

	delay_ms(1000);

#if (com_relogio == true)
	rtc_init();		// inicializa RTC ds1302
	delay_ms(100);
	rtc_init();		// inicializa RTC ds1302
	delay_ms(100);
	rtc_get_date();
	rtc_get_time();
	tempo_ajuste_relogio = 0;
	ajuste_relogio = 6;
	#if (aju_time == true)
		{
		conta_seg = conv_relogio_long();
		}
	#endif
#endif

#if (com_regs == true)
	wr_falta_energia();
	inicializa_regs();
	prox_grava = (int32)(aux_l2 + intervalo_reg);
#endif
	cont0 = INTS_PER_SECOND;

#if (com_relogio == true)
	le_calend();	
#endif

	delay_ms(1000);

	valida_programa();

	inic_rx();

#if (com_menu == true)
	#if (com_regs == true)
		calcula_autonomia();
		exibe_status();
	#endif
#endif	

#if (com_menu == true)
	reinicializa_menus();
#endif

//data1_int = crc16t();
//para:
//goto para;

// ****************************************************************************************
//  LOOP PRINCIPAL	
//*****************************************************************************************
while(TRUE) 
	{
#if (ade7754 == true)
	 tx_ade7754();
#endif

#if (chip_cs5460a == true)
	output_high(CS5460A_RST);
	output_high(CS5460A_CS_R);
	output_high(CS5460A_CS_S);
	output_high(CS5460A_CS_T);
#endif
#if (com_485 == true)
	output_low(direcao);
#endif		
#if (com_display == true)
	output_high(CS_DISP);
#endif

#if (com_regs == true)
	Unhold();
#endif		

	pulsa_wdt();

#if (com_modbus == true)
	trata_modbus();
#endif
#if (st_prog == true)
	trata_sultech();
#endif
			
#if (com_menu == true)
	teclado();
#endif		

#if (com_cht == true)
		if (modo_funca == 1)
			{
			if (programando == 0)
				{
				cht_online();
				}
			}
#endif		
		passo_main++;
		switch(passo_main)
			{
			case 1:
				{
				if (virou_500ms == 1)
					{
					trata_virada_500ms();
					}
				break;
				}
			case 2:
				{
				if (virouseg == 1)
					{
					trata_virada_segundo();
					}
				break;	
				}




			}




	}

}

void pulsa_wdt(void)
{

}

void trata_virada_500ms(void)
{
#if (com_relogio == true)
	le_calend();	
#endif

#if (com_regs == true)
	if (intervalo_reg < 60)
		{
		decide_regs();	
		}
#endif	

	
#if (com_menu == true)
	exibir_menu = 1;
	if (programando == 1)
		{
		piscar = ~piscar;
		}
	else
		{
		piscar = 0;
		}
	#if ((portatil == TRUE) || (st_prog == true))
		tempo_senha = 255;
	#else
		if (tempo_senha != 0 )
			{
			tempo_senha--;
			}
		else
			{
			programando = 0;
			}
	#endif
#else
	programando = 0;
#endif		
	

#if (st5x == true)
	output_low(led_ok);
	output_high(led_tx);
	output_high(led_rx);
#endif

	virou_500ms = 0;

}


void trata_virada_segundo(void)
{

#if (ade7754 == true)
	le_senoides();
#endif

//	finaliza_calculo_tensao_corrente();

#if (com_relogio == false)
	le_calend_int();
#endif

#if (st5x == true)
	output_high(led_ok);
	ler_dips = 1;
	le_dip_endereco();
	trata_led();
#endif				


#if (st5x == true)
	#if (printa == true)
		#if (com_485 == true)
			output_high(direcao);
			delay_ms(1);
		#endif	
			le_dip_baud_ligacao();
	
	//     TESTE TABELA DE ENDEREÇOS
			printf(";Val_addr=%lu ", val_addr);
			printf("; Dip_vel=%lu,", dip_vel);
			printf(";  Endereço=%u ", tabela_addr[val_addr]);
			printf(";  baud rate=%lu ", baud_rate);
			printf(";  Ligação=%u ", tipo_ligacao);
	
			printf("\r\n");
		#if (com_485 == true)
			delay_ms(2);
			output_low(direcao);
		#endif
	#else
		le_dip_baud_ligacao();
	#endif
#endif


#if (chip_cs5460a == true)
	int_cs5460_r = 0;
	int_cs5460_s = 0;
	int_cs5460_t = 0;
#endif

#if (com_consumo == true)
	soma_consumo();
#endif				


//	printf("nro ciclos = %u\l\r", conta_media);

	nro_conta_media = conta_media;
	conta_media = 0;

	if (retardo_alarmes != 0)
		{
		retardo_alarmes--;
		}

	decide();

#if (com_regs == true)
	if (intervalo_reg >= 60)
		{
		decide_regs();	
		}
	wr_segundo_old();
#endif	
	

	ponto_segundo = ~ponto_segundo;

#if (com_display == true)
	if (val_pwm != 0)
		{
		val_pwm--;
		}
#endif

#if (com_menu == true)
	trata_time_out_menus();
	#if (st_prog == false)
		{
		if (menu1 == 0)
			{
			exibe_status();
			}
		if (time_out_exibe_erro != 0)
			{
			time_out_exibe_erro--;
			}
		}
	#endif
#endif
		
	
#if (com_cht == true)
	lendo_cht = false;
#endif	


#if (st5x == true)
	if (segundo % 10 == 0 )
		{
		le_dip_baud_ligacao();
		}
#endif


#if (com_relogio == true)
	#if (aju_time == true)
		if (tempo_ajuste_relogio != 0)
			{
			tempo_ajuste_relogio--;
			if (tempo_ajuste_relogio == 0)
				{
				if (adiantado == true)
					{
					segundo = segundo - ajuste_relogio;
					}
				else
					{
					segundo = segundo + ajuste_relogio;
					if (segundo > 59)
						{
						minuto++;
						segundo = segundo - 59;
						if (minuto > 59)
							{
							minuto = 0;
							}
						}
					}
				rtc_set_datetime();
				conta_seg = conv_relogio_long();
				}
			}
	#else
		if (tempo_ajuste_relogio != 0)
			{
			tempo_ajuste_relogio--;
			if (tempo_ajuste_relogio == 0)
				{
				segundo = segundo - ajuste_relogio;
				rtc_set_datetime();
				}
			}
	#endif
#endif

	virouseg = 0;




}	


void trata_virada_minuto(void)
{
	pisca_minuto = ~pisca_minuto;

#if (st5x == true)
	le_dip_baud_ligacao();
#endif				
	
#if (com_regs == true)
	wr_tempo_old();
	if (registro == 1)
		{
		calcula_autonomia();
		}
#endif	

#if (com_consumo == true)
	calcula_demandas();
	integra_consumo();
#endif	

	verifica_checksum_vars();
//	if (var_mem != 67)
//		{
//	 	var_mem = 67;
//		}

	valida_programa();

#if (com_display == true)
    setup_timer_2(T2_DIV_BY_4, 127, 1);
	setup_ccp1(ccp_pwm);
#endif


#if (fixar_parametro ==	true)
	fixa_parametros();
#endif
	

	viroumin=0;

}

void trata_virada_dia(void)
{
 	viroudia=0;
	codigo_old = 0;
#if (com_relogio == true)
	#if (aju_time == true)
		//  se tempo for menor que 86400, então relogio está adiantando.
		//  se tempo for maior que 86400, então relogio está atrasando.
		//  se adiantando, então a difereça = 86400 - tempo;
		//	se atrasando, então a diferença = tempo - 86400;
		if (conta_seg < 86399)
			{
			ajuste_relogio = (char)(86400 - conta_seg);
			tempo_ajuste_relogio = (ajuste_relogio * 2);
			adiantado = true;
			}
		else if (conta_seg > 86400)
			{
			ajuste_relogio = (char)(conta_seg - 86400);
			tempo_ajuste_relogio = (ajuste_relogio * 2);
			adiantado = false;
			}
	#else
			ajuste_relogio = 6;
			tempo_ajuste_relogio = (ajuste_relogio * 2);
	#endif
#endif
 	
}

void trata_virada_mes(void)
{
 	viroumes = 0;
 	dem_maxima_aparente_ant = dem_maxima_aparente;
 	dem_maxima_ativa_ant = dem_maxima_ativa;
 	
 	write_word(ee_dem_maxima_aparente_ant, dem_maxima_aparente_ant);
 	write_word(ee_dem_maxima_ativa_ant, dem_maxima_ativa_ant);

	dem_maxima_aparente = 0;
	dem_maxima_ativa = 0;
	
 	write_word(ee_dem_maxima_aparente, 0);
 	write_word(ee_dem_maxima_ativa, 0);
	
}


void trace(char aux_trace)
{
#if ( debugar == true)
	if (aux_trace != 0)
		{
		#if (com_485 == true)
			output_high(direcao);
			delay_ms(1);
		#endif
			printf("[%u,%u,%u]\r\n",var_mem,passo_main, aux_trace);
		#if (com_485 == true)
			delay_ms(1);
			output_low(direcao);
		#endif
		}
#endif
}




/* Fim st_main */
