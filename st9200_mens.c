/* mensagem.c
	área para definicao de mensagens
*/
		const char tabela_unidades[9][6]={"A",  	//0
										  "kW  ",	//1
										  "kVA ",	//2
										  "kVAr",	//3
										  "Hz  ",	//4
										  "Vac ",	//5
										  "kWh",	//6
										  "kVArh"	//7
										  };

	//					  [linha][colunas-fixa em 17]
	//					              1234567890123456
	const char tabela_mens[96][17] ={"                ",  	//0
								#if (st9200r == true)
			     		             " S T 9 2 0 0 R  ",	//1
								#else
									#if (epcos ==  true)
				     		             " ST9230R/EPCOS  ",	//1
									#else
				     		             " S T 9 2 3 0 R  ",	//1
				     		        #endif
			     		        #endif
			     		             "NR:@@@@.@ V:@.@@",	//2
			     		             " Med. Eletricas ",    //3
			     		             "  Harm. Tensao  ",	//4
			     		             " Harm. Corrente ",	//5
			     		             " Programa Geral ",	//6
			     		             "Programa Alarmes",	//7
			     		             "  Data e Hora   ",	//8
			     		             "     Status     ",	//9
									 "Tensao:     Vac ",	//10
									 "Valor TC:     /5",	//11
									 "Valor TP:       ",	//12
									 "Set-Point:      ",	//13
									 "End. Modbus:    ",	//14
									 "Integracao:     ",	//15
									 "Tempo Reg:      ",	//16
									 "Forma Reg.CH:   ",	//17
									 "Baud Rate:      ",	//18
									 "Tipo Ligacao:   ",	//19
									 "FP Indutivo:    ",	//20
									 "FP Capacit.:    ",	//21
									 "Tensao Alta:   %",	//22
									 "Sub Tensao:    %",	//23
									 "Cor. Alta:     %",	//24
									 "Cor. Baixa:    %",	//25
									 "CH Tensao:     %",	//26
									 "CH Corrente:   %",	//27
									 " Apaga Consumos ",	//28
									 " Apaga  Memoria ",	//29
									 "Confirma?<ENTER>",	//30
									 " A G U A R D E !",	//31
									 "Corrente Critica",	//32
									 " Tensao Critica ",	//33
									 "  Tensao Baixa  ",	//34
									 "  Tensao Alta   ",	//35
									 " Corrente Baixa ",	//36
									 " Corrente Alta  ",	//37
									 " TC R Invertido ",	//38
									 " TC S Invertido ",	//39
									 " TC T Invertido ",	//40
									 " kW Fornecido R ",	//41
									 " kW Fornecido S ",	//42
									 " kW Fornecido T ",	//43
									 "  Demanda-P kW  ",    //44
									 "Demanda-P kVA(r)",	//45
									 " Consumo PONTA  ", 	//46
									 "Memoria: 1 NOK!!",	//47
									 "Prog. Autorizada",	//48
									 "Prog. Nao Autor.",	//49
									 "   /  /     :   ",	//50
									 "@@@@@@@@@ (R)   ",	//51
									 "  (S)     (T)   ",	//52
									 "Ten. (V):       ",	//53
									 "Cor. (A):       ", 	//54
									 "FP:     R: @@@@ ",    //55
									 "S: @@@@ T: @@@@ ",	//56
									 "Pot.kW          ", 	//57
									 "Pot.kVA         ",  	//58
									 "Pot.kVAr        ",	//59
									 " Consumo  Ativo ",	//60
									 "Consumo  Reativo",	//61
									 " Demanda  Ativa ",	//62
									 "Demanda  Reativa",	//63
									 " kVAr Requerido ",	//64
									 "Dem. Ativa: Med.",	//65
									 "Dem. Ativa: Max.",	//66
									 "Dem.Aparente:Med",	//67
									 "Dem.Aparente:Max",	//68
									 "   Frequencia   ",	//69
									 "Flt.kVAr:       ",	//70
									 "Exc.kVAr:       ",	//71
									 " Data:   /  /   ",	//72
									 " Hora:   :  :   ",	//73
									 "          Hz    ",	//74
									 "Total:         %",	//75
									 "Fund.:         %",	//76
									 "   Harm:       %",	//77
									 "       %       %",	//78
									 "Horario de Ponta",	//79
									 "Inicio:     :   ",	//80
									 "Final :     :   ",	//81
									 "Dem. Ativa:     ",	//82
									 "Demanda AT. Alta",	//83
									 " P Ati Tot kW   ",	//84
									 " P Apa Tot kVA  ",	//85
									 " P Rea Tot kVAr ",	//86
									 " Flt kVAr Total ",	//87
									 " Exc kVAr Total ",	//88
									 "Fator Pot. Total",	//89
									 "Tempo Funciona. ",	//90
									 "Atual:@@@@@@@@hs",	//91
									 "Ant.: @@@@@@@@hs",	//92
									 "Max.(A):        ", 	//93
									 "Max.kW          ", 	//94
									 "Consumo Aparente"		//95
	 								 };

	const char tabela_mens_esp[93][17] ={"                ",  	//0
								#if (st9200r == true)
			     		             " S T 9 2 0 0 R  ",	//1
								#else
			     		             " S T 9 2 3 0 R  ",	//1
			     		        #endif
			     		             "NR:@@@@.@ V:@.@@",	//2
			     		             " Med. Eletricas ",    //3
			     		             "  Harm. Tensao  ",	//4
			     		             " Harm. Corrente ",	//5
			     		             " Programa Geral ",	//6
			     		             "Programa Alarmes",	//7
			     		             "  Data e Hora   ",	//8
			     		             "     Status     ",	//9
									 "Tensao:     Vac ",	//10
									 "Valor TC:     /5",	//11
									 "Valor TP:       ",	//12
									 "Set-Point:      ",	//13
									 "End. Modbus:    ",	//14
									 "Integracao:     ",	//15
									 "Tempo Reg:      ",	//16
									 "Forma Reg.CH:   ",	//17
									 "Baud Rate:      ",	//18
									 "Tipo Ligacao:   ",	//19
									 "FP Indutivo:    ",	//20
									 "FP Capacit.:    ",	//21
									 "Tensao Alta:   %",	//22
									 "Sub Tensao:    %",	//23
									 "Cor. Alta:     %",	//24
									 "Cor. Baixa:    %",	//25
									 "CH Tensao:     %",	//26
									 "CH Corrente:   %",	//27
									 " Apaga Consumos ",	//28
									 " Apaga  Memoria ",	//29
									 "Confirma?<ENTER>",	//30
									 " A G U A R D E !",	//31
									 "Corrente Critica",	//32
									 " Tensao Critica ",	//33
									 "  Tensao Baixa  ",	//34
									 "  Tensao Alta   ",	//35
									 " Corrente Baixa ",	//36
									 " Corrente Alta  ",	//37
									 " TC R Invertido ",	//38
									 " TC S Invertido ",	//39
									 " TC T Invertido ",	//40
									 " kW Fornecido R ",	//41
									 " kW Fornecido S ",	//42
									 " kW Fornecido T ",	//43
									 "  Demanda-P kW  ",    //44
									 "Demanda-P kVA(r)",	//45
									 " Consumo PONTA  ", 	//46
									 "Memoria: x NOK!!",	//47
									 "Prog. Autorizada",	//48
									 "Prog. Nao Autor.",	//49
									 "   /  /     :   ",	//50
									 "@@@@@@@@@@ (R)  ",	//51
									 "  (S)      (T)  ",	//52
									 "Ten. (V):       ",	//53
									 "Cor. (A):       ", 	//54
									 "FP:     R: @@@@ ",    //55
									 "S: @@@@ T: @@@@ ",	//56
									 "Pot.(kW)        ", 	//57
									 "Pot.(kVA)       ",  	//58
									 "Pot.(kVAr)      ",	//59
									 " Consumo  Ativo ",	//60
									 "Consumo  Reativo",	//61
									 " Demanda  Ativa ",	//62
									 "Demanda  Reativa",	//63
									 " kVAr Requerido ",	//64
									 " D. Ativa: Med. ",	//65
									 " D. Ativa: Max. ",	//66
									 "D. Aparente: Med",	//67
									 "D. Aparente: Max",	//68
									 "   Frequencia   ",	//69
									 "Flt.kVAr:       ",	//70
									 "Exc.kVAr:       ",	//71
									 " Data:   /  /   ",	//72
									 " Hora:   :  :   ",	//73
									 "          Hz    ",	//74
									 "Total:         %",	//75
									 "Fund.:         %",	//76
									 "   Harm:       %",	//77
									 "       %       %",	//78
									 "Horario de Ponta",	//79
									 "Inicio:     :   ",	//80
									 "Final :     :   ",	//81
									 "Dem. Ativa:     ",	//82
									 "Demanda AT. Alta",	//83
									 "Pot Ativa Total ",	//84
									 "P.Aparente Total",	//85
									 "P.Reativa Total ",	//86
									 "Falta Kvar Total",	//87
									 "Exc. Kvar Total ",	//88
									 "Fator Pot. Total",	//89
									 "Tempo Funciona. ",	//90
									 "Atual:@@@@@@@@hs",	//91
									 "Ant.: @@@@@@@@hs"		//92
	 								 };

						
				
									 
	
	#define m_menu_principal 3
	#define m_prog_liberada 59
	#define m_prog_nao_auto 58
	#define m_menu1	3
	#define m_menu2	4
	#define m_menu3	4
	#define m_menu4	5
	#define m_menu5	6
	#define m_menu6	9
	
	#define mapaga_consumos 26

	
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
	#define nro_caracteres	39
	const char tabela_alfabeto[nro_caracteres+1] ={" 0123456789ABCDEFGHIJKLMNOPQRSTUVXYZW-#"};



