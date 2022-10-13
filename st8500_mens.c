
	const char tabela_unidades[6][5]={"A",  	//0
									  "kW  ",	//1
									  "kVA ",	//2
									  "kVAr",	//3
									  "Hz  ",	//4
									  "Vac "	//5
									  };
									  
									  
	const char tabela_mens[178][17]={"                ",  	//0
								#if (com_tc == true)
								//	  0123456789012345
		     		       	     	"S T 8 5 0 0 C/TC",	//1
								#elif (com_rep == true))
								//	  0123456789012345
									"S T 8 5 0 0 C/IU",	//1
								#else
				     		    	#error "Falta definição"
								#endif
			     		             "N@:@@@@.@ V:@.@@",	//2
			     		             " Med. Eletricas ",    //3
			     		             "  E R R O !!!!! ",	//4
			     		             "Falta Sinal REP!",	//5
			     		             "   Ocorrencias  ",	//6
			     		             " Programa Geral ",	//7
			     		             "Programa  Cargas",	//8
									 "Programa Alarmes",	//9
			     		             "Programa Desliga",	//10
									 "   Manutencao   ",	//11
									 "   Instalacao   ",	//12
									 "Pot.Inst:@@@@@kW",	//13
									 "Nro de Cargas:  ",	//14
									 "     Usuario    ",	//15
									 "Max.Carga:@@@@kW",	//16
									 "Set-point:@@@@kW",	//17
									 "Acionamento:   s",	//18
									 "Carga @@:     kW",	//19
									 "T.Carga @@:    s",	//20
									 "Dem.Ativa:   @@%",	//21
									 "Acionado: @@@@kW",	//22
									 "Ten. (V):       ",	//23
									 "Cor. (A):       ", 	//24
									 "   Frequencia   ",    //25
									 "Pot.kW          ", 	//26
									 "Pot.kVA         ",  	//27
									 "Pot.kVAr        ",	//28
									 "Ftr Crg:       %",    //29
									 "Ftr Dmd:       %",	//30
									 "Flt.kVAr:       ",	//31
									 "Exc.kVAr:       ",	//32
									 "          Hz    ",	//33
									 "Dem.Cont.Mes: @@",	//34
									 "Ponta:   @@@@@kW",	//35
									 "F.Ponta: @@@@@kW",	//36
									 "  Apagando!!!   ",	//37
									 "Tipo Ligacao:   ",	//38
									 "End. Modbus:    ",	//39
									 "Baud Rate:      ",	//40
									 "FP Indutivo:    ",	//41
									 "FP Capacit.:    ",	//42
									 "Tensao Alta:   %",	//43
									 "Sub Tensao:    %",	//44
									 "  Periodo SECO  ",	//45
									 "I.@@/@@ F.@@/@@ ",	//46
									 "D. Med. kW:     ",	//47
									 "D. Prj. kW:     ",	//48
									 "Prog. Nao Autor.",	//49
									 " Prog. Liberada ",	//50
									 "@@@@@ Sem Limite",	//51
									 " Liga Carga:    ",	//52
									 " Desl Carga:    ",	//53
									 "D.Md. kVAr:     ",	//54
									 "D.Pj. kVAr:     ",	//55
									 "FP:             ",	//56
									 "Horario de Ponta",	//57
									 "Ajuste Relogio!!",	//58
									 "I.@@:@@ F.@@:@@ ",	//59
									 "   /  /     :   ",	//60
									 "       %       %",	//61
									 "Tempo  Carga:   ",	//62
									 "Aciona Carga:   ",	//63
									 "         Horas  ",	//64
									 "         Vezes  ",	//65
									 " Fim Ocorrencias",	//66	Cod Ocorrencia = 0
									 "Registro  Normal",	//67	Cod Ocorrencia = 1
									 "Tens Alta Fase R",	//68	Cod Ocorrencia = 2
									 "Tens Alta Fase S",	//69	Cod Ocorrencia = 3
									 "Tens Alta Fase T",	//70	Cod Ocorrencia = 4
									 "Ten Baixa Fase R",	//71	Cod Ocorrencia = 5
									 "Ten Baixa Fase S",	//72	Cod Ocorrencia = 6
									 "Ten Baixa Fase T",	//73	Cod Ocorrencia = 7
									 "MSG-OCOR-74-FREE",	//74	Cod Ocorrencia = 8
									 "MSG-OCOR-75-FREE",	//75	Cod Ocorrencia = 9
									 "MSG-OCOR-76-FREE",	//76	Cod Ocorrencia = 10
									 "Corr Alta Fase R",	//77	Cod Ocorrencia = 11
									 "Corr Alta Fase S",	//78	Cod Ocorrencia = 12
									 "Corr Alta Fase T",	//79	Cod Ocorrencia = 13
									 "  FP  Indutivo  ",	//80	Cod Ocorrencia = 14
									 " FP  Capacitivo ",	//81	Cod Ocorrencia = 15
									 "  Demanda ALTA  ",	//82	Cod Ocorrencia = 55
									 " TC Invertido R ",	//83	Cod Ocorrencia = 17
									 " TC Invertido S ",	//84	Cod Ocorrencia = 18
									 " TC Invertido T ",	//85	Cod Ocorrencia = 19
									 " Seq. Invertida ",	//86	Cod Ocorrencia = 20
									 "MSG-OCOR-87-FREE",	//87	Cod Ocorrencia = 21
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
									 "MSG-OCOR-99-FREE",	//99	Cod Ocorrencia = 33
									 "MSG-OCOR-100FREE", 	//100	Cod Ocorrencia = 34
									 "MSG-OCOR-101FREE", 	//101	Cod Ocorrencia = 35
									 "MSG-OCOR-102FREE", 	//102	Cod Ocorrencia = 36
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
									 " Data e Horario ",	//123
									 " Data:   /  /   ",	//124
									 " Hora:     :    ",	//125
									 " Tensao Critica ",	//126
									 "Corrente Critica",	//127
									 "     Tabela     ",	//128
									 " Memoria: 1 NOK!",	//129
									 "Desl. por Tensao",	//130
									 "   Limpa Ocorr. ",	//131
									 "   * Cancelar   ",	//132
									 "  Zerar Carga   ",	//133
									 "Corrente Critica",	//134
									 "     Status     ",	//135
									 " D-??:?? L-??:??",	//136
									 "Desaciona:     s",	//137
									 "@@@@@@@@@@ (R)  ",	//138
									 "  (S)      (T)  ",	//139
									 "kWh:            ",	//140
									 "kVArh:          ",	//141
									 "  k. kWh:       ",	//142
									 "  k.kVArh:      ",	//143
									 "Tar:   Tempo:   ",	//144
									 "P:      /       ",	//145
									 "FP:        @@@@ ",    //146
									 "Ult.P kW:       ",	//147
									 "Ult.P kVAr:     ",	//148
									 " ERRO CRC - IU! ",	//149
									 "Carga em repouso", 	//150		
									 "Ult.kW:         ",	//151
									 "Ult.kVAr:       ",	//152
									 "Periodo Ponta   ",	//153
									 "Periodo F.Ponta ",	//154
									 "MSG_155-LIvre   ",	//155
									 "  Protocolo IU  ",	//156
									 "    REP:        ",	//157
									 "Modo Carga: @@-@",	//158
									 "Tipo de Controle",	//159
									 " Fila Sequencial", 	//160
									 "  Fila Circular ",	//161
									 " Periodo Ponta  ",    //162		Cod Ocorrencia = 58
									 "MSG_163-LIvre   ",    //163		Cod Ocorrencia = 59
									 "Periodo F. Ponta",    //164		Cod Ocorrencia = 60
									 "MSG_165-LIvre   ",	//165		Cod Ocorrencia = 61
									 "Falta Pulso REP ",    //166		Cod Ocorrencia = 62
									 "Volta Pulso REP ",    //167		Cod Ocorrencia = 63
									 "Erro Const.kWh  ",	//168
									 "Erro Const.kVArh",	//169
									 "Valor TC:     /5",	//170
									 "Valor TP:       ",	//171
									 "Modo Acionamento",	//172
									 "Modo Saidas INV ",	//173								 
									 "Modo Saidas NORM",	//174
									 "TESTE MEM       ",	//175
									 "END:            ",	//176
									 "FIM:            "		//177
	 								 };

	 								 /// cuidado esta tabela esta na lcd_16x4

	const char tabela_mens_esp[3][17]={"                ",  	//0
				     		             " S U L T E C H  ",	//1
				     		             "N@:@@@@.@ V:@.@@"	//2
				     		             };
/*
	const char tabela_mens_esp[170][17]={"                ",  	//0
				     		             " S U L T E C H  ",	//1
				     		             "N@:@@@@.@ V:@.@@",	//2
				     		             "Med. Electricas ",    //3
				     		             "   Armonicos    ",	//4
				     		             "    Comandos    ",	//5
				     		             "   Ocorrencias  ",	//6
				     		             "Programa General",	//7
				     		             " Programa Cargas",	//8
										 "Programa Alarmes",	//9
				     		             "Programa Desliga",	//10
										 "  Manutencion   ",	//11
										 "  Harm. Tensao  ",	//12
										 " Harm. Corrente ",	//13
										 "N. de Cargas:   ",	//14
										 " Seq: Usuario   ",	//15
										 "Max.:       kVAr",	//16
										 "Min.:       kVAr",	//17
										 "Acionamento:   s",	//18
										 "B  :        kVAr",	//19
										 "Tempo B  :     s",	//20
										 "Cor Minima:    %",	//21
										 "Manual  FP:     ",	//22
										 "Tensao:         ",	//23
										 "Corrente:       ", 	//24
										 "   Frequencia   ",    //25
										 "P.Ativa         ", 	//26
										 "P.Aparen        ",  	//27
										 "P.Reativa       ",	//28
										 "FP:     R: @@@@ ",    //29
										 "S: @@@@ T: @@@@ ",	//30
										 "Falta:          ",	//31
										 "Excesso:        ",	//32
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
										 " Liga Carga:    ",	//52
										 " Desl Carga:    ",	//53
										 "Total:         %",	//54
										 "Fund.:         %",	//55
										 "   Harm:       %",	//56
										 "                ",	//57
										 "Ajuste Relogio!!",	//58
										 "                ",	//59
										 "   /  /     :   ",	//60
										 "       %       %",	//61
										 "Tempo  Carga:   ",	//62
										 "Aciona Carga:   ",	//63
										 "         Horas  ",	//64
										 "         Vezes  ",	//65
										 " Fim Ocorrencias",	//66	Cod Ocorrencia = 0
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
										 " TC Invertido R ",	//83	Cod Ocorrencia = 17
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
										 " Demanda Alta   ", 	//121	Cod Ocorrencia = 55
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
										 "  Zerar Carga   ",	//133
										 "Corrente Critica",	//134
										 "    Status:     ",	//135
										 "Em Carga Minimo ",	//136
										 "Desaciona:     s",	//137
										 "@@@@@@@@@@ (R)  ",	//138
										 "  (S)      (T)  ",	//139
										 "  Em Modo REP   ",	//140
										 "  Tipo REP      ",	//141
										 "  K. KWh:       ",	//142
										 "  K. KVAh:      ",	//143
										 "FP:        @@@@ ",   //144
										 "P:      /       ",	//145
										 "FP:        @@@@ ",    //146
										 "Ult.P KW:  @@@@@",	//147
										 "Ult.P KVAr:@@@@@",	//148
										 "ERRO CRC - IU!!!",	//149
										 "Carga em repouso", 	//150		
										 "Ult.KW:     @@@@",	//151
										 "Ult.KVAr:   @@@@",	//152
										 "Periodo Ponta   ",	//153
										 "Periodo F.Ponta ",	//154
										 "MSG_155-LIvre   ",	//155
										 "MSG_156-LIvre   ",	//156
										 "MSG_157-LIvre   ",	//157
										 "Modo Carga: @@-@",	//158
										 "Tipo de Controle",	//159
										 " Fila Sequencial", 	//160
										 "  Fila Circular ",	//161
										 " Periodo Ponta  ",    //162		Cod Ocorrencia = 58
										 "MSG_163-LIvre   ",    //163		Cod Ocorrencia = 59
										 "Periodo F. Ponta",    //164		Cod Ocorrencia = 60
										 "MSG_165-LIvre   ",	//165		Cod Ocorrencia = 61
										 "Falta Pulso REP ",    //166		Cod Ocorrencia = 62
										 "Volta Pulso REP ",    //167		Cod Ocorrencia = 63
										 "Erro Const. KW  ",	//168
										 "Erro Const. KVAr"		//169
		 								 };
*/

//	2,3,4,5,6,7,14,15,25,29,41,42,43,44,49,55,58,59,60,61,62,63
	#define nro_tab_ocor	64
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
										82,		//55
										255,	//56
										255,	//57
										162,	//58
										163,	//59
										164,	//60
										165,	//61
										166,	//62
										167		//63
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
									//01234567890123456789012345678901234567890
									//			10		  20        30
//	#define nro_caracteres	39
//	const char tabela_alfabeto[nro_caracteres+1] ={" 0123456789ABCDEFGHIJKLMNOPQRSTUVXYZW-#"};






	const char tabela_mens_tipo2[17][4]={" ",		//00
										"01",		//01
										"02",		//02
										"03",		//03
										"04",		//04
										"05",		//05
										"06",		//06
										"07",		//07
										"08",		//08
										"09",		//09
										"10",		//10
										"11",		//11
										"12",		//12
										"13",		//13
										"14",		//14
										"15",		//15
										"16"		//16
										};

	const char tabela_mens_tipo3[16][5]={"T01-",	//00
										"T02-",		//01
										"T03-",		//02
										"T04-",		//03
										"T05-",		//04
										"T06-",		//05
										"T07-",		//06
										"T08-",		//07
										"T09-",		//08
										"T10-",		//09
										"T11-",		//10
										"T12-",		//11
										"T13-",		//12
										"T14-",		//13
										"T15-",		//14
										"T16-"		//15
										};

	const char tabela_menu4_old[nro_menus4+1]={	0,
											1,
											2,
											3,
											11,
											4,
											5,
											10
											};

	const char tabela_menu_bancos[nro_menu_bancos+1]={	0,
														18,
														6,
														7,
														8,
														9,
														19,
														30,
														17
														};

	

										//   1234567890123456





										
