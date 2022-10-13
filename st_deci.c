
/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRONICOS                                  *
; Modulo: st92ROTA                                                        *
; Funcao: MODULO ROTINAS             									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */

void decide_regs(void);
void decide(void);
void trata_ala_ten_a(void);
void trata_ala_ten_b(void);
void trata_ala_sc(void);
void trata_ala_cht(void);
void trata_ala_fp_ind(void);
void trata_ala_fp_cap(void);
void trata_virada_mes(void);
void trata_falta_fase(void);
void trata_ala_subc(void);
#if (com_alarme_demanda == true)
	void trata_ala_demanda(void);
#endif
void decide_tensao_nominal(void);
void trata_sentido_sensor_corrente(void);
#if (CONTROLADOR == true)
	#if (st8500c == true)
		void trata_desliga_ten_a(void);
	#else
		void trata_corrente_minima(void);
		void trata_desliga_ten_a(void);
		void trata_desliga_ten_b(void);
		void trata_desliga_chtt_a(void);
		void trata_desliga_chtc_a(void);
		void trata_falta_capacitor(void);
	#endif
#endif
void calcula_vref_cr(void);
#if (monofasico == false)
	void calcula_vref_cs(void);
	void calcula_vref_ct(void);
#endif
#if ((st9200r == true) || (st9230r == true))
	#if (com_maximos == true)
		void trata_cor_pot_maxima(void);
	#endif
#endif


void decide_regs(void)
{   
	#if (com_regs == true)
		#if (portatil == false)
			if (registro == 0){	
				registro = 1;
				write_byte(ee_registro, registro);
			}
		#else
			if (memoria_full == 1){
				if (registro == 1){
					grava_registros(reg_final);
					registro = 0;
					prog_time = 0;
					write_byte(ee_registro, registro);
					write_byte(ee_prog_time, prog_time);
				}
				return;
			}
		#endif
	#endif		
	#if (com_menu == true)
		if (qmenu == 5)
			{
			return;
			}
	#endif
	#if (com_regs == true)
		#if (portatil == true)
			if (registro == 0)
				{	
				if (prog_time == 1)
					{
					if (dia == dia_liga)
						{
						if (hora == hora_liga)	
							{
							if (minuto >= minuto_liga)
								{
								registro = 1;
								write_byte(ee_registro, registro);
								grava_registros(reg_inicio);
								grava_registros(registro_normal);
								}
							}
						}
					}
				#if (funcao_505 == true)
					else
						{
						if (modo_funca == 2)
							{
							if (intervalo_reg < 60)
								{
								intervalo_reg = 600;
								write_word(ee_intervalo_reg, 600);
								}
							inicializa_regs();
							if ((prox_grava <= aux_l2) || (viroudia == 1))
								{
								prox_grava = (int32)(aux_l2 + intervalo_reg);
								inic_tensoes_505();
								}
							}
						}
				#endif
				}
			else
				{
				if (prog_time == 1)
					{
					if (dia >= dia_desliga)
						{
						if (hora >= hora_desliga)
							{
							if (minuto >= minuto_desliga)
								{
								grava_registros(reg_final);
								registro = 0;
								write_byte(ee_registro, 0);
								prog_time = 0;
								write_byte(ee_prog_time, 0);
								return;
								}
							}
						}
					}
		
				if (intervalo_reg < 60)
					{
					if (ultimo_tempo == segundo)
						{
						return;
						}
					}
		
				ultimo_tempo = segundo;
				
				inicializa_regs();
				if ((prox_grava <= aux_l2) || (viroudia == 1))
					{
					prox_grava = (int32)(aux_l2 + intervalo_reg);
					grava_registros(registro_normal);
					#if (com_cht == 1)
						grava_cht(registro_normal);
					#endif
					}
				else
					{
					aux_l1 = aux_l2 + intervalo_reg;
					if (prox_grava > aux_l1)
						{
						inicializa_regs();
						prox_grava = (int32)(aux_l2 + intervalo_reg);
						}
					}
				}
			if (fila_circular == 0)
				{
				if (registro == 1 )
					{
					if (memoria_full == 1)
						{			
						grava_registros(reg_final);
						registro = 0;
						prog_time = 0;
						write_byte(ee_registro, registro);
						write_byte(ee_prog_time, prog_time);
						}
					}
				}
		#else
			registro = 1;
			#if (funcao_505 == true)
				if (modo_funca == 2)
					{
					if (intervalo_reg < 60)
						{
						intervalo_reg = 600;
						write_word(ee_intervalo_reg, 600);
						}
					inicializa_regs();
					if ((prox_grava <= aux_l2) || (viroudia == 1))
						{
						prox_grava = (int32)(aux_l2 + intervalo_reg);
						inic_tensoes_505();
						}
					}
			#endif
			inicializa_regs();
			if ((prox_grava <= aux_l2) || (viroudia == 1))
				{
				prox_grava = (int32)(aux_l2 + intervalo_reg);
				grava_registros(registro_normal);
				#if (com_cht == 1)
					grava_cht(registro_normal);
				#endif
				}
			else
				{
				aux_l1 = aux_l2 + intervalo_reg;
				if (prox_grava > aux_l1)
					{
					inicializa_regs();
					prox_grava = (int32)(aux_l2 + intervalo_reg);
					}
				}
		
		#endif
	#endif		
}

#if (com_alarme == 1)
	void trata_alarme(void)
	{

		#if (st5x == false)
			tem_comando_alarme = 0;
		#endif

		#if (st8500c == true)
			#if (com_rep == true)
				cor_a_r = false; 
				cor_a_s = false;	
				cor_a_t = false;
			#endif
			chtt_a = false; 
			chtc_a = false;
		#endif


		#if (com_rep == false)
			ferro_rep = false;
		#endif
		#if (monofasico == true)
			if (fp_cap == true)
				{
				status_equipamento_L = status_equipamento_L | STATUS_FP_CAP_ON;
				}
			else
				{
				status_equipamento_L = status_equipamento_L & STATUS_FP_CAP_OFF;
				}
			if (fp_ind == true) 
				{
				status_equipamento_L = status_equipamento_L | STATUS_FP_IND_ON;
				}
			else
				{
				status_equipamento_L = status_equipamento_L & STATUS_FP_IND_OFF;
				}
			if (ten_a_r == true)
				{
				status_equipamento_L = status_equipamento_L | STATUS_TEN_A_ON;
				}
			else
				{
				status_equipamento_L = status_equipamento_L & STATUS_TEN_A_OFF;
				}
			if (ten_b_r == true)
				{
				status_equipamento_L = status_equipamento_L | STATUS_TEN_B_ON;
				}
			else
				{
				status_equipamento_L = status_equipamento_L & STATUS_TEN_B_OFF;
				}
			if (cor_a_r == true)
				{
				status_equipamento_L = status_equipamento_L | STATUS_COR_A_ON;
				}
			else
				{
				status_equipamento_L = status_equipamento_L & STATUS_COR_A_OFF;
				}
			if (cor_b_r == true) 
				{
				status_equipamento_L = status_equipamento_L | STATUS_COR_B_ON;
				}
			else
				{
				status_equipamento_L = status_equipamento_L & STATUS_COR_B_OFF;
				}
			if (chtt_a == true)
				{
				status_equipamento_L = status_equipamento_L | STATUS_CHTA_A_ON;
				}
			else
				{
				status_equipamento_L = status_equipamento_L & STATUS_CHTA_A_OFF;
				}
			if (chtc_a == true)
				{
				status_equipamento_L = status_equipamento_L | STATUS_CHTC_A_ON;
				}
			else
				{
				status_equipamento_L = status_equipamento_L & STATUS_CHTC_A_OFF;
				}
			if (dem_ati == true)
				{
				status_equipamento_L = status_equipamento_L | STATUS_DEM_A_ON;
				}
			else
				{
				status_equipamento_L = status_equipamento_L & STATUS_DEM_A_OFF;
				}
			if (ferro_rep == true)
				{
				status_equipamento_L = status_equipamento_L | STATUS_ERRO_REP_ON;
				}
			else
				{
				status_equipamento_L = status_equipamento_L & STATUS_ERRO_REP_OFF;
				}
			#if (com_rep == true)
				if ((saturou_kw == true) || (saturou_kvar == true))
					{
					status_equipamento_L = status_equipamento_L | STATUS_ERRO_CONST_REP_ON;
					}
				else
					{
					status_equipamento_L = status_equipamento_L & STATUS_ERRO_CONST_REP_OFF;
					}
			#else
				status_equipamento_L = status_equipamento_L & STATUS_ERRO_CONST_REP_OFF;
			#endif
				
		#else
		
			if (fp_cap == true)
				{
				status_equipamento_L = status_equipamento_L | STATUS_FP_CAP_ON;
				}
			else
				{
				status_equipamento_L = status_equipamento_L & STATUS_FP_CAP_OFF;
				}
			if (fp_ind == true) 
				{
				status_equipamento_L = status_equipamento_L | STATUS_FP_IND_ON;
				}
			else
				{
				status_equipamento_L = status_equipamento_L & STATUS_FP_IND_OFF;
				}
			if ((ten_a_r == true) || (ten_a_s == true) || (ten_a_t == true))
				{
				status_equipamento_L = status_equipamento_L | STATUS_TEN_A_ON;
				}
			else
				{
				status_equipamento_L = status_equipamento_L & STATUS_TEN_A_OFF;
				}
			if ((ten_b_r == true) || (ten_b_s == true) || (ten_b_t == true))
				{
				status_equipamento_L = status_equipamento_L | STATUS_TEN_B_ON;
				}
			else
				{
				status_equipamento_L = status_equipamento_L & STATUS_TEN_B_OFF;
				}
			if ((cor_a_r == true) || (cor_a_s == true) || (cor_a_t == true))
				{
				status_equipamento_L = status_equipamento_L | STATUS_COR_A_ON;
				}
			else
				{
				status_equipamento_L = status_equipamento_L & STATUS_COR_A_OFF;
				}
			if ((cor_b_r == true) || (cor_b_s == true) || (cor_b_t == true))
				{
				status_equipamento_L = status_equipamento_L | STATUS_COR_B_ON;
				}
			else
				{
				status_equipamento_L = status_equipamento_L & STATUS_COR_B_OFF;
				}
			if (chtt_a == true)
				{
				status_equipamento_L = status_equipamento_L | STATUS_CHTA_A_ON;
				}
			else
				{
				status_equipamento_L = status_equipamento_L & STATUS_CHTA_A_OFF;
				}
			if (chtc_a == true)
				{
				status_equipamento_L = status_equipamento_L | STATUS_CHTC_A_ON;
				}
			else
				{
				status_equipamento_L = status_equipamento_L & STATUS_CHTC_A_OFF;
				}
			if (dem_ati == true)
				{
				status_equipamento_L = status_equipamento_L | STATUS_DEM_A_ON;
				}
			else
				{
				status_equipamento_L = status_equipamento_L & STATUS_DEM_A_OFF;
				}
			if (ferro_rep == true)
				{
				status_equipamento_L = status_equipamento_L | STATUS_ERRO_REP_ON;
				}
			else
				{
				status_equipamento_L = status_equipamento_L & STATUS_ERRO_REP_OFF;
				}
			#if (com_rep == true)
				if ((saturou_kw == true) || (saturou_kvar == true))
					{
					status_equipamento_L = status_equipamento_L | STATUS_ERRO_CONST_REP_ON;
					}
				else
					{
					status_equipamento_L = status_equipamento_L & STATUS_ERRO_CONST_REP_OFF;
					}
			#else
				status_equipamento_L = status_equipamento_L & STATUS_ERRO_CONST_REP_OFF;
			#endif
				
				

		
		#endif

		#if (home_system == false)
			if (tem_comando_alarme == 0)
				{
				#if (monofasico == true)
					if ((fp_cap == true) || (fp_ind == true) || (ten_a_r == true) || (ten_b_r == true) || (cor_a_r == true) || (cor_b_r == true) || (chtt_a == true) || (chtc_a == true) ||  (sentido_r == true) || (dem_ati == true) || (ferro_rep == true))
						{
						if (tem_alarme == 0)
							{
							if (time_out_aciona_alarme == 0)
								{
								output_high(alarme);
								tem_alarme = 1;
								#if (st5x == true)
									fled_alarme = 0;
								#elif (controlador == true)
									led_alarme = 1;
								#endif		
								return;
								}
							}
						else
							{
							time_out_aciona_alarme = 15;
							}
						}
				#else
					if ((fp_cap == true) || (fp_ind == true) || (ten_a_r == true) || (ten_a_s == true) || (ten_a_t == true) || (ten_b_r == true) || (ten_b_s == true) || (ten_b_t == true) || (cor_a_r == true) || (cor_a_s == true) || (cor_a_t == true) || (chtt_a == true) || (chtc_a == true) || (dem_ati == true) || (ferro_rep == true))
							{
						if (tem_alarme == 0)
							{
							if (time_out_aciona_alarme == 0)
								{
								output_high(alarme);
								tem_alarme = 1;
								#if (st5x == true)
									fled_alarme = 0;
								#elif ((controlador == true) || (st92 == true))
									led_alarme = 1;
								#endif
								return;
								}
							}
						else
							{
							time_out_aciona_alarme = 15;
							}
						}
				#endif
				}
	
			
				if (tem_comando_alarme == 0)
					{
					#if (monofasico == true)
						if (fp_cap == false)
							{
						 	if (fp_ind == false)
						 		{
						 		if (ten_a_r == false)
						 			{
						 			if (ten_b_r == false)
						 				{
						 				if (cor_a_r == false)
						 					{
							 				if (cor_b_r == false)
							 					{
											 	if (chtt_a == false)
											 		{
												 	if (chtc_a == false)
												 		{
													 	if (sentido_r == false)
															{
															if (dem_ati == false)
																{
																if (ferro_rep == false)
																	{
																	if (tem_alarme == 1)
																		{
																		tem_alarme = 0;
																		#if (st5x == true)
																			fled_alarme = 1;
																		#elif (controlador == true)
																			led_alarme = 0;
																		#endif		
																		output_low(alarme);		// apartir da versÿão x.48
																		}
																	time_out_aciona_alarme = 15;
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
					#else
						if (fp_cap == false)
							{
						 	if (fp_ind == false)
						 		{
						 	 	if (ten_a_r == false)
						 	 		{
						 	 		if (ten_a_s == false)
						 	 			{
						 	 	 		if (ten_a_t == false)
						 	 	 			{
						 	 	 			if (ten_b_r == false)
						 	 	 				{
						 	 	 	 			if (ten_b_s == false)
						 	 	 	 				{
									 	 	 	 	if (ten_b_t == false) 
									 	 	 	 		{
										 	 	 	 	if (cor_a_r == false) 
										 	 	 	 		{
											 	 	 	 	if (cor_a_s == false)	
											 	 	 	 		{
												 	 			if (cor_a_t == false)
												 	 				{
													 	 	 	 	if (cor_b_r == false) 
													 	 	 	 		{
														 	 	 	 	if (cor_b_s == false)	
														 	 	 	 		{
															 	 			if (cor_b_t == false)
															 	 				{
															 	 	 	  		if (chtt_a == false) 
															 	 	 	  			{
														 	 	 	   				if (chtc_a == false)
														 	 	 	   					{
																						if (dem_ati == false)
																							{
																							if (ferro_rep == false)
																								{
																								if (tem_alarme == 1)
																									{
																									tem_alarme = 0;
																									#if (st5x == true)
																										fled_alarme = 1;
																									#elif ((controlador == true) || (st92 == true))
																										led_alarme = 0;
																									#endif		
																									output_low(alarme);		// apartir da versÿão x.48
																									}
																								time_out_aciona_alarme = 15;
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
					#endif
				}
		#endif
			
	}
#endif




void decide(void)
{
	#if (st5x == true)
		trata_status_led();
	#endif
	
	decide_tensao_nominal();
	#if (portatil == true)
		#if (se_com_flex ==	true)
			if (recarrega_ponteira == true)
				{
				config_ponteiras();
				}
		#endif
		decide_que_ponteira();
	#endif
	#if (tc_fixo == true) 
		#if (se_com_flex ==	true)
			busca_mul_tc();  
		#else
			if (ultimo_tc != valor_tc)
				{
				busca_mul_tc();  
				ultimo_tc = valor_tc;
				}
		#endif
	#endif  

/* trata intervalo entre registros */
	if (virouseg == 1)
		{
		#if (com_regs == true)
			#if (com_menu == true)
				if (qmenu != 5)
					{
					if (registro_old != registro)
						{
						inicializa_flags_alarmes();
						registro_old = registro;
						#if (portatil == true)
							calcula_autonomia();
						#endif
						}
					}
			#endif
		#endif			


		if (retardo_alarmes == 0)
			{
			#if (CONTROLADOR == true)
				#if (st8500c == true)
					trata_desliga_ten_a();
				#else
					// teste se corrente menor que minimo
					#if (com_rep == true)
						#if (monofasico == true)
							if (tensao_r > TENSAO_FALTA)
						#else
							if ((tensao_r > TENSAO_FALTA) && (tensao_s > TENSAO_FALTA) && (tensao_t > TENSAO_FALTA))
						#endif
							{
							trata_corrente_minima();
							}
					#else
						trata_corrente_minima();
					#endif
					trata_desliga_ten_a();
					trata_desliga_ten_b();
					#if ((com_cht == true) && (com_rep == false))
						trata_desliga_chtt_a();
						trata_desliga_chtc_a();
					#else
						des_chtc = false;
						des_chtt = false;
					#endif
					trata_falta_capacitor();
				#endif
			#endif
				
			#if (home_system == false)
				/* teste de fator de potencia indutivo */
				trata_ala_fp_ind();
	
				/* teste de fator de potencia capacitivo */
				trata_ala_fp_cap();
				
				/* teste de tensao alta */
				trata_ala_ten_a();
	
				/* teste de tensao baixa */
				trata_ala_ten_b(); 
	
				/* teste de sobre corrente */
				trata_ala_sc(); 
	
				/* teste de sub corrente */
				trata_ala_subc(); 
	
				#if (com_alarme_demanda == true)
					// Teste de Demanda Ativa
					trata_ala_demanda();
				#else
					dem_ati = false;
				#endif
				// teste de falta de fase
				trata_falta_fase();
	
				#if (com_cht == true)
					/* teste de conteudo harmonico alto */
					trata_ala_cht();
				#endif
				#if ((st9200r == true) || (st9230r == true))
					#if (com_maximos == true)
						trata_cor_pot_maxima();
					#endif
				#endif
				
			#endif
			trata_sentido_sensor_corrente();
         	}
		else
			{
			status_equipamento_H = 0;
			status_equipamento_L = 0;
			ferro_rep = false;
			fp_ind = 0;
			fp_cap = 0;
			ten_a_r = 0;
			ten_b_r = 0;
			cor_a_r = 0;
			ffase_r = 0;
   			tem_alarme = 0;
			sentido_r = 0;
			#if (monofasico == false)
				ten_a_s = 0;
				ten_a_t = 0;
				ten_b_s = 0;
				ten_b_t = 0;
				cor_a_s = 0;
				cor_a_t = 0;
				chtt_a = 0;
				chtc_a = 0;
				ffase_s = 0;
				ffase_t = 0;
				sentido_s = 0;
				sentido_t = 0;
			#endif
			#if (controlador == true)
				falta_capacitor = false;
				des_ten_a = false;
				des_chtt = false;
				des_chtc = false;
				des_fp_ind = false;
			#endif
			#if (st8500c == true)
				fprintar = false;
				saturou_kw = false; 
				saturou_kvar = false;
			#endif
			}

		}
}




void trata_ala_ten_a(void)
{
	word tensao_r_old;
	#if (monofasico == false)
		word tensao_s_old;
		word tensao_t_old;
	#endif
	if (ala_ten_a != 0)		/* SE PROGRAMACAO DIFERENTE DE ZERO COM CRITICA */
		{
		if (modo_funca == 2)
			{
			tensao_r_old = tensao_r;
			tensao_r = (word)(soma_media_tensao_r / conta_media_tensao_r);
			#if (monofasico == false)
				tensao_s_old = tensao_s;
				tensao_s = (word)(soma_media_tensao_s / conta_media_tensao_s);
				tensao_t_old = tensao_t;
				tensao_t = (word)(soma_media_tensao_t / conta_media_tensao_t);
			#endif
			}

		if ((tipo_ligacao == 0) || (tipo_ligacao == 2))
			{
			aux_w1 = ten_nomi;
			}
		else
			{
			aux_w1 = (int16)(ten_nomi * 1.7320508);
			}
// valor para tensao acima da minima			
		aux_w2 = aux_w1;
		aux_w2 = aux_w2 * 64;
// valor para tensao abaixo da minima		
		data1_int = (word)(aux_w1 * ala_ten_a);
		data1_int = (word)(data1_int/100);
		data1_int++;
		aux_w1 = (word)(aux_w1 + data1_int);
		aux_w1 = (word)(aux_w1 * 64);
		#if (monofasico == true)
			if (tensao_r > aux_w1)
				{
				if (ten_a_r == 0)
					{
					 ten_a_r = 1;
					 tem_ocor = 1;
					tem_alarme = 0;
					}
				}
			if (tensao_r < aux_w2)
				{
				 ten_a_r = 0;
				}
		#else
			if (tensao_r > aux_w1)
				{
				if (ten_a_r == 0)
					{
					 ten_a_r = 1;
					 tem_ocor = 1;
					tem_alarme = 0;
					
					}
				}
			if (tensao_r < aux_w2)
				{
				 ten_a_r = 0;
				}
			if (tensao_s > aux_w1)
				{
				if (ten_a_s == 0)
					{
					 ten_a_s = 1;
					 tem_ocor = 1;
					tem_alarme = 0;
					}
				}
			if (tensao_s < aux_w2)
				{
				 ten_a_s = 0;
				}
			if (tensao_t > aux_w1)
				{
				if (ten_a_t == 0)
					{
					 ten_a_t = 1;
					 tem_ocor = 1;
					tem_alarme = 0;
					}
				}
			if (tensao_t < aux_w2)
				{
				 ten_a_t = 0;
				}
		#endif

		#if (com_regs == 1)
			if (tem_ocor == 1)
				{
				tem_ocor = 0;
				#if (monofasico == true)
			 		if (ten_a_r == 1)
				 		{
						 grava_ocorrencias(reg_tensao_r_alta);
						 }
				#else
					if ((ten_a_r == 1) && (ten_a_s == 1) && (ten_a_t == 1))
						{
				 		grava_ocorrencias(reg_tensao_alta);
						}
					else
						{
				 		if (ten_a_r == 1)
					 		{
							 grava_ocorrencias(reg_tensao_r_alta);
							 }
					 	if (ten_a_s == 1)
					 		{
							 grava_ocorrencias(reg_tensao_s_alta);
							 }
					 	if (ten_a_t == 1)
							 {
							 grava_ocorrencias(reg_tensao_t_alta);
							 }
						}
				#endif
				}
		#endif
		if (modo_funca == 2)
			{
			tensao_r = tensao_r_old;
			#if (monofasico == false)
				tensao_s = tensao_s_old;
				tensao_t = tensao_t_old;
			#endif
			}

		}
	else
		{
		 ten_a_r = 0;
		#if (monofasico == false)
			 ten_a_s = 0;
			 ten_a_t = 0;
		#endif
		}
	
}

void trata_ala_ten_b(void)
{
	word tensao_r_old;
	#if (monofasico == false)
		word tensao_s_old;
		word tensao_t_old;
	#endif
	if (ala_ten_b != 0)
		{
		if (modo_funca == 2)
			{
			tensao_r_old = tensao_r;
			tensao_r = (word)(soma_media_tensao_r / conta_media_tensao_r);
			#if (monofasico == false)
				tensao_s_old = tensao_s;
				tensao_s = (word)(soma_media_tensao_s / conta_media_tensao_s);
				tensao_t_old = tensao_t;
				tensao_t = (word)(soma_media_tensao_t / conta_media_tensao_t);
			#endif
			}

		if ((tipo_ligacao == 0) || (tipo_ligacao == 2))
			{
			aux_w1 = ten_nomi;
			}
		else
			{
			aux_w1 = (int16)(ten_nomi * 1.7320508);
			}
// valor para tensao acima da minima			
		aux_w2 = aux_w1;
		aux_w2 = aux_w2 * 64;

// valor para tensao abaixo da minima		
		data1_int = (word)(aux_w1 * ala_ten_b);
		data1_int = (word)(data1_int/100);
		data1_int++;
		aux_w1 = (int16)(aux_w1 - data1_int);
		aux_w1 = (int16)(aux_w1 * 64);
		#if (monofasico == true)
			if (tensao_r < aux_w1)
				{
				if (ten_b_r == 0)
					{
					 ten_b_r = 1;
					 tem_ocor = 1;
					tem_alarme = 0;
					}
				}
			if (tensao_r > aux_w2)
				{
				 ten_b_r = 0;
				}
		#else
			if (tensao_r < aux_w1)
				{
				if (ten_b_r == 0)
					{
					 ten_b_r = 1;
					 tem_ocor = 1;
					tem_alarme = 0;
					}
				}
			if (tensao_r > aux_w2)
				{
				 ten_b_r = 0;
				}
	//
			if (tensao_s < aux_w1)
				{
				if (ten_b_s == 0)
					{
					 ten_b_s = 1;
					 tem_ocor = 1;
					tem_alarme = 0;
					}
				}
			if (tensao_s > aux_w2)
				{
				 ten_b_s = 0;
				}
	//
			if (tensao_t < aux_w1)
				{
				if (ten_b_t == 0)
					{
					 ten_b_t = 1;
					 tem_ocor = 1;
					tem_alarme = 0;
					}
				}
			if (tensao_t > aux_w2)
				{
				 ten_b_t = 0;
				}
		#endif
//
		#if (com_regs == 1)
			if (tem_ocor == 1)
				{
				tem_ocor = 0;
				#if (monofasico == true)
				 	if (ten_b_r == 1)
				 		{
						 grava_ocorrencias(reg_tensao_r_baixa);
						 }
				#else
					if ((ten_b_r == 1) && (ten_b_s == 1) && (ten_b_t == 1))
					 	{
					 	grava_ocorrencias(reg_tensao_baixa);
		   				}
			   		else
						{
					 	if (ten_b_r == 1)
					 		{
							 grava_ocorrencias(reg_tensao_r_baixa);
							 }
					 	if (ten_b_s == 1)
					 		{
							 grava_ocorrencias(reg_tensao_s_baixa);
							 }
					 	if (ten_b_t == 1)
					 		{
							 grava_ocorrencias(reg_tensao_t_baixa);
							 }
						}
				#endif
				}		
		#endif
		}
	else
		{
		 ten_b_r = 0;
		#if (monofasico == false)
			 ten_b_s = 0;
			 ten_b_t = 0;
		#endif
		}

}



void trata_ala_sc(void)
{			
	#if (st8500c == true)
		cor_a_r = 0;
		#if (monofasico == false)
			cor_a_s = 0;
			cor_a_t = 0;
		#endif
	#else
		if(ala_sc == 0)
			{
			cor_a_r = 0;
			#if (monofasico == false)
				cor_a_s = 0;
				cor_a_t = 0;
			#endif
			}
		else 		/* SE PROGRAMACAO DIFERENTE DE ZERO COM CRITICA */
			{
			if (corrente_r < 8)
				{
				cor_a_r = 0;
				cor_b_r = 0;
				}
			#if (monofasico == false)
				if (corrente_s < 8)
					{
					cor_a_s = 0;
					cor_b_s = 0;
					}
				if (corrente_t < 8)
					{
					cor_a_t = 0;
				 	cor_b_t = 0;
					}
			#endif
			#if (monofasico == true)
				if (corrente_r < 8)
					{
					return;
					}
			#else
				if ((corrente_r < 8) && (corrente_s < 8) && (corrente_t < 8))
					{
					return;
					}
			#endif
			#if (tc_fixo == true)
				aux_l1 = valor_tc_fixo;
			#else
				aux_l1 = valor_tc;
			#endif
			aux_w1 = (int16)(((aux_l1 * ala_sc) / 100));
			aux_w1 = aux_w1 * 8; 
			aux_w2 = aux_w1 - (aux_w1 / 20);
			if (corrente_r > aux_w1)
				{
				if (cor_a_r == 0)
					{
					 cor_a_r = 1;
					 cor_b_r = 0;
		             tem_ocor = 1;
					 tem_alarme = 0;
					}
				}
			else if (corrente_r < aux_w2)
				{
				 cor_a_r = 0;
				}
			#if (monofasico == false)
				if (corrente_s > aux_w1)
					{
					if (cor_a_s == 0)
						{
						 cor_a_s = 1;
						 cor_b_s = 0;
						tem_ocor = 1;
						tem_alarme = 0;
						}
					}
				else if (corrente_s < aux_w2)
					{
					 cor_a_s = 0;
					}
				if (corrente_t > aux_w1)
					{
					if (cor_a_t == 0)
						{
						 cor_a_t = 1;
						 cor_b_t = 0;
						tem_ocor = 1;
						tem_alarme = 0;
						}
					}
				else if (corrente_t < aux_w2)
					{
					 cor_a_t = 0;
					}
			#endif
			#if (com_regs == 1)
				if (tem_ocor == 1)
					{
					tem_ocor = 0;
					#if (monofasico == true)
					 	if (cor_a_r == 1)
					 		{
							 grava_ocorrencias(reg_cor_r_alta);
							 }
					#else
						if ((cor_a_r == 1) && (cor_a_s == 1) && (cor_a_t == 1))
							{
						 	grava_ocorrencias(reg_corrente_alta);
						 	}
						else
							{
						 	if (cor_a_r == 1)
						 		{
								 grava_ocorrencias(reg_cor_r_alta);
								 }
						 	if (cor_a_s == 1)
						 		{
								 grava_ocorrencias(reg_cor_s_alta);
								 }
						 	if (cor_a_t == 1)
						 		{
								 grava_ocorrencias(reg_cor_t_alta);
								 }
							}
					#endif
					}
			#endif
			}
	#endif
}

#if (com_cht == 1)
	void trata_ala_cht(void)
	{
	if (modo_funca == 2)
		{
		chtt_a = 0;
		chtc_a = 0;
		return;
		}
		if (ala_chtt == 0)
			{
			chtt_a = 0;
			}
		else
			{
		/* Testa conteudo harmonico de tensao */				
			#if (monofasico == true)
				data1_int = (int16)(CHT_tr[0]);
			#else
				data1_int = (int16)((CHT_tr[0] + CHT_ts[0]  + CHT_tt[0]) / 3);
			#endif
			aux_w1 = ala_chtt;
			aux_w1 = aux_w1 << 6;
			if ( data1_int > aux_w1)
				{
				if (chtt_a == 0)
					{
					#if (com_regs == 1)
						grava_ocorrencias(reg_chtt_alto);
					#endif
					tem_alarme = 0;
					chtt_a = 1;
					}
				}
			else
				{
				chtt_a = 0;
				}
			}
		if (ala_chtc == 0)
			{
			chtc_a = 0;
			}
		else
			{
		/* Testa conteudo harmonico de corrente */				
			#if (monofasico == true)
				data1_int = (int16)(CHT_cr[0]);
			#else
				data1_int = (int16)((CHT_cr[0] + CHT_cs[0]  + CHT_ct[0]) / 3);
			#endif
			aux_w1 = ala_chtc;
			aux_w1 = aux_w1 << 6;
			if ( data1_int > aux_w1)
				{
				if (chtc_a == 0)
					{
					#if (com_regs == 1)
						grava_ocorrencias(reg_chtc_alto);
					#endif				
					tem_alarme = 0;
					chtc_a = 1;
					}
				}
			else
				{
				chtc_a = 0;
				}
			}
	}
#endif

void trata_ala_fp_ind(void)
{			
	#if (controlador == true)
		#if ((ST8100C == true) || (ST8200C == true) || (ST8300C == true))
			for (aux_b1 = 0; aux_b1 < (nro_bancos_capacitor -1); aux_b1++)
				{
				if (banco_acionado[aux_b1] == false)
					{
					fp_ind = 0;
					falta_capacitor = false;
					return;
					}
				}
		#endif
	#endif
	#if (monofasico == true)
		if (fator_pot_r < 0 )
			{
			fp_cap = 0;
			if (ala_fp_ind < 100)
				{
				aux_l1 = fator_pot_r * (-1);
				data1_int = (aux_l1 * 100)/ 1024;
				if (data1_int < ala_fp_ind)
					{
					if (fp_ind == 0)
						{
						fp_ind = 1;
						#if (com_regs == 1)
							grava_ocorrencias(reg_fp_ind);
						#endif
						tem_alarme = 0;
						}
					}
				else
					{
					fp_ind = 0;
					}
				}
			}
		else
			{
			fp_ind = 0;
			}
	#else
		if (fator_pot < 0 )
			{
			fp_cap = 0;
			if (ala_fp_ind < 100)
				{
				aux_l1 = fator_pot * (-1);
				data1_int = (aux_l1 * 100)/ 1024;
				if (data1_int < ala_fp_ind)
					{
					if (fp_ind == 0)
						{
						fp_ind = 1;
						#if (com_regs == 1)
							grava_ocorrencias(reg_fp_ind);
						#endif
						tem_alarme = 0;
						}
					}
				else
					{
					fp_ind = 0;
					}
				}
			}
		else
			{
			fp_ind = 0;
			}
	#endif
}

#if (controlador == true)
	#if ((ST8100C == true) || (ST8200C == true) || (ST8300C == true))
		void trata_falta_capacitor(void)
		{			
			for (aux_b1 = 0; aux_b1 < (nro_bancos_capacitor -1); aux_b1++)
				{
				if (banco_acionado[aux_b1] == false)
					{
					falta_capacitor = false;
					return;
					}
				}
			#if (monofasico == true)
				if (fator_pot_r < 0 )
					{
					aux_l1 = fator_pot_r * (-1);
					data1_int = (aux_l1 * 100)/ 1024;
					if (data1_int < set_point)
						{
						if (falta_capacitor == false)
							{
							falta_capacitor = true;
							#if (com_regs == 1)
								grava_ocorrencias(reg_faltou_cap);
							#endif
							tem_alarme = 0;
							}
						}
					else
						{
						falta_capacitor = false;
						}
					}
			#else
				if (fator_pot < 0 )
					{
					aux_l1 = fator_pot * (-1);
					data1_int = (aux_l1 * 100)/ 1024;
					if (data1_int < set_point)
						{
						if (falta_capacitor == false)
							{
							falta_capacitor = true;
							#if (com_regs == 1)
								grava_ocorrencias(reg_faltou_cap);
							#endif
							tem_alarme = 0;
							}
						}
					else
						{
						falta_capacitor = false;
						}
					}
			#endif
		}
	#endif
#endif


void trata_ala_fp_cap(void)
{			
	#if (controlador == true)
		#if ((ST8100C == true) || (ST8200C == true) || (ST8300C == true))
			for (aux_b1 = 0; aux_b1 < (nro_bancos_capacitor -1); aux_b1++)
				{
				if (banco_acionado[aux_b1] == 1)
					{
					fp_cap = 0;
					return;
					}
				}
		#endif
	#endif
		
	#if (monofasico == true)
		if ((fator_pot_r > 0 ) && (fator_pot_r < 1025))
			{
			fp_ind = 0;
			if (ala_fp_cap < 100)
				{
				aux_l1 = fator_pot_r;
				data1_int = (aux_l1 * 100)/ 1024;
				if (data1_int < ala_fp_cap)
					{
					if (fp_cap == 0)
						{
						fp_cap = 1;
						#if (com_regs == 1)
	   						grava_ocorrencias(reg_fp_cap);
						#endif
						tem_alarme = 0;
						}
					}
				else
					{
					fp_cap = 0;
					}
				}
			}
		else
			{
			fp_cap = 0;
			}
	#else
		if ((fator_pot > 0 ) && (fator_pot < 1025))
			{
			fp_ind = 0;
			if (ala_fp_cap < 100)
				{
				aux_l1 = fator_pot;
				data1_int = (aux_l1 * 100)/ 1024;
				if (data1_int < ala_fp_cap)
					{
					if (fp_cap == 0)
						{
						fp_cap = 1;
						#if (com_regs == 1)
	   						grava_ocorrencias(reg_fp_cap);
						#endif
						tem_alarme = 0;
						}
					}
				else
					{
					fp_cap = 0;
					}
				}
			}
		else
			{
			fp_cap = 0;
			}
	#endif
}




void trata_falta_fase(void)
{
//	
	if (ala_ten_b == 0)
		{
		ffase_r = 0;
		#if (monofasico == false)
			ffase_s = 0;
			ffase_t = 0;
		#endif
		return;
		}

	#if (monofasico == true)
		if (tensao_r < TENSAO_FALTA)
			{
			if (ffase_r == 0)
				{
				#if (com_regs == 1)
				 grava_ocorrencias(reg_falta_fases);
				#endif
				tem_alarme = 0;
				ffase_r = 1;
				}
			}
		else
			{
			if (tensao_r < TENSAO_FALTA)
				{
				if (ffase_r == 0)
					{
					#if (com_regs == 1)
					 grava_ocorrencias(reg_falta_fase_r);
					#endif
					tem_alarme = 0;
					ffase_r = 1;
					}
				}
			else if (tensao_r > (TENSAO_FALTA + 256))
				{
				ffase_r = 0;
				}
			}
	#else
		if ((tensao_r < TENSAO_FALTA) && (tensao_s < TENSAO_FALTA) && (tensao_t < TENSAO_FALTA))
			{
			if ((ffase_r == 0) || (ffase_s == 0) || (ffase_t == 0))
				{
				#if (com_regs == 1)
				 grava_ocorrencias(reg_falta_fases);
				#endif
				tem_alarme = 0;
				ffase_r = 1;
				ffase_s = 1;
				ffase_t = 1;
				}
			}
		else
			{
			if (tensao_r < TENSAO_FALTA)
				{
				if (ffase_r == 0)
					{
					#if (com_regs == 1)
					 grava_ocorrencias(reg_falta_fase_r);
					#endif
					tem_alarme = 0;
					ffase_r = 1;
					}
				}
			else if (tensao_r > (TENSAO_FALTA + 256))
				{
				ffase_r = 0;
				}
		//
			if (tensao_s < TENSAO_FALTA)
				{
				if (ffase_s == 0)
					{
					#if (com_regs == 1)
					 grava_ocorrencias(reg_falta_fase_s);
					#endif
					tem_alarme = 0;
					ffase_s = 1;
					}
				}
			else if (tensao_s > (TENSAO_FALTA + 256))
				{
				ffase_s = 0;
				}
		//
			if (tensao_t < TENSAO_FALTA)
				{
				if (ffase_t == 0)
					{
					#if (com_regs == 1)
					 grava_ocorrencias(reg_falta_fase_t);
					#endif
					tem_alarme = 0;
					ffase_t = 1;
					}
				}
			else if (tensao_t > (TENSAO_FALTA + 256))
				{
				ffase_t = 0;
				}
			}
	#endif
	
}

void trata_ala_subc(void)
{
	#if (st8500c == true)
		cor_b_r = 0;
		#if (monofasico == false)
			cor_b_s = 0;
			cor_b_t = 0;
		#endif
	#else
		if (ala_subc == 0)
			{
			cor_b_r = 0;
			#if (monofasico == false)
				cor_b_s = 0;
				cor_b_t = 0;
			#endif
			}
		else		/* SE PROGRAMACAO DIFERENTE DE ZERO COM CRITICA */
			{
			if (corrente_r < 8)
				{
				 cor_a_r = 0;
				 cor_b_r = 0;
				}
			#if (monofasico == false)
				if (corrente_s < 8)
					{
					 cor_a_s = 0;
					 cor_b_s = 0;
					}
				if (corrente_t < 8)
					{
					 cor_a_t = 0;
					 cor_b_t = 0;
					}
			#endif
			#if (monofasico == true)
				if (corrente_r < 8)
					{
					return;
					}
			#else
				if ((corrente_r < 8) && (corrente_s < 8) && (corrente_t < 8))
					{
					return;
					}
			#endif
	
			#if (tc_fixo == true)
				aux_l1 = valor_tc_fixo;
			#else
				aux_l1 = valor_tc;
			#endif
			aux_w1 = (int16)(((aux_l1 * ala_subc) / 100));
			aux_w1 = aux_w1 * 8; 
			aux_w2 = aux_w1 - (aux_w1 / 20);
	
			if (corrente_r < aux_w1)
				{
				if (cor_b_r == 0)
					{
					cor_b_r = 1;
					cor_a_r = 0;
					tem_ocor = 1;
					tem_alarme = 0;
					}
				}
			else if (corrente_r > aux_w2)
				{
				 cor_b_r = 0;
				}
			#if (monofasico == false)
				if (corrente_s < aux_w1)
					{
					if (cor_b_s == 0)
						{
						 cor_b_s=1;
						 cor_a_s = 0;
						tem_ocor = 1;
						tem_alarme = 0;
						}
					}
				else if (corrente_s > aux_w2)
					{
					 cor_b_s = 0;
					}
				if (corrente_t < aux_w1)
					{
					if (cor_b_t == 0)
						{
						 cor_b_t = 1;
						 cor_a_t = 0;
						tem_ocor = 1;
						tem_alarme = 0;
						}
					}
				else if (corrente_t > aux_w2)
					{
					 cor_b_t = 0;
					}
			#endif
			#if (com_regs == 1)
				if (tem_ocor == 1)
					{
					tem_ocor = 0;
					#if (monofasico == true)
					 	if (cor_b_r == 1)
					 		{
						 	grava_ocorrencias(reg_corrente_baixa);
							}
					#else
						if ((cor_b_r == 1) && (cor_b_s == 1) && (cor_b_t == 1))
							{
						 	grava_ocorrencias(reg_corrente_baixa);
						 	}
						else
							{
						 	if (cor_b_r == 1)
						 		{
								 grava_ocorrencias(reg_cor_r_baixa);
								 }
						 	if (cor_b_s == 1)
						 		{
								 grava_ocorrencias(reg_cor_s_baixa);
								 }
						 	if (cor_b_t == 1)
						 		{
								 grava_ocorrencias(reg_cor_t_baixa);
								 }
							}
					#endif
					}
			#endif
			}
	#endif
}

#if (com_alarme_demanda == true)
	void trata_ala_demanda(void)
	{
		#if (st8500c == true)
			if(ala_demanda_ativa == 0)
				{
				dem_ati = false;
				}
			else
				{
				if (dem_ativa_proj > dem_contratada)
					{
					aux_f2 = (float)(ala_demanda_ativa);
					aux_f2 = ((float)(aux_f2 + 100) / 100);
					aux_f1 = (float)(dem_contratada);
					aux_f1 = (float)(aux_f1 * aux_f2);
					aux_l1 = (int32)(aux_f1);
					if (dem_ativa_proj > aux_l1)
						{
						if (dem_ati == false)
							{
							dem_ati = true;
							#if (com_regs == true)
							 	grava_ocorrencias(reg_demanda_ativa_alta);
							#endif
						 	}
						}
					else
						{
						if (ala_demanda_ativa > 1)
							{
							aux_f2 = (float)(ala_demanda_ativa - 1);
							aux_f2 = ((float)(aux_f2 + 100) / 100);
							aux_f1 = (float)(dem_contratada);
							aux_f1 = (float)(aux_f1 * aux_f2);
							aux_l1 = (int32)(aux_f1);
							if (dem_ativa_proj < aux_l1)
								{
								dem_ati = false;
								}
							}
						else if (dem_ativa_proj < aux_l1)
							{
							dem_ati = false;
							}
						}
					}
				else
					{
					dem_ati = false;
					}
				}
		
		#else
			if(ala_demanda_ativa == 0)
				{
				dem_ati = false;
				}
			else
				{
				aux_f1 = (float)(dem_ativa);
				aux_f1 = (float)(aux_f1 * mul_tc);
				aux_w1 = (word)(aux_f1 * valor_tp);
				aux_w2 = ala_demanda_ativa;
				if (ala_demanda_ativa > 1)
					{
					aux_w2 = (aux_w2 / 100) + 1;
					aux_w2 = ala_demanda_ativa - aux_w2;
					}
				if (aux_w1 > ala_demanda_ativa)
					{
					if (dem_ati == false)
						{
						dem_ati = true;
						#if (com_regs == true)
						 	grava_ocorrencias(reg_demanda_ativa_alta);
						#endif
					 	}
					}
				else if (aux_w1 < aux_w2)
					{
					dem_ati = false;
					}
				}
		#endif
	}
#endif

/* decide que tensÿão nonimal estÿá */
void decide_tensao_nominal(void)	
{
	#if (monofasico == true)
		if (tipo_ligacao == 0)
			{
			if (tensao_r > (160 * 64))	
				{
				if (tensao_r > (242 * 64)) 		// trocado para 242(220+ 10%) em 30/11 causa problema obispa	(250 * 64)) 
					{
					if (ten_nomi != 254)
				  		{
						write_word(ee_ten_nomi, 254);
						#if (com_regs == 1)
							grava_ocorrencias(reg_troca_tensao);
						#endif
						retardo_alarmes = 10;
					 	ten_nomi = 254;
				  		}
					}
				else
					{
					if (ten_nomi != 220)
				  		{
						write_word(ee_ten_nomi, 220);
						#if (com_regs == 1)
							grava_ocorrencias(reg_troca_tensao);
						#endif
						retardo_alarmes = 10;
					 	ten_nomi = 220;
				  		}
				 	}
				}
			else
				{
				  if (ten_nomi != 127)
				  	{
					write_word(ee_ten_nomi, 127);
					#if (com_regs == 1)
						grava_ocorrencias(reg_troca_tensao);
					#endif
					retardo_alarmes = 10;
					 ten_nomi = 127;
				  	}
				}
			}
		else
			{
			if (tensao_r > (300 * 64))			// alterado em 07/07/2006, estava dando ero quandoem FF e tansao < 400V, sempre assumia 127V
				{
				if (tensao_r > (400 * 64)) 		
					{
					if (ten_nomi != 254)
				  		{
						write_word(ee_ten_nomi, 254);
						#if (com_regs == 1)
							grava_ocorrencias(reg_troca_tensao);
						#endif
						retardo_alarmes = 10;
					 	ten_nomi = 254;
				  		}
					}
				else
					{
					if (ten_nomi != 220)
				  		{
						write_word(ee_ten_nomi, 220);
						#if (com_regs == 1)
							grava_ocorrencias(reg_troca_tensao);
						#endif
						retardo_alarmes = 10;
					 	ten_nomi = 220;
				  		}
				 	}
				}
			else
				{
				if (ten_nomi != 127)
				  	{
					write_word(ee_ten_nomi, 127);
					#if (com_regs == 1)
						grava_ocorrencias(reg_troca_tensao);
					#endif
					retardo_alarmes = 10;
					ten_nomi = 127;
				  	}
				}
			}
	#else
		if (tensao_r > (160 * 64))	
			{
			if (tensao_r > (242 * 64)) 		// trocado para 242(220+ 10%) em 30/11 causa problema obispa	(250 * 64)) 
				{
				if (ten_nomi != 254)
			  		{
					write_word(ee_ten_nomi, 254);
					#if (com_regs == 1)
						grava_ocorrencias(reg_troca_tensao);
					#endif
					retardo_alarmes = 10;
				 	ten_nomi = 254;
			  		}
				}
			else
				{
				if (ten_nomi != 220)
			  		{
					write_word(ee_ten_nomi, 220);
					#if (com_regs == 1)
						grava_ocorrencias(reg_troca_tensao);
					#endif
					retardo_alarmes = 10;
				 	ten_nomi = 220;
			  		}
			 	}
			}
		else
			{
			  if (ten_nomi != 127)
			  	{
				write_word(ee_ten_nomi, 127);
				#if (com_regs == 1)
					grava_ocorrencias(reg_troca_tensao);
				#endif
				retardo_alarmes = 10;
				 ten_nomi = 127;
			  	}
			}
	#endif

	os_ten_r = os_ten_r1;
	os_ten_s = os_ten_s1;
	os_ten_t = os_ten_t1;
	
}


//	signed word os_cor_pt_r[NRO_POSI_TC];
//	signed word os_cor_pt_s[NRO_POSI_TC];
//	signed word os_cor_pt_t[NRO_POSI_TC];

//void calcula_vref_cr(void)
//{
// 	aux_l1 = 0;
//	for (aux_calc = 0; aux_calc < NRO_AMOSTRAS; aux_calc++)
//		{
//		aux_l1 += buf_corrente_r[aux_calc];
//		}
//	aux_l1 = aux_l1 / NRO_AMOSTRAS;
// 	data1_int = (word)(aux_l1);
// 	vref_cr = data1_int;
//}
//
//#if (monofasico == false)
//	void calcula_vref_cs(void)
//	{
//	 	aux_l1 = 0;
//		for (aux_calc = 0; aux_calc < NRO_AMOSTRAS; aux_calc++)
//			{
//			aux_l1 += buf_corrente_s[aux_calc];
//			}
//		aux_l1 = aux_l1 / NRO_AMOSTRAS;
//	 	data1_int = (word)(aux_l1);
//	 	vref_cs = data1_int;
//	}
//	void calcula_vref_ct(void)
//	{
//	 	aux_l1 = 0;
//		for (aux_calc = 0; aux_calc < NRO_AMOSTRAS; aux_calc++)
//			{
//			aux_l1 += buf_corrente_t[aux_calc];
//			}
//		aux_l1 = aux_l1 / NRO_AMOSTRAS;
//	 	data1_int = (word)(aux_l1);
//	 	vref_ct = data1_int;
//	}
//#endif

#if (portatil == true)

	void atualiza_ganho(char ponteira)
	{
		#if (versao_pci_st96 > 3)		//Para versÿões 4,5 e 6.
			ganho_ponteira = ganhos_ponteiras[ponteira];
			#if (versao_pci_st96 > 4)		//Para versÿões 5 e 6.
				ajustar_ponteira = true;
			#else
				pga_gain_set(ganho_ponteira, 1); 
				pga_gain_set(ganho_ponteira, 2); 
				pga_gain_set(ganho_ponteira, 3); 
				pga_gain_set(0, 4); 
			#endif
		#endif
	}

	#if (se_com_flex ==	true)
		void ve_ref_ponteiras(void)
		{
			if ((tipo_ponteira >= INICIO_LEM) && (tipo_ponteira <= FIM_LEM))
				{
				calcula_vref_cr();
				calcula_vref_cs();
				calcula_vref_ct();
				}
			else
				{
				vref_cr = vref;
				vref_cs = vref;
				vref_ct = vref;
				}
		}
		void decide_que_ponteira(void)
		{

			ve_ref_ponteiras();
			
			os_cor_r = os_cor_pt_r[tipo_ponteira];
			os_cor_s = os_cor_pt_s[tipo_ponteira];
			os_cor_t = os_cor_pt_t[tipo_ponteira];
			os_pot_r = os_pot_pt_r[tipo_ponteira];
			os_pot_s = os_pot_pt_s[tipo_ponteira];
			os_pot_t = os_pot_pt_t[tipo_ponteira];

			off_cor_r = off_set_fp[tipo_ponteira];

			erro = 1;
			if ((tipo_ponteira >= 0) && (tipo_ponteira < (NRO_POSI_TABELA_TIPO_PT+1)))
				{
				erro = 0;
				atualiza_ganho(tipo_ponteira);
				}

			if (erro == 1)
				{
				tipo_ponteira =  read_word(ee_tipo_ponteira);
				if ((tipo_ponteira >= 0) && (tipo_ponteira < (NRO_POSI_TABELA_TIPO_PT+1)))
					{
					erro = 0;
					atualiza_ganho(tipo_ponteira);
					break;
					}
				if (erro == 1)
					{
					erro = 0;
					tipo_ponteira =  2;		//Alicate de 1000A
					valor_tc = tabela_pt[tipo_ponteira];
					write_byte(ee_tipo_ponteira, tipo_ponteira);
					atualiza_ganho(tipo_ponteira);
					}
				}
		}
		#if (versao_pci_st96 >= 6)
			#if (selecao_pt_auto == true)
				void selecao_ponteira_auto(void)
				{
					float mul_pt;
					aux_w1 = corrente_r;
					if (corrente_s > aux_w1)
						{
						aux_w1 = corrente_s;
						}
					if (corrente_t > aux_w1)
						{
						aux_w1 = corrente_t;
						}
					// aux_w1 com maior corrente	
					if ((tipo_ponteira > 1) && (tipo_ponteira < (5)))
						{
						mul_pt = tabela_mul_tc[tipo_ponteira];
						aux_f1 = (float)(aux_w1);
						aux_f1 = (float)(aux_f1 * mul_pt);
						aux_w1 = (word)(aux_f1);
						if (tipo_ponteira == (2))
							{
							aux_w2 =  tabela_pt[2];
							aux_w3 = aux_w2 / 4;
							aux_w2 = (aux_w2 + aux_w3) * 8;
							if (aux_w1 > aux_w2)
								{
								time_out_troca_ponteira = 15;
							 	grava_ocorrencias(reg_troca_pt_1);
							 	tipo_ponteira = 3;
								valor_tc = tabela_pt[tipo_ponteira];
								write_byte(ee_tipo_ponteira, tipo_ponteira);
								recarrega_ponteira = true;
								atualiza_ganho(tipo_ponteira);
								}
							}
						else if (tipo_ponteira == (3))
							{
							aux_w2 =  tabela_pt[3];
							aux_w3 = aux_w2 / 4;
							aux_w2 = (aux_w2 + aux_w3) * 8;
							if (aux_w1 > aux_w2)
								{
								time_out_troca_ponteira = 15;
							 	grava_ocorrencias(reg_troca_pt_2);
							 	tipo_ponteira = 4;
								valor_tc = tabela_pt[tipo_ponteira];
								write_byte(ee_tipo_ponteira, tipo_ponteira);
								recarrega_ponteira = true;
								atualiza_ganho(tipo_ponteira);
								}
							else if (aux_w1 < (tabela_pt[2] * 8))
								{
								time_out_troca_ponteira = 15;
							 	grava_ocorrencias(reg_troca_pt_0);
							 	tipo_ponteira = 2;
								valor_tc = tabela_pt[tipo_ponteira];
								write_byte(ee_tipo_ponteira, tipo_ponteira);
								recarrega_ponteira = true;
								atualiza_ganho(tipo_ponteira);
								}
							}
						else if (tipo_ponteira == (4))
							{
							if (aux_w1 < (tabela_pt[(3)] * 8))
								{
								time_out_troca_ponteira = 15;
							 	grava_ocorrencias(reg_troca_pt_1);
							 	tipo_ponteira = 3;
								valor_tc = tabela_pt[tipo_ponteira];
								write_byte(ee_tipo_ponteira, tipo_ponteira);
								recarrega_ponteira = true;
								atualiza_ganho(tipo_ponteira);
								}
							}
						}
				}
			#endif
		#endif
	#else
		void decide_que_ponteira(void)
		{
			erro=1;
			for (aux_b1=0; aux_b1 < NRO_POSI_TC; aux_b1++)
				{
				if (valor_tc == tabela_tc[aux_b1])
					{
					erro=0;
					posi_tc = aux_b1;
					os_cor_r = os_cor_pt_r[aux_b1];
					os_cor_s = os_cor_pt_s[aux_b1];
					os_cor_t = os_cor_pt_t[aux_b1];
					os_pot_r = os_pot_pt_r[aux_b1];
					os_pot_s = os_pot_pt_s[aux_b1];
					os_pot_t = os_pot_pt_t[aux_b1];
					atualiza_ganho(aux_b1);
					break;
					}
				}
			if (erro == 1)
				{
				valor_tc =  read_word(ee_valor_tc);
				for (aux_b1=0; aux_b1 < NRO_POSI_TC; aux_b1++)
					{
					if (valor_tc == tabela_tc[aux_b1])
						{
						posi_tc = aux_b1;
						erro=0;
						os_cor_r = os_cor_pt_r[aux_b1];
						os_cor_s = os_cor_pt_s[aux_b1];
						os_cor_t = os_cor_pt_t[aux_b1];
						os_pot_r = os_pot_pt_r[aux_b1];
						os_pot_s = os_pot_pt_s[aux_b1];
						os_pot_t = os_pot_pt_t[aux_b1];
						atualiza_ganho(aux_b1);
						break;
						}
					}
				if (erro == 1)
					{
					valor_tc = valor_ponteira_default;		
					posi_tc = posi_ponteira_default;
					os_cor_r = os_cor_pt_r[posi_ponteira_default];
					os_cor_s = os_cor_pt_s[posi_ponteira_default];
					os_cor_t = os_cor_pt_t[posi_ponteira_default];
					os_pot_r = os_pot_pt_r[posi_ponteira_default];
					os_pot_s = os_pot_pt_s[posi_ponteira_default];
					os_pot_t = os_pot_pt_t[posi_ponteira_default];
					write_word(ee_valor_tc, valor_tc);
					atualiza_ganho(2);
					}
				}
		#if (tc_fixo == true) 
			if (ultima_tc != valor_tc)
				{
				busca_mul_tc();  
				ultima_tc = valor_tc;
				}
		#endif  
		}
	#endif
#endif	


void trata_sentido_sensor_corrente(void)
{
	
	#if ((st8500c == true) && (com_rep == true))
		sentido_r = false;
		sentido_s = false;
		sentido_t = false;
	#else
		#if (monofasico == true)
			if (corrente_r > 80)
				{
				if (sentido_r == true)
					{
					if (fsentido_r == 0)
						{
						#if (com_regs == 1)
						 	grava_ocorrencias(reg_tc_inv_r);
						#endif
						fsentido_r = 1;
						tem_alarme = 0;
						}
					}
				else
					{
					fsentido_r = 0;
					}
				}
			else
				{
				fsentido_r = 0;
				}
		#else
			if (corrente_r > 80)
				{
				if (sentido_r == true)
					{
					if (fsentido_r == 0)
						{
						#if (com_regs == 1)
						 	grava_ocorrencias(reg_tc_inv_r);
						#endif
						fsentido_r = 1;
						tem_alarme = 0;
						}
					}
				else
					{
					fsentido_r = 0;
					}
				}
			else
				{
				fsentido_r = 0;
				}
			if (corrente_s > 80)
				{
				if (sentido_s == true)
					{
					if (fsentido_s == 0)
						{
						#if (com_regs == 1)
						 	grava_ocorrencias(reg_tc_inv_s);
						#endif
						fsentido_s = 1;
						tem_alarme = 0;
						}
					}
				else
					{
					fsentido_s = 0;
					}
				}
			else
				{
				fsentido_s = 0;
				}
			if (corrente_t > 80)
				{
				if (sentido_t == true)
					{
					if (fsentido_t == 0)
						{
						#if (com_regs == 1)
						 	grava_ocorrencias(reg_tc_inv_t);
						#endif
						fsentido_t = 1;
						tem_alarme = 0;
						}
					}
				else
					{
					fsentido_t = 0;
					}
				}
			else
				{
				fsentido_t = 0;
				}
		#endif
	#endif
	
}


#if ((st9200r == true) || (st9230r == true))
	#if (com_maximos == true)
		void trata_cor_pot_maxima()
		{
			if (corrente_r > cor_maxima_r)
				{
				cor_maxima_r = corrente_r;
				}
			if (corrente_s > cor_maxima_s)
				{
				cor_maxima_s = corrente_s;
				}
			if (corrente_t > cor_maxima_t)
				{
				cor_maxima_t = corrente_t;
				}
			if (pot_ativa_r > pot_ativa_max_r)
				{
				pot_ativa_max_r = pot_ativa_r;
				}
			if (pot_ativa_s > pot_ativa_max_s)
				{
				pot_ativa_max_s = pot_ativa_s;
				}
			if (pot_ativa_t > pot_ativa_max_t)
				{
				pot_ativa_max_t = pot_ativa_t;
				}

		}
	#endif
#endif
