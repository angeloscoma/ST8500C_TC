//***********************************************************************
// Empresa: Sultech Sistemas Eletrônicos								*
// Modulo: Inicial														*
// Função: Tratamento da Leitura do Canal IU do REP						*
// Responsável: Edison Valério Nunes Junior								*
// Modificado: Edison Valério Nunes Junior								*
// Inicio: 02/07/2012													*
// Revisão: Edison Valério Nunes Junior									*
//***********************************************************************
  
#define printar_rep 		false
#define EM_PONTA			00
#define FORA_DE_PONTA		01
#define TAR_AZUL			00
#define TAR_VERDE			01
#define TAR_IRRIGANTES		02
#define TAR_OUTRAS			03

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
void VerificarReativo(void);
int16 crc16(char *msg, char tamanho, char formato);
void LeituraProtocoloNormal(void);
void LeituraProtocoloEstendido(void);
void LeituraProtocoloGrandezas(void);
void LeituraProtocoloMisto(void);

void tx_erro_rep(char erro){
	#if (printar_rep == true)
		#if (com_485 == true)
			output_high(direcao);
			delay_ms(1);
		#endif	
		
		fprintf(modbus,"\l\rREP-%u: ", erro);
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
				fprintf(modbus,"\l\rErro pulso 1:%lu, %lu:", puls_c1_rep, puls_c1_rep_ant);
				break;
			}
			case 2:{
				fprintf(modbus,"\l\rErro pulso 2:%lu, %lu:", puls_c2_rep, puls_c2_rep_ant);
				break;
			}
			case 3:
			case 4:{
				fprintf(modbus,"\l\rErro tempo:%u, %lu, %lu:", erro, seg_falt_rep, seg_falt_rep_ant);
				break;
			}
			case 5:{
				fprintf(modbus,"\l\rIntegrou!:%lu, %u, %u", seg_falt_rep, num_int, num_int_ant);
				break;
			}
			case 6:{
				fprintf(modbus,"\l\rErro CRC!:%u, %u", buf_rec_tmp[7], buf_rec_tmp[8]);
				break;
			}
		}
	
		#if (com_485 == true)
			delay_ms(1);
			output_low(direcao);
		#endif	
	#endif
}

void Zerar_REP(void){
	cod_bloco_REP			= 0;
	definicao_REP 			= 0;
	data_REP 				= 0;
	caracterizacao_REP		= 0;
	tensao_R_REP 			= 0;
	tensao_S_REP 			= 0;
	tensao_T_REP 			= 0;
	corrente_R_REP 			= 0;
	corrente_S_REP 			= 0;
	corrente_T_REP 			= 0;
	corrente_N_REP 			= 0;
	pot_ativa_R_REP 		= 0;
	pot_ativa_S_REP 		= 0;
	pot_ativa_T_REP 		= 0;
	pot_ativa_total_REP 	= 0;
	pot_reativa_R_REP 		= 0;
	pot_reativa_S_REP 		= 0;
	pot_reativa_T_REP 		= 0;
	pot_reativa_total_REP 	= 0;
	pot_aparente_R_REP 		= 0;
	pot_aparente_S_REP		= 0;
	pot_aparente_T_REP 		= 0;
	pot_aparente_total_REP 	= 0;
	frequencia_REP 			= 0;
	seg_falt_rep 			= 0;
	ctrl_demanda_REP		= 0;
	ene_ati_pos				= 0;
	ene_rea_pos_ati_pos		= 0;
	ene_rea_neg_ati_pos		= 0;
	ene_ati_neg				= 0;
	ene_rea_pos_ati_neg		= 0;
	ene_rea_neg_ati_neg		= 0;
	puls_c1_rep 			= 0;
	puls_c2_rep 			= 0;
	fator_pot	 			= 1024;
	fator_pot_r 			= 1024;
	fator_pot_s 			= 1024;
	fator_pot_t 			= 1024;
}

void inic_rep(void){
	nbyte_rep = 0;
	rec_rep_ok = false;
}
void trat_rep(void){
	int x;
	if(transferir_REP){
		for(x = 0; x < qtd_byte_REP; x++){
			buf_rec_tmp[x] = buf_rec_rep[x];
		}
		transferir_REP = 0;
		if(cont_sem_REP > 1000){
			Zerar_REP();
		}
		else{
			cont_sem_REP++;
			rec_rep_ok = 1;
		}
	}

 //	#if(testando_REP)
//		buf_rec_tmp[0] =    1;
//		buf_rec_tmp[1] =    0;
//		buf_rec_tmp[2] =  213;
//		buf_rec_tmp[3] =   74;
//		buf_rec_tmp[4] =    3;
//		buf_rec_tmp[5] =   62;
//		buf_rec_tmp[6] =   16;
//		buf_rec_tmp[7] =   39;
//		buf_rec_tmp[8] =    0;
//		buf_rec_tmp[9] =    0;
//		buf_rec_tmp[10] = 112;
//		buf_rec_tmp[11] =  48;
//		buf_rec_tmp[12] =   0;
//		buf_rec_tmp[13] =   0;
//		buf_rec_tmp[14] =   0;
//		buf_rec_tmp[15] =   0;
//		buf_rec_tmp[16] = 148;
//		buf_rec_tmp[17] =  11;
//		buf_rec_tmp[18] =   0;
//		buf_rec_tmp[19] =   0;
//		buf_rec_tmp[20] =   0;
//		buf_rec_tmp[21] =   0;
//		buf_rec_tmp[22] = 149;
//		buf_rec_tmp[23] =  11;
//		buf_rec_tmp[24] =  92;
//		buf_rec_tmp[25] =  14;
//		buf_rec_tmp[26] =   0;
//		buf_rec_tmp[27] =   0;
//		buf_rec_tmp[28] =   0;
//		buf_rec_tmp[29] =   0;
//		buf_rec_tmp[30] = 247;
//		buf_rec_tmp[31] = 255;
//		buf_rec_tmp[32] =   0;
//		buf_rec_tmp[33] =   0;
//		buf_rec_tmp[34] =   0;
//		buf_rec_tmp[35] =   0;
//		buf_rec_tmp[36] = 117;
//		buf_rec_tmp[37] =  23;
//		buf_rec_tmp[38] = 186;
//		buf_rec_tmp[39] =   1;
//		buf_rec_tmp[40] =   0;
//		buf_rec_tmp[41] =   0;
//		buf_rec_tmp[42] = 234;
//		buf_rec_tmp[43] =   0;
//		buf_rec_tmp[44] =   0;
//		buf_rec_tmp[45] =   0;
//		buf_rec_tmp[46] =   1;
//		buf_rec_tmp[47] =   0;
//		buf_rec_tmp[48] =   0;
//		buf_rec_tmp[49] =   0;
//		buf_rec_tmp[50] =   0;
//		buf_rec_tmp[51] =   0;
//		buf_rec_tmp[52] =   0;
//		buf_rec_tmp[53] =   0;
//		buf_rec_tmp[54] = 155;
//		buf_rec_tmp[55] = 128;
//	#endif
	
	if (rec_rep_ok) {		// seta o bit quando do rx de 8 bytes 
		if (time_out_modo_rep < 5){
			time_out_modo_rep++;			
			time_out_modo_rep++;			
		}
		trat_msg_rep();
		rec_rep_ok = 0;
	}

//	if(baud_rate_REP){
//		output_high(VEL_REP);
//	}
//	else{
//		output_low(VEL_REP);
//	}
}

void trat_msg_rep(void){
	short erro_REP;
	
	erro_REP = 0;
//	protocolo_REP = 0;				//Antes de implementação da interface para troca fixamos em "0" (normal).
	switch(protocolo_REP){
		case REP_NORMAL:{
			LeituraProtocoloNormal();
			break;
		}
		case REP_ESTENDIDO:{
			LeituraProtocoloEstendido();
			break;
		}
		case REP_GRANDEZAS:{
			LeituraProtocoloGrandezas();
			break;
		}
		case REP_MISTO:{
			LeituraProtocoloMisto();
			break;
		}
		default:{
			protocolo_REP = 0;
			LeituraProtocoloNormal();
		}
	}
	
	if(erro_REP){
		return;
	}
	switch (seg_falt_rep){
		case 600:{
			if ((minuto > 2) && (minuto < 8)){
				minuto = 5;
			}
			else if ((minuto > 17) && (minuto < 23)){
				minuto = 20;
			}
			else if ((minuto > 32) && (minuto < 38)){
				minuto = 35;
			}
			else if ((minuto > 42) && (minuto < 48)){
				minuto = 45;
			}
			#if (com_regs == true)
				segundo = 0;
				grava_registros(reg_normal);
				gravou = true;
				#if (com_relogio == true)
				   	write_ds1302(0x82,dec_bcd(minuto));
   						write_ds1302(0x80,dec_bcd(segundo));
				#endif
			#endif
			break;
		}
		case 300:{
			if ((minuto > 7) && (minuto < 13)){
				minuto = 10;
			}
			else if ((minuto > 22) && (minuto < 28)){
				minuto = 25;
			}
			else if ((minuto > 37) && (minuto < 43)){
				minuto = 40;
			}
			else if ((minuto > 52) && (minuto < 58)){
				minuto = 55;
			}
			#if (com_regs == true)
				segundo = 0;
				grava_registros(reg_normal);
				gravou = true;
				#if (com_relogio == true)
				   	write_ds1302(0x82,dec_bcd(minuto));
   						write_ds1302(0x80,dec_bcd(segundo));
				#endif
			#endif
			break;
		}
		case 0:{
			if (minuto < 3){
				minuto = 0;
			}
			else if ((minuto > 12) && (minuto < 18)){
				minuto = 15;
			}
			else if ((minuto > 27) && (minuto < 33)){
				minuto = 30;
			}
			else if ((minuto > 42) && (minuto < 48)){
				minuto = 45;
			}
			#if (com_regs == true)
				segundo = 0;
				grava_registros(reg_normal);
				gravou = true;
				#if (com_relogio == true)
				   	write_ds1302(0x82,dec_bcd(minuto));
   						write_ds1302(0x80,dec_bcd(segundo));
				#endif
			#endif
			break;
		}
	}
	
	if (seg_falt_rep > seg_falt_rep_ant){
		ultimo_pulso_at = ultimo_pulso_at_tmp;
		ultimo_pulso_reat = ultimo_pulso_reat_tmp;
		write_word(ee_ultimo_pulso_at, ultimo_pulso_at);
		write_word(ee_ultimo_pulso_reat, ultimo_pulso_reat);

		aux_f1 = (float)(ultimo_pulso_at * kkw);
		aux_f2 = (float)(ultimo_pulso_reat * kkvar);
		pot_ativa_tot = (int32)(aux_f1);
		pot_reativa_tot = (int32)(aux_f2);

		ultima_pot_at = pot_ativa_tot;
		ultima_pot_reat = pot_reativa_tot;
		write_word(ee_ultima_pot_at, pot_ativa_tot);
		write_word(ee_ultima_pot_reat, pot_reativa_tot);
	}
	ultimo_pulso_at_tmp = puls_c1_rep;
	ultimo_pulso_reat_tmp = puls_c2_rep;

	if (tarif_ind_rep_old != tarif_ind_rep){
		time_out_troca_tarifa++;
		if (time_out_troca_tarifa == 10){
			time_out_troca_tarifa = 0;
			fecha_periodo();
			if (tarif_ind_rep == 0){
				for (aux_b1 = 0; aux_b1 < NRO_MAXIMO_BANCOS_CAPACITOR; aux_b1++){
					desligar_banco(aux_b1);
				}
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
	num_int = (unsigned char)(aux_w1 / 60);

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

		#if (printar_rep == true)
			#if (com_485 == true)
				output_high(direcao);
				delay_ms(1);
			#endif	
			fprintf(modbus,"\l\rPulsos:%lu/%lu ; %lu/%lu", puls_c1_rep,  ultimo_pulso_at,  puls_c2_rep , ultimo_pulso_reat);
			fprintf(modbus,"\l\rEnergias:%lu(kWh) ;%lu(kVAr)", e_ativa, e_reativa);
			#if (com_485 == true)
				delay_ms(1);
				output_low(direcao);
			#endif	
		#endif
		faz_int_minuto(num_int);
		num_int_ant = num_int;
	}		
}

void faz_int_minuto(char parte){
//*******************************************************************************************************************************
//	A diferença entre o número de pulsos, tanto de energia ativa quanto reativa, recebido na última integração parcial e o atual
//	é armazenada em tabelas (int_ativa e int_reativa) e indexado pelo índice "parte". O somatório das partes nos devolve o valor
//	total de pulsos já recebido, fazemos então a média aritmética para com ela preenchermos o restante da tabela e projetar o 
//	valor de demanda para o intervalo completo de 15 minutos.
//	As estimativas de corrente e potências instantâneas são feitas considerando a demanda projetada para o término do intervalo 
//	de integração.
//*******************************************************************************************************************************
	int32 extra2;
	int32 extra1; 
	char x;
	
	atualizar = 1;
	   
	if (parte > (NRO_INTERVALOS_INTEGRACAO - 1)){
	    parte = 0;
	    return;
	}

    int_ativa[parte] = e_ativa;
	int_reativa[parte] = e_reativa;
	write_word(ee_int_ativa + (parte*2), e_ativa);
	write_word(ee_int_reativa + (parte*2), e_reativa);

	fp_ativa = 0;
	fp_reativa = 0;
	
	for (x = 0; x < (parte + 1); x++){
		fp_ativa += (float)(int_ativa[x]); 
		fp_reativa += (float)(int_reativa[x]); 
	}
	fp_ati_aux = fp_ativa;
	fp_rea_aux = fp_reativa;
	
	fp_ativa = (float)(fp_ativa * kkw);
	fp_reativa = (float)(fp_reativa * kkvar);

	fp_ati_aux = (float)(fp_ati_aux / (parte + 1));
	fp_rea_aux = (float)(fp_rea_aux / (parte + 1));
	for (x = 0; x < NRO_INTERVALOS_INTEGRACAO; x++){
		if (x > parte){
			int_ati_aux[x] = (word)fp_ati_aux;
			int_rea_aux[x] = (word)fp_rea_aux;
		}
		else{
			int_ati_aux[x] = int_ativa[x];
			int_rea_aux[x] = int_reativa[x];
		}
	}

	fp_ati_aux = 0;
	fp_rea_aux = 0;
	for (x = 0; x < NRO_INTERVALOS_INTEGRACAO; x++){
		fp_ati_aux += (float)int_ati_aux[x]; 
		fp_rea_aux += (float)int_rea_aux[x]; 
	}
	fp_ati_aux = (float)(fp_ati_aux * kkw);
	fp_rea_aux = (float)(fp_rea_aux * kkvar);
	dem_ativa_proj = (word)(fp_ati_aux);
	dem_reativa_proj = (word)(fp_rea_aux);

//	aux_f1 = (float)(fp_ati_aux);
//	pot_ativa_tot = (int32)((aux_f1 * 32));
	pot_ativa_tot = (int32)(fp_ati_aux);
	pot_ativa_r = (word)(pot_ativa_tot / 3);
	#if (monofasico == false)
		pot_ativa_s = pot_ativa_r;
		pot_ativa_t = pot_ativa_r;
	#endif

//	aux_f1 = (float)(fp_rea_aux);
//	pot_reativa_tot = (int32)((aux_f1 * 32));
	pot_reativa_tot = (int32)(fp_rea_aux);
	pot_reativa_r = (word)(pot_reativa_tot / 3);
	#if (monofasico == false)
		pot_reativa_s = pot_reativa_r;
		pot_reativa_t = pot_reativa_r;
	#endif

	#if (printar_rep == true)
		#if (com_485 == true)
			output_high(direcao);
			delay_ms(1);
		#endif	

		fprintf(modbus,"\l\rAtiva:");
		for (x = 0; x < 15; x++) 
			{
			fprintf(modbus,"%lu, ", int_ativa[x]);
			}
		fprintf(modbus,"\l\rReativa:");
		for (x = 0; x < 15; x++) 
			{
			fprintf(modbus,"%lu, ", int_reativa[x]);
			}
		fprintf(modbus,"\l\rPotencias:%f(kWh)/%lu ;%f(kVAr), Sinal:%u", fp_ativa, pot_ativa_r, fp_reativa, tipo_fp);
		aux_f1 = pot_ativa_r;
		aux_f1 = aux_f1 / 32;
		fprintf(modbus,"\l\rPotencias:%f(kWh)", aux_f1);
		aux_f1 = pot_reativa_r;
		aux_f1 = aux_f1 / 32;
		fprintf(modbus," ;%f(kVArh)", aux_f1);

		#if (com_485 == true)
			delay_ms(2);
			output_low(direcao);
		#endif	
	#endif
	#if (feira == true)
		#if(TEN_220V)
			pot_ativa_r = 352;
			pot_ativa_s = 352;
			pot_ativa_t = 352;
			pot_aparente_r = 352;
			pot_aparente_s = 352;
			pot_aparente_t = 352;
		#else
			pot_ativa_r = 203;
			pot_ativa_s = 203;
			pot_ativa_t = 203;
			pot_aparente_r = 203;
			pot_aparente_s = 203;
			pot_aparente_t = 203;
		#endif
		pot_reativa_r = 0;
		pot_reativa_s = 0;
		pot_reativa_t = 0;
		fator_pot_r = 1024;
		fator_pot_s = 1024;
		fator_pot_t = 1024;
	#endif
}
// A cada 15 min. faz o fechamento (parte = 14) que pode ser chamado pelo
// pulso de integracao externo ou pela passagem do temporizador interno
// (timer_integra) que subt. o ext. no caso da falta ou perda de sinal
// rotinas que sao executadas a cada 15 minutos
// no fechamento do intervalo de integracao

void fecha_periodo(void){
	char x;
	
	for (x = 0; x < 15; x++){
		int_ativa[x] = 0;             /* zera os acumuladores de pulsos */
		write_word(ee_int_ativa+(x*2), 0);
		int_reativa[x] = 0;
		write_word(ee_int_reativa+(x*2), 0);
	}
}
void recupera_rep(void){
	for (aux_b1 = 0; aux_b1 < 15; aux_b1++){
		int_ativa[aux_b1] = read_word(ee_int_ativa + (aux_b1*2));
		int_reativa[aux_b1] = read_word(ee_int_reativa + (aux_b1*2));
	}
	nbyte_rep = 0;
 	nbit_rep = 0;
	start_rep = 0;
	time_out_rep = 2;
}

void zera_rep(void){
	for (aux_b1 = 0; aux_b1 < 15; aux_b1++){
		write_word(ee_int_ativa+(aux_b1*2), 0);
		write_word(ee_int_reativa+(aux_b1*2), 0);
	}
	recupera_rep();
	ultimo_pulso_at = 0;
	ultimo_pulso_reat = 0;
	ultima_pot_at = 0;
	ultima_pot_reat = 0;	
}


//*******************************************************************************************************************************
// VerificarReativo
// Verifica se a carga reativa existente é capacitiva, mesmo com tarifação indutiva. Para isso medimos o valor da potência 
// reativa e comparamos com seu valor no minuto posterior. Se, mesmo depois de realizados os acionamentos, a energia reativa 
// aumentar significa que a origem desta energia são os capacitores.
// Desta forma, desligamos as saídas para começar novamente o processo.
// Se durante a contagem para novo acionamento (cont_decide_rep > 0) a comparação entre a carga reativa atual e anterior mostrar 
// aumento, a rotina indica necessidade de desligamento.
// Se o equipamento estiver em condição de "falta de capacitores" e o fator de potência for inferior a -0,92, desligamos todas 
// as saídas para recomeçar o processo de acionamento.
// Ao término da rotina, renovamos a base de comparação.
//*******************************************************************************************************************************
void VerificarReativo(void){
	short desligar_tudo;

	desligar_tudo = 0;
	if(pot_reativa_r > pot_reativa_r_ant){
		if(cont_decide_rep > 0){
			desligar_tudo = 1;
		}
	}
	if(falta_capacitor){
		if(fator_pot_r < set_point){
			desligar_tudo = 1;
		}
	}

	if(desligar_tudo){
		for (aux_b1 = 0; aux_b1 < NRO_MAXIMO_BANCOS_CAPACITOR; aux_b1++){
			desligar_banco(aux_b1);
		}
	}

	pot_reativa_r_ant = pot_reativa_r;
}

long CalcularPotAparente(long pot_ativa, long pot_reativa){
	float valorf1;
	float valorf2;
	long saida;
	
	valorf1 = pot_ativa;
	valorf1 *= valorf1;
	valorf2 = pot_reativa;
	valorf2 *= valorf2;
	
	saida = (long)(sqrt(valorf1 + valorf2));
	return(saida);
}

void LeituraProtocoloNormal(void){
//################################################################################
//|					Protocolo Normal - 8 Bytes - 110 Baud			|
//################################################################################
//|Byte	|Bit7	|Bit6	|Bit5	|Bit4	|Bit3	|Bit2	|Bit1	|Bit0	|
//| 0	|					Segundos (LSB)								|
//| 1	|ERIC	|ERCC	|FIR	|RD		|		Segundos (MSB)			|
//| 2	|TR		|X		|Tipo Tarifa	|	Segmento Horo-Sazonal		|
//| 3	|			Número Pulsos Energia Ativa (LSB)					|
//| 4	|	X	|			Número Pulsos Energia Ativa (MSB)			|
//| 5	|			Número Pulsos Energia Reativa (LSB)					|
//| 6	|	X	|			Número Pulsos Energia Reativa (MSB)			|
//| 7	|		Complemento do "OU Exclusivo" dos bytes anteriores		|
//################################################################################
// RD	Reposição de Demanda							
// FIR	Fim Intervalo Reativo							
// ERIC	Pulso de Energia Reativa Capacitiva computado para cálculo de UFER e DMCR
// ERCC	Pulso de Energia Reativa Indutiva computado para cálculo de UFER e DMCR
// TR	Tarifa de Reativos ativada							
// X		Não usado							
//								
// Tipo Tarifa		Bit 5	Bit 4		Horo-Sazonal	Bit 3	Bit 2	Bit 1	Bit 0
// Azul				0		0			Ponta			0		0		0		1
// Verde			0		1			Fora Pota		0		0		1		0
// Irrigantes		1		0			Reservado		1		0		0		0
// Outras			1		1
//################################################################################
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
		erro_REP = 1;
		return;
	}

	fatura_rep = buf_rec_tmp[1];
	if(bit_test(fatura_rep,4)!= bit_test(fatura_rep_old,4)){
		fatura_rep_old = fatura_rep;
		write_byte(ee_fatura_rep, fatura_rep);
		#if (com_regs == true)
			grava_registros(reg_fatura_rep);
			grava_ocorrencias(reg_fatura_rep);
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
}

void LeituraProtocoloEstendido(void){
//################################################################################
//|					Protocolo Estendido - 9 Bytes - 110 Baud			|
//################################################################################
//|Byte	|Bit7	|Bit6	|Bit5	|Bit4	|Bit3	|Bit2	|Bit1	|Bit0	|
//| 0	|					Segundos (LSB)								|
//| 1	|ERIC	|ERCC	|FIR	|RD		|		Segundos (MSB)			|
//| 2	|	TR	|	X	|	Quadrante	|	X	|	X	| Posto Horário |
//| 3	|			Número Pulsos Energia Ativa (LSB)					|
//| 4	|			Número Pulsos Energia Ativa (MSB)					|
//| 5	|			Número Pulsos Energia Reativa (LSB)					|
//| 6	|			Número Pulsos Energia Reativa (MSB)					|
//| 7	|					CRC (LSB)									|
//| 8	|					CRC (MSB)									|
//################################################################################
// RD	Reposição de Demanda (Fechamento da conta)
// FIR	Fim Intervalo Reativo 
// ERCC	Indicação de Tarifação Capacitiva
// ERIC	Indicação de Tarifação Indutiva
// TR	Tarifa de Reativos Ativada no Medidor
// X	Não usado
//
// Posto Horário	Bit 1	Bit 0			Quadrante	Bit 5	Bit 4
// Reservado		0		0					1		0		0
// Ponta			0		1					4		0		1
// Fora Ponta		1		0					2		1		0
// Quarto Posto		1		1					3		1		1
//################################################################################

	CRC_calculado = crc16(buf_rec_tmp, (qtd_byte_REP - 2),'R');	// Calculamos o CRC para todo o buffer recebido
	aux_b1 = buf_rec_tmp[qtd_byte_REP - 1];						// exceto os dois últimos bytes pois são o CRC
	aux_b2 = buf_rec_tmp[qtd_byte_REP - 2];						// enviado. 
	CRC_recebido = make16(aux_b2, aux_b1);						// Montamos o CRC enviado pelo REP e comparamos 
	if (CRC_calculado != CRC_recebido){							// com o calculado. Se forem diferentes informamos
		tx_erro_rep(6);											// o erro e encerramos a função.
		erro_REP = 1;
		return;
	}

	fatura_rep = buf_rec_tmp[1];
	if(bit_test(fatura_rep,4)!= bit_test(fatura_rep_old,4)){
		flag_fatura_rep = ~flag_fatura_rep;
		fatura_rep_old = fatura_rep;
		write_byte(ee_fatura_rep, fatura_rep);
		grava_registros(reg_fatura_rep);
		grava_ocorrencias(reg_fatura_rep);
	}

	fim_interv_reat_rep	= (buf_rec_tmp[1] & 0x20) >> 5;
	posto_reativo		= (buf_rec_tmp[1] & 0xC0) >> 6;
//	tarif_cap_rep		= (buf_rec_tmp[1] & 0x40) >> 6;
//	tarif_ind_rep		= (buf_rec_tmp[1] & 0x80) >> 7;
	posto_horario		= (buf_rec_tmp[2] & 0x03);
	quadrante_aux		= (buf_rec_tmp[2] & 0x30) >> 4;
	tarif_reativo_ativa	= (buf_rec_tmp[2] & 0x80) >> 7;
	seg_falt_rep = make16((buf_rec_tmp[1] & 0x0F),buf_rec_tmp[0]);
	puls_c1_rep  = make16(buf_rec_tmp[4],buf_rec_tmp[3]);
	puls_c2_rep  = make16(buf_rec_tmp[6],buf_rec_tmp[5]);
	switch(quadrante_aux){
		case 0:{
			quadrante = 1;
			break;
		}
		case 1:{
			quadrante = 4;
			break;
		}
		case 2:{
			quadrante = 2;
			break;
		}
		case 3:{
			quadrante = 3;
			break;
		}
		default:{
			quadrante = 1;
			break;
		}
	}
}

void LeituraProtocoloGrandezas(void){
}
void LeituraProtocoloMisto(void){
//#######################################################################################
//|					Protocolo Misto - 56 Bytes - 600 Baud								|
//#######################################################################################
//|	Byte	|	Formato	|						Descrição								|
//| 0		|	Word8	|1																|
//| 1		|	Word8	|Caracter de definição do bloco (ver observações).				|
//|	2 a 5	|	Word32	|Número de segundos desde 00:00:00 01/01/1980 (Data/Hora)		|
//| 6 a 9	|	Word32	|Se o resto de (número de segundos / 6) for igual a:			|
//|										0: Número de série do medidor;					|
//|										1: RTP (x10000);								|
//|										2: RTC (x10000);								|
//|										3: Ke (x10000) Wh/pulso e VArh/pulso			|
//|										4 ou 5: Reservado para uso futuro.				|
//| 10 a 11	|	Word16	|Tensão secundária no elemento A do medidor (x100)				|
//| 12 a 13	|	Word16	|Tensão secundária no elemento B do medidor (x100)				|
//| 14 a 15	|	Word16	|Tensão secundária no elemento C do medidor (x100)				|
//| 16 a 17	|	Word16	|Corrente secundária no elemento A do medidor (x1000)			|
//| 18 a 19	|	Word16	|Corrente secundária no elemento B do medidor (x1000)			|
//| 20 a 21	|	Word16	|Corrente secundária no elemento C do medidor (x1000)			|
//| 22 a 23	|	Word16	|Corrente de neutro secundária (x1000)							|
//| 24 a 25	|	Int16	|Potência ativa secundária elemento A do medidor (x10)			|
//| 26 a 27	|	Int16	|Potência ativa secundária elemento B do medidor (x10)			|
//| 28 a 29	|	Int16	|Potência ativa secundária elemento C do medidor (x10)			|
//| 30 a 31	|	Int16	|Potência reativa secundária elemento A do medidor (x10)		|
//| 32 a 33	|	Int16	|Potência reativa secundária elemento B do medidor (x10)		|
//| 34 a 35	|	Int16	|Potência reativa secundária elemento C do medidor (x10)		|
//| 36 a 37	|	Word16	|Frequência da rede (x100)										|
//| 38 a 39	|	Word16	|Número de segundos restantes deste intervalo de demanda		|
//| 40 a 41	|	Word16	|Dados para controle de demanda									|
//|							Bit 15: Posto reativo ativado;								|
//|							Bit 14: Posto reativo indutivo em vigor;					|
//|							Bit 13: Posto reativo capacitivo em vigor;					|
//|							Bit 12: Complementado a cada intervalo de reativo;			|
//|							Bit 11 a 3: Não utilizados;									|
//|							Bit 2: Complementado a cada reposição de demanda;			|
//|							Bit 1 e 0: Posto horário:									|
//|								00 = Ponta;												|
//|								01 = Fora ponta;										|
//|								11 = Reservado;											|
//|								10 = Quarto posto;										|
//| 42 a 43	|	Word16	|Contador de pulsos de Wh positiva								|
//| 44 a 45	|	Word16	|Contador de pulsos de VArh positiva com Wh positiva			|
//| 46 a 47	|	Word16	|Contador de pulsos de VArh negativa com Wh positiva			|
//| 48 a 49	|	Word16	|Contador de pulsos de Wh negativa								|
//| 50 a 51	|	Word16	|Contador de pulsos de VArh positiva com Wh negativa			|
//| 52 a 53	|	Word16	|Contador de pulsos de VArh negativa com Wh negativa			|
//| 54 a 55	|	Word16	|Caracter de redundância CRC16 (x^16 + x^15 + x^2 + x^0)		|
//#######################################################################################
// Definição dos Campos																	|
// Valores do caractere de definição do bloco:											|
// 0: Ligação Estrela																	|
// 1: Indefinido																		|
// 2: Ligação Delta																		|
// 3: Bifásico 120°																		|
// 4: Monofásico																		|
// 5: Série Paralela																	|
// 6: Delta Aterrado																	|
// 																						|
// As tensões, correntes e potências deste bloco são observadas nos terminais do 		|
// medidor. A interpretação destas informações no que diz respeito ao modo de ligação 	|
// deve ser feita pelo recptor do bloco. Isto quer dizer que, se a ligação for estrela, |
// tesnão no elemento A é a tensão de fase, e se for delta, tensão no elemento A é a 	|
// tensão de linha AB, tensão no elemento B á tensão de linha BC, tensão no elemento C 	|
// é a tensão de linha CA.																|
// 																						|
// Potências ativas positivas indicam fluxo de energia da linha para a carga do 		|
// medidor. Potências ativas negativas indicam fluxo de energia da carga para a 		|
// linha do medidor.																	|
//																						|
// Os contadores de pulso são sempre incrementados e voltam a zero quando fecha o 		|
// intervalo de demanda.																|
// 																						|
// Descrição dos Formatos:																|
// Word8:	Inteiro 8 bits, sem sinal													|
// Word16:	Inteiro 16 bits sem sinal, byte menos significativo antes					|
// Word32:	Inteiro 32 bits sem sinal, byte menos significativo antes					|
// Int16:	Inteiro 16 bits com sinal, byte menos significativo antes					|
//#######################################################################################

	CRC_calculado = crc16(buf_rec_tmp, 54,'R');		// Calculamos o CRC para todo o buffer recebido
//	aux_b1 = buf_rec_tmp[qtd_byte_REP - 1];			// exceto os dois últimos bytes pois são o CRC
//	aux_b2 = buf_rec_tmp[qtd_byte_REP - 2];			// enviado. 
	CRC_recebido = make16(buf_rec_tmp[54], buf_rec_tmp[55]);// Montamos o CRC enviado pelo REP e comparamos 
	if (CRC_calculado != CRC_recebido){						// com o calculado. Se forem diferentes informamos
		tx_erro_rep(6);										// o erro e encerramos a função.
		erro_REP = 1;
		return;
	}
	cod_bloco_REP		= buf_rec_tmp[0];
	definicao_REP 		= buf_rec_tmp[1];
	data_REP 			= make32(buf_rec_tmp[5], buf_rec_tmp[4], buf_rec_tmp[3], buf_rec_tmp[2]);
	caracterizacao_REP	= make32(buf_rec_tmp[9], buf_rec_tmp[8], buf_rec_tmp[7], buf_rec_tmp[6]);
	tensao_R_REP 		= make16(buf_rec_tmp[11], buf_rec_tmp[10]);		// *100
	tensao_S_REP 		= make16(buf_rec_tmp[13], buf_rec_tmp[12]);		// *100
	tensao_T_REP 		= make16(buf_rec_tmp[15], buf_rec_tmp[14]);		// *100
	corrente_R_REP 		= make16(buf_rec_tmp[17], buf_rec_tmp[16]);		// *1000
	corrente_S_REP 		= make16(buf_rec_tmp[19], buf_rec_tmp[18]);		// *1000
	corrente_T_REP 		= make16(buf_rec_tmp[21], buf_rec_tmp[20]);		// *1000
	corrente_N_REP 		= make16(buf_rec_tmp[23], buf_rec_tmp[22]);		// *1000
	pot_ativa_R_REP 	= make16(buf_rec_tmp[25], buf_rec_tmp[24]);		// *10
	pot_ativa_S_REP 	= make16(buf_rec_tmp[27], buf_rec_tmp[26]);		// *10
	pot_ativa_T_REP 	= make16(buf_rec_tmp[29], buf_rec_tmp[28]);		// *10
	pot_reativa_R_REP 	= make16(buf_rec_tmp[31], buf_rec_tmp[30]);		// *10
	pot_reativa_S_REP 	= make16(buf_rec_tmp[33], buf_rec_tmp[32]);		// *10
	pot_reativa_T_REP 	= make16(buf_rec_tmp[35], buf_rec_tmp[34]);		// *10
	frequencia_REP 		= make16(buf_rec_tmp[37], buf_rec_tmp[36]);		// *100
	seg_falt_rep 		= make16(buf_rec_tmp[39], buf_rec_tmp[38]);
	ctrl_demanda_REP	= make16(buf_rec_tmp[41], buf_rec_tmp[40]);
	ene_ati_pos			= make16(buf_rec_tmp[43], buf_rec_tmp[42]);
	ene_rea_pos_ati_pos	= make16(buf_rec_tmp[45], buf_rec_tmp[44]);
	ene_rea_neg_ati_pos	= make16(buf_rec_tmp[47], buf_rec_tmp[46]);
	ene_ati_neg			= make16(buf_rec_tmp[49], buf_rec_tmp[48]);
	ene_rea_pos_ati_neg	= make16(buf_rec_tmp[51], buf_rec_tmp[50]);
	ene_rea_neg_ati_neg	= make16(buf_rec_tmp[53], buf_rec_tmp[52]);

	puls_c1_rep = ene_ati_pos;
	puls_c2_rep = ene_rea_pos_ati_pos;
	
	if(bit_test(ctrl_demanda_REP,15)){		// Verificamos se existe posto reativo
		posto_reativo = 1;					// e em seguida identificamos se é 
		if(bit_test(ctrl_demanda_REP,13)){	// indutivo ou capacitivo.
			tarif_cap_rep = 1;				//
		}									//
	}										//
	else{									// Se o reativo não estiver habilitado
		posto_reativo = 0;					// zeramos nossa variável.
	}										//
	
	if(bit_test(ctrl_demanda_REP,2)){			// Verificamos se houve reposição de demanda
		fatura_rep = 1;							// copiando o estado atual e comparando com
	}											// o que já tínhamos.
	else{										//
		fatura_rep = 0;							//
	}											//
	if(fatura_rep != fatura_rep_old){			//
		fatura_rep_old = fatura_rep;			// Salvamos o novo estado como registro da flash.
		write_byte(ee_fatura_rep, fatura_rep);	// Ainda é preciso definir se deve existir algum
		grava_registros(reg_fatura_rep);		// outro procedimento ou alerta para este evento.
		grava_ocorrencias(reg_fatura_rep);		//
	}											//

	aux_b1 = data_REP % 6;
	switch(aux_b1){
		case 0:{
			nro_serie_REP = caracterizacao_REP;
			break;
		}
		case 1:{
			rtp_REP = caracterizacao_REP;			// *10000
			break;
		}
		case 2:{
			rtc_REP = caracterizacao_REP;			// *10000
			break;
		}
		case 3:{
			ke_REP = caracterizacao_REP;			// *10000
			break;
		}
		case 4:
		case 5:{
			break;
		}
	}

	quadrante_aux = (ctrl_demanda_REP & 0x03);
	switch(quadrante_aux){
		case 0:{
			quadrante = 1;
			break;
		}
		case 1:{
			quadrante = 4;
			break;
		}
		case 2:{
			quadrante = 2;
			break;
		}
		case 3:{
			quadrante = 3;
			break;
		}
		default:{
			quadrante = 1;
			break;
		}
	}
	
	pot_ativa_total_REP = (pot_ativa_R_REP + pot_ativa_S_REP + pot_ativa_T_REP);
	pot_reativa_total_REP = (pot_reativa_R_REP + pot_reativa_S_REP + pot_reativa_T_REP);
	
	if(bit_test(pot_ativa_R_REP,15)){			// Verificamos se o número é negativo
		bit_clear(pot_ativa_R_REP,15);			// o que indica energia ativa fornecida.
		if(bit_test(pot_reativa_R_REP,15)){		// E zeramos o bit para acertar o cáculo.
			sinal_fp[0] = 'I';					// Assim, energia reativa positiva é
			pot_reativa_R_REP *= (-1);			// capacitiva.
		}										// 
		else{									// 
			sinal_fp[0] = 'C';					// 
		}										//
	}											// 
	else{										// Se, ao contrário, o número é positivo
		if(bit_test(pot_reativa_R_REP,15)){		// temos indicação de energia ativa consumida.
			sinal_fp[0] = 'C';					// Assim energia reativa positiva é
			pot_reativa_R_REP *= (-1);			// indutiva.
		}										// 
		else{									// 
			sinal_fp[0] = 'I';					// 
		}										//
	}											// 
	
	if(bit_test(pot_ativa_S_REP,15)){			// Verificamos se o número é negativo
		bit_clear(pot_ativa_S_REP,15);			// o que indica energia ativa fornecida.
		if(bit_test(pot_reativa_S_REP,15)){		// E zeramos o bit para acertar o cáculo.
			sinal_fp[1] = 'I';					// Assim, energia reativa positiva é
			pot_reativa_S_REP *= (-1);			// capacitiva.
		}										// 
		else{									// 
			sinal_fp[1] = 'C';					// 
		}										//
	}											// 
	else{										// Se, ao contrário, o número é positivo
		if(bit_test(pot_reativa_S_REP,15)){		// temos indicação de energia ativa consumida.
			sinal_fp[1] = 'C';					// Assim energia reativa positiva é
			pot_reativa_S_REP *= (-1);			// indutiva.
		}										// 
		else{									// 
			sinal_fp[1] = 'I';					// 
		}										//
	}											// 

	if(bit_test(pot_ativa_T_REP,15)){			// Verificamos se o número é negativo
		bit_clear(pot_ativa_T_REP,15);			// o que indica energia ativa fornecida.
		if(bit_test(pot_reativa_T_REP,15)){		// E zeramos o bit para acertar o cáculo.
			sinal_fp[2] = 'I';					// Assim, energia reativa positiva é
			pot_reativa_T_REP *= (-1);			// capacitiva.
		}										// 
		else{									// 
			sinal_fp[2] = 'C';					// 
		}										//
	}											// 
	else{										// Se, ao contrário, o número é positivo
		if(bit_test(pot_reativa_T_REP,15)){		// temos indicação de energia ativa consumida.
			sinal_fp[2] = 'C';					// Assim energia reativa positiva é
			pot_reativa_T_REP *= (-1);			// indutiva.
		}										// 
		else{									// 
			sinal_fp[2] = 'I';					// 
		}										//
	}											// 

	if(bit_test(pot_ativa_total_REP,15)){		// Verificamos se o número é negativo
		bit_clear(pot_ativa_total_REP,15);		// o que indica energia ativa fornecida.
		if(bit_test(pot_reativa_total_REP,15)){	// E zeramos o bit para acertar o cáculo.
			sinal_fp[3] = 'I';					// Assim, energia reativa positiva é
			pot_reativa_total_REP *= (-1);		// capacitiva.
		}										// 
		else{									// 
			sinal_fp[3] = 'C';					// 
		}										//
	}											// 
	else{										// Se, ao contrário, o número é positivo
		if(bit_test(pot_reativa_total_REP,15)){	// temos indicação de energia ativa consumida.
			sinal_fp[3] = 'C';					// Assim energia reativa positiva é
			bit_clear(pot_reativa_total_REP,15);// indutiva.
		}										// 
		else{									// 
			sinal_fp[3] = 'I';					// 
		}										//
	}											// 

	pot_aparente_R_REP = CalcularPotAparente(pot_ativa_R_REP, pot_reativa_R_REP);
	pot_aparente_S_REP = CalcularPotAparente(pot_ativa_S_REP, pot_reativa_S_REP);
	pot_aparente_T_REP = CalcularPotAparente(pot_ativa_T_REP, pot_reativa_T_REP);
	pot_aparente_total_REP = CalcularPotAparente(pot_ativa_total_REP, pot_reativa_total_REP);
	
	aux_l1 = pot_ativa_R_REP;
	aux_l1 *= 1024;
	fator_pot_r = aux_l1 / pot_aparente_R_REP;
	if(sinal_fp[0] == 'I'){
		fator_pot_r *= (-1);
	}
	aux_l1 = pot_ativa_S_REP;
	aux_l1 *= 1024;
	fator_pot_s = aux_l1 / pot_aparente_S_REP;
	if(sinal_fp[1] == 'I'){
		fator_pot_s *= (-1);
	}
	aux_l1 = pot_ativa_T_REP;
	aux_l1 *= 1024;
	fator_pot_t = aux_l1 / pot_aparente_T_REP;
	if(sinal_fp[2] == 'I'){
		fator_pot_t *= (-1);
	}
	aux_l1 = pot_ativa_total_REP;
	aux_l1 *= 1024;
	fator_pot = aux_l1 / pot_aparente_total_REP;
	if(sinal_fp[3] == 'I'){
		fator_pot *= (-1);
	}
}

