
	const char tabela_unidades[6][5]={"A",  	//0
									  "kW  ",	//1
									  "kVA ",	//2
									  "kVAr",	//3
									  "Hz  ",	//4
									  "Vac "	//5
									  };


	const char tabela_mens[158][17]={"                ",  	//0
									#if (teste_aciona_rele == true)
		     		             		"ST8200C/teste   ",	//1
									#else
										#if (bancos_12 == true)
											#if (com_rep == true)
				     		             		" ST8200C/12/IU  ",	//1
											#else
				     		             		"S T 8 2 0 0 C/12",	//1
				     		             	#endif
										#else
											#if (com_rep == true)
				     		             		"S T 8 2 0 0 C/IU",	//1
											#else
				     		             		" S T 8 2 0 0 C  ",	//1
				     		             	#endif
				     		             #endif
			     		            #endif
			     		             "NR:@@@@.@ V:@.@@",	//2
			     		             " Med. Eletricas ",    //3
			     		             "   Harmonicos   ",	//4
			     		             " Comando Manual ",	//5
			     		             "   Ocorrencias  ",	//6
			     		             " Programa Geral ",	//7
			     		             "Programa  Bancos",	//8
									 "Programa Alarmes",	//9
			     		             "Programa Desliga",	//10
									 "   Manutencao   ",	//11
									 "  Harm. Tensao  ",	//12
									 " Harm. Corrente ",	//13
									 "N. de Bancos:   ",	//14
									 "     Usuario    ",	//15
									 "Max.:       kVAr",	//16
									 "Min.:       kVAr",	//17
									 "Acionamento:   s",	//18
									 "B  :        kVAr",	//19
									 "Tempo B  :     s",	//20
									 "Cor Minima:    %",	//21
									 "Manual FP:      ",	//22
									 "   Tensao RMS   ",	//23
									 "  Corrente RMS  ", 	//24
									 "   Frequencia   ",    //25
									 "   Pot. Ativa   ", 	//26
									 " Pot.  Aparente ",  	//27
									 "  Pot. Reativa  ",	//28
									 " Fator Potencia ",    //29
									 "Memoria: x NOK!!",	//30
									 " kVAr Excedente ",	//31
									 "????????????????",	//32
									 "          Hz    ",	//33
									 "Tensao:     Vac ",	//34
									 "Valor TC:     /5",	//35
									 "Valor TP:       ",	//36
									 "Set-Point:      ",	//37
									 "Tipo Ligacao:   ",	//38
									 "End. Modbus:    ",	//39
									 "Baud Rate:      ",	//40
									 "FP Indutivo:    ",	//41
									 "FP Capacit.:    ",	//42
									 "Tensao Alta:   %",	//43
									 "Sub Tensao:    %",	//44
									 "Cor. Alta:     %",	//45
									 "Cor. Baixa:    %",	//46
									 "CH Tensao:     %",	//47
									 "CH Corrente:   %",	//48
									 "Prog. Nao Autor.",	//49
									 " Prog. Liberada ",	//50
									 "@@@@@ Sem Limite",	//51
									 " Liga Banco:    ",	//52
									 " Desl Banco:    ",	//53
									 "     Total:     ",	//54
									 "  Fundamental:  ",	//55
									 "     Harmonica: ",	//56
									 "          %     ",	//57
									 "Ajustar Relogio!",	//58
									 "                ",	//59
									 "   /  /     :   ",	//60
									 "       %       %",	//61
									 "Tempo  Banco:   ",	//62
									 "Aciona Banco:   ",	//63
									 "         Horas  ",	//64
									 "         Vezes  ",	//65
									 " Fim Ocorrencias",	//66	Cod Ocorrencia = 0
									 "Registro  Normal",	//67	Cod Ocorrencia = 1
									 "  Tensao Alta   ",	//68	Cod Ocorrencia = 2
									 "  Tensao Alta   ",	//69	Cod Ocorrencia = 3
									 "  Tensao Alta   ",	//70	Cod Ocorrencia = 4
									 "  Tensao Baixa  ",	//71	Cod Ocorrencia = 5
									 "  Tensao Baixa  ",	//72	Cod Ocorrencia = 6
									 "  Tensao Baixa  ",	//73	Cod Ocorrencia = 7
									 " CHT Corr. Alto ",	//74	Cod Ocorrencia = 8
									 "CHT Corr. Alto S",	//75	Cod Ocorrencia = 9
									 "CHT Corr. Alto T",	//76	Cod Ocorrencia = 10
									 " Corrente Alta  ",	//77	Cod Ocorrencia = 11
									 " Corrente Alta  ",	//78	Cod Ocorrencia = 12
									 " Corrente Alta  ",	//79	Cod Ocorrencia = 13
									 "  FP  Indutivo  ",	//80	Cod Ocorrencia = 14
									 " FP  Capacitivo ",	//81	Cod Ocorrencia = 15
									 "Falta  Capacitor",	//82	Cod Ocorrencia = 16
									 "  TC Invertido  ",	//83	Cod Ocorrencia = 17
									 " TC Invertido S ",	//84	Cod Ocorrencia = 18
									 " TC Invertido T ",	//85	Cod Ocorrencia = 19
									 " Seq. Invertida ",	//86	Cod Ocorrencia = 20
									 "Temperatura Alta",	//87	Cod Ocorrencia = 21
									 "Transmissao Reg.",	//88	Cod Ocorrencia = 22
									 "Transmissao Ocor",	//89	Cod Ocorrencia = 23
									 "Volta de Energia",	//90	Cod Ocorrencia = 24
									 "      Reset     ", 	//91	Cod Ocorrencia = 25
									 "Inicio  Registro", 	//92	Cod Ocorrencia = 26
									 " Final Registro ", 	//93	Cod Ocorrencia = 27
									 " Ajuste de Data ", 	//94	Cod Ocorrencia = 28
									 "   Apagamento   ", 	//95	Cod Ocorrencia = 29
									 "Programa Teclado",	//96	Cod Ocorrencia = 30
									 "Prog Nao Autoriz",	//97	Cod Ocorrencia = 31
									 "Falta de Energia",    //98	Cod Ocorrencia = 32
									 " Apagamento CHT ",	//99	Cod Ocorrencia = 33
									 "Transmissao  CHT", 	//100	Cod Ocorrencia = 34
									 "CHT Tensao  Alto", 	//101	Cod Ocorrencia = 35
									 "CHT Corren. Alto", 	//102	Cod Ocorrencia = 36
									 "Reset do Alarme ",	//103	Cod Ocorrencia = 37
									 "  Tensao  Alta  ",	//104	Cod Ocorrencia = 38
									 "  Tensao Baixa  ",	//105	Cod Ocorrencia = 39
									 " Corrente  Alta ",	//106	Cod Ocorrencia = 40
									 "  Falta Fase R  ",	//107	Cod Ocorrencia = 41
									 "  Falta Fase S  ",	//108	Cod Ocorrencia = 42
									 "  Falta Fase T  ",	//109	Cod Ocorrencia = 43
									 "  Falta  Fases  ",	//110	Cod Ocorrencia = 44
									 " Corrente Baixa ",	//111	Cod Ocorrencia = 45
									 "Corrente Baixa S",	//112	Cod Ocorrencia = 46
									 "Corrente Baixa T",	//113	Cod Ocorrencia = 47
									 " Corrente Baixa ",	//114	Cod Ocorrencia = 48
									 "  Troca Tensao  ",	//115	Cod Ocorrencia = 49
									 " Potencia  Alta ",	//116	Cod Ocorrencia = 50
									 "Potencia Alta  R",	//117	Cod Ocorrencia = 51
									 "Potencia Alta  S",	//118	Cod Ocorrencia = 52
									 "Potencia Alta  T",	//119	Cod Ocorrencia = 53
									 "  Codigo Local  ",	//120	Cod Ocorrencia = 54
									 " Registro Teste ", 	//121	Cod Ocorrencia = 99
									 "Ocorrencia:     ",	//122
									 "     Relogio    ",	//123
									 " Data:   /  /   ",	//124
									 " Hora:     :    ",	//125
									 " Tensao Critica ",	//126
									 "Corrente Critica",	//127
									 "     Tabela     ",	//128
									 " Memoria: 1 NOK!",	//129
									 "Desl. por Tensao",	//130
									 "   Limpa Ocorr. ",	//131
									 "   * Cancelar   ",	//132
									 "  Zerar Banco   ",	//133
									 "Corrente Critica",	//134
									 "     Status     ",	//135
									 "Em Banco Minimo ",	//136
									 "Desaciona:     s",	//137
									 "     Status     ",	//138
									 "Modo Medicao:   ",	//139
									 "Modo Medicao: IU",	//140
									 " K. kWh:        ",	//141
									 " K. kVArh:      ",	//142
									 "Tar:   Tempo:   ",	//143
									 "P:      /       ",	//144
									 "Ult.P kW:  @@@@@",	//145
									 "Ult.P kVAr:@@@@@",	//146
									 "ERRO CRC - IU!!!",	//147
									 "Repouso B@@/@@@s",	//148
									 "Em Auto Set !!!!",	//149
									 "Ult.kW:  @@@@   ",	//150
									 "Ult.kVAr:@@@@   ",	//151
									 " Em Auto teste  ",	//152
									 "Atuacao em: @@@s",	//153
									 "FP Unitario:1.00",	//154
									 "Defasagem: @@@ G",	//155  
									 " Repos. Demanda ",	//156	Cod Ocorrencia = 69
									 " Prot. REP:     "		//157
	 								 };

	const char tabela_mens_esp[154][17]={"                ",  	//0
				     		             " S U L T E C H  ",	//1
				     		             "    ST8620C     ",	//2
				     		             " Med. Electricas",    //3
				     		             "   Harmonicos   ",	//4
				     		             "    Comandos    ",	//5
				     		             "   Ocorrencias  ",	//6
				     		             "Programa General",	//7
				     		             "Programa  Bancos",	//8
										 "Programa Alarmes",	//9
				     		             "Programa Desliga",	//10
										 "   Manutencao   ",	//11
										 "  Harm. Tensao  ",	//12  		             
										 " Harm. Corrente ",	//13
										 "N. de Bancos:   ",	//14
										 "     Usuario    ",	//15
										 "Max.:       kVAr",	//16  		             
										 "Min.:       kVAr",	//17
										 "Acionamento:   s",	//18
										 "B  :        kVAr",	//19
										 "Tempo B  :     s",	//20
										 "Cor Minima:    %",	//21
										 "Manual  FP:     ",	//22
										 "   Tensao RMS   ",	//23
										 "  Corrente RMS  ", 	//24  		             
										 "   Frequencia   ",    //25
										 "   Pot. Ativa   ", 	//26
										 " Pot.  Aparente ",  	//27
										 "  Pot. Reativa  ",	//28
										 " Fator Potencia ",    //29
										 "Memoria: x NOK!!",	//30
										 "     Falta:     ",	//31
										 "    Excesso:    ",	//32
										 "          Hz    ",	//33
										 "Tensao:     Vac ",	//34
										 "Valor TC:     /5",	//35
										 "Valor TP:       ",	//36
										 "Set-Point:      ",	//37
										 "Tipo Ligacao:   ",	//38
										 "End. Modbus:    ",	//39
										 "Baud Rate:      ",	//40
										 "FP Indutivo:    ",	//41
										 "FP Capacit.:    ",	//42
										 "Tensao Alta:   %",	//43
										 "Sub Tensao:    %",	//44
										 "Cor. Alta:     %",	//45
										 "Cor. Baixa:    %",	//46
										 "CH Tensao:     %",	//47
										 "CH Corrente:   %",	//48
										 "Prog. Nao Autor.",	//49
										 " Prog. Liberada ",	//50
										 "@@@@@ Sem Limite",	//51
										 " Liga Banco:    ",	//52
										 " Desl Banco:    ",	//53
										 "     Total:     ",	//54
										 "  Fundamental:  ",	//55
										 "     Harmonica: ",	//56
										 "          %     ",	//57
										 "Ajuste Relogio!!",	//58
										 "                ",	//59
										 "   /  /     :   ",	//60
										 "       %       %",	//61
										 "Tempo  Banco:   ",	//62
										 "Aciona Banco:   ",	//63
										 "         Horas  ",	//64
										 "         Vezes  ",	//65
										 " Sem Ocorrencia ",	//66	Cod Ocorrencia = 0
										 "Registro  Normal",	//67	Cod Ocorrencia = 1
										 "Tens Alta Fase R",	//68	Cod Ocorrencia = 2
										 "Tens Alta Fase S",	//69	Cod Ocorrencia = 3
										 "Tens Alta Fase T",	//70	Cod Ocorrencia = 4
										 "Ten Baixa Fase R",	//71	Cod Ocorrencia = 5
										 "Ten Baixa Fase S",	//72	Cod Ocorrencia = 6
										 "Ten Baixa Fase T",	//73	Cod Ocorrencia = 7
										 "CHT Corr. Alto R",	//74	Cod Ocorrencia = 8
										 "CHT Corr. Alto S",	//75	Cod Ocorrencia = 9
										 "CHT Corr. Alto T",	//76	Cod Ocorrencia = 10
										 "Corr Alta Fase R",	//77	Cod Ocorrencia = 11
										 "Corr Alta Fase S",	//78	Cod Ocorrencia = 12
										 "Corr Alta Fase T",	//79	Cod Ocorrencia = 13
										 "  FP  Indutivo  ",	//80	Cod Ocorrencia = 14
										 " FP  Capacitivo ",	//81	Cod Ocorrencia = 15
										 "Falta  Capacitor",	//82	Cod Ocorrencia = 16
										 "  TC Invertido  ",	//83	Cod Ocorrencia = 17
										 " TC Invertido S ",	//84	Cod Ocorrencia = 18
										 " TC Invertido T ",	//85	Cod Ocorrencia = 19
										 " Seq. Invertida ",	//86	Cod Ocorrencia = 20
										 "Temperatura Alta",	//87	Cod Ocorrencia = 21
										 "Transmissao Reg.",	//88	Cod Ocorrencia = 22
										 "Transmissao Ocor",	//89	Cod Ocorrencia = 23
										 "Volta de Energia",	//90	Cod Ocorrencia = 24
										 "      Reset     ", 	//91	Cod Ocorrencia = 25
										 "Inicio  Registro", 	//92	Cod Ocorrencia = 26
										 " Final Registro ", 	//93	Cod Ocorrencia = 27
										 "  Ajuste  Data  ", 	//94	Cod Ocorrencia = 28
										 "   Apagamento   ", 	//95	Cod Ocorrencia = 29
										 "Programa Teclado",	//96	Cod Ocorrencia = 30
										 "Prog Nao Autoriz",	//97	Cod Ocorrencia = 31
										 "Falta de Energia",    //98	Cod Ocorrencia = 32
										 " Apagamento CHT ",	//99	Cod Ocorrencia = 33
										 "Transmissao  CHT", 	//100	Cod Ocorrencia = 34
										 "CHT Tensao  Alto", 	//101	Cod Ocorrencia = 35
										 "CHT Corren. Alto", 	//102	Cod Ocorrencia = 36
										 "Reset do Alarme ",	//103	Cod Ocorrencia = 37
										 "  Tensao  Alta  ",	//104	Cod Ocorrencia = 38
										 "  Tensao Baixa  ",	//105	Cod Ocorrencia = 39
										 " Corrente  Alta ",	//106	Cod Ocorrencia = 40
										 "  Falta Fase R  ",	//107	Cod Ocorrencia = 41
										 "  Falta Fase S  ",	//108	Cod Ocorrencia = 42
										 "  Falta Fase T  ",	//109	Cod Ocorrencia = 43
										 "  Falta  Fases  ",	//110	Cod Ocorrencia = 44
										 "Corrente Baixa R",	//111	Cod Ocorrencia = 45
										 "Corrente Baixa S",	//112	Cod Ocorrencia = 46
										 "Corrente Baixa T",	//113	Cod Ocorrencia = 47
										 " Corrente Baixa ",	//114	Cod Ocorrencia = 48
										 "  Troca Tensao  ",	//115	Cod Ocorrencia = 49
										 " Potencia  Alta ",	//116	Cod Ocorrencia = 50
										 "Potencia Alta  R",	//117	Cod Ocorrencia = 51
										 "Potencia Alta  S",	//118	Cod Ocorrencia = 52
										 "Potencia Alta  T",	//119	Cod Ocorrencia = 53
										 "  Codigo Local  ",	//120	Cod Ocorrencia = 54
										 " Registro Teste ", 	//121	Cod Ocorrencia = 99
										 "Ocorrencia:     ",	//122
										 "Programa Relogio",	//123
										 " Data:   /  /   ",	//124
										 " Hora:     :    ",	//125
										 " Tensao Critica ",	//126
										 "Corrente Critica",	//127
										 "     Tabela     ",	//128
										 " Memoria: 1 NOK!",	//129
										 "Desl. por Tensao",	//130
										 "   Limpa Ocorr. ",	//131
										 "   * Cancelar   ",	//132
										 "  Zerar Banco   ",	//133
										 "Corrente Critica",	//134
										 "     Status     ",	//135
										 "Em Banco Minimo ",	//136
										 "Modo Medicao:TC ",	//139
										 "Modo Medicao:IU ",	//140
										 "  K. kWh:       ",	//141
										 "  K. kVAh:      ",	//142
										 "Tar:   Tempo:   ",	//143
										 "P:      /       ",	//144
										 "Ult.P kW:  @@@@@",	//145
										 "Ult.P kVAr:@@@@@",	//146
										 "ERRO - IU!!!    ",	//147
										 "Banco em repouso",	//148
										 "Em Auto Set !!!!",	//149
										 "Ult.kW:  @@@@@@ ",	//150
										 "Ult.kVAr:@@@@@@ ",	//151
										 " Em Auto teste  ",	//152
		 								 };

	#define nro_tab_ocor	71
	const char tabela_ocorrencias[nro_tab_ocor]={	66,		//0
													67,		//1
													68,		//2
													69,		//3
													70,		//4
													71,		//5
													72,		//6
													73,		//7
													74,		//8
													75,		//9
													76,		//10
													77,		//11
													78,		//12
													79,		//13
													80,		//14
													81,		//15
													82,		//16
													83,		//17
													84,		//18
													85,		//19
													86,		//20
													87,		//21
													88,		//22
													89,		//23
													90,		//24
													91,		//25
													92,		//26
													93,		//27
													94,		//28
													95,		//29
													96,		//30
													97,		//31
													98,		//32
													99,		//33
													100,	//34
													101,	//35
													102,	//36
													103,	//37
													104,	//38
													105,	//39
													106,	//40
													107,	//41
													108,	//42
													109,	//43
													110,	//44
													111,	//45
													112,	//46
													113,	//47
													114,	//48
													115,	//49
													116,	//50
													117,	//51
													118,	//52
													119,	//53
													120,	//54
													121,	//55
													152,	//56
													136,	//57
													0,		//58
													0,		//59
													0,		//60
													0,		//61
													147,	//62
													147,	//63
													104,	//64
													105,	//65
													0,		//66
													0,		//67
													0,		//68
													156		//69
													};	

						
	const char tabela_menu4[nro_menus4+1]={	0,
											1,
											2,
											3,
											11,
											4,
											5,
											10
											};									 
	
	#define m_menu_principal 3
	#define m_prog_liberada 11
	#define m_prog_nao_auto 11
	#define m_menu1	3
	#define m_menu2	4
	#define m_menu3	4
	#define m_menu4	5
	#define m_menu5	6
	#define m_menu6	9
	#define m_menu7	0
	#define m_menu8	0
	#define m_menu9	0
	#define m_menu10	0
	
	
	#define m_menu1_110  12
	#define m_menu1_111  13
	#define m_menu1_112  14
	#define m_menu1_113  15
	#define m_menu1_120  16
	#define m_menu1_121  13
	#define m_menu1_122  14
	#define m_menu1_123  15
	#define m_menu1_130  12
	#define m_menu1_131  20
	#define m_menu1_132  21
	#define m_menu1_133  22
	#define m_menu1_140  23
	#define m_menu1_141  20
	#define m_menu1_142  21
	#define m_menu1_143  22
	#define m_menu1_150  24
	#define m_menu1_151  13
	#define m_menu1_152  14
	#define m_menu1_153  15
	#define m_menu1_160  25
	#define m_menu1_161  26
	#define m_menu1_162  27
	#define m_menu1_163  0
	#define m_menu1_170  28
	#define m_menu1_171  30
	#define m_menu1_172  31
	#define m_menu1_173  32
	#define m_menu1_180  29
	#define m_menu1_181  31
	#define m_menu1_182  32
	#define m_menu1_183  33
	#define m_menu1_190  34
	#define m_menu1_191  13
	#define m_menu1_192  14
	#define m_menu1_193  15
	#define m_menu1_1100  35
	#define m_menu1_1101  13
	#define m_menu1_1102  14
	#define m_menu1_1103  15
	
	
	#define m_menu1_7  14
	#define m_menu1_8  14
	#define m_menu1_9  14
	#define m_menu1_10  14
	#define m_menu1_11  14
	#define m_menu1_12  14
	#define m_menu1_13  14
	#define m_menu1_14  14
	#define m_menu1_15  14
	#define m_menu1_16  14
	
	
	#define m_menu4_1	40
	#define m_menu4_2	41
	#define m_menu4_3	42
	#define m_menu4_4	43
	#define m_menu4_5	44
	#define m_menu4_6	45
	#define m_menu4_7	46
	#define m_menu4_8	47
	#define m_menu4_9	48
	#define m_menu4_10	49
	#define m_menu4_11	50
	#define m_menu4_12	51
	#define m_menu4_13	52
	#define m_menu4_14	53
	#define m_menu4_15	54
	#define m_menu4_16	55
	#define m_menu4_17	56



// Tabela para programaÿçÿão dos bancos
	const char NRO_SEQ_BANCOS[9] ={0,4,8,10,16,22};

	const char TAB_2_BANCOS[4][2]= {1,1,
									1,2,
									1,3,
									1,4};

	const char TAB_3_BANCOS[8][3]= {1,1,1,
									1,1,2,
									1,2,2,
									1,2,4,
									1,4,4,
									1,4,8,
									1,2,3,
									1,3,5};

	const char TAB_4_BANCOS[10][4]={1,1,1,1,
									1,1,1,2,
									1,1,2,2,
									1,2,2,2,
									1,2,2,4,
									1,2,4,4,
									1,2,4,8,
									1,2,2,3,
									1,2,3,3,
									1,2,3,4};

	const char TAB_5_BANCOS[16][5]={1,1,1,1,1,
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


	const char TAB_6_BANCOS[22][6]={1,1,1,1,1,1,	//0
									1,1,1,1,1,2,	//1
									1,1,1,1,2,2,	//2
									1,1,1,2,2,2,	//3
									1,1,2,2,2,2,	//4
									1,2,2,2,2,2,	//5
									1,2,2,2,2,4,	//6
									1,2,2,2,4,4,	//7
									1,2,2,4,4,4,	//8
									1,2,4,4,4,4,	//9
									1,2,4,4,4,8,	//10
									1,2,4,4,8,8,	//11
									1,2,4,8,8,8,	//12
									1,1,2,2,3,3,	//13
									1,2,2,2,3,3,	//14
									1,2,2,3,3,3,	//15
									1,2,2,3,3,4,	//16
									1,2,3,3,4,4,	//17
									1,2,3,4,4,4,	//18
									1,2,3,4,4,5,	//19
									1,2,3,4,5,5,	//20
									1,2,3,4,5,6};	//21

/*	const char TAB_7_BANCOS[22][7]={1,1,1,1,1,1,1,
									1,1,1,1,1,1,2,
									1,1,1,1,1,2,2,
									1,1,1,1,2,2,2,
									1,1,1,2,2,2,2,
									1,1,2,2,2,2,2,
									1,2,2,2,2,2,2,
									1,2,2,2,2,2,3,
									1,2,2,2,2,3,3,
									1,2,2,2,3,3,3,
									1,2,2,3,3,3,3,
									1,2,3,3,3,3,3,
									1,2,3,3,3,3,4,
									1,2,3,3,3,4,4,
									1,2,3,3,4,4,4,
									1,2,3,4,4,4,4,
									1,2,3,4,4,4,5,
									1,2,3,4,4,5,5,
									1,2,3,4,5,5,5,
									1,2,3,4,5,5,6,
									1,2,3,4,5,6,6,
									1,2,3,4,5,6,7};
									
	const char TAB_8_BANCOS[29[8]= {1,1,1,1,1,1,1,1,
									1,1,1,1,1,1,1,2,
									1,1,1,1,1,1,2,2,
									1,1,1,1,1,2,2,2,
									1,1,1,1,2,2,2,2,
									1,1,1,2,2,2,2,2,
									1,1,2,2,2,2,2,2,
									1,2,2,2,2,2,2,2,
									1,2,2,2,2,2,2,3,
									1,2,2,2,2,2,3,3,
									1,2,2,2,2,3,3,3,
									1,2,2,2,3,3,3,3,
									1,2,2,3,3,3,3,3,
									1,2,3,3,3,3,3,3,
									1,2,3,3,3,3,3,4,
									1,2,3,3,3,3,4,4,
									1,2,3,3,3,4,4,4,
									1,2,3,3,4,4,4,4,
									1,2,3,4,4,4,4,4,
									1,2,3,4,4,4,4,5,
									1,2,3,4,4,4,5,5,
									1,2,3,4,4,5,5,5,
									1,2,3,4,5,5,5,5,
									1,2,3,4,5,5,5,6,
									1,2,3,4,5,5,6,6,
									1,2,3,4,5,6,6,6,
									1,2,3,4,5,6,6,7,
									1,2,3,4,5,6,7,7,
									1,2,3,4,5,6,7,8};
*/
