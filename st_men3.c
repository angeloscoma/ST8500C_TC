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
void mostra_chtc(void);


void trata_menu3(void)
{
/* TRATA EXIBIÇÀO CONTEUDO HARMONICO DE TENSAO */
	if (qmenu != 3)
		{
		if (modo_funca == 2)
			{
			mensagem(2, 96);
			}
		else
			{
	 		menu_aux = 0;
			qmenu = 3;
			qchtt = 0;
			qchtt_impar = 0;
			#if (monofasico == true)
				CHT_tr[1] = 6399;
				CHT_cr[1] = 6399;
			#else
				CHT_tr[1] = 6399;
				CHT_ts[1] = 6399;
				CHT_tt[1] = 6399;
				CHT_cr[1] = 6399;
				CHT_cs[1] = 6399;
				CHT_ct[1] = 6399;
			#endif
//			exibe_menu();
			}
//		return;
		}
	if (tecla_up==1)
		{
		tecla_up=0;
		exibir_menu = 1;
 		if (menu_aux > 0)
 			{
 			menu_aux--;
 			if (qchtt_impar != 1)
 				{
	 			qchtt_impar = qchtt_impar - 2;
	 			}
	 		}
		 }
	else if (tecla_down==1)
		{
		 tecla_down = 0;
         exibir_menu = 1;
		 if (menu_aux < NRO_CHT_BY_2)
	 		{
 			menu_aux++;
 			if (qchtt_impar != 0)
 				{
	 			qchtt_impar = qchtt_impar + 2;
	 			}
 			}
		}
	else if (tecla_enter==1)
		{
	 	tecla_enter=0;
		if (qmenu == 3)
			{
			qmenu = 2;
	 		menu_aux = 0;
			qchtt = 0;
			qchtt_impar = 0;
			exibiu = 0;
			}
		exibir_menu = 1;
		}		
	else if (tecla_reset==1)
		{
		encerra_menus();
		return;
		}
	if (qmenu == 2)
		{
		mostra_chtt();
		}
	if (qmenu == 3)
		{
		mostra_chtc();
		}
}



void mostra_chtc(void)		
{

	if (exibir_menu == 1)
		{
		if (exibiu == 0)
			{
			exibiu = 1;
			mensagem(1,39);
			mensagem(2,m_menu1_111);
			mensagem(3,m_menu1_112);
			mensagem(4,m_menu1_113);
			}
		
		exibir_menu = 0;
		qchtt = menu_aux;
		if (qchtt == 0)
			{
			lcd_gotoxy(4,1);
			display('T');
			display('o');
			display('t');
			displayp(9,qchtt+1,2,0,0);
			displayp(14,qchtt+3,2,0,0);
			qchtt_impar = 0;
			}
		else if (qchtt == 1)
			{
			displayp(4,1,2,0,0);
			displayp(9,3,2,0,0);
			displayp(14,5,2,0,0);
			qchtt_impar = 1;
			lcd_gotoxy(6,1);
			display(' ');
			}
		else
			{
			if (qchtt_impar < 46)
				{
				displayp(4,qchtt_impar,2,0,0);
				displayp(9,qchtt_impar+2,2,0,0);
				displayp(14,qchtt_impar+4,2,0,0);
				}
			lcd_gotoxy(6,1);
			display(' ');
			}
		
		
		if (qchtt_impar < 46)
			{
			displayp(19,CHT_cr[qchtt],2,1,6);
			displayp(24,CHT_cr[qchtt+1],2,1,6);
			displayp(29,CHT_cr[qchtt+2],2,1,6);
	
			displayp(35,CHT_cs[qchtt],2,1,6);
			displayp(40,CHT_cs[qchtt+1],2,1,6);
			displayp(45,CHT_cs[qchtt+2],2,1,6);
	
			displayp(51,CHT_ct[qchtt],2,1,6);
			displayp(56,CHT_ct[qchtt+1],2,1,6);
			displayp(61,CHT_ct[qchtt+2],2,1,6);
			}
	}
}

