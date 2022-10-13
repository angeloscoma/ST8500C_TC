/****************************************************************************
* Empresa: SULTECH SISTEMAS ELETRÔNICOS										*
* Modulo: ST_E2P															*
* Funcao: MODULO DEFINIÇÃO VARIAVEIS EM E2P									*
* Responsavel: VAGNER SANTOS												*
* Modificado ; VAGNER SANTOS												*
* Inicio: 06/06/2003														*
* Revisao: RENGAV ARIERREF SOD SOTNAS										*
*****************************************************************************/



/* definicao de variaveis não voláteis, gravadas na e2prom */
/* definicacao de variaveis  na e2prom */
#define ee_passo_main				0
#define endereco_modbus_e2p			2
#define baud_rate_e2p				4
#define ee_off_cor_r		6
#define ee_off_cor_s		7
#define ee_off_cor_t		8
#define ee_set_point		10
#define ee_os_cor_r			11
#define ee_os_cor_s			12
#define ee_os_cor_t			13
#define ee_os_ten_r1		14
#define ee_os_ten_s1		15
#define ee_os_ten_t1		16
#define ee_ten_nomi			17

#if (portatil == true)
	#if (se_com_flex == true)
		#define ee_tipo_ponteira	19
	#else
		#define ee_valor_tc			19
	#endif
#else
	#define ee_valor_tc			19
#endif

#define ee_os_ten_r2		21
#define ee_os_ten_s2		22
#define ee_os_ten_t2		23

#define ee_defasagem		24
#define ee_qual_variavel_pulsa	25


#define ee_ala_fp_ind		28
#define ee_ala_fp_cap		29
#define ee_ala_ten_a		30
#define ee_ala_ten_b		31
#define ee_ala_sc			32
#define ee_ala_chtt			33
#define ee_ala_chtc			34
#define ee_des_fp_ind		35
#define ee_des_ten_a		36
#define ee_des_cht			37
#define ee_endereco			38
#define ee_intervalo_reg    39
#define ee_intervalo_integra 	41
#define ee_forma_reg_cht	42
#define ee_valor_tp 		43
#define ee_baud_rate		45
#define ee_registro			47
#define ee_prog_time		48
#define ee_dia_liga			49
#define ee_dia_desliga		50
#define ee_hora_liga		51
#define ee_minuto_liga		52
#define ee_hora_desliga		53
#define ee_minuto_desliga	54
#define ee_fila_circular	55
#define ee_banco_escrita    56
#define ee_banco_leitura	57
#define ee_hora_ponta		58
#define ee_minuto_ponta		59
#define ee_hora_final_ponta	60
#define ee_minuto_final_ponta	61
#define ee_tipo_ligacao		62
#define ee_ala_subc			63
#define ee_modo_funca		64
#define ee_idioma			65
#define ee_ala_skw			66
#define ee_fase_r			67
#define ee_fase_s			68
#define ee_fase_t			69

#define ee_os_pot_r			70
#define ee_os_pot_s			71
#define ee_os_pot_t			72

#if (st8500c == true)
	#define ee_ala_demanda_ativa	73
	#define ee_saida2				74
	#define ee_saida3				75
	#define ee_modo_saidas			76
#else
	#define ee_ala_demanda_ativa	73
#endif
#if (st5x== true)
	#if (com_saida_pulsos == true)
	 	#define ee_const_saida_kw	75
		#define ee_const_saida_kvar 77
	#endif
#endif

#define ee_tipo_controle_demanda	79												// 1byte define se demanda por FILO  ou Fila circular
#define ee_forma_controle			80												// 16 bytes - tabela definição se carga controlável ou por horário
#define ee_hora_liga_controle		(ee_forma_controle + NRO_MAXIMO_CARGAS)			// 16 bytes - tabela de horarios de funcionamento
#define ee_minuto_liga_controle		(ee_hora_liga_controle + NRO_MAXIMO_CARGAS)		// 17 bytes - tabela de horarios de funcionamento
#define ee_hora_desliga_controle	(ee_minuto_liga_controle + NRO_MAXIMO_CARGAS)	// 16 bytes - tabela de horarios de funcionamento
#define ee_minuto_desliga_controle	(ee_hora_desliga_controle + NRO_MAXIMO_CARGAS)	// 17 bytes - tabela de horarios de funcionamento


#define ee_dia				236
#define ee_mes				237
#define ee_ano				238
#define ee_hora				239
#define ee_minuto			240

#define ee_ptr_regs			242			
#define ee_ptr_rocor		244			
#define ee_ptr_cht			246			

#define final_variaveis		250

#define ee_dem_maxima_aparente_ant 	252
#define ee_dem_maxima_ativa_ant		254
#define ee_dem_maxima_aparente		256
#define ee_dem_maxima_ativa			258


#define ee_consumo_ati			260		//4 bytes
#define ee_consumo_reati		264		//4 bytes
#define ee_consumo_ati_ant		268	//4bytes
#define ee_consumo_reati_ant	272	//4bytes
#define ee_consumo_l			276
#define ee_consumo_h			278
#define ee_consumo_rea_l		280
#define ee_consumo_rea_h		282
#define ee_consumo_ati_tmp_ant	284
#define	ee_consumo_reati_tmp_ant	286
#define ee_consumo_l_p			288
#define ee_consumo_h_p			290
#define ee_consumo_rea_l_p		292
#define ee_consumo_rea_h_p		294

#define ee_fatura_rep		299		//1 byte paraverificaçaõ do fechamento de fatura
#if (com_rep == true)
	#define ee_int_ativa	300 												// (NRO_INTERVALOS_INTEGRACAO * 4) bytes int 
	#define ee_int_reativa  ee_int_ativa + (NRO_INTERVALOS_INTEGRACAO * 4)		// NRO_INTERVALOS_INTEGRACAO * 2) bytes int 
#endif
#if (com_tc == true)
	#define ee_buf_dem_ativa		400		// 60 word de 16 bits
	#define ee_buf_dem_aparente		520	// 60 word de 16 bits
#endif

// endereços exclusivod dos controladores
#if (st8500c == true)
	#define ee_max_kw				641
	#define ee_min_kw				642
#else
	#define ee_max_kvar				641
	#define ee_min_kvar				642
#endif
#define ee_tempo_aciona			643
#define ee_tempo_desaciona		644
#define ee_sequencia			645
#define ee_modo_rep				646


#define ee_minuteiro			650		// 16 bytes
#define ee_horimetro			666		// 16 words(32 bytes)
#define ee_acionamentos			698		// 16 words(32 bytes)
#define ee_tempo_repouso_1		730		// 16 bytes



#define ee_com_des_ten_a		746
#define ee_com_des_chtt			747	
#define ee_com_des_chtc			748
#define ee_com_des_fp_ind_cap	749
#define ee_cor_minima			750
#define ee_com_des_ten_b		751

#if (st8500c == true)
	#define ee_carga_1	755
	#define ee_carga_2	756
	#define ee_carga_3	757
	#define ee_carga_4	758
	#define ee_carga_5	759
	#define ee_carga_6	760
	#define ee_carga_7	761
	#define ee_carga_8	762
	#define ee_carga_9	763
	#define ee_carga_10	764
	#define ee_carga_11	765
	#define ee_carga_12	766
	#define ee_carga_13	767
	#define ee_carga_14	768
	#define ee_carga_15	769
	#define ee_carga_16	770
#else
	#define ee_banco_capacitor_1	755
	#define ee_banco_capacitor_2	756
	#define ee_banco_capacitor_3	757
	#define ee_banco_capacitor_4	758
	#define ee_banco_capacitor_5	759
	#define ee_banco_capacitor_6	760
	#define ee_banco_capacitor_7	761
	#define ee_banco_capacitor_8	762
	#define ee_banco_capacitor_9	763
	#define ee_banco_capacitor_10	764
	#define ee_banco_capacitor_11	765
	#define ee_banco_capacitor_12	766
	#define ee_banco_capacitor_13	767
	#define ee_banco_capacitor_14	768
	#define ee_banco_capacitor_15	769
	#define ee_banco_capacitor_16	770
#endif

#if (st8500c == true)
	#define ee_nro_cargas	787
#else
	#define ee_nro_bancos_capacitor	787
#endif

#if (controlador == true)
	#define ee_ptr_ocor				788	
	#if (st8500c == false)
		#define ee_ocorrencias		790		//100 posições
	#else
		#define ee_dem_cont_ponta		790
		#define ee_dem_cont_fora_ponta		ee_dem_cont_ponta + 24
	#endif
#endif


#define ee_nro_1			892
#define ee_nro_2			893
#define ee_nro_3			894
#define ee_nro_4			895

#define ee_bits_menu		896
	#define EE_M1_C1		0
	#define EE_M1_C2		1
	#define EE_M1_C3		2
	#define EE_M1_C4		3
	#define EE_M1_C5		4
	#define EE_M1_C6		5
	#define EE_M1_C7		6
	#define EE_M1_C8		7

#define ee_bits_menu2		897	
	#define EE_MENU_FIXO		0
	#define EE_EXISTE_LOCAL		1
	#define EE_DIGITOU_TEXTO	2

#define ee_menu_aux			898
#define ee_qmenu			899
#define ee_menu1			900



#if (com_rep == true)
	#define ee_cor_minima_rep 		902

	#define ee_ultima_pot_at		904		// 2 bytes
	#define ee_ultima_pot_reat		906		// 2 bytes
	
	#define ee_fat_conv_ativa		908
	#define ee_fat_conv_reativa		910
	#define ee_ultimo_pulso_at		912
	#define ee_ultimo_pulso_reat	914
#endif
#if (com_time_funciona == true)
	#define ee_horas_funcionamento		916		// 4 bytes (int32)
	#define ee_horas_funcionamento_ant	920		// 4 bytes (int32)
	#define ee_min_funciona				924		// 1 byte
#endif
#if (com_relogio == false)
	#define ee_tabela_minuto	930			// 60 posicoes para salvar minutos  /final em 990
#endif


#if (portatil == true)
	#define ee_localizacao_0	980
	#define ee_localizacao_1	981
	#define ee_localizacao_2	982
	#define ee_localizacao_3	983
	#define ee_localizacao_4	984
	#define ee_localizacao_5	985
	#define ee_localizacao_6	986
	#define ee_localizacao_7	987
	#define ee_localizacao_8	988
	#define ee_localizacao_9	989
	#define ee_localizacao_10	990
	#define ee_localizacao_11	991
	#define ee_localizacao_12	992
	#define ee_localizacao_13	993
	#define ee_localizacao_14	994
	#define ee_localizacao_15	995
	#define ee_localizacao_16	996
#else
	#if (com_consumo_aparente == true)
		#define ee_consumo_apa_l_p	980
		#define ee_consumo_apa_h_p	982
		#define ee_consumo_apa_l	984
		#define ee_consumo_apa_h	986
	#endif
#endif
#if (st8500c == true)
	#define ee_carga_programada	988
	#define ee_dia_inicio_pc	990
	#define ee_mes_inicio_pc	991
	#define ee_dia_final_pc		992
	#define ee_mes_final_pc		993
#endif

#if (com_rep)
	#define ee_protocolo_REP	994
	#define ee_baud_rate_REP	995
#endif

#define ee_bloqueio_gravacao	1000
