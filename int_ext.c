/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÿÔNICOS                                  *
; Modulo: ST_INTS                                                        *
; Funcao: MODULO Interrupÿçoes 					  						 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 06/06/2003                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/


#if (st94 == true) || (st92 == true)
	#if (rev_pci_st94 >= 11)
		#INT_EXT  // FAST
	#else
		#INT_EXT2  // FAST
	#endif
#else
	#INT_EXT  // FAST
#endif
void int_externa0(void)
{
	// TRATAMENTO DA INTERRUPÇÃO EXTERNA 0(TENSAO) //
	
	// obtem o timer atual;
	conta_freq++;
	
	if (calculando_freq == 0)
		{
		freq_tmp1 = freq_tmp;
		freq_tmp = get_timer1();
		nro_ints_old = nro_ints;
		nro_ints = 0;
		if (nro_ints_old <= 2)
			{
			calcular_frequencia = 1;
			}
		else
			{
			calcular_frequencia = 0;
			}
		}

		
	ler_senoide = 1;
	time_out_t3 = 3;
	if (med_ten_ok == 0)
		{
		ler_ad_t3 = 1;
		}


			
	// obtem a fase entre tensao e corrente	
	distancia_fase = cont_fase;
		
	fase_tmp = get_timer1() - fase_tmp1;
//	#if (controlador == true)
//		tempo_falta_energia = 255;
//		faltou_energia = false;
//
//	#endif
}


#INT_EXT1 // FAST
void int_externa1(void)
{
	// TRATAMENTO DA INTERRUPÇÃO EXTERNA 1(CORRENTE) //
		fase_tmp1 = get_timer1();
		
		cont_fase = 0;
		
}



