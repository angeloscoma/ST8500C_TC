/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRONICOS                                  *
; Modulo: ST8610PORT           				    						 *
; Funcao: DEFINICAO DA INTERFACE COM HARDWARE			 				 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 06/06/2003                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/


#define PGD				PIN_B7
#define CA0				PIN_E2


#define rcv_rep		PIN_G2

// DEFINE I/O

#if (pci_st8200 >= 2)
	#define CS_DISP		PIN_E1
	#define CSIO1		PIN_E3
	#define CSIO2		PIN_E4
	#define CSIO3		PIN_E5
	#define CSIO4		PIN_E6
#else
	#define CS_DISP		PIN_A4
	#define CSIO1		PIN_A4
	#define CSIO2		PIN_C0
	#define CSIO3		PIN_C1
	#define CSIO4		PIN_C2
#endif

#define FLASH_CLK		PIN_C3
#define FLASH_SI		PIN_C5
#define FLASH_SO		PIN_C4
#define FLASH1_CE		PIN_B3

#define alarme			PIN_B2
#define back			PIN_B4

struct DEF_LEDS
{
	short LED1 : 1;
	short LED2 : 1;
	short LED3 : 1;
	short LED4 : 1;
	short LED5 : 1;
	short LED6 : 1;
	short LED7 : 1;
	short LED8 : 1;
}LED;

struct DEF_SAIDA2
{
	short SD1 : 1;
	short SD2 : 1;
	short SD3 : 1;
	short SD4 : 1;
	short SD5 : 1;
	short SD6 : 1;
	short SD7 : 1;
	short SD8 : 1;
}SAIDA2;

struct DEF_SAIDA3
{
	short SD9 : 1;
	short SD10 : 1;
	short SD11 : 1;
	short SD12 : 1;
	short SD13 : 1;
	short SD14 : 1;
	short SD15 : 1;
	short SD16 : 1;
}SAIDA3;

struct DEF_SAIDA4
{
	short SD17 : 1;
	short SD18 : 1;
	short SD19 : 1;
	short SD20 : 1;
	short SD21 : 1;
	short SD22 : 1;
	short SD23 : 1;
	short SD24 : 1;
}SAIDA4;

#define TRIAC_1	 SAIDA2.SD1
#define TRIAC_2	 SAIDA2.SD2
#define TRIAC_3	 SAIDA2.SD3
#define TRIAC_4	 SAIDA2.SD4
#define TRIAC_5	 SAIDA2.SD5
#define TRIAC_6	 SAIDA2.SD6
#if (bancos_12 == false)
	#define TRIAC_7 SAIDA2.SD7
	#define TRIAC_8 SAIDA2.SD8
	#define TRIAC_9 SAIDA3.SD9
	#define TRIAC_10 SAIDA3.SD10
	#define TRIAC_11 SAIDA3.SD11
	#define TRIAC_12 SAIDA3.SD12
	#define TRIAC_13 SAIDA3.SD13
	#define TRIAC_14 SAIDA3.SD14
	#define TRIAC_15 SAIDA3.SD15
	#define TRIAC_16 SAIDA3.SD16
#else
	#define TRIAC_7 SAIDA3.SD9
	#define TRIAC_8 SAIDA3.SD10
	#define TRIAC_9 SAIDA3.SD11
	#define TRIAC_10 SAIDA3.SD12
	#define TRIAC_11 SAIDA3.SD13
	#define TRIAC_12 SAIDA3.SD14
	#define TRIAC_13 SAIDA3.SD15
	#define TRIAC_14 SAIDA3.SD16
	#define TRIAC_15 SAIDA3.SD16
	#define TRIAC_16 SAIDA3.SD16
#endif

#define DISPLAY_1 SAIDA4.SD17
#define DISPLAY_2 SAIDA4.SD18
#define DISPLAY_3 SAIDA4.SD19
#define DISPLAY_4 SAIDA4.SD20
#define DISPLAY_5 SAIDA4.SD21

#define led_ok		LED.LED1
#define led_alarme	LED.LED2
#define led_rx		LED.LED3
#define led_tx		LED.LED4
#define led_v		LED.LED5
#define led_a		LED.LED6
#define led_r		LED.LED7
#define led_w		LED.LED8

	#define DISPLAY1	0b00000001
	#define DISPLAY2	0b00000010
	#define DISPLAY3	0b00000100
	#define DISPLAY4	0b00001000
	#define DISPLAY5	0b00010000
	#define DISPLAY6	0b00000000

	const char tabela_disp[6] ={DISPLAY1, 	 	//0
 								DISPLAY2,		//1
 								DISPLAY3,		//2
 								DISPLAY4,		//3
 								DISPLAY5,		//4
 								DISPLAY6		//5
								};


//  PINOS NÿÃO USADOS

#define rd  		PIN_B5

#define RST_AD 		PIN_B5
#define CS_AD2		PIN_B5
#define CS_AD3		PIN_B5

//#if (chip_cs5460a == true)
	#define CS5460A_CLK  PIN_B5
	#define CS5460A_DOUT PIN_B5 
	#define CS5460A_DIN  PIN_B5
	#define CS5460A_CS_R PIN_B5
	#define CS5460A_CS_S PIN_B5
	#define CS5460A_CS_T PIN_B5
	#define CS5460A_RST	 PIN_B5
//#endif

//equates de pinos controle do relÿógio
#define RTC_SCLK PIN_B5
#define RTC_IO   PIN_B5
#define RTC_RST  PIN_B5

#define FLASH2_CE  PIN_B5
#define FLASH3_CE  PIN_B5
#define FLASH4_CE  PIN_B5
#define FLASH_HOLD PIN_B5
#define FLASH_WP   PIN_B5


#define CA1			PIN_B5



#define direcao   PIN_B5
#define direcao2  PIN_B5

#define CSIO5		PIN_B5
#define CSIO6		PIN_B5
#define CSIO7		PIN_B5
#define CSIO8		PIN_B5

#define MCP3208_CLK  PIN_B5
#define MCP3208_DOUT PIN_B5
#define MCP3208_DIN  PIN_B5
#define MCP3208_CS   PIN_B5
