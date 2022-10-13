/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_MAIN                                                        *
; Funcao: MODULO GERENCIADOR DOS DADOS PARA A RESOLUÇÃO 505				 *
; 		Registrador Portátil de Grandezas Elétricas Trifásico            *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 01/08/2003                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/


void totaliza_tensao(void)
{
	if (segundo_old_505 == segundo)
		{
		return;
		}

	if (tipo_ligacao == 0)
		{
		aux_w1 = tensao_r;
		aux_w2 = tensao_s;
		aux_w3 = tensao_t;
		}
	else
		{
		aux_w1 = tensao_rs;
		aux_w2 = tensao_st;
		aux_w3 = tensao_rt;
		}

	if (aux_w1 > TENSAO_FALTA)
		{
		soma_media_tensao_r += aux_w1;
		conta_media_tensao_r++;
		}

	if (aux_w2 > TENSAO_FALTA)
		{
		soma_media_tensao_s += aux_w2;
		conta_media_tensao_s++;
		}

	if (aux_w3 > TENSAO_FALTA)
		{
		soma_media_tensao_t += aux_w3;
		conta_media_tensao_t++;
		}

	segundo_old_505 = segundo;

}





void inic_tensoes_505(void)
{

	soma_media_tensao_r = 0;
	conta_media_tensao_r = 0;
	soma_media_tensao_s = 0;
	conta_media_tensao_s = 0;
	soma_media_tensao_t = 0;
	conta_media_tensao_t = 0;

	tensao_media_r = 0;
	tensao_media_s = 0;
	tensao_media_t = 0;

}


/* Fim st_505 */
