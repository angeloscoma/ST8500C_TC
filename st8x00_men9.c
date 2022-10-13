/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST8610_MEN9                                                    *
; Funcao: TRATAMENTO DO MENU DE OCORRÊNCIAS								 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/
#if ((st8500c == true) || (ST8200C == true) || (ST8300C == true))
	char ult_posi_ocor;
#endif
short prog_apaga;
short existe_ocor;
void exibe_ocorrencia(void);


void trata_menu9(void)
{
	if (qmenu != 9)
		{
		qmenu = 9;
		limpa_ocor = 0;
		prog_apaga = 0;
		#if ((st8500c == true) || (ST8200C == true) || (ST8300C == true))
			// ler posicao da ultima ocorrencia	
			aux_w1 = 0;	
			#if (com_relogio == true)
				aux_w1 =  read_word_nvr(ds_ptr_ocor);
			#else
				aux_w1 =  read_word(ee_ptr_rocor);
			#endif
			if (aux_w1 > limite_ocorrencias)
				{
				aux_w1 = 0;
				}
			if (aux_w1 != 0)
				{
				aux_w1--;
				}
			menu_aux = aux_w1;
			ult_posi_ocor = menu_aux;
		#else
			menu_aux = read_byte(ee_ptr_ocor);
			if (menu_aux > 99)
				{
				menu_aux = 0;
				write_byte(ee_ptr_ocor,0);
				}
			menu_aux = 1;
			em_status = false;
			reset_rolar();
		#endif
		exibiu = 0;
		time_out_menus = 60;
		}
		
	if (tecla_enter == 1)
		{
	 	tecla_enter = 0;
		exibiu = 0;
		#if ((st8500c == true) || (ST8200C == true) || (ST8300C == true))
			menu_aux = ult_posi_ocor;
		#else
			menu_aux = read_byte(ee_ptr_ocor);
		#endif
		if (tempo_senha == 0)
			{
			trata_senha();
			return;
			}
		else
			{
			#if (ST8100C == true)
				if (prog_apaga == 0)
					{
					prog_apaga = 1;
					limpa_ocor = 1;
					if (rolando == true)
						{
						rolando = false;
						ja_rolou = true;
						return;
						}
					}
				else
					{
					limpa_ocor = 0;
					prog_apaga = 0;
					apaga_ocorrencias();
					rolando = false;
					ja_rolou = false;
					}
			#else
				if (limpa_ocor == 1)
					{
					limpa_ocor = 0;
					#if (com_regs == true)
						apaga_ocorrencias();
					#endif
					goto tec_reset_menu9;
					}
				else
					{
					limpa_ocor = 1;
					}
			#endif
			}
		}

	if (tecla_reset == 1)
		{
tec_reset_menu9:
		prog_apaga = 0;
		tecla_reset = 0;
		exibiu = 0;
		if (limpa_ocor == 1)
			{
			limpa_ocor = 0;
			}
		else
			{
			menu_aux = 1;
			menu1 = 9;
			qmenu = 0;
			exibe_menu();
			}
		return;
		}

	if (tecla_up == 1)
		{
		tecla_up = 0;
		exibiu = 0;
		#if ((st8500c == true) || (ST8200C == true) || (ST8300C == true))
			if (menu_aux < limite_ocorrencias)
				{
				menu_aux++;
				}
			else
				{
				menu_aux = 0;
				}
		#else		
			if (menu_aux < read_byte(ee_ptr_ocor))
				{
				menu_aux++;
				#if (ST8100C == true)
					rolando = false;
				#endif
				}
		#endif
		}

	if (tecla_down == 1)
		{
		tecla_down = 0;
		exibiu = 0;
		if (menu_aux > 0)
			{
			menu_aux--;
			#if (ST8100C == true)
				rolando = false;
			#endif
			}
		#if ((st8500c == true) || (ST8200C == true) || (ST8300C == true))
			else
				{
				menu_aux = limite_ocorrencias;
				}
		#endif
		}

	exibe_ocorrencia();
}

void exibe_ocorrencia(void)
{
	#if (ST8100C == true)
		if (limpa_ocor == 1)
			{
			if (rolando == false)
				{
				mensagem_rola(52,1);		//busca mensagem na tabela de mensagens geral
				}
			}
		else
			{
			aux_b1 = read_byte(ee_ocorrencias + menu_aux);
			if (aux_b1 > limite_ocorrencias)
				{
				if (rolando == false)
					{
					mensagem_rola(1,0);
					}
				}
			else
				{
				if (rolando == false)
					{
					mensagem_rola(aux_b1,0);		//busca mensagem na tabela de erros
					}
				}
			}
	#else
		#if ((st8500c == true) || (ST8200C == true) || (ST8300C == true))
			#if (com_regs == true)
				if (exibiu == 0)
					{
					exibiu = 1;
					if (limpa_ocor == 1)
						{
						mensagem(1,131);
						lcd_gotoxy(2,1);
					    wr_lcd(1,0x7F);		//escreve a seta para esquerda
						mensagem(2,132);
						}
					else
						{
						// apontar para posicao de ocorrencia na flash
						// ler da Flash a ocorrencia
						// se codigo for 255, avançar até encontrar um código válido, se rodar 255 posiçoes, avisa final de ocorrencias
						existe_ocor = false;
						for (aux_b1 = menu_aux; aux_b1 < 250; aux_b1++)
							{
							aux_l2 = aux_b1;
							aux_l1 = inicio_ocorrencias;
							aux_l1 = aux_l1 + (int32)(aux_l2 * TAM_REGS);
							aux_b2 = read_byte_flash(aux_l1); 
							if (aux_b2 != 0xff)
								{
								if (aux_b2 < nro_tab_ocor)
									{
									aux_l1++;
									// Le dia e hora
									dia_old = read_byte_flash(aux_l1++);
									mes_old = read_byte_flash(aux_l1++);
									ano_old = read_byte_flash(aux_l1++);
									hora_old = read_byte_flash(aux_l1++);
									minuto_old = read_byte_flash(aux_l1);
									if (dia_old < 32)
										{
										if (mes_old < 13)
											{
											if (hora_old < 24)
												{
												if (minuto_old < 60)
													{
													existe_ocor = true;
													break;
													}
												}
											}
										}
									}
								}
							}
						if (existe_ocor == false)
							{
							for (aux_b1 = 0; aux_b1 < menu_aux; aux_b1++)
								{
								aux_l2 = aux_b1;
								aux_l1 = inicio_ocorrencias;
								aux_l1 = aux_l1 + (int32)(aux_l2 * TAM_REGS);
								aux_b2 = read_byte_flash(aux_l1); 
								if (aux_b2 != 0xff)
									{
									if (aux_b2 < nro_tab_ocor)
										{
										aux_l1++;
										// Le dia e hora
										dia_old = read_byte_flash(aux_l1++);
										mes_old = read_byte_flash(aux_l1++);
										ano_old = read_byte_flash(aux_l1++);
										hora_old = read_byte_flash(aux_l1++);
										minuto_old = read_byte_flash(aux_l1);
										if (dia_old < 32)
											{
											if (mes_old < 13)
												{
												if (hora_old < 24)
													{
													if (minuto_old < 60)
														{
														existe_ocor = true;
														break;
														}
													}
												}
											}
										}
									}
								}
							}
						menu_aux = aux_b1;
						if (existe_ocor == false)
							{
							// exibe final de ocorencias
							mensagem(1,66);
							mensagem(2,0);
							}
						else
							{
							// colocar a mensagem referente a ocorrencia
							mensagem(1,tabela_ocorrencias[aux_b2]);
							mensagem(2,60);
							// colocar a data e hora da ocorrencia
							//displayp(17,aux_b1,2,0,0);
							
							displayp(18,dia_old,2,0,0);
							displayp(21,mes_old,2,0,0);
							displayp(24,ano_old,2,0,0);
							displayp(27,hora_old,2,0,0);
							displayp(30,minuto_old,2,0,0);
							}
						}
					}
			#endif
		#else
			if (exibiu == 0)
				{
				exibiu = 1;
				if (limpa_ocor == 1)
					{
					mensagem(1,131);
					lcd_gotoxy(2,1);
				    wr_lcd(1,0x7F);		//escreve a seta para esquerda
					mensagem(2,132);
					}
				else
					{
					mensagem(1,122);
					aux_b1 = read_byte(ee_ocorrencias + menu_aux);
					if (aux_b1 > limite_ocorrencias)
						{
						mensagem(2,tabela_ocorrencias[0]);
						displayp(14,0,2,0,0);
						}
					else
						{
						mensagem(2,tabela_ocorrencias[aux_b1]);
						displayp(14,aux_b1,2,0,0);
						}
					}
				}
		#endif
	#endif
}



