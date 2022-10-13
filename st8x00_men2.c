/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_MAIN                                                        *
; Funcao: TRATAMENTO DO MENU DE CONTEUDO HARMONICO						 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */
  
void trata_menu2(void);
void exibe_chtt(void);
void mostra_chtt(void);
void disp_chttr(char);
void disp_ctt(char);

void trata_menu2(void)
{
	if (menu1 == 2)
		{
		if (qmenu != 2)
			{
	 		menu_aux = 0;
	 		exibiu = 0;
			qmenu = 2;
			time_out_menus = 60;
			qchtt = 0;
			exibir_menu = 0;
			reset_rolar();
			time_out2 = 2;
			return;
			}
		}
	else if (menu1 == 3)
		{
		if (qmenu != 3)
			{
	 		menu_aux = 0;
	 		exibiu = 0;
			qmenu = 3;
			time_out_menus = 60;
			qchtt = 0;
			exibir_menu = 0;
			reset_rolar();
			time_out2 = 2;
			return;
			}
		}
	if (tecla_up==1)
		{
		tecla_up=0;
		exibiu = 0;
		exibir_menu = 1;
		ja_rolou = false;
		time_out2 = 2;
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
	else if (tecla_down==1)
		{
		tecla_down=0;
		exibiu = 0;
		exibir_menu = 1;
		ja_rolou = false;
		time_out2 = 2;
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
	else if (tecla_enter==1)
		{
		time_out2 = 2;
	 	tecla_enter = 0;
	 	exibiu = 0;
	 	if (ja_rolou == false)
			{
			ja_rolou = true;
			}
		qchtt = 0;
		exibir_menu = 1;
		}		
	else if (tecla_reset==1)
		{
		tecla_reset=0;
		menu_aux = 1;
		qmenu = 0;
		ja_rolou = false;
		exibe_menu();
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
	qchtt = menu_aux;
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
}

void disp_chttr(char x)
{
	#if (disp_7seg == true)
		if (time_out2 == 0)
			{
			ja_rolou= true;
			}
		disp_ctt(x);
		if (ja_rolou == true)
			{
			exibir_menu = 0;
			if (qchtt == 0)
				{
				if (qmenu == 2)
					{
					display(1,CHT_tr[0],1,6);
					}
				else
					{
					display(1,CHT_cr[0],1,6);
					}
				}
			else if (qchtt == 1)
				{
				if (qmenu == 2)
					{
					display(1,100,1,0);
					}
				else
					{
					display(1,100,1,0);
					}
				}
			else
				{
				if (qmenu == 2)
					{
					display(1,CHT_tr[qchtt],1,6);
					}
				else
					{
					display(1,CHT_cr[qchtt],1,6);
					}
				}
			}
	#else
	
		disp_ctt(x);
		qchtt = menu_aux;
		if (qmenu == 2)
			{
			if (qchtt == 0)
				{
				#if (monofasico == false)
					displayp(11,CHT_tr[0],2,2,6);
					displayp(19,CHT_ts[0],2,2,6);
					displayp(27,CHT_tt[0],2,2,6);
				#else
					displayp(22,CHT_tr[0],2,2,6);
				#endif
				}
			else if (qchtt == 1)
				{
				#if (monofasico == false)
					displayp(11,100,3,1,0);
					displayp(19,100,3,1,0);
					displayp(27,100,3,1,0);
				#else
					displayp(22,100,3,1,0);
				#endif
				}
			else
				{
				if (qchtt < (NRO_CHT+1))
					{
					#if (monofasico == false)
						displayp(11,CHT_tr[qchtt],2,2,6);
						displayp(19,CHT_ts[qchtt],2,2,6);
						displayp(27,CHT_tt[qchtt],2,2,6);
					#else
						displayp(22,CHT_tr[qchtt],2,2,6);
					#endif
					}
				}
			}
		else
			{
			if (qchtt == 0)
				{
				#if (monofasico == false)
					displayp(11,CHT_cr[0],2,2,6);
					displayp(19,CHT_cs[0],2,2,6);
					displayp(27,CHT_ct[0],2,2,6);
				#else
					displayp(22,CHT_cr[0],2,2,6);
				#endif
				}
			else if (qchtt == 1)
				{
				#if (monofasico == false)
					displayp(11,100,3,1,0);
					displayp(19,100,3,1,0);
					displayp(27,100,3,1,0);
				#else
					displayp(22,100,3,1,0);
				#endif
				}
			else
				{
				if (qchtt < (NRO_CHT+1))
					{
					#if (monofasico == false)
						displayp(11,CHT_cr[qchtt],2,2,6);
						displayp(19,CHT_cs[qchtt],2,2,6);
						displayp(27,CHT_ct[qchtt],2,2,6);
					#else
						displayp(22,CHT_cr[qchtt],2,2,6);
					#endif
					}
				}
			}
	#endif
}

void disp_ctt(char x)
{	
	#if (disp_7seg == true)
		switch (x)
			{
			case 0:
				{
				buf_display[0]=tabela_caracteres[MT];
				buf_display[1]=tabela_caracteres[MO];
				buf_display[2]=tabela_caracteres[MT];
				buf_display[3]=mponto;
				break;
				}
			case 1:
				{
				buf_display[0]=tabela_caracteres[MF];
				buf_display[1]=tabela_caracteres[MU];
				buf_display[2]=tabela_caracteres[MN];
				buf_display[3]=tabela_caracteres[MD];
				break;
				}
			default:
				{
				buf_display[0]=tabela_caracteres[MH];
				buf_display[1]=mhifen;
				binasc(x);					
				buf_display[2]=tabela_caracteres[buf_tmp[1]-'0'];
				buf_display[3]=tabela_caracteres[buf_tmp[2]-'0'];
				}
			}
	#else
		if (exibiu == 0)
			{
			switch (x)
				{
				case 0:
					{
					mensagem(1,54);
					break;
					}
				case 1:
					{
					mensagem(1,55);
					break;
					}
				default:
					{
					mensagem(1,56);
					#if (monofasico == true)
						displayp(3,x,2,0,0);
					#else
						displayp(1,x,2,0,0);
					#endif
					break;
					}
				}
			#if (monofasico == true)
				mensagem(2,57);
			#else
				mensagem(2,61);
			#endif
			exibiu = 1;
			}
	#endif
}

