/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_E2P                                                        *
; Funcao: MODULO DEFINIÇÃO VARIAVEIS EM E2P
;		By Sultech For AGST
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 06/06/2003                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/



/* definicao de variaveis não voláteis, gravadas na e2prom */
/* definicacao de variaveis  na e2prom */
#define ee_passo_main			0
#define endereco_modbus_e2p		2
#define baud_rate_e2p			4
#define ee_off_cor_r			6
#define ee_off_cor_s			7
#define ee_off_cor_t			8
#define ee_set_point			10
#define ee_os_cor_r				11
#define ee_os_cor_s				12
#define ee_os_cor_t				13
#define ee_os_ten_r1			14
#define ee_os_ten_s1			15
#define ee_os_ten_t1			16
#define ee_ten_nomi			24

#if (se_com_flex == true)
	#define ee_tipo_ponteira	26
#else
	#define ee_valor_tc			26
#endif


#define ee_ala_fp_ind		28
#define ee_ala_fp_cap		29
#define ee_ala_ten_a		30
#define ee_ala_ten_b		31
#define ee_ala_sc			32
#define ee_ala_chtt			33
#define ee_ala_chtc			34
#define ee_des_fp_cap		35
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

#if (se_com_flex ==	true)
		#define ee_os_cor_r_9001g1		70
		#define ee_os_cor_s_9001g1		71
		#define ee_os_cor_t_9001g1		72
		#define ee_os_cor_r_9001g2		73
		#define ee_os_cor_s_9001g2		74
		#define ee_os_cor_t_9001g2		75
		#define ee_os_cor_r_9002g1		76
		#define ee_os_cor_s_9002g1		77
		#define ee_os_cor_t_9002g1		78
		#define ee_os_cor_r_9003g1		79
		#define ee_os_cor_s_9003g1		80
		#define ee_os_cor_t_9003g1		81
		#define ee_os_cor_r_9004g1		82
		#define ee_os_cor_s_9004g1		83
		#define ee_os_cor_t_9004g1		84
		#define ee_os_cor_r_9005g1		85
		#define ee_os_cor_s_9005g1		86
		#define ee_os_cor_t_9005g1		87
		#define ee_os_cor_r_9005g2		88
		#define ee_os_cor_s_9005g2		89
		#define ee_os_cor_t_9005g2		90
		#define ee_os_cor_r_9005g3		91
		#define ee_os_cor_s_9005g3		92
		#define ee_os_cor_t_9005g3		93
		#define ee_os_cor_r_9005g4		94
		#define ee_os_cor_s_9005g4		95
		#define ee_os_cor_t_9005g4		96
		#define ee_os_cor_r_9005g5		97
		#define ee_os_cor_s_9005g5		98
		#define ee_os_cor_t_9005g5		99
		#define ee_os_cor_r_9006g1		100
		#define ee_os_cor_s_9006g1		101
		#define ee_os_cor_t_9006g1		102
		#define ee_os_cor_r_9006g2		103
		#define ee_os_cor_s_9006g2		104
		#define ee_os_cor_t_9006g2		105
		#define ee_os_cor_r_9006g3		106
		#define ee_os_cor_s_9006g3		107
		#define ee_os_cor_t_9006g3		108
		#define ee_os_cor_r_9006g4		109
		#define ee_os_cor_s_9006g4		110
		#define ee_os_cor_t_9006g4		111
		#define ee_os_cor_r_9006g5		112
		#define ee_os_cor_s_9006g5		113
		#define ee_os_cor_t_9006g5		114
		#define ee_os_cor_r_9007g1		115
		#define ee_os_cor_s_9007g1		116
		#define ee_os_cor_t_9007g1		117
		#define ee_os_cor_r_9007g2		118
		#define ee_os_cor_s_9007g2		119
		#define ee_os_cor_t_9007g2		120
		#define ee_os_cor_r_9008g1		121
		#define ee_os_cor_s_9008g1		122
		#define ee_os_cor_t_9008g1		123
		#define ee_os_cor_r_9009g1		124
		#define ee_os_cor_s_9009g1		125
		#define ee_os_cor_t_9009g1		126
		#define ee_os_cor_r_9009g2		127
		#define ee_os_cor_s_9009g2		128
		#define ee_os_cor_t_9009g2		129
		
		#define ee_off_fp_9001g1		130
		#define ee_off_fp_9001g2		131
		#define ee_off_fp_9002g1		132
		#define ee_off_fp_9003g1		133
		#define ee_off_fp_9004g1		134
		#define ee_off_fp_9005g1		135
		#define ee_off_fp_9005g2		136
		#define ee_off_fp_9005g3		137
		#define ee_off_fp_9005g4		138
		#define ee_off_fp_9005g5		139
		#define ee_off_fp_9006g1		140
		#define ee_off_fp_9006g2		141
		#define ee_off_fp_9006g3		142 
		#define ee_off_fp_9006g4		143
		#define ee_off_fp_9006g5		144
		#define ee_off_fp_9007g1		145
		#define ee_off_fp_9007g2		146
		#define ee_off_fp_9008g1		147
		#define ee_off_fp_9009g1		148
		#define ee_off_fp_9009g2		149
	
		#define ee_os_pot_r_9001g1		150
		#define ee_os_pot_s_9001g1		151
		#define ee_os_pot_t_9001g1		152
		#define ee_os_pot_r_9001g2		153
		#define ee_os_pot_s_9001g2		154
		#define ee_os_pot_t_9001g2		155
		#define ee_os_pot_r_9002g1		156
		#define ee_os_pot_s_9002g1		157
		#define ee_os_pot_t_9002g1		158
		#define ee_os_pot_r_9003g1		159
		#define ee_os_pot_s_9003g1		160
		#define ee_os_pot_t_9003g1		161
		#define ee_os_pot_r_9004g1		162
		#define ee_os_pot_s_9004g1		163
		#define ee_os_pot_t_9004g1		164
		#define ee_os_pot_r_9005g1		165
		#define ee_os_pot_s_9005g1		166
		#define ee_os_pot_t_9005g1		167
		#define ee_os_pot_r_9005g2		168
		#define ee_os_pot_s_9005g2		169
		#define ee_os_pot_t_9005g2		170
		#define ee_os_pot_r_9005g3		171
		#define ee_os_pot_s_9005g3		172
		#define ee_os_pot_t_9005g3		173
		#define ee_os_pot_r_9005g4		174
		#define ee_os_pot_s_9005g4		175
		#define ee_os_pot_t_9005g4		176
		#define ee_os_pot_r_9005g5		177
		#define ee_os_pot_s_9005g5		178
		#define ee_os_pot_t_9005g5		179
		#define ee_os_pot_r_9006g1		180
		#define ee_os_pot_s_9006g1		181
		#define ee_os_pot_t_9006g1		182
		#define ee_os_pot_r_9006g2		183
		#define ee_os_pot_s_9006g2		184
		#define ee_os_pot_t_9006g2		185
		#define ee_os_pot_r_9006g3		186
		#define ee_os_pot_s_9006g3		187
		#define ee_os_pot_t_9006g3		188
		#define ee_os_pot_r_9006g4		189
		#define ee_os_pot_s_9006g4		190
		#define ee_os_pot_t_9006g4		191
		#define ee_os_pot_r_9006g5		192
		#define ee_os_pot_s_9006g5		193
		#define ee_os_pot_t_9006g5		194
		#define ee_os_pot_r_9007g1		195
		#define ee_os_pot_s_9007g1		196
		#define ee_os_pot_t_9007g1		197
		#define ee_os_pot_r_9007g2		198
		#define ee_os_pot_s_9007g2		199
		#define ee_os_pot_t_9007g2		201
		#define ee_os_pot_r_9008g1		202
		#define ee_os_pot_s_9008g1		202
		#define ee_os_pot_t_9008g1		203
		#define ee_os_pot_r_9009g1		204
		#define ee_os_pot_s_9009g1		205
		#define ee_os_pot_t_9009g1		206
		#define ee_os_pot_r_9009g2		207
		#define ee_os_pot_s_9009g2		208
		#define ee_os_pot_t_9009g2		209
#else
		#define ee_os_cor_r_20		70
		#define ee_os_cor_s_20		71
		#define ee_os_cor_t_20		72
		#define ee_os_cor_r_200		73
		#define ee_os_cor_s_200		74
		#define ee_os_cor_t_200		75
		#define ee_os_cor_r_300		76
		#define ee_os_cor_s_300		77
		#define ee_os_cor_t_300		78
		#define ee_os_cor_r_600		79
		#define ee_os_cor_s_600		80
		#define ee_os_cor_t_600		81
		#define ee_os_cor_r_1000	82
		#define ee_os_cor_s_1000	83
		#define ee_os_cor_t_1000	84
		#define ee_os_cor_r_1500	85
		#define ee_os_cor_s_1500	86
		#define ee_os_cor_t_1500	87
		#define ee_os_cor_r_2000	88
		#define ee_os_cor_s_2000	89
		#define ee_os_cor_t_2000	90
		#define ee_os_cor_r_3000	91
		#define ee_os_cor_s_3000	92
		#define ee_os_cor_t_3000	93
		#define ee_os_cor_r_6000	94
		#define ee_os_cor_s_6000	95
		#define ee_os_cor_t_6000	96
		
		#define ee_off_fp_20		100
		#define ee_off_fp_200		101
		#define ee_off_fp_300		102
		#define ee_off_fp_600		103
		#define ee_off_fp_1000		104
		#define ee_off_fp_1500		105
		#define ee_off_fp_2000		106
		#define ee_off_fp_3000		107
		#define ee_off_fp_6000		108
	
		#define ee_os_pot_r_20		110
		#define ee_os_pot_s_20		111
		#define ee_os_pot_t_20		112
		#define ee_os_pot_r_200		113
		#define ee_os_pot_s_200		114
		#define ee_os_pot_t_200		115
		#define ee_os_pot_r_300		116
		#define ee_os_pot_s_300		117
		#define ee_os_pot_t_300		118
		#define ee_os_pot_r_600		119
		#define ee_os_pot_s_600		120
		#define ee_os_pot_t_600		121
		#define ee_os_pot_r_1000	122
		#define ee_os_pot_s_1000	123
		#define ee_os_pot_t_1000	124
		#define ee_os_pot_r_1500	125
		#define ee_os_pot_s_1500	126
		#define ee_os_pot_t_1500	127
		#define ee_os_pot_r_2000	128
		#define ee_os_pot_s_2000	129
		#define ee_os_pot_t_2000	130
		#define ee_os_pot_r_3000	131
		#define ee_os_pot_s_3000	132
		#define ee_os_pot_t_3000	133
		#define ee_os_pot_r_6000	134
		#define ee_os_pot_s_6000	135
		#define ee_os_pot_t_6000	136
#endif


#define ee_os_pot_r			230
#define ee_os_pot_s			232
#define ee_os_pot_t			234

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


//#define ee_consumo_ati			260		//4 bytes
//#define ee_consumo_rea			264		//4 bytes
#define ee_consumo_ati_ant		268
#define ee_consumo_reati_ant		272
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


#define ee_int_ativa	300		/* 30 bytes int */
#define ee_int_reativa  360		/* 30 bytes int */

#define ee_buf_dem_ativa		400		// 60 word de 16 bits
#define ee_buf_dem_aparente		520		// 60 word de 16 bits

// endereços exclusivod dos controladores
#define ee_max_kvar				641
#define ee_min_kvar				642
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
#define ee_com_des_fp_cap		749
#define ee_cor_minima			750
#define ee_saida1				751
#define ee_saida2				752
#define ee_saida3				753
#define ee_saida4				754

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


#define ee_nro_bancos_capacitor	787

#define ee_ptr_ocor			788	
#define ee_ocorrencias		789		//100 posições


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



#define ini_ee_cs5460		910

#define ee_off_set_vrms_a	950
#define ee_off_set_vrms_b	952
#define ee_off_set_vrms_c	954
#define ee_ganho_a_ade7754	956
#define ee_ganho_b_ade7754	958
#define ee_ganho_c_ade7754	960
#define ee_off_set_freq		966
#define ee_reg_cfnum		968
#define ee_reg_cfdem		970

#define ee_os_ten_r2		972
#define ee_os_ten_s2		974
#define ee_os_ten_t2		976

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
#endif
#if (com_relogio == false)
	#define ee_tabela_minuto	930			// 60 posicoes para salvar minutos
#endif

#define ee_fat_conv_ativa		990
#define ee_fat_conv_reativa		992


#define ee_bloqueio_gravacao	1000
