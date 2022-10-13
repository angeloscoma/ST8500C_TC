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
		}
#endif
				
	
trata_temporizacao:	
	cont_ms--;
	if (cont_ms == 0)
		{
		cont_ms = tempo_1_ms;		//4;   // para 260us valor 4 para 520us valor 2
		if (time_out_modbus != 0)
			{
			time_out_modbus--;
			}
#if com_menu
  		if (time_tecla != 0)
  			{
	  		time_tecla--;
	  		}

		set_adc_channel(8);
		delay_us(20);												// espera chavear
		teclas = read_adc();
#endif	  		

		cont0--;
		if (cont0 == (INTS_PER_SECOND/2))
			{
			virou_500ms = 1;
#if (chip_cs5460a == true)
	med_ten_ok = 1;
#endif
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
			disable_interrupts(INT_TIMER3);
			passo_rd_cht = 0;
			passo_fase_cht = 0;
			lendo_cht = false;
			}
		delay_us(15);												// espera chavear
		buffer_cht[passo_rd_cht] = (read_adc() << 2);
		passo_rd_cht++;
		if (passo_rd_cht == NRO_AMOSTRAS_CHT)
			{
			lendo_cht = false;
			disable_interrupts(INT_TIMER3);
			passo_rd_cht = 0;
			ler_senoide = 0;
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

	conta_freq++;		//Edison: Contador de interrupções do comparador

// obtem o timer atual;
	freq_tmp = freq_tmp + nro_ints;
	nro_ints = 0;
		
	ler_senoide = 1;
	
// obtem a fase entre tensao e corrente	
	distancia_fase = cont_fase;
	
}


#INT_EXT1
void int_externa1(void)
{
// TRATAMENTO DA INTERRUPÇÃO EXTERNA 1(CORRENTE) //

	cont_fase = 0;
	
}

#INT_EXT2
void int_externa2(void)
{
	disable_interrupts(INT_EXT2);

}







