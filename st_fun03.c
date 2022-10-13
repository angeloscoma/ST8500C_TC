/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRONICOS                                  *
; Modulo: ST_COMU                                                        *
; Funcao: MODULO gerencialde comunicacao rs232/485						 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */
  
void filtra_corrente_r_new(void);

short tx_buffer;

void modbus_funcao03(void)
{
	erro_mod = 0;
	qerro_mod = 0;
	le_endereco();
	le_nro_pontos();
	buf_tx[ptrtx++] = nro_pontos_modbus * 2;	/* monta nro de pontos */;

	if (addr_regs_modbus == 0)
		{
		erro_mod = 1;
		qerro_mod = 2;
		}
	if (erro_mod == 0)
		{
		existe = 0;
		for (aux_b1 = 0; aux_b1 < nro_pontos_modbus; aux_b1++)
 			{
	 		if (erro_mod == 1)
	 			{
		 		break;
		 		}
//			if ((addr_regs_modbus >= 4000) && (addr_regs_modbus < 4064))
//			 	{
//				#if (teste_off_set == 1)
//		 		 	aux_b3 = addr_regs_modbus - 4000;
//					if (aux_b3 == 0)
//						{
//						tx_buffer = 1;
//						#if (chip_cs5460a == false)
//							#if (ade7754 == false)
//								memcpy(buf_ten_tmp, buf_tensao_r, NRO_AMOSTRAS);
//								memcpy(buf_cor_tmp, buf_corrente_r, NRO_AMOSTRAS);
//							#endif
//						#endif
//						tx_buffer = 0;
//						}
//					data1_int = buf_ten_tmp[aux_b3];
//				#else
//		 		 	aux_b3 = addr_regs_modbus - 4000;
//		 		 	if (aux_b3 == 0)
//		 		 		{
////						filtra_corrente_r_new();
//			 		 	}
////					data1_int = buf_tensao_r[aux_b3];
//					if (aux_b3 < (NRO_AMOSTRAS/4))
//						{
//						data1_int = buf_tensao[aux_b3]-vref;
//						}
//					else
//						{
//						data1_int = buf_corrente[aux_b3 - (NRO_AMOSTRAS/4)]- vref;
//						}
//				#endif
//				}
//			else if ((addr_regs_modbus >= 4064) && (addr_regs_modbus < 4128))
//			 	{
//				#if (teste_off_set == 1)
//		 		 	aux_b3 = addr_regs_modbus - 4064;
//					data1_int = buf_cor_tmp[aux_b3];
//				#else
//		 		 	aux_b3 = addr_regs_modbus - 4064;
////					data1_int = buf_tensao_r[aux_b3];
//					data1_int = buf_corrente_r[aux_b3];
//				#endif
//				}
//			else
//				{
			 	le_byte_regs_modbus();
//				}
		 	addr_regs_modbus++; 
			poe_word_buftx();
 			}
	 	}
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

	 
