

			buf_dados[0] = codigo;
			buf_dados[1] = dia;
			buf_dados[2] = mes;
			buf_dados[3] = ano;
			buf_dados[4] = hora;
			buf_dados[5] = minuto;
			buf_dados[6] = segundo;
		  	buf_dados[7] = frequencia;

			buf_dados[8] = (char)((soma_reg_tr / nro_soma_reg) >> 8);
			buf_dados[9] = (char)(soma_reg_tr / nro_soma_reg);
			buf_dados[10] = (char)((soma_reg_cr / nro_soma_reg) >> 8);
			buf_dados[11] = (char)(soma_reg_cr / nro_soma_reg);
			buf_dados[12] = (char)(fator_pot_r >> 8);
			buf_dados[13] = (char)(fator_pot_r);
		//
			buf_dados[14] = (char)((soma_reg_ts / nro_soma_reg) >> 8);
			buf_dados[15] = (char)(soma_reg_ts / nro_soma_reg);
			buf_dados[16] = (char)((soma_reg_cs / nro_soma_reg) >> 8);
			buf_dados[17] = (char)(soma_reg_cs / nro_soma_reg);
			buf_dados[18] = (char)(fator_pot_s >> 8);
			buf_dados[19] = (char)(fator_pot_s);
			//
			buf_dados[20] = (char)((soma_reg_tt / nro_soma_reg) >> 8);
			buf_dados[21] = (char)(soma_reg_tt / nro_soma_reg);
			buf_dados[22] = (char)((soma_reg_ct / nro_soma_reg) >> 8);
			buf_dados[23] = (char)(soma_reg_ct / nro_soma_reg);
			buf_dados[24] = (char)(fator_pot_t >> 8);
			buf_dados[25] = (char)(fator_pot_t);

		//	
			#if (portatil == true)
				#if (se_com_flex == true)
		 			 buf_dados[26] = tipo_ponteira;
		 		#else
					buf_dados[26] = posi_tc;
			 	#endif
			#else
				buf_dados[26] = posi_tc;
			#endif
	

			buf_dados[27] = modo_funca;
			buf_dados[28] = ten_nomi;

			#if (monofasico == true)
			if (tipo_ligacao == 0)
				{
				buf_dados[29] = 'Y';
				}
			else
				{
				buf_dados[29] = 'D';
				}
			#else
			if (tipo_ligacao == 1)
				{
				buf_dados[29] = 'D';
				}
			else if (tipo_ligacao == 2)
				{
				buf_dados[29] = 'A';
				}
			else
				{
				buf_dados[29] = 'Y';
				}

			buf_dados[30] = (char)(valor_tp >> 8);
			buf_dados[31] = (char)(valor_tp);

