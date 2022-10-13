/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÿÔNICOS                                  *
; Modulo: ST_INTS                                                        *
; Funcao: MODULO Interrupÿçoes 					  						 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 06/06/2003                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/


#INT_TIMER1		//a cada 10 ms
void temporizador(void)
{   
	#if (st5x == true)
		char saida;
		#if (cpu_rev1011 == true)
			char entrada_tmp;
		#endif
	#endif
	set_timer1(valor_timer1);
	
	#if (ST8100C == true)
		#if (simula_forno == true)
			if (TRIAC_3 == false)
				{
				TRIAC_3 = true;
				}
			else
				{
				TRIAC_3 = false;
				}
		
			if (tempo_on != 0)
				{
				TRIAC_1 = true;
				TRIAC_2 = true;
				TRIAC_4 = true;
				tempo_on--;
				}
			else
				{
				if (tempo_off != 0)
					{
					TRIAC_1 = false;
					TRIAC_2 = false;
					TRIAC_4 = false;
					tempo_off--;
					}
				else
					{
					tempo_on = valor_tp;
					tempo_off = 60 - tempo_on;
					}
				}
				output_high (CSIO1);
				output_high (CSIO4);
			
				output_01 = saida2;
				output_low(CSIO2);
				output_d(output_01);
				output_high(CSIO2);
	
				output_01 = saida3;
				output_low(CSIO3);
				output_d(output_01);
				output_high(CSIO3);
				
		#endif		
	#endif
	
	nro_ints++;
	conta_ints++;
	morder_t1 = 1;
	if (time_out_int0 != 0)
		{
		time_out_int0--;
		}
	if (time_out_t3 != 0)
		{
		time_out_t3--;
		}
		
	if (time_out_modbus != 0)
		{
		time_out_modbus--;
		}
	#if (com_menu == true)
		if (time_tecla != 0)
			{
	  		time_tecla--;
	  		}
		#if (com_cht == true)
			if (lendo_cht == false)
				{
				#if (st_prog == true)
					set_adc_channel(0);
				#elif (controlador == true)
					#if (st8300c == true)
						#if(MALA_FEIRA)
							set_adc_channel(3);
						#else
							set_adc_channel(8);
						#endif
					#elif (st8500c == true)
						#if (pci_mono == true)
							set_adc_channel(3);
						#else
							set_adc_channel(8);
						#endif	
					#else
						set_adc_channel(3);
					#endif
				#else
					set_adc_channel(8);
				#endif
				delay_us(20);												// espera chavear
				teclas = read_adc();
				}
		#else
				#if (st_prog == true)
					set_adc_channel(0);
				#elif (controlador == true)
					#if (st8300c == true)
						set_adc_channel(8);
					#elif (st8500c == true)
						#if (pci_mono == true)
							set_adc_channel(3);
						#else
							set_adc_channel(8);
						#endif
					#else
						set_adc_channel(3);
					#endif
				#else
					set_adc_channel(8);
				#endif
				delay_us(20);												// espera chavear
				teclas = read_adc();
		#endif
	#endif	  		

	#if (st5x == true)
		#if (st5000c_rev12 == true)
			#if (endereco_via_serial == true)
				dip_addr = endereco;
			#else
				set_tris_d(0b11111111);
				dip_addr = ~input_d();
				set_tris_d(0b00000000);
				output_bit(xled_alarme, fled_alarme);						
				output_bit(xled_rx, fled_rx);						
				output_bit(xled_tx, fled_tx);						
				output_bit(xled_tc_r, fled_tc_r);						
				output_bit(xled_tc_s, fled_tc_s);						
				output_bit(xled_tc_t, fled_tc_t);						
				output_bit(xled_ok, fled_ok);
			#endif

			if (nro_pisca_led == 0)
				{
				output_high(xled_erro);
				fled_erro = 1;						
				time_led = 200;
				}
			else
				{			
				time_led--;
				if (time_led == 0)
					{
					fled_erro = ~fled_erro;
					time_led = 33;
					nro_pisca_led--;
					}
				if (fled_erro == 0)
					{
					output_high(xled_erro);
					}
				else
					{
					output_low(xled_erro);	
					}
				}
		#else
			#if (painel_12 == true)
				#if (cpu_rev1011 == true)
					#if (home_system == false)
						if (med_ten_ok == 1)
							{
							if (spi_ocupada == false)
								{
								#if (endereco_via_serial == true)
									dip_addr = endereco;
								#else
									set_tris_d(0b11111111);
									set_tris_e(0b11111111);
									dip_addr = input_d();
									saida = input_e();
									set_tris_d(0b00000100);
									set_tris_e(0b00000000);
									dip_addr = dip_addr >> 4;
									saida = saida & 0b11110000;
									dip_addr = ~(dip_addr | saida);
								#endif
		
						 	  	output_high(MCP3208_CS);
					 	  	    output_low(RTC_RST);
								}
							}	
					#endif
						
					output_bit(xled_alarme, fled_alarme);						
					output_bit(xled_rx, fled_rx);						
					output_bit(xled_tx, fled_tx);						
					output_bit(xled_tc_r, fled_tc_r);						
					output_bit(xled_tc_s, fled_tc_s);						
					output_bit(xled_tc_t, fled_tc_t);						
					output_bit(xled_ok, fled_ok);
					
											
					#if (teste_painel == false)
						if (nro_pisca_led == 0)
							{
							output_high(xled_erro);
							fled_erro = 1;						
							time_led = 200;
							}
						else
							{			
							time_led--;
							if (time_led == 0)
								{
								fled_erro = ~fled_erro;
								time_led = 33;
								nro_pisca_led--;
								}
							if (fled_erro == 0)
								{
								output_high(xled_erro);
								}
							else
								{
								output_low(xled_erro);	
								}
							}
					#else
						output_bit(xled_erro, fled_erro);
					#endif
						
				#else
					output_d(0xff);
					set_tris_d(0b11111111);
					dip_addr = input_d();
					dip_addr = ~dip_addr;
					set_tris_d(0b00000000);
					saida = LEDS;
					output_d(saida);
				#endif
			#endif
		#endif
	#endif
	#if (st_prog == true)
		if (time_out_sultech != 0)
			{
			time_out_sultech--;
			}
	#endif		

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
	if (cont0 == 0)
		{
		cont0 = INTS_PER_250MS;
		virou_250ms = 1;
		cont1++;
		#if ((controlador == true) || (st92 == true))
			if (tem_erro == 1)
				{
				led_alarme = ~led_alarme;
				}
			else
				{
				led_alarme = 0;
				}
		#endif
		
		if (cont1 == 1)
			{
			virou_500ms = 1;
			#if (st5x == true)
				fled_ok = ~fled_ok;
			#endif
			#if ((st9200r == true) || (st9230r == true) || (controlador == true))
				led_ok = ~led_ok;
			#endif
			}
		else if (cont1 == 2)
			{
			virou_750ms = 1;
			}
		else if (cont1 == 3)
			{
			#if ((st9200r == true) || (st9230r == true) || (controlador == true))
				led_ok = ~led_ok;
			#endif
			#if (st5x == true)
				fled_ok = ~fled_ok;
			#endif
			#if (com_relogio == false)
				{
			   	segundo++;
		 	  	if (segundo >= 60)
					{
					segundo = 0;
		 	  		viroumin = 1;
					}
				}
			#endif
	
			virouseg = 1;
			fechar_frequencia = 1;
			if (time_out != 0)
				{
				time_out--;
				}
			#if ((controlador == true) || (st92 == true))
				if (time_out2 != 0)
					{
					time_out2--;
					}
			#endif
			#if (st5x == true)
				#if (st5000c_rev12 == true)
				#else
					#if (painel_12 == false)
						set_adc_channel(9);
						delay_us(20);												// espera chavear
						dip_addr = read_adc();
					#endif
					set_adc_channel(10);
					delay_us(30);												// espera chavear
					dip_vel = read_adc();
				#endif
			#endif
			#if (ST8100C == true)
				output_high (CSIO1);
				output_high (CSIO4);
			
				output_01 = saida2;
				output_low(CSIO2);
				output_d(output_01);
				output_high(CSIO2);
	
				output_01 = saida3;
				output_low(CSIO3);
				output_d(output_01);
				output_high(CSIO3);
			#endif
			}
		else if (cont1 == 4)
			{
			cont1 = 0;
			}
		else
			{
			cont1 = 0;
			}
		
		}
	delay_cycles(1);
}



