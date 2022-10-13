/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST8610_MEN6                                                    *
; Funcao: TRATAMENTO DO MENU DE PROGRAMAÇAO DE ALARMES					 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */
  
void trata_menu6(void);
void exibe_alarmes(void);
void salva_alarmes(void);
//void exibe_off(void);
//void valida_programa(void);


void trata_menu6(void)
{
	if (qmenu != 6)
		{
		qmenu = 6;
		exibiu = 0;
		#if (st8500c == true)
			tabela_programa[1] = ala_fp_ind;
			tabela_programa[2] = ala_fp_cap;
			tabela_programa[3] = ala_ten_a;
			tabela_programa[4] = ala_ten_b;
			tabela_programa[5] = ala_demanda_ativa;
		#else
			tabela_programa[1] = ala_fp_ind;
			tabela_programa[2] = ala_fp_cap;
			tabela_programa[3] = ala_ten_a;
			tabela_programa[4] = ala_ten_b;
			tabela_programa[5] = ala_sc;
			tabela_programa[6] = ala_subc;
			tabela_programa[7] = ala_chtt;
			tabela_programa[8] = ala_chtc;
		#endif
		time_out_menus = 60;
		ja_rolou = false;
		rolando = false;
		exibe_alarmes();
		return;
		}
		
	if (tecla_enter == 1)
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
				salva_alarmes();
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
	else if (tecla_up == 1)
		{
		tecla_up = 0;
		exibiu = 0;
		if (programando == 1)
			{
			tempo_senha = 255;
			switch(menu_aux)
				{
				case 1:					//FP Indutivo e Capacitivo
				case 2:
					{
				 	if (tabela_programa[menu_aux] < 100)
				 		{
						tabela_programa[menu_aux]++;
						}
					break;
		 			}
		 		case 3:					//Sobretensão
			 		{
				 	if (tabela_programa[3] < 20)
				 		{
						tabela_programa[3]++;
						}
					break;
				 	}
				 case 4:			//Subtensão
			 		{
				 	if (tabela_programa[4] < 30)
				 		{
						tabela_programa[4]++;
						}
					break;
			 		}
		 		case 5:							//Sobrecorrente
			 		{
				 	#if (st8500c == true)
					 	if (tabela_programa[5] < 20)
					 		{
							tabela_programa[5]++;
							}
				 	#else
					 	if (tabela_programa[5] < 150)
					 		{
							tabela_programa[5]++;
							}
					#endif
					break;
					}
				#if ((st8100c == true) || (st8200c == true) || (st8300c == true))
				 	case 6:							//Subcorrente
				 		{
					 	if (tabela_programa[6] < 20)
					 		{
							tabela_programa[6]++;
							}
						break;
						}
		 			default:											//Conteúdo Harmônico de Tensão
		 				{
					 	if (tabela_programa[menu_aux] < 50)
					 		{
							tabela_programa[menu_aux]++;
							}
						}
				#endif
				}
		 	}
		else
			{
		 	if (menu_aux > 0)
		 		{
 				menu_aux--;
				ja_rolou = false;
				rolando = false;
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
		 	if ((menu_aux == 1) || (menu_aux == 2))
		 		{
			 	if (tabela_programa[menu_aux] > 80)
			 		{
					tabela_programa[menu_aux]--;
					}
				}
		 	else
		 		{
			 	if (tabela_programa[menu_aux] > 0)
			 		{
					tabela_programa[menu_aux]--;
					}
				}
		 	}
		else
			{
			#if (st8500c == true)
				 if (menu_aux < nro_menus6)
			#else
				 if (menu_aux < nro_menus5)
			#endif
		 		{
	 			menu_aux++;
				reset_rolar();
	 			}
	 		}
		}
	else if (tecla_reset == 1)
		{
		tecla_reset = 0;
		reset_rolar();
		if (programando == 1)
			{
			programando = 0;
			tabela_programa[1] = ala_fp_ind;
			tabela_programa[2] = ala_fp_cap;
			tabela_programa[3] = ala_ten_a;
			tabela_programa[4] = ala_ten_b;
			#if (st8500c == true)
				tabela_programa[5] = ala_demanda_ativa;
			#else
				tabela_programa[5] = ala_sc;
				tabela_programa[6] = ala_subc;
				tabela_programa[7] = ala_chtt;
				tabela_programa[8] = ala_chtc;
			#endif
			}
		else
			{
			menu_aux = 0;
			menu1 = 6;
			qmenu = 0;
			exibe_menu();
			return;
			}
		}
	exibe_alarmes();
}


void salva_alarmes(void)
{
	ala_fp_ind = tabela_programa[1];
	ala_fp_cap = tabela_programa[2];
	ala_ten_a = tabela_programa[3];
	ala_ten_b = tabela_programa[4];
	#if (st8500c == true)
		ala_demanda_ativa = tabela_programa[5];
	#else
		ala_sc = tabela_programa[5];
		ala_subc = tabela_programa[6];
		ala_chtt = tabela_programa[7];
		ala_chtc = tabela_programa[8];
	#endif

	salva_programa();
	valida_programa();
 	exibe_alarmes();
}


void exibe_alarmes(void)
{
	char x;
	x = 38;
	#if (ST8100C == true)
		switch (menu_aux)
			{
			case 0:
				{
				menu_aux = 1;
				break;
				}
			default:
				{
				if (ja_rolou == true)
					{
					rolando = false;
					}
				else
					{
					if (rolando == false)
						{
						mensagem_rola((x + menu_aux),1);
						}
					}
				break;						
				}
			}
	
		if (ja_rolou == true)
			{
			if ((menu_aux == 1) || (menu_aux == 2))
				{
				if (tabela_programa[menu_aux] == 100)
					{
					exibe_off();
					}
				else
					{
					binasc2(tabela_programa[menu_aux]);
					buf_display[0] = tabela_caracteres[MESPACO];
					buf_display[1] = tabela_caracteres[M0] | 0x80;
					buf_display[2] = tabela_caracteres[buf_tmp[3] - '0'];
					buf_display[3] = tabela_caracteres[buf_tmp[4] - '0'];
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
	
		pisca_pontos();
	#else
		switch (menu_aux)
			{
			case 1:
				{
				if (exibiu == 0)
					{
					exibiu = 1;
					mensagem (2,41);
					}
				if (tabela_programa[1] > 99 )
					{
					exibe_off(29);
					}
				else
					{
					displayd(29,tabela_programa[1],'P');
					}
				break;
				}
			case 2:
				{
				if (exibiu == 0)
					{
					exibiu = 1;
					mensagem (2,42);
					}
				if (tabela_programa[2] > 99 )
					{
					exibe_off(29);
					}
				else
					{
					displayd(29,tabela_programa[2],'P');
					}
				break;
				}
			case 3:
				{
				if (exibiu == 0)
					{
					exibiu = 1;
					mensagem (2,43);
					}
				if (tabela_programa[3] == 0)
					{
					exibe_off(29);
					}
				else
					{
					displayp(30,tabela_programa[3],2,0,'P');
					}
				break;
				}
			case 4:
				{
				if (exibiu == 0)
					{
					exibiu = 1;
					mensagem (2,44);
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
			#if (st8500c == true)
				case 5:
					{
					if (exibiu == 0)
						{
						exibiu = 1;
						mensagem (2,21);
						}
					if (tabela_programa[5] == 0)
						{
						exibe_off(28);
						wr_lcd(1,' ');
						}
					else
						{
						displayp(30,tabela_programa[5],2,0,'P');
						}
					break;
					}
			#else
				case 5:
					{
					if (exibiu == 0)
						{
						exibiu = 1;
						mensagem (2,45);
						}
					if (tabela_programa[5] == 0)
						{
						exibe_off(29);
						}
					else
						{
						displayp(29,tabela_programa[5],3,0,'P');
						}
					break;
					}
			#endif
			#if ((st8100c == true) || (st8200c == true) || (st8300c == true))
				case 6:
					{
					if (exibiu == 0)
						{
						exibiu = 1;
						mensagem (2,46);
						}
					if (tabela_programa[6] == 0)
						{
						exibe_off(29);
						}
					else
						{
						displayp(29,tabela_programa[6],3,0,'P');
						}
					break;
					}
				case 7:
					{
					if (exibiu == 0)
						{
						exibiu = 1;
						mensagem (2,47);
						}
					if (tabela_programa[7] == 0)
						{
						exibe_off(29);
						}
					else
						{
						displayp(30,tabela_programa[7],2,0,'P');
						}
					break;
					}
				case 8:
					{
					if (exibiu == 0)
						{
						exibiu = 1;
						mensagem (2,48);
						}
					if (tabela_programa[8] == 0)
						{
						exibe_off(29);
						}
					else
						{
						displayp(30,tabela_programa[8],2,0,'P');
						}
					break;
					}
			#endif
			default:
				{
				menu_aux = 1;
				break;
				}
			}
	#endif
}
