/************************************************************************
; Empresa: SULTECH SISTEMAS ELETRONICOS									*
; Modulo: st_CALC														*
; Funcao: MODULO ROTINAS DE CALCULOS									*
; Responsavel: VAGNER SANTOS											*
; Modificado ; VAGNER SANTOS											*
; Inicio: 30/08/2000													*
; Revisao: RENGAV ARIERREF SOD SOTNAS									*
;************************************************************************/

//void trata_modbus(void);
void calcula_vref_cr(void);
void calcula_vref_cs(void);
void calcula_vref_ct(void);

void calcula_vref(void){
	calculando_vref = true;
	if (nro_soma_vref >= NRO_MEDIAS_VREF)
		{
		aux_w1 = (word)(soma_vref / nro_soma_vref);
//		if ((aux_w1 > 1996) && (vref < 2096))
			{
			vref = aux_w1;
			}
		soma_vref = 0;
		nro_soma_vref = 0;
		}
	calculando_vref = false;
}


int32 calcula_soma_efi(int32 soma, char tipo){		//	Rotina para calcular o valor eficaz de num conjunto de valores lidos pelo AD
	float aux_f1;

	aux_f1 = (float)(soma / NRO_AMOSTRAS);
	aux_l1 = (int32)(sqrtx(aux_f1));
	if (tipo == 'C'){
		aux_l2 = valor_tc_fixo;
		#if (Magmattec == true)
			return((int32)((aux_l1 * aux_l2) / 32));	// Sensor Magmattec
		#else
			return((int32)((aux_l1 * aux_l2) / 64));
		#endif
	}
	else{
		return((int32)(aux_l1 * 32));	
	}
}


word calcula_eficaz(int32 soma_efi, signed word off_set, char tipo){
	aux_l1 = soma_efi >> nro_desloca;
	if (tipo == 'C'){
		aux_l2 = (signed word)(1024 + off_set);
	}
	else{
		aux_l2 = (signed word)(1024 + off_set);
	}
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
		aux_sl1 = (signed int32)(buf_tensao_r[aux_calc] - vref);
		soma_tr += (signed int32)(aux_sl1 * aux_sl1);
// fase S
		aux_sl1 = (signed int32)(buf_tensao_s[aux_calc]- vref);
		soma_ts += (signed int32)(aux_sl1 * aux_sl1);
// fase T
		aux_sl1 = (signed int32)(buf_tensao_t[aux_calc] - vref);
		soma_tt += (signed int32)(aux_sl1 * aux_sl1);
	}
}

void mul_buffers_ten_cor(void){
	if (modo_funca == 1){
		le_off_set_kvar();
		for (aux_calc = 0; aux_calc < NRO_AMOSTRAS; aux_calc++){
			#if (com_modbus == true)
				trata_modbus();
			#endif
			#if (home_system == true)
				trata_hsnet();
			#endif

// fase R
			aux_sl1 = (signed int32)(buf_tensao_r[aux_calc] - vref);
			if (aux_calc < (NRO_AMOSTRAS-1)){
				aux_sl3 = (signed int32)(buf_tensao_r[aux_calc+1] - vref);
			}
			else{
				aux_sl3 = (signed int32)(buf_tensao_r[0] - vref);
			}
			aux_sl4 = (signed int32)(buf_tensao_r[off_set_kvar] - vref);
			aux_sl2 = (signed int32)(buf_corrente_r[aux_calc] - vref_cr);
			
			aux_sl5 = aux_sl2;					// soma corrente de neutro

			soma_tr += (signed int32)(aux_sl1 * aux_sl1);
			soma_cr += (signed int32)(aux_sl2 * aux_sl2);
			if (cor_baixa_r == 0){
				aux_sl1 = (aux_sl1 + aux_sl3) / 2;
				soma_pr += (signed int32)(aux_sl1 * aux_sl2);
				soma_kvar_r += (signed int32)(aux_sl4 * aux_sl2);
			}
				
// fase S
			aux_sl1 = (signed int32)(buf_tensao_s[aux_calc]- vref);
			if (aux_calc < (NRO_AMOSTRAS-1)){
				aux_sl3 = (signed int32)(buf_tensao_s[aux_calc+1] - vref);
			}
			else{
				aux_sl3 = (signed int32)(buf_tensao_s[0] - vref);
			}
			aux_sl4 = (signed int32)(buf_tensao_s[off_set_kvar] - vref);
			aux_sl2 = (signed int32)(buf_corrente_s[aux_calc] - vref_cs);
			aux_sl5 += aux_sl2;					// soma corrente de neutro
			
			soma_ts += (signed int32)(aux_sl1 * aux_sl1);
			soma_cs += (signed int32)(aux_sl2 * aux_sl2);
			if (cor_baixa_s == 0){
				aux_sl1 = (aux_sl1 + aux_sl3) / 2;
				soma_ps += (signed int32)(aux_sl1 * aux_sl2);
				soma_kvar_s += (signed int32)(aux_sl4 * aux_sl2);
			}
// fase T
			aux_sl1 = (signed int32)(buf_tensao_t[aux_calc] - vref);
			if (aux_calc < (NRO_AMOSTRAS-1)){
				aux_sl3 = (signed int32)(buf_tensao_t[aux_calc+1] - vref);
			}
			else{
				aux_sl3 = (signed int32)(buf_tensao_t[0] - vref);
			}
			aux_sl4 = (signed int32)(buf_tensao_t[off_set_kvar] - vref);
			aux_sl2 = (signed int32)(buf_corrente_t[aux_calc]- vref_ct);
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
			aux_sl1 = (signed int32)(buf_tensao_r[aux_calc] - vref);
			soma_tr += (signed int32)(aux_sl1 * aux_sl1);
	// fase S
			aux_sl1 = (signed int32)(buf_tensao_s[aux_calc]- vref);
			soma_ts += (signed int32)(aux_sl1 * aux_sl1);
	// fase T
			aux_sl1 = (signed int32)(buf_tensao_t[aux_calc] - vref);
			soma_tt += (signed int32)(aux_sl1 * aux_sl1);
		}
	}
}

void mul_buffers(void){
	modo_funca = 1;
	#if (com_rep == true)
		mul_buffers_ten();
	#endif
	#if (com_tc == true)
		mul_buffers_ten_cor();
	#endif
}

void finaliza_calculo_tensao_corrente(void){
	#if (st8500c == true)
		if (conta_media_ten == nro_media_amostras){
 			if (tensao_r < TENSAO_FALTA){
				tensao_r = 0;
				tensao_rs = 0;
			}
		 	if (tensao_s < TENSAO_FALTA){
				tensao_s = 0;
				tensao_st = 0;
			}
		 	if (tensao_t < TENSAO_FALTA){
	 			tensao_t = 0;
				tensao_rt = 0;
			}

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
						
				if (corrente_r > 40){
					corrente_r -= 40;
				}
				if (corrente_s > 40){
					corrente_s -= 40;
				}
				if (corrente_t > 40){
					corrente_t -= 40;
				}
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
			#if (monofasico == false)
				soma_pot_efi_s = 0;
				soma_pot_efi_t = 0;
				soma_pot_kvar_s = 0;
				soma_pot_kvar_t = 0;
			#endif
	
			soma_efi_tr = 0;
			#if (monofasico == false)
				soma_efi_tt = 0;
				soma_efi_ts = 0;
			#endif
			
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
	#endif
}

void calcula_tensao_corrente(void)
{

	conta_media++;
	morder_calc = 1;
	
	cor_baixa_r = 0;
	#if (monofasico == false)
		cor_baixa_s = 0;
		cor_baixa_t = 0;
	#endif

	#if (tc_fixo == true)
		#if (portatil == true)
			#if (se_com_flex == true)
				#if (versao_pci_st96 == 6)
//					aux_w1 = 500;	//tabela_pt[tipo_ponteira];
//					aux_w1 = ((aux_w1 * 24) / 200);
					aux_w1 = 1;			//
				#elif (versao_pci_st96 == 4)
					aux_w1 = 200;						//5%
				#else
					if (tabela_pt[tipo_ponteira] == 200)
						{
						aux_w1 = 48;
						}
					else
						{
						aux_w1 = 120;
						}
				#endif
			#endif
		#else
			aux_w1 = 80;
		#endif
	#else	
		if (valor_tc < 61)
			{
			aux_w1 = 8;
			}
		else if (valor_tc < 201)
			{
			aux_w1 = 40;
			}
		else
			{
			aux_w1 = 80;
			}
	#endif
	if (corrente_r < aux_w1) // 3%
		{
		cor_baixa_r = 1;
		#if ((st5000t == 1) | (st5030t == 1))
			fled_tc_r = 1;
		#endif
		sinal_fp[0] = '1';
		soma_pr = 0;
		soma_kvar_r = 0;
		}
	#if (monofasico == false)
		if (corrente_s < aux_w1) // 3%
			{
			cor_baixa_s = 1;
			#if (st5x == true)
				fled_tc_s = 1;
			#endif
			sinal_fp[1] = '1';
			soma_ps = 0;
			soma_kvar_s = 0;
			}
		if (corrente_t < aux_w1) // 3%
			{
			cor_baixa_t = 1;
			#if (st5x == true)
				fled_tc_t = 1;
			#endif
			sinal_fp[2] = '1';
			soma_pt = 0;
			soma_kvar_t = 0;
			}
	#endif

	soma_tr = 0;
	soma_cr = 0;
	soma_pr = 0;
	soma_kvar_r = 0;
	#if (monofasico == false)
		soma_ts = 0;
		soma_cs = 0;
		soma_ps = 0;
		soma_tt = 0;
		soma_ct = 0;
		soma_pt = 0;
		soma_kvar_s = 0;
		soma_kvar_t = 0;
		soma_cn = 0;
	#endif

	mul_buffers();				// multiplica pontos dos buffers de senoide
	
	#if (st8500c == true)
	// tensao r
		soma_efi_tr += calcula_soma_efi(soma_tr, 'T');
	// tensao s
		soma_efi_ts += calcula_soma_efi(soma_ts, 'T');
	// tensao t
		soma_efi_tt += calcula_soma_efi(soma_tt, 'T');
		
		#if (com_tc == true)
			soma_efi_cr += calcula_soma_efi(soma_cr, 'C');
			soma_efi_cs += calcula_soma_efi(soma_cs, 'C');
			soma_efi_ct += calcula_soma_efi(soma_ct, 'C');
			soma_pot_efi_r += (signed int32)((soma_pr / NRO_AMOSTRAS));
			soma_pot_efi_s += (signed int32)((soma_ps / NRO_AMOSTRAS));
			soma_pot_efi_t += (signed int32)((soma_pt / NRO_AMOSTRAS));
			soma_pot_kvar_r += (signed int32)((soma_kvar_r / NRO_AMOSTRAS));
			soma_pot_kvar_s += (signed int32)((soma_kvar_s / NRO_AMOSTRAS));
			soma_pot_kvar_t += (signed int32)((soma_kvar_t / NRO_AMOSTRAS));
		#endif

		conta_media_ten++;
		finaliza_calculo_tensao_corrente();
		med_ten_ok = 0;

	#else
	// tensao r
		soma_efi_tr += calcula_soma_efi(soma_tr, 'T');
			
		#if (monofasico == false)
	// tensao s
			soma_efi_ts += calcula_soma_efi(soma_ts, 'T');
	// tensao t
			soma_efi_tt += calcula_soma_efi(soma_tt, 'T');
		#endif
		
		if (modo_funca == 1)
			{
			/* calculo da corrente */
			#if ((st92 == true) || (st94 == true))
				if(soma_cr < COR_CRITICA_SOMA){
					soma_cr = 0;
				}
				if(soma_cs < COR_CRITICA_SOMA){
					soma_cs = 0;
				}
				if(soma_ct < COR_CRITICA_SOMA){
					soma_ct = 0;
				}
			#endif
			
			soma_efi_cr += calcula_soma_efi(soma_cr, 'C');
			#if (monofasico == false)
				soma_efi_cs += calcula_soma_efi(soma_cs, 'C');
				soma_efi_ct += calcula_soma_efi(soma_ct, 'C');
				soma_efi_cn += calcula_soma_efi(soma_cn, 'C');
			#endif
			
			soma_pot_efi_r += (signed int32)((soma_pr / NRO_AMOSTRAS));
			#if (st9230r == true)
				#if (epcos == true)
					aux_f1 = soma_pr;
					soma_pot_efi_r_epcos += (float)((aux_f1 / NRO_AMOSTRAS));
					aux_f1 = soma_kvar_r;
					soma_pot_kvar_r_epcos += (signed int32)((aux_f1 / NRO_AMOSTRAS));
					
				#endif
			#endif
			soma_pot_kvar_r += (signed int32)((soma_kvar_r / NRO_AMOSTRAS));
			#if (monofasico == false)
				soma_pot_efi_s += (signed int32)((soma_ps / NRO_AMOSTRAS));
				soma_pot_efi_t += (signed int32)((soma_pt / NRO_AMOSTRAS));
				soma_pot_kvar_s += (signed int32)((soma_kvar_s / NRO_AMOSTRAS));
				soma_pot_kvar_t += (signed int32)((soma_kvar_t / NRO_AMOSTRAS));
			#endif
			}	
		conta_media_ten++;
		finaliza_calculo_tensao_corrente();
		med_ten_ok = 0;
	#endif
	
}

