/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_display                                                        *
; Funcao: MODULO PRINCIPAL DE CONTROLE									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */
  
#define TAM_DSP		64         	/* Define numero de carac. do display */
#define LINHA_1		0
#define LINHA_2     16          
#define LINHA_3     32
#define LINHA_4     48
#define MEIO_DSP	TAM_DSP/2   /* Define o meio do display					*/
#define FIM_DSP		TAM_DSP     /* Ultimo caracter do display				*/
#define LIMP_DSP	1           /* Comando que limpa o display				*/
#define POSI_DSP	0x80        /* Coloca cursor na posicao inicial			*/
#define COND_UTI	0x38        /* Condicoes de utilizacao do display		*/
								/*  2 linhas, matriz 8x5, interface 8 bit	*/
#define MODOP_DSP	0x06        /* Modo de operacao do display:				*/
								/* Desloc. a direita com avanco autom.		*/
#define ATIVA_DSP	0x0C        /* Ativacao do display:						*/
							 	/* Mensagem aparente e cursor nao			*/
#define CUR_ESQ		0x10        /* Move o cursor para a esquerda			*/
#define CUR_DIR		0x14        /* Move o cursor para a direita				*/
#define CUR_ATV		0x0E        /* Ativa o cursor							*/
#define CUR_DATV	0x0C        /* Desativa o cursor						*/
#define SET_CGRAM_ADDRESS	0x40
#define TROC_LIN	0xC0        /*  ; Passa o cursor para a segunda linha	*/

#define TIPO_LCD	2
byte const LCD_INIC[4] ={COND_UTI, COND_UTI, MODOP_DSP, ATIVA_DSP};
byte lcd_linha;

char ultima_linha;
char ultima_mensagem;

#if (controlador == true)
	const char DB_DIR[8]={	
						// Caracter "0":
						//DB_DIR:
							0b00000001,
							0b00000011,
							0b00000011,
							0b00000011,
							0b00000011,
							0b00000011,
							0b00000011,
							0b00000001};
							
	const char DB_ESQ[8]={	
						//; Caracter "1":
						//DB_ESQ:
							0b00010000,
							0b00011000,
							0b00011000,
							0b00011000,
							0b00011000,
							0b00011000,
							0b00011000,
							0b00010000};
								
	const char DB_UP2[8]={	
						//; Caracter "2":
						//DB_UP2:
							0b00011111,
							0b00011111,
							0b00000000,
							0b00000000,
							0b00000000,
							0b00000000,
							0b00000000,
							0b00000000};
							
	const char DB_DOWN2[8]={	
						//; Caracter "3":
						//DB_DOWN2:
							0b00000000,
							0b00000000,
							0b00000000,
							0b00000000,
							0b00000000,
							0b00000000,
							0b00011111,
							0b00011111};
						
	const char DB_UP2_DOWN1[8]={	
						//; Caracter "4":
						//DB_UP2_DOWN1:
							0b00011111,
							0b00011111,
							0b00000000,
							0b00000000,
							0b00000000,
							0b00000000,
							0b00000000,
							0b00011111};
						
	const char DB_UP1_DOWN2[8]={	
						//; Caracter "5":
						//DB_UP1_DOWN2:
							0b00011111,
							0b00000000,
							0b00000000,
							0b00000000,
							0b00000000,
							0b00000000,
							0b00011111,
							0b00011111};
						
	const char DB_UP1[8]={	
						//; Caracter "6":
						//DB_UP1:
							0b00011111,
							0b00000000,
							0b00000000,
							0b00000000,
							0b00000000,
							0b00000000,
							0b00000000,
							0b00000000};
						
	const char DB_DOWN1[8]={	
						//; Caracter "7":
						//DB_DOWN1:
							0b00000000,
							0b00000000,
							0b00000000,
							0b00000000,
							0b00000000,
							0b00000000,
							0b00000000,
							0b00011111};

//Definiçao dos numeros para o display:
	const char D_ZERO_U[]={0, 2, 2, 1};
	const char D_ZERO_D[]={0, 3, 3, 1};
	const char D_UM_U[]={32, 0, 32, 32};
	const char D_UM_D[]={32, 0, 32, 32};
	const char D_DOIS_U[]={32, 4, 4, 1};
	const char D_DOIS_D[]={0, 5, 5, 32};
	const char D_TRES_U[]={32, 4, 4, 1};
	const char D_TRES_D[]={32, 5, 5, 1};
	const char D_QUATRO_U[]={0, 7, 7, 1};
	const char D_QUATRO_D[]={32, 6, 6, 1};
	const char D_CINCO_U[]={0, 4, 4, 32};
	const char D_CINCO_D[]={32, 5, 5, 1};
	const char D_SEIS_U[]={0, 4, 4, 32};
	const char D_SEIS_D[]={0, 5, 5, 1};
	const char D_SETE_U[]={32, 2, 2, 1};
	const char D_SETE_D[]={32, 32, 32, 1};
	const char D_OITO_U[]={0, 4, 4, 1};
	const char D_OITO_D[]={0, 5, 5, 1};
	const char D_NOVE_U[]={0, 4, 4, 1};
	const char D_NOVE_D[]={32, 5, 5, 1};
		
		
	const char D_C_U[]={"FP:"};
	const char D_C_D[]={"CAP"};
	const char D_I_U[]={"FP:"};
	const char D_I_D[]={"IND"};
	const char D_B_U[]={"FP:"};
	const char D_B_D[]={32, 32, 32};

	//;D_C_U:		DCB		0, 4, 32
	//;D_C_D:		DCB		32, 6, 32
	//;D_I_U:		DCB		32, 32, 32
	//;D_I_D:		DCB		0, 32, 32
	//;D_B_U:		DCB		32, 32, 32
	//;D_B_D:		DCB		32, 32, 32

#else
	#define nro_caracteres_cgram	3
	const char tabela_cgram[nro_caracteres_cgram * 8] ={	
	// up
									0b00000100,
									0b00001110,
									0b00011111,
									0b00000100,
									0b00000100,
									0b00000100,
									0b00000000,
									0b00000000,
	// down
									0b00000000,
									0b00000100,
									0b00000100,
									0b00000100,
									0b00011111,
									0b00001110,
									0b00000100,
									0b00000000
	// Enter
									0b00000001,
									0b00000001,
									0b00000101,
									0b00001101,
									0b00011111,
									0b00001100,
									0b00000100,
									0b00000000
	
								};
#endif


void display(char);


void wr_lcd(short controle_display, char caracter)
{
	if (controle_display == 1)
		{
		output_high(CA0);
		}
	else
		{
		output_low(CA0);
		}
	disable_interrupts(GLOBAL);
	
	output_d(caracter);
	output_low(CS_DISP);
	delay_cycles(1);
	output_high(CS_DISP);
	
	enable_interrupts(GLOBAL);

	output_high(CA0);
	if (controle_display == 1)
		{
		delay_ms(2);
		}
	else
		{
		delay_us(45);
		}
}

void ativa_cursor(void)
{
	wr_lcd(0,CUR_ATV);	
}
void desativa_cursor(void)
{
	wr_lcd(0,CUR_DATV);	
}
void volta_cursor(void)
{
	wr_lcd(0,CUR_ESQ);	
}
void avanca_cursor(void)
{
	wr_lcd(0,CUR_DIR);	
}

void primeira_linha(void)		/* Coloca cursor na posicao inicial	*/
{
	wr_lcd(0,POSI_DSP);	
}
void troca_linha(void)
{
	wr_lcd(0,TROC_LIN);	
}

void inic_dis(void)
{   
	char i;
	for(i = 0; i <= 3; i++)
		{
		wr_lcd(0,LCD_INIC[i]);	
		}
	#if (controlador == true)
		wr_lcd(0,SET_CGRAM_ADDRESS);	
		for(i = 0; i < 8 ; i++)
			{
			wr_lcd(1,DB_DIR[i]);	
			}
		for(i = 0; i < 8; i++)
			{
			wr_lcd(1,DB_ESQ[i]);	
			}
		for(i = 0; i < 8; i++)
			{
			wr_lcd(1,DB_UP2[i]);	
			}
		for(i = 0; i < 8; i++)
			{
			wr_lcd(1,DB_DOWN2[i]);	
			}
		for(i = 0; i < 8; i++)
			{
			wr_lcd(1,DB_UP2_DOWN1[i]);	
			}
		for(i = 0; i < 8; i++)
			{
			wr_lcd(1,DB_UP1_DOWN2[i]);	
			}
		for(i = 0; i < 8; i++)
			{
			wr_lcd(1,DB_UP1[i]);	
			}
		for(i = 0; i < 8; i++)
			{
			wr_lcd(1,DB_DOWN1[i]);	
			}
	#else
		wr_lcd(0,SET_CGRAM_ADDRESS);	
		for(i = 0; i < (nro_caracteres_cgram * 8); i++)
			{
			wr_lcd(1,tabela_cgram[i]);	
			}
	#endif
}

void lcd_gotoxy(byte x, byte y)
{
	byte lcd_addr;
	switch(y)
		{
		case 1:
			{
			lcd_addr = 0x80;
			break;
			}	
		case 2:
			{
			lcd_addr = 0xC0;
			break;
			}
		case 3:
			{
			lcd_addr = 0x90;
			break;
			}
		case 4:
			{
			lcd_addr = 0xD0;
			break;
			}
		}
	lcd_addr += x-1;
	wr_lcd(0, lcd_addr);
}

void limpa_display(void)
{
	wr_lcd(0,LIMP_DSP);
	delay_ms(2);	
}



void mensagem_rola(char linha, char linha_mens)
{
}

void mensagem(char linha, char linha_mens)
{
	char aux_disp;	
	ultima_linha = linha;
	ultima_mensagem = linha_mens;
	if (linha > 4)
		{
		linha = 1;
		}
	lcd_linha = linha;
	lcd_gotoxy(1,lcd_linha);
	caracter = 0xff;
	aux_disp = 0;
	while (caracter != 0)
		{
		if (linha_mens < 200)
			{
			#if (st_prog ==  false)
				if (idioma == ESPANHOL)
					{
					caracter = tabela_mens_esp[linha_mens][aux_disp++];
					}
				else
					{
					caracter = tabela_mens[linha_mens][aux_disp++];
					}
			#else
				caracter = tabela_mens[linha_mens][aux_disp++];
			#endif
			}
		else
			{
			if (linha_mens == 200)
				{
				#if (tratar_localizacao	== true)
					#if (portatil == true)
						caracter = localizacao[aux_disp++];
						if (digitando_texto == 0)
							{
							if (caracter == '#')		// enter, final de linha, terminador de localizacao
								{
								caracter = ' ';
								}
							}
					#endif
				#endif
				}
			}
		if (caracter == '@')			// pula caracter
			{
			avanca_cursor();
			}
		else if (caracter == 'é')		// up
			{
			wr_lcd(1, 0);
			}
		else if (caracter == 'â')		// down
			{
			wr_lcd(1, 1);
			}
		else if (caracter == 'ä')		// enter
			{
			wr_lcd(1, 2);
			}
		else
			{
			display(caracter);
			}
		if(aux_disp > 16)
			{
			break;
			}
		} 
}

void display(char caracter)
{   
	switch (caracter)
		{
		case '\f':
			{
			wr_lcd(0,1);
			lcd_linha = 1;
			break;			
			}
		case '\n':
			{
			lcd_gotoxy(1,++lcd_linha);
			break;
			}
		case '\b':
			{
			wr_lcd(0, 0x10);
			break;
			}
		case 0:
			{
			break;
			}
		default:
			{
			wr_lcd(1, caracter);
			}
		}	
}

void lcd_posi(char pos)
{
	if (pos < 16)				// 12345678901234567890
		{
		lcd_gotoxy(pos,1);
		}						// 1              16  20
	else if(pos < 32)			// 12345678901234567890
		{
		pos = pos - 16;
		lcd_gotoxy(pos,2);
		}						// 21			  36  40
	else if(pos < 48)			// 1234567890123456xxxx
		{
		pos = pos - 32;
		lcd_gotoxy(pos,3);
		}						// 21             36  40 
	else						// 1234567890123456xxxx
		{
		pos = pos - 48;		 
		lcd_gotoxy(pos,4);
		}
}

void mostra_cur(char pos)
{
	lcd_posi(pos);
	wr_lcd(0,CUR_ATV);	
}
	

void displayp(char pos, int16 variavel,char inteiros, char decimais,char quantizacao)	
{
	char z;
	char x;
	char decimal;
	int16 i;	

	decimal = decimais;			    

	if (pos < 16)				// 12345678901234567890
		{
		lcd_gotoxy(pos,1);
		}						// 1              16  20
	else if(pos < 32)			// 12345678901234567890
		{
		pos = pos - 16;
		lcd_gotoxy(pos,2);
		}						// 21			  36  40
	else if(pos < 48)			// 1234567890123456xxxx
		{
		pos = pos - 32;
		lcd_gotoxy(pos,3);
		}						// 21             36  40 
	else						// 1234567890123456xxxx
		{
		pos = pos - 48;		 
		lcd_gotoxy(pos,4);
		}
	
	if (quantizacao == 'P')	
		{
		if (programando == 1)
			{
			pisca = 1;	
			}
		else
			{
			pisca = 0;
			}
		z = 1;
		}
	else
		{
		pisca = 0;
		z = pob(quantizacao);
		}
	i = variavel / z;
	binasc2(i);		/* saida em buf_tmp[0 a 4]*/
	for (x = 5 - inteiros; x < 5; x++)
		{
		if (pisca == 1)
			{
			if (piscar == 1)
				{
			    wr_lcd(1,' ');
				}
			else
				{
			    wr_lcd(1,buf_tmp[x]);
		    	}
		    }
		 else
		 	{
		    wr_lcd(1,buf_tmp[x]);
			}
		}
	if (decimal != 0)
		{
		wr_lcd(1,',');
    	i=(int16)(variavel % z);
    	i=(int16)(i * 100 / z);
		binasc2(i);		/* saida em buf_tmp[0 a 4]*/
		for (x=3; x < 3 + decimal; x++)
			{
			if (pisca == 1)
				{
				if (piscar == 1)
					{
				    wr_lcd(1,' ');
					}
				else
					{
		    		wr_lcd(1,buf_tmp[x]);
		    		}
		    	}
		    else
		    	{
	    		wr_lcd(1,buf_tmp[x]);
			    }
			}
		}    
}


void print_display(char pos, int16 variavel,char quantizacao, char tipo)	
{
	
}

void displayd(char pos, int16 variavel,char status)	
{
	if (pos < 16)				// 12345678901234567890
		{
		lcd_gotoxy(pos,1);
		}						// 1              16  20
	else if(pos < 32)			// 12345678901234567890
		{
		pos = pos - 16;
		lcd_gotoxy(pos,2);
		}						// 21			  36  40
	else if(pos < 48)			// 1234567890123456xxxx
		{
		pos = pos - 32;
		lcd_gotoxy(pos,3);
		}						// 21             36  40 
	else						// 1234567890123456xxxx
		{
		pos = pos - 48;		 
		lcd_gotoxy(pos,4);
		}
	
	if (status == 'P')	
		{
		if (programando == 1)
			{
			pisca = 1;	
			}
		else
			{
			pisca = 0;
			}
		}
	else
		{
		pisca = 0;
		}
	if (pisca == 1)
		{
		if (piscar == 1)
			{
		    wr_lcd(1,' ');
			}
		else
			{
		    wr_lcd(1,'0');
		   	}
		}
	else
	 	{
	    wr_lcd(1,'0');
		}
	wr_lcd(1,',');
	binasc2(variavel);		/* saida em buf_tmp[0 a 4]*/
	if (pisca == 1)
		{
		if (piscar == 1)
			{
			wr_lcd(1,' ');
			wr_lcd(1,' ');
			}
		else
			{
	    	wr_lcd(1,buf_tmp[3]);
	    	wr_lcd(1,buf_tmp[4]);
	    	}
	    }
	else
	   	{
    	wr_lcd(1,buf_tmp[3]);
    	wr_lcd(1,buf_tmp[4]);
	    }
}


void displaypl(char pos, int32 variavel, char inteiros)	
{
	char x;
	lcd_posi(pos);
	long_asc(variavel);		/* saida em buf_tmp[0 a 9]*/
	for (x = 10 - inteiros; x < 10; x++)
		{
	    wr_lcd(1,buf_tmp[x]);
		}
}



#if (controlador == true)
void escreve_caracter_especial(char caracter, char posicao)
	{
	char x;
	caracter = caracter -'0';
	switch(caracter)
	   	{
	    case 0:
	    	{
	    	for (x = 0; x < 4; x++)
	 	  		{
		 	  	if (posicao == 'U')
		 	  		{
	 				wr_lcd(1,D_ZERO_U[x]);
	  				}
	   			else
	   				{
	   				wr_lcd(1,D_ZERO_D[x]);
					}
		    	}
		    break;
		    }
	    case 1:
	    	{
	    	for (x = 0; x < 4; x++)
	 	  		{
		 	  	if (posicao == 'U')
		 	  		{
	 				wr_lcd(1,D_UM_U[x]);
	  				}
	   			else
	   				{
	   				wr_lcd(1,D_UM_D[x]);
					}
		    	}
		    break;
		    }
	    case 2:
	    	{
	    	for (x = 0; x < 4; x++)
	 	  		{
		 	  	if (posicao == 'U')
		 	  		{
	 				wr_lcd(1,D_DOIS_U[x]);
	  				}
	   			else
	   				{
	   				wr_lcd(1,D_DOIS_D[x]);
					}
		    	}
		    break;
		    }
	    case 3:
	    	{
	    	for (x = 0; x < 4; x++)
	 	  		{
		 	  	if (posicao == 'U')
		 	  		{
	 				wr_lcd(1,D_TRES_U[x]);
	  				}
	   			else
	   				{
	   				wr_lcd(1,D_TRES_D[x]);
					}
		    	}
		    break;
		    }
	    case 4:
	    	{
	    	for (x = 0; x < 4; x++)
	 	  		{
		 	  	if (posicao == 'U')
		 	  		{
	 				wr_lcd(1,D_QUATRO_U[x]);
	  				}
	   			else
	   				{
	   				wr_lcd(1,D_QUATRO_D[x]);
					}
		    	}
		    break;
		    }
	    case 5:
	    	{
	    	for (x = 0; x < 4; x++)
	 	  		{
		 	  	if (posicao == 'U')
		 	  		{
	 				wr_lcd(1,D_CINCO_U[x]);
	  				}
	   			else
	   				{
	   				wr_lcd(1,D_CINCO_D[x]);
					}
		    	}
		    break;
		    }
	    case 6:
	    	{
	    	for (x = 0; x < 4; x++)
	 	  		{
		 	  	if (posicao == 'U')
		 	  		{
	 				wr_lcd(1,D_SEIS_U[x]);
	  				}
	   			else
	   				{
	   				wr_lcd(1,D_SEIS_D[x]);
					}
		    	}
		    break;
		    }
	    case 7:
	    	{
	    	for (x = 0; x < 4; x++)
	 	  		{
		 	  	if (posicao == 'U')
		 	  		{
	 				wr_lcd(1,D_SETE_U[x]);
	  				}
	   			else
	   				{
	   				wr_lcd(1,D_SETE_D[x]);
					}
		    	}
		    break;
		    }
	    case 8:
	    	{
	    	for (x = 0; x < 4; x++)
	 	  		{
		 	  	if (posicao == 'U')
		 	  		{
	 				wr_lcd(1,D_OITO_U[x]);
	  				}
	   			else
	   				{
	   				wr_lcd(1,D_OITO_D[x]);
					}
		    	}
		    break;
		    }
	    case 9:
	    	{
	    	for (x = 0; x < 4; x++)
	 	  		{
		 	  	if (posicao == 'U')
		 	  		{
	 				wr_lcd(1,D_NOVE_U[x]);
	  				}
	   			else
	   				{
	   				wr_lcd(1,D_NOVE_D[x]);
					}
		    	}
		    break;
		    }
		}
}
#endif


#if (controlador == true)
	void displayfp(char pos, signed int16 variavel, char tipo )
#else
	void displayfp(char pos, signed int16 variavel )
#endif
{
	int16 i;
	short sinal;
	char x, y;
	
	lcd_posi(pos);


	if (variavel > 0)
		{
		sinal = 0;
		i = (unsigned int16)(variavel);
		}
	else
		{
		sinal = 1;
		i = (unsigned int16)(variavel * (-1));
		}
	
    i = (unsigned int16)(i / 1.024);
    
	#if (controlador == true)
		if (tipo == 1)
			{
			primeira_linha();		/* Coloca cursor na posicao inicial	*/
		    if ((i > 995) && (i <  1005))
		    	{
			    wr_lcd(1,D_I_U[0]);
			    wr_lcd(1,D_I_U[1]);
			    wr_lcd(1,D_I_U[2]);
			    	
		    	// ESCREVE PRIMEIRA LINHA
			    escreve_caracter_especial('1', 'U');
			    wr_lcd(1,' ');
			    escreve_caracter_especial('0', 'U');
			    escreve_caracter_especial('0', 'U');
				troca_linha();
			    wr_lcd(1,D_B_D[0]);
			    wr_lcd(1,D_B_D[1]);
			    wr_lcd(1,D_B_D[2]);
			    
			    escreve_caracter_especial('1', 'D');
			    wr_lcd(1,'.');
			    escreve_caracter_especial('0', 'D');
			    escreve_caracter_especial('0', 'D');
			    
		    	}
		    else
		    	{
			    wr_lcd(1,D_I_U[0]);
			    wr_lcd(1,D_I_U[1]);
			    wr_lcd(1,D_I_U[2]);

//			    wr_lcd(1,'0');
//			    wr_lcd(1,',');
				binasc2(i);							/* saida em buf_tmp[0 a 4]*/
//		    	wr_lcd(1,buf_tmp[2]);
//		    	wr_lcd(1,buf_tmp[3]);
		    	
		    	// ESCREVE PRIMEIRA LINHA
			    escreve_caracter_especial('0', 'U');
			    wr_lcd(1,' ');
			    escreve_caracter_especial(buf_tmp[2], 'U');
			    escreve_caracter_especial(buf_tmp[3], 'U');
			    
		    	
				// ESCREVE SEGUNDA LINHA
				troca_linha();
				if (sinal==1)
			    	{
				    wr_lcd(1,D_I_D[0]);
				    wr_lcd(1,D_I_D[1]);
				    wr_lcd(1,D_I_D[2]);
		    		}
		    	else
		    		{
				    wr_lcd(1,D_C_D[0]);
				    wr_lcd(1,D_C_D[1]);
				    wr_lcd(1,D_C_D[2]);
		    		}
		    		
			    escreve_caracter_especial('0', 'D');
			    wr_lcd(1,'.');
			    escreve_caracter_especial(buf_tmp[2], 'D');
			    escreve_caracter_especial(buf_tmp[3], 'D');
		    		
		    	
				}
		    wr_lcd(1,' ');
		    }
		else
			{
		    if ((i > 995) && (i <  1005))
		    	{
			    wr_lcd(1,' ');
			    wr_lcd(1,'1');
			    wr_lcd(1,'.');
			    wr_lcd(1,'0');
			    wr_lcd(1,'0');
		    	}
		    else
		    	{
				if (sinal==1)
			    	{
				    wr_lcd(1,'i');
		    		}
		    	else
		    		{
				    wr_lcd(1,'c');
		    		}
			    wr_lcd(1,'0');
			    wr_lcd(1,',');
				binasc2(i);							/* saida em buf_tmp[0 a 4]*/
		    	wr_lcd(1,buf_tmp[2]);
		    	wr_lcd(1,buf_tmp[3]);
				}
		    wr_lcd(1,' ');
		   	}
	#else
	    if ((i > 995) && (i <  1005))
	    	{
		    wr_lcd(1,' ');
		    wr_lcd(1,'1');
		    wr_lcd(1,'.');
		    wr_lcd(1,'0');
		    wr_lcd(1,'0');
	    	}
	    else
	    	{
			if (sinal==1)
		    	{
			    wr_lcd(1,'i');
	    		}
	    	else
	    		{
			    wr_lcd(1,'c');
	    		}
		    wr_lcd(1,'0');
		    wr_lcd(1,',');
			binasc2(i);							/* saida em buf_tmp[0 a 4]*/
	    	wr_lcd(1,buf_tmp[2]);
	    	wr_lcd(1,buf_tmp[3]);
			}
	    wr_lcd(1,' ');
   #endif

}


/*		    	for (x = 0; x < 4; x++)
		    		{
    				wr_lcd(1,D_ZERO_D[x]);
			    	}
			    y = (buf_tmp[2] - '0')* 4;
		    	for (x = 0; x < 4; x++)
		    		{
    				wr_lcd(1,D_ZERO_D[y++]);
			    	}
			    y = (buf_tmp[3] - '0')* 4;
		    	for (x = 0; x < 4; x++)
		    		{
    				wr_lcd(1,D_ZERO_D[y++]);
			    	}
*/
void exibe_sim_nao(int16 variavel, char pos, char status)
{
	if (pos < 16)				// 12345678901234567890
		{
		lcd_gotoxy(pos,1);
		}						// 1              16  20
	else if(pos < 32)			// 12345678901234567890
		{
		pos = pos - 16;
		lcd_gotoxy(pos,2);
		}						// 21			  36  40
	else if(pos < 48)			// 1234567890123456xxxx
		{
		pos = pos - 32;
		lcd_gotoxy(pos,3);
		}						// 21             36  40 
	else						// 1234567890123456xxxx
		{
		pos = pos - 48;		 
		lcd_gotoxy(pos,4);
		}
				
	if (variavel == 0)
		{
		buf_tmp[0]='N';
		buf_tmp[1]='a';
		buf_tmp[2]='o';
		}
	else
		{
		buf_tmp[0]='S';
		buf_tmp[1]='i';
		buf_tmp[2]='m';
		}
	if ((piscar == 1) && (status == 'P'))
		{
		buf_tmp[0]=' ';
		buf_tmp[1]=' ';
		buf_tmp[2]=' ';
		}
	wr_lcd(1,buf_tmp[0]);
	wr_lcd(1,buf_tmp[1]);
	wr_lcd(1,buf_tmp[2]);
}

void exibe_off(char pos)
{
	#if (st8600c == true) || (st8620c == true)
		if (programando == 1)
			{
			if (piscar == 1)
				{
				lcd_posi(pos);
				wr_lcd(1,' ');
				wr_lcd(1,' ');
				wr_lcd(1,' ');
				wr_lcd(1,' ');
				}
			else
				{
				lcd_posi(pos);
				wr_lcd(1,' ');
				wr_lcd(1,'O');
				wr_lcd(1,'F');
				wr_lcd(1,'F');
				}
			}
		else
			{
			lcd_posi(pos);
			wr_lcd(1,' ');
			wr_lcd(1,'O');
			wr_lcd(1,'F');
			wr_lcd(1,'F');
			}
	#else
		lcd_posi(pos);
		wr_lcd(1,' ');
		wr_lcd(1,'O');
		wr_lcd(1,'F');
		wr_lcd(1,'F');
	#endif
}

void mensagem_inicial(void)
{
	char buf_nro[4];

	buf_nro[0] = read_byte(ee_nro_1);
	buf_nro[1] = read_byte(ee_nro_2);
	buf_nro[2] = read_byte(ee_nro_3);
	buf_nro[3] = read_byte(ee_nro_4);

	inic_dis();
	inic_idioma();
	#if (st_prog == true)
		mensagem(1,0);
		mensagem(2,1);
		mensagem(3,2);
		lcd_gotoxy(5,4);
		for (aux_b1=0; aux_b1 < 7; aux_b1++)
			{
			display(cequipo[aux_b1]);
			}
		mensagem(4,0);
		lcd_gotoxy(3,4);
		existe = false;
	#endif

	#if (st9600r == true)
		mensagem(1,69);
		mensagem(2,66);
		mensagem(3,0);
		lcd_gotoxy(5,3);
		for (aux_b1=0; aux_b1 < 7; aux_b1++)
			{
			display(cequipo[aux_b1]);
			}
		mensagem(4,0);
		lcd_gotoxy(3,4);
		existe = false;
	#endif

	#if ((st8600c == true) || (st8620c == true))
		mensagem(1,1);
		mensagem(2,2);
	#endif
	for (aux_b1=8; aux_b1 < 20; aux_b1++)
		{
		data1 = cequipo[aux_b1];
       	if (data1 == '@') 
       		{
			if ((buf_nro[0] > ('0'- 1)) && (buf_nro[0] < ('9' + 1)))
				{
				if ((buf_nro[1] > ('0'- 1)) && (buf_nro[1] < ('9' + 1)))
					{
					if ((buf_nro[2] > ('0'- 1)) && (buf_nro[2] < ('9' + 1)))
						{
						if ((buf_nro[3] > ('0'- 1)) && (buf_nro[3] < ('9' + 1)))
							{
							display('-');
							existe = true;
						    for (aux_b2 = 0; aux_b2 < 4; aux_b2++)
       							{
								data1 = buf_nro[aux_b2];
								display(data1);
								aux_b1++;
       							}
							}
						}
					}
				}
			if (existe == false)
				{
				display('-');
			    for (aux_b2 = 0; aux_b2 < 4; aux_b2++)
					{
					data1 = cequipo[aux_b1];
					display(data1);
					aux_b1++;
					}

				}
			}
		else
			{
			display(data1);
			}
		}

}	


#if (st8620c == true) 
	void leds(char qleds)
		{
		}
#endif


/* Fim lcd_16x2 */

