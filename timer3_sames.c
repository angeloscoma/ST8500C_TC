/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_INTS                                                        *
; Funcao: MODULO Interrupçoes 					  						 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 06/06/2003                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/

#if (st94 == 1 )
	char ptr_disp;
	char disp_timer;
#elif (st8610c == true)
	char ptr_disp;
	char disp_timer;
#endif



#INT_TIMER3  // FAST //a cada ???? ms
void temporizador3(void)
{   
	if (lendo_cht == true)
		{
		if (freq_50HZ == 1)
			{
			set_timer3(valor_timer3_CHT_50HZ);
			}
		else
			{
			set_timer3(valor_timer3_CHT_60HZ);
			}
		ler_ad = 1;
		passo_tensao = 0;
		passo_corrente = off_cor_r;
		#if (monofasico == false)
			#if (com_cht == true)
				set_adc_channel(que_ad);
				delay_us(20);
				buffer_cht[passo_rd_cht] = (signed word)((read_adc() << 2));
			#endif
			goto fim_timer3;
		#else
			#if (com_cht == true)
				if (que_ad == 0)
					{
					set_adc_channel(2);
					}
				else
					{
					set_adc_channel(0);
					}
				delay_us(20);
				buffer_cht[passo_rd_cht] = (signed word)((read_adc() << 2));
			#endif
			goto fim_timer3;
		#endif
		}
	else
		{
		cont_fase++;
		if (freq_50HZ == 1)
			{
			set_timer3(valor_timer3_2_50HZ);
			}
		else
			{
			set_timer3(valor_timer3_2_60HZ);
			}
		if (med_ten_ok == 0)
			{
			#if (monofasico == true)
				{
				goto fim_timer3;
				}
				
			#else
				if (modo_funca == 2)
					{
					}
				else
					{
					if (tipo_ligacao == 2)
						{
						}
					else
						{				
						}
					}
			#endif
			}
		}
fim_timer3:
#if (st94==true)
		if (disp_timer == 0)
			{
			disp_timer = 1;
			output_low(CS_IO2);
			output_d(buf_display[ptr_disp]);
			output_high (CS_IO2);
				
			if (ptr_disp < 8)
				{
				output_low(CS_IO3);
				output_d(tabela_disp[ptr_disp]);
				output_high (CS_IO3);
				output_low(CS_IO4);
				output_d(0);
				output_high (CS_IO4);
				}
			else
				{
				output_low(CS_IO4);
				output_d(tabela_disp[ptr_disp]);
				output_high (CS_IO4);
				output_low(CS_IO3);
				output_d(0);
				output_high (CS_IO3);
				}
			ptr_disp++;
			if (ptr_disp > 12)
				{
				ptr_disp=0;
				}
			}
		else
			{
			disp_timer = 0;
			}
#elif (st8610c == true)
		if (disp_timer == 0)
			{
			disp_timer = 8;
			output_low(CSIO1);
			output_d(buf_display[0]);
			output_high (CSIO1);
			output_low(CSIO4);
			output_d(tabela_disp[ptr_disp]);
			output_high (CSIO4);

			output_low(CSIO1);
			if (ptr_disp == 0)
				{
				output_d(buf_display[0]);
				}
			else if (ptr_disp == 1)
				{
				output_d(buf_display[1]);
				}
			else if (ptr_disp == 2)
				{
				output_d(buf_display[2]);
				}
			else if (ptr_disp == 3)
				{
				output_d(buf_display[3]);
				}
			else if (ptr_disp == 4)
				{
				output_d(buf_display[4]);
				}
			output_high (CSIO1);

			output_low(CSIO4);
			output_d(tabela_disp[ptr_disp]);
			output_high (CSIO4);
			ptr_disp++;
			if (ptr_disp > 5)
				{
				ptr_disp=0;
				}
			}
		else
			{
			disp_timer--;
			}
#else
	delay_cycles(1);			
#endif

}



