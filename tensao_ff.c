/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: st_CALC                                                        *
; Funcao: MODULO ROTINAS DE CALCULOS   									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */


void calc_tensao_ff(void)
{
/* calcula tensao entre R e S */	
	#if (monofasico == false)
		if (tipo_ligacao == 0)
			{
			aux_l1 = 0;
			aux_l1 = tensao_r;
			aux_l1 += tensao_s;
			aux_l1 = aux_l1 >> 1;
			tensao_rs = (word)(aux_l1 * 1.7320508);
	
		/* calcula tensao entre T e S */	
			aux_l1 = 0;
			aux_l1 = tensao_s;
			aux_l1 += tensao_t;
			aux_l1 = aux_l1 >> 1;
			tensao_st = (word)(aux_l1 * 1.7320508);
		
		/* calcula tensao entre R e T */	
			aux_l1 = 0;
			aux_l1 = tensao_r;
			aux_l1 += tensao_t;
			aux_l1 = aux_l1 >> 1;
			tensao_rt = (word)(aux_l1 * 1.7320508);
			}
		else
			{
			
			// calcula tensao entre R e S 
			aux_w1 = (word)(tensao_r + (tensao_s >> 1));
			aux_l1 = tensao_s;
			aux_l1 = (int32)(aux_l1 * 887);
			aux_w2 = (word)(aux_l1 >> 10);
			aux_l1 = aux_w1;
			aux_l1 = aux_l1 * aux_l1;
			aux_l2 = aux_w2;
			aux_l2 = aux_l2 * aux_l2;
			aux_l1 = (sqrtx(aux_l1 + aux_l2));
			tensao_rs = (word)(aux_l1);
		
		// calcula tensao entre T e S 
			aux_w1 = (word)(tensao_s + (tensao_t >> 1));
			aux_l1 = tensao_t;
			aux_l1 = (int32)(aux_l1 * 887);
			aux_w2 = (word)(aux_l1 >> 10);
			aux_l1 = aux_w1;
			aux_l1 = aux_l1 * aux_l1;
			aux_l2 = aux_w2;
			aux_l2 = aux_l2 * aux_l2;
			aux_l1 = (sqrtx(aux_l1 + aux_l2));
			tensao_st = (word)(aux_l1);
		
		// calcula tensao entre R e T 
			aux_w1 = (word)(tensao_t + (tensao_r >> 1));
			aux_l1 = tensao_r;
			aux_l1 = (int32)(aux_l1 * 887);
			aux_w2 = (word)(aux_l1 >> 10);
			aux_l1 = aux_w1;
			aux_l1 = aux_l1 * aux_l1;
			aux_l2 = aux_w2;
			aux_l2 = aux_l2 * aux_l2;
			aux_l1 = (sqrtx(aux_l1 + aux_l2));
			tensao_rt = (word)(aux_l1);
			
			}
			
	#else
		aux_l1 = 0;
		aux_l1 = tensao_r;
		tensao_rs = (word)(aux_l1 * 1.7320508);
	#endif

}


