/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST94MENS                                                       *
; Funcao: MODULO DE DEFINIÇÃO DAS MENSAGENS DA LINHA ST94				 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/

//					  [linha][colunas-fixa em 9]  
//					             12345678
const char tabela_mens[49][9] ={"        ",  	//0
  								"TEN NOMI",		//1
  								"TIPO TC ",		//2
								"TIPO TP ",		//3
								"SET PNT ",		//4
								"ADDRMODB",		//5
  								"TIMEREGI",		//6
  								"TIPOREG ",		//7
  								"INTEGRA ",		//8
  								"MODORCHT",		//9
  								"BAUDRATE",		//10
  								"TIPOLIGA",		//11
  								" EN  AT ",		//12
  								" EN REA ",		//13
  								"DEMF AT ",		//14
  								"DEMFREA ",		//15
  								"MED  AT ",		//16
  								"MAX  AT ",		//17
  								"MED  AP ",		//18
  								"MAX  AP ",		//19
  								"FRE     ",		//20
 								"PROG SIM",		//21
 								"PROG NAO",		//22
 								"MED.ELET",		//23
 								"HARMTEN ",		//24
 								"HARMCOR ",		//25
 								"PROG    ",		//26
 								"ALARMES ",		//27
 								"DATAHORA",		//28
 								"APAGANDO",		//29
  								"DEM  AT ",		//30
  								"DEM  REA",		//31
  								"HORA PON",		//32
  								"HORAFPON",		//33
  								"FP  IND ",		//34
  								"FP  CAP ",		//35
  								"TENSALTA",		//36
  								"TENSBAIX",		//37
  								"SOBRCORR",		//38
  								"SUB CORR",		//39
  								"HARMTENS",		//40
  								"HARMCORR",		//41
  								"STATUS  ",		//42
  								"MIN  PON",		//43
  								"MIN FPON",		//44
  								"DEM ATIV",		//45
  								"DEM ALTA",		//46
  								"TIMEFUNC",		//47
  								"FUNC ANT"		//48
 								};
   
 									//   123456789012  
 	const char tabela_erros[14][13]	  ={"            ",  	//0  
 										"COR CRIT    ",		//1  
 										"TENSCRIT    ",		//2  
 										"TENSALTA    ",		//3  
 										"TENSBAIX    ",		//4  
 										"COR ALTA    ",		//5  
 										"COR BAIX    ",		//6  
 										"TC  R   INV ",		//7  
 										"TC  S   INV ",		//8  
 										"TC  T   INV ",		//9  
 										"MODOFUNC    ",		//10  
 										"P ATFORN R  ",		//11  
 										"P ATFORN S  ",		//12  
 										"P ATFORN T  "		//13  
 										};  
   
 	#define m_ten_nomi		1  
	#define m_tipo_tc		2  
 	#define m_tipo_tp		3  
 	#define m_set_pnt		4  
 	#define m_addr_mod		5  
 	#define m_time_regi		6  
 	#define m_tiporeg		7  
 	#define m_integra		8  
 	#define m_modo_cht		9  
 	#define m_baudrate		10  
 	#define m_tipo_liga		11  
 	  
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
 	#define m_menu5			27  
 	#define m_menu6			28  
 	#define m_menu7			42
 	#define mapaga			29  
   
   
