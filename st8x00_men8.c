/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRONICOS                                  *
; Modulo: ST8610_MEN8                                                    *
; Funcao: TRATAMENTO DO MENU DE ACIONAMENTO MANUAL						 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/


void exibe_aciona (void)
{
	status_banco_minimo = 0;
	if (exibir_menu == 1)
		{
		exibir_menu = 0;
		if (menu_aux <= nro_bancos_capacitor)
			{
			#if (ST8100C == true)
				mensagem(menu_aux,2);
			#else
				mensagem (1,22);
				#if (monofasico == false)
					displayfp_aciona(12,fator_pot, 0);
				#else
					displayfp_aciona(12,fator_pot_r,0);
				#endif
			#endif
	
			if (tabela_programa[menu_aux] == 1)		//exibe: Desliga Banco: xx
				{
				#if (disp_7seg == true)
					buf_display[3] = tabela_caracteres[20];
				#else
					mensagem (2,53);
					displayp (30,menu_aux,2,0,0);
				#endif
				}
			else									//exibe: Liga Banco: xx
				{
				#if (disp_7seg == true)
					buf_display[3] = tabela_caracteres[28];
				#else
					mensagem (2,52);
					displayp (30,menu_aux,2,0,0);
				#endif
				}
			}
		}
}


void trata_menu8(void)
{
	char x;
	if (qmenu != 8)
		{
		qmenu = 8;
		exibiu = 0;
		time_out_menus = 60;
		reset_rolar();
		menu_aux = 1;
		com_manual = true;
		for (x = 0; x < nro_bancos_capacitor; x++)
			{
			tabela_programa[x + 1] = 0;
			desligar_banco(x);
			}
		}
	else
		{
		if (tecla_enter == 1)
			{
		 	tecla_enter = 0;
		 	exibiu = 0;
			if (ja_rolou == true)
				{
				reset_rolar();
				}
			if (tabela_programa[menu_aux] == 1)			//desliga banco
				{
				tabela_programa[menu_aux] = 0;
				desligar_banco(menu_aux - 1);
				if (menu_aux > 1)
					{
					menu_aux--;
					}
				}
			else								//liga banco
				{
				tabela_programa[menu_aux] = 1;
				aux_tempo_repouso[menu_aux - 1] = 0;
				banco_disponivel[menu_aux - 1] = 1;
				ligar_banco(menu_aux - 1);
				if (menu_aux < nro_bancos_capacitor)
					{
					menu_aux++;
					}
				}
			}		
		else if (tecla_up == 1)
			{
			tecla_up = 0;
			exibiu = 0;
			if (menu_aux > 1)
				{
				menu_aux--;
				}
			}
		else if (tecla_down == 1)
			{
			tecla_down = 0;
			exibiu = 0;
			if (menu_aux < nro_bancos_capacitor)
				{
				menu_aux++;
				}
			}
		else if (tecla_reset==1)
			{
			
			tecla_reset=0;
			menu_aux = 1;
			menu1 = 8;
			qmenu = 0;
			com_manual = false;
			aux_tempo_aciona = tempo_desaciona;
			for (x = 0; x < NRO_MAXIMO_BANCOS_CAPACITOR; x--)
				{
				aux_tempo_repouso[x] = tempo_repouso[x];
				banco_acionado[x] = 0;
				}
			
			exibe_menu();
			return;
			}
		}
	exibe_aciona();
}

