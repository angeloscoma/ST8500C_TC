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
void zera_soma_reg(void);
void soma_reg(void);

void grava_registros_505(char);
#if (com_cht == true)
	void apaga_cht(void);
#endif




void grava_registros(char codigo)
{

	char buf_dados[TAM_REGS];
	
//	if (registro == 0)
//		{
//		return;
//		}

#if feira
	return;
#endif

	if ((dia > 31) || (mes > 12) || (ano < 3) || (hora > 23) || (minuto > 59) || (segundo > 59))
		{
		le_calend();
		return;
		}


#if (st9600r == true)
	#if (funcao_505 == true)
		if (modo_funca == 2)
			{
			if ((codigo == reg_inicio) || (codigo == reg_final) || (codigo == reg_normal))
				{
				grava_registros_505(codigo);
				}
			else if ((codigo == reg_falta_energia) || (codigo == reg_volta_energia))
				{
			 	grava_ocorrencias(codigo);
				}
			return;
			}
	#endif
#endif

	soma_reg();

	
	buf_dados[0] = codigo;

	if (codigo == reg_inicio)
		{
#if com_consumo
		zera_consumo();
#endif			
		inicializa_regs();
		exibiu = 0;
		}
	else if (codigo == reg_final)
		{
#if com_consumo
		grava_consumo_old();
#endif
		exibiu = 0;
		}

	if (codigo == reg_falta_energia)
		{
		buf_dados[1] = dia_old;
		buf_dados[2] = mes_old;
		buf_dados[3] = ano_old;
		buf_dados[4] = hora_old;
		buf_dados[5] = minuto_old;
		buf_dados[6] = segundo_old;
		goto reg_zero;
		}
	else
        {
		buf_dados[1] = dia;
		buf_dados[2] = mes;
		buf_dados[3] = ano;
		buf_dados[4] = hora;
		buf_dados[5] = minuto;
		buf_dados[6] = segundo;
		}
	if (codigo == reg_volta_energia)
		{
		goto reg_zero;
		}

	if (codigo != reg_normal)
		{
		if (codigo_old_regs == codigo)
			{
			return;
			}
		}
	if (nro_soma_reg < 2)
		{
		soma_reg();
		}
	codigo_old_regs = codigo;
	buf_dados[7] = frequencia;
	if (modo_funca == 3)
		{
	//
		buf_dados[8] = (char)((soma_reg_tr / nro_soma_reg) >> 8);
		buf_dados[9] = (char)(soma_reg_tr / nro_soma_reg);
	//
		buf_dados[10] = (char)((soma_reg_ts / nro_soma_reg) >> 8);
		buf_dados[11] = (char)(soma_reg_ts / nro_soma_reg);
	//
		buf_dados[12] = (char)((soma_reg_tt / nro_soma_reg) >> 8);
		buf_dados[13] = (char)(soma_reg_tt / nro_soma_reg);
	//	
		buf_dados[14] = (char)(valor_tp >> 8);
		buf_dados[15] = (char)(valor_tp);
		}
	else
		{
	//
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
		buf_dados[26] = 0;
		buf_dados[27] = 0;
		buf_dados[28] = 0;
		buf_dados[29] = 0;
		buf_dados[30] = (char)(valor_tp >> 8);
		buf_dados[31] = (char)(valor_tp);
		}

	zera_soma_reg();
	goto salva_regs;
	
reg_zero:
	for (aux_b1 = 8; aux_b1 < TAM_REGS; aux_b1++)
		{
		buf_dados[aux_b1] = 0;
		}
	buf_dados[7] = 240;
	buf_dados[12] = 4;
	buf_dados[18] = 4;
	buf_dados[24] = 4;
	buf_dados[30] = (char)(valor_tp >> 8);
	buf_dados[31] = (char)(valor_tp);

salva_regs:
	if (tipo_ligacao == 0)
		{
		buf_dados[29] = 'Y';
		}
	else
		{
		buf_dados[29] = 'D';
		}

	aux_l1 = 0;
	aux_w1 = read_word_nvr(ds_ptr_regs);
	aux_l1 = (int32)(aux_w1);
	if (modo_funca == 3)
		{
		aux_l1 = (int32)(aux_l1 * TAM_REGS_MODO3);
		}
	else
		{
		aux_l1 = (int32)(aux_l1 * TAM_REGS);
		}
	
//	antes de salva, verifica se este setor está apagado,caso não esteja, apaga o setor de 4K.
	aux_b1 = read_byte_flash(aux_l1); 		// primeira posicao disponível, possui o codigo, sempre != 255
	if (aux_b1 != 0xff)
		{
		sector_flash_erase(aux_l1);
		}
// salva no buffer da flash 
	if (modo_funca == 3)
		{
		aux_b1 = TAM_REGS_MODO3;
		}
	else
		{
		aux_b1 = TAM_REGS;
		}
	for (aux_b4 = 0; aux_b4 < aux_b1; aux_b4++)
		{
		write_byte_flash(aux_l1++, buf_dados[aux_b4]);
		}
	WRDI(aux_l1);	//Desabilita flash para gravação.
	aux_w1++;
	write_word_nvr(ds_ptr_regs, aux_w1);   

	aux_b1 = (char)(aux_w1 / nro_registros_por_banco);
	write_byte_nvr(ds_banco_escrita,aux_b1);

	if (fila_circular == 0)
		{
		if (aux_w1 >= (limite_registros - 3))
			{
			memoria_full = 1;
			aux_l1 = 0;
			aux_w1 = read_word_nvr(ds_ptr_regs);
			aux_l1 = (int32)(aux_w1);
			if (modo_funca == 3)
				{
				aux_l1 = (int32)(aux_l1 * TAM_REGS_MODO3);
				}
			else
				{
				aux_l1 = (int32)(aux_l1 * TAM_REGS);
				}
				
	
//	antes de salva, verifica se este setor está apagado,caso não esteja, apaga o setor de 4K.
			aux_b1 = read_byte_flash(aux_l1); 		// primeira posicao disponível, possui o codigo, sempre != 255
			if (aux_b1 != 0xff)
				{
				sector_flash_erase(aux_l1);
				}
// salva no buffer da flash 
			codigo = reg_final;
			buf_dados[0] = codigo;
			if (modo_funca == 3)
				{
				aux_b1 = TAM_REGS_MODO3;
				}
			else
				{
				aux_b1 = TAM_REGS;
				}
			for (aux_b4 = 0; aux_b4 < aux_b1; aux_b4++)
				{
				write_byte_flash(aux_l1, buf_dados[aux_b4]);
				aux_l1++;
				}
			WRDI(aux_l1);	//Desabilita flash para gravação.
			aux_w1++;
			write_word_nvr(ds_ptr_regs, aux_w1);   
			registro = 0;
			prog_time = 0;
			write_byte(ee_registro, registro);
			write_byte(ee_prog_time, prog_time);
			}
		}
	else
		{
		if (aux_w1 >= (limite_registros - 3 ))
			{
			memoria_full = 0;
			write_byte_nvr(ds_banco_escrita,0);
			write_word_nvr(ds_ptr_regs, 0);   
			sector_flash_erase(0);
			}
		}
}





/*   Transmissão dos registros */
void tx_reg_mdb(void)
{
	char x;
	char y;
	aux_b4 = read_byte_nvr(ds_banco_leitura);
	if (aux_b4 > 8)
		{
		aux_b4 = 0;
		write_byte_nvr(ds_banco_leitura, 0);
		}
	aux_l1 = (int32)(addr_regs_modbus - 1000);
	if (modo_funca == 3)
		{
		aux_l2 = (int32)(nro_registros_por_banco * TAM_REGS_MODO3 * aux_b4);
		aux_l1 = aux_l2 + (int32)(aux_l1 * TAM_REGS_MODO3);
		}
	else
		{
		aux_l2 = (int32)(nro_registros_por_banco * TAM_REGS * aux_b4);
		aux_l1 = aux_l2 + (int32)(aux_l1 * TAM_REGS);
		}
	y = (nro_pontos_modbus * 2);
	for (x = 0; x < y ; x++)
		{
		buf_tx[ptrtx++] = read_byte_flash(aux_l1++); 
    	}
}


void apaga_registros(void)
{
	memoria_full = 0;
	write_byte_nvr(ds_banco_escrita, 0);
	write_byte_nvr(ds_banco_leitura, 0);
	write_word_nvr(ds_ptr_regs, 0);
	for (aux_l1 = 0; aux_l1 < 32768; aux_l1++)
		{
		sector_flash_erase(aux_l1);
		aux_l1 += 4096;
		}
	grava_ocorrencias(reg_apagou);
	registro = 0;
	prog_time = 0;
	write_byte(ee_registro, 0);
	write_byte(ee_prog_time, 0);
	
}



void zera_soma_reg(void)
{
	soma_reg_tr = 0;
	soma_reg_ts = 0;
	soma_reg_tt = 0;
	soma_reg_cr = 0;
	soma_reg_cs = 0;
	soma_reg_ct = 0;
	nro_soma_reg = 0;
}


void soma_reg(void)
{
	if (tipo_ligacao == 0)
		{
		soma_reg_tr = (int32)(soma_reg_tr + tensao_r);
		soma_reg_ts = (int32)(soma_reg_ts + tensao_s);
		soma_reg_tt = (int32)(soma_reg_tt + tensao_t);
		}	
	else
		{
		soma_reg_tr = (int32)(soma_reg_tr + tensao_rs);
		soma_reg_ts = (int32)(soma_reg_ts + tensao_st);
		soma_reg_tt = (int32)(soma_reg_tt + tensao_rt);
		}

	if (modo_funca == 3)
		{
		soma_reg_cr = 0;
		soma_reg_cs = 0;
		soma_reg_ct = 0;
		}
	else
		{
		soma_reg_cr = (int32)(soma_reg_cr + corrente_r);
		soma_reg_cs = (int32)(soma_reg_cs + corrente_s);
		soma_reg_ct = (int32)(soma_reg_ct + corrente_t);
		}

	nro_soma_reg++;
	if (nro_soma_reg == 0)
		{
		zera_soma_reg();
		}
}

void apaga_memoria(void)
{
	desprotege_flash(BANCO_0);
	flash_erase(BANCO_0);	
	if (nro_bancos > 2)
		{
		desprotege_flash(BANCO_1);
		flash_erase(BANCO_1);	
		}
	if (nro_bancos > 4)
		{
		desprotege_flash(BANCO_2);
		flash_erase(BANCO_2);	
		}
	if (nro_bancos > 6)
		{
		desprotege_flash(BANCO_3);
		flash_erase(BANCO_3);	
		}
	write_word_nvr(ds_ptr_ocor, 0);
	write_word_nvr(ds_ptr_regs, 0);
	write_byte_nvr(ds_banco_escrita,0);
	write_byte_nvr(ds_banco_leitura, 0);
	memoria_full = 0;
	grava_ocorrencias(reg_apagou);
	registro = 0;
	prog_time = 0;
	write_byte(ee_registro, registro);
	write_byte(ee_prog_time, prog_time);
#if (com_cht == true)
	apaga_cht();
#endif

}


void wr_falta_energia(void)
{
	delay_ms(100);
	dia_old = rtc_read_nvr(ds_dia_old);
	mes_old = rtc_read_nvr(ds_mes_old);
	ano_old = rtc_read_nvr(ds_ano_old);
	hora_old = rtc_read_nvr(ds_hora_old);
	minuto_old = rtc_read_nvr(ds_minuto_old);
	segundo_old = rtc_read_nvr(ds_segundo_old);

	if (((segundo - segundo_old) > 4) || (minuto_old != minuto) || (hora_old != hora))
		{
		
		zera_soma_reg();
		
		frequencia = 240;
		corrente_r = 0;
		corrente_s = 0;
		corrente_t = 0;
		tensao_r = 0;
		tensao_s = 0;
		tensao_t = 0;
		fator_pot_r = 1024;
		fator_pot_s = 1024;
		fator_pot_t = 1024;
		soma_reg();
		
		grava_registros(reg_falta_energia);
		
		delay_ms(100);
		rtc_get_date();
		rtc_get_time();

		corrente_r = 0;
		corrente_s = 0;
		corrente_t = 0;
		tensao_r = 0;
		tensao_s = 0;
		tensao_t = 0;
		fator_pot_r = 1024;
		fator_pot_s = 1024;
		fator_pot_t = 1024;

		soma_reg();
	
		grava_registros(reg_volta_energia);

		}

#if (funcao_505 == true)
	if (modo_funca == 2)
		{
// calcula o tempo sem energia em segundos e coloca este valor nos contadores de nro_falta_r,_s e_t.

// tempo_atual
		aux_l2 = 0;
		aux_l2 = (int32)(hora);
		aux_w1 = (int16)(minuto);
		aux_l2 = (int32)(aux_l2 * 3600);
		aux_w1 = (int16)(aux_w1 * 60);
		aux_l2 = (int32)(aux_l2 + aux_w1);
		aux_l2 = (int32)(aux_l2 + segundo);		// aux_l2 com o tempo atual.

// tempo_anterior
		aux_l1 = 0;
		aux_l1 = (int32)(hora_old);
		aux_w1 = (int16)(minuto_old);
		aux_l1 = (int32)(aux_l1 * 3600);
		aux_w1 = (int16)(aux_w1 * 60);
		aux_l1 = (int32)(aux_l1 + aux_w1);
		aux_l1 = (int32)(aux_l1 + segundo_old);		// aux_l2 com o tempo atual.

		if (dia_old != dia)
			{
			aux_l1 = 86400 - aux_l1;		// soma as diferenças entre os 2 dias.
			aux_l1 = aux_l1 + aux_l2;
			}
		else
			{	
			if (aux_l1 > aux_l2)
				{
				aux_l1 = aux_l1 - aux_l2;
				}
			else if (aux_l1 < aux_l2)
				{
				aux_l1 = aux_l2 - aux_l1;
				}
			else
				{
				aux_l1 = 0;
				}
			}
	
		nro_faltas_r = (word)(aux_l1);
		nro_faltas_s = (word)(aux_l1);
		nro_faltas_t = (word)(aux_l1);
		}
#endif

}


/* fim st92regs */    
