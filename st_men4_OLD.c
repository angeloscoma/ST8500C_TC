/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_MAIN                                                        *
; Funcao: MODULO PRINCIPAL DE CONTROLE									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */

  
char aux_tab;


void trata_menu4(void)
{
/* TRATA ALARMES */
	
	if (qmenu != 4)
		{
		qmenu = 4;
		menu_aux = 1;
		}
	else if (tecla_enter==1)
		{
	 	tecla_enter=0;
		exibiu = 0;
		if (programando == 1)
			{
			goto salvar_programa;
			}
		else
			{
			goto trata_menu4_enter;
			}
		}		
	else if (tecla_up==1)
		{
		exibiu = 0;
		tecla_up=0;
		 if (programando == 1)
		 	{
			if (tempo_senha != 255)
				{
				tempo_senha++;
				}
			goto trata_menu4_up;
		 	}
		 else
		 	{
			 if (menu_aux > 1)
			 	{
				 menu_aux--;
#if (portatil == true)
				if (menu_aux == 10)
					{
					 menu_aux--;
					}
				if (menu_aux == 9)
					{
					 menu_aux--;
					}
#endif
				}
			}
		}
	else if (tecla_down==1)
		{
		exibiu = 0;
		 tecla_down=0;
		 if (programando == 1)
		 	{
			if (tempo_senha != 255)
				{
				tempo_senha++;
				}
			goto trata_menu4_down;
		 	}
		 else
		 	{
			 if (menu_aux < nro_menus4)
			 	{
				 menu_aux++;
#if (portatil == true)
				if (menu_aux == 9)
					{
					 menu_aux++;
					}
				if (menu_aux == 10)
					{
					 menu_aux++;
					}
#endif
				}
			}
		}
	else if (tecla_reset==1)
		{
		tecla_reset = 0;
		if (programando == 1)
			{
			programando = 0;
			}
		else
			{
			inicializa_programa();
			valida_programa();
			encerra_menus();
			}
		return;
		}
	goto exibe_programa;


salvar_programa:
	salva_programa();
	
	valida_programa();

	if (menu_aux < nro_menus4)
		{
		menu_aux++;
		}
	exibiu = 0;
	
						
exibe_programa: 

	if (programando == 1)
		{
		exibir_menu = 1;
		}
	if (exibir_menu == 0)
		{
		return;
		}
	if (menu_aux < 5)
		{
		if (exibiu == 0)
			{
			if (programando == 0)
				{
				mensagem(1, 40);	
				mensagem(2, 41);	
				mensagem(3, 42);	
				mensagem(4, 43);
				}
			exibiu = 1;
			}
		switch(menu_aux)
			{
			case 1:
				{
				displayp(13,ten_nomi,3,0,'P');
				if (programando == 0)
					{
					displayp(28,valor_tc,4,0,0);
					displayp(45,valor_tp,3,0,0);
					displayd(60,set_point,0);	
					}
				break;
				}
			case 2:
				{
				displayp(28,valor_tc,4,0,'P');		// linha 2
				if (programando == 0)
					{
					displayp(13,ten_nomi,3,0,0);		// linha 1
					displayp(45,valor_tp,3,0,0);		// linha 3
					displayd(60,set_point,0);	
					}
				break;
				}
			case 3:
				{
				displayp(45,valor_tp,3,0,'P');		// linha 3
				if (programando == 0)
					{
					displayp(13,ten_nomi,3,0,0);		// linha 1
					displayp(28,valor_tc,4,0,0);		// linha 2
					displayd(60,set_point,0);	
					}
				break;
				}
			case 4:
				{
				if (programando == 0)
					{
					displayp(13,ten_nomi,3,0,0);
					displayp(28,valor_tc,4,0,0);
					displayp(45,valor_tp,3,0,0);
					}
				displayd(60,set_point,'P');	
				break;
				}
			}
		}
	else
		{
		if (exibiu == 0)
			{
			if (programando == 0)
				{
				mensagem(1, tabela_menu4[menu_aux-4]);	
				mensagem(2, tabela_menu4[menu_aux-3]);	
				mensagem(3, tabela_menu4[menu_aux-2]);	
				mensagem(4, tabela_menu4[menu_aux-1]);
				}
			exibiu = 1;
			}
		
		switch(menu_aux)
			{
			case 5:
				{
				if (programando == 0)
					{
					displayp(12,valor_tc,4,0,0);
					displayp(29,valor_tp,3,0,0);
					displayd(44,set_point,0);	
					}
				displayp(60,intervalo_reg,4,0,'P');
				break;
				}
			case 6:
				{
				if (programando == 0)
					{
					displayp(13,valor_tp,3,0,0);
					displayd(28,set_point,0);	
					displayp(44,intervalo_reg,4,0,0);
					}
				displayp(63,forma_reg_cht,1,0,'P');
				break;
				}
			case 7:
				{
				if (programando == 0)
					{
					displayd(12,set_point,0);	
					displayp(28,intervalo_reg,4,0,0);
					displayp(47,forma_reg_cht,1,0,0);
					}
				exibe_sim_nao(registro,61,'P');
				break;
				}
			case 8:
				{
				if (programando == 0)
					{
					displayp(12,intervalo_reg,4,0,0);
					displayp(31,forma_reg_cht,1,0,0);
					exibe_sim_nao(registro,45,0);
					}
				displayp(62,intervalo_integra,2,0,'P');
				break;
				}
			case 9:
				{
				if (programando == 0)
					{
					displayp(15,forma_reg_cht,1,0,0);
					exibe_sim_nao(registro,29,0);
					displayp(46,intervalo_integra,2,0,0);
					}
				displayp(59,baud_rate,5,0,'P');
				break;
				}
			case 10:
				{
				if (programando == 0)
					{
					exibe_sim_nao(registro,13,0);
					displayp(30,intervalo_integra,2,0,0);
					displayp(43,baud_rate,5,0,0);
					}
				displayp(61,endereco,3,0,'P');
				break;
				}
			case 11:
				{
				if (programando == 0)
					{
					displayp(14,intervalo_integra,2,0,0);
					displayp(27,baud_rate,5,0,0);
					displayp(45,endereco,3,0,0);
					}
				if (ala_fp_ind > 99 )
					{
					exibe_off(60);
					}
				else
					{
					displayd(60,ala_fp_ind,'P');	
					}
				break;
				}
			case 12:
				{
				if (programando == 0)
					{
					displayp(11,baud_rate,5,0,0);
					displayp(29,endereco,3,0,0);
					if (ala_fp_ind > 99 )
						{
						exibe_off(44);
						}
					else
						{
						displayd(44,ala_fp_ind,0);	
						}
					}
				if (ala_fp_cap > 99 )
					{
					exibe_off(60);
					}
				else
					{
					displayd(60,ala_fp_cap,'P');	
					}
				
				break;
				}
			case 13:
				{
				if (programando == 0)
					{
					displayp(13,endereco,3,0,0);
					if (ala_fp_ind > 99 )
						{
						exibe_off(28);
						}
					else
						{
						displayd(28,ala_fp_ind,0);	
						}
					if (ala_fp_cap > 99 )
						{
						exibe_off(44);
						}
					else
						{
						displayd(44,ala_fp_cap,0);	
						}
					}
				if (ala_ten_a == 0)
					{
					exibe_off(59);
					}
				else
					{
					displayp(60,ala_ten_a,3,0,'P');
					}
				break;
				}
			case 14:
				{
				if (programando == 0)
					{
					if (ala_fp_ind > 99 )
						{
						exibe_off(12);
						}
					else
						{
						displayd(12,ala_fp_ind,0);	
						}
					if (ala_fp_cap > 99 )
						{
						exibe_off(28);
						}
					else
						{
						displayd(28,ala_fp_cap,0);	
						}
					if (ala_ten_a == 0)
						{
						exibe_off(43);
						}
					else
						{
						displayp(44,ala_ten_a,3,0,0);
						}
					}
				if (ala_ten_b == 0)
					{
					exibe_off(59);
					}
				else
					{
					displayp(60,ala_ten_b,3,0,'P');
					}
				break;
				}
			case 15:
				{
				if (programando == 0)
					{
					if (ala_fp_cap > 99 )
						{
						exibe_off(12);
						}
					else
						{
						displayd(12,ala_fp_cap,0);	
						}
					if (ala_ten_a == 0)
						{
						exibe_off(27);
						}
					else
						{
						displayp(28,ala_ten_a,3,0,0);
						}
					if (ala_ten_b == 0)
						{
						exibe_off(43);
						}
					else
						{
						displayp(45,ala_ten_b,3,0,0);
						}
					}
				if (ala_sc == 0)
					{
					exibe_off(59);
					}
				else
					{
					displayp(60,ala_sc,3,0,'P');
					}
				break;
				}
			case 16:
				{
				if (programando == 0)
					{
					if (ala_ten_a == 0)
						{
						exibe_off(11);
						}
					else
						{
						displayp(12,ala_ten_a,3,0,0);
						}
					if (ala_ten_b == 0)
						{
						exibe_off(27);
						}
					else
						{
						displayp(28,ala_ten_b,3,0,0);
						}
					if (ala_sc == 0)
						{
						exibe_off(43);
						}
					else
						{
						displayp(44,ala_sc,3,0,0);
						}
					}
				if (ala_chtt == 0)
					{
					exibe_off(59);
					}
				else
					{
					displayp(60,ala_chtt,3,0,'P');
					}
				break;
				}
			case 17:
				{
				if (programando == 0)
					{
					if (ala_ten_b == 0)
						{
						exibe_off(11);
						}
					else
						{
						displayp(12,ala_ten_b,3,0,0);
						}
					if (ala_sc == 0)
						{
						exibe_off(27);
						}
					else
						{
						displayp(28,ala_sc,3,0,0);
						}
					if (ala_chtt == 0)
						{
						exibe_off(43);
						}
					else
						{
						displayp(44,ala_chtt,3,0,0);
						}
					}
				if (ala_chtc == 0)
					{
					exibe_off(59);
					}
				else
					{
					displayp(60,ala_chtc,3,0,'P');
					}
				break;
				}
			case 18:
				{
				if (programando == 0)
					{
					if (ala_sc == 0)
						{
						exibe_off(11);
						}
					else
						{
						displayp(12,ala_sc,3,0,0);
						}
					if (ala_chtt == 0)
						{
						exibe_off(27);
						}
					else
						{
						displayp(28,ala_chtt,3,0,0);
						}
					if (ala_chtc == 0)
						{
						exibe_off(43);
						}
					else
						{
						displayp(44,ala_chtc,3,0,0);
						}
					}
				lcd_gotoxy(63-48, 4);
				if (tipo_ligacao == 0)
					{
					if (programando == 1)
						{
						if (piscar == 1)
							{
							display(' ');
							}
						else
							{
							display('Y');
							}
						}
					else
						{
						display('Y');
						}
					}
				else
					{
					if (programando == 1)
						{
						if (piscar == 1)
							{
							display(' ');
							}
						else
							{
							display('D');
							}
						}
					else
						{
						display('D');
						}
					}
				
				break;
				}
			case 19:
				{
				if (programando == 0)
					{
					if (ala_chtt == 0)
						{
						exibe_off(11);
						}
					else
						{
						displayp(12,ala_chtt,3,0,0);
						}
					if (ala_chtc == 0)
						{
						exibe_off(27);
						}
					else
						{
						displayp(28,ala_chtc,3,0,0);
						}
					}
				lcd_gotoxy(15, 3);
				if (tipo_ligacao == 0)
					{
					display('Y');
					}
				else
					{
					display('D');
					}
				if (programando == 0)
					{
					if (idioma == 1)
						{
						mensagem(4,93);
						}
					else
						{
						mensagem(4,92);
						}
					}
				else
					{
					if (piscar == 1)
						{
						mensagem(4,94);
						}
					else
						{
						if (idioma == 1)
							{
							mensagem(4,93);
							}
						else
							{
							mensagem(4,92);
							}
						}
					}
				break;
				}
#if (funcao_505 == true)
			case 20:
				{
				if (programando == 0)
					{
					if (ala_chtc == 0)
						{
						exibe_off(11);
						}
					else
						{
						displayp(12,ala_chtc,3,0,0);
						}
					}

				lcd_gotoxy(15, 2);
				if (tipo_ligacao == 0)
					{
					display('Y');
					}
				else
					{
					display('D');
					}
				if (programando == 0)
					{
					if (idioma == 1)
						{
						mensagem(3,93);
						}
					else
						{
						mensagem(3,92);
						}
					}
				lcd_gotoxy(15, 4);
				if (modo_funca == 1)
					{
					if (programando == 1)
						{
						if (piscar == 1)
							{
							display(' ');
							}
						else
							{
							display('1');
							}
						}
					else
						{
						display('1');
						}
					}
				else
					{
					if (programando == 1)
						{
						if (piscar == 1)
							{
							display(' ');
							}
						else
							{
							display('2');
							}
						}
					else
						{
						display('2');
						}
					}
				break;
				}
#else
			case 20:
#endif
			case 21:
				{
				if (programando == 0)
					{
					lcd_gotoxy(15, 1);
					if (tipo_ligacao == 0)
						{
						display('Y');
						}
					else
						{
						display('D');
						}
					if (idioma == 1)
						{
						mensagem(2,93);
						}
					else
						{
						mensagem(2,92);
						}
					lcd_gotoxy(15, 3);
					if (modo_funca == 1)
						{
						display('1');
						}
					else
						{
						display('2');
						}
					}
				displayp(62, hora_ponta,2,0,'P');
				break;
				}
			case 22:
				{
				if (programando == 0)
					{
					if (idioma == 1)
						{
						mensagem(1,93);
						}
					else
						{
						mensagem(1,92);
						}
					lcd_gotoxy(15, 2);
					if (modo_funca == 1)
						{
						display('1');
						}
					else
						{
						display('2');
						}
					displayp(46, hora_ponta,2,0,0);
					}
				displayp(62, hora_fora_ponta,2,0,'P');
				break;
				}

			default:
				{
				menu_aux = nro_menus4;
				}
			}	
		}
	exibe_colchete();
		
	exibir_menu = 0;
	return;


trata_menu4_enter:
	programando = 1;
 	switch(menu_aux)
 		{
	 	case 1:
	 		{
			aux_tab = 0;
	 		for (aux_b1 = 0; aux_b1 < NRO_POSI_TEN ;aux_b1++)
	 			{
				if (ten_nomi == tabela_ten[aux_b1])
					{
					aux_tab = aux_b1;
					break;
					}
				}
			break;
			}
		case 2:
			{
			aux_tab = 0;
			for (aux_b1 = 0; aux_b1 < (NRO_POSI_TC-1) ;aux_b1++)
				{
				if (valor_tc == tabela_tc[aux_b1])
					{
					aux_tab = aux_b1;
					break;
					}
				}
			break;
			}
		case 5:
			{
			aux_tab = 0;
			for (aux_b1 = 0; aux_b1 < NRO_POSI_INTERVALO ;aux_b1++)
 				{
 				if (intervalo_reg == tabela_intervalo_reg[aux_b1])
 					{
					aux_tab = aux_b1;
					break;
					}
				}
			break;
			}
		default:
			{
			aux_tab = 1;
			}
		}
	goto exibe_programa;	


trata_menu4_down:
	switch(menu_aux)
		{
		case 1:
			{
			if (aux_tab > 0)
				{
				aux_tab--;
				}
			ten_nomi = tabela_ten[aux_tab];
			break;
			}
		case 2:
			{
			if (aux_tab > 0)
				{
				aux_tab--;
				}
			valor_tc = tabela_tc[aux_tab];
			break;
			}
		case 3:
			{
			if (valor_tp > 1)
				{
				valor_tp--;
				}
			break;
			}
		case 4:
			{
			if (set_point > 90)
				{
				set_point--;
				}
			break;
			}
		case 5:
			{
			if (aux_tab > 0)
				{
				aux_tab--;
				if (registro == 1)
					{
#if com_regs	true
					grava_registros( reg_final);
					registro = 0;
#endif					
					}
				}
			intervalo_reg = tabela_intervalo_reg[aux_tab];
			break;
			}			
		
		case 6:
			{
			if (forma_reg_cht > 0)
				{
				forma_reg_cht--;
				}
			break;
			}
		case 7:
			{
			if (registro == 1)
				{
#if com_regs	true
				grava_registros(reg_final);
				registro = 0;
#endif					
				}
			else
				{
				registro = 1;
				write_byte(ee_registro, registro);
#if com_regs	true
					grava_registros(reg_inicio);

#endif					
				}	
			break;
			}
		case 8:
			{
			if (intervalo_integra > 2)
				{
				intervalo_integra--;
				}
			break;
			}
		case 9:
			{
			if (aux_tab > 0)
				{
				aux_tab--;
				}	
			baud_rate= tabela_baud[aux_tab];
			break;
			}
		case 10:
			{
			if (endereco > 2)
				{
				endereco--;
				}
			break;	
			}
		case 11:
			{
			if (ala_fp_ind > 81)
				{
				ala_fp_ind--;
				}
			break;	
			}
		case 12:
			{
			if (ala_fp_cap > 81)
				{
				ala_fp_cap--;
				}
			break;	
			}
		case 13:
			{
			if (ala_ten_a > 0)
				{
				ala_ten_a--;
				}
			break;	
			}
		case 14:
			{
			if (ala_ten_b > 0)
				{
				ala_ten_b--;
				}
			break;	
			}
		case 15:
			{
			if (ala_sc > 0)
				{
				ala_sc--;
				}
			break;	
			}
		case 16:
			{
			if (ala_chtt > 0)
				{
				ala_chtt--;
				}
			break;	
			}
		case 17:
			{
			if (ala_chtc > 0)
				{
				ala_chtc--;
				}
			break;	
			}
		case 18:
			{
			if (tipo_ligacao == 0)
				{
				tipo_ligacao = 1;
				}
			else
				{
				tipo_ligacao = 0;
				}
			break;	
			}
		case 19:
			{
			if (idioma == 0)
				{
				idioma = 1;
				}
			else
				{
				idioma = 0;
				}
			break;	
			}
#if (funcao_505 == true)
		case 20:
			{
			if (modo_funca == 1)
				{
				modo_funca = 2;
				}
			else
				{
				modo_funca = 1;
				}
			break;	
			}
#else
		case 20:
#endif
		case 21:
			{
			if (hora_ponta > 0)
				{
				hora_ponta--;
				}
			break;	
			}
		case 22:
			{
			if (hora_fora_ponta > (hora_ponta + 1))
				{
				hora_fora_ponta--;
				}
			break;	
			}

		}	
	goto exibe_programa;

trata_menu4_up:
	switch(menu_aux)
		{
		case 1:
			{
			if (aux_tab < NRO_POSI_TEN)
				{
				aux_tab++;
				}
			ten_nomi = tabela_ten[aux_tab];
			break;
			}
		case 2:
			{
			if (aux_tab < (NRO_POSI_TC-1))
				{
				aux_tab++;
				}
			valor_tc = tabela_tc[aux_tab];
			break;
			}
		case 3:
			{
			if (valor_tp < 500)
				{
				valor_tp++;
				}
			break;
			}
		case 4:
			{
			if (set_point < 99)
				{
				set_point++;
				}
			break;
			}
		case 5:
			{
			if (aux_tab < NRO_POSI_INTERVALO)
				{
				aux_tab++;
				if (registro == 1)
					{
#if com_regs	true
					grava_registros(reg_final);
					registro = 0;
#endif					
					}
				}
			intervalo_reg = tabela_intervalo_reg[aux_tab];
			break;
			}			
		case 6:
			{
			if (forma_reg_cht < 3)
				{
				forma_reg_cht++;
				}
			break;
			}
		case 7:
			{
			if (registro == 1)
				{
#if com_regs	true
				grava_registros(reg_final);
				registro = 0;
#endif					
				}
			else
				{
				registro = 1;
				write_byte(ee_registro, registro);
#if com_regs	true
				grava_registros(reg_inicio);
#endif					
				}	
			break;
			}
		case 8:
			{
			if (intervalo_integra < 60)
				{
				intervalo_integra++;
				}
			break;
			}
		case 9:
			{
			if (aux_tab < (NRO_POSI_BAUD - 1))
				{
				aux_tab++;
				}	
			baud_rate = tabela_baud[aux_tab];
			break;
			}
		case 10:
			{
			if (endereco < 247)
				{
				endereco++;
				}
			break;	
			}
		case 11:
			{
			if (ala_fp_ind < 100)
				{
				ala_fp_ind++;
				}
			break;	
			}
		case 12:
			{
			if (ala_fp_cap < 100)
				{
				ala_fp_cap++;
				}
			break;	
			}
		case 13:
			{
			if (ala_ten_a < 20)
				{
				ala_ten_a++;
				}
			break;	
			}
		case 14:
			{
			if (ala_ten_b < 20)
				{
				ala_ten_b++;
				}
			break;	
			}
		case 15:
			{
			if (ala_sc < 150)
				{
				ala_sc++;
				}
			break;	
			}
		case 16:
			{
			if (ala_chtt < 50)
				{
				ala_chtt++;
				}
			break;	
			}
		case 17:
			{
			if (ala_chtc < 50)
				{
				ala_chtc++;
				}
			break;	
			}
		case 18:
			{
			if (tipo_ligacao == 0)
				{
				tipo_ligacao = 1;
				}
			else
				{
				tipo_ligacao = 0;
				}
			break;	
			}
		case 19:
			{
			if (idioma == 0)
				{
				idioma = 1;
				}
			else
				{
				idioma = 0;
				}
			break;	
			}
#if (funcao_505 == true)
		case 20:
			{
			if (modo_funca == 1)
				{
				modo_funca = 2;
				}
			else
				{
				modo_funca = 1;
				}
			break;	
			}
#else
		case 20:
#endif
		case 21:
			{
			if (hora_ponta < (hora_fora_ponta -1))
				{
				hora_ponta++;
				}
			break;	
			}
		case 22:
			{
			if ((hora_fora_ponta < 23) && (hora_fora_ponta > hora_ponta))
				{
				hora_fora_ponta++;
				}
			break;	
			}

		}	
goto exibe_programa;
}

