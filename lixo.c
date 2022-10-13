	if (programando == true)
		{
		return;
		}
//	if ((segundo == 0) || (segundo == 10)|| (segundo == 20) || (segundo == 30)|| (segundo == 40) || (segundo == 50))
//		{
//		if (exibiu_erro_menu == 0)
//			{
//			mensagem(4,0);
//			exibiu_erro_menu = 1;
//			time_out_exibe_erro = 2;
//			}
//		}
		
	#if (teste_edison == true)
		corrente_r = 0;
		tensao_r = 0;
		ten_a_r = 1;
		ten_b_r = 1;
		cor_a_r = 1;
		cor_b_r = 1;
		sentido_r = 1;
		#if (monofasico == false)
			sentido_s = 1;
			sentido_t = 1;
		#endif
	#endif

	passo_exibe_erro++;
	switch(passo_exibe_erro)
		{
		case 1:		//Corrente Crítica
			{
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
						mensagem(1,0);
					#elif (st8610c == true)
					#elif (st8620c == true)
					#elif (st8600c == true)
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
			}
		case 2:		//Tensão Crítica
			{
			#if (monofasico == true)
				if (tensao_r < (20 * 64))
			#else
				if ((tensao_r < (20 * 64)) || (tensao_s < (20 * 64)) || (tensao_t < (20 * 64))) 
			#endif
					{
					#if (st94 == true)
						mensagem(2,0);
					#elif (st8610c == true)
					#elif (st8620c == true)
					#elif (st8600c == true)
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
			}
		case 3:		//Valor do TC ou da Ponteira
			{
			if (registro == 1)
				{
				exibiu_erro = 1;
				#if (st94 == true)
					{	
					passo_exibe_erro++;
					}
				#elif (st8610c == true)
					{	
					passo_exibe_erro++;
					}
				#elif (st8620c == true)
					{	
					passo_exibe_erro++;
					}
				#elif (st8600c == true)
					{	
					passo_exibe_erro++;
					}
				#else
					mensagem(4,41);
					displayp(60,valor_tc,4,0,0);
				#endif
				break;
				}
			else
				{
				passo_exibe_erro++;
				}
			}
		case 4:		//Tempo entre Registros
			{
			if (registro == 1)
				{
				exibiu_erro = 1;
				#if (st94 == true)
					passo_exibe_erro++;
				#elif (st8610c == true)
					passo_exibe_erro++;
				#elif (st8620c == true)
					passo_exibe_erro++;
				#elif (st8600c == true)
					passo_exibe_erro++;
				#else
					mensagem(4,44);
					displayp(60,intervalo_reg,4,0,0);
				#endif
				break;
				}
			else
				{
				passo_exibe_erro++;
				}
			}
		case 5:		//Tipo de Ligação
			{
			if (registro == 1)
				{
				exibiu_erro = 1;
				if (tipo_ligacao == 0)
					{
					#if (st94 == true)
						passo_exibe_erro++;
					#elif (st8610c == true)
					#elif ((st8620c == true) || (st8600c == true))
						mensagem(1,2);
						mensagem(2,38);
						lcd_gotoxy(15,2);
						display('Y');
					#else
						mensagem(4,80);
					#endif
					}
				else
					{
					#if (st94 == true)
						passo_exibe_erro++;
					#elif (st8610c == true)
					#elif ((st8620c == true) || (st8600c == true))
						mensagem(1,2);
						mensagem(2,38);
						lcd_gotoxy(15,2);
						display('D');
					#else
						mensagem(4,79);
					#endif
					}
				break;
				}
			else
				{
				passo_exibe_erro++;
				}
			}
		case 6:		//Memória Cheia
			{
			#if (st94 == true)
				passo_exibe_erro++;
			#elif (st8610c == true)
				passo_exibe_erro++;
			#elif (st8620c == true)
				passo_exibe_erro++;
			#else
				#if (com_regs == true)
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
				#else
					passo_exibe_erro++;
				#endif
			#endif
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
						mensagem(3,0);
					#elif (st8610c == true)
					#elif (st8620c == true)
						mensagem(1,2);
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
						mensagem(4,0);
					#elif (st8610c == true)
					#elif (st8620c == true)
						mensagem(1,2);
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
			#if (monofasico == true)
				if (cor_a_r == 1)
			#else
				if ((cor_a_r == 1) || (cor_a_s == 1) || (cor_a_t == 1))
			#endif
					{
					exibiu_erro = 1;
					#if (st94 == true)
						mensagem(5,0);
					#elif (st8610c == true)
					#elif (st8620c == true)
						mensagem(1,2);
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
			}
		case 10:		//Corrente Baixa
			{
			#if (monofasico == true)
				if (cor_b_r == 1) 
			#else
				if ((cor_b_r == 1) || (cor_b_s == 1) || (cor_b_t == 1))
			#endif
					{
					exibiu_erro = 1;
					#if (st94 == true)
						mensagem(6,0);
					#elif (st8610c == true)
					#elif (st8620c == true)
						mensagem(1,2);
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
			}
		case 11:		//KW Fornecido
			{
			if (sentido_r == 1)
				{
				exibiu_erro = 1;
				if (pisca_minuto == 1)
					{
					#if (st94 == true)
						mensagem(7,0);
					#elif (st8610c == true)
					#elif (st8620c == true)
						mensagem(2,83);
					#else
						mensagem(4,85);
					#endif
					}
				else
					{
					#if (st94 == true)
						mensagem(11,0);
					#elif (st8610c == true)
						passo_exibe_erro++;
					#elif (st8620c == true)
						passo_exibe_erro++;
					#else
						mensagem(4,88);
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
							mensagem(8,0);
						#elif (st8610c == true)
						#elif (st8620c == true)
						#else
							mensagem(4,86);
						#endif
						}
					else
						{
						#if (st94 == true)
							mensagem(12,0);
						#elif (st8610c == true)
						#elif (st8620c == true)
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
			#else
				passo_exibe_erro++;
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
							mensagem(9,0);
						#elif (st8610c == true)
						#elif (st8620c == true)
						#else
							mensagem(4,87);
						#endif
						}
					else
						{
						#if (st94 == true)
							mensagem(13,0);
						#elif (st8610c == true)
						#elif (st8620c == true)
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
			#else
				passo_exibe_erro++;
			#endif
			}
		case 14:		//Modo de Funcionamento
			{
			exibiu_erro = 1;
			#if (st94 == true)
				{
				passo_exibe_erro++;
				}
			#elif (st8610c == true)
				passo_exibe_erro++;
			#elif (st8620c == true)
				passo_exibe_erro++;
			#else
				mensagem(4,95);
				lcd_gotoxy(15, 4);
			#endif
			if (modo_funca == 1)
				{
				#if (st94 == true)
					passo_exibe_erro++;
				#elif (st8610c == true)
					passo_exibe_erro++;
				#elif (st8620c == true)
					passo_exibe_erro++;
				#else
					display('1');
				#endif
				}
			else
				{
				#if (st94 == true)
					passo_exibe_erro++;
				#elif (st8610c == true)
					passo_exibe_erro++;
				#elif (st8620c == true)
					passo_exibe_erro++;
				#else
					display('2');
				#endif
				}
			break;
			}

		case 15:	//Número de Registros
			{
			if (registro == 1)
				{
				exibiu_erro = 1;
// exibe quantos registros possiveis e disponíveis.
				#if (st94 == true)
					passo_exibe_erro++;
				#elif (st8610c == true)
					passo_exibe_erro++;
				#elif (st8620c == true)
					passo_exibe_erro++;
				#elif (st8600c == true)
					passo_exibe_erro++;
				#else
					#if (com_regs == true)
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
					#endif
				#endif
				break;
				}
			else
				{
				passo_exibe_erro++;
				}
			}
		case 16:		//Demanda
			{
			if (erro_freq == 1)
				{
				exibiu_erro = 1;
				#if (st94 == true)
					passo_exibe_erro++;
				#elif (st8610c == true)
					passo_exibe_erro++;
				#elif (st8620c == true)
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
			}
		#if (tratar_localizacao == true)
			case 17:		//Nome do Local da Coleta de Dados
				{
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
				}
		#endif

		case 18:		//Indicação de Coleta de Dados
			{
			#if (com_regs == true)
				if (time_out_coleta != 0)
					{
					#if (st94 == true)
						passo_exibe_erro++;
					#elif (st8610c == true)
						passo_exibe_erro++;
					#elif (st8620c == true)
						passo_exibe_erro++;
					#else
						exibiu_erro = 1;
						mensagem(4,106);
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
		case 19:		//Exibição do Alerta de data e hora para equipamentos sem relógio em tempo real.
			{
			#if (com_relogio == false)
				if (ajuste_relogio == 0)
					{
					#if (st8610c == true)
					#elif (st8620c == true) || (st8600c == true)
						mensagem(1,58);
						mensagem(2,59);
					#endif
					}
			#else
				passo_exibe_erro++;
			#endif
			break;
			}
		default:
			{
			passo_exibe_erro = 0;
			if (exibiu_erro_menu == 0);
				{
				#if (st94 == true)
				#elif (st8610c == true)
				#elif (st8620c == true)
					exibe_data_hora();
				#else
					exibe_data_hora();
				#endif
//				#if (chip_cs5460a == true)
//					displayp(50,status_cs5460h,3,0,0);	
//					wr_lcd(1,'/');
//					displayp(54,status_cs5460m,3,0,0);	
//					wr_lcd(1,'/');
//					displayp(58,status_cs5460l,3,0,0);	
//					if (int_cs5460 == 1)
//						{
//						wr_lcd(1,'I');
//						}
//					else
//						{
//						wr_lcd(1,'i');
//						}
//				#endif
				}
			}
		}
	if (exibiu_erro == 1)
		{
		exibiu = 0 ;
		}
	
}

