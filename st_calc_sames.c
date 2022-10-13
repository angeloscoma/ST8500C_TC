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
void filtra_corrente_r(void);




void calcula_vref(void)
{
}

void calcula_frequencia(void)
{
}


word calcula_teficaz(int32 soma_efi, signed word off_set)
{
	aux_l1 = soma_efi >> 4;
	aux_l1 = aux_l1 * 600 * 64;
	aux_l1 = aux_l1 / 730;
	aux_l2 = (signed word)(1000 + off_set);
	aux_l2 = (int32)(aux_l2 * aux_l1);
	return(aux_l2 / 1000);
}




#define cristal_sames_128	27965		//  cristal de 3.5795MHZ / 128

void calcula_tensao_corrente(void)
{

	int32 aux_l4;
		
	cor_baixa_r = 0;
	#if (monofasico == false)
		cor_baixa_s = 0;
		cor_baixa_t = 0;
	#endif

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
	if (corrente_r < aux_w1) // 3%
		{
		cor_baixa_r = 1;
		#if ((st5000t == 1) | (st5030t == 1))
			fled_tc_r = 1;
		#endif
		sinal_fp[0] = '1';
		soma_pr = 0;
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
			}
		if (corrente_t < aux_w1) // 3%
			{
			cor_baixa_t = 1;
			#if (st5x == true)
				fled_tc_t = 1;
			#endif
			sinal_fp[2] = '1';
			soma_pt = 0;
			}
	#endif

	// Tensao_r
	tensao_r = calcula_teficaz(soma_efi_tr, os_ten_r);
	aux_l1 = (int32)(soma_kw_r);
	aux_l2 = (int32)(soma_kvar_r);
	aux_l3 = (int32)(aux_l1 * aux_l1);
	aux_l4 = (int32)(aux_l2 * aux_l2);
	KVA_R_SAMES =(word)(sqrtx(aux_l3 + aux_l4));
	aux_l3 = (int32)(aux_l1 * 1024);
	fator_pot_r = (signed int16)(aux_l3/KVA_R_SAMES);
	corrente_r = (int16)(((int32)(KVA_R_SAMES * 16000)) / tensao_r);
	pot_ativa_r = soma_kw_r;
	pot_aparente_r = KVAR_R_SAMES;
	pot_reativa_r = soma_kvar_r;
	

	
	#if (monofasico == false)
		// tensao s
		tensao_s = calcula_teficaz(soma_efi_ts, os_ten_s);
		aux_l1 = (int32)(soma_kw_s);
		aux_l2 = (int32)(soma_kvar_s);
		aux_l3 = (int32)(aux_l1 * aux_l1);
		aux_l4 = (int32)(aux_l2 * aux_l2);
		KVA_S_SAMES =(word)(sqrtx(aux_l3 + aux_l4));
		aux_l3 = (int32)(aux_l1 * 1024);
		fator_pot_s = (signed int16)(aux_l3/KVA_S_SAMES);
		corrente_s = (int16)(((int32)(KVA_S_SAMES * 16000)) / tensao_s);
		pot_ativa_s = soma_kw_s;
		pot_aparente_s = KVAR_S_SAMES;
		pot_reativa_s = soma_kvar_s;

		// tensao t
		tensao_t = calcula_teficaz(soma_efi_tt, os_ten_t);
		aux_l1 = (int32)(soma_kw_t);
		aux_l2 = (int32)(soma_kvar_t);
		aux_l3 = (int32)(aux_l1 * aux_l1);
		aux_l4 = (int32)(aux_l2 * aux_l2);
		KVA_T_SAMES =(word)(sqrtx(aux_l3 + aux_l4));
		aux_l3 = (int32)(aux_l1 * 1024);
		fator_pot_t = (signed int16)(aux_l3/KVA_T_SAMES);
		corrente_t = (int16)(((int32)(KVA_T_SAMES * 16000)) / tensao_t);
		pot_ativa_t = soma_kw_t;
		pot_aparente_t = KVAR_T_SAMES;
		pot_reativa_t = soma_kvar_t;
		
	#endif

	if (modo_funca == 1)
		{
		/* calculo da corrente R */

		#if (monofasico == false)
			/* calculo da corrente S */
			
			/* calculo da corrente T */
		#endif

		/* calculo da KW R */
	
		#if (monofasico == false)
			/* calculo da KW S */
			
			/* calculo da KW T */
		#endif
		}	

	
		aux_b1 = (char)(HZ_SAMES);
		frequencia = (char)(cristal_sames_128 / aux_b1);


/*		
		#if (com_485 == true)
			output_high(direcao);
			delay_ms(1);
		#endif

	   	fprintf(modbus,"\r\n");
	   	fprintf(modbus,"R: ");
	   	fprintf(modbus,"V:%lu ,", tensao_r);
	   	fprintf(modbus,"Corrente:%lu ,", corrente_r);
	   	fprintf(modbus,"KW:%lu ,", soma_kw_r);
	   	fprintf(modbus,"KVAR:%lu ,", soma_kvar_r);
	   	fprintf(modbus,"KVA:%lu ,", KVA_R_SAMES);
	   	fprintf(modbus,"FP:%ld ,", fator_pot_r);

	   	fprintf(modbus,"  S: ");
	   	fprintf(modbus,"V:%lu ,", tensao_s);
	   	fprintf(modbus,"Corrente:%lu ,", corrente_s);
	   	fprintf(modbus,"KW:%lu ,", soma_kw_s);
	   	fprintf(modbus,"KVAR:%lu ,", soma_kvar_s);
	   	fprintf(modbus,"KVA:%lu ,", KVA_S_SAMES);
	   	fprintf(modbus,"FP:%ld ,", fator_pot_s);

	   	fprintf(modbus,"  T: ");
	   	fprintf(modbus,"V:%lu ,", tensao_t);
	   	fprintf(modbus,"Corrente:%lu ,", corrente_t);
	   	fprintf(modbus,"KW:%lu ,", soma_kw_t);
	   	fprintf(modbus,"KVAR:%lu ,", soma_kvar_t);
	   	fprintf(modbus,"KVA:%lu ,", KVA_T_SAMES);
	   	fprintf(modbus,"FP:%ld ,", fator_pot_t);
	   	
	   	fprintf(modbus,"  HZ:%u ,", frequencia);
	   	fprintf(modbus,"HZ:%lu ,", HZ_SAMES);
	   	fprintf(modbus,"\r\n");
	   	
		#if (com_485 == true)
			output_low(direcao);
			delay_ms(2);
		#endif

*/

	conta_media_ten = 0;
	soma_efi_tr = 0;
	soma_kw_r = 0;
	soma_kvar_r = 0;
	#if (monofasico == false)
		soma_efi_ts = 0;
		soma_kw_s = 0;
		soma_kvar_s = 0;
		soma_efi_tt = 0;
		soma_kw_t = 0;
		soma_kvar_t = 0;
	#endif

	med_ten_ok = false;
	calcular_frequencia = false;
	calc_ten_ok = false;

}

