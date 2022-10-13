/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: st94men4.c                                                     *
; Funcao: Controle do Menu de Programação Geral							 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/

void exibe_programa(void)
{
	#if (st92 == true)
		switch (menu_aux)
			{
			case 1:		//Tensão Nominal
				{
				if (exibiu == 0)
					{
					mensagem (2,0);
					mensagem (2,10);
					exibiu = 1;
					}
				displayp(25,tabela_programa[1],3,0,'P');
				break;
				}
			case 2:		//Valor TC
				{
				if (exibiu == 0)
					{
					mensagem (2,0);
					mensagem (2,11);
					exibiu = 1;
					}
				displayp(27,tabela_programa[2],4,0,'P');
				break;
				}
			case 3:		//Valor TP
				{
				if (exibiu == 0)
					{
					mensagem (2,0);
					mensagem (2,12);
					exibiu = 1;
					}
				displayp(29,tabela_programa[3],3,0,'P');
				break;
				}
			case 4:		//Set-Point
				{
				if (exibiu == 0)
					{
					mensagem (2,0);
					mensagem (2,13);
					exibiu = 1;
					}
				displayd(28,tabela_programa[4],'P');
				break;
				}
			case 5:		//Endereço Modbus
				{
				if (exibiu == 0)
					{
					mensagem (2,0);
					mensagem (2,14);
					exibiu = 1;
					}
				displayp (30,tabela_programa[5],3,0,'P');
				break;
				}
			case 6:		//Intervalo de Integração
				{
				if (exibiu == 0)
					{
					mensagem (2,0);
					mensagem (2,15);
					lcd_gotoxy(16,2);
				    wr_lcd(1,'m');
					exibiu = 1;
					}
				displayp (30,tabela_programa[6],2,0,'P');
				break;
				}
			#if (st9230r == true)
				case 7:		//Intervalo Entre Registros
					{
					if (exibiu == 0)
						{
						mensagem (2,0);
						mensagem (2,16);
						lcd_gotoxy(16,2);
					    wr_lcd(1,'s');
						exibiu = 1;
						}
					displayp (28,tabela_programa[7],4,0,'P');
					break;
					}
				case 8:		//Forma de Registro do Conteúdo Harmônico
					{
					if (exibiu == 0)
						{
						mensagem (2,0);
						mensagem (2,17);
						exibiu = 1;
						}
					displayp (31,tabela_programa[8],2,0,'P');
					break;
					}
			#endif
			case 9:		//Baud Rate
				{
				if (exibiu == 0)
					{
					mensagem (2,0);
					mensagem (2,18);
					exibiu = 1;
					}
				displayp (28,tabela_baud[tabela_programa[9]],5,0,'P');
				break;
				}
			case 10:		//Tipo de Ligação
				{
				if (exibiu == 0)
					{
					mensagem (2,0);
					mensagem (2,19);
					exibiu = 1;
					}
				lcd_gotoxy(15,2);
				if (tabela_programa[10] == 0)
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
				else if (tabela_programa[10] == 1)
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
				else
					{
					if (programando == 1)
				 		{
						if (piscar == 1)
							{
							display(' ');
							display(' ');
							}
						else
							{
							display('D');
							display('A');
							}
						}
					else
						{
						display('D');
						display('A');
						}
					}
				break;
				}
			case 11:		//Exibição do Horário de Ponta em um sub-menu
				{
				if (aux_tab == 1)
					{
					if (exibiu == 0)
						{
						mensagem (1,79);
						mensagem (2,80);
						exibiu = 1;
						}
					if (programando == 1)
						{
						if (minuto_hora_ponta == 0)
							{
							displayp (27,tabela_programa[11],2,0,'P');
							displayp (30,tabela_programa[13],2,0,0);
							}
						else
							{
							displayp (27,tabela_programa[11],2,0,0);
							displayp (30,tabela_programa[13],2,0,'P');
							}
						}
					else
						{
						displayp (27,tabela_programa[11],2,0,0);
						displayp (30,tabela_programa[13],2,0,0);
						}
					}
				if (aux_tab == 2)
					{
					if (exibiu == 0)
						{
						mensagem (1,79);
						mensagem (2,81);
						exibiu = 1;
						}
					if (programando == 1)
						{
						if (minuto_hora_ponta == 0)
							{
							displayp (27,tabela_programa[12],2,0,'P');
							displayp (30,tabela_programa[14],2,0,0);
							}
						else
							{
							displayp (27,tabela_programa[12],2,0,0);
							displayp (30,tabela_programa[14],2,0,'P');
							}
						}
					else
						{
						displayp (27,tabela_programa[12],2,0,0);
						displayp (30,tabela_programa[14],2,0,0);
						}
					}
				if (aux_tab == 0)
					{
					if (exibiu == 0)
						{
						mensagem (1,6);
						mensagem (2,79);
						exibiu = 1;
						}
					}
				break;
				}
			default:
				{
				menu_aux = 1;
				}
			}
	#else
		switch (menu_aux)
			{
			case 0:
				{
				exibe_menu();
				break;
				}
			case 1:		//Tensão Nominal
				{
				mensagem(m_ten_nomi,1);
				binasc2(tabela_programa[1]);
				buf_display[8] = tabela_caracteres[MESPACO];
				buf_display[9] = tabela_caracteres[buf_tmp[2] - '0'];
				buf_display[10] = tabela_caracteres[buf_tmp[3] - '0'];
				buf_display[11] = tabela_caracteres[buf_tmp[4] - '0'];
				break;
				}
			case 2:		//Valor TC
				{
				mensagem(m_tipo_tc,1);
				binasc2(tabela_programa[2]);
				buf_display[8] = tabela_caracteres[buf_tmp[1] - '0'];
				buf_display[9] = tabela_caracteres[buf_tmp[2] - '0'];
				buf_display[10] = tabela_caracteres[buf_tmp[3] - '0'];
				buf_display[11] = tabela_caracteres[buf_tmp[4] - '0'];
				break;
				}
			case 3:		//Valor TP
				{
				mensagem(m_tipo_tp,1);
				binasc2(tabela_programa[3]);
				buf_display[8] = tabela_caracteres[buf_tmp[1] - '0'];
				buf_display[9] = tabela_caracteres[buf_tmp[2] - '0'];
				buf_display[10] = tabela_caracteres[buf_tmp[3] - '0'];
				buf_display[11] = tabela_caracteres[buf_tmp[4] - '0'];
				break;
				}
			case 4:		//Set-Point
				{
				mensagem(m_set_pnt,1);
				binasc2(tabela_programa[4]);
				buf_display[8] = tabela_caracteres[MESPACO];
				buf_display[9] = tabela_caracteres[M0] | 0x80;
				buf_display[10] = tabela_caracteres[buf_tmp[3] - '0'];
				buf_display[11] = tabela_caracteres[buf_tmp[4] - '0'];
				break;
				}
			case 5:		//Endereço Modbus
				{
				mensagem(m_addr_mod,1);
				binasc2(tabela_programa[5]);
				buf_display[8] = tabela_caracteres[MESPACO];
				buf_display[9] = tabela_caracteres[buf_tmp[2] - '0'];
				buf_display[10] = tabela_caracteres[buf_tmp[3] - '0'];
				buf_display[11] = tabela_caracteres[buf_tmp[4] - '0'];
				break;
				}
			case 6:		//Intervalo de Integração
				{
				mensagem(m_integra,1);
				binasc2(tabela_programa[6]);
				buf_display[8] = tabela_caracteres[MESPACO];
				buf_display[9] = tabela_caracteres[MESPACO];
				buf_display[10] = tabela_caracteres[buf_tmp[3] - '0'];
				buf_display[11] = tabela_caracteres[buf_tmp[4] - '0'];
				break;
				}
			#if (st9430r == true)
				case 7:		//Intervalo entre Registros
					{
					mensagem(m_time_regi,1);
					binasc2(tabela_programa[7]);
					buf_display[8] = tabela_caracteres[buf_tmp[1] - '0'];
					buf_display[9] = tabela_caracteres[buf_tmp[2] - '0'];
					buf_display[10] = tabela_caracteres[buf_tmp[3] - '0'];
					buf_display[11] = tabela_caracteres[buf_tmp[4] - '0'];
					break;
					}
				case 8:		//Modo de Registro de Conteúdo Harmônico
					{
					mensagem(m_modo_cht,1);
					binasc2(tabela_programa[8]);
					buf_display[8] = tabela_caracteres[MESPACO];
					buf_display[9] = tabela_caracteres[MESPACO];
					buf_display[10] = tabela_caracteres[buf_tmp[3] - '0'];
					buf_display[11] = tabela_caracteres[buf_tmp[4] - '0'];
					break;
					}
			#endif			
			case 9:		//Velocidade de Comunicação
				{
				mensagem(m_baudrate,1);
				buf_display[8] = tabela_caracteres[MESPACO];
				buf_display[9] = tabela_caracteres[MESPACO];
				switch(tabela_programa[9])
					{
					case 0:
						{
						buf_display[10] = tabela_caracteres[2] | 0x80;
						buf_display[11] = tabela_caracteres[4];
						break;
						}
					case 1:
						{
						buf_display[10] = tabela_caracteres[4] | 0x80;
						buf_display[11] = tabela_caracteres[8];
						break;
						}
					case 2:
						{
						buf_display[10] = tabela_caracteres[9] | 0x80;
						buf_display[11] = tabela_caracteres[6];
						break;
						}
					case 3:
						{
						buf_display[9] = tabela_caracteres[1];
						buf_display[10] = tabela_caracteres[9] | 0x80;
						buf_display[11] = tabela_caracteres[2];
						break;
						}
					case 4:
						{
						buf_display[9] = tabela_caracteres[3];
						buf_display[10] = tabela_caracteres[8] | 0x80;
						buf_display[11] = tabela_caracteres[4];
						break;
						}
					case 5:
						{
						buf_display[9] = tabela_caracteres[5];
						buf_display[10] = tabela_caracteres[7] | 0x80;
						buf_display[11] = tabela_caracteres[6];
						break;
						}
					}
				break;
				}
			case 10:	//Tipo de Ligação
				{
				mensagem(m_tipo_liga,1);
				binasc2(tabela_programa[10]);
				buf_display[8] = tabela_caracteres[MESPACO];
				buf_display[9] = tabela_caracteres[MESPACO];
				buf_display[10] = tabela_caracteres[buf_tmp[3] - '0'];
				buf_display[11] = tabela_caracteres[buf_tmp[4] - '0'];
				break;
				}
			case 11:		//Hora do Horário de Ponta
				{
				mensagem(32,1);
				binasc2(tabela_programa[11]);
				buf_display[8] = tabela_caracteres[MESPACO];
				buf_display[9] = tabela_caracteres[MESPACO];
				buf_display[10] = tabela_caracteres[buf_tmp[3] - '0'];
				buf_display[11] = tabela_caracteres[buf_tmp[4] - '0'];
				break;
				}
			case 12:		//Minuto do Horário de Ponta
				{
				mensagem(43,1);
				binasc2(tabela_programa[13]);
				buf_display[8] = tabela_caracteres[MESPACO];
				buf_display[9] = tabela_caracteres[MESPACO];
				buf_display[10] = tabela_caracteres[buf_tmp[3] - '0'];
				buf_display[11] = tabela_caracteres[buf_tmp[4] - '0'];
				break;
				}
			case 13:		//Hora Final do Horário de Ponta
				{
				mensagem(33,1);
				binasc2(tabela_programa[12]);
				buf_display[8] = tabela_caracteres[MESPACO];
				buf_display[9] = tabela_caracteres[MESPACO];
				buf_display[10] = tabela_caracteres[buf_tmp[3] - '0'];
				buf_display[11] = tabela_caracteres[buf_tmp[4] - '0'];
				break;
				}
			case 14:		//Minuto Final do Horário de Ponta
				{
				mensagem(44,1);
				binasc2(tabela_programa[14]);
				buf_display[8] = tabela_caracteres[MESPACO];
				buf_display[9] = tabela_caracteres[MESPACO];
				buf_display[10] = tabela_caracteres[buf_tmp[3] - '0'];
				buf_display[11] = tabela_caracteres[buf_tmp[4] - '0'];
				break;
				}
			default:
				{
				menu_aux = 1;
				}
			}
	#endif
		
	if (programando == 1)
		{
		if (ponto_segundo == 1)
			{
			#if (st92 == true)
			#else
				buf_display[8] = buf_display[8] | 0x80;
				buf_display[9] = buf_display[9] | 0x80;
				buf_display[10] = buf_display[10] | 0x80;
				buf_display[11] = buf_display[11] | 0x80;
			#endif
			}
		}
}



void salvar_programa(void)
{
	ten_nomi = tabela_programa[1];
	valor_tc = tabela_programa[2];
	valor_tp = tabela_programa[3];
	set_point = tabela_programa[4];
	endereco = tabela_programa[5];
	intervalo_integra = tabela_programa[6];
	#if ((st9430r == true) || (st9230r == true))
		intervalo_reg = tabela_programa[7];
	#endif	
	aux_intervalo_integra = intervalo_integra;
	
	forma_reg_cht = tabela_programa[8];
	baud_rate = tabela_baud[tabela_programa[9]];
	tipo_ligacao = tabela_programa[10];
	hora_ponta = tabela_programa[11];
	hora_final_ponta = tabela_programa[12];
	minuto_ponta = tabela_programa[13];
	minuto_final_ponta = tabela_programa[14];

	#if ((st9430r == true) || (st9230r == true))
		inicializa_regs();
		prox_grava = aux_l2 + intervalo_reg;
	#endif

	salva_programa();
	valida_programa();
 	exibe_programa();
	calcula_mul_tc();
}


void trata_menu4(void)
{
	char x;
	if (M1_C4 == 0)
		{
		M1_C4 = 1;
		exibiu = 0;
		aux_tab = 0;
		aux_b1 = 0;
		minuto_hora_ponta = 0;
		tabela_programa[1] = ten_nomi;
		tabela_programa[2] = valor_tc;
		tabela_programa[3] = valor_tp;
		tabela_programa[4] = set_point;
		tabela_programa[5] = endereco;
		tabela_programa[6] = intervalo_integra;
		#if ((st9430r == 1) || (st9230r == 1))
			tabela_programa[7] = intervalo_reg;
		#endif	
		tabela_programa[8] = forma_reg_cht;
		tabela_programa[9] = 0;
		for (x = 0; x < (NRO_POSI_BAUD); x++)
			{
			if (baud_rate == tabela_baud[x])
				{
				tabela_programa[9] = x;
				}
			}
		tabela_programa[10] = tipo_ligacao;
		tabela_programa[11] = hora_ponta;
		tabela_programa[12] = hora_final_ponta;
		tabela_programa[13] = minuto_ponta;
		tabela_programa[14] = minuto_final_ponta;
		
		time_out_menus = 60;
		}
		
	if (tecla_enter == 1)
		{
	 	tecla_enter = 0;
	 	exibiu = 0;
		if (programando == 1)
			{
			if (menu_aux != 1)
				{
				#if (st92 == true)
					if (menu_aux != 11)
						{
						programando = 0;
						salvar_programa();
						}
					else
						{
						salvar_programa();
						if (minuto_hora_ponta == 0)
							{
							minuto_hora_ponta = 1;
							programando = 1;
							}
						else
							{
							if (aux_tab == 1)
								{
								aux_tab = 2;
								}
							else
								{
								aux_tab = 1;
								}
							minuto_hora_ponta = 0;
							programando = 0;
							exibiu = 0;
							}
						}
				#else
					programando = 0;
					salvar_programa();
				#endif
				}
			}
		else
			{
			if (tempo_senha != 0)
				{
			 	if (menu_aux == 2)
			 		{
				 	programando = 1;
					aux_tab = 18;
			 		for (x = 0; x < (NRO_POSI_TC + 1) ;x++)
			 			{
			 			if (tabela_programa[2] == tabela_tc[x])
			 				{
							aux_tab = x;
							break;
							}
						}
					}
				#if ((st9430r == true) || st9230r == true))
				 	else if (menu_aux == 7)
				 		{
					 	programando = 1;
						aux_tab = 6;
				 		for (x = 0; x < (NRO_POSI_INTERVALO-1) ;x++)
				 			{
				 			if (tabela_programa[7] == tabela_intervalo_reg[x])
				 				{
								aux_tab = x;
								break;
								}
							}
						}
				#endif
				#if (st92 == true)
					else if (menu_aux == 11)
						{
						if (aux_tab == 0)
							{
							aux_tab = 1;
							}
						else
							{
							programando = 1;
							}
						}
				#endif
				else if (menu_aux != 1)
					{
					programando = 1;
					}
				}
			else
				{
				if (aux_tab == 0)
					{
					aux_tab = 1;
					}
				else
					{
					trata_senha();
					}
				return;
				}
			}
		}

	if (tecla_up == 1)
		{
		tecla_up = 0;
	 	exibiu = 0;
		if (programando == 1)
			{
			switch (menu_aux)
				{
				case 1:	/* incrementa tensao nominal */
			 		{
					}
			 	case 2: /* incrementa valor tc */
			 		{
					if (aux_tab < (NRO_POSI_TC-1))
						{
						aux_tab++;
						}
			 		else if (aux_tab > (NRO_POSI_TC-1))
			 			{
						aux_tab = 0;
						}
					tabela_programa[2] = tabela_tc[aux_tab];
					break;
					}
			 	case 3: /* incrementa valor valor_tp */
			 		{
			 		if (tabela_programa[3] < 500)
						{
						tabela_programa[3]++;
						}
					break;
			 		}	
			 	case 4: /* incrementa valor set_point */
			 		{
			 		if (tabela_programa[4] < 99)
						{
						tabela_programa[4]++;
						}
					break;
					}
			 	case 5: /* incrementa valor endereco do modbus */
			 		{
			 		if (tabela_programa[5] < 247)
						{
						tabela_programa[5]++;
						}
					else
						{
						tabela_programa[5] = 1;
						}
					break;
					}
			 	case 6: /* intervalo_integra */
			 		{
			 		if (tabela_programa[6] < 60)
						{
						tabela_programa[6]++;
						}
					else if (tabela_programa[6] > 60)
						{
						tabela_programa[6] = 1;
						}
					break;
					}
				#if ((st9430r == true) || (st9230r == true))
				 	case 7: /* incrementa intervalo_reg */
				 		{
						if (aux_tab < (NRO_POSI_INTERVALO-1))
							{
							aux_tab++;
							}
				 		else if (aux_tab > (NRO_POSI_INTERVALO-1))
				 			{
			 				aux_tab = 0;
			 				}
						tabela_programa[7] = tabela_intervalo_reg[aux_tab];
						break;
				 		}
				 	case 8: /* incrementa modo de gravar cht */
				 		{                   
				 		if (tabela_programa[8] < 3)
			 				{
							tabela_programa[8]++;
							}
						else if (tabela_programa[8] > 3)
							{
							tabela_programa[8] = 0;
							}
						break;
			 			}
				#endif
			 	case 9: /* incrementa valor de baudrate */
			 		{                   
			 		if (tabela_programa[9] < (NRO_POSI_BAUD - 1))
						{
						tabela_programa[9]++;
						}
					else
						{
						tabela_programa[9] = 0;
						}
					break;
					}
			 	case 10: /* incrementa valor de tipo ligacao */
			 		{                   
			 		if (tabela_programa[10] < 2)
						{
						tabela_programa[10]++;
						}
					else
						{
						tabela_programa[10] = 0;
						}
					break;
					}
				#if (st92 == true)
					case 11:
						{
						if (aux_tab == 1)
							{
							if (minuto_hora_ponta == 0)
								{
								if (tabela_programa[11] < 23)
									{
									if (tabela_programa[11] < (tabela_programa[12] - 1))
										{
										tabela_programa[11]++;
										}
									}
								}
							else
								{
								if (tabela_programa[13] < 59)
									{
									tabela_programa[13]++;
									}
								}
							}
						if (aux_tab == 2)
							{
							if (minuto_hora_ponta == 0)
								{
								if (tabela_programa[12] < 23)
									{
									tabela_programa[12]++;
									}
								}
							if (minuto_hora_ponta == 1)
								{
								if (tabela_programa[14] < 59)
									{
									tabela_programa[14]++;
									}
								}
							}
						break;	
						}
				#else
					case 11:
						{
						if (tabela_programa[11] < 23)		//Hora de Ponta
							{
							if (tabela_programa[11] < (tabela_programa[12] - 1))
								{
								tabela_programa[11]++;
								}
							}
						break;
						}
					case 12:
						{
						if (tabela_programa[13] < 59)		//Minuto de Ponta
							{
							tabela_programa[13]++;
							}
						break;
						}
					case 13:
						{
						if (tabela_programa[12] < 23)		//Hora Final de Ponta
							{
							tabela_programa[12]++;
							}
						break;
						}
					case 14:
						{
						if (tabela_programa[14] < 59)		//Minuto Final de Ponta
							{
							tabela_programa[14]++;
							}
						break;
						}
				#endif
				}
			if (tempo_senha != 255)
				{
				tempo_senha++;
				}
			}
		else
			{
			#if (st92 ==true)
				if (menu_aux == 11)
					{
					if (aux_tab != 0)
						{
						if (aux_tab == 1)
							{
							aux_tab = 2;
							}
						else
							{
							aux_tab = 1;
							}
						}
					else
						{
						if (menu_aux > 0)
							{
							menu_aux--;
							}
						}
					}
				else if (menu_aux > 0)
			#else
				if (menu_aux > 0)
			#endif
				{
 				menu_aux--;
				#if (com_regs == false)
				 	if (menu_aux == 8) 
						{
						menu_aux--;
						} 
				 	if (menu_aux == 7) 
						{
						menu_aux--;
						} 
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
			switch (menu_aux)
				{
				case 1: 	/* decrementa tensao nominal */
				case 2: /* decrementa valor tc */
			 		{
					if (aux_tab > 0)
						{
						aux_tab --;
						}
					tabela_programa[2] = tabela_tc[aux_tab];
					break;
			 		}
				case 3: /* decrementa valor set_point */
			 		{
			 		if (tabela_programa[3] > 1)
			 			{
						tabela_programa[3]--;
						}
					break;
			 		}
				case 4: /* decrementa valor set_point */
			 		{
			 		if (tabela_programa[4] > 90)
			 			{
						tabela_programa[4]--;
						}
					break;
			 		}
				case 5: /* decrementa valor endereco do modbus */
			 		{
			 		if (tabela_programa[5] > 1)
			 			{
						tabela_programa[5]--;
						}
					else
						{
						tabela_programa[5] = 247;
						}
					break;
			 		}
				case 6: /* detervalo_integra */
			 		{
			 		if (tabela_programa[6] > 1)
			 			{
						tabela_programa[6]--;
						}
					if (tabela_programa[6] > 60)
						{
						tabela_programa[6] = 1;
						}
					break;
		 			}
				#if ((st9430r == true) || (st9230r == true))
			 		case 7: /* decrementa intervalo_reg */
				 		{
						if (aux_tab > 0)
							{
							aux_tab --;
							}
						tabela_programa[7] = tabela_intervalo_reg[aux_tab];
						break;
				 		}
			 		case 8: /* decrementa modo de gravar cht */
				 		{                   
				 		if (tabela_programa[8] > 0)
				 			{
							tabela_programa[8]--;
							}
						if (tabela_programa[8] > 3)
							{
							tabela_programa[8] = 0;
							}
						break;
				 		}
					#endif		 		
				case 9: /* decrementa valor de baudrate */
			 		{                   
			 		if (tabela_programa[9] > 0)
			 			{
						tabela_programa[9]--;
						}
					if (tabela_programa[9] > (NRO_POSI_BAUD - 1))
						{
						tabela_programa[9] = 0;
						}
					break;
			 		}
				case 10: /* decrementa valor de tipo ligacao */
			 		{                   
			 		if (tabela_programa[10] > 0)
			 			{
						tabela_programa[10]--;
						}
					else
						{
						tabela_programa[10] = 2;
						}
					break;
			 		}
			 	#if (st92 == true)
					case 11:
						{
						if (aux_tab == 1)
							{
							if (minuto_hora_ponta == 0)
								{
								if (tabela_programa[11] > 0)
									{
									tabela_programa[11]--;
									}
								}
							else
								{
								if (tabela_programa[13] > 0)
									{
									tabela_programa[13]--;
									}
								}
							}
						if (aux_tab == 2)
							{
							if (minuto_hora_ponta == 0)
								{
								if (tabela_programa[12] > (tabela_programa[11] + 1))
									{
									tabela_programa[12]--;
									}
								}
							if (minuto_hora_ponta == 1)
								{
								if (tabela_programa[14] > 0)
									{
									tabela_programa[14]--;
									}
								}
							}
						break;	
						}
				#else
					case 11:
						{
						if (tabela_programa[11] > 0)
							{
							tabela_programa[11]--;
							}
						break;
						}
					case 12:
						{
						if (tabela_programa[13] > (tabela_programa[11] + 1))
							{
							tabela_programa[13]--;
							}
						break;
						}
					case 13:
						{
						if (tabela_programa[12] > (tabela_programa[11] + 1))
							{
							tabela_programa[12]--;
							}
						break;
						}
					case 14:
						{
						if (tabela_programa[14] > 0)
							{
							tabela_programa[14]--;
							}
						break;
						}
				#endif
				}		// fecha o switch

			if (tempo_senha != 255)
				{
				tempo_senha++;
				}
		 	}
		else
			{
			#if (st92 == true)
				if (menu_aux == 11)
					{
					if (aux_tab != 0)
						{
						if (aux_tab == 1)
							{
							aux_tab = 2;
							}
						else
							{
							aux_tab = 1;
							}
						}
					else
						{
						if (menu_aux < nro_menus4 - 1)
							{
							menu_aux++;
							}
						}
					}
				else if (menu_aux < nro_menus4 - 1)
			#else
				if (menu_aux < nro_menus4 - 1)
			#endif
				{
	 			menu_aux++;
				#if (com_regs == false)
				 	if (menu_aux == 7) 
						{
						menu_aux++;
						} 
				 	if (menu_aux == 8) 
						{
						menu_aux++;
						} 
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
			minuto_hora_ponta = 0;
			tabela_programa[1] = ten_nomi;
			tabela_programa[2] = valor_tc;
			tabela_programa[3] = valor_tp;
			tabela_programa[4] = set_point;
			tabela_programa[5] = endereco;
			tabela_programa[6] = intervalo_integra;
			#if ((st9430r == 1) || (st9230r == 1))
				tabela_programa[7] = intervalo_reg;
			#endif	
			tabela_programa[8] = forma_reg_cht;
			tabela_programa[9] = 0;
			for (x = 0; x < (NRO_POSI_BAUD - 1); x++)
				{
				if (baud_rate == tabela_baud[x])
					{
					tabela_programa[9] = x;
					}
				}
			tabela_programa[10] = tipo_ligacao;
			tabela_programa[11] = hora_ponta;
			tabela_programa[12] = hora_final_ponta;
			tabela_programa[13] = minuto_ponta;
			tabela_programa[14] = minuto_final_ponta;
			}
		else
			{
			if (aux_tab == 0)
				{
				menu_aux = 0;
				M1_C4 = 0;
				menu_aux = 0;
				menu1 = 4;
				exibe_menu();
				MENU_FIXO = 0;
				salva_menus();
				return;
				}
			else
				{
				aux_tab = 0;
				exibiu = 0;
				}
			}
		}
	exibe_programa();
}


