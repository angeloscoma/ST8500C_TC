/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: st94men7.c                                                     *
; Funcao: Controle do Menu de Status									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */

void trata_menu7(void)
{
	em_status = true;
    if (M1_C7 == 0)
    	{
		M1_C7 = 1;
		time_out_menus = 60;
		passo_exibe_erro = 0;
		tecla_up = 1;
		}
	if (tecla_enter == 1)
		{
		tecla_enter = 0;
		exibe_erro();
		}
	else if (tecla_up == 1)
		{
		tecla_up = 0;
		exibe_erro();
		}
	else if (tecla_down == 1)
		{
		tecla_down = 0;
		exibe_erro();
		}
	else if (tecla_reset == 1)
		{
		tecla_reset = 0;
		em_status = false;
		M1_C7 = 0;
		exibe_menu();
		return;
		}
}
