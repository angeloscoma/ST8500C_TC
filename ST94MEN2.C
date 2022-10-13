/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: st94men2.c                                                     *
; Funcao: Controle do Menu de Conteúdo Harmônico						 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */

void trata_menu2(void);
void exibe_chtt(void);
void mostra_chtt(void);
void disp_chttr(char);
void disp_chtts(char);
void disp_chttt(char);
void disp_ctt(char);

void trata_menu2(void)
{
	if (menu1 == 2)
		{
		if (M1_C2 == 0)
			{
			M1_C2 = 1;
			M1_C3 = 0;
			menu_aux = 0;
			time_out_menus = 60;
			exibe_menu();
			qchtt = 0;
			fase_cht = 'R';
			exibiu = 0;
			qmenu = 2;
			return;
			}
 		}
 	else if (menu1 == 3)
 		{
		if (M1_C3 == 0)
			{
			M1_C2 = 0;
			M1_C3 = 1;
			menu_aux = 0;
			time_out_menus = 60;
			exibe_menu();
			qchtt = 0;
			fase_cht = 'R';
			exibiu = 0;
			qmenu = 3;
			
			return;
			}
	 	}

	if (tecla_up == 1)
		{
		tecla_up = 0;
		exibiu = 0;
		exibir_menu = 1;
	 	if (menu_aux > 0)
	 		{
	 		if (menu_aux > 1)
	 			{
	 			menu_aux = menu_aux - 2;
	 			}
	 		else
	 			{
	 			menu_aux--;
	 			}
	 		mostra_chtt();
		 	}
		 }
	else if (tecla_down == 1)
		{
		tecla_down = 0;
		exibiu = 0;
        exibir_menu = 1;
		if (menu_aux < nro_menus2)
	 		{
	 		if (menu_aux == 0)
	 			{
	 			menu_aux++;
	 			}
	 		else
	 			{
	 			menu_aux = menu_aux + 2;
	 			}
	 		mostra_chtt();
	 		}
		}
	else if (tecla_enter == 1)
		{
	 	tecla_enter = 0;
		exibiu = 0;
		exibir_menu = 1;
		#if (st92 == false)
			if (fase_cht == 'R')
				{
				fase_cht = 'S';
				}
			else if (fase_cht == 'S')
				{
				fase_cht = 'T';
				}
			else
				{
				fase_cht = 'R';
				}
		#endif
		}		
	else if (tecla_reset == 1)
		{
		menu_aux = 0;
		tecla_reset = 0;
		exibe_menu();
		M1_C2 = 0;
		M1_C3 = 0;
		return;
		}
	exibe_chtt();
}




void exibe_chtt(void)
{
	if (exibir_menu == 1)
		{
		mostra_chtt();
		}
}


void mostra_chtt(void)		
{
	char x;
	exibir_menu = 0;
	
	qchtt = menu_aux;


	#if (st92 == true)
		if (qchtt == 0)
			{
			disp_chttr(0);
		    }
		else
			{
			for (x = 1 ; x < (NRO_CHT+1); x = x + 2)
				{
				if (x == qchtt) 
					{
					disp_chttr(x);
					}
				}
			}
	#else
		buf_display[0] = tabela_caracteres[MD];
		buf_display[1] = tabela_caracteres[MH];
		if (menu1 == 2 )
			{
			buf_display[2] = tabela_caracteres[MT];
			}
		else
			{
			buf_display[2] = tabela_caracteres[MC];
			}
		if (qchtt == 0)
			{
			if (fase_cht == 'R')
				{
				disp_chttr(0);
				}
			else if (fase_cht == 'S')
				{
				disp_chtts(0);
				}
			else
				{
				disp_chttt(0);
				}
		    }
		else
			{
			for (x = 1 ; x < (NRO_CHT + 1); x = x + 2)
				{
				if (x == qchtt)
					{
					if (fase_cht == 'R')
						{
						disp_chttr(x);
						break;
						}
					if (fase_cht == 'S')
						{
						disp_chtts(x);
						break;
						}
					else
						{
						disp_chttt(x);
						break;
						}
					}
				}
			}
	#endif
}

void disp_chttr(char x)
{
	#if (st92 == true)
		disp_ctt(x);
		qchtt = menu_aux;
		if (qmenu == 2)
			{
			if (qchtt == 0)
				{
				displayp(11,CHT_tr[0],2,2,6);
				displayp(19,CHT_ts[0],2,2,6);
				displayp(27,CHT_tt[0],2,2,6);
				}
			else if (qchtt == 1)
				{
				displayp(11,100,3,1,0);
				displayp(19,100,3,1,0);
				displayp(27,100,3,1,0);
				}
			else
				{
				if (qchtt < (NRO_CHT+1))
					{
					displayp(11,CHT_tr[qchtt],2,2,6);
					displayp(19,CHT_ts[qchtt],2,2,6);
					displayp(27,CHT_tt[qchtt],2,2,6);
					}
				}
			}
		else
			{
			if (qchtt == 0)
				{
				displayp(11,CHT_cr[0],2,2,6);
				displayp(19,CHT_cs[0],2,2,6);
				displayp(27,CHT_ct[0],2,2,6);
				}
			else if (qchtt == 1)
				{
				displayp(11,100,3,1,0);
				displayp(19,100,3,1,0);
				displayp(27,100,3,1,0);
				}
			else
				{
				if (qchtt < (NRO_CHT+1))
					{
					displayp(11,CHT_cr[qchtt],2,2,6);
					displayp(19,CHT_cs[qchtt],2,2,6);
					displayp(27,CHT_ct[qchtt],2,2,6);
					}
				}
			}
	#else
		buf_display[3] = tabela_caracteres[MR];
		disp_ctt(x);
		if (x == 1)
			{
			display(3,100,1,0);
			}
		else
			{
			if (M1_C3 == 1)
				{
				display(3,CHT_cr[qchtt],1,6);
				}
			else
				{
				display(3,CHT_tr[qchtt],1,6);
				}
			}
	#endif
}

void disp_chtts(char x)
{
	#if (st92 == true)
	#else
		buf_display[3]= tabela_caracteres[MS];
		disp_ctt(x);
		if (M1_C3 == 1)
			{
			display(3,CHT_cs[qchtt],1,6);
			}
		else
			{
			display(3,CHT_ts[qchtt],1,6);
			}
	#endif
}

void disp_chttt(char x)
{
	#if (st92 == true)
	#else
		buf_display[3] = tabela_caracteres[MT];
		disp_ctt(x);
		if (M1_C3 == 1)
			{
			display(3,CHT_ct[qchtt],1,6);
			}
		else
			{
			display(3,CHT_tt[qchtt],1,6);
			}
	#endif
}

void disp_ctt(char x)
{	
	#if (st92 == true)
		if (exibiu == 0)
			{
			switch (x)
				{
				case 0:
					{
					mensagem(1,75);
					break;
					}
				case 1:
					{
					mensagem(1,76);
					break;
					}
				default:
					{
					mensagem(1,77);
					displayp(1,x,2,0,0);
					break;
					}
				}
			mensagem(2,78);
			exibiu = 1;
			}
	#else
		if (x == 0)
			{
			buf_display[4] = tabela_caracteres[MT];
			buf_display[5] = tabela_caracteres[MO];
			buf_display[6] = tabela_caracteres[MT];
			buf_display[7] = tabela_caracteres[mespaco];
			}
		else if (x == 1)
			{
			buf_display[4] = tabela_caracteres[MF];
			buf_display[5] = tabela_caracteres[MU];
			buf_display[6] = tabela_caracteres[MN];
			buf_display[7] = tabela_caracteres[MD];
			}
		else
			{
			buf_display[4] = tabela_caracteres[MH];
			buf_display[5] = mhifen;
			binasc(x);					
			buf_display[6] = tabela_caracteres[buf_tmp[1]-'0'];
			buf_display[7] = tabela_caracteres[buf_tmp[2]-'0'];
			}
	#endif
}

