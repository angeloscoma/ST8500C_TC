/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: st94men5.c                                                     *
; Funcao: Controle do Menu de Programação de Alarmes					 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */
  
void trata_menu5(void);
void exibe_alarmes(void);
void salva_alarmes(void);
//void valida_programa(void);

#if (st92 == false)
void exibe_off(void)
{
	buf_display[8] = tabela_caracteres[MESPACO];
	buf_display[9] = tabela_caracteres[MO];
	buf_display[10] = tabela_caracteres[MF];
	buf_display[11] = tabela_caracteres[MF];
}
#endif

void trata_menu5(void)
{
	if (M1_C5 == 0)
		{
		M1_C5 = 1;
		exibiu = 0;
		tabela_alarmes[1] = ala_fp_ind;
		tabela_alarmes[2] = ala_fp_cap;
		tabela_alarmes[3] = ala_ten_a;
		tabela_alarmes[4] = ala_ten_b;
		tabela_alarmes[5] = ala_sc;
		tabela_alarmes[6] = ala_subc;
		tabela_alarmes[7] = ala_chtt;
		tabela_alarmes[8] = ala_chtc;
		ala_demanda_ativa_aux = ala_demanda_ativa;
		time_out_menus = 60;
		menu_aux = 1;
		}

	if (tecla_enter == 1)
		{
	 	tecla_enter = 0;
		exibiu = 0;
		if (programando == 1)
			{
			programando = 0;
			salva_alarmes();
			}
		else
			{
			if (tempo_senha != 0)
				{
				programando = 1;
				}
			else
				{
				trata_senha();
				return;
				}
			}
		}

	if (tecla_up == 1)
		{
		tecla_up = 0;
		exibiu = 0;
		 if (programando == 1)
		 	{
	 		if ((menu_aux == 1) || ( menu_aux == 2))	//FP Indutivo ou Capacitivo de 0.80 até 1.00
	 			{
			 	if (tabela_alarmes[menu_aux] < 100)
			 		{
					tabela_alarmes[menu_aux]++;
					}
				}
			else if (menu_aux == 3)						//Tensão Alta de 1% a 20% da tensão nominal
				{
			 	if (tabela_alarmes[3] < 20)
			 		{
					tabela_alarmes[3]++;
					}
				}
			else if (menu_aux == 4)						//Tensão Baixa de 1% a 30% da tensão nominal
				{
			 	if (tabela_alarmes[4] < 30)
			 		{
					tabela_alarmes[4]++;
					}
				}
	 		else if (menu_aux == 5)						//Sobre-Corrente vai 1% a 150% do valor do TC
		 		{
			 	if (tabela_alarmes[5] < 150)
			 		{
					tabela_alarmes[5]++;
					}
		 		}
			else if (menu_aux == 6)						//Sub-Corrente de 1% a 20% do valor do TC
				{
//			 	if (tabela_alarmes[6] < 20)
			 	if (tabela_alarmes[6] < 100)			//Implementado em 29/09/09 por solicitação de cliente.
			 		{
					tabela_alarmes[6]++;
					}
				}
			#if (com_alarme_demanda == true)
				else if (menu_aux == 9)						//Demanda Ativa: De 0 a 9999
					{
					if (ala_demanda_ativa_aux < 9999)
						{
						ala_demanda_ativa_aux++;
						}
					}
			#endif
		 	else										//Harmônicos de Tensão e Corrente: de 1% a 50%
		 		{
			 	if (tabela_alarmes[menu_aux] < 50)
			 		{
					tabela_alarmes[menu_aux]++;
					}
				}
		 	}
		 else
		 	{
		 	if (menu_aux > 1)
		 		{
 				menu_aux--;
		 		}
		 	}
		 }
	if (tecla_down == 1)
		{
		tecla_down = 0;
		exibiu = 0;
		if (programando == 1)
			{
			if ((menu_aux == 1) || (menu_aux == 2))
				{
			 	if (tabela_alarmes[menu_aux] > 80)
			 		{
					tabela_alarmes[menu_aux]--;
					}
				}
			else if (menu_aux == 9)
				{
				if (ala_demanda_ativa_aux > 0)
					{
					ala_demanda_ativa_aux--;
					}
				}
			else
				{
				if (tabela_alarmes[menu_aux] > 0)
					{
					tabela_alarmes[menu_aux]--;
					}
				}
			}
		else
			{
			if (menu_aux < nro_menus5)
				{
	 			menu_aux++;
	 			}
	 		}
		}

	if (tecla_reset == 1)
		{
		tecla_reset = 0;
		if (programando == 1)
			{
			programando = 0;
			tabela_alarmes[1] = ala_fp_ind;
			tabela_alarmes[2] = ala_fp_cap;
			tabela_alarmes[3] = ala_ten_a;
			tabela_alarmes[4] = ala_ten_b;
			tabela_alarmes[5] = ala_sc;
			tabela_alarmes[6] = ala_subc;
			tabela_alarmes[7] = ala_chtt;
			tabela_alarmes[8] = ala_chtc;
			ala_demanda_ativa_aux = ala_demanda_ativa;
			}
		else
			{
			menu_aux = 0;
			M1_C5 = 0;
			menu1 = 5;
			exibe_menu();
			MENU_FIXO = 0;
			salva_menus();
			return;
			}
		}
	exibe_alarmes();
}


void salva_alarmes(void)
{
	ala_fp_ind = tabela_alarmes[1];
	ala_fp_cap = tabela_alarmes[2];
	ala_ten_a = tabela_alarmes[3];
	ala_ten_b = tabela_alarmes[4];
	ala_sc = tabela_alarmes[5];
	ala_subc = tabela_alarmes[6];
	ala_chtt = tabela_alarmes[7];
	ala_chtc = tabela_alarmes[8];
	ala_demanda_ativa = ala_demanda_ativa_aux;

	salva_programa();
	valida_programa();
 	exibe_alarmes();
}


void exibe_alarmes(void)
{
	#if (st92 == true)
		switch (menu_aux)
			{
			case 1:
				{
				if (exibiu == 0)
					{
					exibiu = 1;
					mensagem (2,20);
					}
				if (tabela_alarmes[1] > 99 )
					{
					exibe_off(29);
					}
				else
					{
					displayd(29,tabela_alarmes[1],'P');
					}
				break;
				}
			case 2:
				{
				if (exibiu == 0)
					{
					exibiu = 1;
					mensagem (2,21);
					}
				if (tabela_alarmes[2] > 99 )
					{
					exibe_off(29);
					}
				else
					{
					displayd(29,tabela_alarmes[2],'P');
					}
				break;
				}
			case 3:
				{
				if (exibiu == 0)
					{
					exibiu = 1;
					mensagem (2,22);
					}
				if (tabela_alarmes[3] == 0)
					{
					exibe_off(29);
					}
				else
					{
					displayp(30,tabela_alarmes[3],2,0,'P');
					}
				break;
				}
			case 4:
				{
				if (exibiu == 0)
					{
					exibiu = 1;
					mensagem (2,23);
					}
				if (tabela_alarmes[4] == 0)
					{
					exibe_off(29);
					}
				else
					{
					displayp(30,tabela_alarmes[4],2,0,'P');
					}
				break;
				}
			case 5:
				{
				if (exibiu == 0)
					{
					exibiu = 1;
					mensagem (2,24);
					}
				if (tabela_alarmes[5] == 0)
					{
					exibe_off(29);
					}
				else
					{
					displayp(29,tabela_alarmes[5],3,0,'P');
					}
				break;
				}
			case 6:
				{
				if (exibiu == 0)
					{
					exibiu = 1;
					mensagem (2,25);
					}
				if (tabela_alarmes[6] == 0)
					{
					exibe_off(29);
					}
				else
					{
					displayp(30,tabela_alarmes[6],2,0,'P');
					}
				break;
				}
			case 7:
				{
				if (exibiu == 0)
					{
					exibiu = 1;
					mensagem (2,26);
					}
				if (tabela_alarmes[7] == 0)
					{
					exibe_off(29);
					}
				else
					{
					displayp(30,tabela_alarmes[7],2,0,'P');
					}
				break;
				}
			case 8:
				{
				if (exibiu == 0)
					{
					exibiu = 1;
					mensagem (2,27);
					}
				if (tabela_alarmes[8] == 0)
					{
					exibe_off(29);
					}
				else
					{
					displayp(30,tabela_alarmes[8],2,0,'P');
					}
				break;
				}
			case 9:
				{
				#if (com_alarme_demanda == true)
					if (exibiu == 0)
						{
						exibiu = 1;
						mensagem(2,82);
						}
					if (ala_demanda_ativa_aux == 0)
						{
						exibe_off(29);
						}
					else
						{
						displayp(29,ala_demanda_ativa_aux,4,0,'P');
						}
				#endif
				break;
				}
			default:
				{
				menu_aux = 1;
				break;
				}
			}
	#else
		char x;
		x = 33;

		switch (menu_aux)
			{
			case 0:
				{
				exibe_menu();
				break;
				}
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
				{
				mensagem((x + menu_aux),1);
				break;
				}
			case 9:
				{
				mensagem(45,1);
				break;
				}
			default:
				{
				menu_aux = 1;
				}
			}

		if (menu_aux <= nro_menus5)
			{
	 		if ((menu_aux == 1) || ( menu_aux == 2))
	 			{
				 if (tabela_alarmes[menu_aux] == 100)
				 	{
					exibe_off();
				 	goto exibe_alarmes_10;
				 	}
				}
	 		else 
	 			{
				if ((tabela_alarmes[menu_aux] == 0) || (ala_demanda_ativa_aux == 0))
					{
		 			exibe_off();
				 	goto exibe_alarmes_10;
					}
				}
			if (menu_aux == 9)
				{
				binasc2(ala_demanda_ativa_aux);
				}
			else
				{
				binasc(tabela_alarmes[menu_aux]);
				}
			buf_display[8] = tabela_caracteres[MESPACO];
	 		if (menu_aux == 5)								//Sobre-Corrente
				{
				buf_display[9] = tabela_caracteres[buf_tmp[0] - '0'];
				buf_display[10] = tabela_caracteres[buf_tmp[1] - '0'];
				buf_display[11] = tabela_caracteres[buf_tmp[2] - '0'];
				}
			else if(menu_aux == 6)							//Sub-Corrente
				{
				buf_display[9] = tabela_caracteres[MESPACO];
				buf_display[10] = tabela_caracteres[buf_tmp[1] - '0'];
				buf_display[11] = tabela_caracteres[buf_tmp[2] - '0'];
				}
	 		else if ((menu_aux == 1) || ( menu_aux == 2))	//FP Indutivo e FP Capacitivo
				{
				buf_display[9] = tabela_caracteres[M0];
				buf_display[9] = buf_display[9] | 0x80;
				buf_display[10] = tabela_caracteres[buf_tmp[1] - '0'];
				buf_display[11] = tabela_caracteres[buf_tmp[2] - '0'];
				}
			else if(menu_aux == 9)							//Demanda Ativa
				{
				buf_display[8] = tabela_caracteres[buf_tmp[1] - '0'];
				buf_display[9] = tabela_caracteres[buf_tmp[2] - '0'];
				buf_display[10] = tabela_caracteres[buf_tmp[3] - '0'];
				buf_display[11] = tabela_caracteres[buf_tmp[4] - '0'];
				}
			else											//Tensão Alta e Baixa; Harmônicos de Tensão e de Corrente
				{
				buf_display[9] = tabela_caracteres[MESPACO];
				buf_display[10] = tabela_caracteres[buf_tmp[1] - '0'];
				buf_display[11] = tabela_caracteres[buf_tmp[2] - '0'];
				}
			}

exibe_alarmes_10:
		if (programando == 1)
			{
			if (ponto_segundo == 1)
				{
				buf_display[8] = buf_display[8] | 0x80;
				buf_display[9] = buf_display[9] | 0x80;
				buf_display[10] = buf_display[10] | 0x80;
				buf_display[11] = buf_display[11] | 0x80;
				}
			}
	#endif
}





