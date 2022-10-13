/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_MAIN                                                        *
; Funcao: MODULO PRINCIPAL DE CONTROLE									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */
  


// tabela de caracteres   

// definicao do acentimento dos leds */
/*       11111111
		 ||||||||----- LED TENSAO
		 |||||||------ LED CORRENTE
		 ||||||------- LED FP
		 |||||-------- LED KW
		 ||||--------- LED KVA
		 |||---------- LED KVAR
		 ||----------- LED H
		 |------------ LED DEM

*/		                 
/*
  DISPOSICAO DO LEDS NP PAINEL
  
	LED K/M 
		ONDE:
  			 APAGADO MEDIÇOES EM K(10^3) / Kilo 
  			 ACESO MEDICOES EM M(10^6) / Mega
  	LED TENSAO
  		ONDE:
  			ACESO 
  				a)APENAS ESTE LED, INDICA MEDICAO DE TENSÃO
  				b)EM CONJUNTO COM O LED DE CORRENTE EXIBE POTENCIA APARENTE "VA".
  					c)EM CONJUNTO COM O LED DE R EXIBE POTENCIA REATIVA "VAR".
  						d)EM CONJUNTO COM O LED DE D EXIBE DEMANDACIA REATIVA "DemVAR".
  				
  	LED CORRENTE
  		ONDE:
  			ACESO 
  				a)APENAS ESTE LED, INDICA MEDICAO DE CORRENTE
  				b)EM CONJUNTO COM O LED DE TENSAO EXIBE POTENCIA APARENTE "VA".
  					c)EM CONJUNTO COM O LED DE R EXIBE POTENCIA REATIVA "VAR".
  						d)EM CONJUNTO COM O LED DE D EXIBE DEMANDACIA REATIVA "DemVAR".

	LED R
		ONDE:
			ACESO - INDICA MEDICAO DE REATIVOS
			
	LED W
		ONDE:
			ACESO - INDICA MEDICAO DE WATTS ( POTENCIA/DEMANDA ATIVA)
			
	LED H
		ONDE:
			ACESO - SOZINHO INDICA DATA/HORA
				  - EM CONJUNTO COM OUTRAS, MEDICÓES HORÁRIAS EX.: KWH ( KILOWATTHORA)
				  
	LED D
		ONDE
			ACESO - INDICA MEDICAO DE DEMANDA				  	

	LED FP
		ONDE:
			ACESO - INDICA MEDICAO DE FATOR DE POTENCIA

*/

#if (st94 == true)
	#define LED_HZ			0x00
	#define LED_APAGADO		0x00
	#define LED_K			0x00
	#define LED_M			0x01
	#define LED_TENSAO		0x02
	#define LED_CORRENTE	0x04
	#define LED_R			0x08
	#define LED_W			0x10
	#define LED_H			0x20
	#define LED_D			0x40
	#define LED_FP			0x80

	#define LED_KW			LED_K | LED_W
	#define LED_KVA			LED_K | LED_TENSAO | LED_CORRENTE
	#define LED_KVAR		LED_K | LED_TENSAO | LED_CORRENTE | LED_R
	#define LED_DEM			LED_D | LED_W
	#define LED_KWH			LED_K | LED_W | LED_H
	#define LED_KVARH		LED_K | LED_TENSAO | LED_CORRENTE | LED_R | LED_H
	#define LED_DEMKW		LED_D | LED_K | LED_W
	#define LED_DEMKVA		LED_D | LED_K | LED_TENSAO | LED_CORRENTE
	#define LED_DEMKVAR		LED_D | LED_K | LED_TENSAO | LED_CORRENTE | LED_R


	#define LED_MW			LED_M | LED_W
	#define LED_MVA			LED_M | LED_TENSAO | LED_CORRENTE
	#define LED_MVAR		LED_M | LED_TENSAO | LED_CORRENTE | LED_R
	#define LED_MWH			LED_M | LED_W | LED_H
	#define LED_MVARH		LED_M | LED_TENSAO | LED_CORRENTE | LED_R | LED_H
	#define LED_DEMMW		LED_D | LED_M | LED_W
	#define LED_DEMMVA		LED_D | LED_M | LED_TENSAO | LED_CORRENTE
	#define LED_DEMMVAR		LED_D | LED_M | LED_TENSAO | LED_CORRENTE | LED_R

#endif
/*
; Tabela para display 7 seg.
;			      a
;				#######
;				#     #
;             f #     # b
;				#  g  #
;				#######
;				#     #
;     		  e #     # c
;				#     #
;				#######  #
;	  			   d     p
;
;
;	DCB			pgfedcbaB
*/

#define M0				'0'-'0'
#define M1				'1'-'0'
#define M2				'2'-'0'
#define M3				'3'-'0'
#define M4				'4'-'0'
#define M5				'5'-'0'
#define M6				'6'-'0'
#define M7				'7'-'0'
#define M8				'8'-'0'
#define M9				'9'-'0'
#define MESPACO			'@'-'0'
#define MA				'A'-'0'
#define MB				'B'-'0'
#define MC				'C'-'0'
#define MD				'D'-'0'
#define ME				'E'-'0'
#define MF				'F'-'0'
#define MG				'G'-'0'
#define MH				'H'-'0'
#define MI				'I'-'0'
#define MJ				'J'-'0'
#define MK				'K'-'0'
#define ML				'L'-'0'
#define MM				'M'-'0'
#define MN				'N'-'0'
#define MO				'O'-'0'
#define MP				'P'-'0'
#define MQ				'Q'-'0'
#define MR				'R'-'0'
#define MS				'S'-'0'
#define MT				'T'-'0'
#define MU				'U'-'0'
#define MV				'V'-'0'
#define MW				'W'-'0'
#define MX				'X'-'0'
#define MY				'Y'-'0'
#define MZ				'Z'-'0'
#define mhifen			0b01000000
#define mbarra_esquerda	0x10
#define mbarra_direita	0x04
#define mponto			0b10000000
					
/*; Tabela para display 7 seg.
;			      a
;				#######
;				#     #
;             f #     # b
;				#  g  #
;				#######
;				#     #
;     		  e #     # c
;				#     #
;				#######  #
;	  			   d     p
;
;
;	DCB			pgfedcbaB
*/

const char tabela_caracteres[44]={
										63,		//	00111111B	; 30H =>  '0' 	0
										06,		//	00000110B	; 31H =>  '1' 	1
										91,		//	01011011B	; 32H =>  '2' 	2	
										79,		//	01001111B	; 33H =>  '3' 	3
										102,	//	01100110B	; 34H =>  '4' 	4
										109,	//	01101101B	; 35H =>  '5' 	5
										125,	//	01111101B	; 36H =>  '6' 	6
										07,		//	00000111B	; 37H =>  '7' 	7
										127,	//	01111111B	; 38H =>  '8' 	8
										111,	//	01101111B	; 39H =>  '9' 	9
										130,	//	10000010B	; 3AH =>  ':' 	10
										00,		//	00000000B	; 3BH =>  ';' 	11
										00,		//	00000000B	; 3CH =>  '<' 	12
										64,		//	01000000B	; 3DH =>  '=' 	13
										00,		//	00000000B	; 3EH =>  '>' 	14
										00,		//	00000000B	; 3FH =>  '?' 	15
										00,		//	00000000B	; 40H =>  '@' 	16
										119,	//	01110111B	; 41H =>  'A' 	17
										124,	//	01111100B	; 42H =>  'B' 	18
										88,		//	01011000B	; 43H =>  'C' 	19
										94,		//	01011110B	; 44H =>  'D' 	20
										121,	//	01111001B	; 45H =>  'E' 	21
										113,	//	01110001B	; 46H =>  'F' 	22
										111,	//	01101111B	; 47H =>  'G' 	23
										118,	//	01110110B	; 48H =>  'H' 	24
										04,		//	00000100B	; 49H =>  'I' 	25
										30,		//	00011110B	; 4AH =>  'J' 	26
										00,		//	00000000B	; 4BH =>  'K' 	27
										56,		//	00111000B	; 4CH =>  'L' 	28
										55,		//	00110111B	; 4DH =>  'M' 	29
										84,		//	01010100B	; 4EH =>  'N' 	30
										92,		//	01011100B	; 4FH =>  'O' 	31
										115,	//	01110011B	; 50H =>  'P' 	32
										103,	//	01100111B	; 51H =>  'Q' 	33
										80,		//	01010000B	; 52H =>  'R' 	34
										109,	//	01101101B	; 53H =>  'S' 	35
										120,	//	01111000B	; 54H =>  'T' 	36
										28,		//	00011100B	; 55H =>  'U' 	37
										62,		//	00111110B	; 56H =>  'V' 	38
										00,		//	00000000B	; 57H =>  'W' 	39
										118,	//	01110110B	; 58H =>  'X' 	40
										110,	//	01101110B	; 59H =>  'Y' 	41
										91};	//	01011011B	; 5AH =>  'Z' 	42
											






void display(char linha,word variavel,char decimais,char quantizacao)	
{   
	char posicao;
	char x, y, z;
	word i;

	if (rolando == true)
		{
		if (ja_rolou == false)
			{
			return;
			}
		}
	
	if (linha==1)
		{
		posicao=0;
		}
	else if (linha==2)
		{
		posicao=4;
		}
	else if (linha==3)
		{
		posicao=8;
		}
	z = pob(quantizacao);
	i = variavel / z;
	binasc2(i);							/* saida em buf_tmp[0 a 4]*/
	if (decimais==1)
		{
		y = 2;
		}
	else
		{
		y = 1;
		}
	if (buf_tmp[y] == '0')
		{
		buf_tmp[y] = ';';
		if (buf_tmp[y+1] == '0')
			{
			buf_tmp[y+1] = ';';
			}
		}
	for (x = y; x < 5; x++)
		{
	    buf_display[posicao++] = tabela_caracteres[buf_tmp[x]-'0'];
		}
	if (decimais==1)
		{
	    i=(word)(variavel-(word)((variavel / z)*z));
	    i=(word)(i*100 / z);
		binasc2(i);		/* saida em buf_tmp[0 a 4]*/
	    buf_display[posicao] = tabela_caracteres[buf_tmp[3]-'0'];
	    
	    posicao--;
	    x = buf_display[posicao];
	    x = x | 0x80;
	    buf_display[posicao] = x;
    	}
    	
}




void put_disp(char carac)
{
//	if (carac != ' ')
//		{
		buf_tmp[ptr_buf++] = carac;
		if (ptr_buf > 5)
			{
			ptr_buf--;
			}
//		}
}

void print_display(char linha, int32 variavel,char quantizacao, char tipo )
{
	char posicao;
	char x,y;
	if (rolando == true)
		{
		if (ja_rolou == false)
			{
			return;
			}
		}

	buf_tmp[0] = '0';
	buf_tmp[1] = '0';
	buf_tmp[2] = '0';
	buf_tmp[3] = '0';
	buf_tmp[4] = '0';
		
	valorf = (float)(variavel);
	ptr_buf = 0;
	if (tipo == 0)
		{
		#if (com_rep == true)
			if (modo_rep == 1)
				{
				mul_tc = 1;
				}
		#endif
		valorf = (float)(mul_tc * valorf);
		valorf = (float)(valorf/pob(quantizacao));
		if (valorf > 1000)
			{
			sprintf(buf_tmp,"%4.0f",(float)(valorf));
			}
		else if (valorf > 100)
			{
			sprintf(buf_tmp,"%3.1f",(float)(valorf));
			}
		else if (valorf > 10)
			{
			sprintf(buf_tmp,"%2.2f",(float)(valorf));
			}
		else
			{
			sprintf(buf_tmp,"%1.3f",(float)(valorf));
			}
		}
	else
		{
		if (quantizacao == 0)
			{
			printf(put_disp,"%ld",(int32)(variavel));
			if (ptr_buf < 4)
				{
				if (ptr_buf == 1)
					{
					buf_tmp[3] = buf_tmp[0];
					buf_tmp[0] = '@';
					buf_tmp[1] = '@';
					buf_tmp[2] = '@';
					}
				else if (ptr_buf == 2)
					{
					buf_tmp[2] = buf_tmp[0];
					buf_tmp[3] = buf_tmp[1];
					buf_tmp[0] = '@';
					buf_tmp[1] = '@';
					}
				else if (ptr_buf == 3)
					{
					buf_tmp[3] = buf_tmp[2];
					buf_tmp[2] = buf_tmp[1];
					buf_tmp[1] = buf_tmp[0];
					buf_tmp[0] = '@';
					}
				}

//			fprintf(modbus,"\r\n%ld,%f,",(int32)(variavel), 11.50);

			}
		else
			{
			valorf = (float)(valorf / pob(quantizacao));
			
//			printf(put_disp,"%f",(float)(valorf));

			if (valorf > 100)
				{
				sprintf(buf_tmp,"%3.1f",(float)(valorf));
				}
			else if (valorf > 10)
				{
				sprintf(buf_tmp,"%2.2f",(float)(valorf));
				}
			else
				{
				sprintf(buf_tmp,"%1.3f",(float)(valorf));
				}
			
//			fprintf(modbus,"%f",(float)(valorf));
//			fprintf(modbus,"\r\n%f,%f",(float)(valorf) , (float)(11.50) );
			}
		}
	if (linha==1)
		{
		posicao = 0;
		}
	else if (linha==2)
		{
		posicao = 4;
		}
	else if (linha==3)
		{
		posicao = 8;
		}
	if (buf_tmp[0] == ' ')
		{
		if (buf_tmp[1] == ' ')
			{
			if (buf_tmp[2] == ' ')
				{
				if (buf_tmp[3] == ' ')
					{
					if (buf_tmp[4] == ' ')
						{
						buf_tmp[0] = ' ';
						buf_tmp[1] = ' ';
						buf_tmp[2] = '0';
						buf_tmp[3] = '.';
						buf_tmp[4] = '0';
						}
					}
				}
			}
		}
	
	for (y = 0; y < 5; y++)
		{
		if (y == 0)
			{
			if ((buf_tmp[0] == '.') || (buf_tmp[0] == ','))
				{
			    x = tabela_caracteres[0];
			    x = x | 0x80;
			    buf_display[posicao++] = x;
				}
			else if (buf_tmp[0] == '@')
				{
				buf_display[posicao++] = tabela_caracteres[MESPACO];
				}
			else if (buf_tmp[0] == ' ')
				{
				buf_display[posicao++] = tabela_caracteres[MESPACO];
				}
			else
				{
				buf_display[posicao++] = tabela_caracteres[buf_tmp[0]-'0'];
				}
			}
		else
			{
			if ((buf_tmp[y] == '.') || (buf_tmp[y] == ','))
				{
				posicao--;
			    x = buf_display[posicao];
			    x = x | 0x80;
			    buf_display[posicao] = x;
				posicao++;
				}
			else if (buf_tmp[y] == ' ')
				{
				buf_display[posicao++] = tabela_caracteres[MESPACO];
				}
			else if (buf_tmp[y] == '@')
				{
				buf_display[posicao++] = tabela_caracteres[MESPACO];
				}
			else
				{
				if ((buf_tmp[y] < '0') || (buf_tmp[y] > '9'))
					{
					buf_tmp[y] = '0';
					}
				buf_display[posicao++] = tabela_caracteres[buf_tmp[y]-'0'];
				}
			}
		}
	posicao--;
    x = buf_display[posicao];
    x = x & 0x7F;
    buf_display[posicao] = x;

}


void display_xx_xx(char linha,word variavel,char decimais,char quantizacao)	
{   
	char posicao;
	char x, z;
	word i;
	if (rolando == true)
		{
		if (ja_rolou == false)
			{
			return;
			}
		}
	
	if (linha==1)
		{
		posicao=0;
		}
	else if (linha==2)
		{
		posicao=4;
		}
	else if (linha==3)
		{
		posicao=8;
		}
	z = pob(quantizacao);
	i = variavel / z;
	binasc2(i);							/* saida em buf_tmp[0 a 4]*/
//    buf_display[posicao++] = tabela_caracteres[buf_tmp[2]-'0'];
    buf_display[posicao++] = tabela_caracteres[buf_tmp[3]-'0'];
    posicao--;
    x = buf_display[posicao];
    x = x | 0x80;
    buf_display[posicao] = x;
    posicao++;
    buf_display[posicao++] = tabela_caracteres[buf_tmp[4]-'0'];

    i=(int)(variavel-(int)((variavel / z)*z));
    i=(int)(i*100 / z);
	binasc2(i);		/* saida em buf_tmp[0 a 4]*/
    buf_display[posicao++] = tabela_caracteres[buf_tmp[0]-'0'];
}

void display_xxx_x(char linha,word variavel,char quantizacao)	
{   
	char posicao;
	char x, z;
	word i;
	if (rolando == true)
		{
		if (ja_rolou == false)
			{
			return;
			}
		}
	if (linha==1)
		{
		posicao=0;
		}
	else if (linha==2)
		{
		posicao=4;
		}
	else if (linha==3)
		{
		posicao=8;
		}
	z = pob(quantizacao);
	i = variavel / z;
	binasc2(i);							/* saida em buf_tmp[0 a 4]*/
    buf_display[posicao++] = tabela_caracteres[buf_tmp[2]-'0'];
    buf_display[posicao++] = tabela_caracteres[buf_tmp[3]-'0'];
    buf_display[posicao++] = tabela_caracteres[buf_tmp[4]-'0'];
    posicao--;
    x = buf_display[posicao];
    x = x | 0x80;
    buf_display[posicao] = x;
    posicao++;

    i=(int)(variavel-(int)((variavel / z)*z));
    i=(int)(i*100 / z);
	binasc2(i);		/* saida em buf_tmp[0 a 4]*/
    buf_display[posicao++] = tabela_caracteres[buf_tmp[3]-'0'];
}


void display_x_xxx(char linha,word variavel,char decimais,char quantizacao)	
{   
	char posicao;
	char x, z;
	word i;
	if (rolando == true)
		{
		if (ja_rolou == false)
			{
			return;
			}
		}
	
	if (linha==1)
		{
		posicao=0;
		}
	else if (linha==2)
		{
		posicao=4;
		}
	else if (linha==3)
		{
		posicao=8;
		}
	z = pob(quantizacao);
	i = variavel / z;
	binasc2(i);							/* saida em buf_tmp[0 a 4]*/
    buf_display[posicao++] = tabela_caracteres[buf_tmp[3]-'0'];

    posicao--;
    x = buf_display[posicao];
    x = x | 0x80;
    buf_display[posicao] = x;

    posicao++;
    buf_display[posicao++] = tabela_caracteres[buf_tmp[4]-'0'];

    i=(word)(variavel-(word)((variavel / z)*z));
    i=(word)(i*100 / z);
	binasc2(i);		/* saida em buf_tmp[0 a 4]*/
    buf_display[posicao++] = tabela_caracteres[buf_tmp[3]-'0'];
    buf_display[posicao++] = tabela_caracteres[buf_tmp[4]-'0'];
	    
    	
}


void display_n(char inicio, word variavel, char tamanho)	
{   
	char x;
	binasc2(variavel);							/* saida em buf_tmp[0 a 4]*/
	for (x = (5 - tamanho); x < 5; x++)
		{
	    buf_display[inicio++] = tabela_caracteres[buf_tmp[x]-'0'];
		}
}


#if (IFG == true)
	void displayfp(char linha, signed word variavel)
	{
		char posicao;
		word i;
		short sinal;
		if (rolando == true)
			{
			if (ja_rolou == false)
				{
				return;
				}
			}
	
		if (linha==1)
			{
			posicao=0;
			}
		else if (linha==2)
			{
			posicao=4;
			}
		else if (linha==3)
			{
			posicao=8;
			}
	
		if (variavel > 0)
			{
			sinal = 0;
			i = (word)(variavel);
			}
		else
			{
			sinal = 1;
			i = (word)(variavel * (-1));
			}
		i = i * 10;
	    i = (word)(i / 1.024);
	    
	    if ((i > 9950) && (i <  10050))
	    	{
		    buf_display[posicao++] = tabela_caracteres[MESPACO];
	    	buf_display[posicao++] = tabela_caracteres[M1] | 0x80; /* 0 e ponto */
			buf_display[posicao++] = tabela_caracteres[0];
			buf_display[posicao++] = tabela_caracteres[0];
	    	}
	    else
	    	{
//			if (sinal==1)
//		    	{
//			    buf_display[posicao++] = tabela_caracteres['I'-'0'];
//	    		}
//	    	else
//	    		{
//		    	buf_display[posicao++] = tabela_caracteres['C'-'0'];
//	    		}
//	   		buf_display[posicao++] = tabela_caracteres[M0] | 0x80; /* 0 e ponto */
			binasc2(i);							/* saida em buf_tmp[0 a 4]*/
			buf_display[posicao++]= tabela_caracteres[buf_tmp[1]-'0'];
			buf_display[posicao++]= tabela_caracteres[buf_tmp[2]-'0'];
			buf_display[posicao++]= tabela_caracteres[buf_tmp[3]-'0'];
			buf_display[posicao++]= tabela_caracteres[buf_tmp[4]-'0'];
			}
			
	}
#else
	void displayfp(char linha, signed word variavel)
	{
		char posicao;
		word i;
		short sinal;
		if (rolando == true)
			{
			if (ja_rolou == false)
				{
				return;
				}
			}
	
		if (linha==1)
			{
			posicao=0;
			}
		else if (linha==2)
			{
			posicao=4;
			}
		else if (linha==3)
			{
			posicao=8;
			}
	
		if (variavel > 0)
			{
			sinal = 0;
			i = (word)(variavel);
			}
		else
			{
			sinal = 1;
			i = (word)(variavel * (-1));
			}
		
	    i = (word)(i / 1.024);
	    
	    if ((i > 995) && (i <  1005))
	    	{
		    buf_display[posicao++] = tabela_caracteres[MESPACO];
	    	buf_display[posicao++] = tabela_caracteres[M1] | 0x80; /* 0 e ponto */
			buf_display[posicao++] = tabela_caracteres[0];
			buf_display[posicao++] = tabela_caracteres[0];
	    	}
	    else
	    	{
			if (sinal==1)
		    	{
			    buf_display[posicao++] = tabela_caracteres['I'-'0'];
	    		}
	    	else
	    		{
		    	buf_display[posicao++] = tabela_caracteres['C'-'0'];
	    		}
	   		buf_display[posicao++] = tabela_caracteres[M0] | 0x80; /* 0 e ponto */
			binasc2(i);							/* saida em buf_tmp[0 a 4]*/
			buf_display[posicao++]= tabela_caracteres[buf_tmp[2]-'0'];
			buf_display[posicao++]= tabela_caracteres[buf_tmp[3]-'0'];
			}
			
	}
#endif

#if (st94 == true)
	void leds(char qleds)
	{
		buf_display[12]=0;
 		buf_display[12]=qleds;
	}

#endif

void mensagem(char mens, char tipo)
{
	char x, caracter;

	if (rolando == true)
		{
		if (ja_rolou == false)
			{
			return;
			}
		}
	
	for (x = 0 ; x < 13; x++)
		{
		if (tipo == 0)
			{
			caracter = tabela_erros[mens][x];
			}
		#if (controlador == true)
			else if (tipo == 2)
				{
				caracter = tabela_mens_tipo2[mens][x];
				}	
			else if (tipo == 3)
				{
				caracter = tabela_mens_tipo3[mens][x];
				}	
			else if (tipo == 4)
				{
				caracter = tabela_mens_tipo4[mens][x];
				}
		#endif
		else
			{
			caracter = tabela_mens[mens][x];
			}
 		if (caracter == 0)
 			{
 			 return;
 			}
 		if ((caracter == '@') || (caracter == ' ' ))
 			{
			buf_display[x]= tabela_caracteres[MESPACO];
 			}
 		else if  (caracter == '-')
 			{
			buf_display[x]= 0x40;//mhifen;
 			}
 		else if  (caracter == '.')
 			{
			buf_display[x]= mponto;
 			}
 		else
 			{
			buf_display[x]= tabela_caracteres[caracter-'0'];
			}
		}
} 		


void mensagem_rola(char mens, char tipo)
{
	char x,y, caracter;
	if (rolando == false)
		{
		ja_rolou = false;
		rolando = true;
		ptr_rola = 0;
		ultima_mens = mens;
		ultimo_tipo = tipo;
		}
	else
		{
		mens = ultima_mens;
		tipo = ultimo_tipo;
		ptr_rola++;
		}

	y = 0;
	for (x = ptr_rola; x < (ptr_rola + 4); x++)
		{
		if (tipo == 0)
			{
			caracter = tabela_erros[mens][x];
			}
		#if (controlador == true)
			else if (tipo == 2)
				{
				caracter = tabela_mens_tipo2[mens][x];
				}
			else if (tipo == 4)
				{
				caracter = tabela_mens_tipo4[mens][x];
				}
			else if (tipo == 5)
				{
				caracter = tabela_mens_status[mens][x];
				}
		#endif
		else
			{
			caracter = tabela_mens[mens][x];
			}
 		if ((caracter == 0) || (caracter == '#'))
 			{
			ja_rolou = true;
			ptr_rola = 0;
			break;
 			}
 		if ((caracter == '@') || (caracter == ' ' ))
 			{
			buf_display[y]= tabela_caracteres[MESPACO];
 			}
 		else if  (caracter == '-' )
 			{
			buf_display[y]= mhifen;
 			}
 		else if  (caracter == '.' )
 			{
			buf_display[y]= mponto;
 			}
 		else
 			{
			buf_display[y]= tabela_caracteres[caracter-'0'];
			}
		y++;
		}
} 		


char converte_msg(char caracter)
{
	if (caracter == '@')
		{
		return(0);
		}
	else if (caracter == ' ' )
		{
		return(0);
 		}
 	else if (caracter == '.' )
 		{
		return(mponto);
 		}
 	else
 		{
		return(tabela_caracteres[caracter-'0']);
		}
}

void mensagem_inicial(void)
{
	char buf_nro[4];

	buf_nro[0] = read_byte(ee_nro_1);
	buf_nro[1] = read_byte(ee_nro_2);
	buf_nro[2] = read_byte(ee_nro_3);
	buf_nro[3] = read_byte(ee_nro_4);
	
	if ((buf_nro[0] < '0')	|| (buf_nro[0] > '9'))
		{
		buf_nro[0] = '0';
		write_byte(ee_nro_1, '0');
		}
	if ((buf_nro[1] < '0')	|| (buf_nro[1] > '9'))
		{
		buf_nro[1] = '0';
		write_byte(ee_nro_2, '0');
		}
	if ((buf_nro[2] < '0')	|| (buf_nro[2] > '9'))
		{
		buf_nro[2] = '0';
		write_byte(ee_nro_3, '0');
		}
	if ((buf_nro[3] < '0')	|| (buf_nro[3] > '9'))
		{
		buf_nro[3] = '0';
		write_byte(ee_nro_4, '0');
		}
	
	#if (ST8100C == true)
		LED = 0;
	
		buf_display[0]= tabela_caracteres[8];
		buf_display[1]= tabela_caracteres[1];
		buf_display[2]= tabela_caracteres[0];
		buf_display[3]= tabela_caracteres[0];
		buf_display[4] = 0;

		delay_ms(1000);

		return;
	
		if ((buf_nro[0] > ('0'- 1)) && (buf_nro[0] < ('9' + 1)))
			{
			if ((buf_nro[1] > ('0'- 1)) && (buf_nro[1] < ('9' + 1)))
				{
				if ((buf_nro[2] > ('0'- 1)) && (buf_nro[2] < ('9' + 1)))
					{
					if ((buf_nro[3] > ('0'- 1)) && (buf_nro[3] < ('9' + 1)))
						{
						buf_display[0]= tabela_caracteres[buf_nro[0]-'0'];
						buf_display[1]= tabela_caracteres[buf_nro[1]-'0'];
						buf_display[2]= tabela_caracteres[buf_nro[2]-'0'];
						buf_display[3]= tabela_caracteres[buf_nro[3]-'0'];
						existe = true;
						}
					}
				}
			}
		if (existe == false)
			{
			buf_display[0]= tabela_caracteres[cequipo[14]-'0'];
			buf_display[1]= tabela_caracteres[cequipo[15]-'0'];
			buf_display[2]= tabela_caracteres[cequipo[16]-'0'];
			buf_display[3]= tabela_caracteres[cequipo[17]-'0'];
			}
	
		delay_ms(1000);

	#else
	//				  012345678901234567890
	// cequipo[22] = "ST9400R-V2.20@0001.B";
	
	
		buf_display[0]= tabela_caracteres[cequipo[2]-'0'];
		buf_display[1]= tabela_caracteres[cequipo[3]-'0'];
		buf_display[2]= tabela_caracteres[cequipo[4]-'0'];
		buf_display[3]= tabela_caracteres[cequipo[5]-'0'];
	
		if ((buf_nro[0] > ('0'- 1)) && (buf_nro[0] < ('9' + 1)))
			{
			if ((buf_nro[1] > ('0'- 1)) && (buf_nro[1] < ('9' + 1)))
				{
				if ((buf_nro[2] > ('0'- 1)) && (buf_nro[2] < ('9' + 1)))
					{
					if ((buf_nro[3] > ('0'- 1)) && (buf_nro[3] < ('9' + 1)))
						{
						buf_display[4]= tabela_caracteres[buf_nro[0]-'0'];
						buf_display[5]= tabela_caracteres[buf_nro[1]-'0'];
						buf_display[6]= tabela_caracteres[buf_nro[2]-'0'];
						buf_display[7]= tabela_caracteres[buf_nro[3]-'0'];
						existe = true;
						}
					}
				}
			}
		if (existe == false)
			{
			buf_display[4]= tabela_caracteres[cequipo[14]-'0'];
			buf_display[5]= tabela_caracteres[cequipo[15]-'0'];
			buf_display[6]= tabela_caracteres[cequipo[16]-'0'];
			buf_display[7]= tabela_caracteres[cequipo[17]-'0'];
			}
	
		buf_display[8]= mponto;
		buf_display[9]= tabela_caracteres[cequipo[19]-'0'];
		buf_display[10]= tabela_caracteres[MESPACO];
		buf_display[11]= tabela_caracteres[MESPACO];
		buf_display[12]= 0x00;
	#endif
	
}




void limpa_linha(char linha)
{
	char x;
	if (linha == 1)
		{
		for (x = 0 ; x < 4; x++)
			{
			buf_display[x]= tabela_caracteres[MESPACO];
			}
		}
	else if (linha == 2)
		{
		for (x = 4 ; x < 8; x++)
			{
			buf_display[x]= tabela_caracteres[MESPACO];
			}
		}
	else if (linha == 3)
		{
		for (x = 8 ; x < 12; x++)
			{
			buf_display[x]= tabela_caracteres[MESPACO];
			}
		}


}
