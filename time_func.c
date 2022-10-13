/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_MAIN                                                        *
; Funcao: MODULO PRINCIPAL DE CONTROLE									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */


void trata_time_funcionamento(void)
{
	#if (monofasico == true)
		if (tensao_r > TENSAO_FALTA)
			{
	#else
		if ((tensao_r > TENSAO_FALTA) ||(tensao_s > TENSAO_FALTA) ||(tensao_t > TENSAO_FALTA))
			{
	#endif
			#if (com_relogio == true)
				min_funciona = read_byte_nvr(ds_min_funciona);
			#endif
			min_funciona++;
			if (min_funciona >= 60)
				{
				min_funciona = 0;
				aux_l1 = read_long(ee_horas_funcionamento);
				aux_l1++;
				write_long(ee_horas_funcionamento, aux_l1);
				}
			#if (com_relogio == true)
				write_byte_nvr(ds_min_funciona, min_funciona);
			#else
				if ((minuto == 0) || (minuto == 15) || (minuto == 30) || (minuto == 45))
					{
					write_byte(ee_min_funciona, min_funciona);
					}
			#endif
			}
	
}
