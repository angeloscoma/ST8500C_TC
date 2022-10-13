/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST8610_MEN4                                                    *
; Funcao: TRATAMENTO DO MENU DE PROGRAMAÇAO GERAL						 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */

void le_programa_st8500c(void){
	char x;
	tabela_programa[1] = dem_cont_ponta[mes - 1];
	tabela_programa[2] = dem_cont_fora_ponta[mes - 1];
	tabela_programa[3] = carga_programada;
	tabela_programa[4] = dia_inicio_pc;
	tabela_programa[5] = mes_inicio_pc;
	tabela_programa[6] = dia_final_pc;
	tabela_programa[7] = mes_final_pc;
	tabela_programa[8] = hora_ponta;
	tabela_programa[9] = minuto_ponta;
	tabela_programa[10] = hora_final_ponta;
	tabela_programa[11] = minuto_final_ponta;
	#if (com_rep == true)
		tabela_programa[12] = fat_conv_ativa;
		tabela_programa[13] = fat_conv_reativa;
	#endif
	#if (com_tc == true)
		tabela_programa[12] = valor_tc;
		tabela_programa[13] = valor_tp;
	#endif
	tabela_programa[14] = endereco;
	tabela_programa[15] = 0;
	for (x = 0; x < (NRO_POSI_BAUD); x++){
		if (baud_rate == tabela_baud[x]){
			tabela_programa[15] = x;
		}
	}
	aux_tab = mes - 1;
	tabela_programa[16] = modo_saidas;
	#if(com_rep)
		tabela_programa[17] = protocolo_REP;
	#endif
}
	
void trata_up4_st8500c(void){
	switch(menu_aux){
		case 1:										//demanda contratada ponta
		case 2:										//demanda contratada fora ponta
		case 3:{									// carga instalada
			if (tabela_programa[menu_aux] < CARGA_INSTALADA_MAX){
				tabela_programa[menu_aux]++;
			}
			break;
		}
		case 4:{									//dia inico periodo seco
			if (tabela_programa[4] < 31){
				tabela_programa[4]++;
			}
			break;
		}
		case 5:{									// mes inicio periodo seco
			if (tabela_programa[5] < 11){			// faz teste no mes final, que não pode ficar menor ou igual 
				tabela_programa[5]++;				// que o mes inicial, então só pode ir até mes 11.
				if (tabela_programa[5] < 11){
					tabela_programa[7] = tabela_programa[5] + 1;
				}
			}
			if (tabela_programa[5] >= tabela_programa[7]){
				tabela_programa[7] = tabela_programa[5] + 1;
			}
			break;
		}
		case 6:{									//dia fim periodo seco
			if (tabela_programa[6] < 31){
				tabela_programa[6]++;
			}
			break;
		}
		case 7:{									// mes fim periodo seco
			if (tabela_programa[7] < 12){
				tabela_programa[7]++;
			}
			break;
		}
		case 8:{
			if (tabela_programa[8] < 22){			// horariode inico ponta
				tabela_programa[8]++;
				if (tabela_programa[8] < 22){
					tabela_programa[10] = tabela_programa[8] + 1;
				}
			}
			if (tabela_programa[8] >= tabela_programa[10]){
				tabela_programa[10] = tabela_programa[8] + 1;
			}
			break;
		}
		case 9:{									// minuto inicio
			if (tabela_programa[9] < 59){
				tabela_programa[9]++;
			}
			break;
		}				
		case 10:{									// hora final
			if (tabela_programa[10] < 23){
				tabela_programa[10]++;
			}
			break;
		}				
		case 11:{									// minimo final
			if (tabela_programa[11] < 59){
				tabela_programa[11]++;
			}
			break;
		}				
		#if (com_tc == true)
		 	case 12:{								// incrementa valor tc
				if (aux_tab < (NRO_POSI_TC-1)){
					aux_tab++;
				}
				if (aux_tab > (NRO_POSI_TC-1)){
		 			aux_tab = 0;
		 		}
				tabela_programa[12] = tabela_tc[aux_tab];
				break;
		 	}
			case 13:{								// incrementa valor valor_tp
				if (tabela_programa[13] < 500){
					tabela_programa[13]++;
				}
				break;
			}
		#elif (com_rep == true)
		 	case 12:								// incrementa fat_conv_ativa e fat_conv_reativa
		 	case 13:{                   
			 	if (tabela_programa[menu_aux] < 9999){
					tabela_programa[menu_aux]++;
				}
				break;
 			}
 		#endif
	 	case 14:{									// incrementa valor endereco do modbus
	 		if (tabela_programa[14] < 247){
				tabela_programa[14]++;
			}
			break;
 		}
	 	case 15:{									// incrementa valor de baudrate
	 		if (tabela_programa[15] < (NRO_POSI_BAUD - 1)){
				tabela_programa[15]++;
			}
			if (tabela_programa[15] > (NRO_POSI_BAUD - 1)){
				tabela_programa[15] = 0;
			}
			break;
 		}
 		case 16:{
	 		if (tabela_programa[16] == MODO_INVERTIDO){
 				tabela_programa[16] = MODO_NORMAL;
		 	}
		 	else{
				tabela_programa[16] = MODO_INVERTIDO;
			}
	 		break;
	 	}
 		case 17:{
	 		#if(com_rep)
		 		if(tabela_programa[17] < (NRO_PROTO_REP - 1)){
			 		tabela_programa[17]++;
		 		}
		 		else{
			 		tabela_programa[17] = 0;
		 		}
		 		break;
		 	#endif
 		}
 	}
}

void trata_down4_st8500c(void){							//decrementa parâmetros no teclado
	switch(menu_aux){
		case 1:											// demanda contratada ponta
		case 2:{										// demandas contratadas fora da ponta 
			if (tabela_programa[menu_aux] > 0){
				tabela_programa[menu_aux]--;
			}
			break;
		}
		case 3:{										// carga instalada
			aux_w1 = 0;
			if (aux_w1 < tabela_programa[1]){
				aux_w1 = tabela_programa[1];
			}
			if (aux_w1 < tabela_programa[2]){
				aux_w1 = tabela_programa[2];
			}
			if (tabela_programa[3] > aux_w1){
				tabela_programa[3]--;					//
			}
			else{
				tabela_programa[3] = aux_w1;
			}
			break;
		}
		case 4:{										//dia inico periodo seco
			if (tabela_programa[4] > 1){
				tabela_programa[4]--;
			}
			break;
		}
		case 5:{										// mes inicio periodo seco
			if (tabela_programa[5] > 1){				// faz teste no mes final, que não pode ficar menor ou igual 
				tabela_programa[5]--;					// que o mes inicial, então só pode ir até mes 11.
			}
			if (tabela_programa[5] >= tabela_programa[7]){
				tabela_programa[7] = tabela_programa[5] + 1;
			}
			break;
		}
		case 6:{										//dia fim periodo seco
			if (tabela_programa[6] > 1){
				tabela_programa[6]--;
			}
			break;
		}
		case 7:{										// mes fim periodo seco
			if (tabela_programa[7] > 1){
				tabela_programa[7]--;
			}
			break;
		}
		case 8:											// horario de inicio ponta
		case 9:											// minuto inicio
		case 10:										// hora final
		case 11:{										// minuto final
			if (tabela_programa[menu_aux] > 0){
				tabela_programa[menu_aux]--;
			}
			break;
		}				
		#if (com_tc == true)
	 		case 12:{									// decrementa valor tc
				if (aux_tab > 0){
					aux_tab --;
				}
				tabela_programa[12] = tabela_tc[aux_tab];
				break;
		 	}
	 		case 13:{									// decrementa valor tp
		 		if (tabela_programa[13] > 1){
					tabela_programa[13]--;
				}
				break;
		 	}
		#elif (com_rep == true)
		 	case 12:									// incrementa fat_conv_ativa e fat_conv_reativa
		 	case 13:{
			 	if (tabela_programa[menu_aux] > 1){
					tabela_programa[menu_aux]--;
				}
				break;
 			}
 		#endif
	 	case 14:{										// incrementa valor endereco do modbus
	 		if (tabela_programa[14] > 2){
				tabela_programa[14]--;
			}
			else{
				tabela_programa[14] = 1;
			}
			break;
 		}
	 	case 15:{										// incrementa valor de baudrate
	 		if (tabela_programa[15] > 0){
				tabela_programa[15]--;
			}
			if (tabela_programa[15] > (NRO_POSI_BAUD - 1)){
				tabela_programa[15] = 0;
			}
			break;
 		}
 		case 16:{
	 		if (tabela_programa[16] == MODO_INVERTIDO){
 				tabela_programa[16] = MODO_NORMAL;
		 	}
		 	else{
				tabela_programa[16] = MODO_INVERTIDO;
			}
	 		break;
	 	}
 		case 17:{
	 		if(tabela_programa[17] > 0){
		 		tabela_programa[17]--;
	 		}
	 		else{
		 		tabela_programa[17] = 0;
	 		}
	 		break;
 		}
	}
}


void exibe_programa(void){
	if (menu_aux == 0){
		menu_aux = 1;
	}

	if (exibir_menu == 0){
		return;
	}
	exibir_menu = 0;
	switch (menu_aux){
		case 1:
		case 2:
		case 3:{
			if (exibiu == 0){
				desativa_cursor();
				if (menu_aux == 3){
					mensagem (1, 12);
					mensagem (2, 13);
				}
				else{
					if(aux_tab<12){
						mensagem (1, 34);						// Demanda Contratado			
						displayp(14,(aux_tab+1),2,0,0);
						mensagem (2, 35 + (menu_aux -1));		// msg qdemanda
					}
					else{
						aux_tab=11;
					}
				}
				exibiu = 1;
			}
			displayp(26,tabela_programa[menu_aux],5,0,'P');
			break;
		}
		
		case 4:
		case 5:
		case 6:
		case 7:{
			if (exibiu == 0){
				desativa_cursor();
				mensagem (1, 45);			//  PROGRAMAÿÇÿÃO DO PERIODO SECO
				mensagem (2, 46);	
				exibiu = 1;
				tabela_pisca[0] = 0;
				tabela_pisca[1] = 0;
				tabela_pisca[2] = 0;
				tabela_pisca[3] = 0;
				if (menu_aux == 6){
					tabela_pisca[0] = 'P';
				}
				else if (menu_aux == 7){
					tabela_pisca[1] = 'P';
				}
				else if (menu_aux == 8){
					tabela_pisca[2] = 'P';
				}
				else{
					tabela_pisca[3] = 'P';
				}
			}
			displayp(19,tabela_programa[4],2,0,tabela_pisca[0]);
			displayp(22,tabela_programa[5],2,0,tabela_pisca[1]);
			displayp(27,tabela_programa[6],2,0,tabela_pisca[2]);
			displayp(30,tabela_programa[7],2,0,tabela_pisca[3]);
			if (menu_aux == 4){
				lcd_gotoxy(4,2);
			}
			else if (menu_aux == 5){
				lcd_gotoxy(7,2);
			}
			else if (menu_aux == 6){
				lcd_gotoxy(12,2);
			}
			else{
				lcd_gotoxy(15,2);
			}
			ativa_cursor();
			break;
		}
		case 8:
		case 9:
		case 10:
		case 11:{
			if (exibiu == 0){
				desativa_cursor();
				mensagem (1, 57);				// PROGRAMAÇAO DO PERIODO DE PONTA
				mensagem (2, 59);		
				exibiu = 1;
				tabela_pisca[0] = 0;
				tabela_pisca[1] = 0;
				tabela_pisca[2] = 0;
				tabela_pisca[3] = 0;
				if (menu_aux == 8){
					tabela_pisca[0] = 'P';
				}
				else if (menu_aux == 9){
					tabela_pisca[1] = 'P';
				}
				else if (menu_aux == 10){
					tabela_pisca[2] = 'P';
				}
				else{
					tabela_pisca[3] = 'P';
				}
			}
			displayp(19,tabela_programa[8],2,0,tabela_pisca[0]);
			displayp(22,tabela_programa[9],2,0,tabela_pisca[1]);
			displayp(27,tabela_programa[10],2,0,tabela_pisca[2]);
			displayp(30,tabela_programa[11],2,0,tabela_pisca[3]);
			if (menu_aux == 8){
				lcd_gotoxy(4,2);
			}
			else if (menu_aux == 9){
				lcd_gotoxy(7,2);
			}
			else if (menu_aux == 10){
				lcd_gotoxy(12,2);
			}
			else{
				lcd_gotoxy(15,2);
			}
			ativa_cursor();
			break;
		}
		case 12:
		case 13:{
			if (exibiu == 0){
				desativa_cursor();
				#if (com_tc == true)
					mensagem (1,170);
					mensagem (2,171);
				#endif
				#if (com_rep == true)
					mensagem (1,142);
					mensagem (2,143);
				#endif
				exibiu = 1;
				tabela_pisca[0] = 0;
				tabela_pisca[1] = 0;
				if (menu_aux == 12){
					tabela_pisca[0] = 'P';
				}
				else{
					tabela_pisca[1] = 'P';
				}
			}
			#if (com_tc == true)
				displayp (11, tabela_programa[12],4,0,tabela_pisca[0]);
				displayp (29, tabela_programa[13],3,0,tabela_pisca[1]);
			#endif
			#if (com_rep == true)
				displayp (12, tabela_programa[12],4,0,tabela_pisca[0]);
				displayp (28, tabela_programa[13],4,0,tabela_pisca[1]);
			#endif
			if (menu_aux == 12){
				lcd_gotoxy(14,1);
			}
			else{
				lcd_gotoxy(15,2);
			}
			ativa_cursor();
			break;
		}
		case 14:
		case 15:{
			if (exibiu == 0){
				desativa_cursor();
				mensagem (1,39);
				mensagem (2,40);
				exibiu = 1;
				tabela_pisca[0] = 0;
				tabela_pisca[1] = 0;
				if (menu_aux == 14){
					tabela_pisca[0] = 'P';
				}
				else{
					tabela_pisca[1] = 'P';
				}
			}
			displayp (14,tabela_programa[14],3,0,tabela_pisca[0]);
			displayp (28,tabela_baud[tabela_programa[15]],5,0,tabela_pisca[1]);
			if (menu_aux == 14){
				lcd_gotoxy(16,1);
			}
			else{
				lcd_gotoxy(16,2);
			}
			ativa_cursor();
			break;
		}
 		case 16:{
			mensagem (1,172);
	 		if (tabela_programa[16] == MODO_INVERTIDO){
		 		if (programando == 1){
			 		if (piscar == true){
						lcd_gotoxy(13,2);
						wr_lcd(1, ' ');
						wr_lcd(1, ' ');
						wr_lcd(1, ' ');
						wr_lcd(1, ' ');
				 	}
				 	else{
						mensagem (2,173);
					}
			 	}
			 	else{
					mensagem (2,173);
				}
		 	}
		 	else{
		 		if (programando == 1){
			 		if (piscar == true){
						lcd_gotoxy(13,2);
						wr_lcd(1, ' ');
						wr_lcd(1, ' ');
						wr_lcd(1, ' ');
						wr_lcd(1, ' ');
				 	}
				 	else{
						mensagem (2,174);
					}
			 	}
			 	else{
					mensagem (2,174);
				}
			}
	 		break;
	 	}
		case 17:{						// Tipo de Protocolo do REP
			if (exibiu == 0){
				mensagem (1,156);
				mensagem (2,0);
				mensagem (2,157);
				exibiu = 1;
			}
			lcd_gotoxy(10,2);
			if (programando == 1){
				if (piscar){
					display(' ');
					display(' ');
					display(' ');
				}
				else{
					switch(tabela_programa[17]){
						case 0:{
							display('N');
							display('O');
							display('R');
							break;
						}
						case 1:{
							display('E');
							display('S');
							display('T');
							break;
						}
						case 2:{
							display('G');
							display('R');
							display('A');
							break;
						}
						case 3:{
							display('M');
							display('I');
							display('S');
							break;
						}
					}
				}
			}
			else{
				switch(tabela_programa[17]){
					case 0:{
						display('N');
						display('O');
						display('R');
						break;
					}
					case 1:{
						display('E');
						display('S');
						display('T');
						break;
					}
					case 2:{
						display('G');
						display('R');
						display('A');
						break;
					}
					case 3:{
						display('M');
						display('I');
						display('S');
						break;
					}
				}
			}
			break;
		}
		default:{
			menu_aux = 1;
		}
	}
}

void salvar_programa(void){
	dem_cont_ponta[aux_tab] = tabela_programa[1];
	dem_cont_fora_ponta[aux_tab] = tabela_programa[2];
	carga_programada = tabela_programa[3];
	dia_inicio_pc = tabela_programa[4];
	mes_inicio_pc = tabela_programa[5];
	dia_final_pc = tabela_programa[6];
	mes_final_pc = tabela_programa[7];
	hora_ponta = tabela_programa[8];
	minuto_ponta = tabela_programa[9];
	hora_final_ponta = tabela_programa[10];
	minuto_final_ponta = tabela_programa[11];
	#if (com_rep == true)
		fat_conv_ativa = tabela_programa[12];
		fat_conv_reativa = tabela_programa[13];
	#endif
	#if (com_tc == true)
		valor_tc = tabela_programa[12];
		valor_tp = tabela_programa[13];
	#endif
	endereco = tabela_programa[14];
	baud_rate = tabela_baud[tabela_programa[15]];
	modo_saidas = tabela_programa[16];
	#if(com_rep)
		protocolo_REP = tabela_programa[17];
	#endif

	busca_demanda_contratada();

	salva_programa();
	valida_programa();
 	exibe_programa();
	calcula_mul_tc();
}

void trata_menu4(void){
	char x;

	if (qmenu != 4){
		qmenu = 4;
	 	exibiu = 0;
		menu_aux = 1;
		time_out_menus = 60;
		exibir_menu = 1;
		le_programa_st8500c();
		reset_rolar();
	}
		
	
	if (tecla_up == 1){
		exibir_menu = 1;
		tecla_up=0;
	 	exibiu = 0;
		if (programando == 1){
			tempo_senha = 255;
	 		trata_up4_st8500c();
			if (tempo_senha != 255){
				tempo_senha++;
			}
		}
		else{
			if (menu_aux > 0){
				if (menu_aux < 3){
					if (menu_aux == 1){
						if (aux_tab > 0){
							aux_tab--;
							menu_aux = 2;
							tabela_programa[1] = dem_cont_ponta[aux_tab];
							tabela_programa[2] = dem_cont_fora_ponta[aux_tab];
						}
					}
					else{
						menu_aux--;
					}
				}
				else{
					if (menu_aux == 3){
						aux_tab = 11;
						tabela_programa[1] = dem_cont_ponta[aux_tab];
						tabela_programa[2] = dem_cont_fora_ponta[aux_tab];
					}
					#if (com_tc == true)
						else if (menu_aux == 13){
							aux_tab = 18;
							for (x = 0; x < (NRO_POSI_TC) ;x++){
								if (tabela_programa[12] == tabela_tc[x]){
									aux_tab = x;
									break;
								}
							}
						}
					#endif
					menu_aux--;
				}
			}
			else{
			 	if (menu_aux > 1){
 					menu_aux--;
 				}
 			}
			reset_rolar();
		}
	}
	else if (tecla_down){
		exibir_menu = 1;
		tecla_down = 0;
		exibiu = 0;
		if (programando == 1){
			tempo_senha = 255;
	 		trata_down4_st8500c();
			if (tempo_senha != 255){
				tempo_senha++;
			}
		}
		else{
			if (menu_aux < nro_menus4){
				if (menu_aux < 3){
					if (menu_aux == 2){
						aux_tab++;
						menu_aux = 1;
						if (aux_tab<12){
							tabela_programa[1] = dem_cont_ponta[aux_tab];
							tabela_programa[2] = dem_cont_fora_ponta[aux_tab];
						}
						if (aux_tab > 11){
							menu_aux = 3;
							aux_tab=11;
						}
					}
					else{
						menu_aux++;
					}
				}
				else{
					#if (com_tc == true)
						if (menu_aux == 11){
							aux_tab = 18;
							for (x = 0; x < (NRO_POSI_TC) ;x++){
								if (tabela_programa[12] == tabela_tc[x]){
									aux_tab = x;
									break;
								}
							}
						}
					#endif
	 				menu_aux++;
	 			}
				reset_rolar();
	 		}
 		}
	}
	else if (tecla_enter){
	 	tecla_enter = 0;
		exibir_menu = 1;
	 	exibiu = 0;
		desativa_cursor();
		if (programando == 1){
			programando = 0;
			salvar_programa();
		 	exibiu = 0;
			exibir_menu = 1;
			if (menu_aux < 3){
				if (aux_tab <= 11){
					if (menu_aux == 2){
						aux_tab++;
						menu_aux = 1;
						if (aux_tab<12) {
							tabela_programa[1] = dem_cont_ponta[aux_tab];
							tabela_programa[2] = dem_cont_fora_ponta[aux_tab];
						}
						if (aux_tab>11){
							menu_aux=3;
							aux_tab=11;
						}
					}
					else{
						menu_aux++;
					}
				}
				else {
					menu_aux = 3;
				}
			}
			else{
				if (menu_aux < nro_menus4){
					#if (com_tc == true)
						if (menu_aux == 11){
							aux_tab = 18;
							for (x = 0; x < (NRO_POSI_TC) ;x++){
								if (tabela_programa[12] == tabela_tc[x]){
									aux_tab = x;
									break;
								}
							}
						}
					#endif
		 			menu_aux++;
	 			}
			}
		}
		else{
			if (tempo_senha == 0){
				trata_senha();
				return;
			}
			else{
				programando = 1;
			}
		}
	}		
	else if (tecla_reset){
		exibir_menu = 1;
		tecla_reset=0;
		reset_rolar();
		desativa_cursor();
		if (programando == 1){
			programando = 0;
			le_programa_st8500c();
		}
		else{
			menu_aux = 0;
			menu1 = 4;
			qmenu = 0;
			exibe_menu();
			return;
		}
	}
	exibe_programa();
}


