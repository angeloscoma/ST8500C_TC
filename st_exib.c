/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_MAIN                                                        *
; Funcao: MODULO PRINCIPAL DE CONTROLE									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */

void exibe_erro(void);


void exibe_tensao_fn(void)
{
//	if (modo_funca == 2)
//		{
//		}
//	else
//		{
		displayp(19,tensao_r,3,1,6);	/* exibe tensao R no display1 com 1 casa decimal entrada em q6)*/
		displayp(35,tensao_s,3,1,6);	/* exibe tensao S no display1 com 1 casa decimal entrada em q6)*/
		displayp(51,tensao_t,3,1,6);	/* exibe tensao T no display1 com 1 casa decimal entrada em q6)*/
//		}
}

void exibe_corrente(void)
{
	#if (tc_fixo == true)
		print_display(27, corrente_r, 4, 1,3, 'C' , 255);	
		print_display(43, corrente_s, 4, 1,3, 'C' , 255);	
		print_display(59, corrente_t, 4, 1,3, 'C' , 255);	
	#else
		displayp(27,corrente_r,4,1,3);
		displayp(43,corrente_s,4,1,3);
		displayp(59,corrente_t,4,1,3);
	#endif
}

void exibe_tensao_ff(void)
{
	displayp(20,tensao_rs,3,1,6);	/* exibe tensao RS no display1 com 1 casa decimal entrada em q6)*/
	displayp(36,tensao_st,3,1,6);	/* exibe tensao ST no display1 com 1 casa decimal entrada em q6)*/
	displayp(52,tensao_rt,3,1,6);	/* exibe tensao RT no display1 com 1 casa decimal entrada em q6)*/
}

void exibe_tensao_fn_cor(void)
{
	if (exibiu == 0)
		{
		exibiu = 1;
		mensagem(1,m_menu1_110);
		mensagem(2,m_menu1_111);
		mensagem(3,m_menu1_112);
		mensagem(4,m_menu1_113);
		}
	exibe_tensao_fn();
	exibe_corrente();
}

void exibe_tensao_ff_cor(void)
{
	if (exibiu == 0)
		{
		exibiu = 1;
		mensagem(1,m_menu1_130);
		mensagem(2,m_menu1_131);
		mensagem(3,m_menu1_132);
		mensagem(4,m_menu1_133);
		}
	exibe_tensao_ff();
	exibe_corrente();
}

void exibe_pot_kw_kva(void)
{
	if (!exibiu){
		exibiu = 1;

		mensagem(1,19);
		mensagem(1,m_menu1_120);
		mensagem(2,m_menu1_121);
		mensagem(3,m_menu1_122);
		mensagem(4,m_menu1_123);
	}
	
	if (valor_tp != 1)
		{
		aux_l1 = (int32)(pot_ativa_r);
		aux_l1 = (int32)(aux_l1 * valor_tp);
		data1_int = (int16)(aux_l1 / 32);
		
		#if (tc_fixo == true)
			print_display(19, data1_int, 4, 1, 0, 'C' , 255);	
		#else
			displayp(19,data1_int,5,0,0);
		#endif
					
		aux_l1 = (int32)(pot_ativa_s);
		aux_l1 = (int32)(aux_l1 * valor_tp);
		data1_int = (int16)(aux_l1 / 32);
		#if (tc_fixo == true)
			print_display(35, data1_int, 4, 1, 0, 'C' , 255);	
		#else
			displayp(35,data1_int,5,0,0);
		#endif

		aux_l1 = (int32)(pot_ativa_t);
		aux_l1 = (int32)(aux_l1 * valor_tp);
		data1_int = (int16)(aux_l1 / 32);
		#if (tc_fixo == true)
			print_display(51, data1_int, 4, 1, 0, 'C' , 255);	
		#else
			displayp(51,data1_int,5,0,0);
		#endif

		aux_l1 = (int32)(pot_aparente_r);
		aux_l1 = (int32)(aux_l1 * valor_tp);
		data1_int = (int16)(aux_l1 / 32);
		#if (tc_fixo == true)
			print_display(27, data1_int, 4, 1, 0, 'C' , 255);	
		#else
			displayp(27,data1_int,5,0,0);
		#endif
					
		aux_l1 = (int32)(pot_aparente_s);
		aux_l1 = (int32)(aux_l1 * valor_tp);
		data1_int = (int16)(aux_l1 / 32);
		#if (tc_fixo == true)
			print_display(43, data1_int, 4, 1, 0, 'C' , 255);	
		#else
			displayp(43,data1_int,5,0,0);
		#endif

		aux_l1 = (int32)(pot_aparente_t);
		aux_l1 = (int32)(aux_l1 * valor_tp);
		data1_int = (int16)(aux_l1 / 32);
		#if (tc_fixo == true)
			print_display(59, data1_int, 4, 1, 0, 'C' , 255);	
		#else
			displayp(59,data1_int,5,0,0);
		#endif
		
	 	}
	 else
	 	{
		if (sentido_r == 1)
			{
			lcd_gotoxy(3,2);
		    wr_lcd(1,'-');
			#if (tc_fixo == true)
				print_display(20, pot_ativa_r, 4, 1,5, 'C' , 255);	
			#else
				displayp(20,pot_ativa_r,4,1,5);
			#endif
			}
		else
			{
			#if (tc_fixo == true)
				print_display(19, pot_ativa_r, 4, 1,5, 'C' , 255);	
			#else
				displayp(19,pot_ativa_r,4,1,5);
			#endif
		    wr_lcd(1,' ');
			}
		if (sentido_s == 1)
			{
			lcd_gotoxy(3,3);
		    wr_lcd(1,'-');
			#if (tc_fixo == true)
				print_display(36, pot_ativa_s, 4, 1,5, 'C' , 255);	
			#else
				displayp(36,pot_ativa_s,4,1,5);
			#endif
			}
		else
			{
			#if (tc_fixo == true)
				print_display(35, pot_ativa_s, 4, 1,5, 'C' , 255);	
			#else
				displayp(35,pot_ativa_s,4,1,5);
			#endif
		    wr_lcd(1,' ');
			}
		if (sentido_t == 1)
			{
			lcd_gotoxy(3,4);
		    wr_lcd(1,'-');
			#if (tc_fixo == true)
				print_display(52, pot_ativa_t, 4, 1,5, 'C' , 255);	
			#else
				displayp(52,pot_ativa_t,4,1,5);
			#endif
			}
		else
			{
			#if (tc_fixo == true)
				print_display(51, pot_ativa_t, 4, 1,5, 'C' , 255);	
			#else
				displayp(51,pot_ativa_t,4,1,5);
			#endif			  
		    wr_lcd(1,' ');
			}
		#if (tc_fixo == true)
			print_display(27, pot_aparente_r, 4, 1,5, 'C' , 255);	
			print_display(43, pot_aparente_s, 4, 1,5, 'C' , 255);	
			print_display(59, pot_aparente_t, 4, 1,5, 'C' , 255);	
		#else
			displayp(27,pot_aparente_r,4,1,5);
			displayp(43,pot_aparente_s,4,1,5);
			displayp(59,pot_aparente_t,4,1,5);
		#endif
		}
}


void exibe_tensao_alta(void)
{
//	valor_tp = 1;
	displayp(20,tensao_rs_na_alta,3,1,6);
	displayp(36,tensao_st_na_alta,3,1,6);
	displayp(52,tensao_rt_na_alta,3,1,6);

}

void exibe_tensao_alta_cor(void)
{
	if (exibiu == 0)
		{
		exibiu = 1;
		mensagem(1,m_menu1_140);
		mensagem(2,m_menu1_141);
		mensagem(3,m_menu1_142);
		mensagem(4,m_menu1_143);
		}
	exibe_tensao_alta();
	exibe_corrente();
}


void exibe_pot_reativa(void)
{
	if (valor_tp != 1)
		{
		aux_l1 = (unsigned long)(pot_reativa_r);
		aux_l1 = (unsigned long)(aux_l1 * valor_tp);
		data1_int = (unsigned int)(aux_l1 / 32);
		#if (tc_fixo == true)
			print_display(27, data1_int, 4, 1, 0, 'C' , 255);	
		#else
			displayp(27,data1_int,5,0,0);
		#endif

		aux_l1 = (unsigned long)(pot_reativa_s);
		aux_l1 = (unsigned long)(aux_l1 * valor_tp);
		data1_int = (unsigned int)(aux_l1 / 32);
		#if (tc_fixo == true)
			print_display(43, data1_int, 4, 1, 0, 'C' , 255);	
		#else
			displayp(43,data1_int,5,0,0);
		#endif

		aux_l1 = (unsigned long)(pot_reativa_t);
		aux_l1 = (unsigned long)(aux_l1 * valor_tp);
		data1_int = (unsigned int)(aux_l1 / 32);
		#if (tc_fixo == true)
			print_display(59, data1_int, 4, 1, 0, 'C' , 255);	
		#else
			displayp(59,data1_int,5,0,0);
		#endif
		}
	else
		{
		#if (tc_fixo == true)
			print_display(27, pot_reativa_r, 4, 1,5, 'C' , 255);	
			print_display(43, pot_reativa_s, 4, 1,5, 'C' , 255);	
			print_display(59, pot_reativa_t, 4, 1,5, 'C' , 255);	
		#else
			displayp(27,pot_reativa_r,4,1,5);
			displayp(43,pot_reativa_s,4,1,5);
			displayp(59,pot_reativa_t,4,1,5);
		#endif
		}
}

void exibe_fator_pot(void)
{
	displayfp(19,fator_pot_r);
	displayfp(35,fator_pot_s);
	displayfp(51,fator_pot_t);
}

void exibe_kvar_fp(void)
{
	if (exibiu == 0)
		{
		exibiu = 1;
		mensagem(1,m_menu1_150);
		mensagem(2,m_menu1_151);
		mensagem(3,m_menu1_152);
		mensagem(4,m_menu1_153);
		}
	exibe_fator_pot();
	exibe_pot_reativa();
}


#if (com_consumo == true)
	void exibe_dec_consumo(word decimal)
	{
	    wr_lcd(1,',');
		aux_b1 = (char)(decimal  / 3200);
	    wr_lcd(1, aux_b1 +'0');
	}
	
	void exibe_consumos_fora_ponta(void)
	{
		if (exibiu == 0)
			{
			exibiu = 1;
			if (teclou_enter == 0)
				{
				mensagem(1,m_menu1_160);
				}
			else
				{
				mensagem(1,91);
				}
			mensagem(2,m_menu1_161);
			mensagem(3,m_menu1_162);
			mensagem(4,m_menu1_163);
			}
		
		if (teclou_enter == 0)
			{
			#if (tc_fixo == true)
				aux_f1 = consumo_ati;
				aux_f1 = aux_f1 * mul_tc;
				aux_l1 = (int32)(aux_f1);
				displaypl(23,aux_l1,8);

				aux_f1 = consumo_r_tmp * 1000;
				aux_f1 = aux_f1 * mul_tc;
				aux_l1 = (int32)(aux_f1);
				exibe_dec_consumo((int16)(aux_l1));

				aux_f1 = consumo_reati;
				aux_f1 = aux_f1 * mul_tc;
				aux_l1 = (int32)(aux_f1);
				displaypl(39,aux_l1,8);

				aux_f1 = consumo_reati_r_tmp * 1000;
				aux_f1 = aux_f1 * mul_tc;
				aux_l1 = (int32)(aux_f1);
				exibe_dec_consumo((int16)(aux_l1));
				
			#else
				displaypl(23,consumo_ati,8);
				exibe_dec_consumo((int16)(consumo_r_tmp * 1000));
	
				displaypl(39,consumo_reati,8);
				exibe_dec_consumo((int16)(consumo_reati_r_tmp * 1000));
			#endif
			}
		else
			{
			#if (tc_fixo == true)
				aux_f1 = read_word(ee_consumo_ati_ant);
				aux_f1 = aux_f1 * mul_tc;
				aux_l1 = (int32)(aux_f1);
				displaypl(23,aux_l1,8);
				aux_f1 = read_word(ee_consumo_reati_ant);
				aux_f1 = aux_f1 * mul_tc;
				aux_l1 = (int32)(aux_f1);
				displaypl(39,aux_l1,8);
			#else
				displaypl(23,read_word(ee_consumo_ati_ant),8);
		//		exibe_dec_consumo(read_word(ee_consumo_ati_tmp_ant));
		
				displaypl(39,read_word(ee_consumo_reati_ant),8);
		//		exibe_dec_consumo(read_word(ee_consumo_rea_tmp_ant));
			#endif
			}
	
	}


	void exibe_consumos_ponta(void)
	{
		if (exibiu == 0)
			{
			exibiu = 1;
			mensagem(1,100);
			mensagem(2,m_menu1_161);
			mensagem(3,m_menu1_162);
			mensagem(4,m_menu1_163);
			}
		#if (tc_fixo == true)
			aux_f1 = consumo_ati_p;
			aux_f1 = aux_f1 * mul_tc;
			aux_l1 = (int32)(aux_f1);
			displaypl(23,aux_l1,8);
			aux_f1 = consumo_rea_p;
			aux_f1 = aux_f1 * mul_tc;
			aux_l1 = (int32)(aux_f1);
			displaypl(39,aux_l1,8);
		#else
			displaypl(23,consumo_ati_p,8);
			displaypl(39,consumo_rea_p,8);
		#endif
	}

	#if (com_consumo_aparente == true)
	#endif

#endif

void exibe_demanda_ativa(void)
{
	float mul_pt;
	if (exibiu == 0)
		{
		exibiu = 1;
		if ((hora >= hora_ponta) && (hora < hora_final_ponta))
			{
			mensagem(1,98);
			}
		else
			{
			mensagem(1,m_menu1_170);
			}
		mensagem(2,m_menu1_171);
		mensagem(3,m_menu1_172);
		mensagem(4,m_menu1_173);
		}

	#if (tc_fixo == true)
		mul_pt = tabela_mul_tc[tipo_ponteira];
		
		aux_f1 = dem_ativa;
		aux_f1 = aux_f1 * mul_pt;
		aux_w1 = (int32)(aux_f1);
		displayp(25,aux_w1,5,0,0);
		aux_f1 = dem_media_ativa;
		aux_f1 = aux_f1 * mul_pt;
		aux_w1 = (int32)(aux_f1);
		displayp(41,aux_w1,5,0,0);
		aux_f1 = dem_maxima_ativa;
		aux_f1 = aux_f1 * mul_pt;
		aux_w1 = (int32)(aux_f1);
		displayp(57,aux_w1,5,0,0);
	#else
		displayp(25,dem_ativa,5,0,0);
		displayp(41,dem_media_ativa,5,0,0);
		displayp(57,dem_maxima_ativa,5,0,0);
	#endif
	

}

void exibe_demanda_kva_kvar(void)
{
	if (exibiu == 0)
		{
		exibiu = 1;
		if ((hora >= hora_ponta) && (hora < hora_final_ponta))
			{
			mensagem(1,99);
			}
		else
			{
			mensagem(1,m_menu1_180);
			}
		mensagem(2,m_menu1_181);
		mensagem(3,m_menu1_182);
		mensagem(4,m_menu1_183);
		}
	#if (tc_fixo == true)
		aux_f1 = dem_media_aparente;
		aux_f1 = aux_f1 * mul_tc;
		aux_w1 = (int32)(aux_f1);
		displayp(25,aux_w1,5,0,0);
		aux_f1 = dem_maxima_aparente;
		aux_f1 = aux_f1 * mul_tc;
		aux_w1 = (int32)(aux_f1);
		displayp(41,aux_w1,5,0,0);
		aux_f1 = dem_reativa;
		aux_f1 = aux_f1 * mul_tc;
		aux_w1 = (int32)(aux_f1);
		displayp(54,aux_w1,5,0,0);
	#else
		displayp(25,dem_media_aparente,5,0,0);
		displayp(41,dem_maxima_aparente,5,0,0);
		displayp(54,dem_reativa,5,0,0);	
	#endif

}


void exibe_pot_requerida(void)
{
	if (exibiu == 0)
		{
		exibiu = 1;
		mensagem(1,m_menu1_190);
		mensagem(2,m_menu1_191);
		mensagem(3,m_menu1_192);
		mensagem(4,m_menu1_193);
		}

	lcd_gotoxy(11,2);
	display('T');
	display('o');
	display('t');
	display('a');
	display('l');

	#if (tc_fixo == true)
		print_display(19, pot_req_r, 4, 1,5, 'C' , 255);	
		print_display(35, pot_req_s, 4, 1,5, 'C' , 255);	
		print_display(51, pot_req_t, 4, 1,5, 'C' , 255);	
	#else
		displayp(19,pot_req_r,4,1,5);	
		displayp(35,pot_req_s,4,1,5);	
		displayp(51,pot_req_t,4,1,5);	
	#endif

	aux_l1 = pot_req_r;
	aux_l1 += pot_req_s;
	aux_l1 += pot_req_t;
	aux_w1 = aux_l1 / 32;

	#if (tc_fixo == true)
		print_display(42, aux_w1, 5, 0,0, 'C' , 255);	
	#else
		displayp(42,aux_w1,5,0,0);	
	#endif

}

void exibe_pot_excedente(void)
{
	if (exibiu == 0)
		{
		exibiu = 1;
		mensagem(1,m_menu1_1100);
		mensagem(2,m_menu1_1101);
		mensagem(3,m_menu1_1102);
		mensagem(4,m_menu1_1103);
		}

	lcd_gotoxy(11,2);
	display('T');
	display('o');
	display('t');
	display('a');
	display('l');

	#if (tc_fixo == true)
		print_display(19, pot_exec_r, 4, 1,5, 'C' , 255);	
		print_display(35, pot_exec_s, 4, 1,5, 'C' , 255);	
		print_display(51, pot_exec_t, 4, 1,5, 'C' , 255);	
	#else
		displayp(19,pot_exec_r,4,1,5);	
		displayp(35,pot_exec_s,4,1,5);	
		displayp(51,pot_exec_t,4,1,5);	
	#endif

	aux_l1 = pot_exec_r;
	aux_l1 += pot_exec_s;
	aux_l1 += pot_exec_t;
	aux_w1 = aux_l1 / 32;

	#if (tc_fixo == true)
		print_display(42, aux_w1, 5, 0,0, 'C' , 255);	
	#else
		displayp(42,aux_w1,5,0,0);	
	#endif

}	



void exibe_data_hora(void)
{	
	#if (portatil == true)
		mensagem(4,0);
	#endif
	displayp(50,dia,2,0,0);	
	wr_lcd(1,'/');
	displayp(53,mes,2,0,0);	
	displayp(56,hora,2,0,0);	
	wr_lcd(1,':');
	displayp(59,minuto,2,0,0);	
	wr_lcd(1,':');
	displayp(62,segundo,2,0,0);	
}

void verifica_status_old(void)
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
	if ((corrente_r < aux_w1) || (corrente_s < aux_w1) || (corrente_t < aux_w1)) // 3%
		{
		goto status_erro;
		}
	else if ((tensao_r < (20 * 64)) || (tensao_s < (20 * 64)) || (tensao_t < (20 * 64))) 
		{
		goto status_erro;
		}
#if (com_regs == true)
	else if (memoria_full == 1)
		{
		goto status_erro;
		}
#endif
	else if ((ten_a_r == 1) || (ten_a_s == 1) || (ten_a_t == 1))
		{
		goto status_erro;
		}
	else if ((ten_b_r == 1) || (ten_b_s == 1) || (ten_b_t == 1))
		{
		goto status_erro;
		}
	else if ((cor_a_r == 1) || (cor_a_s == 1) || (cor_a_t == 1))
		{
		goto status_erro;
		}
	else if ((cor_b_r == 1) || (cor_b_s == 1) || (cor_b_t == 1))
		{
		goto status_erro;
		}
	else if ((sentido_r == 1)||(sentido_s == 1) || (sentido_t == 1))
		{
		goto status_erro;
		}
	else if (erro_freq == 1)
		{
		goto status_erro;
		}
	else
		{
		tem_erro = 0;
		return;
		}
status_erro:
	tem_erro = 1;

}


void exibe_erro_old(void)
{
	passo_exibe_erro++;
	switch(passo_exibe_erro)
		{
		case 1:
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
			if ((corrente_r < aux_w1) || (corrente_s < aux_w1) || (corrente_t < aux_w1)) // 3%
				{
				mensagem(4,77);
				exibiu_erro = 1;
				break;
				}
			else
				{
				passo_exibe_erro++;
				}
			}
		case 2:
			{
			if ((tensao_r < (20 * 64)) || (tensao_s < (20 * 64)) || (tensao_t < (20 * 64))) 
				{
				mensagem(4,78);
				exibiu_erro = 1;
				break;
				}	
			else
				{
				passo_exibe_erro++;
				}
			}
		case 3:
			{
			if (registro == 1)
				{
				exibiu_erro = 1;
				mensagem(4,41);
				displayp(60,valor_tc,4,0,0);
				break;
				}
			else
				{
				passo_exibe_erro++;
				}
			}
		case 4:
			{
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
			}
		case 5:
			{
			if (registro == 1)
				{
				exibiu_erro = 1;
				if (tipo_ligacao == 0)
					{
					mensagem(4,80);
					}
				else
					{
					mensagem(4,79);
					}
				break;
				}
			else
				{
				passo_exibe_erro++;
				}
			}
		case 6:
			{
#if (com_regs == true)
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
			}
		case 7:
			{
			if ((ten_a_r == 1) || (ten_a_s == 1) || (ten_a_t == 1))
				{
				exibiu_erro = 1;
				mensagem(4,82);
				break;
				}
			else
				{
				passo_exibe_erro++;
				}
			}
		case 8:
			{
			if ((ten_b_r == 1) || (ten_b_s == 1) || (ten_b_t == 1))
				{
				exibiu_erro = 1;
				mensagem(4,81);
				break;
				}
			else
				{
				passo_exibe_erro++;
				}
			}
		case 9:
			{
			if ((cor_a_r == 1) || (cor_a_s == 1) || (cor_a_t == 1))
				{
				exibiu_erro = 1;
				mensagem(4,84);
				break;
				}
			else
				{
				passo_exibe_erro++;
				}
			}
		case 10:
			{
			if ((cor_b_r == 1) || (cor_b_s == 1) || (cor_b_t == 1))
				{
				exibiu_erro = 1;
				mensagem(4,83);
				break;
				}
			else
				{
				passo_exibe_erro++;
				}
			}
		case 11:
			{
			if (sentido_r == 1)
				{
				exibiu_erro = 1;
				if (pisca_minuto == 1)
					{
					mensagem(4,85);
					}
				else
					{
					mensagem(4,88);
					}
				break;
				}
			else
				{
				passo_exibe_erro++;
				}
			}
		case 12:
			{
			if (sentido_s == 1)
				{
				exibiu_erro = 1;
				if (pisca_minuto == 1)
					{
					mensagem(4,86);
					}
				else
					{
					mensagem(4,89);
					}
				break;
				}
			else
				{
				passo_exibe_erro++;
				}
			}
		case 13:
			{
			if (sentido_t == 1)
				{
				exibiu_erro = 1;
				if (pisca_minuto == 1)
					{
					mensagem(4,87);
					}
				else
					{
					mensagem(4,90);
					}
				break;
				}
			else
				{
				passo_exibe_erro++;
				}
			}
		case 14:
			{
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
			}

		case 15:	
			{
#if (com_regs == true)
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
			}
		case 16:
			{
			if (erro_freq == 1)
				{
				exibiu_erro = 1;
				mensagem(4,98);
				break;
				}
			else
				{
				passo_exibe_erro++;
				}
			}


		default:
			{
			passo_exibe_erro = 0;
			if (exibiu_erro_menu == 0)
				{
				exibe_data_hora();
#if (chip_cs5460a == true)
				displayp(50,status_cs5460h,3,0,0);	
				wr_lcd(1,'/');
				displayp(54,status_cs5460m,3,0,0);	
				wr_lcd(1,'/');
				displayp(58,status_cs5460l,3,0,0);	
				if (int_cs5460 == 1)
					{
					wr_lcd(1,'I');
					}
				else
					{
					wr_lcd(1,'i');
					}
#endif
				}
			}
		}

}

void exibe_status_old(void)
{	

	if (exibiu == 0)
		{
		inic_dis();
		limpa_display();
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
		exibiu = 1;
		}


// exibe a autonomia e o horario atual

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


}


void exibe_colchete(void)
{
	if (qmenu == 5)
		{
		switch(menu_aux)
			{
			case 2:
				{
				lcd_gotoxy(1,1);
				display('[');
				lcd_gotoxy(16,1);
				display(']');
				break;
				}
			case 3:
				{
				lcd_gotoxy(1,2);
				display('[');
				lcd_gotoxy(16,2);
				display(']');
				break;
				}
			case 4:
				{
				lcd_gotoxy(1,3);
				display('[');
				lcd_gotoxy(16,3);
				display(']');
				break;
				}
			default:
				{
				lcd_gotoxy(1,4);
				display('[');
				lcd_gotoxy(16,4);
				display(']');
				break;
				}
			}			
		}
	else
		{
		switch(menu_aux)
			{
			case 1:
				{
				lcd_gotoxy(1,1);
				display('[');
				lcd_gotoxy(16,1);
				display(']');
				break;
				}
			case 2:
				{
				lcd_gotoxy(1,2);
				display('[');
				lcd_gotoxy(16,2);
				display(']');
				break;
				}
			case 3:
				{
				lcd_gotoxy(1,3);
				display('[');
				lcd_gotoxy(16,3);
				display(']');
				break;
				}
			default:
				{
				lcd_gotoxy(1,4);
				display('[');
				lcd_gotoxy(16,4);
				display(']');
				break;
				}
			}			
		}
}
