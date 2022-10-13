/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: st_CALC                                                        *
; Funcao: MODULO ROTINAS DE CALCULOS   									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */


void calculo_potencias(char fase)
{
	int32 aux_lx;
	char indice_fp;
	word tensao;
	word corrente;
	word pot_ativa;
	word pot_aparente;
	word pot_reativa;
	int32 pot_ativa_long;
	int32 pot_aparente_long;
	signed word os_cor;
	signed word os_ten;
	signed int32 soma_efi_p;

	short sentido;

	if (fase == 'R')
		{
		tensao = tensao_r;
		corrente = corrente_r;
		soma_efi_p = soma_efi_pr;
		os_cor = os_cor_r;
		os_ten = os_ten_r;
		pot_ativa = pot_ativa_r;
		indice_fp = 0;
		}
	else if (fase == 'S')
		{
		tensao = tensao_s;
		corrente = corrente_s;
		soma_efi_p = soma_efi_ps;
		os_cor = os_cor_s;
		os_ten = os_ten_s;
		pot_ativa = pot_ativa_s;
		indice_fp = 1;
		}
	else 
		{
		tensao = tensao_t;
		corrente = corrente_t;
		soma_efi_p = soma_efi_pt;
		os_cor = os_cor_t;
		os_ten = os_ten_t;
		pot_ativa = pot_ativa_t;
		indice_fp = 2;
		}

	if (tensao > (20 * 64))
		{	
		if (corrente > ((valor_tc/20) << 3))		//  	*8))
			{
	
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
    			}
		
			pot_aparente = data1_int;		
		   	if (pot_ativa > pot_aparente)
		   		{
//			   	pot_ativa = pot_aparente;
			   	}

		   	data1_int = pot_aparente - pot_ativa;
			if (valor_tc == 20)
				{
				if (data1_int < 6)
					{
//			   		pot_ativa = pot_aparente;
					}
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
					
				if (aux_w1 == 1024)
					{
				   	pot_ativa = pot_aparente;
					pot_reativa = 0;
					}

				if (fase == 'R')
					{
				   	fator_pot_r = aux_w1;
//					pot_ativa_r = pot_ativa;
					pot_aparente_r = pot_aparente;
					pot_reativa_r = pot_reativa;
					kvar_requerido('R');
					}
				else if (fase == 'S')
					{
				   	fator_pot_s = aux_w1;
//					pot_ativa_s = pot_ativa;
					pot_aparente_s = pot_aparente;
					pot_reativa_s = pot_reativa;
					kvar_requerido('S');
					}
				else
					{
				   	fator_pot_t = aux_w1;
//					pot_ativa_t = pot_ativa;
					pot_aparente_t = pot_aparente;
					pot_reativa_t = pot_reativa;
/* calculo do kvar requerido */	    
/* pot_req_x = potencia_reativa - srq(((potencia_ativa / setpoint) ^2)) - ( potencia_ativa ^ 2))  */
					kvar_requerido('T');
					}

				}
			}
		else
			{
			if (fase == 'R')
				{
			   	fator_pot_r = 1024;
				pot_ativa_r = 0;
				pot_aparente_r = 0;
				pot_reativa_r = 0;
				pot_req_r = 0;
				pot_exec_r = 0;
				corrente_r = 0;
				sentido_r = 0;
				}
			else if (fase == 'S')
				{
			   	fator_pot_s = 1024;
				pot_ativa_s = 0;
				pot_aparente_s = 0;
				pot_reativa_s = 0;
				pot_req_s = 0;
				pot_exec_s = 0;
				corrente_s = 0;
				sentido_s = 0;
				}
			else
				{
			   	fator_pot_r = 1024;
				pot_ativa_t = 0;
				pot_aparente_t = 0;
				pot_reativa_t = 0;
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
}  


