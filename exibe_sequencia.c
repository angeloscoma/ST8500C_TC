/*************************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST8610_MEN11                                                   *
; Funcao: TRATAMENTO DO MENU DE AJUSTE DO RELÓGIO						 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 29/03/2005                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;************************************************************************/

void exibe_sequencia(void)
{
	if (exibiu == 0)
		{
		exibiu = 1;
		mensagem(2,0);
		troca_linha();
		wr_lcd(1,'S');
		wr_lcd(1,'e');
		wr_lcd(1,'q');
		wr_lcd(1,' ');
		wr_lcd(1,' ');
		wr_lcd(1,' ');
		wr_lcd(1,' ');
		wr_lcd(1,'=');
		wr_lcd(1,' ');
		displayp(21,tabela_programa[7],2,0,0);
		}

	if (tabela_programa[7] == 0)
		{
		if (sel_seq_tab == 0)
			{
			lcd_gotoxy(10,2);
			wr_lcd(1,'U');
			wr_lcd(1,'s');
			wr_lcd(1,'u');
			wr_lcd(1,'a');
			wr_lcd(1,'r');
			wr_lcd(1,'i');
			wr_lcd(1,'o');
			}
		else
			{
			lcd_gotoxy(10,2);
			if (piscar == 0)
				{
				wr_lcd(1,'T');
				wr_lcd(1,'a');
				wr_lcd(1,'b');
				wr_lcd(1,'e');
				wr_lcd(1,'l');
				wr_lcd(1,'a');
				wr_lcd(1,' ');
				}
			else
				{
				wr_lcd(1,' ');
				wr_lcd(1,' ');
				wr_lcd(1,' ');
				wr_lcd(1,' ');
				wr_lcd(1,' ');
				wr_lcd(1,' ');
				wr_lcd(1,' ');
				}
			}
		}
	else
		{
		if (piscar == 0)
			{
			switch(nro_bancos_capacitor)
				{
				case 1:
					{
					break;
					}
				case 2:
					{
					lcd_gotoxy(12,2);
					wr_lcd(1,TAB_2_BANCOS[tabela_programa[7] - 1][0]+'0');
					wr_lcd(1,TAB_2_BANCOS[tabela_programa[7] - 1][1]+'0');
					break;
					}
				case 3:
					{
					lcd_gotoxy(11,2);
					wr_lcd(1,TAB_3_BANCOS[tabela_programa[7] - 1][0]+'0');
					wr_lcd(1,TAB_3_BANCOS[tabela_programa[7] - 1][1]+'0');
					wr_lcd(1,TAB_3_BANCOS[tabela_programa[7] - 1][2]+'0');
					break;
					}
				case 4:
					{
					lcd_gotoxy(11,2);
					wr_lcd(1,TAB_4_BANCOS[tabela_programa[7] - 1][0]+'0');
					wr_lcd(1,TAB_4_BANCOS[tabela_programa[7] - 1][1]+'0');
					wr_lcd(1,TAB_4_BANCOS[tabela_programa[7] - 1][2]+'0');
					wr_lcd(1,TAB_4_BANCOS[tabela_programa[7] - 1][3]+'0');
					break;
					}
				case 5:
					{
					lcd_gotoxy(10,2);
					wr_lcd(1,TAB_5_BANCOS[tabela_programa[7] - 1][0]+'0');
					wr_lcd(1,TAB_5_BANCOS[tabela_programa[7] - 1][1]+'0');
					wr_lcd(1,TAB_5_BANCOS[tabela_programa[7] - 1][2]+'0');
					wr_lcd(1,TAB_5_BANCOS[tabela_programa[7] - 1][3]+'0');
					wr_lcd(1,TAB_5_BANCOS[tabela_programa[7] - 1][4]+'0');
					break;
					}
				case 6:
					{
					lcd_gotoxy(10,2);
					wr_lcd(1,TAB_6_BANCOS[tabela_programa[7] - 1][0]+'0');
					wr_lcd(1,TAB_6_BANCOS[tabela_programa[7] - 1][1]+'0');
					wr_lcd(1,TAB_6_BANCOS[tabela_programa[7] - 1][2]+'0');
					wr_lcd(1,TAB_6_BANCOS[tabela_programa[7] - 1][3]+'0');
					wr_lcd(1,TAB_6_BANCOS[tabela_programa[7] - 1][4]+'0');
					wr_lcd(1,TAB_6_BANCOS[tabela_programa[7] - 1][5]+'0');
					break;
					}
				default:
					{
					lcd_gotoxy(10,2);
					wr_lcd(1,TAB_6_BANCOS[tabela_programa[7] - 1][0]+'0');
					wr_lcd(1,TAB_6_BANCOS[tabela_programa[7] - 1][1]+'0');
					wr_lcd(1,TAB_6_BANCOS[tabela_programa[7] - 1][2]+'0');
					wr_lcd(1,TAB_6_BANCOS[tabela_programa[7] - 1][3]+'0');
					wr_lcd(1,TAB_6_BANCOS[tabela_programa[7] - 1][4]+'0');
					wr_lcd(1,TAB_6_BANCOS[tabela_programa[7] - 1][5]+'0');
					break;
					}
				}
			}
		else
			{
			lcd_gotoxy(9,2);
			wr_lcd(1,' ');
			wr_lcd(1,' ');
			wr_lcd(1,' ');
			wr_lcd(1,' ');
			wr_lcd(1,' ');
			wr_lcd(1,' ');
			wr_lcd(1,' ');
			wr_lcd(1,' ');
			wr_lcd(1,' ');
			}
		}
}


