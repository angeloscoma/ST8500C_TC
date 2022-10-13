/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_MAIN                                                        *
; Funcao: MODULO PRINCIPAL DE CONTROLE									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */

  

void trata_menu_coma(void)
{
/* TRATA PROGRAMACAO DE REGISTROS */
	
	if (qmenu != 6)
		{
		qmenu = 6;
		menu_aux = 1;
		limpa_display();
		}
	else if (tecla_enter==1)
		{
	 	tecla_enter=0;
		exibiu = 0;
		if (programando == 0)
			{
			programando = 1;
			mensagem(4,65);
			return;
			}
		else
			{
			goto menu_coma_enter;
			}
		}		
	else if (tecla_up==1)
		{
		exibiu = 0;
		tecla_up=0;
	 	if (menu_aux > 1)
		 	{
			 menu_aux--;
			}
		goto exibe_menu_coma;
		}
	else if (tecla_down==1)
		{
		exibiu = 0;
		tecla_down=0;
		if (menu_aux < nro_menus6)
			{
			 menu_aux++;
			}
		goto exibe_menu_coma;
		}
	else if (tecla_reset==1)
		{
		if (programando == 1)
			{
			programando = 0;
			goto exibe_menu_coma;
			}
		else
			{
			encerra_menus();
			return;
			}
		}
	else
		{
		return;
		}

exibe_menu_coma:
	mensagem(4,0);
    mensagem(1,62);			//" Apaga Consumos ",	//62
    mensagem(2,63);			//" Apaga Registro "		//64
//    mensagem(3,11);
	exibe_colchete();
	exibir_menu = 0;
	return;
	
menu_coma_enter:
	mensagem(4,66);
	delay_ms(500);
	switch(menu_aux)
		{
		case 1:
			{
#if com_consumo
			zera_consumo();
#endif			
			mensagem(4,64);			//	 " Comando OK !!! "		//64
			break;
			}
		case 2:
			{
#if com_regs	true
			apaga_memoria();
#endif			
			mensagem(4,64);			//	 " Comando OK !!! "		//64
			break;
			}
		case 3:						// comando para auste do relogio, abre a menu 6					
			{
			break;
			}				
		default:
			{
			menu_aux = nro_menus6;
	
			}

		}
	programando = 0;
	return;

	
	
}
