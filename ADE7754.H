/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ADE7754.H                                                      *
; Funcao: MODULO DEFINICAO DE ENDERCOS DO ADE7754 						 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 18/02/2003                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */
/* VARIAVEL				ENDERECO		TAMANHO		TIPO 	DESCRICAO*/
#define ADE_RESERVED	0x00		/*  ??  		?	 	RESERVADO*/
#define AENERGY			0x01		/*  24 bits 	R	 	ENERGIA ATIVA ACUMULADA*/
#define RAENERGY		0x02		/*  24 bits 	R	 	ENERGIA ATIVA ACUMULADA, ZERADA A CADA LEITURA DA ANTERIOR*/
#define LAENERGY		0x03		/*  24 bits 	R	 	ENERGIA ATIVA ACUMULADA, DE LINHA*/
#define VAENERGY		0x04		/*  24 bits 	R	 	ENERGIA APARENTE ACUMULADA*/
#define RVAENERGY		0x05		/*  24 bits 	R	 	ENERGIA APARENTE ACUMULADA, ZERADA A CADA LEITURA DA ANTERIOR*/
#define LVAENERGY		0x06		/*  24 bits 	R	 	ENERGIA APARENTE ACUMULADA, DE LINHA*/
#define PERIOD_ADE7754	0x07		/*  15 bits 	R	 	PERIODO DA SENOIDE / FREQUENCIA*/
#define ADE_TEMP		0x08		/*  8 bits 		R	 	TEMPERATURA */
#define WAVEFORM		0x09		/*  24 bits 	R	 	PONTO DA FORMA DE ONDA*/
#define OPMODE			0x0A		/*  8 bits 		R/W	 	REG. DE MODO DE OPERACAO - CONFIGURACAO DO CHIP, DEFAULT 04H*/
#define MMODE			0x0B		/*  8 bits 		R/W	 	REG. DE MODO DE MEDIÇÃO - CONFIGURACAO DO CANAL A SER ANALIZADO, DEFAULT 70H*/
#define WAVEMODE		0x0C		/*  8 bits 		R/W	 	REG. DE MODO DO FORMA DE ONDA - QUAL CANAL ESTA SENDO LIDO, DEFAULT 00H*/
#define WATMODE			0x0D		/*  8 bits 		R/W	 	REG. DE FORMULA DE CALCULO DA ENERGIA ATIVA, DEFAULT 3FH*/
#define VAMODE			0x0E		/*  8 bits 		R/W	 	REG. DE FORMULA DE CALCULO DA ENERGIA APARENTE, DEFAULT 3FH*/
#define MASK			0x0F		/*  16 bits 	R/W	 	MASCARA DE INTERRUPÇOES, DEFINE QUAL EVENTO GERA INTERRUPÇÃO, DEFAULT 00H*/
#define STATUS			0x10		/*  16 bits 	R	 	STATUS DAS INTERRUPÇOES, DEFINE QUAL EVENTO GEROU INTERRUPÇÃO, DEFAULT 00H*/
#define RSTATUS			0x11		/*  16 bits 	R	 	STATUS DAS INTERRUPÇOES, MESMO ANTERIOR, ZERADO APOS LEITURA, DEFAULT 00H*/
#define ZEROCROSTIME	0x12		/*  16 bits 	R/W	 	REG. DE TEMPO DE CRUZAMENTO POR ZERO, DEFAULT FFFFH*/
#define LINECYCLE		0x13		/*  16 bits 	R/W	 	REG. DE CICLO DE LINHA, NRO DE CICLOS ACUMULADOS, DEFAULT FFFFH*/
#define SAGCYCLE		0x14		/*  8 bits 		R/W	 	REG. DE CICLO DE LINHA SAG, NRO DE CICLOS COM FALHA SAG, DEFAULT FFH*/
#define SAGLEVEL		0x15		/*  8 bits 		R/W	 	REG. DE NIVEL DE TENSAO SAG, NIVEL DE COMPARAÇÃO FALHA SAG, DEFAULT 00H*/
#define VPEAK			0x16		/*  8 bits 		R/W	 	REG. DE NIVEL DE PICO TENSAO, NIVEL DE COMPARAÇÃO PICO DE TENSAO, DEFAULT FFH*/
#define IPEAK			0x17		/*  8 bits 		R/W	 	REG. DE NIVEL DE PICO CORRENTE, NIVEL DE COMPARAÇÃO PICO DE CORRENTE, DEFAULT FFH*/
#define GAIN			0x18		/*  8 bits 		R/W	 	REG. GANHO PGA, AJUSTE DE GANHO DE TENSAO E CORRENTE NO PGA, DEFAULT 00H*/
#define AWG				0x19		/*  12 bits		R/W	 	REG. GANHO POT ATIVA FASE A,AJUSTE DE GANHO , DEFAULT 00H*/
#define BWG				0x1A		/*  12 bits		R/W	 	REG. GANHO POT ATIVA FASE B,AJUSTE DE GANHO , DEFAULT 00H*/
#define CWG				0x1B		/*  12 bits		R/W	 	REG. GANHO POT ATIVA FASE C,AJUSTE DE GANHO , DEFAULT 00H*/
#define AVAG			0x1C		/*  12 bits		R/W	 	REG. GANHO POT APARENTE FASE A,AJUSTE DE GANHO , DEFAULT 00H*/
#define BVAG			0x1D		/*  12 bits		R/W	 	REG. GANHO POT APARENTE FASE B,AJUSTE DE GANHO , DEFAULT 00H*/
#define CVAG			0x1E		/*  12 bits		R/W	 	REG. GANHO POT APARENTE FASE C,AJUSTE DE GANHO , DEFAULT 00H*/
#define APHCAL			0x1F		/*  6 bits		R/W	 	REG. CALIBRACAO FASE A, DEFAULT 00H*/
#define BPHCAL			0x20		/*  6 bits		R/W	 	REG. CALIBRACAO FASE B, DEFAULT 00H*/
#define CPHCAL			0x21		/*  6 bits		R/W	 	REG. CALIBRACAO FASE C, DEFAULT 00H*/
#define AAPOS			0x22		/*  12 bits		R/W	 	REG. CALIBRACAO OFFSET DE POTENCIA FASE A, DEFAULT 00H*/
#define BAPOS			0x23		/*  12 bits		R/W	 	REG. CALIBRACAO OFFSET DE POTENCIA FASE B, DEFAULT 00H*/
#define CAPOS			0x24		/*  12 bits		R/W	 	REG. CALIBRACAO OFFSET DE POTENCIA FASE C, DEFAULT 00H*/
#define CFNUM			0x25		/*  12 bits		R/W	 	REG. CF SCALING NUMERATOR,  DEFAULT 00H*/
#define CFDEN			0x26		/*  12 bits		R/W	 	REG. CF SCALING DENOMINATOR,  DEFAULT 3FH*/
#define WDIV			0x27		/*  8 bits		R/W	 	REG. DIVISOR DE ENERGIA ATIVA,  DEFAULT 00H*/
#define VADIV			0x28		/*  8 bits		R/W	 	REG. DIVISOR DE ENERGIA APARENTE,  DEFAULT 00H*/
#define AIRMS			0x29		/*  24 bits		R	 	CORRENTE RMS DA FASE A,  DEFAULT 00H*/
#define BIRMS			0x2A		/*  24 bits		R	 	CORRENTE RMS DA FASE B,  DEFAULT 00H*/
#define CIRMS			0x2B		/*  24 bits		R	 	CORRENTE RMS DA FASE C,  DEFAULT 00H*/
#define AVRMS			0x2C		/*  24 bits		R	 	TENSAO RMS DA FASE A,  DEFAULT 00H*/
#define BVRMS			0x2D		/*  24 bits		R	 	TENSAO RMS DA FASE A,  DEFAULT 00H*/
#define CVRMS			0x2E		/*  24 bits		R	 	TENSAO RMS DA FASE A,  DEFAULT 00H*/
#define AIRMSOS			0x2F		/*  12 bits		R/W	 	OFFSET DE AJUSTE DE CORRENTE FASE A,  DEFAULT 00H*/
#define BIRMSOS			0x30		/*  12 bits		R/W	 	OFFSET DE AJUSTE DE CORRENTE FASE B,  DEFAULT 00H*/
#define CIRMSOS			0x31		/*  12 bits		R/W	 	OFFSET DE AJUSTE DE CORRENTE FASE C,  DEFAULT 00H*/
#define AVRMSOS			0x32		/*  12 bits		R/W	 	OFFSET DE AJUSTE DE TENSAO FASE A,  DEFAULT 00H*/
#define BVRMSOS			0x33		/*  12 bits		R/W	 	OFFSET DE AJUSTE DE TENSAO FASE B,  DEFAULT 00H*/
#define CVRMSOS			0x34		/*  12 bits		R/W	 	OFFSET DE AJUSTE DE TENSAO FASE C,  DEFAULT 00H*/
#define AAPGAIN			0x35		/*  12 bits		R/W	 	AJUSTE DE GANHO DA POTENCIA ATIVA DA FASE A,  DEFAULT 00H*/
#define BAPGAIN			0x36		/*  12 bits		R/W	 	AJUSTE DE GANHO DA POTENCIA ATIVA DA FASE B,  DEFAULT 00H*/
#define CAPGAIN			0x37		/*  12 bits		R/W	 	AJUSTE DE GANHO DA POTENCIA ATIVA DA FASE C,  DEFAULT 00H*/
#define AVGAIN			0x38		/*  12 bits		R/W	 	AJUSTE DE GANHO DA TENSAO RMS FASE A,  DEFAULT 00H*/
#define BVGAIN			0x39		/*  12 bits		R/W	 	AJUSTE DE GANHO DA TENSAO RMS FASE B,  DEFAULT 00H*/
#define CVGAIN			0x3A		/*  12 bits		R/W	 	AJUSTE DE GANHO DA TENSAO RMS FASE C,  DEFAULT 00H*/
#define ADECHKSUM		0x3E		/*  8			R	 	CHECKSUM DA MENORIA DO ADE7754*/
#define ADEVERSION		0x3F		/*  8			R	 	VERSAO DO CHIP ADE7754, DEFAULT 01H*/



#define NR0_CICLOS		90			//(4 CICLOS DE 60HZ)


// valor a ser  gravado em OPMODE
#define MODO_OPER_ADE7754 0b00000100
/* 										modo de operacao 
							00000100
							||||||||- filtro passa alta entrada de corrente , 0 enable , 1  desable
							|||||||-- filtro passa baixa entrada de corrente , 0 enable , 1  desable
							||||||--- Saida de frequencia CF, 0, enable, 1 desable
							|||||---- 0 Normal Operation
							||||----- 0 Normal Operation
							|||------ 0 Normal Operation
							||------- 0 chip reset
							|-------- reserved
*/

#define GAIN_PGAS 0x00
/* Ganho das entradas de corrente e tensao , PGA1 e PGA2
	76543210
	00000000
	||||||||- \bits 0 e 1 PGA1 - Corrente: 00, Ganho 1; 01, Ganho 2; 10 Ganho 4; 11 Reservado
	|||||||-- /
	||||||--- ABS; Soma absoluta Wh, 
	|||||---- NOLOAD; não acummula kw se carga é baixa
	||||----- Reserved
	|||------ \bits 0 e 1 PGA2 - Tensao: 00, Ganho 1; 01, Ganho 2; 10 Ganho 4; 11 Reservado
	||------- /
	|-------- reserved
*/

#define MMODE_ADE7754 0x70
#define MMODE_ADE7754_A 0x10
#define MMODE_ADE7754_B 0x21
#define MMODE_ADE7754_C 0x42
/* Modo de medição
	76543210
	01110000	- 0x70
	00010000	- 0x10
	00100001	- 0x21
	01000010	- 0x42
	||||||||- \bits 0 e 1 seleciona a fase do periodo: 00 fase A; 01 fase B; 10 fase C; 11 Reserved
	|||||||-- /
	||||||--- \bits 2 e 3 seleciona a fase para detectar picos: 00 fase A; 01 fase B; 10 fase C; 11 Reserved
	|||||---- /
	||||----- \bits 4,5 e 6 Seleciona fase para contador de zero crossing
	|||------ /defalt 111
	||------- /
	|-------- reserved
*/

#define WAVEMODE_ADE7754_VR 0x30
#define WAVEMODE_ADE7754_VS 0x31
#define WAVEMODE_ADE7754_VT 0x32
#define WAVEMODE_ADE7754_CR 0x33
#define WAVEMODE_ADE7754_CS 0x34
#define WAVEMODE_ADE7754_CT 0x35
/* MODO DA FORMA DE ONDA
	76543210
	00100000	-VR	
	00100001	-VS
	00100010	-VT
	00100011	-CR
	00100100	-CS
	00100101	-CT
	||||||||- \bits 0,1 e 2 seleciona a fase tensao ou corrente
	|||||||-- / 000=VA; 001=VB; 010=VC;
	||||||--- / 011=CA; 100=CB; 101=CC;  11x - reserved
	|||||---- \bits 3, 4 Nro de amostras
	||||----- / 00=26.9kps; 01=13,0kps; 10=6,5kps; 11=3,3kps
	|||------ LVARSEL, Enabled acumulador de energia
	||------- 
	|-------- reserved
*/

#define WATMODE_ADE7754_TRI	0X3F
#define WATMODE_ADE7754_A	0X24
#define WATMODE_ADE7754_B	0X12
#define WATMODE_ADE7754_C	0X09
/* FORMULA DE CALCULO DE ENERGIA ativa
	76543210
	00100100	0x24 kw fase a
	00010010	0x12 kw fase b
	00001001	0x09 kw fase c
	00111111	0x3f kw trifase
	00000000	
	||||||||- \ bits 0,1 e 2 seleciona cada parte da formula
	|||||||-- / 000=VA; 001=VB; 010=VC;
	||||||--- / 011=CA; 100=CB; 101=CC;  11x - reserved
	|||||---- \ bits 3, 4 e 5 separa cada parte da formula
	||||----- / 000=
	|||------ /
	||------- \ formula de calculo da energia ativa
	|-------- / 00 VA*IA + VB*IB + VC*IC
				01 VA*(IA-IB) + 0 + VC*(IC-IB)
				10 VA*(IA-IB) + 0 + VC*IC
				11 reservado
*/

#define VAMODE_ADE7754 0x3f
/* FORMULA DE CALCULO DE ENERGIA aparente
	76543210                          
	00000000
	||||||||- \ bits 0,1 e 2 seleciona cada parte da formula
	|||||||-- / 000=VA; 001=VB; 010=VC;
	||||||--- / 011=CA; 100=CB; 101=CC;  11x - reserved
	|||||---- \ bits 3, 4 e 5 separa cadaparte da formula
	||||----- / 000=
	|||------ /
	||------- \ formula de calculo da energia ativa
	|-------- / 00 VA*IA + VB*IB + VC*IC
				01 VA*(IA-IB) + 0 + VC*(IC-IB)
				10 VA*(IA-IB) + 0 + VC*IC
				11 reservado
*/


#define MASK_ADE7754 0x07F0
//#define MASK_ADE7754 0x4000
#define MASK_ADE7754_WAVE 0x4000
#define MASK_ADE7754_KW 0x0400
/* MODO DA FORMA DE ONDA
	FEDCBA9876543210
	0000001110000000 0x0380
	0000011111110000 0x07F0
	0100000000000000 0x4000
	0000011110000000 0x0780
	0000010000000000 0x0400
	0000010010000000 0x0480
	0000010100000000 0x0500
	0000011000000000 0x0600
	1000011110000001 0x8781
	||||||||||||||||- 0-AEHF 	- ints 0/1 AENERGY FULL
	|||||||||||||||-- 1-SAGA 	- int efeito SAG na tensao fase A
	||||||||||||||--- 2-SAGB 	- int efeito SAG na tensao fase B
	|||||||||||||---- 3-SAGC 	- int efeito SAG na tensao fase C
	||||||||||||----- 4-ZXTOA	- int de zero crossing timeout fase A(Falta de fase A)
	|||||||||||------ 5-ZXTOB	- int de zero crossing timeout fase B(Falta de fase B)
	||||||||||------- 6-ZXTOC	- int de zero crossing timeout fase C(Falta de fase C)
	|||||||||-------- 7-ZXA  	- int de zero crossing, fase A
	||||||||--------- 8-ZXB  	- int de zero crossing, fase B
	|||||||---------- 9-ZXC  	- int de zero crossing, fase C
	||||||----------- 10-LENERGY - int p/ LAENERGY e LVAENERGY acumuladas e LINCYC finalizadas 
	|||||------------ 11-Reservado
	||||------------- 12-PKV	- int 
	|||-------------- 13-PKI 	- int 
	||--------------- 14-WFSM	- int dado forma de onda pronto 
	|---------------- 15-VAEHF	- ints 0/1 VAENERGY FULL
*/



