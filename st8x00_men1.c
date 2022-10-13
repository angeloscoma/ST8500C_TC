//***********************************************************************
// Empresa: Sultech Sistemas Eletrônicos								*
// Modulo: Menu Medidas Elétricas										*
// Função: Exibir as Grandezas Medidas									*
// Responsável: Edison Valério Nunes Junior								*
// Inicio: 30/08/2000													*
//***********************************************************************

void trata_menu1(void){
	if (qmenu != 1){		
		qmenu = 1;
		exibiu = 0;
		menu_aux = 1;
		time_out_menus = 60;
		salva_menus();
		calcula_mul_tc();
		reset_rolar();
		limpa_display();
		aux_menu1 = 0;
	}
	else if (tecla_up){
		aux_menu1 = 0;
		exibir_menu = 1;
		exibiu = 0;
		MENU_FIXO = 0;
	 	if (menu_aux > 1){
	 		menu_aux--;
			reset_rolar();
	 	}
	}
	else if (tecla_down){
		aux_menu1 = 0;
		exibir_menu = 1;
		exibiu = 0;
		MENU_FIXO = 0;
		 if (menu_aux < nro_menus1){
	 		menu_aux++;
			reset_rolar();
 		}
	}
	else if (tecla_enter){
	 	tecla_enter = 0;
		exibiu = 0;
		MENU_FIXO = 1;
		salva_menus();
		exibir_menu = 1;
		rolando = false;
		ja_rolou = true;
 		if (aux_menu1 == 0){
 			aux_menu1 = 1;
 		}
 		else{
 			aux_menu1 = 0;
 		}
	}		
	else if (tecla_reset){
		menu_aux = 0;
		reset_rolar();
		tecla_reset = 0;
		qmenu = 0;
		MENU_FIXO = 0;
		salva_menus();
		menu1 = 1;
		exibe_menu();
	}

re_exibe_medidas:
	if (exibir_menu == 1){
		exibir_menu = 0;
		piscar = ~piscar;
		modo_rep = 1;
		switch(menu_aux){
	 		case 0:
	 		case 1:{
 				exibe_tensao_fn();
				break;
			}
	 		case 2:{
	 			if (valor_tp != 1){
	 				exibe_tensao_alta();
					break;
				}
				else{
					exibiu = 0;
					if (tecla_up){
						menu_aux--;
					}
					if (tecla_down){
						menu_aux++;
					}
					break;
				}
			}
	 		case 3:{
				exibe_corrente();
				break;
			}
	 		case 4:{
				exibe_frequencia();
				break;
			}
	 	    case 5:{
	 			exibe_kw_kvar();
				break;
			}
			case 6:{
				exibe_fp_kva();
				break;
			}
	 		case 7:{
	 			exibe_pot_requerida_excedente();
				break;
			}
			case 8:{
				exibe_demanda_ativa();
				break;
			}
			case 9:{
				exibe_set_point_demanda();
				break;
			}
			case 10:{
				exibe_demanda_reativa();
				break;
			}
			case 11:{
				exibe_fator_carga_demanda();
				break;
			}
			case 12:{
				#if (com_rep == true)						
					exibe_status_rep();
					break;
				#endif
                    break;
			}
			case 13:{
				#if (com_rep == true)						
					exibe_status_rep_pul_ant();
					break;
				#endif
                    break;
			}
			case 14:{
				#if (com_rep == true)						
					exibe_status_rep_pot_ant();
					break;
				#endif
                    break;
			}
			case 15:{
				exibe_consumo();
				break;
			}
			case 16:{
				exibe_consumo_mes_ant();
				break;
			}
	 		default:{
				menu_aux = 1;
				goto re_exibe_medidas;
			}
		}
	}
	tecla_up = 0;
   	tecla_down = 0;
}

