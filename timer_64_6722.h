#if (cristal_10MHz == true)
	#define cristal	40
	#define valor_timer1  65536 - 50000			// 10 milisegundo
												// (0,010/(8/40000000)) = 50000
												// calculo: 65536-50000
	#define INTS_PER_SECOND 100
			
	#define valor_timer3_2 64234				// para 64 amostras
	#define valor_timer3_2_60HZ 64234			// para 64 amostras
	#define valor_timer3_2_50HZ 63973			// para 64 amostras
												// 60HZ
												// calculo: 65536-(0,0002604/(8/40000000)),  = "64234" p/ 260us / 40mhz   
												// onde 0,000260us eh intervalo entre ints do timer 1 
												// para 260us 64234 p/ 64 amostras por senoide em 24MHZ
												// 50HZ
												// calculo: 65536-(0,0003125/(8/40000000)),  = "63973" p/ 312,5us / 40mhz   
												// onde 0,0003125 eh intervalo entre ints do timer 1 
												// para 312,5us 63973 p/ 64 amostras por senoide em 40MHZ

	#define valor_timer3_CHT_60HZ 64842 + 46	// este timer faz as leituras analogicas de tensao e corrente em 8 bits pelo ad interno 
												// como vao ser 120 pontos o intervalo deve ser 1/freq / 120 = 0,000138889
												// em 40mhz 65536 - (0,000138889/(8/40000000)) = 64842						
			
	#define valor_timer3_CHT_50HZ 64703	+ 46	// este timer faz as leituras analogicas de tensao e corrente em 8 bits pelo ad interno 
												// como vao ser 120 pontos o intervalo deve ser 1/freq / 120 = 0,000138889
												// em 40mhz 65536 - (0,000166666/(8/40000000)) = 64703

#else
	#define cristal	24
		
	#define INTS_PER_SECOND 100
		
	#define valor_timer1  65536 - 30000			// 10 milisegundo
												// (0,010/(8/24000000)) = 30000
												// calculo: 65536-30000
	#define valor_timer3_2 64790				// para 64 amostras
	#define valor_timer3_2_60HZ 64790			// para 64 amostras
	#define valor_timer3_2_50HZ 64598			// para 64 amostras
		
												// 60HZ
												// calculo: 65536-(0,0002604/(8/24000000)),  = "64756" p/ 260us / 24mhz   
												// onde 0,000260 eh intervalo entre ints do timer 1 
												// para 260us 64756 p/ 64 amostras por senoide em 24MHZ
												// 50HZ
												// calculo: 65536-(0,0003125/(8/24000000)),  = "64756" p/ 312,5us / 24mhz   
												// onde 0,0003125 eh intervalo entre ints do timer 1 
												// para 312,5us 64598 p/ 64 amostras por senoide em 24MHZ
	
	
	
	#define valor_timer3_CHT_60HZ 65119 + 23	
												// este timer faz as leituras analogicas de tensao e corrente em 8 bits pelo ad interno 
												// como vao ser 120 pontos o intervalo deve ser 1/freq / 120 = 0,000138889
												// em 24mhz 65536 - (0,000138889/(8/24000000)) = 65119						;64984
	
	#define valor_timer3_CHT_50HZ 65036 + 23	
												// este timer faz as leituras analogicas de tensao e corrente em 8 bits pelo ad interno 
												// como vao ser 120 pontos o intervalo deve ser 1/freq / 120 = 0,000138889
												// em 24mhz 65536 - (0,000166666/(8/24000000)) = 65036						;64984

#endif
