/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_INTS                                                        *
; Funcao: MODULO Interrupçoes 					  						 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 06/06/2003                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/



#INT_TIMER3  // FAST //a cada ???? ms
void temporizador3(void){
	word leitura;
	cont_fase++;
	if (freq_50HZ == 1){
		set_timer3(valor_timer3_2_50HZ);
	}
	else{
		set_timer3(valor_timer3_2_60HZ);
	}
	morder_t3 = 1;
	if (med_ten_ok == 0){
		if ((ler_ad_t3 == 1) || (time_out_t3 == 0)){
			if (passo_ad_8300 == 0){
				set_adc_channel(6);
				delay_us(20);
				buf_tensao_r[passo_tensao] = (signed word)read_adc();
				#if (com_tc == true)
					set_adc_channel(0);
					delay_us(20);
					buf_corrente_r[passo_corrente] = (signed word)read_adc();
				#endif
				}
			else if (passo_ad_8300 == 1){
				set_adc_channel(7);
				delay_us(20);
				buf_tensao_s[passo_tensao] = (signed word)read_adc();
				#if (com_tc == true)
					set_adc_channel(1);
					delay_us(20);
					buf_corrente_s[passo_corrente] = (signed word)read_adc();
				#endif
			}
			else if (passo_ad_8300 == 2){
				set_adc_channel(8);
				delay_us(20);
				buf_tensao_t[passo_tensao] = (signed word)read_adc();
				#if (com_tc == true)
					set_adc_channel(2);
					delay_us(20);
					buf_corrente_t[passo_corrente] = (signed word)read_adc();
				#endif
			}
			else{
				med_ten_ok = 1;
				passo_ad_8300 = 255;
			}
				
			passo_tensao++;
			#if (com_tc == true)
				passo_corrente++;
				if (passo_corrente == NRO_AMOSTRAS){
					passo_corrente = 0;
				}
			#endif
			if (passo_tensao == NRO_AMOSTRAS){
				med_ten_ok = 1;
				ler_ad_t3 = 0;
				passo_tensao = 0;
				#if (com_tc == true)
					passo_corrente = off_cor_r;
				#endif
				passo_ad_8300++;
//				if (nro_soma_vref < NRO_MEDIAS_VREF){
//					set_adc_channel(4);
//					delay_us(20);
//					soma_vref += read_adc();
//					nro_soma_vref++;
//				}
			}
		}
	}
}



