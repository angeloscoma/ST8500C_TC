/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ROTINAS                               	                     *
; Funcao: MODULO DE ROTINAS DE COMUNICACAO								 *
; 																		 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 01/08/2003                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/

// grandezas elétricas lidas do equipamento em teste
#define med_tensao_r	0
#define med_tensao_s	1
#define med_tensao_t	2
#define med_corrente_r	3
#define med_corrente_s	4
#define med_corrente_t	5
#define med_fp_r		6
#define med_fp_s		7
#define med_fp_t		8
#define med_kw_r		9
#define med_kw_s		10
#define med_kw_t		11
#define med_kva_r		12
#define med_kva_s		13
#define med_kva_t		14
#define med_kvar_r		15
#define med_kvar_s		16
#define med_kvar_t		17
#define med_freq		18


// parametros de programaao lidos do equipamento em teste
#define prog_off_set_fp_r		0
#define prog_off_set_fp_s		1
#define prog_off_set_fp_t		2
#define prog_off_set_tensao1_r	3
#define prog_off_set_tensao1_s	4
#define prog_off_set_tensao1_t	5
#define prog_off_set_tensao2_r	6
#define prog_off_set_tensao2_s	7
#define prog_off_set_tensao2_t	8
#define prog_off_set_corrente_r	9
#define prog_off_set_corrente_s	10
#define prog_off_set_corrente_t	11
#define prog_off_set_kw_r		12
#define prog_off_set_kw_s		13
#define prog_off_set_kw_t		14
#define prog_valor_tc			15
#define prog_valor_tp			16
#define prog_set_point			17
#define prog_ten_nomi			18
#define prog_time_aciona		19
#define prog_time_repouso		20
#define prog_n_bancos			21
#define prog_val_banco1			22
#define prog_val_banco2			23
#define prog_val_banco3			24
#define prog_val_banco4			25
#define prog_val_banco5			26
#define prog_val_banco6			27
#define prog_val_banco7			28
#define prog_val_banco8			29
#define prog_val_banco9			30
#define prog_val_banco10		31
#define prog_val_banco11		32
#define prog_val_banco12		33
#define prog_ala_fp_ind			34
#define prog_ala_fp_cap			35
#define prog_ala_ten_a			36	
#define prog_ala_ten_b			37
#define prog_ala_sc				38
#define prog_ala_chtt			39
#define prog_des_fp_cap			40
#define prog_des_ten_a			41
#define prog_des_chtt			42
#define prog_min_kvar			43
#define prog_max_kvar			44
#define prog_seq_bancos			45
#define prog_tempo_b1			46
#define prog_tempo_b2			47
#define prog_tempo_b3			48
#define prog_tempo_b4			49
#define prog_tempo_b5			50
#define prog_tempo_b6			51
#define prog_tempo_b7			52
#define prog_tempo_b8			53
#define prog_tempo_b9			54
#define prog_tempo_b10			55
#define prog_tempo_b11			56
#define prog_tempo_b12			57
#define prog_min_cor			58	
#define prog_ala_chtc			59
#define prog_des_chtc			60
#define prog_se_reg_chtt		61
#define prog_off_senoide		62



#define prot_modbus		0
#define prot_sultech	1

void le_entrada1(void)
{
	output_low(CSIO1);
	ENTRADA1 = ~input_d();
	output_high(CSIO1);
}

void le_entrada2(void)
{
	output_low(CSIO2);
	ENTRADA2 = ~input_d();
	output_high(CSIO2);
}

void le_entrada3(void)
{
	output_low(CSIO3);
	ENTRADA3 = input_d();
	output_high(CSIO3);
}

void le_entrada4(void)
{
	output_low(CSIO4);
	ENTRADA4 = input_d();
	output_high(CSIO4);
}

void wr_saida1(void)
{
	char saida;
	saida = SAIDA1;
	output_low(CSIO5);
	output_d(saida);
	output_high(CSIO5);

}

void wr_saida2(void)
{
	char saida;
	saida = SAIDA2;
	output_low(CSIO6);
	output_d(saida);
	output_high(CSIO6);
}


short testa_resposta_ok(void)
{
	if (ret_ser2() == 'O')
		{
		if (ret_ser2() == 'K')
			{
			return(true);
			}
		}
	return(false);
}

void identifica_equipamento(void)
{
	if (time_out_sultech == 0)
		{
		if (protocolo == prot_modbus)
			{
			}
		else
			{
			passo_comuni_sultech = 1;
			buf_tx2[0] = 'C';
			buf_tx2[1] = nro_serie[0];
			buf_tx2[2] = nro_serie[1];
			buf_tx2[3] = nro_serie[2];
			buf_tx2[4] = nro_serie[3];
			buf_tx2[5] = nro_serie[4];
			buf_tx2[6] = nro_serie[5];
			ptrtx2=7;
			tx2_lfcr();
			dispara_tx2();
			}
		}
}	

void le_grandezas_sultech(void)
{
	if (time_out_sultech == 0)
		{
		if (protocolo == prot_modbus)
			{
			}
		else
			{
			buf_tx2[0] = 'P';
			buf_tx2[1] = 'V';
			buf_tx2[2] = 'A';
			ptrtx2=3;
			tx2_lfcr();
			dispara_tx2();
			}
		}

}


void le_programa_sultech(void)
{
	if (time_out_sultech == 0)
		{
		if (protocolo == prot_modbus)
			{
			}
		else
			{
			buf_tx2[0] = 'P';
			buf_tx2[1] = 'G';
			ptrtx2 = 2;
			tx2_lfcr();
			dispara_tx2();
			}
		}
}

void le_offsets_sultech(void)
{
	if (time_out_sultech == 0)
		{
		if (protocolo == prot_modbus)
			{
			}
		else
			{
			ptrtx2 = 0;
			if ((equipamento == 8100) || (equipamento == 8200) || (equipamento == 620) || (equipamento == 310)) 
				{
				buf_tx2[0] = 'P';
				buf_tx2[1] = 'O';
				buf_tx2[2] = 'S';
				ptrtx2 = 3;
				}
			else if ((equipamento == 8300) || (equipamento == 9300) || (equipamento == 930) ) 
				{
				buf_tx2[0] = 'P';
				buf_tx2[1] = 'R';
				buf_tx2[2] = 'O';
				buf_tx2[3] = '?';
				ptrtx2 = 4;
				}
			tx2_lfcr();
			dispara_tx2();
			}
		}
}

#define TAM_OFFSETS_MONO 24
#define TAM_OFFSETS_TRI 50
void processa_offsets_sultech(void)
{
	if (protocolo == prot_modbus)
		{
		}
	else
		{
		if ((equipamento == 8100) || (equipamento == 8200) || (equipamento == 620) || (equipamento == 310)) 
			{
			if (numbrx2 >= TAM_OFFSETS_MONO)
				{
				programas[prog_off_set_tensao1_r] = retira_xxxxx();		
				programas[prog_off_set_tensao2_r] = retira_xxxxx();		
				programas[prog_off_set_corrente_r] = retira_xxxxx();		
				programas[prog_off_set_fp_r] = retira_xxxxx();		
				programas[prog_off_senoide] = retira_xxxxx();		
				passo_comuni_sultech++;
				}
			}
		else if ((equipamento == 8300) || (equipamento == 9300) || (equipamento == 930) ) 
			{
			if (numbrx2 >= TAM_OFFSETS_TRI)
				{
				programas[prog_off_set_tensao1_r] = retira_xxxxx();		
				programas[prog_off_set_tensao1_s] = retira_xxxxx();		
				programas[prog_off_set_tensao1_t] = retira_xxxxx();		
				programas[prog_off_set_corrente_r] = retira_xxxxx();		
				programas[prog_off_set_corrente_s] = retira_xxxxx();		
				programas[prog_off_set_corrente_t] = retira_xxxxx();		
				programas[prog_off_set_fp_r] = retira_xxxxx();		
				programas[prog_off_set_fp_s] = retira_xxxxx();		
				programas[prog_off_set_fp_t] = retira_xxxxx();		
				passo_comuni_sultech++;
				}
			}
		}

}


#define TAM_GRANDEZA_MONO 64
#define TAM_GRANDEZA_TRI 128
void processa_grandezas_sultech(void)
{
	if (protocolo == prot_modbus)
		{
		}
	else
		{
		if ((equipamento == 8100) || (equipamento == 8200) || (equipamento == 620) || (equipamento == 310)) 
			{
			if (numbrx2 >= TAM_GRANDEZA_MONO)
				{
				avanca_retrx(7);
				programas[prog_ten_nomi] = retira_xxx();		
				avanca_retrx(2);
				programas[prog_valor_tc] = retira_xxxx();		
				avanca_retrx(10);
				programas[prog_time_aciona] = retira_xxx();		
				avanca_retrx(2);
				programas[prog_set_point] = retira_xx();		
				programas[prog_n_bancos] = retira_xx();		
				programas[prog_val_banco1] = retira_xxx_x_q5();
				programas[prog_val_banco2] = retira_xxx_x_q5();
				programas[prog_val_banco3] = retira_xxx_x_q5();
				programas[prog_val_banco4] = retira_xxx_x_q5();
				programas[prog_val_banco5] = retira_xxx_x_q5();
				programas[prog_val_banco6] = retira_xxx_x_q5();
				programas[prog_val_banco7] = retira_xxx_x_q5();
				programas[prog_val_banco8] = retira_xxx_x_q5();
				programas[prog_val_banco9] = retira_xxx_x_q5();
				programas[prog_val_banco10] = retira_xxx_x_q5();
				programas[prog_val_banco11] = retira_xxx_x_q5();
				programas[prog_val_banco12] = retira_xxx_x_q5();
				avanca_retrx(2);
				programas[prog_ala_fp_ind] = retira_xx();		
				avanca_retrx(2);
				programas[prog_ala_fp_cap] = retira_xx();		
				programas[prog_ala_ten_a] = retira_xx();		
				programas[prog_ala_ten_b] = retira_xx();		
				programas[prog_ala_sc] = retira_xx();		
				programas[prog_ala_chtc] = retira_xx();		
				avanca_retrx(2);
				programas[prog_des_fp_cap] = retira_xx();		
				programas[prog_des_ten_a] = retira_xx();		
				programas[prog_des_chtc] = retira_xx();		
				programas[prog_max_kvar] = retira_xxx_x_q5();
				programas[prog_seq_bancos] = retira_xx();		
				programas[prog_tempo_b1] = retira_xxx();		
				programas[prog_tempo_b2] = retira_xxx();		
				programas[prog_tempo_b3] = retira_xxx();		
				programas[prog_tempo_b4] = retira_xxx();		
				programas[prog_tempo_b5] = retira_xxx();		
				programas[prog_tempo_b6] = retira_xxx();		
				programas[prog_tempo_b7] = retira_xxx();		
				programas[prog_tempo_b8] = retira_xxx();		
				programas[prog_tempo_b9] = retira_xxx();		
				programas[prog_tempo_b10] = retira_xxx();		
				programas[prog_tempo_b11] = retira_xxx();		
				programas[prog_tempo_b12] = retira_xxx();		
				programas[prog_min_kvar] = retira_xxx_x_q5();
				programas[prog_min_cor] = retira_xx();		
				programas[prog_se_reg_chtt] = ret_ser2() - '0';		
				avanca_retrx(1);
				programas[prog_valor_tp] = retira_xxx();		
				programas[prog_ala_chtt] = retira_xx();		
				programas[prog_des_chtt] = retira_xx();		

				passo_comuni_sultech++;
				}
			}
		else if ((equipamento == 8300) || (equipamento == 9300) || (equipamento == 930) ) 
			{
			if (numbrx2 >= TAM_GRANDEZA_TRI)
				{
				avanca_retrx(7);
				programas[prog_ten_nomi] = retira_xxx();		
				avanca_retrx(2);
				programas[prog_valor_tc] = retira_xxxx();		
				avanca_retrx(10);
				programas[prog_time_aciona] = retira_xxx();		
				avanca_retrx(2);
				programas[prog_set_point] = retira_xx();		
				programas[prog_n_bancos] = retira_xx();		
				programas[prog_val_banco1] = retira_xxx_x_q5();
				programas[prog_val_banco2] = retira_xxx_x_q5();
				programas[prog_val_banco3] = retira_xxx_x_q5();
				programas[prog_val_banco4] = retira_xxx_x_q5();
				programas[prog_val_banco5] = retira_xxx_x_q5();
				programas[prog_val_banco6] = retira_xxx_x_q5();
				programas[prog_val_banco7] = retira_xxx_x_q5();
				programas[prog_val_banco8] = retira_xxx_x_q5();
				programas[prog_val_banco9] = retira_xxx_x_q5();
				programas[prog_val_banco10] = retira_xxx_x_q5();
				programas[prog_val_banco11] = retira_xxx_x_q5();
				programas[prog_val_banco12] = retira_xxx_x_q5();
				avanca_retrx(2);
				programas[prog_ala_fp_ind] = retira_xx();		
				avanca_retrx(2);
				programas[prog_ala_fp_cap] = retira_xx();		
				programas[prog_ala_ten_a] = retira_xx();		
				programas[prog_ala_ten_b] = retira_xx();		
				programas[prog_ala_sc] = retira_xx();		
				programas[prog_ala_chtt] = retira_xx();		
				avanca_retrx(2);
				programas[prog_des_fp_cap] = retira_xx();		
				programas[prog_des_ten_a] = retira_xx();		
				programas[prog_des_chtt] = retira_xx();		
				programas[prog_max_kvar] = retira_xxx_x_q5();
				programas[prog_seq_bancos] = retira_xx();		
				programas[prog_tempo_b1] = retira_xxx();		
				programas[prog_tempo_b2] = retira_xxx();		
				programas[prog_tempo_b3] = retira_xxx();		
				programas[prog_tempo_b4] = retira_xxx();		
				programas[prog_tempo_b5] = retira_xxx();		
				programas[prog_tempo_b6] = retira_xxx();		
				programas[prog_tempo_b7] = retira_xxx();		
				programas[prog_tempo_b8] = retira_xxx();		
				programas[prog_tempo_b9] = retira_xxx();		
				programas[prog_tempo_b10] = retira_xxx();		
				programas[prog_tempo_b11] = retira_xxx();		
				programas[prog_tempo_b12] = retira_xxx();		
				programas[prog_min_kvar] = retira_xxx_x_q5();

				passo_comuni_sultech++;

				}
			}

		}
}

#define TAM_PROG_MONO 64
#define TAM_PROG_TRI 128
void processa_programa_sultech(void)
{
	if (protocolo == prot_modbus)
		{
		}
	else
		{
		if ((equipamento == 8100) || (equipamento == 8200) || (equipamento == 620) || (equipamento == 310)) 
			{
			if (numbrx2 >= TAM_PROG_MONO)
				{
				medicoes[med_tensao_r] = retira_xxx_x_q6();		
				medicoes[med_corrente_r] = retira_xxxx_x_q3();		
				medicoes[med_freq] = retira_xxx_x_q6();		
				medicoes[med_kw_r] = retira_xxxx_x_q5();		
				medicoes[med_kva_r] = retira_xxxx_x_q5();		
				medicoes[med_kvar_r] = retira_xxxx_x_q5();		
				medicoes[med_fp_r] = retira_x_xx_q10();		
				passo_comuni_sultech++;
				}
			}
		else if ((equipamento == 8300) || (equipamento == 9300) || (equipamento == 930) ) 
			{
			if (numbrx2 >= TAM_PROG_TRI)
				{
				medicoes[med_tensao_r] = retira_xxx_x_q6();		
				medicoes[med_tensao_s] = retira_xxx_x_q6();		
				medicoes[med_tensao_t] = retira_xxx_x_q6();		
				medicoes[med_corrente_r] = retira_xxxx_x_q3();		
				medicoes[med_corrente_s] = retira_xxxx_x_q3();		
				medicoes[med_corrente_t] = retira_xxxx_x_q3();		
				medicoes[med_freq] = retira_xxx_x_q6();		
				medicoes[med_kw_r] = retira_xxxx_x_q5();		
				medicoes[med_kw_s] = retira_xxxx_x_q5();		
				medicoes[med_kw_t] = retira_xxxx_x_q5();		
				medicoes[med_kva_r] = retira_xxxx_x_q5();		
				medicoes[med_kva_s] = retira_xxxx_x_q5();		
				medicoes[med_kva_t] = retira_xxxx_x_q5();		
				medicoes[med_kvar_r] = retira_xxxx_x_q5();		
				medicoes[med_kvar_s] = retira_xxxx_x_q5();		
				medicoes[med_kvar_t] = retira_xxxx_x_q5();		
				medicoes[med_fp_r] = retira_x_xx_q10();		
				medicoes[med_fp_r] = retira_x_xx_q10();		
				medicoes[med_fp_s] = retira_x_xx_q10();		
				medicoes[med_fp_t] = retira_x_xx_q10();		
				passo_comuni_sultech++;
				}
			}

		}

}


void ajusta_horario(void)
{
	if (time_out_sultech == 0)
		{
		if (protocolo == prot_modbus)
			{
			}
		else
			{
			if (testa_resposta_ok() == true)
				{
				}
			}
		}
}


void calibra_tensao(void){
	if (time_out_sultech == 0){
		if (protocolo == prot_modbus){
		}
		else{
			if (testa_resposta_ok() == true){
			}
		}
	}
}

void calibra_corrente(void){
	if (time_out_sultech == 0){
		if (protocolo == prot_modbus){
		}
		else{
			if (testa_resposta_ok() == true){
			}
		}
	}
}

void calibra_fp(void){
	if (time_out_sultech == 0){
		if (protocolo == prot_modbus){
		}
		else{
			if (testa_resposta_ok() == true){
			}
		}
	}
}

void calibra_kw(void){
	if (time_out_sultech == 0){
		if (protocolo == prot_modbus){
		}
		else{
			if (testa_resposta_ok() == true){
			}
		}
	}
}

void le_parametros(void){
	if (time_out_sultech == 0){
		if (protocolo == prot_modbus){
		}
		else{
		}
	}
}

void define_equipamento(void){
	if ((equipamento == 8100) || (equipamento == 8200) || (equipamento == 620) || (equipamento == 310)){
		equip_tri = 0;
		if (serie == 'A'){
			equip_mono = 1;
			equip_bi = 0;
		}
		else{
			equip_mono = 1;
			equip_bi = 0;
		}
	}
	else if ((equipamento == 8300) || (equipamento == 9300) || (equipamento == 930)){
		equip_tri = 1;
		equip_mono = 0;
		equip_bi = 0;
	}
	else if ((equipamento == 5000) || (equipamento == 5030) || (equipamento == 9400) || (equipamento == 9430) || (equipamento == 9600)){
		equip_tri = 1;
		equip_mono = 0;
		equip_bi = 0;
	}
	else if ((equipamento == 5100)){
		equip_tri = 0;
		equip_mono = 0;
		equip_bi = 1;
	}
	else{
		equip_tri = 0;
		equip_mono = 0;
		equip_bi = 0;
	}
}

void trata_contactora_16(void){
	if (equip_mono == 1){
		CTR_MT = 1;
	}
	else if (equip_bi == 1){
		CTR_MT = 0;
	}
	else if (equip_tri == 1){
		CTR_MT = 1;
	}
	else{
		CTR_MT = 1;
	}
}


void trata_sultech(void){
	if (retrx2 == ptrrx2){
		return;
	}
	
	switch(passo_comuni_sultech){
		case 1:{
			if (testa_resposta_ok() == true){
				passo_comuni_sultech = 2;
			}
			break;
		}
		case 2:{
			processa_grandezas_sultech();
			break;
		}
		case 3:{
			processa_programa_sultech();
			break;
		}
		case 4:{
			processa_offsets_sultech();
			break;
		}
		case 5:{
			break;
		}
		default:{
		}
	}
}


void st_prog_decisao(void){
	#if (simula_rep == false)
		trata_contactora_16();
		switch(passo_comuni_sultech){
			case 1:{
				identifica_equipamento();
				break;
			}
			case 2:{
				le_grandezas_sultech();
				break;
			}
			case 3:{
				le_programa_sultech();
				break;
			}
			case 4:{
				le_offsets_sultech();
				break;
			}
			default:{
				passo_comuni_sultech = 1;
			}
		}
	#endif

	le_entrada1();
	le_entrada2();
	le_entrada3();
	le_entrada4();
	wr_saida1();
	wr_saida2();
}

#if (simula_rep == true)
	void ConverteEstendido(void){
		tempo1 = minuto;
		tempo1 = tempo1 * 60;
		tempo1 = tempo1 + segundo;
		tempo1 = 3600 - tempo1;
		tempo2 = (word)(tempo1 / 900);
		tempo2 = (word)(tempo2 * 900);
		time_integra = tempo1 - tempo2;
		if (time_integra >= 899){
			pulso_ati = 0;
			pulso_reat = 0;
		}

		aux_f1 = (float)(pulso_ati);
		aux_f2 = (float)(pulso_reat);
		aux_f1 = (float)(aux_f1 * aux_f1);
		aux_f2 = (float)(aux_f2 * aux_f2);
		aux_l1 = (word)(sqrt(aux_f1 + aux_f2));
		aux_l2 = (float)(pulso_ati);
		aux_l2 = (float)(aux_l2 * 1024);
		fator_pot_rep =  (signed word)(aux_l2 / aux_l1);

        low_nro_segundos = make8(time_integra, 0);
        high_nro_segundos = make8(time_integra, 1);
            
        if (reposicao_de_demanda == 1){
            high_nro_segundos = high_nro_segundos | 16;
		}
        else{
            high_nro_segundos = high_nro_segundos & 239;
		}

        if (tarifa[0] == True)     {
            high_nro_segundos = high_nro_segundos | 64;
		}
        if (tarifa[1] == True){
            high_nro_segundos = high_nro_segundos | 128;
			fator_pot_rep = fator_pot_rep * (-1);
		}
        if (tarifa[2] == True){
            high_nro_segundos = high_nro_segundos | 192;
		}

		buf_tx2[0] = low_nro_segundos;
		buf_tx2[1] = high_nro_segundos;
		buf_tx2[2] = ((tipo_de_tarifa * 16) || segmento_horo_sazonal);
		buf_tx2[3] = make8(pulso_ati,0);
		buf_tx2[4] = make8(pulso_ati,1);
		buf_tx2[5] = make8(pulso_reat,0);
		buf_tx2[6] = make8(pulso_reat,1);
		ptrtx2 = 7;
		
		data1_int =  crc16(buf_tx2, ptrtx2);
		buf_tx2[ptrtx2++] = data1_int >> 8;
		buf_tx2[ptrtx2++] = data1_int;
		dispara_tx2();
	}
	
	void converte_pots_rep(void){
		char  carga_meio_dia, fabrica_on , varia_carga_16;
		word tempo1, tempo2, time_integra_old;
		float carga_cap[4];
			
			//byte1: 	0000 0000
			//			|||| |||+- Intervalo de Integração: Bit 0 de 11.
			//			|||| ||+-- Intervalo de Integração: Bit 1 de 11.
			//			|||| |+--- Intervalo de Integração: Bit 2 de 11.
			//			|||| +---- Intervalo de Integração: Bit 3 de 11.
			//			|||+------ Intervalo de Integração: Bit 4 de 11.
			//			||+------- Intervalo de Integração: Bit 5 de 11.
			//			|+-------- Intervalo de Integração: Bit 6 de 11.
			//			+--------- Intervalo de Integração: Bit 7 de 11.
			//byte2: 	0000 0000
			//			|||| |||+- Intervalo de Integração: Bit 8 de 11.
			//			|||| ||+-- Intervalo de Integração: Bit 9 de 11.
			//			|||| |+--- Intervalo de Integração: Bit 10 de 11.
			//			|||| +---- Intervalo de Integração: Bit 11 de 11.
			//			|||+------ Reposição de Demanda: Complemento indica reposição.
			//			||+------- Indicador Intervalo Reativo: Complementado a cada final de intervalo reativo.
			//			|+-------- Se igual a 1, indica que os pulsos de energia reativa capacitiva estão sendo computados para cálculo de UFER e DMCR.
			//			+--------- Se igual a 1, indica que os pulsos de energia reativa indutiva estão sendo computados para cálculo de UFER e DMCR.
			//byte3: 	0000 0000
			//			|||| |||+- | Segmento Horo-Sazonal
			//			|||| ||+-- | 0001 - Ponta
			//			|||| |+--- | 0010 - Fora da Ponta
			//			|||| +---- |_1000 - Reservado
			//			|||+------ | Tipo de Tarifa
			//			||+------- |_00-Azul; 01-Verde; 10-Irrigantes; 11-Outras.
			//			|+-------- Não utilizado.
			//			+--------- Se igual a 1, tarifa de reativos ativada.
			//byte4: 	0000 0000
			//			|||| |||+- Número de pulsos de energia ativa desde o início do intervalo de demanda ativa atual LSB (Bit00)
			//			|||| ||+-- Número de pulsos de energia ativa desde o início do intervalo de demanda ativa atual LSB (Bit01)
			//			|||| |+--- Número de pulsos de energia ativa desde o início do intervalo de demanda ativa atual LSB (Bit02)
			//			|||| +---- Número de pulsos de energia ativa desde o início do intervalo de demanda ativa atual LSB (Bit03)
			//			|||+------ Número de pulsos de energia ativa desde o início do intervalo de demanda ativa atual LSB (Bit04)
			//			||+------- Número de pulsos de energia ativa desde o início do intervalo de demanda ativa atual LSB (Bit05)
			//			|+-------- Número de pulsos de energia ativa desde o início do intervalo de demanda ativa atual LSB (Bit06)
			//			+--------- Número de pulsos de energia ativa desde o início do intervalo de demanda ativa atual LSB (Bit07)
			//byte5: 	0000 0000
			//			|||| |||+- Número de pulsos de energia ativa desde o início do intervalo de demanda ativa atual MSB (Bit08)
			//			|||| ||+-- Número de pulsos de energia ativa desde o início do intervalo de demanda ativa atual MSB (Bit09)
			//			|||| |+--- Número de pulsos de energia ativa desde o início do intervalo de demanda ativa atual MSB (Bit10)
			//			|||| +---- Número de pulsos de energia ativa desde o início do intervalo de demanda ativa atual MSB (Bit11)
			//			|||+------ Número de pulsos de energia ativa desde o início do intervalo de demanda ativa atual MSB (Bit12)
			//			||+------- Número de pulsos de energia ativa desde o início do intervalo de demanda ativa atual MSB (Bit13)
			//			|+-------- Número de pulsos de energia ativa desde o início do intervalo de demanda ativa atual MSB (Bit14)
			//			+--------- Não Usado.
			//byte4: 	0000 0000
			//			|||| |||+- Número de pulsos de energia ativa desde o início do intervalo de demanda reativa atual LSB (Bit00)
			//			|||| ||+-- Número de pulsos de energia ativa desde o início do intervalo de demanda reativa atual LSB (Bit01)
			//			|||| |+--- Número de pulsos de energia ativa desde o início do intervalo de demanda reativa atual LSB (Bit02)
			//			|||| +---- Número de pulsos de energia ativa desde o início do intervalo de demanda reativa atual LSB (Bit03)
			//			|||+------ Número de pulsos de energia ativa desde o início do intervalo de demanda reativa atual LSB (Bit04)
			//			||+------- Número de pulsos de energia ativa desde o início do intervalo de demanda reativa atual LSB (Bit05)
			//			|+-------- Número de pulsos de energia ativa desde o início do intervalo de demanda reativa atual LSB (Bit06)
			//			+--------- Número de pulsos de energia ativa desde o início do intervalo de demanda reativa atual LSB (Bit07)
			//byte5: 	0000 0000
			//			|||| |||+- Número de pulsos de energia ativa desde o início do intervalo de demanda reativa atual MSB (Bit08)
			//			|||| ||+-- Número de pulsos de energia ativa desde o início do intervalo de demanda reativa atual MSB (Bit09)
			//			|||| |+--- Número de pulsos de energia ativa desde o início do intervalo de demanda reativa atual MSB (Bit10)
			//			|||| +---- Número de pulsos de energia ativa desde o início do intervalo de demanda reativa atual MSB (Bit11)
			//			|||+------ Número de pulsos de energia ativa desde o início do intervalo de demanda reativa atual MSB (Bit12)
			//			||+------- Número de pulsos de energia ativa desde o início do intervalo de demanda reativa atual MSB (Bit13)
			//			|+-------- Número de pulsos de energia ativa desde o início do intervalo de demanda reativa atual MSB (Bit14)
			//			+--------- Não Usado.
			//byte8: 	0000 0000
			//			|||| |||+- Complemento do "ou exclusivo" dos bytes anteriores (Bit 0).
			//			|||| ||+-- Complemento do "ou exclusivo" dos bytes anteriores (Bit 1).
			//			|||| |+--- Complemento do "ou exclusivo" dos bytes anteriores (Bit 2).
			//			|||| +---- Complemento do "ou exclusivo" dos bytes anteriores (Bit 3).
			//			|||+------ Complemento do "ou exclusivo" dos bytes anteriores (Bit 4).
			//			||+------- Complemento do "ou exclusivo" dos bytes anteriores (Bit 5).
			//			|+-------- Complemento do "ou exclusivo" dos bytes anteriores (Bit 6).
			//			+--------- Complemento do "ou exclusivo" dos bytes anteriores (Bit 7).

			
        #if (novo_REP == true)
        	pulso_ati = quantidade_kW;
        	pulso_reat = quantidade_kVAr;
        #else
		    reposicao_de_demanda = 1; 
		    segmento_horo_sazonal = 7;
		    tipo_de_tarifa = 1;
		#endif
	
	    if (hora < 6){
		    tarifa[0] = true;      
		    tarifa[1] = false;      
	    	tarifa[2] = false;     
		}
		else{
		    tarifa[0] = false;      
		    tarifa[1] = True;      
		    tarifa[2] = false;     
		}

		tempo1 = minuto;
		tempo1 = tempo1 * 60;
		tempo1 = tempo1 + segundo;
		tempo1 = 3600 - tempo1;
		tempo2 = (word)(tempo1 / 900);
		tempo2 = (word)(tempo2 * 900);
		time_integra = tempo1 - tempo2;

//		if (time_integra > time_integra_old)
		if (time_integra >= 899){
			pulso_ati = 0;
			pulso_reat = 0;
		}
		time_integra_old = time_integra;

		if (hora == 12){
			carga_meio_dia = 0;
		}
		else{
			carga_meio_dia = 1;
		}

		if (hora < 8 ){
			fabrica_on = 0;
		}
		else{
			if (hora > 22){
				fabrica_on = 0;
			}
			else{
				fabrica_on = 1;
			}
		}

		if (minuto < 15){
			varia_carga_16 = 1;
		}
		else if (minuto < 30){
			varia_carga_16 = 0;
		}
		else if (minuto < 45){
			varia_carga_16 = 1;
		}
		else{
			varia_carga_16 = 0;
		}
			
		var_fp[14] = var_fp[14] - 0.0010;
		var_fp[15] = var_fp[15] + 0.0020;
		if ((hora < 12) || ((hora >= 13) && (hora <= 18))){
			if (var_fp[14] < 0.1){
				var_fp[14] = 1;
			}
			if (var_fp[15] > 1){
				var_fp[15] = .20;
			}
		}
		else{
			var_fp[14] = 1;
			var_fp[15] = 1;
		}
			
		degrau1 = 1;
		if (minuto < 5) {
			degrau1 = .01;
		}
		if ((minuto > 25) && (minuto < 30)) {
			degrau1 = .2;
		}
		if ((minuto > 35) && (minuto < 38)){
			degrau1 = .1;
		}
		if ((minuto > 45) && (minuto < 48)){
			degrau1 = .1;
		}
		if (minuto < 1){
			degrau1 = 1.2;
		}
		if ((minuto > 14) && (minuto < 16)){
			degrau1 = 1.5;
		}
		if ((minuto > 29) && (minuto < 31)){
			degrau1 = 1.5;
		}
		if ((minuto > 44) && (minuto < 46)){
			degrau1 = 1.5;
		}
					
		carga_at[0] = banco_capacitor[0] * RELE1 * carga_meio_dia * fabrica_on  * degrau1;
		carga_at[1] = banco_capacitor[1] * RELE2 * carga_meio_dia * fabrica_on ;
		carga_at[2] = banco_capacitor[2] * RELE3 * carga_meio_dia * fabrica_on ;
		carga_at[3] = banco_capacitor[3] * RELE4 * carga_meio_dia * fabrica_on ;
		carga_at[4] = banco_capacitor[4] * RELE5 * carga_meio_dia * fabrica_on ;
		carga_at[5] = banco_capacitor[5] * RELE6 * carga_meio_dia * fabrica_on ;
		carga_at[6] = banco_capacitor[6] * RELE7 * carga_meio_dia * fabrica_on ;
		carga_at[7] = banco_capacitor[7] * RELE8 * carga_meio_dia * fabrica_on ;

		carga_at[8] = banco_capacitor[8] * RELE9 * fabrica_on ;
		carga_at[9] = banco_capacitor[9] * RELE10  * fabrica_on ;
		carga_at[10] = banco_capacitor[10] * RELE11 * fabrica_on ;
		carga_at[11] = banco_capacitor[11] * RELE12 * fabrica_on ;
		carga_at[12] = banco_capacitor[12] * RELE13 * fabrica_on ;
		carga_at[13] = banco_capacitor[13] * RELE14 * fabrica_on ;
		carga_at[14] = banco_capacitor[14] * RELE15 * fabrica_on ;
		carga_at[15] = banco_capacitor[15] * RELE16 * fabrica_on ;

		carga_at[12] = 0;
		carga_at[13] = 0;
		carga_at[14] = 0;
		carga_at[15] = 0;

		carga_at[0] = carga_at[0] * 4;
		carga_at[1] = carga_at[1] * 2;


		carga_reat[0] = 0;
		carga_reat[1] = 0;
		carga_reat[2] = 0;
		carga_reat[3] = 0;
		carga_reat[4] = 0;
		carga_reat[5] = 0;
		carga_reat[6] = 0;
		carga_reat[7] = 0;

		carga_reat[8] = (150 * RELE9 *  fabrica_on);
		carga_reat[9] = (150 * RELE10 * fabrica_on );
		carga_reat[10] = (100 * RELE11 * fabrica_on);
		carga_reat[11] = (100 * RELE12 * fabrica_on);

		carga_cap[0] = (150 * RELE13 * fabrica_on);
		carga_cap[1] = (150 * RELE14 * fabrica_on);
		carga_cap[2] = (100 * RELE15 * fabrica_on);
		carga_cap[3] = (100 * RELE16 * fabrica_on);

		if (carga_reat[8] != 0){
			carga_reat[8] = carga_reat[8] - carga_cap[0];
		}
		if (carga_reat[9] != 0){
			carga_reat[9] = carga_reat[9] - carga_cap[1];
		}
		if (carga_reat[10] != 0){
			carga_reat[10] = carga_reat[10] - carga_cap[2];
		}
		if (carga_reat[11] != 0){
			carga_reat[11] = carga_reat[11] - carga_cap[3];
		}
		
		carga_reat[12] = 0;
		carga_reat[13] = 0;
		carga_reat[14] = 0;
		carga_reat[15] = 0;

		carga_total_at = 0;
		carga_total_reat = 0;
		for(aux_b1 = 0; aux_b1 < 16; aux_b1++){
			carga_total_at += carga_at[aux_b1];	
			carga_total_reat += carga_reat[aux_b1];
		}

		aux_f1= carga_total_at;
		aux_f1 = aux_f1 * 100;
	   	aux_f1 = aux_f1 / 3600;
    	somaf_at = somaf_at + aux_f1;
    	if (somaf_at >= 1) {
        	aux_l1 = somaf_at;
        	pulso_ati = pulso_ati + aux_l1;
        	somaf_at = somaf_at - aux_l1;
        }

		aux_f1= carga_total_reat;
		aux_f1 = aux_f1 * 100;
    	aux_f1 = aux_f1 / 3600;
    	somaf_reat = somaf_reat + aux_f1;
    	if (somaf_reat >= 1) {
        	aux_l1 = somaf_reat;
        	pulso_reat = pulso_reat + aux_l1;
        	somaf_reat = somaf_reat - aux_l1;
        }
        
    
		aux_f1 = (float)(pulso_ati);
		aux_f2 = (float)(pulso_reat);
		aux_f1 = (float)(aux_f1 * aux_f1);
		aux_f2 = (float)(aux_f2 * aux_f2);
		aux_l1 = (word)(sqrt(aux_f1 + aux_f2));
		aux_l2 = (float)(pulso_ati);
		aux_l2 = (float)(aux_l2 * 1024);
		fator_pot_rep =  (signed word)(aux_l2 / aux_l1);

        low_nro_segundos = make8(time_integra, 0);
        high_nro_segundos = make8(time_integra, 1);
            
        if (reposicao_de_demanda == 1){
            high_nro_segundos = high_nro_segundos | 16;
		}
        else{
            high_nro_segundos = high_nro_segundos & 239;
		}

        if (tarifa[0] == True)     {
            high_nro_segundos = high_nro_segundos | 64;
		}
        if (tarifa[1] == True){
            high_nro_segundos = high_nro_segundos | 128;
			fator_pot_rep = fator_pot_rep * (-1);
		}
        if (tarifa[2] == True){
            high_nro_segundos = high_nro_segundos | 192;
		}
        

		buf_tx2[0] = low_nro_segundos;
		buf_tx2[1] = high_nro_segundos;
		buf_tx2[2] = ((tipo_de_tarifa * 16) || segmento_horo_sazonal);
		buf_tx2[3] = make8(pulso_ati,0);
		buf_tx2[4] = make8(pulso_ati,1);
		buf_tx2[5] = make8(pulso_reat,0);
		buf_tx2[6] = make8(pulso_reat,1);
		
		buf_tx2[7] = 0;	
		buf_tx2[7] ^= buf_tx2[0];
		buf_tx2[7] ^= buf_tx2[1];
		buf_tx2[7] ^= buf_tx2[2];
		buf_tx2[7] ^= buf_tx2[3];
		buf_tx2[7] ^= buf_tx2[4];
		buf_tx2[7] ^= buf_tx2[5];
		buf_tx2[7] ^= buf_tx2[6];
		buf_tx2[7] = ~buf_tx2[7];
		
		ptrtx2 = 8;
		dispara_tx2();
	}
#endif

void desligar_banco(void){
}
void ligar_banco(void){
}
void gera_sequencia_valor_bancos(void){
}
