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


char ultima_tecla;
short MENU_FIXO;


void reinicializa_menus(void)
{
	MENU_FIXO = read_bit(ee_bits_menu2, EE_MENU_FIXO);;
	menu_aux = read_byte(ee_menu_aux);
	qmenu = read_byte(ee_qmenu);
	menu1 = read_byte(ee_menu1);
	exibiu = 0;
	time_tecla = 0;
}

void salva_menus(void)
{
	write_bit(ee_bits_menu2, EE_MENU_FIXO, MENU_FIXO);
	write_byte(ee_menu_aux, menu_aux);
	write_byte(ee_qmenu, qmenu);
	write_byte(ee_menu1, menu1);
}



void exibe_menu(void);
void teclado(void);
void trata_senha(void);
void trata_time_out_menus(void);
void encerra_menus(void);


#include "st_exib.c"
#include "st_erros.c"
#include "st_men1.c"
#if (com_cht == true)
	#include "st_men2.c"
	#include "st_men3.c"
#endif
#include "st_men4.c"
#include "st_men5.c"
#include "st_coma.c"
//#include "st_men6.c"



void trata_menu(void)
{
//	if (tecla_reset_up == 1)
//		{
//		tecla_reset_up = 0;
//		tempo_senha = 255;		
//		mensagem(1, m_prog_liberada);
//		if (codigo != reg_prog_tecla)
//			{
//			grava_ocorrencias(reg_prog_tecla);
//			}
//		return;		
//		}
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
						mensagem(4,0);
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
	switch(qmenu)
		{
		case 1:
			{
		 	trata_menu1();
		 	break;
			}
		case 2:
			{
			#if (com_cht == true)
		 		trata_menu2();
			#else
				qmenu = 3;
			#endif		 	
			break;
			}        
		case 3:
			{
			#if (com_cht == true)
		 		trata_menu3();
			#else
				qmenu = 4;
			#endif	
			break;
			}
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
		 	trata_menu_coma();
		 	break;
			}
		default:
			{
			if (tecla_up == 1)
				{
				tecla_up = 0;
				exibiu = 0;
			 	if (menu1 > 1)
			 		{
				 	if (menu1 == 4)
				 		{
					 	menu1 = 2;
					 	}
					else
						{
				 		menu1--;
				 		}
				 	}
		 		exibe_menu();
				}
			else if (tecla_down == 1)
				{
				tecla_down = 0;
				exibiu = 0;
				if (menu1 < nro_menus)
		 			{
			 		if (menu1 == 2)
			 			{
				 		menu1 = 4;
				 		}
				 	else
				 		{
			 			menu1++;
			 			}
			 		}
		 		exibe_menu();
				}
			else if (tecla_enter == 1)
				{
				exibiu = 0;
		 		tecla_enter = 0;
			 	menu_aux = 1;
			 	switch(menu1)
			 		{
					case 1:
						{
						salva_menus();
						trata_menu1();
						break;
						}
					case 2:
						{
						#if (com_cht == true)
							qchtt = 0;
							trata_menu2();
						#else
							qmenu = 3;
						#endif		 	
						break;
						}
					case 3:
						{
						#if (com_cht == true)
							qchtt = 0;
							trata_menu3();
						#else
							qmenu = 4;
						#endif		 	
						break;
						}
					case 4:
						{
						trata_menu4();		/* menu programacao */
						break;
						}
					case 5:
						{
						trata_menu5();		/* menu programacao de registros */
						break;
						}
					case 6:
						{
					 	trata_menu_coma();
		 				break;
						}
					default:
						{
//						trata_menu1();
						}
					}
				}		
			else if (tecla_reset == 1)
				{
				encerra_menus();
				}
        	}
        }
}


void encerra_menus(void)
{
	limpa_display();
	time_out_menus = 120;
	tecla_up = 0;
	tecla_down = 0;
	tecla_reset = 0;
	tecla_enter = 0;
	digitando_texto = 0;
	menu1 = 0;
	menu_aux = 0;
	programando = 0;
	qmenu = 0;
	exibiu = 0;
	exibe_status();
	MENU_FIXO = 0;
	salva_menus();
}

void exibe_menu(void)
{
	if (menu1 == 0)
		{
		menu1 = 1;
		}

	if (menu1 < 6)
		{
		mensagem(1,m_menu1);
		mensagem(2,m_menu2);
		mensagem(3,m_menu4);
		mensagem(4,m_menu5);
		}
	else
		{
		mensagem(1,m_menu2);
		mensagem(2,m_menu4);
		mensagem(3,m_menu5);
		mensagem(4,7);
		}

		
	switch(menu1)
		{
		case 1:
			{
			lcd_gotoxy(1,1);
			display('[');
			lcd_gotoxy(16,1);
			display(']');
			break;
			}
		case 2:
			{
			}
		case 3:
			{
			lcd_gotoxy(1,2);
			display('[');
			lcd_gotoxy(16,2);
			display(']');
			break;
			}
		case 4:
			{
			lcd_gotoxy(1,3);
			display('[');
			lcd_gotoxy(16,3);
			display(']');
			break;
			}
		default:
			{
			lcd_gotoxy(1,4);
			display('[');
			lcd_gotoxy(16,4);
			display(']');
			break;
			}
		}			
	
	exibir_menu = 0;
}        



// Definicao dos valores a serem comparados para definicao das teclas via conversor AD.
#define VAL_UP			690-2
#define VAL_DOWN		500-2
#define VAL_UP_DOWN		417-2
#define VAL_ENTER		355-2
#define VAL_ENTER_DOWN	270-2
#define VAL_RESET		180-2
#define VAL_UP_RESET	170-2
#define VAL_ENTER_RESET	140-2


void teclado(void){
	if (time_tecla == 0){
		if (ha_tecla == false){
			if (teclas < 1000){
				ha_tecla = true;
			}
		}
		if (ha_tecla == true){
			time_out_exibe_status_teclando = 10;
			time_out_menus = 120;
			teclando = 30;
			teclando_2 = 5;
			val_pwm = LIMITE_VAL_PWM;

			time_tecla = MAX_TIME_TECLA - acelera_teclado;

			if (teclas > VAL_UP+100){
				enter_low = 1;
			}
			else if (teclas >= VAL_UP){
				tecla_up = 1;			/* tecla up pressionada */
//				val_pwm = LIMITE_VAL_PWM;
			}
			else if (teclas >= VAL_DOWN){
				tecla_down = 1;			/* tecla down pressionada */
//				val_pwm = LIMITE_VAL_PWM;
			}
			else if (teclas >= VAL_UP_DOWN){
				tecla_up_down = 1;  	/* tecla up e down pressionadas */
			}
			else if (teclas >= VAL_ENTER){
				if (enter_low == 1){
					tecla_enter = 1;			/* tecla enter pressionada */
//					val_pwm = LIMITE_VAL_PWM;
					enter_low = 0;
				}
			}
			else if (teclas >= VAL_ENTER_DOWN){
				tecla_enter_down = 1;  	/* tecla enter e down pressionadas */
			}
			else if (teclas >= VAL_RESET){
				tecla_reset = 1;			/* tecla reset pressionada */
//				val_pwm = LIMITE_VAL_PWM;
//				#if (com_display == true)
//					setup_timer_2(T2_DIV_BY_4, 127, 1);
//					setup_ccp1(ccp_pwm);
//					set_pwm1_duty(val_pwm);	
//					desativa_cursor();
//				#endif
			}
			else if (teclas >= VAL_UP_RESET){
				tecla_reset_up = 1;	/* tecla up e reset pressionadas */
			}
			else if (teclas >= VAL_ENTER_RESET){
				tecla_enter_reset = 1;	/* tecla enter e reset pressionadas */
			}
			else{
				enter_low = 1;
			}
			if (ultima_tecla == teclas){
				if (acelera_teclado < (MAX_TIME_TECLA - 20)){
					acelera_teclado = acelera_teclado + 10;
				}
			}
			else{
				acelera_teclado = 0;
			}
			ultima_tecla = teclas;
			teclas = 1023;
			ha_tecla = false;
		}
		else{
			enter_low = 1;
		}
		trata_menu();
	}
}


void trata_senha(void)
{
	mensagem(1,m_prog_nao_auto);
#if (com_regs == true)
	grava_ocorrencias(reg_prog_nauto);
#endif		
}   



void trata_time_out_menus(void)
{	
	if (MENU_FIXO == 1)
		{
		return;
		}
	if (teclando_2 != 0)
		{
		teclando_2--;
		}
	if (teclando != 0)
		{
		 teclando--;
		 time_out_menus = 120;
		 return;
		}
	if (time_out_menus != 0)
		{
		 time_out_menus--;
		 if (time_out_menus == 0)
		 	{
			 time_out_menus = 120;
			 exibiu = 0;
		 	 if (qmenu == 1)
		 	 	{
		 	 	if (menu_aux == 0)
		 	 		{
		 	 		menu_aux = 1;
		 	 		}
		 		else if (menu_aux < nro_menus1)
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
				menu1 = 1;
				menu_aux = 1;
				programando = 0;
				qmenu = 1;
				exibe_medidas();
		 	 	}
		 	}
		}
}
	
