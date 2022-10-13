/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_INTS                                                        *
; Funcao: MODULO Interrupçoes 					  						 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 06/06/2003                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/


#INT_TIMER1		//a cada 10 ms
void temporizador(void){
	set_timer1(valor_timer1);
	
	nro_ints++;
	conta_ints++;
	morder_t1 = 1;
	if (time_out_int0 != 0){
		time_out_int0--;
	}
	if (time_out_t3 != 0){
		time_out_t3--;
	}
		
	if (time_out_modbus != 0){
		time_out_modbus--;
	}
	if (time_tecla != 0){
  		time_tecla--;
  	}
	set_adc_channel(9);
	delay_us(20);												// espera chavear
	teclas = read_adc();

	#if (com_rep == true)
		if (modo_rep == 1){
			if (time_out_rec_rep != 0){
				time_out_rec_rep--;
				cont_sem_REP = 0;
			}
			else{
				qtd_byte_REP = nbyte_rep;
				nbyte_rep = 0;
				transferir_REP = 1;
			}
		}
	#endif

	cont0--;
	if (cont0 == 0){
		cont0 = INTS_PER_250MS;
		virou_250ms = 1;
		cont1++;
		if (tem_erro == 1){
			led_alarme = ~led_alarme;
		}
		else{
			led_alarme = 0;
		}
		
		if (cont1 == 1){
			virou_500ms = 1;
			led_ok = ~led_ok;
		}
		else if (cont1 == 2){
			virou_750ms = 1;
		}
		else if (cont1 == 3){
			led_ok = ~led_ok;
			virouseg = 1;
			if (time_out != 0){
				time_out--;
			}
			if (time_out2 != 0){
				time_out2--;
			}
		}
		else if (cont1 == 4){
			cont1 = 0;
		}
		else{
			cont1 = 0;
		}
	}
}



