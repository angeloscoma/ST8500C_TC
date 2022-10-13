/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ROTINAS                               	                     *
; Funcao: MODULO DE ROTINAS DE COMUNICACAO								 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 01/08/2003                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/

#define printa_autoset	true

void monta_tabela_bancos(char);
void ligar_banco(char);


void auto_set(void)
{

	#if (disp_lcd == true)
		val_pwm = 512;
		set_pwm1_duty(val_pwm);	
	#endif

	
	switch(passo_autoset)
		{
		case 0:
			{
			#if (disp_lcd == true)
				lcd_gotoxy(1,1);
							  //1234567890123456
				printf(display,"Desliga bancos  ");
				delay_ms(500);
			#else
				#ERROR falta esta tela
			#endif

			
			for (aux_b1 = 0; aux_b1 < NRO_MAXIMO_BANCOS_CAPACITOR; aux_b1++)
				{
				if (banco_acionado[aux_b1] == 1)
					{
					desligar_banco(aux_b1);
					#if (disp_lcd == true)
						 trata_saidas();
					#endif
					delay_ms(500);
					}
				}

			nro_bancos_capacitor = NRO_MAXIMO_BANCOS_CAPACITOR;
			valor_tc = 500;
			max_kvar = 0;
			min_kvar = 0;
			tempo_aciona = 30;
			tempo_desaciona = 5;
			sequencia = 0;
			monta_tabela_bancos(sequencia);
			salva_programa();
			passo_autoset++;
			time_out_teste_autoset = 5;
			aux_teste = 0;
			aux_banco = 0;
			nro_bancos_capacitor = 0;
			soma_media_reativa_r = 0;
			tentativas_autoset = 0;
			pot_reativa_ind_r = 0;
			pot_reativa_cap_r = 0;
			
			break;
			}
		case 1:
			{
			#if (disp_lcd == true)
				lcd_gotoxy(1,1);
				aux_f1 = pot_reativa_r;
				printf(display,"%4.1f ", aux_f1/32);
				aux_f1 = valor_capacitor;
				printf(display,"B=%3.1f", aux_f1/2);
		
				lcd_gotoxy(1,2);
				printf(display,"%u-", aux_teste);
				printf(display,"%u-", (aux_banco+1));
				printf(display,"%u-", (tentativas_autoset+1));

			#else
				#ERROR falta esta tela
			#endif

				
			if (time_out_teste_autoset == 0)
				{
				time_out_autoset = 60;					
				
				
				if (aux_teste == 0)
					{
					time_out_teste_autoset = 8;
					
					pot_reativa_r_old = pot_reativa_r;
					
					aux_teste = 1;
					aux_tempo_repouso[aux_banco] = 0;
					banco_disponivel[aux_banco] = true;
					if (fator_pot_r < 1)
						{
						pot_reativa_ind_r = pot_reativa_r;
						}
					else
						{
						pot_reativa_cap_r = pot_reativa_r;
						}
						
					ligar_banco(aux_banco);
					}
				else if (aux_teste == 1)
					{
						

					if (fator_pot_r < 1)
						{
						pot_reativa_ind_r = pot_reativa_r;
						}
					else
						{
						pot_reativa_cap_r = pot_reativa_r;
						}
					aux_w1 = pot_reativa_cap_r + pot_reativa_ind_r;
						
					if (aux_w1 > pot_reativa_r_old)
						{
						valor_capacitor = ((aux_w1 - pot_reativa_r_old))/ 16;
						}
					else
						{
						valor_capacitor = ((pot_reativa_r_old - aux_w1))/ 16;
						}
					if (valor_capacitor == 0)
						{
						tentativas_autoset += 2;
						}
					soma_media_reativa_r += valor_capacitor;
					tentativas_autoset++;
					if (tentativas_autoset >= 4)
						{
						valor_capacitor = (soma_media_reativa_r / 4);
						if (valor_capacitor > 250)
							{
							valor_capacitor = 250;
							}
						banco_capacitor[aux_banco] = (char)(valor_capacitor);
						aux_w2 = aux_banco;
						aux_w2 += ee_banco_capacitor_1;
						write_byte(aux_w2, valor_capacitor);
						nro_bancos_capacitor++;
						write_byte(ee_nro_bancos_capacitor, nro_bancos_capacitor);
						if (max_kvar < (valor_capacitor* 2))
							{
							if (valor_capacitor < 125)	
								{
								max_kvar = (valor_capacitor * 2);
								}
							else
								{
								max_kvar = 0;
								}
							write_byte(ee_max_kvar, max_kvar);
							}
						#if (printa_autoset == true)
			         		fprintf(modbus,"aux_banco:%d, ", aux_banco);
			         		fprintf(modbus,"valor_capacitor:%ld ", valor_capacitor);
 		 	        		fprintf(modbus,"max_kvar:%d ",max_kvar);
 		    	     		fprintf(modbus,"Nro bancos:%d \r\n", nro_bancos_capacitor);
 		    	     	#endif
						soma_media_reativa_r = 0;
						aux_teste = 2;
						tentativas_autoset = 0;
						time_out_teste_autoset = 5;
						desligar_banco(aux_banco);
						
						pot_reativa_ind_r = 0;
						pot_reativa_cap_r = 0;
						
						aux_banco++;
						}
					else
						{
						aux_teste = 0;
						desligar_banco(aux_banco);
						time_out_teste_autoset = 5;
						}
					}
				 else
				 	{
					aux_teste = 0;
					pot_reativa_r_old = pot_reativa_r;
					time_out_teste_autoset = 5;
					}
				if (aux_banco >= NRO_MAXIMO_BANCOS_CAPACITOR)
					{
					for (aux_b1 = (NRO_MAXIMO_BANCOS_CAPACITOR -1); aux_b1 > 0; aux_b1--)
						{
						if (banco_capacitor[aux_b1] == 0)
							{
							nro_bancos_capacitor--;
							write_byte(ee_nro_bancos_capacitor, nro_bancos_capacitor);
							}
						else
							{
							break;
							}
						}
					passo_autoset = 99;
					}

				#if (printa_autoset == true)
		        	fprintf(modbus,"+Kvar:%lu, -Kvar:%lu, Kvar:%lu, Old:%lu\r\n ",pot_reativa_cap_r, pot_reativa_ind_r, pot_reativa_r, pot_reativa_r_old);
				#endif
					
				}
			break;
			}
		case 99:
			{
			em_autoset = false;
			for (aux_b1 = 0; aux_b1 < NRO_MAXIMO_BANCOS_CAPACITOR; aux_b1++)
				{
				desligar_banco(aux_b1);
				}
			#if (disp_lcd == true)
				 trata_saidas();
			#endif
			salva_programa();

			#if (printa_autoset == true)
        		fprintf(modbus,"\r\n ********************************************************\r\n");
         		fprintf(modbus,"Resumo do Auto Set:\r\n");
   	     		fprintf(modbus,"Nro bancos:%d \r\n", nro_bancos_capacitor);
        		fprintf(modbus,"Max_kvar(Q1):%d\r\n ",max_kvar);
         		fprintf(modbus,"Capacitores:", valor_capacitor);
				for (aux_b1 = 0; aux_b1 < nro_bancos_capacitor; aux_b1++)
					{
	         		fprintf(modbus,"%d:%d, ", (aux_b1+1), banco_capacitor[aux_b1]);
					}
        		fprintf(modbus,"\r\n");
        		fprintf(modbus,"********************************************************\r\n");
   	     	#endif
			
			fim_menu1();
			break;
			}
			
		default:
			{
			}
		}

	#if (disp_lcd == true)
		 trata_saidas();
	#endif
		
}
