/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST53PORT.C                                                     *
; Funcao: MODULO de definição do Hardware								 *
; 		transdutor de energia elétrica st53xxT		                     *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 11/11/2003                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/
//#define add0  	PIN_G0

//#define rd  	PIN_E0
//#define wr	  	PIN_E1
//#define cs_io   PIN_E2

// equates de pinos dos leds
#if (ad_microchip == true)

	#define ADE7754_CS	PIN_G1
	#define ADE7754_RST	PIN_G1


	#define CS5460A_CLK  PIN_G1
	#define CS5460A_DOUT PIN_G1
	#define CS5460A_DIN  PIN_G1
	#define CS5460A_CS_R PIN_G1
	#define CS5460A_CS_S PIN_G1
	#define CS5460A_CS_T PIN_G1
	#define CS5460A_RST	 PIN_G1
	
	// equates de pinos de controle do conversor AD
	#define MCP3208_CLK  PIN_F6
	#define MCP3208_DOUT PIN_F5
	#define MCP3208_DIN  PIN_F4
	#define MCP3208_CS   PIN_C1
	
	
	//equates de pinos controle do relógio
	#define RTC_SCLK PIN_C3
	#define RTC_IO   PIN_C5
	#define RTC_RST  PIN_C0


	// equates de pinos de controle da memoria flash
	#define FLASH_CLK  PIN_C3
	#define FLASH_SI   PIN_C5
	#define FLASH_SO   PIN_C4
	#define FLASH1_CE  PIN_E3
	#define FLASH2_CE  PIN_G1
	#define FLASH3_CE  PIN_G1
	#define FLASH4_CE  PIN_G1
	#define FLASH_HOLD PIN_B4
	
	
	#define alarme 		PIN_G0
	#define direcao		PIN_F7

	// EQUATES DE DEFINIÇÃO DO CONTROLE DO DISPLAY
	#define	CS_IO2		PIN_E5
	#define	CS_IO3		PIN_E6
	#define	CS_IO4		PIN_E7

	#define DISPLAY1	0b00000001
	#define DISPLAY2	0b00000010
	#define DISPLAY3	0b00000100
	#define DISPLAY4	0b00001000
	#define DISPLAY5	0b00010000
	#define DISPLAY6	0b00100000
	#define DISPLAY7	0b01000000
	#define DISPLAY8	0b10000000
	#define DISPLAY9	0b00000001
	#define DISPLAY10	0b00000010
	#define DISPLAY11	0b00000100
	#define DISPLAY12	0b00001000
	#define DISPLAY13	0b00010000

	const char tabela_disp[13]={DISPLAY1, 	 	//0
 								DISPLAY2,		//1
 								DISPLAY3,		//2
 								DISPLAY4,		//3
 								DISPLAY5,		//4
 								DISPLAY6,		//5
 								DISPLAY7,		//6
 								DISPLAY8,		//7
 								DISPLAY9,		//8
 								DISPLAY10,		//9
 								DISPLAY11,		//10
 								DISPLAY12,		//11
 								DISPLAY13		//12
								};


#endif


