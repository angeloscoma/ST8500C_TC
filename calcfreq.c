/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: st_CALC                                                        *
; Funcao: MODULO ROTINAS DE CALCULOS   									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */


/*   calculo de frequencia
	Funçao: Calcular a frequencia da fase R
	Entrada: val_freq com o nro de interrupçoes do timer e da interrupcao de rede
	saida: Frequencia em Q2.
	Obs.  se freq_final = 0, frequencia = 60hz
	para calculo da regra de tres, temos que com 60hz, temos 32 * 60 interrupcoes 
	do timer = INTS_PER_SECOND(= 1920 => definicao na st_main.c)
	freq_final * 240(60hz em q2) / INTS_PER_SECOND
*/

void calc_frequencia(void){
	#if (feira)
		frequencia = 240;
		return;
	#endif

	float aux_f1;
	float aux_f2;
	int32 freq_aux;

	calculando_freq = 1;
	if (nro_ints_old == 1){
		freq_aux = 65536 - freq_tmp1;
		freq_aux += freq_tmp - 15536;
//		#if (cristal == 40)
//			freq_aux = (word)(freq_aux / 2 );
//		#else
//			freq_aux = (word)(freq_aux / 3 );
//			freq_aux += 10000;
//		#endif
	}
	else if (nro_ints_old == 2){
		aux_w1 = 65535 - freq_tmp1;
		#if (cristal == 20)
			aux_w2 = freq_tmp - (65536 - 25000);	//valor_timer1;
		#elif (cristal == 24)
			aux_w2 = freq_tmp - (65536 - 30000);	//valor_timer1;
		#elif (cristal == 40)
			aux_w2 = freq_tmp - (65536 - 50000);	//valor_timer1;
		#else			
			aux_w2 = freq_tmp - (65536 - 30000);	//valor_timer1;
		#endif
		freq_aux = aux_w1;
		freq_aux += aux_w2;
		freq_aux += 50000;
//		#if (cristal == 40)
//			aux_w1 = (word)(aux_l1 / 2);
//			freq_aux = (word)(aux_w1);
//		#else
//			aux_w1 = (word)(aux_l1 / 3);
//			freq_aux = (word)(aux_w1 + 10000);
//		#endif
	}
	else{
		if(freq_50hz){
			freq_aux = 100000;
		}
		else{
			freq_aux = 83333;
		}
	}
	aux_f1 = (float)(0.0000002);
	aux_f2 = freq_aux;
	aux_f1 = (float)(aux_f1 * aux_f2);
	aux_f1 = (float)(4 / aux_f1);
	aux_w1 = aux_f1;
	if (aux_w1 > 140){
		aux_w1 = 240;
		soma_freq += aux_w1;
		conta_soma_freq++;
		if (conta_soma_freq > 15){
			frequencia = soma_freq / conta_soma_freq;
			soma_freq = 0;
			conta_soma_freq = 0;
		}
	}
	calcular_frequencia = 0;
	calculando_freq = 0;

	if (tensao_r < TENSAO_FALTA){
		freq_50hz = 0;
		frequencia = 0;	
	}
	else{
		if(frequencia > 220){			// em 60hz
			freq_50hz = 0;
		}
		else{							// em 50hz
			freq_50hz = 1;
		}
		if((frequencia < 180) && (frequencia > 250)){
			erro_freq = 1;
			frequencia = 0;
		}
		else{
			erro_freq = 0;
		}
	}
}

//void calculo_frequencia(void){
//	if(nro_media_freq > 2){
//		aux_w1 = (word)(soma_freq / 4);
//		frequencia = (aux_w1 * 4);
//		soma_freq = 0;
//		nro_media_freq = 0;
//	}
//	else{
//		soma_freq += (conta_freq * 4);			// (4 é quantização)
//		conta_freq = 0;
//		nro_media_freq++;
//	}	
//
//	if (tensao_r < TENSAO_FALTA){
//		freq_50hz = 0;
//		frequencia = 0;
//	}
//	else{
//		if (frequencia > 200){
//			freq_50hz = 0;		// em 60hz
//		}
//		else{
//			freq_50hz = 1;		// em 50hz
//		}
//		if ((frequencia < 180) && (frequencia > 250)){
//			erro_freq = 1;
//		}
//		else{
//			erro_freq = 0;
//		}
//	}
//	calcular_frequencia = false;
//
//	#if (feira)
//		if(frequencia > 220){
//			frequencia = 240;
//		}
//		else if(frequencia > 180){
//			frequencia = 200;
//		}
//		else{
//			frequencia = 0;
//		}
//	#endif
//}	


//void calc_frequencia(void)
//{
//	#if (feira)
//		frequencia = 240;
//		return;
//	#endif
//#if (ade7754 == true)
//	float aux_f1;
//	aux_f1 = 0.0000024;
//	aux_f1 = aux_f1 * periodo_ade7754;
//	aux_f1 = (1 / aux_f1) * 4;
//	frequencia = (char)(aux_f1);
//	calcular_frequencia = 0;
///*
//	if (tensao_r > 3200)			// 50 Vac (50 * 64)
//		{
//*/
//		if (frequencia < 120)		// 30hz
//			{
//			frequencia = 240;
//			}
///*
//		}
//*/
//#else
//	float aux_f1;
//	long long freq_aux;
//
//	calculando_freq = 1;
//	if (nro_ints_old == 1){
//		if (freq_tmp > freq_tmp1){
//			freq_aux = freq_tmp - freq_tmp1;
//		}
//		else{
//			freq_aux = freq_tmp1 - freq_tmp;
//		}
//		#if (cristal == 40)
//			freq_aux = (word)(freq_aux / 2 );
//		#else
//			freq_aux = (word)(freq_aux / 3 );
//			freq_aux += 10000;
//		#endif
//	}
//	else if (nro_ints_old == 2){
//		aux_w1 = 65535 - freq_tmp1;
//		#if (cristal == 20)
//			aux_w2 = freq_tmp - (65536 - 25000);	//valor_timer1;
//		#elif (cristal == 24)
//			aux_w2 = freq_tmp - (65536 - 30000);	//valor_timer1;
//		#elif (cristal == 40)
//			aux_w2 = freq_tmp - (65536 - 50000);	//valor_timer1;
//		#else			
//			aux_w2 = freq_tmp - (65536 - 30000);	//valor_timer1;
//		#endif
//		aux_l1 = (int32)(aux_w1);
//		aux_l1 += aux_w2;
//		#if (cristal == 40)
//			aux_w1 = (word)(aux_l1 / 2);
//			freq_aux = (word)(aux_w1);
//		#else
//			aux_w1 = (word)(aux_l1 / 3);
//			freq_aux = (word)(aux_w1 + 10000);
//		#endif
//	}
//	else{
//		if(freq_50hz){
//			freq_aux = 20000;
//		}
//		else{
//			freq_aux = 16666;
//		}	
//	}
//
//	aux_w1 = freq_aux;
//	aux_f1 = (float)(freq_aux);
//	aux_f1 = (float)(aux_f1 / 1000000);
//	aux_f1 = (float)(4 / aux_f1);
//	freq_aux = (char)(aux_f1);
//	if (freq_aux > 140){
//		soma_freq = soma_freq + freq_aux;
//		conta_soma_freq++;
//		if (conta_soma_freq > 15){
//			frequencia = soma_freq / conta_soma_freq;
//			soma_freq = 0;
//			conta_soma_freq = 0;
//		}
//	}
//	calcular_frequencia = 0;
//	calculando_freq = 0;
//
////
////
//#endif
//	if (tensao_r < TENSAO_FALTA)
//		{
//		freq_50hz = 0;
//		frequencia = 0;	
//		}
//	else	
//		{
//		if (frequencia > 220)
//			{
//			// em 60hz
//			freq_50hz = 0;
//			}
//		else
//			{
//			// em 50hz
//			freq_50hz = 1;
//			}
//		if ((frequencia < 180) && (frequencia > 250))
//			{
//			erro_freq = 1;
//			}
//		else
//			{
//			erro_freq = 0;
//			}
//		}
//
////
////	erro_freq = 0;
////	freq_50hz = 0;
////	
//
//}
//





///*;***********************************************************************
//; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
//; Modulo: st_CALC                                                        *
//; Funcao: MODULO ROTINAS DE CALCULOS   									 *
//; Responsavel: VAGNER SANTOS											 *
//; Modificado ; VAGNER SANTOS                                             *
//; Inicio: 30/08/2000                                                     *
//; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
//;**********************************************************************  */
//void calc_frequencia(void){
//	float aux_f1;
//	word freq_aux;
//
//	if (calcular_frequencia == 1){
//		if(fechar_frequencia){
//			calculando_freq = 1;
//			freq_aux = conta_freq * 4;
//			soma_freq += freq_aux;
//			conta_soma_freq++;
//			if(conta_soma_freq > 10){
//				frequencia = soma_freq / conta_soma_freq;
//				soma_freq = 0;
//				conta_soma_freq = 0;
//			}
//			conta_freq = 0;
//			fechar_frequencia = 0;
//			calculando_freq = 0;
//		}
//		calcular_frequencia = 0;
//	}	
//
//	if (tensao_r < TENSAO_FALTA){
//		freq_50hz = 0;
//		frequencia = 0;
//	}
//	else{
//		if (frequencia > 200){
//			// em 60hz
//			freq_50hz = 0;
//		}
//		else{
//			// em 50hz
//			freq_50hz = 1;
//		}
//		if ((frequencia < 180) && (frequencia > 250)){
//			erro_freq = 1;
//		}
//		else{
//			erro_freq = 0;
//		}
//	}
//	
//	#if(feira)
//		frequencia = 240;
//	#endif
//
//	erro_freq = 0;
//}
//

