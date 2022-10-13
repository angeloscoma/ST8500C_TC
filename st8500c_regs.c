/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_MAIN                                                        *
; Funcao: MODULO PRINCIPAL DE CONTROLE									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */


/*
OBSERVACAO, QUANDO FOR IMPLEMENTADO O REGISTRO DE 250 EM 250MS, COLOCAR NOS 4 BIT MSB DO MES, ONDE:
BITS:  76543210
	   ||||||||
	   ||||++++- Bits do mes variam de 1 a 12.
	   |||+----- Não usado, sempre 0.
	   |++------ Bits do intervalo de 250ms dentro do segundo
	   |		 00 - tempo 0
	   |		 01 - tempo 250ms
	   |		 10 - tempo 500ms
	   |		 11 - tempo 750ms
	   +-------- indica registro com intervalo menor que 1 segundo.
*/

void grava_registros(void);
void tx_reg_mdb(void);
void apaga_registros(void);


void grava_registros(char codigo)
{

	char buf_dados[TAM_REGS];

	
	buf_dados[0] = codigo;
	
	
	if (codigo == reg_falta_energia)
		{
		#if (com_relogio == true)
			buf_dados[1] = dia_old;
			buf_dados[2] = mes_old;
			buf_dados[3] = ano_old;
			buf_dados[4] = hora_old;
			buf_dados[5] = minuto_old;
			buf_dados[6] = segundo_old;
		#else
			buf_dados[1] = dia;
			buf_dados[2] = mes;
			buf_dados[3] = ano;
			buf_dados[4] = hora;
			buf_dados[5] = minuto;
			buf_dados[6] = 0;
		#endif
		buf_dados[7] = 240;
		}
	else
       	{
		buf_dados[1] = dia;
		buf_dados[2] = mes;
		buf_dados[3] = ano;
		buf_dados[4] = hora;
		buf_dados[5] = minuto;
		if (codigo == registro_normal)
			{
			buf_dados[6] = 0;
			}
		else
			{
			buf_dados[6] = segundo;
			}
		}


	codigo_old_regs = codigo;
  	buf_dados[7] = frequencia;
  	
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


	aux_l1 = 0;
	#if (com_relogio == true)
		aux_w1 = read_word_nvr(ds_ptr_regs);
	#else
		aux_w1 = read_word(ee_ptr_regs);
	#endif
	aux_l1 = (int32)(aux_w1);
	aux_l1 = (int32)(aux_l1 * TAM_REGS);
		
	//	antes de salva, verifica se este setor está apagado,caso não esteja, apaga o setor de 4K.
	if (read_byte_flash(aux_l1) != 0xff)// primeira posicao disponível, possui o codigo, sempre != 255
		{
		sector_flash_erase(aux_l1);
		}
	// salva no buffer da flash 
	aux_b1 = TAM_REGS;

	for (aux_b4 = 0; aux_b4 < aux_b1; aux_b4++)
		{
	//	antes de salva, verifica se este setor está apagado,caso não esteja, apaga o setor de 4K.
		if (read_byte_flash(aux_l1) != 0xff)	// posicao disponível, possui o codigo, sempre != 255
			{
			sector_flash_erase(aux_l1);
			}
		write_byte_flash(aux_l1++, buf_dados[aux_b4]);
		}
	WRDI(aux_l1);	//Desabilita flash para gravação.
	aux_w1++;
	#if (com_relogio == true)
		write_word_nvr(ds_ptr_regs, aux_w1);   
	#else
		write_word(ee_ptr_regs, aux_w1);   
	#endif
	
	aux_b1 = (char)(aux_w1 / nro_registros_por_banco);
	#if (com_relogio == true)
		write_byte_nvr(ds_banco_escrita,aux_b1);
	#else
		write_byte(ee_banco_escrita,aux_b1);
	#endif
	
	if (aux_w1 >= (limite_registros - 3 ))
		{
		#if (com_relogio == true)
			write_byte_nvr(ds_banco_escrita,0);
			write_word_nvr(ds_ptr_regs, 0);   
		#else
			write_byte(ee_banco_escrita,0);
			write_word(ee_ptr_regs, 0);   
		#endif
		sector_flash_erase(0);
		}
	
	write_long(ee_consumo_ati, consumo_ati);
	write_long(ee_consumo_reati, consumo_reati);
	

}





/*   Transmissão dos registros */
void tx_reg_mdb(void)
{
	
	char x;
	char y;
	#if (com_relogio == true)
		aux_b4 = read_byte_nvr(ds_banco_leitura);
	#else
		aux_b4 = read_byte(ee_banco_leitura);
	#endif
	if (aux_b4 > 8)
		{
		aux_b4 = 0;
		#if (com_relogio == true)
			write_byte_nvr(ds_banco_leitura, 0);
		#else
			write_byte(ee_banco_leitura, 0);
		#endif
		}
	aux_l1 = (int32)(addr_regs_modbus - addr_inicio_coleta_regs);
	aux_l2 = (int32)(nro_registros_por_banco * TAM_REGS * aux_b4);
	aux_l1 = aux_l2 + (int32)(aux_l1 * TAM_REGS);
	y = (nro_pontos_modbus * 2);
	for (x = 0; x < y ; x++)
		{
		buf_tx[ptrtx++] = read_byte_flash(aux_l1++); 
    	}
}


void apaga_registros(void)
{
	#if (com_relogio == true)
		write_byte_nvr(ds_banco_escrita, 0);
		write_byte_nvr(ds_banco_leitura, 0);
		write_word_nvr(ds_ptr_regs, 0);
	#else
		write_byte(ee_banco_escrita, 0);
		write_byte(ee_banco_leitura, 0);
		write_word(ee_ptr_regs, 0);
	#endif
	for (aux_l1 = 0; aux_l1 < 32768; aux_l1++)
		{
		sector_flash_erase(aux_l1);
		aux_l1 += 4096;
		}
	grava_ocorrencias(reg_apagou);
	registro = 0;
	write_byte(ee_prog_time, 0);
	
}



void apaga_memoria(void)
{
	desprotege_flash(BANCO_0);
	flash_erase(BANCO_0);	
	write_word_nvr(ds_ptr_ocor, 0);
	write_word_nvr(ds_ptr_regs, 0);
	write_byte_nvr(ds_banco_escrita,0);
	write_byte_nvr(ds_banco_leitura, 0);
	grava_ocorrencias(reg_apagou);
	registro = 0;
	write_byte(ee_registro, registro);
}


void wr_falta_energia(void)
{
	#if (com_relogio == true)
		delay_ms(100);
		dia_old = rtc_read_nvr(ds_dia_old);
		mes_old = rtc_read_nvr(ds_mes_old);
		ano_old = rtc_read_nvr(ds_ano_old);
		hora_old = rtc_read_nvr(ds_hora_old);
		minuto_old = rtc_read_nvr(ds_minuto_old);
		segundo_old = rtc_read_nvr(ds_segundo_old);
		
		if ((segundo != segundo_old) || (minuto_old != minuto) || (hora_old != hora))
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

		
			grava_registros(reg_falta_energia);
			grava_ocorrencias(reg_falta_energia);
			
			delay_ms(100);
			rtc_get_date();
			rtc_get_time();
		
			grava_registros(reg_volta_energia);
			grava_ocorrencias(reg_volta_energia);
		
			}
	
	#else		
		delay_ms(100);
		grava_registros(reg_falta_energia);
	#endif
}

	
void calcula_autonomia(void)
	{
	}


/* fim st_regs */    
