/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_COMU                                                        *
; Funcao: MODULO gerencialde comunicação rs232/485						 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */

//void tx_cht_mdb(void);

//void le_senoide_cht_timer(void);

#if (com_gestal == true)
	#include "gestal.c"  
#endif


#if (chip_cs5460a == true)
	void aguarda_cruzar_zero(char);
	void le_seno(char fase);
#endif


void modbus_funcao04(void)
{
	char ptrtx_old, ptrtx_regs;
	char x;
	
    erro_mod = 0;
	qerro_mod = 0;

	le_endereco();
	le_nro_pontos();
                    
	ptrtx_old = ptrtx;

    ptrtx++;
    
    ptrtx_regs = ptrtx;

	if (addr_regs_modbus == 0)
		{
        erro_mod = 1;
		qerro_mod = 2;
		}
	if (erro_mod == 0)
		{
		existe = 0;			    
		aux_b2 = addr_regs_modbus - 1;
		for (aux_b1 = 0; aux_b1 < nro_pontos_modbus; aux_b1++)
			{
			 if ((addr_regs_modbus >= 100) && (addr_regs_modbus <= 224))
			 	 {
	 		 	aux_b3 = addr_regs_modbus - 100;	
				#if (com_cht == true)
					#if (ade7754 == true)
						if (aux_b3 >= NRO_AMOSTRAS_CHT)
							{
							 aux_sw1 = (signed word)(buf_corrente_r[aux_b3 - NRO_AMOSTRAS_CHT]);
							 aux_sw1 = (signed word)(aux_sw1 / 8);
							data1_int = 2048 + aux_sw1;
							}
						else
							{
							aux_sw1 = (signed word)(buf_tensao_r[aux_b3]);
							aux_sw1 = (signed word)(aux_sw1 / 8);
							data1_int = 2048 + aux_sw1;
							}
					#else
						if (aux_b3 == 0)
							{
							passo_fase_cht = 0;
							#if (chip_cs5460a == true)
								lendo_cht_cs5460 = 1;
								aguarda_cruzar_zero('R');
								le_seno('R');
							#else
								le_senoide_cht_timer();
							#endif
							}
						#if (chip_cs5460a == true)
					 		aux_sw1 = (signed word)(buffer_cht_t[aux_b3]);
					 		aux_sw1 = (signed word)(aux_sw1 / 16);
							data1_int = 2048 + aux_sw1;
						#else
							#if (teste_off_set == 1)
								if (aux_b3 >= NRO_AMOSTRAS)
									{
		 					 		data1_int = buf_cor_tmp[aux_b3 - NRO_AMOSTRAS] - vref;
									}
								else
									{
		 					 		data1_int = buf_ten_tmp[aux_b3] - vref;
		 					 		}
							#else
								#if (CONTROLADOR == true)
	 						 		data1_int = buffer_cht[aux_b3];
								#else
 						 			data1_int = buffer_cht[aux_b3];
 						 		#endif
 						 	#endif
						#endif
					#endif
				#else
//					data1_int = vref;
					#if (teste_off_set == 1)
				 		data1_int = buf_ten_tmp[aux_b3/2];
					#else
						data1_int = buf_tensao_r[aux_b3/2];
					#endif
				#endif
			 	 }
			 else if ((addr_regs_modbus >= 225) && (addr_regs_modbus <= 349))
			 	 {
 		 		aux_b3 = addr_regs_modbus - 225;	
				#if (com_cht == true)
					#if (ade7754 == true)
			 			aux_sw1 = (signed word)(buf_tensao_s[aux_b3]);
			 			aux_sw1 = (signed word)(aux_sw1 / 8);
						data1_int = 2048 + aux_sw1;
					#else
						if (aux_b3 == 0)
							{
							passo_fase_cht = 1;
							#if (chip_cs5460a == true)
								lendo_cht_cs5460 = 1;
								aguarda_cruzar_zero('S');
								le_seno('S');
							#else
								le_senoide_cht_timer();
							#endif
							}
						#if (chip_cs5460a == true)
					 		aux_sw1 = (signed word)(buffer_cht_t[aux_b3]);
					 		aux_sw1 = (signed word)(aux_sw1 / 16);
							data1_int = 2048 + aux_sw1;
						#else
							aux_b3 += (NRO_AMOSTRAS_CHT * 120 / 360);
							if (aux_b3 >= NRO_AMOSTRAS_CHT)
								{
								aux_b3 = aux_b3 - NRO_AMOSTRAS_CHT;
								}
					 		data1_int = buffer_cht[aux_b3];
						#endif
					#endif
				#else
//					data1_int = vref;
					data1_int = buf_tensao_s[aux_b3/2];
				#endif
	 		 	 }
	 		 else if ((addr_regs_modbus >= 350) && (addr_regs_modbus <= 474))
	 		 	 {
 		 		aux_b3 = addr_regs_modbus - 350;	
				#if (com_cht == true)
					#if (ade7754 == true)
				 		aux_sw1 = (signed word)(buf_tensao_t[aux_b3]);
				 		aux_sw1 = (signed word)(aux_sw1 / 8);
						data1_int = 2048 + aux_sw1;
					#else
						if (aux_b3 == 0)
							{
							passo_fase_cht = 2;
							#if (chip_cs5460a == true)
								lendo_cht_cs5460 = 1;
								aguarda_cruzar_zero('T');
								le_seno('T');
							#else
								le_senoide_cht_timer();
							#endif
							}
						#if (chip_cs5460a == true)
					 		aux_sw1 = (signed word)(buffer_cht_t[aux_b3]);
		 					aux_sw1 = (signed word)(aux_sw1 / 16);
							data1_int = 2048 + aux_sw1;
						#else
							aux_b3 += ((NRO_AMOSTRAS_CHT * 120 / 360) * 2);
							if (aux_b3 >= NRO_AMOSTRAS_CHT)
								{
								aux_b3 = aux_b3 - NRO_AMOSTRAS_CHT;
								}
					 		data1_int = buffer_cht[aux_b3];
						#endif
					#endif
				#else
//					data1_int = vref;
					data1_int = buf_tensao_t[aux_b3/2];
				#endif	
	 		 	 }
	 		 else if ((addr_regs_modbus >= 475) && (addr_regs_modbus <= 599))
	 		 	 {
 		 		aux_b3 = addr_regs_modbus - 475;	
				#if (com_cht == true)
					#if (ade7754 == true)
			 			aux_sw1 = (signed word)(buf_corrente_r[aux_b3]);
			 			aux_sw1 = (signed word)(aux_sw1 / 8);
						data1_int = 2048 + aux_sw1;
					#else
						if (aux_b3 == 0)
							{
							passo_fase_cht = 3;
							#if (chip_cs5460a == true)
								lendo_cht_cs5460 = 1;
								aguarda_cruzar_zero('R');
								le_seno('R');
							#else
								le_senoide_cht_timer();
							#endif
							}
						#if (chip_cs5460a == true)
					 		aux_sw1 = (signed word)(buffer_cht_c[aux_b3]);
					 		aux_sw1 = (signed word)(aux_sw1 / 16);
							data1_int = 2048 + aux_sw1;
						#else
					 		data1_int = buffer_cht[aux_b3];
						#endif
					#endif
				#else
//					data1_int = vref;
					#if (teste_off_set == 1)
				 		data1_int = buf_cor_tmp[aux_b3/2];
					#else
						data1_int = buf_corrente_r[aux_b3/2];
					#endif
				#endif	
	 		 	 }
	 		 else if ((addr_regs_modbus >= 600) && (addr_regs_modbus <= 724))
	 		 	 {
	 		 		aux_b3 = addr_regs_modbus - 600;	
				#if (com_cht == true)
					#if (ade7754 == true)
			 			aux_sw1 = (signed word)(buf_corrente_s[aux_b3]);
			 			aux_sw1 = (signed word)(aux_sw1 / 8);
						data1_int = 2048 + aux_sw1;
					#else
						if (aux_b3 == 0)
							{
							passo_fase_cht = 4;
							#if (chip_cs5460a == true)
								lendo_cht_cs5460 = 1;
								aguarda_cruzar_zero('S');
								le_seno('S');
							#else
								le_senoide_cht_timer();
							#endif
							}
						#if (chip_cs5460a == true)
					 		aux_sw1 = (signed word)(buffer_cht_c[aux_b3]);
					 		aux_sw1 = (signed word)(aux_sw1 / 16);
							data1_int = 2048 + aux_sw1;
						#else
							aux_b3 = (NRO_AMOSTRAS_CHT * 120 / 360)  + aux_b3;
							if (aux_b3 >= NRO_AMOSTRAS_CHT)
								{
								aux_b3 = aux_b3 - NRO_AMOSTRAS_CHT;
								}
					 		data1_int = buffer_cht[aux_b3];
						#endif
					#endif
				#else
					data1_int = buf_corrente_s[aux_b3/2];
				#endif	
	 		 	 }
	 		 else if ((addr_regs_modbus >= 725) && (addr_regs_modbus <= 849))
	 		 	 {
	 		 	aux_b3 = addr_regs_modbus - 725;	
				#if (com_cht == true)
					#if (ade7754 == true)
						aux_sw1 = (signed word)(buf_corrente_t[aux_b3]);
						aux_sw1 = (signed word)(aux_sw1 / 8);
						data1_int = 2048 + aux_sw1;
					#else
						if (aux_b3 == 0)
							{
							passo_fase_cht = 5;
							#if (chip_cs5460a == true)
								lendo_cht_cs5460 = 1;
								aguarda_cruzar_zero('T');
								le_seno('T');
							#else
								le_senoide_cht_timer();
							#endif
							}
						#if (chip_cs5460a == true)
					 		aux_sw1 = (signed word)(buffer_cht_c[aux_b3]);
					 		aux_sw1 = (signed word)(aux_sw1 / 16);
							data1_int = 2048 + aux_sw1;
						#else
							aux_b3 = ((NRO_AMOSTRAS_CHT * 120 / 360) * 2)  + aux_b3;
							if (aux_b3 >= NRO_AMOSTRAS_CHT)
								{
								aux_b3 = aux_b3 - NRO_AMOSTRAS_CHT;
								}
					 		data1_int = buffer_cht[aux_b3];
						#endif
					#endif
				#else
					data1_int = buf_corrente_t[aux_b3/2];
				#endif	
	 		 	 }
			#if (com_gestal == true)
 		 		else if ((addr_regs_modbus >= 900) && (addr_regs_modbus <= 999))
 		 			{
					tx_regs_gestal();
	 		 		}
	 		 #endif
			#if (com_regs == true)
		 		 else if ((addr_regs_modbus >= addr_inicio_coleta_regs) && (addr_regs_modbus <= (addr_inicio_coleta_regs + nro_registros_por_banco)))
		 		 	{
				    ptrtx = ptrtx_regs;
			 		 	
					tx_reg_mdb();
					aux_b1 += (nro_pontos_modbus * 2);
					goto modbus_funcao04_00;
					}
		 		 else if ((addr_regs_modbus >= addr_inicio_coleta_ocor) && (addr_regs_modbus <= (addr_inicio_coleta_ocor + limite_ocorrencias)))
		 		 	{
				    ptrtx = ptrtx_regs;
				    
					tx_ocor_mdb();
					aux_b1 +=  (nro_pontos_modbus * 2);
					goto modbus_funcao04_00;
		 	 		}
	 	 	#endif
	 	 	#if (com_cht == true)
		 		 else if ((addr_regs_modbus >= 8000) && (addr_regs_modbus <= (8000 + limite_chts)))
		 		 	{
					#if (com_regs == true)
						tx_cht_mdb();
						aux_b1 += (nro_pontos_modbus * 2);
						goto modbus_funcao04_00;
					#else
						data1_int = 0;
					#endif				
					}
		 		else if ((addr_regs_modbus >= 9700) && (addr_regs_modbus <= 9749))
		 		 	{
		 		 	 aux_b3 = addr_regs_modbus - 9700;
		 		 	 x = 1;
		 		 	 goto cht_modb;
					}
		 		else if ((addr_regs_modbus >= 9750) && (addr_regs_modbus <= 9799))
		 		 	{
		 		 	 aux_b3 = addr_regs_modbus - 9750;
		 		 	 x = 2;
		 		 	 goto cht_modb;
					}
		 		else if ((addr_regs_modbus >= 9800) && (addr_regs_modbus <= 9849))
		 		 	{
		 		 	 aux_b3 = addr_regs_modbus - 9800;
		 		 	 x = 3;
		 		 	 goto cht_modb;
					}
		 		else if ((addr_regs_modbus >= 9850) && (addr_regs_modbus <= 9899))
		 		 	{
		 		 	 aux_b3 = addr_regs_modbus - 9850;
		 		 	 x = 4;
		 		 	 goto cht_modb;
					}
		 		else if ((addr_regs_modbus >= 9900) && (addr_regs_modbus <= 9949))
		 		 	{
		 		 	 aux_b3 = addr_regs_modbus - 9900;
		 		 	 x = 5;
		 		 	 goto cht_modb;
					}
		 		else if ((addr_regs_modbus >= 9950) && (addr_regs_modbus <= 9999))
		 		 	{
		 		 	 aux_b3 = addr_regs_modbus - 9950;
		 		 	 x = 6;
	cht_modb: 		
					switch(x)
						{
						case 1:
							{
			 		 	 	data1_int =  CHT_tr[aux_b3];
				 		 	 break;
							}
						case 2:
							{
							#if (monofasico == false)
			 		 	 		data1_int =  CHT_ts[aux_b3];
			 		 	 	#else
			 		 	 		data1_int = 0;
			 		 	 	#endif
			 		 	 	
				 		 	 break;
							}
						case 3:
							{
							#if (monofasico == false)
					 		 	 data1_int =  CHT_tt[aux_b3];
							#else
							 	data1_int = 0;
							#endif
				 		 	 break;
							}
						case 4:
							{
			 		 	 	data1_int =  CHT_cr[aux_b3];
				 		 	 break;
							}
						case 5:
							{
							#if (monofasico == false)
					 		 	 data1_int =  CHT_cs[aux_b3];
							#else
							 	data1_int = 0;
							#endif
				 		 	 break;
							}
						case 6:
							{
							#if (monofasico == false)
				 		 	 	data1_int =  CHT_ct[aux_b3];
							#else
							 	data1_int = 0;
							#endif
				 		 	 break;
							}
						} 	 
					}
			#endif
			#if (controlador == true)
				#if (st8500c == false)
			 		else if ((addr_regs_modbus >= 10000) && (addr_regs_modbus <= 10100))
		 			 	{
		 			 	 aux_b3 = addr_regs_modbus - 10000;
		 			 	 addr =  ee_ptr_ocor + aux_b3;
			 			 data1_int = read_byte(addr);
			 			 if (aux_b3 == 0)
							{
							if (data1_int == 0xff)
								{
								data1_int = 0;
								}
				 			 }
						}
				#endif
			 		else if ((addr_regs_modbus >= 10101) && (addr_regs_modbus <= 10116))
		 			 	{
		 			 	 aux_b3 = addr_regs_modbus - 10101;
			 			 addr =  ee_acionamentos + (aux_b3 * 2);
			 			 data1_int = read_word(addr);
						}
			 		else if ((addr_regs_modbus >= 10117) && (addr_regs_modbus <= 10132))
		 			 	{
		 			 	 aux_b3 = addr_regs_modbus - 10117;
			 			 addr =  ee_horimetro + (aux_b3 * 2);
			 			 data1_int = read_word(addr);
						}
			#endif
	 	 	else
				{
				le_word_vars_modbus();
				}
			poe_word_buftx();
modbus_funcao04_00:
			addr_regs_modbus++;
			if (erro_mod == 1)
				{
				break;
				}
			}    
		}
	buf_tx[ptrtx_old] = nro_pontos_modbus * 2;  /* monta nro de pontos */

 	if (erro_mod == 1)
 		{
		buf_tx[1] = buf_tx[1] | 0x80;
		buf_tx[2] = qerro_mod;
		ptrtx = 3;
 		}
 		
	crc_modbus =  crc16(buf_tx, ptrtx, 'M');
	data1_int = crc_modbus;
	poe_word_buftx();
	dispara_tx();
}











	 
