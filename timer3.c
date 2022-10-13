/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_INTS                                                        *
; Funcao: MODULO Interrupções 					  						 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 06/06/2003                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/

#INT_TIMER3  // FAST //a cada ???? ms
void temporizador3(void){
#if (ST8500C == true)
	lendo_cht == false;
#endif
#if (com_cht == true)
	#if ((st94 == true) || (controlador == true))
		word leitura;
	#elif (st5x==true)		
		#if  (st5000c_rev12 == true)
			word leitura;
		#endif
	#endif
	if (lendo_cht == true)
		{
		ler_ad_t3 = 0;
		if (freq_50HZ == 1)
			{
			set_timer3(valor_timer3_CHT_50HZ);
			}
		else
			{
			set_timer3(valor_timer3_CHT_60HZ);
			}			
		morder_t3 = 1;
		ler_ad = 1;
		passo_tensao = 0;
		med_ten_ok = 0;
		ler_ad_t3 = 0;
		#if (controlador == true)
			if (tipo_ligacao == 1) // FF
				{
				passo_corrente_r = off_cor_r + (NRO_AMOSTRAS/4);		//+ off_cor_s;
				}
			else
				{
				passo_corrente_r = off_cor_r;
				}
			trata_tempo_falta_energia();
		#else
			passo_corrente = off_cor_r;
			passo_corrente_r = off_cor_r;
		#endif
		#if (st94 == true)
			switch(que_ad)
				{
				case 0:
					{
					leitura = (word)(le_canal_0());
					break;
					}
				case 1:
					{
					leitura = (word)(le_canal_1());
					break;
					}
				case 2:
					{
					leitura = (word)(le_canal_2());
					break;
					}
				case 4:
					{
					leitura = (word)(le_canal_4());
					break;
					}
				case 5:
					{
					leitura = (word)(le_canal_5());
					break;
					}
				case 6:
					{
					leitura = (word)(le_canal_6());
					break;
					}
				default:
					{
					leitura = 2048;
					}
				}
				buffer_cht[passo_rd_cht] = leitura;
				goto fim_timer3;
		#elif (st5x == true)
			#if(st5000c_rev12 == true)
				switch(que_ad)
					{
					case 0:
						{
						leitura = (word)(le_canal_0());
						break;
						}
					case 1:
						{
						leitura = (word)(le_canal_1());
						break;
						}
					case 2:
						{
						leitura = (word)(le_canal_2());
						break;
						}
					case 4:
						{
						leitura = (word)(le_canal_4());
						break;
						}
					case 5:
						{
						leitura = (word)(le_canal_5());
						break;
						}
					case 6:
						{
						leitura = (word)(le_canal_6());
						break;
						}
					default:
						{
						leitura = 2048;
						}
					}
					buffer_cht[passo_rd_cht] = leitura;
					goto fim_timer3;
			#endif
		#elif ((ST8100C == true) || (ST8200C == true))
			if (que_ad == 0)
				{
				set_adc_channel(2);
				}
			else
				{
				set_adc_channel(0);
				}
			delay_us(5);
			buffer_cht[passo_rd_cht] = (signed word)((read_adc() << 2));
			goto fim_timer3;
		#elif (ST8300C == true)
			switch(que_ad)
				{
				case 0:
					{
					set_adc_channel(0);
					break;
					}
				case 1:
					{
					set_adc_channel(1);
					break;
					}
				case 2:
					{
					set_adc_channel(2);
					break;
					}
				case 4:
					{
					set_adc_channel(4);
					break;
					}
				case 5:
					{
					set_adc_channel(5);
					break;
					}
				case 6:
					{
					set_adc_channel(6);
					break;
					}
				default:
					{
					leitura = 2048;
					}
				}
				delay_us(5);
				buffer_cht[passo_rd_cht] = (signed word)((read_adc() << 2));
				goto fim_timer3;
		#elif (st9600r == true)
			#if (versao_pci_st96 >= 4)	
				switch(que_ad)
					{
					case 0:
						{
						buffer_cht[passo_rd_cht] = (signed word)(le_canal_0());
						break;
						}
					case 1:
						{
						buffer_cht[passo_rd_cht] = (signed word)(le_canal_1());
						break;
						}
					case 2:
						{
						buffer_cht[passo_rd_cht] = (signed word)(le_canal_2());
						break;
						}
					case 4:
						{
						buffer_cht[passo_rd_cht] = (signed word)(le_canal_4());
						break;
						}
					case 5:
						{
						buffer_cht[passo_rd_cht] = (signed word)(le_canal_5());
						break;
						}
					case 6:
						{
						buffer_cht[passo_rd_cht] = (signed word)(le_canal_6());
						break;
						}
					default:
						{
						buffer_cht[passo_rd_cht] = 2048;
						}
					}
				passo_rd_cht++;
				if (passo_rd_cht == NRO_AMOSTRAS_CHT)
					{
					lendo_cht = false;
					}
			#endif
		#endif

		}
	else
		{
		cont_fase++;
		if (freq_50HZ == 1)
			{
			set_timer3(valor_timer3_2_50HZ);
			}
		else
			{
			set_timer3(valor_timer3_2_60HZ);
			}
		morder_t3 = 1;

		#if (controlador == true)
			trata_tempo_falta_energia();
		#endif

		if (med_ten_ok == 0)
			{
			if ((ler_ad_t3 == 1) || (time_out_t3 == 0))
				{
				#if (monofasico == true)
					{
					set_adc_channel(2);
					delay_us(5);
					leitura = (signed word)(read_adc() << 2);
					set_adc_channel(0);
					delay_us(5);
					buf_tensao_r[passo_tensao] = leitura;
					if (modo_rep == 0)
						{
						delay_us(5);
						buf_corrente_r[passo_corrente_r] = (signed word)(read_adc() << 2);
						}
					passo_tensao++;
					passo_corrente_r++;
					if (passo_corrente_r == NRO_AMOSTRAS)
						{
						passo_corrente_r = 0;
						}
					if (passo_tensao == NRO_AMOSTRAS)
						{
						med_ten_ok = 1;
						ler_ad_t3 = 0;
						passo_tensao = 0;
						if (tipo_ligacao == 1) // FF
							{
							#if (prog_defasagem ==	true)
								passo_corrente_r = tabela_defasagem_trafo_ff[defasagem];
							#else
								passo_corrente_r = off_cor_r + (NRO_AMOSTRAS/4);
							#endif
							}
						else
							{
							#if (prog_defasagem ==	true)
								passo_corrente_r = tabela_defasagem_trafo[defasagem];
							#else
								passo_corrente_r = off_cor_r;
							#endif
							}
				// obtem a referencia do ad
						if (nro_soma_vref < NRO_MEDIAS_VREF)
							{
							set_adc_channel(1);
							delay_us(5);
							soma_vref += (read_adc() << 2);
							nro_soma_vref++;
							}
						}
					goto fim_timer3;
					}
				#elif (ST8300C == true)
					{
					#if (buffer_fixo)
						buf_tensao_r[passo_tensao] = (signed word)(tab_valor_senoide_ten[passo_tensao]);
						buf_tensao_s[passo_tensao] = (signed word)(tab_valor_senoide_ten[passo_tensao]);
						buf_tensao_t[passo_tensao] = (signed word)(tab_valor_senoide_ten[passo_tensao]);
						buf_corrente_r[passo_corrente] = (signed word)(tab_valor_senoide_cor[passo_tensao]);
						buf_corrente_s[passo_corrente] = (signed word)(tab_valor_senoide_cor[passo_tensao]);
						buf_corrente_t[passo_corrente] = (signed word)(tab_valor_senoide_cor[passo_tensao]);
						passo_tensao++;
						passo_corrente++;
						if (passo_corrente == NRO_AMOSTRAS){
							passo_corrente = 0;
						}
						if (passo_tensao == NRO_AMOSTRAS){
							med_ten_ok = 1;
							ler_ad_t3 = 0;
							passo_tensao = 0;
							#if (prog_defasagem ==	true)
								passo_corrente = tabela_defasagem_trafo[defasagem];
							#else
								passo_corrente = off_cor_r;
							#endif
							if (nro_soma_vref < NRO_MEDIAS_VREF)
								{
								set_adc_channel(3);
								delay_us(5);
								soma_vref += (read_adc() << 2);
								nro_soma_vref++;
								}
						}
					#else
						if (passo_ad_8300 == 0)
							{
							set_adc_channel(4);
							delay_us(5);
							buf_tensao_r[passo_tensao] = (signed word)(read_adc() << 2);
							if (modo_rep == 0)
								{
								set_adc_channel(0);
								delay_us(5);
								buf_corrente_r[passo_corrente] = (signed word)(read_adc() << 2);
								}
							}
						else if (passo_ad_8300 == 1)
							{
							set_adc_channel(5);
							delay_us(5);
							buf_tensao_s[passo_tensao] = (signed word)(read_adc() << 2);
							if (modo_rep == 0)
								{
								set_adc_channel(1);
								delay_us(5);
								buf_corrente_s[passo_corrente] = (signed word)(read_adc() << 2);
								}
							}
						else if (passo_ad_8300 == 2)
							{
							set_adc_channel(6);
							delay_us(5);
							buf_tensao_t[passo_tensao] = (signed word)(read_adc() << 2);
							if (modo_rep == 0)
								{
								set_adc_channel(2);
								delay_us(5);
								buf_corrente_t[passo_corrente] = (signed word)(read_adc() << 2);
								}
							}
						else
							{
		//					med_ten_ok = 1;
							passo_ad_8300 = 255;
							}
						
						passo_tensao++;
						passo_corrente++;
						if (passo_corrente == NRO_AMOSTRAS)
							{
							passo_corrente = 0;
							}
						if (passo_tensao == NRO_AMOSTRAS)
							{
							med_ten_ok = 1;
							ler_ad_t3 = 0;
							passo_tensao = 0;
							#if (prog_defasagem ==	true)
								passo_corrente = tabela_defasagem_trafo[defasagem];
							#else
								passo_corrente = off_cor_r;
							#endif
							passo_ad_8300++;
							if (nro_soma_vref < NRO_MEDIAS_VREF)
								{
								set_adc_channel(3);
								delay_us(5);
								soma_vref += (read_adc() << 2);
								nro_soma_vref++;
								}
							}
						goto fim_timer3;
					#endif
					}
				#else		// Registradores  st92/94/96
					{
					#if (buffer_fixo)
						buf_tensao_r[passo_tensao] = (signed word)(tab_valor_senoide_ten[passo_tensao]);
						buf_tensao_s[passo_tensao] = (signed word)(tab_valor_senoide_ten[passo_tensao]);
						buf_tensao_t[passo_tensao] = (signed word)(tab_valor_senoide_ten[passo_tensao]);
						buf_corrente_r[passo_corrente] = (signed word)(tab_valor_senoide_cor[passo_tensao]);
						buf_corrente_s[passo_corrente] = (signed word)(tab_valor_senoide_cor[passo_tensao]);
						buf_corrente_t[passo_corrente] = (signed word)(tab_valor_senoide_cor[passo_tensao]);
						passo_tensao++;
						passo_corrente++;
						if (passo_corrente == NRO_AMOSTRAS){
							passo_corrente = 0;
						}
						if (passo_tensao == NRO_AMOSTRAS){
							med_ten_ok = 1;
							ler_ad_t3 = 0;
							passo_tensao = 0;
							#if(portatil)
								passo_corrente = off_cor_r + tabela_defasagem[tipo_ponteira];
							#else
								passo_corrente = off_cor_r;
							#endif
							if (nro_soma_vref < NRO_MEDIAS_VREF){
								soma_vref += le_canal_3();
								nro_soma_vref++;
							}
							#if(portatil)
								if (ajustar_ponteira == true){
									ajustar_ponteira = false;
									pga_gain_set(ganho_ponteira, 1); 
								}
							#endif
						}
					#else
						if (modo_funca == 2)
							{
							buf_tensao_r[passo_tensao] = (signed word)(le_canal_4()); 
							buf_tensao_s[passo_tensao] = (signed word)(le_canal_5());
							buf_tensao_t[passo_tensao] = (signed word)(le_canal_6());
						
							passo_tensao++;
							if (passo_tensao == NRO_AMOSTRAS)
								{
								med_ten_ok = 1;
								ler_ad_t3 = 0;
								passo_tensao = 0;
					// obtem a referencia do ad
								if (nro_soma_vref < NRO_MEDIAS_VREF)
									{
									soma_vref += le_canal_3();
									nro_soma_vref++;
									}
								}
							}
						else
							{
							if (tipo_ligacao == 2)
								{
								buf_tensao_r[passo_tensao] = (signed word)(le_canal_4());
								buf_corrente_r[passo_corrente_r] = (signed word)(le_canal_0());
						
								buf_tensao_s[passo_tensao] = (signed word)(le_canal_5());	
								buf_corrente_s[passo_tensao] = vref;
						
								buf_tensao_t[passo_tensao] = (signed word)(le_canal_6());	
								buf_corrente_t[passo_corrente_t] = (signed word)(le_canal_2());
				
								passo_tensao++;
								passo_corrente_r++;
								passo_corrente_t++;
								if (passo_corrente_r == NRO_AMOSTRAS)
									{
									passo_corrente_r = 0;
									}
								if (passo_corrente_t == NRO_AMOSTRAS)
									{
									passo_corrente_t = 0;
									}
								if (passo_tensao == NRO_AMOSTRAS)
									{
									med_ten_ok = 1;
									ler_ad_t3 = 0;
									passo_tensao = 0;
									passo_corrente_r = off_cor_r + (NRO_AMOSTRAS - off_cor_delta);
									passo_corrente_t = off_cor_r + off_cor_delta;
					// obtem a referencia do ad
									if (nro_soma_vref < NRO_MEDIAS_VREF)
										{
										soma_vref += le_canal_3();
										nro_soma_vref++;
										}
									#if (portatil == true)
										#if (versao_pci_st96 >= 5)
											if (ajustar_ponteira == true)
												{
												ajustar_ponteira = false;
												pga_gain_set(ganho_ponteira, 1); 
												}
										#endif
									#endif
									}
								}
							else
								{				
								buf_tensao_r[passo_tensao] = (signed word)(le_canal_4());
								buf_corrente_r[passo_corrente] = (signed word)(le_canal_0());
						
								buf_tensao_s[passo_tensao] = (signed word)(le_canal_5());	
								buf_corrente_s[passo_corrente] = (signed word)(le_canal_1());
									
								buf_tensao_t[passo_tensao] = (signed word)(le_canal_6());	
								buf_corrente_t[passo_corrente] = (signed word)(le_canal_2());
					
								passo_tensao++;
								passo_corrente++;
								if (passo_corrente == NRO_AMOSTRAS)
									{
									passo_corrente = 0;
									}
								if (passo_tensao == NRO_AMOSTRAS)
									{
									med_ten_ok = 1;
									ler_ad_t3 = 0;
									passo_tensao = 0;
									
									#if (portatil == true)
										#if (versao_pci_st96 > 3)
											passo_corrente = off_cor_r + tabela_defasagem[tipo_ponteira];
										#elif (viercon == true)
											passo_corrente = off_cor_r + defasagem_flex;
										#else
											passo_corrente = off_cor_r;
										#endif
									#else
										passo_corrente = off_cor_r;
									#endif
					// obtem a referencia do ad
									if (nro_soma_vref < NRO_MEDIAS_VREF)
										{
										soma_vref += le_canal_3();
										nro_soma_vref++;
										}
									#if (portatil == true)
										#if (versao_pci_st96 >= 5)
											if (ajustar_ponteira == true)
												{
												ajustar_ponteira = false;
												pga_gain_set(ganho_ponteira, 1); 
												}
										#endif
									#endif
									}
								}
							}
						#endif		//buffer_fixo
					}
				#endif
				}
			}
		}
#else
	#if ((st94 == true) || (ST8100C == true) || (ST8200C == true) || (st92 == true))
		word leitura;
	#endif
	cont_fase++;
	#if (teste_vag == true)
		set_timer3(valor_timer3_16p);
	#else	
		if (freq_50HZ == 1)
			{
			set_timer3(valor_timer3_2_50HZ);
			}
		else
			{
			set_timer3(valor_timer3_2_60HZ);
			}
	#endif
	morder_t3 = 1;
	#if (controlador == true)
		trata_tempo_falta_energia();
	#endif
	
	#if (home_system == true)
		if(Count_1ms != 0)           // 1ms is here
   			{
	   		Count_1ms--;
	   		}
	   	else
	   		{
			Count_1ms = 3;
      		Net_Timer_1ms();
			}
	#endif

	if (med_ten_ok == 0)
		{
		if ((ler_ad_t3 == 1) || (time_out_t3 == 0))
			{
			#if (monofasico == true)
				{
				set_adc_channel(2);
				delay_us(5);
				leitura = (signed word)(read_adc() << 2);
				set_adc_channel(0);
				delay_us(5);
				buf_tensao_r[passo_tensao] = leitura;
				buf_corrente_r[passo_corrente_r] = (signed word)(read_adc() << 2);
		
				passo_tensao++;
				passo_corrente_r++;
				if (passo_corrente_r == NRO_AMOSTRAS)
					{
					passo_corrente_r = 0;
					}
				if (passo_tensao == NRO_AMOSTRAS)
					{
					med_ten_ok = 1;
					ler_ad_t3 = 0;
					passo_tensao = 0;
					passo_corrente_r = off_cor_r;
			// obtem a referencia do ad
					if (nro_soma_vref < NRO_MEDIAS_VREF)
						{
						set_adc_channel(1);
						delay_us(5);
						soma_vref += (read_adc() << 2);
						nro_soma_vref++;
						}
					}
				goto fim_timer3;
				}
			#elif (sames_9904 == true)
			
			#elif (ST8300C == true) 
				if (passo_ad_8300 == 0)
					{
					set_adc_channel(4);
					delay_us(5);
					buf_tensao_r[passo_tensao] = (signed word)(read_adc() << 2);
					set_adc_channel(0);
					delay_us(5);
					if (modo_rep == 0)
						{
						buf_corrente_r[passo_corrente] = (signed word)(read_adc() << 2);
						}
					}
				else if (passo_ad_8300 == 1)
					{
					set_adc_channel(5);
					delay_us(5);
					buf_tensao_s[passo_tensao] = (signed word)(read_adc() << 2);
					set_adc_channel(1);
					delay_us(5);
					if (modo_rep == 0)
						{
						buf_corrente_s[passo_corrente] = (signed word)(read_adc() << 2);
						}
					}
				else if (passo_ad_8300 == 2)
					{
					set_adc_channel(6);
					delay_us(5);
					buf_tensao_t[passo_tensao] = (signed word)(read_adc() << 2);
					set_adc_channel(2);
					delay_us(5);
					if (modo_rep == 0)
						{
						buf_corrente_t[passo_corrente] = (signed word)(read_adc() << 2);
						}
					}
				else
					{
//					med_ten_ok = 1;
					passo_ad_8300 = 255;
					}
				
				passo_tensao++;
				passo_corrente++;
				if (passo_corrente == NRO_AMOSTRAS)
					{
					passo_corrente = 0;
					}
				if (passo_tensao == NRO_AMOSTRAS)
					{
					med_ten_ok = 1;
					ler_ad_t3 = 0;
					passo_tensao = 0;
					passo_corrente = off_cor_r;
					passo_ad_8300++;
					if (nro_soma_vref < NRO_MEDIAS_VREF)
						{
						set_adc_channel(3);
						delay_us(5);
						soma_vref += (read_adc() << 2);
						nro_soma_vref++;
						}
					}
				goto fim_timer3;
			#else
				if (modo_funca == 2)
					{
					buf_tensao_r[passo_tensao] = (signed word)(le_canal_4()); 
					buf_tensao_s[passo_tensao] = (signed word)(le_canal_5());
					buf_tensao_t[passo_tensao] = (signed word)(le_canal_6());
				
					passo_tensao++;
					if (passo_tensao == NRO_AMOSTRAS)
						{
						med_ten_ok = 1;
						ler_ad_t3 = 0;
						passo_tensao = 0;
			// obtem a referencia do ad
						if (nro_soma_vref < NRO_MEDIAS_VREF)
							{
							soma_vref += le_canal_3();
							nro_soma_vref++;
							}
						}
					}
				else
					{
					if (tipo_ligacao == 2)
						{
						buf_tensao_r[passo_tensao] = (signed word)(le_canal_4());
						buf_corrente_r[passo_corrente_r] = (signed word)(le_canal_0());
				
						buf_tensao_s[passo_tensao] = (signed word)(le_canal_5());	
						buf_corrente_s[passo_tensao] = vref;
				
						buf_tensao_t[passo_tensao] = (signed word)(le_canal_6());	
						buf_corrente_t[passo_corrente_t] = (signed word)(le_canal_2());
		
						passo_tensao++;
						passo_corrente_r++;
						passo_corrente_t++;
						if (passo_corrente_r == NRO_AMOSTRAS)
							{
							passo_corrente_r = 0;
							}
						if (passo_corrente_t == NRO_AMOSTRAS)
							{
							passo_corrente_t = 0;
							}
						if (passo_tensao == NRO_AMOSTRAS)
							{
							med_ten_ok = 1;
							ler_ad_t3 = 0;
							passo_tensao = 0;
							passo_corrente_r = off_cor_r + (NRO_AMOSTRAS - off_cor_delta);
							passo_corrente_t = off_cor_r + off_cor_delta;
			// obtem a referencia do ad
							if (nro_soma_vref < NRO_MEDIAS_VREF)
								{
								soma_vref += le_canal_3();
								nro_soma_vref++;
								}
							}
						}
					else
						{				
						#if (teste_vag == true)
							if (conta_ciclo <= NRO_CICLOS)
								{
									
							output_high(pino_teste);
							
								aux_sw1t = (signed word)(le_canal_4())- vref;
								buf_corrente_r[passo_corrente] = (signed word)(le_canal_0());
							
								aux_sw2t = (signed word)(le_canal_5())- vref;
								buf_corrente_s[passo_corrente] = (signed word)(le_canal_1());
									
								aux_sw3t = (signed word)(le_canal_6())- vref;
								buf_corrente_t[passo_corrente] = (signed word)(le_canal_2());
								
								aux_sl1t = (signed int32)(aux_sw1t);
								soma_tr += (signed int32)(aux_sl1t * aux_sl1t);
								aux_sl2t = (signed int32)(aux_sw2t);
								soma_ts += (signed int32)(aux_sl2t * aux_sl2t);
								aux_sl3t = (signed int32)(aux_sw3t);
								soma_tt += (signed int32)(aux_sl3t * aux_sl3t);
//	
								aux_sl4t = (signed int32)(buf_corrente_r[passo_tensao]-vref);
								soma_cr += (signed int32)(aux_sl4t * aux_sl4t);
								aux_sl5t = (signed int32)(buf_corrente_s[passo_tensao]-vref);
								soma_cs += (signed int32)(aux_sl5t * aux_sl5t);
								aux_sl6t = (signed int32)(buf_corrente_t[passo_tensao]-vref);
								soma_ct += (signed int32)(aux_sl6t * aux_sl6t);
	
								soma_pr += (signed int32)(aux_sl1t * aux_sl4t);
								soma_ps += (signed int32)(aux_sl2t * aux_sl5t);
								soma_pt += (signed int32)(aux_sl3t * aux_sl6t);
	
					
								passo_tensao++;
								passo_corrente++;
								if (passo_corrente == NRO_AMOSTRAS_MODO3)
									{
									passo_corrente = 0;
									}
									
							output_low(pino_teste);

									
								if (passo_tensao == NRO_AMOSTRAS_MODO3)
									{
										
									soma_tr_tmp[conta_ciclo] = (soma_tr);
									soma_ts_tmp[conta_ciclo] = (soma_ts);
									soma_tt_tmp[conta_ciclo] = (soma_tt);
									soma_cr_tmp[conta_ciclo] = (soma_cr);
									soma_cs_tmp[conta_ciclo] = (soma_cs);
									soma_ct_tmp[conta_ciclo] = (soma_ct);
									soma_pr_tmp[conta_ciclo] = (soma_pr);
									soma_ps_tmp[conta_ciclo] = (soma_ps);
									soma_pt_tmp[conta_ciclo] = (soma_pt);
									soma_tr = 0;
									soma_ts = 0;
									soma_tt = 0;
									soma_cr = 0;
									soma_cs = 0;
									soma_ct = 0;
									soma_pr = 0;
									soma_ps = 0;
									soma_pt = 0;

									conta_ciclo++;
									
									med_ten_ok = 0;
									ler_ad_t3 = 0;
									passo_tensao = 0;
									
									passo_corrente = off_cor_r / 4;
									
									
					// obtem a referencia do ad
									}
								else
									{
									if (nro_soma_vref < NRO_MEDIAS_VREF)
										{
										soma_vref += le_canal_3();
										nro_soma_vref++;
										}
									}

									
								}
						#else
							
							buf_tensao_r[passo_tensao] = (signed word)(le_canal_4());
							buf_corrente_r[passo_corrente] = (signed word)(le_canal_0());
					
							#if (padrao_referencia == true)
								buf_tensao_s[passo_tensao] = buf_tensao_r[passo_tensao];
								buf_corrente_s[passo_corrente] = buf_corrente_r[passo_corrente];
								
								buf_tensao_t[passo_tensao] = buf_tensao_r[passo_tensao];	
								buf_corrente_t[passo_corrente] = buf_corrente_r[passo_corrente];
							#else
								buf_tensao_s[passo_tensao] = (signed word)(le_canal_5());	
								buf_corrente_s[passo_corrente] = (signed word)(le_canal_1());
								
								buf_tensao_t[passo_tensao] = (signed word)(le_canal_6());	
								buf_corrente_t[passo_corrente] = (signed word)(le_canal_2());
							#endif
					
							passo_tensao++;
							passo_corrente++;
							if (passo_corrente == NRO_AMOSTRAS)
								{
								passo_corrente = 0;
								}
							if (passo_tensao == NRO_AMOSTRAS)
								{
								med_ten_ok = 1;
								ler_ad_t3 = 0;
								passo_tensao = 0;
								passo_corrente = off_cor_r;
					// obtem a referencia do ad
								if (nro_soma_vref < NRO_MEDIAS_VREF)
									{
									soma_vref += le_canal_3();
									nro_soma_vref++;
									}
								}
						#endif
						}
					}
			#endif
			}
		}
#endif
#if ((st94 == true) || (st92 == true))
fim_timer3:
	#if (st92 == true)
		delay_cycles(1);
	#else
		if (disp_timer == 0)
			{
			disp_timer = 1;
			output_low(CS_IO2);
			output_d(buf_display[ptr_disp]);
			output_high (CS_IO2);
				
			if (ptr_disp < 8)
				{
				output_low(CS_IO3);
				output_d(tabela_disp[ptr_disp]);
				output_high (CS_IO3);
				output_low(CS_IO4);
				output_d(0);
				output_high (CS_IO4);
				}
			else
				{
				output_low(CS_IO4);
				output_d(tabela_disp[ptr_disp]);
				output_high (CS_IO4);
				output_low(CS_IO3);
				output_d(0);
				output_high (CS_IO3);
				}
			ptr_disp++;
			if (ptr_disp > 12)
				{
				ptr_disp = 0;
				}
			}
		else
			{
			disp_timer = 0;
			}
	#endif
#endif
#if (st5x == true)
	#if (st5000c_rev12 == true)
		fim_timer3:
			delay_cycles(1);
	#endif
#endif

#if (ST8200C == true)
	fim_timer3:
		delay_cycles(1);
#endif
#if (ST8300C == true)
	fim_timer3:
		delay_cycles(1);
#endif
#if (ST8100C == true)
	fim_timer3:
	#if (__DEVICE__ == 6722)
			if (disp_timer == 0)
				{
				disp_timer = 8;
				output_high(CSIO2);
				output_high(CSIO3);
					
				digito = tabela_disp[ptr_disp];
				output_low(CSIO4);
				output_d(digito);
				output_high (CSIO4);
	
				digito = buf_display[ptr_disp];
	//			digito = tabela_caracteres[ptr_disp];
				output_low(CSIO1);
				output_d(digito);
				output_high (CSIO1);
	
				ptr_disp++;
				if (ptr_disp > 4)
					{
					ptr_disp = 0;
					}
				}
			else
				{
				disp_timer--;
				}
				
	#else		
			if (disp_timer == 0)
				{
				disp_timer = 8;
				output_high(CSIO2);
				output_high(CSIO3);
					
				digito = tabela_disp[ptr_disp];
				output_low(CSIO4);
				output_d(digito);
				output_high (CSIO4);
	
				digito = buf_display[ptr_disp];
				output_low(CSIO1);
				output_d(digito);
				output_high (CSIO1);
	
				ptr_disp++;
				if (ptr_disp > 4)
					{
					ptr_disp = 0;
					}
				}
			else
				{
				disp_timer--;
				}
	#endif			
#endif

}



