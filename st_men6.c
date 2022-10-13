/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_MAIN                                                        *
; Funcao: MODULO PRINCIPAL DE CONTROLE									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */
  

void trata_menu6(void);
void exibe_data_hora(void);
void salva_data_hora(void);
void exibe_menu6(void);

void trata_menu6(void)
{
/* TRATA DATA E HORA */
    if (M1_C6 == 0)
    	{
		M1_C6 = 1;
		time_out_menus = 60;
		}
	if (tecla_enter==1)
		{
		tecla_enter=0;
		if (programando==1)
			{
			menu_aux++;
			if (menu_aux == nro_menus6)
				{
				salva_data_hora();
				}
			}
		else
			{
			if (tempo_senha != 0)
				{
				programando = 1;
				buf_menu[0] = dia;
				buf_menu[1] = mes;
				buf_menu[2] = ano;
				buf_menu[3] = hora;
				buf_menu[4] = minuto;
				}
			else
				{
				trata_senha();
				return;
				}
			}
		}
	else if (tecla_reset==1)
		{
		menu_aux = 0;
		tecla_reset=0;
		M1_C6=0;
		programando=0;
		exibe_menu();
		return;
		}
	else if (programando==1)
		{
		if (tecla_up==1)
			{
			tecla_up=0;
			buf_menu[menu_aux]++;
			if (tempo_senha != 255)
				{
				tempo_senha++;
				}
		 	}
		else if (tecla_down==1)
			{
		 	tecla_down=0;
			buf_menu[menu_aux]--;
			if (tempo_senha != 255)
				{
				tempo_senha++;
				}
			}
// testa se valores dentro dos limites para data e hora 
//                        123456789012345678901234567890 
//const char mdata[28] = "ST9300M v1.00 050803 200000";
		if ((buf_menu[0] > 31) || (buf_menu[0] == 0))
			{
			buf_tmp[1] = '0';
			buf_tmp[2] = mdata[15];
			buf_tmp[3] = mdata[16];
			ascbin2();
			buf_menu[0] = data1;
			}
		if ((buf_menu[1] > 12) || (buf_menu[1] == 0))
			{
			buf_tmp[1] = '0';
			buf_tmp[2] = mdata[17];
			buf_tmp[3] = mdata[18];
			ascbin2();
			buf_menu[1] = data1;
			}
		if (buf_menu[2] < 2)
			{
			buf_tmp[1] = '0';
			buf_tmp[2] = mdata[19];
			buf_tmp[3] = mdata[20];
			ascbin2();
			buf_menu[2] = data1;
			}
		if (buf_menu[3] > 24)
			{
			buf_tmp[1] = '0';
			buf_tmp[2] = mdata[22];
			buf_tmp[3] = mdata[23];
			ascbin2();
			buf_menu[3] = data1;
			}
		if (buf_menu[4] > 59)
			{
			buf_tmp[1] = '0';
			buf_tmp[2] = mdata[24];
			buf_tmp[3] = mdata[25];
			ascbin2();
			buf_menu[4] = data1;
			}
		}
		exibe_data_hora();
}


void salva_data_hora(void)
{
	programando=0;
	dia = buf_menu[0];
	mes = buf_menu[1];
	ano = buf_menu[2];
	hora = buf_menu[3];
	minuto = buf_menu[4];
	rtc_set_datetime();
	exibe_data_hora();
	menu_aux=0;
}


void exibe_data_hora(void)
{
	if (programando == 1)
		{
		exibe_menu6();
		}
	else
		{
		buf_menu[0]=dia;
		buf_menu[1]=mes;
		buf_menu[2]=ano;
		buf_menu[3]=hora;
		buf_menu[4]=minuto;
		exibe_menu6();
		}
}


void exibe_menu6(void)
{				
	binasc(buf_menu[0]);					

//	buf_display[0]=tabela_caracteres[buf_tmp[1]-'0'];
//	buf_display[1]=tabela_caracteres[buf_tmp[2]-'0'];
	binasc(buf_menu[1]);
	if (buf_tmp[1]=='0')
		{
//		buf_display[2]=mbarra_esquerda;
		}
	else
		{
//		buf_display[2]=(tabela_caracteres[buf_tmp[1]-'0'] | mbarra_esquerda);
		}
//	buf_display[3]=tabela_caracteres[buf_tmp[2]-'0'];
	
	binasc(buf_menu[2]);
//	buf_display[4]=tabela_caracteres[M2];
//	buf_display[5]=tabela_caracteres[M0];
//	buf_display[6]=tabela_caracteres[buf_tmp[1]-'0'];
//	buf_display[7]=tabela_caracteres[buf_tmp[2]-'0'];
	
	binasc(buf_menu[3]);					
//	buf_display[8]=tabela_caracteres[buf_tmp[1]-'0'];
	if (ponto_segundo==1)
		{
//		buf_display[9]=(tabela_caracteres[buf_tmp[2]-'0'] | 0x80) ;
		}
	else
		{
//		buf_display[9]=tabela_caracteres[buf_tmp[2]-'0'] ;
		}
	binasc(buf_menu[4]);					
//	buf_display[10]=tabela_caracteres[buf_tmp[1]-'0'];
//	buf_display[11]=tabela_caracteres[buf_tmp[2]-'0'];
	
	if (programando == 1)
		{
		 if (menu_aux==0)
		 	{
		 	if (ponto_segundo == 1)
		 		{
//				buf_display[0] = buf_display[0] | 0x80;  /* acende ponto */
//				buf_display[1] = buf_display[1] | 0x80;  /* acende ponto */
				}
			else
				{
//				buf_display[0] = buf_display[0] & 0x7F;  /* apaga ponto */
//				buf_display[1] = buf_display[1] & 0x7F;  /* apaga ponto */
				}
			}
		 else if (menu_aux==1)
		 	{
		 	if (ponto_segundo == 1)
		 		{
//				buf_display[2] = buf_display[2] | 0x80;  /* acende ponto */
//				buf_display[3] = buf_display[3] | 0x80;  /* acende ponto */
				}
			else
				{
//				buf_display[2] = buf_display[2] & 0x7F;  /* apaga ponto */
//				buf_display[3] = buf_display[3] & 0x7F;  /* apaga ponto */
				}
			}
		 else if (menu_aux==2)
		 	{
		 	if (ponto_segundo == 1)
		 		{
//				buf_display[6] = buf_display[6] | 0x80;  /* acende ponto */
//				buf_display[7] = buf_display[7] | 0x80;  /* acende ponto */
				}
			else
				{
//				buf_display[6] = buf_display[6] & 0x7F;  /* apaga ponto */
//				buf_display[7] = buf_display[7] & 0x7F;  /* apaga ponto */
				}
			}
		 else if (menu_aux==3)
		 	{
		 	if (ponto_segundo == 1)
		 		{
//				buf_display[8] = buf_display[8] | 0x80;  /* acende ponto */
//				buf_display[9] = buf_display[9] | 0x80;  /* acende ponto */
				}
			else
				{
//				buf_display[8] = buf_display[8] & 0x7F;  /* apaga ponto */
//				buf_display[9] = buf_display[9] & 0x7F;  /* apaga ponto */
				}
			}
		 else if (menu_aux==4)
		 	{
		 	if (ponto_segundo == 0)
		 		{
//				buf_display[10] = buf_display[10] | 0x80;  /* acende ponto */
//				buf_display[11] = buf_display[11] | 0x80;  /* acende ponto */
				}
			else
				{
//				buf_display[10] = buf_display[10] & 0x7F;  /* apaga ponto */
//				buf_display[11] = buf_display[11] & 0x7F;  /* apaga ponto */
				}
		 	}
//		buf_display[12] = tempo_senha;  /* apaga leds */
		}
	else
		{
//		buf_display[12] = 0;  /* apaga leds */
		}
}


