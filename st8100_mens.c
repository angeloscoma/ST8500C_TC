
	//					  [linha][colunas-fixa em 18+1]
	//					            01234567890123456789
	const char tabela_mens[74][21]={"                ",		//0
 									" TENSAO NOMINAL ",		//1
 									" TC VALOR ",			//2
 									" TP VALOR ",			//3
 									" SET POINT ",			//4
 									" ENDERECO MODBUS ",	//5
 									"MAIOR ACIONAMENTO ",	//6
 									" BANCO MINIMO ",		//7
 									" CORRENTE MINIMA ",	//8
 									"TEMPO ACIONAMENTO ",	//9
 									" BAUD RATE ",			//10
 									" TIPO LIGACAO ",		//11
 									" POT.ATIVA ",			//12
 									" POT.APARENTE ",		//13
 									" POT.REATIVA ",		//14
 									" FALTA KVAR ",			//15
 									" FATOR POTENCIA ",		//16
 									" TEMPO REPOUSO ",		//17
 									" NRO DE BANCOS ",		//18
 									" SEQUENCIA ",			//19
 									" FREQUENCIA ",			//20
									" PROG.AUTORIZADA ",	//21
									" PROG. NAO AUTO. ",	//22
									" MED. ELETRICAS ",		//23
									" CH TENSAO ",			//24
									" CH CORRENTE ",		//25
									" GERAL PROGRAMA ",		//26
									" ALARMES ",			//27
									" BANCOS PROGRAMA ",	//28
									"",						//29
 									" VALOR BANCOS ",		//30
 									" DESLIGAMENTOS ",		//31
 									" ACIONAMENTO ",		//32
 									" OCORRENCIAS ",		//33
									" TENSAO FN ",			//34
									" TENSAO FF ",			//35
									" TENSAO NA ALTA ",		//36
									" CORRENTE ",			//37
									" MANUTENCAO ",			//38
									" FP INDUTIVO ",		//39
									" FP CAPACITIVO ",		//40
									" TENSAO ALTA ",		//41
									" TENSAO BAIXA ",		//42
									" SOBRE CORRENTE ",		//43
									" SUB CORRENTE ",		//44
									" HARM. TENSAO ",		//45
									" HARM. CORRENTE ",		//46
									" TEMPO ACIONADO ",		//47
									" NRO ACIONAMENTOS ",	//48
 									" VAR ACIMA ",			//49
 									" RELOGIO ",			//50
 									" USUARIO ",			//51
 									" APAGAR ",				//52
 									" CORRENTE CRITICA ",	//53
 									" TABELA ",				//54
 									" TEMPO DESLIGA ",		//55
 									" STATUS ",				//56
 									" SEM LIMITE ",			//57
 									" TARIFACAO ",			//58
 									" TEMPO FALTA ",		//59
 									" PULSO ATIVO ",		//60
 									" PULSO REATIVO ",		//61
 									" MODO MEDICAO ",		//62
 									" CONS.ATIVA ",			//63
 									" CONS.REATIVA ",		//64
 									" MODO MEDICAO TC ",	//65
 									" MODO MEDICAO IU ",	//66
 									" ERRO CRC IU ",		//67
 									" BANCO EM REPOUSO ",	//68
 									" ULT PULSO ATIVO ",	//69
 									" ULT PULSO REATIVO ",	//70
 									" ULT POT ATIVA ",		//71
 									" ULT POT REATIVO ",	//72
									" FP "		//73
 									
 									
									};

	const char tabela_mens_tipo2[17][5]={" ",		//00
										"B01",		//01
										"B02",		//02
										"B03",		//03
										"B04",		//04
										"B05",		//05
										"B06",		//06
										"B07",		//07
										"B08",		//08
										"B09",		//09
										"B10",		//10
										"B11",		//11
										"B12",		//12
										"B13",		//13
										"B14",		//14
										"B15",		//15
										"B16"		//16
										};

	const char tabela_mens_tipo3[17][5] = {	" ",		//00
											"01-T",		//01
											"02-T",		//02
											"03-T",		//03
											"04-T",		//04
											"05-T",		//05
											"06-T",		//06
											"07-T",		//07
											"08-T",		//08
											"09-T",		//09
											"10-T",		//10
											"11-T",		//11
											"12-T",		//12
											"13-T",		//13
											"14-T",		//14
											"15-T",		//15
											"16-T"		//16
											};

	const char tabela_mens_tipo4[17][5] = {	" ",		//00
											"01-V",		//01
											"02-V",		//02
											"03-V",		//03
											"04-V",		//04
											"05-V",		//05
											"06-V",		//06
											"07-V",		//07
											"08-V",		//08
											"09-V",		//09
											"10-V",		//01
											"11-V",		//11
											"12-V",		//12
											"13-V",		//13
											"14-V",		//14
											"15-V",		//15
											"16-V"		//16
											};

//											012345678901234567890
	const char tabela_mens_status[18][21] ={" ",					//0
											" TENSAO CRITICA ",		//1
											" LIGACAO FN ",			//2
											" LIGACAO FF ",			//3
											" TENSAO ALTA ",		//4
											" TENSAO BAIXA ",		//5
											" CORRENTE ALTA ",		//6
											" CORRENTE BAIXA ",		//7
											" TC INVERTIDO ",		//8
											" AJUSTAR RELOGIO ",	//9
											" DESL TENSAO ALTA ",	//10
											" FALTA CAPACITOR ",	//11
											" FP CAPACITIVO ",		//12
											" CORRENTE CRITICA ",	//13
											" EM BANCO MINIMO ",	//14
											" DESL CHT TENSAO ",	//15
											" DESL CHT CORRENTE ",	//16
											" EM MODO REP "			//17
											};

	#if (com_rep == true)
		const char tabela_menu4[nro_menus4_rep+1]={	0,
												1,
												2,
												3,
												11,
												4,
												5,
												10,
												62,
												63,
												64
												};
	#else
		const char tabela_menu4[nro_menus4+1]={	0,
												1,
												2,
												3,
												11,
												4,
												5,
												10
												};
	#endif

//	const char tabela_cont_harm[5]= {" ",
//									"FUND",
//									"03A",
//									"05A",
//									"07A",
//									"11A"
//									};


	const char tabela_menu_bancos[nro_menu_bancos+1]={	0,	//
														18,	// Nro de Bancos
														6,	// Maior Acioanmeto
														7,	// Banco Mínimo
														8,	// Corrente Mínima
														9,	// Tempo Acionamento
														55,	// Tesmpo Desliga
														19,	// Seqüência
														30,	// Valor dos Bancos
														17	// Tempo Repouso
														};

	
	#define m_menu1_7		12
	#define m_menu1_8		13
	#define m_menu1_9		14
	#define m_menu1_9_2		30
	#define m_menu1_10		15
	#define m_menu1_10_2	31
	#define m_menu1_12		16
	#define m_menu1_13		17
	#define m_menu1_14		18	
	#define m_menu1_15		19
	#define m_menu1_16		20

/* definições de menus */
	#define m_prog_liberada	21
	#define m_prog_nao_auto	22
	#define m_menu1			23
	#define m_menu2			24
	#define m_menu3			25
	#define m_menu4			26
	#define m_menu5			28
	#define m_menu6			27
	#define m_menu7			31
	#define m_menu8			32
	#define m_menu9			33
	#define m_menu10		38
	#define m_menu11		50
	#define m_menu12		56


									//  01234567890123456789
	const char tabela_erros[58][21]	  ={"                  ",	//0
										" FIM OCORRENCIA ",		//1
										" REGISTRO NORMAL ",	//2
										" TENS ALTA FASE R ",	//3
										" TENS ALTA FASE S ",	//4
										" TENS ALTA FASE T ",	//5
										" TEN BAIXA FASE R ",	//6
										" TEN BAIXA FASE S ",	//7
										" TEN BAIXA FASE T ",	//8
										" CHT CORR. ALTO R ",	//9
										" CHT CORR. ALTO S ",	//10
										" CHT CORR. ALTO T ",	//11
										" CORR ALTA FASE R ",	//12
										" CORR ALTA FASE S ",	//13
										" CORR ALTA FASE T ",	//14
										" FP INDUTIVO ",		//15
										" FP CAPACITIVO ",		//16
										" FALTA CAPACITOR ",	//17
										" TC INVERTIDO R ",		//18
										" TC INVERTIDO S ",		//19
										" TC INVERTIDO T ",		//20
										" SEQ. INVERTIDA ",		//21
										" TEMPERATURA ALTA ",	//22
										" TRANSMISSAO REG. ",	//23
										" TRANSMISSAO OCOR ",	//24
										" VOLTA DE ENERGIA ",	//25
										" RESET ",				//26
										" INICIO REGISTRO ",	//27
										" FINAL REGISTRO ",		//28
										" AJUSTE DE DATA ",		//29
										" APAGAMENTO ",			//30
										" PROGRAMA TECLADO ",	//31
										" PROG NAO AUTORIZ ",	//32
										" FALTA DE ENERGIA ",	//33
										" APAGAMENTO CHT ",		//34
										" TRANSMISSAO CHT ",	//35
										" CHT TENSAO ALTO ",	//36
										" CHT CORREN ALTO ",	//37
										" RESET DO ALARME ",	//38
										" TENSAO ALTA ",		//39
										" TENSAO BAIXA ",		//40
										" CORRENTE ALTA ",		//41
										" FALTA FASE R ",		//42
										" FALTA FASE S ",		//43
										" FALTA FASE T ",		//44
										" FALTA FASES ",		//45
										" CORRENTE BAIXA R ",	//46
										" CORRENTE BAIXA S ",	//47
										" CORRENTE BAIXA T ",	//48
										" CORRENTE BAIXA ",		//49
										" TROCA TENSAO ",		//50
										" POTENCIA ALTA ",		//51
										" POTENCIA ALTA R ",	//52
										" POTENCIA ALTA S ",	//53
										" POTENCIA ALTA T ",	//54
										" CODIGO LOCAL ",		//55
										" REGISTRO TESTE ",		//56
										" EM BANCO MINIMO "		//57
										};




// Tabela para programação dos bancos
	const char NRO_SEQ_BANCOS[7] ={0,4,8,10,16,22,22};

	const char TAB_2_BANCOS[4][2] = {1,1,
									1,2,
									1,3,
									1,4};

	const char TAB_3_BANCOS[8][3] = {1,1,1,
									1,1,2,
									1,2,2,
									1,2,4,
									1,4,4,
									1,4,8,
									1,2,3,
									1,3,5};

	const char TAB_4_BANCOS[10][4] = {1,1,1,1,
									1,1,1,2,
									1,1,2,2,
									1,2,2,2,
									1,2,2,4,
									1,2,4,4,
									1,2,4,8,
									1,2,2,3,
									1,2,3,3,
									1,2,3,4};

	const char TAB_5_BANCOS[16][5] = {1,1,1,1,1,
									1,1,1,1,2,
									1,1,1,2,2,
									1,1,2,2,2,
									1,2,2,2,2,
									1,2,2,2,4,
									1,2,2,4,4,
									1,2,4,4,4,
									1,2,4,4,8,
									1,2,4,8,8,
									1,1,2,2,3,
									1,2,2,2,3,
									1,2,2,3,3,
									1,2,3,3,4,
									1,2,3,4,4,
									1,2,3,4,5};


	const char TAB_6_BANCOS[22][6] = {1,1,1,1,1,1,
									1,1,1,1,1,2,
									1,1,1,1,2,2,
									1,1,1,2,2,2,
									1,1,2,2,2,2,
									1,2,2,2,2,2,
									1,2,2,2,2,4,
									1,2,2,2,4,4,
									1,2,2,4,4,4,
									1,2,4,4,4,4,
									1,2,4,4,4,8,
									1,2,4,4,8,8,
									1,2,4,8,8,8,
									1,1,2,2,3,3,
									1,2,2,2,3,3,
									1,2,2,3,3,3,
									1,2,2,3,3,4,
									1,2,3,3,4,4,
									1,2,3,4,4,4,
									1,2,3,4,4,5,
									1,2,3,4,5,5,
									1,2,3,4,5,6};

