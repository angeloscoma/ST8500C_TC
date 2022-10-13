/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_display                                                     *
; Funcao: MODULO PRINCIPAL DE CONTROLE									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/
  
#define TAM_DSP		32         	// Define numero de carac. do display
#define MEIO_DSP	TAM_DSP/2   // Define o meio do display
#define FIM_DSP		TAM_DSP     // Ultimo caracter do display
#define LIMP_DSP	1           // Comando que limpa o display
#define POSI_DSP	0x80        // Coloca cursor na posicao inicial
#define TROC_LIN	0xC0        // Passa o cursor para a segunda linha
#define COND_UTI	0x38        // Condicoes de utilizacao do display
								// 2 linhas, matriz 8x5, interface 8 bit
#define MODOP_DSP	0x06        // Modo de operacao do display:
								// Desloc. a direita com avanco autom.
#define ATIVA_DSP	0x0C        // Ativacao do display:
							 	// Mensagem aparente e cursor nao
#define CUR_ESQ		0x10        // Move o cursor para a esquerda
#define CUR_DIR		0x14        // Move o cursor para a direita
#define CUR_ATV		0x0E        // Ativa o cursor
#define CUR_DATV	0x0C        // Desativa o cursor

void wr_dado_lcd(char caracter)
{
	output_d(0);
	output_low(add0);
	output_high(add0);
	
	output_high(rd);
	output_d(caracter);
	output_low(wr);
	output_low(cs_io);
	output_high(wr);
	output_high(cs_io);
	delay_us(4);
}

void wr_inst_lcd(char instrucao)
{
	output_d(1);
	output_low(add0);
	output_high(add0);
	
	output_high(rd);
	output_d(instrucao);
	output_low(wr);
	output_low(cs_io);
	output_high(wr);
	output_high(cs_io);
	delay_ms(10);
}

void inic_dis(void)
{   
	wr_inst_lcd(COND_UTI);			/* Escreve COND_UTI no display (comando)*/
	wr_inst_lcd(COND_UTI);			/* Escreve COND_UTI no display (comando)*/
	wr_inst_lcd(MODOP_DSP);		/* Carrega o reg. aux. com MODOP_DSP */
	wr_inst_lcd(ATIVA_DSP); 		/*Carrega o reg. aux. com ATIVA_DSP*/
}

void display(char pos, char *str)
{   
	char x;
	if (pos < 16)
		{
		wr_inst_lcd(POSI_DSP);
		}
	else
		{
		wr_inst_lcd(TROC_LIN);
		} 
	x = 0;
	caracter=0xff;
	while (caracter != 0x00 && x < 16) 
		{
	    x++;
	    caracter= *str;
	    *str++;
	    if (caracter != 0x00)
	    	{
		    wr_dado_lcd(caracter);
		   	}
		}
}

void displayp(char pos, int16 variavel,char inteiros, char decimais,char quantizacao)	
{
	char z;
	char x;
	int16 i;
	if (pos < 16)
		{
		wr_inst_lcd(POSI_DSP + pos);
		}
	else
		{
		pos=pos - 16;
		wr_inst_lcd(TROC_LIN + pos);
		}
	z = pob(quantizacao);
	i = variavel/z;
	binasc2(i);		/* saida em buf_tmp[0 a 4]*/
	for (x= 5 - inteiros; x < 5; x++)
		{
	    wr_dado_lcd(buf_tmp[x]);
		}
	if (decimais!=0)
		{
		wr_dado_lcd(',');
    	i=(int)(variavel-(int)((variavel/z)*z));
    	i=(int)(i*100/z);
		binasc2(i);		/* saida em buf_tmp[0 a 4]*/
		for (x=3; x < 3 + decimais; x++)
			{
	    	wr_dado_lcd(buf_tmp[x]);
			}
		}    
}


/* Fim lcd_16x2 */
