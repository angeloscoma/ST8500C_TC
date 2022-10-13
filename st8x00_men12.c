/*************************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST8610_MEN12                                                   *
; Funcao: TRATAMENTO DO MENU DE STATUS									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado:  VAGNER SANTOS                                             *
; Inicio: 03/2005                                                        *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/

void trata_menu12(void)
{
	if (qmenu != 12)
		{
		qmenu = 12;
		em_status = true;
		exibiu = 0;
		time_out_menus = 60;
		rolando = false;
		tecla_up = 1;
		}
	if (tecla_enter == 1)
		{
	 	tecla_enter = 0;
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
		menu1 = 12;
		qmenu = 0;
		exibe_menu();
		}
}
