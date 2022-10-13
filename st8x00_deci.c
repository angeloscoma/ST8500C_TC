/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ROTINAS                               	                     *
; Funcao: MODULO DE ROTINAS DE COMUNICACAO								 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 01/08/2003                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/


#define printar false

short comuni_ok;



char trata_desligamentos(char);
#if (controle_por_fase == true)
	char trata_desligamentos_old(char);
	char trata_acionamentos_old(char);
#else
	char trata_desligamentos_old(void);
	char trata_acionamentos_old(void);
#endif


#if (AUTOSET == true)
	#include "autoset.c"
#endif

void trata_tempo_falta_energia(void)
{
//	char aux_b1;
//	faltou_energia = FALSE;
	
//	if (tempo_falta_energia != 0)
//		{
//		tempo_falta_energia--;
//		aux_tempo_aciona = tempo_desaciona;
//		if (tempo_falta_energia == 0)
//			{
//			saida2 = 0;
//			saida3 = 0;
//			faltou_energia = true;
//			output_high (CSIO1);
//			output_high (CSIO4);
//			
//			output_01 = saida2;
//			output_low(CSIO2);
//			output_d(output_01);
//			output_high(CSIO2);
//	
//			output_01 = saida3;
//			output_low(CSIO3);
//			output_d(output_01);
//			output_high(CSIO3);
//			
//			for (aux_b1 = 0; aux_b1 < NRO_MAXIMO_BANCOS_CAPACITOR; aux_b1--)
//				{
//				aux_tempo_repouso[aux_b1] = tempo_repouso[aux_b1];
//				banco_acionado[aux_b1] = 0;
//				}
//			}
//		}
}

void apaga_tempos(void)
{					
	for (data1 = 0; data1 < NRO_MAXIMO_BANCOS_CAPACITOR; data1++)
		{
		minuteiro[data1] = 0;
		horimetro[data1] = 0;
		acionamentos[data1] = 0;
		write_byte(ee_minuteiro + data1, 0);
		write_word(ee_horimetro + (data1 * 2), 0);
		write_word(ee_acionamentos + (data1 * 2), 0);
		}
}


#if (controle_por_fase == true)
	void calcula_kvar_float(char fase)
#else
	void calcula_kvar_float(void)
#endif
{
	float valorf;

	#if (monofasico == true)
		if (cor_min == true)
			{
			if (min_kvar != 0)
				{
				if (status_banco_minimo == 0)
					{
					pot_req_r = 0;
					pot_exec_r = min_kvar;
					pot_exec_r = pot_exec_r * 16;
					if (tudo_desligado == true)
						{
						status_banco_minimo = 1;
						}
					}
				else
					{
					if (status_banco_minimo != 2)
						{
						if (total_acionado < min_kvar)
							{
							pot_req_r = min_kvar;
							pot_exec_r = 0;
							}
						else if (total_acionado > min_kvar)
							{
							pot_req_r = 0;
							pot_exec_r = min_kvar;
							}
						else
							{
							#if (com_regs == true)
								if (status_banco_minimo != 2)
									{
									 grava_ocorrencias(reg_em_banco_minimo);
									 }
							#endif
							pot_req_r = 0;
							pot_exec_r = 0;
							status_banco_minimo = 2;
							}
						pot_req_r = pot_req_r * 16;
						pot_exec_r = pot_exec_r * 16;
						}
					else
						{	
						if (total_acionado < min_kvar)
							{
							status_banco_minimo = 1;
							}
						pot_req_r = 0;
						pot_exec_r = 0;
						}
					}
				}
			else
				{
				pot_req_r = 0;
				pot_exec_r = 0;
				}
			}
			
		valorf = (float)(pot_req_r);
		valorf = (float)(mul_tc * valorf);
		kvar_req = (float)(valorf / 16);
	
		valorf = (float)(pot_exec_r);
		valorf = (float)(mul_tc * valorf);
		kvar_exec = (float)(valorf / 16);
			
	#else
		#if (controle_por_fase == true)
			if (fase == 'R')
				{
				ifase = 0;
				}
			else if (fase == 'S')
				{
				ifase = 1;
				}
			else
				{
				ifase = 2;
				}
		
			if (cor_min == true)
				{
				if (min_kvar != 0)
					{
					if (status_banco_minimo == 0)
						{
						if (fase == 'R')
							{
							pot_exec_r = max_kvar * 16;
							pot_req_r = 0;
							ifase = 0;
							}
						else if (fase == 'S')
							{
							pot_exec_s = max_kvar * 16;
							pot_req_s = 0;
							ifase = 1;
							}
						else
							{
							pot_exec_t = max_kvar * 16;
							pot_req_t = 0;
							ifase = 2;
							}
						if (tudo_desligado == true);
							{
							status_banco_minimo = 1;
							}
						}
					else
						{
						if (status_banco_minimo != 2)
							{
							if (total_acionado[ifase] < min_kvar)
								{
								if (fase == 'R')
									{
									pot_exec_r = 0;
									pot_req_r = min_kvar * 16;
									}
								else if (fase == 'S')
									{
									pot_exec_s = 0;
									pot_req_s = min_kvar * 16;
									}
								else
									{
									pot_exec_t = 0;
									pot_req_t = min_kvar * 16;
									}
								}
							else if (total_acionado[ifase] > min_kvar)
								{
								if (fase == 'R')
									{
									pot_exec_r = min_kvar * 16;
									pot_req_r = 0;
									}
								else if (fase == 'S')
									{
									pot_exec_s = min_kvar * 16;
									pot_req_s = 0;
									}
								else
									{
									pot_exec_t = min_kvar * 16;
									pot_req_t = 0;
									}
								}
							else
								{
								if (fase == 'R')
									{
									pot_exec_r = 0;
									pot_req_r = 0;
									}
								else if (fase == 'S')
									{
									pot_exec_s = 0;
									pot_req_s = 0;
									}
								else
									{
									pot_exec_t = 0;
									pot_req_t = 0;
									}
								#if (com_regs == true)
									if (status_banco_minimo != 2)
										{
										 grava_ocorrencias(reg_em_banco_minimo);
										 }
								#endif
								status_banco_minimo = 2;
								}
							}
						else
							{	
							if (total_acionado[ifase] < min_kvar)
								{
								status_banco_minimo = 1;
								}
							if (fase == 'R')
								{
								pot_exec_r = 0;
								pot_req_r = 0;
								}
							else if (fase == 'S')
								{
								pot_exec_s = 0;
								pot_req_s = 0;
								}
							else
								{
								pot_exec_t = 0;
								pot_req_t = 0;
								}
							}
						}
					}
				else
					{
					if (fase == 'R')
						{
						pot_exec_r = 0;
						pot_req_r = 0;
						}
					else if (fase == 'S')
						{
						pot_exec_s = 0;
						pot_req_s = 0;
						}
					else
						{
						pot_exec_t = 0;
						pot_req_t = 0;
						}
					}
				}
			if (fase == 'R')
				{
				aux_l1 = pot_req_r;
				valorf = (float)(aux_l1);
				valorf = (float)(mul_tc * valorf);
				kvar_req = (float)(valorf / 16);
					
				aux_l1 = pot_exec_r;
				valorf = (float)(aux_l1);
				valorf = (float)(mul_tc * valorf);
				kvar_exec = (float)(valorf / 16);
				}
			else if (fase == 'S')
				{
				aux_l1 = pot_req_s;
				valorf = (float)(aux_l1);
				valorf = (float)(mul_tc * valorf);
				kvar_req = (float)(valorf / 16);
					
				aux_l1 = pot_exec_s;
				valorf = (float)(aux_l1);
				valorf = (float)(mul_tc * valorf);
				kvar_exec = (float)(valorf / 16);
				}
			else
				{
				aux_l1 = pot_req_t;
				valorf = (float)(aux_l1);
				valorf = (float)(mul_tc * valorf);
				kvar_req = (float)(valorf / 16);
					
				aux_l1 = pot_exec_t;
				valorf = (float)(aux_l1);
				valorf = (float)(mul_tc * valorf);
				kvar_exec = (float)(valorf / 16);
				}
				
		#else
			if (cor_min == true)
				{
				if (min_kvar != 0)
					{
					if (status_banco_minimo == 0)
						{
						pot_req_r = 0;
						pot_req_s = 0;
						pot_req_t = 0;
						pot_exec_r = max_kvar * 16;
						pot_exec_s = pot_exec_r;
						pot_exec_t = pot_exec_r;
						if (tudo_desligado == true)
							{
							status_banco_minimo = 1;
							}
						}
					else
						{
						if (status_banco_minimo != 2)
							{
							if (total_acionado < min_kvar)
								{
								pot_req_r = min_kvar * 16;
								pot_req_s = pot_exec_r;
								pot_req_t = pot_exec_r;
								pot_exec_r = 0;
								pot_exec_s = 0;
								pot_exec_t = 0;
								}
							else if (total_acionado > min_kvar)
								{
								pot_req_r = 0;
								pot_req_s = 0;
								pot_req_t = 0;
								pot_exec_r = min_kvar * 16;
								pot_exec_s = pot_exec_r;
								pot_exec_t = pot_exec_r;
								}
							else
								{
								pot_req_r = 0;
								pot_exec_r = 0;
								pot_req_s = 0;
								pot_exec_s = 0;
								pot_req_t = 0;
								pot_exec_t = 0;
								#if (com_regs == true)
									if (status_banco_minimo != 2)
										{
										 grava_ocorrencias(reg_em_banco_minimo);
										 }
								#endif
								status_banco_minimo = 2;
								}
							}
						else
							{	
							if (total_acionado < min_kvar)
								{
								status_banco_minimo = 1;
								}
							pot_req_r = 0;
							pot_exec_r = 0;
							pot_req_s = 0;
							pot_exec_s = 0;
							pot_req_t = 0;
							pot_exec_t = 0;
							}
						}
					}
				else
					{
					pot_req_r = 0;
					pot_exec_r = 0;
					pot_req_s = 0;
					pot_exec_s = 0;
					pot_req_t = 0;
					pot_exec_t = 0;
					}
				}
			aux_l1 = pot_req_r;
			aux_l1 += pot_req_s + pot_req_t;
	
			valorf = (float)(aux_l1 / 3);
			valorf = (float)(mul_tc * valorf);
			kvar_req = (float)(valorf / 16);
				
			aux_l1 = pot_exec_r;
			aux_l1 += pot_exec_s + pot_exec_t;
		
			valorf = (float)(aux_l1 / 3);
			valorf = (float)(mul_tc * valorf);
			kvar_exec = (float)(valorf / 16);
		#endif
	#endif

}


void recupera_tempos_acionamentos(void)
{
	for (aux_b1 = 0; aux_b1 < NRO_MAXIMO_BANCOS_CAPACITOR; aux_b1++)
		{
		minuteiro[aux_b1] = read_byte(ee_minuteiro + aux_b1);
		horimetro[aux_b1] = read_word(ee_horimetro + (aux_b1 * 2));
		acionamentos[aux_b1] = read_word(ee_acionamentos + (aux_b1 * 2));
		tempo_repouso[aux_b1] = read_byte(ee_tempo_repouso_1 + aux_b1);
		aux_tempo_repouso[aux_b1] = tempo_repouso[aux_b1];
		}
}

void salva_contadores(void)
{
	char aux_b1;
	for (aux_b1 = 0; aux_b1 < NRO_MAXIMO_BANCOS_CAPACITOR; aux_b1++)
		{
		write_byte(ee_minuteiro + aux_b1, minuteiro[aux_b1]);
		write_word(ee_horimetro + (aux_b1 * 2), horimetro[aux_b1]);
		write_word(ee_acionamentos + (aux_b1 * 2), acionamentos[aux_b1]);
		}
}

#if (disp_lcd == true)
	void trata_saidas(void)
	{
		output_01 = LED;
		output_low(CSIO1);
		output_d(output_01);
		output_high(CSIO1);
		
		output_low(CSIO4);
		output_d(0b00010000);
		output_high(CSIO4);
		
		output_01 = saida2;
		output_low(CSIO2);
		output_d(output_01);
		output_high(CSIO2);
	
		output_01 = saida3;
		output_low(CSIO3);
		output_d(output_01);
		output_high(CSIO3);
	}				
#endif



void trata_corrente_minima(void)
{
	#if (com_rep == true)
		if (modo_rep == 1)
			{
			aux_w1 = corrente_r / 8;
			if (aux_w1 < cor_minima_rep)
				{
				if (tudo_desligado == true)
					{
					cor_min_r = true;
					#if (monofasico == false)
						cor_min_s = true;
						cor_min_t = true;
					#endif
					}
				}
			else 
				{
				if (aux_w1 > cor_minima_rep)
					{
					cor_min_r = false;
					#if (monofasico == false)
						cor_min_s = false;
						cor_min_t = false;
					#endif
					}
				}
			return;
			}
	#endif
	#if (tc_fixo == true)
		aux_l1 = (valor_tc_fixo * 8);
	#else
		aux_l1 = valor_tc;
	#endif
	aux_w1 = (word)(((aux_l1 * cor_minima) / 100));
	aux_w2 = aux_w1 + 8;
	if (corrente_r < aux_w1)
		{
//		if (tudo_desligado == true)
			{
			cor_min_r = true;
			}
		}
	else 
		{
		if (corrente_r > aux_w2)
			{
			cor_min_r = false;
			}
		}
	#if (monofasico == false)
		if (corrente_s < aux_w1)
			{
			if (tudo_desligado == true)
				{
				cor_min_s = true;
				}
			}
		else 
			{
			if (corrente_s > aux_w2)
				{
				cor_min_s = false;
				}
			}
		if (corrente_t < aux_w1)
			{
			if (tudo_desligado == true)
				{
				cor_min_t = true;
				}
			}
		else 
			{
			if (corrente_t > aux_w2)
				{
				cor_min_t = false;
				}
			}
	#endif
}



void trata_desliga_ten_a(void)
{
	if (com_des_ten_a != 0)		/* SE PROGRAMACAO DIFERENTE DE ZERO COM CRITICA */
		{
		if ((tipo_ligacao == 0) || (tipo_ligacao == 2))
			{
			aux_w1 = ten_nomi;
			}
		else
			{
			aux_w1 = (int16)(ten_nomi * 1.7320508);
			}
// valor para tensao acima da minima			
		aux_w2 = aux_w1;
		aux_w3 = aux_w1;
		aux_w2 = (int16)(aux_w2 << 6);
// valor para tensao abaixo da minima		
		aux_w1 = 1 + (int16)((aux_w1 * com_des_ten_a)/100);
		aux_w1 = (int16)((aux_w1 + aux_w3) * 64);
		#if (monofasico == true)
			if (tensao_r > aux_w1)
				{
				if (des_ten_a == false)
					{
					des_ten_a = true;
					#if (com_regs == true)
     					grava_ocorrencias(reg_des_ten_alta);
     				#endif
     				}
				}
			else if (tensao_r < aux_w2)
				{
				des_ten_a = false;
				}
		#else
			if ((tensao_r > aux_w1) || (tensao_s > aux_w1) || (tensao_t > aux_w1))
				{
				if (des_ten_a == false)
					{
					des_ten_a = true;
     				grava_ocorrencias(reg_des_ten_alta);
     				}
				}
			else if ((tensao_r < aux_w2) && (tensao_s < aux_w2) && (tensao_t < aux_w2))
				{
				des_ten_a = false;
				}
		#endif
		}
	else
		{
		des_ten_a = false;
		}

}

void trata_desliga_ten_b(void)
{
	if (com_des_ten_b != 0)		/* SE PROGRAMACAO DIFERENTE DE ZERO COM CRITICA */
		{
		if ((tipo_ligacao == 0) || (tipo_ligacao == 2))
			{
			aux_w1 = ten_nomi;
			}
		else
			{
			aux_w1 = (int16)(ten_nomi * 1.7320508);
			}
// valor para tensao acima da minima			
		aux_w2 = aux_w1;
		aux_w3 = aux_w1;
		if (com_des_ten_b < 3)
			{
			aux_w2 = (int16)(aux_w2 << 6);
			}
		else
			{
			aux_w2 = 1 + (int16)((aux_w1 * (com_des_ten_b - 2))/100);
			aux_w2 = (int16)((aux_w3 - aux_w1) * 64);
			}
// valor para tensao abaixo da minima		
		aux_w1 = 1 + (int16)((aux_w1 * com_des_ten_b)/100);
		aux_w1 = (int16)((aux_w3 - aux_w1) * 64);
		#if (monofasico == true)
			if (tensao_r < aux_w1)
				{
				if (des_ten_b == false)
					{
					des_ten_b = true;
					#if (com_regs == true)
     					grava_ocorrencias(reg_des_ten_baixa);
     				#endif
     				}
				}
			else if (tensao_r > aux_w2)
				{
				des_ten_b = false;
				}
		#else
			if ((tensao_r < aux_w1) || (tensao_s < aux_w1) || (tensao_t < aux_w1))
				{
				if (des_ten_b == false)
					{
					des_ten_b = true;
     				grava_ocorrencias(reg_des_ten_baixa);
     				}
				}
			else if ((tensao_r > aux_w2) && (tensao_s > aux_w2) && (tensao_t > aux_w2))
				{
				des_ten_b = false;
				}
		#endif
		}
	else
		{
		des_ten_b = false;
		}

}

#if (com_cht == 1)
	void trata_desliga_chtt_a(void)
	{
		if (com_des_chtt == 0)
			{
			des_chtt = false;
			}
		else
			{
		/* Testa conteudo harmonico de tensao */				
			#if (monofasico == true)
				data1_int = (int16)(CHT_tr[0]);
			#else
				data1_int = (int16)((CHT_tr[0] + CHT_ts[0]  + CHT_tt[0]) / 3);
			#endif
			aux_w1 = com_des_chtt;
			aux_w1 = aux_w1 << 6;
			if ( data1_int > aux_w1)
				{
				des_chtt = true;
				}
			else
				{
				des_chtt = false;
				}
			}
	}

	void trata_desliga_chtc_a(void)
	{
		if (com_des_chtc == 0)
			{
			des_chtc = false;
			}
		else
			{
		/* Testa conteudo harmonico de tensao */				
			#if (monofasico == true)
				data1_int = (int16)(CHT_cr[0]);
			#else
				data1_int = (int16)((CHT_cr[0] + CHT_cs[0]  + CHT_ct[0]) / 3);
			#endif
			aux_w1 = com_des_chtc;
			aux_w1 = aux_w1 << 6;
			if ( data1_int > aux_w1)
				{
				des_chtc = true;
				}
			else
				{
				des_chtc = false;
				}
			}
	}
#endif



void ligar_banco(char banco)		
{
	char saida;

	ligou_banco = false;
	if (aux_tempo_repouso[banco] == 0)
		{
		if (banco_disponivel[banco] == true)
			{
			switch (banco)
				{
				case 0:
					{
					if (TRIAC_1 == false)
						{
						ligou_banco = true;
						}
					TRIAC_1 = true;
					break;
					}
				case 1:
					{
					if (TRIAC_2 == false)
						{
						ligou_banco = true;
						}
					TRIAC_2 = true;
					break;
					}
				case 2:
					{
					if (TRIAC_3 == false)
						{
						ligou_banco = true;
						}
					TRIAC_3 = true;
					break;
					}
				case 3:
					{
					if (TRIAC_4 == false)
						{
						ligou_banco = true;
						}
					TRIAC_4 = true;
					break;
					}
				case 4:
					{
					if (TRIAC_5 == false)
						{
						ligou_banco = true;
						}
					TRIAC_5 = true;
					break;
					}
				case 5:
					{
					if (TRIAC_6 == false)
						{
						ligou_banco = true;
						}
					TRIAC_6 = true;
					break;
					}
				case 6:
					{
					if (TRIAC_7 == false)
						{
						ligou_banco = true;
						}
					TRIAC_7 = true;
					break;
					}
				case 7:
					{
					if (TRIAC_8 == false)
						{
						ligou_banco = true;
						}
					TRIAC_8 = true;
					break;
					}
				case 8:
					{
					if (TRIAC_9 == false)
						{
						ligou_banco = true;
						}
					TRIAC_9 = true;
					break;
					}
				case 9:
					{
					if (TRIAC_10 == false)
						{
						ligou_banco = true;
						}
					TRIAC_10 = true;
					break;
					}
				case 10:
					{
					if (TRIAC_11 == false)
						{
						ligou_banco = true;
						}
					TRIAC_11 = true;
					break;
					}
				case 11:
					{
					if (TRIAC_12 == false)
						{
						ligou_banco = true;
						}
					TRIAC_12 = true;
					break;
					}
				case 12:
					{
					if (TRIAC_13 == false)
						{
						ligou_banco = true;
						}
					TRIAC_13 = true;
					break;
					}
				case 13:
					{
					if (TRIAC_14 == false)
						{
						ligou_banco = true;
						}
					TRIAC_14 = true;
					break;
					}
				case 14:
					{
					if (TRIAC_15 == false)
						{
						ligou_banco = true;
						}
					TRIAC_15 = true;
					break;
					}
				case 15:
					{
					if (TRIAC_16 == false)
						{
						ligou_banco = true;
						}
					TRIAC_16 = true;
					break;
					}
				}
			}
		}
	if (ligou_banco == true)
		{
		#if (printar == true)
			if (comuni_ok == 1)
				{
		       	fprintf(modbus,"\r\nLigou-%u;", banco + 1);
		       	}
		#endif
		acionamentos[banco]++;
		banco_acionado[banco] = true;
		}
	
}

void desligar_banco(char banco)		
{
	char saida;
	desligou_banco = false;

	switch (banco)
		{
		case 0:
			{
			if (TRIAC_1 == true)
				{
				desligou_banco = true;
				}
			TRIAC_1 = false;
			break;
			}
		case 1:
			{
			if (TRIAC_2 == true)
				{
				desligou_banco = true;
				}
			TRIAC_2 = false;
			break;
			}
		case 2:
			{
			if (TRIAC_3 == true)
				{
				desligou_banco = true;
				}
			TRIAC_3 = false;
			break;
			}
		case 3:
			{
			if (TRIAC_4 == true)
				{
				desligou_banco = true;
				}
			TRIAC_4 = false;
			break;
			}
		case 4:
			{
			if (TRIAC_5 == true)
				{
				desligou_banco = true;
				}
			TRIAC_5 = false;
			break;
			}
		case 5:
			{
			if (TRIAC_6 == true)
				{
				desligou_banco = true;
				}
			TRIAC_6 = false;
			break;
			}
		case 6:
			{
			if (TRIAC_7 == true)
				{
				desligou_banco = true;
				}
			TRIAC_7 = false;
			break;
			}
		case 7:
			{
			if (TRIAC_8 == true)
				{
				desligou_banco = true;
				}
			TRIAC_8 = false;
			break;
			}
		case 8:
			{
			if (TRIAC_9 == true)
				{
				desligou_banco = true;
				}
			TRIAC_9 = false;
			break;
			}
		case 9:
			{
			if (TRIAC_10 == true)
				{
				desligou_banco = true;
				}
			TRIAC_10 = false;
			break;
			}
		case 10:
			{
			if (TRIAC_11 == true)
				{
				desligou_banco = true;
				}
			TRIAC_11 = false;
			break;
			}
		case 11:
			{
			if (TRIAC_12 == true)
				{
				desligou_banco = true;
				}
			TRIAC_12 = false;
			break;
			}
		case 12:
			{
			if (TRIAC_13 == true)
				{
				desligou_banco = true;
				}
			TRIAC_13 = false;
			break;
			}
		case 13:
			{
			if (TRIAC_14 == true)
				{
				desligou_banco = true;
				}
			TRIAC_14 = false;
			break;
			}
		case 14:
			{
			if (TRIAC_15 == true)
				{
				desligou_banco = true;
				}
			TRIAC_15 = false;
			break;
			}
		case 15:
			{
			if (TRIAC_16 == true)
				{
				desligou_banco = true;
				}
			TRIAC_16 = false;
			break;
			}

		}

	if (desligou_banco == true)
		{
		aux_tempo_repouso[banco] = tempo_repouso[banco];
		banco_acionado[banco] = false;
		}
		
}


void trata_tempos_aciona_repouso(void)
{
   	
	for (aux_b1 = 0; aux_b1 < nro_bancos_capacitor; aux_b1++)
		{
		if (aux_tempo_repouso[aux_b1] > 0)
			{
			if (aux_tempo_repouso[aux_b1] > tempo_repouso[aux_b1])
				{
				aux_tempo_repouso[aux_b1] = tempo_repouso[aux_b1];
				}
			else
				{
				aux_tempo_repouso[aux_b1]--;
				}
			}
		}
	if (aux_tempo_aciona != 0)
		{
		aux_tempo_aciona--;
		}
	
		
}


// saida2 com os primeiros 8 bancos
// Saida3 com os ultimos 8 bancos
void trata_segundeiro(void)
{
	for (aux_b1 = 0; aux_b1 < nro_bancos_capacitor; aux_b1++)
		{
		if (banco_acionado[aux_b1] == 1)
			{
			segundeiro[aux_b1]++;
			if (segundeiro[aux_b1] > 59)
				{
				segundeiro[aux_b1] = 0;
				minuteiro[aux_b1]++;
				if (minuteiro[aux_b1]>59)
					{
					minuteiro[aux_b1] = 0;
					horimetro[aux_b1]++;
					write_byte(ee_minuteiro + aux_b1, minuteiro[aux_b1]);
					write_word(ee_horimetro + (aux_b1* 2), horimetro[aux_b1]);
					write_word(ee_acionamentos + (aux_b1 * 2), acionamentos[aux_b1]);
					}
				}
			}
		}
}



#if (controle_por_fase == true)
	void ve_total_acionado(char fase)
#else
	void ve_total_acionado()
#endif
{
	char aux_b1;
	word aux_w2;
	#if (controle_por_fase == true)
		if (fase == 'R')
			{
			banco_inicial = 0;
			banco_final = 5;
			ifase = 0;
			}
		else if (fase == 'S')
			{
			banco_inicial = 5;
			banco_final = 10;
			ifase = 1;
			}
		else if (fase == 'T')
			{
			banco_inicial = 10;
			banco_final = 15;
			ifase = 2;
			}
		else
			{
			banco_inicial = 0;
			banco_final = nro_bancos_capacitor;
			ifase = 0;
			}
		total_acionado[ifase] = 0;
	#else
		banco_inicial = 0;
		banco_final = nro_bancos_capacitor;
		total_acionado = 0;
	#endif
	for (aux_b1 = banco_inicial; aux_b1 < banco_final; aux_b1++)
		{
		if (banco_acionado[aux_b1] == 1)
			{
			#if (controle_por_fase == true)
				total_acionado[ifase] += banco_capacitor[aux_b1];
			#else
				total_acionado += banco_capacitor[aux_b1];
			#endif
			}
		}

	tudo_desligado = false;
	tudo_ligado = false;
	#if (controle_por_fase == true)
		if (total_acionado[ifase] == 0)
	#else
		if (total_acionado == 0)
	#endif
		{
		tudo_desligado = true;
		tudo_ligado = false;
		}
	else
		{
		aux_w2 = 0;
		for (aux_b1 = banco_inicial; aux_b1 < banco_final; aux_b1++)
			{
			if (banco_acionado[aux_b1] == 1)
				{
				aux_w2 += banco_capacitor[aux_b1];
				}
			}
		#if (controle_por_fase == true)
			if (total_acionado[ifase] == aux_w2)
		#else
			if (total_acionado == aux_w2)
		#endif
			{
			tudo_desligado = false;
			tudo_ligado = true;
			}
		}
}


char trata_desligamentos(char banco)
{
	desligou_banco = false;
	if (banco_disponivel[banco] == true)
		{
		desligar_banco(banco);
		}
	if (desligou_banco == true)
		{
		aux_tempo_aciona = tempo_desaciona;
		return(banco);
		}
	else
		{
		return(0xff);
		}
		
}


char trata_acionamentos(char banco)
{
	ligou_banco = false;
	if (banco_disponivel[banco] == true)
		{
		ligar_banco(banco);
		}
	#if (printar == true)
		if (comuni_ok == 1)
			{
		   	fprintf(modbus,"\r\nligou banco:%u", qbanco);
		   	}
	#endif
	if (ligou_banco == true)
		{
		aux_tempo_aciona = tempo_aciona;
		return(banco);
		}
	else
		{
		return(0xff);
		}
		
}


#if (controle_por_fase == true)
	void ve_menor_banco_disponivel(char fase)
#else
	void ve_menor_banco_disponivel(void)
#endif
{
	char aux_b1;
	#if (controle_por_fase == true)
		if (fase == 'R')
			{
			banco_inicial = 0;
			banco_final = 5;
			}
		else if (fase == 'S')
			{
			banco_inicial = 5;
			banco_final = 10;
			}
		else if (fase == 'T')
			{
			banco_inicial = 10;
			banco_final = 15;
			}
		else
			{
			banco_inicial = 0;
			banco_final = nro_bancos_capacitor;
			}
	#else
		banco_inicial = 0;
		banco_final = nro_bancos_capacitor;
	#endif
	
	proximo_banco = 255;
	for(aux_b1 = banco_inicial; aux_b1 < banco_final; aux_b1++)
		{
		if (kvar_req > 0) 
			{
			if (aux_tempo_repouso[aux_b1] == 0)
				{
				if (banco_acionado[aux_b1] == false)
					{
					if (proximo_banco > banco_capacitor[aux_b1])
						{
						proximo_banco = banco_capacitor[aux_b1];
						}
					}
				}
			}
		else if (kvar_exec > 0)
			{
			if (banco_acionado[aux_b1] == true)
				{
				if (proximo_banco > banco_capacitor[aux_b1])
					{
					proximo_banco = banco_capacitor[aux_b1];
					}
				}
			}
		}
	for(aux_b1 = banco_inicial; aux_b1 < banco_final; aux_b1++)
		{
		if (kvar_req > 0) 
			{
			if (aux_tempo_repouso[aux_b1] == 0)
				{
				if (banco_acionado[aux_b1] == 0)
					{
					if (proximo_banco == banco_capacitor[aux_b1])
						{
						banco_disponivel[aux_b1] = true;
						break;
						}
					}
				}
			}
		else if (kvar_exec > 0)
			{
			if (banco_acionado[aux_b1] == 1)
				{
				if (proximo_banco == banco_capacitor[aux_b1])
					{
					banco_disponivel[aux_b1] = true;
					break;
					}
				}
			}
		}										
	
}


#if (controle_por_fase == true)
	void ve_banco_disponivel(char fase)
#else
	void ve_banco_disponivel(void)
#endif
{
	char aux_b1;
	#if (controle_por_fase == true)
		if (fase == 'R')
			{
			banco_inicial = 0;
			banco_final = 5;
			ifase = 0;
			}
		else if (fase == 'S')
			{
			banco_inicial = 5;
			banco_final = 10;
			ifase = 1;
			}
		else if (fase == 'T')
			{
			banco_inicial = 10;
			banco_final = 15;
			ifase = 2;
			}
		else
			{
			banco_inicial = 0;
			banco_final = nro_bancos_capacitor;
			ifase = 0;
			}
		kvar_disponivel[ifase] = 0;
	#else
		banco_inicial = 0;
		banco_final = nro_bancos_capacitor;
		kvar_disponivel = 0;
	#endif
	for(aux_b1 = banco_inicial; aux_b1 < banco_final; aux_b1++)
		{
		banco_disponivel[aux_b1] = false;
		}
		
	if (cor_min == true)
		{
		aux_b1 = banco_final + 1;
		do
			{
			aux_b1--;
			if (aux_tempo_repouso[aux_b1] == 0)
				{
				if (cor_min == true)
					{
					if (min_kvar != 0 )
						{
						if (kvar_req > 0)
							{
							if (banco_acionado[aux_b1] == 0)
								{
								#if (controle_por_fase == true)
									if (total_acionado[ifase] < min_kvar)
								#else
									if (total_acionado < min_kvar)
								#endif
									{
									if (banco_capacitor[aux_b1] <= min_kvar)
										{
										#if (controle_por_fase == true)
											if (kvar_disponivel[ifase] < min_kvar)
										#else
											if (kvar_disponivel < min_kvar)
										#endif
											{
											#if (controle_por_fase == true)
												kvar_disponivel[ifase] += banco_capacitor[aux_b1];
											#else
												kvar_disponivel += banco_capacitor[aux_b1];
											#endif
											banco_disponivel[aux_b1] = true;
											}
										else
											{
											break;
											}
										}
									}
								else
									{
									break;
									}
								}
							}
						else if (kvar_exec > 0)
							{
							if (banco_acionado[aux_b1] == 1)
								{
								#if (controle_por_fase == true)
									if (total_acionado[ifase] > min_kvar)
								#else
									if (total_acionado > min_kvar)
								#endif
									{
									if (banco_capacitor[aux_b1] >= min_kvar)
										{
										#if (controle_por_fase == true)
											if (kvar_disponivel[ifase] > min_kvar)
										#else
											if (kvar_disponivel > min_kvar)
										#endif
											{
											#if (controle_por_fase == true)
												kvar_disponivel[ifase] += banco_capacitor[aux_b1];
											#else
												kvar_disponivel += banco_capacitor[aux_b1];
											#endif
											banco_disponivel[aux_b1] = true;
											}
										else
											{
											break;
											}
										}
									}
								else
									{
									break;
									}
								}
							}
						}
					}
				}
			}
		while (aux_b1 != banco_inicial);
/*		
		for(aux_b1 = banco_final; aux_b1 > banco_inicial; aux_b1--)
			{
			if (aux_tempo_repouso[aux_b1] == 0)
				{
				if (cor_min == true)
					{
					if (min_kvar != 0 )
						{
						if (kvar_req > 0)
							{
							if (banco_acionado[aux_b1] == 0)
								{
								#if (controle_por_fase == true)
									if (total_acionado[ifase] < min_kvar)
								#else
									if (total_acionado < min_kvar)
								#endif
									{
									if (banco_capacitor[aux_b1] <= min_kvar)
										{
										#if (controle_por_fase == true)
											if (kvar_disponivel[ifase] < min_kvar)
										#else
											if (kvar_disponivel < min_kvar)
										#endif
											{
											#if (controle_por_fase == true)
												kvar_disponivel[ifase] += banco_capacitor[aux_b1];
											#else
												kvar_disponivel += banco_capacitor[aux_b1];
											#endif
											banco_disponivel[aux_b1] = true;
											}
										else
											{
											break;
											}
										}
									}
								else
									{
									break;
									}
								}
							}
						else if (kvar_exec > 0)
							{
							if (banco_acionado[aux_b1] == 1)
								{
								#if (controle_por_fase == true)
									if (total_acionado[ifase] > min_kvar)
								#else
									if (total_acionado > min_kvar)
								#endif
									{
									if (banco_capacitor[aux_b1] >= min_kvar)
										{
										#if (controle_por_fase == true)
											if (kvar_disponivel[ifase] > min_kvar)
										#else
											if (kvar_disponivel > min_kvar)
										#endif
											{
											#if (controle_por_fase == true)
												kvar_disponivel[ifase] += banco_capacitor[aux_b1];
											#else
												kvar_disponivel += banco_capacitor[aux_b1];
											#endif
											banco_disponivel[aux_b1] = true;
											}
										else
											{
											break;
											}
										}
									}
								else
									{
									break;
									}
								}
							}
						}
					}
				}
			}
*/			
		}
	else if (kvar_exec > 0)
		{
		for(aux_b1 = banco_inicial; aux_b1 < banco_final; aux_b1++)
			{
			if (banco_acionado[aux_b1] == true)
				{
				#if (controle_por_fase == true)
					if (kvar_disponivel[ifase] <= kvar_exec)
				#else
					if (kvar_disponivel <= kvar_exec)
				#endif
					{
					if (banco_capacitor[aux_b1] <= kvar_exec)
						{
						#if (controle_por_fase == true)
							kvar_disponivel[ifase] += banco_capacitor[aux_b1];
						#else
							kvar_disponivel += banco_capacitor[aux_b1];
						#endif
						banco_disponivel[aux_b1] = true;
						if (max_kvar != 0)
							{
							#if (controle_por_fase == true)
								if (kvar_disponivel[ifase] >= max_kvar)
							#else
								if (kvar_disponivel >= max_kvar)
							#endif
								{
								break;
								}
							}
						}
					else
						{
						if (banco_capacitor[aux_b1] <= menor_banco)
							{
							#if (controle_por_fase == true)
								kvar_disponivel[ifase] += banco_capacitor[aux_b1];
							#else
								kvar_disponivel += banco_capacitor[aux_b1];
							#endif
							banco_disponivel[aux_b1] = true;
							if (max_kvar != 0)
								{
								#if (controle_por_fase == true)
									if (kvar_disponivel[ifase] >= max_kvar)
								#else
									if (kvar_disponivel >= max_kvar)
								#endif
									{
									break;
									}
								}
							}
						}
					}
				else
					{
					break;
					}
				}
			}
		}
	else
		{
		aux_b1 = banco_final + 1;	//
		do							//
			{						//	
			aux_b1--;				//
//		for(aux_b1 = banco_final; aux_b1 > banco_inicial; aux_b1--)
//			{
			if (aux_tempo_repouso[aux_b1] == 0)
				{
				if (banco_acionado[aux_b1] == 0)
					{
					#if (controle_por_fase == true)
						if (kvar_disponivel[ifase] <= kvar_req)
					#else
						if (kvar_disponivel <= kvar_req)
					#endif
						{
						if (banco_capacitor[aux_b1] <= kvar_req)
							{
							#if (controle_por_fase == true)
								kvar_disponivel[ifase] += banco_capacitor[aux_b1];
							#else
								kvar_disponivel += banco_capacitor[aux_b1];
							#endif
							banco_disponivel[aux_b1] = true;
							if (max_kvar != 0)
								{
								#if (controle_por_fase == true)
									if (kvar_disponivel[ifase] >= max_kvar)
								#else
									if (kvar_disponivel >= max_kvar)
								#endif
									{
									break;
									}
								}
							}
						else
							{
							if (banco_capacitor[aux_b1] <= (menor_banco * 2))
								{
								#if (controle_por_fase == true)
									kvar_disponivel[ifase] += banco_capacitor[aux_b1];
								#else
									kvar_disponivel += banco_capacitor[aux_b1];
								#endif
								banco_disponivel[aux_b1] = true;
								if (max_kvar != 0)
									{
									#if (controle_por_fase == true)
										if (kvar_disponivel[ifase] >= max_kvar)
									#else
										if (kvar_disponivel >= max_kvar)
									#endif
										{
										break;
										}
									}
								}
							}
						}
					else
						{
						break;
						}
					}
				}
//			}
			}									//
		while (aux_b1 != banco_inicial);		//
		}
		#if (controle_por_fase == true)
			kvar_disponivel[ifase] = kvar_disponivel[ifase] / 2;
			if (kvar_disponivel[ifase] == 0)
		#else
			kvar_disponivel = kvar_disponivel / 2;
			if (kvar_disponivel == 0)
		#endif			
			{
			#if (controle_por_fase == true)
				ve_menor_banco_disponivel(fase);
			#else
				ve_menor_banco_disponivel();
			#endif
			}
		
}


#if (rotacionar == true)
	#if (controle_por_fase == true)
		void rotaciona_banco(char fase)
	#else	
		void rotaciona_banco(void)
	#endif
	{
		char aux_b1;
		#if (controle_por_fase == true)
			if (fase == 'R')
				{
				banco_inicial = 0;
				banco_final = 5;
				}
			else if (fase == 'S')
				{
				banco_inicial = 5;
				banco_final = 10;
				}
			else if (fase == 'T')
				{
				banco_inicial = 10;
				banco_final = 15;
				}
			else
				{
				banco_inicial = 0;
				banco_final = nro_bancos_capacitor;
				}
		#else
			banco_inicial = 0;
			banco_final = nro_bancos_capacitor;
		#endif
		
		if (sequencia == 1)
			{
			for (aux_b1 = banco_inicial; aux_b1 < banco_final; aux_b1++)
				{
				if (banco_acionado[aux_b1] == false)
					{
					#if (controle_por_fase == true)
						trata_desligamentos_old(fase);
					#else
						trata_desligamentos_old();
					#endif
					break;
					}
				}
			}
		else
			{
			if (cor_min == true)
				{
				#if (controle_por_fase == true)
					trata_desligamentos_old(false);
				#else
					trata_desligamentos_old();
				#endif
				}
			}
	}
#endif


void valida_acionamentos(void)
{		
//******************************************************************
// Validação dos acionamento e flags		
	for (aux_b1 = banco_inicial; aux_b1 < nro_bancos_capacitor; aux_b1++)
		{
		if (banco_acionado[aux_b1] == true)
			{
			ligar_banco(aux_b1);
			}
		else if (banco_acionado[aux_b1] > 1)
			{
			banco_acionado[aux_b1] = false;
			desligar_banco(aux_b1);
			}
		else if (banco_acionado[aux_b1] == false)
			{
			desligar_banco(aux_b1);
			}
		}
//******************************************************************
}


#if (controle_por_fase == true)
	void st8x00_decisao(char fase)
#else	
	void st8x00_decisao(void)
#endif
{
	char qbanco;
	#if (monofasico == true)
		signed word fator_pot;
	#endif

	#if (ST8100C == true)
		#if (simula_forno == true)
			return;
		#endif
	#endif

	#if (st8200c == true)
		#if (teste_aciona_rele == true)
			return;
		#endif
	#endif
	
	#if (AUTOSET == true)
		if (em_autoset == true)
			{
			auto_set();
			return;
			}
	#endif

	
	sentido = false;
	comuni_ok = false;

	#if (controle_por_fase == true)
		if (fase == 'R')
			{
			banco_inicial = 0;
			banco_final = 5;
			ifase = 0;
			}
		else if (fase == 'S')
			{
			banco_inicial = 5;
			banco_final = 10;
			ifase = 1;
			}
		else if (fase == 'T')
			{
			banco_inicial = 10;
			banco_final = 15;
			ifase = 2;
			}
		else
			{
			banco_inicial = 0;
			banco_final = nro_bancos_capacitor;
			ifase = 0;
			}
	#else
		banco_inicial = 0;
		banco_final = nro_bancos_capacitor;
	#endif


	#if ((com_rep == true) && (com_cht == false))
		des_chtt = false;
		des_chtc = false;
		if (modo_rep == 1)
			{
			sentido_r = false;
			sentido_s = false;
			sentido_t = false;
			}
	#endif

	if (com_manual == true)
		{
		#if (printar == true)
			if (comuni_ok == 1)
				{
		       	fprintf(modbus,"\r\nEm Manual");
		       	}
		#endif
		return;
		}
	
	
	if (aux_tempo_aciona == 0)
		{

		if (comuni_busy == 0)
			{
			comuni_ok = 1;
			}

		
		#if (printar == true)
		
	//	   	fprintf(modbus,"\r\n Na decisao!:%u  ;Distancia fase:%u", nro_bancos_capacitor, distancia_fase);
	//	   	fprintf(modbus,"\r\n Sinal FP=%c :fase_tmp:%ld  ;fase_tmp1:%lu", sinal_fp[0],fase_tmp, fase_tmp1);
		
		#endif		
		#if (com_rep == false)
			#if (monofasico == true)
				if (tensao_r < TENSAO_FALTA)
			#else
				if ((tensao_r < TENSAO_FALTA) && (tensao_s < TENSAO_FALTA) && (tensao_t < TENSAO_FALTA))
			#endif
				{
				#if (controle_por_fase == true)
					trata_desligamentos_old(fase);
				#else
					trata_desligamentos_old();
				#endif
				return;
				}
		#endif


		#if (DESLIGA_F5 == FALSE)
			for (aux_b1 = banco_final; aux_b1 < NRO_MAXIMO_BANCOS_CAPACITOR; aux_b1++)
				{
				desligar_banco(aux_b1);
				}
		#endif
		
		valida_acionamentos();
		
		#if (monofasico == true)
			if (sentido_r == true)
				{
				sentido = true;
				}
			if (cor_min_r == true)
				{
				cor_min = true;
				}
			else
				{
				cor_min = false;
				}
			fator_pot = fator_pot_r;
		#else
			if ((sentido_r == true) || (sentido_s == true) || ( sentido_t == true))
				{
				sentido = true;
				}
			if ((cor_min_r == true) && (cor_min_s == true) && (cor_min_t == true))
				{
				cor_min = true;
				}
			else
				{
				cor_min = false;
				}
				
		#endif


		#if (com_rep == true)
			if (modo_rep == 1)
				{
				if (time_out_modo_rep == 0)
					{
					#if (monofasico == true)
						if (pot_reativa_r == 0) 
					#else
						if ((pot_reativa_r == 0) && (pot_reativa_s == 0) && (pot_reativa_t == 0) )
					#endif
							{
							if (cor_min == false)
								{
								#if (controle_por_fase == true)
									trata_desligamentos_old(fase);
								#else
									trata_desligamentos_old();
								#endif
								return;
								}
							}
					}
				}
		#endif

		#if (controle_por_fase == true)
			ve_total_acionado(fase);
			calcula_kvar_float(fase);
			ve_banco_disponivel(fase);
		#else			
			ve_total_acionado();
			calcula_kvar_float();
			ve_banco_disponivel();
		#endif

		#if (printar == true)
			if (comuni_ok == 1)
				{
			   	fprintf(modbus,"\r\n\r\nTempos Repouso:");
				for (aux_b1 = banco_inicial; aux_b1 < banco_final; aux_b1++)
					{
			       	fprintf(modbus,"/%d",aux_tempo_repouso[aux_b1]);
					}
			   	fprintf(modbus,"\r\nAcionamentos:");
				for (aux_b1 = banco_inicial; aux_b1 < banco_final; aux_b1++)
					{
			       	fprintf(modbus,"/%lu", acionamentos[aux_b1]);
					}
			   	fprintf(modbus,"\r\nTempo acionado:");
				for (aux_b1 = banco_inicial; aux_b1 < banco_final; aux_b1++)
					{
			       	fprintf(modbus,"/%lu:%u", horimetro[aux_b1], minuteiro[aux_b1]);
					}
			   	fprintf(modbus,"\r\nBanco acionado:");
				for (aux_b1 = banco_inicial; aux_b1 < banco_final; aux_b1++)
					{
			       	fprintf(modbus,"/%u", banco_acionado[aux_b1]);
			       	}
			   	fprintf(modbus,"\r\nValor Bancos:");
				for (aux_b1 = banco_inicial; aux_b1 < banco_final; aux_b1++)
					{
			       	fprintf(modbus,"/%u", banco_capacitor[aux_b1]);
			       	}
			   	fprintf(modbus,"\r\nBanco Disponivel:");
				for (aux_b1 = banco_inicial; aux_b1 < banco_final; aux_b1++)
					{
			       	fprintf(modbus,"/%u", banco_disponivel[aux_b1]);
			       	}
			   }
		#endif
			
		#if (printar == true)
			if (comuni_ok == 1)
				{
			   	fprintf(modbus,"\r\nMáx=%u; Min=%u", max_kvar, min_kvar);
		 	  	fprintf(modbus,"\r\nAcionado=%lu;  Dispon=%f; Req=%f; Exc=%f, Prox:%u", total_acionado, kvar_disponivel, kvar_req,  kvar_exec, proximo_banco);
		 	  	}
		#endif


		if ((des_ten_a == true) || (des_ten_b == true) || (des_chtt == true) || (des_chtc == true))	// trata desligamentos
			{
			#if (printar == true)
				if (comuni_ok == 1)
					{
			       	fprintf(modbus,"\r\nTrata Desligamentos");
			       	}
			#endif
			#if (controle_por_fase == true)
				trata_desligamentos_old(fase);
			#else
				trata_desligamentos_old();
			#endif
			return;
			}

		
		if (cor_min == true)
			{
			if (sentido == false)	
				{
				#if (printar == true)
					if (comuni_ok == 1)
						{
				       	fprintf(modbus,"\r\nCor Minima: Kvar Acionado:%lu, Corrente:%lu; Kvar Minimo:%u; Status:%u", total_acionado, corrente_r, min_kvar, status_banco_minimo );
				       	}
				#endif
				}
			else
				{
				#if (printar == true)
					if (comuni_ok == 1)
						{
				       	fprintf(modbus,"\r\nTC Invertido");
				       	}
				#endif
				return;
				}
			}
		else
			{
			status_banco_minimo = 0;
			}
		if (kvar_req > 0)
			{
			#if (printar == true)
				if (comuni_ok == 1)
					{
			       	fprintf(modbus,"\r\nAcionado:%lu, Requerido:%f", total_acionado, kvar_req);
				   	fprintf(modbus,"\r\nBancos Disponiveis:");
					for (aux_b1 = banco_inicial; aux_b1 < banco_final; aux_b1++)
						{
				       	fprintf(modbus,"/%u", banco_disponivel[aux_b1]);
			    	   	}
			    	}
			#endif
			for (aux_b1 = banco_inicial; aux_b1 < banco_final; aux_b1++)
				{
				if (banco_disponivel[aux_b1] == true)
					{
					#if (printar == true)
						if (comuni_ok == 1)
							{
						   	fprintf(modbus,"\r\nLigando Banco:%u/%u", aux_b1,  banco_disponivel[aux_b1]);
					    	}
					#endif
					#if (rotacionar == true)
						if (sequencia == 1)
							{
							#if (controle_por_fase == true)
								trata_acionamentos_old(fase);
							#else
								trata_acionamentos_old();
							#endif
							if (cor_min == true)
								{
								break;
								}
							}
						else
							{
							trata_acionamentos(aux_b1);
							}
					#else
						trata_acionamentos(aux_b1);
					#endif
					}
				}
			}
		else if (kvar_exec > 0)
			{
			#if (printar == true)
				if (comuni_ok == 1)
					{
			       	fprintf(modbus,"\r\nDesacionado:%lu, Requerido:%f", total_acionado, kvar_exec);
			       	}
			#endif
			for (aux_b1 = banco_inicial; aux_b1 < banco_final; aux_b1++)
				{
				if (banco_acionado[aux_b1] == true)
					{
					if (sequencia == 1)
						{
						#if (controle_por_fase == true)
							aux_b2 =  trata_desligamentos_old(fase);
						#else
							aux_b2 =  trata_desligamentos_old();
						#endif
						#if (controle_por_fase == true)
							if (kvar_disponivel[ifase] > banco_capacitor[aux_b2])
							{
							kvar_disponivel[ifase] -= banco_capacitor[aux_b2];
							}
						#else
							if (kvar_disponivel > banco_capacitor[aux_b2])
							{
							kvar_disponivel -= banco_capacitor[aux_b2];
							}
						#endif
						else
							{
							break;
							}
						}
					else
						{
						trata_desligamentos(aux_b1);
						}
					}
				}
			}
		}
}





#if (controle_por_fase == true)
	char trata_desligamentos_old(char fase)
#else
	char trata_desligamentos_old(void)
#endif
{
	char tipo, aux_b1, aux_b2;
	word maior_hora;
	word maior_minuto;
	word menor_nro;
	char qbanco;
	maior_hora = 0;
	maior_minuto = 0;
	menor_nro = 0xffff;
	tipo = TUDO_IGUAL;

	#if (controle_por_fase == true)
		if (fase == 'R')
			{
			banco_inicial = 0;
			banco_final = 5;
			}
		else if (fase == 'S')
			{
			banco_inicial = 5;
			banco_final = 10;
			}
		else if (fase == 'T')
			{
			banco_inicial = 10;
			banco_final = 15;
			}
		else
			{
			banco_inicial = 0;
			banco_final = nro_bancos_capacitor;
			}
	#else
		banco_inicial = 0;
		banco_final = nro_bancos_capacitor;
	#endif
	
	for (aux_b2 = banco_inicial; aux_b2 < banco_final; aux_b2++)
		{
		if (banco_acionado[aux_b2] == true)
			{
			if (horimetro[aux_b2] >= maior_hora)
				{
				maior_hora = horimetro[aux_b2];
				}
			if (minuteiro[aux_b2] >= maior_minuto)
				{
				maior_minuto = minuteiro[aux_b2];
				}
			if (acionamentos[aux_b2] <= menor_nro)
				{
				menor_nro = acionamentos[aux_b2];
				}
			}
		}
	
	for (aux_b2 = banco_inicial; aux_b2 < banco_final; aux_b2++)
		{
		for (aux_b1 = aux_b2; aux_b1 < banco_final; aux_b1++)
			{
			if (banco_acionado[aux_b1] == true)
				{
				if (acionamentos[aux_b2] != acionamentos[aux_b1])
					{
					tipo = NRO_ACIONA_DIF;
					break;
					}
				}
			}
		if (tipo == NRO_ACIONA_DIF)
			{
			break;
			}
		}
	if (tipo == TUDO_IGUAL)
		{
		for (aux_b2 = banco_inicial; aux_b2 < banco_final; aux_b2++)
			{
			for (aux_b1 = aux_b2; aux_b1 < banco_final; aux_b1++)
				{
				if (banco_acionado[aux_b1] == true)
					{
					if (horimetro[aux_b2] != horimetro[aux_b1])
						{
						tipo = NRO_HORAS_DIF;
						break;
						}
					}
				}
			if (tipo == NRO_HORAS_DIF)
				{
				break;
				}
			}
		}
	if (tipo == TUDO_IGUAL)
		{
		for (aux_b2 = banco_inicial; aux_b2 < banco_final; aux_b2++)
			{
			for (aux_b1 = aux_b2; aux_b1 < banco_final; aux_b1++)
				{
				if (banco_acionado[aux_b1] == true)
					{
					if (minuteiro[aux_b2] != minuteiro[aux_b1])
						{
						tipo = NRO_MIN_DIF;
						break;
						}
					}
				}
			if (tipo == NRO_MIN_DIF)
				{
				break;
				}
			}
		}
	
	qbanco = 0xff;
	aux_b1 = banco_final;
	while (aux_b1 != banco_inicial)
		{
		aux_b1--;
		if (banco_acionado[aux_b1] == true)
			{
			switch (tipo)
				{
				case NRO_HORAS_DIF:
					{
					if (horimetro[aux_b1] == maior_hora)
						{
						qbanco = aux_b1;
						goto encerra_pesquisa;
						}
					break;
					}
				case NRO_MIN_DIF:
					{
					if (minuteiro[aux_b1] == maior_minuto)
						{
						qbanco = aux_b1;
						goto encerra_pesquisa;
						}
					break;
					}
				case TUDO_IGUAL:
				case NRO_ACIONA_DIF:
				default:
					{
					if (acionamentos[aux_b1] == menor_nro)
						{
						qbanco = aux_b1;
						goto encerra_pesquisa;
						}
					}
				}
			}
		}
	encerra_pesquisa:

	if (qbanco != 0xff)
		{
		desligar_banco(qbanco);
	
		if (desligou_banco == true)
			{
			if ((des_ten_a == true) || (des_ten_b == true))
				{
				aux_tempo_aciona = 1;
				}
			else
				{
				aux_tempo_aciona = tempo_desaciona;
				}
			return(qbanco);
			}
		else
			{
			return(0xff);
			}
		}
	else
		{
		for (aux_b1 = banco_inicial; aux_b1 < banco_final; aux_b1++)
			{
			if (banco_acionado[aux_b1] == true)
				{
				desligar_banco(aux_b1);
				if ((des_ten_a == true) || (des_ten_b == true))
					{
					aux_tempo_aciona = 1;
					}
				else
					{
					aux_tempo_aciona = tempo_desaciona;
					}
				return(aux_b1);
				}
			}
		}
		
}


#if (controle_por_fase == true)
	char trata_acionamentos_old(char fase)
#else
	char trata_acionamentos_old(void)
#endif
{
	char tipo, aux_b1, aux_b2;
	word menor_hora, menor_minuto ;
	word menor_nro;
	char qbanco;
	menor_hora = 0xffff;
	menor_minuto = 0xffff;
	menor_nro = 0xffff;
	tipo = TUDO_IGUAL;

	#if (controle_por_fase == true)
		if (fase == 'R')
			{
			banco_inicial = 0;
			banco_final = 5;
			}
		else if (fase == 'S')
			{
			banco_inicial = 5;
			banco_final = 10;
			}
		else if (fase == 'T')
			{
			banco_inicial = 10;
			banco_final = 15;
			}
		else
			{
			banco_inicial = 0;
			banco_final = nro_bancos_capacitor;
			}
	#else
		banco_inicial = 0;
		banco_final = nro_bancos_capacitor;
	#endif

	for (aux_b2 = banco_inicial; aux_b2 < banco_final; aux_b2++)
		{
		if (banco_disponivel[aux_b2] == true)
			{
			if (aux_tempo_repouso[aux_b2] == 0)
				{
				if (banco_acionado[aux_b2] == false)
					{
					if (horimetro[aux_b2] <= menor_hora)
						{
						menor_hora = horimetro[aux_b2];
						}
					if (minuteiro[aux_b2] <= menor_minuto)
						{
						menor_minuto = minuteiro[aux_b2];
						}
					if (acionamentos[aux_b2] <= menor_nro)
						{
						menor_nro = acionamentos[aux_b2];
						}
					}
				}
			}
		}
	
	for (aux_b2 = banco_inicial; aux_b2 < banco_final; aux_b2++)
		{
		for (aux_b1 = aux_b2; aux_b1 < banco_final; aux_b1++)
			{
			if (banco_disponivel[aux_b1] == true)
				{
				if (banco_acionado[aux_b1] == false)
					{
					if (acionamentos[aux_b2] != acionamentos[aux_b1])
						{
						tipo = NRO_ACIONA_DIF;
						break;
						}
					}
				}
			}
		if (tipo == NRO_ACIONA_DIF)
			{
			break;
			}
		}
	if (tipo == TUDO_IGUAL)
		{
		for (aux_b2 = banco_inicial; aux_b2 < banco_final; aux_b2++)
			{
			for (aux_b1 = aux_b2; aux_b1 < banco_final; aux_b1++)
				{
				if (banco_disponivel[aux_b1] == true)
					{
					if (banco_acionado[aux_b1] == false)
						{
						if (horimetro[aux_b2] != horimetro[aux_b1])
							{
							tipo = NRO_HORAS_DIF;
							break;
							}
						}
					}
				}
			}
		if (tipo == NRO_HORAS_DIF)
			{
			break;
			}
		}
	if (tipo == TUDO_IGUAL)
		{
		for (aux_b2 = banco_inicial; aux_b2 < banco_final; aux_b2++)
			{
			for (aux_b1 = aux_b2; aux_b1 < banco_final; aux_b1++)
				{
				if (banco_disponivel[aux_b1] == true)
					{
					if (banco_acionado[aux_b1] == false)
						{
						if (minuteiro[aux_b2] != minuteiro[aux_b1])
							{
							tipo = NRO_MIN_DIF;
							break;
							}
						}
					}
				}
			}
		if (tipo == NRO_MIN_DIF)
			{
			break;
			}
		}


		
	aux_b1 = banco_final;
	qbanco = 0xff;
	while (aux_b1 != banco_inicial)
		{
		aux_b1--;
		if (aux_tempo_repouso[aux_b1] == 0)
			{
			if (banco_disponivel[aux_b1] == true)
				{
				if (banco_acionado[aux_b1] == false)
					{
					switch (tipo)
						{
						case NRO_HORAS_DIF:
							{
							if (horimetro[aux_b1] == menor_hora)
								{
								qbanco = aux_b1;
								goto encerra_pesquisa;
								}
							break;
							}
						case NRO_MIN_DIF:
							{
							if (minuteiro[aux_b1] == menor_minuto)
								{
								qbanco = aux_b1;
								goto encerra_pesquisa;
								}
							break;
							}
						case TUDO_IGUAL:
						case NRO_ACIONA_DIF:
						default:
							{
							if (acionamentos[aux_b1] == menor_nro)
								{
								qbanco = aux_b1;
								goto encerra_pesquisa;
								}
							}
						}
					}
				}
			}
		}

	encerra_pesquisa:
	if (qbanco != 0xff)
		{	
	
		ligar_banco(qbanco);
	
		if (ligou_banco == true)
			{
			aux_tempo_aciona = tempo_aciona;
				
			return(qbanco);
			}
		else
			{
			return(0xff);
			}
		}
	else
		{
		for (aux_b1 = banco_inicial; aux_b2 < banco_final; aux_b1++)
			{
			if (aux_tempo_repouso[aux_b1] == 0)
				{
				if (banco_acionado[aux_b1] == false)
					{
					ligar_banco(aux_b1);
					aux_tempo_aciona = tempo_aciona;
					return(aux_b1);
					}
				}
			}
		}
		
}

char trata_acionamentos_old_old(void)
{
	char tipo, aux_b1;
	word maior_tempo;
	word menor_nro;
	char qbanco;
	qbanco = nro_bancos_capacitor - 1;
	maior_tempo = 0xffff;
	menor_nro = 0xffff;
	tipo = TUDO_IGUAL;
	for (aux_b1 = 0; aux_b1 < qbanco; aux_b1++)
		{
		if (banco_disponivel[aux_b1] == true)
			{
			if (banco_acionado[aux_b1] == 0)
				{
				if (acionamentos[0] != acionamentos[aux_b1])
					{
					tipo = NRO_ACIONA_DIF;
					break;
					}
				}
			}
		}
	if (tipo == TUDO_IGUAL)
		{
		for (aux_b1 = 0; aux_b1 < qbanco; aux_b1++)
			{
			if (banco_disponivel[aux_b1] == true)
				{
				if (banco_acionado[aux_b1] == 0)
					{
					if (horimetro[0] != horimetro[aux_b1])
						{
						tipo = NRO_HORAS_DIF;
						break;
						}
					}
				}
			}
		}
	if (tipo == TUDO_IGUAL)
		{
		for (aux_b1 = 0; aux_b1 < qbanco; aux_b1++)
			{
			if (banco_disponivel[aux_b1] == true)
				{
				if (banco_acionado[aux_b1] == 0)
					{
					if (minuteiro[0] != minuteiro[aux_b1])
						{
						tipo = NRO_MIN_DIF;
						break;
						}
					}
				}
			}
		}


		
	aux_b1 = nro_bancos_capacitor;
	while (aux_b1 != 0)
		{
		aux_b1--;
		if (banco_disponivel[aux_b1] == true)
			{
			if (banco_acionado[aux_b1] == 0)
				{
				switch (tipo)
					{
					case NRO_HORAS_DIF:
						{
						if (horimetro[aux_b1] < maior_tempo)
							{
							maior_tempo = horimetro[aux_b1];
							qbanco = aux_b1;
							}
						break;
						}
					case NRO_MIN_DIF:
						{
						if (minuteiro[aux_b1] < maior_tempo)
							{
							maior_tempo = minuteiro[aux_b1];
							qbanco = aux_b1;
							}
						break;
						}
					case TUDO_IGUAL:
					case NRO_ACIONA_DIF:
					default:
						{
						if (acionamentos[aux_b1] < menor_nro)
							{
							menor_nro = acionamentos[aux_b1];
							qbanco = aux_b1;
							}
						}
					}
				}
			}
		}

			
	ligou_banco = false;
	while (ligou_banco == false)			
		{
		if (banco_disponivel[qbanco] == true)
			{
			ligar_banco(qbanco);
			}
		#if (printar == true)
			if (comuni_ok == 1)
				{
			   	fprintf(modbus,"\r\nligou banco:%u", qbanco);
			   	}
		#endif
		if (qbanco != 0)
			{
			qbanco--;
			}
		else
			{
			break;
			}
		
		}
	if (ligou_banco == true)
		{
		aux_tempo_aciona = tempo_aciona;
			
		return(qbanco);
		}
	else
		{
		return(0xff);
		}
		
}

/*
void calcula_kvar_float_old(void)
{
	float valorf;

	#if (monofasico == true)
		if (cor_min == true)
			{
			if (status_banco_minimo == 0)
				{
				pot_req_r = 0;
				pot_exec_r = min_kvar;
				pot_exec_r = pot_exec_r * 16;
				if (tudo_desligado == true);
					{
					status_banco_minimo = 1;
					}
				}
			else
				{
				if (status_banco_minimo != 2)
					{
					if (min_kvar != 0)
						{
						if (total_acionado < min_kvar)
							{
							pot_req_r = min_kvar;
							pot_exec_r = 0;
							}
						else if (total_acionado > min_kvar)
							{
							pot_req_r = 0;
							pot_exec_r = min_kvar;
							}
						else
							{
							pot_req_r = 0;
							pot_exec_r = 0;
							#if (com_regs == true)
								if (status_banco_minimo != 2)
									{
									 grava_ocorrencias(reg_em_banco_minimo);
									 }
							#endif
							status_banco_minimo = 2;
							}
						pot_req_r = pot_req_r * 16;
						pot_exec_r = pot_exec_r * 16;
						}
					else
						{
						pot_req_r = 0;
						pot_exec_r = 0;
						}
					}
				else
					{	
					if (total_acionado < min_kvar)
						{
						status_banco_minimo = 1;
						}
					pot_req_r = 0;
					pot_exec_r = 0;
					}
				}
			}
			
		valorf = (float)(pot_req_r);
		valorf = (float)(mul_tc * valorf);
		kvar_req = (float)(valorf / 16);
	
		valorf = (float)(pot_exec_r);
		valorf = (float)(mul_tc * valorf);
		kvar_exec = (float)(valorf / 16);
			
	#else
		if (cor_min == true)
			{
			if (status_banco_minimo == 0)
				{
				pot_req_r = 0;
				pot_req_s = 0;
				pot_req_t = 0;
				pot_exec_r = max_kvar * 16;
				pot_exec_s = max_kvar * 16;
				pot_exec_t = max_kvar * 16;
				if (tudo_desligado == true);
					{
					status_banco_minimo = 1;
					}
				}
			else
				{
				if (status_banco_minimo != 2)
					{
					if (min_kvar != 0)
						{
						if (total_acionado < min_kvar)
							{
							pot_req_r = min_kvar * 16;
							pot_req_s = min_kvar * 16;
							pot_req_t = min_kvar * 16;
							pot_exec_r = 0;
							pot_exec_s = 0;
							pot_exec_t = 0;
							}
						else if (total_acionado > min_kvar)
							{
							pot_req_r = 0;
							pot_req_s = 0;
							pot_req_t = 0;
							pot_exec_r = min_kvar * 16;
							pot_exec_s = min_kvar * 16;
							pot_exec_t = min_kvar * 16;
							}
						else
							{
							pot_req_r = 0;
							pot_exec_r = 0;
							pot_req_s = 0;
							pot_exec_s = 0;
							pot_req_t = 0;
							pot_exec_t = 0;
							#if (com_regs == true)
								if (status_banco_minimo != 2)
									{
									 grava_ocorrencias(reg_em_banco_minimo);
									 }
							#endif
							status_banco_minimo = 2;
							}
						}
					else
						{
						pot_req_r = 0;
						pot_exec_r = 0;
						pot_req_s = 0;
						pot_exec_s = 0;
						pot_req_t = 0;
						pot_exec_t = 0;
						}
					}
				else
					{	
					if (total_acionado < min_kvar)
						{
						status_banco_minimo = 1;
						}
					pot_req_r = 0;
					pot_exec_r = 0;
					pot_req_s = 0;
					pot_exec_s = 0;
					pot_req_t = 0;
					pot_exec_t = 0;
					}
				}
		}
		aux_l1 = pot_req_r;
		aux_l1 += pot_req_s + pot_req_t;

		valorf = (float)(aux_l1 / 3);
		valorf = (float)(mul_tc * valorf);
		kvar_req = (float)(valorf / 16);
			
		aux_l1 = pot_exec_r;
		aux_l1 += pot_exec_s + pot_exec_t;
	
		valorf = (float)(aux_l1 / 3);
		valorf = (float)(mul_tc * valorf);
		kvar_exec = (float)(valorf / 16);

			
	#endif

}

*/
