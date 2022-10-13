/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÿÔNICOS                                  *
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
//void zera_soma_reg(void);
//void soma_reg(void);

#if (funcao_505 == true)
	void inic_tensoes_505(void);
#endif

void grava_registros_505(char);
#if (com_cht == true)
	void apaga_cht(void);
#endif

#if (controlador == true)
	void salva_ocorrencia(char);
#endif


char buf_dados[TAM_REGS];

void monta_txcalend(char codigo)
{
	buf_dados[0] = codigo;
	buf_dados[1] = dia;
	buf_dados[2] = mes;
	buf_dados[3] = ano;
	buf_dados[4] = hora;
	buf_dados[5] = minuto;
	buf_dados[6] = segundo;
}



void grava_registros(char codigo){
	int valor01, valor02;
	short erro_leitura;
	char aux_b1, aux_b2, aux_b4;
	word aux_w1;
	int32 aux_l1, aux_l2;
	
	if (codigo == reg_normal){
		if (time_out_troca_ponteira	 != 0){
			return;
		}
	}

	#if (com_consumo == true)
		if (codigo == reg_consumo){
			monta_txcalend(reg_consumo);
		  	buf_dados[7] = frequencia;
		  	buf_dados[8] = make8(fator_pot,1);
		  	buf_dados[9] = make8(fator_pot,0);
			buf_dados[10] = make8(consumo_ati,3);
			buf_dados[11] = make8(consumo_ati,2);
			buf_dados[12] = make8(consumo_ati,1);
			buf_dados[13] = make8(consumo_ati,0);
			buf_dados[14] = make8(consumo_reati,3);
			buf_dados[15] = make8(consumo_reati,2);
			buf_dados[16] = make8(consumo_reati,1);
			buf_dados[17] = make8(consumo_reati,0);
			buf_dados[18] = make8(consumo_ati_p,3);
			buf_dados[19] = make8(consumo_ati_p,2);
			buf_dados[20] = make8(consumo_ati_p,1);
			buf_dados[21] = make8(consumo_ati_p,0);
			buf_dados[22] = make8(consumo_rea_p,3);
			buf_dados[23] = make8(consumo_rea_p,2);
			buf_dados[24] = make8(consumo_rea_p,1);
			buf_dados[25] = make8(consumo_rea_p,0);
			#if (se_com_flex == true)
		 		 buf_dados[26] = tipo_ponteira;
		 	#else
				buf_dados[26] = posi_tc;
		 	#endif
		  	goto salva_regs;
		}
	#endif

	rotina = 1;

	soma_reg();
	if (nro_soma_reg < 2){
		soma_reg();
	}
	
	buf_dados[0] = codigo;
	
	if (codigo == reg_inicio){
		retardo_alarmes = 60;
		#if com_consumo
			zera_consumo();
		#endif			
		inicializa_regs();
		#if (com_display == true)
			exibiu = 0;
		#endif
	}
	else if (codigo == reg_final){
		#if (com_consumo == true)
			grava_consumo_old();
		#endif
		#if (com_display == true)
			exibiu = 0;
		#endif
		#if (com_menu == true)
			#if (tratar_localizacao == true)
				if (digitou_texto == true){
					monta_txcalend(reg_codigo_local);
					aux_b2 = 8;
					for (aux_b1 = 0; aux_b1 < 15; aux_b1++){
						buf_dados[aux_b2++] = '#';
					}
					aux_b2 = 8;
					for (aux_b1 = 1; aux_b1 < 15; aux_b1++){
						if ((localizacao[aux_b1] != 0) && (localizacao[aux_b1] != '#') && (localizacao[aux_b1] != '[') && (localizacao[aux_b1] != ']')){
							buf_dados[aux_b2++] = localizacao[aux_b1];
						}
						else{
							if ((localizacao[aux_b1] != 0) || (localizacao[aux_b1] != '#')){
								buf_dados[aux_b2] = localizacao[aux_b1];
							}
							else{
								buf_dados[aux_b2] = '#';
							}
							break;
						}
					}
					goto gravar_local;
				}	
			#endif
		#endif
	}
	
volta_apos_gravar_local:	
	
	if (codigo == reg_falta_energia){
		#if (com_relogio == true)
			buf_dados[1] = dia_old;
			buf_dados[2] = mes_old;
			buf_dados[3] = ano_old;
			buf_dados[4] = hora_old;
			buf_dados[5] = minuto_old;
			buf_dados[6] = segundo_old;
		#endif
		goto reg_zero;
	}
	else{
		buf_dados[1] = dia;
		buf_dados[2] = mes;
		buf_dados[3] = ano;
		buf_dados[4] = hora;
		buf_dados[5] = minuto;
		if ((intervalo_reg >= 60) && (codigo == reg_normal)){
			buf_dados[6] = 0;
		}
		else{
			buf_dados[6] = segundo;
		}
	}
	if (codigo == reg_volta_energia){
		goto reg_zero;
	}

	if (codigo != reg_normal){
		if (codigo_old_regs == codigo){
			return;
		}
	}
	codigo_old_regs = codigo;
  	buf_dados[7] = frequencia;
	if (modo_funca == 3){
		buf_dados[8] = (char)((soma_reg_tr / nro_soma_reg) >> 8);
		buf_dados[9] = (char)(soma_reg_tr / nro_soma_reg);
		#if (monofasico == false)
			buf_dados[10] = (char)((soma_reg_ts / nro_soma_reg) >> 8);
			buf_dados[11] = (char)(soma_reg_ts / nro_soma_reg);
			buf_dados[12] = (char)((soma_reg_tt / nro_soma_reg) >> 8);
			buf_dados[13] = (char)(soma_reg_tt / nro_soma_reg);
		#else
			buf_dados[10] = 0;
			buf_dados[11] = 0;
			buf_dados[12] = 0;
			buf_dados[13] = 0;
		#endif
		buf_dados[14] = (char)(valor_tp >> 8);
		buf_dados[15] = (char)(valor_tp);
	
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
	else if (modo_funca == 2){
		if ((codigo == reg_inicio) || (codigo == reg_final)){
			tensao_media_r = ten_nomi * 64;
			#if (monofasico == false)
				tensao_media_s = ten_nomi * 64;
				tensao_media_t = ten_nomi * 64;
			#endif
		}
		else{
			tensao_media_r = (word)(soma_media_tensao_r / conta_media_tensao_r);
			#if (monofasico == false)
				tensao_media_s = (word)(soma_media_tensao_s / conta_media_tensao_s);
				tensao_media_t = (word)(soma_media_tensao_t / conta_media_tensao_t);
			#endif
		}
	
		buf_dados[8] = (char)(tensao_media_r >> 8);
		buf_dados[9] = (char)(tensao_media_r);
		buf_dados[10] = (char)((soma_reg_cr / nro_soma_reg) >> 8);
		buf_dados[11] = (char)(soma_reg_cr / nro_soma_reg);
		buf_dados[12] = (char)(fator_pot_r >> 8);
		buf_dados[13] = (char)(fator_pot_r);
		#if (monofasico == false)
			buf_dados[14] = (char)(tensao_media_s >> 8);
			buf_dados[15] = (char)(tensao_media_s);
			buf_dados[16] = (char)((soma_reg_cs / nro_soma_reg) >> 8);
			buf_dados[17] = (char)(soma_reg_cs / nro_soma_reg);
			buf_dados[18] = (char)(fator_pot_s >> 8);
			buf_dados[19] = (char)(fator_pot_s);
			buf_dados[20] = (char)(tensao_media_t >> 8);
			buf_dados[21] = (char)(tensao_media_t);
			buf_dados[22] = (char)((soma_reg_ct / nro_soma_reg) >> 8);
			buf_dados[23] = (char)(soma_reg_ct / nro_soma_reg);
			buf_dados[24] = (char)(fator_pot_t >> 8);
			buf_dados[25] = (char)(fator_pot_t);
		#else
			buf_dados[14] = 0;
			buf_dados[15] = 0;
			buf_dados[16] = 0;
			buf_dados[17] = 0;
			buf_dados[18] = 4;
			buf_dados[19] = 0;
			buf_dados[20] = 0;
			buf_dados[21] = 0;
			buf_dados[22] = 0;
			buf_dados[23] = 0;
			buf_dados[24] = 4;
			buf_dados[25] = 0;
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
	
		#if (funcao_505 == true)
			inic_tensoes_505();
		#endif
	
	}
	else{
		buf_dados[8] = (char)((soma_reg_tr / nro_soma_reg) >> 8);
		buf_dados[9] = (char)(soma_reg_tr / nro_soma_reg);
		buf_dados[10] = (char)((soma_reg_cr / nro_soma_reg) >> 8);
		buf_dados[11] = (char)(soma_reg_cr / nro_soma_reg);
		buf_dados[12] = (char)(fator_pot_r >> 8);
		buf_dados[13] = (char)(fator_pot_r);
		#if (monofasico == false)
			#if ((com_rep == true) && (GEBRAS == true))
				if (modo_rep == true){
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
					buf_dados[24] = 4;
					buf_dados[25] = 0;
				}
				else{
					buf_dados[14] = (char)((soma_reg_ts / nro_soma_reg) >> 8);
					buf_dados[15] = (char)(soma_reg_ts / nro_soma_reg);
					buf_dados[16] = (char)((soma_reg_cs / nro_soma_reg) >> 8);
					buf_dados[17] = (char)(soma_reg_cs / nro_soma_reg);
					buf_dados[18] = (char)(fator_pot_s >> 8);
					buf_dados[19] = (char)(fator_pot_s);
					buf_dados[20] = (char)((soma_reg_tt / nro_soma_reg) >> 8);
					buf_dados[21] = (char)(soma_reg_tt / nro_soma_reg);
					buf_dados[22] = (char)((soma_reg_ct / nro_soma_reg) >> 8);
					buf_dados[23] = (char)(soma_reg_ct / nro_soma_reg);
					buf_dados[24] = (char)(fator_pot_t >> 8);
					buf_dados[25] = (char)(fator_pot_t);
				}
			#else
				buf_dados[14] = (char)((soma_reg_ts / nro_soma_reg) >> 8);
				buf_dados[15] = (char)(soma_reg_ts / nro_soma_reg);
				buf_dados[16] = (char)((soma_reg_cs / nro_soma_reg) >> 8);
				buf_dados[17] = (char)(soma_reg_cs / nro_soma_reg);
				buf_dados[18] = (char)(fator_pot_s >> 8);
				buf_dados[19] = (char)(fator_pot_s);
				buf_dados[20] = (char)((soma_reg_tt / nro_soma_reg) >> 8);
				buf_dados[21] = (char)(soma_reg_tt / nro_soma_reg);
				buf_dados[22] = (char)((soma_reg_ct / nro_soma_reg) >> 8);
				buf_dados[23] = (char)(soma_reg_ct / nro_soma_reg);
				buf_dados[24] = (char)(fator_pot_t >> 8);
				buf_dados[25] = (char)(fator_pot_t);
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
				buf_dados[24] = 4;
				buf_dados[25] = 0;
			#else
				buf_dados[16] = (char)(pot_ativa_r >> 8);
				buf_dados[17] = (char)(pot_ativa_r);
				buf_dados[18] = (char)(pot_aparente_r >> 8);
				buf_dados[19] = (char)(pot_aparente_r);
				buf_dados[20] = (char)(pot_reativa_r >> 8);
				buf_dados[21] = (char)(pot_reativa_r);
				buf_dados[22] = 0;
				buf_dados[23] = 0;
				buf_dados[24] = 4;
				buf_dados[25] = 0;
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
	}
	zera_soma_reg();
	goto salva_regs;
		
reg_zero:
	for (aux_b1 = 8; aux_b1 < TAM_REGS; aux_b1++){
		buf_dados[aux_b1] = 0;
	}
	buf_dados[7] = 240;
	buf_dados[12] = 4;
	buf_dados[18] = 4;
	buf_dados[24] = 4;
	
	gravar_local:
	salva_regs:

	if (codigo == reg_consumo){
		buf_dados[27] = modo_funca & 0x80;
	}
	else{
		buf_dados[27] = modo_funca;
	}
	buf_dados[28] = ten_nomi;
	if (tipo_ligacao == 1){
		buf_dados[29] = 'D';
	}
	else if (tipo_ligacao == 2){
		buf_dados[29] = 'A';
	}
	else{
		buf_dados[29] = 'Y';
	}

	buf_dados[30] = (char)(valor_tp >> 8);
	buf_dados[31] = (char)(valor_tp);

	aux_w1 = read_word_nvr(ds_ptr_regs);					// Buscamos o ponteiro dentro do banco e o
	aux_b2 = read_byte_nvr(ds_banco_escrita);				// banco de escrita atual.
	aux_l2 = (int32)(nro_registros_por_banco * aux_b2);		// 
	aux_l1 = (int32)(aux_w1 + aux_l2);						// O produto fornece a posição da linha de registro.
	
	if (modo_funca == 3){									// Verificamos o tamanho da linha de registro de
		aux_b1 = TAM_REGS_MODO3;							// acordo com o modo de funcionamento programado.
	}														// 
	else{													// Depois utilizamos este valor para obter o ponteiro
		aux_b1 = TAM_REGS;									// em bytes, ou seja, a posição exata dentro da 
	}														// memória.
	aux_l1 = (int32)(aux_l1 * aux_b1);						// 
		
//	aux_l2 = (int32)(aux_l1);								// 
//	aux_l2 = (int32)(aux_l2 >> 12);							// 
//	aux_l2 = (int32)(aux_l2 << 12);							// 
	
	erro_leitura = 1;										// 
	while(erro_leitura){									// Sistema de consistência: implementado para garantir
		valor01 = read_byte_flash(aux_l1);					// o valor que é lido da memória e em seguida verificar 
		delay_us(2);										// se aquela posição está pronta para gravação.
		valor02 = read_byte_flash(aux_l1);					// 
		if(valor01 == valor02){								// Só é permitida gravação quando o valor atual da posição
			if (valor01 != 0xFF){							// de memória é 0xFF. Caso outro valor seja encontrado é 
				sector_flash_erase(aux_l1);					// obrigatório apagar o setor inteiro.
			}												// 
			else{											// Quando o byte lido (duas vezes) for igual a 0xFF
				erro_leitura = 0;							// zeramos o erro e habilitamos o processo de 
			}												// gravação.
		}													// 
	}														// 

	for (aux_b4 = 0; aux_b4 < aux_b1; aux_b4++){			// Movimentamos o ponteiro de escrita byte a byte.
		write_byte_flash(aux_l1++, buf_dados[aux_b4]);		// Escrevendo os valores já definidos no buffer.
	}
	WRDI(aux_l1);											// Desabilitamos flash para gravação.
	
	aux_w1++;												// Incrementamos o ponteiro de registro.
	if(aux_w1 > nro_registros_por_banco-1){					// Se o limite dentro do banco foi atingido,
		aux_b2++;											// incrementamos o valor do banco de escrita
		aux_w1 = 0;											// e reiniciamos o ponteiro.
		if(aux_b2 > nro_bancos-1){							// Se o limite de bancos foi atingido verificamos
			if(fila_circular == 0){							// o tipo de fila programado, no caso de linear
				memoria_full = 1;							// indicamos a memória esgotada.
			}
			else{											// Em caso de fila circular, apenas reiniciamos
				aux_b2 = 0;									// o contador do banco de escrita.
				memoria_full = 0;							// Indicamos memória livre para gravação.
			}
		}
	}
	write_word_nvr(ds_ptr_regs, aux_w1);					// Salvamos o último valor do ponteiro e do
	write_byte_nvr(ds_banco_escrita,aux_b2);				// banco de escrita.
	
	if (codigo == reg_final){
		if (digitou_texto == true){
			codigo = reg_final;
			buf_dados[0] = codigo;
			existe_local = false;
			digitou_texto = false;
			write_bit(ee_bits_menu2, EE_EXISTE_LOCAL, existe_local);
			write_bit(ee_bits_menu2, EE_DIGITOU_TEXTO, digitou_texto);
			goto volta_apos_gravar_local;
		}
	}
}


// Transmissão dos Registros
void tx_reg_mdb(void){
	char x;
	char y;
	int32 aux_l1, aux_l2;

	aux_b4 = read_byte_nvr(ds_banco_leitura);
	#if ((SST25VF080 == true) || (SST25LF080 == true))
		if (aux_b4 > 16){
	#else
		if (aux_b4 > 8){
	#endif
		aux_b4 = 0;
		write_byte_nvr(ds_banco_leitura, 0);
	}

	aux_l1 = (int32)(addr_regs_modbus - addr_inicio_coleta_regs);
	if (modo_funca == 3){
		aux_l2 = 0;
		aux_l2 = (int32)(nro_registros_por_banco);
		aux_l2 = (int32)(aux_l2 * TAM_REGS_MODO3 * aux_b4);
		aux_l1 = aux_l2 + (int32)(aux_l1 * TAM_REGS_MODO3);
	}
	else{
		aux_l2 = 0;
		aux_l2 = (int32)(nro_registros_por_banco);
		aux_l2 = (int32)(aux_l2 * TAM_REGS * aux_b4);
		aux_l1 = aux_l2 + (int32)(aux_l1 * TAM_REGS);
	}
	y = (nro_pontos_modbus * 2);
	for (x = 0; x < y ; x++){
		buf_tx[ptrtx++] = read_byte_flash(aux_l1++);
	}
}


void apaga_registros(void){
	memoria_full = 0;
	write_byte_nvr(ds_banco_escrita, 0);
	write_byte_nvr(ds_banco_leitura, 0);
	write_word_nvr(ds_ptr_regs, 0);
	write_word_nvr(ds_ptr_regs_high, 0);

//	for (aux_l1 = 0; aux_l1 < 32768; aux_l1++){
//		sector_flash_erase(aux_l1);
//		aux_l1 += 4096;
//	}
	grava_ocorrencias(reg_apagou);
	registro = 0;
	write_byte(ee_prog_time, 0);
	prog_time = 0;
	write_byte(ee_registro, 0);
}

void apaga_memoria(void){
	desprotege_flash(BANCO_0);
	flash_erase(BANCO_0);	
	memoria_full = 0;
	#if ((SST25VF080 == true) || (SST25LF080 == true))
		if (nro_bancos > 4){
			desprotege_flash(BANCO_1);
			flash_erase(BANCO_1);	
		}
		if (nro_bancos > 8){
			desprotege_flash(BANCO_2);
			flash_erase(BANCO_2);	
		}
		if (nro_bancos > 12){
			desprotege_flash(BANCO_3);
			flash_erase(BANCO_3);	
		}
	#else
		if (nro_bancos > 2){
			desprotege_flash(BANCO_1);
			flash_erase(BANCO_1);	
		}
		if (nro_bancos > 4){
			desprotege_flash(BANCO_2);
			flash_erase(BANCO_2);	
		}
		if (nro_bancos > 6){
			desprotege_flash(BANCO_3);
			flash_erase(BANCO_3);	
		}
	#endif

	write_word_nvr(ds_ptr_ocor, 0);
	write_word_nvr(ds_ptr_regs, 0);
	write_word_nvr(ds_ptr_regs_high, 0);
	write_byte_nvr(ds_banco_escrita,0);
	write_byte_nvr(ds_banco_leitura, 0);
	write_word_nvr(ds_ptr_cht, 0);
	write_word_nvr(ds_ptr_ocor, 0);

	grava_ocorrencias(reg_apagou);
	registro = 0;
	write_byte(ee_registro, registro);
	prog_time = 0;
	write_byte(ee_prog_time, prog_time);
	apaga_cht();
}

void wr_falta_energia(void){
	if (registro == 0){
		return;
	}

	delay_ms(100);
	dia_old = rtc_read_nvr(ds_dia_old);
	mes_old = rtc_read_nvr(ds_mes_old);
	ano_old = rtc_read_nvr(ds_ano_old);
	hora_old = rtc_read_nvr(ds_hora_old);
	minuto_old = rtc_read_nvr(ds_minuto_old);
	segundo_old = rtc_read_nvr(ds_segundo_old);
	
	if ((segundo != segundo_old) || (minuto_old != minuto) || (hora_old != hora)){
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
		grava_ocorrencias(reg_falta_energia);
		
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
		grava_ocorrencias(reg_volta_energia);
	}

	#if (funcao_505 == true)
		if (modo_funca == 2){
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
		
			if (dia_old != dia){
				aux_l1 = 86400 - aux_l1;		// soma as diferenÿças entre os 2 dias.
				aux_l1 = aux_l1 + aux_l2;
			}
			else{	
				if (aux_l1 > aux_l2){
					aux_l1 = aux_l1 - aux_l2;
				}
				else if (aux_l1 < aux_l2){
					aux_l1 = aux_l2 - aux_l1;
				}
				else{
					aux_l1 = 0;
				}
			}
		//		nro_faltas_r = (word)(aux_l1);
		//		nro_faltas_s = (word)(aux_l1);
		//		nro_faltas_t = (word)(aux_l1);
		}
	#endif
}
	
void calcula_autonomia(void){					// descobre a memoria disponível e exibe a quantidade disponível.
	if (modo_funca == 2){
		aux_l3 = limite_registros_modo2;
	}
	else{
		aux_l3 = limite_registros;
	}
	
	if(fila_circular == 1){
		aux_w1 = read_word_nvr(ds_ptr_regs);
		aux_w2 = nro_registros_por_banco - aux_w1;
		aux_b1 = (read_byte_nvr(ds_banco_escrita) + 1);
		aux_l2 = ((nro_bancos - aux_b1) * nro_registros_por_banco);
		aux_l1 = aux_w2 + aux_l2;
	}
	else{
		aux_l1 = 0;
	}
	
	if (aux_l1 < (aux_l3 - 2)){
		//	descobre a autonomia do hardware e exibe.
		// 	formula:
		//  nro_dias = (nro de registros * intervalo) / 86400
		//  nro_horas = ((nro de registros * intervalo) - (nro_dias * 86400)) / 3600
		//  nro_minutos = (((nro de registros * intervalo) - (nro_dias * 86400) - (nro_horas * 3600)) / 60
		//  nro segundo = restante
		//  cada banco tera 6144 registros
		//  nro de registros = nro máximo de registros - memoria_em_uso;
		memoria_full = 0;
		aux_l1 = (int32)(aux_l3 - aux_l1);
		aux_l2 = (int32)(intervalo_reg);
		aux_l1 = (int32)(aux_l1 * aux_l2);
		nro_dias = (int16)(aux_l1 / 86400);
		aux_l2 = (int32)(nro_dias * 86400);
		aux_l3 = (int32)(aux_l1 - aux_l2);
		nro_horas = (char)(aux_l3 / 3600);
		aux_l2 = (int32)(nro_horas * 3600);
		aux_w1 = (int16)(aux_l3 - aux_l2);
		nro_minutos = (char)(aux_w1 / 60);
		nro_segundos = (char)(aux_w1 - (int16)(nro_minutos * 60));
	}
}


// Fim st_regs.c
