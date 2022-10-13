/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: st95ROTA                                                        *
; Funcao: MODULO ROTINAS             									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */
  

#define printar_rep false


// flags



#define EM_PONTA			00
#define FORA_DE_PONTA		01

/* Valores dos bits de erro.	*/
#define ER_PULSO_M_18	    0x01
#define ER_PULSO_M_16	    0x02
#define ER_PULSO_M_14	    0x04
#define ER_PULSO_M_12	    0x08

/* Tipos de potencia Reativa */
#define IND			0
#define UNIT        1
#define CAP         2


void trat_rep(void);
char tst_msg_rep(void);
void desmonta_msg_rep(void);
void trat_msg_rep(void);

			
void faz_int_minuto(char);
void fecha_periodo(void);


void tx_erro_rep(char erro){
//	#if (ST8200C == true)
//		if (erro == 6){
//			//mensagem(2,147);
//		}
//	#elif (st8300c == true)
//		if (erro == 6){
//			//mensagem(2,149);
//		}
//	#elif (st8100c == true)
//		if (erro == 6){
//			//mensagem_rola(67, 1);
//		}
//	#endif

	if (fprintar == true){
		#if (printar_rep == true)
			#if (com_485 == true)
				output_high(direcao);
				delay_ms(1);
			#endif	
			
			fprintf(modbus,"\r\n\r\nREP-%u: ", erro);
			fprintf(modbus,"%u, ",buf_rec_tmp[0]);
			fprintf(modbus,"%u, ",buf_rec_tmp[1]);
			fprintf(modbus,"%u, ",buf_rec_tmp[2]);
			fprintf(modbus,"%u, ",buf_rec_tmp[3]);
			fprintf(modbus,"%u, ",buf_rec_tmp[4]);
			fprintf(modbus,"%u, ",buf_rec_tmp[5]);
			fprintf(modbus,"%u, ",buf_rec_tmp[6]);
			fprintf(modbus,"%u, ",buf_rec_tmp[7]);
			fprintf(modbus," CRC:%u, ",buf_rec_tmp[8]);
		
			switch(erro){
				case 1:{
					fprintf(modbus,"\r\nErro pulso 1:%lu, %lu:", puls_c1_rep, puls_c1_rep_ant);
					break;
				}
				case 2:{
					fprintf(modbus,"\r\nErro pulso 2:%lu, %lu:", puls_c2_rep, puls_c2_rep_ant);
					break;
				}
				case 3:
				case 4:{
					fprintf(modbus,"\r\nErro tempo:%u, %lu, %lu:", erro, seg_falt_rep, seg_falt_rep_ant);
					break;
				}
				case 5:{
					fprintf(modbus,"\r\nIntegrou!:%lu, %u, %u", seg_falt_rep, num_int, num_int_ant);
					break;
				}
				case 6:{
					fprintf(modbus,"\r\nErro CRC!:%u, %u", buf_rec_tmp[7], buf_rec_tmp[8]);
					break;
				}
			}
		
			#if (com_485 == true)
				delay_ms(1);
				output_low(direcao);
			#endif	
		#endif
	}
}


void inic_rep(void){
	nbyte_rep = 0;
	rec_rep_ok = false;
}


void trat_rep(void){
	if (rec_rep_ok == true){		//seta o bit quando do rx de 8 bytes
		if (time_out_modo_rep < 5){
			time_out_modo_rep++;			
			time_out_modo_rep++;			
		}
		trat_msg_rep();
		inic_rep();
	}
}
char tst_msg_rep(void){
	buf_rec_tmp[8] = 0;	
	buf_rec_tmp[8] ^= buf_rec_tmp[0];
	buf_rec_tmp[8] ^= buf_rec_tmp[1];
	buf_rec_tmp[8] ^= buf_rec_tmp[2];
	buf_rec_tmp[8] ^= buf_rec_tmp[3];
	buf_rec_tmp[8] ^= buf_rec_tmp[4];
	buf_rec_tmp[8] ^= buf_rec_tmp[5];
	buf_rec_tmp[8] ^= buf_rec_tmp[6];
	
	buf_rec_tmp[8] = ~buf_rec_tmp[8];


	if (buf_rec_tmp[8] == buf_rec_tmp[7]){
		return(true);
	}
	else{
		tx_erro_rep(6);
	}
	return(false);
}
void trat_msg_rep(void){
	buf_rec_tmp[8] = 0;	
	buf_rec_tmp[8] ^= buf_rec_tmp[0];
	buf_rec_tmp[8] ^= buf_rec_tmp[1];
	buf_rec_tmp[8] ^= buf_rec_tmp[2];
	buf_rec_tmp[8] ^= buf_rec_tmp[3];
	buf_rec_tmp[8] ^= buf_rec_tmp[4];
	buf_rec_tmp[8] ^= buf_rec_tmp[5];
	buf_rec_tmp[8] ^= buf_rec_tmp[6];

	buf_rec_tmp[8] = ~buf_rec_tmp[8];
	
	if (buf_rec_tmp[8] != buf_rec_tmp[7]){
		tx_erro_rep(6);
		return;
	}

	fatura_rep = (buf_rec_tmp[1] & 0x10) >> 4;
	if (fatura_rep != fatura_rep_old){
		write_byte(ee_fatura_rep, fatura_rep);
		fatura_rep_old = fatura_rep;
		#if (com_regs == true)
			grava_registros(reg_fatura_rep);
		#endif
	}
	
//	fim_interv_reat_rep = (buf_rec_tmp[1] & 0x20) >> 5;
	tarif_cap_rep       = (buf_rec_tmp[1] & 0x40) >> 6;
	tarif_ind_rep       = (buf_rec_tmp[1] & 0x80) >> 7;
//	posto_tarif_rep     = (buf_rec_tmp[2] & 0x0f);
//	tipo_tarif_rep      = (buf_rec_tmp[2] & 0xf0) >> 4;

	seg_falt_rep = make16((buf_rec_tmp[1] & 0x0f),buf_rec_tmp[0]);
	puls_c1_rep  = make16((buf_rec_tmp[4] & 0x7f),buf_rec_tmp[3]);
	puls_c2_rep  = make16((buf_rec_tmp[6] & 0x7f),buf_rec_tmp[5]);

	if (seg_falt_rep > seg_falt_rep_ant){
		ultimo_pulso_at = ultimo_pulso_at_tmp;
		ultimo_pulso_reat = ultimo_pulso_reat_tmp;
		write_word(ee_ultimo_pulso_at, ultimo_pulso_at);
		write_word(ee_ultimo_pulso_reat, ultimo_pulso_reat);
		ultima_pot_at = pot_ativa_tot;
		ultima_pot_reat = pot_reativa_tot;
		write_word(ee_ultima_pot_at, pot_ativa_tot);
		write_word(ee_ultima_pot_reat, pot_reativa_tot);
		aux_tempo_aciona = 0;
	
		write_long(ee_consumo_ati, consumo_ati);
		write_long(ee_consumo_reati, consumo_reati);
	}
	ultimo_pulso_at_tmp = puls_c1_rep;
	ultimo_pulso_reat_tmp = puls_c2_rep;

	if (tarif_ind_rep_old != tarif_ind_rep){
		time_out_troca_tarifa++;
		if (time_out_troca_tarifa == 10){
			time_out_troca_tarifa = 0;
			fecha_periodo();
			if (tarif_ind_rep == 0){
				#if (st8500c == false)
					for (aux_b1 = 0; aux_b1 < NRO_MAXIMO_BANCOS_CAPACITOR; aux_b1++){
						desligar_banco(aux_b1);
					}
				#endif
			}
		}
	}
	else{
		time_out_troca_tarifa = 0;
	}
	if (time_out_troca_tarifa == 0){
		tarif_ind_rep_old = tarif_ind_rep;
	}

	seg_falt_rep_ant = seg_falt_rep;
	
	switch (posto_tarif_rep){
	    case 0x01:
			periodo = EM_PONTA;
			break;
	    case 0x02:
			periodo = FORA_DE_PONTA;
			break;
	}
		
	aux_w1 =  (word)(900 - seg_falt_rep);
	#if (NRO_INTERVALOS_INTEGRACAO == 15)
		num_int = (unsigned char)(aux_w1 / 60);
	#elif (NRO_INTERVALOS_INTEGRACAO == 30)
		num_int = (unsigned char)(aux_w1 / 30);
//		num_int = (unsigned char)(aux_w1 / 120);		//Edison 22/12/09 - Não desliga com demanda pouco acima de 10%, caso Senai/SC.
	#else
		#error
	#endif
	
// controle de 15 em 15 segundos	
	num_int2 =  (unsigned char)(aux_w1 / 10);
	if (num_int2 != num_int2_ant){
		puls_c1_rep2 = puls_c1_rep;
	    if (puls_c1_rep2 > puls_c1_rep2_ant){
			e_ativa2 = puls_c1_rep2 - puls_c1_rep2_ant;
		}
	    else if (puls_c1_rep2 < puls_c1_rep2_ant){
			e_ativa2 = e_ativa2_ant;
		}
		else{
			e_ativa2 = 0;	//puls_c1_rep;
		}
		
		if (e_ativa2 > e_ativa2_ant){
			aux_w1 = e_ativa2 - e_ativa2_ant;
		}
		else{
			aux_w1 =  e_ativa2_ant - e_ativa2;
		}
			
//		aux_w1 = 0;				// Suspeito: Erro multiplicador 25/02/10.
		aux_f2 = e_ativa2 + aux_w1;
		aux_f2 = (float)(aux_f2 * kkw * 360);
		dem_ativa_proj = (word)(aux_f2);
		
		puls_c1_rep2_ant = puls_c1_rep2;
		e_ativa2_ant = e_ativa2;
		num_int2_ant = num_int2;
	}
		
//  controle de 30 em 30 segundos
	if (num_int != num_int_ant){
		timer_integra = num_int;
		tx_erro_rep(5);
				
	    if (puls_c1_rep > puls_c1_rep_ant){
			e_ativa = puls_c1_rep - puls_c1_rep_ant;
		}
	    else if (puls_c1_rep < puls_c1_rep_ant){
			e_ativa = e_ativa_ant;
		}
		else{
			e_ativa = 0;	//puls_c1_rep;
		}
		e_ativa_ant = e_ativa;
		puls_c1_rep_ant = puls_c1_rep;
			
		if (puls_c2_rep > puls_c2_rep_ant){
			e_reativa = puls_c2_rep - puls_c2_rep_ant;
		}
		else if (puls_c2_rep < puls_c2_rep_ant){
			e_reativa = e_reativa_ant;
		}
		else{
			e_reativa = 0;	//puls_c2_rep;
		}

		e_reativa_ant = e_reativa;
		puls_c2_rep_ant = puls_c2_rep;

		if (fprintar == true){
			#if (printar_rep == true)
				#if (com_485 == true)
					output_high(direcao);
					delay_ms(1);
				#endif	
			
				fprintf(modbus,"\r\nPulsos:%lu/%lu ; %lu/%lu", puls_c1_rep,  ultimo_pulso_at,  puls_c2_rep , ultimo_pulso_reat);
				fprintf(modbus,"\r\nEnergias:%lu(kwh) ;%lu(KVAr)", e_ativa, e_reativa);
				
			
				#if (com_485 == true)
					delay_ms(1);
					output_low(direcao);
				#endif	
			#endif
		}
		faz_int_minuto(num_int);
		num_int_ant = num_int;
	}
}

void faz_int_minuto(char parte){
	int32 extra2;
	int32 extra1; 
	char x;
	
	atualizar = true;

	if (aux_tempo_aciona != 0){
		if (aux_tempo_aciona > 30){
			aux_tempo_aciona -= 30;
		}
		else{
			aux_tempo_aciona = 0;
		}
	}
   
	if (parte > (NRO_INTERVALOS_INTEGRACAO - 1)){
	    parte = 0;
	    return;
	}

    int_ativa[parte] = e_ativa;
	int_reativa[parte] = e_reativa;
	
	if (int_ativa[parte] != 0){
	    int_ativa[0] = e_ativa;
	}

	if (int_reativa[parte] != 0){
		int_reativa[0] = e_reativa;
	}

	for (x = parte; x < NRO_INTERVALOS_INTEGRACAO; x++){
		int_ativa[x] = int_ativa[parte]; 
		int_reativa[x] = int_reativa[parte]; 
	}

	write_word(ee_int_ativa+(parte*2), e_ativa);
	write_word(ee_int_reativa+(parte*2), e_reativa);

	fp_ativa = 0;
	fp_reativa = 0;
	
	for (x = 0; x < NRO_INTERVALOS_INTEGRACAO; x++){
		fp_ativa += (float)(int_ativa[x]); 
		fp_reativa += (float)(int_reativa[x]); 
	}

	fp_ativa = (float)(fp_ativa * kkw);
	
	if (fp_ativa > 1000){
		fp_ativa = 1000;
		saturou_kw = 1;
	}
	else{
		saturou_kw = 0;
	}
	
	fp_reativa = (float)(fp_reativa * kkvar);
	
	if (fp_reativa > 1000){
		fp_reativa = 1000;
		saturou_kvar = 1;
	}
	else{
		saturou_kvar = 0;
	}

	aux_f1 = int_ativa[parte];
	aux_f1 = (float)(aux_f1 * kkw);
	consumo_ati += aux_f1;
	aux_f1 = int_reativa[parte];
	aux_f1 = (float)(aux_f1 * kkvar);
	consumo_reati += aux_f1;
		
	aux_f1 = (float)(fp_ativa);

	aux_f2 = e_ativa;
	#if (NRO_INTERVALOS_INTEGRACAO == 15)
		aux_f2 = (float)(aux_f2 * kkw * 60);
	#elif (NRO_INTERVALOS_INTEGRACAO == 30)
		aux_f2 = (float)(aux_f2 * kkw * 120);			//Suspeito: 25/02/2010
	#else
		#error
	#endif
//	dem_ativa_proj = (word)(aux_f2);

	pot_ativa_tot = (word)(fp_ativa * 4);
	dem_ativa = (word)(fp_ativa * 4);
//	pot_ativa_tot = (word)(fp_ativa);		//Retirada multiplicação para correção do fator de conversão.
//	dem_ativa = (word)(fp_ativa);			//25/02/2010.
	
	aux_f1 = pot_ativa_tot;
	aux_f1 = (float)((aux_f1 * 32));
	aux_f1 = (float)(aux_f1 / 3);
	pot_ativa_r = (word)(aux_f1);
	
	#if (monofasico == false)
		pot_ativa_s = pot_ativa_r;
		pot_ativa_t = pot_ativa_r;
	#endif

	aux_f1 = (float)(fp_reativa);

	aux_f2 = e_reativa;
	#if (NRO_INTERVALOS_INTEGRACAO == 15)
		aux_f2 = (float)(aux_f2 * kkvar * 60);
	#elif (NRO_INTERVALOS_INTEGRACAO == 30)
		aux_f2 = (float)(aux_f2 * kkvar * 120);			//Suspeito: 25/02/2010
	#else
		#error
	#endif

	dem_reativa_proj = (word)(aux_f2);
	pot_reativa_tot = (word)(fp_reativa * 4);
	dem_reativa = (word)(fp_reativa * 4);
//	pot_ativa_tot = (word)(fp_reativa);		//Retirada multiplicação para correção do fator de conversão.
//	dem_ativa = (word)(fp_reativa);			//25/02/2010.

	
	aux_f1 = pot_reativa_tot;
	aux_f1 = (float)((aux_f1 * 32));
	aux_f1 = (float)(aux_f1 / 3);
	pot_reativa_r = (word)(aux_f1);
	#if (monofasico == false)
		pot_reativa_s = pot_reativa_r;
		pot_reativa_t = pot_reativa_r;
	#endif

	// calculo do fator de carga  ==  demanda_media / demanda maxima.
	// aux_l1 saiu com  a soma das demandas e foi feito a media,  
	// multiplicado por 1024 para dar maior que 1.
	// aux_l2 tem o maior valor de demanda.
	aux_l1 = 0;
	aux_l2 = 0;
	for (x = 0; x < NRO_INTERVALOS_INTEGRACAO; x++) {
		aux_l1 += int_ativa[x]; 
		if (aux_l2 < int_ativa[x]){
			aux_l2 = int_ativa[x];
		}
	}
	aux_l1 = ((aux_l1 * 1024)/NRO_INTERVALOS_INTEGRACAO);
	fator_carga = aux_l1 / aux_l2;

	// calculo do  fator de demanda.  = demanda maxima / carga instalada(carga_programada)
	aux_f2 = (float)(aux_l2);

	#if (NRO_INTERVALOS_INTEGRACAO == 15)
		aux_f2 = (float)(aux_f2 * kkw * 60 * 1024);
	#elif (NRO_INTERVALOS_INTEGRACAO == 30)
		aux_f2 = (float)(aux_f2 * kkw * 120 * 1024);
	#else
		#error
	#endif
	fator_demanda = (word)(aux_f2 /  carga_programada);
	

	if (fprintar == true)
		{
		#if (printar_rep == true)
			#if (com_485 == true)
				output_high(direcao);
				delay_ms(1);
			#endif	
	
			fprintf(modbus,"\r\nAtiva:");
			for (x = 0; x < NRO_INTERVALOS_INTEGRACAO; x++) 
				{
				fprintf(modbus,"%lu, ", int_ativa[x]);
				}
			fprintf(modbus,"\r\nReAtiva:");
			for (x = 0; x < NRO_INTERVALOS_INTEGRACAO; x++) 
				{
				fprintf(modbus,"%lu, ", int_reativa[x]);
				}
			fprintf(modbus,"\r\nPotencias:%f(kwh)/%lu ;%f(KVAr), Sinal:%u", fp_ativa, pot_ativa_r, fp_reativa, tipo_fp);
			aux_f1 = pot_ativa_r;
			aux_f1 = aux_f1 / 32;
			fprintf(modbus,"\r\nPotencias:%f(kwh)", aux_f1);
			aux_f1 = pot_reativa_r;
			aux_f1 = aux_f1 / 32;
			fprintf(modbus," ;%f(kvarh)", aux_f1);


			#if (com_485 == true)
				delay_ms(1);
				output_low(direcao);
			#endif	
		#endif
	

		#if (com_485 == true)
			output_high(direcao);
			delay_ms(1);
		#endif	
	

		#if (com_485 == true)
			delay_ms(1);
			output_low(direcao);
		#endif	
		}
}


	// A cada 15 min. faz o fechamento (parte = 14) que pode ser chamado pelo
	// pulso de integracao externo ou pela passagem do temporizador interno
	// (timer_integra) que subt. o ext. no caso da falta ou perda de sinal.
	// Rotinas que sao executadas a cada 15 minutos no fechamento do intervalo
	// de integracao.
void fecha_periodo(void){
	char x;
	
	for (x = 0; x < NRO_INTERVALOS_INTEGRACAO; x++){
		int_ativa[x] = 0;             			// zera os acumuladores de pulsos
		write_word(ee_int_ativa+(x*2), 0);
		
		int_reativa[x] = 0;
		write_word(ee_int_reativa+(x*2), 0);
	}
}
void recupera_rep(void){
	for (aux_b1 = 0; aux_b1 < NRO_INTERVALOS_INTEGRACAO; aux_b1++){
		int_ativa[aux_b1] = read_word(ee_int_ativa+(aux_b1*2));
		int_reativa[aux_b1] = read_word(ee_int_reativa+(aux_b1*2));
	}
	nbyte_rep = 0;
 	nbit_rep = 0;
	start_rep = 0;
	time_out_rep = 2;
}

void zera_rep(void){
	for (aux_b1 = 0; aux_b1 < NRO_INTERVALOS_INTEGRACAO; aux_b1++){
		write_word(ee_int_ativa+(aux_b1*2), 0);
		write_word(ee_int_reativa+(aux_b1*2), 0);
	}
	recupera_rep();
	ultimo_pulso_at = 0;
	ultimo_pulso_reat = 0;
	ultima_pot_at = 0;
	ultima_pot_reat = 0;
}
void zera_demandas_rep(void){
	
	dem_ativa = 0;
	pot_ativa_tot = 0;
	dem_ativa_proj = 0;

	dem_reativa = 0;
	pot_reativa_tot = 0;
	dem_reativa_proj = 0;
	
	dem_maxima_aparente = 0;
	dem_maxima_ativa = 0;
	dem_media_ativa = 0;
	dem_media_aparente = 0;

	dem_ativa = 0;
	dem_reativa = 0;
}

void zera_consumo_rep(void){
	write_long(ee_consumo_ati, 0);
	write_long(ee_consumo_reati, 0);
	write_long(ee_consumo_ati_ant, 0);
	write_long(ee_consumo_reati_ant, 0);

	dem_maxima_aparente_ant = 0;
	dem_maxima_ativa_ant = 0;
	
 	write_word(ee_dem_maxima_aparente_ant,0);
 	write_word(ee_dem_maxima_ativa_ant,0);

	zera_demandas_rep();
	zera_rep();
	fecha_periodo();    /* rotinas que sao executadas a cada 15 minutos */
	inicializa_8500c();
}
