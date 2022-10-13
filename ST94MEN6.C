/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: st94men6.c                                                     *
; Funcao: Controle do Menu de Data e Hora								 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */

void exibe_data_hora(void);
//void rtc_set_datetime(void);
char buf_menu6[6];

void trata_menu6(void)
{
    if (M1_C6 == 0)
    	{
		M1_C6 = 1;
		time_out_menus = 60;
		menu_aux = 0;
		exibiu = 0;
		buf_menu6[0] = dia;
		buf_menu6[1] = mes;
		buf_menu6[2] = ano;
		buf_menu6[3] = hora;
		buf_menu6[4] = minuto;
		buf_menu6[5] = segundo;
		}

	if (tecla_enter == 1)
		{
		tecla_enter = 0;
		exibiu = 0;
		if (programando == 1)
			{
			if (menu_aux == (nro_menus6 - 1))
				{
				programando = 0;
				menu_aux = 0;
				salva_data_hora();
				}
			else
				{
				menu_aux++;
				salva_data_hora();
				}
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
	if (tecla_reset == 1)
		{
		if (programando == 1)
			{
			programando = 0;
			buf_menu6[0] = dia;
			buf_menu6[1] = mes;
			buf_menu6[2] = ano;
			buf_menu6[3] = hora;
			buf_menu6[4] = minuto;
			buf_menu6[5] = segundo;
			}
		else
			{
			menu_aux = 0;
			exibiu = 0;
			tecla_reset = 0;
			M1_C6 = 0;
			exibe_menu();
			return;
			}
		}
	if (programando == 1)
		{
		if (tecla_up == 1)
			{
			tecla_up = 0;
			exibiu = 0;
			if (tempo_senha != 255)
				{
				tempo_senha++;
				}
			switch (menu_aux)
				{
				case 0:
					{
					if ((buf_menu6[2] % 4) == 0)		//ano
						{
						if (buf_menu6[1] == 2)
							{
							if (buf_menu6[0] < 29)		//dia
								{
								buf_menu6[0]++;
								}
							}
						}
					else
						{
						if (buf_menu6[1] == 2)
							{
							if (buf_menu6[0] < 28)		//dia
								{
								buf_menu6[0]++;
								}
							}
						}
					if (buf_menu6[1] != 2)
						{
						if (buf_menu6[1] == 1 || 3 || 5 || 7 || 8 || 10 || 12 )
							{
							if (buf_menu6[0] < 31)		//dia
								{
								buf_menu6[0]++;		//dia
								}
							}
						else
							{
							if (buf_menu6[0] < 30)		//dia
								{
								buf_menu6[0]++;		//dia
								}
							}
						}
					break;
					}
				case 1:
					{
					if (buf_menu6[1] < 12)		//mes
						{
						buf_menu6[1]++;
						}
					break;
					}
				case 2:
					{
					if (buf_menu6[2] < 99)		//ano
						{
						buf_menu6[2]++;		//ano
						}
					break;
					}
				case 3:
					{
					if (buf_menu6[3] < 23)		//hora
						{
						buf_menu6[3]++;		//hora
						}
					break;
					}
				case 4:
				case 5:
					{
					if (buf_menu6[menu_aux] < 59)		//minuto e segundo
						{
						buf_menu6[menu_aux]++;		//minuto e segundo
						}
					break;
					}
				default:
					{
					menu_aux = 0;
					}
				}
		 	}
		else if (tecla_down == 1)
			{
		 	tecla_down = 0;
			exibiu = 0;
			if (tempo_senha != 255)
				{
				tempo_senha++;
				}
			if (menu_aux < 3)
				{
				if (buf_menu6[menu_aux] > 1)
					{
					buf_menu6[menu_aux]--;
					}
				}
			else
				{
				if (buf_menu6[menu_aux] > 0)
					{
					buf_menu6[menu_aux]--;
					}
				}
			}
		}
	exibe_data_hora();
}


void salva_data_hora(void)
{
	dia = buf_menu6[0];
	mes = buf_menu6[1];
	ano = buf_menu6[2];
	hora = buf_menu6[3];
	minuto = buf_menu6[4];
	segundo = buf_menu6[5];

	#if (com_relogio == true)
		data_modbus = data1_int;
		rtc_set_datetime();
	#else
		data_modbus = data1_int;
		rtc_wr_e2p();
	#endif
	exibe_data_hora();
}


void exibe_data_hora(void)
{				
	#if (st92 == true)
		if (M1_C6 == 1)
			{
			if (exibiu == 0)
				{
				exibiu = 1;
				mensagem (1,72);
				mensagem (2,73);
				}
			if (programando == 1)
				{
				switch (menu_aux)
					{
					case 0:
						{
						displayp (8,buf_menu6[0],2,0,'P');		//dia
						displayp (11,buf_menu6[1],2,0,0);		//mes
						displayp (14,buf_menu6[2],2,0,0);		//ano
						displayp (24,buf_menu6[3],2,0,0);		//hora
						displayp (27,buf_menu6[4],2,0,0);		//minuto
						displayp (30,buf_menu6[5],2,0,0);		//segundo
						break;
						}
					case 1:
						{
						displayp (8,buf_menu6[0],2,0,0);		//dia
						displayp (11,buf_menu6[1],2,0,'P');		//mes
						displayp (14,buf_menu6[2],2,0,0);		//ano
						displayp (24,buf_menu6[3],2,0,0);		//hora
						displayp (27,buf_menu6[4],2,0,0);		//minuto
						displayp (30,buf_menu6[5],2,0,0);		//segundo
						break;
						}
					case 2:
						{
						displayp (8,buf_menu6[0],2,0,0);		//dia
						displayp (11,buf_menu6[1],2,0,0);		//mes
						displayp (14,buf_menu6[2],2,0,'P');		//ano
						displayp (24,buf_menu6[3],2,0,0);		//hora
						displayp (27,buf_menu6[4],2,0,0);		//minuto
						displayp (30,buf_menu6[5],2,0,0);		//segundo
						break;
						}
					case 3:
						{
						displayp (8,buf_menu6[0],2,0,0);		//dia
						displayp (11,buf_menu6[1],2,0,0);		//mês
						displayp (14,buf_menu6[2],2,0,0);		//ano
						displayp (24,buf_menu6[3],2,0,'P');		//hora
						displayp (27,buf_menu6[4],2,0,0);		//minuto
						displayp (30,buf_menu6[5],2,0,0);		//segundo
						break;
						}
					case 4:
						{
						displayp (8,buf_menu6[0],2,0,0);		//dia
						displayp (11,buf_menu6[1],2,0,0);		//mês
						displayp (14,buf_menu6[2],2,0,0);		//ano
						displayp (24,buf_menu6[3],2,0,0);		//hora
						displayp (27,buf_menu6[4],2,0,'P');		//minuto
						displayp (30,buf_menu6[5],2,0,0);		//segundo
						break;
						}
					case 5:
						{
						displayp (8,buf_menu6[0],2,0,0);		//dia
						displayp (11,buf_menu6[1],2,0,0);		//mês
						displayp (14,buf_menu6[2],2,0,0);		//ano
						displayp (24,buf_menu6[3],2,0,0);		//hora
						displayp (27,buf_menu6[4],2,0,0);		//minuto
						displayp (30,buf_menu6[5],2,0,'P');		//segundo
						break;
						}
					}
				}
			else
				{
				displayp (8,buf_menu6[0],2,0,0);		//dia
				displayp (11,buf_menu6[1],2,0,0);		//mês
				displayp (14,buf_menu6[2],2,0,0);		//ano
				displayp (24,buf_menu6[3],2,0,0);		//hora
				displayp (27,buf_menu6[4],2,0,0);		//minuto
				displayp (30,buf_menu6[5],2,0,0);		//segundo
				}
			}
		else
			{
			mensagem (2,50);
			displayp (18,dia,2,0,0);		//dia
			displayp (21,mes,2,0,0);		//mês
			displayp (24,ano,2,0,0);		//ano
			displayp (24,hora,2,0,0);		//hora
			displayp (27,minuto,2,0,0);		//minuto
			displayp (30,segundo,2,0,0);		//segundo
			}
	#else
		binasc(buf_menu6[0]);					
		buf_display[0]=tabela_caracteres[buf_tmp[1]-'0'];
		buf_display[1]=tabela_caracteres[buf_tmp[2]-'0'];
		binasc(buf_menu6[1]);
		if (buf_tmp[1]=='0')
			{
			buf_display[2]=mbarra_esquerda;
			}
		else
			{
			buf_display[2]=(tabela_caracteres[buf_tmp[1]-'0'] | mbarra_esquerda);
			}
		buf_display[3]=tabela_caracteres[buf_tmp[2]-'0'];
		
		binasc(buf_menu6[2]);
		buf_display[4]=tabela_caracteres[M2];
		buf_display[5]=tabela_caracteres[M0];
		buf_display[6]=tabela_caracteres[buf_tmp[1]-'0'];
		buf_display[7]=tabela_caracteres[buf_tmp[2]-'0'];
		
		binasc(buf_menu6[3]);					
		buf_display[8]=tabela_caracteres[buf_tmp[1]-'0'];
		if (ponto_segundo==1)
			{
			buf_display[9]=(tabela_caracteres[buf_tmp[2]-'0'] | 0x80) ;
			}
		else
			{
			buf_display[9]=tabela_caracteres[buf_tmp[2]-'0'] ;
			}
		binasc(buf_menu6[4]);					
		buf_display[10]=tabela_caracteres[buf_tmp[1]-'0'];
		buf_display[11]=tabela_caracteres[buf_tmp[2]-'0'];
		
		if (programando == 1)
			{
			 if (menu_aux==0)
			 	{
			 	if (ponto_segundo == 1)
			 		{
					buf_display[0] = buf_display[0] | 0x80;  /* acende ponto */
					buf_display[1] = buf_display[1] | 0x80;  /* acende ponto */
					}
				else
					{
					buf_display[0] = buf_display[0] & 0x7F;  /* apaga ponto */
					buf_display[1] = buf_display[1] & 0x7F;  /* apaga ponto */
					}
				}
			 else if (menu_aux==1)
			 	{
			 	if (ponto_segundo == 1)
			 		{
					buf_display[2] = buf_display[2] | 0x80;  /* acende ponto */
					buf_display[3] = buf_display[3] | 0x80;  /* acende ponto */
					}
				else
					{
					buf_display[2] = buf_display[2] & 0x7F;  /* apaga ponto */
					buf_display[3] = buf_display[3] & 0x7F;  /* apaga ponto */
					}
				}
			 else if (menu_aux==2)
			 	{
			 	if (ponto_segundo == 1)
			 		{
					buf_display[6] = buf_display[6] | 0x80;  /* acende ponto */
					buf_display[7] = buf_display[7] | 0x80;  /* acende ponto */
					}
				else
					{
					buf_display[6] = buf_display[6] & 0x7F;  /* apaga ponto */
					buf_display[7] = buf_display[7] & 0x7F;  /* apaga ponto */
					}
				}
			 else if (menu_aux==3)
			 	{
			 	if (ponto_segundo == 1)
			 		{
					buf_display[8] = buf_display[8] | 0x80;  /* acende ponto */
					buf_display[9] = buf_display[9] | 0x80;  /* acende ponto */
					}
				else
					{
					buf_display[8] = buf_display[8] & 0x7F;  /* apaga ponto */
					buf_display[9] = buf_display[9] & 0x7F;  /* apaga ponto */
					}
				}
			 else if (menu_aux==4)
			 	{
			 	if (ponto_segundo == 0)
			 		{
					buf_display[10] = buf_display[10] | 0x80;  /* acende ponto */
					buf_display[11] = buf_display[11] | 0x80;  /* acende ponto */
					}
				else
					{
					buf_display[10] = buf_display[10] & 0x7F;  /* apaga ponto */
					buf_display[11] = buf_display[11] & 0x7F;  /* apaga ponto */
					}
			 	}
			buf_display[12] = tempo_senha;  /* apaga leds */
			}
		else
			{
			buf_display[12] = 0;  /* apaga leds */
			}
	#endif
}

void aceita_data(void)
{
	buf_menu6[0] = dia;
	buf_menu6[1] = mes;
	buf_menu6[2] = ano;
	buf_menu6[3] = hora;
	buf_menu6[4] = minuto;
	buf_menu6[5] = segundo;

	if ((buf_menu6[2] % 4) == 0)		//ano
		{
		if (mes == 2)
			{
			if (buf_menu6[0] > 29)		//dia
				{
				buf_menu6[0] = 1;		//dia
				}
			}
		else
			{
			if (buf_menu6[0] > 31)		//dia
				{
				buf_menu6[0] = 1;		//dia
				}
			}
		}
	else
		{
		if (buf_menu6[1] == 2)		//mes
			{
			if (buf_menu6[0] > 28)	//dia
				{
				buf_menu6[0] = 1;	//dia
				}
			}
		else
			{
			if (buf_menu6[0] > 31)	//dia
				{
				buf_menu6[0] = 1;	//dia
				}
			}
		}
	if (buf_menu6[1] > 12)		//mes
		{
		buf_menu6[1] = 1;		//mes
		}
	if (buf_menu6[2] > 99)		//ano
		{
		buf_menu6[2] = 1;		//ano
		}
	if (buf_menu6[3] > 23)		//hora
		{
		buf_menu6[3] = 1;		//hora
		}
	if (buf_menu6[4] > 59)		//minuto
		{
		buf_menu6[4] = 1;		//minuto
		}
	if (buf_menu6[5] > 59)		//segundo
		{
		buf_menu6[5] = 1;		//segundo
		}
}
