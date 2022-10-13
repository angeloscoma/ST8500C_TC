
/************************************************************************|
|* Empresa: Sultech Sistemas Eletrônicos								*|
|* Modulo: Menu de Configuração do REP									*|
|* Funcao: Módulo do ST-Prog											*|
|* Responsável: Edison Valério Nunes Junior								*|
|* Modificado: Edison Valério Nunes Junior								*|
|* Inicio: 13/02/2009													*|
|* Revisao: Edison Valério Nunes Junior									*|
*************************************************************************/
void salvar_programa_rep(void);
void exibe_programa_rep(void);
	
void trata_menu_rep(void){
	if (qmenu != 3){
		qmenu = 3;
		menu_aux = 1;
	}
	else if (tecla_enter == 1){
		tecla_enter = 0;
		exibiu = 0;
		if (programando == 1){
			salvar_programa_rep();
		}
		else{
			programando = 1;
		}
	}		
	else if (tecla_up == 1){
		exibiu = 0;
		tecla_up = 0;
		if (programando == 1){
			if (tempo_senha != 255){
				tempo_senha++;
			}
			switch(menu_aux){
				case 1:{
					if (intervalo < 900){
						intervalo++;
					}
					break;
				}
				case 2:{
					if (reposicao_de_demanda == 0){
						reposicao_de_demanda = 1;
					}
					else{
						reposicao_de_demanda = 0;
					}
					break;
				}
				case 3:{
					indicador_reativo = ~indicador_reativo;
					break;
				}
				case 4:{
					pulsos_cap_considerado = ~pulsos_cap_considerado;
					break;
				}
				case 5:{
					pulsos_ind_considerado = ~pulsos_ind_considerado;
					break;
				}
				case 6:{
					if (segmento_horo_sazonal < 8){
						segmento_horo_sazonal++;
					}
					break;
				}
				case 7:{
					if (tipo_de_tarifa < 3){
						tipo_de_tarifa++;
					}
					break;
				}
				case 8:{
					tarifar_reativos = ~tarifar_reativos;
					break;
				}
				case 9:{
					if (quantidade_kW < 9999){
						quantidade_kW++;
					}
					break;
				}
				case 10:{
					if (quantidade_kVAr < 9999){
						quantidade_kVAr++;
					}
					break;
				}
				case 11:{
					tipo_REP = ~tipo_REP;
					break;
				}
			}
		}
		else{
			if (menu_aux > 1){
				menu_aux--;
			}
		}
	}
	else if (tecla_down == 1){
		exibiu = 0;
		tecla_down = 0;
		if (programando == 1){
			if (tempo_senha != 255){
				tempo_senha++;
			}
			switch(menu_aux){
				case 1:{
					if (intervalo > 0){
						intervalo--;
					}
					break;
				}
				case 2:{
					if (reposicao_de_demanda == 0){
						reposicao_de_demanda = 1;
					}
					else{
						reposicao_de_demanda = 0;
					}
					break;
				}
				case 3:{
					indicador_reativo = ~indicador_reativo;
					break;
				}
				case 4:{
					pulsos_cap_considerado = ~pulsos_cap_considerado;
					break;
				}
				case 5:{
					pulsos_ind_considerado = ~pulsos_ind_considerado;
					break;
				}
				case 6:{
					if (segmento_horo_sazonal > 1){
						segmento_horo_sazonal--;
					}
					break;
				}
				case 7:{
					if (tipo_de_tarifa > 0){
						tipo_de_tarifa--;
					}
					break;
				}
				case 8:{
					tarifar_reativos = ~tarifar_reativos;
					break;
				}
				case 9:{
					if (quantidade_kW > 0){
						quantidade_kW--;
					}
					break;
				}
				case 10:{
					if (quantidade_kVAr > 0){
						quantidade_kVAr--;
					}
					break;
				}
				case 11:{
					tipo_REP = ~tipo_REP;
					break;
				}
			}
		}
		else{
			 if (menu_aux < 11){
				 menu_aux++;
			}
		}
	}
	else if (tecla_reset == 1){
		tecla_reset = 0;
		inicializa_programa();
		valida_programa();
		encerra_menus();
		return;
	}
	exibe_programa_rep();
}
	
void salvar_programa_rep(void){
	salva_programa();
	valida_programa();

	if (menu_aux < 2){
		menu_aux++;
	}
	exibiu = 0;
}

void exibe_programa_rep(void){
	if (programando == 1){
		exibir_menu = 1;
	}
	if (exibir_menu == 0){
		return;
	}
	switch(menu_aux){
		case 1:{
			if (exibiu == 0){
				if (programando == 0){
					mensagem(1, 14);
					mensagem(2, 15);
					mensagem(3, 16);
					mensagem(4, 17);
				}
				exibiu = 1;
			}
			displayp(29,intervalo,3,0,'P');
			if (programando == 0){
				displayp(47,reposicao_de_demanda,1,0,0);
				displayp(63,indicador_reativo,1,0,0);
			}
			break;
		}
		case 2:{
			if (exibiu == 0){
				if (programando == 0){
					mensagem(1, 14);
					mensagem(2, 15);
					mensagem(3, 16);
					mensagem(4, 17);
				}
				exibiu = 1;
			}
			displayp(47,reposicao_de_demanda,1,0,'P');
			if (programando == 0){
				displayp(29,intervalo,3,0,0);
				displayp(63,indicador_reativo,1,0,0);
			}
			break;
		}
		case 3:{
			if (exibiu == 0){
				if (programando == 0){
					mensagem(1, 14);
					mensagem(2, 15);
					mensagem(3, 16);
					mensagem(4, 17);
				}
				exibiu = 1;
			}
			displayp(63,indicador_reativo,1,0,'P');
			if (programando == 0){
				displayp(47,reposicao_de_demanda,1,0,0);
				displayp(29,intervalo,3,0,0);
			}
			break;
		}
		case 4:{
			if (exibiu == 0){
				if (programando == 0){
					mensagem(1, 14);
					mensagem(2, 16);
					mensagem(3, 17);
					mensagem(4, 18);
				}
				exibiu = 1;
			}
			displayp(63,pulsos_cap_considerado,1,0,'P');
			if (programando == 0){
				displayp(31,reposicao_de_demanda,1,0,0);
				displayp(47,indicador_reativo,1,0,0);
			}
			break;
		}
		case 5:{
			if (exibiu == 0){
				if (programando == 0){
					mensagem(1, 14);
					mensagem(2, 17);
					mensagem(3, 18);
					mensagem(4, 19);
				}
				exibiu = 1;
			}
			displayp(63,pulsos_ind_considerado,1,0,'P');
			if (programando == 0){
				displayp(47,pulsos_cap_considerado,1,0,0);
				displayp(31,indicador_reativo,1,0,0);
			}
			break;
		}
		case 6:{
			if (exibiu == 0){
				if (programando == 0){
					mensagem(1, 14);
					mensagem(2, 18);
					mensagem(3, 19);
					mensagem(4, 20);
				}
				exibiu = 1;
			}
			displayp(60,segmento_horo_sazonal,4,0,'P');
			if (programando == 0){
				displayp(47,pulsos_ind_considerado,1,0,0);
				displayp(31,pulsos_cap_considerado,1,0,0);
			}
			break;
		}
		case 7:{
			if (exibiu == 0){
				if (programando == 0){
					mensagem(1, 14);
					mensagem(2, 19);
					mensagem(3, 20);
					mensagem(4, 21);
				}
				exibiu = 1;
			}
			displayp(60,tipo_de_tarifa,4,0,'P');
			if (programando == 0){
				displayp(44,segmento_horo_sazonal,4,0,0);
				displayp(31,pulsos_ind_considerado,1,0,0);
			}
			break;
		}
		case 8:{
			if (exibiu == 0){
				if (programando == 0){
					mensagem(1, 14);
					mensagem(2, 20);
					mensagem(3, 21);
					mensagem(4, 22);
				}
				exibiu = 1;
			}
			displayp(61,tarifar_reativos,3,0,'P');
			if (programando == 0){
				displayp(44,tipo_de_tarifa,4,0,0);
				displayp(28,segmento_horo_sazonal,4,0,0);
			}
			break;
		}
		case 9:{
			if (exibiu == 0){
				if (programando == 0){
					mensagem(1, 14);
					mensagem(2, 21);
					mensagem(3, 22);
					mensagem(4, 23);
				}
				exibiu = 1;
			}
			displayp(59,pulso_ati,5,0,'P');
			if (programando == 0){
				displayp(47,tarifar_reativos,1,0,0);
				displayp(28,tipo_de_tarifa,4,0,0);
			}
			break;
		}
		case 10:{
			if (exibiu == 0){
				if (programando == 0){
					mensagem(1, 14);
					mensagem(2, 22);
					mensagem(3, 23);
					mensagem(4, 24);
				}
				exibiu = 1;
			}
			displayp(59,pulso_reat,5,0,'P');
			if (programando == 0){
				displayp(43,pulso_ati,5,0,0);
				displayp(31,tarifar_reativos,1,0,0);
			}
			break;
		}
		case 11:{
			if (exibiu == 0){
				if (programando == 0){
					mensagem(1, 14);
					mensagem(2, 23);
					mensagem(3, 24);
					mensagem(4, 25);
				}
				exibiu = 1;
			}
			displayp(61,tipo_REP,3,0,'P');
			if (programando == 0){
				displayp(43,pulso_reat,5,0,0);
				displayp(27,pulso_ati,5,0,0);
			}
			break;
		}
	}
	exibe_colchete();
	exibir_menu = 0;
}