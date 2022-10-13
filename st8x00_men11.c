/*************************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST8610_MEN11                                                   *
; Funcao: TRATAMENTO DO MENU DE AJUSTE DO RELÓGIO						 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 29/03/2005                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;************************************************************************/
void salva_relogio (void);


void exibe_relogio (void)
{
	#if (ST8100C == true)
		if (time_out2 == 0)
			{
			ja_rolou = true;
			}
		if (menu_aux == 1)
			{
			if (aux_tab == 0)
				{
				if (ja_rolou == true)
					{
					rolando = false;
					binasc2(tabela_programa[1]);
					buf_display[0] = tabela_caracteres[MESPACO];
					buf_display[1] = tabela_caracteres[MESPACO];
					buf_display[2] = tabela_caracteres[buf_tmp[3] - '0'];
					buf_display[3] = tabela_caracteres[buf_tmp[4] - '0'];
					}
				else if (rolando == false)
					{
					buf_display[0] = tabela_caracteres[MESPACO];
					buf_display[1] = tabela_caracteres[MD];
					buf_display[2] = tabela_caracteres[MI];
					buf_display[3] = tabela_caracteres[MA];
					}
				}
			else if (aux_tab == 1)
				{
				if (ja_rolou == true)
					{
					rolando = false;
					binasc2(tabela_programa[2]);
					buf_display[0] = tabela_caracteres[MESPACO];
					buf_display[1] = tabela_caracteres[MESPACO];
					buf_display[2] = tabela_caracteres[buf_tmp[3] - '0'];
					buf_display[3] = tabela_caracteres[buf_tmp[4] - '0'];
					}
				else if (rolando == false)
					{
					buf_display[0] = tabela_caracteres[MESPACO];
					buf_display[1] = tabela_caracteres[MM];
					buf_display[2] = tabela_caracteres[ME];
					buf_display[3] = tabela_caracteres[MS];
					}
				}
			else if (aux_tab == 2)
				{
				if (ja_rolou == true)
					{
					rolando = false;
					binasc2(tabela_programa[3]);
					buf_display[0] = tabela_caracteres[MESPACO];
					buf_display[1] = tabela_caracteres[MESPACO];
					buf_display[2] = tabela_caracteres[buf_tmp[3] - '0'];
					buf_display[3] = tabela_caracteres[buf_tmp[4] - '0'];
					}
				else if (rolando == false)
					{
					buf_display[0] = tabela_caracteres[MESPACO];
					buf_display[1] = tabela_caracteres[MA];
					buf_display[2] = tabela_caracteres[MN];
					buf_display[3] = tabela_caracteres[MO];
					}
				}
			}
		else
			{
			if (aux_tab == 0)
				{
				if (ja_rolou == true)
					{
					rolando = false;
					binasc2(tabela_programa[4]);
					buf_display[0] = tabela_caracteres[MESPACO];
					buf_display[1] = tabela_caracteres[MESPACO];
					buf_display[2] = tabela_caracteres[buf_tmp[3] - '0'];
					buf_display[3] = tabela_caracteres[buf_tmp[4] - '0'];
					}
				else if (rolando == false)
					{
					buf_display[0] = tabela_caracteres[MH];
					buf_display[1] = tabela_caracteres[MO];
					buf_display[2] = tabela_caracteres[MR];
					buf_display[3] = tabela_caracteres[MA];
					}
				}
			else if (aux_tab == 1)
				{
				if (ja_rolou == true)
					{
					rolando = false;
					binasc2(tabela_programa[5]);
					buf_display[0] = tabela_caracteres[MESPACO];
					buf_display[1] = tabela_caracteres[MESPACO];
					buf_display[2] = tabela_caracteres[buf_tmp[3] - '0'];
					buf_display[3] = tabela_caracteres[buf_tmp[4] - '0'];
					}
				else if (rolando == false)
					{
					buf_display[0] = tabela_caracteres[MM];
					buf_display[1] = tabela_caracteres[MI];
					buf_display[2] = tabela_caracteres[MN];
					buf_display[3] = tabela_caracteres[MU];
					}
				}
			}
		pisca_pontos();
	#else
		if (menu_aux == 1)
			{
			if (exibiu == 0)
				{
				mensagem (2,124);
				exibiu = 1;
				}
			if (programando == 1)
				{
				if (aux_tab == 0)
					{
					displayp (24,tabela_programa[1],2,0,'P');	//dia
					displayp (27,tabela_programa[2],2,0,0);		//mes
					displayp (30,tabela_programa[3],2,0,0);		//ano
					}
				else if (aux_tab == 1)
					{
					displayp (24,tabela_programa[1],2,0,0);		//dia
					displayp (27,tabela_programa[2],2,0,'P');	//mes
					displayp (30,tabela_programa[3],2,0,0);		//ano
					}
				else if (aux_tab == 2)
					{
					displayp (24,tabela_programa[1],2,0,0);		//dia
					displayp (27,tabela_programa[2],2,0,0);		//mes
					displayp (30,tabela_programa[3],2,0,'P');	//ano
					}
				}
			else
				{
				displayp (24,tabela_programa[1],2,0,0);		//dia
				displayp (27,tabela_programa[2],2,0,0);		//mês
				displayp (30,tabela_programa[3],2,0,0);		//ano
				}
			}
		else
			{
			if (exibiu == 0)
				{
				mensagem (2,125);
				exibiu = 1;
				}
			if (programando == 1)
				{
				if (aux_tab == 0)
					{
					displayp (26,tabela_programa[4],2,0,'P');		//hora
					displayp (29,tabela_programa[5],2,0,0);		//minuto
					}
				else if (aux_tab == 1)
					{
					displayp (26,tabela_programa[4],2,0,0);		//hora
					displayp (29,tabela_programa[5],2,0,'P');		//minuto
					}
				}
			else
				{
				displayp (26,tabela_programa[4],2,0,0);		//hora
				displayp (29,tabela_programa[5],2,0,0);		//minuto
				}
			}
	#endif
}
	

void trata_menu11(void)
{
	if (qmenu != 11)
		{
		qmenu = 11;
		exibiu = 0;
		menu_aux = 1;
		aux_tab = 0;
		time_out_menus = 60;
		reset_rolar();
	 	time_out2 = 2;

		tabela_programa[1] = dia;			//dia;
		tabela_programa[2] = mes;			//mes;
		tabela_programa[3] = ano;			//ano;
		tabela_programa[4] = hora;			//hora;
		tabela_programa[5] = minuto;		//minuto;
		
		}
	else if (tecla_enter == 1)
		{
	 	tecla_enter = 0;
		exibiu = 0;
		if (programando == 1)
			{
			#if (ST8100C == true)
				programando = 0;
				salva_relogio();
				reset_rolar();
			 	time_out2 = 2;
			#else
				if (menu_aux == 1)
					{
					if (aux_tab == 2)
						{
						programando = 0;
						salva_relogio();
						aux_tab = 0;
						}
					else
						{
						aux_tab++;
						}
					}
				else
					{
					if (aux_tab == 1)
						{
						programando = 0;
						salva_relogio();
						aux_tab = 0;
						}
					else
						{
						aux_tab++;
						}
					}
			#endif
			}
		else
			{
			#if (ST8100C == true)
				if (time_out2 != 0)
					{
					ja_rolou = true;
					}
				else
					{
					if (tempo_senha != 0)
						{
						programando = 1;
						}
					else
						{
						trata_senha();
						return;
						}
					}
			#else
				if (tempo_senha != 0)
					{
					programando = 1;
					}
				else
					{
					trata_senha();
					return;
					}
			#endif
			}
		}		
	else if (tecla_up == 1)
		{
		tecla_up = 0;
		exibiu = 0;
		ja_rolou = false;
	 	time_out2 = 2;
		if (programando == 1)
			{
			tempo_senha = 255;
			switch (menu_aux)
				{
				case 1:
					{
					if (aux_tab == 0)
						{
						if (tabela_programa[1] < 31)
							{
							tabela_programa[1]++;
							}
						}
					else if (aux_tab == 1)
						{
						if (tabela_programa[2] < 12)
							{
							tabela_programa[2]++;
							}
						}
					else if (aux_tab == 2)
						{
						if (tabela_programa[2] < 99)
							{
							tabela_programa[3]++;
							}
						}
					break;
					}
				case 2:
					{
					if (aux_tab == 0)
						{
						if (tabela_programa[4] < 23)
							{
							tabela_programa[4]++;
							}
						}
					else if (aux_tab == 1)
						{
						if (tabela_programa[5] < 59)
							{
							tabela_programa[5]++;
							}
						}
					break;
					}
				default:
					{
					menu_aux = 1;
					}
				}
		 	}
		else
			{
		 	#if (ST8100C == true)
		 		if (menu_aux == 2)
		 			{
			 		if (aux_tab > 0)
			 			{
				 		aux_tab--;
				 		}
				 	else
				 		{
					 	menu_aux--;
					 	aux_tab = 2;
					 	}
			 		}
			 	else
			 		{
				 	if (aux_tab > 0)
				 		{
					 	aux_tab--;
					 	}
				 	}
		 	#else
			 	if (menu_aux > 1)
		 			{
					menu_aux--;
					reset_rolar();
		 			}
	 		#endif
		 	}
		}
	else if (tecla_down == 1)
		{
		tecla_down = 0;
		exibiu = 0;
		ja_rolou = false;
	 	time_out2 = 2;
		if (programando == 1)
	 		{
			tempo_senha = 255;
			switch (menu_aux)
				{
				case 1:
					{
					if (aux_tab == 0)
						{
						if (tabela_programa[1] > 1)
							{
							tabela_programa[1]--;
							}
						}
					else if (aux_tab == 1)
						{
						if (tabela_programa[2] > 1)
							{
							tabela_programa[2]--;
							}
						}
					else if (aux_tab == 2)
						{
						if (tabela_programa[3] > 0)
							{
							tabela_programa[3]--;
							}
						}
					break;
					}
				case 2:
					{
					if (aux_tab == 0)
						{
						if (tabela_programa[4] > 0)
							{
							tabela_programa[4]--;
							}
						}
					else if (aux_tab == 1)
						{
						if (tabela_programa[5] > 0)
							{
							tabela_programa[5]--;
							}
						}
					break;
					}
				default:
					{
					menu_aux = 1;
					}
				}
			}
		 else
		 	{
		 	#if (ST8100C == true)
		 		if (menu_aux == 1)
		 			{
			 		if (aux_tab < 2)
			 			{
				 		aux_tab++;
				 		}
				 	else
				 		{
					 	menu_aux++;
					 	aux_tab = 0;
					 	}
			 		}
			 	else
			 		{
				 	if (aux_tab < 1)
				 		{
					 	aux_tab++;
					 	}
				 	}
		 	#else
				if (menu_aux < nro_menus11)
			 		{
					menu_aux++;
					reset_rolar();
		 			}
		 	#endif
	 		}
		}
	else if (tecla_reset==1)
		{
		tecla_reset = 0;
		reset_rolar();
	 	time_out2 = 2;
		if (programando == 1)
			{
			programando = 0;
			tabela_programa[1] = dia;
			tabela_programa[2] = mes;
			tabela_programa[3] = ano;
			tabela_programa[4] = hora;
			tabela_programa[5] = minuto;
			}
		else
			{
			menu_aux = 0;
			menu1 = 11;
			qmenu = 0;
			exibe_menu();
			return;
			}
		}
	exibe_relogio();
}

void salva_relogio (void)
{
	dia = tabela_programa[1];
	mes = tabela_programa[2];
	ano = tabela_programa[3];
	hora = tabela_programa[4];
	minuto = tabela_programa[5];

	if ((ano % 4) == 0)
		{
		if (mes == 2)
			{
			if (dia > 29)
				{
				dia = 1;
				}
			}
		else
			{
			if (dia > 31)
				{
				dia = 1;
				}
			}
		}
	else
		{
		if (mes == 2)
			{
			if (dia > 28)
				{
				dia = 1;
				}
			}
		else
			{
			if (dia > 31)
				{
				dia = 1;
				}
			}
		}
	if (mes > 12)
		{
		mes = 1;
		}
	if (ano > 99)
		{
		ano = 1;
		}
	if (hora > 23)
		{
		hora = 1;
		}
	if (minuto > 59)
		{
		minuto = 1;
		}
	
	ajuste_relogio = 0;

	#if (com_relogio == true)
		data_modbus = data1_int;
		rtc_set_datetime();
	#else
		data_modbus = data1_int;
		rtc_wr_e2p();
	#endif

	tabela_programa[1] = dia;
	tabela_programa[2] = mes;
	tabela_programa[3] = ano;
	tabela_programa[4] = hora;
	tabela_programa[5] = minuto;

	exibe_data_hora();
}

void exibe_data_hora(void)
{
	#if ((st8200c == true) || (st8300c == true) || ( st8500c == true))
		mensagem(2,60);
		displayp(18,dia,2,0,0);
		displayp(21,mes,2,0,0);
		displayp(24,ano,2,0,0);
		displayp(27,hora,2,0,0);
		displayp(30,minuto,2,0,0);
	#endif
}
