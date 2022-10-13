/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: st92ROTA                                                        *
; Funcao: MODULO ROTINAS             									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */

void inic_consumo(void)
{	
	nro_soma_consumo = 0;
	soma_consumo_r = 0;
	soma_consumo_s = 0;
	soma_consumo_t = 0;
	soma_consumo_rea_r = 0;
	soma_consumo_rea_s = 0;
	soma_consumo_rea_t = 0;

	consumo = 0;
	consumo_ati= 0;
	consumo_ati_p= 0;
	consumo_r_tmp = 0;
	consumo_reati_r_tmp = 0;
	consumo_reati = 0;
	consumo_rea_p = 0;
	
	#if (com_consumo_aparente == true)
		soma_dem_apa_r = 0;
		soma_dem_apa_s = 0;
		soma_dem_apa_t = 0;

		consumo_apa_r_tmp = 0;
		consumo_apa = 0;
		consumo_apa_p = 0;
	#endif
}

void grava_consumo_old(void){
	write_word(ee_consumo_ati_ant,consumo_ati);
	write_word(ee_consumo_reati_ant,consumo_reati);
	aux_l1 = (int32)(consumo_r_tmp * 1000);
	write_word(ee_consumo_ati_tmp_ant ,aux_l1);
	aux_l1 = (int32)(consumo_reati_r_tmp * 1000);
	write_word(ee_consumo_reati_tmp_ant,aux_l1);
}


#if (com_demanda == true)
	void zera_demandas(void)
	{
		dem_maxima_aparente = 0;
		dem_maxima_ativa = 0;
		dem_media_ativa = 0;
		dem_media_aparente = 0;
		soma_dem_apa_r = 0;
		soma_dem_apa_s = 0;
		soma_dem_apa_t = 0;
		for (aux_b1 = 0; aux_b1 < 59; aux_b1++)
			{
			morder_t1 = 1;
			morder_t3 = 1;
			morder_calc = 1;
			write_word(ee_buf_dem_ativa + (aux_b1 * 2), 0);
			write_word(ee_buf_dem_aparente + (aux_b1 * 2), 0);
			pulsa_wdt();
			}
		#if (st8500c == true)
			#if (com_tc == true)
				aux_intervalo_integra = 1;	//intervalo_integra;
			#endif
		#else
			aux_intervalo_integra = intervalo_integra;
		#endif
		
		dem_apa_r = 0;
		dem_apa_s = 0;
		dem_apa_t = 0;
		dem_aparente = 0;
	
		demanda_r = 0;	
		demanda_s = 0;
		demanda_t = 0;	
		dem_ativa = 0;
	
		dem_reat_r = 0;	
		dem_reat_s = 0;
		dem_reat_t = 0;	
		dem_reativa = 0;
	
	}
#endif

void zera_consumo(void)
{

	inic_consumo();

	write_word(ee_consumo_l,0);
	write_word(ee_consumo_h,0);
		
	write_word(ee_consumo_rea_l,0);
	write_word(ee_consumo_rea_h,0);

	write_word(ee_consumo_l_p,0);
	write_word(ee_consumo_h_p,0);
		
	write_word(ee_consumo_rea_l_p,0);
	write_word(ee_consumo_rea_h_p,0);

	#if (com_consumo_aparente == true)
		write_word(ee_consumo_apa_l,0);
		write_word(ee_consumo_apa_h,0);
	
		write_word(ee_consumo_apa_l_p,0);
		write_word(ee_consumo_apa_h_p,0);
	#endif

	#if (com_demanda == true)
		zera_demandas();
	
		dem_maxima_aparente_ant = 0;
		dem_maxima_ativa_ant = 0;
		
	 	write_word(ee_dem_maxima_aparente_ant,0);
	 	write_word(ee_dem_maxima_ativa_ant,0);
	#endif
}


void integra_consumo(void){
	int32 soma_consumo;
	float aux_f1;
	if (modo_funca != 1){
		return;
	}
	
	#if (st8500c == true)
		aux_w1 = 120;		// como integralizamos a cada 30 segundos, deve ser multiplicado por 2.
	#else
		aux_w1 = 60;
	#endif
	periodo_soma = (word)(nro_soma_consumo * aux_w1);		// multiplica cada valor integrado 

	aux_b1 = minuto - 1;
	if (aux_b1 == 255){
		aux_b1 = 59;
	}
	aux_b1 = aux_b1 * 2;
															// por 60 para dar 1 minuto(3600 segundos)
// integra/calcula consumo ativo		
	#if (com_demanda == true)
		aux_l2 = soma_dem_apa_r;
		dem_apa_r = (int16)(aux_l2 / nro_soma_consumo);
		aux_l2 = soma_dem_apa_s; 
		dem_apa_s = (int16)(aux_l2 / nro_soma_consumo);
		aux_l2 = soma_dem_apa_t; 
		dem_apa_t = (int16)(aux_l2 / nro_soma_consumo);
		aux_l2 = dem_apa_r;
		aux_l2 += dem_apa_s; 
		aux_l2 += dem_apa_t;
		aux_l2 *= valor_tp;
		dem_aparente = (int16)(aux_l2 / 32);
	
		write_word((ee_buf_dem_aparente + aux_b1), dem_aparente);
	#endif

	#if (com_demanda == true)
	    aux_l2 = soma_consumo_r;
		demanda_r = (int16)(aux_l2 / nro_soma_consumo);	
	    aux_l2 = soma_consumo_s;
		demanda_s = (int16)(aux_l2 / nro_soma_consumo);
	    aux_l2 = soma_consumo_t;
		demanda_t = (int16)(aux_l2 / nro_soma_consumo);	
		aux_l2 = demanda_r;
		aux_l2 += demanda_s; 
		aux_l2 += demanda_t;
		aux_l2 *= valor_tp;
		dem_ativa = (int16)(aux_l2 / 32);
		
		write_word((ee_buf_dem_ativa + aux_b1), dem_ativa);
	#endif
	#if (st8500c == true)
		#if (com_tc == true)
			aux_b1 = minuto + 15;
			if (aux_b1 > 59)
				{
				aux_b1 = aux_b1 - 59;
				}
			write_word((ee_buf_dem_ativa + (aux_b1 * 2)), 0);			// apaga a demanda do intervalo futuro.
			write_word((ee_buf_dem_aparente + (aux_b1 * 2)), 0);
		#endif
	#endif

	soma_consumo = soma_consumo_r + soma_consumo_s + soma_consumo_t;
	aux_f1 = soma_consumo;
	consumo_r_tmp += (float)(aux_f1 / periodo_soma);

	#if(com_rep)
		consumo_tmp = (int16)(consumo_r_tmp);
		consumo_r_tmp = (float)(consumo_r_tmp - consumo_tmp);
	#else
		consumo_tmp = (int16)(consumo_r_tmp / 32);
		consumo_r_tmp = (float)(consumo_r_tmp - (consumo_tmp * 32));
	#endif
	consumo_l = read_word(ee_consumo_l);	
	consumo_h = read_word(ee_consumo_h);	
	consumo = make32(consumo_h,consumo_l);
	consumo += consumo_tmp;
	consumo_l = consumo;
	consumo_h = consumo >> 16;

	write_word(ee_consumo_l, consumo_l);
	write_word(ee_consumo_h, consumo_h);

	consumo_ati = consumo;

	soma_consumo_r = 0;
	soma_consumo_s = 0;
	soma_consumo_t = 0;
		
// integra/calcula consumo reativo		
    aux_l2 = soma_consumo_rea_r;
	dem_reat_r = (int16)(aux_l2 / nro_soma_consumo);	
    aux_l2 = soma_consumo_rea_s;
	dem_reat_s = (int16)(aux_l2 / nro_soma_consumo);
    aux_l2 = soma_consumo_rea_t;
	dem_reat_t = (int16)(aux_l2 / nro_soma_consumo);	
	aux_l2 = dem_reat_r;
	aux_l2 += dem_reat_s; 
	aux_l2 += dem_reat_t; 
	aux_l2 *= valor_tp;
	dem_reativa = (int16)(aux_l2 / 32);

	soma_consumo = soma_consumo_rea_r + soma_consumo_rea_s + soma_consumo_rea_t;
	aux_f1 = soma_consumo;
	consumo_reati_r_tmp += (float)(aux_f1 / periodo_soma);

	consumo_tmp = (int16)(consumo_reati_r_tmp);
	consumo_reati_r_tmp = (float)(consumo_reati_r_tmp - consumo_tmp);

	consumo_l = read_word(ee_consumo_rea_l);	
	consumo_h = read_word(ee_consumo_rea_h);	

	consumo = make32(consumo_h,consumo_l);
	consumo += consumo_tmp;
	consumo_l = consumo;
	consumo_h = consumo >> 16;

	write_word(ee_consumo_rea_l, consumo_l);
	write_word(ee_consumo_rea_h, consumo_h);

	consumo_reati = consumo;

	soma_consumo_rea_r = 0;
	soma_consumo_rea_s = 0;                           
	soma_consumo_rea_t = 0;

//#################################################################################################
	
	// Integra/calcula consumo aparente atendendo Maxi Eletro
	#if (com_consumo_aparente == true)
		soma_consumo = soma_dem_apa_r + soma_dem_apa_s + soma_dem_apa_t;
		aux_f1 = soma_consumo;
		consumo_apa_r_tmp += (float)(aux_f1 / periodo_soma);

		if (consumo_apa_r_tmp > 32){
			consumo_tmp = (int16)(consumo_apa_r_tmp / 32);
			consumo_apa_r_tmp = (float)(consumo_apa_r_tmp - (consumo_tmp * 32));			
			if ((hora >= hora_ponta) && ( hora < hora_final_ponta)){
				consumo_l = read_word(ee_consumo_apa_l_p);	
				consumo_h = read_word(ee_consumo_apa_h_p);	
			}
			else{
				consumo_l = read_word(ee_consumo_apa_l);
				consumo_h = read_word(ee_consumo_apa_h);
			}
			consumo = make32(consumo_h,consumo_l);
			consumo += consumo_tmp;
			consumo_l = consumo;
			consumo_h = consumo >> 16;
			if ((hora >= hora_ponta) && ( hora < hora_final_ponta)){
				write_word(ee_consumo_apa_l_p, consumo_l);
				write_word(ee_consumo_apa_h_p, consumo_h);
			}
			else{
				write_word(ee_consumo_apa_l, consumo_l);
				write_word(ee_consumo_apa_h, consumo_h);
			}
		}
		else
			{
			if ((hora >= hora_ponta) && ( hora < hora_final_ponta)){
				consumo_l = read_word(ee_consumo_apa_l_p);
				consumo_h = read_word(ee_consumo_apa_h_p);
			}
			else{
				consumo_l = read_word(ee_consumo_apa_l);
				consumo_h = read_word(ee_consumo_apa_h);
			}
			consumo = make32(consumo_h,consumo_l);
		}
	
		if ((hora >= hora_ponta) && ( hora < hora_final_ponta)){
			consumo_apa_p = consumo;
		}
		else{
			consumo_apa = consumo;
		}
		soma_dem_apa_r = 0;
		soma_dem_apa_s = 0;
		soma_dem_apa_t = 0;
	#else
		#if (com_demanda == true)
			soma_dem_apa_r = 0;
			soma_dem_apa_s = 0;
			soma_dem_apa_t = 0;
		#endif
	#endif
//#################################################################################################


// reinicializa somatorio de consumo
	nro_soma_consumo = 0;

}

void soma_consumo(void){
	if (modo_funca != 1){
		return;
	}

	#if(com_rep)
		aux_l1 = (int32)(pot_ativa_tot / 3);
		soma_consumo_r += aux_l1;
		soma_consumo_s += aux_l1;
		soma_consumo_t += aux_l1;
	
		soma_dem_apa_r += pot_aparente_r;
		soma_dem_apa_s += pot_aparente_s;
		soma_dem_apa_t += pot_aparente_t;
	
		aux_l1 = (int32)(pot_reativa_tot / 3);
		soma_consumo_rea_r += aux_l1;
		soma_consumo_rea_s += aux_l1;
		soma_consumo_rea_t += aux_l1;
	#else
		soma_consumo_r += pot_ativa_r;
		soma_consumo_s += pot_ativa_s;
		soma_consumo_t += pot_ativa_t;
	
		soma_dem_apa_r += pot_aparente_r;
		soma_dem_apa_s += pot_aparente_s;
		soma_dem_apa_t += pot_aparente_t;
	
		soma_consumo_rea_r += pot_reativa_r;
		soma_consumo_rea_s += pot_reativa_s;
		soma_consumo_rea_t += pot_reativa_t;
	#endif

	nro_soma_consumo++;
	
}



#if (com_demanda == true)
	void calcula_demandas(void)
	{
		#if (st8500c == true)
			word dem_max_ativa_tmp;
		#endif
		if (modo_funca != 1)
			{
			return;
			}
	/* integracao de potencia ativa e aparente média e máxima */		
	/* calcula potencia ativa e aparente média e máxima */
		aux_b1 = minuto - 1;
		if (aux_b1 == 255)
			{
			aux_b1 = 59;
			}
		aux_w1 = read_word(ee_buf_dem_ativa + (aux_b1 * 2));
		aux_w2 = read_word(ee_buf_dem_aparente + (aux_b1 * 2));
			
		if (dem_maxima_aparente < aux_w2)
			{
			dem_maxima_aparente = aux_w2;
			}
		if (dem_maxima_ativa < aux_w1)
			{
			dem_maxima_ativa = aux_w1;
			}
		#if (tc_fixo == true)
			#if (st8500c == true)
				if (dem_maxima_ativa > (valor_tc_fixo * ten_nomi * 2))
					{
					 dem_maxima_ativa = 0;
					}
				if (dem_maxima_aparente > (valor_tc_fixo * ten_nomi * 2))
					{
					 dem_maxima_aparente = 0;
					}
			#else
				if (dem_maxima_ativa > (valor_tc_fixo * ten_nomi * valor_tp * 2))
					{
					 dem_maxima_ativa = 0;
					}
				if (dem_maxima_aparente > (valor_tc_fixo * ten_nomi * valor_tp * 2))
					{
					 dem_maxima_aparente = 0;
					}
			#endif
		#else
			if (dem_maxima_ativa > (valor_tc * ten_nomi * valor_tp * 2))
				{
				 dem_maxima_ativa = 0;
				}
			if (dem_maxima_aparente > (valor_tc * ten_nomi * valor_tp * 2))
				{
				 dem_maxima_aparente = 0;
				}
		#endif
		if (aux_intervalo_integra > intervalo_integra)
			{
			#if (st8500c == true)
				aux_intervalo_integra = 1;
			#else
				aux_intervalo_integra = intervalo_integra;
			#endif
			}
		aux_intervalo_integra--;
	
	//	tendencia_demanda_ativa	
		
		if (aux_intervalo_integra == 0)
			{
			aux_l2 = 0;
			aux_l1 = 0;
			#if (st8500c == true)
				dem_max_ativa_tmp = 0;
			#endif
			for (aux_b2 = 0; aux_b2 < intervalo_integra ; aux_b2++)
				{                                          
				aux_l2 += (int32)read_word(ee_buf_dem_aparente + (aux_b1 * 2));
				aux_l3 = (int32)read_word(ee_buf_dem_ativa + (aux_b1 * 2));
				aux_l1 += aux_l3;
				
				aux_b1--;					/* faz minuto = minuto-1 */
				if (aux_b1 == 255)			/* se virou, recomeça em 59 */
					{
					aux_b1 = 59;
					}
				#if (st8500c == true)
					if (dem_max_ativa_tmp < aux_l3)
						{
						dem_max_ativa_tmp = (word)(aux_l3);
						}
				#endif
				pulsa_wdt();
				}
			dem_media_ativa = (int16)(aux_l1 / intervalo_integra);
			dem_media_aparente = (int16)(aux_l2 / intervalo_integra);
			aux_f1 = (float)(dem_media_ativa);
			aux_f1 = (float)(aux_f1 * aux_f1);
			aux_f2 = (float)(dem_media_aparente);
			aux_f2 = (float)(aux_f2 * aux_f2);
			dem_media_reativa = (word)(sqrtx(aux_f2 - aux_f1));
			aux_intervalo_integra = 1;	//intervalo_integra;
			write_word(ee_dem_maxima_aparente, dem_maxima_aparente);
			write_word(ee_dem_maxima_ativa, dem_maxima_ativa);
			#if (st8500c == true)
				#if (com_tc == true)
					aux_l2 = 0;
					aux_l1 = 0;
					aux_b1 = minuto - 1;
					if (aux_b1 > 59)			/* se virou, recomeça em 59 */
						{
						aux_b1 = 59;
						}
					
	//			fprintf(modbus,"NA cons:%u - %u :", minuto, aux_b1 );
					for (aux_b2 = 0; aux_b2 < 2 ; aux_b2++)
						{         
							
	//			fprintf(modbus,"%lu ;", (int32)read_word(ee_buf_dem_ativa + (aux_b1 * 2)));
							                                 
						aux_l2 += (int32)read_word(ee_buf_dem_aparente + (aux_b1 * 2));
						aux_l1 += (int32)read_word(ee_buf_dem_ativa + (aux_b1 * 2));
						aux_b1--;					/* faz minuto = minuto-1 */
						if (aux_b1 > 59)			/* se virou, recomeça em 59 */
							{
							aux_b1 = 59;
							}
						}
					aux_l1 = aux_l1 / 2;
					aux_l2 = aux_l2 / 2;
					dem_ativa_proj = aux_l1;
					aux_f1 = (float)(aux_l1);
					aux_f1 = (float)(aux_f1 * aux_f1);
					aux_f2 = (float)(aux_l2);
					aux_f2 = (float)(aux_f2 * aux_f2);
					dem_reativa_proj =(word)(sqrtx(aux_f2 - aux_f1));
	
	//				fprintf(modbus,"%lu ;", dem_ativa_proj);
	
					// calculo do fator de carga  ==  demanda_media / demanda maxima.
					fator_carga = (dem_media_ativa * 1024) / dem_max_ativa_tmp;			//aux_l2 tem o maior valor de demanda.
					// calculo do  fator de demanda.  = demanda maxima / carga instalada(carga_programada)
					fator_demanda = (word)((dem_max_ativa_tmp * 1024) /  carga_programada);
	
	//			fprintf(modbus,"fc:%lu ; fd:%lu", fator_carga, fator_demanda);
	
	//			fprintf(modbus,"\r\n");
					
				#endif
			#endif
			#if (tc_fixo == true)
				#if (st8500c == true)
					if (dem_maxima_ativa_ant > (valor_tc_fixo * ten_nomi* 2))
						{
						 dem_maxima_ativa_ant = dem_maxima_ativa;
						}
					if (dem_maxima_aparente_ant > (valor_tc_fixo * ten_nomi* 2))
						{
					 	dem_maxima_aparente_ant = dem_maxima_aparente;
						}
				#else
					if (dem_maxima_ativa_ant > (valor_tc_fixo * ten_nomi * valor_tp * 2))
						{
						 dem_maxima_ativa_ant = dem_maxima_ativa;
						}
					if (dem_maxima_aparente_ant > (valor_tc_fixo * ten_nomi * valor_tp * 2))
						{
					 	dem_maxima_aparente_ant = dem_maxima_aparente;
						}
				#endif
			#else
				if (dem_maxima_ativa_ant > (valor_tc * ten_nomi * valor_tp * 2))
					{
					 dem_maxima_ativa_ant = dem_maxima_ativa;
					}
				if (dem_maxima_aparente_ant > (valor_tc * ten_nomi * valor_tp * 2))
					{
				 	dem_maxima_aparente_ant = dem_maxima_aparente;
					}
			#endif
			}
	}
#endif
