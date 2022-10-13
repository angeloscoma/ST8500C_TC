/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_MAIN                                                        *
; Funcao: MODULO PRINCIPAL DE CONTROLE									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/
  
void exibe_medidas(void);


void trata_menu1(void)
{
/* MENU DE MEDIDAS ELÉTRICAS */
	if (qmenu != 1)
		{		
		qmenu = 1;
		}
	if (tecla_up==1)
		{
		exibir_menu = 1;
		exibiu = 0;
	 	if (menu_aux > 0)
	 		{
	 		menu_aux--;
		 	}
		 }
	else if (tecla_down==1)
		{
		exibir_menu = 1;
		exibiu = 0;
		 if (menu_aux < nro_menus1)
	 		{
	 		menu_aux++;
	 		}
		}
	else if (tecla_enter==1)
		{
	 	tecla_enter = 0;
		teclou_enter = ~teclou_enter;
		exibir_menu = 1;
		exibiu = 0;
		MENU_FIXO = 1;
		salva_menus();
		}		
	else if (tecla_reset==1)
		{
		if (MENU_FIXO == 1)
			{
			MENU_FIXO = 0;
			}
		else
			{
			encerra_menus();
			return;
			}
		}
	exibe_medidas();
    tecla_down=0;
	tecla_up=0;
	
}


void exibe_medidas(void)
{
/*
	if (modofunca == 2)
		{
		if (exibir_menu == 1)
		{
		 switch(menu_aux)
	 		{
	 		case 1:
	 			{
				if (tipo_ligacao == 0)
					{
		 			exibe_tensao_fn_cor();
					break;
					}
				}
	
		}
*/	
	if (exibir_menu == 1)
		{
		 switch(menu_aux)
	 		{
//	 		case 0:
//			 	{
//				exibe_menu();
//				break;
//				}
	 		case 1:
	 			{
				if (tipo_ligacao == 0)
					{
		 			exibe_tensao_fn_cor();
					break;
					}
				}
	 		case 2:
	 			{
	 			exibe_tensao_ff_cor();
				break;
				}
	 		case 3:
	 			{
	 			if (valor_tp != 1)
	 				{
	 				exibe_tensao_alta_cor();
					break;
					}
				else
					{
					if (tecla_up == 1)
						{
						menu_aux--;
			 			exibe_tensao_ff_cor();
						}
					if (tecla_down == 1)
						{
						menu_aux++;
			 			exibe_pot_kw_kva();
						}
					break;
					}
				}
	 		case 4:
	 			{
	 			exibe_pot_kw_kva();
				break;
				}
	 		case 5:
	 			{
		 		exibe_kvar_fp();
				break;
				}
	 		case 6:
	 			{  
				#if (com_consumo == true)
	 				exibe_consumos_fora_ponta();
					break;
				#else
					menu_aux++;
				#endif
				}
	 		case 7:
	 			{  
				#if (com_consumo == true)
	 				exibe_consumos_ponta();
				#else
					menu_aux++;
				#endif
				break;
				}
	 		case 8:
	 			{
	 			exibe_demanda_ativa();
				break;
				}
	 		case 9:
	 			{
	 			exibe_demanda_kva_kvar();
				break;
				}
	 		case 10:
	 			{
	 			exibe_pot_requerida();
				break;
				}
	 		case 11:
	 			{
	 			exibe_pot_excedente();
				break;
				}
	 		case 12:
	 			{
				mensagem(1,75);
				displayp(9,frequencia,2,1,2);
				mensagem(2,0);
/*				#if (versao_pci_st96 > 3)
					mensagem(3,8);
					#if (tc_fixo == true)
						print_display(43, corrente_n, 4, 1,3, 'C' , 255);	
					#else
						displayp(43,corrente_n,4,1,3);
					#endif
				#else
					mensagem(3,0);
				#endif*/
				mensagem(3,0);
				mensagem(4,0);
				break;
				}
	 		case 13:
	 			{
				exibe_status();
				break;
				}
	 		default:
	 			{
				menu_aux = 1;
				}
			}
		}

	exibir_menu = 0;
		
}

