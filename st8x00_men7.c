/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST8610_MEN7                                                    *
; Funcao: TRATAMENTO DO MENU DE DESLIGAMENTOS							 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/
  
void trata_menu7(void);
void exibe_desliga(void);
void salva_desliga(void);
//void exibe_off(void);
//void valida_programa(void);



void trata_menu7(void)
	{
	aux_set_point = 98 + (100 - set_point) ;
		
	if (qmenu != 7)
		{
		qmenu = 7;
		exibiu = 0;
		tabela_programa[1] = com_des_fp_ind_cap;
		tabela_programa[2] = com_des_ten_a;
		tabela_programa[3] = com_des_ten_b;
		tabela_programa[4] = com_des_chtt;
		tabela_programa[5] = com_des_chtc;
		time_out_menus = 60;
		reset_rolar();
		
		}
	else if (tecla_enter == 1)
		{
	 	#if ((st8200c == true) || (st8300c == true) || (st8500c == true))
	 		ja_rolou = true;
			rolando = false;
	 	#endif
	 	
	 	tecla_enter = 0;
	 	exibiu = 0;
		if (ja_rolou == false)
			{
			ja_rolou = true;
			rolando = false;
			}
		else
			{
			exibir_menu = 1;
			if (programando == 1)
				{
				programando = 0;
				salva_desliga();
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
			}
		}		
	if (tecla_up == 1)
		{
		tecla_up = 0;
		exibiu = 0;
		if (programando == 1)
			{
			tempo_senha = 255;
			switch (menu_aux)
				{
				case 1:
					{
					if (tabela_programa[1] > 80)
						{
						tabela_programa[1]--;
						}
					break;
					}
				case 2:
					{
					if (tabela_programa[2] < 25)
						{
						tabela_programa[2]++;
						}
					break;
					}
				case 3:
					{
					if (tabela_programa[3] < 50)
						{
						tabela_programa[3]++;
						}
					break;
					}
				case 4:
				case 5:
					{
					if (tabela_programa[menu_aux] < 50)
						{
						tabela_programa[menu_aux]++;
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
		 	if (menu_aux > 1)
		 		{
 				menu_aux--;
				reset_rolar();
		 		}
		 	}
		 }
	else if (tecla_down == 1)
		{
		tecla_down = 0;
		exibiu = 0;
		if (programando == 1)
		 	{
			tempo_senha = 255;
			switch (menu_aux)
				{
				case 1:
					{
					if (tabela_programa[1] < aux_set_point)
						{
						tabela_programa[1]++;
						}
					break;
					}
				case 2:
				case 3:
				case 4:
				case 5:
					{
					if (tabela_programa[menu_aux] > 0)
						{
						tabela_programa[menu_aux]--;
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
			 if (menu_aux < nro_menus7)
		 		{
	 			menu_aux++;
				reset_rolar();
	 			}
	 		}
		}
	else if (tecla_reset == 1)
		{
		menu_aux = 0;
		tecla_reset=0;
		qmenu=0;
		reset_rolar();
		if (programando == 1)
			{
			programando = 0;
			tabela_programa[1] = com_des_fp_ind_cap;
			tabela_programa[2] = com_des_ten_a;
			tabela_programa[3] = com_des_ten_b;
			tabela_programa[4] = com_des_chtt;
			tabela_programa[5] = com_des_chtc;
			}
		else
			{
			menu_aux = 1;
			menu1 = 7;
			qmenu = 0;
			exibe_menu();
			return;
			}
		}
	exibe_desliga();
	}


void salva_desliga(void)
	{
	com_des_fp_ind_cap = tabela_programa[1];
	com_des_ten_a =	tabela_programa[2];
	com_des_ten_b =	tabela_programa[3];
	com_des_chtt = tabela_programa[4];
	com_des_chtc = tabela_programa[5];

	salva_programa();
	valida_programa();
 	exibe_desliga();
	}


void exibe_desliga(void)
{
	#if (ST8100C == true)
 		switch (menu_aux)
			{
			case 0:
				{
				menu_aux = 1;
				break;
				}
			case 1:
				{
				if (ja_rolou == true)
					{
					rolando = false;
					}
				else
					{
					if (rolando == false)
						{
						mensagem_rola(73,1);
						}
					}
				break;			
				}
			case 2:
				{
				if (ja_rolou == true)
					{
					rolando = false;
					}
				else
					{
					if (rolando == false)
						{
						mensagem_rola(41,1);
						}
					}
				break;						
				}
			case 3:
				{
				if (ja_rolou == true)
					{
					rolando = false;
					}
				else
					{
					if (rolando == false)
						{
						mensagem_rola(42,1);
						}
					}
				break;						
				}
			case 4:
				{
				if (ja_rolou == true)
					{
					rolando = false;
					}
				else
					{
					if (rolando == false)
						{
						mensagem_rola(45,1);
						}
					}
				break;						
				}
			case 5:
				{
				if (ja_rolou == true)
					{
					rolando = false;
					}
				else
					{
					if (rolando == false)
						{
						mensagem_rola(46,1);
						}
					}
				break;						
				}
			default:
				{
				menu_aux = 1;
				}
			}
		if (ja_rolou == true)
			{
			if (menu_aux == 1)
				{
				if (tabela_programa[1] > 100)
					{
					binasc2((100 - (tabela_programa[1]-100)));
					buf_display[0] = tabela_caracteres[MI];
					buf_display[1] = tabela_caracteres[M0] | 0x80;
					buf_display[2] = tabela_caracteres[buf_tmp[3] - '0'];
					buf_display[3] = tabela_caracteres[buf_tmp[4] - '0'];
					}
				else if (tabela_programa[1] < 100)
					{
					binasc2(tabela_programa[1]);
					buf_display[0] = tabela_caracteres[MC];
					buf_display[1] = tabela_caracteres[M0] | 0x80;
					buf_display[2] = tabela_caracteres[buf_tmp[3] - '0'];
					buf_display[3] = tabela_caracteres[buf_tmp[4] - '0'];
					}
				else
					{
					buf_display[0] = tabela_caracteres[MESPACO];
					buf_display[1] = tabela_caracteres[1];
					buf_display[2] = tabela_caracteres[0];
					buf_display[3] = tabela_caracteres[0];
					}
				}
			else
				{
				if (tabela_programa[menu_aux] == 0)
					{
					exibe_off();
					}
				else
					{
					binasc2(tabela_programa[menu_aux]);
					buf_display[0] = tabela_caracteres[MESPACO];
					buf_display[1] = tabela_caracteres[buf_tmp[2] - '0'];
					buf_display[2] = tabela_caracteres[buf_tmp[3] - '0'];
					buf_display[3] = tabela_caracteres[buf_tmp[4] - '0'];
					}
				}
			}
	
		if (programando == 1)
			{
			if (ponto_segundo == 1)
				{
				buf_display[0] = buf_display[0] | 0x80;
				buf_display[1] = buf_display[1] | 0x80;
				buf_display[2] = buf_display[2] | 0x80;
				buf_display[3] = buf_display[3] | 0x80;
				}
			}
	#else
		switch (menu_aux)
			{
			case 1:
				{
				if (exibiu == 0)
					{
					exibiu = 1;
					if (tabela_programa[1] > 100)
						{
						mensagem (2,41);
						}
					else if (tabela_programa[1] < 100)
						{
						mensagem (2,42);
						}
					else
						{
						#if (monofasico == true)
							mensagem (2,154);
						#else
							mensagem (2,155);
						#endif
						}
					}
				if (tabela_programa[1] > 100)
					{
					displayd (29,(100 - (tabela_programa[1]-100)),'P');
					}
				else if (tabela_programa[1] < 100)
					{
					displayd (29,tabela_programa[1],'P');
					}
				else
					{
					if (programando == true)
						{
						if (piscar == true)
							{
							lcd_gotoxy(13, 2);		// x1 - posicao, y1, linha
							wr_lcd(1, ' ');
							wr_lcd(1, '.');
							wr_lcd(1, ' ');
							wr_lcd(1, ' ');
							}
						else
							{
							#if (monofasico == true)
								mensagem (2,154);
							#else
								mensagem (2,155);
							#endif
							}
						}
					}
				break;
				}
			case 2:
			case 3:
				{
				if (exibiu == 0)
					{
					exibiu = 1;
					if (menu_aux == 2)
						{
						mensagem (2,43);
						}
					else
						{
						mensagem (2,44);
						}
					}
				if (tabela_programa[menu_aux] == 0)
					{
					exibe_off(29);
					}
				else
					{
					displayp(30,tabela_programa[menu_aux],2,0,'P');
					}
				break;
				}
			case 4:
				{
				if (exibiu == 0)
					{
					exibiu = 1;
					mensagem (2,47);
					}
				if (tabela_programa[4] == 0)
					{
					exibe_off(29);
					}
				else
					{
					displayp(30,tabela_programa[4],2,0,'P');
					}
				break;
				}
			case 5:
				{
				if (exibiu == 0)
					{
					exibiu = 1;
					mensagem (2,48);
					}
				if (tabela_programa[5] == 0)
					{
					exibe_off(29);
					}
				else
					{
					displayp(30,tabela_programa[5],2,0,'P');
					}
				break;
				}
			default:
				{
				menu_aux = 1;
				}
			}
	#endif
}
