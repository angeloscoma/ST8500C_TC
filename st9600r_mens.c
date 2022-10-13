/* mensagem.c
	ÿárea para definicao de mensagens
*/

/*                         1234567890123456789012345678901 */

	//					  [linha][colunas-fixa em 17]
	//					              1234567890123456
	const char tabela_mens[132][17] ={"                ",  	//0
									#if (teste_coletas	== true)
			     		             "NAO LIBERAR!!!  ",	//1
			     		             "VERSÃO TESTE!!! ",	//2
									#else
			     		             " S U L T E C H  ",	//1
				     		             #if (viercon == true)
				     		             	"ST9600R-Viercon ",	//2
				     		             #elif (sazi == true)
				     		             	"  ST9600R-Sazi  ",	//2
				     		             #else
				     		             	"    ST9600R  ",	//2
				     		             #endif
									#endif
			     		             " Med. Eletricas ",    //3
			     		             "   Harmonicos   ",	//4
			     		             " Programa Geral ",	//5
			     		             "   Registros    ",	//6
			     		             "    Comandos    ",	//7
			     		             " Cor. N:        ",	//8
			     		             "msg-9-livre     ",	//9
									 "Programacao OK! ",	//10
									 " Ajuste Relogio ",	//11
									 "  V(ac)  A(ac)  ",	//12  		             
									 "R=              ",	//13
									 "S=              ",	//14
									 "T=              ",	//15
									 "   kW      kVA  ",	//16  		             
									 " ST9600R(Ativo) ",	//17
									 "ST9600R(Inativo)",	//18
									 "   MW      MVA  ",	//19
									 "RS=             ",	//20
									 "ST=             ",	//21
									 "RT=             ",	//22
									 " kV(alta) A(ac) ", 	//23
									 "   FP     kVAr  ",    //24
									 "Consumo F.PONTA ", 	//25
									 "kWh:            ",  	//26
									 "kVArh:          ",	//27
									 " Demanda-FP kW  ",    //28
									 "Demanda-FP  kVAr",	//29
									 "Atual:          ",	//30
									 "Media:          ",	//31
									 "Maxima:         ",	//32
									 "kVAr:      Atual",	//33
									 " kVAr em Falta  ",	//34
									 " kVAr em Excesso",	//35
									 "Data:   /  /    ",	//36
									 "Hora:   :  :    ",	//37
									 "HT      01   03 ",	//38
									 "HC      01   03 ",	//39
									 " Tensao:    @@@ ",	//40
									 " Valor PT: @@@@ ",	//41
									 " Valor TP:  @@@ ",	//42
									 " Set-Point:0.@@ ",	//43
									 " Tempo Reg:@@@@ ",	//44
									 " Forma Reg:CH:@ ",	//45
									 " Registrar: @@@ ",	//46
									 " Integracao: @@ ",	//47
									 " BaudRate:@@@@@ ",	//48
									 " Endereco:  @@@ ",	//49
									 " Al.Fp Ind:0.@@ ",	//50
									 " Al.Fp Cap:0.@@ ",	//51
									 " Al.Ten.A:  @@% ",	//52
									 " Al.Ten.B:  @@% ",	//53
									 " Al.Cor.A: @@@% ",	//54
									 " Al.Ch T:   @@% ",	//55
									 " Al.Ch C:   @@% ",	//56
									 " R/Horario:     ",	//57
									 " Progr. Horario ",	//58
									 "       dd/hh:mm ",	//59
									 " Liga:   ,  :   ",	//60
									 " Desl:   ,  :   ",	//61
									 " Apaga Consumos ",	//62
									 " Apaga Memoria  ",	//63
									 " Comando OK !!! ",	//64
									 "COMFIRMA?<ENTER>",	//65
									 " A G U A R D E !",	//66
									 " Fila Circ.:    ",	//67
									 "   Autonomia    ",	//68
									 "Inicializando!!!",	//69
									 "Lendo Pointers  ",	//70
									 "Busca Memorias  ",	//71
									 "Memoria:      kB",	//72
									 "Memoria cheia!!!",	//73
									 " Tipo Ligacao:  ",	//74
									 "  Freq.:  . Hz  ",	//75
									 "ST9600R(Tempo..)",	//76
									 "Corrente Critica",	//77
									 " Tensao Critica ",	//78
									 " Medicao: Delta ",	//79
									 " Medicao:Estrela",	//80
									 "  Tensao Baixa  ",	//81
									 "  Tensao Alta   ",	//82
									 " Corrente Baixa ",	//83
									 " Corrente Alta  ",	//84
									 " Ponteira R Inv.",	//85
									 " Ponteira S Inv.",	//86
									 " Ponteira T Inv.",	//87
									 " kW Fornecido R ",	//88
									 " kW Fornecido S ",	//89
									 " kW Fornecido T ",	//90
									 "Consumo Reg.Ant.", 	//91
									 " Idioma: Port.  ", 	//92
									 " Idioma: Esp.   ", 	//93
									 " Idioma:        ", 	//94
									 " Modo Funcio.:  ", 	//95
									 " Nao Disponivel ",	//96
									 " Erro Frequencia",	//97
									 "  Demanda-P KW  ",    //98
									 "Demanda-P KVA(r)",	//99
									 " Consumo PONTA  ", 	//100
									 " Inic. PONTA:   ", 	//101
									 " Final PONTA:   ", 	//102
									 "Digite Local da ",	//103
									 "Coleta,Use:éâä* ",	//104
									 " # Conclui      ",	//105
									 "Coletando dados!",	//106
									 "Memoria: x NOK!!",	//107
									 " Tipo  Ponteira ",	//108
									 "Selecione Modelo",	//109
									 " Linha:  Valor: ",	//110
									#if (versao_pci_st96 == 4)				//Incluído para diferenciar os flexíveis LEM e ENGRO
									 " ST9003G    50A ",	//111			Alterei para não aparecer como opção (9009)
									 " ST9003G   200A ",	//112			Alterei para não aparecer como opção (9009)
									 " ST9009G  1000A ",	//113
									 " ST9010G    30A ",	//114
									 " ST9010G   300A ",	//115
									 " ST9010G  3000A ",	//116
									#else
									 " ST9002G    50A ",	//111
									 " ST9002G   200A ",	//112
									 " ST9002G  1000A ",	//113
									 " ST9009G    30A ",	//114
									 " ST9009G   300A ",	//115
									 " ST9009G  3000A ",	//116
									#endif
									 " ST9001G    20A ",	//117
									 " ST9001G   200A ",	//118
									 " ST9005G  1500A ",	//119
									 " ST9005G  3000A ",	//120
									 " ST900?G    60A ",	//121
									 " ST900?G   300A ",	//122
									 " ST900?G   600A ",	//123
									 " ST900?G  3000A ",	//124
									 " ST900?G  6000A ",	//125
									 " ST9007G   400A ",	//126
									 " ST9007G  1000A ",	//127
									 " ST9008G   200A ",	//128
									 " ST900?G   ???A ",	//129
									 " ST900?G  ????A ",	//130
			     		             "NR:@@@@.@ V:@.@@"		//131
	 								 };

	const char tabela_mens_esp[132][17] ={"                ",  	//0
			     		             " S U L T E C H  ",	//1
			     		             "    ST9600R     ",	//2
			     		             " Med. Electricas",    //3
			     		             "    Armonicos   ",	//4
			     		             "Programa General",	//5
			     		             "   Registros    ",	//6
			     		             "    Comandos    ",	//7
			     		             "msg-8-libre     ",	//8
			     		             "msg-9-libre     ",	//9
									 "Programacion OK!",	//10
									 "  Ajuste Reloj  ",	//11
									 " V(ac)   Amp(ac)",	//12  		             
									 "R=              ",	//13
									 "S=              ",	//14
									 "T=              ",	//15
									 "   KW      KVA  ",	//16  		             
									 " ST9600R(Activo)",	//17
									 "ST9600R-Inactivo",	//18
									 "msg-19-libre    ",	//19
									 "RS=             ",	//20
									 "ST=             ",	//21
									 "RT=             ",	//22
									 " kV(alta) A(ac) ", 	//23
									 "   FP     KVAr  ",    //24
									 "Consumo F.PONTA ", 	//25
									 "KWh:            ",  	//26
									 "KVArh:          ",	//27
									 " Demanda-F KW   ",    //28
									 "Demanda-F KVA(r)",	//29
									 "Actual:         ",	//30
									 "Media:          ",	//31
									 "Maxima:         ",	//32
									 "KVAr:     Actual",	//33
									 " KVAr en Falta  ",	//34
									 " KVAr en Exceso ",	//35
									 "Fecha:  /  /    ",	//36
									 "Hora:   :  :    ",	//37
									 "HT      01   03 ",	//38
									 "HC      01   03 ",	//39
									 " Tension:   @@@ ",	//40
									 " Valor PT: @@@@ ",	//41
									 " Valor TP:  @@@ ",	//42
									 " Set-Point:0.@@ ",	//43
									 "Tiempo Reg:@@@@ ",	//44
									 "  Modo Reg:CH:@ ",	//45
									 " Registrar: @@@ ",	//46
									 " Integracion:@@ ",	//47
									 " BaudRate:@@@@@ ",	//48
									 " Direccion: @@@ ",	//49
									 " Al.Fp Ind:0.@@ ",	//50
									 " Al.Fp Cap:0.@@ ",	//51
									 " Al.Ten.A:  @@% ",	//52
									 " Al.Ten.B:  @@% ",	//53
									 " Al.Corr.A:@@@% ",	//54
									 " Al.Ch T:   @@% ",	//55
									 " Al.Ch C:   @@% ",	//56
									 " R/Horario:     ",	//57
									 " Progr. Horario ",	//58
									 "       dd/hh:mm ",	//59
									 "Conect:  ,  :   ",	//60
									 " Desc:   ,  :   ",	//61
									 " Borra Consumos ",	//62
									 " Borra Memoria  ",	//63
									 " Comando OK !!! ",	//64
									 "CONFIRMA?<ENTER>",	//65
									 " A G U A R D E !",	//66
									 " Fila Circ.:    ",	//67
									 "   Autonomia    ",	//68
									 "Inicializando!!!",	//69
									 "Leyendo Pointers",	//70
									 "Busca Memorias  ",	//71
									 "Memoria:      kB",	//72
									 "Memoria llena!!!",	//73
									 "Tipo Conexion:  ",	//74
									 "  Freq.:  . Hz  ",	//75
									 "ST9600R(Tiempo.)",	//76
									 " Corr. Critica  ",	//77
									 " Tension Critica",	//78
									 " Medicion: Delta",	//79
									 " Medic.:Estrella",	//80
									 "  Tension Baja  ",	//81
									 "  Tension Alta  ",	//82
									 " Corriente Baja ",	//83
									 " Corriente Alta ",	//84
									 "  Puntera R Inv.",	//85
									 "  Puntera S Inv.",	//86
									 "  Puntera T Inv.",	//87
									 " KW Provisto R  ",	//88
									 " KW Provisto S  ",	//89
									 " KW Provisto T  ",	//90
									 "Consumo Reg.Ant.", 	//91
									 " Idioma: Port.  ", 	//92
									 " Idioma: Esp.   ", 	//93
									 " Idioma:        ", 	//94
									 " Modo Funcio.:  ", 	//95
									 " Nao Disponivel ",	//96
									 " Erro Frequencia",	//97
									 "  Demanda-P KW  ",    //98
									 "Demanda-P KVA(r)",	//99
									 " Consumo PUNTA  ", 	//100
									 " Inic. PUNTA:   ", 	//101
									 " Final PUNTA:   ", 	//102
									 "Digite Local da ",	//103
									 "Coleta,Use:     ",	//104
									 " # Encerra      ",	//105
									 "Coletando dados!",	//106
									 "Memoria: x NOK!!",	//107
									 " Tipo  Ponteira ",	//108
									 "Selecione Modelo",	//109
									 " Linha:  Valor: ",	//110
									 " ST9002G    50A ",	//111
									 " ST9002G   200A ",	//112
									 " ST9002G  1000A ",	//113
									 " ST9009G    30A ",	//114
									 " ST9009G   300A ",	//115
									 " ST9009G  3000A ",	//116
									 " ST9005G   150A ",	//117
									 " ST9005G   300A ",	//118
									 " ST9005G  1500A ",	//119
									 " ST9005G  3000A ",	//120
									 " ST900?G    60A ",	//121
									 " ST900?G   300A ",	//122
									 " ST900?G   600A ",	//123
									 " ST900?G  3000A ",	//124
									 " ST900?G  6000A ",	//125
									 " ST9007G   400A ",	//126
									 " ST9007G  1000A ",	//127
									 " ST9008G   200A ",	//128
									 " ST900?G   ???A ",	//129
									 " ST900?G  ????A ",	//130
			     		             "NR:@@@@.@ V:@.@@"		//131
									 };
						
	const char tabela_menu4[nro_menus4]={40,
								41,
								42,
								43,
								74,	
								94,	
	#if (funcao_505 == true)
								95,	
								47,
								50,
								51,
								52,
								53,
								54,
								55,
								56,
								101,
								102
	#else
								95,
								47,
								50,
								51,
								52,
								53,
								54,
								55,
								56,
								101,
								102
	#endif
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



	const char tabela_unidades[6][5]={"A",  	//0
									  "KW  ",	//1
									  "KVA ",	//2
									  "KVAr",	//3
									  "HZ  ",	//4
									  "Vac "	//5
									  };
