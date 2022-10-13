/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_MAIN                                                        *
; Funcao: MODULO PRINCIPAL DE CONTROLE									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */
  
void exibe_tensao_fn(void);
void exibe_tensao_ff(void);
void exibe_tensao_alta(void);
void exibe_corrente(char);
#if (com_consumo == true)
	void exibe_consumo_ati(void);
	void exibe_consumo_reati(void);
	#if (com_consumo_aparente == true)
		void exibe_consumo_aparente(void);
	#endif
#endif
void exibe_dem_ativa(void);
void exibe_dem_reativa(void);
void exibe_pot_requerida(void);
void exibe_pot_excedente(void);
void exibe_dem_media_ativa(void);
void exibe_dem_maxima_ativa(void);
void exibe_dem_media_aparente(void);
void exibe_dem_maxima_aparente(void);
void dsp_ecd(void);
void dsp_flt(void);
void exibe_fator_potencia(void);
void exibe_pot_ativa(char);
void exibe_pot_aparente(void);
void exibe_pot_reativa(void);
void exibe_frequencia(void);
void exibe_time_funciona(void);


void exibe_tensao_fn(void)
{
	#if (disp_7seg == true)
		if (tipo_ligacao == 0)		/* 0 estrela; 1 Delta  ; 2 Delta Aberto*/
			{
			print_display(1,tensao_r,6,1);
			print_display(2,tensao_s,6,1);
			print_display(3,tensao_t,6,1);
			leds(LED_TENSAO);
			}
		else
			{
			exibe_tensao_ff();
			}
	#else
		if (exibiu == 0)
			{
			mensagem(1,53);
			mensagem(2,0);
			exibiu = 1;
			}
		if (time_out2 == 0)
			{
			mensagem (1,51);
			mensagem (2,52);
			time_out2 = DEF_TIME_OUT2;
			}
		else
			{
			print_display(11,tensao_r,3,1,6,'T', 255);	/* exibe tensao R no display1 com 1 casa decimal entrada em q6)*/
			print_display(18,tensao_s,3,1,6,'T', 255);	/* exibe tensao S no display1 com 1 casa decimal entrada em q6)*/
			print_display(27,tensao_t,3,1,6,'T', 255);	/* exibe tensao T no display1 com 1 casa decimal entrada em q6)*/
			}
	#endif
}


void exibe_tensao_ff(void)
{
	#if (disp_7seg == true)
		print_display(1,tensao_rs,6,1);
		print_display(2,tensao_st,6,1);
		print_display(3,tensao_rt,6,1);
		if (piscar == 1)
			{
			leds(LED_TENSAO);
			}
		else
			{
			leds(LED_APAGADO);
			}
	#else
		if (exibiu == 0)
			{
			mensagem (1,53);
			mensagem (2,0);
			exibiu = 1;
			}
		if (time_out2 == 0)
			{
			mensagem (1,51);
			mensagem (2,52);
			time_out2 = DEF_TIME_OUT2;
			}
		else
			{
			print_display(11,tensao_rs,3,1,6,'T', 255);	/* exibe tensao R no display1 com 1 casa decimal entrada em q6)*/
			print_display(18,tensao_st,3,1,6,'T', 255);	/* exibe tensao S no display1 com 1 casa decimal entrada em q6)*/
			print_display(27,tensao_rt,3,1,6,'T', 255);	/* exibe tensao T no display1 com 1 casa decimal entrada em q6)*/
			}
	#endif
}

void exibe_tensao_alta(void)
{
	#if (disp_7seg == true)
		print_display(1,tensao_rs_na_alta,6,1);
		print_display(2,tensao_st_na_alta,6,1);
		print_display(3,tensao_rt_na_alta,6,1);
	//	display(1,(unsigned int)(tensao_rs_na_alta),1,6);	/* exibe tensao R no display1 com 1 casa decimal entrada em q6)*/
	//	display(2,(unsigned int)(tensao_st_na_alta),1,6);	/* exibe tensao R no display1 com 1 casa decimal entrada em q6)*/
	//	display(3,(unsigned int)(tensao_rt_na_alta),1,6);	/* exibe tensao R no display1 com 1 casa decimal entrada em q6)*/
//	    buf_display[0] = tabela_caracteres[MP];
//	    buf_display[4] = tabela_caracteres[MP];
//	    buf_display[8] = tabela_caracteres[MP];
		if (piscar == 1)
			{
			leds(LED_TENSAO);
			}
		else
			{
			leds(LED_APAGADO);
			}
	#else
		if (exibiu == 0)
			{
			mensagem (1,53);
			mensagem (2,0);
			lcd_gotoxy(5,1);
		    wr_lcd(1,'(');
		    wr_lcd(1,'k');
			exibiu = 1;
			}
		if (time_out2 == 0)
			{
			mensagem (1,51);
			mensagem (2,52);
			time_out2 = DEF_TIME_OUT2;
			}
		else
			{
			print_display(10,tensao_rs_na_alta,5,1,6,'T', 255);	/* exibe tensao R no display1 com 1 casa decimal entrada em q6)*/
			print_display(17,tensao_st_na_alta,5,1,6,'T', 255);	/* exibe tensao S no display1 com 1 casa decimal entrada em q6)*/
			print_display(26,tensao_rt_na_alta,5,1,6,'T', 255);	/* exibe tensao T no display1 com 1 casa decimal entrada em q6)*/
			}
	#endif
}



void exibe_corrente(char tipo)
{
	#if (disp_7seg == true)
		print_display(1,corrente_r,3,0);
		print_display(2,corrente_s,3,0);
		print_display(3,corrente_t,3,0);
		leds(LED_CORRENTE);
	#else
		if (exibiu == 0)
			{
			if (tipo == 1)
				{
				mensagem (1,93);
				}
			else
				{
				mensagem (1,54);
				}
			mensagem (2,0);
			exibiu = 1;
			}
		if (time_out2 == 0)
			{
			mensagem (1,51);
			mensagem (2,52);
			time_out2 = DEF_TIME_OUT2;
			}
		else
			{
			if (tipo == 1)
				{
				aux_w1 = cor_maxima_r;
				aux_w2 = cor_maxima_s;
				aux_w3 = cor_maxima_t;
				}
			else
				{
				aux_w1 = corrente_r;
				aux_w2 = corrente_s;
				aux_w3 = corrente_t;
				}
			print_display(10,aux_w1,3,1,3,'C', 255);	/* exibe tensao R no display1 com 1 casa decimal entrada em q6)*/
			print_display(18,aux_w2,3,1,3,'C', 255);	/* exibe tensao S no display1 com 1 casa decimal entrada em q6)*/
			print_display(26,aux_w3,3,1,3,'C', 255);	/* exibe tensao T no display1 com 1 casa decimal entrada em q6)*/
				
			}
	#endif
}
		



#if (com_consumo == true)
	#if (disp_7seg == true)
		void exibe_consumo_ati(void)
		{
			mensagem(m_menu1_7, 1);
			aux_l1 = ajusta_leitura_long(consumo_ati);
			if (aux_l1 < 9999)
				{
				display(3,aux_l1,0,0);
				leds(LED_KWH);
				}
			else 
				{
				if (aux_l1 < 999999)
					{
					display_n(8,(unsigned int)(aux_l1 / 1000),3);
					binasc2((unsigned int)(aux_l1 % 1000));							/* saida em buf_tmp[0 a 4]*/
				    buf_display[11] = tabela_caracteres[buf_tmp[2]-'0'];
					buf_display[10] = buf_display[10] | 0x80;
					}
				else 
					{
					display(3,(aux_l1 / 10000),0,0);
					}
				leds(LED_MWH);
				}
		}
		
		
		void exibe_consumo_reati(void)
		{
			mensagem(m_menu1_8,1);
			aux_l1 = ajusta_leitura_long(consumo_reati);
		
			if (aux_l1 < 9999)
				{
				display(3,aux_l1,0,0);
				leds(LED_KVARH);
				}
			else 
				{
				if (aux_l1 < 999999)
					{
					display_n(8,(unsigned int)(aux_l1 / 1000),3);
					binasc2((unsigned int)(aux_l1 % 1000));							/* saida em buf_tmp[0 a 4]*/
				    buf_display[11] = tabela_caracteres[buf_tmp[2]-'0'];
					buf_display[10] = buf_display[10] | 0x80;
					}
				else 
					{
					display(3,(aux_l1 / 10000),0,0);
					}
				leds(LED_MVARH);
				}
		}
	#else
		void exibe_consumo_ati(void)
		{
			if (exibiu == 0)
				{
				mensagem(1,60);
				mensagem(2,0);
				lcd_gotoxy(12,2);
			    wr_lcd(1,'k');
			    wr_lcd(1,'W');
			    wr_lcd(1,'h');
				}
			aux_l1 = consumo_ati * valor_tp * mul_tc;
			displaypl(19,aux_l1,8);
			}
		void exibe_consumo_reati(void)
		{
			if (exibiu == 0)
				{
				mensagem(1,61);
				mensagem(2,0);
				lcd_gotoxy(11,2);
			    wr_lcd(1,'k');
			    wr_lcd(1,'V');
			    wr_lcd(1,'A');
			    wr_lcd(1,'r');
			    wr_lcd(1,'h');
				}
			aux_l1 = consumo_reati * valor_tp * mul_tc;
			displaypl(18,aux_l1,8);
		}
		#if (com_consumo_aparente == true)
			void exibe_consumo_aparente(void){
				if (exibiu == 0){
					mensagem(1,95);
					mensagem(2,0);
					lcd_gotoxy(12,2);
				    wr_lcd(1,'k');
				    wr_lcd(1,'V');
				    wr_lcd(1,'A');
				    wr_lcd(1,'h');
				}
				aux_l1 = consumo_apa * valor_tp * mul_tc;
				displaypl(19,aux_l1,8);
			}
		#endif
	#endif
#endif


void exibe_dem_ativa(void)
{
	#if (disp_7seg == true)
		if ((hora >= hora_ponta) && (hora < hora_final_ponta))
			{
			mensagem(m_menu1_9_2,1);
			}
		else
			{		
			mensagem(m_menu1_9,1);
			}
		aux_w1 = dem_ativa;
		if (aux_w1 < 9999)
			{
			print_display(3,aux_w1,0,0);
			leds(LED_DEMKW);
			}
		else
			{
			print_display(3,(aux_w1/1000),0,0);
			leds(LED_DEMMW);
			}
	#else
		if (exibiu == 0)
			{
			mensagem(1,62);
			mensagem(2,0);
			}
		if ((hora >= hora_ponta) && (hora < hora_final_ponta))
			{
			if (piscar == 1)
				{
				lcd_gotoxy(1,2);
			    wr_lcd(1,'(');
			    wr_lcd(1,'P');
			    wr_lcd(1,')');
			    }
			else
				{
				lcd_gotoxy(1,2);
			    wr_lcd(1,' ');
			    wr_lcd(1,' ');
			    wr_lcd(1,' ');
				}
			}
		aux_w1 = dem_ativa;
		if (aux_w1 < 9999)
			{
			lcd_gotoxy(13,2);
		    wr_lcd(1,'k');
		    wr_lcd(1,'W');
			print_display(21,aux_w1,4,1,0,'C', 255);
			}
		else
			{
			lcd_gotoxy(13,2);
		    wr_lcd(1,'M');
		    wr_lcd(1,'W');
			print_display(21,(aux_w1 / 1000),4,1,0,'C', 255);
			}
	#endif
}

void exibe_dem_reativa(void)
{
	#if (disp_7seg == true)
		if ((hora >= hora_ponta) && (hora < hora_final_ponta))
			{
			mensagem(m_menu1_10_2,1);
			}
		else
			{		
			mensagem(m_menu1_10,1);
			}
		aux_w1 = dem_reativa;
		if (aux_w1 < 9999)
			{
			print_display(3,aux_w1,0,0);
			leds(LED_DEMKVAR);
			}
		else
			{
			print_display(3,(aux_w1/1000),0,0);
			leds(LED_DEMMVAR);
			}
	#else
		if (exibiu == 0)
			{
			mensagem(1,63);
			mensagem(2,0);
			}
		if ((hora >= hora_ponta) && (hora < hora_final_ponta))
			{
			if (piscar == 1)
				{
				lcd_gotoxy(1,2);
			    wr_lcd(1,'(');
			    wr_lcd(1,'P');
			    wr_lcd(1,')');
				}
			else
				{
				lcd_gotoxy(1,2);
			    wr_lcd(1,' ');
			    wr_lcd(1,' ');
			    wr_lcd(1,' ');
				}
			}
		aux_w1 = dem_reativa;
		if (aux_w1 < 9999)
			{
			lcd_gotoxy(13,2);
		    wr_lcd(1,'k');
		    wr_lcd(1,'V');
		    wr_lcd(1,'A');
		    wr_lcd(1,'r');
			print_display(21,aux_w1,4,1,0,'C', 255);
			}
		else
			{
			lcd_gotoxy(13,2);
		    wr_lcd(1,'M');
		    wr_lcd(1,'V');
		    wr_lcd(1,'A');
		    wr_lcd(1,'r');
			print_display(21,(aux_w1 / 1000),4,1,0,'C', 255);
			}
	#endif
}

void exibe_pot_requerida(void)
{
	#if (disp_7seg == true)
		dsp_flt();
		buf_display[3] = tabela_caracteres[MESPACO];
		buf_display[4] = tabela_caracteres[MESPACO];
		buf_display[6] = tabela_caracteres[MESPACO];
		buf_display[7] = tabela_caracteres[MESPACO];

		if (aux_menu1 == 0)
			{
			buf_display[5] = tabela_caracteres[MR];
			print_display(3,pot_req_r,5,0);
			}
		else if (aux_menu1 == 1)
			{
			buf_display[5] = tabela_caracteres[MS];
			print_display(3,pot_req_s,5,0);
			}
		else if (aux_menu1 == 2)
			{
			buf_display[5] = tabela_caracteres[MT];
			print_display(3,pot_req_t,5,0);
			}
		else
			{
			aux_l1 = pot_req_r;
			aux_l1 += pot_req_s;
			aux_l1 += pot_req_t;
			data1_int = aux_l1 / 32;
			buf_display[4] = tabela_caracteres[MT];
			buf_display[5] = tabela_caracteres[MO];
			buf_display[6] = tabela_caracteres[MT];
			print_display(3,data1_int,0,0);
			}
		if (piscar == 1)
			{
			leds(LED_KVAR);
			}
		else
			{
			leds(LED_APAGADO);
			}

		#define printa_edison false
		#if (printa_edison == true) 
			#if (com_485 == true) 
				output_high(direcao); 
				delay_ms(1); 
			#endif	 
			printf(";Req R=%lu ", pot_req_r); 
			printf(";Req S=%lu ", pot_req_s); 
			printf(";Req T=%lu ", pot_req_t); 
			printf(";Req Total=%u ", aux_l1); 
			printf("\r\n"); 
			#if (com_485 == true) 
			delay_ms(2); 
			output_low(direcao); 
			#endif 
		#endif 


	#else
		if (aux_menu1 == 0)
			{
			if (exibiu == 0)
				{
				#if (com_rep == true)
					if (modo_rep == 1)
						{
	//					mensagem(1,31);
	//					mensagem(2,32);
						}
					else
						{
						mensagem(1,70);
						mensagem(2,0);
						}
				#else
					mensagem(1,70);
					mensagem(2,0);
				#endif
				exibiu = 1;
				}
			#if (com_rep == true)
				if (modo_rep == 1)
					{
					aux_l1 = pot_req_r;
					aux_l1 = aux_l1 + pot_req_s + pot_req_t;
					print_display(11,aux_l1,4,1,5,'C', 255);
					aux_l1 = pot_exec_r;
					aux_l1 = aux_l1 + pot_exec_s + pot_exec_t;
					print_display(27,aux_l1,4,1,5,'C', 255);
					return;
					}
			#endif
			if (time_out2 == 0)
				{
				mensagem (1,51);
				mensagem (2,52);
				time_out2 = DEF_TIME_OUT2;
				}
			else
				{
				print_display(11,pot_req_r,4,1,5,'C', 255);
				print_display(18,pot_req_s,4,1,5,'C', 255);
				print_display(27,pot_req_t,4,1,5,'C', 255);
				}
			}
		else
			{
			if (exibiu == 0)
				{
				mensagem(1,87);
				mensagem(2,0);
				}
			aux_l1 = pot_req_r;
			aux_l1 += pot_req_s;
			aux_l1 += pot_req_t;

			lcd_gotoxy(6,1);
			if (aux_l1 < 9999){
			    wr_lcd(1,'k');
				data1_int = aux_l1;
			}
			else{
			    wr_lcd(1,'M');
				data1_int = aux_l1 / 1000;
			}

			print_display(23,data1_int,6,1,5,'C', 255);
			}
	#endif
}

void exibe_pot_excedente(void)
{
	#if (disp_7seg == true)
		dsp_ecd();
		buf_display[3] = tabela_caracteres[MESPACO];
		buf_display[4] = tabela_caracteres[MESPACO];
		buf_display[6] = tabela_caracteres[MESPACO];
		buf_display[7] = tabela_caracteres[MESPACO];

		if (aux_menu1 == 0)
			{
			buf_display[5] = tabela_caracteres[MR];
			print_display(3,pot_exec_r,5,0);
			}
		else if (aux_menu1 == 1)
			{
			buf_display[5] = tabela_caracteres[MS];
			print_display(3,pot_exec_s,5,0);
			}
		else if (aux_menu1 == 2)
			{
			buf_display[5] = tabela_caracteres[MT];
			print_display(3,pot_exec_t,5,0);
			}
		else
			{
			aux_l1 = pot_exec_r;
			aux_l1 += pot_exec_s;
			aux_l1 += pot_exec_t;
			data1_int = aux_l1 / 32;
			buf_display[4] = tabela_caracteres[MT];
			buf_display[5] = tabela_caracteres[MO];
			buf_display[6] = tabela_caracteres[MT];
			print_display(3,data1_int,0,0);
			}
		if (piscar == 1)
			{
			leds(LED_KVAR);
			}
		else
			{
			leds(LED_APAGADO);
			}
	#else
		if (aux_menu1 == 0)
			{
			if (exibiu == 0)
				{
				#if (com_rep == true)
					if (modo_rep == 1)
						{
	//					mensagem (1,147);
	//					mensagem (2,148);
						}
					else
						{
						mensagem (1,71);
						mensagem (2,0);
						}
				#else
					mensagem (1,71);
					mensagem (2,0);
				#endif
				exibiu = 1;
				}
			#if (com_rep == true)
				if (modo_rep == 1)
					{
					displayp(12, ultimo_pulso_at,5,0,0);
					displayp(28, ultimo_pulso_reat,5,0,0);
					return;
					}
			#endif
			if (time_out2 == 0)
				{
				mensagem (1,51);
				mensagem (2,52);
				time_out2 = DEF_TIME_OUT2;
				}
			else
				{
				print_display(11,pot_exec_r,4,1,5,'C', 255);
				print_display(18,pot_exec_s,4,1,5,'C', 255);
				print_display(27,pot_exec_t,4,1,5,'C', 255);
				}
			}
		else
			{
			if (exibiu == 0)
				{
				mensagem(1,88);
				mensagem(2,0);
				}
			aux_l1 = pot_exec_r;
			aux_l1 += pot_exec_s;
			aux_l1 += pot_exec_t;
			data1_int = aux_l1;

			lcd_gotoxy(6,1);
			if (aux_l1 < 9999){
			    wr_lcd(1,'k');
				data1_int = aux_l1;
			}
			else{
			    wr_lcd(1,'M');
				data1_int = aux_l1 / 1000;
			}

			print_display(23,data1_int,6,1,5,'C', 255);
			}
			
	#endif
}


void exibe_dem_media_ativa(void)
{
	#if (disp_7seg == true)
		mensagem(m_menu1_12,1);
		aux_w1 = dem_media_ativa;
		if (aux_w1 < 9999)
			{
			print_display(3,aux_w1,0,0);
			leds(LED_DEMKW);
			}
		else
			{
			print_display(3,(aux_w1 / 1000),0,0);
			leds(LED_DEMMW);
			}
	#else
		if (exibiu == 0)
			{
			mensagem(1,65);
			mensagem(2,0);
			}
		aux_w1 = dem_media_ativa;
		if (aux_w1 < 9999)
			{
			lcd_gotoxy(13,2);
		    wr_lcd(1,'k');
		    wr_lcd(1,'W');
			print_display(21,aux_w1,4,1,0,'C', 255);
			}
		else
			{
			lcd_gotoxy(13,2);
		    wr_lcd(1,'M');
		    wr_lcd(1,'W');
			print_display(21,(aux_w1 / 1000),4,1,0,'C', 255);
			}
	#endif
}

void exibe_dem_maxima_ativa(void)
{
	#if (disp_7seg == true)
		mensagem(m_menu1_13,1);
		aux_w1 = dem_maxima_ativa;
		if (aux_w1 < 9999)
			{
			print_display(3,aux_w1,0,0);
			leds(LED_DEMKW);
			}
		else
			{
			print_display(3,(aux_w1 / 1000),0,0);
			leds(LED_DEMMW);
			}
	#else
		if (exibiu == 0)
			{
			mensagem(1,66);
			mensagem(2,0);
			}
		aux_w1 = dem_maxima_ativa;
		if (aux_w1 < 9999)
			{
			lcd_gotoxy(13,2);
		    wr_lcd(1,'k');
		    wr_lcd(1,'W');
			print_display(21,aux_w1,4,1,0,'C', 255);
			}
		else
			{
			lcd_gotoxy(13,2);
		    wr_lcd(1,'M');
		    wr_lcd(1,'W');
			print_display(21,(aux_w1 / 1000),4,1,0,'C', 255);
			}
	#endif
}

void exibe_dem_media_aparente(void)
{
	#if (disp_7seg == true)
		mensagem(m_menu1_14,1);
		aux_w1 = dem_media_aparente;
		if (aux_w1 < 9999)
			{
			print_display(3,aux_w1,0,0);
			leds(LED_DEMKVA);
			}
		else
			{
			print_display(3,(aux_w1 / 1000),0,0);
			leds(LED_DEMMVA);
			}
	#else
		if (exibiu == 0)
			{
			mensagem(1,67);
			mensagem(2,0);
			}
		aux_w1 = dem_media_aparente;
		if (aux_w1 < 9999)
			{
			lcd_gotoxy(13,2);
		    wr_lcd(1,'k');
		    wr_lcd(1,'V');
		    wr_lcd(1,'A');
			print_display(21,aux_w1,4,1,0,'C', 255);
			}
		else
			{
			lcd_gotoxy(13,2);
		    wr_lcd(1,'M');
		    wr_lcd(1,'V');
		    wr_lcd(1,'A');
			print_display(21,(aux_w1 / 1000),4,1,0,'C', 255);
			}
	#endif
}

void exibe_dem_maxima_aparente(void)
{
	#if (disp_7seg == true)
		mensagem(m_menu1_15,1);
		aux_w1 = dem_maxima_aparente;
		if (aux_w1 < 9999)
			{
			print_display(3,aux_w1,0,0);
			leds(LED_DEMKVA);
			}
		else
			{
			print_display(3,(aux_w1 / 1000),0,0);
			leds(LED_DEMMVA);
			}
	#else
		if (exibiu == 0)
			{
			mensagem(1,68);
			mensagem(2,0);
			}
		aux_w1 = dem_maxima_aparente;
		if (aux_w1 < 9999)
			{
			lcd_gotoxy(13,2);
		    wr_lcd(1,'k');
		    wr_lcd(1,'V');
		    wr_lcd(1,'A');
			print_display(21,aux_w1,4,1,0,'C', 255);
			}
		else
			{
			lcd_gotoxy(13,2);
		    wr_lcd(1,'M');
		    wr_lcd(1,'V');
		    wr_lcd(1,'A');
			print_display(21,(aux_w1 / 1000),4,1,0,'C', 255);
			}
	#endif
}


void dsp_ecd(void)
{
	#if (disp_7seg == true)
		buf_display[0]=tabela_caracteres[ME];
		buf_display[1]=tabela_caracteres[MC];
		buf_display[2]=tabela_caracteres[MD];
	#else
		if (exibiu == 0)
			{
			mensagem(1,71);
			mensagem(2,0);
			}
		if (time_out2 == 0)
			{
			mensagem (1,51);
			mensagem (2,52);
			time_out2 = DEF_TIME_OUT2;
			}
		else
			{
			print_display(11,pot_exec_r,4,1,5,'C', 255);
			print_display(18,pot_exec_s,4,1,5,'C', 255);
			print_display(27,pot_exec_t,4,1,5,'C', 255);
			}
	#endif
}

void dsp_flt(void)
{
	#if (disp_7seg == true)
		buf_display[0]=tabela_caracteres[MF];
		buf_display[1]=tabela_caracteres[ML];
		buf_display[2]=tabela_caracteres[MT];
	#else
		if (exibiu == 0)
			{
			mensagem(1,70);
			mensagem(2,0);
			}
		if (time_out2 == 0)
			{
			mensagem (1,51);
			mensagem (2,52);
			time_out2 = DEF_TIME_OUT2;
			}
		else
			{
			print_display(11,pot_req_r,4,1,5,'C', 255);
			print_display(18,pot_req_s,4,1,5,'C', 255);
			print_display(27,pot_req_t,4,1,5,'C', 255);
			}
	#endif
}

void exibe_fator_potencia(void)
{
	#if (disp_7seg == true)
		if(aux_menu1 == 0)
			{
			displayfp(1,fator_pot_r);
			displayfp(2,fator_pot_s);
			displayfp(3,fator_pot_t);
			}
		else
			{
			buf_display[0]=tabela_caracteres[MF];
			buf_display[1]=tabela_caracteres[MP];
			buf_display[2]=tabela_caracteres[MESPACO];
			buf_display[3]=tabela_caracteres[MESPACO];
			buf_display[4]=tabela_caracteres[MT];
			buf_display[5]=tabela_caracteres[MO];
			buf_display[6]=tabela_caracteres[MT];
			buf_display[7]=tabela_caracteres[MESPACO];
			displayfp(3,fator_pot);
			}
		leds(LED_FP);
	#else
		if(aux_menu1 == 0)
			{
			if (exibiu == 0)
				{
				mensagem (1,55);
				mensagem (2,0);
				mensagem (2,56);
				exibiu = 1;
				}
			displayfp(11,fator_pot_r);
			displayfp(19,fator_pot_s);
			displayfp(27,fator_pot_t);
			}
		else
			{
			if (exibiu == 0)
				{
				mensagem(1,89);
				mensagem(2,0);
				exibiu = 1;
				}
			displayfp(22,fator_pot);
			}
	#endif
}

void exibe_pot_ativa(char tipo)
{
	#if (disp_7seg == true)
		if (aux_menu1 == 0)
			{
			if (valor_tp != 1)
				{
				aux_l1 = pot_ativa_r;
				aux_l1 = aux_l1 * valor_tp;
				data1_int = aux_l1 / 32;
				print_display(1,data1_int,0,0);
				
				aux_l1 = pot_ativa_s;
				aux_l1 = aux_l1 * valor_tp;
				data1_int = aux_l1 / 32;
				print_display(2,data1_int,0,0);

				aux_l1 = pot_ativa_t;
				aux_l1 = aux_l1 * valor_tp;
				data1_int = aux_l1 / 32;
				print_display(3,data1_int,0,0);
			 	}
			else
			 	{
				print_display(1,pot_ativa_r,5,0);
				print_display(2,pot_ativa_s,5,0);
				print_display(3,pot_ativa_t,5,0);
				}
			leds(LED_KW);
			}
		else
			{
			buf_display[0]=tabela_caracteres[MP];
			buf_display[1]=tabela_caracteres[MO];
			buf_display[2]=tabela_caracteres[MT];
			buf_display[3]=tabela_caracteres[MESPACO];
			buf_display[4]=tabela_caracteres[MT];
			buf_display[5]=tabela_caracteres[MO];
			buf_display[6]=tabela_caracteres[MT];
			buf_display[7]=tabela_caracteres[MESPACO];

			aux_l1 = pot_ativa_r;
			aux_l1 += pot_ativa_s;
			aux_l1 += pot_ativa_t;

			if (valor_tp != 1)
				{
				aux_l1 = aux_l1 * valor_tp;
				data1_int = aux_l1 / 32;
				if (data1_int > 9999)
					{
					data1_int = data1_int / 1000;
					leds(LED_MW);
					}
				else
					{
					leds(LED_KW);
					}
				print_display(3,data1_int,0,0);
				}
			else
				{
				data1_int = aux_l1 / 32;
				print_display(3,data1_int,0,0);
				leds(LED_KW);
				}
			}
	#else
		if (tipo == 1){
			aux_w1 = pot_ativa_max_r;
			aux_w2 = pot_ativa_max_s;
			aux_w3 = pot_ativa_max_t;
		}
		else{
			aux_w1 = pot_ativa_r;
			aux_w2 = pot_ativa_s;
			aux_w3 = pot_ativa_t;
		}
		if (aux_menu1 == 0){
			if (exibiu == 0){
				if (tipo == 1){
					mensagem(1,94);
				}
				else{
					mensagem(1,57);
				}
				mensagem(2,0);
				exibiu = 1;
			}

			if (time_out2 == 0){
				mensagem (1,51);
				mensagem (2,52);
				time_out2 = DEF_TIME_OUT2;
			}
			else{
				if (valor_tp != 1){
					aux_l1 = aux_w1;
					aux_l1 = aux_l1 * valor_tp;
					data1_int = aux_l1 / 32;
					print_display(10,data1_int,6,1,0,'C', 255);
								
					aux_l1 = aux_w2;
					aux_l1 = aux_l1 * valor_tp;
					data1_int = aux_l1 / 32;
					print_display(18,data1_int,6,1,0,'C', 255);
			
					aux_l1 = aux_w3;
					aux_l1 = aux_l1 * valor_tp;
					data1_int = aux_l1 / 32;
					print_display(26,data1_int,6,1,0,'C', 255);
				 }
				 else{
					if (sentido_r == 1){
						lcd_gotoxy(9,1);
					    wr_lcd(1,'-');
						print_display(10,aux_w1,4,1,5,'C', 255);
					}
					else{
						print_display(10,aux_w1,4,1,5,'C', 255);
					    wr_lcd(1,' ');
					}
					if (sentido_s == 1){
						lcd_gotoxy(1,2);
					    wr_lcd(1,'-');
						print_display(18,aux_w2,4,1,5,'C', 255);
					}
					else{
						print_display(18,aux_w2,4,1,5,'C', 255);
					    wr_lcd(1,' ');
					}
					if (sentido_s == 1){
						lcd_gotoxy(9,2);
					    wr_lcd(1,'-');
						print_display(26,aux_w3,4,1,5,'C', 255);
					}
					else{
						print_display(26,aux_w3,4,1,5,'C', 255);
					    wr_lcd(1,' ');
					}
				}
			}
		}
		else{
			if (exibiu == 0){
				mensagem(1,84);
				mensagem(2,0);
				exibiu = 1;
			}
			aux_l1 = aux_w1;
			aux_l1 += aux_w2;
			aux_l1 += aux_w3;

			#if (teste_edison == true)
				output_high(direcao);
				delay_ms(1);
				fprintf(modbus,"Apagou Setor!");
				fprintf(modbus,"\r\n");
				delay_ms(2);
				output_low(direcao);
			#endif

			if (valor_tp != 1){
				aux_l1 = aux_l1 * valor_tp;
				data1_int = aux_l1 / 32;
				print_display(23,data1_int,6,1,0,'C', 255);
			}
			else{
				data1_int = aux_l1;
				print_display(23,data1_int,6,1,5,'C', 255);
			}
		}
	#endif
}

void exibe_pot_aparente(void)
{
	#if (disp_7seg == true)
		if(aux_menu1 == 0)
			{
			if (valor_tp != 1)
				{
				aux_l1 = pot_aparente_r;
				aux_l1 = aux_l1 * valor_tp;
				data1_int = aux_l1 / 32;
				print_display(1,data1_int,0,0);
				
				aux_l1 = pot_aparente_s;
				aux_l1 = aux_l1 * valor_tp;
				data1_int = aux_l1 / 32;
				print_display(2,data1_int,0,0);

				aux_l1 = pot_aparente_t;
				aux_l1 = aux_l1 * valor_tp;
				data1_int = aux_l1 / 32;
				print_display(3,data1_int,0,0);
				}
			else
				{
				print_display(1,pot_aparente_r,5,0);
				print_display(2,pot_aparente_s,5,0);
				print_display(3,pot_aparente_t,5,0);
				}
			leds(LED_KVA);
			}
		else
			{
			buf_display[0]=tabela_caracteres[MP];
			buf_display[1]=tabela_caracteres[MO];
			buf_display[2]=tabela_caracteres[MT];
			buf_display[3]=tabela_caracteres[MESPACO];
			buf_display[4]=tabela_caracteres[MT];
			buf_display[5]=tabela_caracteres[MO];
			buf_display[6]=tabela_caracteres[MT];
			buf_display[7]=tabela_caracteres[MESPACO];

			aux_l1 = pot_aparente_r;
			aux_l1 += pot_aparente_s;
			aux_l1 += pot_aparente_t;

			if (valor_tp != 1)
				{
				aux_l1 = aux_l1 * valor_tp;
				data1_int = aux_l1 / 32;
				if (data1_int > 9999)
					{
					data1_int = data1_int / 1000;
					leds(LED_MVA);
					}
				else
					{
					leds(LED_KVA);
					}
				print_display(3,data1_int,0,0);
				}
			else
				{
				data1_int = aux_l1 / 32;
				print_display(3,data1_int,0,0);
				leds(LED_KVA);
				}
			}
	#else
		if (aux_menu1 == 0)
			{
			if (exibiu == 0)
				{
				mensagem(1,58);
				mensagem(2,0);
				exibiu = 1;
				}
			if (time_out2 == 0)
				{
				mensagem (1,51);
				mensagem (2,52);
				time_out2 = DEF_TIME_OUT2;
				}
			else
				{
				if (valor_tp != 1)
					{
					aux_l1 = pot_aparente_r;
					aux_l1 = aux_l1 * valor_tp;
					data1_int = aux_l1 / 32;
					print_display(10,data1_int,6,1,0,'C', 255);
								
					aux_l1 = pot_aparente_s;
					aux_l1 = aux_l1 * valor_tp;
					data1_int = aux_l1 / 32;
					print_display(18,data1_int,6,1,0,'C', 255);
			
					aux_l1 = pot_aparente_t;
					aux_l1 = aux_l1 * valor_tp;
					data1_int = aux_l1 / 32;
					print_display(26,data1_int,6,1,0,'C', 255);
				 	}
				 else
				 	{
					print_display(10,pot_aparente_r,4,1,5,'C', 255);
					print_display(18,pot_aparente_s,4,1,5,'C', 255);
					print_display(26,pot_aparente_t,4,1,5,'C', 255);
					}
				}
			}
		else
			{
			if (exibiu == 0)
				{
				mensagem(1,85);
				mensagem(2,0);
				exibiu = 1;
				}
			aux_l1 = pot_aparente_r;
			aux_l1 += pot_aparente_s;
			aux_l1 += pot_aparente_t;
			if (valor_tp != 1)
				{
				aux_l1 = aux_l1 * valor_tp;
				data1_int = aux_l1 / 32;
				print_display(23,data1_int,6,1,0,'C', 255);
			 	}
			 else
			 	{
				data1_int = aux_l1;
				print_display(23,data1_int,6,1,5,'C', 255);
				}
			}
	#endif
}

void exibe_pot_reativa(void)
{
	#if (disp_7seg == true)
		if (aux_menu1 == 0)
			{
			if (valor_tp != 1)
				{
				aux_l1 = pot_reativa_r;
				aux_l1 = aux_l1 * valor_tp;
				data1_int = aux_l1 / 32;
				print_display(1,data1_int,0,0);
				
				aux_l1 = pot_reativa_s;
				aux_l1 = aux_l1 * valor_tp;
				data1_int = aux_l1 / 32;
				print_display(2,data1_int,0,0);

				aux_l1 = pot_reativa_t;
				aux_l1 = aux_l1 * valor_tp;
				data1_int = aux_l1 / 32;
				print_display(3,data1_int,0,0);
				}
			else
				{
				print_display(1,pot_reativa_r,5,0);
				print_display(2,pot_reativa_s,5,0);
				print_display(3,pot_reativa_t,5,0);
				}
			leds(LED_KVAR);
			}
		else
			{
			buf_display[0]=tabela_caracteres[MP];
			buf_display[1]=tabela_caracteres[MO];
			buf_display[2]=tabela_caracteres[MT];
			buf_display[3]=tabela_caracteres[MESPACO];
			buf_display[4]=tabela_caracteres[MT];
			buf_display[5]=tabela_caracteres[MO];
			buf_display[6]=tabela_caracteres[MT];
			buf_display[7]=tabela_caracteres[MESPACO];

			aux_l1 = pot_reativa_r;
			aux_l1 += pot_reativa_s;
			aux_l1 += pot_reativa_t;

			if (valor_tp != 1)
				{
				aux_l1 = aux_l1 * valor_tp;
				data1_int = aux_l1 / 32;
				if (data1_int > 9999)
					{
					data1_int = data1_int / 1000;
					leds(LED_MVAR);
					}
				else
					{
					leds(LED_KVAR);
					}
				print_display(3,data1_int,0,0);
				}
			else
				{
				data1_int = aux_l1 / 32;
				print_display(3,data1_int,0,0);
				leds(LED_KVAR);
				}
			}
	#else
		if (aux_menu1 == 0)
			{
			if (exibiu == 0)
				{
				mensagem(1,59);
				mensagem(2,0);
				exibiu = 1;
				}
			if (time_out2 == 0)
				{
				mensagem (1,51);
				mensagem (2,52);
				time_out2 = DEF_TIME_OUT2;
				}
			else
				{
				if (valor_tp != 1)
					{
					aux_l1 = pot_reativa_r;
					aux_l1 = aux_l1 * valor_tp;
					data1_int = aux_l1 / 32;
					print_display(10,data1_int,6,1,0,'C', 255);
			
					aux_l1 = pot_reativa_s;
					aux_l1 = aux_l1 * valor_tp;
					data1_int = aux_l1 / 32;
					print_display(18,data1_int,6,1,0,'C', 255);
			
					aux_l1 = pot_reativa_t;
					aux_l1 = aux_l1 * valor_tp;
					data1_int = aux_l1 / 32;
					print_display(26,data1_int,6,1,0,'C', 255);
					}
				else
					{
					print_display(10,pot_reativa_r,4,1,5,'C', 255);
					print_display(18,pot_reativa_s,4,1,5,'C', 255);
					print_display(26,pot_reativa_t,4,1,5,'C', 255);
					}
				}
			}
		else
			{
			if (exibiu == 0)
				{
				mensagem(1,86);
				mensagem(2,0);
				exibiu = 1;
				}
			aux_l1 = pot_reativa_r;
			aux_l1 += pot_reativa_s;
			aux_l1 += pot_reativa_t;
			if (valor_tp != 1)
				{
				aux_l1 = aux_l1 * valor_tp;
				data1_int = aux_l1 / 32;
				print_display(23,data1_int,6,1,0,'C', 255);
			 	}
			 else
			 	{
				data1_int = aux_l1;
				print_display(23,data1_int,6,1,5,'C', 255);
				}
			}
	#endif
}
void exibe_frequencia(void)
{
	#if (st92 == true)
		if (exibiu == 0)
			{
			exibiu = 1;
			mensagem(1,69);
			mensagem(2,74);
			}
		print_display(22, frequencia, 2, 1, 2, 'F' , 4);
	#else
		mensagem(m_menu1_16,1);
		leds(LED_HZ);
		display(3,frequencia,1,2);
	#endif
}


#if (com_time_funciona == true)
	void exibe_time_funciona(void)
	{
		#if (disp_7seg == true)
			if (aux_menu1 == 0)
				{
				mensagem(47,1);
				aux_l1 = read_long(ee_horas_funcionamento);
				}
			else
				{
				mensagem(48,1);
				aux_l1 = read_long(ee_horas_funcionamento_ant);
				}
			if (aux_l1 > 9999)
				{
				aux_l1 = ((aux_l1 / 24) * 10);
				display(3,aux_l1,0,0);
				buf_display[8] = tabela_caracteres[MD];
				}
			else
				{
				display(3,aux_l1,0,0);
				}
				
		#else
			if (aux_menu1 == 0)
				{
				if (exibiu == 0)
					{
					mensagem(1,90);
					mensagem(2,91);
					exibiu = 1;
					}
				aux_l1 = read_long(ee_horas_funcionamento);
				}
			else
				{
				if (exibiu == 0)
					{
					mensagem(1,90);
					mensagem(2,92);
					exibiu = 1;
					}
				aux_l1 = read_long(ee_horas_funcionamento_ant);
				}
			displaypl(23,aux_l1,8);
				
		#endif
		
	}
#endif


