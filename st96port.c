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


#define PGD		PIN_B7


#define CS_DISP   PIN_E2

#define MCP3208_CLK  PIN_F6
#define MCP3208_DOUT PIN_F5
#define MCP3208_DIN  PIN_F4
#define MCP3208_CS   PIN_C1

#if (versao_pci_st96 >= 4)
	#define MUX1	PIN_E5
	#define MUX2	PIN_E1
	
	#if (versao_pci_st96 >= 5)
		#define CS_PGA1	PIN_E6
		#define CS_PGA2	PIN_E6
		#define CS_PGA3	PIN_E6
		#define CS_PGA4	PIN_E6
		#define	Teste	PIN_E7
		
		#define PGA_SCLK PIN_F6
		#define PGA_DO   PIN_F4
	#else
		#define CS_PGA1	PIN_E6
		#define CS_PGA2	PIN_E7
		#define CS_PGA3	PIN_E0
		#define CS_PGA4	PIN_B4
		
		#define PGA_SCLK PIN_C3
		#define PGA_DO   PIN_C5
	#endif

	
	#define FLASH_HOLD PIN_F7

//equates de pinos controle do relógio
	#define RTC_SCLK PIN_C3
	#define RTC_IO   PIN_C5
	#define RTC_RST  PIN_C0

	#define FLASH_CLK  PIN_C3
	#define FLASH_SI   PIN_C5
	#define FLASH_SO   PIN_C4
	#define FLASH1_CE  PIN_E3
	#define FLASH2_CE  PIN_G4
	#define FLASH3_CE  PIN_G0
	#define FLASH4_CE  PIN_G3
	#define FLASH_WP   PIN_F7

	#define CA0			PIN_E4

	#define alarme 		PIN_F7


#else
	#define rd  	PIN_E0
	#define RST_AD	PIN_E1
	#define CS_AD2	PIN_E6
	#if (teste_vag == true)
		#define pino_teste PIN_E7
		#define CS_AD3	PIN_F7
	#else
		#define CS_AD3	PIN_E7
	#endif
	#define CA1		PIN_E5
	#define FLASH_HOLD PIN_B4

//equates de pinos controle do relógio
	#define RTC_SCLK PIN_C3
	#define RTC_IO   PIN_C5
	#define RTC_RST  PIN_C0

	#define FLASH_CLK  PIN_C3
	#define FLASH_SI   PIN_C5
	#define FLASH_SO   PIN_C4
	#define FLASH1_CE  PIN_E3
	#define FLASH2_CE  PIN_G4
	#define FLASH3_CE  PIN_G0
	#define FLASH4_CE  PIN_G3
	#define FLASH_WP   PIN_F7

	#define CA0			PIN_E4

	#define alarme PIN_B2

#endif	

//#if (chip_cs5460a == true)
	#define CS5460A_CLK  PIN_F7
	#define CS5460A_DOUT PIN_F7
	#define CS5460A_DIN  PIN_F7
	#define CS5460A_CS_R PIN_F7
	#define CS5460A_CS_S PIN_F7	
	#define CS5460A_CS_T PIN_F7	
	#define CS5460A_RST	 PIN_F7
//#endif






