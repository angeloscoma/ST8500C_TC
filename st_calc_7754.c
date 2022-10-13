/*
;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: st_CALC                                                        *
; Funcao: MODULO ROTINAS DE CALCULOS   									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */

void le_sinal_fp(char);

void trata_modbus(void);



void calcula_vref(void)
{
	vref = 0;
}


int32 calcula_soma_efi(int32 soma, char tipo)
{
/*
	Rotina para calcular o valoro eficaz de num conjunto de valores lidos pelo AD
*/
	
	if (tipo == 'C')
		{
		return((int32)(soma * 1));	
		}
	else
		{
		return((int32)(soma * 8));	
		}
}


word calcula_eficaz(int32 soma_efi, signed word off_set, char tipo)
{
	aux_l1 = soma_efi >> nro_desloca;
	aux_l2 = (signed word)(1000 + off_set);
	aux_l2 = aux_l2 * aux_l1;
	return(aux_l2 / 1000);
}






void finaliza_calculo_tensao_corrente(void)
{
	if (conta_media_ten_r == nro_media_amostras)
		{
		tensao_r = calcula_eficaz(soma_efi_tr, os_ten_r, 'T');
		if (modo_funca == 1)
			{
			le_sinal_fp('R');
			corrente_r = calcula_eficaz(soma_efi_cr, os_cor_r, 'C');
			aux_sl1 = (signed int32)(soma_pot_efi_r >> nro_desloca);
			soma_efi_pr = (signed int32)(aux_sl1); 
			}
		else
			{
			corrente_r = 0;
			soma_efi_pr = 0; 
			}
		soma_efi_cr = 0;
		soma_pot_efi_r = 0;
		soma_efi_tr = 0;
		conta_media_ten_r = 0;
		}

	if (conta_media_ten_s == nro_media_amostras)
		{
		tensao_s = calcula_eficaz(soma_efi_ts, os_ten_s, 'T');
		if (modo_funca == 1)
			{
			le_sinal_fp('S');
			corrente_s = calcula_eficaz(soma_efi_cs, os_cor_s, 'C');
			aux_sl1 = (signed int32)(soma_pot_efi_s >> nro_desloca);
			soma_efi_ps = (signed int32)(aux_sl1); 
			}
		else
			{
			corrente_s = 0;
			soma_efi_ps = 0; 
			}
		soma_efi_cs = 0;
		soma_pot_efi_s = 0;
		soma_efi_ts = 0;
		conta_media_ten_s = 0;
		}
	if (conta_media_ten_t == nro_media_amostras)
		{
		tensao_t = calcula_eficaz(soma_efi_tt, os_ten_t, 'T');
		if (modo_funca == 1)
			{
			le_sinal_fp('T');
			corrente_t = calcula_eficaz(soma_efi_ct, os_cor_t, 'C');
			aux_sl1 = (signed int32)(soma_pot_efi_t >> nro_desloca);
			soma_efi_pt = (signed int32)(aux_sl1); 
			}
		else
			{
			corrente_t = 0;
			soma_efi_pt = 0; 
			}
		soma_efi_ct = 0;
		soma_pot_efi_t = 0;
		soma_efi_tt = 0;
		conta_media_ten_t = 0;
		}
	calc_ten_ok = 1;
}

void calcula_tensao_corrente(void)
{


	if (bit_test(status_ade7754, 4) && bit_test(status_ade7754, 5) && bit_test(status_ade7754, 6) ) 
		{
		tensao_a_rms = 0;
		tensao_b_rms = 0;
		tensao_c_rms = 0;
		corrente_a_rms = 0;
		corrente_b_rms = 0;
		corrente_c_rms = 0;
		return;
		}
	else
		{
		if (bit_test(status_ade7754, 4)) 
			{
			tensao_a_rms = 0;
			corrente_a_rms = 0;
			}
		if (bit_test(status_ade7754, 5)) 
			{
			tensao_b_rms = 0;
			corrente_b_rms = 0;
			}
		if (bit_test(status_ade7754, 6)) 
			{
			tensao_c_rms = 0;
			corrente_c_rms = 0;
			}
		}



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



// tensao r
	if (med_ten_ok_r == 1)
		{
		cor_baixa_r = 0;
		if (corrente_r < aux_w1) // 3%
			{
			cor_baixa_r = 1;
#if ((st5000t == 1) || (st5030t == 1))
			output_high(led_tc_r);
#endif
			sinal_fp[0] = '1';
			}
		soma_efi_tr += calcula_soma_efi(tensao_a_rms, 'T');
		if (modo_funca == 1)
			{
			soma_efi_cr += calcula_soma_efi(corrente_a_rms, 'C');
			soma_pot_efi_r += (signed int32)(RAENERGY_R);
			}
		conta_media_ten_r++;
		finaliza_calculo_tensao_corrente();
		med_ten_ok_r = 0;
		}
// tensao s
	if (med_ten_ok_s == 1)
		{
		cor_baixa_s = 0;
		if (corrente_s < aux_w1) // 3%
			{
			cor_baixa_s = 1;
#if ((st5000t == 1) || (st5030t == 1))
		output_high(led_tc_s);
#endif
			sinal_fp[1] = '1';
			}

		soma_efi_ts += calcula_soma_efi(tensao_b_rms, 'T');
		if (modo_funca == 1)
			{
			soma_efi_cs += calcula_soma_efi(corrente_b_rms, 'C');
			soma_pot_efi_s += (signed int32)(RAENERGY_S);
			}
		conta_media_ten_s++;
		finaliza_calculo_tensao_corrente();
		med_ten_ok_s = 0;
		}
// tensao t
	if (med_ten_ok_t == 1)
		{
		cor_baixa_t = 0;
		if (corrente_t < aux_w1) // 3%
			{
			cor_baixa_t = 1;
#if ((st5000t == 1) || (st5030t == 1))
			output_high(led_tc_t);
#endif
			sinal_fp[2] = '1';
			}

		soma_efi_tt += calcula_soma_efi(tensao_c_rms, 'T');
		if (modo_funca == 1)
			{
			soma_efi_ct += calcula_soma_efi(corrente_c_rms, 'C');
			soma_pot_efi_t += (signed int32)(RAENERGY_T);
			}
		conta_media_ten_t++;
		finaliza_calculo_tensao_corrente();
		med_ten_ok_t = 0;
		}



	med_ten_ok = 0;
	
}

