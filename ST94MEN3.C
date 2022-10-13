/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_MAIN                                                        *
; Funcao: MODULO PRINCIPAL DE CONTROLE									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */

void trata_menu3(void);
void exibe_chtc(void);
void mostra_chtc(void);


void trata_menu3(void)
{
/* TRATA EXIBIÇÀO CONTEUDO HARMONICO DE TENSAO */
	if (M1_C3 == 0)
		{
 		menu_aux = 0;
		M1_C3 = 1;
		time_out_menus = 60;
		exibe_menu();
		qchtt = 0;
		fase_cht = 'R';
		return;
		}
	if (tecla_up==1)
		{
		tecla_up=0;
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
	 		mostra_chtc();
		 	}
		 }
	else if (tecla_down==1)
		{
		 tecla_down=0;
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
	 		mostra_chtc();
	 		}
		}
	else if (tecla_enter==1)
		{
	 	tecla_enter=0;
		qchtt = 0;
		menu_aux = 0;
		exibir_menu = 1;
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
		}		
	else if (tecla_reset==1)
		{
		menu_aux = 0;
		tecla_reset=0;
		exibe_menu();
		M1_C3=0;
		return;
		}
	exibe_chtc();
}




void exibe_chtc(void)
{
	if (exibir_menu == 1)
		{
		mostra_chtc();
		}
}


void mostra_chtc(void)		
{
	unsigned char x;
	exibir_menu = 0;
	#if (st92 == true)
	#else
		buf_display[0]=tabela_caracteres[MD];
		buf_display[1]=tabela_caracteres[MH];
		buf_display[2]=tabela_caracteres[MC];
		qchtt = menu_aux;
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
			for (x = 1 ; x < (NRO_CHT+1); x = x + 2)
				{
				if (x == qchtt) 
					{
					if (fase_cht == 'R')
						{
						disp_chttr(x);
						break;
						}
					else if (fase_cht == 'S')
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



