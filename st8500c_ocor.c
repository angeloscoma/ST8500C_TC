/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_MAIN                                                        *
; Funcao: MODULO PRINCIPAL DE CONTROLE									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */


 
	
void grava_ocorrencias(char codigo)
{

	char buf_dados[TAM_REGS];
		
	write_long(ee_consumo_ati, consumo_ati);
	write_long(ee_consumo_reati, consumo_reati);

	for (aux_b1 = 8; aux_b1 < TAM_REGS; aux_b1++)
		{
		buf_dados[aux_b1] = 0;
		}

	codigo_old = codigo;
	buf_dados[0] = codigo;
	
	if (codigo == reg_falta_energia)
		{
		buf_dados[1] = dia_old;
		buf_dados[2] = mes_old;
		buf_dados[3] = ano_old;
		buf_dados[4] = hora_old;
		buf_dados[5] = minuto_old;
		buf_dados[6] = segundo_old;
		buf_dados[7] = 240;
		}
	else
		{
		buf_dados[1] = dia;
		buf_dados[2] = mes;
		buf_dados[3] = ano;
		buf_dados[4] = hora;
		buf_dados[5] = minuto;
		buf_dados[6] = segundo;
		buf_dados[7] = frequencia;
		}

	if (codigo == reg_reset)
		{
		consumo_ati = read_long(ee_consumo_ati);	
		consumo_reati = read_long(ee_consumo_reati);

		tensao_tri = 0;
		corrente_tri = 0;
		fator_pot = 1024;
	
		dem_ativa = 0;
		dem_reativa = 0;

		dem_ativa_proj = 0;
		dem_reativa_proj = 0;
		}
	buf_dados[8] = (char)(make8(tensao_tri, 1));
	buf_dados[9] = (char)(make8(tensao_tri, 0));
	#if (com_tc == true)
		aux_f1 = (float)(corrente_tri);
		aux_f1 = aux_f1 * mul_tc;
		aux_w1 = (word)(aux_f1);
		buf_dados[10] = (char)(make8(aux_w1, 1));
		buf_dados[11] = (char)(make8(aux_w1, 0));
	#else
		buf_dados[10] = (char)(make8(corrente_tri, 1));
		buf_dados[11] = (char)(make8(corrente_tri, 0));
	#endif
	buf_dados[12] = (char)(make8(fator_pot, 1));
	buf_dados[13] = (char)(make8(fator_pot, 0));
	
	#if (com_tc == true)
		aux_f1 = (float)(dem_ativa_proj);
		aux_f1 = aux_f1 * mul_tc * valor_tp;
		aux_w1 = (word)(aux_f1);
		buf_dados[14] = (char)(make8(aux_w1, 1));
		buf_dados[15] = (char)(make8(aux_w1, 0));

		aux_f1 = (float)(dem_reativa_proj);
		aux_f1 = aux_f1 * mul_tc * valor_tp;
		aux_w1 = (word)(aux_f1);
		buf_dados[16] = (char)(make8(aux_w1, 1));
		buf_dados[17] = (char)(make8(aux_w1, 0));

		aux_f1 = (float)(consumo_ati);
		aux_f1 = aux_f1 * mul_tc * valor_tp;
		aux_l1 = (int32)(aux_f1);
		buf_dados[18] = (char)(make8(aux_l1,3));
		buf_dados[19] = (char)(make8(aux_l1,2));
		buf_dados[20] = (char)(make8(aux_l1,1));
		buf_dados[21] = (char)(make8(aux_l1,0));

		aux_f1 = (float)(consumo_reati);
		aux_f1 = aux_f1 * mul_tc * valor_tp;
		aux_l1 = (int32)(aux_f1);
		buf_dados[22] = (char)(make8(aux_l1,3));
		buf_dados[23] = (char)(make8(aux_l1,2));
		buf_dados[24] = (char)(make8(aux_l1,1));
		buf_dados[26] = (char)(make8(aux_l1,0));

		aux_f1 = (float)(dem_ativa);
		aux_f1 = aux_f1 * mul_tc * valor_tp;
		aux_w1 = (word)(aux_f1);
		buf_dados[26] = (char)(make8(aux_w1, 1));
		buf_dados[27] = (char)(make8(aux_w1, 0));
		
		aux_f1 = (float)(dem_reativa);
		aux_f1 = aux_f1 * mul_tc * valor_tp;
		aux_w1 = (word)(aux_f1);
		buf_dados[28] = (char)(make8(aux_w1, 1));
		buf_dados[29] = (char)(make8(aux_w1, 0));
		
	#else
	
		buf_dados[14] = (char)(make8(dem_ativa_proj, 1));
		buf_dados[15] = (char)(make8(dem_ativa_proj, 0));
		buf_dados[16] = (char)(make8(dem_reativa_proj, 1));
		buf_dados[17] = (char)(make8(dem_reativa_proj, 0));

		buf_dados[18] = (char)(make8(consumo_ati,3));
		buf_dados[19] = (char)(make8(consumo_ati,2));
		buf_dados[20] = (char)(make8(consumo_ati,1));
		buf_dados[21] = (char)(make8(consumo_ati,0));
	
		buf_dados[22] = (char)(make8(consumo_reati,3));
		buf_dados[23] = (char)(make8(consumo_reati,2));
		buf_dados[24] = (char)(make8(consumo_reati,1));
		buf_dados[25] = (char)(make8(consumo_reati,0));

		buf_dados[26] = (char)(make8(dem_ativa, 1));
		buf_dados[27] = (char)(make8(dem_ativa, 0));
		buf_dados[28] = (char)(make8(dem_reativa, 1));
		buf_dados[29] = (char)(make8(dem_reativa, 0));
		
	#endif


	buf_dados[30] = SAIDA2;
	buf_dados[31] = SAIDA3;

	#if (com_relogio == true)
		aux_w1 =  read_word_nvr(ds_ptr_ocor);
	#else
		aux_w1 =  read_word(ee_ptr_rocor);
	#endif
	if (aux_w1 > limite_ocorrencias)
		{
		aux_w1 = 0;
		}
	aux_l2 = (int32)(aux_w1 * TAM_REGS);
	aux_l1 =  aux_l2 + inicio_ocorrencias;

//	antes de salva, verifica se este setor está apagado,caso não esteja, apaga o setor de 4K.
	aux_b1 = read_byte_flash(aux_l1); 
	if (aux_b1 != 0xff)
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
	
	aux_l1 = inicio_ocorrencias;
	
	sector_flash_erase(aux_l1);
	aux_l1 += 4096;
	sector_flash_erase(aux_l1);
	aux_l1 += 4096;
	sector_flash_erase(aux_l1);

	write_word_nvr(ds_ptr_ocor, 0);
	grava_ocorrencias(reg_apagou);
	
	mensagem(2,37);
	delay_ms(2000);

}



void tx_ocor_mdb(void)
{
	char x;
	char y;
	
	
	aux_l1 = (int32)(addr_regs_modbus);
	
	aux_l2 = (int32)(addr_inicio_coleta_ocor);
	
	aux_l2 = (int32)(aux_l1 - aux_l2);

	aux_l1 = inicio_ocorrencias;

	aux_l1 = aux_l1 + (int32)(aux_l2 * TAM_REGS);

	y = (nro_pontos_modbus * 2);
	for (x = 0; x < y ; x++)
		{
		buf_tx[ptrtx++] = read_byte_flash(aux_l1); 
		aux_l1++;
   		}
    	
}



/* fim st_ocor */    
