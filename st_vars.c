/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRONICOS                                  *
; Modulo: ST_VARS                                                        *
; Funcao: MODULO DEFINICAO DE VARIAVEIS         						 *
;		By Sultech 														 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 06/06/2003                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/

#define word int16

#define PORTUGUES   0
#define ESPANHOL	1
#define INGLES		2

#define LIMITE_VAL_PWM 512

#define nro_ocorrencia  20
#if (home_system == true)
	#define TAM_RX  10
	#define TAM_TX 	10
#else
	#define TAM_RX  32
	#define TAM_TX 	254
#endif

#if (st5000t == true)
	#if (home_system == true)
		#define NRO_CHT 		12	//23
		#define NRO_CHT_BY_2	6	//11
	#else
		#define NRO_CHT 		49	//23
		#define NRO_CHT_BY_2	23	//11
	#endif
#elif (st5030t == true)
	#define NRO_CHT 		49	//23
	#define NRO_CHT_BY_2	23	//11
#elif (st92 == true)
	#define NRO_CHT 		49	//23
	#define NRO_CHT_BY_2	23	//11
#elif (st9400r == true)
	#define NRO_CHT 		49	//23
	#define NRO_CHT_BY_2	23	//11
#elif (st9430r == true)
	#define NRO_CHT 		49	//23
	#define NRO_CHT_BY_2	23	//11
#elif (ST8100C == true)
	#define NRO_CHT 		12	
	#define NRO_CHT_BY_2	5
#elif (ST8200C == true)
	#define NRO_CHT 		12	
	#define NRO_CHT_BY_2	5
#elif (ST8300C == true)
	#define NRO_CHT 		12	
	#define NRO_CHT_BY_2	5
#elif (st9600r == true)
	#if (teste_vag == true)
		#define NRO_CHT 		49/2
		#define NRO_CHT_BY_2	23/2
	#else
		#define NRO_CHT 		49	
		#define NRO_CHT_BY_2	23
	#endif
#else
	#define NRO_CHT 		49
	#define NRO_CHT_BY_2	23
#endif

#define off_cor_delta	16

#if (st5000t == true)
	#if (ade7754 == true)
		#define NRO_AMOSTRAS 	54
	#else
		#define NRO_AMOSTRAS 	64
	#endif
#elif (st5030t == true)
	#if (ade7754 == true)
		#define NRO_AMOSTRAS 	54
	#else
		#define NRO_AMOSTRAS 	64
	#endif
#elif (st92 == true)
	#define NRO_AMOSTRAS 	64
#elif (st9400r == true)
	#if (ade7754 == true)
		#define NRO_AMOSTRAS 	54
	#else
		#define NRO_AMOSTRAS 	64
	#endif
#elif (st9430r == true)
	#if (ade7754 == true)
		#define NRO_AMOSTRAS 	54
	#else
		#define NRO_AMOSTRAS 	64
	#endif
#elif (st9600r == true)
	#define NRO_CICLOS		16
	#define NRO_AMOSTRAS_MODO3 	16
	#define NRO_AMOSTRAS 	64
#else
	#define NRO_AMOSTRAS 	64
#endif

#if (ade7754 == true)
	#define NRO_AMOSTRAS_CHT 54
#else
	#define NRO_AMOSTRAS_CHT 120
//	#define NRO_AMOSTRAS_CHT 40
#endif


#define nro_media_amostras 2			// Sempre múltiplo de 2 (2,4,8,16,32,64,128,256).

#if (nro_media_amostras == 2)
	#define nro_desloca	1
#endif
#if (nro_media_amostras == 4)
	#define nro_desloca	2
#endif
#if (nro_media_amostras == 8)
	#define nro_desloca	3
#endif
#if (nro_media_amostras == 16)
	#define nro_desloca	4
#endif
#if (nro_media_amostras == 32)
	#define nro_desloca	5
#endif
#if (nro_media_amostras == 64)
	#define nro_desloca	6
#endif
#if (nro_media_amostras == 128)
	#define nro_desloca	7
#endif
#if (nro_media_amostras == 256)
	#define nro_desloca	8
#endif
#define nro_medias 2
#define NRO_POSI_TEN	3
#if (portatil == TRUE)
	#if (ponteira_kyoritsu == true)
		#define NRO_POSI_TC		6
	#elif (viercon == true)
		#define NRO_POSI_TC		3
	#else
		#define NRO_POSI_TC		9
	#endif
	#define NRO_POSI_TABELA_TIPO_PT	21
#else
	#define NRO_POSI_TC		37
#endif
#define NRO_POSI_BAUD		6

#define valor_tc_fixo	500
#define nro_alarmes 7

/***************************************** Definição dos Menus **************************************/

#if (com_rep == true)
	#define NRO_MODOS_MEDICAO 2
#endif

#if (ST8100C == true)
	#define nro_menus 12
	#if (com_rep == true)
		#define nro_menus1 14+4
		#define nro_menus4_rep 11
	#else
		#define nro_menus1 10
	#endif
	#define nro_menus2 NRO_CHT
	#define nro_menus3 NRO_CHT
	#define nro_menus4 	7
	#define nro_menus5 	8
	#define nro_menus7	5
	#define nro_menu_bancos	9
	#define nro_menus11 5
	
#elif (ST8200C == true)
	#define nro_menus 12
	#if (com_rep == true)
		#define nro_menus1 11
		#define nro_menus4_rep 12
	#else
		#define nro_menus1 9
	#endif
	#define nro_menus2 NRO_CHT
	#define nro_menus3 NRO_CHT
	#if (prog_defasagem ==	true)
		#define nro_menus4 	8
	#else
		#define nro_menus4 	7
	#endif
	#define nro_menus5 	8
	#define nro_menus7	5
	#define nro_menu_bancos	8
	#define nro_menus11 2
	
#elif (ST8300C == true)
	#define nro_menus 12
	#if (com_rep == true)
		#if (com_consumo == true)
			#define nro_menus1 12
		#else
			#define nro_menus1 11
		#endif
		#define nro_menus4_rep 11
	#else
		#if (com_consumo == true)
			#define nro_menus1 11
		#else
			#define nro_menus1 10
		#endif
	#endif
	#define nro_menus2 NRO_CHT
	#define nro_menus3 NRO_CHT
	#if (prog_defasagem ==	true)
		#define nro_menus4 	8
	#else
		#define nro_menus4 	7
	#endif
	#define nro_menus5 	9
	#define nro_menus7	5
	#define nro_menu_bancos	8
	#define nro_menus11 2
#elif (ST8500C == true)
	#define nro_menus 12
	#if (pci_mono == true)
		#define nro_menus1 23
	#else
		#if (com_rep == true)
			#define nro_menus1 16
		#endif
		#if (com_tc == true)
			#define nro_menus1 13
		#endif
	#endif
		#if (com_rep == true)
			#define nro_menus4 	17
		#else
			#define nro_menus4 	16
		#endif
	#define nro_menus2	NRO_CHT
	#define nro_menus5 	8
	#define nro_menus6 	5
	#define nro_menus7	4
	#define nro_menu_bancos	8
	#define nro_menus11 2
	
#elif (st9400r == true)
	#define nro_menus	7
	#define nro_menus1	18 + com_time_funciona 
	#define nro_menus2	NRO_CHT
	#define nro_menus3	NRO_CHT
	#define nro_menus4	15
	#define nro_menus5 	9
	#define nro_menus6 	6
	#define nro_menus7	4
	
#elif (st9430r == true)
	#define nro_menus	7
	#define nro_menus1	18 + com_time_funciona
	#define nro_menus2	NRO_CHT
	#define nro_menus3	NRO_CHT
	#define nro_menus4	15
	#define nro_menus5 	9
	#define nro_menus6 	6

#elif (st9200r == true)
	#define nro_menus	7
	#define nro_menus1	18 + com_time_funciona + (com_maximos * 2)
	#define nro_menus2	NRO_CHT
	#define nro_menus3	NRO_CHT
	#define nro_menus4	12
	#define nro_menus5	9
	#define nro_menus6	5
	#define nro_menus7	4

#elif (st9230r == true)
	#define nro_menus	7
	#define nro_menus1	19 + com_time_funciona  + (com_maximos * 2)
	#define nro_menus2	NRO_CHT
	#define nro_menus3	NRO_CHT
	#define nro_menus4	12
	#define nro_menus5	9
	#define nro_menus6 	5
	#define nro_menus7	4

#else
	#define nro_menus	6
	#define nro_menus1	19
	#define nro_menus2	NRO_CHT
	#define nro_menus3	NRO_CHT
	#if (funcao_505 == true)
		#define nro_menus4 17
	#else
		#define nro_menus4 16
	#endif
	#define nro_menus5	12
	#define nro_menus6	2
	#define nro_menus7	4
#endif

#define PERIODO_PONTA		1
#define PERIODO_FORA_PONTA	2


/***************************************** Fim Definicao dos Menus **************************************/

#if (com_menu == true)
	// variaveis de controle dos menu
	char idioma;
	char time_out_exibe_status_teclando;				
	char time_out_inicializando;
	
	char passo_exibe_erro;
	char time_out_menus;
	#define VAL_TIME_OUT_MENUS		60;
	#define VAL_TIME_OUT_MENUS1		10;
	word teclas;
//	word media_teclas;
	//char cont_teclas;
	//char ultima_tecla;
	char acelera_teclado;
	char menu1;
	char menu_aux;
	#if (com_cht== true)
		char qchtt;
		char qchtt_impar;
	#endif
	char time_tecla;
	char teclando_2;
	char teclando;
	char qmenu;

	char aux_texto;
	char caracter_texto;

	#if (disp_7seg == true)
		char ptr_buf;
		char ptr_rola;
		char ultima_mens;
		char ultimo_tipo;
	#endif

#endif

/* Definicao das memorias em uso na placa */
#if (com_regs == true)
// sobre ocorrencias
	#if (st8500c == true)
		#define limite_ocorrencias 250
	#else
		#define limite_ocorrencias 100
	#endif
// sobre registros
	#if (funcao_505 == true)
		#define nro_modos	2
	#else
		#define nro_modos	1
	#endif
// modo 0 ou 1
	#define TAM_REGS 	32
	#if ((st5030t == true) || (st9430r == true) || (st9230r == true))
		#if ((SST25VF080 == true) || (SST25LF080 == true))
			#define	nro_bancos 	4
		#else
			#define	nro_bancos  2
		#endif
	#elif (controlador == true)
		#if (st8500c == true)
			#define	nro_bancos  1
		#else
			#if ((SST25VF080 == true) || (SST25LF080 == true))
				#define	nro_bancos 	4
			#else
				#define	nro_bancos  2
			#endif
		#endif
	#else
		#if ((SST25VF080 == true) || (SST25LF080 == true))
			#define	nro_bancos 	16
		#else
			#define	nro_bancos  8
		#endif
	#endif
	
	#if (st8500c == true)
		#define nro_registros_por_banco		15000
		#define addr_inicio_coleta_regs		15000
		#define addr_inicio_coleta_ocor		100 + (addr_inicio_coleta_regs + nro_registros_por_banco)
		#define addr_inicio_coleta_cht		0
	#else
		#define nro_registros_por_banco		6176
		#define addr_inicio_coleta_regs		1000
		#define addr_inicio_coleta_ocor		7200
		#define addr_inicio_coleta_cht		8000 
	#endif
	#define	limite_registros (nro_registros_por_banco * nro_bancos)
	#define inicio_ocorrencias  (limite_registros * 32) + 4096

// modo 2
	#define TAM_REGS_MODO2 	32
	#if ((st5030t == true) || (st9430r == true) || (st9230r == true))
		#if ((SST25VF080 == true) || (SST25LF080 == true))
			#define	nro_bancos_modo2  	4
		#else
			#define	nro_bancos_modo2  	2
		#endif
	#elif (controlador == true)
		#if ((SST25VF080 == true) || (SST25LF080 == true))
			#define	nro_bancos_modo2 	4
		#else
			#define	nro_bancos_modo2  	2
		#endif
	#else
		#if ((SST25VF080 == true) || (SST25LF080 == true))
			#define	nro_bancos_modo2 	16
		#else
			#define	nro_bancos_modo2  	8
		#endif
	#endif
	#define nro_registros_por_banco2	6176
	#define	limite_registros_modo2 (nro_registros_por_banco2 * nro_bancos_modo2)

	#define final_ocor_modo2	((limite_registros_modo2 * TAM_REGS_MODO2) + 4096 ) + (TAM_REGS * limite_ocorrencias)

// modo 3
	#define TAM_REGS_MODO3	16
	#if ((st5030t == true) || (st9430r == true) || (st9230r == true))
		#define nro_bancos_modo3	nro_bancos * 2
	#elif (controlador == true)
		#define nro_bancos_modo3	nro_bancos * 2
	#else
		#define nro_bancos_modo3	nro_bancos * 2
	#endif

	#define	limite_registros_modo3 (nro_registros_por_banco * nro_bancos_modo3)

	#if ((SST25VF080 == true) ||(SST25LF080 == true))
		#define BANCO_0 	0
		#define BANCO_1		1024 * 1024
		#define BANCO_2		2048 * 1024
		#define BANCO_3		3072 * 1024
	#else
		#define BANCO_0 	0
		#define BANCO_1		512 * 1024
		#define BANCO_2		1024 * 1024
		#define BANCO_3		1536 * 1024
	#endif

// sobre registros de chts
	#if (portatil == true)
		#define addr_inic_cht 	4096 + (limite_registros * TAM_REGS) + 4096 + (limite_ocorrencias * TAM_REGS) + 896	+4096		//2944
	#else
		#define addr_inic_cht 	(int32)(417792 + 4096) 
	#endif
	#define addr_inic_cht_modo3 	4096 + (limite_registros * TAM_REGS_MODO3) + 4096 + (limite_ocorrencias * TAM_REGS_MODO3) + 896 + 4096		//2944
	#if ((st94) || (st5x) || (st92))
		#define limite_chts		242
	#elif (controlador == true)
		#if (st8500c == true)
			#define limite_chts		0
		#else
			#define limite_chts		242
		#endif
	#else
		#define limite_chts		768
	#endif

	char dia_old;
	char mes_old;
	char ano_old;
	char hora_old;
	char minuto_old;
	char segundo_old;


// variaveis para definicao da autonomia de memoria.
	int16 nro_dias;
	char nro_horas;
	char nro_minutos;
	char nro_segundos;

	int32 prox_grava;
	char codigo_old;
	char codigo_old_regs;

#else	
	#define	nro_bancos  0
	#define	limite_registros 0
	#define limite_ocorrencias 0
	#define nro_registros_por_banco		0
	#define limite_chts 0
#endif


#define TENSAO_FALTA 50 * 64

/* TABELA DE PARAMETROS DEFAULT */

#define sazi_old  false
#if (portatil == 1)
	#if (se_com_flex == true)
		#define OFF_SET_FP_R	6
		#define OFF_SET_FP_S	6
		#define OFF_SET_FP_T	6

		#define OFF_SET_TEN_R1	-19
		#define OFF_SET_TEN_S1	-1
		#define OFF_SET_TEN_T1	20

		#define OFF_SET_TEN_R2	-19
		#define OFF_SET_TEN_S2	-1
		#define OFF_SET_TEN_T2	-20

		#define OFF_SET_COR_R	0
		#define OFF_SET_COR_S	0
		#define OFF_SET_COR_T	0
		
		#define OFF_SET_COR_R_9001G1	0
		#define OFF_SET_COR_S_9001G1	0
		#define OFF_SET_COR_T_9001G1	0
		#define OFF_SET_COR_R_9001G2	0
		#define OFF_SET_COR_S_9001G2	0
		#define OFF_SET_COR_T_9001G2	0
		#define OFF_SET_COR_R_9002G1	0
		#define OFF_SET_COR_S_9002G1	0
		#define OFF_SET_COR_T_9002G1	0
		#define OFF_SET_COR_R_9003G1	0
		#define OFF_SET_COR_S_9003G1	0
		#define OFF_SET_COR_T_9003G1	0
		#define OFF_SET_COR_R_9004G1	0
		#define OFF_SET_COR_S_9004G1	0
		#define OFF_SET_COR_T_9004G1	0
		#define OFF_SET_COR_R_9005G1	0
		#define OFF_SET_COR_S_9005G1	0
		#define OFF_SET_COR_T_9005G1	0
		#define OFF_SET_COR_R_9005G2	0
		#define OFF_SET_COR_S_9005G2	0
		#define OFF_SET_COR_T_9005G2	0
		#define OFF_SET_COR_R_9005G3	0
		#define OFF_SET_COR_S_9005G3	0
		#define OFF_SET_COR_T_9005G3	0
		#define OFF_SET_COR_R_9005G4	0
		#define OFF_SET_COR_S_9005G4	0
		#define OFF_SET_COR_T_9005G4	0
		#define OFF_SET_COR_R_9005G5	0
		#define OFF_SET_COR_S_9005G5	0
		#define OFF_SET_COR_T_9005G5	0
		#define OFF_SET_COR_R_9006G1	0
		#define OFF_SET_COR_S_9006G1	0
		#define OFF_SET_COR_T_9006G1	0
		#define OFF_SET_COR_R_9006G2	0
		#define OFF_SET_COR_S_9006G2	0
		#define OFF_SET_COR_T_9006G2	0
		#define OFF_SET_COR_R_9006G3	0
		#define OFF_SET_COR_S_9006G3	0
		#define OFF_SET_COR_T_9006G3	0
		#define OFF_SET_COR_R_9006G4	0
		#define OFF_SET_COR_S_9006G4	0
		#define OFF_SET_COR_T_9006G4	0
		#define OFF_SET_COR_R_9006G5	0
		#define OFF_SET_COR_S_9006G5	0
		#define OFF_SET_COR_T_9006G5	0
		#define OFF_SET_COR_R_9007G1	0
		#define OFF_SET_COR_S_9007G1	0
		#define OFF_SET_COR_T_9007G1	0
		#define OFF_SET_COR_R_9007G2	0
		#define OFF_SET_COR_S_9007G2	0
		#define OFF_SET_COR_T_9007G2	0
		#define OFF_SET_COR_R_9008G1	0
		#define OFF_SET_COR_S_9008G1	0
		#define OFF_SET_COR_T_9008G1	0
		#define OFF_SET_COR_R_9009G1	0
		#define OFF_SET_COR_S_9009G1	0
		#define OFF_SET_COR_T_9009G1	0
		#define OFF_SET_COR_R_9009G2	0
		#define OFF_SET_COR_S_9009G2	0
		#define OFF_SET_COR_T_9009G2	0

		#define LIMITE_TEN_INF	-100
		#define LIMITE_TEN_SUP	100
		#define LIMITE_COR_INF	-100
		#define LIMITE_COR_SUP	100
		#define LIMITE_POT_INF	-120
		#define LIMITE_POT_SUP  120
	#else
		#if (SAZI_old == true)
			#define OFF_SET_FP_R	6
			#define OFF_SET_FP_S	6
			#define OFF_SET_FP_T	6
		
			#define OFF_SET_COR_R_20	46
			#define OFF_SET_COR_S_20	0
			#define OFF_SET_COR_T_20	0
			#define OFF_SET_COR_R_200	93
			#define OFF_SET_COR_S_200	105
			#define OFF_SET_COR_T_200	77
			#define OFF_SET_COR_R_300	0
			#define OFF_SET_COR_S_300	0
			#define OFF_SET_COR_T_300	0
			#define OFF_SET_COR_R_600	0
			#define OFF_SET_COR_S_600	0
			#define OFF_SET_COR_T_600	0
			#define OFF_SET_COR_R_1000	100
			#define OFF_SET_COR_S_1000	122
			#define OFF_SET_COR_T_1000	128
			#define OFF_SET_COR_R_1500	0
			#define OFF_SET_COR_S_1500	0
			#define OFF_SET_COR_T_1500	0
			#define OFF_SET_COR_R_2000	0
			#define OFF_SET_COR_S_2000	0
			#define OFF_SET_COR_T_2000	0	
			#define OFF_SET_COR_R_3000	0
			#define OFF_SET_COR_S_3000	0
			#define OFF_SET_COR_T_3000	0
			#define OFF_SET_COR_R_6000	0
			#define OFF_SET_COR_S_6000	0
			#define OFF_SET_COR_T_6000	0
			
			#define OFF_SET_TEN_R1	-19
			#define OFF_SET_TEN_S1	-1
			#define OFF_SET_TEN_T1	20
			
			#define OFF_SET_TEN_R2	-19
			#define OFF_SET_TEN_S2	-1
			#define OFF_SET_TEN_T2	-20
			
			#define LIMITE_TEN_INF	-50
			#define LIMITE_TEN_SUP	50
			#define LIMITE_COR_INF	-100
			#define LIMITE_COR_SUP	100
			#define LIMITE_POT_INF	-102
			#define LIMITE_POT_SUP  102
		
		#else
	
			#define OFF_SET_FP_R	7
			#define OFF_SET_FP_S	7
			#define OFF_SET_FP_T	7
	
			#define OFF_SET_COR_R	0
			#define OFF_SET_COR_S	0
			#define OFF_SET_COR_T	0
		
			#define OFF_SET_COR_R_20	0
			#define OFF_SET_COR_S_20	0
			#define OFF_SET_COR_T_20	0
			#define OFF_SET_COR_R_200	0
			#define OFF_SET_COR_S_200	0
			#define OFF_SET_COR_T_200	0
			#define OFF_SET_COR_R_300	0
			#define OFF_SET_COR_S_300	0
			#define OFF_SET_COR_T_300	0
			#define OFF_SET_COR_R_600	0
			#define OFF_SET_COR_S_600	0
			#define OFF_SET_COR_T_600	0
			#define OFF_SET_COR_R_1000	0
			#define OFF_SET_COR_S_1000	0
			#define OFF_SET_COR_T_1000	0
			#define OFF_SET_COR_R_1500	0
			#define OFF_SET_COR_S_1500	0
			#define OFF_SET_COR_T_1500	0
			#define OFF_SET_COR_R_2000	0
			#define OFF_SET_COR_S_2000	0
			#define OFF_SET_COR_T_2000	0	
			#define OFF_SET_COR_R_3000	0
			#define OFF_SET_COR_S_3000	0
			#define OFF_SET_COR_T_3000	0
			#define OFF_SET_COR_R_6000	0
			#define OFF_SET_COR_S_6000	0
			#define OFF_SET_COR_T_6000	0
	
			#define OFF_SET_POT_R_20	0
			#define OFF_SET_POT_S_20	0
			#define OFF_SET_POT_T_20	0
			#define OFF_SET_POT_R_200	0
			#define OFF_SET_POT_S_200	0
			#define OFF_SET_POT_T_200	0
			#define OFF_SET_POT_R_300	0
			#define OFF_SET_POT_S_300	0
			#define OFF_SET_POT_T_300	0
			#define OFF_SET_POT_R_600	0
			#define OFF_SET_POT_S_600	0
			#define OFF_SET_POT_T_600	0
			#define OFF_SET_POT_R_1000	0
			#define OFF_SET_POT_S_1000	0
			#define OFF_SET_POT_T_1000	0
			#define OFF_SET_POT_R_1500	0
			#define OFF_SET_POT_S_1500	0
			#define OFF_SET_POT_T_1500	0
			#define OFF_SET_POT_R_2000	0
			#define OFF_SET_POT_S_2000	0
			#define OFF_SET_POT_T_2000	0	
			#define OFF_SET_POT_R_3000	0
			#define OFF_SET_POT_S_3000	0
			#define OFF_SET_POT_T_3000	0
			#define OFF_SET_POT_R_6000	0
			#define OFF_SET_POT_S_6000	0
			#define OFF_SET_POT_T_6000	0
	
			#define OFF_SET_TEN_R1	66
			#define OFF_SET_TEN_S1	59
			#define OFF_SET_TEN_T1	77
		
			#define OFF_SET_TEN_R2	66
			#define OFF_SET_TEN_S2	59
			#define OFF_SET_TEN_T2	77
		
			#define LIMITE_TEN_INF	-100	//-60
			#define LIMITE_TEN_SUP	100		//60
			#define LIMITE_COR_INF	-100	//-150
			#define LIMITE_COR_SUP	100	//150
			#define LIMITE_POT_INF	-100
			#define LIMITE_POT_SUP  100
		#endif
	#endif

	#define OFF_SET_POT_R   0
	#define OFF_SET_POT_S   0
	#define OFF_SET_POT_T   0

#else
	#if (chip_cs5460a == true)
		#define OFF_SET_FP_R	0
		#define OFF_SET_FP_S	0
		#define OFF_SET_FP_T	0
	
		#define OFF_SET_COR_R	0
		#define OFF_SET_COR_S	0
		#define OFF_SET_COR_T	0
		
		#define OFF_SET_TEN_R1	0
		#define OFF_SET_TEN_S1	0
		#define OFF_SET_TEN_T1	0
		
		#define OFF_SET_TEN_R2	0
		#define OFF_SET_TEN_S2	0
		#define OFF_SET_TEN_T2	0
	
		#define LIMITE_TEN_INF	-100
		#define LIMITE_TEN_SUP	100
		#define LIMITE_COR_INF	-100
		#define LIMITE_COR_SUP	100
		#define LIMITE_POT_INF	-100
		#define LIMITE_POT_SUP  100
	
		#define OFF_SET_POT_R   (OFF_SET_COR_R + OFF_SET_TEN_R1)
		#define OFF_SET_POT_S   (OFF_SET_COR_S + OFF_SET_TEN_S1)
		#define OFF_SET_POT_T   (OFF_SET_COR_T + OFF_SET_TEN_T1)

	#elif (ade7754 == true)
		#define OFF_SET_FP_R	2
		#define OFF_SET_FP_S	2
		#define OFF_SET_FP_T	2
	
		#define OFF_SET_COR_R	6
		#define OFF_SET_COR_S	8
		#define OFF_SET_COR_T	7
		
		#define OFF_SET_TEN_R1	-86
		#define OFF_SET_TEN_S1	-96
		#define OFF_SET_TEN_T1	-86
		
		#define OFF_SET_TEN_R2	-86
		#define OFF_SET_TEN_S2	-96
		#define OFF_SET_TEN_T2	-86
	
		#define LIMITE_TEN_INF	-100
		#define LIMITE_TEN_SUP	100
		#define LIMITE_COR_INF	-100
		#define LIMITE_COR_SUP	100
		#define LIMITE_POT_INF	-100
		#define LIMITE_POT_SUP  100
	
		#define OFF_SET_POT_R   (OFF_SET_COR_R + OFF_SET_TEN_R1)
		#define OFF_SET_POT_S   (OFF_SET_COR_S + OFF_SET_TEN_S1)
		#define OFF_SET_POT_T   (OFF_SET_COR_T + OFF_SET_TEN_T1)

	#elif (controlador == true)
		#define NRO_MODOS_TRAFO_ALTA	1
		#if (monofasico == true)
			#define OFF_SET_FP_R	0
			#define OFF_SET_FP_S	16
			#define OFF_SET_FP_T	0
		
			#define OFF_SET_COR_R	0
			#define OFF_SET_COR_S	0
			#define OFF_SET_COR_T	0
			
			#define OFF_SET_TEN_R1	0
			#define OFF_SET_TEN_S1	0
			#define OFF_SET_TEN_T1	0
			
			#define OFF_SET_TEN_R2	0
			#define OFF_SET_TEN_S2	0
			#define OFF_SET_TEN_T2	0
		
			#define LIMITE_TEN_INF	-80
			#define LIMITE_TEN_SUP	80
			#define LIMITE_COR_INF	-80
			#define LIMITE_COR_SUP	80
			#define LIMITE_POT_INF	-80
			#define LIMITE_POT_SUP  80
		
			#define OFF_SET_POT_R   0
			#define OFF_SET_POT_S   0
			#define OFF_SET_POT_T   0
		#else
			#define OFF_SET_FP_R	0
			#define OFF_SET_FP_S	16
			#define OFF_SET_FP_T	0
		
			#define OFF_SET_COR_R	10
			#define OFF_SET_COR_S	10
			#define OFF_SET_COR_T	10
			
			#define OFF_SET_TEN_R1	10
			#define OFF_SET_TEN_S1	10
			#define OFF_SET_TEN_T1	10
			
			#define OFF_SET_TEN_R2	10
			#define OFF_SET_TEN_S2	10
			#define OFF_SET_TEN_T2	10
		
			#define LIMITE_TEN_INF	-120
			#define LIMITE_TEN_SUP	120
			#define LIMITE_COR_INF	-120
			#define LIMITE_COR_SUP	120
			#define LIMITE_POT_INF	-120
			#define LIMITE_POT_SUP  120
		
			#define OFF_SET_POT_R   0
			#define OFF_SET_POT_S   0
			#define OFF_SET_POT_T   0
		#endif

	#elif (st5x == true)
		#define OFF_SET_FP_R	0
		#define OFF_SET_FP_S	0
		#define OFF_SET_FP_T	0
		
		#if (padrao_referencia == true)
			#define OFF_SET_COR_R	-32
			#define OFF_SET_COR_S	-29
			#define OFF_SET_COR_T	-31
						
			#define OFF_SET_TEN_R1	40
			#define OFF_SET_TEN_S1	30
			#define OFF_SET_TEN_T1	40
			
			#define OFF_SET_TEN_R2	40
			#define OFF_SET_TEN_S2	30
			#define OFF_SET_TEN_T2	40

			#define OFF_SET_POT_R   4
			#define OFF_SET_POT_S   0
			#define OFF_SET_POT_T   0
		
			#define LIMITE_COR_INF	-33
			#define LIMITE_COR_SUP	-28

			#define LIMITE_TEN_INF	29
			#define LIMITE_TEN_SUP	41

			#define LIMITE_POT_INF	-1
			#define LIMITE_POT_SUP  5
		#else
			#define OFF_SET_COR_R	0
			#define OFF_SET_COR_S	0
			#define OFF_SET_COR_T	0
			
			#define OFF_SET_TEN_R1	0
			#define OFF_SET_TEN_S1	0
			#define OFF_SET_TEN_T1	0
			
			#define OFF_SET_TEN_R2	0
			#define OFF_SET_TEN_S2	0
			#define OFF_SET_TEN_T2	0

			#define OFF_SET_POT_R   0
			#define OFF_SET_POT_S   0
			#define OFF_SET_POT_T   0
		
			#define LIMITE_TEN_INF	-100
			#define LIMITE_TEN_SUP	100
			#define LIMITE_COR_INF	-100
			#define LIMITE_COR_SUP	100
			#define LIMITE_POT_INF	-100
			#define LIMITE_POT_SUP  100
		#endif
	

	#elif (st94 == true)
		#define OFF_SET_FP_R	0
		#define OFF_SET_FP_S	0
		#define OFF_SET_FP_T	0
	
		#define OFF_SET_COR_R	76
		#define OFF_SET_COR_S	75
		#define OFF_SET_COR_T	75
		
		#define OFF_SET_TEN_R1	29
		#define OFF_SET_TEN_S1	27
		#define OFF_SET_TEN_T1	28
		
		#define OFF_SET_TEN_R2	29
		#define OFF_SET_TEN_S2	27
		#define OFF_SET_TEN_T2	28
	
		#define LIMITE_TEN_INF	-125
		#define LIMITE_TEN_SUP	125
		#define LIMITE_COR_INF	-125
		#define LIMITE_COR_SUP	125
		#define LIMITE_POT_INF	-125
		#define LIMITE_POT_SUP  125
	
		#define OFF_SET_POT_R   0
		#define OFF_SET_POT_S   0
		#define OFF_SET_POT_T   0

	#elif (st92 == true)
		#define OFF_SET_FP_R	0
		#define OFF_SET_FP_S	0
		#define OFF_SET_FP_T	0
	
		#define OFF_SET_COR_R	76
		#define OFF_SET_COR_S	75
		#define OFF_SET_COR_T	75
		
		#define OFF_SET_TEN_R1	29
		#define OFF_SET_TEN_S1	27
		#define OFF_SET_TEN_T1	28
		
		#define OFF_SET_TEN_R2	29
		#define OFF_SET_TEN_S2	27
		#define OFF_SET_TEN_T2	28
	
		#define LIMITE_TEN_INF	-125
		#define LIMITE_TEN_SUP	125
		#define LIMITE_COR_INF	-125
		#define LIMITE_COR_SUP	125
		#define LIMITE_POT_INF	-125
		#define LIMITE_POT_SUP  125
	
		#define OFF_SET_POT_R   0
		#define OFF_SET_POT_S   0
		#define OFF_SET_POT_T   0

	#else
		#define OFF_SET_FP_R	0
		#define OFF_SET_FP_S	0
		#define OFF_SET_FP_T	0
	
		#define OFF_SET_COR_R	76
		#define OFF_SET_COR_S	75
		#define OFF_SET_COR_T	75
		
		#define OFF_SET_TEN_R1	29
		#define OFF_SET_TEN_S1	27
		#define OFF_SET_TEN_T1	28
		
		#define OFF_SET_TEN_R2	29
		#define OFF_SET_TEN_S2	27
		#define OFF_SET_TEN_T2	28
	
		#define LIMITE_TEN_INF	-100
		#define LIMITE_TEN_SUP	100
		#define LIMITE_COR_INF	-100
		#define LIMITE_COR_SUP	100
		#define LIMITE_POT_INF	-100
		#define LIMITE_POT_SUP  100
	
		#define OFF_SET_POT_R   0
		#define OFF_SET_POT_S   0
		#define OFF_SET_POT_T   0
	#endif
	
#endif


#if (disp_7seg == true)
	char ptr_disp;
	char disp_timer;
#endif

char bloqueio_gravacao;
// definicao de variaveis com endereÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿços fixos
char PRODH;
char PRODL;
char RES0;
char RES1;
char RES2;
char RES3;
char WREG;
int32 res_32b;

#LOCATE PRODH = 0XFF4
#LOCATE PRODL = 0XFF3

#LOCATE WREG = 0XFE8

#locate RES3 = 0X940
#locate RES2 = 0X941
#locate RES1 = 0X942
#locate RES0 = 0X943

#locate res_32b = 0x944



#if (com_cht== true)
	// definicao de variaveis de controle do calculo de cht
	float AP;
	float AP1;
	float zx;		// float
	float AN1;		// float
	float AN2;		// float
	float BN1;		// float
	float BN2;		// float
	float A1;		// float
	float A2;		// float
	float S_AN2;		// float
	float S_BN2;		// float
	float SAP;		// float
	int16 CHT;
	char qcht;
	char passo_cht;
	char passo_qcht;
	char passo_rd_cht;
	char passo_fase_cht;
	float  AMPLITUDE[NRO_AMOSTRAS_CHT+2];
	#if (chip_cs5460a == true)
		unsigned word buffer_t[NRO_AMOSTRAS_CHT+2];
		unsigned word buffer_c[NRO_AMOSTRAS_CHT+2];
//	unsigned word buffer_p[NRO_AMOSTRAS_CHT+2];
		word buffer_cht_t[NRO_AMOSTRAS_CHT+2];
		word buffer_cht_c[NRO_AMOSTRAS_CHT+2];
	#else
		word buffer_cht[NRO_AMOSTRAS_CHT+1];
	#endif
	word CHT_tr[NRO_CHT+2];
	word CHT_cr[NRO_CHT+2];
	#if (monofasico == false)
		word CHT_ts[NRO_CHT+2];
		word CHT_cs[NRO_CHT+2];
		word CHT_tt[NRO_CHT+2];
		word CHT_ct[NRO_CHT+2];
	#endif
	#if (debug_cht == true)
		float AN11;
		float BN11;
		float AN22;
		float BN22;
		float APP;
	#endif
#endif


char buf_nro[4];

#if (CONTROLADOR == true) || (st_prog == true)
	char que_banco_repouso;
	char banco_inicial;
	char banco_final;
	char tempo_falta_energia;
	char status_banco_minimo;
	char comuni_busy;

	char com_des_ten_a;
	char com_des_ten_b;
	char com_des_chtt;
	char com_des_chtc;
	char com_des_fp_ind_cap;

	#if (controle_por_fase == true)
		char ifase;
		word total_acionado[3];
		float kvar_disponivel[3];
	#else
		word total_acionado;
		float kvar_disponivel;
	#endif
	#if (st8500c == true)
		char min_kw;
		word max_kw;
	#else
		char min_kvar;
		char max_kvar;
	#endif
	char sequencia;

	char aux_tempo_aciona;
	char ultimo_tempo_aciona;

	char tempo_aciona;
	char tempo_desaciona;
	#if (st8500c == true)
		char modo_saidas;
			#define MODO_INVERTIDO	false
			#define MODO_NORMAL		true
		char nro_cargas;
		word carga_instalada;
		word menor_carga;
	#else
		char nro_bancos_capacitor;
		char aux_nro_bancos_capacitor;
	#endif
	char output_01;

	float kvar_req;
	float kvar_req_anterior;
	float kvar_exec;

	char fase_cht;
	char aux_tab;
	char aux_tab2;
	char tab_manut;
	char ultima_tecla;
	#if (st8500c == true)
//		char maior_carga;
//		char menor_carga;
//		char proximo_carga;
	#else
		char maior_banco;
		char menor_banco;
		char proximo_banco;
	#endif

	
	#if (st8500C == true)
		#define CONTROLE_FILO			0
		#define CONTROLE_FILA_CIRCULAR	1
		
		char tipo_controle_demanda;
		char ptr_aciona;
		char ptr_desaciona;
		word horimetro[NRO_MAXIMO_CARGAS];
		char minuteiro[NRO_MAXIMO_CARGAS];
		char segundeiro[NRO_MAXIMO_CARGAS];
		word acionamentos[NRO_MAXIMO_CARGAS];
		char tempo_repouso[NRO_MAXIMO_CARGAS];
		char aux_tempo_repouso[NRO_MAXIMO_CARGAS];
		char carga[NRO_MAXIMO_CARGAS];
		char carga_acionada[NRO_MAXIMO_CARGAS];
		char carga_disponivel[NRO_MAXIMO_CARGAS];
		char tabela_valor_cargas[NRO_MAXIMO_CARGAS+1];
		char tabela_tempo_repouso[NRO_MAXIMO_CARGAS+1];
		char forma_controle[NRO_MAXIMO_CARGAS+1];				// tabela definição se carga controlável ou por horário
		char hora_liga_controle[NRO_MAXIMO_CARGAS+1];			// tabela de horarios de funcionamento
		char minuto_liga_controle[NRO_MAXIMO_CARGAS+1];			// tabela de horarios de funcionamento
		char hora_desliga_controle[NRO_MAXIMO_CARGAS+1];			// tabela de horarios de funcionamento
		char minuto_desliga_controle[NRO_MAXIMO_CARGAS+1];			// tabela de horarios de funcionamento
		int cont_tempo_rep_15;
		int cont_tempo_rep_30;
	#else
		word horimetro[NRO_MAXIMO_BANCOS_CAPACITOR];
		char minuteiro[NRO_MAXIMO_BANCOS_CAPACITOR];
		char segundeiro[NRO_MAXIMO_BANCOS_CAPACITOR];
		word acionamentos[NRO_MAXIMO_BANCOS_CAPACITOR];
		char tempo_repouso[NRO_MAXIMO_BANCOS_CAPACITOR];
		char aux_tempo_repouso[NRO_MAXIMO_BANCOS_CAPACITOR];
		char banco_capacitor[NRO_MAXIMO_BANCOS_CAPACITOR];
		char banco_acionado[NRO_MAXIMO_BANCOS_CAPACITOR];
		char banco_disponivel[NRO_MAXIMO_BANCOS_CAPACITOR];
		char tabela_valor_bancos[NRO_MAXIMO_BANCOS_CAPACITOR+1];
		char tabela_tempo_repouso[NRO_MAXIMO_BANCOS_CAPACITOR+1];
	#endif

	char buf_display[13];
	char que_ocor[nro_ocorrencia];
	char tabela_pisca[6];

	word tabela_programa[18];


	#define TUDO_IGUAL			0
	#define NRO_ACIONA_DIF		1
	#define NRO_HORAS_DIF		2
	#define NRO_MIN_DIF			3
	

#endif



#if (st_prog == true)
	#define TAM_RX2	16
	#define TAM_TX2	250

	float carga_at[16];
	float carga_reat[16];
	float var_fp[16];
	
	char tarifa[3];     
	word carga_total_at;
	word carga_total_reat;
	float somaf_at, somaf_reat;
	char low_nro_segundos;
	char high_nro_segundos;
	float degrau1;
	signed word fator_pot_rep;
	
	short indicador_fatura;			//Indicador de fatura. Complementado a cada reposição de demanda.
	short indicador_reativo;		//Indicador de Intervalo Reativo - Complementado a cada final de intervalo reativo
	short pulsos_cap_considerado;	//Se = 1, indica pulsos capacitivos computados para UFER e DMCR.
	short pulsos_ind_considerado;	//Se = 1, indica pulsos indutivos computados para UFER e DMCR.
	short tipo_REP;					//0 = Padrão; 1 = Estendido
	char segmento_horo_sazonal;		//0001 = Ponta; 0010 = Fora da Ponta; 1000 = Reservado
	char tipo_de_tarifa;			//00 = Azul; 01 = Verde; 10 = Irrigantes; 11 = Outras
	short tarifar_reativos;			//Se = 1, tarifa de reativos ativada.
	char reposicao_de_demanda;
	word quantidade_kW;				//Valor a ser transmitido de Potência Ativa
	word quantidade_kVAr;			//Valor a ser transmitido de Potência Reativa
	word pulso_ati;					//Quantidade de pulsos de energia ativa (kW).
	word pulso_reat;				//Quantidade de pulsos de energia reativa (kVAr).
	word time_integra;				//Intervalo de Integração. Contador regressivo de 899 a 0 (15 minutos).
	word intervalo;					//Período pré-definido: 300; 600; 900;
	
		
//	char banco_acionado[NRO_MAXIMO_BANCOS_CAPACITOR];
	
	char ptrtx2;
	char ptrrx2;
	char retrx2;
	char numbrx2;
	char numbtx2;
	char time_out_modbus2;
	char time_out_sultech;


	word equipamento;
	char serie;
	char passo_comuni_sultech;
	
	word programas[64];
	word medicoes[20];
	word forma_onda_tensao[169];
	word forma_onda_corrente[169];
	char buf_rx2[TAM_RX2];
	char buf_tx2[TAM_TX2];
	char nro_serie[6];

#endif


//word conta_kw_r;
//word nro_kw_r;

#if (st5x == true)
	char status_led;
	char nro_pisca_led;
	char status_flags;
	char time_led;
	#if (st5000c_rev12 == true)
		char dip_addr;
	#else
		#if (painel_12 == true)
			char dip_addr;
		#else
			int16 dip_addr;
		#endif
	#endif
	int16 dip_vel;
//	int16 val_addr;
//	char media_addr;
	int16 soma_addr;
#endif

#if (com_relogio == true)
//	char tempo_ajuste_relogio;
//	int32 conta_seg;
//	char ajuste_relogio;
#endif

char conta_sinal_r;
signed int16 fase_tmp;
int16 fase_tmp1;


// VARIAVEIS DA FASE R
#if (sames_9904 == true)
	int32 KW_R_SAMES;
	int32 KW_S_SAMES;
	int32 KW_T_SAMES;
	int32 KVAR_R_SAMES;
	int32 KVAR_S_SAMES;
	int32 KVAR_T_SAMES;
	int32 VR_SAMES;
	int32 VS_SAMES;
	int32 VT_SAMES;
	int32 HZ_SAMES;
	int32 KW_R_SAMES_OLD;
	int32 KW_S_SAMES_OLD;
	int32 KW_T_SAMES_OLD;
	int32 KVAR_R_SAMES_OLD;
	int32 KVAR_S_SAMES_OLD;
	int32 KVAR_T_SAMES_OLD;
	int32 KVA_R_SAMES;
	int32 KVA_S_SAMES;
	int32 KVA_T_SAMES;
	int32 KW_R;
	int32 KW_S;
	int32 KW_T;
	int32 KVAR_R;
	int32 KVAR_S;
	int32 KVAR_T;

	int32 soma_kw_r;
	int32 soma_kw_s;
	int32 soma_kw_t;
	int32 soma_kvar_r;
	int32 soma_kvar_s;
	int32 soma_kvar_t;
	signed long int sinal_r;
	int32 soma_reg_tr;
	int32 soma_reg_cr;
	int32 soma_efi_tr;
	int32 soma_efi_cr;
	int32 soma_ten_r;
	int32 soma_cor_r;
	int32 soma_cr;
	int32 soma_tr;
	signed int32 soma_pr;
	signed int32 soma_efi_p_tmp;
	signed int32 soma_efi_pr;
	signed int32 soma_pot_efi_r;
	
#else
	int32 soma_pot_r;
	signed long int sinal_r;
	int32 soma_reg_tr;
	int32 soma_reg_cr;
	int32 soma_efi_tr;
	int32 soma_efi_cr;
	int32 soma_ten_r;
	int32 soma_cor_r;
	#if (chip_cs5460a == true)
		int32 soma_efi_pr;
	#else
		int32 soma_cr;
		int32 soma_tr;
		signed int32 soma_pr;
		signed int32 soma_efi_pr;
		signed int32 soma_pot_efi_r;
		signed int32 soma_kvar_r;
		signed int32 soma_efi_kvar_r;
		signed int32 soma_pot_kvar_r;
	#endif
	signed int32 soma_efi_p_tmp;
#endif
// variaveis eletricas 

int32 pot_ativa_tot;
int32 pot_reativa_tot;
int32 pot_aparente_tot;


char frequencia;
int nro_media_freq;
word tensao_r;
word corrente_r;
word cor_maxima_r;
word pot_ativa_max_r;
word pot_ativa_r;
word pot_aparente_r;
word pot_reativa_r;
word pot_reativa_r_ant;
int cont_decide_rep;
int cont_falta_cap;
signed word fator_pot_r;
word dem_media_ativa;
word dem_media_aparente;
word dem_media_reativa;
word dem_maxima_ativa;
word dem_maxima_aparente;
word dem_maxima_ativa_ant;
word dem_maxima_aparente_ant;
word tensao_rs;
word tensao_rs_na_alta;
word dem_ativa;
word dem_reativa;
word dem_contratada;
word dem_acionada;
word dem_ativa_proj;
word dem_reativa_proj;
word fator_carga;
word fator_demanda;
word pot_exec_r;
word pot_req_r;
char sinal_fp[4];

word tensao_tri;
word corrente_tri;
signed word fator_pot;
char time_out_tc_r;

#if (ST8100C == true)
	char 	digito;
#endif
#if ((ST8300C == true) || (ST8500C == true))
	char passo_ad_8300;
#endif	


#if (monofasico == false)

// VARIAVEIS DA FASE S
	int32 soma_pot_s;
	signed long int sinal_s;
	int32 soma_reg_ts;
	int32 soma_reg_cs;
	int32 soma_efi_ts;
	int32 soma_efi_cs;
	int32 soma_ten_s;
	int32 soma_cor_s;

	#if (chip_cs5460a == true)
		int32 soma_efi_ps;
	#else
		int32 soma_ts;
		int32 soma_cs;
		signed int32 soma_ps;
		signed int32 soma_efi_ps;
		signed int32 soma_pot_efi_s;
		signed int32 soma_kvar_s;
		signed int32 soma_efi_kvar_s;
		signed int32 soma_pot_kvar_s;
	#endif

	word tensao_s;
	word corrente_s;
	word cor_maxima_s;
	word pot_ativa_max_s;
	word pot_ativa_s;
	word pot_aparente_s;
	word pot_reativa_s;
	signed word fator_pot_s;
	word tensao_st;
	word tensao_st_na_alta;
	word pot_exec_s;
	word pot_req_s;
	char time_out_tc_s;

// VARIAVEIS DA FASE T
	int32 soma_pot_t;
	signed long int sinal_t;
	int32 soma_reg_tt;
	int32 soma_reg_ct;
	int32 soma_efi_tt;
	int32 soma_efi_ct;
	int32 soma_cor_t;
	int32 soma_ten_t;

	#if (chip_cs5460a == true)
		int32 soma_efi_pt;
		signed int32 soma_pt;
	#else
		int32 soma_tt;
		int32 soma_ct;
		signed int32 soma_pt;
		signed int32 soma_efi_pt;
		signed int32 soma_pot_efi_t;

		signed int32 soma_kvar_t;
		signed int32 soma_efi_kvar_t;
		signed int32 soma_pot_kvar_t;
	#endif

	word tensao_t;
	word corrente_t;
	word cor_maxima_t;
	word pot_ativa_max_t;
	word pot_ativa_t;
	word pot_aparente_t;
	word pot_reativa_t;
	signed word fator_pot_t;
	word tensao_rt;
	word tensao_rt_na_alta;
	word pot_exec_t;
	word pot_req_t;
	char time_out_tc_t;
	
	int32 soma_cn;
	int32 soma_efi_cn;
	word corrente_n;
	
	//word temperatura;

#endif


float mul_tc;

int32 fundo_escala_corrente;

// variaveis somente para testes, devem ser apagadas
char nro_conta_media;
char conta_media;

char rotina;

word status;
word status_equipamento_H;
word status_equipamento_L;

char periodo_fatura;
// definicao de variavesi de uso geral 
#if (ade7754 == true)
	char conta_media_ten_r;
	char conta_media_ten_s;
	char conta_media_ten_t;
#else
	char conta_media_ten;
#endif
//char conta_media_cor;
char passo_main;
word aux_w1;
word aux_w2;
word aux_w3;
word aux_wexibe1;
word aux_wexibe2;
//word aux_w4;
signed word aux_sw1;
signed word aux_sw2;
int32 aux_l1;
int32 aux_l2;
int32 aux_l3;
int32 aux_l4;
int32 aux_l5;
int32 aux_l6;
signed int32 aux_l7;
signed int32 aux_l8;
signed int32 aux_l9;
float aux_f1;
float aux_f2;
float aux_f3;
float aux_f4;
float aux_f5;
float aux_f6;
float valorf;

char aux_disp;	

char aux_b1;
char aux_b2;
char aux_b3;
char aux_b4;
char aux_calc;

/* Definicao das variaveis	em ram */
char var_mem;
char time_out;	
char time_out2;
#define DEF_TIME_OUT2	40
char time_out_exibe_erro;	
char time_out_back;
char time_out_t3;
char time_out_aciona_alarme;


char caracter;
char data1;
char dia;
char mes;
char ano;
char hora;
char minuto;
char segundo;
char distancia_fase;
char cont_fase;

#if (com_time_funciona == true)
	char min_funciona;
#endif	


word val_pwm;

signed int32 aux_sl1;
signed int32 aux_sl2;
signed int32 aux_sl3;
signed int32 aux_sl4;
signed int32 aux_sl5;
signed int32 aux_sl6;
//word vref;
//word vref_cr;
//word vref_cs;
//word vref_ct;
word vrefcr;
word vrefcs;
word vrefct;
word vreftr;
word vrefts;
word vreftt;
word addr;
word data1_int;
char cont0;
char cont1;
//word aux_int;
word aux_intervalo_integra;
char retardo_alarmes;


int32 soma_pot_ati;
int32 soma_pot_reat;
int32 pot_apa_tri;
int32 soma_pot_apa;
signed char sinal;
char cruza_cor;
char cruza_ten;

int16 nro_soma_reg;

char passo_tensao;
char passo_corrente;
char passo_corrente_r;
char passo_corrente_t;

int32 soma_vref;
int32 soma_vreft;
int32 soma_vrefc;
char nro_soma_vref;
#define NRO_MEDIAS_VREF	32



// variaveis para o calculo de frequencia
word freq_tmp;
word freq_tmp1;
char nro_ints;
char nro_ints_old;
char time_out_int0;
word soma_freq;
short fechar_frequencia;
char conta_soma_freq;
int conta_freq;
int conta_ints;




// variaveis do controle de consumo
#if (com_consumo == true)
	int32 consumo_reati;
	int32 consumo_ati;
	int32 consumo_rea_p;
	int32 consumo_ati_p;
	word nro_soma_consumo;
	int32 soma_consumo_r;
	int32 soma_consumo_s;
	int32 soma_consumo_t;
	int32 soma_consumo_rea_r;
	int32 soma_consumo_rea_s;
	int32 soma_consumo_rea_t;
	int32 soma_dem_apa_r;
	int32 soma_dem_apa_s;
	int32 soma_dem_apa_t;
	float consumo_r_tmp;
	float consumo_reati_r_tmp; 

	//int32 consumo_rea_r;
	
	word consumo_l;
	word consumo_h;
	int32 consumo;
	
	word dem_reat_r; 
	word dem_reat_s; 
	word dem_reat_t; 
	
	word dem_apa_r;
	word dem_apa_s;
	word dem_apa_t;
	word dem_aparente;
	
	word demanda_r;	
	word demanda_s;
	word demanda_t;	
	
	word consumo_tmp;
	word periodo_soma;
	
	word tendencia_demanda_ativa;

	#if (com_consumo_aparente == true)	//Atendendo solicitação da Maxi Eletro
		word consumo_apa_l;
		word consumo_apa_h;
		word consumo_apa_tmp;
		int32 consumo_apa;
		int32 consumo_apa_p;
		int32 soma_consumo_apa;
		int32 soma_consumo_apa_r;
		int32 soma_consumo_apa_s;
		int32 soma_consumo_apa_t;
		float consumo_apa_r_tmp;
	#endif
	
#endif

#if (ST8500c == true)
	#if (com_tc == false)
//		int32 consumo_reati;
//		int32 consumo_ati;
		int32 consumo_reati_ant;
		int32 consumo_ati_ant;
	#endif
#endif

int32 nro_erro_mem = 0;
word nro_erro_mem2 = 0;

#if (funcao_505 == true)
	char segundo_old_505;	
#endif

word tensao_media_r;
int32 soma_media_tensao_r;
word conta_media_tensao_r;
#if (monofasico == false)
	word tensao_media_s;
	word tensao_media_t;
	int32 soma_media_tensao_s;
	int32 soma_media_tensao_t;
	word conta_media_tensao_s;
	word conta_media_tensao_t;
#endif




// variaveis de programacao
#if (st5x == true)
	#if (com_saida_pulsos == true)
		word const_saida_kw;
		word const_saida_kvar ;
		byte qual_variavel_pulsa;
	#endif
#endif

char tempo_senha;
char modo_funca;
signed byte os_ten_r;
signed byte os_ten_s;
signed byte os_ten_t;
signed byte os_ten_r1;
signed byte os_ten_s1;
signed byte os_ten_t1;
char os_ten_r2;
char os_ten_s2;
char os_ten_t2;
signed byte os_cor_r;
signed byte os_cor_s;
signed byte os_cor_t;
signed byte os_pot_r;
signed byte os_pot_s;
signed byte os_pot_t;

#if (ade7754 == true)
	char fase_r;
	char fase_s;
	char fase_t;
	char fase_delta;
	word CFNUM_R;
	word CFNUM_S;
	word CFNUM_T;
#else
	char off_cor_r;
	char off_cor_s;
	char off_cor_t;
	char off_set_kvar;
	char defasagem;
#endif


/* definicoes de variaveis padroes para qualquer equipamento */
char ultimo_tc;
word ten_nomi;
word valor_tc;
word valor_tp;
word baud_rate;
#if (controlador == true)
	#if (st8500c == true)
		#define	INTERVALO_REG_DEFAULT 300		//60
	#else
		#define	INTERVALO_REG_DEFAULT 120		//300 - Passamos para 120 em 29/11/12. Autonomia de aproximadamente 34 dias.
	#endif
#else
	#define	INTERVALO_REG_DEFAULT 600
#endif
word intervalo_reg;

char tipo_ligacao;
char modo_rep;

char registro_old;
char aux_set_point;
char set_point;
char registro;
char forma_reg_cht;
#if (st5x == true)
	#if (TECNOFLUX == TRUE)
		char endereco_nro_serie;
	#endif
#endif	
char endereco;
char intervalo_integra;
char ala_fp_ind;
char ala_fp_cap;
char ala_ten_a;
char ala_ten_b;
char ala_sc;
char ala_chtt;
char ala_chtc;
char ala_subc;
char ala_skw;

#if (controlador == true) || (st_prog == true)
	char cor_minima;
#endif	
#if (com_rep == true)
	word cor_minima_rep;
#endif
#if (st8500c == true)
	char ala_demanda_ativa;
#else
	word ala_demanda_ativa;
	word ala_demanda_ativa_aux;
#endif

#if (st8500c == true)
	word dem_cont_ponta[13];
	word dem_cont_fora_ponta[13];
	word carga_programada;
		
	char dia_inicio_pc;
	char mes_inicio_pc;
	char dia_final_pc;
	char mes_final_pc;

#else
#endif

	char hora_ponta;
	char minuto_ponta;
	char hora_final_ponta;
	char minuto_final_ponta;

#if (portatil == true)
	#if (versao_pci_st96 >= 6)
		char time_out_troca_ponteira;
	#endif
	char ultimo_tempo;
	char prog_time;
	char fila_circular;
	char dia_liga;
	char dia_desliga;
	char hora_liga;
	char minuto_liga;
	char hora_desliga;
	char minuto_desliga;
#endif	


#if (portatil == TRUE)
	#if (versao_pci_st96 > 3)		//Para versões 4, 5 e 6.
		word ganho_ponteira;
	#endif
	#if (se_com_flex ==	true)
		char tipo_ponteira;
		signed char os_cor_pt_r[NRO_POSI_TABELA_TIPO_PT+1];
		signed char os_cor_pt_s[NRO_POSI_TABELA_TIPO_PT+1];
		signed char os_cor_pt_t[NRO_POSI_TABELA_TIPO_PT+1];
		signed char os_pot_pt_r[NRO_POSI_TABELA_TIPO_PT+1];
		signed char os_pot_pt_s[NRO_POSI_TABELA_TIPO_PT+1];
		signed char os_pot_pt_t[NRO_POSI_TABELA_TIPO_PT+1];
		char off_set_fp[NRO_POSI_TABELA_TIPO_PT+1];
	#else
		signed char os_cor_pt_r[NRO_POSI_TC];
		signed char os_cor_pt_s[NRO_POSI_TC];
		signed char os_cor_pt_t[NRO_POSI_TC];
		signed char os_pot_pt_r[NRO_POSI_TC];
		signed char os_pot_pt_s[NRO_POSI_TC];
		signed char os_pot_pt_t[NRO_POSI_TC];
		char off_set_fp[NRO_POSI_TC];
	#endif
	char localizacao[17];
#endif	
char posi_tc;
	

/* variaveis do protocolo mod bus*/
char addr_modbus;
char funcao_modbus;
char data_count_modbus;
char time_out_modbus;
char qerro_mod;
word data_modbus;
word nro_regs_modbus;
word force_data_modbus;
word crc_modbus;
word nro_pontos_modbus;
word addr_regs_modbus;
//word nro_bits_modbus;

#if (chip_cs5460a == true)
	short int_cs5460_r;
	short int_cs5460_s;
	short int_cs5460_t;
	short lendo_cht_cs5460;
	char datah;
	char datam;
	char datal;
	char status_cs5460h;
	char status_cs5460m;
	char status_cs5460l;
	int32 aux_ten_l;
	int32 aux_cor_l;
	int32 aux_pot_l;
	int32 aux_ener_l;
	int32 aux_cs5460_l;
	int32 status_cs5460_l;	
#endif

#if (com_rep == true)
	#define NRO_MODOS_REP	1
	#define NRO_PROTO_REP	4
	#define REP_NORMAL		0
	#define REP_ESTENDIDO	1
	#define REP_GRANDEZAS	2
	#define REP_MISTO		3

	short igual;
	short flag_fatura_rep;
	short transferir_REP;

	char definicao_REP;
	char cod_bloco_REP;
	char quadrante_aux;
	long long nro_serie_REP;
	long long ke_REP;
	long long rtc_REP;
	long long rtp_REP;
	long long data_REP;
	long long caracterizacao_REP;
	long tensao_R_REP;
	long tensao_S_REP;
	long tensao_T_REP;
	long corrente_R_REP;
	long corrente_S_REP;
	long corrente_T_REP;
	long corrente_N_REP;
	signed long pot_ativa_R_REP;
	signed long pot_ativa_S_REP;
	signed long pot_ativa_T_REP;
	signed long pot_ativa_total_REP;
	signed long pot_reativa_R_REP;
	signed long pot_reativa_S_REP;
	signed long pot_reativa_T_REP;
	signed long pot_reativa_total_REP;
	signed long pot_aparente_R_REP;
	signed long pot_aparente_S_REP;
	signed long pot_aparente_T_REP;
	signed long pot_aparente_total_REP;
	long frequencia_REP;
	long ctrl_demanda_REP;
	long ene_ati_pos;
	long ene_rea_pos_ati_pos;
	long ene_rea_neg_ati_pos;
	long ene_ati_neg;
	long ene_rea_pos_ati_neg;
	long ene_rea_neg_ati_neg;
	long cont_sem_REP;

	// bytes
	char baud_rate_REP;
	char quadrante;
	char protocolo_REP;
	char qtd_byte_REP;
	char tarif_reativo_ativa;
	char posto_horario;
	char time_out_rec_rep;
	char time_out_troca_tarifa;
	char fatura_rep;
	char fatura_rep_old;
	char tarifa_rep;
	char tarifa_rep_old;
	char periodo;
	char fim_interv_reat_rep;
	char posto_reativo;
	char tarif_cap_rep;
	char tarif_ind_rep;
	char tarif_ind_rep_old;
	char posto_tarif_rep;
	char tipo_tarif_rep;
	char num_int2_ant;
	char num_int_ant;
	char num_int;
	char num_int2;
	char timer_integra;
	char erro_rep;
	char tipo_fp;
	char tipo_fp_men;
	char time_out_rep;
	char nbyte_rep;
	char byte_rep;
	char nbit_rep;
	char time_out_modo_rep;
	char posi_erro1;
	char posi_erro2;
	
	long CRC_calculado;
	long CRC_recebido;

	// words
	word fat_conv_ativa;
	word fat_conv_reativa;
	float kkw;
	float kkvar;
	
	word puls_c1_rep2_ant;
	word puls_c1_rep_ant;
	word puls_c2_rep_ant;
	word seg_falt_rep;
	word seg_falt_rep_ant;
	word puls_c1_rep2;
	word puls_c1_rep;
	word puls_c2_rep;
	word e_ativa2;
	word e_ativa;
	word e_reativa;
	word e_ativa2_ant;
	word e_ativa_ant;
	word e_reativa_ant;
	
	word ultimo_pulso_at;
	word ultimo_pulso_reat;
	word ultimo_pulso_at_tmp;
	word ultimo_pulso_reat_tmp;

	word ultima_pot_at;
	word ultima_pot_reat;
	
	// longs
	int32 val_ativa;
	int32 val_reativa;
	int32 val_rea_ind;
	int32 val_rea_cap;
//	float aux_f1;
	float fp_ativa;
	float fp_reativa;
	float fp_ati_aux;
	float fp_rea_aux;
	
	// buffers
	char buf_rec_rep[10];
	char buf_rec_tmp[10];
	#if (ST8500C == true)
		#define NRO_INTERVALOS_INTEGRACAO	30
	#else
		#define NRO_INTERVALOS_INTEGRACAO	15
	#endif
	word int_ativa[NRO_INTERVALOS_INTEGRACAO + 1];
	word int_reativa[NRO_INTERVALOS_INTEGRACAO + 1];
	word int_ati_aux[NRO_INTERVALOS_INTEGRACAO + 1];
	word int_rea_aux[NRO_INTERVALOS_INTEGRACAO + 1];
	
//	char char_reativa[NRO_INTERVALOS_INTEGRACAO + 1];
//	word buf_pulso1[5];
//	word buf_pulso2[5];

#else
	#if (st8500c == true)
		#if (com_tc == true)
			char time_out_modo_rep;
			char timer_integra;
			word seg_falt_rep;
		#endif
	#endif
#endif

#if (controlador == true)
	#if (AUTOSET == true)
		short em_autoset;

		char time_out_enter;
		char time_out_reset;
		char time_out_autoset;
		char passo_autoset;
		char time_out_teste_autoset;
		char aux_teste;
		char aux_banco;
		char tentativas_autoset;
		
		word pot_reativa_r_old;
		word pot_reativa_s_old;
		word pot_reativa_t_old;
		word valor_capacitor;
		word pot_reativa_cap_r;
		word pot_reativa_ind_r;
		
		int32 soma_media_reativa_r;
		
	#endif
#endif


/* Definicao das variaveis	de tratamento da comunicacao serial */
char ptrtx;
char ptrrx;
char retrx;
char numbrx;
char numbtx;



// definicao dos buffers de uso geral.


#if (st5x == true)
	#define teste_off_set	0
#elif (st94 == true)
	#define teste_off_set	0
#elif (st92 == true)
	#define teste_off_set	0
#elif (ST8100C == true)
	#define teste_off_set	0
#elif (ST8200C == true)
	#define teste_off_set	0
#elif (ST8300C == true)
	#define teste_off_set	0
#elif (st9600r == true)
	#if (teste_vag == true)
		#define teste_off_set	0
	#else
		#define teste_off_set	0
	#endif
#else
	#define teste_off_set	0
#endif


#if (chip_cs5460a == true) 

#elif (ade7754 == true)
	signed word buf_tensao_r[NRO_AMOSTRAS_CHT + 1];
	signed word buf_corrente_r[NRO_AMOSTRAS_CHT + 1];
	#if (monofasico == false)
		signed word buf_tensao_s[NRO_AMOSTRAS_CHT + 1];
		signed word buf_corrente_s[NRO_AMOSTRAS_CHT + 1];
		signed word buf_tensao_t[NRO_AMOSTRAS_CHT + 1];
		signed word buf_corrente_t[NRO_AMOSTRAS_CHT + 1];
	#endif
	char passo_le_senoide;

#else
	signed word buf_tensao_r[NRO_AMOSTRAS+1];
	signed word buf_corrente_r[NRO_AMOSTRAS+1];
	#if (monofasico == false)
		signed word buf_tensao_s[NRO_AMOSTRAS+1];
		signed word buf_tensao_t[NRO_AMOSTRAS+1];
		signed word buf_corrente_s[NRO_AMOSTRAS+1];
		signed word buf_corrente_t[NRO_AMOSTRAS+1];
	#endif
#endif

//signed word buf_tensao[(NRO_AMOSTRAS)];
//signed word buf_corrente[(NRO_AMOSTRAS)];

#if (teste_off_set == 1)
	int32 soma_efi_cr_tmp;
	signed word buf_ten_tmp[NRO_AMOSTRAS];
	signed word buf_cor_tmp[NRO_AMOSTRAS];
#endif	


char buf_rx[TAM_RX+4];
char buf_tx[TAM_TX+4];

char buf_tmp[32];

#if (ST8100C == true)
	#if (simula_forno == true)
		char tempo_on, tempo_off, conta_tempo, aux_btmp;
		char buf_lig_banco[255];
	#endif		
#endif


// Definição dos Códigos de Registros
#define reg_sem_ocor									0
#define registro_normal 								1
#define reg_tensao_r_alta								2
#define reg_tensao_s_alta								3
#define reg_tensao_t_alta								4
#define reg_tensao_r_baixa								5
#define reg_tensao_s_baixa								6
#define reg_tensao_t_baixa								7
#define reg_chtc_alto_r									8
#define reg_chtc_alto_s									9
#define reg_chtc_alto_t									10
#define reg_cor_r_alta									11
#define reg_cor_s_alta									12
#define reg_cor_t_alta									13
#define reg_fp_ind										14
#define reg_fp_cap										15
#define reg_faltou_cap									16
#define reg_tc_inv_r									17
#define reg_tc_inv_s									18
#define reg_tc_inv_t									19
#define reg_seq_inv										20
#define reg_temp_alta									21
#define reg_transm_regs									22
#define reg_transm_ocor									23			
#define reg_volta_energia 								24
#define reg_reset										25
#define reg_inicio										26
#define reg_final										27
#define reg_aj_calend 									28
#define reg_apagou										29
#define reg_prog_tecla									30
#define reg_prog_nauto									31
#define reg_falta_energia 								32
#define reg_apagou_cht									33
#define reg_transmitir_cht								34
#define reg_chtt_alto									35
#define reg_chtc_alto									36
#define reg_reset_alarme								37
#define reg_tensao_alta									38
#define reg_tensao_baixa								39
#define reg_corrente_alta								40
#define reg_falta_fase_r								41
#define reg_falta_fase_s								42
#define reg_falta_fase_t								43
#define reg_falta_fases									44
#define reg_cor_r_baixa									45
#define reg_cor_s_baixa									46
#define reg_cor_t_baixa									47
#define reg_corrente_baixa								48
#define reg_troca_tensao								49
#define reg_potencia_alta								50
#define reg_pot_r_alta									51
#define reg_pot_s_alta									52
#define reg_pot_t_alta									53
#define reg_codigo_local								54
#define reg_demanda_ativa_alta							55
#define reg_auto_set									56
#define reg_em_banco_minimo								57
#define reg_trocou_periodo_fatura_periodo_ponta			58
#define reg_trocou_periodo_fatura_periodo_fora_ponta	60
#define reg_falta_pulso_rep								62
#define reg_volta_pulso_rep								63
#define reg_des_ten_alta								64
#define reg_des_ten_baixa								65
#define reg_troca_pt_0									66
#define reg_troca_pt_1									67
#define reg_troca_pt_2									68
#define reg_fatura_rep									69
#define reg_virou_dia									70
#define reg_prog_defasagem								71
#define reg_consumo										72
#define reg_tarifa_rep									73

#define reg_teste										99

// tabela de erros
/*
char qerro
#define erro_0		0b00000000			// erro de corrente critica; corrente < 3%
#define erro_1		0b00000010			// alarme corrente baixa; corrente < alarme corrente baixa
#define erro_2		0b00000100			// alarme corrente alta; corrente > alarme corrente alta
#define erro_3		0b00001000			// alarme de sub-tensão; tensao < alarme de tensão baixa
#define erro_4		0b00010000			// alarme de sobre-tensão; tensão > alarme de tensão alta.
#define erro_5		0b00100000			// alarme de chtt alto. chtt > alarme de chtt
#define erro_6		0b01000000			// alarme de chtc alto. chtc > alarme de chtt
#define erro_7		0b10000000			// alarme de ponteira invertida; ponteira em fase errada ou invertida.
*/

// tabela de status de alarmes
// Parte LOW
							//5432109876543210
#define STATUS_FP_CAP_ON			0b0000000000000001
#define STATUS_FP_IND_ON			0b0000000000000010
#define STATUS_TEN_A_ON				0b0000000000000100
#define STATUS_TEN_B_ON				0b0000000000001000
#define STATUS_COR_A_ON				0b0000000000010000
#define STATUS_COR_B_ON				0b0000000000100000
#define STATUS_CHTA_A_ON			0b0000000001000000
#define STATUS_CHTC_A_ON			0b0000000010000000
#define STATUS_DEM_A_ON				0b0000000100000000
#define STATUS_ERRO_REP_ON			0b0000001000000000
#define STATUS_ERRO_CONST_REP_ON	0b0000010000000000

							//5432109876543210
#define STATUS_FP_CAP_OFF			0b1111111111111110
#define STATUS_FP_IND_OFF			0b1111111111111101
#define STATUS_TEN_A_OFF			0b1111111111111011
#define STATUS_TEN_B_OFF			0b1111111111110111
#define STATUS_COR_A_OFF			0b1111111111101111
#define STATUS_COR_B_OFF			0b1111111111011111
#define STATUS_CHTA_A_OFF			0b1111111110111111
#define STATUS_CHTC_A_OFF			0b1111111101111111
#define STATUS_DEM_A_OFF			0b1111111011111111
#define STATUS_ERRO_REP_OFF			0b1111110111111111
#define STATUS_ERRO_CONST_REP_OFF	0b1111101111111111

#if (home_system == true)
	int ContHSnet;
	#define TEMPO_HSNET		60
		#if (debug_hsnet == true)
			int debug_count = 0;
		#endif
#endif
