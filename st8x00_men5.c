/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST8610_MEN5                                                    *
; Funcao: TRATAMENTO DO MENU DE PROGRAMAÇÃO DE BANCOS					 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/
  
short primeira;
short topo_menu;


void monta_tabela_bancos(char qsequencia)
{
	char x;
	if (qsequencia != 0)
		{
		if (nro_bancos_capacitor == 2)
			{
			tabela_valor_bancos[1]= tabela_valor_bancos[0] * TAB_2_BANCOS[(qsequencia-1)][1];
			}
		else if (nro_bancos_capacitor == 3)
			{
			for (x = 1 ;x < 3; x++)
				{
				tabela_valor_bancos[x]= tabela_valor_bancos[0] * TAB_3_BANCOS[(qsequencia-1)][x];
				}
			}
		else if (nro_bancos_capacitor == 4)
			{
			for (x = 1 ;x < 4; x++)
				{
				tabela_valor_bancos[x]= tabela_valor_bancos[0] * TAB_4_BANCOS[(qsequencia-1)][x];
				}
			}
		else if (nro_bancos_capacitor == 5)
			{
			for (x = 1 ;x < 5; x++)
				{
				tabela_valor_bancos[x]= tabela_valor_bancos[0] * TAB_5_BANCOS[(qsequencia-1)][x];
				}
			}
		else if (nro_bancos_capacitor >= 6)
			{
			for (x = 1 ;x < 6; x++)
				{
				tabela_valor_bancos[x]= tabela_valor_bancos[0] * TAB_6_BANCOS[(qsequencia-1)][x];
				}
			for (x = 6 ;x < NRO_MAXIMO_BANCOS_CAPACITOR; x++)
				{
				tabela_valor_bancos[x]= tabela_valor_bancos[5];
				}
			}
		for (x = 0 ;x < NRO_MAXIMO_BANCOS_CAPACITOR; x++)
			{
			if (tabela_valor_bancos[x] > MAIOR_BANCO_POSSIVEL)
				{
				tabela_valor_bancos[x] = MAIOR_BANCO_POSSIVEL;
				}
			}
		}
	else
		{
		for (x = 0 ;x < nro_bancos_capacitor; x++)
			{
			if (tabela_valor_bancos[x] == 0)
				{
				tabela_valor_bancos[x] = 5;
				}
			}
		}
}

void gera_sequencia_valor_bancos(void)
{				
	char x;
	if (sequencia != 0)
		{
		tabela_valor_bancos[0] = banco_capacitor[0];
		monta_tabela_bancos(sequencia);
		for (x = 1; x < nro_bancos_capacitor; x++)
			{
			banco_capacitor[x] = tabela_valor_bancos[x];
			}
		}
}		

void exibe_programa_bancos(void)
{
	char x;
	if (menu_aux == 0)
		{
		menu_aux = 1;
		}

	#if (ST8100C == true)
		led_v = 0;
		led_a = 0;
		led_r = 0;
		led_w = 0;
		
		switch(menu_aux)
			{
			case 1:
			case 4:		// corrente minima
			case 5:		// Tempo Acionamento
			case 6:		// Tempo Desaciona
				{
				if (ja_rolou == true)
					{
					print_display(1,tabela_programa[menu_aux],0,1);
					rolando = false;
					}
				else
					{
					if (rolando == false)
						{
						mensagem_rola(tabela_menu_bancos[menu_aux], 1);
						}
					}
				break;
				}
			case 7:		//Seqüência de Acionamento
				{
				if (sel_sequencia == 0)
					{
					if (ja_rolou == true)
						{
						if (tabela_programa[7] == 0)
							{
							buf_display[0] = tabela_caracteres[MU];
							buf_display[1] = tabela_caracteres[MS];
							buf_display[2] = tabela_caracteres[MU];
							buf_display[3] = tabela_caracteres[MA];
							}
						else
							{
							binasc2(tabela_programa[7]);
							buf_display[0] = tabela_caracteres[MESPACO];
							buf_display[1] = tabela_caracteres[MESPACO];
							buf_display[2] = tabela_caracteres[buf_tmp[3] - '0'];
							buf_display[3] = tabela_caracteres[buf_tmp[4] - '0'];
							}
						}
					else
						{
						if (rolando == false)
							{
							mensagem_rola(19,1);	//exibe palavra "SEQUENCIA"
							}
						}
					}
				else
					{
					if (aux_tab == 1)		//opção usuario na seleção da sequencia
						{
						buf_display[0] = tabela_caracteres[MU];
						buf_display[1] = tabela_caracteres[MS];
						buf_display[2] = tabela_caracteres[MU];
						buf_display[3] = tabela_caracteres[MA];
						}
					else
						{
						if (sel_seq_tab == 1)		//opção de entrada para tabela de sequencia
							{
							binasc2(tabela_programa[7]);
							buf_display[0] = tabela_caracteres[MESPACO];
							buf_display[1] = tabela_caracteres[MESPACO];
							buf_display[2] = tabela_caracteres[buf_tmp[3] - '0'];
							buf_display[3] = tabela_caracteres[buf_tmp[4] - '0'];
							}
						else
							{
							buf_display[0] = tabela_caracteres[MT];
							buf_display[1] = tabela_caracteres[MA];
							buf_display[2] = tabela_caracteres[MB];
							buf_display[3] = tabela_caracteres[ME];
							}
						}
					}
				break;
				}
			case 2:
				{
				if (ja_rolou == true)
					{
					if (tabela_programa[2] == 0)
						{
						buf_display[0] = tabela_caracteres[MESPACO];
						buf_display[1] = tabela_caracteres[MS];
						buf_display[2] = tabela_caracteres[ME];
						buf_display[3] = tabela_caracteres[MM];
						rolando = false;
						}
					else
						{
						display_xxx_x(1,tabela_programa[2],1);	
						rolando = false;
						}
					}
				else
					{
					if (rolando == false)
						{
						mensagem_rola(tabela_menu_bancos[2],1);
						}
					}
				break;
				}
			case 3:
				{
				if (ja_rolou == true)
					{
					display_xxx_x(1,tabela_programa[3],1);	
					rolando = false;
					}
				else
					{
					if (rolando == false)
						{
						mensagem_rola(tabela_menu_bancos[3], 1);
						}
					}
				break;
				}
			case 8:
				{
				if (topo_menu == true)
					{
					if (rolando == false)
						{
						mensagem_rola(30,1);
						}
					if (ja_rolou == true)
						{
						topo_menu = false;
						}
					}
				else
					{
					if (primeira == false)
						{
						if (time_out2 == 0)
							{
							display_xxx_x(1,tabela_valor_bancos[aux_tab],1);
							}
						}
					else
						{
						mensagem(aux_tab + 1, 4);
						primeira = false;
						}
					}
				break;
				}
			case 9:
				{
				if (topo_menu == true)
					{
					if (rolando == false)
						{
						mensagem_rola(17,1);
						}
					if (ja_rolou == true)
						{
						topo_menu = false;
						}
					}
				else
					{
					if (primeira == false)
						{
						if (time_out2 == 0)
							{
							display_xxx_x(1,tabela_tempo_repouso[aux_tab],0);
							}
						}
					else
						{
						mensagem(aux_tab + 1, 3);
						primeira = false;
						}
					}
				break;
				}
	
			default:
				{
				menu_aux = 1;
				}
			}
		pisca_pontos();
		
	#else
		switch (menu_aux)
			{
			case 1:		//Número de Bancos
				{
				if (exibiu == 0)
					{
					mensagem (2,14);
					exibiu = 1;
					}
				displayp (31,tabela_programa[1],2,0,'P');
				break;
				}
			case 2:		//Máximo Acionamento
				{
				if (exibiu == 0)
					{
					mensagem (2,16);
					exibiu = 1;
					}
				if (programando == 1)
					{
					if (tabela_programa[2] == 0)
						{
						mensagem (2,51);
						}
					else
						{
						if (piscar == 1)
							{
							lcd_gotoxy(7,2);
							wr_lcd(1,' ');
							wr_lcd(1,' ');
							wr_lcd(1,' ');
							wr_lcd(1,' ');
							wr_lcd(1,' ');
							}
						else
							{
							displayp (23,tabela_programa[2],3,1,1);
							}
						}
					}
				else
					{
					if (tabela_programa[2] == 0)
						{
						mensagem (2,51);
						}
					else
						{
						displayp (23,tabela_programa[2],3,1,1);
						}
					}
				break;
				}
			case 3:		//Banco Mínimo
				{
				if (exibiu == 0)
					{
					mensagem (2,17);
					exibiu = 1;
					}
				if (programando == 1)
					{
					if (piscar == 1)
						{
						lcd_gotoxy(7,2);
						wr_lcd(1,' ');
						wr_lcd(1,' ');
						wr_lcd(1,' ');
						wr_lcd(1,' ');
						wr_lcd(1,' ');
						}
					else
						{
						if (tabela_programa[3] == 0)
							{
							exibe_off(29);
							}
						else
							{
							displayp (23,tabela_programa[3],3,1,1);
							}
						}
					}
				else
					{
					if (tabela_programa[3] == 0)
						{
						exibe_off(29);
						}
					else
						{
						displayp (23,tabela_programa[3],3,1,1);
						}
					}
				break;
				}
			case 4:		//Corrente Mínima
				{
				if (exibiu == 0)
					{
					mensagem (2,21);
					exibiu = 1;
					}
				#if (com_rep == true)
					if (modo_rep == true)
						{
						displayp (28,tabela_programa[4],4,0,'P');
						wr_lcd(1,'A');
						}
					else
						{
						displayp (29,tabela_programa[4],3,0,'P');
						}
				#else
					displayp (29,tabela_programa[4],3,0,'P');
				#endif
				break;
				}
			case 5:		//Tempo de Acionamento
				{
				if (exibiu == 0)
					{
					mensagem (2,18);
					exibiu = 1;
					}
					displayp (29,tabela_programa[5],3,0,'P');
				break;
				}
			case 6:		//Tempo Desaciona
				{
				if (exibiu == 0)
					{
					mensagem (2,137);
					exibiu = 1;
					}
					displayp (29,tabela_programa[6],3,0,'P');
				break;
				}
			case 7:		//Seqüência de Acionamento
				{
				if (sel_sequencia == 0)
					{
					exibe_sequencia();
					}
				else
					{
					if (aux_tab == 1)
						{
						mensagem (2,15);					// exibe seq usuario
						}
					else
						{
						if (sel_seq_tab == 0)
							{
							mensagem(2,128);				// exibe mensagem de entrada para tabela
							}
						else
							{
							exibe_sequencia();
							}
						}
					}
				break;
				}
			case 8:		//Valor de Cada Banco
				{
				if (exibiu == 0)
					{
					mensagem (2,19);
					exibiu = 1;
					}
				if (programando == 1)
					{
					if (piscar == 1)
						{
						lcd_gotoxy(6,2);
						wr_lcd(1,' ');
						wr_lcd(1,' ');
						wr_lcd(1,' ');
						wr_lcd(1,' ');
						wr_lcd(1,' ');
						}
					else
						{
						displayp (22,tabela_valor_bancos[aux_tab],3,1,1);
						}
					}
				else
					{
					displayp (22,tabela_valor_bancos[aux_tab],3,1,1);
					}
				displayp (18,aux_tab + 1,2,0,0);
				break;
				}
			case 9:		//Tempo de Repouso de Cada Banco
				{
				if (exibiu == 0)
					{
					mensagem (2,20);
					exibiu = 1;
					}
				if (programando == 1)
					{
					if (piscar == 1)
						{
						lcd_gotoxy(13,2);
						wr_lcd(1,' ');
						wr_lcd(1,' ');
						wr_lcd(1,' ');
						}
					else
						{
						displayp (29,tabela_tempo_repouso[aux_tab],3,0,0);
						}
					}
				else
					{
					displayp (29,tabela_tempo_repouso[aux_tab],3,0,0);
					}
				displayp (24,aux_tab + 1,2,0,0);
				break;
				}
			default:
				{
				menu_aux = 1;
				}
			}
	#endif
}



void salva_programa_bancos(void)
{
	char x;
	nro_bancos_capacitor = tabela_programa[1];
	max_kvar = tabela_programa[2];
	min_kvar = tabela_programa[3];
	#if (com_rep == true)
		if (modo_rep == true)
			{
			cor_minima_rep = tabela_programa[4];
			}
		else
			{
			cor_minima = tabela_programa[4];
			}
	#else
		cor_minima = tabela_programa[4];
	#endif
	tempo_aciona = tabela_programa[5];
	tempo_desaciona = tabela_programa[6];
	sequencia =	tabela_programa[7];
	if (nro_bancos_capacitor != aux_nro_bancos_capacitor)
		{
		for (aux_b1 = 0; aux_b1 < nro_bancos_capacitor; aux_b1++)
			{
			if (sequencia == 0)
				{
				if (tabela_valor_bancos[aux_b1] == 0)
					{
					tabela_valor_bancos[aux_b1] = 5;
					}
				}
			minuteiro[aux_b1] = 0;
			horimetro[aux_b1] = 0;
			acionamentos[aux_b1] = 0;
			write_byte(ee_minuteiro + aux_b1, 0);
			write_word(ee_horimetro + (aux_b1 * 2), 0);
			write_word(ee_acionamentos + (aux_b1 * 2), 0);
			}
		}
	for (x = 0; x < nro_bancos_capacitor; x++)
		{
		banco_capacitor[x] = tabela_valor_bancos[x];
		tempo_repouso[x] = tabela_tempo_repouso[x];
		}

	if (cor_minima == 0)
		{
		cor_minima = 2;
		}

	salva_programa();

	valida_programa();

 	exibe_programa_bancos();
}


void trata_menu5(void)
{
	char x;
	if (qmenu != 5)
		{
		qmenu = 5;
		exibiu = 0;
		menu_aux = 1;
		time_out_menus = 60;
		
		#if (ST8100C == true)
			ja_rolou = false;
			rolando = false;
			time_out2 = 3;
		#endif
		
		aux_tab = 0;
		sel_sequencia = 0;
		sel_seq_tab = 0;

		if ((nro_bancos_capacitor == 0) || (nro_bancos_capacitor > NRO_MAXIMO_BANCOS_CAPACITOR))
			{
			nro_bancos_capacitor = 6;
			}
		tabela_programa[1] = nro_bancos_capacitor;
		aux_nro_bancos_capacitor = nro_bancos_capacitor;
		if (max_kvar != 0)
			{
			for (x = 0; x < nro_bancos_capacitor; x++)
				{
				if (max_kvar < banco_capacitor[x])
					{
					max_kvar = banco_capacitor[x];
					}
				}
			}
		tabela_programa[2] = max_kvar;
		if (max_kvar != 0)
			{
			if (min_kvar > max_kvar)
				{
				min_kvar = max_kvar;
				}
			}
		tabela_programa[3] = min_kvar;
		if (cor_minima == 0)
			{
			cor_minima = 2;
			}
			
		#if (com_rep == true)
			if (modo_rep == true)
				{
				tabela_programa[4] = cor_minima_rep;
				}
			else
				{
				tabela_programa[4] = cor_minima;
				}
		#else
			tabela_programa[4] = cor_minima;
		#endif
		
		if (tempo_aciona == 0)
			{
			tempo_aciona = 30;
			}
		tabela_programa[5] = tempo_aciona;
		if (tempo_desaciona == 0)
			{
			tempo_desaciona = 30;
			}
		tabela_programa[6] = tempo_desaciona;
		tabela_programa[7] = sequencia;
		tabela_programa[8] = 30;
		tabela_programa[9] = 180;
		for (x = 0; x < nro_bancos_capacitor; x++)
			{
			tabela_valor_bancos[x] = banco_capacitor[x];
			tabela_tempo_repouso[x] = tempo_repouso[x];
			}
		}

	if (tecla_up == 1)
		{
		tecla_up = 0;
		exibiu = 0;

		#if (ST8100C == true)
			time_out2 = 3;
		#endif

		if (programando == 1)
			{
			tempo_senha = 255;
			switch (menu_aux)
				{
				case 1:				// incrementa nro de bancos 
			 		{
			 		if (tabela_programa[1] < NRO_MAXIMO_BANCOS_CAPACITOR)
		 				{
						tabela_programa[1]++;
						}
					break;
		 			}
			 	case 2: // incrementa max kvar 
			 		{
			 		if (tabela_programa[2] < MAIOR_BANCO_POSSIVEL)
		 				{
						tabela_programa[2]++;
						}
					break;
		 			}
			 	case 3: // incrementa min kvar - banco minimo 
			 		{
			 		if (tabela_programa[3] < MAIOR_BANCO_POSSIVEL)
		 				{
						tabela_programa[3]++;
						}
					break;
			 		}	
			 	case 4: // incrementa corrente minima 
			 		{                   
					#if (com_rep == true)
						if (modo_rep == true)
							{
					 		if (tabela_programa[4] < 9999)
		 						{
								tabela_programa[4]++;
								}
							}
						else
							{
					 		if (tabela_programa[4] < 50)
		 						{
								tabela_programa[4]++;
								}
							}
					#else
				 		if (tabela_programa[4] < 50)
			 				{
							tabela_programa[4]++;
							}
					#endif
					break;
		 			}
			 	case 5: // incrementa tempo acionamento 
			 		{
			 		if (tabela_programa[5] < 180)
		 				{
						tabela_programa[5]++;
						}
					break;
		 			}
				case 6:	// incrementa tempo desaciona 
					{
			 		if (tabela_programa[6] < 180)
		 				{
						tabela_programa[6]++;
						}
					break;
					}
			 	case 7: // incrementa sequencia bancos 
			 		{
					if (sel_sequencia == 1)
						{
						if (sel_seq_tab == 1)
							{
							if (tabela_programa[1] < 7)
								{
						 		if (tabela_programa[7] < NRO_SEQ_BANCOS[(tabela_programa[1]-1)])
					 				{
									tabela_programa[7]++;
									}
								}
							else
								{
						 		if (tabela_programa[7] < NRO_SEQ_BANCOS[5])
					 				{
									tabela_programa[7]++;
									}
								}
							}
						}
					break;
		 			}
			 	case 8: // incrementa valor de cada banco 
			 		{                   
					if (tabela_valor_bancos[aux_tab] < MAIOR_BANCO_POSSIVEL)
						{
						tabela_valor_bancos[aux_tab]++;
						}
					#if (ST8100C == true)
						topo_menu = false;
						primeira = false;
						time_out2 = 0;
					#endif
					break;
		 			}
			 	case 9: // incrementa valor de tempo de repouso por banco 
			 		{                   
					if (tabela_tempo_repouso[aux_tab] < 240)
						{
						tabela_tempo_repouso[aux_tab]++;
						}
					#if (ST8100C == true)
						topo_menu = false;
						primeira = false;
						time_out2 = 0;
					#endif
					break;
		 			}
				}
		 	}
		else
		 	{
			primeira = true;
			if (topo_menu == true)
				{
				topo_menu = false;
				}
			else
				{
				if (menu_aux == 8)
					{
					if (aux_tab == 0)
						{
						menu_aux--;
						topo_menu = true;
						}
					else if (aux_tab > 0)
						{
						aux_tab--;
						}
					}
				else if (menu_aux == 9)
					{
					if (aux_tab == 0)
						{
						menu_aux--;
						aux_tab = nro_bancos_capacitor - 1;
						topo_menu = true;
						}
					else if (aux_tab > 0)
						{
						aux_tab--;
						}
					}
				else if (menu_aux == 7)
					{
					if (sel_sequencia == 1)
						{
						if (sel_seq_tab == 0)
							{
							if (aux_tab < 1)
								{
								aux_tab++;
								}
							}
						}
					else
						{
						menu_aux--;
						}
					}
				else
					{
				 	if (menu_aux > 1)
				 		{
						topo_menu = true;
		 				menu_aux--;
						}
					}
				}
			ja_rolou = false;
			rolando = false;
		 	}
		}
	if (tecla_down == 1)
		{
		tecla_down = 0;
		exibiu = 0;

		#if (ST8100C == true)
			time_out2 = 3;
		#endif

		if (programando == 1)
			{
			tempo_senha = 255;
			switch (menu_aux)
				{
				case 1:	// decrementa nro de bancos 
			 		{
			 		if (tabela_programa[1] > 2)
		 				{
						tabela_programa[1]--;
						}
					break;
		 			}
			 	case 2: // decrementa max kvar
			 	case 3: // decrementa min kvar - banco minimo 
			 		{
			 		if (tabela_programa[menu_aux] > 0)
		 				{
						tabela_programa[menu_aux]--;
						}
					break;
			 		}	
			 	case 4: // decrementa corrente minima 
			 		{                   
					#if (com_rep == true)
						if (modo_rep == true)
							{
					 		if (tabela_programa[4] > 0)
		 						{
								tabela_programa[4]--;
								}
							}
						else
							{
					 		if (tabela_programa[4] > 2)
		 						{
								tabela_programa[4]--;
								}
							}
					#else
				 		if (tabela_programa[4] > 2)
			 				{
							tabela_programa[4]--;
							}
					#endif
					break;
				 	}
			 	case 5: // decrementa tempo acionamento 
			 		{
			 		if (tabela_programa[5] > 1)
		 				{
						tabela_programa[5]--;
						}
					break;
		 			}
				case 6:	// decrementa tempo desaciona 
					{
			 		if (tabela_programa[6] > 1)
		 				{
						tabela_programa[6]--;
						}
					break;
					}
			 	case 7: // decrementa sequencia bancos 
			 		{
				 	if (sel_sequencia == 1)
				 		{
					 	if (sel_seq_tab == 1)
					 		{
						 	if (tabela_programa[7] > 1)
						 		{
							 	tabela_programa[7]--;
							 	}
						 	}
					 	}
				 	break;
				 	}
			 	case 8: // decrementa valor de cada banco 
			 		{                   
					if (tabela_valor_bancos[aux_tab] > 1)
						{
						tabela_valor_bancos[aux_tab]--;
						}
					#if (ST8100C == true)
						topo_menu = false;
						primeira = false;
						time_out2 = 0;
					#endif
					break;
		 			}
			 	case 9: // decrementa valor de tempo de repouso por banco 
			 		{                   
					if (tabela_tempo_repouso[aux_tab] > tabela_programa[5])
						{
						tabela_tempo_repouso[aux_tab]--;
						}
					#if (ST8100C == true)
						topo_menu = false;
						primeira = false;
						time_out2 = 0;
					#endif
					break;
		 			}
				}
		 	}
		 else
		 	{
			primeira = true;
			if (topo_menu == true)
				{
				topo_menu = false;
				}
			else
				{
				if (menu_aux == 8)
					{
					if (aux_tab == (nro_bancos_capacitor - 1))
						{
						menu_aux++;
						aux_tab = 0;
						topo_menu = true;
						}
					else if (aux_tab < (nro_bancos_capacitor - 1))
						{
						aux_tab++;
						}
					}
				else if (menu_aux == 9)
					{
					if (aux_tab < (nro_bancos_capacitor - 1))
						{
						aux_tab++;
						}
					}
				else if (menu_aux == 7)
					{
					if (sel_sequencia == 1)
						{
						if (sel_seq_tab == 0)
							{
							if (aux_tab > 0)
								{
								aux_tab--;
								}
							}
						}
					else
						{
						menu_aux++;
						topo_menu = true;
						}
					}
				else
					{
					 if (menu_aux < nro_menus5)
			 			{
			 			menu_aux++;
						}
					}
				}
			ja_rolou = false;
			rolando = false;
	 		}
		}
	if (tecla_enter == 1)
		{
	 	tecla_enter = 0;
		exibiu = 0;
		topo_menu = false;

		#if (ST8100C == true)
			time_out2 = 0;
		#endif


	 	#if ((st8200c == true) || (st8300c == true))
	 		ja_rolou = true;
			rolando = false;
	 	#endif

	 	if (ja_rolou == false)
	 		{
			rolando = false;
			ja_rolou = true;
			}
		else
			{
			if (programando == 1)
				{
				programando = 0;
				if ((menu_aux == 7) || (menu_aux == 8))
					{
					monta_tabela_bancos(tabela_programa[7]);
					}
				if (menu_aux == 7)
					{
					if (aux_tab == 0)
						{
						if (sel_seq_tab == 1)
							{
							sel_sequencia = 0;
							sel_seq_tab = 0;
							aux_tab = 0;
							menu_aux++;
							}
						}
					}
				salva_programa_bancos();
				}
			else
				{
				if (tempo_senha != 0)
					{
					if (menu_aux == 8)		//para permitir programação de todos os bancos qdo seq. == usuário
						{
						if (tabela_programa[7] == 0)
							{
							programando = 1;
							}
						else
							{
							if (aux_tab < 1)
								{
								programando = 1;
								}
							}
						}
					else if (menu_aux == 7)		//para entrar no submenu da programação da sequencia de acionamento
						{
						if (sel_sequencia == 1)
							{
							if (aux_tab == 1)
								{
								tabela_programa[7] = 0;
								salva_programa_bancos();
								sel_sequencia = 0;
								sel_seq_tab = 0;
								aux_tab = 0;
								menu_aux++;
								}
							else
								{
								if (sel_seq_tab == 1)
									{
									programando = 1;
									}
								else
									{
									sel_seq_tab = 1;
									}
								}
							}
						else
							{
							sel_sequencia = 1;
							}
						}
					else
						{
						programando = 1;
						}
					}
				else
					{
					trata_senha();
					return;
					}
				}
			}
		}		
	if (tecla_reset == true)
		{
		tecla_reset = 0;
		topo_menu = false;
		rolando = false;
		ja_rolou = false;
		exibiu = 0;
		if (sel_sequencia == 1)
			{
			if (sel_seq_tab == 1 )
				{
				if (programando == 1)
					{
					programando = 0;
					sel_seq_tab = 0;
					tabela_programa[7] = sequencia;
					}
				else
					{
					sel_seq_tab = 0;
					}
				}
			else
				{
				sel_sequencia = 0;
				aux_tab = 0;
				}
			}
		else
			{
			if (programando == 1)
				{
				programando = 0;
				tabela_programa[1] = nro_bancos_capacitor;
				tabela_programa[2] = max_kvar;
				tabela_programa[3] = min_kvar;
				#if (com_rep == true)
					if (modo_rep == true)
						{
						tabela_programa[4] = cor_minima_rep;
						}
					else
						{
						tabela_programa[4] = cor_minima;
						}
				#else
					tabela_programa[4] = cor_minima;
				#endif
				tabela_programa[5] = tempo_aciona;
				tabela_programa[6] = tempo_desaciona;
				tabela_programa[7] = sequencia;
				}
			else
				{
				menu_aux = 1;
				menu1 = 5;
				qmenu = 0;
				exibe_menu();
				return;
				}
			}
		}
	exibe_programa_bancos();
}
