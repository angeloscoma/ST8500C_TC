/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: EXMD                                                           *
; Funcao: MODULO EXIBIÇÃO DE VALORES DA LINHA ST8XXXc					 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */


void exibe_tensao_fn(void)
{
	#if (ST8100C == true)
		if (ja_rolou == true)
			{
			print_display(1,tensao_r,6,1);
			rolando = false;
			}
		else
			{
			mensagem_rola(34, 1);
			}
		led_v = 1;
		led_a = 0;
		led_r = 0;
		led_w = 0;
	#else
		if (exibiu == 0)
			{
			mensagem (1,23);
			mensagem (2,0);
			exibiu = 1;
			}
		#if (monofasico == true)
			print_display(21,tensao_r,3,2,6,'T', 5);	/* exibe tensao RS no display1 com 1 casa decimal entrada em q6)*/
			lcd_gotoxy(12,2);
		    wr_lcd(1,'V');
		    wr_lcd(1,'a');
		    wr_lcd(1,'c');
		#else
			if (time_out2 == 0)
				{
				mensagem (1,138);
				mensagem (2,139);
				time_out2 = 10;
				}
			else
				{
				print_display(11,tensao_r,3,1,6,'T', 255);	/* exibe tensao R no display1 com 1 casa decimal entrada em q6)*/
				print_display(18,tensao_s,3,1,6,'T', 255);	/* exibe tensao S no display1 com 1 casa decimal entrada em q6)*/
				print_display(27,tensao_t,3,1,6,'T', 255);	/* exibe tensao T no display1 com 1 casa decimal entrada em q6)*/
				}
		#endif
	#endif
	
}


void exibe_tensao_ff(void)
{
	#if (ST8100C == true)
		if (ja_rolou == true)
			{
			#if (monofasico == true)
				print_display(1,tensao_r,6,1);
				rolando = false;
			#else
				print_display(1,tensao_rs,6,1);
				rolando = false;
			#endif
			}
		else
			{
			mensagem_rola(35, 1);
			}
		if (piscar == 1)
			{
			led_v = 1;
			}
		else
			{
			led_v = 0;
			}
		led_a = 0;
		led_r = 0;
		led_w = 0;
	#else
		if (exibiu == 0)
			{
			mensagem (1,23);
			mensagem (2,0);
			exibiu = 1;
			}
		#if (monofasico == true)
			print_display(21,tensao_r,3,2,6,'T',5);	/* exibe tensao RS no display1 com 1 casa decimal entrada em q6)*/
			lcd_gotoxy(12,2);
		    wr_lcd(1,'V');
		    wr_lcd(1,'a');
		    wr_lcd(1,'c');
		#else
			if (time_out2 == 0)
				{
				mensagem (1,138);
				mensagem (2,139);
				time_out2 = 10;
				}
			else
				{
				print_display(11,tensao_rs,3,1,6,'T',255);	/* exibe tensao RS no display1 com 1 casa decimal entrada em q6)*/
				print_display(18,tensao_st,3,1,6,'T',255);	/* exibe tensao ST no display1 com 1 casa decimal entrada em q6)*/
				print_display(27,tensao_rt,3,1,6,'T',255);	/* exibe tensao RT no display1 com 1 casa decimal entrada em q6)*/
				}
		#endif
	#endif

}


void exibe_tensao_alta(void)
{
	#if (ST8100C == true)
		if (ja_rolou == true)
			{
			print_display(1,tensao_rs_na_alta,6,1);
			rolando = false;
			}
		else
			{
			mensagem_rola(36, 1);
			}
		if (piscar == 1)
			{
			led_v = 1;
			}
		else
			{
			led_v = 0;
			}
		led_a = 0;
		led_r = 0;
		led_w = 0;
	#else
		if (exibiu == 0)
			{
			mensagem (1,23);
			#if (monofasico == false)
				lcd_gotoxy(5,1);
			    wr_lcd(1,'(');
			    wr_lcd(1,'k');
			#endif
			mensagem (2,0);
			exibiu = 1;
			}
		#if (monofasico == true)
			print_display(17,tensao_rs_na_alta,3,1,6,'T', 255);
			lcd_gotoxy(7,2);
		    wr_lcd(1,'k');
		    wr_lcd(1,'V');
		    wr_lcd(1,'a');
		    wr_lcd(1,'c');
		    wr_lcd(1,'/');
		    wr_lcd(1,'A');
		    wr_lcd(1,'l');
		    wr_lcd(1,'t');
		    wr_lcd(1,'a');
		#else
			if (time_out2 == 0)
				{
				mensagem (1,138);
				mensagem (2,139);
				time_out2 = 10;
				}
			else
				{
				print_display(11,tensao_rs_na_alta,3,1,6,'T', 255);
				print_display(18,tensao_st_na_alta,3,1,6,'T', 255);
				print_display(27,tensao_rt_na_alta,3,1,6,'T', 255);
				}
		#endif
	#endif
}



void exibe_corrente(void)
{
	#if (ST8100C == true)
		if (ja_rolou == true)
			{
			print_display(1,corrente_r,3,0);
			rolando = false;
			}
		else
			{
			mensagem_rola(37, 1);
			}
		led_v = 0;
		led_a = 1;
		led_r = 0;
		led_w = 0;
	#else
		if (exibiu == 0)
			{
			mensagem (1,24);
			mensagem (2,0);
			exibiu = 1;
			}
		#if (monofasico == true)
			if (corrente_r == 0)
				{
				mensagem (2,0);
				}
			print_display(21,corrente_r,4,1,3,'C', 0);
		#else
			if (time_out2 == 0)
				{
				mensagem (1,138);
				mensagem (2,139);
				time_out2 = 10;
				}
			else
				{
				print_display(11,corrente_r,4,1,3,'C', 255);
				print_display(18,corrente_s,4,1,3,'C', 255);
				print_display(27,corrente_t,4,1,3,'C', 255);
				}
		#endif
	#endif
}


void exibe_frequencia(void)
{
	#if (ST8100C == true)
		if (ja_rolou == true)
			{
			print_display(1,frequencia,2,1);
			rolando = false;
			}
		else
			{
			mensagem_rola(m_menu1_16, 1);
			}
		led_v = 0;
		led_a = 0;
		led_r = 0;
		led_w = 0;
	#else
		if (exibiu == 0)
			{
			mensagem (1,25);
			mensagem (2,33);
			exibiu = 1;
			}
		print_display(22,frequencia,2,1,2,'F', 4);
	#endif
}



#if (st8500c == true)
	void exibe_kw_kvar(void)
		{
		if (exibiu == 0)
			{
			mensagem(1,26);
			mensagem(2,28);
			exibiu = 1;
			}
		#if (com_tc == true)
			aux_wexibe1 = pot_ativa_tot;
			aux_wexibe2 = pot_reativa_tot;
			if (valor_tc != 1)
				{
				aux_wexibe1 = aux_wexibe1 * valor_tp;
				aux_wexibe2 = aux_wexibe2 * valor_tp;
				}
			print_display(10,aux_wexibe1,4,1,5,'C', 255);
			print_display(26,aux_wexibe2,4,1,5,'C', 255);
		#else
			displayp(10,pot_ativa_tot,5,0,0);
			displayp(26,pot_reativa_tot,5,0,0);
		#endif
			
		}
#else		
	void exibe_pot_ativa(void)
	{
		#if (ST8100C == true)
			if (ja_rolou == true)
				{
				#if (com_rep == true)
					if (modo_rep == 1)
						{
						print_display(1,pot_ativa_tot,5,0);
						rolando = false;
						led_w = 1;
						goto exibe_pot_ativa_10;
						}
				#endif
				if (valor_tp != 1)
					{
					aux_l1 = pot_ativa_r;
					data1_int = aux_l1 / 32;
					print_display(1,(data1_int),0,0);
					rolando = false;
					if (piscar == 1)
						{
						led_w = 1;
						}
					else
						{
						led_w = 0;
						}
					}
				 else
			 		{
					print_display(1,pot_ativa_r,5,0);
					rolando = false;
					led_w = 1;
					}
				}
			else
				{
				mensagem_rola(12, 1);
				led_w = 1;
				}
exibe_pot_ativa_10:			
			led_v = 0;
			led_a = 0;
			led_r = 0;
		#else
			#if (monofasico == true)
				if (exibiu == 0)
					{
					mensagem(1,26);
					mensagem(2,0);
					exibiu = 1;
					}
				#if (com_rep == true)
					if (modo_rep == 1)
						{
						print_display(21,pot_ativa_tot,4,1,5,'C', 1);
					    wr_lcd(1,' ');
					    return;
						}
				#endif
				if (valor_tp != 1)
					{
					aux_l1 = pot_ativa_r;
					aux_l1 = aux_l1 * valor_tp;
					data1_int = aux_l1 / 32;
					print_display(21,data1_int,6,1,0,'C', 1);
					}
				else
					{
					if (sentido_r == 1)
						{
						lcd_gotoxy(4,2);
					    wr_lcd(1,'-');
						print_display(21,pot_ativa_r,4,1,5,'C', 1);
						}
					else
						{
						print_display(21,pot_ativa_r,4,1,5,'C', 1);
					    wr_lcd(1,' ');
						}
					}
			#else
				#if (com_rep == true)
					if (modo_rep == 1)
						{
						if (exibiu == 0)
							{
							mensagem(1,26);
							mensagem(2,28);
							exibiu = 1;
							}
						print_display(10,pot_ativa_tot,4,1,0,'C', 255);
					    wr_lcd(1,' ');
						print_display(26,pot_reativa_tot,4,1,0,'C', 255);
					    return;
						}
					else
						{
						if (exibiu == 0)
							{
							mensagem(1,26);
							mensagem(2,0);
							exibiu = 1;
							}
						}
				#else
					if (exibiu == 0)
						{
						mensagem(1,26);
						mensagem(2,0);
						exibiu = 1;
						}
				#endif
				if (time_out2 == 0)
					{
					mensagem (1,138);
					mensagem (2,139);
					time_out2 = 10;
					}
				else
					{
					if (valor_tp != 1)
						{
						aux_l1 = pot_ativa_r;
						aux_l1 = aux_l1 * valor_tp;
						data1_int = aux_l1 / 32;
						print_display(10,data1_int,6,1,0,'C', 255);
										
						aux_l1 = pot_ativa_s;
						aux_l1 = aux_l1 * valor_tp;
						data1_int = aux_l1 / 32;
						print_display(18,data1_int,6,1,0,'C', 255);
					
						aux_l1 = pot_ativa_t;
						aux_l1 = aux_l1 * valor_tp;
						data1_int = aux_l1 / 32;
						print_display(26,data1_int,6,1,0,'C', 255);
					 	}
					 else
					 	{
						if (sentido_r == 1)
							{
							lcd_gotoxy(10,1);
						    wr_lcd(1,'-');
							print_display(11,pot_ativa_r,4,1,5,'C', 255);
							}
						else
							{
							print_display(10,pot_ativa_r,4,1,5,'C', 255);
						    wr_lcd(1,' ');
							}
						if (sentido_s == 1)
							{
							lcd_gotoxy(1,2);
						    wr_lcd(1,'-');
							print_display(18,pot_ativa_s,4,1,5,'C', 255);
							}
						else
							{
							print_display(18,pot_ativa_s,4,1,5,'C', 255);
						    wr_lcd(1,' ');
							}
						if (sentido_t == 1)
							{
							lcd_gotoxy(10,2);
						    wr_lcd(1,'-');
							print_display(27,pot_ativa_t,4,1,5,'C', 255);
							}
						else
							{
							print_display(26,pot_ativa_t,4,1,5,'C', 255);
						    wr_lcd(1,' ');
							}
						}
					}
			#endif
		#endif
	}
#endif


void exibe_pot_aparente(void)
{
	#if (ST8100C == true)
		if (ja_rolou == true)
			{
			led_r = 0;
			led_w = 0;
			#if (com_rep == true)
				if (modo_rep == 1)
					{
					print_display(1,pot_aparente_tot,5,0);
					rolando = false;
					led_v = 1;
					led_a = 1;
					return;
					}
			#endif
			if (valor_tp != 1)
				{
				aux_l1 = pot_aparente_r;
				aux_l1 = aux_l1 * valor_tp;
				data1_int = aux_l1 / 32;
					
				print_display(1,(data1_int ),0,0);
				rolando = false;
				if (piscar == 1)
					{
					led_v = 1;
					led_a = 1;
					}
				else
					{
					led_v = 0;
					led_a = 0;
					}
				}
			 else
		 		{
				print_display(1,pot_aparente_r,5,0);
				rolando = false;
				led_v = 1;
				led_a = 1;
				}
			}
		else
			{
			mensagem_rola(13, 1);
			led_v = 1;
			led_a = 1;
			}
	#else
		#if (monofasico == true)
			if (exibiu == 0)
				{
				mensagem(1,27);
				mensagem(2,0);
				exibiu = 1;
				}
			#if (com_rep == true)
				if (modo_rep == 1)
					{
					print_display(20,pot_aparente_tot,4,1,5,'C', 2);
				    return;
					}
			#endif
			if (valor_tp != 1)
				{
				aux_l1 = pot_aparente_r;
				aux_l1 = aux_l1 * valor_tp;
				data1_int = aux_l1 / 32;
				print_display(20,data1_int,6,1,0,'C', 2);
				}
			 else
			 	{
				print_display(20,pot_aparente_r,4,1,5,'C', 2);
				}
		#else
			#if (com_rep == true)
				if (modo_rep == 1)
					{
					if (exibiu == 0)
						{
						mensagem(1,28);
						mensagem(2,27);
						exibiu = 1;
						}
					print_display(10,pot_reativa_tot,4,1,0,'C', 255);
				    wr_lcd(1,' ');
					print_display(26,pot_aparente_tot,4,1,0,'C', 255);
				    return;
					}
				else
					{
					if (exibiu == 0)
						{
						mensagem(1,27);
						mensagem(2,0);
						exibiu = 1;
						}
					}
			#else
				if (exibiu == 0)
					{
					mensagem(1,27);
					mensagem(2,0);
					exibiu = 1;
					}
			#endif
			if (time_out2 == 0)
				{
				mensagem (1,138);
				mensagem (2,139);
				time_out2 = 10;
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
		#endif
	#endif
}



void exibe_pot_reativa(void)
{
	#if (ST8100C == true)
		led_w = 0;
		if (ja_rolou == true)
			{
			#if (com_rep == true)
				if (modo_rep == 1)
					{
					print_display(1,pot_reativa_tot,5,0);
					rolando = false;
					led_v = 1;
					led_a = 1;
					led_r = 1;
					return;
					}
			#endif
			if (valor_tp != 1)
				{
				aux_l1 = pot_reativa_r;
				aux_l1 = aux_l1 * valor_tp;
				data1_int = aux_l1 / 32;
				print_display(1,(data1_int),0,0);
				rolando = false;
				if (piscar == 1)
					{
					led_v = 1;
					led_a = 1;
					led_r = 1;
					}
				else
					{
					led_v = 0;
					led_a = 0;
					led_r = 0;
					}
				}
			 else
		 		{
				print_display(1,pot_reativa_r,5,0);
				rolando = false;
				led_v = 1;
				led_a = 1;
				led_r = 1;
				}
			}
		else
			{
			mensagem_rola(14, 1);
			led_v = 1;
			led_a = 1;
			led_r = 1;
			}
	#else
		#if (monofasico == true)
			if (exibiu == 0)
				{
				mensagem(1,28);
				mensagem(2,0);
				exibiu = 1;
				}
			#if (com_rep == true)
				if (modo_rep == 1)
					{
					print_display(20,pot_reativa_tot,4,1,5,'C', 3);
				    return;
					}
			#endif
			if (valor_tp != 1)
				{
				aux_l1 = pot_reativa_r;
				aux_l1 = aux_l1 * valor_tp;
				data1_int = aux_l1 / 32;
				print_display(20,data1_int,6,1,0,'C', 3);
				}
			else
				{
				print_display(20,pot_reativa_r,4,1,5,'C', 3);
				}
		#else
			#if (com_rep == true)
				if (modo_rep == 1)
					{
					if (exibiu == 0)
						{
						mensagem(1,28);
						mensagem(2,146);
						exibiu = 1;
						}
					print_display(10,pot_reativa_tot,4,1,0,'C',255);
					displayfp(26,fator_pot_t,0);
					return;
					}
				else
					{
					if (exibiu == 0)
						{
						mensagem(1,28);
						mensagem(2,0);
						exibiu = 1;
						}
					}
			#else
				if (exibiu == 0)
					{
					mensagem(1,28);
					mensagem(2,0);
					exibiu = 1;
					}
			#endif
			if (time_out2 == 0)
				{
				mensagem (1,138);
				mensagem (2,139);
				time_out2 = 10;
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
		#endif
	#endif
}



#if (st8500c == true)
	void exibe_fp_kva(void)
		{
		if (exibiu == 0)
			{
			mensagem(1,27);
			mensagem(2,56);
			exibiu = 1;
			}
		#if (com_tc == true)
			aux_wexibe1 = pot_aparente_tot;
			if (valor_tc != 1)
				{
				aux_wexibe1 = aux_wexibe1 * valor_tp;
				}
			print_display(10,aux_wexibe1,4,1,5,'C', 255);
			displayfp(22,fator_pot,0);
		#else
			displayp(10,pot_aparente_tot,5,0,0);
			displayfp(25,fator_pot,0);
		#endif
		
		}
		
#else
	void exibe_fator_potencia(void)
	{
		#if (ST8100C == true)
			if (ja_rolou == true)
				{
				displayfp(1,fator_pot_r);
				rolando = false;
				}
			else
				{
				mensagem_rola(16, 1);
				}
			led_v = 0;
			led_a = 0;
			led_r = 0;
			led_w = 0;
		#else
			#if (monofasico == true)
				if (teclando == 0)
					{
					displayfp(22,fator_pot_r,1);
					}
				else
					{
					if (exibiu == 0)
						{
						mensagem (1,29);
						mensagem (2,0);
						exibiu = 1;
						}
					displayfp(21,fator_pot_r,0);
					}
			#else
				#if (com_rep == true)
					if (modo_rep == 1){
						exibe_pot_reativa();
						return;
						}
				#endif
				if (teclou_enter){
					displayfp(22,fator_pot,1);
				}
				else{
					if (exibiu == 0){
						mensagem (1,29);
						mensagem (2,0);
						mensagem (2,30);
						exibiu = 1;
					}
					displayfp(11,fator_pot_r,0);
					displayfp(19,fator_pot_s,0);
					displayfp(27,fator_pot_t,0);
				}
			#endif
		#endif
	}
#endif


#if (ST8100C == false)
	#if (st8500c == true)
		void exibe_pot_requerida_excedente(void)
		{
			if (exibiu == 0)
				{
				mensagem(1,31);
				mensagem(2,32);
				exibiu = 1;
				}
			aux_l1 = pot_req_r;
			aux_l1 = aux_l1 + pot_req_s + pot_req_t;
			print_display(11,aux_l1,4,1,5,'C', 255);
			aux_l1 = pot_exec_r;
			aux_l1 = aux_l1 + pot_exec_s + pot_exec_t;
			print_display(27,aux_l1,4,1,5,'C', 255);
		}
	#else
		void exibe_pot_requerida_excedente(void)
		{
			if (exibiu == 0)
				{
				mensagem (1,31);
				mensagem (2,0);
				exibiu = 1;
				}
			lcd_gotoxy(1,2);
			if (pot_req_r != 0)
				{
			    wr_lcd(1,'I');
			    wr_lcd(1,'n');
			    wr_lcd(1,'d');
			    data1_int = pot_req_r;
			    }
			else if (pot_exec_r != 0)
				{
			    wr_lcd(1,'C');
			    wr_lcd(1,'a');
			    wr_lcd(1,'p');
			    data1_int = pot_exec_r;
			    }
			else
				{
			    wr_lcd(1,' ');
			    wr_lcd(1,' ');
			    wr_lcd(1,' ');
			    data1_int = 0;
			    }
		    wr_lcd(1,':');
			print_display(23,data1_int,4,1,5,'C', 3);
		}
	#endif
#endif


#if (st8500c == false)
	void exibe_pot_requerida(void)
	{
		#if (ST8100C == true)
			if (ja_rolou == true)
				{
				print_display(1,pot_req_r,5,0);
				rolando = false;
				}
			else
				{
				mensagem_rola(15, 1);
				}
			led_v = 1;
			led_a = 1;
			led_r = 1;
			led_w = 0;
		#else
			if (exibiu == 0)
				{
				#if (com_rep == true)
					if (modo_rep == 1)
						{
						mensagem(1,31);
						mensagem(2,32);
						}
					else
						{
						mensagem(1,31);
						mensagem(2,0);
						}
				#else
					mensagem(1,31);
					mensagem(2,0);
				#endif
				exibiu = 1;
				}
			#if (monofasico == true)
				print_display(20,pot_req_r,4,1,5,'C', 3);
			#else
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
					mensagem (1,138);
					mensagem (2,139);
					time_out2 = 10;
					}
				else
					{
					print_display(11,pot_req_r,4,1,5,'C', 255);
					print_display(18,pot_req_s,4,1,5,'C', 255);
					print_display(27,pot_req_t,4,1,5,'C', 255);
					}
			#endif
		#endif
	}
	
	
	void exibe_pot_excedente(void)
	{
		#if (ST8100C == true)
			if (ja_rolou == true)
				{
				print_display(1,pot_exec_r,5,0);
				rolando = false;
				}
			else
				{
				mensagem_rola(49, 1);
				}
			led_v = 1;
			led_a = 1;
			led_r = 1;
			led_w = 0;
		#else
			if (exibiu == 0)
				{
				#if (com_rep == true)
					if (modo_rep == 1)
						{
						#if (st8300c == true)
							if (aux_menu1 == 0)
								{
								mensagem (1,147);
								mensagem (2,148);
								}
							else
								{
								mensagem (1,152);
								mensagem (2,153);
								}
						#else
							if (aux_menu1 == 0)
								{
								mensagem (1,147);
								mensagem (2,148);
								}
							else
								{
								mensagem (1,150);
								mensagem (2,151);
								}
						#endif
						}
					else
						{
						mensagem (1,32);
						mensagem (2,0);
						}
				#else
					mensagem (1,32);
					mensagem (2,0);
				#endif
				exibiu = 1;
				}
			#if (monofasico == true)
				print_display(20,pot_exec_r,4,1,5,'C', 3);
			#else
				#if (com_rep == true)
					if (modo_rep == 1)
						{
						if (aux_menu1 == 0)
							{
							displayp(12, ultimo_pulso_at,5,0,0);
							displayp(28, ultimo_pulso_reat,5,0,0);
							}
						else
							{
							displayp(12, (ultima_pot_at),5,0,0);
							displayp(28, (ultima_pot_reat),5,0,0);
							}
						return;
						}
				#endif
				if (time_out2 == 0)
					{
					mensagem (1,138);
					mensagem (2,139);
					time_out2 = 10;
					}
				else
					{
					print_display(11,pot_exec_r,4,1,5,'C', 255);
					print_display(18,pot_exec_s,4,1,5,'C', 255);
					print_display(27,pot_exec_t,4,1,5,'C', 255);
					}
			#endif
		#endif
	}
#endif	


#if (com_rep == true)
	void exibe_status_rep(void)
		{
		#if (ST8100C == true)
			switch(menu_aux)
				{
				case 11:
					{
					if (ja_rolou == true)
						{
						if (tarif_cap_rep == 1)
							{
							buf_display[0] = tabela_caracteres[MC];
							buf_display[1] = tabela_caracteres[MA];
							buf_display[2] = tabela_caracteres[MP];
							buf_display[3] = tabela_caracteres[MESPACO];
							}
						else
							{
							buf_display[0] = tabela_caracteres[MI];
							buf_display[1] = tabela_caracteres[MN];
							buf_display[2] = tabela_caracteres[MD];
							buf_display[3] = tabela_caracteres[MESPACO];
							}
						rolando = false;
						}
					else
						{
						mensagem_rola(58, 1);
						}
					led_v = 1;
					led_a = 1;
					led_r = 1;
					led_w = 0;
					break;
					}
				case 12:
					{
					if (ja_rolou == true)
						{
						print_display(1,seg_falt_rep,0,1);
						rolando = false;
						}
					else
						{
						mensagem_rola(59, 1);
						}
					led_v = 0;
					led_a = 0;
					led_r = 0;
					led_w = 0;
					break;
					}
				case 13:
					{
					if (ja_rolou == true)
						{
						print_display(1,puls_c1_rep,0,1);
						rolando = false;
						}
					else
						{
						mensagem_rola(60, 1);
						}
					led_v = 0;
					led_a = 0;
					led_r = 0;
					led_w = 1;
					break;
					}
				case 14:
					{
					if (ja_rolou == true)
						{
						print_display(1,puls_c2_rep,0,1);
						rolando = false;
						}
					else
						{
						mensagem_rola(61, 1);
						}
					led_v = 1;
					led_a = 1;
					led_r = 1;
					led_w = 0;
					break;
					}
				}
		#else
			if (exibiu == 0)
				{
				#if (st8300c == true)
					mensagem (1,144);
					mensagem (2,145);
				#elif (st8500c == true)
					mensagem (1,144);
					mensagem (2,145);
				#else
					mensagem (1,143);
					mensagem (2,144);
				#endif
				exibiu = 1;
				}
	
	//		  01234567890123456
	//		  67890123456789012
	//		 "Tar:   Tempo:   ",	//144
	//		 "P:      /       "		//145
			lcd_gotoxy(5,1);
			if (tarif_cap_rep == 1)
				{
			    wr_lcd(1,'C');
				}
			else
				{
			    wr_lcd(1,'I');
				}
			displayp (14,seg_falt_rep,3,0,0);
			displayp (19,puls_c1_rep,5,0,0);
			displayp (27,puls_c2_rep,5,0,0);
		#endif
		}


		#if (ST8100C == true)
			void exibe_status_rep_ant(void)
			{
				switch(menu_aux)
					{
					case 15:
						{
						if (ja_rolou == true)
							{
							print_display(1,ultimo_pulso_at,0,1);
							rolando = false;
							}
						else
							{
							mensagem_rola(69, 1);
							}
						led_v = 0;
						led_a = 0;
						led_r = 0;
						led_w = 1;
						break;
						}
					case 16:
						{
						if (ja_rolou == true)
							{
							print_display(1,ultimo_pulso_reat,0,1);
							rolando = false;
							}
						else
							{
							mensagem_rola(70, 1);
							}
						led_v = 1;
						led_a = 1;
						led_r = 1;
						led_w = 0;
						break;
						}
					case 17:
						{
						if (ja_rolou == true)
							{
							print_display(1,ultima_pot_at,5,0);
							rolando = false;
							}
						else
							{
							mensagem_rola(71, 1);
							}
						led_v = 0;
						led_a = 0;
						led_r = 0;
						led_w = 1;
						break;
						}
					case 18:
						{
						if (ja_rolou == true)
							{
							print_display(1,ultima_pot_reat,5,0);
							rolando = false;
							}
						else
							{
							mensagem_rola(72, 1);
							}
						led_v = 1;
						led_a = 1;
						led_r = 1;
						led_w = 0;
						break;
						}
					}
			}
		#else
			#if ((st8200c == true) || st8300c == true))
				void exibe_status_rep_ant(void)
				{
			 		if (aux_menu1 == 0)
			 			{
						if (exibiu == 0)
							{
							mensagem (1,145);
							mensagem (2,146);
							exibiu = 1;
							}
						displayp(12, ultimo_pulso_at,5,0,0);
						displayp(28, ultimo_pulso_reat,5,0,0);
						}
					else
						{
						if (exibiu == 0)
							{
							mensagem (1,150);
							mensagem (2,151);
							exibiu = 1;
							}
						displayp(10,ultima_pot_at,4,0,0);
						displayp(26,ultima_pot_reat,4,0,0);
						
						}
				}
			#endif
		#endif
		

		
#endif

#if (st8300c == true)
	#if (com_consumo == true)
		void exibe_consumo(void)
		{
		if (exibiu == 0)
			{
			mensagem (1,156);
			mensagem (2,157);
			exibiu = 1;
			}
			aux_f1 = consumo_ati;
			aux_l1 = (int32)(aux_f1 * mul_tc * valor_tp);
			displaypl(8,aux_l1,8);
			aux_f1 = consumo_reati;
			aux_l1 = (int32)(aux_f1 * mul_tc * valor_tp);
			displaypl(24,aux_l1,8);
		}
	#endif
#endif

#if (st8500c == true)
	void exibe_consumo(void)
	{
	if (exibiu == 0)
		{
		mensagem (1,140);
		mensagem (2,141);
		exibiu = 1;
		}
	#if (com_tc == true)
		aux_f1 = consumo_ati;
		aux_l1 = (int32)(aux_f1 * mul_tc * valor_tp);
		displaypl(7,aux_l1,10);
		aux_f1 = consumo_reati;
		aux_l1 = (int32)(aux_f1 * mul_tc * valor_tp);
		displaypl(23,aux_l1,10);
	#endif
	#if (com_rep == true)
		displaypl(7,consumo_ati,10);
		displaypl(23,consumo_reati,10);
	#endif
	}
	void exibe_consumo_mes_ant(void)
	{
	if (exibiu == 0)
		{
		mensagem (1,140);
		mensagem (2,141);
		exibiu = 1;
		}
	#if (com_tc == true)
		aux_f1 = read_long(ee_consumo_ati_ant);
		aux_l1 = (int32)(aux_f1 * mul_tc * valor_tp);
		displaypl(7,aux_l1,10);
		aux_f1 = read_long(ee_consumo_reati_ant);
		aux_l1 = (int32)(aux_f1 * mul_tc * valor_tp);
		displaypl(23,aux_l1,10);
	#endif
	#if (com_rep == true)
		displaypl(7,read_long(ee_consumo_ati_ant),10);
		displaypl(23,read_long(ee_consumo_reati_ant),10);
	#endif
	}
	#if (com_rep == true)
		void exibe_status_rep_pul_ant(void)
		{
			if (exibiu == 0)
				{
				mensagem (1,147);
				mensagem (2,148);
				exibiu = 1;
				}
			displayp(12, ultimo_pulso_at,5,0,0);
			displayp(28, ultimo_pulso_reat,5,0,0);
			}
		void exibe_status_rep_pot_ant(void)
			{
			if (exibiu == 0)
				{
				mensagem (1,151);
				mensagem (2,152);
				exibiu = 1;
				}
	//				print_display(10,ultima_pot_at,4,2,5,'C', 255);
	//				print_display(26,ultima_pot_reat,4,2,5,'C', 255);
	
			displayp(12,ultima_pot_at,5,0,0);
			displayp(28,ultima_pot_reat,5,0,0);
			}
	#endif
		
	void exibe_demanda_ativa(void)
		{
		if (exibiu == 0)
			{
			mensagem(1,47);
			mensagem(2,48);
			exibiu = 1;
			}
		#if (com_tc == true)
			aux_wexibe1 = dem_media_ativa;
			aux_wexibe2 = dem_ativa_proj;
			if (valor_tc != 1)
				{
				aux_wexibe1 = aux_wexibe1 * valor_tp;
				aux_wexibe2 = aux_wexibe2 * valor_tp;
				}
			print_display(12,aux_wexibe1,5,0,0,'C', 255);
			print_display(28,aux_wexibe2,5,0,0,'C', 255);
		#else
			displayp(12,dem_ativa,5,0,0);
			displayp(28,dem_ativa_proj,5,0,0);
		#endif
			
		}
	void exibe_demanda_reativa(void){
		if (exibiu == 0){
			mensagem(1,54);
			mensagem(2,55);
			exibiu = 1;
		}
		#if (com_tc == true)
			aux_wexibe1 = dem_media_reativa;
			aux_wexibe2 = dem_reativa_proj;
			if (valor_tc != 1)
				{
				aux_wexibe1 = aux_wexibe1 * valor_tp;
				aux_wexibe2 = aux_wexibe2 * valor_tp;
				}
			print_display(12,aux_wexibe1,5,0,0,'C', 255);
			print_display(28,aux_wexibe2,5,0,0,'C', 255);
		#else
			displayp(12,dem_reativa,5,0,0);
			displayp(28,dem_reativa_proj,5,0,0);
		#endif
	}
	void exibe_fator_carga_demanda(void)
		{
		if (exibiu == 0)
			{
			mensagem(1,29);
			mensagem(2,30);
			exibiu = 1;
			}
//		print_display(12,fator_carga,1,3,10,'C', 255);
//		print_display(28,fator_demanda,1,3,10,'C', 255);
		print_display(10,fator_carga,3,1,6,'C', 255);
		print_display(26,fator_demanda,3,1,6,'C', 255);
		}

	void exibe_set_point_demanda(void)
		{
		if (exibiu == 0)
			{
			mensagem(1,17);
			mensagem(2,22);
			exibiu = 1;
			}
		displayp(11,dem_contratada,4,0,0);
		displayp(27,dem_acionada,4,0,0);
		}
#endif


#if (st8500c == true)

	#define nro_medidas	17
	const char tabela_msg_medidas[nro_medidas]={
												26,			//0		
												28,			//1
												27,			//2
												31,			//3
												32,			//4
												47,			//5
												48,			//6
												54,			//7
												55,			//8
												29,			//9
												30,			//10
												144,		//11
												145,		//12
												147,		//13
												148,		//14
												151,		//15
												152			//16
												};									 
												

	void rola_medidas(void)
		{
		char aux_tab;
		aux_tab = menu_aux - 6; 
		if (exibiu == 0)
			{
			mensagem(1,tabela_msg_medidas[aux_tab]);
			mensagem(2,tabela_msg_medidas[aux_tab+1]);
			exibiu = 1;
			}
		switch(aux_tab)
			{
			case 0:
				{
				print_display(10,pot_ativa_tot,4,1,5,'C', 255);
				print_display(26,pot_reativa_tot,4,1,5,'C', 255);
				break;
				}
			case 1:
				{
				print_display(10,pot_reativa_tot,4,1,5,'C', 255);
				print_display(26,pot_aparente_tot,4,1,5,'C', 255);
				break;
				}
			case 2:
				{
				print_display(10,pot_aparente_tot,4,1,5,'C', 255);
				aux_l1 = pot_req_r;
				aux_l1 = aux_l1 + pot_req_s + pot_req_t;
				print_display(27,aux_l1,4,1,5,'C', 255);
				break;
				}
			case 3:
				{
				aux_l1 = pot_req_r;
				aux_l1 = aux_l1 + pot_req_s + pot_req_t;
				print_display(11,aux_l1,4,1,5,'C', 255);
				aux_l1 = pot_exec_r;
				aux_l1 = aux_l1 + pot_exec_s + pot_exec_t;
				print_display(27,aux_l1,4,1,5,'C', 255);
				break;
				}
			case 4:
				{
				aux_l1 = pot_exec_r;
				aux_l1 = aux_l1 + pot_exec_s + pot_exec_t;
				print_display(11,aux_l1,4,1,5,'C', 255);
				displayp(28,dem_ativa,4,0,0);
				break;	
				}
			case 5:
				{
				displayp(12,dem_ativa,4,0,0);
				displayp(28,dem_ativa_proj,4,0,0);
				break;
				}
			case 6:
				{
				displayp(12,dem_ativa_proj,4,0,0);
				displayp(28,dem_reativa,4,0,0);
				break;
				}
			case 7:
				{
				displayp(12,dem_reativa,4,0,0);
				displayp(28,dem_reativa_proj,4,0,0);
				break;
				}
			case 8:
				{
				displayp(12,dem_reativa_proj,4,0,0);
				displayp(28,fator_carga,3,0,0);
				break;
				}
			case 9:
				{
				displayp(12,fator_carga,3,0,0);
				displayp(28,fator_demanda,3,0,0);
				break;
				}
			case 10:
				{
				#if (com_rep == true)
					displayp(12,fator_demanda,3,0,0);
					lcd_gotoxy(5,2);
					if (tarif_cap_rep == 1)
						{
					    wr_lcd(1,'C');
						}
					else
						{
					    wr_lcd(1,'I');
						}
					displayp (30,seg_falt_rep,3,0,0);
					break;					
				#endif
                    break;
				}
			case 11:
				{
				#if (com_rep == true)
		//		  	  01234567890123456
		//		  	  67890123456789012
		//			 "Tar:   Tempo:   ",	//144
		//			 "P:      /       "		//145
					lcd_gotoxy(5,1);
					if (tarif_cap_rep == 1)
						{
					    wr_lcd(1,'C');
						}
					else
						{
					    wr_lcd(1,'I');
						}
					displayp(14,seg_falt_rep,3,0,0);
					displayp(19,puls_c1_rep,5,0,0);
					displayp(27,puls_c2_rep,5,0,0);
					break;
				#endif
                    break;
				}
			case 12:
				{
				#if (com_rep == true)
					displayp(3,puls_c1_rep,5,0,0);
					displayp(11,puls_c2_rep,5,0,0);
					displayp(28, ultimo_pulso_at,5,0,0);
					break;
				#endif
                    break;
				}
			case 13:
				{
				#if (com_rep == true)
					displayp(12, ultimo_pulso_at,5,0,0);
					displayp(28, ultimo_pulso_reat,5,0,0);
					break;
				#endif
                    break;
				}
			case 14:
				{
				#if (com_rep == true)
					displayp(12, ultimo_pulso_reat,5,0,0);
					print_display(26,ultima_pot_at,4,2,5,'C', 255);
					break;
				#endif
                    break;
				}
			case 15:
				{
				#if (com_rep == true)
					print_display(10,ultima_pot_at,4,2,5,'C', 255);
					print_display(26,ultima_pot_reat,4,2,5,'C', 255);
					break;					
				#endif
				}
			}
		}
		
#endif
