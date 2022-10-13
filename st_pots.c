/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRONICOS								     *
; Modulo: st_pots                                                        *
; Funcao: MODULO ROTINAS DE CALCULOS de potencias e FP					 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */


void busca_mul_tc(void){
	char aux_bx;
	word aux_wx;
	for (aux_bx = 0; aux_bx < NRO_POSI_TC; aux_bx++)
		{
		aux_wx = tabela_tc[aux_bx];
		if (aux_wx == valor_tc){
			mul_tc = (float)(valor_tc);
			mul_tc = (float)(mul_tc/500);
			break;
		}
	}
}

void calcula_fundo_escala_corrente(void){

}

void zera_soma_pot(void){
	soma_ten_r = 0;
	soma_cor_r = 0;
	soma_pot_r = 0;
	soma_ten_s = 0;
	soma_cor_s = 0;
	soma_pot_s = 0;
	soma_ten_t = 0;
	soma_cor_t = 0;
	soma_pot_t = 0;
}

void calculo_potencias(char fase){
	char indice_fp;
	word tensao;
	word corrente;
	word pot_ativa;
	word pot_aparente;
	word pot_reativa;
	int32 aux_lx;
	signed byte os_cor;
	signed byte os_ten;
	signed byte os_pot;
	signed int32 soma_efi_p;
	signed int32 soma_efi_kvar;
	
	float aux_f1;
	float aux_f2;

	short sentido;

	#if (com_rep == true)
		modo_rep = 1;
	#endif
	
	#if (com_rep == true)
		if (modo_rep == 1){
			if (time_out_modo_rep != 0){
				if (atualizar == false){
					return;
				}
				atualizar = false;
				
				if (fase == 'R'){
					aux_l1 = pot_ativa_tot;
					aux_l2 = pot_reativa_tot;
					pot_aparente_tot = sqrt((aux_l1 * aux_l1) + ( aux_l2 * aux_l2));
					if (pot_ativa_tot > pot_aparente_tot){
						pot_ativa_tot = pot_aparente_tot;
					}
						
					sentido_r = 0;
					pot_aparente_r = (word)(pot_aparente_tot / 3);
					if (pot_ativa_r > pot_aparente_r){
						pot_ativa_r = pot_aparente_r;
					}
					
					if (tensao_r > TENSAO_FALTA){
						aux_l1 = pot_aparente_r;
						aux_l1 = aux_l1 * 512000;
						aux_l2 = tensao_r;

						if (valor_tp != 1){
							aux_l2 = aux_l2 * valor_tp;
						}
						aux_l1 = aux_l1 / aux_l2;
						corrente_r = (word)(aux_l1);
					}
					else{
						tensao_r = 0;
						corrente_r = 0;
					}
					aux_w1 = corrente_r / 8;
					if (aux_w1 > cor_minima_rep){
						status_banco_minimo = 0;
					}
			/* calculo do fator de potencia  */    
					if (pot_ativa_tot != pot_aparente_tot){
						aux_l1 = pot_ativa_tot;
						aux_l1 = (int32)(aux_l1 * 1024);
						fator_pot = (word)(aux_l1 / pot_aparente_tot);
						
						if (tarif_ind_rep == 1){
							fator_pot = fator_pot * (-1);
						}
					}
					else{
						fator_pot = 1024;
					}
					fator_pot_r = fator_pot;
					fator_pot_s = fator_pot_r;
					fator_pot_t = fator_pot_r;

					sentido_s = 0;
					pot_aparente_s = pot_aparente_r;
					if (tensao_s > TENSAO_FALTA){
						aux_l1 = pot_aparente_s;
						aux_l1 = aux_l1 * 512000;
						aux_l2 = tensao_s;
						if (valor_tp != 1){
							aux_l2 = aux_l2 * valor_tp;
						}
						aux_l1 = aux_l1 / aux_l2;
						corrente_s = (word)(aux_l1);
					}
					else{
						tensao_s = 0;
						corrente_s = 0;
					}
					sentido_t = 0;
					pot_aparente_t = pot_aparente_r;
					if (tensao_t > TENSAO_FALTA){
						aux_l1 = pot_aparente_t;
						aux_l1 = aux_l1 * 512000;
						aux_l2 = tensao_t;
						if (valor_tp != 1){
							aux_l2 = aux_l2 * valor_tp;
						}
						aux_l1 = aux_l1 / aux_l2;
						corrente_t = (word)(aux_l1);
					}
					else{
						tensao_t = 0;
						corrente_t = 0;
					}
				}

				#if (com_cht == true)
					for ( aux_b1 = 0; aux_b1 < NRO_CHT; aux_b1++){
						if (fase == 'R'){
							CHT_cr[aux_b1]=0;
						}
						else if (fase == 'S'){
							CHT_cs[aux_b1]=0;
						}
						else{
							CHT_ct[aux_b1]=0;
						}
					}
				#endif
				return;
			}
			else{
				corrente_r = 0;
				corrente_s = 0;
				corrente_t = 0;
				pot_ativa_tot = 0;
				pot_reativa_tot = 0;
				pot_aparente = 0;
				dem_ativa = 0;
				dem_reativa = 0;
				dem_ativa_proj = 0;
				dem_reativa_proj = 0;
				pot_ativa_r = 0;
				pot_ativa_s = 0;
				pot_ativa_t = 0;
				pot_reativa_r = 0;
				pot_reativa_s = 0;
				pot_reativa_t = 0;
				pot_aparente_r = 0;
				pot_aparente_s = 0;
				pot_aparente_r = 0;
				fator_pot = 1024;
				fator_pot_r = 1024;
				fator_pot_s = 1024;
				fator_pot_r = 1024;
				fator_carga = 1024;
				fator_demanda = 1024;
				seg_falt_rep = 0;
				puls_c1_rep = 0;
				puls_c2_rep = 0;
				return;
			}
		}
	#endif


	if (fase == 'R'){
		tensao = tensao_r;
		corrente = corrente_r;
		soma_efi_p = soma_efi_pr;
		soma_efi_kvar = soma_efi_kvar_r;
		os_cor = os_cor_r;
		os_ten = os_ten_r;
		os_pot = os_pot_r;
		indice_fp = 0;
	}
	else if (fase == 'S'){
		tensao = tensao_s;
		corrente = corrente_s;
		soma_efi_p = soma_efi_ps;
		soma_efi_kvar = soma_efi_kvar_s;
		os_cor = os_cor_s;
		os_ten = os_ten_s;
		os_pot = os_pot_s;
		indice_fp = 1;
	}
	else if (fase == 'T'){
		tensao = tensao_t;
		corrente = corrente_t;
		soma_efi_p = soma_efi_pt;
		soma_efi_kvar = soma_efi_kvar_t;
		os_cor = os_cor_t;
		os_ten = os_ten_t;
		os_pot = os_pot_t;
		indice_fp = 2;
	}
	else{
		return;
	}


	if (tensao > TENSAO_FALTA){	
		aux_w1 = 80;
		sentido = 0;
		if (corrente > aux_w1){
			status_banco_minimo = 0;
			if (make8(soma_efi_p, 3) != 0){
				sentido = 1;
				soma_efi_p = ~soma_efi_p;
				soma_efi_p = soma_efi_p & 0x00ffffff;
			}
			soma_efi_p_tmp = soma_efi_p;

			if (make8(soma_efi_kvar, 3) != 0 ){
				sinal_fp[indice_fp] = '-';
				soma_efi_kvar = ~soma_efi_kvar;
				soma_efi_kvar = soma_efi_kvar & 0x00ffffff;
			}
			else{
				sinal_fp[indice_fp] = '+';
			}
				
			#if (Magmattec == true)
				aux_l1 = (int32)(soma_efi_p / 32);
			#else
				aux_l1 = (int32)(soma_efi_p / 64);
			#endif

			aux_sw1 = 1024;
			if (fase == 'R'){
				if (corrente_r > 40){
					aux_sw1 -= 10;
				}
			}
			else if (fase == 'S'){
				if (corrente_s > 40){
					aux_sw1 -= 10;
				}
			}
			else{
				if (corrente_t > 40){
					aux_sw1 -= 10;
				}
			}
			aux_sw1 += os_pot;
			aux_sw1 += os_cor;
			aux_sw1 += os_ten;
			aux_l2 = (int32)(aux_l1 * aux_sw1);
			aux_l2 = (int32)(aux_l2 / 1024);
			pot_ativa = (word)(aux_l2);
			
			if (fase == 'R'){
				soma_pot_r += pot_ativa;
				pot_ativa = soma_pot_r >> 1;
				soma_pot_r -= pot_ativa;
			}
			else if (fase == 'S'){
				soma_pot_s += pot_ativa;
				pot_ativa = soma_pot_s >> 1;
				soma_pot_s -= pot_ativa;
			}
			else if (fase == 'T'){
				soma_pot_t += pot_ativa;
				pot_ativa = soma_pot_t >> 1;
				soma_pot_t -= pot_ativa;
			}

// calculo da potencia aparente 
	    	aux_l1 = tensao;
		    aux_l1 = aux_l1 * corrente;
		    aux_l1 = (int32)(aux_l1 / 16000);
		    data1_int = (word)(aux_l1);
    			
			pot_aparente = data1_int;		
		   	if (pot_ativa > pot_aparente){
			   	pot_ativa = pot_aparente;
			}

			if (fase == 'R'){
				if (sentido != sentido_r){
					if (time_out_tc_r >= 15){
						sentido_r = sentido;
					}
					else{
						time_out_tc_r++;
					}
				}
				else{
					time_out_tc_r = 0;
				}
				pot_ativa_r = pot_ativa;
				pot_aparente_r = pot_aparente;
			}
			else if (fase == 'S'){
				if (sentido != sentido_s){
					if (time_out_tc_s >= 15){
						sentido_s = sentido;
					}
					else{
						time_out_tc_s++;
					}
				}
				else{
					time_out_tc_s = 0;
				}
				pot_ativa_s = pot_ativa;
				pot_aparente_s = pot_aparente;
			}
			else if (fase == 'T'){
				if (sentido != sentido_t){
					if (time_out_tc_t >= 15){
						sentido_t = sentido;
					}
					else{
						time_out_tc_t++;
					}
				}
				else{
					time_out_tc_t = 0;
				}
				pot_ativa_t = pot_ativa;
				pot_aparente_t = pot_aparente;
			}
	
			if (pot_ativa != pot_aparente){
/* calculo da potencia reativa */    
/* Kvar = sqr(kva^2 - Kw^2) */	
				aux_f1 = (float)(pot_ativa);
				aux_f1 = (float)(aux_f1 * aux_f1);
				aux_f2 = (float)(pot_aparente);
				aux_f2 = (float)(aux_f2 * aux_f2);
				pot_reativa =(word)(sqrtx(aux_f2 - aux_f1));
		
/* calculo do fator de potencia  */    
				aux_l1 = pot_ativa;
				aux_l1 = (int32)(aux_l1 * 1024);
				aux_sw1 = (signed word)(aux_l1 / pot_aparente);

				if (sinal_fp[indice_fp] == '-'){
	    			aux_sw1 = aux_sw1 * (-1);
				}
				if (sinal_fp[indice_fp] == '1'){
					aux_sw1 = 1024;
				}
				if (aux_sw1 > 1024){
					aux_sw1 = 1024;
				}
				if ((aux_sw1 < 1024) && (aux_sw1 > 1020)){
					aux_sw1 = 1024;
				}
				if ((aux_sw1 == 1024) || (aux_sw1 == 0)){
			 	  	pot_ativa = pot_aparente;
					pot_reativa = 0;
				}

				if (fase == 'R'){
				   	fator_pot_r = aux_sw1;
					pot_reativa_r = pot_reativa;
				}
				else if (fase == 'S'){
				   	fator_pot_s = aux_sw1;
					pot_reativa_s = pot_reativa;
				}
				else if (fase == 'T'){
				   	fator_pot_t = aux_sw1;
					pot_reativa_t = pot_reativa;
				}
			}
			else{
				if (fase == 'R'){
				   	fator_pot_r = 1024;
					pot_reativa_r = 0;
					pot_req_r = 0;
					pot_exec_r = 0;
				}
				else if (fase == 'S'){
				   	fator_pot_s = 1024;
					pot_reativa_s = 0;
					pot_req_s = 0;
					pot_exec_s = 0;
				}
				else if (fase == 'T'){
				   	fator_pot_t = 1024;
					pot_reativa_t = 0;
					pot_req_t = 0;
					pot_exec_t = 0;
				}
			}
		}
		else{
			if (fase == 'R'){
				soma_pot_efi_r = 0;
				soma_pot_kvar_r = 0;
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
			else if (fase == 'S'){
				soma_pot_efi_s = 0;
				soma_pot_kvar_s = 0;
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
			else if (fase == 'T'){
				soma_pot_efi_t = 0;
				soma_pot_kvar_t = 0;
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
				for ( aux_b1 = 0; aux_b1 < (NRO_CHT + 1); aux_b1++){
					if (fase == 'R'){
						CHT_cr[aux_b1]=0;
					}
					else if (fase == 'S'){
						CHT_cs[aux_b1]=0;
					}
					else if (fase == 'T'){
						CHT_ct[aux_b1]=0;
					}
				}
			#endif
		}
	}
	else{
		if (fase == 'R'){
			soma_pot_efi_r = 0;
			soma_pot_kvar_r = 0;
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
		else if (fase == 'S'){
			soma_pot_efi_s = 0;
			soma_pot_kvar_s = 0;
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
		else if (fase == 'T'){
			soma_pot_efi_t = 0;
			soma_pot_kvar_t = 0;
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
			for ( aux_b1 = 0; aux_b1 < (NRO_CHT + 1); aux_b1++){
				if (fase == 'R'){
					CHT_tr[aux_b1]=0;
				 	CHT_cr[aux_b1]=0;
				}
				else if (fase == 'S'){
					CHT_ts[aux_b1]=0;
				 	CHT_cs[aux_b1]=0;
				}
				else{
					CHT_tt[aux_b1]=0;
			 		CHT_ct[aux_b1]=0;
				}
			}
		#endif
	}
}






