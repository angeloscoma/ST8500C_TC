/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_MAIN                                                        *
; Funcao: MODULO PRINCIPAL DE CONTROLE ST9600R0   						 *
; 		Registrador Portátil de Grandezas Elétricas Trifásico            *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 01/08/2003                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/
#if (st5030t == true)
	#if (TECNOFLUX == TRUE)
		#use rs232(baud=1200, xmit=PIN_C6, rcv=PIN_C7, restart_wdt, parity=N, bits=8, errors, stream = modbus)  
	#else
		#use rs232(baud=19200, xmit=PIN_C6, rcv=PIN_C7, restart_wdt, parity=N, bits=8, errors, stream = modbus)  
	#endif
#else
	#if (st9600r == true)
		#if (teste_baud_115	== true)
			#use rs232(baud=57600, xmit=PIN_C6, rcv=PIN_C7, restart_wdt, parity=N, bits=8, errors, stream = modbus)  
		#else
			#use rs232(baud=19200, xmit=PIN_C6, rcv=PIN_C7, restart_wdt, parity=N, bits=8, errors, stream = modbus)  
		#endif
	#else
		#if ((st8610c == true) || (st8620c == true))
			#if (pci_r01 == true)
				#use rs232(baud=19200, xmit=PIN_G1, rcv=PIN_G2, restart_wdt, parity=N, bits=8, errors, stream = modbus)  
			#else
				#use rs232(baud=19200, xmit=PIN_C6, rcv=PIN_C7, restart_wdt, parity=N, bits=8, errors, stream = modbus)  
			#endif
		#else
			#use rs232(baud=19200, xmit=PIN_C6, rcv=PIN_C7, restart_wdt, parity=N, bits=8, errors, stream = modbus)  
		#endif
	#endif
#endif	

#if (st_prog == true)
	#use rs232(baud=19200, xmit=PIN_G1, rcv=PIN_G2, restart_wdt, parity=N, bits=8, errors, stream = sultech)  
#endif
#if (st8600c == true)
	#use rs232(baud = 19200, xmit=PIN_G1, rcv=PIN_G2, restart_wdt, parity=N, bits=8, errors, stream = rep)  
#endif



#ignore_warnings 202, 203, 215
//#ignore_warnings 202,203,204

#priority Timer3

/* definição de hardware = ios */

/* equates */

#define CR	13
#define LF  10

#if (__DEVICE__ == 6722)
	#define cristal	40
	#define valor_timer1  65536 - 50000			// 10 milisegundo
								// (0,010/(8/40000000)) = 50000
								// calculo: 65536-50000
	
	
	#define INTS_PER_SECOND 100
	
	#if (st5000t == 1)
		#define valor_timer3_2 64234	// para 64 amostras
		#define valor_timer3_2_60HZ 64234	// para 64 amostras
		#define valor_timer3_2_50HZ 63973	// para 64 amostras
	#elif (st5030t == true)
		#define valor_timer3_2 64234	// para 64 amostras
		#define valor_timer3_2_60HZ 6423	// para 64 amostras
		#define valor_timer3_2_50HZ 63973	// para 64 amostras
	#else
		#define valor_timer3_2 64234	// para 64 amostras
		#define valor_timer3_2_60HZ 64234	// para 64 amostras
		#define valor_timer3_2_50HZ 63973	// para 64 amostras
	#endif
								
								// 60HZ
								// calculo: 65536-(0,0002604/(8/40000000)),  = "64234" p/ 260us / 40mhz   
								// onde 0,000260 é intervalo entre ints do timer 1 
								// para 260us 64234 p/ 64 amostras por senoide em 24MHZ
								// 50HZ
								// calculo: 65536-(0,0003125/(8/40000000)),  = "63973" p/ 312,5us / 40mhz   
								// onde 0,0003125 é intervalo entre ints do timer 1 
								// para 312,5us 63973 p/ 64 amostras por senoide em 24MHZ
	
	
	
	#define valor_timer3_CHT_60HZ 64842	// este timer faz as leituras analogicas de tensao e corrente em 8 bits pelo ad interno 
								// como vão ser 120 pontos o intervalo deve ser 1/freq / 120 = 0,000138889
								// em 24mhz 65536 - (0,000138889/(8/40000000)) = 64842						
	
	#define valor_timer3_CHT_50HZ 64703	// este timer faz as leituras analogicas de tensao e corrente em 8 bits pelo ad interno 
								// como vão ser 120 pontos o intervalo deve ser 1/freq / 120 = 0,000138889
								// em 24mhz 65536 - (0,000166666/(8/40000000)) = 64703

#elif (__DEVICE__ == 4620)
	#define cristal	40
	#define valor_timer1  65536 - 50000			// 10 milisegundo
								// (0,010/(8/40000000)) = 50000
								// calculo: 65536-50000
	
	
	#define INTS_PER_SECOND 100
	
	#if (st5000t == 1)
		#define valor_timer3_2 64234	// para 64 amostras
		#define valor_timer3_2_60HZ 64234	// para 64 amostras
		#define valor_timer3_2_50HZ 63973	// para 64 amostras
	#elif (st5030t == true)
		#define valor_timer3_2 64234	// para 64 amostras
		#define valor_timer3_2_60HZ 6423	// para 64 amostras
		#define valor_timer3_2_50HZ 63973	// para 64 amostras
	#else
		#define valor_timer3_2 64234	// para 64 amostras
		#define valor_timer3_2_60HZ 64234	// para 64 amostras
		#define valor_timer3_2_50HZ 63973	// para 64 amostras
	#endif
								
								// 60HZ
								// calculo: 65536-(0,0002604/(8/40000000)),  = "64234" p/ 260us / 40mhz   
								// onde 0,000260 é intervalo entre ints do timer 1 
								// para 260us 64234 p/ 64 amostras por senoide em 24MHZ
								// 50HZ
								// calculo: 65536-(0,0003125/(8/40000000)),  = "63973" p/ 312,5us / 40mhz   
								// onde 0,0003125 é intervalo entre ints do timer 1 
								// para 312,5us 63973 p/ 64 amostras por senoide em 24MHZ
	
	
	
	#define valor_timer3_CHT_60HZ 64842	// este timer faz as leituras analogicas de tensao e corrente em 8 bits pelo ad interno 
								// como vão ser 120 pontos o intervalo deve ser 1/freq / 120 = 0,000138889
								// em 24mhz 65536 - (0,000138889/(8/40000000)) = 64842						
	
	#define valor_timer3_CHT_50HZ 64703	// este timer faz as leituras analogicas de tensao e corrente em 8 bits pelo ad interno 
								// como vão ser 120 pontos o intervalo deve ser 1/freq / 120 = 0,000138889
								// em 24mhz 65536 - (0,000166666/(8/40000000)) = 64703

#else
	#define INTS_PER_SECOND 100
	
	#if (st5000t == 1)
		#define cristal	24
		#define valor_timer1  65536 - 30000			// 10 milisegundo
									// (0,010/(8/24000000)) = 3000
									// calculo: 65536-30000
		#define valor_timer3_2 64790	// para 64 amostras
		#define valor_timer3_2_60HZ 64790	// para 64 amostras
		#define valor_timer3_2_50HZ 64598	// para 64 amostras
								// 60HZ
								// calculo: 65536-(0,0002604/(8/24000000)),  = "64756" p/ 260us / 24mhz   
								// onde 0,000260 é intervalo entre ints do timer 1 
								// para 260us 64756 p/ 64 amostras por senoide em 24MHZ
								// 50HZ
								// calculo: 65536-(0,0003125/(8/24000000)),  = "64756" p/ 312,5us / 24mhz   
								// onde 0,0003125 é intervalo entre ints do timer 1 
								// para 312,5us 64598 p/ 64 amostras por senoide em 24MHZ
	
	
	
		#define valor_timer3_CHT_60HZ 65119 + 23	
								// este timer faz as leituras analogicas de tensao e corrente em 8 bits pelo ad interno 
								// como vão ser 120 pontos o intervalo deve ser 1/freq / 120 = 0,000138889
								// em 24mhz 65536 - (0,000138889/(8/24000000)) = 65119						;64984
	
		#define valor_timer3_CHT_50HZ 65036 + 23
								// este timer faz as leituras analogicas de tensao e corrente em 8 bits pelo ad interno 
								// como vão ser 120 pontos o intervalo deve ser 1/freq / 120 = 0,000138889
								// em 24mhz 65536 - (0,000166666/(8/24000000)) = 65036						;64984
	#elif (st5030t == true)
		#if (TECNOFLUX == TRUE)
			#define cristal	20
			#define valor_timer1  65536 - 25000			// 10 milisegundo
									// (0,010/(8/20000000)) = 25000
									// calculo: 65536-25000
			#define valor_timer3_2 64885	// para 64 amostras
			#define valor_timer3_2_60HZ 64885	// para 64 amostras
			#define valor_timer3_2_50HZ 64754	// para 64 amostras
								// 60HZ
								// calculo: 65536-(0,0002604/(8/20000000)),  = "64885" p/ 260us / 20mhz   
								// onde 0,000260 é intervalo entre ints do timer 1 
								// para 260us 64885 p/ 64 amostras por senoide em 20MHZ
								// 50HZ
								// calculo: 65536-(0,0003125/(8/20000000)),  = "64754" p/ 312,5us / 20mhz   
								// onde 0,0003125 é intervalo entre ints do timer 1 
								// para 312,5us 64754 p/ 64 amostras por senoide em 20MHZ
	
	
			
			#define valor_timer3_CHT_60HZ 65189 + 23	
								// este timer faz as leituras analogicas de tensao e corrente em 8 bits pelo ad interno 
								// como vão ser 120 pontos o intervalo deve ser 1/freq / 120 = 0,000138889
								// em 20mhz 65536 - (0,000138889/(8/20000000)) = 65189						;64984
	
			#define valor_timer3_CHT_50HZ 65119 + 23	
								// este timer faz as leituras analogicas de tensao e corrente em 8 bits pelo ad interno 
								// como vão ser 120 pontos o intervalo deve ser 1/freq / 120 = 0,000138889
								// em 20mhz 65536 - (0,000166666/(8/20000000)) = 65119						;64984
		#else
			#define cristal	24
			#define valor_timer1  65536 - 30000			// 10 milisegundo
									// (0,010/(8/24000000)) = 3000
									// calculo: 65536-30000
			#define valor_timer3_2 64790	// para 64 amostras
			#define valor_timer3_2_60HZ 64790	// para 64 amostras
			#define valor_timer3_2_50HZ 64598	// para 64 amostras
								// 60HZ
								// calculo: 65536-(0,0002604/(8/24000000)),  = "64756" p/ 260us / 24mhz   
								// onde 0,000260 é intervalo entre ints do timer 1 
								// para 260us 64756 p/ 64 amostras por senoide em 24MHZ
								// 50HZ
								// calculo: 65536-(0,0003125/(8/24000000)),  = "64756" p/ 312,5us / 24mhz   
								// onde 0,0003125 é intervalo entre ints do timer 1 
								// para 312,5us 64598 p/ 64 amostras por senoide em 24MHZ
	
	
	
		#define valor_timer3_CHT_60HZ 65119 + 23	
								// este timer faz as leituras analogicas de tensao e corrente em 8 bits pelo ad interno 
								// como vão ser 120 pontos o intervalo deve ser 1/freq / 120 = 0,000138889
								// em 24mhz 65536 - (0,000138889/(8/24000000)) = 65119						;64984
	
		#define valor_timer3_CHT_50HZ 65036 + 23	
								// este timer faz as leituras analogicas de tensao e corrente em 8 bits pelo ad interno 
								// como vão ser 120 pontos o intervalo deve ser 1/freq / 120 = 0,000138889
								// em 24mhz 65536 - (0,000166666/(8/24000000)) = 65036						;64984
			
		#endif
	#else
		#define cristal	24
		#define valor_timer1  65536 - 30000			// 10 milisegundo
									// (0,010/(8/24000000)) = 3000
									// calculo: 65536-30000
		#define valor_timer3_2 64790	// para 64 amostras
		#define valor_timer3_2_60HZ 64790	// para 64 amostras
		#define valor_timer3_2_50HZ 64598	// para 64 amostras
		
								// 60HZ
								// calculo: 65536-(0,0002604/(8/24000000)),  = "64756" p/ 260us / 24mhz   
								// onde 0,000260 é intervalo entre ints do timer 1 
								// para 260us 64756 p/ 64 amostras por senoide em 24MHZ
								// 50HZ
								// calculo: 65536-(0,0003125/(8/24000000)),  = "64756" p/ 312,5us / 24mhz   
								// onde 0,0003125 é intervalo entre ints do timer 1 
								// para 312,5us 64598 p/ 64 amostras por senoide em 24MHZ
	
	
	
		#define valor_timer3_CHT_60HZ 65119 + 23	
								// este timer faz as leituras analogicas de tensao e corrente em 8 bits pelo ad interno 
								// como vão ser 120 pontos o intervalo deve ser 1/freq / 120 = 0,000138889
								// em 24mhz 65536 - (0,000138889/(8/24000000)) = 65119						;64984
	
		#define valor_timer3_CHT_50HZ 65036 + 23	
								// este timer faz as leituras analogicas de tensao e corrente em 8 bits pelo ad interno 
								// como vão ser 120 pontos o intervalo deve ser 1/freq / 120 = 0,000138889
								// em 24mhz 65536 - (0,000166666/(8/24000000)) = 65036						;64984
	#endif
#endif



// definicoes para inclusao de modulos para testes 
#define teste_cht		false
#define com_modbus		true
#define com_alarme		true
#define feira			false
#define teste_consumo	false
#define fixar_parametro	false
#define teste_regs		false


#if (st5x == true)
	#if (sames_9904 == true)
		#use standard_io (D)
		#use fast_io (E)
	#else
//		#use stardard_io (D)
//		#use stardard_io (E)
	#endif
#endif
#if (st94 == true)
	#use fast_io (D)
	#use fast_io (E)
#endif
#if (st9600r == true)
	#use fast_io (D)
	#use fast_io (G)
	#use fast_io (E)
#endif
#if (st9100r == true)
	#use fast_io (D)
	#use fast_io (G)
	#use fast_io (E)
#endif
#if (st_prog == true))
	#use fast_io (G)
	#use fast_io (E)
#endif
#if (st8610c == true)
	#use fast_io (D)
//	#use fast_io (C)
#endif
#if (st8600c == true)
	#use fast_io (D)
//use fast_io (E)
#endif
#if (st8620c == true)
	#use fast_io (D)
//use fast_io (E)
#endif


// CONTROLE DE REVISOES 



/* DECLARACAO DE FUNCOES */
void main(void);
void pulsa_wdt(void);
void trata_virada_500ms(void);
void trata_virada_750ms(void);
void trata_virada_segundo(void);
void trata_virada_minuto(void);
void trata_virada_dia(void);
void trata_virada_mes(void);
void trace(char);

#define debugar	true

// Includes 
#include <math.h>
#include <stdio.h>

#include "st_flag.c"
#include "st_vars.c"
#if (st9600r == true)
	#include "st96port.c"
#endif	
#if (st_prog == true)
	#include "stprog_port.c"
#endif
#if (st9100r == true)
	#include "st91port.c"
#endif	
#if (st5300T == true)
	#include "st53port.c"
#elif (st5330T == true)
	#include "st53port.c"
#endif	
#if (st5000T == true) 
	#include "st50port.c"
#elif (st5030T == true)
	#include "st50port.c"
#endif	
#if (ST9400R == true)
	#include "st94port.c"
#endif	
#if (ST9430R == true)
	#include "st94port.c"
#elif (st8610c == true)
	#include "st8610port.c"
#elif (st8620c == true)
	#include "st8620port.c"
#elif (st8600c == true)
	#include "st8600port.c"
#endif	

#include "st_e2p.h"
#include "st_e2p.c"
#include "st_prot.c"	//prototipos de funcoes
#include "st_tabs.c"
#if (com_cht == true)
//	#include "seno_120.c"
#endif
#include "st_mens.c"
#if (st9600r == true)
	#include "st9600r_mens.c"
#endif
#if (st8610c == true)
	#include "st8610_mens.c"
#endif
#if (st8620c == true)
	#include "st8620_mens.c"
#endif
#if (st8600c == true)
	#include "st8600_mens.c"
#endif
#if (st5x == true)
	#include "st50_led.c"
#endif
#if (chip_cs5460a == true)
	#include "cs5460a.c"
#endif	
#if (ad_microchip == true)
	#include "mcp3208.c"
#endif
#if (ade7754 == true)
	#include "ade7754.c"
	#include "spi_ade7754.c"
#endif
#if (sames_9904 == true)
	#include "sa9904.c"
#endif
#if (com_relogio == true)
	#include "ds1302.c"
#endif
#include "st_conf.c"
#include "st_roti.c"
#include "st_rota.c"
#include "st_deci.c"
#include "st_vali.c"
#if (com_regs == true)
	#include "sst25vfxxx.c"
#endif	
#if (com_menu == true)
	#if (st9600r == true)
		#include "lcd_16x4.c"
	#elif (st9100r == true) 
		#include "lcd_16x4.c"
	#elif (st8620c == true) 
		#include "lcd_16x4.c"
	#elif (st8600c == true) 
		#include "lcd_16x4.c"
	#elif (st_prog == true)
		#include "lcd_16x4.c"
	#endif	
#endif
#if (com_regs == true)
	#include "st_regs.c"
	#include "st_ocor.c"
	#if (com_cht == true)
		#include "st_rcht.c"
	#endif		
#endif
#if (com_cht == true)
	#if (ade7754 == true)
		#include "st_ccht_7754.c"
	#else
		#include "st_ccht.c"
	#endif
#endif

#if (st_prog == true)
	#include "stprog_deci.c"
#endif
#if (CONTROLADOR == true)
	#include "st8610_deci.c"
#endif	
#if (com_menu == true)
	#if (st9100r == true)
		#include "st91menu.c"
	#elif (st94 == true)
		#include "st94menu.c"
	#elif (st_prog == true)
		#include "stprog_menu.c"
	#elif (st8610c == true)
		#include "st8610_menu.c"
	#elif (st8620c == true)
		#include "st8610_menu.c"
	#elif (st8600c == true)
		#include "st8610_menu.c"
	#else
		#include "st_menu.c"
	#endif
#endif
#if (chip_cs5460a == true)
	#if (st9600r == true)
		#include "st96ints.c"
		#include "st96calc.c"
		#include "st96pots.c"
	#endif
	#if (st5x == true)
		#include "st50ints.c"
		#include "st50calc.c"
		#include "st50addr.c"
		#include "st50pots.c"
	#endif
#elif (ad_microchip == true)
	#if (st9100r == true)
		#include "st91ints.c"
		#include "st91calc.c"
		#include "st91pots.c"
	#else
		#include "st_ints.c"
		#include "st_calc.c"
		#include "st_pots.c"
		#if (st5x == true)
			#include "st50addr.c"
		#endif
	#endif
#elif (ade7754 == true)
	#if (st9100r == true)
		#include "st91_ints_7754.c"
		#include "st91calc_7754.c"
		#include "st91pots.c"
	#else
		#include "st_ints_7754.c"
		#include "st_calc_7754.c"
		#include "st_pots_7754.c"
		#if (st5x == true)
			#include "st50addr.c"
		#endif
	#endif
#elif (sames_9904 == true)
	#include "st_ints.c"
	#include "st_calc_sames.c"
	#include "st_pots_sames.c"
#else
	#include "st_ints.c"
	#include "st_calc.c"
	#include "st_pots.c"
#endif

#include "tensao_ff.c"
#include "tensao_alta.c"
#if (monofasico == false)
	#include "tensao_tri.c"
#endif
#include "kvar_req.c"
#include "calcfreq.c"
#if (monofasico == false)
	#include "calcfptotal.c"
#endif


#if (com_consumo == true)
	#include "st_cons.c"
#endif
#if (funcao_505 == true)
	#include "st_505.c"
#endif
#if (com_modbus == true)
	#include "st_modb.c"
#endif	


#if (st_prog == true)
	#zero_ram
#endif
void main(void)
{

	disable_interrupts(GLOBAL);

	#if (st5300t == true) 
		//			 76543210
		set_tris_b(0b11100111);
	//	set_tris_c(0b10100000);
		set_tris_d(0b00000100);
		set_tris_e(0x11110000);
		set_tris_f(0b01111111);
		set_tris_g(0b11111000);
	#elif (st5330t == true)
		//			 76543210
		set_tris_b(0b11100111);
		set_tris_c(0b10100000);
		set_tris_d(0b00000100);
		set_tris_e(0x11110000);
		set_tris_f(0b01111111);
		set_tris_g(0b11111000);
	#elif (st8610c == 1)
		//			 76543210
		set_tris_a(0b11101111);
		set_tris_b(0b11100011);
//		set_tris_c(0b10010000);
		set_tris_d(0b00000000);
		set_tris_e(0b00000011);
	#elif (st8620c == 1)
		//			 76543210
		set_tris_a(0b11111111);
		set_tris_b(0b11111111);//		set_tris_b(0b11100111);
		set_tris_c(0b10010000);
		set_tris_d(0b00000000);
		set_tris_e(0b00000011);
		set_tris_g(0b11111110);
	#elif (st8600c == 1)
		//			 76543210
		set_tris_a(0b11111111);
		set_tris_b(0b11101111);
		set_tris_c(0b10100000);
		set_tris_d(0b00000000);
		set_tris_e(0b00000011);
		set_tris_g(0b11111110);
	#elif (st_prog == 1)
		//			 76543210
		set_tris_b(0b11111111);
		set_tris_c(0b10100000);
		set_tris_d(0b11111111);
		set_tris_e(0b00000000);
		set_tris_f(0b01111011);
		set_tris_g(0b11111100);
		output_e(255);
		output_g(255);
	#elif (st5x == true)
		//		    	 76543210
		#if (ad_microchip == true)
			set_tris_b(0b11111111);
			set_tris_c(0b10010000);
			set_tris_d(0b00000100);
			set_tris_e(0b00000000);
			set_tris_f(0b01111111);
			set_tris_g(0b11111110);
			output_high(ADE7754_CS);
			output_high(ADE7754_RST);
			output_high(MCP3208_CS);
	
		#elif (ade7754 == true))
			set_tris_b(0b11111111);
			set_tris_c(0b10010000);
			set_tris_d(0b00000100);
			set_tris_e(0b00000000);
			set_tris_f(0b01111111);
			set_tris_g(0b11100110);
			output_high(ADE7754_CS);
			output_high(ADE7754_RST);
			output_high(MCP3208_CS);
		#elif (sames_9904 == true)
			set_tris_b(0b11111111);
			set_tris_c(0b10010000);
			set_tris_d(0b11111111);
			set_tris_e(0b00000000);
			set_tris_f(0b01111111);
			set_tris_g(0b11111110);
			output_low(SA9904_CS); 	//= OFF	//drop chip select
		#else
			set_tris_b(0b11111111);
			set_tris_c(0b10010000);
			set_tris_d(0b11111111);
			set_tris_e(0b00000000);
			set_tris_f(0b11111111);
			set_tris_g(0b11101110);
		#endif
	#elif (st94 == true)
		//			 76543210
		set_tris_b(0b01101111);
//		set_tris_c(0b10010000);
		set_tris_d(0b00000000);
		set_tris_e(0b00000001);
		set_tris_f(0b00101111);
		set_tris_g(0b11100000);
		output_high(MCP3208_CS);
		output_high(MCP3208_CLK);
		output_high(MCP3208_CS);
		output_high(MCP3208_DOUT);
	#elif (st9600r == true)
		//			 76543210
		set_tris_b(0b01101111);
	//	set_tris_c(0b10100000);
		set_tris_d(0b00000000);
		set_tris_e(0b00000001);
		set_tris_f(0b00101111);
		set_tris_g(0b11100000);
	#elif (st9100r == 1)
		//			 76543210
		set_tris_b(0b11101111);
	//	set_tris_c(0b10100000);
		set_tris_d(0b00000000);
		set_tris_e(0b00000001);
		set_tris_f(0b00101111);
		set_tris_g(0b11100000);
	#endif	


	#if (chip_cs5460a == true)
		output_low(CS5460A_RST);
		output_high(CS5460A_CS_R);
		output_high(CS5460A_CS_S);
		output_high(CS5460A_CS_T);
	#else
		output_high(CS5460A_CS_R);
		output_high(CS5460A_CS_S);
		output_high(CS5460A_CS_T);
	#endif	
	#if (st_prog == true)
		saida1 = read_byte(ee_saida1);
		saida2 = read_byte(ee_saida2);
		wr_saida1();
		wr_saida2();
		for (aux_b1 = 0; aux_b1 < (NRO_MAXIMO_BANCOS_CAPACITOR - 1); aux_b1++)
			{
			banco_acionado[aux_b1] = 0;
			}
		
	#endif
	#if (CONTROLADOR == true)
		write_byte(ee_saida2, 0);
		write_byte(ee_saida3, 0);
		SAIDA2 = 0;
		SAIDA3 = 0;
	#endif
	#if (com_485 == true)
		output_low(direcao);
	#endif	
   	output_low(MCP3208_CLK);

/* define funcionamento do temporizador 1 */
	setup_timer_1(T1_INTERNAL|T1_DIV_BY_2);
	set_timer1(valor_timer1);
	enable_interrupts(INT_TIMER1);

	setup_timer_3(T1_INTERNAL|T3_DIV_BY_2);
	set_timer3(valor_timer3_2_60HZ);
	enable_interrupts(INT_TIMER3);


/* define funcionamento da uart */
	baud_rate =  read_word(ee_baud_rate);
	#if (st_prog == true)
		baud_rate = 19200;
		write_word(ee_baud_rate, 19200);
	#endif
	#if (CONTROLADOR == true)
		baud_rate = 19200;
		write_word(ee_baud_rate, 19200);
	#endif
	#if (st9600r == true)
		#if (teste_baud_115	== true)
	  		set_uart_speed (57600, modbus);
		#endif	
	#endif	
	seta_baud_rate();
	
	#if (st8610c == true) || (st8620c == true)
		#if (pci_r01 == true)
			enable_interrupts(INT_RDA2);
		#else
			enable_interrupts(INT_RDA);
		#endif
	#else
		enable_interrupts(INT_RDA);
	#endif		
	#if (st_prog == true)
		enable_interrupts(INT_RDA2);
	#endif
	
	#if (ade7754 == true)
		ext_int_edge(2,H_TO_L);
		enable_interrupts(INT_EXT2);
	
		ext_int_edge(3,H_TO_L);
		enable_interrupts(INT_EXT3);
	#endif
	#if (CONTROLADOR == true)
		ext_int_edge(0,H_TO_L);
		enable_interrupts(INT_EXT);
		ext_int_edge(1,H_TO_L);
		enable_interrupts(INT_EXT1);
	#endif

	#if (ad_microchip == true)
		#if ((st94 == true) && (rev_11 == false))
			ext_int_edge(2,H_TO_L);
			enable_interrupts(INT_EXT2);
		#else
			ext_int_edge(0,H_TO_L);
			enable_interrupts(INT_EXT);
		#endif
		ext_int_edge(1,H_TO_L);
		enable_interrupts(INT_EXT1);
	#endif
	#if (chip_cs5460a == true)
		ext_int_edge(2,H_TO_L);
		enable_interrupts(INT_EXT2);
	//	ext_int_edge(3,H_TO_L);
	//	enable_interrupts(INT_EXT3);
	#endif
	#if (SAMES_9904 == true)
		ext_int_edge(0,L_TO_H);
		enable_interrupts(INT_EXT);
		ext_int_edge(1,L_TO_H);
		enable_interrupts(INT_EXT1);
		ext_int_edge(2,L_TO_H);
		enable_interrupts(INT_EXT2);
	#endif
	
	#if (com_display == true)
		#if (st8620c == true)
			setup_ccp1(CCP_OFF);
		#else
		    setup_timer_2(T2_DIV_BY_4, 127, 1);
			setup_ccp1(ccp_pwm);
			set_pwm1_duty(0);	
		#endif
	#else
		setup_ccp1(CCP_OFF);
	#endif


/* define funcionamento da watchdog */
	setup_wdt(WDT_ON);
	restart_wdt();

	#if (st5x == true)
	//	setup_adc_ports(ANALOG_AN0_TO_AN9 | VSS_VDD);
		setup_adc_ports(ALL_ANALOG | VSS_VDD);
	#elif (st8610c == true)
		setup_adc_ports(AN0_TO_AN4 | VSS_VDD);
	#elif (st8620c == true)
		setup_adc_ports(AN0_TO_AN4 | VSS_VDD);
	#elif (st8600c == true)
//		setup_adc_ports(AN0_TO_AN8 | VSS_VDD);
		setup_adc_ports(ALL_ANALOG | VSS_VDD);
	#else
		setup_adc_ports(ANALOG_AN0_TO_AN7 | VSS_VDD);
	#endif	
	setup_adc(ADC_CLOCK_INTERNAL);

	enable_interrupts(GLOBAL);

	#if (st5030t == 1))
		#if (teste_painel == true)
			tudodenovo:
				output_high(led_alarme);
				output_high(led_tx);
				output_high(led_rx);
				output_high(led_tc_r);
				output_high(led_tc_s);
				output_high(led_tc_t);
				output_high(led_erro);
				output_high(led_ok);
				
				output_low(led_alarme);
				delay_ms(250);
				output_high(led_alarme);
				output_low(led_tx);
				delay_ms(250);
				output_high(led_tx);
				output_low(led_rx);
				delay_ms(250);
				output_high(led_rx);
				output_low(led_tc_r);
				delay_ms(250);
				output_high(led_tc_r);
				output_low(led_tc_s);
				delay_ms(250);
				output_high(led_tc_s);
				output_low(led_tc_t);
				delay_ms(250);
				output_high(led_tc_t);
				output_low(led_erro);
				delay_ms(250);
				output_high(led_erro);
				delay_ms(250);
				output_low(led_ok);
				delay_ms(250);
				output_high(led_ok);
				goto tudodenovo;
		#endif
	#endif
		

	#if (com_display == true)
		#if ((st9600r == true) || (ST8600C == true) || (ST8620C == true) || (st_prog == true))
			{
			inic_dis();
			limpa_display();
			}
		#endif
		#if (st94 == true)
			{
			limpa_linha(1);
			limpa_linha(2);
			limpa_linha(3);
			}
		#endif
		#if (st8610c == true)
			{
			limpa_linha(1);
			}
		#endif
	#endif


//	#if ((st5x == true) | (st94 == true) | (st_prog == true) | (controlador == true))
			#if (com_485 == true)
				output_high(direcao);
				delay_ms(1);
			#endif
			aux_b1 = restart_cause();
			switch ( aux_b1 )
			   {
		      	case WDT_TIMEOUT:
			    	{
		         	fprintf(modbus,"%d - Watchdog Mordeu!!!!\r\n", aux_b1);
		         	break;
		    	  	}
				case NORMAL_POWER_UP:
			      	{
		         	fprintf(modbus,"%d - Normal power up!!!!\r\n", aux_b1);
		         	break;
		    	  	}	
				case MCLR_FROM_SLEEP:
			      	{
		         	fprintf(modbus,"%d - MCLR_FROM_SLEEP!!!!\r\n", aux_b1);
		         	break;
		    	  	}	
				case BROWNOUT_RESTART:
			      	{
		         	fprintf(modbus,"%d - BROWNOUT_RESTART!!!!\r\n", aux_b1);
		         	break;
		    	  	}	
		      	default:
		      	  	{
		         	fprintf(modbus,"%d -Anormal Reset!!!!\r\n", aux_b1);
		         	break;
			      	}
		   		}
			if (var_mem != 67)
				{
				fprintf(modbus,"\r\nReset Frio!!!!\r\n");
				}
			else
				{
				fprintf(modbus,"\r\nReset Quente!!!!\r\n");
				}
			fprintf(modbus,"%u:%u:%u  %u,%u",hora,minuto,segundo,var_mem,passo_main);
			fprintf(modbus,"\r\n");
			#if (st5x == true)
				#if (TECNOFLUX == TRUE)
					endereco_nro_serie = ((read_byte(ee_nro_3) -'0') * 10) + (read_byte(ee_nro_4) - '0');
					fprintf(modbus,"%u:%c:%c",(100+endereco_nro_serie),read_byte(ee_nro_3),read_byte(ee_nro_4));
					fprintf(modbus,"\r\n");
				#endif
			#endif
			#if (com_485 == true)
				output_low(direcao);
				delay_ms(1);
			#endif
//	#endif

	#if (com_regs == true)
	/* inicializa o canal SPI */
   		output_low(FLASH_SI);
	   	output_low(FLASH_CLK);
   		output_high(FLASH1_CE);
		#if ((st9600r == true) | (st9100r == true) | (st_prog == true))
	 	  	output_high(FLASH2_CE);
	   		output_high(FLASH3_CE);
		   	output_high(FLASH4_CE);
		#endif   	
	   	aux_b1 = input(FLASH_SO);

		setup_spi(SPI_MASTER | SPI_L_TO_H | SPI_CLK_DIV_16);
	
		FLASH_CE_High();
		Unhold();
	#endif


	#if (st5x == true)
		fled_ok = 1;
		fled_tx = 1;
		fled_rx = 1;
		fled_alarme = 1;
		fled_tc_r = 1;
		fled_tc_s = 1;
		fled_tc_t = 1;
	#endif
	#if (controlador == true)
		led_ok = ~led_ok;
		led_tx = 1;
		led_rx = 1;
	#endif


	#if (chip_cs5460a == true)
	 	reset_cs5460();
		inic_cs5640();
	#endif

	write_byte(ee_passo_main, passo_main);

	trace(0);

	le_config();	// Le configuracoes
	inicializa_variaveis();	//inicializa variaveis
	inicializa_programa();

	#if (com_menu == true) 
		mensagem_inicial();
	#endif

	#if (chip_cs5460a == true)
		config_cs5460();
	#endif

	#if (ade7754 == true)
		acao_ade7754 = 0;
	#endif

	#if (com_relogio == true)
		le_calend();	
	#endif


//	delay_ms(1000);

	#if (com_relogio == true)
		rtc_init();		// inicializa RTC ds1302
		delay_ms(100);
		rtc_init();		// inicializa RTC ds1302
		delay_ms(100);
		rtc_get_date();
		rtc_get_time();
	#else
		rtc_get_e2p();	
		ajuste_relogio = 1;
	#endif

	if (var_mem != 67)
		{
		#if (com_regs == true)
			le_hardware();
			grava_ocorrencias(reg_reset);
		#endif		
		var_mem = 67;
		}

	#if (com_regs == true)
		wr_falta_energia();
		inicializa_regs();
		prox_grava = (int32)(aux_l2 + intervalo_reg);
	#endif
	cont0 = INTS_PER_SECOND;


//	delay_ms(1000);

	valida_programa();

	inic_rx();

	#if (com_menu == true)
		#if (com_regs == true)
			#if (portatil == true)
				calcula_autonomia();
			#endif
			exibe_status();
		#endif
	#endif	

	#if (com_menu == true)
		reinicializa_menus();
	#endif

#if (com_relogio == false)
	ajuste_relogio = 1;
#endif

	output_high(back);		//modelo de placa com backlight ligado sem pwm


	// ****************************************************************************************
	//  LOOP PRINCIPAL	
	//*****************************************************************************************
	while(TRUE) 
		{
	
		pulsa_wdt();

		#if (com_modbus == true)
			trata_modbus();
		#endif

		#if (com_menu == true)
			teclado();
		#endif		


		#if (controlador == true)
			#if (st8610c == true)
				leds(0);
			#endif
			#if (disp_lcd == true)
				trata_saidas();
			#endif
		#endif


		passo_main++;
		switch(passo_main)
			{
			case 1:
				{
				if (virou_500ms == 1)
					{
					trata_virada_500ms();
					}
				break;
				}
			case 2:
				{
				if (virouseg == 1)
					{
					trata_virada_segundo();
					}
				break;	
				}
			case 3:
				{
				if (viroumin == 1)
					{
					trata_virada_minuto();
					}
				break;	
				}

// C U I D A D O,  ALTERAR ESTA POSIÇÃO CASO SEJA CRIADO + OPÇÕES NO CASE DA PASSO_MAIN
#define LIMITE_PASSO_MAIN 3
//
			default:
				{
				if (passo_main > LIMITE_PASSO_MAIN)
					{
					passo_main = 0;
					}
				}
			}
		}
}


void pulsa_wdt(void)
{
	if (morder == 1)	
		{
		morder = 0;
		restart_wdt();
		}
}


void trata_virada_500ms(void)
{

	virou_500ms = 0;


}

void trata_virada_750ms(void)
{
	
	virou_750ms = 0;
}



void trata_virada_segundo(void)
{
	

	#if (com_relogio == false)
		le_calend_int();
	#endif


	nro_conta_media = conta_media;
	conta_media = 0;

	if (retardo_alarmes != 0)
		{
		retardo_alarmes--;
		}

	ponto_segundo = ~ponto_segundo;


	#if (com_menu == true)
		trata_time_out_menus();
		#if (st_prog == false)
			{
			if (menu1 == 0)
				{
				exibe_status();
				}
			if (time_out_exibe_erro != 0)
				{
				time_out_exibe_erro--;
				}
			}
		#endif
	#endif
		
	
	#if (com_cht == true)
		lendo_cht = false;
	#endif	



	#if (controlador == true)
		trata_tempos_aciona_repouso();
		trata_segundeiro();
		led_rx = 0;
		led_tx = 0;
	#endif

	virouseg = 0;

	if ((segundo == 30) || (segundo == 0))
		{
		saida2++;
		saida3++;
		}

}	


void trata_virada_minuto(void)
{
	pisca_minuto = ~pisca_minuto;


	#if (com_display == true)
		#if (st8620c == false)
	    	setup_timer_2(T2_DIV_BY_4, 127, 1);
			setup_ccp1(ccp_pwm);
		#endif
	#endif


	#if (fixar_parametro ==	true)
		fixa_parametros();
	#endif
	
	

	viroumin=0;
}






void trace(char aux_trace)
{
#if ( debugar == true)
	if (aux_trace != 0)
		{
		#if (com_485 == true)
			output_high(direcao);
			delay_ms(1);
		#endif
			printf("[%u,%u,%u]\r\n",var_mem,passo_main, aux_trace);
		#if (com_485 == true)
			delay_ms(1);
			output_low(direcao);
		#endif
		}
#endif
}



/* Fim st_main */
