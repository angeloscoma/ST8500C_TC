/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: st92ROTA                                                        *
; Funcao: MODULO ROTINAS             									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */
  
#include "tab_z.c"


#define drad ((2 * PI) / NRO_AMOSTRAS_CHT)

void le_seno(char);


#if (com_modbus == true)
	void trata_modbus(void);
#endif

void cht_online (void);
void le_senoide_cht(void);
void calcula_qcht(void);
void le_tensao_r(void);
void le_tensao_s(void);
void le_tensao_t(void);

void le_corrente_r(void);
void le_corrente_s(void);
void le_corrente_t(void);
void zera_senoide(void);



void le_senoides(void)
{				
	char aux_b;
	word aux_w;

	lendo_cht = false;

	return;

	if (lendo_cht == false)
		{
		abre_leitura_cht = 1;
		lendo_cht = true;
		leu_senoide = false;
		passo_rd_cht = 0;
		time_out_int0 = 10;
		while (lendo_cht == true)
			{
#if (com_modbus == true)
			trata_modbus();
#endif
			if (time_out_int0 == 0)
				{
				lendo_cht = false;
				break;
				}
			}
		if (leu_senoide == true)
			{
			for (aux_b = 0; aux_b < NRO_AMOSTRAS_CHT; aux_b++)
				{	
				 aux_w =  buffer_cht[aux_b];
				if (passo_le_senoide == 0)
					{
					buf_tensao_r[aux_b] = aux_w;
					}
				else if (passo_le_senoide == 1)
					{
					buf_tensao_s[aux_b] = aux_w;
					}
				else if (passo_le_senoide == 2)
					{
					buf_tensao_t[aux_b] = aux_w;
					}
				else if (passo_le_senoide == 3)
					{
					buf_corrente_r[aux_b] = aux_w;
					}
				else if (passo_le_senoide == 4)
					{
					buf_corrente_s[aux_b] = aux_w;
					}
				else if (passo_le_senoide == 5)
					{
					buf_corrente_t[aux_b] = aux_w;
					}
				else 
					{
					passo_le_senoide = 255;
					}
#if (com_modbus == true)
				trata_modbus();
#endif
				}
			passo_le_senoide++;
			}
		}

}
             

void cht_online (void)
{
	short calcular_cht;

#if (com_regs == 1)

#endif
#if feira
	CHT_tr[0] = 12;
	CHT_ts[0] = 13;
	CHT_tt[0] = 11;
	CHT_cr[0] = 19;
	CHT_cs[0] = 22;
	CHT_ct[0] = 17;
	for (aux_b1 = 1; aux_b1 < NRO_CHT; aux_b1++)
		{
		pulsa_wdt();
		CHT_tr[aux_b1] = CHT_tr[aux_b1-1]/2;
		CHT_ts[aux_b1] = CHT_ts[aux_b1-1]/2;
		CHT_tt[aux_b1] = CHT_tt[aux_b1-1]/2;
		CHT_cr[aux_b1] = CHT_cr[aux_b1-1]/2;
		CHT_cs[aux_b1] = CHT_cs[aux_b1-1]/2;
		CHT_ct[aux_b1] = CHT_ct[aux_b1-1]/2;
		}
	return;
#endif
	
	if (qcht > (NRO_CHT+1))
		{
		qcht = 0;
		}

	calcular_cht = 1;
	if (qcht == 0)
 	 	{
		if (passo_cht == 1)
			{
			if (tensao_r < TENSAO_FALTA)
				{
				calcular_cht = 0;
			
				passo_cht++;
	 	 		}
			else
				{
				passo_le_senoide = 0;
				le_senoides();
				}
 	 		}
		else if (passo_cht == 2)
			{
			if (tensao_s < TENSAO_FALTA)
				{
				calcular_cht = 0;
				passo_cht++;
	 	 		}
			else
				{
				passo_le_senoide = 1;
				le_senoides();
				}
 	 		}
		else if (passo_cht == 3)
			{
			if (tensao_t < TENSAO_FALTA)
				{
				calcular_cht = 0;
				passo_cht++;
	 	 		}
			else
				{
				passo_le_senoide = 2;
				le_senoides();
				}
 	 		}
		else if (passo_cht == 4)
			{
			if (corrente_r < 8)
				{
				calcular_cht = 0;
				passo_cht++;
	 	 		}
			else
				{
				passo_le_senoide = 3;
				le_senoides();
				}
 	 		}
		else if (passo_cht == 5)
			{
			if (corrente_s < 8)
				{
				calcular_cht = 0;
				passo_cht++;
	 	 		}
			else
				{
				passo_le_senoide = 4;
				le_senoides();
				}
 	 		}
		else if (passo_cht == 6)
			{
			if (corrente_t < 8)
				{
				calcular_cht = 0;
				passo_cht++;
	 	 		}
			else
				{
				passo_le_senoide = 5;
				le_senoides();
				}
 	 		}
		else
			{
			calcular_cht = 0;
			qcht = 0;
			passo_cht = 1;
			}
		if (calcular_cht == 1)
			{				
			le_senoide_cht();
			SAN2 = 0;
			SBN2 = 0;
			qcht = 1;
			passo_qcht = 0;
			}
		else
			{
			qcht = 0;
			}
 	 	}

	else if (qcht == (NRO_CHT+1))
 	 	{
		SAP = (float)(sqrtx((float)(SAN2 + SBN2)));
		SAP = (float)(SAP / AP1);
		CHT = (int16)(SAP * 6400);
		if (passo_cht == 1)
			{
			CHT_tr[0] = CHT;
			CHT_tr[1] = 6399;
			}
		else if (passo_cht == 2)
			{
			CHT_ts[0] = CHT;
			CHT_ts[1] = 6399;
			}
		else if (passo_cht == 3)
			{
			CHT_tt[0] = CHT;
			CHT_tt[1] = 6399;
			}
		else if (passo_cht == 4)
			{
			CHT_cr[0] = CHT;
			CHT_cr[1] = 6399;
			}
		else if (passo_cht == 5)
			{
			CHT_cs[0] = CHT;
			CHT_cs[1] = 6399;
			}
		else if (passo_cht == 6)
			{
			CHT_ct[0] = CHT;
			CHT_ct[1] = 6399;
			}
		else
			{
			passo_cht = 1;
			}
		qcht = 0;
		passo_cht++;
		if (passo_cht > 6)
			{
			 passo_cht = 1;
			}
 	 	}
	else
		{		 	 	
		if (calcular_cht == 1)
			{
	 	 	calcula_qcht();
			}
 	 	}

	 	
}


void calcula_qcht(void)
{
	float aux_f1;
	if (passo_qcht == 0)
		{
 	 	BN1 = 0;
 	 	AN1 = 0;
		zx = tabela_z[qcht]; 						/* z = 2 * PI * y; */	
		passo_qcht++;
		}
	if (passo_qcht < (NRO_AMOSTRAS_CHT+1))
		{
		A1 = (float)(AMPLITUDE[passo_qcht] - AMPLITUDE[passo_qcht-1]);
		A1 = (float)(A1 / zx);	
		A2 = (float)(passo_qcht);
		A2 = (float)(A2 *  qcht);
		A2 = (float)(drad * A2);
		AN1 = (float)(AN1 - ((float)(A1 * sin (A2))));
		BN1 = (float)(BN1 + ((float)(A1 * cos (A2))));
		passo_qcht++;
		}
	else 
		{
		passo_qcht = 0;
		AN1 = (float)(2 * AN1);
		BN1 = (float)(2 * BN1);
		AN2 = (float)(AN1 * AN1);
		BN2 = (float)(BN1 * BN1);
		AP = (float)(sqrtx((float)(AN2 + BN2)));
		if (qcht == 1 )
			{
			AP1 = AP;
			}
		else
			{
			 SAN2 += AN2;
			 SBN2 += BN2;
			}
	    aux_f1 = (float)(AP / AP1);
	    CHT = (int16)(aux_f1 * 6400);
		if (qcht > (NRO_CHT+1))
			{
			qcht = 0;
			}
		if (passo_cht == 1)
			{
			CHT_tr[qcht] = CHT;
	 		}
		else if (passo_cht == 2)
			{
			CHT_ts[qcht] = CHT;
	 		}
		else if (passo_cht == 3)
			{
			CHT_tt[qcht] = CHT;
	 		}
		else if (passo_cht == 4)
			{
			CHT_cr[qcht] = CHT;
	 		}
		else if (passo_cht == 5)
			{
			CHT_cs[qcht] = CHT;
	 		}
		else if (passo_cht == 6)
			{
			CHT_ct[qcht] = CHT;
	 		}
		else
	 		{
		 	passo_cht = 1;
		 	}
		qcht++;
		}
}


void le_senoide_cht()
{
	char aux_b4;
	switch(passo_cht)
		{
/* FASE S */	
		case 1:
			{
			le_tensao_r();
			break;
			}
		
/* FASE S */	
		case 2:
			{
			le_tensao_s();
			break;
			}

/* FASE T */	
		case 3:
			{
			le_tensao_t();
			break;
        	}
		
/* harmonicos de corrente */
/* FASE R */	
		case 4:
			{
			le_corrente_r();
			break;
			}
/* FASE S */	
		case 5:
			{
			le_corrente_s();
    	 	break;
			}

/* FASE T */	
		case 6:
			{
			le_corrente_t();
    	 	break;
        	}

		default:
    		{
    		passo_cht = 1;
    		}
    	}

	for ( aux_b4= 0; aux_b4 < NRO_AMOSTRAS_CHT; aux_b4++)
		{
		if (passo_fase_cht == 0)
			{
			AMPLITUDE[aux_b4] = (float)(buf_tensao_r[aux_b4]);
			}
		else if (passo_fase_cht == 1)
			{
			AMPLITUDE[aux_b4] = (float)(buf_tensao_s[aux_b4]);
			}
		else if (passo_fase_cht == 2)
			{
			AMPLITUDE[aux_b4] = (float)(buf_tensao_t[aux_b4]);
			}
		else if (passo_fase_cht == 3)
			{
			AMPLITUDE[aux_b4] = (float)(buf_corrente_r[aux_b4]);
			}
		else if (passo_fase_cht == 4)
			{
			AMPLITUDE[aux_b4] = (float)(buf_corrente_s[aux_b4]);
			}
		else if (passo_fase_cht == 5)
			{
			AMPLITUDE[aux_b4] = (float)(buf_corrente_t[aux_b4]);
			}
#if (com_modbus == true)
			trata_modbus();
#endif

		}
		if (passo_fase_cht == 0)
			{
			AMPLITUDE[NRO_AMOSTRAS_CHT] = (float)(buf_tensao_r[0]);
			}
		else if (passo_fase_cht == 1)
			{
			AMPLITUDE[NRO_AMOSTRAS_CHT] = (float)(buf_tensao_s[0]);
			}
		else if (passo_fase_cht == 2)
			{
			AMPLITUDE[NRO_AMOSTRAS_CHT] = (float)(buf_tensao_t[0]);
			}
		else if (passo_fase_cht == 3)
			{
			AMPLITUDE[NRO_AMOSTRAS_CHT] = (float)(buf_corrente_r[0]);
			}
		else if (passo_fase_cht == 4)
			{
			AMPLITUDE[NRO_AMOSTRAS_CHT] = (float)(buf_corrente_s[0]);
			}
		else if (passo_fase_cht == 5)
			{
			AMPLITUDE[NRO_AMOSTRAS_CHT] = (float)(buf_corrente_t[0]);
			}

}


void le_tensao_r(void)
{   
	if (tensao_r < TENSAO_FALTA)
		{
		zera_senoide();
		}
	else
		{
		passo_fase_cht = 0;
		}
}
void le_tensao_s(void)
{
	if (tensao_s < TENSAO_FALTA)
		{
		zera_senoide();
		}
	else
		{
		passo_fase_cht = 1;
		}
		
}
void le_tensao_t(void)
{
	if (tensao_t < TENSAO_FALTA)
		{
		zera_senoide();
		}
	else
		{
		passo_fase_cht = 2;
		}
		
}

void le_corrente_r(void)
{
#if (tc_fixo == true)
	aux_w1 = 80;
#else
	if (valor_tc < 61)
		{
		aux_w1 = 8;
		}
	if (valor_tc < 201)
		{
		aux_w1 = 40;
		}
	else
		{
		aux_w1 = 80;
		}
#endif

	if (corrente_r < (aux_w1))
		{
		zera_senoide();
		}
	else
		{
		passo_fase_cht = 3;
		}
}

void le_corrente_s(void)
{
#if (tc_fixo == true)
	aux_w1 = 80;
#else
	if (valor_tc < 61)
		{
		aux_w1 = 8;
		}
	if (valor_tc < 201)
		{
		aux_w1 = 40;
		}
	else
		{
		aux_w1 = 80;
		}
#endif
	if (corrente_s < (aux_w1))
		{
		zera_senoide();
		}
	else
		{
		passo_fase_cht = 4;
		}
		
}

void le_corrente_t(void)
{

#if (tc_fixo == true)
	aux_w1 = 80;
#else
	if (valor_tc < 61)
		{
		aux_w1 = 8;
		}
	if (valor_tc < 201)
		{
		aux_w1 = 40;
		}
	else
		{
		aux_w1 = 80;
		}
#endif
	if (corrente_t < (aux_w1))
		{
		zera_senoide();
		}
	else
		{
		passo_fase_cht = 5;
		}
}

void zera_senoide(void)
{		
	char aux_b;
	for (aux_b = 0; aux_b < NRO_AMOSTRAS_CHT; aux_b++)
		{	
		if (passo_cht == 1)
			{
			buf_tensao_r[aux_b] = 0;
			}
		else if (passo_cht == 2)
			{
			buf_tensao_s[aux_b] = 0;
			}
		else if (passo_cht == 3)
			{
			buf_tensao_t[aux_b] = 0;
			}
		else if (passo_cht == 4)
			{
			buf_corrente_r[aux_b] = 0;
			}
		else if (passo_cht == 5)
			{
			buf_corrente_s[aux_b] = 0;
			}
		else if (passo_cht == 6)
			{
			buf_corrente_t[aux_b] = 0;
			}
#if (com_modbus == true)
			trata_modbus();
#endif
		}
}		



/*
void calcula_qcht_old(void)
{

	for (aux_b1 = 1; aux_b1 < (NRO_AMOSTRAS_CHT + 1) ; aux_b1++)
		{
		pulsa_wdt();
		aux_l1 = (int32)(AMPLITUDE[aux_b1] - AMPLITUDE[aux_b1-1]);
		A1 = (float)(aux_l1 / zx);				// A1 = (AMPLITUDE[aux_b1] - AMPLITUDE[aux_b1-1]) / z; 
		A2 = (float)(drad * aux_b1 *  qcht );
		AN1 = (float)(AN1 - A1 * sin (A2));
		BN1 = (float)(BN1 + A1 * cos (A2));
		}
		
	AN = (float)(2 * AN1);
	BN = (float)(2 * BN1);
	AN2 = (float)(AN * AN);
	BN2 = (float)(BN * BN);


	AP = (float)(sqrtx((float)(AN2 + BN2)));

	if (qcht == 1 )
		{
		AP1 = AP;
		}
	else
		{
		 SAN2 = (float)(SAN2 + AN2);
		 SBN2 = (float)(SBN2 + BN2);
		}
	switch(passo_cht)
		{
		case 1:
			{
			CHT_tr[qcht] = (int16)((AP * 6400) / AP1);
	 		break;
	 		}
		case 2:
			{
			CHT_ts[qcht] = (int16)((AP * 6400) / AP1);
	 		break;
	 		}
		case 3:
			{
			CHT_tt[qcht] = (int16)((AP * 6400) / AP1);
	 		break;
	 		}
		case 4:
			{
			CHT_cr[qcht] = (int16)((AP * 6400) / AP1);
	 		break;
	 		}
		case 5:
			{
			CHT_cs[qcht] = (int16)((AP * 6400) / AP1);
	 		break;
	 		}
		case 6:
			{
			CHT_ct[qcht] = (int16)((AP * 6400) / AP1);
	 		break;
	 		}
	 	default:
	 		{
		 	passo_cht = 1;
		 	}
		}

		
}
*/
