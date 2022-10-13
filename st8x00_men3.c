/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST8610_MEN3                                                    *
; Funcao: MODULO PRINCIPAL DE CONTROLE									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */

void xtrata_menu3(void);
void xexibe_chtc(void);
void xmostra_chtc(void);


void xtrata_menu3(void)
{
/* TRATA EXIBIÇÀO CONTEUDO HARMONICO DE TENSAO */
	if (qmenu != 3)
		{
 		menu_aux = 1;
		qmenu = 3;
		time_out_menus = 60;
		exibe_menu();
		qchtt = 0;
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
	 		xmostra_chtc();
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
	 		xmostra_chtc();
	 		}
		}
	else if (tecla_enter==1)
		{
	 	tecla_enter=0;
		qchtt = 0;
		menu_aux = 0;
		exibir_menu = 1;
		ja_rolou = false;
		rolando = false;
		}		
	else if (tecla_reset==1)
		{
		tecla_reset=0;
		menu_aux = 1;
		menu1 = 3;
		qmenu = 0;
		exibe_menu();
		return;
		}
	xexibe_chtc();
}




void xexibe_chtc(void)
{
	if (exibir_menu == 1)
		{
		xmostra_chtc();
		}
}


void xmostra_chtc(void)		
{
	unsigned char x;
	exibir_menu = 0;
	ja_rolou = false;
	rolando = false;
	#if (disp_7seg == true)
		buf_display[0]=tabela_caracteres[MD];
		buf_display[1]=tabela_caracteres[MH];
		buf_display[2]=tabela_caracteres[MC];
	#endif
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



