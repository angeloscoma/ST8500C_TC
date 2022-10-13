/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: st_CALC                                                        *
; Funcao: MODULO ROTINAS DE CALCULOS   									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */



void calcula_vref(void)
{
}


void aguarda_cruzar_zero(char fase)
{
	char aux_b10;
	aux_sw1 = read_word_cs5460(V_register, fase );
	if (aux_sw1 < 0)
		{
		zero_r = 0;
		}
	else
		{
		zero_r = 1;
		}	
	for (aux_b10 = 0; aux_b10 < NRO_AMOSTRAS_CHT; aux_b10++)
		{
		delay_us(130);
		aux_sw1 = read_word_cs5460(V_register, fase );

		if (zero_r == 1)
			{
			if (aux_sw1 < 0)
				{
				break;
				}
			}
		else
			{
			if (aux_sw1 > 0)
				{
				break;
				}
			}
		}
}



void le_seno(char fase)
{
	char aux_b10;
	char aux_b20;
	ler_cs5460 = 0;
	aux_b20 = 4;
	aux_b10 = 0;
	disable_interrupts(INT_TIMER1);
	disable_interrupts(INT_TIMER3);
	setup_timer_3(T3_INTERNAL|T3_DIV_BY_2);
	set_timer3(valor_timer3);
	enable_interrupts(INT_TIMER3);
	while(true)
		{
		if (ler_cs5460 == 1)
			{
			if (lendo_cht_cs5460 ==  0)
				{
				buffer_t[aux_b10++] = read_word_cs5460(V_register, fase );
				buffer_c[aux_b20++] = read_word_cs5460(I_register, fase);
				}
			else
				{
				buffer_cht_t[aux_b10++] = read_word_cs5460(V_register, fase );
				buffer_cht_c[aux_b20++] = read_word_cs5460(I_register, fase);
//				buffer_cht_c[aux_b20++] = read_word_cs5460(P_register, fase);
				}
			if (aux_b10 == NRO_AMOSTRAS_CHT)
				{
				break;
				}
			if (aux_b20 >= NRO_AMOSTRAS_CHT)
				{
				aux_b20 = 0;
				}
			ler_cs5460 = 0;
			}

		}
	lendo_cht_cs5460 = 0;

	disable_interrupts(INT_TIMER3);
	enable_interrupts(INT_TIMER1);
}

void le_sinal_fp(char fase)	
{
	if (fase == 'R')
		{
		aux_b2 = 0;
		}
	else if (fase == 'S')
		{
		aux_b2 = 1;
		}
	else if (fase == 'T')
		{
		aux_b2 = 2;
		}
	else
		{
		return;
		}

	aux_sw1 = buffer_t[0];
	if (aux_sw1 > 0)
		{
		zero_r = 1;
		}
	else
		{
		zero_r = 0;
		}	

	for (aux_b1 = 0; aux_b1 < NRO_AMOSTRAS_CHT; aux_b1++)
		{
		aux_sw1 = buffer_t[aux_b1];
		aux_sw2 = buffer_c[aux_b1];

		if (aux_sw1 > 0)
			{
			if (zero_r == 0)
				{
				if (aux_sw2 > 0)
					{
					sinal_fp[aux_b2] = '+';
					}
				else
					{
					sinal_fp[aux_b2] = '-';
					}
				break;
				}
			}
		else
			{
			if (zero_r == 1)
				{
				if (aux_sw2 > 0)
					{
					sinal_fp[aux_b2] = '-';
					}
				else
					{
					sinal_fp[aux_b2] = '+';
					}
				break;
				}
			}
		}
}



void calcula_tensao_corrente(void)
{

	aux_w1 = read_word_cs5460(V_rms,'R');
	aux_w1 = aux_w1 >> 1;
	soma_efi_tr += aux_w1;

	aux_w1 = read_word_cs5460(V_rms,'S');
	aux_w1 = aux_w1 >> 1;   // este calculo dá um fundo de escala de 735V, debtro da especificação de 600V FN.
	soma_efi_ts += aux_w1;

	aux_w1 = read_word_cs5460(V_rms,'T');
	aux_w1 = aux_w1 >> 1;   // este calculo dá um fundo de escala de 735V, debtro da especificação de 600V FN.
	soma_efi_tt += aux_w1;

	aux_l2 = 0;
	aux_l2 = valor_tc;
	aux_l2 = aux_l2 << 3;

	aux_l1 = read_word_cs5460(I_rms,'R');
	aux_l1 = aux_l1 * aux_l2;
	aux_l1 = aux_l1 / 32768;   // este calculo dá um fundo de escala de valor do tc, debtro da especificação de 600V FN.
	soma_efi_cr += aux_l1;

	aux_l1 = read_word_cs5460(I_rms,'S');
	aux_l1 = aux_l1 * aux_l2;
	aux_l1 = aux_l1 / 32768;   // este calculo dá um fundo de escala de valor do tc, debtro da especificação de 600V FN.
	soma_efi_cs += aux_l1;

	aux_l1 = read_word_cs5460(I_rms,'T');
	aux_l1 = aux_l1 * aux_l2;
	aux_l1 = aux_l1 / 32768;   // este calculo dá um fundo de escala de valor do tc, debtro da especificação de 600V FN.
	soma_efi_ct += aux_l1;

	aux_ener_l = read_cs5460(E_register,'R');
	if (datah & 0x80)
		{
		aux_ener_l = ~aux_ener_l;
		aux_ener_l = aux_ener_l & 0x00ffffff;
		sentido_r = 1;
		}
	else
		{
		sentido_r = 0;
		}

	aux_l2 = 0;
	aux_l2 = valor_tc;
	aux_l2 = (int32)(aux_l2 << 5);
	aux_l2 = (int32)(aux_l2 / 1000);


	aux_l1 = aux_ener_l >> 8;
	aux_l1 = (int32)(aux_l1 * aux_l2);
	aux_l1 = (int32)(aux_l1 >> 5);
	soma_efi_pr += aux_l1;



	aux_ener_l = read_cs5460(E_register,'S');
	if (datah & 0x80)
		{
		aux_ener_l = ~aux_ener_l;
		aux_ener_l = aux_ener_l & 0x00ffffff;
		sentido_s = 1;
		}
	else
		{
		sentido_s = 0;
		}

	aux_l1 = aux_ener_l >> 8;
	aux_l1 = (int32)(aux_l1 * aux_l2);
	aux_l1 = (int32)(aux_l1 >> 5);
	soma_efi_ps += aux_l1;

	aux_ener_l = read_cs5460(E_register,'T');
	if (datah & 0x80)
		{
		aux_ener_l = ~aux_ener_l;
		aux_ener_l = aux_ener_l & 0x00ffffff;
		sentido_t = 1;
		}
	else
		{
		sentido_t = 0;
		}

	aux_l1 = aux_ener_l >> 8;
	aux_l1 = (int32)(aux_l1 * aux_l2);
	aux_l1 = (int32)(aux_l1 >> 5);
	soma_efi_pt += aux_l1;

	lendo_cht_cs5460 = 0;
	aguarda_cruzar_zero('T');
	le_seno('T');
	soma_pt = 0;
	for (aux_b1 = 0; aux_b1 < NRO_AMOSTRAS_CHT; aux_b1++)
		{
		aux_sl1 = buffer_t[aux_b1];
		aux_sl2 = buffer_c[aux_b1];
		soma_pt += (signed int32)(aux_sl1 * aux_sl2);
		}

	soma_pt = (signed int32)((soma_pt / NRO_AMOSTRAS_CHT));


	conta_media_ten++;
	if (conta_media_ten == nro_media_amostras)
		{
		aux_l1 = soma_efi_tr >> nro_desloca;
		aux_l2 = (signed word)(1000 + os_ten_r);
		aux_l2 = aux_l2 * aux_l1;
		tensao_r = (word)(aux_l2 / 1000);

		aux_l1 = soma_efi_ts >> nro_desloca;
		aux_l2 = (signed word)(1000 + os_ten_s);
		aux_l2 = aux_l2 * aux_l1;
		tensao_s = (word)(aux_l2 / 1000);

		aux_l1 = soma_efi_tt >> nro_desloca;
		aux_l2 = (signed word)(1000 + os_ten_t);
		aux_l2 = aux_l2 * aux_l1;
		tensao_t = (word)(aux_l2 / 1000);

		aux_l1 = soma_efi_cr >> nro_desloca;
		aux_l2 = (signed word)(1000 + os_cor_r);
		aux_l2 = aux_l2 * aux_l1;
		corrente_r = (word)(aux_l2 / 1000);

		aux_l1 = soma_efi_cs >> nro_desloca;
		aux_l2 = (signed word)(1000 + os_cor_s);
		aux_l2 = aux_l2 * aux_l1;
		corrente_s = (word)(aux_l2 / 1000);

		aux_l1 = soma_efi_ct >> nro_desloca;
		aux_l2 = (signed word)(1000 + os_cor_t);
		aux_l2 = aux_l2 * aux_l1;
		corrente_t = (word)(aux_l2 / 1000);

		aux_l1 = soma_efi_pr >> nro_desloca;
		aux_l2 = (signed word)(1000 + os_cor_r + os_ten_r);
		aux_l2 = aux_l2 * aux_l1;
		pot_ativa_r = (word)(aux_l2 / 1000);

		aux_l1 = soma_efi_ps >> nro_desloca;
		aux_l2 = (signed word)(1000 + os_cor_s + os_ten_s);
		aux_l2 = aux_l2 * aux_l1;
		pot_ativa_s = (word)(aux_l2 / 1000);

		aux_l1 = soma_efi_pt >> nro_desloca;
		aux_l2 = (signed word)(1000 + os_cor_t + os_ten_t);
		aux_l2 = aux_l2 * aux_l1;
		pot_ativa_t = (word)(aux_l2 / 1000);


		soma_efi_tr = 0;
		soma_efi_ts = 0;
		soma_efi_tt = 0;
		soma_efi_cr = 0;
		soma_efi_cs = 0;
		soma_efi_ct = 0;
		soma_efi_pr = 0;
		soma_efi_ps = 0;
		soma_efi_pt = 0;

		if (tensao_r > 255)
			{
			if (corrente_r > 8)
				{
				aguarda_cruzar_zero('R');
				le_seno('R');
				le_sinal_fp('R');
				}
			else
				{
				sinal_fp[0] = '1';
				sentido_r = 0;
				}
			}
		else
			{
			sinal_fp[0] = '1';
			sentido_r = 0;
			}

		if (tensao_s > 255)
			{
			if (corrente_s > 8)
				{
				aguarda_cruzar_zero('S');
				le_seno('S');
				le_sinal_fp('S');
				}
			else
				{
				sinal_fp[1] = '1';
				sentido_s = 0;
				}
			}
		else
			{
			sinal_fp[1] = '1';
			sentido_s = 0;
			}
		if (tensao_t > 255)
			{
			if (corrente_t > 8)
				{
				aguarda_cruzar_zero('T');
				le_seno('T');
				le_sinal_fp('T');
				}
			else
				{
				sentido_t = 0;
				sinal_fp[2] = '1';
				}
			}
		else
			{
			sinal_fp[2] = '1';
			sentido_t = 0;
			}



		conta_media_ten = 0;
		calc_ten_ok = 1;
		
		}

	med_ten_ok = 0;

}


#define mul_kw 870 	// (1,36 * 1,25 * 1,4142 * 1,4142 ) * 256



