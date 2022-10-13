//***********************************************************************
// Empresa: Sultech Sistemas Eletrônicos								*
// Módulo: Principal													*
// Função: Definir o funcionamento do equipamento						*
// Responsável: Edison Valério Nunes Junior								*
// Modificado: Edison Valério Nunes Junior								*
// Inicio: 22/11/2013													*
// Revisão: Edison Valério Nunes Junior									*
//***********************************************************************


	#use rs232(baud=19200, xmit=PIN_C6, rcv=PIN_C7,  parity=N, bits=8, errors, stream = modbus)  
	#if (com_rep == true)
		#use rs232(baud = 2400, xmit=PIN_G1, rcv=PIN_G2,  parity=N, bits=8, errors, stream = rep)  
	#endif


#ignore_warnings 202, 203, 204
#priority timer3

#define CR	13
#define LF  10

#define cristal	40
#define valor_timer1  65536 - 50000			// 10 milisegundos
											// (0,010/(8/40000000)) = 50000
											// calculo: 65536-50000
#define INTS_PER_SECOND 100

#define valor_timer3_2 		64234			// para 64 amostras
#define valor_timer3_2_60HZ 64234			// para 64 amostras
#define valor_timer3_2_50HZ 63973			// para 64 amostras
							
											// 60HZ
											// calculo: 65536-(0,0002604/(8/40000000)),  = "64234" p/ 260us / 40mhz   
											// onde 0,000260us eh intervalo entre ints do timer 1 
											// para 260us 64234 p/ 64 amostras por senoide em 24MHZ
											// 50HZ
											// calculo: 65536-(0,0003125/(8/40000000)),  = "63973" p/ 312,5us / 40mhz   
											// onde 0,0003125 eh intervalo entre ints do timer 1 
											// para 312,5us 63973 p/ 64 amostras por senoide em 24MHZ



#define valor_timer3_CHT_60HZ 64842			// este timer faz as leituras analogicas de tensao e corrente em 8 bits pelo ad interno 
											// como vao ser 120 pontos o intervalo deve ser 1/freq / 120 = 0,000138889
											// em 24mhz 65536 - (0,000138889/(8/40000000)) = 64842						

#define valor_timer3_CHT_50HZ 64703			// este timer faz as leituras analogicas de tensao e corrente em 8 bits pelo ad interno 
											// como vao ser 120 pontos o intervalo deve ser 1/freq / 120 = 0,000138889
											// em 24mhz 65536 - (0,000166666/(8/40000000)) = 64703

#define INTS_PER_250MS (INTS_PER_SECOND/4)

#define valor_timer3_16p 62411	// para 16 amostras
								// 60HZ
								// calculo: 65536-(0,001041557/(8/24000000)),  = 62411
								// onde 0,001041557 eh intervalo entre ints do timer 1 
								// para 1,041667us 64885 p/ 16 amostras por senoide em 24MHZ
									
#use fast_io (D)
//#use standard_io (C)
//#use fast_io (E)

/* DECLARACAO DE FUNCOES */
void main(void);
void pulsa_wdt(void);
void trata_virada_250ms(void);
void trata_virada_500ms(void);
void trata_virada_750ms(void);
void trata_virada_segundo(void);
void trata_virada_minuto(void);
void trata_virada_hora(void);
void trata_virada_dia(void);
void trata_virada_mes(void);
#if ( debugar == true)
	void trace(char);
#endif


// Includes 

#include "C:\Program Files (x86)\PICC\Drivers\math.H"
#include "C:\Program Files (x86)\PICC\Drivers\stdio.H"

#include "st_flag.c"
#include "st_vars.c"
#include "st8500_port.c"
#include "st_e2p.h"
#include "st_e2p.c"
#include "st_prot.c"	//prototipos de funcoes
#include "st_tabs.c"
#include "st_mens.c"
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
#include "lcd_16x4.c"
#include "st8500c_regs.c"
#include "teste_regs.c"
#include "novo_testa_mem.c"

#if (com_regs == true)
	#include "st8500c_ocor.c"
	#if (com_cht == true)
		#include "st_rcht.c"
	#endif		
#endif
#if (com_cht == true)
	#include "st_ccht.c"
#endif
#include "st8500_deci.c"
#include "tensao_ff.c"
#include "tensao_alta.c"
#include "tensao_tri.c"
#include "kvar_req.c"
#include "calcfreq.c"
#include "calcfptotal.c"

#if (com_rep == true)
	#include "st8500c_rep.c"
#endif

#if (com_consumo == true)
	#include "st_cons.c"
#endif
#if (funcao_505 == true)
	#include "st_505.c"
#endif
#if (com_modbus == true)
	#include "st_modb.c"
#endif	


#include "st8X00_menu.c"

#include "st_ints.c"
#include "st_calc.c"
#include "st_pots.c"

#if (com_time_funciona == true)
	#include "time_func.c"
#endif

void main(void){
	disable_interrupts(GLOBAL);

	//			 76543210
	set_tris_a(0b11111111);
	set_tris_b(0b11101111);
	set_tris_c(0b10100000);
	set_tris_d(0b00000000);
	set_tris_e(0b00000000);
	set_tris_g(0b11100100);

	SAIDA2 = 0;
	SAIDA3 = 0;
	trata_saidas();

	#if (com_485 == true)
		output_low(direcao);
	#endif	

//	setup_timer_0(T0_DIV_2);
//	disable_interrupts(INT_TIMER0);
//	setup_rtc(RTC_ENABLE,20);
	setup_rtc(RTC_DISABLE);

/* define funcionamento do temporizador 1 */
	setup_timer_1(T1_INTERNAL|T1_DIV_BY_2);
	set_timer1(valor_timer1);
	enable_interrupts(INT_TIMER1);

//	setup_timer_2(T2_DISABLED,0,1);
	
	setup_timer_3(T3_INTERNAL|T3_DIV_BY_2);
	set_timer3(valor_timer3_2_60HZ);
	enable_interrupts(INT_TIMER3);

	setup_timer_4(T4_DISABLED,0,1);

/* define funcionamento da uart */

	baud_rate =  read_word(ee_baud_rate);
	seta_baud_rate();
	enable_interrupts(INT_RDA);
	#if (com_rep == true)
		enable_interrupts(INT_RDA2);
  		set_uart_speed (2400, rep);
	#endif
	
	ext_int_edge(0,H_TO_L);
	enable_interrupts(INT_EXT);
	ext_int_edge(1,H_TO_L);
	enable_interrupts(INT_EXT1);

    setup_timer_2(T2_DIV_BY_4, 127, 1);
	setup_ccp1(ccp_pwm);
	set_pwm1_duty(512);	

// Define funcionamento do watchdog.
	setup_wdt(WDT_ON);
	restart_wdt();

	setup_adc_ports(sAN0 | sAN1 | sAN2 | sAN3 | sAN4 | sAN5 | sAN6 | sAN7 | VSS_VDD);
	setup_adc(ADC_CLOCK_DIV_4);

	enable_interrupts(GLOBAL);

	inic_dis();
	limpa_display();

	le_config();	// Le configuracoes
	inicializa_variaveis();	//inicializa variaveis
	inicializa_programa();
	valida_programa();

	
	
	// Inicializa o canal SPI
	setup_spi(SPI_MASTER | SPI_SCK_IDLE_HIGH | SPI_XMIT_L_TO_H | SPI_SAMPLE_AT_MIDDLE | SPI_CLK_DIV_4);
	output_low(FLASH_SI);
	output_low(FLASH_CLK);
	output_high(FLASH1_CE);
	aux_b1 = input(FLASH_SO);
	FLASH_CE_High();
	Unhold();

	led_tx = 1;
	led_rx = 1;

	write_byte(ee_passo_main, passo_main);

	mensagem_inicial();
	delay_ms(250);


	#if (com_relogio == true)
		rtc_init();		// inicializa RTC ds1302
		delay_ms(100);
		rtc_init();		// inicializa RTC ds1302
		delay_ms(100);
		rtc_get_date();
		rtc_get_time();
	#else
		rtc_get_e2p();	
		ajuste_relogio = 1;
	#endif

	if (var_mem != 67){
		le_hardware();
		grava_ocorrencias(reg_reset);
		var_mem = 67;
	}

//	#if (com_relogio == true)
//		le_calend();	
//	#endif

	#if (com_regs == true)
		wr_falta_energia();
		inicializa_regs();
		prox_grava = (int32)(aux_l2 + intervalo_reg);
	#endif
	
	cont0 = INTS_PER_SECOND;


	inic_rx();
	#if (com_rep == true)
		inic_rep();
	#endif

	restart_wdt();

	exibe_status();
	reinicializa_menus();
	busca_demanda_contratada();

	#if (com_relogio == false)
		ajuste_relogio = 1;
	#endif

	#if (versao_hsnet_calibra == true)
		output_high(direcao);
		delay_ms(1);
		fprintf(modbus,"\r\nModo Calibra HSnet!\r\n");
		delay_ms(2);
		output_low(direcao);
	#endif

// ****************************************************************************************
//  LOOP PRINCIPAL	
//*****************************************************************************************
	while(TRUE){
re_while:
		rotina = 0;
		modo_rep = 0;
   		output_high(FLASH1_CE);
		output_low(direcao);
		output_low(CS_DISP);
		Unhold();
		pulsa_wdt();
		trata_modbus();

		
		if (time_out_inicializando == 0){
			teclado();
		}

		#if (home_system == false)
			#if (com_cht == true)
				if (modo_funca == 1){
					if (programando == 0){
						cht_online();
					}
				}
			#endif		
		#else
			lendo_cht = false;
		#endif

		trata_saidas();

		#if (com_relogio == true)
			if ((dia > 31) || (mes > 12) || (ano < 4) || (hora > 23) || (minuto > 59) || (segundo > 59)){
				le_calend();
			}
		#endif

		passo_main++;
		switch(passo_main){
			case 0:{
				if (virou_250ms){
					trata_virada_250ms();
				}
				break;
			}
			case 1:{
				if (virou_500ms){
					trata_virada_500ms();
				}
				break;
			}
			case 2:{
				if (virouseg){
					trata_virada_segundo();
					}
				break;	
				}
			case 3:{
				if (viroumin){
				 	trata_virada_minuto();
				}
				break;	
			}
			case 4:{	
				if (viroudia){
					trata_virada_dia();
				}
				break;	
			}
			case 5:{
				if (virouhora){
					trata_virada_hora();
				}
				break;	
			}
			case 6:{
				if (viroumes){
					trata_virada_mes();
				}
				break;	
			}
			case 7:{
				calcula_vref();
				break;
			}
			case 8:{
					if (med_ten_ok == true){
						calcula_tensao_corrente();
					}
				break;	
			}
			case 9:{	
				if (programando == 0){
					if (calc_ten_ok == 1){
						calculo_potencias('R');
						kvar_requerido('R');
					}
				}
				break;	
			}
			case 10:{
				if (programando == 0){
					if (calc_ten_ok == 1){
						#if (com_tc == true)
							#if (com_rep == true)
								if (modo_rep == false){
									calculo_potencias('S');
									kvar_requerido('S');
								}
								else{
									passo_main++;
								}
							#else
								calculo_potencias('S');
								kvar_requerido('S');
							#endif
						#else
							passo_main++;
						#endif
					}
				}
				break;	
			}
			case 11:{
				if (programando == 0){
					if (calc_ten_ok == 1){
						#if (com_tc == true)
							#if (com_rep == true)
								if (modo_rep == false){
									calculo_potencias('T');
									kvar_requerido('T');
								}
								else{
									passo_main++;
								}
							#else
								calculo_potencias('T');
								kvar_requerido('T');
							#endif
						#else
							passo_main++;
						#endif
					}
				}
				break;
			}
			case 12:{
				if (programando == 0){
					if (calc_ten_ok == 1){
						calculo_trifasico();
					}
				}
				break;	
			}
			case 13:{
				if (calc_ten_ok){
					calc_ten_ok = 0;	
				}
				break;	
			}
			case 14:{
				if (var_mem != 67){
					reset_cpu();
				}
				break;	
			}
			case 15:{
				break;	
			}
			case 16:{
				#if (home_system == false)
					#if (com_cht == true)
						if (modo_funca == 1){
							if (programando == 0){
								cht_online();
							}
						}
						break;	
					#else
						passo_main++;
					#endif
				#else
					lendo_cht = false;
					passo_main++;
				#endif
                    break;
			}
			case 17:{
				if (programando == 0){
					calc_frequencia();
				}
				break;	
			}
			case 18:{
				passo_main++;
                break;
			}
			case 19:{
				passo_main++;
                break;
			}
			case 20:{
				#if (com_alarme == true)
					if (programando == 0){
						trata_alarme();
					}
					break;
				#else
					passo_main++;
				#endif
			}
			case 21:{
				#if (teste_regs == true)
					if (registro){
						grava_registros(registro_normal);
						if (programando == false){
							mensagem(2,1);
							mensagem(3,2);
						}
					}
				#else
					passo_main++;
				#endif
                    break;
			}
			case 22:{
				verifica_status();
				break;
			}
			case 23:{
				passo_main++;
                break;
			}
			case 24:{
				if(programando == false){
					st8500_decisao();
				}
				break;
			}
			case 25:{
				if (virou_750ms){
					trata_virada_750ms();
				}
				break;
			}

			#define LIMITE_PASSO_MAIN 25			// C U I D A D O,  ALTERAR ESTA POSICAO CASO SEJA CRIADO + OPCES NO CASE DA PASSO_MAIN
			default:{
				if (passo_main > LIMITE_PASSO_MAIN){
					passo_main = 255;
				}
			}
		}
	}
}

void pulsa_wdt(void){
	if ((morder_t1 == 1) && (morder_t3 == 1) && (morder_calc == 1)){
		morder_t1 = 0;
		morder_t3 = 0;
		morder_calc = 0;
		restart_wdt();
	}
}


void trata_virada_500ms(void){
	le_calend();	


	if(intervalo_reg < 60){
		decide_regs();	
	}
	if(intervalo_reg != INTERVALO_REG_DEFAULT){
		intervalo_reg = INTERVALO_REG_DEFAULT;
	}

	exibir_menu = 1;
	if(programando){
		piscar = ~piscar;
	}
	else{
		piscar = 0;
	}

	if(tempo_senha != 0){
		tempo_senha--;
	}
	else{
		programando = 0;
	}

	virou_500ms = 0;
}

void trata_virada_750ms(void){
	virou_750ms = 0;
}

void trata_virada_250ms(void){
	if (programando == true){
		exibir_menu = 1;
	}
	piscar = 0;

	virou_250ms = 0;
}

void trata_virada_segundo(void){
	enable_interrupts(INT_RDA);
	if (time_out_inicializando != 0){
		if (time_out_inicializando > 5){
			time_out_inicializando = 4;
		}
		time_out_inicializando--;
	}

	if (time_out_aciona_alarme != 0){
		time_out_aciona_alarme--;
	}

//	finaliza_calculo_tensao_corrente();

	#if (home_system == true)
		ler_dips = 1;
		le_dip_ligacao();
		trata_led();
		fprintf(hsnet,"Mul_TC=%u ", mul_tc);
		fprintf(hsnet,"Tensão=%lu ", tensao_r);
		fprintf(hsnet,"Corrente=%lu ", corrente_r);
	#endif
	
	#if (com_consumo == true)
		soma_consumo();
		#if (com_tc == true)
			if ((seg_falt_rep == 0) || (seg_falt_rep > 900)){
				seg_falt_rep = 900;
			}
			seg_falt_rep--;
			aux_w1 =  (word)(900 - seg_falt_rep);
			timer_integra = (unsigned char)(aux_w1 / 60);
		#endif
		if (segundo == 30){
			integra_consumo();
			#if (com_demanda == true)
				calcula_demandas();
			#endif
		}
	#endif				

	nro_conta_media = conta_media;
	conta_media = 0;

	if (retardo_alarmes != 0){
		retardo_alarmes--;
	}

	decide();

	if (intervalo_reg >= 60){
		decide_regs();	
	}
	wr_segundo_old();

	ponto_segundo = ~ponto_segundo;

	if (val_pwm > 130){
		val_pwm--;
	}
	set_pwm1_duty(val_pwm);	


	trata_time_out_menus();
	if (time_out_exibe_status_teclando!= 0){
		time_out_exibe_status_teclando--;				
	}

	if (menu1 == 0){
		exibe_status();
	}
	if (time_out_exibe_erro != 0){
		time_out_exibe_erro--;
	}

	#if (com_cht == true)
		lendo_cht = false;
	#endif	

	trata_tempos_aciona_repouso();
	trata_segundeiro();
	led_rx = 0;
	led_tx = 0;
	if (comuni_busy != 0){
		comuni_busy--;
	}
	if (calcular_bancos == 1){
		calcular_bancos = 0;
		gera_sequencia_valor_bancos();
	}

	#if (AUTOSET == true)
		if (em_autoset == true){
			if (time_out_autoset != 0){
				time_out_autoset--;
			}
			else{
				em_autoset = false;
			}
			if (time_out_teste_autoset != 0){
				time_out_teste_autoset --;
			}
		}
	#endif

	virouseg = 0;
}	


void trata_virada_minuto(void){
	gravou = false;
	
	pisca_minuto = ~pisca_minuto;
	#if (com_relogio == false)
		le_calend_int();
	#endif	

	#if (versao_hsnet_calibra == true)
		baud_rate = 19200;
		endereco = 1;
		seta_baud_rate();
		tipo_ligacao = 0;
	#endif

	#if (com_relogio == true)
		wr_tempo_old();
	#endif

	#if (com_consumo == true)
		integra_consumo();
		#if (com_demanda == true)
			calcula_demandas();
		#endif
	#endif	

	verifica_checksum_vars();

	valida_programa();

	setup_timer_2(T2_DIV_BY_4, 127, 1);
	setup_ccp1(ccp_pwm);
	
	#if (com_rep == true)
		if (modo_rep == 1){
			if (time_out_modo_rep != 0){
				time_out_modo_rep--;			
			}
		}
		kkw = (float)(fat_conv_ativa);
//		kkvar = (float)(fat_conv_reativa);
		kkvar = (float)(fat_conv_ativa);
		kkw = (float)((kkw) /  1000);
		kkvar = (float)((kkvar) / 1000);
	#endif

	#if (com_time_funciona == true)
		trata_time_funcionamento();
	#endif
	
	busca_demanda_contratada();

	viroumin=0;
}

void trata_virada_hora(void){
	virouhora = false;
	
	#if (rotacionar == true)
		#if (controle_por_fase == true)
			rotaciona_banco('R');
			rotaciona_banco('S');
			rotaciona_banco('T');
		#else
			rotaciona_banco();
		#endif
		salva_contadores();
	#endif

	fsentido_r = 0;
	fsentido_s = 0;
	fsentido_t = 0;

	fprintar = false;

	#if (com_regs == true)
		codigo_old = 0;
	#endif
}

void trata_virada_dia(void){
 	viroudia = 0;

	segundo++;
	grava_registros(registro_normal);
	grava_registros(reg_virou_dia);

	#if (com_cht == 1)
		grava_cht(registro_normal);
	#endif
	codigo_old = 0;
}

void trata_virada_mes(void){
 	viroumes = 0;
 	#if (com_consumo == true)
 		#if (com_demanda == true)
		 	dem_maxima_aparente_ant = dem_maxima_aparente;
 			dem_maxima_ativa_ant = dem_maxima_ativa;
 	
	 		write_word(ee_dem_maxima_aparente_ant, dem_maxima_aparente_ant);
	 		write_word(ee_dem_maxima_ativa_ant, dem_maxima_ativa_ant);

			dem_maxima_aparente = 0;
			dem_maxima_ativa = 0;
	
		 	write_word(ee_dem_maxima_aparente, 0);
 			write_word(ee_dem_maxima_ativa, 0);
 		#endif
 	#endif

	write_long(ee_consumo_ati_ant,read_long(ee_consumo_ati));
	write_long(ee_consumo_reati_ant,read_long(ee_consumo_reati));

	#if (com_time_funciona == true)
		write_long(ee_horas_funcionamento_ant,read_long(ee_horas_funcionamento));
	#endif	
}


#if ( debugar == true)
	void trace(char aux_trace){
		if (aux_trace != 0){
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
	}
#endif

// Fim st_main.c
