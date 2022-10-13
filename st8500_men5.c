/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST8610_MEN5                                                    *
; Funcao: TRATAMENTO DO MENU DE PROGRAMAÇÃO DE BANCOS					 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/
  


void exibe_programa_cargas(void)
{
	char x;
	if (exibir_menu == 0)
		{
		return;
		}
	exibir_menu = 0;
	
	if (menu_aux == 0)
		{
		menu_aux = 1;
		}
	if (menu_aux < 7)
		{
		desativa_cursor();
		}
	switch (menu_aux)
		{
		case 1:		//Número de Cargas
			{
			if (exibiu == 0)
				{
				mensagem (1,8);
				mensagem (2,14);
				exibiu = 1;
				}
			displayp (31,tabela_programa[1],2,0,'P');
			break;
			}
		case 2:		//Tipo de controle
			{
			if (exibiu == 0)
				{
				mensagem (1,159);
				exibiu = 1;
				}
			if (tabela_programa[2] == 0)
				{
				if (programando == true)
					{
					if (piscar == 1)
						{
						mensagem (2,0);
						}
					else
						{
						mensagem (2,160);
						}
					}
				else
					{
					mensagem (2,160);
					}
				}
			else if (tabela_programa[2] == 1)
				{
				if (programando == true)
					{
					if (piscar == 1)
						{
						mensagem (2,0);
						}
					else
						{
						mensagem (2,161);
						}
					}
				else
					{
					mensagem (2,161);
					}
				}
			break;
			}
		case 3:		//Máximo Acionamento
			{
			if (exibiu == 0)
				{
				mensagem (1,8);
				mensagem (2,16);
				exibiu = 1;
				}
			displayp (27,tabela_programa[3],4,0,'P');
			break;
			}
		case 4:		//Tempo de Acionamento
			{
			if (exibiu == 0)
				{
				mensagem (2,18);
				exibiu = 1;
				}
				displayp (29,tabela_programa[4],3,0,'P');
			break;
			}
		case 5:		//Tempo Desaciona
			{
			if (exibiu == 0)
				{
				mensagem (2,137);
				exibiu = 1;
				}
				displayp (29,tabela_programa[5],3,0,'P');
			break;
			}
		case 6:		//Valor de Cada Carga
			{
			if (exibiu == 0)
				{
				mensagem (2,19);
				exibiu = 1;
				}
			displayp (23,aux_tab + 1,2,0,0);
			displayp (27,tabela_valor_cargas[aux_tab],3,0,'P');
			break;
			}
		case 7:		//Tempo de Repouso de Cada Carga
			{
			if (exibiu == 0)
				{
				mensagem (1,8);
				mensagem (2,20);
				exibiu = 1;
				}
			displayp (25,aux_tab + 1,2,0,0);
			displayp (28,tabela_tempo_repouso[aux_tab],3,0,'P');
			break;
			}
		case 8:		// se carga tem controle por horario ou pro demanda e se tiver programação pro horário, programar o horario
			{
			if (exibiu == 0)
				{
				//		1234567890123456
				//		Modo Carga: @@-X		onde o X = D(demanda) ou H(horario)
				//		 L-??:?? D-??:??
				if (aux_tab2 == 0)
					{
					mensagem (1,8);
					mensagem (2,158);
					}
				else
					{
					if (forma_controle[aux_tab] == 'H')
						{
						mensagem (1,158);
					    displayp(13,aux_tab+1,2,0,0);
						lcd_gotoxy(16,1);
					    wr_lcd(1,'H');
						}
					else
						{
						mensagem (1,8);
						}
					mensagem (2,136);
					}
				exibiu = 1;

				tabela_pisca[0] = 0;
				tabela_pisca[1] = 0;
				tabela_pisca[2] = 0;
				tabela_pisca[3] = 0;
				tabela_pisca[4] = 0;
				tabela_pisca[aux_tab2] = 'P';
				}
			if (aux_tab2 == 0)
				{
			    displayp(29,aux_tab+1,2,0,0);
				lcd_gotoxy(16,2);
				if (piscar == 1)
					{
				    wr_lcd(1,' ');
					}
				else
					{
					if (forma_controle[aux_tab] == 'H')
						{
					    wr_lcd(1,'H');
						}
					else
						{
					    wr_lcd(1,'D');
					    }
					}
				}
			else
				{
			    displayp(20,hora_desliga_controle[aux_tab],2,0,tabela_pisca[1]);
			    displayp(23,minuto_desliga_controle[aux_tab],2,0,tabela_pisca[2]);
			    displayp(28,hora_liga_controle[aux_tab],2,0,tabela_pisca[3]);
			    displayp(31,minuto_liga_controle[aux_tab],2,0,tabela_pisca[4]);
			    }
			if (aux_tab2 == 0)
				{
				lcd_gotoxy(18,2);
				}
			else if (aux_tab2 == 1)
				{
				lcd_gotoxy(5,2);
				}
			else if (aux_tab2 == 2)
				{
				lcd_gotoxy(8,2);
				}
			else if (aux_tab2 == 3)
				{
				lcd_gotoxy(13,2);
				}
			else if (aux_tab2 == 4)
				{
				lcd_gotoxy(16,2);
				}
			ativa_cursor();
			break;
			}
		default:
			{
			menu_aux = 1;
			}
		}
}



void salva_programa_cargas(void)
{
	char x;
	nro_cargas = tabela_programa[1];
	tipo_controle_demanda = tabela_programa[2];
	max_kw = tabela_programa[3];
	write_word(ee_max_kw, max_kw);

	
	tempo_aciona = tabela_programa[4];
	tempo_desaciona = tabela_programa[5];
	for (x = 0; x < nro_cargas; x++)
		{
		carga[x] = tabela_valor_cargas[x];
		tempo_repouso[x] = tabela_tempo_repouso[x];
		}

	valida_max_kw();
	tabela_programa[3] = max_kw;

	salva_programa();
	valida_programa();
 	exibe_programa_cargas();
}


void trata_menu5(void)
{
	char x;
	if (qmenu != 5)
		{
		qmenu = 5;
		exibiu = 0;
		menu_aux = 1;
		aux_tab2 = 0;
		time_out_menus = 60;
		
		aux_tab = 0;

		if ((nro_cargas == 0) || (nro_cargas > NRO_MAXIMO_CARGAS))
			{
			nro_cargas = (NRO_MAXIMO_CARGAS/2);
			}
		tabela_programa[1] = nro_cargas;
		if (max_kw != 0)
			{
			for (x = 0; x < nro_cargas; x++)
				{
				if (max_kw < carga[x])
					{
					max_kw = carga[x];
					}
				}
			}
		tabela_programa[2] = tipo_controle_demanda;
		tabela_programa[3] = max_kw;
			
		if (tempo_aciona == 0)
			{
			tempo_aciona = 30;
			}
		tabela_programa[4] = tempo_aciona;
		if (tempo_desaciona == 0)
			{
			tempo_desaciona = 30;
			}
		tabela_programa[5] = tempo_desaciona;
		for (x = 0; x < nro_cargas; x++)
			{
			tabela_valor_cargas[x] = carga[x];
			tabela_tempo_repouso[x] = tempo_repouso[x];
			}
		}

	if (tecla_up == 1)
		{
		tecla_up = 0;
		exibiu = 0;
		exibir_menu = 1;

		if (programando == 1)
			{
			tempo_senha = 255;
			switch (menu_aux)
				{
				case 1:				// incrementa nro de cargas 
			 		{
			 		if (tabela_programa[1] < NRO_MAXIMO_CARGAS)
		 				{
						tabela_programa[1]++;
						}
					break;
		 			}
		 		case 2:
		 			{
			 		if (tabela_programa[2] == 0)
		 				{
						tabela_programa[2] = 1;
						}
					else
		 				{
						tabela_programa[2] = 0;
						}
			 		break;
			 		}
			 	case 3: // incrementa max kvar 
			 		{
			 		if (tabela_programa[3] < carga_instalada)
		 				{
						tabela_programa[3]++;
						}
					break;
		 			}
			 	case 4: // incrementa tempo acionamento 
			 		{
			 		if (tabela_programa[4] < 240)
		 				{
						tabela_programa[4]++;
						}
					break;
		 			}
				case 5:	// incrementa tempo desaciona 
					{
			 		if (tabela_programa[5] < 240)
		 				{
						tabela_programa[5]++;
						}
					break;
					}
			 	case 6: // incrementa valor de cada carga 
			 		{                   
					if (tabela_valor_cargas[aux_tab] < MAXIMA_CARGA)
						{
						tabela_valor_cargas[aux_tab]++;
						}
					break;
		 			}
			 	case 7: // incrementa valor de tempo de repouso por carga 
			 		{                   
					if (tabela_tempo_repouso[aux_tab] < 240)
						{
						tabela_tempo_repouso[aux_tab]++;
						}
					break;
		 			}
		 		case 8:
		 			{
			 		switch (aux_tab2)
			 			{
				 		case 0:
				 			{
							if (forma_controle[aux_tab] == 'H')
								{
								forma_controle[aux_tab] = 'P';
								}
							else
								{
								forma_controle[aux_tab] = 'H';
								}
					 		break;
					 		}
				 		case 1:
				 			{
					 		if (hora_desliga_controle[aux_tab] < 23)
					 			{
						 		hora_desliga_controle[aux_tab]++; 
						 		}
					 		break;
					 		}
				 		case 2:
				 			{
					 		if (minuto_desliga_controle[aux_tab] < 59)
					 			{
						 		minuto_desliga_controle[aux_tab]++; 
						 		}
					 		break;
					 		}
				 		case 3:
				 			{
					 		if (hora_liga_controle[aux_tab] < 23)
					 			{
						 		hora_liga_controle[aux_tab]++; 
						 		}
					 		break;
					 		}
				 		case 4:
				 			{
					 		if (minuto_liga_controle[aux_tab] < 59)
					 			{
						 		minuto_liga_controle[aux_tab]++; 
						 		}
					 		break;
					 		}
				 		default:
				 			{
				 			aux_tab2 = 0;
				 			}
				 		}
			 		}		 			
				}
		 	}
		else
		 	{
			if ((menu_aux == 6) || (menu_aux == 7))
				{
				if (aux_tab > 0)
					{
					aux_tab--;
					}
				else
					{
					if (menu_aux == 7)
						{
						menu_aux--;
						aux_tab = nro_cargas-1;
						}
					else if (menu_aux == 8)
						{
						menu_aux--;
						aux_tab = nro_cargas-1;
						aux_tab2 = 0;
						}
					else
						{
						menu_aux--;
						}
					}
				}
			else if (menu_aux == 8)
				{
				if (forma_controle[aux_tab] == 'D')
					{
					aux_tab2 = 0;
					if (aux_tab > 0)
						{
						aux_tab--;
						}
					else
						{
						menu_aux--;					// Edison 22/12/09 - Não permitia subida no menu de programação.
						aux_tab = nro_cargas-1;
						aux_tab2 = 0;
						}
					}
				else
					{
					if (aux_tab2 > 0)
						{
						aux_tab2--;
						}
					else
						{
						aux_tab2 = 4;
						if (aux_tab > 0)
							{
							aux_tab--;
							if (forma_controle[aux_tab] == 'D')
								{
								aux_tab2 = 0;
								}
							}
						else
							{
							menu_aux--;					// Edison 22/12/09 - Não permitia subida no menu de programação.
							aux_tab = nro_cargas-1;
							aux_tab2 = 0;
							}
						}
					}
				}
			else
				{
				if (menu_aux > 1)
					{
					menu_aux--;
					}
				}
		 	}
		}
	if (tecla_down == 1)
		{
		tecla_down = 0;
		exibiu = 0;
		exibir_menu = 1;

		if (programando == 1)
			{
			tempo_senha = 255;
			switch (menu_aux)
				{
				case 1:	// decrementa nro de cargas 
			 		{
			 		if (tabela_programa[1] > 2)
		 				{
						tabela_programa[1]--;
						}
					break;
		 			}
		 		case 2:
		 			{
			 		if (tabela_programa[2] == 0)
		 				{
						tabela_programa[2] = 1;
						}
					else
		 				{
						tabela_programa[2] = 0;
						}
			 		break;
			 		}
			 	case 3: // decrementa max kw
			 		{
			 		if (tabela_programa[3] > menor_carga)
		 				{
						tabela_programa[3]--;
						}
					break;
			 		}	
			 	case 4: // decrementa tempo acionamento 
			 		{
			 		if (tabela_programa[4] > 5)				//Alterado por pedido de cliente de 30s para 5s em 14/01/09.
		 				{
						tabela_programa[4]--;
						}
					break;
		 			}
				case 5:	// decrementa tempo desaciona 
					{
			 		if (tabela_programa[5] > 5)				//Alterado por pedido de cliente de 30s para 5s em 14/01/09.
		 				{
						tabela_programa[5]--;
						}
					break;
					}
			 	case 6: // decrementa valor de cada carga 
			 		{                   
					if (tabela_valor_cargas[aux_tab] > 0)
						{
						tabela_valor_cargas[aux_tab]--;
						}
					break;
		 			}
			 	case 7: // decrementa valor de tempo de repouso por carga 
			 		{                   
					if (tabela_tempo_repouso[aux_tab] > tabela_programa[4])
						{
						tabela_tempo_repouso[aux_tab]--;
						}
					break;
		 			}
		 		case 8:
		 			{
			 		switch (aux_tab2)
			 			{
				 		case 0:
				 			{
							if (forma_controle[aux_tab] == 'H')
								{
								forma_controle[aux_tab] = 'P';
								}
							else
								{
								forma_controle[aux_tab] = 'H';
								}
					 		break;
					 		}
				 		case 1:
				 			{
					 		if (hora_desliga_controle[aux_tab] > 0)
					 			{
						 		hora_desliga_controle[aux_tab]--; 
						 		}
					 		break;
					 		}
				 		case 2:
				 			{
					 		if (minuto_desliga_controle[aux_tab] > 0)
					 			{
						 		minuto_desliga_controle[aux_tab]--; 
						 		}
					 		break;
					 		}
				 		case 3:
				 			{
					 		if (hora_liga_controle[aux_tab] > 0)
					 			{
						 		hora_liga_controle[aux_tab]--; 
						 		}
					 		break;
					 		}
				 		case 4:
				 			{
					 		if (minuto_liga_controle[aux_tab] > 0)
					 			{
						 		minuto_liga_controle[aux_tab]--; 
						 		}
					 		break;
					 		}
				 		default:
				 			{
				 			aux_tab2 = 0;
				 			}
				 		}
			 		}
				}
		 	}
		 else
		 	{
			if ((menu_aux == 6) || (menu_aux == 7))
				{
				if (aux_tab < (nro_cargas-1))
					{
					aux_tab++;
					}
				else
					{
					if (menu_aux == 6)
						{
						menu_aux++;
						aux_tab = 0;
						}
					else if (menu_aux == 7)
						{
						menu_aux++;
						aux_tab = 0;
						aux_tab2 = 0;
						}
					}
				}
			else if (menu_aux == 8)
				{
				if (forma_controle[aux_tab] == 'D')
					{
					if (aux_tab < (nro_cargas-1))
						{
						aux_tab++;
						}
					}
				else
					{
					if (aux_tab2 < 4)
						{
						aux_tab2++;
						}
					else
						{
						aux_tab2 = 0;
						if (aux_tab < (nro_cargas-1))
							{
							aux_tab++;
							}
						}
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
		}
	if (tecla_enter == 1)
		{
		exibir_menu = 1;
	 	tecla_enter = 0;
		if (programando == 1)
			{
			programando = 0;
			if (menu_aux == 8)
				{
				exibiu = 0;
				if (forma_controle[aux_tab] == 'H')
					{
					if (aux_tab2 < 4)
						{
						aux_tab2++;
						}
					else
						{
						aux_tab2 = 0;
						if (aux_tab < (nro_cargas-1))
							{
							aux_tab++;
							}
						}
					}
				else
					{
					aux_tab2 = 0;
					if (aux_tab < (nro_cargas-1))
						{
						aux_tab++;
						}
					}
				}
			salva_programa_cargas();
			}
		else
			{
			if (tempo_senha == 0)
				{
				trata_senha();
				return;
				}
			else
				{
				programando = 1;
				}
			}
		}
	if (tecla_reset == true)
		{
		exibir_menu = 1;
		tecla_reset = 0;
		exibiu = 0;
		if (programando == 1)
			{
			programando = 0;
			tabela_programa[1] = nro_cargas;
			tabela_programa[2] = tipo_controle_demanda;
			tabela_programa[3] = max_kw;
			tabela_programa[4] = tempo_aciona;
			tabela_programa[5] = tempo_desaciona;
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
//	}
	exibe_programa_cargas();
}


void gera_sequencia_valor_bancos(void) 
{
}
