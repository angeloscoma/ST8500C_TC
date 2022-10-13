// DEFINIÇÕES DE INTERRUPÇÕES DO TIMER 3 PARA 83 AMOSTRAS DE SENAOIS

#define cristal	24
#define valor_timer1  65536 - 30000			// 10 milisegundo
										// (0,010/(8/24000000)) = 3000
										// calculo: 65536-30000
#define valor_timer3_2 		64933  //para 83 amostras

#define valor_timer3_2_60HZ valor_timer3_2	// para 83 amostras
#define valor_timer3_2_50HZ 64598	// para 83 amostras

									// 60HZ
									// calculo: 65536-(0,0002008032/(8/24000000)),  = "64933" p/ 200us / 24mhz   
									// onde 0,000260 é intervalo entre ints do timer 1 
									// para 260us 64933 p/ 83 amostras por senoide em 24MHZ
									
									// 50HZ
									// calculo: 65536-(0,0003125/(8/24000000)),  = "64756" p/ 312,5us / 24mhz   
									// onde 0,0003125 é intervalo entre ints do timer 1 
									// para 312,5us 64598 p/ 83 amostras por senoide em 24MHZ
		
		
		
#define valor_timer3_CHT_60HZ 65119 + 23	
									// este timer faz as leituras analogicas de tensao e corrente em 8 bits pelo ad interno 
									// como vão ser 120 pontos o intervalo deve ser 1/freq / 120 = 0,000138889
									// em 24mhz 65536 - (0,000138889/(8/24000000)) = 65119						;64984
		
#define valor_timer3_CHT_50HZ 65036 + 23	
									// este timer faz as leituras analogicas de tensao e corrente em 8 bits pelo ad interno 
									// como vão ser 120 pontos o intervalo deve ser 1/freq / 120 = 0,000138889
									// em 24mhz 65536 - (0,000166666/(8/24000000)) = 65036						;64984


