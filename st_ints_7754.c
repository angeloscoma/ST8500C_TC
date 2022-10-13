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




char time_out_int_7754;
word time_int3_now;
word time_int3_old;

#INT_TIMER1 // FAST  							//a cada ???? ms
void temporizador(void)
{   
	set_timer1(valor_timer1);
	morder = 1;

	if (time_out_int_7754 != 0)
		{
		time_out_int_7754--;
		}
	else
		{
		time_out_int_7754 = 250;
		med_ten_ok = 0;
		passo_tensao = 0;
		acao_ade7754 = 0;

		tensao_a_rms = 0;
		corrente_a_rms = 0;
		tensao_b_rms = 0;
		corrente_b_rms = 0;
		tensao_c_rms = 0;
		corrente_c_rms = 0;

		}

	if (time_out_int0 != 0)
		{
		time_out_int0--;
		}

	if (time_out_modbus != 0)
		{
		time_out_modbus--;
		}
#if com_menu
	if (time_tecla != 0)
		{
  		time_tecla--;
  		}
	#if (com_cht == true)
		if (lendo_cht == false)
			{
			set_adc_channel(8);
			teclas = read_adc();
			}
	#else
			set_adc_channel(8);
			teclas = read_adc();
	#endif
#endif	  		

#if (st5x == true)
	if (nro_pisca_led == 0)
		{
		output_high(led_erro);
		time_led = 2 * INTS_PER_SECOND;
		}
	else
		{			
		time_led--;
		if (time_led == 0)
			{
			led = ~led;	
			if (led == 0)
				{
				output_high(led_erro);
				}
			else
				{
				output_low(led_erro);	
				}
			time_led = (INTS_PER_SECOND/3);
			nro_pisca_led--;
			}
		}
#endif
	cont0--;
	if (cont0 == (INTS_PER_SECOND/2))
		{
		virou_500ms = 1;
		return;
		}
	if (cont0 == 0)
		{
		cont0 = (INTS_PER_SECOND);
		virouseg = 1;
		virou_500ms = 1;

		periodo_ade7754 = le_word_ade7754(PERIOD_ADE7754);
		calcular_frequencia = 1;
		temperatura = le_byte_ade7754(ADE_TEMP);

		if (time_out != 0)
			{
			time_out--;
			}
#if (st5x == true)
			set_adc_channel(9);
			delay_us(20);												// espera chavear
			dip_addr = read_adc();
			set_adc_channel(10);
			delay_us(20);												// espera chavear
			dip_vel = read_adc();
#endif
#if (com_relogio == true)	
			conta_seg++;
#endif

		}
	
}



#INT_TIMER3  //a cada ???? ms
void temporizador3(void)
{   
	set_timer3(valor_timer3_2);
	if (abre_leitura_cht == 1)
		{
		abre_leitura_cht = 0;
		if (passo_le_senoide == 1)
			{
			salva_byte_ade7754(WAVEMODE, WAVEMODE_ADE7754_VS);
			lendo_tensao = true;
			}
		else if (passo_le_senoide == 2)
			{
			salva_byte_ade7754(WAVEMODE, WAVEMODE_ADE7754_VT);
			lendo_tensao = true;
			}
		else if (passo_le_senoide == 3)
			{
			salva_byte_ade7754(WAVEMODE, WAVEMODE_ADE7754_CR);
			lendo_tensao = false;
			}
		else if (passo_le_senoide == 4)
			{
			salva_byte_ade7754(WAVEMODE, WAVEMODE_ADE7754_CS);
			lendo_tensao = false;
			}
		else if (passo_le_senoide == 5)
			{
			salva_byte_ade7754(WAVEMODE, WAVEMODE_ADE7754_CT);
			lendo_tensao = false;
			}
		else
			{
			salva_byte_ade7754(WAVEMODE, WAVEMODE_ADE7754_VR);
			passo_le_senoide = 0;
			lendo_tensao = true;
			}
		}
	else
		{
		if (acao_ade7754 == 0)
			{
			acao_ade7754 = 1;
	
			output_high(ADE7754_CS);
			output_low(ADE7754_RST);		
			output_high(ADE7754_RST);
	
			delay_us(20);
	
			salva_byte_ade7754(OPMODE, MODO_OPER_ADE7754);

			delay_us(20);


			salva_word_ade7754(CFNUM, reg_cfnum);
			salva_word_ade7754(CFDEN, reg_cfdem);
			salva_byte_ade7754(WDIV, 0x01);

			salva_byte_ade7754(GAIN, GAIN_PGAS);
	
			salva_byte_ade7754(MMODE, MMODE_ADE7754_A);
			salva_byte_ade7754(WATMODE, WATMODE_ADE7754_A);
	
			salva_word_ade7754(LINECYCLE, NR0_CICLOS);
	
			salva_word_ade7754(MASK, MASK_ADE7754);

			salva_byte_ade7754(WAVEMODE, WAVEMODE_ADE7754_VR);

			salva_byte_ade7754(APHCAL, fase_r);
			salva_byte_ade7754(BPHCAL, fase_s);
			salva_byte_ade7754(CPHCAL, fase_t);

		 	salva_word_ade7754(AWG, 0);
		 	salva_word_ade7754(BWG, 0);
		 	salva_word_ade7754(CWG, 0);

		 	salva_word_ade7754(AAPGAIN, os_pot_r);
		 	salva_word_ade7754(BAPGAIN, os_pot_s);
		 	salva_word_ade7754(CAPGAIN, os_pot_t);

		 	salva_byte_ade7754(GAIN, 0);

		 	salva_word_ade7754(AAPOS, 0);
		 	salva_word_ade7754(BAPOS, 0);
		 	salva_word_ade7754(CAPOS, 0);

		 	salva_word_ade7754(AIRMSOS, 0);
		 	salva_word_ade7754(BIRMSOS, 0);
		 	salva_word_ade7754(CIRMSOS, 0);

		 	salva_word_ade7754(AVRMSOS, 0);
		 	salva_word_ade7754(BVRMSOS, 0);
		 	salva_word_ade7754(CVRMSOS, 0);


		 	salva_word_ade7754(AVGAIN, 0);
		 	salva_word_ade7754(BVGAIN, 0);
		 	salva_word_ade7754(CVGAIN, 0);

		 	salva_word_ade7754(0x3d, 0x01f7);

		 	rstatus_ade7754 = le_word_ade7754(RSTATUS);
	
		 	mascara_ade7754 = le_word_ade7754(LINECYCLE);
	
			passo_ade7754 = 0;
	
			}
		}
}





word aux_ten_r;
word aux_ten_s;
word aux_ten_t;
word aux_cor_r;
word aux_cor_s;
word aux_cor_t;

word conta_ints;

#INT_EXT2
void int_externa2(void)
{
// TRATAMENTO DA INTERRUPÇÃO EXTERNA 0(TENSAO) //
//	ext_int_edge(2,H_TO_L);
//	disable_interrupts(INT_EXT2);
	word aux_w;


	status_ade7754 = le_word_ade7754(STATUS);

	conta_ints++;
	time_out_int_7754 = 250;

	modo_oper = le_byte_ade7754(OPMODE);

	if (bit_test(status_ade7754, 14)) 
		{
		if (lendo_cht == true)
			{
			if (lendo_tensao == true)
				{
				buffer_cht[passo_rd_cht] = le_tlong_ade7754(WAVEFORM);
				}
			else
				{
				buffer_cht[passo_rd_cht] = le_clong_ade7754(WAVEFORM);
				}
			passo_rd_cht++;
			leu_senoide = true;
			if (passo_rd_cht == NRO_AMOSTRAS_CHT)
				{
				lendo_cht = false;
				leu_senoide = true;
				}
			}
		}

	if (bit_test(status_ade7754, 11)) 
		{
		passo_tensao = 0;
		acao_ade7754 = 0;

		salva_byte_ade7754(WAVEMODE, WAVEMODE_ADE7754_VR);

		salva_byte_ade7754(OPMODE, MODO_OPER_ADE7754);

		delay_us(20);

		salva_word_ade7754(CFNUM, reg_cfnum);
		salva_word_ade7754(CFDEN, reg_cfdem);
		salva_byte_ade7754(WDIV, 0x01);

		salva_byte_ade7754(GAIN, GAIN_PGAS);

		salva_byte_ade7754(MMODE, MMODE_ADE7754_A);
		salva_byte_ade7754(WATMODE, WATMODE_ADE7754_A);

		salva_word_ade7754(LINECYCLE, NR0_CICLOS);

		salva_word_ade7754(MASK, MASK_ADE7754);

	 	rstatus_ade7754 = le_word_ade7754(RSTATUS);

	 	ciclos = le_word_ade7754(LINECYCLE);

		passo_ade7754 = 0;

		goto finaliza_int2;

		}

	if (conta_ints > (NR0_CICLOS * 2))
		{
		conta_ints = 0;
		mode_ade7754 = le_byte_ade7754(MMODE);
		wmode_ade7754 = le_byte_ade7754(WATMODE);
	 	ciclos = le_word_ade7754(LINECYCLE);
	
		if ((mode_ade7754 == 0x70) || (wmode_ade7754 == 0x3f) || (ciclos == 0xffff))
			{
			salva_byte_ade7754(OPMODE, MODO_OPER_ADE7754);
			if (passo_ade7754 == 1)
				{
				salva_word_ade7754(LINECYCLE, NR0_CICLOS);
				salva_byte_ade7754(MMODE, MMODE_ADE7754_B);
				salva_byte_ade7754(WATMODE, WATMODE_ADE7754_B);
				}
			else if (passo_ade7754 == 2)
				{
				salva_word_ade7754(LINECYCLE, NR0_CICLOS);
				salva_byte_ade7754(MMODE, MMODE_ADE7754_C);
				salva_byte_ade7754(WATMODE, WATMODE_ADE7754_C);
				}
			else
				{
				salva_word_ade7754(LINECYCLE, NR0_CICLOS);
				salva_byte_ade7754(MMODE, MMODE_ADE7754_A);
				salva_byte_ade7754(WATMODE, WATMODE_ADE7754_A);
				passo_ade7754 = 0;
				}

			}
		}



	if (bit_test(status_ade7754, 10)) 
		{
		conta_ints = 0;
		if (passo_ade7754 == 0)
			{
//			time_int3_old = time_int3_now;
//			time_int3_now = 0;

//			LAENERGY_R = le_long_ade7754(LAENERGY);
//			AENERGY_R = le_long_ade7754(AENERGY);
//			RAENERGY_R = time_int3_old;	//le_long_ade7754(RAENERGY);
			RAENERGY_R = le_long_ade7754(RAENERGY);
			CFNUM_R = le_word_ade7754(CFNUM);

			salva_byte_ade7754(MMODE, MMODE_ADE7754_B);
			salva_byte_ade7754(WATMODE, WATMODE_ADE7754_B);
//			salva_word_ade7754(CFNUM, reg_cfnum);
//			salva_word_ade7754(CFDEN, reg_cfdem);
//			salva_byte_ade7754(OPMODE, MODO_OPER_ADE7754);
			passo_ade7754 = 1;

			}
		else if (passo_ade7754 == 1)
			{
//			time_int3_old = time_int3_now;
//			time_int3_now = 0;
//			LAENERGY_S = le_long_ade7754(LAENERGY);
//			AENERGY_S = le_long_ade7754(AENERGY);
			RAENERGY_S = le_long_ade7754(RAENERGY);
			CFNUM_S = le_word_ade7754(CFNUM);

			salva_byte_ade7754(MMODE, MMODE_ADE7754_C);
			salva_byte_ade7754(WATMODE, WATMODE_ADE7754_C);

//			salva_word_ade7754(CFNUM, reg_cfnum);
//			salva_word_ade7754(CFDEN, reg_cfdem);
//			salva_byte_ade7754(OPMODE, MODO_OPER_ADE7754);
			passo_ade7754 = 2;
			}
		else if (passo_ade7754 == 2)
			{
//			time_int3_old = time_int3_now;
//			time_int3_now = 0;
//			LAENERGY_T = le_long_ade7754(LAENERGY);
//			AENERGY_T = le_long_ade7754(AENERGY);
			RAENERGY_T = le_long_ade7754(RAENERGY);
			CFNUM_T = le_word_ade7754(CFNUM);

			salva_byte_ade7754(MMODE, MMODE_ADE7754_A);
			salva_byte_ade7754(WATMODE, WATMODE_ADE7754_A);
//			salva_word_ade7754(CFNUM, reg_cfnum);
//			salva_word_ade7754(CFDEN, reg_cfdem);
//			salva_byte_ade7754(OPMODE, MODO_OPER_ADE7754);
			passo_ade7754 = 0;
			}
		else
			{
			salva_byte_ade7754(MMODE, MMODE_ADE7754_A);
			salva_byte_ade7754(WATMODE, WATMODE_ADE7754_A);
			passo_ade7754 = 0;
//			salva_word_ade7754(CFNUM, reg_cfnum);
//			salva_word_ade7754(CFDEN, reg_cfdem);
//			salva_byte_ade7754(OPMODE, MODO_OPER_ADE7754);
			}
		}


	if (bit_test(status_ade7754, 4)) 
		{
		tensao_a_rms = 0;
		corrente_a_rms = 0;
		}
	if (bit_test(status_ade7754, 5)) 
		{
		tensao_b_rms = 0;
		corrente_b_rms = 0;
		}
	if (bit_test(status_ade7754, 6)) 
		{
		tensao_c_rms = 0;
		corrente_c_rms = 0;
		}

	if (bit_test(status_ade7754, 7))
		{
		aux_ten_r = le_xlong_ade7754(AVRMS);
		aux_cor_r = le_xlong_ade7754(AIRMS);
		if (med_ten_ok_r == 0)
			{
			tensao_a_rms = aux_ten_r;
			corrente_a_rms = aux_cor_r;
			med_ten_ok_r = 1;
			}
		}
	if (bit_test(status_ade7754, 8))
		{
		aux_ten_s = le_xlong_ade7754(BVRMS);
		aux_cor_s = le_xlong_ade7754(BIRMS);
		if (med_ten_ok_s == 0)
			{
			tensao_b_rms = aux_ten_s;
			corrente_b_rms = aux_cor_s;
			med_ten_ok_s = 1;
			}
		}
	if (bit_test(status_ade7754, 9))
		{
		aux_ten_t = le_xlong_ade7754(CVRMS);
		aux_cor_t = le_xlong_ade7754(CIRMS);
		if (med_ten_ok_t == 0)
			{
			tensao_c_rms = aux_ten_t;
			corrente_c_rms = aux_cor_t;
			med_ten_ok_t = 1;
			}
		}

	if (modo_funca == 2)
		{
		corrente_a_rms = 0;
		corrente_b_rms = 0;
		corrente_c_rms = 0;
		}
	else
		{
		if (tipo_ligacao == 2)
			{
			corrente_b_rms = 0;
			}
		else
			{				
			}
		}

finaliza_int2:

	passo_tensao = NRO_AMOSTRAS + 1;
	
	if (lendo_cht == true)
		{
		salva_word_ade7754(MASK, MASK_ADE7754_WAVE);
		}
	else
		{
		salva_word_ade7754(MASK, MASK_ADE7754);
		}

 	rstatus_ade7754 = le_word_ade7754(RSTATUS);

//	ext_int_edge(2,H_TO_L);
//	enable_interrupts(INT_EXT2);
}




#INT_EXT3
void int_externa3(void)
{
//	time_int3_old = time_int3_now;
//	time_int3_now = get_timer1();
	time_int3_now++;

}



#INT_RDA
void serial(void)
{
#if (st5x==1)
	if (numbtx == 0)
		{
		output_low(led_rx);
		output_high(led_tx);
		}
	else
		{
		output_low(led_rx);
		output_low(led_tx);
		}
#endif
		time_out_modbus = 2;
		buf_rx[ptrrx++] = getc();   
		numbrx++;
		if (ptrrx >= TAM_RX)
			{
			ptrrx = 0;
			numbrx = 0;
			}
}
