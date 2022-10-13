/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: st_pots                                                        *
; Funcao: MODULO ROTINAS DE CALCULOS de potencias e FP					 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */

void zera_potencias(char);
void zera_chts_fase(char);	
void zera_corrente(char);


#if (tc_fixo == true)
void busca_mul_tc(void)
{
	#if (calcular_tc == true)
		char aux_bx;
		word aux_wx;
		for (aux_bx = 0; aux_bx < NRO_POSI_TC; aux_bx++)
			{
			aux_wx = tabela_tc[aux_bx];
			if (aux_wx == valor_tc)
				{
				mul_tc = (float)(valor_tc);
				mul_tc = (float)(mul_tc/5);
				mul_tc = (float)(mul_tc/100);
				break;
				}
			}
	#else
		mul_tc = 1;
	#endif
}
#endif


word ajusta_tc(word valor)
{
#if (tc_fixo == true)
	#if (calcular_tc == true)
		return((word)(mul_tc * valor));
	#else
		return(valor);
	#endif
#else
	return(valor);
#endif
}

void calcula_fundo_escala_corrente(void)
{
#if ((st5000t == true) | (st5030t == true) | (st9400r == true) | (st9430r == true) | (st_prog == true) | (st8610c == true))
	#if (tc_fixo == true)
//		aux_l2 = (int32)(valor_tc_fixo);
//		aux_l2 = (int32)(aux_l2 * 256);			// 8192 = 256*32
//		fundo_escala_corrente = (int32)(aux_l2 / 1000);
		fundo_escala_corrente = (valor_tc_fixo * 256 / 1000);
	#else
		aux_l2 = (int32)(valor_tc);
		aux_l2 = (int32)(aux_l2 * 256);			// 8192 = 256*32
		fundo_escala_corrente = (int32)(aux_l2 / 1000);
	#endif
#else
	mul_tc = (float)(1);
	aux_l2 = (int32)(valor_tc);
	aux_l2 = (int32)(aux_l2 * 8192);			// 8192 = 256*32
	fundo_escala_corrente = (int32)(aux_l2 / 1000);
#endif
}



#if (ade7754 == false)
	void zera_soma_pot(void)
		{
		delay_cycles(1);
		}
#endif


void calculo_potencias(char fase)
{
	if (fase == 'R')
		{
		delay_cycles(1);
		}
	
 }  


void zera_corrente(char fase)
{
	if (fase == 'R')
		{
		corrente_r = 0;
		sentido_r = 0;
		}
	#if (monofasico == false)
		else if (fase == 'S')
			{
			corrente_s = 0;
			sentido_s = 0;
			}
		else
			{
			corrente_t = 0;
			sentido_t = 0;
			}
	#endif
}

void zera_potencias(char fase)
{
	if (fase == 'R')
		{
		soma_pot_efi_r = 0;
		soma_pr = 0;
	    pot_ativa_r = 0;
	    pot_aparente_r = 0;
		pot_reativa_r = 0;
	   	fator_pot_r = 1024;
		pot_req_r = 0;
		pot_exec_r = 0;
		corrente_r = 0;
		sentido_r = 0;
		}
	#if (monofasico == false)
		else if (fase == 'S')
			{
			soma_pot_efi_s = 0;
			soma_ps = 0;
		    pot_ativa_s = 0;
		    pot_aparente_s = 0;
			pot_reativa_s = 0;
		   	fator_pot_s = 1024;
			pot_req_s = 0;
			pot_exec_s = 0;
			corrente_s = 0;
			sentido_s = 0;
			}
		else
			{
			soma_pot_efi_t = 0;
			soma_ps = 0;
		    pot_ativa_t = 0;
		    pot_aparente_t = 0;
			pot_reativa_t = 0;
		   	fator_pot_t = 1024;
			pot_req_t = 0;
			pot_exec_t = 0;
			corrente_t = 0;
			sentido_t = 0;
			}
	#endif
}

#if (com_cht == true)
	void zera_chts_fase(char fase)
	{
		for ( aux_b1 = 0; aux_b1 < (NRO_CHT/2); aux_b1++)
			{
			if (fase == 'R')
				{
				CHT_tr[aux_b1]=0;
			 	CHT_cr[aux_b1]=0;
				}
			else if (fase == 'S')
				{
				CHT_ts[aux_b1]=0;
			 	CHT_cs[aux_b1]=0;
				}
			else
				{
				CHT_tt[aux_b1]=0;
			 	CHT_ct[aux_b1]=0;
				}
			}
	}
#endif





