/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: st_CALC                                                        *
; Funcao: MODULO ROTINAS DE CALCULOS   									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */



void calc_fator_total(void)
{    
	#if (st8500c == false)
	/* calculo do fator de potencia total */
		#if (monofasico == true)
			fator_pot = fator_pot_r;
		#else
			sinal_r = 0;
			sinal_s = 0;
			sinal_t = 0;
			
			if ((fator_pot_r == 1024) && (fator_pot_s == 1024) && (fator_pot_t == 1024))
				{
				 fator_pot = 1024;
				 return;
				}
		
			soma_pot_apa = (int32)(pot_aparente_r +  pot_aparente_s + pot_aparente_t);
			soma_pot_ati = (int32)(pot_ativa_r +  pot_ativa_s + pot_ativa_t) * 1024;
			aux_l3 = soma_pot_ati / soma_pot_apa;
			fator_pot = (signed word)(aux_l3);
		
			if (fator_pot_r != 1024)
				{
				sinal_r = fator_pot_r;
				}
			if (fator_pot_s != 1024)
				{
				sinal_s = fator_pot_s;
				}
			if (fator_pot_t != 1024)
				{
				sinal_t = fator_pot_t;
				}
			sinal_r = sinal_r + sinal_s + sinal_t;
				
			if (sinal_r > 0)
				{
				sinal = 1;
				}
			else
				{
				sinal = (-1);
				}
			
			fator_pot = (signed word)(fator_pot * sinal);
		#endif	
	#else
		#if (com_tc == true)
	/* calculo do fator de potencia total */
			sinal_r = 0;
			sinal_s = 0;
			sinal_t = 0;
			
			if ((fator_pot_r == 1024) && (fator_pot_s == 1024) && (fator_pot_t == 1024))
				{
				 fator_pot = 1024;
				 return;
				}
		
			soma_pot_apa = (int32)(pot_aparente_r +  pot_aparente_s + pot_aparente_t);
			soma_pot_ati = (int32)(pot_ativa_r +  pot_ativa_s + pot_ativa_t) * 1024;
			aux_l3 = soma_pot_ati / soma_pot_apa;
			fator_pot = (signed word)(aux_l3);
		
			if (fator_pot_r != 1024)
				{
				sinal_r = fator_pot_r;
				}
			if (fator_pot_s != 1024)
				{
				sinal_s = fator_pot_s;
				}
			if (fator_pot_t != 1024)
				{
				sinal_t = fator_pot_t;
				}
			sinal_r = sinal_r + sinal_s + sinal_t;
				
			if (sinal_r > 0)
				{
				sinal = 1;
				}
			else
				{
				sinal = (-1);
				}
			
			fator_pot = (signed word)(fator_pot * sinal);
		#endif	
	#endif
}


