/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_MAIN                                                        *
; Funcao: MODULO PRINCIPAL DE CONTROLE									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */


#if (controlador == true)
	#if (st8500c == true)
		void salva_ocorrencia(char codigo)	
			{	
			// somente na pesquisa de um bug, não serve para nada, pois este arquiov não é chamado pelo 8500c
			
			}
	#else
		void salva_ocorrencia(char codigo)	
		{	
				char aux_ptr;
				
				aux_ptr = read_byte(ee_ptr_ocor);
				if (aux_ptr >= 99)
					{
					aux_ptr = 99;
					for (aux_b1 = 0; aux_b1 < 99; aux_b1++)
						{
						write_byte(ee_ocorrencias + aux_b1, read_byte(1 + ee_ocorrencias + aux_b1));
						}
					write_byte(ee_ocorrencias + aux_ptr, codigo);
					}
				else
					{
					write_byte(ee_ocorrencias + aux_ptr, codigo);
					aux_ptr++;
					write_byte(ee_ptr_ocor, aux_ptr);
					}
		}			
	#endif
#endif
  
	
void grava_ocorrencias(char codigo)
{

	char buf_dados[TAM_REGS];
	

	rotina = 2;

	#if (portatil == true)
		if ((registro == 0) || (codigo == codigo_old))
			{
			return;
			}
	#else		
		if (codigo == codigo_old)
			{
			return;
			}
	#endif
	
	#if (controlador == true)
		salva_ocorrencia(codigo);
	#endif

	for (aux_b1 = 8; aux_b1 < TAM_REGS; aux_b1++)
		{
		buf_dados[aux_b1] = 0;
		}

	codigo_old = codigo;
	buf_dados[0] = codigo;
	buf_dados[1] = dia;
	buf_dados[2] = mes;
	buf_dados[3] = ano;
	buf_dados[4] = hora;
	buf_dados[5] = minuto;
	buf_dados[6] = segundo;
	buf_dados[7] = frequencia;

	#if (controlador == false)
		if (codigo == reg_falta_energia)
			{
			buf_dados[1] = dia_old;
			buf_dados[2] = mes_old;
			buf_dados[3] = ano_old;
			buf_dados[4] = hora_old;
			buf_dados[5] = minuto_old;
			buf_dados[6] = segundo_old;
			goto ocor_zero;
			}
		else if (codigo == reg_volta_energia)
			{
			goto ocor_zero;
			}
	#endif
		
	if (tipo_ligacao == 0)
		{
		aux_w1 = tensao_r;
		#if (monofasico == false)
			aux_w2 = tensao_s;
			aux_w3 = tensao_t;
		#endif
		}
	else
		{
		aux_w1 = tensao_rs;
		#if (monofasico == false)
			aux_w2 = tensao_st;
			aux_w3 = tensao_rt;
		#endif
		}
	#if (controlador == false)		
		if (modo_funca == 2)
			{
			tensao_media_r = (word)(soma_media_tensao_r / conta_media_tensao_r);
			tensao_media_s = (word)(soma_media_tensao_s / conta_media_tensao_s);
			tensao_media_t = (word)(soma_media_tensao_t / conta_media_tensao_t);

			buf_dados[8] = (char)(tensao_media_r >> 8);
			buf_dados[9] = (char)(tensao_media_r);
	//
			buf_dados[10] = (char)((soma_reg_cr / nro_soma_reg) >> 8);
			buf_dados[11] = (char)(soma_reg_cr / nro_soma_reg);
			buf_dados[12] = (char)(fator_pot_r >> 8);
			buf_dados[13] = (char)(fator_pot_r);
	//
			buf_dados[14] = (char)(tensao_media_s >> 8);
			buf_dados[15] = (char)(tensao_media_s);
	//
			buf_dados[16] = (char)((soma_reg_cs / nro_soma_reg) >> 8);
			buf_dados[17] = (char)(soma_reg_cs / nro_soma_reg);
			buf_dados[18] = (char)(fator_pot_s >> 8);
			buf_dados[19] = (char)(fator_pot_s);
	//
			buf_dados[20] = (char)(tensao_media_t >> 8);
			buf_dados[21] = (char)(tensao_media_t);
	//	
			buf_dados[22] = (char)((soma_reg_ct / nro_soma_reg) >> 8);
			buf_dados[23] = (char)(soma_reg_ct / nro_soma_reg);
			buf_dados[24] = (char)(fator_pot_t >> 8);
			buf_dados[25] = (char)(fator_pot_t);
	//

			}
		else
			{
			buf_dados[8] = (char)((aux_w1 >> 8) & 0xff);
			buf_dados[9] = (char)(aux_w1 & 0xff);
			buf_dados[10] = (char)((corrente_r >> 8) & 0xff);
			buf_dados[11] = (char)(corrente_r & 0xff);
			buf_dados[12] = (char)((fator_pot_r >> 8) & 0xff);
			buf_dados[13] = (char)(fator_pot_r & 0xff);
			
			buf_dados[14] = (char)((aux_w2 >> 8) & 0xff);
			buf_dados[15] = (char)(aux_w2 & 0xff);
			buf_dados[16] = (char)((corrente_s >> 8) & 0xff);
			buf_dados[17] = (char)(corrente_s & 0xff);
			buf_dados[18] = (char)((fator_pot_s >> 8) & 0xff);
			buf_dados[19] = (char)(fator_pot_s & 0xff);
			
			buf_dados[20] = (char)((aux_w3 >> 8) & 0xff);
			buf_dados[21] = (char)(aux_w3 & 0xff);
			buf_dados[22] = (char)((corrente_t >> 8) & 0xff);
			buf_dados[23] = (char)(corrente_t & 0xff);
			buf_dados[24] = (char)((fator_pot_t >> 8) & 0xff);
			buf_dados[25] = (char)(fator_pot_t & 0xff);
			#if (portatil == true)
				#if (se_com_flex == true)
			 		 buf_dados[26] = tipo_ponteira;
			 	#else
					buf_dados[26] = posi_tc;
			 	#endif
			#else
				buf_dados[26] = posi_tc;
			#endif
			}

			goto salva_ocors;

		ocor_zero:
			buf_dados[7] = 240;
			buf_dados[12] = 4;
			buf_dados[18] = 4;
			buf_dados[24] = 4;
	#else
			#if ((com_rep == true) && (GEBRAS == true))
				if (modo_rep == true)
					{
					buf_dados[8] = (char)((tensao_tri >> 8) & 0xff);
					buf_dados[9] = (char)(tensao_tri & 0xff);
					buf_dados[10] = (char)((corrente_tri >> 8) & 0xff);
					buf_dados[11] = (char)(corrente_tri & 0xff);
					}
				else
					{
					buf_dados[8] = (char)((aux_w1 >> 8) & 0xff);
					buf_dados[9] = (char)(aux_w1 & 0xff);
					buf_dados[10] = (char)((corrente_r >> 8) & 0xff);
					buf_dados[11] = (char)(corrente_r & 0xff);
					}
			#else
				buf_dados[8] = (char)((aux_w1 >> 8) & 0xff);
				buf_dados[9] = (char)(aux_w1 & 0xff);
				buf_dados[10] = (char)((corrente_r >> 8) & 0xff);
				buf_dados[11] = (char)(corrente_r & 0xff);
			#endif
			buf_dados[12] = (char)((fator_pot_r >> 8) & 0xff);
			buf_dados[13] = (char)(fator_pot_r & 0xff);
		
			#if (monofasico == false)
				#if ((com_rep == true) && (GEBRAS == true))
					if (modo_rep == true)
						{
						buf_dados[14] = SAIDA2;
						buf_dados[15] = SAIDA3;
							
						buf_dados[16] = (char)(buf_rec_tmp[0]);
						buf_dados[17] = (char)(buf_rec_tmp[1]);
						buf_dados[18] = (char)(buf_rec_tmp[2]);
						buf_dados[19] = (char)(buf_rec_tmp[3]);
		
						buf_dados[20] = (char)(buf_rec_tmp[4]);
						buf_dados[21] = (char)(buf_rec_tmp[5]);
						buf_dados[22] = (char)(buf_rec_tmp[6]);
						buf_dados[23] = (char)(0);
				//
						buf_dados[24] = 4;
						buf_dados[25] = 0;
							
						}
					else
						{
						buf_dados[14] = (char)((aux_w2 >> 8) & 0xff);
						buf_dados[15] = (char)(aux_w2 & 0xff);
						buf_dados[16] = (char)((corrente_s >> 8) & 0xff);
						buf_dados[17] = (char)(corrente_s & 0xff);
						buf_dados[18] = (char)((fator_pot_s >> 8) & 0xff);
						buf_dados[19] = (char)(fator_pot_s & 0xff);
					
						buf_dados[20] = (char)((aux_w3 >> 8) & 0xff);
						buf_dados[21] = (char)(aux_w3 & 0xff);
						buf_dados[22] = (char)((corrente_t >> 8) & 0xff);
						buf_dados[23] = (char)(corrente_t & 0xff);
						buf_dados[24] = (char)((fator_pot_t >> 8) & 0xff);
						buf_dados[25] = (char)(fator_pot_t & 0xff);
						}
				#else
					buf_dados[14] = (char)((aux_w2 >> 8) & 0xff);
					buf_dados[15] = (char)(aux_w2 & 0xff);
					buf_dados[16] = (char)((corrente_s >> 8) & 0xff);
					buf_dados[17] = (char)(corrente_s & 0xff);
					buf_dados[18] = (char)((fator_pot_s >> 8) & 0xff);
					buf_dados[19] = (char)(fator_pot_s & 0xff);
		
					buf_dados[20] = (char)((aux_w3 >> 8) & 0xff);
					buf_dados[21] = (char)(aux_w3 & 0xff);
					buf_dados[22] = (char)((corrente_t >> 8) & 0xff);
					buf_dados[23] = (char)(corrente_t & 0xff);
					buf_dados[24] = (char)((fator_pot_t >> 8) & 0xff);
					buf_dados[25] = (char)(fator_pot_t & 0xff);
				#endif
			#else
				#if (controlador == true)
					buf_dados[14] = SAIDA2;
					buf_dados[15] = SAIDA3;
				#else
					buf_dados[14] = 0;
					buf_dados[15] = 0;
				#endif
				#if (com_rep == true)
					buf_dados[16] = (char)(buf_rec_tmp[0]);
					buf_dados[17] = (char)(buf_rec_tmp[1]);
					buf_dados[18] = (char)(buf_rec_tmp[2]);
					buf_dados[19] = (char)(buf_rec_tmp[3]);
	
					buf_dados[20] = (char)(buf_rec_tmp[4]);
					buf_dados[21] = (char)(buf_rec_tmp[5]);
					buf_dados[22] = (char)(buf_rec_tmp[6]);
					buf_dados[23] = (char)(0);
				//
					buf_dados[24] = 4;
					buf_dados[25] = 0;
			//
				#else
					buf_dados[16] = (char)(pot_ativa_r >> 8);
					buf_dados[17] = (char)(pot_ativa_r);
					buf_dados[18] = (char)(pot_aparente_r >> 8);
					buf_dados[19] = (char)(pot_aparente_r);
				//
					buf_dados[20] = (char)(pot_reativa_r >> 8);
					buf_dados[21] = (char)(pot_reativa_r);
					buf_dados[22] = 0;
					buf_dados[23] = 0;
					buf_dados[24] = 4;
					buf_dados[25] = 0;
				//
				#endif
			#endif
			#if (portatil == true)
				#if (se_com_flex == true)
			 		 buf_dados[26] = tipo_ponteira;
			 	#else
					buf_dados[26] = posi_tc;
			 	#endif
			#else
				buf_dados[26] = posi_tc;
			#endif
		
	#endif

	salva_ocors:
		buf_dados[27] = modo_funca;
		buf_dados[28] = ten_nomi;
		if (tipo_ligacao == 0)
			{
			buf_dados[29] = 'Y';
			}
		else
			{
			buf_dados[29] = 'D';
			}
		buf_dados[30] = (char)(valor_tp >> 8);
		buf_dados[31] = (char)(valor_tp);

		#if (com_relogio == true)
			aux_w1 =  read_word_nvr(ds_ptr_ocor);
		#else
			aux_w1 =  read_word(ee_ptr_rocor);
		#endif
		if (aux_w1 > limite_ocorrencias)
			{
			aux_w1 = 0;
			}
		aux_l2 = aux_w1;
		#if (controlador == false)		
			if (modo_funca == 3)
				{
				aux_l1 = limite_registros_modo3;
				aux_l1 = (int32)((aux_l1 * TAM_REGS_MODO3))+ 4096;
				}	
			else if (modo_funca == 2)
				{
				aux_l1 = limite_registros_modo2;
				aux_l1 = (int32)((aux_l1 * TAM_REGS_MODO2))+ 4096;
				}
			else
				{
				aux_l1 = limite_registros;
				aux_l1 = (int32)((aux_l1 * TAM_REGS)) + 4096;
				}
		#else
			aux_l1 = limite_registros;
			aux_l1 = (int32)((aux_l1 * TAM_REGS)) + 4096;
		#endif
		aux_l1 = aux_l1 + (int32)(aux_l2 * TAM_REGS);

//	antes de salva, verifica se este setor está apagado,caso não esteja, apaga o setor de 4K.
		if (read_byte_flash(aux_l1) != 0xff)
			{
			sector_flash_erase(aux_l1);
			}
	
/* salva no buffer da flash */	
		aux_b3 = TAM_REGS;
		for (aux_b4 = 0; aux_b4 < aux_b3; aux_b4++)
			{
			write_byte_flash(aux_l1, buf_dados[aux_b4]);
			aux_l1++;
			}
		WRDI(aux_l1);	//Desabilita flash para gravação.
		aux_w1++;
		if (aux_w1 > limite_ocorrencias)
			{
			aux_w1 = 0;	
			}
		#if (com_relogio == true)
			write_word_nvr(ds_ptr_ocor, aux_w1);
		#else
			write_word(ee_ptr_rocor, aux_w1);
		#endif
}


void apaga_ocorrencias(void)
{
	#if (st8500c == true)
	#else
		#if (controlador == true)
			char aux_ptr;
			for (aux_ptr = 0; aux_ptr < 100; aux_ptr++)
				{
				write_byte(ee_ocorrencias + aux_ptr, 0xff);
				}
			write_byte(ee_ptr_ocor, 0);
		#endif
		#if (com_relogio == true)
			write_word_nvr(ds_ptr_ocor, 0);
		#else
			write_word(ee_ptr_rocor, 0);
		#endif
	
		aux_l1 = inicio_ocorrencias;
		sector_flash_erase(aux_l1);
		aux_l1 += 4096;
		sector_flash_erase(aux_l1);
		aux_l1 += 4096;
		sector_flash_erase(aux_l1);
		
		grava_ocorrencias(reg_apagou);
	#endif
}





void tx_ocor_mdb(void)
{
	char x;
	char y;
	
	
	aux_l1 = (int32)(addr_regs_modbus);
	aux_l2 = (int32)(addr_inicio_coleta_ocor);
	aux_l2 = (int32)(aux_l1 - aux_l2);

	#if (controlador == false)		
		if (modo_funca == 3)
			{
			aux_l1 = limite_registros_modo3;
			aux_l1 = (int32)(aux_l1 * TAM_REGS_MODO3) + 4096;
			}
		else if (modo_funca == 2)
			{
			aux_l1 = limite_registros_modo2;
			aux_l1 = (int32)(aux_l1 * TAM_REGS_MODO2) + 4096;
			}
		else
			{
			aux_l1 = limite_registros;
			aux_l1 = (int32)(aux_l1 * TAM_REGS) + 4096;
			}
	#else
		aux_l1 = limite_registros;
		aux_l1 = (int32)(aux_l1 * TAM_REGS) + 4096;
	#endif
	aux_l1 = aux_l1 + (int32)(aux_l2 * TAM_REGS);

	y = (nro_pontos_modbus * 2);
	for (x = 0; x < y ; x++)
		{
		buf_tx[ptrtx++] = read_byte_flash(aux_l1); 
		aux_l1++;
   		}
    	
}



/* fim st_ocor */    
