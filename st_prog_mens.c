/* mensagem.c
	ÿárea para definicao de mensagens
*/

/*                         1234567890123456789012345678901 */

	//					  [linha][colunas-fixa em 17]
	//					              1234567890123456
	const char tabela_mens[26][17]={ "                ",  	//0
			     		             "  SULTECH 2009  ",	//1
			     		             "     ST-REP     ",	//2
			     		             "     OnLine     ",    //3
			     		             " Programa Geral ",	//4
			     		             "    Corrente    ",	//5
									 "     Tensao     ",	//6  		             
									 " Fator Potencia ",	//7  		             
									 " Potencia Ativa ",	//8  		             
									 "FP:       T:    ",	//9
									 "P. kW:          ",	//10
									 "P. kVAr:        ",	//11
									 " BaudRate:@@@@@ ",	//12
									 " Endereco:  @@@ ",	//13
									 " Configurar REP ",	//14
									 " Intervalo  @@@ ",	//15
									 " I. Fatura:   @ ",	//16
									 " I. Reativo:  @ ",	//17
									 " Pulsos Cap.: @ ",	//18
									 " Pulsos Ind.: @ ",	//19
									 " Segmento: @@@@ ",	//20
									 " Tipo Tar.: @@@ ",	//21
									 " Tar. Reat: @@@ ",	//22
									 " kW:      @@@@@ ",	//23
									 " kVAr:    @@@@@ ",	//24
									 " Tipo REP:  @@@ "		//25
	 								 };

									//01234567890123456789012345678901234567890
									//			10		  20        30
	#define nro_caracteres	39
	const char tabela_alfabeto[nro_caracteres+1] ={" 0123456789ABCDEFGHIJKLMNOPQRSTUVXYZW-#"};

/*						
	const char tabela_menu4[nro_menus4]={40,
								41,
								42,
								43,
								74,	
								94,	
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
*/

	const char tabela_unidades[6][5]={"A",  	//0
									  "KW  ",	//1
									  "KVA ",	//2
									  "KVAr",	//3
									  "HZ  ",	//4
									  "Vac "	//5
									  };
