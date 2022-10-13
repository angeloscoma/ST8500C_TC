/*;**********************************************************************
; Empresa:	SULTECH SISTEMAS ELETRÔNICOS								*
; Módulo:	ST92PORT.C													*
; Função: 	MODULO de definição do Hardware								*
; 			Transdutor de Energia Elétrica ST92xxR						*
; Responsável:	VAGNER SANTOS											*
; Modificado:	VAGNER SANTOS											*
; Início:	11/11/2003													*
; Revisão:	RENGAV ARIERREF SOD SOTNAS									*
;************************************************************************/


// equates de pinos dos leds
#if (ad_microchip == true)

	#define ADE7754_CS	PIN_E0
	#define ADE7754_RST	PIN_E0


	#define CS5460A_CLK  PIN_E0
	#define CS5460A_DOUT PIN_E0
	#define CS5460A_DIN  PIN_E0
	#define CS5460A_CS_R PIN_E0
	#define CS5460A_CS_S PIN_E0
	#define CS5460A_CS_T PIN_E0
	#define CS5460A_RST	 PIN_E0
	
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
	#define FLASH2_CE  PIN_E0
	#define FLASH3_CE  PIN_E0
	#define FLASH4_CE  PIN_E0
	#define FLASH_HOLD PIN_B4
	
	
	#define alarme 		PIN_G0
	#define direcao		PIN_F7

	// EQUATES DE DEFINIÇÃO DO CONTROLE DO DISPLAY
	#define CA0			PIN_E4
	#define CS_DISP		PIN_E6
	#define back		PIN_C2

	#define	CS_IO2		PIN_E5
//	#define	CS_IO3		PIN_E6
	#define	CS_IO4		PIN_E7

	// Equates de pinos de controle do Rep
	#define rcv_rep		PIN_G2

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
//
	#define led_ok		LED.LED5
	#define led_alarme	LED.LED6
	#define led_rx		LED.LED7
	#define led_tx		LED.LED8

#endif


