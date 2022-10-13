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
#define add0  	PIN_G0

#define rd  	PIN_E0
#define wr	  	PIN_E1
#define cs_io   PIN_E2

// equates de pinos dos leds
#define led_ok		PIN_D4
#define led_erro	PIN_D5
#define led_rx		PIN_D6
#define led_tx		PIN_D7

// equates de pinos de controle do conversor AD
#define MCP3208_CLK  PIN_D3
#define MCP3208_DOUT PIN_D2
#define MCP3208_DIN  PIN_D1
#define MCP3208_CS   PIN_D0


//equates de pinos controle do relógio
#define RTC_SCLK PIN_C3
#define RTC_IO   PIN_C4
#define RTC_RST  PIN_C0

// equates de pinos de controle da memoria flash
#define FLASH_CLK  PIN_C3
#define FLASH_SI   PIN_C5
#define FLASH_SO   PIN_C4
#define FLASH1_CE  PIN_E3
#define FLASH2_CE  PIN_G4
#define FLASH_HOLD PIN_B3


#define alarme 		PIN_B2
#define direcao		PIN_F7
