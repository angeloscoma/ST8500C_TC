/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_MAIN                                                        *
; Funcao: MODULO PRINCIPAL DE CONTROLE									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */



// buffer localizacao com até 16 caracteres alfanumericos.
#if (tratar_localizacao == true)
	void digita_texto(void)
	{
		 if (tecla_enter==1)
			{
		 	tecla_enter = 0;
			if ((tabela_alfabeto[caracter_texto] != '#') && (aux_texto != 14))
				{
				localizacao[16] = 0;
				mensagem(4, 200);
				aux_texto++;
				ativa_cursor();
			  	lcd_gotoxy(aux_texto+1,4);
				}
			else
				{
				//  encerrar digitação.
				digitando_texto = 0;
				if ((aux_texto == 1) && (tabela_alfabeto[caracter_texto] == '#'))
					{
					digitou_texto = 0;
					write_bit(ee_bits_menu2, EE_DIGITOU_TEXTO, digitou_texto);
					}
				else
					{
					for (aux_texto = 1; aux_texto < 15; aux_texto++)
						{
						if (localizacao[aux_texto] != ' ')
							{
							digitou_texto = true;
							existe_local = true;
							write_bit(ee_bits_menu2, EE_EXISTE_LOCAL, existe_local);
							write_bit(ee_bits_menu2, EE_DIGITOU_TEXTO, digitou_texto);
							break;
							}
						}
					write_byte(EE_LOCALIZACAO_1, localizacao[1]);
					write_byte(EE_LOCALIZACAO_2, localizacao[2]);
					write_byte(EE_LOCALIZACAO_3, localizacao[3]);
					write_byte(EE_LOCALIZACAO_4, localizacao[4]);
					write_byte(EE_LOCALIZACAO_5, localizacao[5]);
					write_byte(EE_LOCALIZACAO_6, localizacao[6]);
					write_byte(EE_LOCALIZACAO_7, localizacao[7]);
					write_byte(EE_LOCALIZACAO_8, localizacao[8]);
					write_byte(EE_LOCALIZACAO_9, localizacao[9]);
					write_byte(EE_LOCALIZACAO_10, localizacao[10]);
					write_byte(EE_LOCALIZACAO_11, localizacao[11]);
					write_byte(EE_LOCALIZACAO_12, localizacao[12]);
					write_byte(EE_LOCALIZACAO_13, localizacao[13]);
					write_byte(EE_LOCALIZACAO_14, localizacao[14]);
					write_byte(EE_LOCALIZACAO_15, localizacao[15]);
					}
				menu_aux++;
				exibiu = 0;
				desativa_cursor();
				localizacao[16] = 0;
				mensagem(4, 200);
				}
			}		
		else if (tecla_up==1)
			{
			tecla_up=0;
			if (caracter_texto < nro_caracteres)
				{
				caracter_texto++;
				}
			else
				{
				caracter_texto = 0;
				}
			localizacao[aux_texto] = tabela_alfabeto[caracter_texto];
			localizacao[16] = 0;
			mensagem(4, 200);
			ativa_cursor();
		  	lcd_gotoxy(aux_texto+1,4);
			}
		else if (tecla_down==1)
			{
			 tecla_down=0;
			if (caracter_texto > 0)
				{
				caracter_texto--;
				}
			else
				{
				caracter_texto = nro_caracteres;
				}
	
			localizacao[aux_texto] = tabela_alfabeto[caracter_texto];
			localizacao[16] = 0;
			mensagem(4, 200);
			ativa_cursor();
		  	lcd_gotoxy(aux_texto+1,4);
			}
		else if (tecla_reset==1)
			{
			tecla_reset = 0;
			if (aux_texto > 1)
				{
				aux_texto--;
				localizacao[16] = 0;
				mensagem(4, 200);
				ativa_cursor();
			  	lcd_gotoxy(aux_texto+1,4);
				}
			else
				{
				digitando_texto = false;
				digitou_texto = false;
				existe_local = false;
				menu_aux++;
				exibiu = 0;
				desativa_cursor();
				}
			}
	}
#endif



void trata_menu5(void)
{
/* TRATA PROGRAMACAO DE REGISTROS */
	
	if (qmenu != 5)
		{
		qmenu = 5;
		menu_aux = 1;
		}
#if (tratar_localizacao	== true)
	else if (digitando_texto == 1)
		{
		digita_texto();
		return;
		}
#endif
	else if (tecla_enter==1)
		{
	 	tecla_enter=0;
		exibiu = 0;
		if (programando == 1)
			{
			desativa_cursor();
			goto salva_programa_menu5;
			}
		else
			{
			goto trata_menu5_enter;
			}
		}		
	else if (tecla_up==1)
		{
		exibiu = 0;
		tecla_up=0;
		 if (programando == 1)
		 	{
			goto trata_menu5_up;
		 	}
		 else
		 	{
			if (digitou_texto == true)
				{
				if (menu_aux > 2)
					{
					 menu_aux--;
					}
				}
			else
				{
				if (menu_aux > 1)
					{
					 menu_aux--;
					}
				}
			desativa_cursor();
			}
		}
	else if (tecla_down==1)
		{
		exibiu = 0;
		 tecla_down=0;
		 if (programando == 1)
		 	{
			goto trata_menu5_down;
		 	}
		 else
		 	{
			 if (prog_time == 1)
			 	{
				 if (menu_aux < nro_menus5)
				 	{
					 menu_aux++;
					}
				}
			else
				{
				 if (menu_aux < 6)
				 	{
					 menu_aux++;
					}
				}
			desativa_cursor();
			}
		}
	else if (tecla_reset==1)
		{
		desativa_cursor();
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
	goto exibe_programa_menu5;


salva_programa_menu5:
	programando = 0;

#if (com_regs == true)
	inicializa_regs();
	prox_grava = aux_l2 + intervalo_reg;
#endif	

	write_word(ee_intervalo_reg, intervalo_reg);
	write_byte(ee_forma_reg_cht, forma_reg_cht);
	write_byte(ee_registro, registro);
	write_byte(ee_prog_time, prog_time);
	write_byte(ee_dia_liga,	dia_liga);		
	write_byte(ee_dia_desliga, dia_desliga);
	write_byte(ee_hora_liga, hora_liga);
	write_byte(ee_minuto_liga, minuto_liga);
	write_byte(ee_hora_desliga, hora_desliga);
	write_byte(ee_minuto_desliga, minuto_desliga);
	write_byte(ee_fila_circular, fila_circular);

	
	valida_programa();

	if (prog_time == 1)
	 	{
		 if (menu_aux < nro_menus5)
		 	{
			 menu_aux++;
			}
		}
	else
		{
		 if (menu_aux < 5)
		 	{
			 menu_aux++;
			}
		}

	exibiu = 0;
						
exibe_programa_menu5: 

	if (programando == 1)
		{
		exibir_menu = 1;
		}
	if (exibir_menu == 0)
		{
		return;
		}
	if (menu_aux > 1)
		{
		if (menu_aux < 6)
			{
			if (exibiu == 0)
				{
				if (programando == 0)
					{
					mensagem(1, 44);	
					mensagem(2, 46);	
					mensagem(3, 45);	
					mensagem(4, 67);
					}
				exibiu = 1;
				}
			exibe_colchete();
			}
		else if (menu_aux == 6)
			{
			if (exibiu == 0)
				{
				if (programando == 0)
					{
					mensagem(1, 46);	
					mensagem(2, 45);
					mensagem(3, 67);
					mensagem(4, 57);
					}
				exibiu = 1;
				}
			exibe_colchete();
			}
		else
			{
			if (exibiu == 0)
				{
				if (programando == 0)
					{
					mensagem(1, 58);	
					mensagem(2, 59);	
					mensagem(3, 60);	
					mensagem(4, 61);
					}
				exibiu = 1;
				}
			}
		}
		
		
	switch(menu_aux)
		{
// só para teste
		case 1:
			{
			if (registro == 0)
				{
				mensagem(1,103);
				mensagem(2,104);
				mensagem(3,105);
				mensagem(4,0);
				digitando_texto = 1;
				digitou_texto = 0;
				caracter_texto = 0;
				existe_local = false;
				write_bit(ee_bits_menu2, EE_EXISTE_LOCAL, existe_local);
				write_bit(ee_bits_menu2, EE_DIGITOU_TEXTO, digitou_texto);
				for (aux_texto = 1; aux_texto < 15; aux_texto++)
					{
					localizacao[aux_texto] = ' ';
					}
				aux_texto = 1;
				localizacao[0] = '[';
				localizacao[15] = ']';
				localizacao[16] = 0;
				write_byte(EE_LOCALIZACAO_0, '[');
				write_byte(EE_LOCALIZACAO_15, ']');
				write_byte(EE_LOCALIZACAO_16, 0);
				digita_texto();
				mensagem(4, 200);
				lcd_gotoxy(2,4);
				ativa_cursor();
				}
			else
				{
				menu_aux++;
				}
			break;
			}
		case 2:
			{
			displayp(12,intervalo_reg,4,0,'P');
			if (programando == 0)
				{
				exibe_sim_nao(registro,29,0);
				displayp(47,forma_reg_cht,1,0,0);
				exibe_sim_nao(fila_circular,61,0);
				}
			break;
			}
		case 3:
			{
			exibe_sim_nao(registro,29,'P');
			if (programando == 0)
				{
				displayp(12,intervalo_reg,4,0,0);
				displayp(47,forma_reg_cht,1,0,0);
				exibe_sim_nao(fila_circular,61,0);
				}
			break;
			}
		case 4:
			{
			displayp(47,forma_reg_cht,1,0,'P');
			if (programando == 0)
				{
				displayp(12,intervalo_reg,4,0,0);
				exibe_sim_nao(registro,29,0);
				exibe_sim_nao(fila_circular,61,0);
				}
			break;
			}
		case 5:
			{
			exibe_sim_nao(fila_circular,61,'P');
			if (programando == 0)
				{
				exibe_sim_nao(registro,29,0);
				displayp(12,intervalo_reg,4,0,0);
				displayp(47,forma_reg_cht,1,0,0);
				}
			break;
			}
		case 6:
			{
			exibe_sim_nao(prog_time,61,'P');
			if (programando == 0)
				{
				exibe_sim_nao(registro,13,0);
				displayp(31,forma_reg_cht,1,0,0);
				exibe_sim_nao(fila_circular,45,0);
				}
			break;
			}
		case 7:
			{
			displayp(40,dia_liga,2,0,'P');
			if (programando == 0)
				{
				displayp(43,hora_liga,2,0,0);
				displayp(46,minuto_liga,2,0,0);
				displayp(56,dia_desliga,2,0,0);
				displayp(59,hora_desliga,2,0,0);
				displayp(62,minuto_desliga,2,0,0);
				}
			mostra_cur(41);
			break;
			}
		case 8:
			{
			displayp(43,hora_liga,2,0,'P');
			if (programando == 0)
				{
				displayp(40,dia_liga,2,0,0);
				displayp(46,minuto_liga,2,0,0);
				displayp(56,dia_desliga,2,0,0);
				displayp(59,hora_desliga,2,0,0);
				displayp(62,minuto_desliga,2,0,0);
				}
			mostra_cur(44);
			break;
			}
		case 9:
			{
			displayp(46,minuto_liga,2,0,'P');
			if (programando == 0)
				{
				displayp(40,dia_liga,2,0,0);
				displayp(43,hora_liga,2,0,0);
				displayp(56,dia_desliga,2,0,0);
				displayp(59,hora_desliga,2,0,0);
				displayp(62,minuto_desliga,2,0,0);
				}
			mostra_cur(47);
			break;
			}
		case 10:
			{
			displayp(56,dia_desliga,2,0,'P');
			if (programando == 0)
				{
				displayp(40,dia_liga,2,0,0);
				displayp(43,hora_liga,2,0,0);
				displayp(46,minuto_liga,2,0,0);
				displayp(59,hora_desliga,2,0,0);
				displayp(62,minuto_desliga,2,0,0);
				}
			mostra_cur(57);
			break;
			}
		case 11:
			{
			displayp(59,hora_desliga,2,0,'P');
			if (programando == 0)
				{
				displayp(40,dia_liga,2,0,0);
				displayp(43,hora_liga,2,0,0);
				displayp(46,minuto_liga,2,0,0);
				displayp(56,dia_desliga,2,0,0);
				displayp(62,minuto_desliga,2,0,0);
				}
			mostra_cur(60);
			break;
			}
		case 12:
			{
			displayp(62,minuto_desliga,2,0,'P');
			if (programando == 0)
				{
				displayp(40,dia_liga,2,0,0);
				displayp(43,hora_liga,2,0,0);
				displayp(46,minuto_liga,2,0,0);
				displayp(56,dia_desliga,2,0,0);
				displayp(59,hora_desliga,2,0,0);
				}
			mostra_cur(63);
			break;
			}
		default:
			{
			menu_aux = nro_menus5;
			}
		}
	exibir_menu = 0;
	return;


trata_menu5_enter:
	programando = 1;
 	switch(menu_aux)
 		{
		case 1:
			{
			break;
			}
		case 2:
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
	goto exibe_programa_menu5;	


trata_menu5_down:
	switch(menu_aux)
		{
		case 1:
			{
			break;
			}
		case 2:
			{
			if (aux_tab > 0)
				{
				aux_tab--;
				if (registro == 1)
					{
					#if (com_regs == true)
						grava_registros(reg_final);
					#endif					
					registro = 0;
					}
				}
			intervalo_reg = tabela_intervalo_reg[aux_tab];
			break;
			}			
		case 3:
			{
			if (registro == 1)
				{
				#if (com_regs == true)
					grava_registros(reg_final);
				#endif					
				registro = 0;
				}
			else
				{
				registro = 1;
				#if (com_regs == true)
					grava_registros(reg_inicio);
				#endif					
				}	
			break;
			}
		case 4:
			{
			if (forma_reg_cht > 0)
				{
				forma_reg_cht--;
				}
			break;
			}
		case 5:
			{
			if (fila_circular == 1)
				{
				fila_circular = 0;
				}
			else
				{
				fila_circular = 1;
				}	
			break;
			}			
		case 6:
			{
			if (prog_time == 1)
				{
				prog_time = 0;
				}
			else
				{
				prog_time = 1;
				}	
			break;
			}			
		case 7:
			{
			if (dia_liga > 1)
				{
				dia_liga--;
				}
			break;
			}
		case 8:
			{
			if (hora_liga > 0)
				{
				hora_liga--;
				}
			break;
			}
		case 9:
			{
			if (minuto_liga > 0)
				{
				minuto_liga--;
				}
			break;
			}
		case 10:
			{
			if (dia_desliga > dia_liga)
				{
				dia_desliga--;
				}
			break;
			}
		case 11:
			{
			if (dia_liga == dia_desliga)
				{
				if (hora_desliga > hora_liga)
					{
					hora_desliga--;
					}
				}
			else
				{
				if (hora_desliga > 0)
					{
					hora_desliga--;
					}
				}
			break;
			}
		case 12:
			{
			if (dia_liga == dia_desliga)
				{
				if (hora_liga == hora_desliga)
					{
					if (minuto_desliga > minuto_liga)
						{
						minuto_desliga--;
						}
					}
				else
					{
					if (minuto_desliga > 0)
						{
						minuto_desliga--;
						}
					}
				}
			else
				{
				if (minuto_desliga > 0)
					{
					minuto_desliga--;
					}
				}
			break;
			}

		}	
	goto exibe_programa_menu5;

trata_menu5_up:
	switch(menu_aux)
		{
		case 1:
			{
			break;
			}
		case 2:
			{
			if (aux_tab < (NRO_POSI_INTERVALO - 1))
				{
				aux_tab++;
				if (registro == 1)
					{
					#if (com_regs == true)
						grava_registros(reg_final);
					#endif					
					registro = 0;
					}
				}
			intervalo_reg = tabela_intervalo_reg[aux_tab];
			break;
			}			
		case 3:
			{
			if (registro == 1)
				{
				#if (com_regs == true)
					grava_registros(reg_final);
					registro = 0;
				#endif					
				}
			else
				{
				registro = 1;
				#if (com_regs == true)
					grava_registros(reg_inicio);
				#endif					
				}	
			break;
			}
		case 4:
			{
			if (forma_reg_cht < 3)
				{
				forma_reg_cht++;
				}
			break;
			}
		case 5:
			{
			if (fila_circular == 1)
				{
				fila_circular = 0;
				}
			else
				{
				fila_circular = 1;
				}	
			break;
			}			
		case 6:
			{
			if (prog_time == 1)
				{
				prog_time = 0;
				}
			else
				{
				prog_time = 1;
				}	
			break;
			}			
		case 7:
			{
			if (dia_liga < 31)
				{
				dia_liga++;
				}
			break;
			}
		case 8:
			{
			if (hora_liga < 23)
				{
				hora_liga++;
				}
			break;
			}
		case 9:
			{
			if (minuto_liga < 59)
				{
				minuto_liga++;
				}
			break;
			}
		case 10:
			{
			if (dia_desliga < 31)
				{
				dia_desliga++;
				}
			break;
			}
		case 11:
			{
			if (hora_desliga < 23)
				{
				hora_desliga++;
				}
			break;
			}
		case 12:
			{
			if (minuto_desliga < 59)
				{
				minuto_desliga++;
				}
			break;
			}
			
		}	
goto exibe_programa_menu5;
}



