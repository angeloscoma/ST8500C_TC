//***********************************************************************
// Empresa: Sultech Sistemas Eletrônicos								*
// Módulo: ST_CALC														*
// Função: Calcular valores de tensão e corrente.						*
// Responsável: Edison Valério Nunes Junior								*
// Modificado: Edison Valério Nunes Junior								*
// Inicio: 01/08/2003													*
// Revisão: Edison Valério Nunes Junior									*
//***********************************************************************

void calcula_vref(void){
	int x;
	soma_vreft = 0;
	soma_vrefc = 0;
	for(x = 0; x < NRO_AMOSTRAS; x++){
		soma_vreft += buf_tensao_r[x];
		soma_vrefc += buf_corrente_r[x];
	}
	vreftr = (soma_vreft / NRO_AMOSTRAS);
	vrefcr = (soma_vrefc / NRO_AMOSTRAS);

	soma_vreft = 0;
	soma_vrefc = 0;
	for(x = 0; x < NRO_AMOSTRAS; x++){
		soma_vreft += buf_tensao_s[x];
		soma_vrefc += buf_corrente_s[x];
	}
	vrefts = (soma_vreft / NRO_AMOSTRAS);
	vrefcs = (soma_vrefc / NRO_AMOSTRAS);

	soma_vreft = 0;
	soma_vrefc = 0;
	for(x = 0; x < NRO_AMOSTRAS; x++){
		soma_vreft += buf_tensao_t[x];
		soma_vrefc += buf_corrente_t[x];
	}
	vreftt = (soma_vreft / NRO_AMOSTRAS);
	vrefct = (soma_vrefc / NRO_AMOSTRAS);
}

int32 calcula_soma_efi(int32 soma, char tipo){
	float aux_f1;

	aux_f1 = (float)(soma / NRO_AMOSTRAS);
	aux_l1 = (int32)(sqrtx(aux_f1));
	if (tipo == 'C'){
		aux_l2 = valor_tc_fixo;
		return((int32)((aux_l1 * aux_l2) / 32)/5);	// Sensor Magmattec
	}
	else{
		return((int32)((aux_l1 * 32)/2));	
	}
}

word calcula_eficaz(int32 soma_efi, signed word off_set, char tipo){
	aux_l1 = soma_efi >> nro_desloca;
	aux_l2 = (signed word)(1024 + off_set);
	aux_l2 = (int32)(aux_l2 * aux_l1);
	return(word)(aux_l2 / 1024);
}

void le_off_set_kvar(void){
	if (tipo_ligacao == 2){
		off_set_kvar = NRO_AMOSTRAS - off_cor_delta + (NRO_AMOSTRAS / 4);
	}
	else{
		off_set_kvar = off_cor_r + (NRO_AMOSTRAS / 4);
	}
}

void mul_buffers_ten(void){
	for (aux_calc = 0; aux_calc < NRO_AMOSTRAS; aux_calc++){
		#if (com_modbus == true)
			trata_modbus();
		#endif
		#if (home_system == true)
			trata_hsnet();
		#endif
	// fase R
		aux_sl1 = (signed int32)(buf_tensao_r[aux_calc] - 2048);
		soma_tr += (signed int32)(aux_sl1 * aux_sl1);
	// fase S
		aux_sl1 = (signed int32)(buf_tensao_s[aux_calc] - 2048);
		soma_ts += (signed int32)(aux_sl1 * aux_sl1);
	// fase T
		aux_sl1 = (signed int32)(buf_tensao_t[aux_calc] - 2048);
		soma_tt += (signed int32)(aux_sl1 * aux_sl1);
	}
}

void mul_buffers_ten_cor(void){
	//calcula_vref();
	if (modo_funca == 1){
		le_off_set_kvar();
		vreftr = 2048;
		vrefcr = 2048;
		for (aux_calc = 0; aux_calc < NRO_AMOSTRAS; aux_calc++){
			#if (com_modbus == true)
				trata_modbus();
			#endif
			#if (home_system == true)
				trata_hsnet();
			#endif

// fase R
			aux_sl1 = (signed int32)(buf_tensao_r[aux_calc] - 2048);
			if (aux_calc < (NRO_AMOSTRAS-1)){
				aux_sl3 = (signed int32)(buf_tensao_r[aux_calc+1] - vreftr);
			}
			else{
				aux_sl3 = (signed int32)(buf_tensao_r[0] - 2048);
			}
			aux_sl4 = (signed int32)(buf_tensao_r[off_set_kvar] - 2048);
			aux_sl2 = (signed int32)(buf_corrente_r[aux_calc] - 2048);
			aux_sl5 = aux_sl2;					// soma corrente de neutro

			soma_tr += (signed int32)(aux_sl1 * aux_sl1);
			soma_cr += (signed int32)(aux_sl2 * aux_sl2);
			if (cor_baixa_r == 0){
				aux_sl1 = (aux_sl1 + aux_sl3) / 2;
				soma_pr += (signed int32)(aux_sl1 * aux_sl2);
				soma_kvar_r += (signed int32)(aux_sl4 * aux_sl2);
			}
					
// fase S
			aux_sl1 = (signed int32)(buf_tensao_s[aux_calc]- 2048);
			if (aux_calc < (NRO_AMOSTRAS-1)){
				aux_sl3 = (signed int32)(buf_tensao_s[aux_calc+1] - 2048);
			}
			else{
				aux_sl3 = (signed int32)(buf_tensao_s[0] - 2048);
			}
			aux_sl4 = (signed int32)(buf_tensao_s[off_set_kvar] - 2048);
			aux_sl2 = (signed int32)(buf_corrente_s[aux_calc] - 2048);
			aux_sl5 += aux_sl2;					// soma corrente de neutro
			
			soma_ts += (signed int32)(aux_sl1 * aux_sl1);
			soma_cs += (signed int32)(aux_sl2 * aux_sl2);
			if (cor_baixa_s == 0){
				aux_sl1 = (aux_sl1 + aux_sl3) / 2;
				soma_ps += (signed int32)(aux_sl1 * aux_sl2);
				soma_kvar_s += (signed int32)(aux_sl4 * aux_sl2);
			}
// fase T
			aux_sl1 = (signed int32)(buf_tensao_t[aux_calc] - 2048);
			if (aux_calc < (NRO_AMOSTRAS-1)){
				aux_sl3 = (signed int32)(buf_tensao_t[aux_calc+1] - 2048);
			}
			else{
				aux_sl3 = (signed int32)(buf_tensao_t[0] - 2048);
			}
			aux_sl4 = (signed int32)(buf_tensao_t[off_set_kvar] - 2048);
			aux_sl2 = (signed int32)(buf_corrente_t[aux_calc]- 2048);
			aux_sl5 += aux_sl2;					// soma corrente de neutro
			
			soma_tt += (signed int32)(aux_sl1 * aux_sl1);
			soma_ct += (signed int32)(aux_sl2 * aux_sl2);
			if (cor_baixa_t == 0){
				aux_sl1 = (aux_sl1 + aux_sl3) / 2;
				soma_pt += (signed int32)(aux_sl1 * aux_sl2);
				soma_kvar_t += (signed int32)(aux_sl4 * aux_sl2);
			}

			soma_cn += (signed int32)(aux_sl5 * aux_sl5);

			off_set_kvar++;
			if (off_set_kvar >= NRO_AMOSTRAS){
				off_set_kvar = 0;
			}
		}
	}
	else{
		for (aux_calc = 0; aux_calc < NRO_AMOSTRAS; aux_calc++){
			#if com_modbus
				trata_modbus();
			#endif
			#if (home_system == true)
				trata_hsnet();
			#endif
// fase R
			aux_sl1 = (signed int32)(buf_tensao_r[aux_calc] - 2048);
			soma_tr += (signed int32)(aux_sl1 * aux_sl1);
// fase S
			aux_sl1 = (signed int32)(buf_tensao_s[aux_calc] - 2048);
			soma_ts += (signed int32)(aux_sl1 * aux_sl1);
// fase T
			aux_sl1 = (signed int32)(buf_tensao_t[aux_calc] - 2048);
			soma_tt += (signed int32)(aux_sl1 * aux_sl1);
		}
	}
}


void finaliza_calculo_tensao_corrente(void){
	#if (st8500c == true)
		if (conta_media_ten == nro_media_amostras){
			tensao_r = calcula_eficaz(soma_efi_tr, os_ten_r, 'T');
			tensao_s = calcula_eficaz(soma_efi_ts, os_ten_s, 'T');
			tensao_t = calcula_eficaz(soma_efi_tt, os_ten_t, 'T');

			soma_ten_r += tensao_r;
			tensao_r = soma_ten_r >> 1;
			soma_ten_r -= tensao_r;
		
			soma_ten_s += tensao_s;
			tensao_s = soma_ten_s >> 1;
			soma_ten_s -= tensao_s;
		
			soma_ten_t += tensao_t;
			tensao_t = soma_ten_t >> 1;
			soma_ten_t -= tensao_t;
	
		
			calc_ten_ok = 1;

			soma_efi_tr = 0;
			soma_efi_ts = 0;
			soma_efi_tt = 0;
			
			#if (com_tc == true)
				corrente_r = calcula_eficaz(soma_efi_cr, os_cor_r, 'C');
				corrente_s = calcula_eficaz(soma_efi_cs, os_cor_s, 'C');
				corrente_t = calcula_eficaz(soma_efi_ct, os_cor_t, 'C');
						
				soma_cor_r += corrente_r;
				corrente_r = soma_cor_r >> 1;
				soma_cor_r -= corrente_r;
			
				soma_cor_s += corrente_s;
				corrente_s = soma_cor_s >> 1;
				soma_cor_s -= corrente_s;
			
				soma_cor_t += corrente_t;
				corrente_t = soma_cor_t >> 1;
				soma_cor_t -= corrente_t;
			
				aux_sl1 = (signed int32)(soma_pot_efi_r >> nro_desloca);
				soma_efi_pr = (signed int32)(aux_sl1); 
						
				aux_sl1 = (signed int32)(soma_pot_kvar_r >> nro_desloca);
				soma_efi_kvar_r = (signed int32)(aux_sl1);
			
				aux_sl1 = (signed int32)(soma_pot_efi_s >> nro_desloca);
				soma_efi_ps = (signed int32)(aux_sl1); 
				aux_sl1 = (signed int32)(soma_pot_kvar_s >> nro_desloca);
				soma_efi_kvar_s = (signed int32)(aux_sl1);
						
				aux_sl1 = (signed int32)(soma_pot_efi_t >> nro_desloca);
				soma_efi_pt = (signed int32)(aux_sl1); 
			
				aux_sl1 = (signed int32)(soma_pot_kvar_t >> nro_desloca);
				soma_efi_kvar_t = (signed int32)(aux_sl1);
				
				soma_efi_cr = 0;
				soma_efi_cs = 0;
				soma_efi_ct = 0;
				soma_pot_efi_r = 0;
				soma_pot_efi_s = 0;
				soma_pot_efi_t = 0;
				soma_pot_kvar_r = 0;
				soma_pot_kvar_s = 0;
				soma_pot_kvar_t = 0;
			
//				fprintf(modbus,"NA calc1:");
//				fprintf(modbus,"T:%lu , C:%lu \r\n", tensao_r, corrente_r);

			#endif
			conta_media_ten = 0;
		}
	#else
		if (conta_media_ten == nro_media_amostras){
			tensao_r = calcula_eficaz(soma_efi_tr, os_ten_r, 'T');
			if (tensao_r < TENSAO_FALTA){
				tensao_r = 0;
			}
			tensao_s = calcula_eficaz(soma_efi_ts, os_ten_s, 'T');
			if (tensao_s < TENSAO_FALTA){
				tensao_s = 0;
			}
			tensao_t = calcula_eficaz(soma_efi_tt, os_ten_t, 'T');
			if (tensao_t < TENSAO_FALTA){
				tensao_t = 0;
			}
	
			soma_ten_r += tensao_r;
			tensao_r = soma_ten_r >> 1;
			soma_ten_r -= tensao_r;
	
			soma_ten_s += tensao_s;
			tensao_s = soma_ten_s >> 1;
			soma_ten_s -= tensao_s;

			soma_ten_t += tensao_t;
			tensao_t = soma_ten_t >> 1;
			soma_ten_t -= tensao_t;
		
			if (modo_funca == 1){
				corrente_r = calcula_eficaz(soma_efi_cr, os_cor_r, 'C');
				corrente_s = calcula_eficaz(soma_efi_cs, os_cor_s, 'C');
				corrente_t = calcula_eficaz(soma_efi_ct, os_cor_t, 'C');
				corrente_n = calcula_eficaz(soma_efi_cn, (os_cor_r + os_cor_s + os_cor_t), 'C');
				
				soma_cor_r += corrente_r;
				corrente_r = soma_cor_r >> 1;
				soma_cor_r -= corrente_r;
	
				soma_cor_s += corrente_s;
				corrente_s = soma_cor_s >> 1;
				soma_cor_s -= corrente_s;

				soma_cor_t += corrente_t;
				corrente_t = soma_cor_t >> 1;
				soma_cor_t -= corrente_t;
	
				aux_sl1 = (signed int32)(soma_pot_efi_r >> nro_desloca);
				soma_efi_pr = (signed int32)(aux_sl1); 
				aux_sl1 = (signed int32)(soma_pot_kvar_r >> nro_desloca);
				soma_efi_kvar_r = (signed int32)(aux_sl1);
		
				aux_sl1 = (signed int32)(soma_pot_efi_s >> nro_desloca);
				soma_efi_ps = (signed int32)(aux_sl1); 
				aux_sl1 = (signed int32)(soma_pot_kvar_s >> nro_desloca);
				soma_efi_kvar_s = (signed int32)(aux_sl1);
			
				aux_sl1 = (signed int32)(soma_pot_efi_t >> nro_desloca);
				soma_efi_pt = (signed int32)(aux_sl1); 
				aux_sl1 = (signed int32)(soma_pot_kvar_t >> nro_desloca);
				soma_efi_kvar_t = (signed int32)(aux_sl1);
			}
			else{
				corrente_r = 0;
				corrente_s = 0;
				corrente_t = 0;
			}
	
			calc_ten_ok = 1;
	
			soma_efi_cr = 0;
			soma_efi_cs = 0;
			soma_efi_ct = 0;
			soma_efi_cn = 0;
	
			soma_pot_efi_r = 0;
				
			soma_pot_kvar_r = 0;
			soma_pot_efi_s = 0;
			soma_pot_efi_t = 0;
			soma_pot_kvar_s = 0;
			soma_pot_kvar_t = 0;
	
			soma_efi_tr = 0;
			soma_efi_tt = 0;
			soma_efi_ts = 0;
			
			conta_media_ten = 0;
		}
	#endif
}

void calcula_tensao_corrente(void){
//	conta_media++;
	morder_calc = 1;
	
	cor_baixa_r = 0;
	cor_baixa_s = 0;
	cor_baixa_t = 0;

	aux_w1 = 80;		// TC de 500: 2% = 15A com a quantização de corrente (2^3 = 8) temos o valor 80.

	if (corrente_r < aux_w1){
		cor_baixa_r = 1;
		sinal_fp[0] = '1';
		soma_pr = 0;
		soma_kvar_r = 0;
	}
	if (corrente_s < aux_w1){
		cor_baixa_s = 1;
		sinal_fp[1] = '1';
		soma_ps = 0;
		soma_kvar_s = 0;
	}
	if (corrente_t < aux_w1){
		cor_baixa_t = 1;
		sinal_fp[2] = '1';
		soma_pt = 0;
		soma_kvar_t = 0;
	}

	soma_tr = 0;
	soma_cr = 0;
	soma_pr = 0;
	soma_kvar_r = 0;
	soma_ts = 0;
	soma_cs = 0;
	soma_ps = 0;
	soma_kvar_s = 0;
	soma_tt = 0;
	soma_ct = 0;
	soma_pt = 0;
	soma_kvar_t = 0;
	soma_cn = 0;

	mul_buffers_ten_cor();				// multiplica pontos dos buffers de senoide
	
	soma_efi_tr += calcula_soma_efi(soma_tr, 'T');
	soma_efi_ts += calcula_soma_efi(soma_ts, 'T');
	soma_efi_tt += calcula_soma_efi(soma_tt, 'T');
		
	if (modo_funca == 1){
		soma_efi_cr += calcula_soma_efi(soma_cr, 'C');
		soma_efi_cs += calcula_soma_efi(soma_cs, 'C');
		soma_efi_ct += calcula_soma_efi(soma_ct, 'C');
		soma_efi_cn += calcula_soma_efi(soma_cn, 'C');
		
		soma_pot_efi_r += (signed int32)(soma_pr /10 / NRO_AMOSTRAS);
		soma_pot_efi_s += (signed int32)(soma_ps /10 / NRO_AMOSTRAS);
		soma_pot_efi_t += (signed int32)(soma_pt /10 / NRO_AMOSTRAS);
		soma_pot_kvar_r += (signed int32)(soma_kvar_r /10 / NRO_AMOSTRAS);
		soma_pot_kvar_s += (signed int32)(soma_kvar_s /10 / NRO_AMOSTRAS);
		soma_pot_kvar_t += (signed int32)(soma_kvar_t /10 / NRO_AMOSTRAS);
	}	
	conta_media_ten++;
	finaliza_calculo_tensao_corrente();
	med_ten_ok = 0;
}

