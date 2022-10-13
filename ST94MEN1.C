/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: st94men1.c                                                     *
; Funcao: Controle do Menu Medidas Elétricas							 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/

void trata_menu1(void);
void exibe_medidas(void);

void trata_menu1(void)
{
	if (M1_C1 == 0)
		{		
		M1_C1=1;
		aux_menu1 = 0;
		time_out_menus = 60;
		salva_menus();
		calcula_mul_tc();
		exibiu = 0;
		}
	if (tecla_up == 1)
		{
		exibir_menu = 1;
		MENU_FIXO = 0;
		exibiu = 0;
	 	if (menu_aux > 1)
	 		{
	 		menu_aux--;
		 	}
		 }
	else if (tecla_down == 1)
		{
		exibir_menu = 1;
		MENU_FIXO = 0;
		exibiu = 0;
		if (menu_aux < nro_menus1)
	 		{
	 		menu_aux++;
	 		}
		}
	else if (tecla_enter == 1)
		{
	 	tecla_enter = 0;
		MENU_FIXO = 1;
		salva_menus();
		exibir_menu = 1;
		exibiu = 0;
	 	if ((menu_aux < 8) && (menu_aux > 3))
	 		{
	 		if (aux_menu1 == 0)
	 			{
	 			aux_menu1 = 1;
	 			}
	 		else
	 			{
	 			aux_menu1 = 0;
	 			}
		 	}
	 	if ((menu_aux == 17) || (menu_aux == 18) || (menu_aux == 19))
	 		{
		 	#if (disp_7seg == true)
		 		if (aux_menu1 < 3)
		 			{
		 			aux_menu1++;
		 			}
		 		else
		 			{
		 			aux_menu1 = 0;
		 			}
		 	#else
		 		if (aux_menu1 == 0)
		 			{
		 			aux_menu1 = 1;
		 			}
		 		else
		 			{
		 			aux_menu1 = 0;
		 			}
		 	#endif
	 		}
		}		
	else if (tecla_reset == 1)
		{
		menu_aux = 0;
		tecla_reset=0;
		menu1 = 1;
		exibe_menu();
		M1_C1=0;
		MENU_FIXO = 0;
		salva_menus();
		return;
		}
	exibe_medidas();
    tecla_down = 0;
	tecla_up = 0;
	
}


void exibe_medidas(void)
{
re_exibe_medidas:
	if (exibir_menu == 1)
		{
		piscar = ~piscar;
		 switch(menu_aux)
	 		{
	 		case 0:
			 	{
				exibe_menu();
				break;
				}
	 		case 1:
	 			{
				if (tipo_ligacao == 0)		/* 0 estrela; 1 Delta  ; 2 Delta Aberto*/
					{
	 				exibe_tensao_fn();
					break;
					}
				else
					{
		 			exibe_tensao_ff();
					break;
					}
				break;
				}
	 		case 2:
	 			{
	 			if (valor_tp != 1)
	 				{
	 				exibe_tensao_alta();
					break;
					}
				else
					{
					if (tecla_up == 1)
						{
						menu_aux--;
						}
					if (tecla_down == 1)
						{
						menu_aux++;
						}
					break;
					}
				}
	 		case 3:
	 			{
				exibe_corrente(0);
				break;
				}
	 		case 4:
	 			{
		 		exibe_fator_potencia();
				break;
				}
	 		case 5:
	 			{
	 			exibe_pot_ativa(0);
				break;
				}
	 		case 6:
	 			{
	 			exibe_pot_aparente();
				break;
				}
	 		case 7:
	 			{
	 			exibe_pot_reativa();
				break;
				}
	 		case 8:
	 			{  
				#if (com_consumo == true)
	 				exibe_consumo_ati();
					break;
				#endif
				}
	 		case 9:
	 			{
				#if (com_consumo == true)
	 				exibe_consumo_reati();
					break;
				#endif
				}
	 		case 10:
	 			{
	 			exibe_dem_ativa();
				break;
				}
	 		case 11:
	 			{
	 			exibe_dem_reativa();
				break;
				}
	 		case 12:
	 			{
	 			exibe_dem_media_ativa();
				break;
				}
	 		case 13:
	 			{
	 			exibe_dem_maxima_ativa();
				break;
				}
	 		case 14:
	 			{
	 			exibe_dem_media_aparente();
				break;
				}
	 		case 15:
	 			{
	 			exibe_dem_maxima_aparente();
				break;
				}
	 		case 16:
	 			{
		 		exibe_frequencia();
				break;
				}
	 		case 17:
	 			{
	 			exibe_pot_requerida();
				break;
				}
			case 18:
				{
				exibe_pot_excedente();
				break;
				}
			#if (com_time_funciona == true)
				case 19:
					{
					exibe_time_funciona();
					break;
					}
			#endif
			#if com_maximos == true)
				case 20:
					{
					exibe_corrente(1);
					break;
					}
				case 21:
					{
		 			exibe_pot_ativa(1);
					break;
					}
			#endif
			#if (com_consumo_aparente == true)
				case 22:{
					exibe_consumo_aparente();
					break;
					}
			#endif
	 		default:
	 			{
				menu_aux = 1;
				goto re_exibe_medidas;
				}
			}
		}

	exibir_menu = 0;
}

