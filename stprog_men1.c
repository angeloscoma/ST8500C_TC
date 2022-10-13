/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_MAIN                                                        *
; Funcao: MODULO PRINCIPAL DE CONTROLE									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */
  
void exibe_medidas(void);


void trata_menu1(void)
{
/* MENU DE MEDIDAS ELÉTRICAS */
	if (qmenu != 1)
		{		
		qmenu = 1;
		}
	if (tecla_up==1)
		{
		exibir_menu = 1;
		exibiu = 0;
	 	if (menu_aux > 0)
	 		{
	 		menu_aux--;
		 	}
		 }
	else if (tecla_down==1)
		{
		exibir_menu = 1;
		exibiu = 0;
		 if (menu_aux < 4)
	 		{
	 		menu_aux++;
	 		}
		}
	else if (tecla_enter==1)
		{
	 	tecla_enter = 0;
		teclou_enter = ~teclou_enter;
		exibir_menu = 1;
		exibiu = 0;
		MENU_FIXO = 1;
		salva_menus();
		}		
	else if (tecla_reset==1)
		{
		if (MENU_FIXO == 1)
			{
			MENU_FIXO = 0;
			}
		else
			{
			encerra_menus();
			return;
			}
		}
	exibe_medidas();
    tecla_down=0;
	tecla_up=0;
	
}


void exibe_tensao_1_2(void)
{
	#if (simula_rep == true)
/*		lcd_gotoxy(1,1);
		if (RELE1 == TRUE)
			{
			display('1');
			}
		else
			{
			display('0');
			}
		if (RELE2 == TRUE)
			{
			display('1');
			}
		else
			{
			display('0');
			}
		if (RELE3 == TRUE)
			{
			display('1');
			}
		else
			{
			display('0');
			}
		if (RELE4 == TRUE)
			{
			display('1');
			}
		else
			{
			display('0');
			}
		if (RELE5 == TRUE)
			{
			display('1');
			}
		else
			{
			display('0');
			}
		if (RELE6 == TRUE)
			{
			display('1');
			}
		else
			{
			display('0');
			}
		if (RELE7 == TRUE)
			{
			display('1');
			}
		else
			{
			display('0');
			}
		if (RELE8 == TRUE)
			{
			display('1');
			}
		else
			{
			display('0');
			}
		if (RELE9 == TRUE)
			{
			display('1');
			}
		else
			{
			display('0');
			}
		if (RELE10 == TRUE)
			{
			display('1');
			}
		else
			{
			display('0');
			}
		if (RELE11 == TRUE)
			{
			display('1');
			}
		else
			{
			display('0');
			}
		if (RELE12 == TRUE)
			{
			display('1');
			}
		else
			{
			display('0');
			}
		if (RELE13 == TRUE)
			{
			display('1');
			}
		else
			{
			display('0');
			}
		if (RELE14 == TRUE)
			{
			display('1');
			}
		else
			{
			display('0');
			}
		if (RELE15 == TRUE)
			{
			display('1');
			}
		else
			{
			display('0');
			}
		if (RELE16 == TRUE)
			{
			display('1');
			}
		else
			{
			display('0');
			}

*/
		if (exibiu == 0){
			exibiu = 1;
			mensagem(1,3);
			mensagem(2,10);
			mensagem(3,11);
			mensagem(4,9);
		}
		displayp(62,time_integra,3,0,0);
//		display('/');
		displayp(28,pulso_ati,5,0,0);
//		display('/');
		displayp(44,pulso_reat,5,0,0);
//		displayp(33,carga_total_at,4,0,0);
//		display('/');
//		displayp(38,carga_total_reat,4,0,0);
//		display('/');
		displayfp(53,fator_pot_rep);
			
//		displayp(60,hora,2,0,0);
//		display(':');
//		displayp(63,minuto,2,0,0);
					

	#else
		if (exibiu == 0)
			{
			exibiu = 1;
			mensagem(1,6);
			mensagem(2,9);
			mensagem(3,10);
			mensagem(4,11);
			}
		displayp(19,tensao_r,3,1,6);	/* exibe tensao R no display1 com 1 casa decimal entrada em q6)*/
		displayp(35,tensao_s,3,1,6);	/* exibe tensao S no display1 com 1 casa decimal entrada em q6)*/
		displayp(51,tensao_t,3,1,6);	/* exibe tensao T no display1 com 1 casa decimal entrada em q6)*/
	
		displayp(27,medicoes[med_tensao_r],3,1,6);	/* exibe tensao R no display1 com 1 casa decimal entrada em q6)*/
		displayp(43,medicoes[med_tensao_s],3,1,6);	/* exibe tensao S no display1 com 1 casa decimal entrada em q6)*/
		displayp(59,medicoes[med_tensao_t],3,1,6);	/* exibe tensao T no display1 com 1 casa decimal entrada em q6)*/
		
	#endif

}

void exibe_corrente_1_2(void)
{
	if (exibiu == 0)
		{
		exibiu = 1;
		mensagem(1,5);
		mensagem(2,9);
		mensagem(3,10);
		mensagem(4,11);
		}
	displayp(19,corrente_r,3,1,3);
	displayp(35,corrente_s,3,1,3);
	displayp(51,corrente_t,3,1,3);

	displayp(27,medicoes[med_corrente_r],3,1,3);	/* exibe tensao R no display1 com 1 casa decimal entrada em q6)*/
	displayp(43,medicoes[med_corrente_s],3,1,3);	/* exibe tensao S no display1 com 1 casa decimal entrada em q6)*/
	displayp(59,medicoes[med_corrente_t],3,1,3);	/* exibe tensao T no display1 com 1 casa decimal entrada em q6)*/
}

void exibe_fp_1_2(void)
{
	if (exibiu == 0)
		{
		exibiu = 1;
		mensagem(1,7);
		mensagem(2,9);
		mensagem(3,10);
		mensagem(4,11);
		}
	displayfp(19,fator_pot_r);
	displayfp(35,fator_pot_s);
	displayfp(51,fator_pot_t);

	displayfp(27,medicoes[med_fp_r]);
	displayfp(43,medicoes[med_fp_s]);
	displayfp(59,medicoes[med_fp_r]);
}

void exibe_kw_1_2(void)
{
	if (exibiu == 0)
		{
		exibiu = 1;
		mensagem(1,8);
		mensagem(2,9);
		mensagem(3,10);
		mensagem(4,11);
		}
	displayp(19,pot_ativa_r,3,1,5);
	displayp(35,pot_ativa_s,3,1,5);
	displayp(51,pot_ativa_t,3,1,5);

	displayp(27,medicoes[med_kw_r],3,1,5);	/* exibe tensao R no display1 com 1 casa decimal entrada em q6)*/
	displayp(43,medicoes[med_kw_s],3,1,5);	/* exibe tensao S no display1 com 1 casa decimal entrada em q6)*/
	displayp(59,medicoes[med_kw_t],3,1,5);	/* exibe tensao T no display1 com 1 casa decimal entrada em q6)*/
}



void exibe_medidas(void)
{
	#if (simula_rep == true)
		menu_aux = 1;
	#endif
	
	if (exibir_menu == 1)
		{
		 switch(menu_aux)
	 		{
	 		case 1:
	 			{
	 			exibe_tensao_1_2();
				break;
				}
	 		case 2:
	 			{
	 			exibe_corrente_1_2();
				break;
				}
	 		case 3:
	 			{
	 			exibe_fp_1_2();
				break;
				}
	 		case 4:
	 			{
	 			exibe_kw_1_2();
				break;
				}
	 		default:
	 			{
				menu_aux = 1;
				}
			}
		}

	exibir_menu = 0;
		
}



