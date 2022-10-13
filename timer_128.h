							// PROGRAMAÇÃO PARA 128 AMOSTRAS
		#define cristal	24
		#define valor_timer1  65536 - 30000			// 10 milisegundo
									// (0,010/(8/24000000)) = 3000
									// calculo: 65536-30000
		#define valor_timer3_2 65145	// para 128 amostras
		#define valor_timer3_2_60HZ 65145	// para 128 amostras
		#define valor_timer3_2_50HZ 65066	// para 128 amostras
			
									// 60HZ
									// calculo: 65536-(0,0001302/(8/24000000)),  = "65145" p/ 130,2us / 24mhz   
									// onde 0,0001302 é intervalo entre ints do timer 1 
									// para 130,2us 65145 p/ 128 amostras por senoide em 24MHZ
									// 50HZ
									// calculo: 65536-(0,0001563/(8/24000000)),  = "65066" p/ 312,5us / 24mhz   
									// onde 0,0001563 é intervalo entre ints do timer 1 
									// para 156,3us 65066 p/ 128 amostras por senoide em 24MHZ
		
		
		
		#define valor_timer3_CHT_60HZ 65119 + 23	
									// este timer faz as leituras analogicas de tensao e corrente em 8 bits pelo ad interno 
									// como vão ser 120 pontos o intervalo deve ser 1/freq / 120 = 0,000138889
									// em 24mhz 65536 - (0,000138889/(8/24000000)) = 65119						;64984
		
		#define valor_timer3_CHT_50HZ 65036 + 23	
									// este timer faz as leituras analogicas de tensao e corrente em 8 bits pelo ad interno 
									// como vão ser 120 pontos o intervalo deve ser 1/freq / 120 = 0,000138889
									// em 24mhz 65536 - (0,000166666/(8/24000000)) = 65036						;64984
	
