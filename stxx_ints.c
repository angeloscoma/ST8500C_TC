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

#define ad_interno false
#define teste_adc false

char conta_int0;

#INT_TIMER1 // FAST  							//a cada ???? ms
void temporizador(void)
{   
	set_timer1(valor_timer1);
	morder = 1;
	cont_fase++;
	nro_ints++;
	
trata_leitura_senoides:
#if (com_cht == true)
	if (lendo_cht == true)
		{
		if (time_out_int0 != 0)
			{
			time_out_int0--;
			}
		passo_senoide = 0;
		passo_corrente = 6;		//off_cor_r;
		goto trata_temporizacao;	
		}
#endif
	if (med_ten_ok == 0)
		{
#if (ad_interno == 1)			
	{
	#if (teste_adc == 1)
		{
		if (passo_le_senoide == 0)
			{
			delay_us(15);												// espera chavear
			buf_tensao_r[passo_senoide] = seno_32[passo_senoide] - vref;
			if (modo_funca != 2)
				{
				delay_us(15);												// espera chavear
				buf_corrente_r[passo_corrente] = seno_32[passo_corrente] - vref;
				}
			}
		else if (passo_le_senoide == 1)
			{
			delay_us(15);												// espera chavear
			buf_tensao_s[passo_senoide] = seno_32[passo_senoide] - vref;
			if (modo_funca != 2)
				{
				delay_us(15);												// espera chavear
				buf_corrente_s[passo_corrente] = seno_32[passo_corrente] - vref;
				}
			}
		else if (passo_le_senoide == 2)
			{
			delay_us(15);												// espera chavear
			buf_tensao_t[passo_senoide] = seno_32[passo_senoide] - vref;
			if (modo_funca != 2)
				{
				delay_us(15);												// espera chavear
				buf_corrente_t[passo_corrente] = seno_32[passo_corrente] -vref;
				}
		}
	}
	#else
		{
		if (passo_le_senoide == 0)
			{
			set_adc_channel(4);											// seta canal do ad
			delay_us(15);												// espera chavear
			buf_tensao_r[passo_senoide] = (signed word)((read_adc() << 2) - vref); 		// colocar o valor lido no buffer	
			if (modo_funca != 2)
				{
				set_adc_channel(0);											// seta o proximo(0)
				delay_us(15);												// espera chavear
				buf_corrente_r[passo_corrente] = (signed word)((read_adc() << 2) - vref);	// coloca no buffer
				}
			}
		else if (passo_le_senoide == 1)
			{
			set_adc_channel(5);											// seta o proximo(5)
			delay_us(15);												// espera chavear
			buf_tensao_s[passo_senoide] = (signed word)((read_adc() << 2) - vref); 		// colocar no buffer
			if (modo_funca != 2)
				{
				set_adc_channel(1);											// seta o proximo(1)
				delay_us(15);												// espera chavear
				buf_corrente_s[passo_corrente] = (signed word)((read_adc() << 2) - vref);	// colocar no buffer
				}
			}
		else if (passo_le_senoide == 2)
			{
			set_adc_channel(6);											// seta o proximo(6)
			delay_us(15);												// espera chavear
			buf_tensao_t[passo_senoide] = (signed word)((read_adc() << 2) - vref); 		// coloca no buffer
			if (modo_funca != 2)
				{
				set_adc_channel(2);											// seta o proximo(2)
				delay_us(15);												// espera chavear
				buf_corrente_t[passo_corrente] = (signed word)((read_adc() << 2) - vref);	// coloca no buffer
				}
		}
	}
	#endif
	}
#else		
	{
		if (passo_le_senoide == 0)
			{
			buf_tensao_r[passo_senoide] = (signed word)(le_canal_4() - vref); 	//4);
			if (modo_funca == 1)
				{
				buf_corrente_r[passo_corrente] = (signed word)(le_canal_0() - vref);	//0);
				}
			}
		else if (passo_le_senoide == 1)
			{
			buf_tensao_s[passo_senoide] = (signed word)(le_canal_5() - vref);		//5);
			if (modo_funca == 1)
				{
				buf_corrente_s[passo_corrente] = (signed word)(le_canal_1() - vref);   //1); 
				}
			}
		else if (passo_le_senoide == 2)
			{
			buf_tensao_t[passo_senoide] = (signed word)(le_canal_6() - vref);		//6);
			if (modo_funca == 1)
				{
				buf_corrente_t[passo_corrente] = (signed word)(le_canal_2() - vref);	//2);
				}
			}
		else
			{
			passo_le_senoide = 0;
			}
	}
#endif		
		passo_senoide++;
		passo_corrente++;
		if (passo_corrente >= NRO_AMOSTRAS)
			{
			passo_corrente = 0;
			}
		if (passo_senoide >= NRO_AMOSTRAS)
			{
			passo_le_senoide++;
			if (passo_le_senoide >= 3)
				{
				med_ten_ok = 1;
				passo_senoide = 0;
				passo_corrente = 6;	//off_cor_r;
				passo_le_senoide = 0;
				}
					else
						{
				passo_senoide = 0;
				passo_corrente = 6;	//off_cor_r;
						}
			}
		}
	else
		{
// obtem a referencia do ad
		if (nro_soma_vref != 32)
			{
#if (ad_interno == 1)			
	{
			set_adc_channel(3);
			delay_us(15);
			soma_vref += (read_adc() << 2); 			//4);
	}
#else
	{
			soma_vref += le_canal_3();	//read_analog_mcp(canal_7);
	}
#endif			
			nro_soma_vref++;
			}
		}
				
	
trata_temporizacao:	
	cont_ms--;
	if (cont_ms == 0)
		{
		cont_ms = tempo_1_ms;		//4;   // para 260us valor 4 para 520us valor 2

		if (conta_int0 != 0)
			{
			conta_int0--;
			if (conta_int0 == 0)
				{
				enable_interrupts(INT_EXT);
				}
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
			delay_us(20);												// espera chavear
			teclas = read_adc();
			}
	#else
			set_adc_channel(8);
			delay_us(20);												// espera chavear
			teclas = read_adc();
	#endif
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
			calcular_frequencia = 1;
			freq_final = freq_tmp;
			freq_tmp = 0;
			if (time_out != 0)
				{
				time_out--;
				}
			}
		}
		
}


#INT_TIMER3  //a cada ???? ms
void temporizador3(void)
{   
#if !com_cht
	disable_interrupts(INT_TIMER3);
	return;
#else
	set_timer3(valor_timer3);
	if (ler_senoide == 1)
		{
		if (passo_fase_cht == 0)
			{
			set_adc_channel(4);
			}
		else if (passo_fase_cht == 1)
			{
			set_adc_channel(5);
			}
		else if (passo_fase_cht == 2)
			{
			set_adc_channel(6);
			}
		else if (passo_fase_cht == 3)
			{
			set_adc_channel(0);
			}
		else if (passo_fase_cht == 4)
			{
			set_adc_channel(1);
			}
		else if (passo_fase_cht == 5)
			{
			set_adc_channel(2);
			}
		else
			{
			passo_rd_cht = 0;
			passo_fase_cht = 0;
			lendo_cht = false;
			disable_interrupts(INT_TIMER3);
			}
		delay_us(15);												// espera chavear
		buffer_cht[passo_rd_cht] = (read_adc() << 2);
		passo_rd_cht++;
		if (passo_rd_cht == NRO_AMOSTRAS_CHT)
			{
			lendo_cht = false;
			passo_rd_cht = 0;
			ler_senoide = 0;
			disable_interrupts(INT_TIMER3);
			}
		}
#endif		
}


#INT_RDA
void serial(void)
{
	if (numbtx == 0)
		{
#if (st5x==1)
		output_low(led_rx);
		output_high(led_tx);
#endif
		time_out_modbus = 6;
		if (ptrrx == 0)
			{
			buf_rx[ptrrx++] = getc();   
			numbrx++;
			}
		else
			{
			if (buf_rx[0] == endereco_modbus)
				{
				buf_rx[ptrrx++] = getc();   
				numbrx++;
				if (ptrrx >= TAM_RX)
					{
					ptrrx = 0;
					numbrx = 0;
					}
				}
			else
				{
				getc();
				}
			}
		}
	else
		{
		getc();
		}
}


#INT_EXT
void int_externa0(void)
{
// TRATAMENTO DA INTERRUPÇÃO EXTERNA 0(TENSAO) //
	ext_int_edge(0,H_TO_L);
	disable_interrupts(INT_EXT);
	conta_int0 = 17;

// obtem o timer atual;
	freq_tmp = freq_tmp + nro_ints;
	nro_ints = 0;
		
	ler_senoide = 1;
	
// obtem a fase entre tensao e corrente	
	distancia_fase = cont_fase;
	
//	ext_int_edge(0,H_TO_L);
//	enable_interrupts(INT_EXT);
}


#INT_EXT1
void int_externa1(void)
{
// TRATAMENTO DA INTERRUPÇÃO EXTERNA 1(CORRENTE) //
	ext_int_edge(1,H_TO_L);
	disable_interrupts(INT_EXT1);

	cont_fase = 0;
	
//	ext_int_edge(1,H_TO_L);
//	enable_interrupts(INT_EXT1);
}







