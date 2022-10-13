/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: st_CALC                                                        *
; Funcao: MODULO ROTINAS DE CALCULOS   									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */


void calc_tensao_alta(void)
{	
	if (valor_tp == 1)
		{
		tensao_rs_na_alta = tensao_r;
		#if (monofasico == false)
			tensao_st_na_alta = tensao_s;
			tensao_rt_na_alta = tensao_t;
		#endif
		}
	else
		{
		aux_l1 = (int32)(tensao_r);
		aux_l1 = (int32)(aux_l1 * valor_tp );
		tensao_rs_na_alta = (word)(aux_l1 / 1000);
	
		#if (monofasico == false)
			aux_l1 = (int32)(tensao_s);
			aux_l1 = (int32)(aux_l1 * valor_tp);
			tensao_st_na_alta = (word)(aux_l1 / 1000);
			
			aux_l1 = (int32)(tensao_r);
			aux_l1 = (int32)(aux_l1 * valor_tp);
			tensao_rt_na_alta = (word)(aux_l1 / 1000);
		#endif
		}
}	


