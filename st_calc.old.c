/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: st_CALC                                                        *
; Funcao: MODULO ROTINAS DE CALCULOS   									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */

void trata_modbus(void);


void calcula_vref(void)
{
	if (nro_soma_vref == 32)
		{
		vref = (word)(soma_vref >> 5);
		if ((vref < 2028) || (vref > 2068))
			{
			vref = 2048;
			}
		soma_vref = 0;
		nro_soma_vref = 0;
		}
	else
		{
		if (nro_soma_vref > 32)
			{
			vref = 2048;
			soma_vref = 0;
			nro_soma_vref = 0;
			}
		}
		
}



void calcula_tensao_corrente(void)
{

//	aux_calc = 80;
	
	conta_media++;
	
	soma_tr =  0;
	soma_ts =  0;
	soma_tt =  0;
	soma_cr =  0;
	soma_cs =  0;
	soma_ct =  0;
	soma_pr = 0;
	soma_ps = 0;
	soma_pt = 0;
	sinalizou_r = 0;
	sinalizou_s = 0;
	sinalizou_t = 0;
	cor_baixa_r = 0;
	cor_baixa_s = 0;
	cor_baixa_t = 0;

	if (corrente_r < (valor_tc >> 4)) // 3%
		{
		cor_baixa_r = 1;
#if ((st5000t == 1) || (st5030t == 1))
		output_high(led_tc_r);
#endif
		}
	if (corrente_s < (valor_tc >> 4)) // 3%
		{
		cor_baixa_s = 1;
#if ((st5000t == 1) || (st5030t == 1))
		output_high(led_tc_s);
#endif
		}
	if (corrente_t < (valor_tc >> 4)) // 3%
		{
		cor_baixa_t = 1;
#if ((st5000t == 1) || (st5030t == 1))
		output_high(led_tc_t);
#endif
		}
//
	if (buf_tensao_r[0] > 0)
		{
		zero_r = 1;
		}
	else
		{
		zero_r = 0;
		}	
//		
	if (buf_tensao_s[0] > 0)
		{
		zero_s = 1;
		}
	else
		{
		zero_s = 0;
		}	
//
	if (buf_tensao_t[0] > 0)
		{
		zero_t = 1;
		}
	else
		{
		zero_t = 0;
		}	
//		

//	aux_calc = 81;

	for (aux_calc = 0; aux_calc < NRO_AMOSTRAS; aux_calc++)
		{
//		pulsa_wdt();

#if com_modbus
		trata_modbus();
#endif

		
// fase R
		aux_sl1 = buf_tensao_r[aux_calc];
		soma_tr += (signed int32)(aux_sl1 * aux_sl1);

		if (modo_funca == 1)
			{
			aux_sl2 = buf_corrente_r[aux_calc];
			soma_cr += (signed int32)(aux_sl2 * aux_sl2);
	
			if (cor_baixa_r == 0)
				{
	/*				
				if (aux_calc == 0)
					{
					aux_sl1 = buf_tensao_r[NRO_AMOSTRAS-1];
					aux_sl1 = aux_sl1 + buf_tensao_r[0];
					}
				else if (aux_calc == (NRO_AMOSTRAS-1))
					{
					aux_sl1 = buf_tensao_r[0];
					aux_sl1 = aux_sl1 + buf_tensao_r[NRO_AMOSTRAS-1];
					}
				else
					{
					aux_sl1 = buf_tensao_r[aux_calc-1];
					aux_sl1 = aux_sl1 + buf_tensao_r[aux_calc+1];
					}
	*/				
				soma_pr += (signed int32)(aux_sl1 * aux_sl2);
		// teste para verificar a fase entre tensao e corrente fase R.
				if (sinalizou_r == 0)
					{
					if (aux_sl1 > 0 )
						{
						if (zero_r == 0)
							{
							if (aux_sl2 > 0)
								{
								sinal_fp[0] = '+';
								}
							else
								{
								sinal_fp[0] = '-';
								}
							sinalizou_r = 1;
							}
						zero_r = 1;
						}
					else
						{
						if (zero_r == 1)
							{
							if (aux_sl2 > 0)
								{
								sinal_fp[0] = '-';
								}
							else
								{
								sinal_fp[0] = '+';
								}
							sinalizou_r = 1;
							}
						zero_r = 0;
						}
					}
				}
			else
				{
				sinal_fp[0] = '1';
				soma_pr = 0;
				soma_pot_efi_r = 0;
				}
			}
			

le_outras_fases:
// fase S
		aux_sl1 = buf_tensao_s[aux_calc];
		soma_ts += (signed int32)(aux_sl1 * aux_sl1);

		if (modo_funca == 1)
			{
			aux_sl2 = buf_corrente_s[aux_calc];
			soma_cs += (signed int32)(aux_sl2 * aux_sl2);

			if (cor_baixa_s == 0)
				{
				soma_ps += (signed int32)(aux_sl1 * aux_sl2);
		// teste para verificar a fase entre tensao e corrente fase S.
				if (sinalizou_s == 0)
					{
					if (aux_sl1 > 0 )
						{
						if (zero_s == 0)
							{
							if (aux_sl2 > 0)
								{
								sinal_fp[1] = '+';
								}
							else
								{
								sinal_fp[1] = '-';
								}
							sinalizou_s = 1;
							}
						zero_s = 1;
						}
					else
						{
						if (zero_s == 1)
							{
							if (aux_sl2 > 0)
								{
								sinal_fp[1] = '-';
								}
							else
								{
								sinal_fp[1] = '+';
								}
							sinalizou_s = 1;
							}
						zero_s = 0;
						}
					}
				}
			else
				{
				sinal_fp[1] = '1';
				soma_ps = 0;
				soma_pot_efi_s = 0;
				}
			}

// fase T
		aux_sl1 = buf_tensao_t[aux_calc];
		soma_tt += (signed int32)(aux_sl1 * aux_sl1);

		if (modo_funca == 1)
			{
			aux_sl2 = buf_corrente_t[aux_calc];
			soma_ct += (signed int32)(aux_sl2 * aux_sl2);
	
			if (cor_baixa_t == 0)
				{
				soma_pt += (signed int32)(aux_sl1 * aux_sl2);
		// teste para verificar a fase entre tensao e corrente fase T.
				if (sinalizou_t == 0)
					{
					if (aux_sl1 > 0 )
						{
						if (zero_t == 0)
							{
							if (aux_sl2 > 0)
								{
								sinal_fp[2] = '+';
								}
							else
								{
								sinal_fp[2] = '-';
								}
							sinalizou_t = 1;
							}
						zero_t = 1;
						}
					else
						{
						if (zero_t == 1)
							{
							if (aux_sl2 > 0)
								{
								sinal_fp[2] = '-';
								}
							else
								{
								sinal_fp[2] = '+';
								}
							sinalizou_t = 1;
							}
						zero_t = 0;
						}
					}
				}
			else
				{
				sinal_fp[2] = '1';
				soma_pt = 0;
				soma_pot_efi_t = 0;
				}
			}
		
		}

//	aux_calc = 82;

	
// tensao r
	aux_l1 = (int32)(soma_tr / NRO_AMOSTRAS);
	aux_l1 = (int32)(sqrtx(aux_l1));
	aux_l1 = (int32)((aux_l1 * (254 * 113) ) >> 10);	
	soma_efi_tr += (word)(aux_l1);

//	output_high(direcao);
//	printf("conta_media=%u",conta_media_ten);
//	printf(" aux_l1=%Lu", aux_l1);
//	printf(" os_ten_r1=%u", os_ten_r1);
//	printf(" os_ten_r=%u\r\n", os_ten_r);
//	output_low(direcao);

// tensao s
	aux_l1 = (int32)(soma_ts / NRO_AMOSTRAS);
	aux_l1 = (int32)(sqrtx(aux_l1));
	aux_l1 = (int32)((aux_l1 * (254 * 113) ) >> 10);	
	soma_efi_ts += (word)(aux_l1);

// tensao t
	aux_l1 = (int32)(soma_tt / NRO_AMOSTRAS);
	aux_l1 = (int32)(sqrtx(aux_l1));
	aux_l1 = (int32)((aux_l1 * (254 * 113) ) >> 10);	
	soma_efi_tt += (word)(aux_l1);


//	aux_calc = 83;

	if (modo_funca == 1)
		{
		/* calculo da corrente */
		aux_l1 = (int32)(soma_cr / NRO_AMOSTRAS);
		aux_l1 = (int32)(sqrtx(aux_l1));
		aux_l2 = valor_tc;
		aux_l2 = aux_l2 * 123;
#if (st9600r == 1)
		aux_l1 = (int32)((aux_l1 * aux_l2) >> 14);	// / 16384;
#else
		aux_l1 = (int32)((aux_l1 * aux_l2) >> 13);	// / 8192;
#endif
		soma_efi_cr += (word)(aux_l1);
			
		aux_l1 = (int32)(soma_cs / NRO_AMOSTRAS);
		aux_l1 = (int32)(sqrtx(aux_l1));
#if (st9600r == 1)
		aux_l1 = (int32)((aux_l1 * aux_l2) >> 14);	// / 16384;
#else
		aux_l1 = (int32)((aux_l1 * aux_l2) >> 13);	// / 8192;
#endif
		soma_efi_cs += (word)(aux_l1);
	
		aux_l1 = (int32)(soma_ct / NRO_AMOSTRAS);
		aux_l1 = (int32)(sqrtx(aux_l1));
#if (st9600r == 1)
		aux_l1 = (int32)((aux_l1 * aux_l2) >> 14);	// / 16384;
#else
		aux_l1 = (int32)((aux_l1 * aux_l2) >> 13);	// / 8192;
#endif
		soma_efi_ct += (word)(aux_l1);
	
		soma_pot_efi_r += (signed int32)((soma_pr / NRO_AMOSTRAS));
		soma_pot_efi_s += (signed int32)((soma_ps / NRO_AMOSTRAS));
		soma_pot_efi_t += (signed int32)((soma_pt / NRO_AMOSTRAS));
		}	
	conta_media_ten++;

//	aux_calc = 84;

	if (conta_media_ten == nro_media_amostras)
		{

//	aux_calc = 85;

		aux_l1 = soma_efi_tr >> nro_desloca;
		aux_l2 = (signed word)(1000 + os_ten_r);
		aux_l2 = aux_l2 * aux_l1;
		tensao_r = aux_l2 / 1000;

		aux_l1 = soma_efi_ts >> nro_desloca;
		aux_l2 = (signed word)(1000 + os_ten_s);
		aux_l2 = aux_l2 * aux_l1;
		tensao_s = aux_l2 / 1000;

		aux_l1 = soma_efi_tt >> nro_desloca;
		aux_l2 = (signed word)(1000 + os_ten_t);
		aux_l2 = aux_l2 * aux_l1;
		tensao_t = aux_l2 / 1000;

		if (modo_funca == 1)
			{
//	aux_calc = 86;
			aux_l1 = soma_efi_cr >> nro_desloca;
			aux_l2 = (signed word)(1000 + os_cor_r);
			aux_l2 = aux_l2 * aux_l1;
			corrente_r = (word)(aux_l2 / 1000);
	
			aux_l1 = soma_efi_cs >> nro_desloca;
			aux_l2 = (signed word)(1000 + os_cor_s);
			aux_l2 = aux_l2 * aux_l1;
			corrente_s = (word)(aux_l2 / 1000);
	
			aux_l1 = soma_efi_ct >> nro_desloca;
			aux_l2 = (signed word)(1000 + os_cor_t);
			aux_l2 = aux_l2 * aux_l1;
			corrente_t = (word)(aux_l2 / 1000);
	
			aux_sl1 = (signed int32)(soma_pot_efi_r >> nro_desloca);
			soma_efi_pr = (signed int32)(aux_sl1); 
	
			aux_sl1 = (signed int32)(soma_pot_efi_s >> nro_desloca);
			soma_efi_ps = (signed int32)(aux_sl1); 
			
			aux_sl1 = (signed int32)(soma_pot_efi_t >> nro_desloca);
			soma_efi_pt = (signed int32)(aux_sl1); 

			}
		else
			{
			corrente_r = 0;
			corrente_s = 0;
			corrente_t = 0;
			}

		calc_ten_ok = 1;

		soma_efi_cr = 0;
		soma_efi_cs = 0;
		soma_efi_ct = 0;
		soma_pot_efi_r = 0;
		soma_pot_efi_s = 0;
		soma_pot_efi_t = 0;

//	aux_calc = 87;

		soma_efi_tr = 0;
		soma_efi_tt = 0;
		soma_efi_ts = 0;
		
		conta_media_ten = 0;

#if teste_consumo					
		tensao_r = 120 * 64;
		tensao_s = 120 * 64;
		tensao_t = 120 * 64;
		corrente_r = 125;
		corrente_s = 125;
		corrente_t = 125;
#endif
#if (teste_cht == true)
		tensao_r = 127 * 64;
		tensao_s = 127 * 64;
		tensao_t = 127 * 64;
		corrente_r = 100 * 8;
		corrente_s = 100 * 8;
		corrente_t = 100 * 8;
#endif

		
		}


	med_ten_ok = 0;
	
}


/*
void calculo_pot_r(void)
{
	int32 aux_lx;
	if (tensao_r > (20 * 64))
		{	
		if (corrente_r > ((valor_tc/20) << 3))		//  	*8))
			{
			if (make8(soma_efi_pr, 3) != 0 )
				{
				sentido_r = 1;
				soma_efi_pr = ~soma_efi_pr;
				soma_efi_pr = soma_efi_pr & 0x00ffffff;
				}
			else
				{
				sentido_r = 0;
				}
/* calculo da potencia ativa */
			aux_l3 = (int32)(valor_tc);
			aux_l2 = (int32)(254 * mul_kw *  aux_l3);
			aux_l2 = (int32)(aux_l2 >> 9 );
			if (valor_tc == 20)
				{
				aux_lx = aux_l2;	
				}
			aux_l2 = (int32)(aux_l2 / 1000);
			aux_l1 = (int32)(soma_efi_pr * aux_l2);
#if (st9600r == 1)
			aux_l1 = (int32)(aux_l1 / 32768 );
#else
			aux_l1 = (int32)(aux_l1 / 16384 );
#endif
			if (valor_tc == 20)
				{
				aux_b1 = 8;
				}
			else if (valor_tc == 200)
				{
				aux_b1 = 19;
				}
			else
				{
				aux_b1 = 0;
				}
			aux_l2 = (signed word)(1000 + (os_cor_r + os_ten_r + aux_b1));
			aux_l2 = (int32)(aux_l2 * aux_l1);
			pot_ativa_r = (word)(aux_l2 / 1000);

			if (valor_tc == 20)
				{
				aux_l1 = (int32)(soma_efi_pr * aux_lx);
#if (st9600r == 1)
				aux_l1 = (int32)(aux_l1 / 32768 );
#else
				aux_l1 = (int32)(aux_l1 / 16384 );
#endif
				aux_b1 = 8;
				aux_l2 = (signed word)(1000 + (os_cor_r + os_ten_r + aux_b1));
				aux_l2 = (int32)(aux_l2 * aux_l1);
				pot_ativa_r_long = aux_l2 / 1000;

				}
			
	
	/* calculo da potencia aparente */
			if (valor_tp !=1)
				{
				aux_l1 = (int32)(tensao_r);
				aux_l1 = (int32)(aux_l1 * 1.7320508);
				aux_l2 = (int32)(aux_l1 * (word)(valor_tp));
		    	aux_l2 = aux_l2 * corrente_r;
			    data1_int = (word)((aux_l2 / 16000) / 100);
				}
			else
				{    
		    	aux_l1 = tensao_r;
			    aux_l1 = aux_l1 * corrente_r;
			    data1_int = aux_l1 / 16000;
				if (valor_tc == 20)
					{
			    	aux_l1 = tensao_r;
				    aux_l1 = aux_l1 * corrente_r;
				    pot_aparente_r_long = aux_l1 / 16;
					}
    			}
		
			pot_aparente_r = data1_int;		
		   	if (pot_ativa_r > pot_aparente_r)
		   		{
			   	pot_ativa_r = pot_aparente_r;
			   	}

		   	data1_int = pot_aparente_r - pot_ativa_r;
			if (valor_tc == 20)
				{
				if (data1_int < 6)
					{
			   		pot_ativa_r = pot_aparente_r;
					}
				}

#if teste_consumo					
	pot_ativa_r = 59;
		
#endif

	
			if (pot_ativa_r != pot_aparente_r)
				{
/* calculo da potencia reativa */    
/* Kvar = sqr(kva^2 - Kw^) */	
				aux_l1 = pot_ativa_r;
				aux_l1 = (int32)(aux_l1 * aux_l1);
				aux_l2 = pot_aparente_r;
				aux_l2 = (int32)(aux_l2 * aux_l2);
				pot_reativa_r =(word)(sqrtx(aux_l2 - aux_l1));
		
/* calculo do fator de potencia  */    
				if (valor_tc != 20)
					{
					aux_l1 = pot_ativa_r;
					aux_l1 = (int32)(aux_l1 * 1024);
					aux_w1 = (word)(aux_l1 / pot_aparente_r);
					}
				else
					{
					aux_l1 = pot_ativa_r_long;
					aux_l1 = (int32)(aux_l1 * 1024);
					aux_w1 = (word)(aux_l1 / pot_aparente_r_long);
					}
				if (sinal_fp[0] == '-')
					{
	    			aux_w1 = aux_w1 * (-1);
					}
				else if (sinal_fp[0] == '1')
					{
					aux_w1 = 1024;
					}
				if ((aux_w1 < 1024) && (aux_w1 > 1018))
					{
					aux_w1 = 1024;
					}
				else if (aux_w1 > 65530)
					{
					aux_w1 = 1024;
					}
					
				if (aux_w1 == 1024)
					{
//				   	pot_ativa_r = pot_aparente_r;
					}

			   	fator_pot_r = aux_w1;
/* calculo do kvar requerido */	    
/* pot_req_x = potencia_reativa - srq(((potencia_ativa / setpoint) ^2)) - ( potencia_ativa ^ 2))  */
				kvar_requerido('R');
				}
			else
				{
			   	fator_pot_r = 1024;
				pot_reativa_r = 0;
				pot_req_r = 0;
				pot_exec_r = 0;
				}
			}
		else
			{
			soma_pot_efi_r = 0;
			soma_pr = 0;
		    pot_ativa_r = 0;
		    pot_aparente_r = 0;
			pot_reativa_r = 0;
		   	fator_pot_r = 1024;
			pot_req_r = 0;
			pot_exec_r = 0;
			corrente_r = 0;
			sentido_r = 0;
#if (com_cht == true)
			for ( aux_b1 = 0; aux_b1 < (NRO_CHT/2); aux_b1++)
				{
				 CHT_cr[aux_b1]=0;
				}
#endif
			}
		}
	else
		{
		soma_pot_efi_r = 0;
		soma_pr = 0;
	    pot_ativa_r = 0;
	    pot_aparente_r = 0;
		pot_reativa_r = 0;
	   	fator_pot_r = 1024;
		pot_req_r = 0;
		pot_exec_r = 0;
		corrente_r = 0;
		tensao_r = 0;
		sentido_r = 0;
#if (com_cht == true)
		for ( aux_b1 = 0; aux_b1 < (NRO_CHT/2); aux_b1++)
			{
			 CHT_tr[aux_b1]=0;
			 CHT_cr[aux_b1]=0;
			}
#endif
			
		}
#if teste_consumo					
   	fator_pot_r = 1024;
#endif
 }  


void calculo_pot_s(void)
{
	int32 aux_lx;
	if (tensao_s > (20 * 64))
		{
		if (corrente_s > ((valor_tc/20)*8))
			{
			if (make8(soma_efi_ps, 3) != 0 )
				{
				sentido_s = 1;
				soma_efi_ps = ~soma_efi_ps;
				soma_efi_ps = soma_efi_ps & 0x00ffffff;
				}
			else
				{
				sentido_s = 0;
				}
	/* calculo da potencia ativa */
			aux_l3 = (int32)(valor_tc);
			aux_l2 = (int32)(254 * mul_kw *  aux_l3);
			aux_l2 = (int32)(aux_l2 >> 9 );
			if (valor_tc == 20)
				{
				aux_lx = aux_l2;	
				}
			aux_l2 = (int32)(aux_l2 / 1000);
			aux_l1 = (int32)(soma_efi_ps * aux_l2);
#if (st9600r == 1)
			aux_l1 = (int32)(aux_l1 / 32768 );
#else
			aux_l1 = (int32)(aux_l1 / 16384 );
#endif
			if (valor_tc == 20)
				{
				aux_b1 = 8;
				}
			else if (valor_tc == 200)
				{
				aux_b1 = 19;
				}
			else
				{
				aux_b1 = 0;
				}
			aux_l2 = (signed word)(1000 + (os_cor_s + os_ten_s + aux_b1));
			aux_l2 = aux_l2 * aux_l1;
			pot_ativa_s = (word)(aux_l2 / 1000);

			if (valor_tc == 20)
				{
				aux_l1 = (int32)(soma_efi_ps * aux_lx);
#if (st9600r == 1)
				aux_l1 = (int32)(aux_l1 / 32768 );
#else
				aux_l1 = (int32)(aux_l1 / 16384 );
#endif
				aux_b1 = 8;
				aux_l2 = (signed word)(1000 + (os_cor_s + os_ten_s + aux_b1));
				aux_l2 = (int32)(aux_l2 * aux_l1);
				pot_ativa_s_long = aux_l2 / 1000;

				}
			
	
	/* calculo da potencia aparente */
			if (valor_tp !=1)
				{
				aux_l1 = (int32)(tensao_s);
				aux_l1 = (int32)(aux_l1 * 1.7320508);
				aux_l2 = (int32)(aux_l1 * (word)(valor_tp));
		    	aux_l2 = aux_l2 * corrente_s;
			    data1_int = (word)((aux_l2 / 16000) / 100);
				}
			else
				{    
		    	aux_l1 = tensao_s;
			    aux_l1 = aux_l1 * corrente_s;
			    data1_int = aux_l1 / 16000;
				if (valor_tc == 20)
					{
			    	aux_l1 = tensao_s;
				    aux_l1 = aux_l1 * corrente_s;
				    pot_aparente_s_long = aux_l1 / 16;
					}
		    	}
			pot_aparente_s = data1_int;		
		   	if (pot_ativa_s > pot_aparente_s)
		   		{
			   	pot_ativa_s = pot_aparente_s;
			   	}
		   	data1_int = pot_aparente_s - pot_ativa_s;
			if (valor_tc == 20)
				{
				if (data1_int < 6)
					{
			   		pot_ativa_s = pot_aparente_s;
					}
				}

#if teste_consumo					
	pot_ativa_s = 59;				
	pot_aparente_s = 125;
#endif

	
			if (pot_ativa_s != pot_aparente_s)
				{
	/* calculo da potencia reativa */    
		/* Kvar = sqr(kva^2 - Kw^) */	
				aux_l1 = pot_ativa_s;
				aux_l1 = aux_l1 * aux_l1;
				aux_l2 = pot_aparente_s;
				aux_l2 = aux_l2 * aux_l2;
				pot_reativa_s =(word)(sqrtx(aux_l2 - aux_l1));
		
	/* calculo do fator de potencia  */    
				if (valor_tc != 20)
					{
					aux_l1 = pot_ativa_s;
					aux_l1 = (int32)(aux_l1 * 1024);
					aux_w1 = (word)(aux_l1 / pot_aparente_s);
					}
				else
					{
					aux_l1 = pot_ativa_s_long;
					aux_l1 = (int32)(aux_l1 * 1024);
					aux_w1 = (word)(aux_l1 / pot_aparente_s_long);
					}
	
				if (sinal_fp[1] == '-')
					{
	    			aux_w1 = aux_w1 * (-1);
					}
				else if (sinal_fp[1] == '1')
					{
					aux_w1 = 1024;
					}
				if ((aux_w1 < 1024) && (aux_w1 > 1018))
					{
					aux_w1 = 1024;
					}
				else if (aux_w1 > 65530)
					{
					aux_w1 = 1024;
					}
				if (aux_w1 == 1024)
					{
//				   	pot_ativa_s = pot_aparente_s;
					}


			   	fator_pot_s = aux_w1;
		
	/* calculo do kvar requerido */	    
	/* pot_req_x = potencia_reativa - srq(((potencia_ativa / setpoint) ^2)) - ( potencia_ativa ^ 2))  */
				kvar_requerido('S');
				}
			else
				{
			   	fator_pot_s = 1024;
				pot_reativa_s = 0;
				pot_req_s = 0;
				pot_exec_s = 0;
				}
			}
		else
			{
			soma_pot_efi_s = 0;
			soma_ps = 0;
		    pot_ativa_s = 0;
		    pot_aparente_s = 0;
			pot_reativa_s = 0;
		   	fator_pot_s = 1024;
			pot_req_s = 0;
			pot_exec_s = 0;
			corrente_s = 0;
			sentido_s = 0;
#if (com_cht == true)
			for ( aux_b1 = 0; aux_b1 < NRO_CHT; aux_b1++)
				{
				 CHT_cs[aux_b1]=0;
				}
#endif
			}
		}
	else
		{
		soma_pot_efi_s = 0;
		soma_ps = 0;
	    pot_ativa_s = 0;
	    pot_aparente_s = 0;
		pot_reativa_s = 0;
	   	fator_pot_s = 1024;
		pot_req_s = 0;
		pot_exec_s = 0;
		corrente_s = 0;
		tensao_s = 0;
		sentido_s = 0;
#if (com_cht == true)
		for ( aux_b1 = 0; aux_b1 < NRO_CHT; aux_b1++)
			{
			 CHT_ts[aux_b1]=0;
			 CHT_cs[aux_b1]=0;
			}
#endif
		}
#if teste_consumo					
   	fator_pot_s = 1024;
#endif

}  


void calculo_pot_t(void)
{
	int32 aux_lx;
	if (tensao_t > (20 * 64))
		{
		if (corrente_t > ((valor_tc/20)*8))
			{
			if (make8(soma_efi_pt, 3) != 0 )
				{
				sentido_t = 1;
				soma_efi_pt = ~soma_efi_pt;
				soma_efi_pt = soma_efi_pt & 0x00ffffff;
				}
			else
				{
				sentido_t = 0;
				}
	/* calculo da potencia ativa */
			aux_l3 = (int32)(valor_tc);
			aux_l2 = (int32)(254 * mul_kw *  aux_l3);
			aux_l2 = (int32)(aux_l2 >> 9 );
			if (valor_tc == 20)
				{
				aux_lx = aux_l2;	
				}
			aux_l2 = (int32)(aux_l2 / 1000);
			aux_l1 = (int32)(soma_efi_pt * aux_l2);
#if (st9600r == 1)
			aux_l1 = (int32)(aux_l1 / 32768 );
#else
			aux_l1 = (int32)(aux_l1 / 16384 );
#endif
			if (valor_tc == 20)
				{
				aux_b1 = 8;
				}
			else if (valor_tc == 200)
				{
				aux_b1 = 19;
				}
			else
				{
				aux_b1 = 0;
				}
			aux_l2 = (signed word)(1000 + (os_cor_t + os_ten_t + aux_b1));
			aux_l2 = aux_l2 * aux_l1;
			pot_ativa_t = (word)(aux_l2 / 1000);

			if (valor_tc == 20)
				{
				aux_l1 = (int32)(soma_efi_pt * aux_lx);
#if (st9600r == 1)
				aux_l1 = (int32)(aux_l1 / 32768 );
#else
				aux_l1 = (int32)(aux_l1 / 16384 );
#endif
				aux_b1 = 8;
				aux_l2 = (signed word)(1000 + (os_cor_t + os_ten_t + aux_b1));
				aux_l2 = (int32)(aux_l2 * aux_l1);
				pot_ativa_t_long = aux_l2 / 1000;

				}

	
	/* calculo da potencia aparente */
			if (valor_tp !=1)
				{
				aux_l1 = (int32)(tensao_t);
				aux_l1 = (int32)(aux_l1 * 1.7320508);
				aux_l2 = (int32)(aux_l1 * (word)(valor_tp));
		    	aux_l2 = aux_l2 * corrente_t;
			    data1_int = (word)((aux_l2 / 16000) / 100);
				}
			else
				{    
		    	aux_l1 = tensao_t;
			    aux_l1 = aux_l1 * corrente_t;
			    data1_int = aux_l1 / 16000;
				if (valor_tc == 20)
					{
			    	aux_l1 = tensao_t;
				    aux_l1 = aux_l1 * corrente_t;
				    pot_aparente_t_long = aux_l1 / 16;
					}
		    	}
		
			pot_aparente_t = data1_int;		
		   	if (pot_ativa_t > pot_aparente_t)
		   		{
			   	pot_ativa_t = pot_aparente_t;
			   	}

		   	data1_int = pot_aparente_t - pot_ativa_t;
			if (valor_tc == 20)
				{
				if (data1_int < 6)
					{
			   		pot_ativa_t = pot_aparente_t;
					}
				}

#if teste_consumo					
	pot_ativa_t = 59;				
	pot_aparente_t = 125;
#endif
	
			if (pot_ativa_t != pot_aparente_t)
				{
	/* calculo da potencia reativa */    
		/* Kvar = sqr(kva^2 - Kw^) */	
				aux_l1 = pot_ativa_t;
				aux_l1 = aux_l1 * aux_l1;
				aux_l2 = pot_aparente_t;
				aux_l2 = aux_l2 * aux_l2;
				pot_reativa_t =(word)(sqrtx(aux_l2 - aux_l1));
		
	/* calculo do fator de potencia  */    
				if (valor_tc != 20)
					{
					aux_l1 = pot_ativa_t;
					aux_l1 = (int32)(aux_l1 * 1024);
					aux_w1 = (word)(aux_l1 / pot_aparente_t);
					}
				else
					{
					aux_l1 = pot_ativa_t_long;
					aux_l1 = (int32)(aux_l1 * 1024);
					aux_w1 = (word)(aux_l1 / pot_aparente_t_long);
					}
				
	
				if (sinal_fp[2] == '-')
					{
	    			aux_w1 = aux_w1 * (-1);
					}
				else if (sinal_fp[2] == '1')
					{
					aux_w1 = 1024;
					}
				if ((aux_w1 < 1024) && (aux_w1 > 1018))
					{
					aux_w1 = 1024;
					}
				else if (aux_w1 > 65530)
					{
					aux_w1 = 1024;
					}
				if (aux_w1 == 1024)
					{
//				   	pot_ativa_t = pot_aparente_t;
					}
			   	fator_pot_t = aux_w1;
		
	/* calculo do kvar requerido */	    
	/* pot_req_x = potencia_reativa - srq(((potencia_ativa / setpoint) ^2)) - ( potencia_ativa ^ 2))  */
				kvar_requerido('T');
				}
			else
				{
			   	fator_pot_t = 1024;
				pot_reativa_t = 0;
				pot_req_t = 0;
				pot_exec_t = 0;
				}
				
			}
		else
			{
			soma_pot_efi_t = 0;
			soma_pt = 0;
		    pot_ativa_t = 0;
		    pot_aparente_t = 0;
			pot_reativa_t = 0;
		   	fator_pot_t = 1024;
			pot_req_t = 0;
			pot_exec_t = 0;
			corrente_t = 0;
			sentido_t = 0;
#if (com_cht == true)
			for ( aux_b1 = 0; aux_b1 < NRO_CHT; aux_b1++)
				{
				 CHT_ct[aux_b1]=0;
				}
#endif
			}
		}
	else
		{
		soma_pot_efi_t = 0;
		soma_pt = 0;
	    pot_ativa_t = 0;
	    pot_aparente_t = 0;
		pot_reativa_t = 0;
	   	fator_pot_t = 1024;
		pot_req_t = 0;
		pot_exec_t = 0;
		corrente_t = 0;
		tensao_t = 0;;
		sentido_t = 0;
#if (com_cht == true)
		for ( aux_b1 = 0; aux_b1 < NRO_CHT; aux_b1++)
			{
			 CHT_ct[aux_b1]=0;
			 CHT_tt[aux_b1]=0;
			}
#endif			
		}

#if teste_consumo					
   	fator_pot_t = 1024;
#endif
		
}  

*/


