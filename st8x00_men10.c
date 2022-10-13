/*************************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST8610_MEN10                                                   *
; Funcao: TRATAMENTO DO MENU DE MANUTENÇÃO								 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 03/2005                                                        *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/

void exibe_manutencao(void)
{
	#if (ST8100C == true)
		if (apaga_banco == 1)
			{
			if (ja_rolou == true)
				{
				mensagem_rola(52,1);		//busca mensagem na tabela de mensagens geral
				ja_rolou = false;
				}
			}
		else
			{
			if (time_out2 == 0)
				{
				ja_rolou = true;
				}
			else
				{
				if (menu_aux < nro_bancos_capacitor)
					{
					mensagem((menu_aux + 1),2);
					}
				else
					{
					aux_tab = menu_aux - nro_bancos_capacitor;
					mensagem((aux_tab + 1),2);
					}
				}
			if (menu_aux < nro_bancos_capacitor)
				{
				if (ja_rolou == true)
					{
					binasc2(horimetro[menu_aux]);
					buf_display[0] = tabela_caracteres[buf_tmp[1] - '0'];
					buf_display[1] = tabela_caracteres[buf_tmp[2] - '0'];
					buf_display[2] = tabela_caracteres[buf_tmp[3] - '0'];
					buf_display[3] = tabela_caracteres[buf_tmp[4] - '0'];
					}
				else
					{
					buf_display[3] = tabela_caracteres[MT];
					}
				}
			else
				{
				if (ja_rolou == true)
					{
					binasc2(acionamentos[menu_aux - nro_bancos_capacitor]);
					buf_display[0] = tabela_caracteres[buf_tmp[1] - '0'];
					buf_display[1] = tabela_caracteres[buf_tmp[2] - '0'];
					buf_display[2] = tabela_caracteres[buf_tmp[3] - '0'];
					buf_display[3] = tabela_caracteres[buf_tmp[4] - '0'];
					}
				else
					{
					buf_display[3] = tabela_caracteres[MA];
					}
				}
			}
	#else
		if (apaga_banco == 1)
			{
			if (exibiu == 0)
				{
				exibiu = 1;
				mensagem(1,133);
				lcd_gotoxy(1,1);
			    wr_lcd(1,0x7F);		//escreve a seta para esquerda
				mensagem(2,132);
				}
			}
		else
			{
			#if (st8500c == true)
				if (menu_aux < nro_cargas)
					{
					if (exibiu == 0)
						{
						mensagem(1,62);
						mensagem(2,64);
						exibiu = 1;
						}
					displayp(19,horimetro[menu_aux],5,0,0);
					displayp(15,(menu_aux+1),2,0,0);
					}
				else
					{
					if (exibiu == 0)
						{
						mensagem(1,63);
						mensagem(2,65);
						exibiu = 1;
						}
					displayp(19,acionamentos[menu_aux - nro_cargas],5,0,0);
					}
			#else
				if (menu_aux < nro_bancos_capacitor)
					{
					if (exibiu == 0)
						{
						mensagem(1,62);
						mensagem(2,64);
						exibiu = 1;
						}
					displayp(19,horimetro[menu_aux],5,0,0);
					displayp(15,(menu_aux+1),2,0,0);
					}
				else
					{
					if (exibiu == 0)
						{
						mensagem(1,63);
						mensagem(2,65);
						exibiu = 1;
						}
					displayp(19,acionamentos[menu_aux - nro_bancos_capacitor],5,0,0);
					}
			#endif
			}
		#if (st8500c == true)
			if (menu_aux < nro_cargas)
				{
				displayp(15,(menu_aux+1),2,0,0);
				}
			else
				{
				aux_tab = menu_aux - nro_cargas;
				displayp(15,(aux_tab+1),2,0,0);
				}
		#else
			if (menu_aux < nro_bancos_capacitor)
				{
				displayp(15,(menu_aux+1),2,0,0);
				}
			else
				{
				aux_tab = menu_aux - nro_bancos_capacitor;
				displayp(15,(aux_tab+1),2,0,0);
				}
		#endif
	#endif
}
			
void trata_menu10(void)
{
	if (qmenu != 10)
		{
		salva_contadores();
		qmenu = 10;
		exibiu = 0;
		time_out_menus = 60;
		reset_rolar();
		menu_aux = 0;
		aux_tab = 0;
	 	apaga_banco = 0;
	 	ja_rolou = false;
	 	time_out2 = 2;
		}
	if (tecla_enter == 1)
		{
	 	tecla_enter = 0;
	 	#if (ST8100C == true)
			if (ja_rolou == false)
				{
				if (menu_aux < nro_bancos_capacitor)
					{
					if (apaga_banco == true)
						{
						apaga_banco = 0;
						minuteiro[menu_aux] = 0;
						horimetro[menu_aux] = 0;
						acionamentos[menu_aux] = 0;
						write_byte(ee_minuteiro + menu_aux, 0);
						write_word(ee_horimetro + (menu_aux * 2), 0);
						write_word(ee_acionamentos + (menu_aux * 2), 0);
						time_out2 = 2;
						}
					else
						{
						time_out2 = 0;
						}
					}
				else
					{
					if (apaga_banco == true)
						{
						apaga_banco = 0;
						aux_b1 = (menu_aux - nro_bancos_capacitor);
						minuteiro[aux_b1] = 0;
						horimetro[aux_b1] = 0;
						acionamentos[aux_b1] = 0;
						write_byte(ee_minuteiro + aux_b1, 0);
						write_word(ee_horimetro + (aux_b1 * 2), 0);
						write_word(ee_acionamentos + (aux_b1 * 2), 0);
						time_out2 = 2;
						}
					else
						{
						time_out2 = 0;
						}
					}
				}
			else
				{
				if (apaga_banco == 0)
					{
					apaga_banco = 1;
					}
				}
		#else
		 	exibiu = 0;
			if (apaga_banco == 0)
				{
				apaga_banco = 1;
				}
			else
				{
				apaga_banco = 0;
				#if (st8500c == true)
					if (menu_aux < nro_cargas)
						{
						minuteiro[menu_aux] = 0;
						horimetro[menu_aux] = 0;
						acionamentos[menu_aux] = 0;
						write_byte(ee_minuteiro + menu_aux, 0);
						write_word(ee_horimetro + (menu_aux * 2), 0);
						write_word(ee_acionamentos + (menu_aux * 2), 0);
						}
					else
						{
						aux_b1 = (menu_aux - nro_cargas);
						minuteiro[aux_b1] = 0;
						horimetro[aux_b1] = 0;
						acionamentos[aux_b1] = 0;
						write_byte(ee_minuteiro + aux_b1, 0);
						write_word(ee_horimetro + (aux_b1 * 2), 0);
						write_word(ee_acionamentos + (aux_b1 * 2), 0);
						}
				#else
					if (menu_aux < nro_bancos_capacitor)
						{
						minuteiro[menu_aux] = 0;
						horimetro[menu_aux] = 0;
						acionamentos[menu_aux] = 0;
						write_byte(ee_minuteiro + menu_aux, 0);
						write_word(ee_horimetro + (menu_aux * 2), 0);
						write_word(ee_acionamentos + (menu_aux * 2), 0);
						}
					else
						{
						aux_b1 = (menu_aux - nro_bancos_capacitor);
						minuteiro[aux_b1] = 0;
						horimetro[aux_b1] = 0;
						acionamentos[aux_b1] = 0;
						write_byte(ee_minuteiro + aux_b1, 0);
						write_word(ee_horimetro + (aux_b1 * 2), 0);
						write_word(ee_acionamentos + (aux_b1 * 2), 0);
						}
				#endif
				}
		#endif
		}		
	else if (tecla_up == 1)
		{
		tecla_up = 0;
		exibiu = 0;
		ja_rolou = false;
	 	time_out2 = 2;
		if (menu_aux > 0)
			{
			menu_aux--;
			}
		}
	else if (tecla_down == 1)
		{
		tecla_down = 0;
		exibiu = 0;
		ja_rolou = false;
	 	time_out2 = 2;
	 	#if (st8500c == true)
			if (menu_aux < ((nro_cargas * 2)-1))
				{
				menu_aux++;
				}
	 	#else
			if (menu_aux < ((nro_bancos_capacitor * 2)-1))
				{
				menu_aux++;
				}
		#endif
		}
	else if (tecla_reset == 1)
		{
		tecla_reset = 0;
		exibiu = 0;
		ja_rolou = false;
		if (apaga_banco == 1)
			{
			apaga_banco = 0;
			}
		else
			{
			menu_aux = 1;
			menu1 = 10;
			qmenu = 0;
			exibe_menu();
			return;
			}
		}
	exibe_manutencao();
}
