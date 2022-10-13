/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_MAIN                                                        *
; Funcao: MODULO PRINCIPAL DE CONTROLE									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */



#if (teste_cht_vag == true)
	#include "seno_120.c"	
#endif

void le_tensao_r(void);
void le_tensao_s(void);
void le_tensao_t(void);
void le_corrente_r(void);
void le_corrente_s(void);
void le_corrente_t(void);

void grava_cht(char codigo_cht)
{   
	char buf_dados[10];
	char tentativas_wr;
	char aux_b3, aux_b4;
	word aux_w1;
	int32 aux_l1, aux_l2;

	#if (portatil == true)
		#if (versao_pci_st96 >= 6)
			if (time_out_troca_ponteira	 != 0)
				{
				return;
				}
		#endif
	#endif

	rotina = 3;	
	#if feira
		return;
	#endif

	if (registro == 0)
		{
		return;
		}

	if (modo_funca == 2)
		{
		if (forma_reg_cht == 2 || forma_reg_cht == 3)
			{
			forma_reg_cht = 1;
			write_byte(ee_forma_reg_cht, forma_reg_cht);
			}
		}


	if (forma_reg_cht == 0)
		{
		#if (com_relogio == true)
			aux_w1 = read_word_nvr(ds_ptr_cht);
		#else
			aux_w1 = read_word(ee_ptr_cht);
		#endif
		if (aux_w1 != 0)
			{
			#if (com_relogio == true)
				write_word_nvr(ds_ptr_cht, aux_w1);
			#else
				write_word(ee_ptr_cht, aux_w1);
			#endif
			}
		return;
		}	
	for (aux_calc = 1 ; aux_calc < 7 ; aux_calc++)
		{
		pulsa_wdt();
		gravar_cht = 0;
		buf_dados[0] = codigo_cht;
		buf_dados[1] = dia;
		buf_dados[2] = mes;
		buf_dados[3] = ano;
		buf_dados[4] = hora;
		buf_dados[5] = minuto;
		buf_dados[6] = segundo;
		switch(aux_calc)
			{
			case 1:
				{
				if (forma_reg_cht == 1 || forma_reg_cht == 3)
					{
					if (tensao_r > 1023)
						{
						buf_dados[7] = 'R';
						le_tensao_r();
						gravar_cht = 1;
						}
					}
				break;
				}
			#if (monofasico == false)
				case 2:
					{
					if (forma_reg_cht == 1 || forma_reg_cht == 3)
						{
						if (tensao_s > 1023)
							{
							buf_dados[7] = 'S';
							le_tensao_s();
							gravar_cht = 1;
							}
						}
					break;
					}
				case 3:
					{
					if (forma_reg_cht == 1 || forma_reg_cht == 3)
						{
						if (tensao_t > 1023)
							{
							buf_dados[7] = 'T';
							le_tensao_t();
							gravar_cht = 1;
							}
						}
					break;
					}
			#endif
			case 4:
				{
				if (modo_funca == 2)
					{
					gravar_cht = 0;
					}
				else
					{
					if (forma_reg_cht == 2 || forma_reg_cht == 3)
						{
						if (corrente_r > 80)
							{
							buf_dados[7] = 'r';
							le_corrente_r();
							gravar_cht = 1;
							}
						}
					}
				break;
				}
			#if (monofasico == false)
				case 5:
					{
					if (modo_funca == 2)
						{
						gravar_cht = 0;
						}
					else
						{
						if (forma_reg_cht == 2 || forma_reg_cht == 3)
							{
							if (corrente_s > 80)
								{
								buf_dados[7] = 's';
								le_corrente_s();
								gravar_cht = 1;
								}
							}
						}
					break;
					}
				case 6:
					{
					if (modo_funca == 2)
						{
						gravar_cht = 0;
						}
					else
						{
						if (forma_reg_cht == 2 || forma_reg_cht == 3)
							{
							if (corrente_t > 80)
								{
								buf_dados[7] = 't';
								le_corrente_t();
								gravar_cht = 1;
								}
							}
						}
					break;
					}
				#endif
			}
		if (gravar_cht == 1)
			{
			#if (com_relogio == true)
				aux_w1 = read_word_nvr(ds_ptr_cht);
			#else
				aux_w1 = read_word(ee_ptr_cht);
			#endif
			if (aux_w1 > limite_chts)
				{
				aux_w1 = 0;
				}
			aux_l2 = 0;
			aux_l2 = aux_w1;
			aux_l2 = (int32)(aux_l2 * 256);
			aux_l1 = (int32)(aux_l2 + addr_inic_cht);
			
			if (aux_l1 < addr_inic_cht)
				{
				aux_l1 = (int32)(addr_inic_cht);
				}
			aux_b4 = (char)(read_byte_flash(aux_l1));
			if(aux_b4 != 0xff)
				{
				sector_flash_erase(aux_l1);
				}
				
			write_byte_flash(aux_l1++, buf_dados[0]);
			write_byte_flash(aux_l1++, buf_dados[1]);
			write_byte_flash(aux_l1++, buf_dados[2]);
			write_byte_flash(aux_l1++, buf_dados[3]);
			write_byte_flash(aux_l1++, buf_dados[4]);
			write_byte_flash(aux_l1++, buf_dados[5]);
			write_byte_flash(aux_l1++, buf_dados[6]);
			write_byte_flash(aux_l1++, buf_dados[7]);
			for (aux_b4 = 0; aux_b4 < NRO_AMOSTRAS_CHT; aux_b4++)
				{
				write_byte_flash(aux_l1++, (char)(buffer_cht[aux_b4] >> 8));
				write_byte_flash(aux_l1++, (char)(buffer_cht[aux_b4]));
				}
			WRDI(aux_l1);		
			#if (com_relogio == true)
				aux_w1 = read_word_nvr(ds_ptr_cht);
			#else
				aux_w1 = read_word(ee_ptr_cht);
			#endif
			aux_w1++;
			if (aux_w1 > limite_chts)
				{
				aux_l2 = (int32)(addr_inic_cht);
				sector_flash_erase(aux_l2);
				aux_w1 = 0;
				}
			#if (com_relogio == true)
				write_word_nvr(ds_ptr_cht, aux_w1);
			#else
				write_word(ee_ptr_cht, aux_w1);
			#endif
			}
		}
}


void tx_cht_mdb(void)
{
	char x;
	char y;
	char aux_bx;
	char aux_by;
	int32 aux_l1;
		

	aux_l1 = 0;
	aux_l1 = (int32)(addr_regs_modbus);
	aux_l1 = (int32)(aux_l1 - 8000);
	aux_l1 = (int32)(aux_l1 << 8);
	aux_l1 = (int32)(aux_l1 + addr_inic_cht);
	y = nro_pontos_modbus;
	y = y - 4;
	for (x = 0; x < 8 ; x++)
		{
		buf_tx[ptrtx++] = read_byte_flash(aux_l1++); 
   		}
	for (x = 0; x < y ; x++)
		{
		buf_tx[ptrtx++] = read_byte_flash(aux_l1++);
		buf_tx[ptrtx++] = read_byte_flash(aux_l1++);
    	}
}


void apaga_cht(void)
{
	#if (com_relogio == true)
		write_word_nvr(ds_ptr_cht, 0);
	#else
		write_word(ee_ptr_cht, 0);
	#endif
	grava_ocorrencias(reg_apagou_cht);
}


/* fim st_rcht */    
