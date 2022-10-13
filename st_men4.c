/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÿÔNICOS                                  *
; Modulo: ST_MAIN                                                        *
; Funcao: MODULO PRINCIPAL DE CONTROLE									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */

char aux_tab;
char aux_tipo_ponteira;
void exibe_programa(void);
void salvar_programa(void);
void trata_menu4_enter(void);
void trata_menu4_up(void);
void trata_menu4_down(void);
void trata_menu4_reset(void);
#if (se_com_flex == true)
	void selecao_ponteira(void);
#endif

void trata_menu4(void)
{
	if (qmenu != 4)
		{
		qmenu = 4;
		menu_aux = 2;
		#if (sazi == true)
			menu_aux = 3;
		#endif		
		escolha_ponteira = 0;
		#if (se_com_flex == true)
			aux_tipo_ponteira = tipo_ponteira;
		#endif
		}
	#if (se_com_flex == true)
		else if (escolha_ponteira == true)
			{
			exibiu = 0;
			selecao_ponteira();
			return;
			}
	#endif
	else if (tecla_enter==1)
		{
	 	tecla_enter = 0;
		exibiu = 0;
		if (programando == 1)
			{
			salvar_programa();
			}
		else
			{
			trata_menu4_enter();
			}
		}		
	else if (tecla_up==1)
		{
		exibiu = 0;
		tecla_up = 0;
		 if (programando == 1)
		 	{
			if (tempo_senha != 255)
				{
				tempo_senha++;
				}
			trata_menu4_up();
		 	}
		 else
		 	{
			 if (menu_aux > 2)
			 	{
				 menu_aux--;
				 #if (sazi == true)
				 	if (menu_aux == 2)
				 		{
						 menu_aux = 3;
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
			trata_menu4_down();
		 	}
		else
			{
			if (menu_aux < nro_menus4)
				{
				menu_aux++;
				 #if (sazi == true)
				 	if (menu_aux == 2)
				 		{
						 menu_aux++ ;
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
			escolha_ponteira = false;
			}
		else
			{
			inicializa_programa();
			valida_programa();
			encerra_menus();
			}
		return;
		}
	exibe_programa();
}

void trata_menu4_enter(void)
{
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
			#if (se_com_flex == true)
				if (escolha_ponteira == false)
					{
					escolha_ponteira = true;
					programando = 0;
					exibiu = 0;
					selecao_ponteira();
					}
			#else
				programando = 1;
				aux_tab = 0;
				for (aux_b1 = 0; aux_b1 < (NRO_POSI_TC-1) ;aux_b1++)
					{
					if (valor_tc == tabela_tc[aux_b1])
						{
						aux_tab = aux_b1;
						break;
						}
					}
			#endif
			break;
			}
		default:
			{
			programando = 1;
			aux_tab = 1;
			}
		}
	exibe_programa();	
}


void trata_menu4_down(void)
{
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
			#if (se_com_flex == true)
			#else
				if (aux_tab > 0)
					{
					aux_tab--;
					}
				valor_tc = tabela_tc[aux_tab];
			#endif
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
		case 6:
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
			case 7:
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
			case 7:
		#endif
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
			if (ala_fp_ind > 81)
				{
				ala_fp_ind--;
				}
			break;	
			}
		case 10:
			{
			if (ala_fp_cap > 81)
				{
				ala_fp_cap--;
				}
			break;	
			}
		case 11:
			{
			if (ala_ten_a > 0)
				{
				ala_ten_a--;
				}
			break;	
			}
		case 12:
			{
			if (ala_ten_b > 0)
				{
				ala_ten_b--;
				}
			break;	
			}
		case 13:
			{
			if (ala_sc > 0)
				{
				ala_sc--;
				}
			break;	
			}
		case 14:
			{
			if (ala_chtt > 0)
				{
				ala_chtt--;
				}
			break;	
			}
		case 15:
			{
			if (ala_chtc > 0)
				{
				ala_chtc--;
				}
			break;	
			}
		case 16:
			{
			if (hora_ponta > 0)
				{
				hora_ponta--;
				}
			break;	
			}
		case 17:
			{
			if (hora_final_ponta > (hora_ponta + 1))
				{
				hora_final_ponta--;
				}
			break;	
			}
		}	
	exibe_programa();
}

void trata_menu4_up(void)
{
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
			#if (se_com_flex == true)
			#else
				if (aux_tab < (NRO_POSI_TC-1))
					{
					aux_tab++;
					}
				valor_tc = tabela_tc[aux_tab];
			#endif
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
		case 6:
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
			case 7:
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
			case 7:
		#endif
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
			if (ala_fp_ind < 100)
				{
				ala_fp_ind++;
				}
			break;	
			}
		case 10:
			{
			if (ala_fp_cap < 100)
				{
				ala_fp_cap++;
				}
			break;	
			}
		case 11:
			{
			if (ala_ten_a < 20)
				{
				ala_ten_a++;
				}
			break;	
			}
		case 12:
			{
			if (ala_ten_b < 20)
				{
				ala_ten_b++;
				}
			break;	
			}
		case 13:
			{
			if (ala_sc < 150)
				{
				ala_sc++;
				}
			break;	
			}
		case 14:
			{
			if (ala_chtt < 50)
				{
				ala_chtt++;
				}
			break;	
			}
		case 15:
			{
			if (ala_chtc < 50)
				{
				ala_chtc++;
				}
			break;	
			}
		case 16:
			{
			if (hora_ponta < (hora_final_ponta -1))
				{
				hora_ponta++;
				}
			break;	
			}
		case 17:
			{
			if ((hora_final_ponta < 23) && (hora_final_ponta > hora_ponta))
				{
				hora_final_ponta++;
				}
			break;	
			}
		}	
	exibe_programa();
}


void salvar_programa(void)
{
	salva_programa();
	valida_programa();
	if (menu_aux < nro_menus4)
		{
		menu_aux++;
		}
	exibiu = 0;
}

void exibe_programa(void)
{
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
				#if (se_com_flex == true)
//					mensagem(2, 108);
					mensagem(2,tab_modelo_pt[aux_tipo_ponteira]);
				#else
					mensagem(2, 41);
				#endif
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
					#if (se_com_flex == true)
//						mensagem(2,108);
						mensagem(2,tab_modelo_pt[aux_tipo_ponteira]);
					#else
						displayp(28,valor_tc,4,0,0);
					#endif
					displayp(45,valor_tp,3,0,0);
					displayd(60,set_point,0);	
					}
				break;
				}
			case 2:
				{
				#if (se_com_flex == true)
//					mensagem(2,108);
					mensagem(2,tab_modelo_pt[aux_tipo_ponteira]);
				#else
					displayp(28,valor_tc,4,0,'P');		// linha 2
				#endif
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
					#if (se_com_flex == true)
//						mensagem(2,108);
						mensagem(2,tab_modelo_pt[aux_tipo_ponteira]);
					#else
						displayp(28,valor_tc,4,0,0);		// linha 2
					#endif
					displayd(60,set_point,0);	
					}
				break;
				}
			case 4:
				{
				if (programando == 0)
					{
					displayp(13,ten_nomi,3,0,0);
					#if (se_com_flex == true)
//						mensagem(2,108);
						mensagem(2,tab_modelo_pt[aux_tipo_ponteira]);
					#else
						displayp(28,valor_tc,4,0,0);
					#endif
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
					#if (se_com_flex == true)
//						mensagem(1,108);
						mensagem(1,tab_modelo_pt[aux_tipo_ponteira]);
					#else
						displayp(12,valor_tc,4,0,0);
					#endif
					displayp(29,valor_tp,3,0,0);
					displayd(44,set_point,0);	
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
			case 6:
				{
				if (programando == 0)
					{
					displayp(13,valor_tp,3,0,0);
					displayd(28,set_point,0);	
					lcd_gotoxy(15, 3);
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
				case 7:
					{
					if (programando == 0)
						{
						displayd(12,set_point,0);	
						lcd_gotoxy(15, 2);
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
				case 7:
			#endif
			case 8:
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
				displayp(62,intervalo_integra,2,0,'P');
				break;
				}
			case 9:
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
					displayp(46,intervalo_integra,2,0,0);
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
			case 10:
				{
				if (programando == 0)
					{
					lcd_gotoxy(15, 1);
					if (modo_funca == 1)
						{
						display('1');
						}
					else
						{
						display('2');
						}
					displayp(30,intervalo_integra,2,0,0);
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
			case 11:
				{
				if (programando == 0)
					{
					displayp(14,intervalo_integra,2,0,0);
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
			case 12:
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
			case 13:
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
			case 14:
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
			case 15:
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
			case 16:
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
				displayp(62, hora_ponta,2,0,'P');
				break;
				}
			case 17:
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
					displayp(46, hora_ponta,2,0,0);
					}
				displayp(62, hora_final_ponta,2,0,'P');
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
}
#if (se_com_flex == true)
	void selecao_ponteira(void)
	{
		if (exibiu == 0)
			{
			exibiu = 1;
			if (programando == 1)
				{
				if (piscar == 1)
					{
					mensagem(4,0);
					}
				else
					{
					mensagem(4,tab_modelo_pt[aux_tipo_ponteira]);
					}
				}
			else
				{
				mensagem(1,109);
				mensagem(2,110);
				mensagem(3,0);
				mensagem(4,tab_modelo_pt[aux_tipo_ponteira]);
				}
			}
			
		if (tecla_enter == 1)
			{
			tecla_enter = 0;
			exibiu = 0;
			if (programando == 0)
				{
				programando = 1;
				}
			else
				{
				programando = 0;
				escolha_ponteira = 0;
				tipo_ponteira = aux_tipo_ponteira;
				valor_tc = tabela_pt[tipo_ponteira];
				recarrega_ponteira = true;
				salva_programa();
				exibe_programa();
				}
			}
		else if (tecla_up == 1)
			{
			tecla_up = 0;
			exibiu = 0;
			if (programando == 1)
				{
				if (aux_tipo_ponteira > 0)
					{
					aux_tipo_ponteira--;
					#if (versao_pci_st96 >= 6)
						time_out_troca_ponteira = 10;
					#endif
					}
				}
			}
		else if (tecla_down == 1)
			{
			tecla_down = 0;
			exibiu = 0;
			if (programando == 1)
				{
//				if (aux_tipo_ponteira < NRO_POSI_TABELA_TIPO_PT - 2)
				if (aux_tipo_ponteira < NRO_DE_PONTEIRAS)
					{
					aux_tipo_ponteira++;
					#if (versao_pci_st96 >= 6)
						time_out_troca_ponteira = 10;
					#endif
					}
				}
			}
		else if (tecla_reset == 1)
			{
			tecla_reset = 0;
			if (programando == 1)
				{
				programando = 0;
				}
			else
				{
				exibiu = 0;
				escolha_ponteira = 0;
				exibe_programa();
				}
			}
	}
#endif
