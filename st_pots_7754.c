/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: st_pots                                                        *
; Funcao: MODULO ROTINAS DE CALCULOS de potencias e FP					 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */

#define limitar_kw	false



#if (tc_fixo == true)
void busca_mul_tc(void)
{
	#if (calcular_tc == true)
		for (aux_b1 = 0; aux_b1 < NRO_POSI_TC; aux_b1++)
			{
			aux_w1 = tabela_tc[aux_b1];
			if (aux_w1 == valor_tc)
				{
				mul_tc = (float)(valor_tc);
				mul_tc = (float)(mul_tc/5);
				mul_tc = (float)(mul_tc/100);
				break;
				}
			}
	#else
		mul_tc = 1;
	#endif
}
#endif


word ajusta_tc(word valor)
{
#if (tc_fixo == true)
	#if (calcular_tc == true)
		return((word)(mul_tc * valor));
	#else
		return(valor);
	#endif
#else
	return(valor);
#endif
}

void calcula_fundo_escala_corrente(void)
{
#if ((st5000t == 1) || (st5030t == 1))
	#if (tc_fixo == true)
		aux_l2 = (int32)(valor_tc_fixo);
	#else
		aux_l2 = (int32)(valor_tc);
	#endif
	aux_l2 = (int32)(aux_l2 * 256);			// 8192 = 256*32
	fundo_escala_corrente = (int32)(aux_l2 / 1000);
#else
	mul_tc = (float)(1);
	aux_l2 = (int32)(valor_tc);
	aux_l2 = (int32)(aux_l2 * 8192);			// 8192 = 256*32
	fundo_escala_corrente = (int32)(aux_l2 / 1000);
#endif
}



void le_sinal_fp(char fase)	
{


	if (fase == 'R')
		{
		aux_sw1 = buf_tensao_r[0];
		aux_b2 = 0;
		}
	else if (fase == 'S')
		{
		aux_sw1 = buf_tensao_s[0];
		aux_b2 = 1;
		}
	else if (fase == 'T')
		{
		aux_sw1 = buf_tensao_t[0];
		aux_b2 = 2;
		}
	else
		{
		return;
		}



	if (aux_sw1 > 0)
		{
		zero_r = 1;
		}
	else
		{
		zero_r = 0;
		}	

	for (aux_b1 = 0; aux_b1 < NRO_AMOSTRAS; aux_b1++)
		{
		if (fase == 'R')
			{
			aux_sw1 = buf_tensao_r[aux_b1];
			aux_sw2 = buf_corrente_r[aux_b1];
			}
		else if (fase == 'S')
			{
			aux_sw1 = buf_tensao_s[aux_b1];
			aux_sw2 = buf_corrente_s[aux_b1];
			}
		else if (fase == 'T')
			{
			aux_sw1 = buf_tensao_t[aux_b1];
			aux_sw2 = buf_corrente_t[aux_b1];
			}
		else
			{
			break;
			}


		if (aux_sw1 > 0)
			{
			if (zero_r == 0)
				{
				if (aux_sw2 > 0)
					{
					sinal_fp[aux_b2] = '+';
					}
				else
					{
					sinal_fp[aux_b2] = '-';
					}
				break;
				}
			}
		else
			{
			if (zero_r == 1)
				{
				if (aux_sw2 > 0)
					{
					sinal_fp[aux_b2] = '-';
					}
				else
					{
					sinal_fp[aux_b2] = '+';
					}
				break;
				}
			}
		}
}



void calculo_potencias(char fase)
{
	char indice_fp;
	float aux_f1;
	word tensao;
	word corrente;
	word pot_ativa;
	word pot_aparente;
	word pot_reativa;
	word CF_NUM;
	int32 aux_lx;
	int32 pot_ativa_long;
	int32 pot_aparente_long;
	signed word os_cor;
	signed word os_ten;
	signed word os_pot;
	signed int32 soma_efi_p;

	short sentido;

	if (fase == 'R')
		{
		tensao = tensao_r;
		corrente = corrente_r;
		soma_efi_p = soma_efi_pr;
		os_cor = os_cor_r;
		os_ten = os_ten_r;
		os_pot = os_pot_r;
		indice_fp = 0;
		CF_NUM = CFNUM_R;
		}
	else if (fase == 'S')
		{
		tensao = tensao_s;
		corrente = corrente_s;
		soma_efi_p = soma_efi_ps;
		os_cor = os_cor_s;
		os_ten = os_ten_s;
		os_pot = os_pot_s;
		indice_fp = 1;
		CF_NUM = CFNUM_S;
		}
	else 
		{
		tensao = tensao_t;
		corrente = corrente_t;
		soma_efi_p = soma_efi_pt;
		os_cor = os_cor_t;
		os_ten = os_ten_t;
		os_pot = os_pot_t;
		indice_fp = 2;
		CF_NUM = CFNUM_T;
		}


#if ((st5000T == true) || (st5030T == true))
	if (tensao > (20 * 64))
		{	
		#if (tc_fixo == true)
			{
			aux_w1 = 80;
			}
		#else
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
		#endif
		if (corrente > aux_w1)
			{
			sentido = 0;
			if ( (bit_test(CF_NUM, 12)) || (bit_test(CF_NUM, 13)) || (bit_test(CF_NUM, 14)) )
				{
				sentido = 1;
				soma_efi_p = ~soma_efi_p;
				soma_efi_p = soma_efi_p & 0x0000ffff;
				}

/* calculo da potencia ativa */
			aux_sw1 = 1000;
			aux_sw1 += os_pot;
			aux_sw1 += os_cor;
			aux_sw1 += os_ten;

			aux_sw1 = 1000;

			aux_l2 = (int32)(soma_efi_p * aux_sw1);
			aux_l2 = (int32)(aux_l2 / 1000);
			pot_ativa = (word)(aux_l2);
			                                           
//			if (tipo_ligacao == 2)
//				{
//				aux_l1 = (int32)(aux_l1 * 443);
//				aux_l1 = (int32)(aux_l1 / 256);
//				pot_ativa = (word)(aux_l1);
//				}
		
			if (fase == 'R')
				{
				soma_pot_r += pot_ativa;
				pot_ativa = soma_pot_r >> 1;
				soma_pot_r -= pot_ativa;
				}
			else if (fase == 'S')
				{
				soma_pot_s += pot_ativa;
				pot_ativa = soma_pot_s >> 1;
				soma_pot_s -= pot_ativa;
				}
			else
				{
				soma_pot_t += pot_ativa;
				pot_ativa = soma_pot_t >> 1;
				soma_pot_t -= pot_ativa;
				}



// calculo da potencia aparente 
			if (valor_tp !=1)
				{
				aux_l1 = (int32)(tensao);
				aux_l1 = (int32)(aux_l1 * 1.7320508);
				aux_l2 = (int32)(aux_l1 * (word)(valor_tp));
		    	aux_l2 = aux_l2 * corrente;
			    aux_l1 = (word)((aux_l2 / 16000) / 100);
			    data1_int = (word)(aux_l1);
				}
			else
				{    
		    	aux_l1 = tensao;
			    aux_l1 = aux_l1 * corrente;
			    aux_l1 = (int32)(aux_l1 / 16000);
			    data1_int = (word)(aux_l1);
    			}
//			if (tipo_ligacao == 2)
//				{
//				aux_l1 = (int32)(aux_l1 * 443);
//				aux_l1 = (int32)(aux_l1 / 256);
//				data1_int = (word)(aux_l1);
//				}
		
			pot_aparente = data1_int;		
#if (limitar_kw == true)
		   	if (pot_ativa > pot_aparente)
		   		{
			   	pot_ativa = pot_aparente;
			   	}
#endif

			if (fase == 'R')
				{
				sentido_r = sentido;
				pot_ativa_r = pot_ativa;
				pot_aparente_r = pot_aparente;
				}
			else if (fase == 'S')
				{
				sentido_s = sentido;
				pot_ativa_s = pot_ativa;
				pot_aparente_s = pot_aparente;
				}
			else
				{
				sentido_t = sentido;
				pot_ativa_t = pot_ativa;
				pot_aparente_t = pot_aparente;
				}
	
			if (pot_ativa != pot_aparente)
				{
				if (pot_ativa > pot_aparente)
					{
					pot_reativa =0;
					aux_w1 = 1024;
					}
				else
					{
/* calculo da potencia reativa */    
/* Kvar = sqr(kva^2 - Kw^2) */	
					aux_l1 = pot_ativa;
					aux_l1 = (int32)(aux_l1 * aux_l1);
					aux_l2 = pot_aparente;
					aux_l2 = (int32)(aux_l2 * aux_l2);
					pot_reativa =(word)(sqrtx(aux_l2 - aux_l1));
		
/* calculo do fator de potencia  */    
					aux_l1 = pot_ativa;
					aux_l1 = (int32)(aux_l1 * 1024);
					aux_w1 = (word)(aux_l1 / pot_aparente);
	
					if (sinal_fp[indice_fp] == '-')
						{
		    			aux_w1 = aux_w1 * (-1);
						}
					else if (sinal_fp[indice_fp] == '1')
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
					}					
#if (limitar_kw == true)
				if ((aux_w1 == 1024) || (aux_w1 == 0))
					{
				   	pot_ativa = pot_aparente;
					pot_reativa = 0;
					}
#endif
				if (fase == 'R')
					{
				   	fator_pot_r = aux_w1;
					pot_reativa_r = pot_reativa;
					}
				else if (fase == 'S')
					{
				   	fator_pot_s = aux_w1;
					pot_reativa_s = pot_reativa;
					}
				else
					{
				   	fator_pot_t = aux_w1;
					pot_reativa_t = pot_reativa;
					}
				}
			else
				{
				if (fase == 'R')
					{
				   	fator_pot_r = 1024;
					pot_reativa_r = 0;
					pot_req_r = 0;
					pot_exec_r = 0;
					}
				else if (fase == 'S')
					{
				   	fator_pot_s = 1024;
					pot_reativa_s = 0;
					pot_req_s = 0;
					pot_exec_s = 0;
					}
				else
					{
				   	fator_pot_t = 1024;
					pot_reativa_t = 0;
					pot_req_t = 0;
					pot_exec_t = 0;
					}
				}
			}
		else
			{
			if (fase == 'R')
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
				}
			else if (fase == 'S')
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
				}
			else
				{
				soma_pot_efi_t = 0;
				soma_ps = 0;
			    pot_ativa_t = 0;
			    pot_aparente_t = 0;
				pot_reativa_t = 0;
			   	fator_pot_t = 1024;
				pot_req_t = 0;
				pot_exec_t = 0;
				corrente_t = 0;
				sentido_t = 0;
				}

#if (com_cht == true)
			for ( aux_b1 = 0; aux_b1 < (NRO_CHT/2); aux_b1++)
				{
				if (fase == 'R')
					{
					 if (CHT_cr[aux_b1] == 0)
						{
						break;
						}
					 CHT_cr[aux_b1] = 0;
					 buf_corrente_r[aux_b1] = 0;
					}
				else if (fase == 'S')
					{
					 if (CHT_cs[aux_b1] == 0)
						{
						break;
						}
					 CHT_cs[aux_b1] = 0;
					 buf_corrente_t[aux_b1] = 0;
					}
				else  
					{
					 if (CHT_ct[aux_b1] == 0)
						{
						break;
						}
					 CHT_ct[aux_b1] = 0;
					 buf_corrente_t[aux_b1] = 0;
					}
				}
#endif
			}
		}
	else
		{
		if (fase == 'R')
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
			}
		else if (fase == 'S')
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
			tensao_t = 0;
			sentido_t = 0;
			}

	#if (com_cht == true)
			for ( aux_b1 = 0; aux_b1 < (NRO_CHT/2); aux_b1++)
				{
				if (fase == 'R')
					{
					 if (CHT_tr[aux_b1] == 0)
						{
						break;
						}
					CHT_tr[aux_b1]=0;
				 	CHT_cr[aux_b1]=0;
					buf_tensao_r[aux_b1] = 0;
					buf_corrente_r[aux_b1] = 0;
					}
				else if (fase == 'S')
					{
					 if (CHT_ts[aux_b1] == 0)
						{
						break;
						}
					CHT_ts[aux_b1]=0;
				 	CHT_cs[aux_b1]=0;
					buf_tensao_s[aux_b1] = 0;
					buf_corrente_s[aux_b1] = 0;
					}
				else
					{
					 if (CHT_tt[aux_b1] == 0)
						{
						break;
						}
					CHT_tt[aux_b1]=0;
				 	CHT_ct[aux_b1]=0;
					buf_tensao_t[aux_b1] = 0;
					buf_corrente_t[aux_b1] = 0;
					}
				}
	#endif
		
		}



//********************* PARA O ST9600R ***********************
#else
	if (tensao > (20 * 64))
		{	
		#if (tc_fixo == true)
			aux_w1 = 80;
		#else
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
		#endif
		if (corrente > aux_w1)
			{
			if (make8(soma_efi_p, 3) != 0 )
				{
				sentido = 1;
				soma_efi_p = ~soma_efi_p;
				soma_efi_p = soma_efi_p & 0x00ffffff;
				}
			else
				{
				sentido = 0;
				}
			if (fase == 'R')
				{
				sentido_r = sentido;
				}
			else if (fase == 'S')
				{
				sentido_s = sentido;
				}
			else  
				{
				sentido_t = sentido;
				}

/* calculo da potencia ativa */
//
			aux_l1 = (int32)(fundo_escala_corrente * soma_efi_p);
			aux_l1 = (int32)(aux_l1 / (520192));
//
			#if (tc_fixo == true)
			#else
				if (valor_tc == 20)
					{
					aux_lx = fundo_escala_corrente * 1000;	
					}
			#endif
			aux_l2 = (signed word)(1000 + (os_cor + os_ten + os_pot));
			aux_l2 = (int32)(aux_l2 * aux_l1);
			pot_ativa = (word)(aux_l2 / 1000);

			#if (tc_fixo == true)
			#else
				if (valor_tc == 20)
					{
					aux_l1 = (int32)(soma_efi_p * aux_lx);
					aux_l1 = (int32)(aux_l1 / (520192));
	
					aux_l2 = (signed word)(1000 + (os_cor + os_ten + os_pot));
					aux_l2 = (int32)(aux_l2 * aux_l1);
					pot_ativa_long = aux_l2 / 1000;
					}
			#endif
	
	/* calculo da potencia aparente */
			if (valor_tp !=1)
				{
				aux_l1 = (int32)(tensao);
				aux_l1 = (int32)(aux_l1 * 1.7320508);
				aux_l2 = (int32)(aux_l1 * (word)(valor_tp));
		    	aux_l2 = aux_l2 * corrente;
			    data1_int = (word)((aux_l2 / 16000) / 100);
				}
			else
				{    
		    	aux_l1 = tensao;
			    aux_l1 = aux_l1 * corrente;
			    data1_int = aux_l1 / 16000;
#if (tc_fixo == true)
#else
				if (valor_tc == 20)
					{
			    	aux_l1 = tensao;
				    aux_l1 = aux_l1 * corrente;
				    pot_aparente_long = aux_l1 / 16;
					}
#endif
    			}
		
			pot_aparente = data1_int;		
		   	if (pot_ativa > pot_aparente)
		   		{
			   	pot_ativa = pot_aparente;
			   	}

		   	data1_int = pot_aparente - pot_ativa;
#if (tc_fixo == true)
#else
			if (valor_tc == 20)
				{
				if (data1_int < 6)
					{
			   		pot_ativa = pot_aparente;
					}
				}
#endif

#if teste_consumo					
	pot_ativa = 59;
#endif
			if (fase == 'R')
				{
				pot_aparente_r = pot_aparente;
				pot_ativa_r = pot_ativa;
				}
			else if (fase == 'S')
				{
				pot_ativa_s = pot_ativa;
				pot_aparente_s = pot_aparente;
				}
			else
				{
				pot_ativa_t = pot_ativa;
				pot_aparente_t = pot_aparente;
				}
	
			if (pot_ativa != pot_aparente)
				{
/* calculo da potencia reativa */    
/* Kvar = sqr(kva^2 - Kw^) */	
				aux_l1 = pot_ativa;
				aux_l1 = (int32)(aux_l1 * aux_l1);
				aux_l2 = pot_aparente;
				aux_l2 = (int32)(aux_l2 * aux_l2);
				pot_reativa =(word)(sqrtx(aux_l2 - aux_l1));
		
/* calculo do fator de potencia  */    
//				if (valor_tc != 20)
//					{
					aux_l1 = pot_ativa;
					aux_l1 = (int32)(aux_l1 * 1024);
					aux_w1 = (word)(aux_l1 / pot_aparente);
//					}
//				else
//					{
//					aux_l1 = pot_ativa_long;
//					aux_l1 = (int32)(aux_l1 * 1024);
//					aux_w1 = (word)(aux_l1 / pot_aparente_long);
//					}
				if (sinal_fp[indice_fp] == '-')
					{
	    			aux_w1 = aux_w1 * (-1);
					}
				else if (sinal_fp[indice_fp] == '1')
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
				   	pot_ativa = pot_aparente;
					pot_reativa = 0;
					}
				if (fase == 'R')
					{
				   	fator_pot_r = aux_w1;
					pot_reativa_r = pot_reativa;
					}
				else if (fase == 'S')
					{
				   	fator_pot_s = aux_w1;
					pot_reativa_s = pot_reativa;
					}
				else
					{
				   	fator_pot_t = aux_w1;
					pot_reativa_t = pot_reativa;
					}
				}
			else
				{
				if (fase == 'R')
					{
				   	fator_pot_r = 1024;
					pot_reativa_r = 0;
					pot_req_r = 0;
					pot_exec_r = 0;
					}
				else if (fase == 'S')
					{
				   	fator_pot_s = 1024;
					pot_reativa_s = 0;
					pot_req_s = 0;
					pot_exec_s = 0;
					}
				else
					{
				   	fator_pot_t = 1024;
					pot_reativa_t = 0;
					pot_req_t = 0;
					pot_exec_t = 0;
					}
				}
			}
		else
			{
			if (fase == 'R')
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
				}
			else if (fase == 'S')
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
				}
			else
				{
				soma_pot_efi_t = 0;
				soma_ps = 0;
			    pot_ativa_t = 0;
			    pot_aparente_t = 0;
				pot_reativa_t = 0;
			   	fator_pot_t = 1024;
				pot_req_t = 0;
				pot_exec_t = 0;
				corrente_t = 0;
				sentido_t = 0;
				}

#if (com_cht == true)
			for ( aux_b1 = 0; aux_b1 < (NRO_CHT/2); aux_b1++)
				{
				if (fase == 'R')
					{
					 CHT_cr[aux_b1]=0;
					}
				else if (fase == 'S')
					{
					 CHT_cs[aux_b1]=0;
					}
				else  
					{
					 CHT_ct[aux_b1]=0;
					}
				}
#endif
			}
		}
	else
		{
		if (fase == 'R')
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
			}
		else if (fase == 'S')
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
			tensao_t = 0;
			sentido_t = 0;
			}

	#if (com_cht == true)
			for ( aux_b1 = 0; aux_b1 < (NRO_CHT/2); aux_b1++)
				{
				if (fase == 'R')
					{
					CHT_tr[aux_b1]=0;
				 	CHT_cr[aux_b1]=0;
					}
				else if (fase == 'S')
					{
					CHT_ts[aux_b1]=0;
				 	CHT_cs[aux_b1]=0;
					}
				else
					{
					CHT_tt[aux_b1]=0;
				 	CHT_ct[aux_b1]=0;
					}
				}
	#endif
		
		}
#endif
#if teste_consumo					
   	fator_pot_r = 1024;
#endif
 }  






