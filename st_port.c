/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: CP_INTS                                                        *
; Funcao: MODULO Interrupçoes   						 *
; 		Conversor de protocolo MP400 / Modbus/RTU                        *
;		By Sultech For AGST
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 06/06/2003                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/

#define add0  	PIN_G0
#define add1  	PIN_G3
#define rd  	PIN_E0
#define wr	  	PIN_E1
#define xram	PIN_B4
#define cs_io   PIN_E2

#define MCP3208_CLK  PIN_F6
#define MCP3208_DOUT PIN_F5
#define MCP3208_DIN  PIN_F4
#define MCP3208_CS   PIN_C1


//equates de pinos controle do relógio
#define RTC_SCLK PIN_C3
#define RTC_IO   PIN_C5
#define RTC_RST  PIN_C0

#define FLASH_CLK  PIN_C3
#define FLASH_SI   PIN_C5
#define FLASH_SO   PIN_C4
#define FLASH1_CE  PIN_E3
#define FLASH2_CE  PIN_G4
#define FLASH_HOLD PIN_B3
#define FLASH_WP   PIN_C0


#define tec_up		PIN_E4
#define tec_down	PIN_E5
#define tec_reset	PIN_E6
#define tec_enter	PIN_E7

#define alarme 		PIN_B2
#define direcao		PIN_F7
