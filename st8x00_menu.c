/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST8610_MENU                                                    *
; Funcao: TRATAMENTO DO MENU PRINCIPAL									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/


  
#define MAX_TIME_TECLA	25

char aux_menu1;

void teclado(void);
void trata_menu(void);
void exibe_menu(void);
void trata_senha(void);
void trata_time_out_menus(void);
#if (disp_7seg == true)
	void exibe_off(void);
#endif
#if (ST8100C == true)
	void display(char, word,  char,  char);
#endif	

void display_n(char, word, char);
void fim_menu1(void);
word inkey(char);

void exibe_data_hora(void);


void reinicializa_menus(void);
void salva_menus(void);

void reset_rolar(void)
{
	ja_rolou = false;
	rolando = false;
}

void pisca_pontos(void)	
{
	if (programando == 1)
		{
		if (ponto_segundo == 1)
			{
			#if (disp_7seg == true)
				buf_display[0] = buf_display[0] | 0x80;
				buf_display[1] = buf_display[1] | 0x80;
				buf_display[2] = buf_display[2] | 0x80;
				buf_display[3] = buf_display[3] | 0x80;
			#endif
			}
		}
}		


#if (disp_7seg == true)
	#include "st94leds.c"
#endif	
#include "st_erros.c"

#include "st8x00_exmd.c"
	
#include "st8x00_men1.c"

#if (com_cht == true)
	#include "st8x00_men2.c"
#endif


#if ((ST8200C == true) || (st8300c == true))
	#include "exibe_sequencia.c"
#endif


#include "st8x00_men4.c"
#if (st8500c == true)
	#include "st8500_men5.c"		// menu cargas
#else
	#include "st8x00_men5.c"		// menu bancos
#endif
#include "st8x00_men6.c"		// menu alarmes
#if ((st8100c == true) || ( st8200c == true) || ( st8300c == true))
	#include "st8x00_men7.c"		// menu desligamentos
	#include "st8x00_men8.c"		// menu manual
#endif	
#include "st8x00_men9.c"
#include "st8x00_men10.c"
#include "st8x00_men11.c"
#if (controlador == true)
	#include "st8x00_men12.c"
#endif

void reinicializa_menus(void)
{
	MENU_FIXO = read_bit(ee_bits_menu2, EE_MENU_FIXO);;
	menu_aux = read_byte(ee_menu_aux);
	qmenu = read_byte(ee_qmenu);
}

void salva_menus(void)
{
	write_bit(ee_bits_menu2, EE_MENU_FIXO, MENU_FIXO);
	write_byte(ee_menu_aux, menu_aux);
	write_byte(ee_qmenu, qmenu);
}

word inkey(char tempo)
{
	short temporizado;
	time_out = tempo;
	temporizado = true;
	if (time_out == 0)
		{
		temporizado = false;
		}
	delay_ms(500);
	teclas = 1023;
	while (teclas > 1000)
		{
		if (temporizado == true)
			{
			if (time_out == 0)
				{
				break;
				}
			}
		}
	return(teclas);
}

void exibe_menu(void)
{
	#if (ST8100C == true)
		switch(menu1)
			{
			case 1:
				{
				mensagem_rola(m_menu1, 1);
				break;
				}
			case 2:
				{
				#if (com_cht == true)
					mensagem_rola(m_menu2, 1);
					break;
				#endif
				}
			case 3:
				{
				#if (com_cht == true)
					mensagem_rola(m_menu3, 1);
					break;
				#endif
				}
			case 4:
				{
				mensagem_rola(m_menu4, 1);
				break;
				}
			case 5:
				{
				mensagem_rola(m_menu5, 1);
				break;
				}
			case 6:
				{
				mensagem_rola(m_menu6, 1);
				break;
				}
			case 7:
				{
				mensagem_rola(m_menu7, 1);
				break;
				}
			case 8:
				{
				mensagem_rola(m_menu8, 1);
				break;
				}
			case 9:
				{
				mensagem_rola(m_menu9, 1);
				break;
				}
			case 10:
				{
				mensagem_rola(m_menu10, 1);
				break;
				}
			case 11:
				{
				mensagem_rola(m_menu11, 1);
				break;
				}
			case 12:
				{
				mensagem_rola(m_menu12, 1);
				break;
				}
	    	default:
		    	{
				 menu1 = 1;
	    		}
			}
		#if (disp_7seg == true)
			buf_display[4]=tabela_caracteres[MESPACO];
		#endif
	#else
		limpa_display();
		if (menu1 == 0)
			{
			menu1 = 1;
			}

		#if (com_cht == false)
			switch (menu1)
				{
				case 2:
				case 3:
					{
					if (tecla_up == 1)
						{
						menu1 = 1;
						}
					else if (tecla_down == 1)
						{
						menu1 = 4;
						}	
					}
				}				
		#endif
		#if (st8500c == true)
			switch (menu1)
				{
				case 7:
				case 8:
					{
					if (tecla_up == 1)
						{
						menu1 = 6;
						}
					else if (tecla_down == 1)
						{
						menu1 = 9;
						}	
					}
				}				
		#endif
		
		switch(menu1)
			{
			case 1:
				{
				mensagem(1,3);
				break;
				}
			#if (com_cht == true)
				case 2:
					{
					mensagem(1,12);
					break;
					}
				case 3:
					{
					mensagem(1,13);
					break;
					}
			#else
				case 2:
				case 3:
			#endif
			case 4:
				{
				mensagem(1,7);
				break;
				}
			case 5:
				{
				mensagem(1,8);
				break;
				}
			case 6:
				{
				mensagem(1,9);
				break;
				}
			#if ((st8100c == true) || (st8200c == true) || (st8300c == true))
				case 7:
					{
					mensagem(1,10);
					break;
					}
				case 8:
					{
					mensagem(1,5);
					break;
					}
			#else
				case 7:
				case 8:
			#endif
			case 9:
				{
				mensagem(1,6);
				break;
				}
			case 10:
				{
				mensagem(1,11);
				break;
				}
			case 11:
				{
				mensagem(1,123);
				break;
				}
			case 12:
				{
				#if (monofasico == true)
					mensagem(1,138);
				#else
					mensagem(1,135);
				#endif
				break;
				}
			default:
				{
				menu1 = 1;
				break;
				}
			}			
		exibir_menu = 0;
	#endif
}        



void trata_menu(void)
{
	#if (AUTOSET == true)
		if (em_autoset == false)
			{
			if (tecla_enter == 1)
				{
				if (time_out_enter < 15)
					{
					time_out_enter++;
					}
				else
					{
					if (tempo_senha != 0)
						{
						tecla_enter = 0;
						em_autoset = true;
						time_out_autoset = 60;
						time_out_enter = 0;
						passo_autoset = 0;
						#if (st8200c == true)
							mensagem(2,149);
						#else
							#error falta mensagem
						#endif
						grava_ocorrencias(reg_auto_set);
						return;
						}
					else
						{
						trata_senha();
						time_out_enter = 0;
						return;
						}	
					}
				}
			}
		else
			{
			if (tecla_reset == true)
				{
				tecla_reset = 0;
				if (time_out_reset < 15)
					{
					time_out_reset++;
					}
				else
					{
					em_autoset = false;
					}
				}
			return;
			}
	#endif

//	if (tecla_up_down_reset == 1)
//		{
//		tecla_up_down_reset = 0;
//		#if (com_consumo == true)
//			mensagem(1,28);
//			mensagem(2,0);
//			exibiu = 0;
//			time_out_menus = 10;
//			zera_consumo();
//			#if (com_demanda == true)
//				zera_demandas();
//			#endif
//			delay_ms(1000);
//			fim_menu1();
//			return;
//		#endif
//		}

	
	if (tecla_reset_up == 1)
		{
		tecla_reset_up = 0;
		}

	if ((programando == 0) && (time_out_exibe_status_teclando == 0))
		{
		if (tem_erro == 1)
			{
			if (qmenu < 4)
				{
				if ((segundo == 0) || (segundo == 10)|| (segundo == 20) || (segundo == 30)|| (segundo == 40) || (segundo == 50))
					{
					if (exibiu_erro_menu == 0)
						{
						exibiu_erro_menu = 1;
						if (em_status == false)
							{
							#if ((st8200c == true) || (st8300c == true))
								mensagem(2,0);
							#endif
							exibe_erro();
							}
						time_out_exibe_erro = 2;
						exibiu = 0;
						}
					return;
					}
				else
					{
					if (time_out_exibe_erro != 0)
						{
						return;
						}
					}
				}
			}
		}
	exibiu_erro_menu = 0;

	switch (qmenu)
		{
		case 1:		
			{
			trata_menu1();
			break;
			}
		#if (com_cht == true)
			case 2:		
			case 3:		
				{
				trata_menu2();
				break;
				}
		#else
			case 2:
			case 3:
		#endif
		case 4:		
			{
			trata_menu4();
			break;
			}
		case 5:		
			{
			trata_menu5();
			break;
			}
		case 6:		
			{
			trata_menu6();
			break;
			}
		#if ((st8100c == true) || ( st8200c == true) || ( st8300c == true))
			case 7:		
				{
				trata_menu7();
				break;
				}
			case 8:		
				{
				trata_menu8();
				break;
				}
		#else
			case 7:
			case 8:
		#endif
		case 9:		
			{
			trata_menu9();
			break;
			}
		case 10:		
			{
			trata_menu10();
			break;
			}
		case 11:
			{
			trata_menu11();
			break;
			}
		case 12:
			{
			trata_menu12();
			break;
			}
		default:
			{
			if (tecla_up == 1)
				{
		 		if (menu1 > 1)
		 			{
			 		menu1--;
					rolando = false;
				 	}
		 		exibe_menu();
				tecla_up = 0;
				}
			else if (tecla_down == 1)
				{
				if (menu1 < nro_menus)
		 			{
		 			menu1++;
					rolando = false;
					}
				else
					{
		 			menu1 = 1;
					rolando = false;
					}
	 			exibe_menu();
				tecla_down = 0;
				}
			else if (tecla_enter == 1)
				{
		 		tecla_enter = 0;
				rolando = false;
				switch(menu1)
					{
					case 1:
						{
						trata_menu1();
						break;
						}
					#if (com_cht == true)
						case 2:
						case 3:
							{
							qchtt = 1;
							fase_cht = 'R';
							trata_menu2();
							break;
							}
					#else
						case 2:
						case 3:
					#endif
					case 4:
						{
						trata_menu4();		/* menu programacao */
						break;
						}
					case 5:
						{
						trata_menu5();
						break;
						}
					case 6:
						{
						trata_menu6();
						break;
						}
					#if ((st8100c == true) || ( st8200c == true) || ( st8300c == true))
						case 7:
							{
							trata_menu7();
							break;
							}
						case 8:
							{
							trata_menu8();
							break;
							}
					#else
						case 7:
						case 8:
					#endif
					case 9:
						{
						trata_menu9();
						break;
						}
					case 10:
						{
						trata_menu10();
						break;
						}
					case 11:
						{
						trata_menu11();
						break;
						}
					case 12:
						{
						rolando = false;
						trata_menu12();
						break;
						}
					default:
						{
						trata_menu1();
						}
					}
				}		
			else if (tecla_reset == 1)
				{
				fim_menu1();
				}
    	    }
        }
		
}



// Definicao dos valores a serem comparados para definicao das teclas via conversor AD.
#define VAL_UP				2800
#define VAL_DOWN			2030
#define VAL_UP_DOWN			1660
#define VAL_ENTER			1420
#define VAL_ENTER_DOWN		1260
#define VAL_RESET			715
#define VAL_UP_RESET		680
#define VAL_UP_DOWN_RESET	600
#define VAL_ENTER_RESET		530

void teclado(void){
	if (time_tecla == 0){
		if (teclas > 3000){
//			ha_tecla = true;
			acelera_teclado = 0;
		}
		else {
			#if (disp_lcd == true)
				time_out_back = 180;
			#endif
			rolando = false;
			
			time_out_exibe_status_teclando = 10;				
			time_out_menus = 10;	//120;
			teclando = 30;
//			teclando_2 = 5;
			#if (disp_lcd == true)
				val_pwm = LIMITE_VAL_PWM;
			#endif


			time_tecla = 1 + (MAX_TIME_TECLA - acelera_teclado);

			if (teclas >= VAL_UP)
				{
				tecla_up = 1;			/* tecla up pressionada */
				#if (AUTOSET == true)
					time_out_enter = 0;
					time_out_reset = 0;
				#endif
				}
			else if (teclas >= VAL_DOWN)
				{
				tecla_down = 1;			/* tecla down pressionada */
				#if (AUTOSET == true)
					time_out_enter = 0;
					time_out_reset = 0;
				#endif
				}
			else if (teclas >= VAL_UP_DOWN)
				{
				tecla_up_down = 1;  	/* tecla up e down pressionadas */
				}
			else if (teclas >= VAL_ENTER)
				{
				tecla_enter = 1;			/* tecla enter pressionada */
				teclou_enter = ~teclou_enter;
				#if (AUTOSET == true)
					time_out_reset = 0;
				#endif
				}
			else if (teclas >= VAL_ENTER_DOWN)
				{
				tecla_enter_down = 1;  	/* tecla enter e down pressionadas */
				}
			else if (teclas >= VAL_RESET)
				{
				tecla_reset = 1;			/* tecla reset pressionada */
				output_low(alarme);
				#if (disp_lcd == true)
					#if (st8200c == false)
					    setup_timer_2(T2_DIV_BY_4, 127, 1);
						setup_ccp1(ccp_pwm);
						set_pwm1_duty(val_pwm);	
					#endif
				#endif
				#if (AUTOSET == true)
					time_out_enter = 0;
				#endif
				}
			else if (teclas >= VAL_UP_RESET)
				{
				tecla_reset_up = 1;	/* tecla up e reset pressionadas */
				}
//			else if (teclas >= VAL_UP_DOWN_RESET)
//				{
//				tecla_up_down_reset = TRUE;
//				}
			else if (teclas >= VAL_ENTER_RESET)
				{
				tecla_enter_reset = 1;	/* tecla enter e reset pressionadas */
				tempo_senha = 255;		
				exibiu = 0;
				#if (ST8100C == true)
					if (rolando == false)
						{
						ja_rolou = false;
						mensagem_rola(m_prog_liberada, 1);
						buf_display[4]=255;
						}
				#else
					mensagem (2,50);
				#endif
				time_out_menus = 10;	//120;
				}

			if (acelera_teclado < MAX_TIME_TECLA )
				{
				acelera_teclado++;	
				}
			teclas = 4095;
			}
		trata_menu();
		}
	}


void trata_senha(void)
{
	#if (ST8100C == true)
		if (rolando == false)
			{
			time_out2 = 15;
			ja_rolou = false;
			mensagem_rola(m_prog_nao_auto, 1);
			buf_display[4] = 255;
			}
	#else
		mensagem (2,49);
	#endif
}   



void trata_time_out_menus(void){
//		if (com_manual == false){
//			if (min_kvar == 0){
//				trata_desligamentos_old();
//			}
//		}
//		if (teclando_2 != 0){
//			teclando_2--;
//		}

	if (teclando != 0){
		teclando--;
		time_out_menus = VAL_TIME_OUT_MENUS1;
		return;
	}
	if (teclando == 0){
		com_manual = false;
	}
	if (time_out_menus != 0){
		if (MENU_FIXO == 0){
			time_out_menus--;
		}
		if (time_out_menus == 0){
			em_status = false;
			time_out_menus = VAL_TIME_OUT_MENUS1;
		 	if (qmenu == 1){
				exibiu = 0;
				reset_rolar();
				if (menu_aux == 0){
					menu_aux = 8;
				}
				if (menu_aux < nro_menus1){
	 				menu_aux++;
	 			}
	 			else{
	 				menu_aux = 1;
				}
		 	}
			else{
			 	#if (disp_lcd == true)
					desativa_cursor();
				#endif
			 	 	
			 	exibiu = 0;
				tecla_reset = 0;
				menu1 = 0;
				menu_aux = 1;
				programando = 0;
				qmenu = 1;
		 	}
	 	}
	}
}
	


void fim_menu1(void){		
	tecla_reset = 0;
	mensagem_inicial();
	if (qmenu != 0){
		salva_menus();
		calcula_mul_tc();
	}
	rolando = false;
	ja_rolou = false;
	menu1 = 0;
	menu_aux = 1;
	programando = 0;
	qmenu = 0;
	MENU_FIXO = 0;
	time_out_menus = 5;
}

#if (disp_7seg == true)
	void exibe_off(void)
	{
		buf_display[0] = tabela_caracteres[MESPACO];
		buf_display[1] = tabela_caracteres[MO];
		buf_display[2] = tabela_caracteres[MF];
		buf_display[3] = tabela_caracteres[MF];
	}
#endif

