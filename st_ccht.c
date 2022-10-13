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

char que_ad;


#define drad ((2 * PI) / NRO_AMOSTRAS_CHT)

void le_seno(char);


void cht_online (void);
void le_senoide_cht(void);
void calcula_qcht(void);
void le_tensao_r(void);
void le_tensao_s(void);
void le_tensao_t(void);

void le_corrente_r(void);
void le_corrente_s(void);
void le_corrente_t(void);
void zera_buffer_cht(void);



void le_senoide_cht_timer(void)
{				
#if (ade7754 == true)
	char aux_b;
#endif
#if (chip_cs5460a == true)
	ler_cs5460 = 0;
#endif


#if (ade7754 == false)
	#if (monofasico == true)
		if (passo_fase_cht == 0)
			{
			que_ad = 0;
			}
		else if (passo_fase_cht == 3)
			{
			que_ad = 1;
			}
		else
			{
			passo_fase_cht = 0;
			lendo_cht = false;
			return;
			}
	#else
		if (passo_fase_cht == 0)
			{
			que_ad = 4;
			}
		else if (passo_fase_cht == 1)
			{
			que_ad = 5;
			}
		else if (passo_fase_cht == 2)
			{
			que_ad = 6;
			}
		else if (passo_fase_cht == 3)
			{
			que_ad = 0;
			}
		else if (passo_fase_cht == 4)
			{
			que_ad = 1;
			}
		else if (passo_fase_cht == 5)
			{
			que_ad = 2;
			}
		else
			{
			passo_fase_cht = 0;
			lendo_cht = false;
			return;
			}
	#endif
	time_out_int0 = 3;
	ler_senoide = 0;
	passo_rd_cht = 0;
	lendo_cht = true;
	#if (st94 == true) || (st92 == true)
		#if (rev_pci_st94 >= 11)
			ext_int_edge(0,H_TO_L);
			enable_interrupts(INT_EXT);
		#else
			ext_int_edge(2,H_TO_L);
			enable_interrupts(INT_EXT2);
		#endif
	#else
		ext_int_edge(0,H_TO_L);
		enable_interrupts(INT_EXT);
	#endif
	while (ler_senoide == 0)
		{
		if (time_out_int0 == 0)
			{
			break;
			}
		}
	ler_ad = 0;
	while (lendo_cht == true)
		{
		#if (chip_cs5460a == true)
			if (ler_senoide == 1)
				{
				lendo_cht = false;
				passo_rd_cht = 0;
				ler_senoide = 0;
				}
		#else
			if (ler_ad == 1)
				{
				ler_ad = 0;
				#if ((st5x == true) || (st9600r == true)) || (sames_9904 == true))
					#if (st5000c_rev12 == true)
					#else
						#if (st9600r == true)
							#if (versao_pci_st96 < 4)
								set_adc_channel(que_ad);
								delay_us(30);
								buffer_cht[passo_rd_cht] = (read_adc() << 2);
							#else
								continue;
							#endif
						#else
							set_adc_channel(que_ad);
							delay_us(30);
							buffer_cht[passo_rd_cht] = (read_adc() << 2);
						#endif
					#endif
				#endif
				passo_rd_cht++;
				if (passo_rd_cht == NRO_AMOSTRAS_CHT)
					{
					lendo_cht = false;
					break;
					}
				}
		#endif
		}

#else
	if (lendo_cht == false)
		{
		abre_leitura_cht = 1;
		lendo_cht = true;
	//	lendo_cht = false;
		passo_rd_cht = 0;
		time_out_int0 = 10;
		while (lendo_cht == true)
			{
			if (time_out_int0 == 0)
				{
	//			lendo_cht = false;
				break;
				}
			}
		for (aux_b = 0; aux_b < NRO_AMOSTRAS_CHT; aux_b++)
			{	
			if (passo_fase_cht == 0)
				{
				buf_tensao_r[aux_b] = buffer_cht[aux_b];
				}
			else if (passo_fase_cht == 1)
				{
				buf_tensao_s[aux_b] = buffer_cht[aux_b];
				}
			else if (passo_fase_cht == 2)
				{
				buf_tensao_t[aux_b] = buffer_cht[aux_b];
				}
			else if (passo_fase_cht == 3)
				{
				buf_corrente_r[aux_b] = buffer_cht[aux_b];
				}
			else if (passo_fase_cht == 4)
				{
				buf_corrente_s[aux_b] = buffer_cht[aux_b];
				}
			else if (passo_fase_cht == 5)
				{
				buf_corrente_t[aux_b] = buffer_cht[aux_b];
				}
			}
		}
#endif

}
             

void cht_online (void)
{
	short calcular_cht;

	#if (com_menu == true)
		if (teclando != 0)
			{
			return;
			}
	#endif
	#if (feira == true)
		CHT_tr[0] = 12 * 64;
		CHT_cr[0] = 19 * 64;
		#if (monofasico == false)
			CHT_ts[0] = 13 * 64;
			CHT_tt[0] = 11 * 64;
			CHT_cs[0] = 22 * 64;
			CHT_ct[0] = 17 * 64;
		#endif
		for (aux_b1 = 1; aux_b1 < NRO_CHT; aux_b1++)
			{
			pulsa_wdt();
			CHT_tr[aux_b1] = CHT_tr[aux_b1-1]/2;
			CHT_cr[aux_b1] = CHT_cr[aux_b1-1]/2;
			#if (monofasico == false)
				CHT_ts[aux_b1] = CHT_ts[aux_b1-1]/2;
				CHT_tt[aux_b1] = CHT_tt[aux_b1-1]/2;
				CHT_cs[aux_b1] = CHT_cs[aux_b1-1]/2;
				CHT_ct[aux_b1] = CHT_ct[aux_b1-1]/2;
			#endif
			}
		CHT_tr[1] = 6400;
		CHT_cr[1] = 6400;
		#if (monofasico == false)
			CHT_ts[1] = 6400;
			CHT_tt[1] = 6400;
			CHT_cs[1] = 6400;
			CHT_ct[1] = 6400;
		#endif
			
		return;
	#endif
	
	if (qcht > (NRO_CHT+1))
		{
		qcht = 0;
		}

	calcular_cht = 1;
	if (qcht == 0)
 	 	{
		#if (monofasico == true)
			if (passo_cht == 1)
				{
				if (tensao_r < (20 * 64))
					{
					calcular_cht = 0;
					passo_cht++;
		 	 		}
	 	 		}
			else if (passo_cht == 2)
				{
		 	 	#if (com_rep == 1)
			 	 	if (modo_rep == 1)
			 	 		{
						calcular_cht = 0;
						passo_cht++;
				 	 	}
				 	else
				 		{
						if (corrente_r < 8)
							{
							calcular_cht = 0;
							passo_cht++;
			  				}
			  			}
			  	#else
					if (corrente_r < 8)
						{
						calcular_cht = 0;
						passo_cht++;
		  				}
			  	#endif
		 	 	}
			else
				{
				calcular_cht = 0;
				qcht = 0;
				passo_cht = 1;
				}
		#else
			if (passo_cht == 1)
				{
				if (tensao_r < (20 * 64))
					{
					calcular_cht = 0;
					passo_cht++;
		 	 		}
	 	 		}
			else if (passo_cht == 2)
				{
				if (tensao_s < (20 * 64))
					{
					calcular_cht = 0;
					passo_cht++;
		 	 		}
	 	 		}
			else if (passo_cht == 3)
				{
				if (tensao_t < (20 * 64))
					{
					calcular_cht = 0;
					passo_cht++;
		 	 		}
	 	 		}
			else if (passo_cht == 4)
				{
		 	 	#if (com_rep == 1)
			 	 	if (modo_rep == 1)
			 	 		{
						calcular_cht = 0;
						passo_cht++;
				 	 	}
				 	else
				 		{
						if (corrente_r < 8)
							{
							calcular_cht = 0;
							passo_cht++;
		 		 			}
		 		 		}
		 		#else
					if (corrente_r < 8)
						{
						calcular_cht = 0;
						passo_cht++;
	 		 			}
		 		#endif 
	 	 		}
			else if (passo_cht == 5)
				{
		 	 	#if (com_rep == 1)
			 	 	if (modo_rep == 1)
			 	 		{
						calcular_cht = 0;
						passo_cht++;
				 	 	}
				 	else
				 		{
						if (corrente_s < 8)
							{
							calcular_cht = 0;
							passo_cht++;
		 		 			}
		 		 		}
		 		#else
					if (corrente_s < 8)
						{
						calcular_cht = 0;
						passo_cht++;
	 		 			}
		 		#endif 
	 	 		}
			else if (passo_cht == 6)
				{
		 	 	#if (com_rep == 1)
			 	 	if (modo_rep == 1)
			 	 		{
						calcular_cht = 0;
						passo_cht++;
				 	 	}
				 	else
				 		{
						if (corrente_t < 8)
							{
							calcular_cht = 0;
							passo_cht++;
		 		 			}
		 		 		}
		 		#else
					if (corrente_t < 8)
						{
						calcular_cht = 0;
						passo_cht++;
	 		 			}
		 		#endif 
	 	 		}
			else
				{
				calcular_cht = 0;
				qcht = 0;
				passo_cht = 1;
				}
		#endif
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
		#if (monofasico == true)
			if (passo_cht == 1)
				{
				CHT_tr[0] = CHT;
				CHT_tr[1] = 6399;
				}
			else if (passo_cht == 2)
				{
				CHT_cr[0] = CHT;
				CHT_cr[1] = 6399;
				}
			else
				{
				passo_cht = 1;
				}
		#else
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
		#endif
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


void calcula_qcht(void){
	#if (novo_cht == true)
		word k;
	#endif
	#if (debug_cht == true)
		word k;
//		float AN11;		// float
//		float BN11;		// float
		float l_sin;
		float l_cos;
		float c_sin;
		float c_cos;
	#endif
	
	float aux_f1;
	if (passo_qcht == 0){
 	 	BN1 = 0;
 	 	AN1 = 0;
		#if (debug_cht == true)
			AN11 = 0;		// float
			BN11 = 0;		// float
		#endif
		zx = tabela_z[qcht]; 						/* z = 2 * PI * y; */	
		passo_qcht++;
	}
	if (passo_qcht < (NRO_AMOSTRAS_CHT+1)){
		output_high(PIN_G1);
		A1 = (float)(AMPLITUDE[passo_qcht] - AMPLITUDE[passo_qcht-1]);
		A1 = (float)(A1 / zx);	
		#if (novo_cht == true)
			k = (word)(qcht) * (word)(passo_qcht);
			if (k >= NRO_AMOSTRAS_CHT){
				k = (k % NRO_AMOSTRAS_CHT);
			}
			AN1 = (float)(AN1 - ((float)(A1 * TAB_SIN[k])));
			BN1 = (float)(BN1 + ((float)(A1 * TAB_COS[k]))); 
		#else
			A2 = (float)(passo_qcht);
			A2 = (float)(A2 *  qcht);
			A2 = (float)(drad * A2);
			AN1 = (float)(AN1 - ((float)(A1 * sin (A2))));
			BN1 = (float)(BN1 + ((float)(A1 * cos (A2))));
		#endif
		
		#if (debug_cht == true)
			k = (word)(qcht) * (word)(passo_qcht);
			if (k >= NRO_AMOSTRAS_CHT){
				k = (k % NRO_AMOSTRAS_CHT);
			}
			AN11 = (float)(AN11 - ((float)(A1 * TAB_SIN[k])));
			BN11 = (float)(BN11 + ((float)(A1 * TAB_COS[k]))); 
			l_sin = TAB_SIN[k];
			l_cos = TAB_COS[k];
			delay_us(10);
			aux_f1 = BN11;
			if (qcht == 3){
				if (passo_qcht == 85){
					delay_us(10);
					aux_f1 = BN11;
				}
			}
		#endif
		passo_qcht++;
		output_low(PIN_G1);
	}
	else {
		passo_qcht = 0;
		AN1 = (float)(2 * AN1);
		BN1 = (float)(2 * BN1);
		AN2 = (float)(AN1 * AN1);
		BN2 = (float)(BN1 * BN1);
		AP = (float)(sqrtx((float)(AN2 + BN2)));

		#if (debug_cht == true)
			AN11 = (float)(2 * AN11);
			BN11 = (float)(2 * BN11);
			AN22 = (float)(AN11 * AN11);
			BN22 = (float)(BN11 * BN11);
			APP = (float)(sqrtx((float)(AN22 + BN22)));
		#endif

		if (qcht == 1 ){
			AP1 = AP;
		}
		else{
			SAN2 += AN2;
			SBN2 += BN2;
		}
	    aux_f1 = (float)(AP / AP1);
	    CHT = (int16)(aux_f1 * 6400);
		#if (monofasico == true)
			if (qcht > (NRO_CHT+1)){
				qcht = 0;
				}
			if (passo_cht == 1)
				{
				CHT_tr[qcht] = CHT;
		 		}
			else if (passo_cht == 2)
				{
				CHT_cr[qcht] = CHT;
		 		}
			else
		 		{
			 	passo_cht = 1;
			 	}
		#else
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
		#endif
		qcht++;
		}

}


#if (chip_cs5460a == true)
	void le_senoide_cht()
	{
	
		switch(passo_cht)
			{
			#if (monofasico == true
		/* FASE R */	
				case 1:
					{
					le_tensao_r();
					goto le_buf_tensao;
					}
				
		/* FASE S */	
				case 2:
					{
					le_corrente_r();
					goto le_buf_corrente;
					}
			#else
		/* FASE R */	
				case 1:
					{
					le_tensao_r();
					goto le_buf_tensao;
					}
				
		/* FASE S */	
				case 2:
					{
					le_tensao_s();
					goto le_buf_tensao;
					}
		
		/* FASE T */	
				case 3:
					{
					le_tensao_t();
					goto le_buf_tensao;
		        	}
				
		/* harmonicos de corrente */
		/* FASE R */	
				case 4:
					{
					le_corrente_r();
					goto le_buf_corrente;
					}
		/* FASE S */	
				case 5:
					{
					le_corrente_s();
					goto le_buf_corrente;
					}
		
		/* FASE T */	
				case 6:
					{
					le_corrente_t();
					goto le_buf_corrente;
		        	}
			#endif
	
			default:
	    		{
	    		passo_cht = 1;
	    		}
	    	}
	
	le_buf_tensao:
		for ( aux_b4= 0; aux_b4 < NRO_AMOSTRAS_CHT; aux_b4++)
			{
	 		aux_sw1 = (signed word)(buffer_cht_t[aux_b4]);
	 		aux_sw1 = (signed word)(aux_sw1 / 16);
			AMPLITUDE[aux_b4] = (float)(2048 + aux_sw1);

//			AMPLITUDE[aux_b4] = (float)(buffer_cht_t[aux_b4]);
			}
 		aux_sw1 = (signed word)(buffer_cht_t[0]);
 		aux_sw1 = (signed word)(aux_sw1 / 16);
		AMPLITUDE[aux_b4] = (float)(2048 + aux_sw1);

//		AMPLITUDE[NRO_AMOSTRAS_CHT] = (float)(buffer_cht_t[0]);
		return;
	
	le_buf_corrente:
		for ( aux_b4= 0; aux_b4 < NRO_AMOSTRAS_CHT; aux_b4++)
			{
	 		aux_sw1 = (signed word)(buffer_cht_c[aux_b4]);
	 		aux_sw1 = (signed word)(aux_sw1 / 16);
			AMPLITUDE[aux_b4] = (float)(2048 + aux_sw1);
			}
		aux_sw1 = (signed word)(buffer_cht_c[0]);
 		aux_sw1 = (signed word)(aux_sw1 / 16);
		AMPLITUDE[aux_b4] = (float)(2048 + aux_sw1);
		return;
	
	}
#else
	void le_senoide_cht()
	{

		switch(passo_cht)
			{
			#if (monofasico == true)
		/* FASE R */	
				case 1:
					{
					le_tensao_r();
					break;
					}
		/* harmonicos de corrente */
				case 2:
					{
		/* FASE R */	
					le_corrente_r();
					break;
					}
			#else
		/* FASE R */	
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
			#endif
	
			default:
	    		{
	    		passo_cht = 1;
	    		}
	    	}
	
		for ( aux_b4= 0; aux_b4 < NRO_AMOSTRAS_CHT; aux_b4++)
			{
	 		AMPLITUDE[aux_b4] = (float)(buffer_cht[aux_b4]);
			}
		AMPLITUDE[NRO_AMOSTRAS_CHT] = (float)(buffer_cht[0]);


	}
#endif



void le_tensao_r(void)
{   
	if (tensao_r < (20 * 64))
		{
		zera_buffer_cht();
		}
	else
		{
		passo_fase_cht = 0;
		#if (chip_cs5460a == true)
			lendo_cht_cs5460 = 1;
			le_seno('R');
			return;
		#else
			le_senoide_cht_timer();
		#endif
		}
}

#if (monofasico == false)
	void le_tensao_s(void)
	{
		if (tensao_s < (20 * 64))
			{
			zera_buffer_cht();
			}
		else
			{
			passo_fase_cht = 1;
			#if (chip_cs5460a == true)
				lendo_cht_cs5460 = 1;
				le_seno('S');
				return;
			#else
				le_senoide_cht_timer();
			#endif
			}
			
	}

	void le_tensao_t(void)
	{
		if (tensao_t < (20 * 64))
			{
			zera_buffer_cht();
			}
		else
			{
			passo_fase_cht = 2;
			#if (chip_cs5460a == true)
				lendo_cht_cs5460 = 1;
				le_seno('T');
				return;
			#else
				le_senoide_cht_timer();
			#endif
			}
	}

#endif

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
		zera_buffer_cht();
		}
	else
		{
		passo_fase_cht = 3;
		#if (chip_cs5460a == true)
			lendo_cht_cs5460 = 1;
			le_seno('R');
			return;
		#else
			le_senoide_cht_timer();
		#endif
		}
}

#if (monofasico == false)
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
			zera_buffer_cht();
			}
		else
			{
			passo_fase_cht = 4;
			#if (chip_cs5460a == true)
				lendo_cht_cs5460 = 1;
				le_seno('S');
				return;
			#else
				le_senoide_cht_timer();
			#endif
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
			zera_buffer_cht();
			}
		else
			{
			passo_fase_cht = 5;
			#if (chip_cs5460a == true)
				lendo_cht_cs5460 = 1;
				le_seno('T');
				return;
			#else
				le_senoide_cht_timer();
			#endif
			}
	}
#endif
void zera_buffer_cht(void)
{		
return;
#if (teste_cht == false)
	for (aux_b4 = 0; aux_b4 < NRO_AMOSTRAS_CHT; aux_b4++)
		{ 
		#if (chip_cs5460a == true)
			switch(passo_cht)
				{
				case 1:
				case 2:
				case 3:
					{
					buffer_cht_t[aux_b4]= 2048;
					break;
					}
				case 4:
				case 5:
				case 6:
					{
					buffer_cht_c[aux_b4]= 2048;
					break;
					}
				}
		#else
				buffer_cht[aux_b4]= 2048;
		#endif
		}
#endif
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
