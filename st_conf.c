/************************************************************************
; Empresa: SULTECH SISTEMAS ELETRÿÔNICOS                                 *
; Modulo: ST_CONF                                                       *
; Funcao: MODULO de configuracoes				   						*
; 		REGISTRADOR ST9600R                       						*
; Responsavel: VAGNER SANTOS											*
; Modificado ; VAGNER SANTOS                                            *
; Inicio: 06/06/2003                                                    *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                   *
;************************************************************************/
/* config.c
	Configuracao e tratamento de e2prom
*/

/* definicacao de variaveis auxiliares */
char checksum_vars;

#if (funcao_505 == true)
	void inic_tensoes_505(void);
#endif

void calcula_fundo_escala_corrente(void);
#if (com_cht == true)
	void zera_chts(void);
#endif

#if (com_menu == true)
	void reinicializa_menus(void);
#endif

#if (tc_fixo == true)
	void busca_mul_tc(void);
	void calcula_mul_tc(void);
#endif

void zera_soma_pot(void);


#if (controlador == true) || (st_prog == true)
	#if (st8500c == true)
		void vali_nro_cargas(void);	    	
		void recupera_tempos_acionamentos(void);
		void desligar_carga(char);
		void busca_demanda_contratada(void);
	#else
		void vali_nro_bancos_capacitor(void);	    	
		void recupera_tempos_acionamentos(void);
		void desligar_banco(char);
	#endif
	#if (com_rep == true)
		void fecha_periodo(void);   
		void recupera_rep(void);
	#endif
#endif

#if (portatil == true)
	void decide_que_ponteira(void);
#endif	

void assume_defaults(void);


void inicializa_flags_alarmes(void)
{
	gravou = false;
	programando = 0;
	retardo_alarmes = 60;
	ferro_rep = false;
	fp_ind = 0;
	fp_cap = 0;
	ten_a_r = 0;
	ten_b_r = 0;
	cor_a_r = 0;
	ffase_r = 0;
   	tem_alarme = 0;
	sentido_r = 0;
	#if (monofasico == false)
		ten_a_s = 0;
		ten_a_t = 0;
		ten_b_s = 0;
		ten_b_t = 0;
		cor_a_s = 0;
		cor_a_t = 0;
		chtt_a = 0;
		chtc_a = 0;
		ffase_s = 0;
		ffase_t = 0;
		sentido_s = 0;
		sentido_t = 0;
	#endif
	
#if (CONTROLADOR == true) || (st_prog == true)
	saturou_kw = 0;
	saturou_kvar = 0;
#endif

	#if (controlador == true)
		falta_capacitor = false;
	#endif
	#if (st8500c == true)
		fprintar = false;
	#endif
	
	tem_comando_alarme = 0;
	calcular_frequencia = 0;
	calculando_freq = 0;
	freq_50hz = 0;

#if (tratar_localizacao == true)
	existe_local = read_bit(ee_bits_menu2, EE_EXISTE_LOCAL);
	digitou_texto = read_bit(ee_bits_menu2, EE_DIGITOU_TEXTO);
#endif
	#if (com_menu == true)
		reinicializa_menus();
	#endif
	

}


#if (portatil == true)
	#if (se_com_flex ==	true)
		void config_ponteiras(void)
		{
			recarrega_ponteira = false;
			aux_w2 = ee_os_cor_r_9001g1;
			for (aux_b1 = 0; aux_b1 < NRO_POSI_TABELA_TIPO_PT; aux_b1++)
				{
				os_cor_pt_r[aux_b1] = read_byte(aux_w2++);
				os_cor_pt_s[aux_b1] = read_byte(aux_w2++);
				os_cor_pt_t[aux_b1] = read_byte(aux_w2++);
				}
			aux_w2 = ee_off_fp_9001g1;
			for (aux_b1 = 0; aux_b1 < NRO_POSI_TABELA_TIPO_PT; aux_b1++)
				{
				off_set_fp[aux_b1] = read_byte(aux_w2++);
				}
			aux_w2 = ee_os_pot_r_9001g1;
			for (aux_b1 = 0; aux_b1 < NRO_POSI_TABELA_TIPO_PT; aux_b1++)
				{
				os_pot_pt_r[aux_b1] = read_byte(aux_w2++);
				os_pot_pt_s[aux_b1] = read_byte(aux_w2++);
				os_pot_pt_t[aux_b1] = read_byte(aux_w2++);
				}

			os_cor_r = os_cor_pt_r[tipo_ponteira];
			os_cor_s = os_cor_pt_s[tipo_ponteira];
			os_cor_t = os_cor_pt_t[tipo_ponteira];
			os_pot_r = os_pot_pt_r[tipo_ponteira];
			os_pot_s = os_pot_pt_s[tipo_ponteira];
			os_pot_t = os_pot_pt_t[tipo_ponteira];
			
			off_cor_r = off_set_fp[tipo_ponteira];

		}
	#endif
#endif	

#if (st8500c == true)
	void inicializa_8500c(void)
	{
		consumo_ati = read_long(ee_consumo_ati);	
		consumo_reati = read_long(ee_consumo_reati);
		if (consumo_ati == 0xffffffff){
			consumo_ati = 0;
			write_long(ee_consumo_ati, 0);
		}
		if (consumo_reati == 0xffffffff){
			consumo_reati = 0;
			write_long(ee_consumo_reati, 0);
		}	
		if (read_long(ee_consumo_ati_ant) == 0xffffffff){
			write_long(ee_consumo_ati_ant, 0);
		}
		if (read_long(ee_consumo_reati_ant) == 0xffffffff){
			write_long(ee_consumo_reati_ant, 0);
		}
		
		nro_cargas = read_byte(ee_nro_cargas);
		vali_nro_cargas();	    	
	
		max_kw = read_word(ee_max_kw);

		tipo_controle_demanda = read_byte(ee_tipo_controle_demanda);

		aux_w1 = ee_carga_1;
		aux_w2 = ee_tempo_repouso_1;
		for (aux_b1 = 0; aux_b1 < nro_cargas; aux_b1++)
			{
			carga[aux_b1] = read_byte(aux_w1++);
			tempo_repouso[aux_b1] = read_byte(aux_w2++);
			carga_acionada[aux_b1] = false;
			carga_disponivel[aux_b1] =false;
			desligar_carga(aux_b1);
					
			forma_controle[aux_b1] = read_byte((ee_forma_controle + aux_b1));
			hora_liga_controle[aux_b1] = read_byte((ee_hora_liga_controle + aux_b1));
			minuto_liga_controle[aux_b1] = read_byte((ee_minuto_liga_controle + aux_b1));
			hora_desliga_controle[aux_b1] = read_byte((ee_hora_desliga_controle + aux_b1));
			minuto_desliga_controle[aux_b1] = read_byte((ee_minuto_desliga_controle + aux_b1));
					
			}
		
		aux_w1 = 0;
		for (aux_b1 = 0; aux_b1< 12; aux_b1++)
			{
			dem_cont_ponta[aux_b1] = read_word(ee_dem_cont_ponta + aux_w1);
			dem_cont_fora_ponta[aux_b1] = read_word(ee_dem_cont_fora_ponta + aux_w1);
			aux_w1 += 2;
			}
		carga_programada = read_word(ee_carga_programada);
			
		mes_inicio_pc = read_byte(ee_mes_inicio_pc);
		dia_inicio_pc = read_byte(ee_dia_inicio_pc);
		dia_final_pc = read_byte(ee_dia_final_pc);
		mes_final_pc = read_byte(ee_mes_final_pc);
	
		#if (com_rep == true)
			fat_conv_ativa = read_word(ee_fat_conv_ativa);
			fat_conv_reativa = read_word(ee_fat_conv_reativa);
			modo_rep = read_byte(ee_modo_rep);
			fat_conv_ativa = read_word(ee_fat_conv_ativa);
			fat_conv_reativa = read_word(ee_fat_conv_reativa);
			time_out_modo_rep = 1;
			ultimo_pulso_at = read_word(ee_ultimo_pulso_at);
			ultimo_pulso_reat = read_word(ee_ultimo_pulso_reat);
			ultima_pot_at = read_word(ee_ultima_pot_at);
			ultima_pot_reat = read_word(ee_ultima_pot_reat);
			fatura_rep = read_byte(ee_fatura_rep);
			fatura_rep_old = fatura_rep;
			if (modo_rep == 1){
				fecha_periodo();    
				recupera_rep();
			}
			protocolo_REP = read_byte(ee_protocolo_REP);
		#endif
	
		hora_ponta = read_byte(ee_hora_ponta);
		hora_final_ponta = read_byte(ee_hora_final_ponta);
		minuto_ponta = read_byte(ee_minuto_ponta);
		minuto_final_ponta = read_byte(ee_minuto_final_ponta);
		
		modo_saidas = read_byte(ee_modo_saidas);
		
//		busca_demanda_contratada();
	}
#endif

void inicializa_variaveis(void)
{
	#if (funcao_505 == true)
		inic_tensoes_505();
	#endif

	#if (home_system == true)
		ContHSnet = TEMPO_HSNET;
	#endif

	status_equipamento_H = 0;
	status_equipamento_L = 0;

	#if (st8500c == true)
		inicializa_8500c();
		ptr_aciona = 0;
		ptr_desaciona = 0;;
	#endif

	ler_ad_t3 = 1;
	time_out_t3 = 0;
	med_ten_ok = 0;
	calc_ten_ok = 0;
	passo_main = 0;
	lendo_cht = 0;
	passo_tensao = 0;
	passo_corrente = 0;
	calculando_vref = false;
	fechar_frequencia = 0;
	#if (controlador == true)
		#if (monofasico == false)
			passo_ad_8300 = 0;
		#endif
	#endif

	#if (ade7754 == true)
		conta_media_ten_r = 0;
		conta_media_ten_s = 0;
		conta_media_ten_t = 0;
		acao_ade7754 = 0;
	#else
		conta_media_ten = 0;
	#endif
	soma_efi_tr = 0;
	soma_efi_cr = 0;
	soma_efi_pr = 0;
	tensao_r = 0;
	corrente_r = 0;
	pot_ativa_r = 0;
	pot_reativa_r = 0;
	pot_aparente_r = 0;
	fator_pot_r = 1024;
	frequencia = 240;
	soma_freq = 0;
	conta_soma_freq = 0;

#if (monofasico == false)
	soma_efi_ts = 0;
	soma_efi_cs = 0;
	soma_efi_ps = 0;
	soma_efi_tt = 0;
	soma_efi_ct = 0;
	soma_efi_pt = 0;
	tensao_s = 0;
	tensao_t = 0;
	corrente_s = 0;
	corrente_t = 0;
	pot_ativa_s = 0;
	pot_ativa_t = 0;
	pot_reativa_s = 0;
	pot_reativa_t = 0;
	pot_aparente_s = 0;
	pot_aparente_t = 0;
	fator_pot_s = 1024;
	fator_pot_t = 1024;
#endif

zera_soma_pot();

#if (tratar_localizacao == true)
	localizacao[0] = read_byte(EE_LOCALIZACAO_0);
	localizacao[1] = read_byte(EE_LOCALIZACAO_1);
	localizacao[2] = read_byte(EE_LOCALIZACAO_2);
	localizacao[3] = read_byte(EE_LOCALIZACAO_3);
	localizacao[4] = read_byte(EE_LOCALIZACAO_4);
	localizacao[5] = read_byte(EE_LOCALIZACAO_5);
	localizacao[6] = read_byte(EE_LOCALIZACAO_6);
	localizacao[7] = read_byte(EE_LOCALIZACAO_7);
	localizacao[8] = read_byte(EE_LOCALIZACAO_8);
	localizacao[9] = read_byte(EE_LOCALIZACAO_9);
	localizacao[10] = read_byte(EE_LOCALIZACAO_10);
	localizacao[11] = read_byte(EE_LOCALIZACAO_11);
	localizacao[12] = read_byte(EE_LOCALIZACAO_12);
	localizacao[13] = read_byte(EE_LOCALIZACAO_13);
	localizacao[14] = read_byte(EE_LOCALIZACAO_14);
	localizacao[15] = read_byte(EE_LOCALIZACAO_15);
#endif

#if (chip_cs5460a == false)
	soma_pot_efi_r = 0;
	soma_tr = 0;
	soma_cr = 0;
	soma_pr = 0;
	soma_ten_r = 0;
	soma_cor_r = 0;
	soma_pot_r = 0;


	#if (monofasico == false)
		soma_pot_efi_s = 0;
		soma_pot_efi_t = 0;
		soma_ts = 0;
		soma_cs = 0;
		soma_ps = 0;
		soma_tt = 0;
		soma_ct = 0;
		soma_pt = 0;
		soma_ten_s = 0;
		soma_ten_t = 0;
		soma_cor_s = 0;
		soma_cor_t = 0;
		soma_pot_s = 0;
		soma_pot_t = 0;
	#endif
#endif
	

#if (com_cht == true)
	passo_rd_cht = 0;
	passo_fase_cht = 0;
	passo_cht = 1;
#endif

// inicializa flags	
#if (com_menu == true)
	exibiu = 0;
	tecla_up = 0;
	tecla_down = 0;
	tecla_enter = 0;
	tecla_reset = 0;

	tecla_reset_up = 0;
	tecla_enter_down = 0;
	tecla_enter_reset = 0;
//	enter_low = 0;
	tecla_enter = 0;
	tecla_reset = 0;
	ha_tecla = 0;
	exibiu_erro = 0;
	exibiu_erro_menu = 0;
	teclou_enter = 0;
	exibir_menu = 0;
	
	tecla_reset_up = 0;
	tecla_up_down_reset = 0;
	
	programando = 0;
	time_out_menus = 60;		//120;
	time_tecla = 20;
	menu1 = 0;
	menu_aux = 0;
	qmenu = 0;
	rolando = false;
	ja_rolou = true;
#endif
	
// inicializa variaveis	
	#if (com_display == true)
		val_pwm = LIMITE_VAL_PWM;
	#endif
// inicializa buffers	
	#if (com_cht == true)
		zera_chts();
	#endif
	#if (com_regs == true)
		prox_grava = 0;
		zera_soma_reg();
	#endif	
	#if (com_consumo == true)
		#if (com_demanda == true)
			zera_demandas();
		#endif
		inic_consumo();
	#endif
	
	#if (chip_cs5460a == false)
		#if (ade7754 == false)
			for (aux_b1 = 0; aux_b1 < NRO_AMOSTRAS; aux_b1++)
				{
				pulsa_wdt();
				buf_tensao_r[aux_b1] = 2048;
				buf_corrente_r[aux_b1] = 2048;
			#if (monofasico == false)
					buf_tensao_s[aux_b1] = 2048;
					buf_corrente_s[aux_b1] = 2048;
					buf_tensao_t[aux_b1] = 2048;
					buf_corrente_t[aux_b1] = 2048;
			#endif
				}
		#endif
	#endif
//	vref = 2048;
//	vref_cr = 2048;
//	vref_cs = 2048;
//	vref_ct = 2048;
//	soma_vref = 0;
//	nro_soma_vref = 0;
	vrefcr = 2048;
	vrefcs = 2048;
	vrefct = 2048;
	vreftr = 2048;
	vrefts = 2048;
	vreftt = 2048;
	soma_vreft = 0;
	soma_vrefc = 0;
	#if (controlador == true)
		#if (AUTOSET == true)
			time_out_enter = 0;
			time_out_autoset = 0;
			em_autoset = false;
			passo_autoset = 0;
		#endif
	#endif
	#if (com_time_funciona == true)
		aux_l1 = read_long(ee_horas_funcionamento);
		if (aux_l1 == 0xffffffff)
			{
			write_long(ee_horas_funcionamento,0);
			}
			
		aux_l1 = read_long(ee_horas_funcionamento_ant);
		if (aux_l1 == 0xffffffff)
			{
			write_long(ee_horas_funcionamento_ant,0);
			}
		#if (com_relogio == true)
			min_funciona = read_byte(ee_min_funciona);
		#endif
	#endif
	inicializa_flags_alarmes();

	#if (com_menu == true)
		time_out_inicializando = 2;
		time_out_exibe_status_teclando = 10;
	#endif
	
	#if ((st9200r == true) || (st9230r == true))
		#if (com_maximos == true)
			cor_maxima_r = 0;
			cor_maxima_s = 0;
			cor_maxima_t = 0;
			pot_ativa_max_r = 0;
			pot_ativa_max_s = 0;
			pot_ativa_max_t = 0;
		#endif
	#endif

}

void inicializa_programa(void)
{
	ten_nomi = read_word(ee_ten_nomi);
	#if (portatil == true)
		#if (se_com_flex == true)
			tipo_ponteira = read_byte(ee_tipo_ponteira);
			valor_tc = tabela_pt[tipo_ponteira];
			atualiza_ganho(tipo_ponteira);
		#else
			valor_tc = read_word(ee_valor_tc);
		#endif
	#else
		valor_tc = read_word(ee_valor_tc);
	#endif
	if ((ten_nomi == 255) && (valor_tc == 255))
		{
		assume_defaults();
		}

	#if (portatil == true)
		decide_que_ponteira();
	#endif	

	#if (tc_fixo == true)
		#if (portatil == true)
			busca_mul_tc();
		#else
			calcula_mul_tc();
		#endif
	#endif

	valor_tp = read_word(ee_valor_tp); 
	#if (com_regs == true)
		#if (controlador == true)
			intervalo_reg = INTERVALO_REG_DEFAULT;
		#else
			intervalo_reg = read_word(ee_intervalo_reg); 
		#endif
	#endif
 	baud_rate = read_word(ee_baud_rate);

	#if (ade7754 == true)
	
		fase_r = read_byte(ee_fase_r);
		fase_s = read_byte(ee_fase_s);
		fase_t = read_byte(ee_fase_t);
	
		os_ten_r1 = read_word(ee_os_ten_r1);
		os_ten_s1 = read_word(ee_os_ten_s1);
		os_ten_t1 = read_word(ee_os_ten_t1);
	
		reg_cfnum = read_word(ee_reg_cfnum);
		reg_cfdem = read_word(ee_reg_cfdem);
	
		os_pot_r = read_word(ee_os_pot_r);
		os_pot_s = read_word(ee_os_pot_s);
		os_pot_t = read_word(ee_os_pot_t);
	
	#else
		os_ten_r1 = read_byte(ee_os_ten_r1);
		os_ten_r2 = read_byte(ee_os_ten_r2);
		#if (portatil == false)
			off_cor_r = read_byte(ee_off_cor_r);
			off_cor_s = read_byte(ee_off_cor_s);
			#if (prog_defasagem ==	true)
				defasagem = read_byte(ee_defasagem);
			#endif
		#endif
		os_pot_r = read_byte(ee_os_pot_r);
		#if (monofasico == false)
			os_ten_s1 = read_byte(ee_os_ten_s1);
			os_ten_t1 = read_byte(ee_os_ten_t1);
			os_ten_s2 = read_byte(ee_os_ten_s2);
			os_ten_t2 = read_byte(ee_os_ten_t2);

	
			off_cor_s = read_byte(ee_off_cor_s);
			off_cor_t = read_byte(ee_off_cor_t);
	
			os_pot_s = read_byte(ee_os_pot_s);
			os_pot_t = read_byte(ee_os_pot_t);
		#endif
	#endif
 	
	endereco = read_byte(ee_endereco);
 	set_point = read_byte(ee_set_point);
	#if (st8500c == true)
		#if (com_tc == true)
		 	intervalo_integra = read_byte(ee_intervalo_integra);
		 	if (intervalo_integra != 15)
		 		{
			 	intervalo_integra = 15;
			 	write_byte(ee_intervalo_integra, 15);
			 	}
		#endif
	#endif
	#if (CONTROLADOR == false)
	 	intervalo_integra = read_byte(ee_intervalo_integra);
	#else
		status_banco_minimo = 0;
		recupera_tempos_acionamentos();
	#endif
	#if (com_regs == true)
	 	forma_reg_cht = read_byte(ee_forma_reg_cht);
	 	#if (portatil == true)
			registro = read_byte(ee_registro);
			prog_time = read_byte(ee_prog_time);
			dia_liga = read_byte(ee_dia_liga);
			dia_desliga = read_byte(ee_dia_desliga);
			hora_liga = read_byte(ee_hora_liga);
			minuto_liga = read_byte(ee_minuto_liga);
			hora_desliga = read_byte(ee_hora_desliga);
			minuto_desliga = read_byte(ee_minuto_desliga);
			fila_circular = read_byte(ee_fila_circular);
		#else
			registro = 1;
		#endif
	#endif
	tipo_ligacao = read_byte(ee_tipo_ligacao);

	hora_ponta = read_byte(ee_hora_ponta);
	hora_final_ponta = read_byte(ee_hora_final_ponta);
	minuto_ponta = read_byte(ee_minuto_ponta);
	minuto_final_ponta = read_byte(ee_minuto_final_ponta);

	modo_funca = read_byte(ee_modo_funca);

	ala_fp_ind = read_byte(ee_ala_fp_ind);
	ala_fp_cap = read_byte(ee_ala_fp_cap);
	ala_ten_a = read_byte(ee_ala_ten_a);
	ala_ten_b = read_byte(ee_ala_ten_b);
	ala_sc = read_byte(ee_ala_sc);
	ala_subc = read_byte(ee_ala_subc);
	ala_chtt = read_byte(ee_ala_chtt);
	ala_chtc = read_byte(ee_ala_chtc);
	ala_skw = read_byte(ee_ala_skw);

	#if (CONTROLADOR == true) || (st_prog == true)
		cor_minima = read_byte(ee_cor_minima);
		#if (com_rep == true)
			cor_minima_rep = read_word(ee_cor_minima_rep);
			protocolo_REP = read_byte(ee_protocolo_REP);
			if(protocolo_REP > 1){
				baud_rate_REP = 1;
			}
			else{
				baud_rate_REP = 0;
			}
		#endif
		com_des_ten_a = read_byte(ee_com_des_ten_a);
		com_des_ten_b = read_byte(ee_com_des_ten_b);
		com_des_chtt = read_byte(ee_com_des_chtt);
		com_des_chtc = read_byte(ee_com_des_chtc);
		com_des_fp_ind_cap = read_byte(ee_com_des_fp_ind_cap);
		tempo_aciona = read_byte(ee_tempo_aciona);
		tempo_desaciona = read_byte(ee_tempo_desaciona);
		ultimo_tempo_aciona = tempo_aciona;
		
		#if (st8500c == false)
			nro_bancos_capacitor = read_byte(ee_nro_bancos_capacitor);
			vali_nro_bancos_capacitor();	    	
			max_kvar = read_byte(ee_max_kvar);
			min_kvar = read_byte(ee_min_kvar);
			sequencia =	read_byte(ee_sequencia);
			aux_w1 = ee_banco_capacitor_1;
			aux_w2 = ee_tempo_repouso_1;
			for (aux_b1 = 0; aux_b1 < nro_bancos_capacitor; aux_b1++)
				{
				banco_capacitor[aux_b1] = read_byte(aux_w1++);
				tempo_repouso[aux_b1] = read_byte(aux_w2++);
				banco_acionado[aux_b1] = false;
				banco_disponivel[aux_b1] =false;
				#if(st_prog == false)
					desligar_banco(aux_b1);
				#endif
				}
		#endif
		
	#endif

	#if (portatil == true)
		#if (se_com_flex ==	true)
			config_ponteiras();
		#else
			aux_w2 = ee_os_cor_r_20;
			for (aux_b1 = 0; aux_b1 < NRO_POSI_TC; aux_b1++)
				{
				os_cor_pt_r[aux_b1] = read_byte(aux_w2++);
				os_cor_pt_s[aux_b1] = read_byte(aux_w2++);
				os_cor_pt_t[aux_b1] = read_byte(aux_w2++);
				}
			aux_w2 = ee_off_fp_20;
			for (aux_b1 = 0; aux_b1 < NRO_POSI_TC; aux_b1++)
				{
				off_set_fp[aux_b1] = read_byte(aux_w2++);
				}
			aux_w2 = ee_os_pot_r_20;
			for (aux_b1 = 0; aux_b1 < NRO_POSI_TC; aux_b1++)
				{
				os_pot_pt_r[aux_b1] = read_byte(aux_w2++);
				os_pot_pt_s[aux_b1] = read_byte(aux_w2++);
				os_pot_pt_t[aux_b1] = read_byte(aux_w2++);
				}
		#endif
	
	#else
		os_cor_r = read_byte(ee_os_cor_r);		
		#if (monofasico == false)
			os_cor_s = read_byte(ee_os_cor_s);		
			os_cor_t = read_byte(ee_os_cor_t);		
		#endif
	#endif

	#if (st5x == true)
		nro_pisca_led = 0;
		time_led = 0;
	    status_led = 0;
	    status_flags = 0;
	#endif
	 calcula_fundo_escala_corrente();

	#if (com_rep == true)
		modo_rep = read_byte(ee_modo_rep);
		fat_conv_ativa = read_word(ee_fat_conv_ativa);
		fat_conv_reativa = read_word(ee_fat_conv_reativa);
		time_out_modo_rep = 1;
		ultimo_pulso_at = read_word(ee_ultimo_pulso_at);
		ultimo_pulso_reat = read_word(ee_ultimo_pulso_reat);
		ultima_pot_at = read_word(ee_ultima_pot_at);
		ultima_pot_reat = read_word(ee_ultima_pot_reat);
		if (modo_rep == 1)
			{
			fecha_periodo();   
			recupera_rep();
			}
	#endif

	#if (st8500c == true)
		ala_demanda_ativa = read_byte(ee_ala_demanda_ativa);
	#else
		#if (com_alarme_demanda == true)
			ala_demanda_ativa = read_word(ee_ala_demanda_ativa);
		#endif
	#endif

	#if (st5x== true)
		#if (com_saida_pulsos == true)
			const_saida_kw = read_word(ee_const_saida_kw);
			const_saida_kvar = read_word(ee_const_saida_kvar);
			qual_variavel_pulsa = read_byte(ee_qual_variavel_pulsa);
		#endif
	#endif
	

}

#if (com_regs == true)
	void inicializa_regs(void)
	{	
		aux_l2 = 0;
		aux_l2 = (int32)(hora);
		aux_w1 = (int16)(minuto);
		aux_l2 = (int32)(aux_l2 * 3600);
		aux_w1 = (int16)(aux_w1 * 60);
		aux_l2 = (int32)(aux_l2 + aux_w1);
		aux_l2 = (int32)(aux_l2 + segundo);
		aux_l2 = (int32)(aux_l2 / intervalo_reg);
		aux_l2 = (int32)(aux_l2 * intervalo_reg);
		}
#endif	

/* rotinas de configuraÿçÿão */

void le_config(void)
{
/* carrega variaveis nÿão volÿáteis da e2prom */

/* 	inicializa variÿáveis volÿáteis */
	
	
/* calcula checksum das variÿáveis */

	calcula_checksum_vars() ;
}

void calcula_checksum_vars (void)
{
	checksum_vars = 0;
}

void verifica_checksum_vars(void)
{
	aux_b1 = checksum_vars;
	calcula_checksum_vars();
	if (aux_b1 != checksum_vars)
		{
		le_config();
		}
}




#if (com_cht == true)
	void zera_chts(void)
	{
		for ( aux_b1 = 0; aux_b1 < (NRO_CHT + 1); aux_b1++)
			{
			pulsa_wdt();
			CHT_tr[aux_b1] = 0;
			CHT_cr[aux_b1] = 0;
			#if (monofasico == false)
				CHT_ts[aux_b1] = 0;
				CHT_cs[aux_b1] = 0;
				CHT_tt[aux_b1] = 0;
			 	CHT_ct[aux_b1] = 0;
			#endif
			}
		 passo_cht = 1;
		 qcht = 0;
	
	}
#endif

	
