/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ROTINAS                               	                     *
; Funcao: MODULO DE ROTINAS DE COMUNICACAO								 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 01/08/2003                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/

void valida_max_kw(void){	
	char aux_b1;
	word aux_w1;
	
	max_kw = read_word(ee_max_kw);
	aux_w1 = 0;
	for (aux_b1 = 0; aux_b1 < nro_cargas; aux_b1++){
		aux_w1 += carga[aux_b1];
	}
	carga_instalada = aux_w1;
	if (max_kw > aux_w1){
		max_kw = 100 * NRO_MAXIMO_CARGAS;
	}
	for (aux_b1 = 0; aux_b1 < nro_cargas; aux_b1++){
		if (max_kw < carga[aux_b1]){
			max_kw = carga[aux_b1];
		}
	}
		
	menor_carga = carga_instalada;
	for (aux_b1 = 0; aux_b1 < nro_cargas; aux_b1++){
		if (menor_carga > carga[aux_b1]){
			menor_carga = carga[aux_b1];
		}
	}
}		
		
void vali_nro_cargas(void){
    if ((nro_cargas == 0) || (nro_cargas > NRO_MAXIMO_CARGAS)){
   	   	nro_cargas = read_byte(ee_nro_cargas);
    	if ((nro_cargas == 0) || (nro_cargas > NRO_MAXIMO_CARGAS)){
	 	   	nro_cargas = NRO_MAXIMO_CARGAS;
			write_byte(ee_nro_cargas, NRO_MAXIMO_CARGAS);
	   	}
	}
}

void apaga_tempos(void){					
	for (data1 = 0; data1 < NRO_MAXIMO_CARGAS; data1++){
		minuteiro[data1] = 0;
		horimetro[data1] = 0;
		acionamentos[data1] = 0;
		write_byte(ee_minuteiro + data1, 0);
		write_word(ee_horimetro + (data1 * 2), 0);
		write_word(ee_acionamentos + (data1 * 2), 0);
	}
}
void recupera_tempos_acionamentos(void){
	for (aux_b1 = 0; aux_b1 < NRO_MAXIMO_CARGAS; aux_b1++){
		minuteiro[aux_b1] = read_byte(ee_minuteiro + aux_b1);
		horimetro[aux_b1] = read_word(ee_horimetro + (aux_b1 * 2));
		acionamentos[aux_b1] = read_word(ee_acionamentos + (aux_b1 * 2));
		tempo_repouso[aux_b1] = read_byte(ee_tempo_repouso_1 + aux_b1);
		aux_tempo_repouso[aux_b1] = tempo_repouso[aux_b1];
	}
}

void salva_contadores(void){
	char aux_b1;
	for (aux_b1 = 0; aux_b1 < NRO_MAXIMO_CARGAS; aux_b1++){
		write_byte(ee_minuteiro + aux_b1, minuteiro[aux_b1]);
		write_word(ee_horimetro + (aux_b1 * 2), horimetro[aux_b1]);
		write_word(ee_acionamentos + (aux_b1 * 2), acionamentos[aux_b1]);
	}
}

void trata_saidas(void){
	output_01 = LED;
	output_low(CSIO1);
	output_d(output_01);
	output_high(CSIO1);
		
	output_low(CSIO4);
	output_d(0b00010000);
	output_high(CSIO4);

	if (modo_saidas == MODO_INVERTIDO){
		output_01 = saida2;
		output_01 = ~output_01;
		output_low(CSIO2);
		output_d(output_01);
		output_high(CSIO2);
		
		output_01 = saida3;
		output_01 = ~output_01;
		output_low(CSIO3);
		output_d(output_01);
		output_high(CSIO3);
	}
	else{	
		output_01 = saida2;
		output_low(CSIO2);
		output_d(output_01);
		output_high(CSIO2);
		
		output_01 = saida3;
		output_low(CSIO3);
		output_d(output_01);
		output_high(CSIO3);
	}
}				

void trata_desliga_ten_a(void){
	if (com_des_ten_a != 0){		/* SE PROGRAMACAO DIFERENTE DE ZERO COM CRITICA */
		if ((tipo_ligacao == 0) || (tipo_ligacao == 2)){
			aux_w1 = ten_nomi;
		}
		else{
			aux_w1 = (int16)(ten_nomi * 1.7320508);
		}
// valor para tensao acima da minima			
		aux_w2 = aux_w1;
		aux_w2 = (int16)(aux_w2 << 6);
// valor para tensao abaixo da minima		
		aux_w1 = 1 + (int16)((aux_w1 * com_des_ten_a)/100);
		aux_w1 = (int16)((aux_w1 + aux_w2) * 64);
		if ((tensao_r > aux_w1) || (tensao_s > aux_w1) || (tensao_t > aux_w1)){
			des_ten_a = true;
		}
		else if ((tensao_r < aux_w2) && (tensao_s < aux_w2) && (tensao_t < aux_w2)){
			des_ten_a = false;
		}
	}
	else{
		des_ten_a = false;
	}
}

void ligar_carga(char carga){
	char saida;

	ligou_carga = false;
	if (aux_tempo_repouso[carga] == 0){
		switch (carga){
			case 0:{
				if (TRIAC_1 == false){
					TRIAC_1 = true;
					ligou_carga = true;
				}
				break;
			}
			case 1:{
				if (TRIAC_2 == false){
					TRIAC_2 = true;
					ligou_carga = true;
				}
				break;
			}
			case 2:{
				if (TRIAC_3 == false){
					TRIAC_3 = true;
					ligou_carga = true;
				}
				break;
			}
			case 3:{
				if (TRIAC_4 == false){
					TRIAC_4 = true;
					ligou_carga = true;
				}
				break;
			}
			case 4:{
				if (TRIAC_5 == false){
					TRIAC_5 = true;
					ligou_carga = true;
				}
				break;
			}
			case 5:{
				if (TRIAC_6 == false){
					TRIAC_6 = true;
					ligou_carga = true;
				}
				break;
			}
			case 6:{
				if (TRIAC_7 == false){
					TRIAC_7 = true;
					ligou_carga = true;
				}
				break;
			}
			case 7:{
				if (TRIAC_8 == false){
					TRIAC_8 = true;
					ligou_carga = true;
				}
				break;
			}
			case 8:{
				if (TRIAC_9 == false){
					TRIAC_9 = true;
					ligou_carga = true;
				}
				break;
			}
			case 9:{
				if (TRIAC_10 == false){
					TRIAC_10 = true;
					ligou_carga = true;
				}
				break;
			}
			case 10:{
				if (TRIAC_11 == false){
					TRIAC_11 = true;
					ligou_carga = true;
				}
				break;
			}
			case 11:{
				if (TRIAC_12 == false){
					TRIAC_12 = true;
					ligou_carga = true;
				}
				break;
			}
			case 12:{
				if (TRIAC_13 == false){
					TRIAC_13 = true;
					ligou_carga = true;
				}
				break;
			}
			case 13:{
				if (TRIAC_14 == false){
					TRIAC_14 = true;
					ligou_carga = true;
				}
				break;
			}
			case 14:{
				if (TRIAC_15 == false){
					TRIAC_15 = true;
					ligou_carga = true;
				}
				break;
			}
			case 15:{
				if (TRIAC_16 == false){
					TRIAC_16 = true;
					ligou_carga = true;
				}
				break;
			}
		}
	}
	if (ligou_carga == true){
		aux_tempo_aciona = tempo_aciona;
		ultimo_tempo_aciona = tempo_aciona;
		acionamentos[carga]++;
		ptr_aciona = carga;
		carga_acionada[carga] = true;
		saida = SAIDA2;
		write_byte(ee_saida2, saida);
		saida = SAIDA3;
		write_byte(ee_saida3, saida);
	}
}

void desligar_carga(char carga){
	char saida;
	desligou_carga = false;

	switch (carga){
		case 0:{
			if (TRIAC_1 == true){
				TRIAC_1 = false;
				desligou_carga = true;
			}
			break;
		}
		case 1:{
			if (TRIAC_2 == true){
				TRIAC_2 = false;
				desligou_carga = true;
			}
			break;
		}
		case 2:{
			if (TRIAC_3 == true){
				TRIAC_3 = false;
				desligou_carga = true;
			}
			break;
		}
		case 3:{
			if (TRIAC_4 == true){
				TRIAC_4 = false;
				desligou_carga = true;
			}
			break;
		}
		case 4:{
			if (TRIAC_5 == true){
				TRIAC_5 = false;
				desligou_carga = true;
			}
			break;
		}
		case 5:{
			if (TRIAC_6 == true){
				TRIAC_6 = false;
				desligou_carga = true;
			}
			break;
		}
		case 6:{
			if (TRIAC_7 == true){
				TRIAC_7 = false;
				desligou_carga = true;
			}
			break;
		}
		case 7:{
			if (TRIAC_8 == true){
				TRIAC_8 = false;
				desligou_carga = true;
			}
			break;
		}
		case 8:{
			if (TRIAC_9 == true){
				TRIAC_9 = false;
				desligou_carga = true;
			}
			break;
		}
		case 9:{
			if (TRIAC_10 == true){
				TRIAC_10 = false;
				desligou_carga = true;
			}
			break;
		}
		case 10:{
			if (TRIAC_11 == true){
				TRIAC_11 = false;
				desligou_carga = true;
			}
			break;
		}
		case 11:{
			if (TRIAC_12 == true){
				TRIAC_12 = false;
				desligou_carga = true;
			}
			break;
		}
		case 12:{
			if (TRIAC_13 == true){
				TRIAC_13 = false;
				desligou_carga = true;
			}
			break;
		}
		case 13:{
			if (TRIAC_14 == true){
				TRIAC_14 = false;
				desligou_carga = true;
			}
			break;
		}
		case 14:{
			if (TRIAC_15 == true){
				TRIAC_15 = false;
				desligou_carga = true;
			}
			break;
		}
		case 15:{
			if (TRIAC_16 == true){
				TRIAC_16 = false;
				desligou_carga = true;
			}
			break;
		}
	}

	if (desligou_carga == true){
		aux_tempo_aciona = tempo_desaciona;
		ultimo_tempo_aciona = tempo_desaciona;
		aux_tempo_repouso[carga] = tempo_repouso[carga];
		ptr_desaciona = carga;
		carga_acionada[carga] = false;
		saida = SAIDA2;
		write_byte(ee_saida2, saida);
		saida = SAIDA3;
		write_byte(ee_saida3, saida);
	}	
}

void trata_tempos_aciona_repouso(void){
   	for (aux_b1 = 0; aux_b1 < nro_cargas; aux_b1++){
		if (aux_tempo_repouso[aux_b1] > 0){
			if (aux_tempo_repouso[aux_b1] > tempo_repouso[aux_b1]){
				aux_tempo_repouso[aux_b1] = tempo_repouso[aux_b1];
			}
			else{
				aux_tempo_repouso[aux_b1]--;
			}
		}
	}
		
	if (aux_tempo_aciona != 0){
		aux_tempo_aciona--;
	}
}

// saida2 com os primeiros 8 cargas
// Saida3 com os ultimos 8 cargas
void trata_segundeiro(void){
	for (aux_b1 = 0; aux_b1 < nro_cargas; aux_b1++){
		if (carga_acionada[aux_b1] == 1){
			segundeiro[aux_b1]++;
			if (segundeiro[aux_b1] > 59){
				segundeiro[aux_b1] = 0;
				minuteiro[aux_b1]++;
				if (minuteiro[aux_b1]>59){
					minuteiro[aux_b1] = 0;
					horimetro[aux_b1]++;
					write_byte(ee_minuteiro + aux_b1, minuteiro[aux_b1]);
					write_word(ee_horimetro + (aux_b1* 2), horimetro[aux_b1]);
					write_word(ee_acionamentos + (aux_b1 * 2), acionamentos[aux_b1]);
				}
			}
		}
	}
}

char trata_desligamentos(char carga){
	desligou_carga = false;
	if (carga_acionada[carga] == true){
		desligar_carga(carga);
	}
	if (desligou_carga == true){
		aux_tempo_aciona = tempo_desaciona;
		ultimo_tempo_aciona = tempo_desaciona;
		return(carga);
	}
	else{
		return(0xff);
	}
}
char trata_acionamentos(char carga){
	ligou_carga = false;
	if (carga_disponivel[carga] == true){
		ligar_carga(carga);
	}
	if (ligou_carga == true){
		aux_tempo_aciona = tempo_aciona;
		ultimo_tempo_aciona = tempo_aciona;
		return(carga);
	}
	else{
		return(0xff);
	}
}

void ve_carga_disponivel(void){
	char aux_b1;
	for (aux_b1 = 0; aux_b1 < nro_cargas; aux_b1++){
		if (carga[aux_b1] > 0){
			if (carga_acionada[aux_b1] == false){
				carga_disponivel[aux_b1] = true;
			}
			else if (carga_acionada[aux_b1] == true){
				carga_disponivel[aux_b1] = false;
			}
			else{
				carga_disponivel[aux_b1] = true;
				desligar_carga(aux_b1);
			}
		}
		else{
			carga_disponivel[aux_b1] = false;
		}
	}
}

void busca_demanda_contratada(void){
	char periodo_fatura_old;
	int32 tempo_ponta, tempo_fora, tempo_atual;
	
	periodo_fatura_old = periodo_fatura;
	periodo_fatura = 0;
	
	aux_l1 = (int32)(hora);
	aux_l2 = (int32)(minuto);
	aux_l1 = aux_l1 * 3600;
	aux_l2 = aux_l2 * 60;
	tempo_atual = aux_l1 + aux_l2;
				
	aux_l1 = (int32)(hora_ponta);
	aux_l2 = (int32)(minuto_ponta);
	aux_l1 = aux_l1 * 3600;
	aux_l2 = aux_l2 * 60;
	tempo_ponta = aux_l1 + aux_l2;

	aux_l1 = (int32)(hora_final_ponta);
	aux_l2 = (int32)(minuto_final_ponta);
	aux_l1 = aux_l1 * 3600;
	aux_l2 = aux_l2 * 60;
	tempo_fora = aux_l1 + aux_l2;
			
	if (tempo_atual >= tempo_ponta){
		if (tempo_atual <= tempo_fora){
			periodo_fatura = PERIODO_PONTA;
		}
		else{
			periodo_fatura = PERIODO_FORA_PONTA;
		}
	}
	else{
		periodo_fatura = PERIODO_FORA_PONTA;
	}

	switch(periodo_fatura){
		case PERIODO_PONTA:{
			dem_contratada = dem_cont_ponta[mes - 1];
			if (periodo_fatura_old != periodo_fatura){
				grava_ocorrencias(reg_trocou_periodo_fatura_periodo_ponta);
			}
			break;
		} 
		case PERIODO_FORA_PONTA:{
			dem_contratada = dem_cont_fora_ponta[mes - 1];
			if (periodo_fatura_old != periodo_fatura){
				grava_ocorrencias(reg_trocou_periodo_fatura_periodo_fora_ponta);
			}
			break;
		} 
		default:{
			dem_contratada = dem_cont_ponta[mes - 1];
		}
	}
}


void ve_carga_acionada(void){
	dem_acionada = 0;
	for (aux_b1=0; aux_b1 < nro_cargas; aux_b1++){
		if (carga_acionada[aux_b1] == true){
			dem_acionada += carga[aux_b1];
		}
		else if (carga_acionada[aux_b1] == false){
		}	
		else{
			carga_acionada[aux_b1] = false;
			desligar_carga(aux_b1);
		}
	}
}

void st8500_decisao(void){
	char qcarga;
	char ligar, desligar;
	word acionamento_tmp;
	word carga_necessaria;
	word dem_contratada_plus;
	word dem_contratada_liga;
	word dem_ativa_decide;
	word dem_ativa_proj_decide;
	int32 tempo_liga, tempo_desliga, tempo_atual;
	
	ligar = false;
	desligar = false;
	
	acionamento_tmp = 0;
	if (aux_tempo_aciona == 0){
		aux_tempo_aciona = ultimo_tempo_aciona;
		for (qcarga = 0; qcarga < nro_cargas; qcarga++){
			if (carga[qcarga] == 0){
				desligar_carga(qcarga);
			}
		}
			
		ve_carga_acionada();
		#if (com_tc == true)
			time_out_modo_rep = 5;
		#endif
		if (time_out_modo_rep == 0){
			if (dem_acionada < dem_contratada){
				for (qcarga = 0; qcarga < nro_cargas; qcarga++){
					if (carga[qcarga] > 0){
						if (forma_controle[qcarga] == 'D'){
							if (carga_acionada[qcarga] != true){
								if (aux_tempo_repouso[qcarga] == 0){
									ligar_carga(qcarga);
									acionamento_tmp += carga[qcarga];
									if ((acionamento_tmp >= max_kw) || (acionamento_tmp > carga_necessaria)){
										break;
									}
								}
								else{
									break;
								}
							}
						}
					}
				}
			}
		}
		else{
			#if (instantaneo==false)
				if (timer_integra < 10){
					aux_l1 = (int32)(dem_contratada);
					aux_l1 = (int32)((aux_l1 * 110) / 100);		// Edison 22/12/09
					dem_contratada_plus = (word)(aux_l1);
					aux_l1 = (int32)(dem_contratada);
					aux_l1 = (int32)((aux_l1 * 100) / 100);
					dem_contratada_liga = (word)(aux_l1);
				}
				else if (timer_integra < 20){
					aux_l1 = (int32)(dem_contratada);
					aux_l1 = (int32)((aux_l1 * 105) / 100);		// Edison 22/12/09
					dem_contratada_plus = (word)(aux_l1);
					aux_l1 = (int32)(dem_contratada);
					aux_l1 = (int32)((aux_l1 * 100) / 100);
					dem_contratada_liga = (word)(aux_l1);
				}
				else{
					aux_l1 = (int32)(dem_contratada);
					aux_l1 = (int32)((aux_l1 * 100) / 100);		// Edison 22/12/09
					dem_contratada_plus = (word)(aux_l1);
					aux_l1 = (int32)(dem_contratada);
					aux_l1 = (int32)((aux_l1 * 100) / 100);
					dem_contratada_liga = (word)(aux_l1);
				}
			#else												// para controle de carga sem intervalo de integração.
					aux_l1 = (int32)(dem_contratada);
					aux_l1 = (int32)((aux_l1 * 100) / 100);		// Edison 22/12/09
					dem_contratada_plus = (word)(aux_l1);
					aux_l1 = (int32)(dem_contratada);
					aux_l1 = (int32)((aux_l1 * 100) / 100);
					dem_contratada_liga = (word)(aux_l1);
			#endif
	
	//		if ((dem_acionada < dem_contratada) && (dem_ativa_proj < dem_contratada))
			#if (com_tc  == true)
				aux_f1 = dem_ativa;
				dem_ativa_decide = (word)(aux_f1 * mul_tc);
				aux_f1 = dem_ativa_proj;
				dem_ativa_proj_decide = (word)(aux_f1 * mul_tc);
			#endif
			#if (com_rep == true)
				dem_ativa_decide = dem_ativa;
				dem_ativa_proj_decide = dem_ativa_proj;
			#endif

//			fprintf(modbus,"DA:%lu ; DP:%lu ; DM%lu ;", dem_ativa, dem_ativa_proj, dem_media_ativa);
//			fprintf(modbus,"DAQ:%lu ; DPQ:%lu ;", dem_ativa_decide, dem_ativa_proj_decide);

//			fprintf(modbus,"\r\n");
			
			if (dem_ativa_decide != dem_contratada){
				if ((dem_ativa_proj_decide < dem_contratada_liga)){
					carga_necessaria = dem_contratada_liga - dem_ativa_proj_decide;
					ligar = true;
					desligar = false;
				}
				else{
					if (dem_ativa_proj_decide > dem_contratada_plus){
						carga_necessaria = dem_ativa_proj_decide - dem_contratada_plus;
						ligar = false;
						desligar = true;
					}
					else{
						desligar = false;
						ligar = false;
					}
				}
		
				if (ligar == true){
					if (tipo_controle_demanda == CONTROLE_FILO){
						for (qcarga = 0; qcarga < nro_cargas; qcarga++){
							if (carga[qcarga] > 0){
								if (forma_controle[qcarga] == 'D'){
									if (carga_acionada[qcarga] != true){
										if (aux_tempo_repouso[qcarga] == 0){
											ligar_carga(qcarga);
											acionamento_tmp += carga[qcarga];
											if ((acionamento_tmp >= max_kw) || (acionamento_tmp > carga_necessaria)){
												break;
											}
										}
										else{
											break;
										}
									}
								}
							}
						}
					}
					else if (tipo_controle_demanda == CONTROLE_FILA_CIRCULAR){
						if (ptr_aciona >= (nro_cargas-1)){
							ptr_aciona = 0;
						}
						for (qcarga = ptr_aciona; qcarga < nro_cargas; qcarga++){
							if (carga[qcarga] > 0){
								if (forma_controle[qcarga] == 'D'){
									if (carga_acionada[qcarga] != true){
										if (aux_tempo_repouso[qcarga] == 0){
											ligar_carga(qcarga);
											acionamento_tmp += carga[qcarga];
											if ((acionamento_tmp >= max_kw) || (acionamento_tmp > carga_necessaria)){
												break;
											}
										}
										else{
											break;
										}
									}
								}
							}
						}
					}
					else{
						tipo_controle_demanda = read_byte(ee_tipo_controle_demanda);
					}
				}
				if (desligar == true){
					if (tipo_controle_demanda == CONTROLE_FILO){
						qcarga = nro_cargas;
						do{
							qcarga--;
							if (carga[qcarga] > 0){
								if (forma_controle[qcarga] == 'D'){
									if (carga_acionada[qcarga] == true){
										desligar_carga(qcarga);
										acionamento_tmp += carga[qcarga];
										if ((acionamento_tmp >= max_kw) || (acionamento_tmp > carga_necessaria)){
											break;
										}
									}
								}
							}
						}
						while (qcarga != 0);
//						for (qcarga = (nro_cargas - 1); qcarga > 0; qcarga--){
//							if (carga[qcarga] > 0){
//								if (forma_controle[qcarga] == 'D'){
//									if (carga_acionada[qcarga] == true){
//										desligar_carga(qcarga);
//										acionamento_tmp += carga[qcarga];
//										if ((acionamento_tmp >= max_kw) || (acionamento_tmp > carga_necessaria)){
//											break;
//										}
//									}
//								}
//							}
//						}
					}
					else if (tipo_controle_demanda == CONTROLE_FILA_CIRCULAR){
						if (ptr_desaciona >= (nro_cargas-1)){
							ptr_desaciona = 0;
						}
						for (qcarga = ptr_desaciona; qcarga < nro_cargas; qcarga++){
							if (carga[qcarga] > 0){
								if (forma_controle[qcarga] == 'D'){
									if (carga_acionada[qcarga] == true){
										desligar_carga(qcarga);
										acionamento_tmp += carga[qcarga];
										if ((acionamento_tmp >= max_kw) || (acionamento_tmp > carga_necessaria)){
											break;
										}
									}
								}
							}
						}
					}
					else{
						tipo_controle_demanda = read_byte(ee_tipo_controle_demanda);
					}
				}
			}
	
			aux_l1 = (int32)(hora);
			aux_l2 = (int32)(minuto);
			aux_l1 = aux_l1 * 3600;
			aux_l2 = aux_l2 * 60;
			tempo_atual = aux_l1 + aux_l2;
				
			for (qcarga = 0; qcarga < nro_cargas; qcarga++){
				ligar = false;
				if (carga[qcarga] > 0){
					if (forma_controle[qcarga] == 'H'){
						aux_l1 = (int32)(hora_liga_controle[qcarga]);
						aux_l2 = (int32)(minuto_liga_controle[qcarga]);
						aux_l1 = aux_l1 * 3600;
						aux_l2 = aux_l2 * 60;
						tempo_liga = aux_l1 + aux_l2;
			
						aux_l1 = (int32)(hora_desliga_controle[qcarga]);
						aux_l2 = (int32)(minuto_desliga_controle[qcarga]);
						aux_l1 = aux_l1 * 3600;
						aux_l2 = aux_l2 * 60;
						tempo_desliga = aux_l1 + aux_l2;
						
						if (tempo_liga < tempo_desliga){
							if (tempo_atual < tempo_liga){
								ligar = false;
								goto decide_h;
							}
							if (tempo_atual > tempo_desliga){
								ligar = false;
								goto decide_h;
							}
							if (tempo_atual > tempo_liga){
								if (tempo_atual < tempo_desliga){
									ligar = true;
									goto decide_h;
								}
								else{
									ligar = false;
									goto decide_h;
								}
							}
						}
						if (tempo_liga > tempo_desliga){
							if (tempo_atual > tempo_liga){
								ligar = true;
								goto decide_h;
							}
							if (tempo_atual < tempo_desliga){
								ligar = true;
								goto decide_h;
							}
							if (tempo_atual < tempo_liga){
								if (tempo_atual > tempo_desliga){
									ligar = false;
									goto decide_h;
								}
								else{
									ligar = true;
									goto decide_h;
								}
							}
						}

decide_h:				// após todas as decisões, liga ou desliga a carga
						if (ligar == true){
							ligar_carga(qcarga);
						}
						else{
							desligar_carga(qcarga);
						}
					}
				}
			}
		}
		ve_carga_acionada();
	}
}
