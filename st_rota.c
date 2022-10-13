/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: st92ROTA                                                        *
; Funcao: MODULO ROTINAS             									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */
//#include <18F6620.H>
//#include "st_vars.c"

/*;                BINASC2
;                ------
;       Funcao:  converte nro binario de 2 bytes em nro ASCII de ate' 4 digitos
;       Entrada: valor- valor binario 16bits
;       Saida:	buf_tmp[0 a 4] -  buffer ASCII (com 4 posicoes)
*/        
void binasc2(int16 valor)
{
    int16 ivalor;

    ivalor = valor/10000;
    buf_tmp[0] = ivalor+'0';
    valor = valor-(ivalor*10000);

    ivalor = valor/1000;
    buf_tmp[1] = ivalor+'0';
    valor = valor-(ivalor*1000);

    ivalor = valor/100;
    buf_tmp[2] = ivalor+'0';
    valor = valor-(ivalor*100);
        
    ivalor = valor/10;
    buf_tmp[3] = ivalor+'0';
    valor = valor-(ivalor*10);

	buf_tmp[4] = valor+'0';

}

/*;                BINASC
;                ------
;       Funcao:  converte nro binario de 1 byte em nro ASCII de ate' 3 digitos
;       Entrada: valor- valor binario 8 bits
;       Saida:	buf_tmp[0 a 2] -  buffer ASCII (com 3 posicoes)
*/        
void binasc(char valor)
{
    char ivalor;
    ivalor = valor/100;
    buf_tmp[0] = ivalor+'0';
    valor = valor-(ivalor*100);
        
    ivalor = valor/10;
    buf_tmp[1] = ivalor+'0';
    valor = valor-(ivalor*10);

	buf_tmp[2] = valor+'0';

}


/*;                BINASC2
;                ------
;       Funcao:  converte nro binario de 2 bytes em nro ASCII de ate' 4 digitos
;       Entrada: valor- valor binario 32 bits
;       Saida:	buf_tmp[0 a 9] -  buffer ASCII (com q0 posicoes)
*/        
void long_asc(int32 valor)
{
    int32 ivalor;

    ivalor = valor/1000000000;
    buf_tmp[0] = ivalor+'0';
    valor = valor-(ivalor*1000000000);
    
    ivalor = valor/100000000;
    buf_tmp[1] = ivalor+'0';
    valor = valor-(ivalor*100000000);
    
    ivalor = valor/10000000;
    buf_tmp[2] = ivalor+'0';
    valor = valor-(ivalor*10000000);

    ivalor = valor/1000000;
    buf_tmp[3] = ivalor+'0';
    valor = valor-(ivalor*1000000);

    ivalor = valor/100000;
    buf_tmp[4] = ivalor+'0';
    valor = valor-(ivalor*100000);

    ivalor = valor/10000;
    buf_tmp[5] = ivalor+'0';
    valor = valor-(ivalor*10000);

    ivalor = valor/1000;
    buf_tmp[6] = ivalor+'0';
    valor = valor-(ivalor*1000);

    ivalor = valor/100;
    buf_tmp[7] = ivalor+'0';
    valor = valor-(ivalor*100);
        
    ivalor = valor/10;
    buf_tmp[8] = ivalor+'0';
    valor = valor-(ivalor*10);

	buf_tmp[9] = valor+'0';

}

/*;***************************************************
;Funcao: converter 4 bytes ascii em 2 bytes binario
;Entrada:buf_tmp[0,1,2,3] com bytes ascii
;Saida:	data1_int com valor binario */
void ascbin1(void)
{
	int16 val_tmp;
	val_tmp = (buf_tmp[0]-'0')*1000;
	data1_int = val_tmp;
	val_tmp = (buf_tmp[1]-'0')*100;
	data1_int = data1_int + val_tmp;
	val_tmp = (buf_tmp[2]-'0')*10;
	data1_int = data1_int + val_tmp;
	val_tmp = buf_tmp[3]-'0';
	data1_int = data1_int + val_tmp;
}

/*;***************************************************
;Funcao: converter 3 bytes ascii em 1 byte binario
;Entrada:buf_tmp[1,2,3] com bytes ascii
;Saida:	data1 com valor binario */
void ascbin2(void)
{
	char val_tmp;
	val_tmp = (buf_tmp[1]-'0')*100;
	data1 =  val_tmp;
	val_tmp = (buf_tmp[2]-'0')*10;
	data1 = data1 + val_tmp;
	val_tmp = buf_tmp[3]-'0';
	data1 = data1 + val_tmp;
}

word pob(char quantizacao)
{
	if (quantizacao==0)
		{
		 return(1);
		}
	else if (quantizacao==1)
		{
		 return(2);
		}
	else if (quantizacao==2)
		{
		 return(4);
		}
	else if (quantizacao==3)
		{
		 return(8);
		}
	else if (quantizacao==4)
		{
		 return(16);
		}
	else if (quantizacao==5)
		{
		 return(32);
		}
	else if (quantizacao==6)
		{
		 return(64);
		}
	else if (quantizacao==7)
		{
		 return(128);
		}
	else if (quantizacao==8)
		{
		 return(256);
		}
	else if (quantizacao==9)
		{
		 return(512);
		}
	else if (quantizacao==10)
		{
		 return(1024);
		}
	else 
		{
		 return(1);
		}
 
}



void mulu_ww_int(int16 mul1, int16 mul2)
{
	char ARG1L;
	char ARG1H; 
	char ARG2L;
	char ARG2H;
	char salva_prodh;
	char salva_prodl;
	
	salva_prodh = PRODH;
	salva_prodl = PRODL;
		
	ARG1L = mul1;
	ARG1H = mul1 >> 8;
	ARG2L = mul2;
	ARG2H = mul2 >> 8;

	#asm
	
	MOVF	ARG1L, W
	MULWF	ARG2L
	
	MOVFF	PRODH, RES1
	MOVFF	PRODL, RES0
	
	MOVF	ARG1H, W
	MULWF	ARG2H
	
	MOVFF	PRODH, RES3
	MOVFF	PRODL, RES2
	
	MOVF	ARG2L, W
	MULWF	ARG1H

	MOVF	PRODL, W
	ADDWF	RES1, F
	MOVF	PRODH, W
	ADDWFC	RES2, F
	CLRF	WREG
	ADDWFC	RES3, F
	
	MOVF	ARG2H, W
	MULWF	ARG1L
	
	MOVF	PRODL, W
	ADDWF	RES1, F
	MOVF	PRODH, W
	ADDWFC	RES2, F
	CLRF	WREG
	ADDWFC	RES3, F

	MOVFF  RES3, 0x947
	MOVFF  RES2, 0x946
	MOVFF  RES1, 0x945
	MOVFF  RES0, 0x944

	#endasm

	PRODH = salva_prodh;
	PRODL = salva_prodl;
		
	return;
}

void mul_ww_int(int16 mul1, int16 mul2)
{
	char ARG1L;
	char ARG1H; 
	char ARG2L;
	char ARG2H;

	char salva_prodh;
	char salva_prodl;
	
	salva_prodh = PRODH;
	salva_prodl = PRODL;
		
	ARG1L = mul1;
	ARG1H = mul1 >> 8;
	ARG2L = mul2;
	ARG2H = mul2 >> 8;

	#asm
	
	MOVF	ARG1L, W
	MULWF	ARG2L
	
	MOVFF	PRODH, RES1
	MOVFF	PRODL, RES0
	
	MOVF	ARG1H, W
	MULWF	ARG2H
	
	MOVFF	PRODH, RES3
	MOVFF	PRODL, RES2
	
	MOVF	ARG2L, W
	MULWF	ARG1H

	MOVF	PRODL, W
	ADDWF	RES1, F
	MOVF	PRODH, W
	ADDWFC	RES2, F
	CLRF	WREG
	ADDWFC	RES3, F
	
	MOVF	ARG2H, W
	MULWF	ARG1L
	
	MOVF	PRODL, W
	ADDWF	RES1, F
	MOVF	PRODH, W
	ADDWFC	RES2, F
	CLRF	WREG
	ADDWFC	RES3, F


	BTFSS  ARG2H, 7			; TESTA SE ARG2 É NEGATIVO
	BRA	   SIGN_ARG1
	MOVF   ARG1L, W
	SUBWF  RES2
	MOVF   ARG1H, W
	SUBWFB RES3

SIGN_ARG1:
	BTFSS  ARG1H, 7			; TESTA SE ARG1 É NEGATIVO
	BRA    CONT_CODE
	MOVF   ARG2L, W
	SUBWF  RES2
	MOVF   ARG2H, W
	SUBWFB RES2
	
CONT_CODE:

	MOVFF  RES3, 0x947
	MOVFF  RES2, 0x946
	MOVFF  RES1, 0x945
	MOVFF  RES0, 0x944
	
	
	#endasm

	PRODH = salva_prodh;
	PRODL = salva_prodl;
		
	return;
}
