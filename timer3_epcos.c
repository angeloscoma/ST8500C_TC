/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÿÿÿÔNICOS                                  *
; Modulo: ST_INTS                                                        *
; Funcao: MODULO Interrupÿÿÿçoes 					  						 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 06/06/2003                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/



#INT_TIMER3  // FAST //a cada ???? ms
void temporizador3(void)
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
	if (med_ten_ok == 0)
		{
		if ((ler_ad_t3 == 1) || (time_out_t3 == 0))
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
				passo_corrente = off_cor_r;
			// obtem a referencia do ad
				if (nro_soma_vref < NRO_MEDIAS_VREF)
					{
					soma_vref += le_canal_3();
					nro_soma_vref++;
					}
				}
			}
		}

}



