/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_MAIN                                                        *
; Funcao: MODULO GERENCIADOR DOS DADOS PARA A RESOLUÇÃO 505				 *
; 		Registrador Portátil de Grandezas Elétricas Trifásico            *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 01/08/2003                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/

void grava_registros_505(char);
void inic_tensoes_505(void);
void salva_buffer_505(void);
int32 busca_tensao(int32);
void calcula_indice(char, word);


void totaliza_tensao(void)
{
	if (segundo_old_505 == segundo)
		{
		return;
		}

	if (tipo_ligacao == 0)
		{
		aux_w1 = tensao_r;
		aux_w2 = tensao_s;
		aux_w3 = tensao_t;
		}
	else
		{
		aux_w1 = tensao_rs;
		aux_w2 = tensao_st;
		aux_w3 = tensao_rt;
		}

	if (aux_w1 > TENSAO_FALTA)
		{
		if ((aux_w1 < tensao_minima_r) || (tensao_minima_r == 0))
			{
			tensao_minima_r = aux_w1;
			}
		if (aux_w1 > tensao_maxima_r)
			{
			tensao_maxima_r = aux_w1;
			}
		soma_media_tensao_r += aux_w1;
		conta_media_tensao_r++;
		}

	if (aux_w2 > TENSAO_FALTA)
		{
		if ((aux_w2 < tensao_minima_s) || (tensao_minima_s == 0))
			{
			tensao_minima_s = aux_w2;
			}
		if (aux_w2 > tensao_maxima_s)
			{
			tensao_maxima_s = aux_w2;
			}
		soma_media_tensao_s += aux_w2;
		conta_media_tensao_s++;
		}

	if (aux_w3 > TENSAO_FALTA)
		{
		if ((aux_w3 < tensao_minima_t) || (tensao_minima_t == 0))
			{
			tensao_minima_t = aux_w3;
			}
		if (aux_w3 > tensao_maxima_t)
			{
			tensao_maxima_t = aux_w3;
			}
		soma_media_tensao_t += aux_w3;
		conta_media_tensao_t++;
		}

	segundo_old_505 = segundo;

// obtem a maior/menor e media tensao por fase.
// incrementa contadores por degrau +/- 40%
// incrementa contador de falta de energia.


// definição do buffer de contadores:
// maior, menor e tensao media, calculado automaticamente na geração do relatorio.
// cada fase vai ter um buffer de dimensão 40 words. onde vai ser colocado o contador de cada fase. 
// totalizando 160 bytes de memoria ram para este calculo. o calculo vai ser feito uma fase da cada vez e após registrado na flash.
// a cada variação de 1% em relação a tensão nominal é incrementado um contador correspondente.
// formula para achar o indice dos contadores:
// indice = (100-((tensao_nominal * 100) / tensão lida)) + (NRO_CONTADORES/2);
// se indice for maior que NRO_CONTADORES, então indice é = NRO_CONTADORES.
// exemplo:
//		TN = 127 * 64
//		TL = 120 * 64
//		indice = ((TN * 100)/ TL)  = 100 - (12700 / 120) = 105
//		se indice > 100 então indice = indice - 100
//		se indice < 100 entao indice = 100 - indice.


	if (tensao_r > TENSAO_FALTA)
		{
		calcula_indice(0, tensao_r);	
		}
	else
		{
		nro_faltas_r++;
		}

	if (tensao_s > TENSAO_FALTA)
		{
		calcula_indice(1, tensao_s);		
		}
	else
		{
		nro_faltas_s++;
		}

	if (tensao_t > TENSAO_FALTA)
		{
		calcula_indice(2, tensao_s);
		}
	else
		{
		nro_faltas_t++;
		}
}


void calcula_indice(char bfase, word tensao)
{
	indice = (char)(ten_nomi_l / tensao);

	if (indice > 100)
		{
		indice = indice - 100;
		if (indice > (NRO_CONTADORES/2))
			{
			indice = (NRO_CONTADORES/2)-1;
			}
		indice = (NRO_CONTADORES / 2) - indice;
		}
	else if (indice < 100)
		{
		indice = 100 - indice;
		if (indice > (NRO_CONTADORES/2))
			{
			indice = (NRO_CONTADORES/2)-1;
			}
		else
			{
			indice = (NRO_CONTADORES / 2) + indice;
			}
		}
	else
		{
		indice = (NRO_CONTADORES/2);
		}
	if (indice > NRO_CONTADORES)
		{
		indice = 0;
		}
	contadores_degrau_tensao[bfase][indice]++;

}


// 40 posições por fase a cada 10 minutos totalizando 1008 posições na flash, como a resolução é no minimo por 7 dias 
// cada registros vai ter data, hora, fase e os demais contadores
void grava_registros_505(char codigo)
{

	if (intervalo_reg < 60)
		{
		intervalo_reg = 600;
		write_word(ee_intervalo_reg, 600);
		}
	buf_tmp[0] = codigo;
	buf_tmp[1] = dia;
	buf_tmp[2] = mes;
	buf_tmp[3] = ano;
	buf_tmp[4] = hora;
	buf_tmp[5] = minuto;
	buf_tmp[6] = frequencia;
	buf_tmp[7] = 0;


	tensao_media_r = (word)(soma_media_tensao_r / conta_media_tensao_r);
	tensao_media_s = (word)(soma_media_tensao_s / conta_media_tensao_s);
	tensao_media_t = (word)(soma_media_tensao_t / conta_media_tensao_t);

	if ((codigo == reg_inicio) || (codigo == reg_final))
		{
		inic_tensoes_505();
		tensao_minima_r = ten_nomi;
		tensao_media_r = valor_tp;
		if (tipo_ligacao == 0)
			{
			tensao_maxima_r = 'Y';
			}
		else
			{
			tensao_maxima_r = 'D';
			}
		}	

	aux_l1 = 0;
	aux_w1 = read_word_nvr(ds_ptr_regs);
	aux_l1 = (int32)(aux_w1);
	aux_l1 = (int32)(aux_l1 * TAM_REGS_MODO2);


	salva_buffer_505();

	aux_w1++;
	write_word_nvr(ds_ptr_regs, aux_w1);   

	aux_b1 = (char)(aux_w1 / nro_registros_por_banco2);
	write_byte_nvr(ds_banco_escrita,aux_b1);

	if (fila_circular == 0)
		{
		if (aux_w1 >= (limite_registros_modo2 - 3))
			{
			memoria_full = 1;
			aux_l1 = 0;
			aux_w1 = read_word_nvr(ds_ptr_regs);
			aux_l1 = (int32)(aux_w1);
			aux_l1 = (int32)(aux_l1 * TAM_REGS_MODO2);

			salva_buffer_505();
	
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
		if (aux_w1 >= (limite_registros_modo2 - 3 ))
			{
			memoria_full = 0;
			write_byte_nvr(ds_banco_escrita,0);
			write_word_nvr(ds_ptr_regs, 0);   
			sector_flash_erase(0);
			}
		}

// para teste
/*
	tensao_media_r = (word)(soma_media_tensao_r / conta_media_tensao_r);
	tensao_media_s = (word)(soma_media_tensao_s / conta_media_tensao_s);
	tensao_media_t = (word)(soma_media_tensao_t / conta_media_tensao_t);
	printf("%lu, %lu, %lu, %lu\l\r", tensao_minima_r, tensao_media_r, tensao_maxima_r, nro_faltas_r);
	printf("%lu, %lu, %lu, %lu\l\r", tensao_minima_s, tensao_media_s, tensao_maxima_s, nro_faltas_s);
	printf("%lu, %lu, %lu, %lu\l\r", tensao_minima_t, tensao_media_t, tensao_maxima_t, nro_faltas_t);

	for (aux_b1 = 0 ; aux_b1 < NRO_CONTADORES; aux_b1++)
		{	
		if (contadores_degrau_tensao[0][aux_b1] != 0)
			{
			printf("%u-%lu ;", aux_b1,contadores_degrau_tensao[0][aux_b1]);
			}			
		}	
	printf("\l\r");
	for (aux_b1 = 0 ; aux_b1 < NRO_CONTADORES; aux_b1++)
		{	
		if (contadores_degrau_tensao[1][aux_b1] != 0)
			{
			printf("%u-%lu ;", aux_b1,contadores_degrau_tensao[1][aux_b1]);
			}			
		}	
	printf("\l\r");
	for (aux_b1 = 0 ; aux_b1 < NRO_CONTADORES; aux_b1++)
		{	
		if (contadores_degrau_tensao[2][aux_b1] != 0)
			{
			printf("%u-%lu ;", aux_b1,contadores_degrau_tensao[2][aux_b1]);
			}			
		}	
	printf("\l\r");
*/

	inic_tensoes_505();

}



/*   Transmissão dos registros */
void tx_reg_mdb_505(void)
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
	aux_l2 = (int32)(nro_registros_por_banco2 * TAM_REGS_MODO2 * aux_b4);
	aux_l1 = aux_l2 + (int32)(aux_l1 * TAM_REGS_MODO2);
	y = (nro_pontos_modbus * 2);
	for (x = 0; x < y ; x++)
		{
		buf_tx[ptrtx++] = read_byte_flash(aux_l1++); 
    	}

}

void inic_tensoes_505(void)
{

	soma_media_tensao_r = 0;
	conta_media_tensao_r = 0;
	soma_media_tensao_s = 0;
	conta_media_tensao_s = 0;
	soma_media_tensao_t = 0;
	conta_media_tensao_t = 0;

	tensao_minima_r = 0;
	tensao_maxima_r = 0;
	tensao_media_r = 0;
	nro_faltas_r = 0;

	tensao_minima_s = 0;
	tensao_maxima_s = 0;
	tensao_media_s = 0;
	nro_faltas_s = 0;

	tensao_minima_t = 0;
	tensao_maxima_t = 0;
	tensao_media_t = 0;
	nro_faltas_t = 0;

	for (aux_b1 = 0 ; aux_b1 < NRO_CONTADORES; aux_b1++)
		{	
		contadores_degrau_tensao[0][aux_b1] = 0;
		contadores_degrau_tensao[1][aux_b1] = 0;
		contadores_degrau_tensao[2][aux_b1] = 0;
		}

}


void salva_buffer_505(void)
{
//	antes de salva, verifica se este setor está apagado,caso não esteja, apaga o setor de 4K.
		aux_b1 = read_byte_flash(aux_l1); 		// primeira posicao disponível, possui o codigo, sempre != 255
		if (aux_b1 != 0xff)
			{
			sector_flash_erase(aux_l1);
			}
// salva no buffer da flash 

		for (aux_b4 = 0; aux_b4 < 8; aux_b4++)
			{
			write_byte_flash(aux_l1++, buf_tmp[aux_b4]);
			}


// fase R		
		aux_l1 = write_word_flash(aux_l1, tensao_minima_r);
		aux_l1 = write_word_flash(aux_l1, tensao_media_r);
		aux_l1 = write_word_flash(aux_l1, tensao_maxima_r);
		aux_l1 = write_word_flash(aux_l1, nro_faltas_r);

		for (aux_b4 = 0; aux_b4 < NRO_CONTADORES; aux_b4++)
			{
			aux_l1 = write_word_flash(aux_l1, contadores_degrau_tensao[0][aux_b4]);
			}
// fase S
		aux_l1 = write_word_flash(aux_l1, tensao_minima_s);
		aux_l1 = write_word_flash(aux_l1, tensao_media_s);
		aux_l1 = write_word_flash(aux_l1, tensao_maxima_s);
		aux_l1 = write_word_flash(aux_l1, nro_faltas_s);
		for (aux_b4 = 0; aux_b4 < NRO_CONTADORES; aux_b4++)
			{
			aux_l1 = write_word_flash(aux_l1, contadores_degrau_tensao[1][aux_b4]);
			}
// fase T		
		aux_l1 = write_word_flash(aux_l1, tensao_minima_t);
		aux_l1 = write_word_flash(aux_l1, tensao_media_t);
		aux_l1 = write_word_flash(aux_l1, tensao_maxima_t);
		aux_l1 = write_word_flash(aux_l1, nro_faltas_t);
		for (aux_b4 = 0; aux_b4 < NRO_CONTADORES; aux_b4++)
			{
			aux_l1 = write_word_flash(aux_l1, contadores_degrau_tensao[2][aux_b4]);
			}

		WRDI(aux_l1);	//Desabilita flash para gravação.
}



/* Fim st_505 */
