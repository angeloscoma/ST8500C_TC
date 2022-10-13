/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: st_CALC                                                        *
; Funcao: MODULO ROTINAS DE CALCULOS   									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */



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
// TRATAMENTO DA INTERRUPÇÃO EXTERNA 2  FASE s//

	goto calcula_tensao_corrente_10;
	aux_ten_l = read_cs5460(V_rms,'R');
	aux_cor_l = read_cs5460(I_rms,'R');
	aux_pot_l = read_cs5460(E_register,'R');

//	output_low(CS5460A_CS_R);
	output_low(CS5460A_CS_S);
//	output_low(CS5460A_CS_T);
	write_cs5460_byte(start_conversions);

calcula_tensao_corrente_10:
	output_high(CS5460A_CS_R);
	output_high(CS5460A_CS_S);
	output_high(CS5460A_CS_T);

	med_ten_ok = 0;
	calc_ten_ok = 0;


}


#define mul_kw 870 	// (1,36 * 1,25 * 1,4142 * 1,4142 ) * 256

void calculo_pot_r(void)
{
	if (tensao_r > (20 * 64))
		{	
		if (corrente_r > ((valor_tc/20) << 3))		//  	*8))
			{
/* calculo da potencia ativa */
			aux_l2 = (signed word)(1000 + (os_cor_r + os_ten_r + aux_b1));
			aux_l2 = (int32)(aux_l2 * aux_l1);
			pot_ativa_r = (word)(aux_l2 / 1000);
			
#if teste_consumo					
	pot_ativa_r = 20 * 32;				
#endif
	
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

	
			if (pot_ativa_r != pot_aparente_r)
				{
/* calculo da potencia reativa */    
/* Kvar = sqr(kva^2 - Kw^) */	
				aux_l1 = pot_ativa_r;
				aux_l1 = (int32)(aux_l1 * aux_l1);
				aux_l2 = pot_aparente_r;
				aux_l2 = (int32)(aux_l2 * aux_l2);
				pot_reativa_r =(word)(sqrt(aux_l2 - aux_l1));
		
/* calculo do fator de potencia  */    
				aux_l1 = pot_ativa_r;
				aux_l1 = (int32)(aux_l1 * 1024);
				aux_w1 = (word)(aux_l1 / pot_aparente_r);

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
				aux_b1 = 'R';
				kvar_requerido();
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
			for ( aux_b1 = 0; aux_b1 < (NRO_CHT/2); aux_b1++)
				{
				 CHT_cr[aux_b1]=0;
				}
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
		for ( aux_b1 = 0; aux_b1 < (NRO_CHT/2); aux_b1++)
			{
			 CHT_tr[aux_b1]=0;
			 CHT_cr[aux_b1]=0;
			}
			
		}
}  


void calculo_pot_s(void)
{
	if (tensao_s > (20 * 64))
		{
		if (corrente_s > ((valor_tc/20)*8))
			{
	/* calculo da potencia ativa */
			aux_l2 = (signed word)(1000 + (os_cor_s + os_ten_s + aux_b1));
			aux_l2 = aux_l2 * aux_l1;
			pot_ativa_s = (word)(aux_l2 / 1000);
			
#if teste_consumo					
	pot_ativa_s = 20 * 32;				
#endif
	
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

	
			if (pot_ativa_s != pot_aparente_s)
				{
	/* calculo da potencia reativa */    
		/* Kvar = sqr(kva^2 - Kw^) */	
				aux_l1 = pot_ativa_s;
				aux_l1 = aux_l1 * aux_l1;
				aux_l2 = pot_aparente_s;
				aux_l2 = aux_l2 * aux_l2;
				pot_reativa_s =(word)(sqrt(aux_l2 - aux_l1));
		
	/* calculo do fator de potencia  */    
				aux_l1 = pot_ativa_s;
				aux_l1 = (int32)(aux_l1 * 1024);
				aux_w1 = (word)(aux_l1 / pot_aparente_s);
	
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
				aux_b1 = 'S';
				kvar_requerido();
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
			for ( aux_b1 = 0; aux_b1 < NRO_CHT; aux_b1++)
				{
				 CHT_cs[aux_b1]=0;
				}
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
		for ( aux_b1 = 0; aux_b1 < NRO_CHT; aux_b1++)
			{
			 CHT_ts[aux_b1]=0;
			 CHT_cs[aux_b1]=0;
			}
		}
}  


void calculo_pot_t(void)
{
	if (tensao_t > (20 * 64))
		{
		if (corrente_t > ((valor_tc/20)*8))
			{
	/* calculo da potencia ativa */
			aux_l2 = (signed word)(1000 + (os_cor_t + os_ten_t + aux_b1));
			aux_l2 = aux_l2 * aux_l1;
			pot_ativa_t = (word)(aux_l2 / 1000);

#if teste_consumo					
	pot_ativa_t = 20 * 32;				
#endif
	
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
	
			if (pot_ativa_t != pot_aparente_t)
				{
	/* calculo da potencia reativa */    
		/* Kvar = sqr(kva^2 - Kw^) */	
				aux_l1 = pot_ativa_t;
				aux_l1 = aux_l1 * aux_l1;
				aux_l2 = pot_aparente_t;
				aux_l2 = aux_l2 * aux_l2;
				pot_reativa_t =(word)(sqrt(aux_l2 - aux_l1));
		
	/* calculo do fator de potencia  */    
				aux_l1 = pot_ativa_t;
				aux_l1 = (int32)(aux_l1 * 1024);
				aux_w1 = (word)(aux_l1 / pot_aparente_t);
				
	
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
				aux_b1 = 'T';
				kvar_requerido();
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
			for ( aux_b1 = 0; aux_b1 < NRO_CHT; aux_b1++)
				{
				 CHT_ct[aux_b1]=0;
				}
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
		for ( aux_b1 = 0; aux_b1 < NRO_CHT; aux_b1++)
			{
			 CHT_ct[aux_b1]=0;
			 CHT_tt[aux_b1]=0;
			}
			
		}

		
}  

void calc_tensao_ff(void)
{
/* calcula tensao entre R e S */	
	aux_w1 = (word)(tensao_r + (tensao_s >> 1));
	aux_l1 = tensao_s;
	aux_l1 = (int32)(aux_l1 * 887);
	aux_w2 = (word)(aux_l1 >> 10);
	mulu_ww_int(aux_w1, aux_w1);
	aux_l1 = res_32b;
	mulu_ww_int(aux_w2, aux_w2);
	aux_l2 = res_32b;
	aux_l1 = (sqrt(aux_l1 + aux_l2));
	tensao_rs = (word)(aux_l1);

/* calcula tensao entre T e S */	
	aux_w3 = (signed word)((-1) * (tensao_s >> 1 ));
	aux_w4 = (signed word)((-1) * (tensao_t >> 1 ));
	aux_w3 = aux_w3 - aux_w4;
	aux_l1 = pow(aux_w3,2);
	
	aux_l1 = tensao_s;
	aux_l1 = aux_l1  * 887;
	aux_w3 = aux_l1 >> 10;
	aux_l1 = tensao_t;
	aux_l1 = aux_l1  * 887;
	aux_w1 = aux_l1 >> 10;
	aux_w4 = (signed word)((-1) * aux_w1);
	aux_w4 = aux_w3 - aux_w4;
	aux_l2 = pow(aux_w4,2);
	
	tensao_st = (word)(sqrt(aux_l1+aux_l2));

/* calcula tensao entre R e T */	
	aux_w2 = tensao_r +(tensao_t >> 1);
	aux_l1 = tensao_t;
	aux_l1 = aux_l1 * 887;
	aux_w1 = aux_l1 >>10;
	aux_l1 = pow(aux_w2,2);
	aux_l2 = pow(aux_w1,2);
	tensao_rt = (word)(sqrt(aux_l1 + aux_l2));

}

void calc_tensao_alta(void)
{	
	if (valor_tp == 1)
		{
		tensao_rs_na_alta = tensao_rs;
		tensao_st_na_alta = tensao_st;
		tensao_rt_na_alta = tensao_rt;
		}
	else
		{
		aux_l1 = (int32)(tensao_rs);
		aux_l1 = (int32)(aux_l1 * valor_tp) / 1000;
		tensao_rs_na_alta = (word)(aux_l1);
	
		aux_l1 = (int32)(tensao_st);
		aux_l1 = (int32)(aux_l1 * valor_tp) / 1000;
		tensao_st_na_alta = (word)(aux_l1);
		
		aux_l1 = (int32)(tensao_rt);
		aux_l1 = (int32)(aux_l1 * valor_tp) / 1000;
		tensao_rt_na_alta = (word)(aux_l1);
		}
}	


void calc_tensao_corrente_tri(void)
{	
// calculos de tensao e corrente trifásica	

#if com_regs
	if (registro == 1)
		{
		soma_reg();
		}
#endif	

	if (tipo_ligacao == 0)		// estrela = 1, em estrela;  estrela = 0, em delta
		{
	 	aux_l3 = (int32)(tensao_rs + tensao_st + tensao_rt) / 3;
		}
	else
		{
	 	aux_l3 = (int32)(tensao_r + tensao_s + tensao_t) / 3;
 		aux_l3 = (int32)(aux_l3 * 1.7320508);
 		}
	tensao_tri = (word)(aux_l3);

	soma_pot_ati = (int32)(pot_ativa_r +  pot_ativa_s + pot_ativa_t);
	soma_pot_reat = (int32)(pot_reativa_r + pot_reativa_s + pot_reativa_t);
	soma_pot_ati = (int32)(soma_pot_ati * soma_pot_ati);
	soma_pot_reat = (int32)(soma_pot_reat * soma_pot_reat);
	pot_apa_tri = (int32)(sqrt((float)(soma_pot_ati + soma_pot_reat))); 	 
	pot_apa_tri = (int32)((pot_apa_tri * 1000) << 4); 	 

 	aux_l3 = (int32)(aux_l3 * 1.7320508);		/* aux_l3 já tem tensao_tri */
 	aux_l3 = (int32)(aux_l3 * valor_tp);		/* aux_l3 já tem tensao_tri */
 	aux_l3 = (int32)(pot_apa_tri / aux_l3);
 	
 	corrente_tri = (word)(aux_l3);
}


void calculo_trifasico(void)
{

// calculo do fator de potencia total 
if (modo_funca != 2)
	{
	calc_fator_total();
	}

	calc_tensao_ff();

	calc_tensao_alta();

	calc_tensao_corrente_tri();
	
}



void calc_fator_total(void)
{    

/* calculo do fator de potencia total */
	sinal_r = 0;
	sinal_s = 0;
	sinal_t = 0;
	
	if ((fator_pot_r == 1024) && (fator_pot_s == 1024) && (fator_pot_t == 1024))
		{
		 fator_pot = 1024;
		 return;
		}

	soma_pot_apa = (int32)(pot_aparente_r +  pot_aparente_s + pot_aparente_t);
	soma_pot_ati = (int32)(pot_ativa_r +  pot_ativa_s + pot_ativa_t) * 1024;
	aux_l3 = soma_pot_ati / soma_pot_apa;
	fator_pot = (signed long int)(aux_l3);

	if (fator_pot_r != 1024)
		{
		sinal_r = fator_pot_r;
		}
	if (fator_pot_s != 1024)
		{
		sinal_s = fator_pot_s;
		}
	if (fator_pot_t != 1024)
		{
		sinal_t = fator_pot_t;
		}
	sinal_r = sinal_r + sinal_s + sinal_t;
		
	if (sinal_r > 0)
		{
		sinal = 1;
		}
	else
		{
		sinal = (-1);
		}
	
	fator_pot = fator_pot * sinal;
	
}




void kvar_requerido(void)
{
/* pot_req_x = potencia_reativa - srq(((potencia_ativa / setpoint) ^2)) - ( potencia_ativa ^ 2))  */

	if (aux_b1=='R')
		{
		if (pot_reativa_r == 0)
			{
			pot_exec_r = 0;
			pot_req_r = 0;
			return;
			}
		if (fator_pot_r > 0 )
			{
			pot_req_r = 0;
			pot_exec_r = pot_reativa_r;
			return;
			}
		else
			{
			pot_exec_r = 0;
			aux_w1 = (word)(fator_pot_r * (-1));
			aux_w1 = (word)(aux_w1 / 10.24);
			if (aux_w1 >= set_point)
				{
				return;
				}
			}
		}
	else if (aux_b1=='S')
		{
		if (pot_reativa_s == 0)
			{
			pot_exec_s = 0;
			pot_req_s = 0;
			return;
			}
		if (fator_pot_s > 0 )
			{
			pot_req_s = 0;
			pot_exec_s = pot_reativa_s;
			return;
			}
		else
			{
			pot_exec_s = 0;
			aux_w1 = (word)(fator_pot_s * (-1));
			aux_w1 = (word)(aux_w1 / 10.24);
			if (aux_w1 >= set_point)
				{
				return;
				}
			}
		}
	else 
		{
		if (pot_reativa_t == 0)
			{
			pot_exec_t = 0;
			pot_req_t = 0;
			return;
			}
		if (fator_pot_t > 0 )
			{
			pot_req_t = 0;
			pot_exec_t = pot_reativa_t;
			return;
			}
		else
			{
			pot_exec_t = 0;
			aux_w1 = (word)(fator_pot_t * (-1));
			aux_w1 = (word)(aux_w1 / 10.24);
			if (aux_w1 >= set_point)
				{
				return;
				}
			}
		}
		
	if (aux_b1=='R')
		{
		aux_w2 = pot_ativa_r;
		aux_w1 = pot_reativa_r;
		}
	else if (aux_b1=='S')
		{
		aux_w2 = pot_ativa_s;
		aux_w1 = pot_reativa_s;
		}
	else 
		{
		aux_w2 = pot_ativa_t;
		aux_w1 = pot_reativa_t;
		}
	aux_l3 = (int32)(aux_w1);
	
	if (valor_tp != 1)
		{
		aux_l1 = (int32)(aux_w2); 
		aux_l1 = (int32)(aux_l1 * 100);
		aux_l2 = aux_l1;
		
		aux_l3 = (int32)(aux_w1); 
		aux_l3 = (int32)(aux_l3 * 100);
		}

    aux_l1 = (int32)(aux_l1 * 100);
    aux_l1 = (word)(aux_l1 / set_point);	
    aux_l1 = aux_l1 * aux_l1;
    aux_l2 = aux_l2 * aux_l2;
    aux_l1 = (int32)(sqrt(aux_l1 - aux_l2));

	aux_w1 = (word)((aux_l3 - aux_l1) / 1000);	
	
	if (aux_b1=='R')
		{
		pot_req_r = aux_w1;
		}
	else if (aux_b1=='S')
		{
		pot_req_s = aux_w1;
		}
	else 
		{
		pot_req_t = aux_w1;
		}	

		
}

/*   calculo de frequencia
	Funçao: Calcular a frequencia da fase R
	Entrada: val_freq com o nro de interrupçoes do timer e da interrupcao de rede
	saida: Frequencia em Q2.
	Obs.  se freq_final = 0, frequencia = 60hz
	para calculo da regra de tres, temos que com 60hz, temos 32 * 60 interrupcoes 
	do timer = INTS_PER_SECOND(= 1920 => definicao na st_main.c)
	freq_final * 240(60hz em q2) / INTS_PER_SECOND
*/
void calc_frequencia(void)
{
	aux_l1 = (int32)(freq_final * 240);
	frequencia = (char)(aux_l1 / (INTS_PER_SECOND * 2));
	if (frequencia < 40)
		{
		frequencia = 240;	
		}
	calcular_frequencia = 0;
}


void seta_fase_r(void)
{
}
void seta_fase_s(void)
{
}
void seta_fase_t(void)
{
}
void le_sinal_fp(void)
{
}
