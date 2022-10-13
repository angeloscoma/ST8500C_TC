/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_MAIN                                                        *
; Funcao: MODULO PRINCIPAL DE CONTROLE									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */

  
//char aux_tab;


void trata_menu4(void)
{
	if (qmenu != 2)
		{
		qmenu = 2;
		menu_aux = 1;
		}
	else if (tecla_enter==1)
		{
	 	tecla_enter=0;
		exibiu = 0;
		if (programando == 1)
			{
			goto salvar_programa;
			}
		else
			{
			goto trata_menu4_enter;
			}
		}		
	else if (tecla_up==1)
		{
		exibiu = 0;
		tecla_up=0;
		 if (programando == 1)
		 	{
			if (tempo_senha != 255)
				{
				tempo_senha++;
				}
			goto trata_menu4_up;
		 	}
		 else
		 	{
			 if (menu_aux > 1)
			 	{
				 menu_aux--;
				}
			}
		}
	else if (tecla_down==1)
		{
		exibiu = 0;
		 tecla_down=0;
		 if (programando == 1)
		 	{
			if (tempo_senha != 255)
				{
				tempo_senha++;
				}
			goto trata_menu4_down;
		 	}
		 else
		 	{
			 if (menu_aux < 2)
			 	{
				 menu_aux++;
				}
			}
		}
	else if (tecla_reset==1)
		{
		inicializa_programa();
		valida_programa();
		encerra_menus();
		return;
		}
	goto exibe_programa;


salvar_programa:
	salva_programa();
	
	valida_programa();

	if (menu_aux < 2)
		{
		menu_aux++;
		}
	exibiu = 0;
	
						
exibe_programa: 

	if (programando == 1)
		{
		exibir_menu = 1;
		}
	if (exibir_menu == 0)
		{
		return;
		}
	if (exibiu == 0)
		{
		if (programando == 0)
			{
			mensagem(1, 4);	
			mensagem(2, 12);	
			mensagem(3, 13);	
			mensagem(4, 0);
			}
			exibiu = 1;
		}
	switch(menu_aux)
		{
		case 1:
			{
			displayp(27,baud_rate,5,0,'P');
			if (programando == 0)
				{
				displayp(45,endereco,3,0,0);
				}
			break;
			}
		case 2:
			{
			displayp(45,endereco,3,0,'P');
			if (programando == 0)
				{
				displayp(27,baud_rate,5,0,0);
				}
			break;
			}
		}
	exibe_colchete();
		
	exibir_menu = 0;
	return;


trata_menu4_enter:
	programando = 1;
	goto exibe_programa;	


trata_menu4_down:;
 	switch(menu_aux)
 		{
	 	case 1:
	 		{
			if (aux_tab > 0)
				{
				aux_tab--;
				}	
			baud_rate= tabela_baud[aux_tab];
			break;
			}
		case 2:
			{
			if (endereco > 1)
				{
				endereco--;
				}
			break;	
			}
		}
	goto exibe_programa;

trata_menu4_up:
	switch(menu_aux)
		{
		case 1:
			{
			if (aux_tab < (NRO_POSI_BAUD - 1))
				{
				aux_tab++;
				}	
			baud_rate = tabela_baud[aux_tab];
			break;
			}
		case 2:
			{
			if (endereco < 247)
				{
				endereco++;
				}
			break;	
			}
		}
goto exibe_programa;
}

