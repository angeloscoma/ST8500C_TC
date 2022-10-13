/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_ERROS                                                       *
; Funcao: MODULO PRINCIPAL DE CONTROLE									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */
void exibe_erro(void);


void exibe_erro_tmp(void)
{
	exibe_erro();
}

void exibe_status(void)
{	
	if (programando == true)
		{
		return;
		}

	#if (portatil == true)	
		if (registro == 1)
			{
			mensagem(1,17);
			}
		else
			{
			if (prog_time == 1)
				{
				mensagem(1,76);
				}
			else
				{
				mensagem(1,18);
				}
			}
		mensagem(2,68);
	//  1234567890123456
	//	07-set 19:20:00
	//   ___d,__:__:__
		lcd_gotoxy(1,3);
		wr_lcd(1,' ');
		displayp(34,nro_dias,3,0,0);
		wr_lcd(1,'d');
		wr_lcd(1,',');
		displayp(39,nro_horas,2,0,0);
		wr_lcd(1,'h');
		displayp(42,nro_minutos,2,0,0);
		wr_lcd(1,'m');
		displayp(45,nro_segundos,2,0,0);
		wr_lcd(1,'s');
	
		if (ponto_segundo == 1)
			{
			if (exibiu_erro == 1)
				{
				exibiu_erro = 0;
				mensagem(4,0);
				}
			exibe_data_hora();
			}
		else
			{
			exibe_erro();
			}
	#endif

}

void verifica_status(void)
{
	#if (portatil == true)
		if (valor_tc < 61)
			{
			aux_w1 = 8;
			}
		if (valor_tc < 201)
			{
			aux_w1 = 40;
			}
		else
			{
			aux_w1 = 80;
			}
	#else
		aux_w1 = 120;
	#endif

	#if (st8500c == true)
		cor_min_r = 0;
		cor_min_s = 0;
		cor_min_t = 0;
		erro_freq = 0;
	#endif

//	status = 0;
	
	#if (com_relogio == false)
		#if (com_regs == false)
			ajuste_relogio = 0;
		#endif
		if (ajuste_relogio == 1)
			{
////			status = 1;
			goto status_erro;
			}
	#endif
		
	#if (controlador == true)
		#if (AUTOSET == true)
			if (em_autoset == true)
				{
//				status = 2;
				goto status_erro;
				}
		#endif
	#endif
	#if (monofasico == true)
		#if (controlador == false)
			if (corrente_r < aux_w1)
				{
//				status = 3;
				goto status_erro;
				}
			else if (tensao_r < (TENSAO_FALTA))
		#else
			if (tensao_r < (TENSAO_FALTA))
		#endif
			{
//			status = 4;
			goto status_erro;
			}
		else if ((ten_a_r == 1) || (ten_b_r == 1) || (cor_a_r == 1) || (cor_b_r == 1) || (sentido_r == 1))
			{
//			status = 5;
			goto status_erro;
			}
	#else
		#if (controlador == false)
			if ((corrente_r < aux_w1) || (corrente_s < aux_w1) || (corrente_t < aux_w1)) // 3%
				{
	//			status = 6;
				goto status_erro;
				}
			else if ((tensao_r < (TENSAO_FALTA)) || (tensao_s < (TENSAO_FALTA)) || (tensao_t < (TENSAO_FALTA))) 
		#else
			if ((tensao_r < (TENSAO_FALTA)) || (tensao_s < (TENSAO_FALTA)) || (tensao_t < (TENSAO_FALTA))) 
		#endif
			{
//			status = 7;
			goto status_erro;
			}
			
		else if ((ten_a_r == 1) || (ten_a_s == 1) || (ten_a_t == 1))
			{
//			status = 8;
			goto status_erro;
			}
		else if ((ten_b_r == 1) || (ten_b_s == 1) || (ten_b_t == 1))
			{
//			status = 9;
			goto status_erro;
			}
		else if ((cor_a_r == 1) || (cor_a_s == 1) || (cor_a_t == 1))
			{
//			status = 10;
			goto status_erro;
			}
		else if ((cor_b_r == 1) || (cor_b_s == 1) || (cor_b_t == 1))
			{
//			status = 11;
			goto status_erro;
			}
		else if ((sentido_r == 1)||(sentido_s == 1) || (sentido_t == 1))
			{
//			status = 12;
			goto status_erro;
			}
			
	#endif
	#if (controlador == true)
		else if (em_repouso == true)
			{
//			status = 13;
			goto status_erro;
			}
		else if ((des_ten_a == true) || (fp_ind == true) || (fp_cap == true) || (falta_capacitor == true) || (des_chtt == true) || (des_chtc == true))
			{
//			status = 14;
			goto status_erro;
			}
		#if (monofasico == true)
			else if (cor_min_r == true)
				{
	//			status = 15;
				goto status_erro;
				}
		#else
			else if ((cor_min_r == true) || (cor_min_s == true) ||(cor_min_t == true))
				{
	//			status = 16;
				goto status_erro;
				}
		#endif
	#endif
	#if (com_regs == true)
		#if (portatil == true)
			else if (memoria_full == 1)
				{
	//			status = 17;
				goto status_erro;
				}
		#endif
	#endif
	#if (com_alarme_demanda == true)
		else if (dem_ati == true)
			{
//			status = 18;
			goto status_erro;
			}
	#endif
		else if (erro_freq == 1)
			{
//			status = 19;
			goto status_erro;
			}
	#if (com_rep == true)
		else if ((saturou_kw == true) || (saturou_kvar == true))
			{
//			status = 21;
			goto status_erro;
			}
		else if (modo_rep == 1)
			{
//			status = 23;
			goto status_erro;
			}
	#endif
	#if (st8500c == true)
		#if (com_tc == false)
			else if (time_out_modo_rep == 0)
				{
	//			status = 2;
				goto status_erro;
				}
		#endif
	#endif
		else
			{
			tem_erro = 0;
			return;
			}
status_erro:
	tem_erro = 1;

}

void exibe_erro(void)
{

	#if (controlador == true)
		#if (AUTOSET == true)
			if (em_autoset == true)
				{
				#if (ST8200C == true)
					mensagem(2,149);
					return;
				#else
					#error falta mensagem
					return;
				#endif
				}
		#endif
	#endif
	
	if (programando == true)
		{
		return;
		}


	#if (ST8100C == true)
		if (em_status == false)
			{
			return;
			}
	#endif
	
	passo_exibe_erro++;
	
	switch(passo_exibe_erro)
		{
		case 1:		//Corrente Crítica
			{
			#if (st8500c == true)
				passo_exibe_erro++;
			#else
				#if (controlador == false)
					if (valor_tc < 61)
						{
						aux_w1 = 8;
						}
					if (valor_tc < 201)
						{
						aux_w1 = 40;
						}
					else
						{
						aux_w1 = 80;
						}
					#if (monofasico == true)
						if (corrente_r < aux_w1)
					#else
						if ((corrente_r < aux_w1) || (corrente_s < aux_w1) || (corrente_t < aux_w1)) // 3%
					#endif
							{
							#if (st94 == true)
								#if (disp_lcd == false)
									mensagem(1,0);
								#else
									mensagem(2,32);
								#endif
							#else
								mensagem(4,77);
							#endif
							exibiu_erro = 1;
							break;
							}
						else
							{
							passo_exibe_erro++;
							}
				#else
					passo_exibe_erro++;
				#endif
			#endif
            break;
			}
		case 2:		//Tensão Crítica
			{
			#if (st8500c == true)
				#if (com_tc == true)
					if ((tensao_r < (TENSAO_FALTA)) || (tensao_s < (TENSAO_FALTA)) || (tensao_t < (TENSAO_FALTA))) 
						{
						mensagem(2,126);
						exibiu_erro = 1;
						break;
						}	
					else
						{
						passo_exibe_erro++;
						}
				#else
					passo_exibe_erro++;
				#endif
			#else
				#if (monofasico == true)
					if (tensao_r < (TENSAO_FALTA))
				#else
					if ((tensao_r < (TENSAO_FALTA)) || (tensao_s < (TENSAO_FALTA)) || (tensao_t < (TENSAO_FALTA))) 
				#endif
						{
						#if (st94 == true)
							#if (disp_lcd == false)
								mensagem(2,0);
							#else
								mensagem(2,33);
							#endif
						#elif (ST8100C == true)
							if (rolando == false)
								{
								mensagem_rola(1,5);
								}
						#elif (ST8200C == true) || (ST8300C == true)
							mensagem(2,126);
						#else
							mensagem(4,78);
						#endif
						exibiu_erro = 1;
						break;
						}	
					else
						{
						passo_exibe_erro++;
						}
			#endif
			}
		case 3:		//Valor do TC ou da Ponteira
			{
			#if (st8500c == true)
				passo_exibe_erro++;
			#else
				#if (portatil == true)
					if (registro == 1)
						{
						mensagem(4,41);
						displayp(60,valor_tc,4,0,0);
						exibiu_erro = 1;
						break;
						}
					else
						{
						passo_exibe_erro++;
						}
				#else
					passo_exibe_erro++;
				#endif
			#endif
                    break;
			}
		case 4:		//Tempo entre Registros
			{
			#if (portatil == true)
				if (registro == 1)
					{
					exibiu_erro = 1;
					mensagem(4,44);
					displayp(60,intervalo_reg,4,0,0);
					break;
					}
				else
					{
					passo_exibe_erro++;
					}
			#else
				passo_exibe_erro++;
			#endif
            break;
			}
		case 5:		//Tipo de Ligação
			{
			#if (st8500c == true) 
				#if (com_tc == false)
					passo_exibe_erro++;
				#else
					exibiu_erro = 1;
					mensagem(2,38);
					lcd_gotoxy(15,2);
					if (tipo_ligacao == 0)
						{
						display('Y');
						}
					else if (tipo_ligacao == 2)
						{
						display('D');
						display('A');
						}
					else
						{
						display('D');
						}
					break;
				#endif
			#else
				if (tipo_ligacao == 0)
					{
					#if (st94 == true)
						#if (disp_lcd == false)
							passo_exibe_erro++;
						#else
							exibiu_erro = 1;
							mensagem(2,19);
							lcd_gotoxy(15,2);
							display('Y');
							break;
						#endif
					#elif (ST8100C == true)
						if (rolando == false)
							{
							mensagem_rola(2,5);
							}
	
					#elif ((ST8200C == true) || (ST8300C == true))
						exibiu_erro = 1;
						mensagem(2,38);
						lcd_gotoxy(15,2);
						#if (ST8200C == true)
							display('F');
							display('N');
						#else
							display('Y');
						#endif
					break;
					#else
						#if (portatil == true)
							if (registro == 1)
								{
								exibiu_erro = 1;
								mensagem(4,80);
								break;
								}
						#else
							passo_exibe_erro++;
						#endif
					#endif
					}
				else if (tipo_ligacao == 2)
					{
					#if (st94 == true)
						#if (disp_lcd == false)
							passo_exibe_erro++;
						#else
							exibiu_erro = 1;
							mensagem(2,19);
							lcd_gotoxy(15,2);
							display('D');
							display('A');
							break;
						#endif
					#elif (st8300c == true)
						exibiu_erro = 1;
						mensagem(2,38);
						lcd_gotoxy(15,2);
						display('D');
						display('A');
						break;
					#else
						passo_exibe_erro++;
					#endif
					}
				else
					{
					#if (st94 == true)
						#if (disp_lcd == false)
							passo_exibe_erro++;
						#else
							exibiu_erro = 1;
							mensagem(2,19);
							lcd_gotoxy(15,2);
							display('D');
							break;
						#endif
					#elif (ST8100C == true)
						if (rolando == false)
							{
							mensagem_rola(3,5);
							}
					#elif ((ST8200C == true) || (ST8300C == true))
						exibiu_erro = 1;
						mensagem(2,38);
						lcd_gotoxy(15,2);
						#if (ST8200C == true)
							display('F');
							display('F');
						#else
							display('D');
						#endif
						break;
					#else
						#if (portatil == true)
							if (registro == 1)
								{
								exibiu_erro = 1;
								mensagem(4,79);
								break;
								}
						#else
							passo_exibe_erro++;
						#endif
					#endif
					}
			#endif
			}
		case 6:		//Memória Cheia
			{
			#if (portatil == true)
				if (memoria_full == 1)
					{
					exibiu_erro = 1;
					mensagem(4,73);
					break;
					}
				else
					{
					passo_exibe_erro++;
					}
			#else
				passo_exibe_erro++;
			#endif
            break;
			}
		case 7:		//Tensão Alta
			{
			#if (monofasico == true)
				if (ten_a_r == 1) 
			#else
				if ((ten_a_r == 1) || (ten_a_s == 1) || (ten_a_t == 1))
			#endif
					{
					exibiu_erro = 1;
					#if (st94 == true)
						#if (disp_lcd == false)
							mensagem(3,0);
						#else
							mensagem(2,35);
						#endif
					#elif (ST8100C == true)
						if (rolando == false)
							{
							mensagem_rola(4,5);
							}
					#elif ((ST8200C == true) || (ST8300C == true) || (st8500c == true))
						mensagem(2,104);
					#else
						mensagem(4,82);
					#endif
					break;
					}
				else
					{
					passo_exibe_erro++;
					}
			}
		case 8:		//Tensão Baixa
			{
			#if (monofasico == true)
				if (ten_b_r == 1) 
			#else
				if ((ten_b_r == 1) || (ten_b_s == 1) || (ten_b_t == 1))
			#endif
					{
					exibiu_erro = 1;
					#if (st94 == true)
						#if (disp_lcd == false)
							mensagem(4,0);
						#else
							mensagem(2,34);
						#endif
					#elif (ST8100C == true)
						if (rolando == false)
							{
							mensagem_rola(5,5);
							}
					#elif ((ST8200C == true) || (ST8300C == true) || (st8500c == true))
						mensagem(2,105);
					#else
						mensagem(4,81);
					#endif
					break;
					}
				else
					{
					passo_exibe_erro++;
					}
			}
		case 9:		//Corrente Alta
			{
			#if (st8500c == true)
				passo_exibe_erro++;
			#else
				#if (monofasico == true)
					if (cor_a_r == 1)
				#else
					if ((cor_a_r == 1) || (cor_a_s == 1) || (cor_a_t == 1))
				#endif
						{
						exibiu_erro = 1;
						#if (st94 == true)
							#if (disp_lcd == false)
								mensagem(5,0);
							#else
								mensagem(2,37);
							#endif
						#elif (ST8100C == true)
							if (rolando == false)
								{
								mensagem_rola(6,5);
								}
						#elif (ST8200C == true) || (ST8300C == true)
							mensagem(2,106);
						#else
							mensagem(4,84);
						#endif
						break;
						}
					else
						{
						passo_exibe_erro++;
						}
			#endif
            break;
			}
		case 10:		//Corrente Baixa
			{
			#if (st8500c == true)
				passo_exibe_erro++;
			#else
				#if (monofasico == true)
					if (cor_b_r == 1) 
				#else
					if ((cor_b_r == 1) || (cor_b_s == 1) || (cor_b_t == 1))
				#endif
						{
						exibiu_erro = 1;
						#if (st94 == true)
							#if (disp_lcd == false)
								mensagem(6,0);
							#else
								mensagem(2,36);
							#endif
						#elif (ST8100C == true)
							if (rolando == false)
								{
								mensagem_rola(7,5);
								}
						#elif (ST8200C == true) || (ST8300C == true)
							mensagem(2,114);
						#else		
							mensagem(4,83);
						#endif
						break;
						}
					else
						{
						passo_exibe_erro++;
						}
			#endif
            break;
			}
		case 11:		//KW Fornecido - TC invertido
			{
			if (sentido_r == 1)
				{
				exibiu_erro = 1;
				if (pisca_minuto == 1)
					{
					#if (st94 == true)
						#if (disp_lcd == false)
							mensagem(7,0);
						#else
							mensagem(2,38);
						#endif
					#elif (ST8100C == true)
						if (rolando == false)
							{
							mensagem_rola(8,5);
							}
					#elif ((ST8200C == true) || (ST8300C == true) || (st8500c == true))
						mensagem(2,83);
					#elif (portatil == true)
						mensagem(4,85);
					#else
//						#erro Que equipamento????
					#endif
					}
				else
					{
					#if (st94 == true)
						#if (disp_lcd == false)
							mensagem(11,0);
						#else
							mensagem(2,41);
						#endif
					#elif (ST8100C == true)
						if (rolando == false)
							{
							mensagem_rola(8,5);
							}
					#elif ((ST8200C == true) || (ST8300C == true) || (st8500c == true))
						mensagem(2,83);
					#elif (portatil == true)
						mensagem(4,88);
					#else
//						#erro Que equipamento????
					#endif
					}
				break;
				}
			else
				{
				passo_exibe_erro++;
				}
			}
		case 12:		//KW Fornecido Fase S ou Ponteira/TC invertido
			{
			#if (monofasico == false)
				if (sentido_s == 1)
					{
					exibiu_erro = 1;
					if (pisca_minuto == 1)
						{
						#if (st94 == true)
							#if (disp_lcd == false)
								mensagem(8,0);
							#else
								mensagem(2,39);
							#endif
						#elif ((ST8300C == true) || (st8500c == true))
							mensagem(2,84);
						#else
							mensagem(4,86);
						#endif
						}
					else
						{
						#if (st94 == true)
							#if (disp_lcd == false)
								mensagem(12,0);
							#else
								mensagem(2,42);
							#endif
						#elif ((ST8300C == true) || (st8500c == true))
							mensagem(2,84);
						#else
							mensagem(4,89);
						#endif
						}
					break;
					}
				else
					{
					passo_exibe_erro++;
					}
			#endif
			}
		case 13:		//KW Fornecido Fase T ou Ponteira/TC invertido
			{
			#if (monofasico == false)
				if (sentido_t == 1)
					{
					exibiu_erro = 1;
					if (pisca_minuto == 1)
						{
						#if (st94 == true)
							#if (disp_lcd == false)
								mensagem(9,0);
							#else
								mensagem(2,40);
							#endif
						#elif ((ST8300C == true) || (st8500c == true))
							mensagem(2,85);
						#else
							mensagem(4,87);
						#endif
						}
					else
						{
						#if (st94 == true)
							#if (disp_lcd == false)
								mensagem(13,0);
							#else
								mensagem(2,43);
							#endif
						#elif ((ST8300C == true) || (st8500c == true))
							mensagem(2,85);
						#else
							mensagem(4,90);
						#endif
						}
					break;
					}
				else
					{
					passo_exibe_erro++;
					}
			#endif
			}
		case 14:		//Modo de Funcionamento
			{
			#if (portatil == true)
				exibiu_erro = 1;
				mensagem(4,95);
				lcd_gotoxy(15, 4);
				if (modo_funca == 1)
					{
					display('1');
					}
				else
					{
					display('2');
					}
				break;
			#else
				passo_exibe_erro++;
			#endif
                break;
			}

		case 15:	//Número de Registros
			{
			#if (portatil == true)
				if (registro == 1)
					{
					exibiu_erro = 1;
	// exibe quantos registros possiveis e disponíveis.
					lcd_gotoxy(1,4);
					wr_lcd(1,'R');
					wr_lcd(1,'e');
					wr_lcd(1,'g');
					wr_lcd(1,'s');
					wr_lcd(1,':');
					displayp(54,read_word_nvr(ds_ptr_regs),5,0,0);
					if (modo_funca == 2)
						{
						aux_w1 = limite_registros_modo2;
						}
					else
						{
						aux_w1 = limite_registros;
						}
					wr_lcd(1,'/');
					displayp(60,aux_w1,5,0,0);
					break;
					}
				else
					{
					passo_exibe_erro++;
					}
			#else
				passo_exibe_erro++;
			#endif
                break;
			}
		case 16:		//Demanda
			{
			#if (st8500c == true)
				passo_exibe_erro++;
			#else
				if (erro_freq == 1)
					{
					exibiu_erro = 1;
					#if (st94 == true)
						passo_exibe_erro++;
					#elif (controlador == true)
						passo_exibe_erro++;
					#else
						mensagem(4,98);
					#endif
					break;
					}
				else
					{
					passo_exibe_erro++;
					}
			#endif
                break;
			}
		case 17:		//Nome do Local da Coleta de Dados
			{
			#if (tratar_localizacao == true)
				if (existe_local == true)
					{
					exibiu_erro = 1;
					mensagem(4,200);
					break;
					}
				else
					{
					passo_exibe_erro++;
					}
			#else
				passo_exibe_erro++;
			#endif
                break;
			}
		case 18:		// LIVRE
			{
			passo_exibe_erro++;
            break;
			}
		case 19:		//Exibição do Alerta de data e hora para equipamentos sem relógio em tempo real.
			{
			#if (com_relogio == false)
				if (ajuste_relogio == 1)
					{
					#if (ST8100C == true)
						if (rolando == false)
							{
							mensagem_rola(9,5);
							}
					#elif ((ST8200C == true) || (ST8300C == true) || (st8500c == true))
						exibiu_erro = 1;
						mensagem(2,58);
					#endif
					break;
					}
				else
					{
					passo_exibe_erro++;
					}
			#else
				passo_exibe_erro++;
			#endif
                break;
			}
		case 20:		//Desligamento por Tensão
			{
			#if (controlador == true)
				#if (st8500c == true)
					passo_exibe_erro++;
				#else
					if (des_ten_a == true)
						{
						#if (ST8100C == true)
							if (rolando == false)
								{
								mensagem_rola(10,5);
								}
						#elif ((ST8200C == true) || (ST8300C == true))
							exibiu_erro = 1;
							mensagem(2,130);
							break;
						#endif
						}
					else
						{
						passo_exibe_erro++;
						}
				#endif
			#else
				passo_exibe_erro++;
			#endif
                break;
			}
		case 21:		//Fator de Potência Indutivo
			{
			#if (controlador == true)
				if ((fp_ind == true) || (falta_capacitor == true))
					{
					#if (ST8100C == true)
						if (rolando == false)
							{
							mensagem_rola(11,5);
							}
					#elif ((ST8200C == true) || (ST8300C == true))
						exibiu_erro = 1;
						mensagem(2,82);
						break;
					#elif (ST8500C == true)
						exibiu_erro = 1;
						mensagem(2,80);
						break;
					
					#endif
					}
				else
					{
					passo_exibe_erro++;
					}
			#else
				passo_exibe_erro++;
			#endif
			}
		case 22:		//Fator de Potência Capacitivo
			{
			#if (controlador == true)
				if (fp_cap == true)
					{
					#if (ST8100C == true)
						if (rolando == false)
							{
							mensagem_rola(12,5);
							}
					#elif ((ST8200C == true) || (ST8300C == true))
						exibiu_erro = 1;
						mensagem(2,81);
						break;
					#elif (ST8500C == true)
						exibiu_erro = 1;
						mensagem(2,81);
						break;
					#endif
					}
				else
					{
					passo_exibe_erro++;
					}
			#else
				passo_exibe_erro++;
			#endif
			}
		case 23:		//Corrente Crítica em Controladores
			{
			#if (st8500c == true)
				passo_exibe_erro++;
			#else
				#if (controlador == true)
					#if (monofasico == true)
						if (cor_min_r == true)
					#else
						if ((cor_min_r == true) && (cor_min_s == true) && (cor_min_t == true))
					#endif					
							{
							#if (ST8100C == true)
								if (rolando == false)
									{
									mensagem_rola(13,5);
									}
							#elif ((ST8200C == true) || (ST8300C == true))
								exibiu_erro = 1;
								mensagem(2,134);
								break;
							#endif
							}
						else
							{
							passo_exibe_erro++;
							}
				#else
					passo_exibe_erro++;
				#endif
			#endif
                    break;
			}
		case 24:		//Em Banco Mínimo
			{
			#if (st8500c == true)
				passo_exibe_erro++;
			#else
				#if (controlador == true)
					#if (monofasico == true)
						if ((cor_min_r == true) && (status_banco_minimo == 2))
					#else
						if (((cor_min_r == true) && (cor_min_s == true) && (cor_min_t == true)) && (status_banco_minimo == 2))
					#endif					
						{
						#if (ST8100C == true)
							if (rolando == false)
								{
								mensagem_rola(14,5);
								}
						#elif ((ST8200C == true) || (ST8300C == true))
							exibiu_erro = 1;
							mensagem(2,136);
							break;
						#else
							passo_exibe_erro++;
						#endif
						}
					else
						{
						passo_exibe_erro++;
						}
				#else
					passo_exibe_erro++;
				#endif
			#endif
                    break;
			}

		case 25:		//Desligamento por CHT DE TENSAO ALTO
			{
			#if (st8500c == true)
				passo_exibe_erro++;
			#else
				#if (controlador == true)
					if (des_chtt == true)
						{
						#if (ST8100C == true)
							if (rolando == false)
								{
								mensagem_rola(15,5);
								}
						#elif ((ST8200C == true) || (ST8300C == true))
							exibiu_erro = 1;
							mensagem(2,101);
							break;
						#endif
						}
					else
						{
						passo_exibe_erro++;
						}
				#else
					passo_exibe_erro++;
				#endif
			#endif
                    break;
			}
		case 26:		//Desligamento por CHT DE CORRENTE ALTO
			{
			#if (st8500c == true)
				passo_exibe_erro++;
			#else
				#if (controlador == true)
					if (des_chtc == true)
						{
						#if (ST8100C == true)
							if (rolando == false)
								{
								mensagem_rola(16,5);
								}
						#elif ((ST8200C == true) || (ST8300C == true))
							exibiu_erro = 1;
							mensagem(2,102);
							break;
						#endif
						}
					else
						{
						passo_exibe_erro++;
						}
				#else
					passo_exibe_erro++;
				#endif
			#endif
                    break;
			}
		case 27:		//Exibe se está em modo REP
			{
			#if (st8500c == true)
				passo_exibe_erro++;
			#else
				#if (com_rep == true)
					if (modo_rep == 1)
						{
						#if (ST8100C == true)
							if (rolando == false)
								{
								if (modo_rep == 0)
									{
									mensagem_rola(65,1);
									}
								else
									{
									mensagem_rola(66,1);
									}
								}
							break;
						#elif (ST8200C == true)
							exibiu_erro = 1;
							mensagem(2,140);
							break;
						#elif (ST8300C == true)
							exibiu_erro = 1;
							mensagem(2,141);
							break;
						#endif
						}
					else
						{
						passo_exibe_erro++;
						}
				#else
					passo_exibe_erro++;
				#endif
			#endif
                    break;
			}
		case 28:
			{
			#if (controlador == true)
				#if (st8500c == true)
					em_repouso = false;
					for (aux_b1 = 0; aux_b1 < nro_cargas ; aux_b1++)
						{
						if (aux_tempo_repouso[aux_b1] != 0)
							{
							em_repouso = true;
							break;
							}
						}
					if (em_repouso == true)
						{
						exibiu_erro = 1;
						mensagem(2,150);			
						break;
						}
					else
						{
						passo_exibe_erro++;
						}
				#else
					em_repouso = false;
					if (que_banco_repouso >= nro_bancos_capacitor)
						{
						que_banco_repouso = 0;
						}
					for (aux_b1 = 0; aux_b1 < nro_bancos_capacitor ; aux_b1++)
						{
						if (aux_tempo_repouso[aux_b1] != 0)
							{
							em_repouso = true;
							break;
							}
						}
					if (em_repouso == true)
						{
						exibiu_erro = 1;
						for (aux_b1 = 0; aux_b1 < nro_bancos_capacitor ; aux_b1++)
							{
							if (aux_tempo_repouso[aux_b1] != 0)
								{
								if (que_banco_repouso == aux_b1)
									{
									break;
									}
								}
							else
								{
								if (que_banco_repouso == aux_b1)
									{
									que_banco_repouso++;
									if (que_banco_repouso >= nro_bancos_capacitor)
										{
										return;
										}
									}
								}
							}
						#if (st8200c == true)
							mensagem(2,148);
							displayp(23+3,(que_banco_repouso + 1),2,0,0);
							displayp(29,aux_tempo_repouso[que_banco_repouso],3,0,0);
//							 "Banco @@ repouso",	//148
							que_banco_repouso++;
							break;
						#elif (ST8100C == true)
							if (rolando == false)
								{
								mensagem_rola(68,1);
								}
							break;
						#else
							mensagem(2,150);			// somente apartir da vx.48
							displayp(23+3,(que_banco_repouso + 1),2,0,0);
							displayp(29,aux_tempo_repouso[que_banco_repouso],3,0,0);
//							 "Banco @@ repouso",	//148
							que_banco_repouso++;
							break;
						#endif
						}
					else
						{
						passo_exibe_erro++;
						}
						
				#endif
			#else
				passo_exibe_erro++;
			#endif
			}
		case 29:
			{
			#if (com_alarme_demanda == true)
				if (dem_ati == true)
					{
					#if (st94 == true)
						exibiu_erro = 1;
						#if (disp_lcd == false)
							mensagem(46,0);
						#else
							mensagem(2,83);
						#endif
						break;
					#elif (ST8500C == true)
						exibiu_erro = 1;
						mensagem(2,82);
						break;
					#else
						passo_exibe_erro++;
					#endif
					}
				else
					{
					passo_exibe_erro++;
					}
			#else
				passo_exibe_erro++;
			#endif
			}
		case 30:
			{
			exibiu_erro = 1;
			#if (ST8100C == true)
				passo_exibe_erro++;
			#elif ((ST8200C == true) || (ST8300C == true) || (ST8500C == true))
				exibe_equip_nro_serie();
				break;
			#elif (st94 == true)
				#if (disp_lcd == true)
					exibe_equip_nro_serie();
					break;
				#else
					passo_exibe_erro++;
				#endif
			#elif (st9600r == true)
				exibe_equip_nro_serie();
				break;			
			#else
				passo_exibe_erro++;
			#endif
			}
		
		case  31:
			{
			#if (controlador == true)
				if (aux_tempo_aciona != 0)
					{
					#if (st8200c == true)
						exibiu_erro = 1;
						mensagem(2,153);
						displayp(29,aux_tempo_aciona,3,0,0);
						break;
					#elif (st8300c == true)
						exibiu_erro = 1;
						mensagem(2,154);
						displayp(29,aux_tempo_aciona,3,0,0);
						break;
					#else
						passo_exibe_erro++;
					#endif
					}
				else
					{
					passo_exibe_erro++;
					}
			#else
				passo_exibe_erro++;
			#endif
                break;
			}
		#if (st8500c == true)
			case 32:
				{
				#if (com_tc == true)
					passo_exibe_erro++;
				#else
					if (time_out_modo_rep == 0)
						{
						if (ferro_rep == false)
							{
							grava_ocorrencias(reg_falta_pulso_rep);
							ferro_rep = true;
							}
						exibiu_erro = 1;
						mensagem(1,4);
						mensagem(2,5);
						break;
						}
					else
						{
						passo_exibe_erro++;
						if (ferro_rep == true)
							{
							grava_ocorrencias(reg_volta_pulso_rep);
							ferro_rep = false;
							}
						}
				#endif
                    break;
				}
			case 33:
				{
				exibiu_erro = 1;
				if (periodo_fatura == PERIODO_PONTA)
					{
					mensagem(2,153);
					break;
					} 
				else
					{
					mensagem(2,154);
					break;
					} 
				}
			case 34:
				{
				#if (com_tc == true)
					passo_exibe_erro++;
				#else
					if (saturou_kw == true) 
						{
						exibiu_erro = 1;
						mensagem(2,168);
						break;
						}
					else if(saturou_kvar == true)
						{
						exibiu_erro = 1;
						mensagem(2,169);
						break;
						}
					else
						{
						passo_exibe_erro++;
						}
				#endif
                    break;
				}
			case 35:
				{
				exibiu_erro = 1;
				mensagem(2,17);
				displayp(27,dem_contratada,4,0,0);
				break;
				}
			case 36:
				{
				exibiu_erro = 1;
				output_01 = saida2;
				if (modo_saidas == MODO_INVERTIDO)
					{
					mensagem(1,173);
					output_01 = ~output_01;
					}
				else
					{
					mensagem(1,174);
					}
				lcd_gotoxy(1,2);
				for (aux_b1 = 0; aux_b1 < 8; aux_b1++)
					{
					if (modo_saidas == MODO_INVERTIDO)
						{
						if  (bit_test(output_01, 0) == true)
							{
							wr_lcd(1,'0');
							}
						else
							{
							wr_lcd(1,'1');
							}
						}
					else
						{
						if  (bit_test(output_01, 0) == true)
							{
							wr_lcd(1,'1');
							}
						else
							{
							wr_lcd(1,'0');
							}
						}
					output_01 = output_01 >> 1;
					}
				output_01 = saida3;
				if (modo_saidas == MODO_INVERTIDO)
					{
					output_01 = ~output_01;
					}
				for (aux_b1 = 0; aux_b1 < 8; aux_b1++)
					{
					if (modo_saidas == MODO_INVERTIDO)
						{
						if  (bit_test(output_01, 0) == true)
							{
							wr_lcd(1,'0');
							}
						else
							{
							wr_lcd(1,'1');
							}
						}
					else
						{
						if  (bit_test(output_01, 0) == true)
							{
							wr_lcd(1,'1');
							}
						else
							{
							wr_lcd(1,'0');
							}
						}
					output_01 = output_01 >> 1;
					}
				break;
				}
			#endif	



		default:		//Exibe Data e Hora
			{
			passo_exibe_erro = 0;
//			if (exibiu_erro_menu == 0);
//				{
				exibiu_erro = 1;
				#if (st94 == true)
					#if (com_regs == true)
						#if (disp_lcd == true)
							exibe_data_hora();
						#else
							if (M1_C6 == 1)
								{
								exibe_data_hora();
								}
						#endif
					#else
						exibiu_erro = 0;
						passo_exibe_erro = 1;
					#endif
				#elif (ST8100C == true)
				#elif ((ST8200C == true) || (ST8300C == true) || (ST8500C == true))
					exibe_data_hora();
				#else
					exibe_data_hora();
				#endif
//				}
			}
		}
	if (exibiu_erro == 1)
		{
		exibiu = 0 ;
		exibiu_erro = 0;
		#if ((st8200c == true) || (st8300c == true))
			mensagem(1,135);
//			displayp(14,passo_exibe_erro,2,0,0);
		#elif ((st8500c == true))
			if ((passo_exibe_erro != 31) && (passo_exibe_erro != 36))
				{
				mensagem(1,135);
//				displayp(12,status,2,0,0);
//				wr_lcd(1,'/');
//				displayp(15,passo_exibe_erro,2,0,0);
				}
		#elif (ST8100C == true)
		#elif (st92 == true)
			mensagem(1,9);
//			displayp(14,passo_exibe_erro,2,0,0);
		#endif
		}
}	
