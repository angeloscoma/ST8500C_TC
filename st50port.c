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
#if (st5000c_rev12 == true)
		// equates de pinos de controle do conversor AD
	#define MCP3208_CLK  PIN_E0
	#define MCP3208_DOUT PIN_G4
	#define MCP3208_DIN  PIN_G3
	#define MCP3208_CS   PIN_G0

	#define alarme 		PIN_C1
	#define direcao		PIN_F7

	
	#define BAUD0		PIN_E4
	#define BAUD1		PIN_E5
	#define LIGA0		PIN_E6
	#define LIGA1		PIN_E7
	
	#define pulso_kw	PIN_B3
	#define pulso_kvar	PIN_B4
	#define entrada_aux	PIN_B2
	
	//equates de pinos controle do relógio
	#define RTC_SCLK PIN_C3
	#define RTC_IO   PIN_C5
	#define RTC_RST  PIN_C0

	// equates de pinos de controle da memoria flash
	#define FLASH_CLK  PIN_C3
	#define FLASH_SI   PIN_C5
	#define FLASH_SO   PIN_C4
	#define FLASH1_CE  PIN_E3
	
	#define FLASH2_CE  PIN_E1
	#define FLASH3_CE  PIN_E1
	#define FLASH4_CE  PIN_E1
	#define FLASH_HOLD PIN_E1
		


#else
	#if (ad_microchip == true)
	
		#define ADE7754_CS	PIN_G0
		#define ADE7754_RST	PIN_G3
	
	
		#define CS5460A_CLK  PIN_G1
		#define CS5460A_DOUT PIN_G1
		#define CS5460A_DIN  PIN_G1
		#define CS5460A_CS_R PIN_G1
		#define CS5460A_CS_S PIN_G1
		#define CS5460A_CS_T PIN_G1
		#define CS5460A_RST	 PIN_G1
		
		// equates de pinos de controle do conversor AD
		#define MCP3208_CLK  PIN_D3
		#define MCP3208_DOUT PIN_D2
		#define MCP3208_DIN  PIN_D1
		#define MCP3208_CS   PIN_D0
		
		
		//equates de pinos controle do relógio
		#define RTC_SCLK PIN_C3
		#define RTC_IO   PIN_C5
		#define RTC_RST  PIN_C0
		
		// equates de pinos de controle da memoria flash
		#define FLASH_CLK  PIN_C3
		#define FLASH_SI   PIN_C5
		#define FLASH_SO   PIN_C4
		#define FLASH1_CE  PIN_E3
		#define FLASH2_CE  PIN_G4
		#define FLASH3_CE  PIN_G4
		#define FLASH4_CE  PIN_G4
		#define FLASH_HOLD PIN_B4
		
		
		#define alarme 		PIN_C1
		#define direcao		PIN_F7
	
	#endif

	#if (ADE7754 == true)
	
		#define ADE7754_CS	PIN_G0
		#define ADE7754_RST	PIN_G3
		#define INT_ADE7754	PIN_B2
		#define CF_ADE7754	PIN_B3
		#define ADE7754_CLK  PIN_D3
		#define ADE7754_DOUT PIN_D2
		#define ADE7754_DIN  PIN_D1
		
	
		#define CS5460A_CLK  PIN_G1
		#define CS5460A_DOUT PIN_G1
		#define CS5460A_DIN  PIN_G1
		#define CS5460A_CS_R PIN_G1
		#define CS5460A_CS_S PIN_G1
		#define CS5460A_CS_T PIN_G1
		#define CS5460A_RST	 PIN_G1
		
		// equates de pinos de controle do conversor AD
		#define MCP3208_CLK  PIN_D3
		#define MCP3208_DOUT PIN_D2
		#define MCP3208_DIN  PIN_D1
		#define MCP3208_CS   PIN_D0
		
		//equates de pinos controle do relógio
		#define RTC_SCLK PIN_C3
		#define RTC_IO   PIN_C5
		#define RTC_RST  PIN_C0
		
		// equates de pinos de controle da memoria flash
		#define FLASH_CLK  PIN_C3
		#define FLASH_SI   PIN_C5
		#define FLASH_SO   PIN_C4
		#define FLASH1_CE  PIN_E3
		#define FLASH2_CE  PIN_G4
		#define FLASH3_CE  PIN_G4
		#define FLASH4_CE  PIN_G4
		#define FLASH_HOLD PIN_B4
		
		
		#define alarme 		PIN_C1
		#define direcao		PIN_F7
	
	#endif

	#if (chip_cs5460a == true)
		#define led_alarme	PIN_E0
		#define led_tx		PIN_E1
		#define led_rx		PIN_E2
		#define led_tc_r	PIN_E3
		#define led_tc_s	PIN_E4
		#define led_tc_t	PIN_E7
		#define led_erro	PIN_E6
		#define led_ok		PIN_E5
		
		
		#define CS5460A_CLK  PIN_D7
		#define CS5460A_DOUT PIN_D6
		#define CS5460A_DIN  PIN_D5
		#define CS5460A_CS_R PIN_D0
		#define CS5460A_CS_S PIN_D1
		#define CS5460A_CS_T PIN_D2
		#define CS5460A_RST	 PIN_D3
		
		// equates de pinos de controle do conversor AD
		#define MCP3208_CLK  PIN_D7
		#define MCP3208_DOUT PIN_D6
		#define MCP3208_DIN  PIN_D5
		#define MCP3208_CS   PIN_D0
		
		
		//equates de pinos controle do relógio
		#define RTC_SCLK PIN_C3
		#define RTC_IO   PIN_C5
		#define RTC_RST  PIN_C0
		
		// equates de pinos de controle da memoria flash
		#define FLASH_CLK  PIN_C3
		#define FLASH_SI   PIN_C5
		#define FLASH_SO   PIN_C4
		#define FLASH1_CE  PIN_G1
		//#define FLASH2_CE  PIN_G4
		//#define FLASH_HOLD PIN_B3
		
		
		#define alarme 		PIN_C1
		#define direcao		PIN_F7
	
	#endif



	#if (sames_9904 == true)
	
		#define SA9904_CLK	PIN_G4	//clk spi sames
		#define SA9904_CS	PIN_C2 	//chip select
		#define SA9904_DOUT	PIN_G3	//MISO
		#define SA9904_DIN	PIN_G0	//MOSI
	
		#define MUX1		PIN_E1
		#define MUX2		PIN_E2
		#define MUX3		PIN_E3
		#define MUX4		PIN_E4
		
		#define ADE7754_CS	PIN_E7
		#define ADE7754_RST	PIN_E7
	
	
		#define CS5460A_CLK  PIN_E7
		#define CS5460A_DOUT PIN_E7
		#define CS5460A_DIN  PIN_E7
		#define CS5460A_CS_R PIN_E7
		#define CS5460A_CS_S PIN_E7
		#define CS5460A_CS_T PIN_E7
		#define CS5460A_RST	 PIN_E7
		
		// equates de pinos de controle do conversor AD
		#define MCP3208_CLK  PIN_E7
		#define MCP3208_DOUT PIN_E7
		#define MCP3208_DIN  PIN_E7
		#define MCP3208_CS   PIN_E7
		
		
		//equates de pinos controle do relógio
		#define RTC_SCLK PIN_C3
		#define RTC_IO   PIN_C5
		#define RTC_RST  PIN_C0
		
		// equates de pinos de controle da memoria flash
		#define FLASH_CLK  PIN_C3
		#define FLASH_SI   PIN_C5
		#define FLASH_SO   PIN_C4
		#define FLASH1_CE  PIN_E0
		#define FLASH2_CE  PIN_E7
		#define FLASH3_CE  PIN_E7
		#define FLASH4_CE  PIN_E7
		#define FLASH_HOLD PIN_E7
		
		
		#define alarme 		PIN_C1
		#define direcao		PIN_F7
	
	
	#endif
#endif


#if (st5000c_rev12 == true)
	#define xled_alarme	PIN_D0		//D4		ok
	#define xled_tx		PIN_D1		//D5		ok
	#define xled_rx		PIN_D2		//D6		ok
	#define xled_tc_r	PIN_D3		//D7		ok
	#define xled_tc_s	PIN_D4		//E4		ok
	#define xled_tc_t	PIN_D5		//E7		ok
	#define xled_erro	PIN_D6		//E6		ok
	#define xled_ok		PIN_D7		//E5
	
	short fled_alarme;
	short fled_rx;
	short fled_tx;
	short fled_tc_r;
	short fled_tc_s;
	short fled_tc_t;
	short fled_erro;
	short fled_ok;

#else
	#if (painel_6 == true)
		#define xled_alarme	PIN_E5	//D4
		#define xled_tx		PIN_E6	//D5
		#define xled_rx		PIN_E7	//D6
		#define xled_tc_r	PIN_E4	//D7
		#define xled_tc_s	PIN_D7	//E4
		#define xled_tc_t	PIN_D6	//E7
		#define xled_erro	PIN_D5	//E6
		#define xled_ok		PIN_D4	//E5
	#else
		#if (painel_12 == true)
			#if (cpu_rev1011 == true)
			
				#define xled_alarme	PIN_E5		//D4		ok
				#define xled_tx		PIN_E6		//D5		ok
				#define xled_rx		PIN_E7		//D6		ok
				#define xled_tc_r	PIN_E4		//D7		ok
				#define xled_tc_s	PIN_D7		//E4		ok
				#define xled_tc_t	PIN_D6		//E7		ok
				#define xled_erro	PIN_D5		//E6		ok
				#define xled_ok		PIN_D4		//E5
	
	
				short fled_alarme;
				short fled_rx;
				short fled_tx;
				short fled_tc_r;
				short fled_tc_s;
				short fled_tc_t;
				short fled_erro;
				short fled_ok;
	
			#else
				struct DEF_LEDS
				{
					short LEDS0 : 1;
					short LEDS1 : 1;
					short LEDS2 : 1;
					short LEDS3 : 1;
					short LEDS4 : 1;
					short LEDS5 : 1;
					short LEDS6 : 1;
					short LEDS7 : 1;
				}LEDS;
			
				#define xled_alarme	PIN_D5
				#define xled_tx		PIN_D7
				#define xled_rx		PIN_D6
				#define xled_tc_r	PIN_D4
				#define xled_tc_s	PIN_D3
				#define xled_tc_t	PIN_D2
				#define xled_erro	PIN_D1
				#define xled_ok		PIN_D0
		
				#define fled_alarme	LEDS.LEDS5
				#define fled_rx		LEDS.LEDS6
				#define fled_tx		LEDS.LEDS7
				#define fled_tc_r	LEDS.LEDS4
				#define fled_tc_s	LEDS.LEDS3
				#define fled_tc_t	LEDS.LEDS2
				#define fled_erro	LEDS.LEDS1
				#define fled_ok		LEDS.LEDS0
			#endif
			
		#else	
			#define xled_alarme	PIN_D4
			#define xled_tx		PIN_D5
			#define xled_rx		PIN_D6
			#define xled_tc_r	PIN_D7
			#define xled_tc_s	PIN_E4
			#define xled_tc_t	PIN_E7
			#define xled_erro	PIN_E6
			#define xled_ok		PIN_E5
	
			short fled_alarme;
			short fled_rx;
			short fled_tx;
			short fled_tc_r;
			short fled_tc_s;
			short fled_tc_t;
			short fled_erro;
			short fled_ok;
			
		#endif
	#endif
#endif
