/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: st_CALC                                                        *
; Funcao: MODULO ROTINAS DE CALCULOS   									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */

void calc_tensao_corrente_tri(void)
{	
// calculos de tensao e corrente trifásica	

	soma_reg();

	#if (monofasico == true)
		if (tipo_ligacao == 0)
			{
			tensao_tri = tensao_r;
			}
		else
			{
			tensao_tri = tensao_rs;
			}
	 	corrente_tri = corrente_r  * 3;
	#else
		if (tipo_ligacao == 0)		// estrela = 0, em delta = 1
			{
		 	aux_l3 = (int32)(tensao_r + tensao_s + tensao_t) / 3;
	 		aux_l3 = (int32)(aux_l3 * 1.7320508);
			}
		else
			{
		 	aux_l3 = (int32)(tensao_rs + tensao_st + tensao_rt) / 3;
	 		}
		tensao_tri = (word)(aux_l3);
		if (modo_funca == 1)
			{
			soma_pot_ati = (int32)(pot_ativa_r +  pot_ativa_s + pot_ativa_t);
			soma_pot_reat = (int32)(pot_reativa_r + pot_reativa_s + pot_reativa_t);
			soma_pot_ati = (int32)(soma_pot_ati * soma_pot_ati);
			soma_pot_reat = (int32)(soma_pot_reat * soma_pot_reat);
			pot_apa_tri = (int32)(sqrtx((float)(soma_pot_ati + soma_pot_reat))); 	 
			pot_apa_tri = (int32)((pot_apa_tri * 1000) << 4); 	 
		
		 	aux_l3 = (int32)(aux_l3 * 1.7320508);		/* aux_l3 já tem tensao_tri */
		 	aux_l3 = (int32)(aux_l3 * valor_tp);		/* aux_l3 já tem tensao_tri */
		 	aux_l3 = (int32)(pot_apa_tri / aux_l3);
		 	
		 	corrente_tri = (word)(aux_l3);
			}
		else
			{
		 	corrente_tri = 0;
			}
	#endif

}


void calculo_trifasico(void)
{
	#if (st8500c  == true)
		#if (com_tc == true)
			float aux_f1;
		#endif
	#endif
	
// calculo do fator de potencia total 
	#if (st8500c == false)
		calc_fator_total();
	#else
		#if (com_tc == true)
		
			calc_fator_total();
		
			aux_l1 = pot_ativa_r;
			aux_l1 += pot_ativa_s;
			aux_l1 += pot_ativa_t;
			pot_ativa_tot = aux_l1;

			aux_l1 = pot_reativa_r;
			aux_l1 += pot_reativa_s;
			aux_l1 += pot_reativa_t;
			pot_reativa_tot = aux_l1;

			aux_l1 = pot_aparente_r;
			aux_l1 += pot_aparente_s;
			aux_l1 += pot_aparente_t;
			pot_aparente_tot = aux_l1;
			
		#endif		
	#endif

	calc_tensao_ff();

	calc_tensao_alta();

	calc_tensao_corrente_tri();
	
	
}


