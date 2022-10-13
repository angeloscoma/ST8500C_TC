/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_MAIN                                                        *
; Funcao: MODULO PRINCIPAL DE CONTROLE									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */

  
#define MAX_TIME_TECLA	25

word tabela_programa[15];
char tabela_alarmes[12];

char que_ocor[nro_ocorrencia];
char buf_display[13];

#if (st92 == true)
	void leds(char qleds)
	{
		buf_display[12] = 0;
 		buf_display[12] = qleds;
	}
#endif


short M1_C1;
short M1_C2;
short M1_C3;
short M1_C4;
short M1_C5;
short M1_C6;
short M1_C7;
short M1_C8;
short MENU_FIXO;

char aux_menu1;
char fase_cht;
char aux_tab;
char ultima_tecla;


void teclado(void);
void trata_menu(void);
void exibe_menu(void);
void trata_senha(void);
void trata_time_out_menus(void);
#if (disp_7seg == true)
	void display(char, word,  char,  char);
	void display_n(char, word, char);
	void displayfp(char, signed word);
	void leds(char);
	void mensagem(char, char);
#endif

//char pob(char);
//void binasc2(word);
//void binasc(char);

void trata_menu6(void);
void exibe_data_hora(void);
void salva_data_hora(void);
void exibe_menu6(void);
//void rtc_set_datetime(void);

void reinicializa_menus(void);
void salva_menus(void);

#endif
#include "st_erros.c"
#if ((st9430r == true) || (st9400r == true))
	#include "st94mens.c"
	#include "st94leds.c"
#endif
#endif
#include "st94exmd.c"
#include "st94men1.c"
#if (com_cht == true)
	#include "st94men2.c"
#endif	
#include "st94men4.c"
#include "st94men5.c"
#include "st94men6.c"
#include "st94men7.c"


void reinicializa_menus(void)
{
	M1_C1 = read_bit(ee_bits_menu, EE_M1_C1);
	M1_C2 = read_bit(ee_bits_menu, EE_M1_C2);
	M1_C3 = read_bit(ee_bits_menu, EE_M1_C3);
	M1_C4 = read_bit(ee_bits_menu, EE_M1_C4);
	M1_C5 = read_bit(ee_bits_menu, EE_M1_C5);
	M1_C6 = read_bit(ee_bits_menu, EE_M1_C6);
	M1_C7 = read_bit(ee_bits_menu, EE_M1_C7);
	M1_C8 = read_bit(ee_bits_menu, EE_M1_C8);
	MENU_FIXO = read_bit(ee_bits_menu2, EE_MENU_FIXO);;
	menu_aux = read_byte(ee_menu_aux);

}

void salva_menus(void)
{
	write_bit(ee_bits_menu, EE_M1_C1, M1_C1);
	write_bit(ee_bits_menu, EE_M1_C2, M1_C2);
	write_bit(ee_bits_menu, EE_M1_C3, M1_C3);
	write_bit(ee_bits_menu, EE_M1_C4, M1_C4);
	write_bit(ee_bits_menu, EE_M1_C5, M1_C5);
	write_bit(ee_bits_menu, EE_M1_C6, M1_C6);
	write_bit(ee_bits_menu, EE_M1_C7, M1_C7);
	write_bit(ee_bits_menu, EE_M1_C8, M1_C8);
	write_bit(ee_bits_menu2, EE_MENU_FIXO, MENU_FIXO);
	write_byte(ee_menu_aux, menu_aux);

}


void exibe_menu(void)
{
re_exibe_menu:
	#if (disp_7seg == false)
		mensagem(2,0);
	#endif
	switch(menu1)
		{
		case 1:
			{
			#if (disp_7seg == true)
				mensagem(m_menu1,1);
				limpa_linha(3);
				buf_display[12] = tabela_caracteres[MESPACO];
			#else
				mensagem(1,3);
			#endif
			break;
			}
		case 2:
			{
			#if (disp_7seg == true)
				mensagem(m_menu2,1);
				limpa_linha(3);
				buf_display[12] = tabela_caracteres[MESPACO];
			#else
				mensagem(1,4);
			#endif
			break;
			}
		case 3:
			{
			#if (disp_7seg == true)
				mensagem(m_menu3,1);
				limpa_linha(3);
				buf_display[12] = tabela_caracteres[MESPACO];
			#else
				mensagem(1,5);
			#endif
			break;
			}
		case 4:
			{
			#if (disp_7seg == true)
				mensagem(m_menu4,1);
				limpa_linha(3);
				buf_display[12] = tabela_caracteres[MESPACO];
			#else
				mensagem(1,6);
			#endif
			break;
			}
		case 5:
			{
			#if (disp_7seg == true)
				mensagem(m_menu5,1);
				limpa_linha(3);
				buf_display[12] = tabela_caracteres[MESPACO];
			#else
				mensagem(1,7);
			#endif
			break;
			}
		case 6:
			{
			#if (com_relogio == true)
				#if (disp_7seg == true)
					mensagem(m_menu6,1);
					limpa_linha(3);
					buf_display[12] = tabela_caracteres[MESPACO];
				#else
					mensagem(1,8);
				#endif
				break;
			#endif
    	    }
		case 7:
			{
			#if (disp_7seg == true)
				mensagem(m_menu7,1);
				limpa_linha(3);
				buf_display[12]= tabela_caracteres[MESPACO];
			#else
				mensagem(1,9);
			#endif
			break;
    	    }
    	default:
	    	{
			menu1 = 1;
			goto re_exibe_menu;
    		}
		}
}        


void fim_menu1(void)
{
	tecla_reset = 0;
	menu1 = 0;
	menu_aux = 0;
	programando = 0;
	M1_C1 = 0;
	M1_C2 = 0;
	M1_C3 = 0;
	M1_C4 = 0;
	M1_C5 = 0;
	M1_C6 = 0;
	M1_C7 = 0;
	M1_C8 = 0;
	MENU_FIXO = 0;
	mensagem_inicial();
	time_out_menus = 5;
	salva_menus();
	calcula_mul_tc();
}


void trata_menu(void)
{
	if (tecla_reset_up == 1)
		{
		tecla_reset_up = 0;
		tempo_senha = 255;		
		#if (st92 == true)
			mensagem(2,48);
 		#else
			mensagem(m_prog_liberada,1);
			buf_display[12]=255;
		#endif
		delay_ms(1000);
		exibiu = 0;
		
		time_out_menus = 10;
		return;		
		}

	if (tecla_up_down_reset == 1)
		{
		tecla_up_down_reset = 0;
		#if (st92 == true)
			mensagem(1,28);
			mensagem(2,0);
			exibiu = 0;
 		#else
			mensagem(mapaga,1);
			buf_display[12] = 255;
		#endif
		time_out_menus = 10;
		#if (com_consumo == true)
			zera_consumo();
		#endif
		delay_ms(1000);
		fim_menu1();
		return;
		}

	
	if (M1_C1==1)
		{
		 trata_menu1();
		}
	#if (com_cht == true)
		else if (M1_C2 == 1)
			{
			 trata_menu2();
			}        
		else if (M1_C3 == 1)
			{
			 trata_menu2();		//alterado para utilizar o mesmo menu para corrente e tensão
			}
	#endif
	else if (M1_C4 == 1)
		{
		 trata_menu4();
		}
	else if (M1_C5 == 1)
		{
		 trata_menu5();
		}
	else if (M1_C6 == 1)
		{
		 trata_menu6();
		}
	else if (M1_C7 == 1)
		{
		 trata_menu7();
		}
	else		
		{
		if (tecla_up == 1)
			{
			tecla_up = 0;
		 	if (menu1 > 0)
		 		{
		 		menu1--;
			 	}
		 	exibe_menu();
		 	return;
			}
		else if (tecla_down == 1)
			{
			tecla_down = 0;
			if (menu1 < nro_menus)
		 		{
		 		menu1++;
		 		}
	 		exibe_menu();
	 		return;
			}
		else if (tecla_enter == 1)
			{
		 	tecla_enter = 0;
		 	menu_aux = 1;
		 	goto m1_seleciona;
			}		
		else if (tecla_reset == 1)
			{
			fim_menu1();
			}
        }
        return;
        

		
m1_seleciona:
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
				trata_menu2();		//alterado para utilizar o mesmo menu para corrente e tensão
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
			#if (com_relogio == true)
				trata_menu6();
				break;
			#endif
			}
		case 7: 
			{
			trata_menu7();
			break;
			}
		default:
			{
			trata_menu1();
			}
		}
		
}



// Definicao dos valores a serem comparados para definicao das teclas via conversor AD.
#define VAL_UP			690		//701
#define VAL_DOWN		500		//511
#define VAL_UP_DOWN		410		//415
#define VAL_ENTER		350		//360
#define VAL_ENTER_DOWN	240		//250
#define VAL_RESET		180		//180
#define VAL_UP_RESET	165		//168
#define VAL_RESET_DOWN		150		
#define VAL_UP_DOWN_RESET	140	//
#define VAL_ENTER_RESET	120		//135


void teclado(void)
{
	if (time_tecla == 0)
		{
		if (ha_tecla == false)
			{
			if (teclas < 1000)
				{
				ha_tecla = true;
				}
			}
		if (ha_tecla == true)
			{
			time_out_exibe_status_teclando = 10;				
			time_out_menus = 10;
			teclando = 30;
			teclando_2 = 5;
			rolando = false;
			#if (st92 == false)
				ptr_rola = 0;
			#endif

			time_tecla = MAX_TIME_TECLA - acelera_teclado;

			if (teclas > VAL_UP+100)
				{
				enter_low = 1;
				}
			else if (teclas >= VAL_UP)
				{
				tecla_up = 1;			/* tecla up pressionada */
				val_pwm = LIMITE_VAL_PWM;
				}
			else if (teclas >= VAL_DOWN)
				{
				tecla_down = 1;			/* tecla down pressionada */
				val_pwm = LIMITE_VAL_PWM;
				}
			else if (teclas >= VAL_UP_DOWN)
				{
				tecla_up_down = 1;  	/* tecla up e down pressionadas */
				}
			else if (teclas >= VAL_ENTER)
				{
				if (enter_low == 1)
					{
					tecla_enter = 1;			/* tecla enter pressionada */
					val_pwm = LIMITE_VAL_PWM;
					enter_low = 0;
					}
				}
			else if (teclas >= VAL_ENTER_DOWN)
				{
				tecla_enter_down = 1;  	/* tecla enter e down pressionadas */
				}
			else if (teclas >= VAL_RESET)
				{
				tecla_reset = 1;			/* tecla reset pressionada */
				output_low(alarme);
				val_pwm = LIMITE_VAL_PWM;
				#if com_display	
				    setup_timer_2(T2_DIV_BY_4, 127, 1);
					setup_ccp1(ccp_pwm);
					set_pwm1_duty(val_pwm);	
				#endif
				}
			else if (teclas >= VAL_UP_RESET)
				{
				tecla_reset_up = 1;		/* tecla up e reset pressionadas */
				}
			else if (teclas >= VAL_RESET_DOWN)
				{
				}
			else if (teclas >= VAL_UP_DOWN_RESET)
				{
				tecla_up_down_reset = TRUE;
				}
			else if (teclas >= VAL_ENTER_RESET)
				{
				tecla_enter_reset = 1;	/* tecla enter e reset pressionadas */
				}
			else
				{
				enter_low = 1;
				}
			if (ultima_tecla == teclas)
				{
				if (acelera_teclado < (MAX_TIME_TECLA - (MAX_TIME_TECLA - (MAX_TIME_TECLA / 5))) )
					{
					acelera_teclado = acelera_teclado + (MAX_TIME_TECLA / 5);
					if (acelera_teclado >= MAX_TIME_TECLA)
						{
						acelera_teclado = MAX_TIME_TECLA - 1;	
						}
					}
				}
			else
				{
				acelera_teclado = 0;
				}
			ultima_tecla = teclas;
			teclas = 1023;
			ha_tecla = false;
			}
		else
			{
			enter_low = 1;
			}

		if ((programando == 0) && (time_out_exibe_status_teclando == 0))
			{
			if (tem_erro == 1)
				{
				if ((M1_C1 == 1) || (M1_C2 == 1) || (M1_C3 == 1))
					{
					if ((segundo == 0) || (segundo == 10)|| (segundo == 20) || (segundo == 30)|| (segundo == 40) || (segundo == 50))
						{
						if (exibiu_erro_menu == 0)
							{
							exibiu_erro_menu = 1;
							exibe_erro();
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

		trata_menu();

		}
	
}


void trata_senha(void)
{
	#if (st92 == true)
		mensagem(2,49);
	#else
		mensagem(m_prog_nao_auto,1);
		buf_display[12]=255;
	#endif
	delay_ms(2000);
#if (com_regs == true)
	grava_ocorrencias(reg_prog_nauto);
#endif		
}   



void trata_time_out_menus(void)
{	
	if (MENU_FIXO == 0)
		{
		if (teclando_2 != 0)
			{
			teclando_2--;
			}
		if (teclando != 0)
			{
			 teclando--;
			 time_out_menus = 10;
			 return;
			}
		if (time_out_menus != 0)
			{
			 time_out_menus--;
			 if (time_out_menus == 0)
			 	{
				 time_out_menus = 10;
				 exibiu = 0;
			 	 if (M1_C1 == 1)
			 	 	{
			 	 	if (menu_aux == 0)
			 	 		{
			 	 		menu_aux = 1;
			 	 		}
			 		if (menu_aux < nro_menus1)
		 				{
		 				menu_aux++;
		 				}
		 			else
		 				{
		 				menu_aux = 1;
		 				}
			 	 	}
			 	 else
			 	 	{
					tecla_reset = 0;
					menu1 = 0;
					menu_aux = 1;
					programando = 0;
					M1_C1 = 1;
					M1_C2 = 0;
					M1_C3 = 0;
					M1_C4 = 0;
					M1_C5 = 0;
					M1_C6 = 0;
					M1_C7 = 0;
					M1_C8 = 0;
			 	 	}
			 	}
			}
		}
}
	


