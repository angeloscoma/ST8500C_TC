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

char conta_ciclo;
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
		}
#endif
				

#if (chip_cs5460a == true)
	conta_ciclo++;
	if (conta_ciclo > 16)
		{
		med_ten_ok = 1;
		conta_ciclo = 0;
		}
#endif
	if (time_out_modbus != 0)
		{
		time_out_modbus--;
		}

	cont0--;
	if (cont0 == (INTS_PER_SECOND/2))
		{
		virou_500ms = 1;
		return;
		}
	if (cont0 == 0)
		{
		nro_kw_r = conta_kw_r;
		conta_kw_r = 0;
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
		set_adc_channel(9);
		delay_us(20);												// espera chavear
		dip_addr = read_adc();
		set_adc_channel(10);
		delay_us(20);												// espera chavear
		dip_vel = read_adc();

		}
		
}


#INT_TIMER3  //a cada ???? ms
void temporizador3(void)
{   
	set_timer3(valor_timer3);
	ler_cs5460 = 1;
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
//	ext_int_edge(0,H_TO_L);
//	disable_interrupts(INT_EXT);

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
//	ext_int_edge(1,H_TO_L);
//	disable_interrupts(INT_EXT1);
//	cont_fase = 0;

	conta_kw_r++;
	int_cs5460_r = 1;

//	ext_int_edge(1,H_TO_L);
//	enable_interrupts(INT_EXT1);

}

#INT_EXT2
void int_externa2(void)
{
	int_cs5460_s = 1;
}

#INT_EXT3
void int_externa3(void)
{
	int_cs5460_t = 1;
}







