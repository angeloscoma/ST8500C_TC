/*;**********************************************************************
; Empresa: SULTECH SISTEMAS ELETRONICOS									*
; Modulo: ST_VALI														*
; Funcao: MODULO VALIDACAO DE PROGRAMACAO								*
; Responsavel: VAGNER SANTOS											*
; Modificado ; VAGNER SANTOS											*
; Inicio: 30/08/2000													*
; Revisao: RENGAV ARIERREF SOD SOTNAS									*
;************************************************************************/
  

void valida_programa(void);
void calcula_fundo_escala_corrente(void);


word valida_word(word variavel, word ee_variavel, word minimo, word maximo, word padrao)
{
	if ((variavel < minimo) || (variavel > maximo))
		{
		variavel = read_word(ee_variavel);
		if ((variavel < minimo) || (variavel > maximo))
			{
			write_word(ee_variavel, padrao);
			variavel = padrao;
			}
		}
	return(variavel);
}			

char valida_byte(byte variavel, word ee_variavel, byte minimo, byte maximo, byte padrao)
{
	if (minimo == 0)
		{
		if (variavel > maximo)
			{
			variavel = read_byte(ee_variavel);
			if (variavel > maximo)
				{
				write_byte(ee_variavel, padrao);
				variavel = padrao;
				}
			}
		}
	else if (maximo == 255)
		{
		if (variavel < minimo)
			{
			variavel = read_byte(ee_variavel);
			if (variavel < minimo)
				{
				write_byte(ee_variavel, padrao);
				variavel = padrao;
				}
			}
		}
	else
		{
		if ((variavel < minimo) || (variavel > maximo))
			{
			variavel = read_byte(ee_variavel);
			if ((variavel < minimo) || (variavel > maximo))
				{
				write_byte(ee_variavel, padrao);
				variavel = padrao;
				}
			}
		}
	return(variavel);
}			

#if (controlador == true) || (st_prog == true)
	#if (st8500c == true)
		void valida_max_kw(void);

	#else
		void gera_sequencia_valor_bancos(void);
	#endif
#endif

/* INICIO DA ROTINA PRINCIPAL */


#if (controlador == true) || (st_prog == true)
	#if (st8500c == true)
	#else
		void valida_min_max_kvar(void)
		{		
			char x;
			#if (AUTOSET == true)
				if (em_autoset == true)
					{
					return;
					}
			#endif
			
			max_kvar = read_byte(ee_max_kvar);
			min_kvar = read_byte(ee_min_kvar);
			if (max_kvar > MAIOR_BANCO_POSSIVEL) 
				{
				max_kvar = 0;
				write_byte(ee_max_kvar, 0);
				}
			if (min_kvar > MAIOR_BANCO_POSSIVEL)
				{
				min_kvar = 5;
				write_byte(ee_min_kvar, 5);
				}
			
			if (max_kvar != 0)
				{
				for (x = 0; x < nro_bancos_capacitor; x++)
					{
					if (max_kvar < banco_capacitor[x])
						{
						max_kvar = banco_capacitor[x];
						write_byte(ee_max_kvar, max_kvar);
						}
					}
				if (min_kvar > max_kvar)
					{
					min_kvar =  max_kvar;
					write_byte(ee_min_kvar, min_kvar);
					}
				}
			maior_banco = 0;
			for (x = 0; x < nro_bancos_capacitor; x++)
				{
				if (maior_banco < banco_capacitor[x])
					{
					maior_banco = banco_capacitor[x];
					}
				}
			menor_banco = 255;
			for (x = 0; x < nro_bancos_capacitor; x++)
				{
				if (menor_banco > banco_capacitor[x])
					{
					menor_banco = banco_capacitor[x];
					}
				}
			if (min_kvar != 0)
				{
				if (min_kvar < menor_banco)
					{
					min_kvar = menor_banco;
					write_byte(ee_min_kvar, min_kvar);
					}
				}
		}
		
		void vali_nro_bancos_capacitor(void)	    	
		{
			#if (AUTOSET == true)
				if (em_autoset == true)
					{
					return;
					}
			#endif
			
		    if ((nro_bancos_capacitor == 0) || (nro_bancos_capacitor > NRO_MAXIMO_BANCOS_CAPACITOR))
	 	   		{
	     	   	nro_bancos_capacitor = read_byte(ee_nro_bancos_capacitor);
		    	if ((nro_bancos_capacitor == 0) || (nro_bancos_capacitor > NRO_MAXIMO_BANCOS_CAPACITOR))
	 	   			{
		 	   		#if (monofasico == true)
		 	   			#if (bancos_12 == true)
					 	   	nro_bancos_capacitor = NRO_MAXIMO_BANCOS_CAPACITOR;
		 	 	    	  	write_byte(ee_nro_bancos_capacitor, NRO_MAXIMO_BANCOS_CAPACITOR);
						#else
					 	   	nro_bancos_capacitor = NRO_MAXIMO_BANCOS_CAPACITOR / 2;
		 	 	    	  	write_byte(ee_nro_bancos_capacitor, NRO_MAXIMO_BANCOS_CAPACITOR / 2);
		 	 	    	 #endif
		 	   		#else
				 	   	nro_bancos_capacitor = NRO_MAXIMO_BANCOS_CAPACITOR;
	 	 	    	  	write_byte(ee_nro_bancos_capacitor, NRO_MAXIMO_BANCOS_CAPACITOR);
		 	   		#endif
		 		   	}
				}
		}
	#endif
#endif


#if (com_menu == true)
	void inic_idioma(void)
	{
		#if (portatil == true)
			idioma = read_byte(ee_idioma);
			if ((idioma != PORTUGUES) && (idioma != ESPANHOL))
				{
				idioma = PORTUGUES;
				write_byte(ee_idioma, idioma);
				}
		#else
			idioma = PORTUGUES;
		#endif
	}
#endif

void valida_programa(void)
{	

	#if (controlador == true)
		#if (AUTOSET == true)
			if (em_autoset == true)
				{
				return;
				}
		#endif
	#endif

	#if (st5x == true)
		 bloqueio_gravacao = read_byte(ee_bloqueio_gravacao);
	#else
		 bloqueio_gravacao = 0;
	#endif

	#if (com_menu == true)
		inic_idioma();
	#endif

	set_point = valida_byte(set_point, ee_set_point, 90, 99, 95);
	
	
	erro=1;
	for (aux_b1=0; aux_b1 < (NRO_POSI_TEN-1); aux_b1++)
		{
		if (ten_nomi == tabela_ten[aux_b1])
			{
			erro=0;
			break;
			}
		}
	if (erro==1)
		{
		ten_nomi = read_word(ee_ten_nomi);
		for (aux_b1=0; aux_b1 < (NRO_POSI_TEN-1); aux_b1++)
			{
			if (ten_nomi == tabela_ten[aux_b1])
				{
				erro=0;
				break;
				}
			}
		if (erro==1)
			{
			ten_nomi = 220;
			write_word(ee_ten_nomi, ten_nomi);
			}
		}

	#if (portatil == true)
		#if (se_com_flex == true)
			if (tipo_ponteira > (NRO_POSI_TABELA_TIPO_PT+1))
				{
				tipo_ponteira = read_byte(ee_tipo_ponteira);
				if (tipo_ponteira > (NRO_POSI_TABELA_TIPO_PT+1))
					{
					tipo_ponteira = 2;		//Alicate 1000A Minipa
					write_byte(ee_tipo_ponteira, 2);
					}
				}
			ve_ref_ponteiras();
			valor_tc = tabela_pt[tipo_ponteira];
			busca_mul_tc();
		#else
			erro = 1;
			for (aux_b1=0; aux_b1 < (NRO_POSI_TC+1); aux_b1++)
				{
				if (valor_tc == tabela_tc[aux_b1])
					{
					erro=0;
					#if (viercon == true)
						if (aux_b1 == 2)
							{
							vref_cr = vref;
							vref_cs = vref;
							vref_ct = vref;
							}
						else
							{
							vref_cr = tabela_vref_cr[aux_b1];
							vref_cs = tabela_vref_cs[aux_b1];
							vref_ct = tabela_vref_ct[aux_b1];
							}
					#endif
					break;
					}
				}
			if (erro == 1)
				{
				valor_tc =  read_word(ee_valor_tc);
				for (aux_b1=0; aux_b1 < (NRO_POSI_TC+1); aux_b1++)
					{
					if (valor_tc == tabela_tc[aux_b1])
						{
						erro=0;
						#if (viercon == true)
							if (aux_b1 == 2)
								{
								vref_cr = vref;
								vref_cs = vref;
								vref_ct = vref;
								}
							else
								{
								vref_cr = tabela_vref_cr[aux_b1];
								vref_cs = tabela_vref_cs[aux_b1];
								vref_ct = tabela_vref_ct[aux_b1];
								}
						#endif
						break;
						}
					}
				#if (viercon == true)
					vref_cr = tabela_vref_cr[2];
					vref_cs = tabela_vref_cs[2];
					vref_ct = tabela_vref_cr[2];
					if (erro == 1)
						{
						valor_tc = 3000;		
						write_word(ee_valor_tc, valor_tc);
						}
				#else
					if (erro == 1)
						{
						valor_tc = 1000;		
						write_word(ee_valor_tc, valor_tc);
						}
				#endif
				}
			 #if (sazi == true)
				if (valor_tc != 200)
					{
					valor_tc = 200;		
					write_word(ee_valor_tc, valor_tc);
					}			 
			 #endif

		#endif
	#else
		erro = 1;
		for (aux_b1=0; aux_b1 < (NRO_POSI_TC+1); aux_b1++)
			{
			if (valor_tc == tabela_tc[aux_b1])
				{
				posi_tc = aux_b1;
				erro=0;
				break;
				}
			}
		if (erro == 1)
			{
			valor_tc =  read_word(ee_valor_tc);
			for (aux_b1=0; aux_b1 < (NRO_POSI_TC+1); aux_b1++)
				{
				if (valor_tc == tabela_tc[aux_b1])
					{
					posi_tc = aux_b1;
					erro=0;
					break;
					}
				}
			if (erro == 1)
				{
				valor_tc = 500;		
				posi_tc = 19;
				write_word(ee_valor_tc, valor_tc);
				}
			}
	#endif

	#if (tc_fixo == true)
		#if (portatil == true)
			busca_mul_tc();
		#else
			calcula_mul_tc();
		#endif
	#endif

	valor_tp = valida_word(valor_tp, ee_valor_tp, 1, 500, 1);
	
	#if (portatil == true)
		#if (se_com_flex == true)
			// Correntes:
			// Fase R:
			aux_w1 = ee_os_cor_r_9001g1;
			for (aux_b1 = 0; aux_b1 < NRO_POSI_TABELA_TIPO_PT; aux_b1++)
				{
				if ((os_cor_pt_r[aux_b1] > LIMITE_COR_SUP) || (os_cor_pt_r[aux_b1] < LIMITE_COR_INF))
					{
					os_cor_pt_r[aux_b1] = read_byte(aux_w1);
					if ((os_cor_pt_r[aux_b1] > LIMITE_COR_SUP) || (os_cor_pt_r[aux_b1] < LIMITE_COR_INF))
						{
						os_cor_pt_r[aux_b1] = OFF_SET_COR_R;
						write_byte(aux_w1, OFF_SET_COR_R);
						}
			        }
				aux_w1 += 3; 
				}
		
			// Fase S:
			aux_w1 = ee_os_cor_s_9001g1;
			for (aux_b1 = 0; aux_b1 < NRO_POSI_TABELA_TIPO_PT; aux_b1++)
				{
				if ((os_cor_pt_s[aux_b1] > LIMITE_COR_SUP) || (os_cor_pt_s[aux_b1] < LIMITE_COR_INF))
					{
					os_cor_pt_s[aux_b1] = read_byte(aux_w1);
					if ((os_cor_pt_s[aux_b1] > LIMITE_COR_SUP) || (os_cor_pt_s[aux_b1] < LIMITE_COR_INF))
						{
						os_cor_pt_s[aux_b1] = OFF_SET_COR_S;
						write_byte(aux_w1, OFF_SET_COR_S);
						}
					}
				aux_w1 += 3; 
		        }
			// Fase T:
			aux_w1 = ee_os_cor_t_9001g1;
			for (aux_b1 = 0; aux_b1 < NRO_POSI_TABELA_TIPO_PT; aux_b1++)
				{
				if ((os_cor_pt_t[aux_b1] > LIMITE_COR_SUP) || (os_cor_pt_t[aux_b1] < LIMITE_COR_INF))
					{
					os_cor_pt_t[aux_b1] = read_byte(aux_w1);
					if ((os_cor_pt_t[aux_b1] > LIMITE_COR_SUP) || (os_cor_pt_t[aux_b1] < LIMITE_COR_INF))
						{
						os_cor_pt_t[aux_b1] = OFF_SET_COR_T;
						write_byte(aux_w1, OFF_SET_COR_T);
						}
					}
				aux_w1 += 3; 
		        }
		
			// Potÿÿÿÿÿÿÿências:
			// Fase R:
			aux_w1 = ee_os_pot_r_9001g1;
			for (aux_b1 = 0; aux_b1 < NRO_POSI_TABELA_TIPO_PT; aux_b1++)
				{
				if ((os_pot_pt_r[aux_b1] > LIMITE_POT_SUP) || (os_pot_pt_r[aux_b1] < LIMITE_POT_INF))
					{
					os_pot_pt_r[aux_b1] = read_byte(aux_w1);
					if ((os_pot_pt_r[aux_b1] > LIMITE_POT_SUP) || (os_pot_pt_r[aux_b1] < LIMITE_POT_INF))
						{
						os_pot_pt_r[aux_b1] = OFF_SET_POT_R;
						write_byte(aux_w1, OFF_SET_POT_R);
						}
			        }
				aux_w1 += 3; 
				}
		
			// Fase S:
			aux_w1 = ee_os_pot_s_9001g1;
			for (aux_b1 = 0; aux_b1 < NRO_POSI_TABELA_TIPO_PT; aux_b1++)
				{
				if ((os_pot_pt_s[aux_b1] > LIMITE_POT_SUP) || (os_pot_pt_s[aux_b1] < LIMITE_POT_INF))
					{
						os_pot_pt_s[aux_b1] = read_byte(aux_w1);
					if ((os_pot_pt_s[aux_b1] > LIMITE_POT_SUP) || (os_pot_pt_s[aux_b1] < LIMITE_POT_INF))
						{
						os_pot_pt_s[aux_b1] = OFF_SET_POT_S;
						write_byte(aux_w1, OFF_SET_POT_S);
						}
					}
				aux_w1 += 3; 
		        }
			// Fase T:
			aux_w1 = ee_os_pot_t_9001g1;
			for (aux_b1 = 0; aux_b1 < NRO_POSI_TABELA_TIPO_PT; aux_b1++)
				{
				if ((os_pot_pt_t[aux_b1] > LIMITE_POT_SUP) || (os_pot_pt_t[aux_b1] < LIMITE_POT_INF))
					{
						os_pot_pt_t[aux_b1] = read_byte(aux_w1);
					if ((os_pot_pt_t[aux_b1] > LIMITE_POT_SUP) || (os_pot_pt_t[aux_b1] < LIMITE_POT_INF))
						{
						os_pot_pt_t[aux_b1] = OFF_SET_POT_T;
						write_byte(aux_w1, OFF_SET_POT_T);
						}
					}
				aux_w1 += 3; 
		        }
		#else
		// correntes
		// fase R
			aux_w1 = ee_os_cor_r_20;
			for (aux_b1=0; aux_b1 < NRO_POSI_TC; aux_b1++)
				{
				if ((os_cor_pt_r[aux_b1] > LIMITE_COR_SUP) || (os_cor_pt_r[aux_b1] < LIMITE_COR_INF))
					{
					os_cor_pt_r[aux_b1] = read_byte(aux_w1);
					if ((os_cor_pt_r[aux_b1] > LIMITE_COR_SUP) || (os_cor_pt_r[aux_b1] < LIMITE_COR_INF))
						{
						os_cor_pt_r[aux_b1] = OFF_SET_COR_R;
						write_byte(aux_w1, OFF_SET_COR_R);
						}
			        }
				aux_w1 += 3; 
				}
		
		// fase S
			aux_w1 = ee_os_cor_s_20;
			for (aux_b1=0; aux_b1 < NRO_POSI_TC; aux_b1++)
				{
				if (os_cor_pt_s[aux_b1] > LIMITE_COR_SUP || os_cor_pt_s[aux_b1] < LIMITE_COR_INF)
					{
					os_cor_pt_s[aux_b1] = read_byte(aux_w1);
					if (os_cor_pt_s[aux_b1] > LIMITE_COR_SUP || os_cor_pt_s[aux_b1] < LIMITE_COR_INF)
						{
						os_cor_pt_s[aux_b1] = OFF_SET_COR_S;
						write_byte(aux_w1, OFF_SET_COR_S);
						}
					}
				aux_w1 += 3; 
		        }
		// fase T
			aux_w1 = ee_os_cor_t_20;
			for (aux_b1=0; aux_b1 < NRO_POSI_TC; aux_b1++)
				{
				if (os_cor_pt_t[aux_b1] > LIMITE_COR_SUP || os_cor_pt_t[aux_b1] < LIMITE_COR_INF)
					{
					os_cor_pt_t[aux_b1] = read_byte(aux_w1);
					if (os_cor_pt_t[aux_b1] > LIMITE_COR_SUP || os_cor_pt_t[aux_b1] < LIMITE_COR_INF)
						{
						os_cor_pt_t[aux_b1] = OFF_SET_COR_T;
						write_byte(aux_w1, OFF_SET_COR_T);
						}
					}
				aux_w1 += 3; 
		        }
		
		// potencias
		// fase R
			aux_w1 = ee_os_pot_r_20;
			for (aux_b1=0; aux_b1 < NRO_POSI_TC; aux_b1++)
				{
				if (os_pot_pt_r[aux_b1] > LIMITE_POT_SUP || os_pot_pt_r[aux_b1] < LIMITE_POT_INF)
					{
					os_pot_pt_r[aux_b1] = read_byte(aux_w1);
					if (os_pot_pt_r[aux_b1] > LIMITE_POT_SUP || os_pot_pt_r[aux_b1] < LIMITE_POT_INF)
						{
						os_pot_pt_r[aux_b1] = OFF_SET_POT_R;
						write_byte(aux_w1, OFF_SET_POT_R);
						}
			        }
				aux_w1 += 3; 
				}
		
		// fase S
			aux_w1 = ee_os_pot_s_20;
			for (aux_b1=0; aux_b1 < NRO_POSI_TC; aux_b1++)
				{
				if (os_pot_pt_s[aux_b1] > LIMITE_POT_SUP || os_pot_pt_s[aux_b1] < LIMITE_POT_INF)
					{
					os_pot_pt_s[aux_b1] = read_byte(aux_w1);
					if (os_pot_pt_s[aux_b1] > LIMITE_POT_SUP || os_pot_pt_s[aux_b1] < LIMITE_POT_INF)
						{
						os_pot_pt_s[aux_b1] = OFF_SET_POT_S;
						write_byte(aux_w1, OFF_SET_POT_S);
						}
					}
				aux_w1 += 3; 
		        }
		// fase T
			aux_w1 = ee_os_pot_t_20;
			for (aux_b1=0; aux_b1 < NRO_POSI_TC; aux_b1++)
				{
				if (os_pot_pt_t[aux_b1] > LIMITE_POT_SUP || os_pot_pt_t[aux_b1] < LIMITE_POT_INF)
					{
					os_pot_pt_t[aux_b1] = read_byte(aux_w1);
					if (os_pot_pt_t[aux_b1] > LIMITE_POT_SUP || os_pot_pt_t[aux_b1] < LIMITE_POT_INF)
						{
						os_pot_pt_t[aux_b1] = OFF_SET_POT_T;
						write_byte(aux_w1, OFF_SET_POT_T);
						}
					}
				aux_w1 += 3; 
		        }
		#endif
#else

		if (os_cor_r > LIMITE_COR_SUP || os_cor_r < LIMITE_COR_INF)
			{
			os_cor_r = read_byte(ee_os_cor_r);
			if (os_cor_r > LIMITE_COR_SUP || os_cor_r < LIMITE_COR_INF)
				{
				os_cor_r = OFF_SET_COR_R;
				write_byte(ee_os_cor_r, os_cor_r);
				}
	        }
		#if (monofasico == false)
			if (os_cor_s > LIMITE_COR_SUP || os_cor_s < LIMITE_COR_INF)
				{
				os_cor_s = read_byte(ee_os_cor_s);
				if (os_cor_s > LIMITE_COR_SUP || os_cor_s < LIMITE_COR_INF)
					{
					os_cor_s = OFF_SET_COR_S;
					write_byte(ee_os_cor_s, os_cor_s);
					}
		        }
			if (os_cor_t > LIMITE_COR_SUP || os_cor_t < LIMITE_COR_INF)
				{
				os_cor_t = read_byte(ee_os_cor_t);
				if (os_cor_t > LIMITE_COR_SUP || os_cor_t < LIMITE_COR_INF)
					{
					os_cor_t = OFF_SET_COR_T;
					write_byte(ee_os_cor_t, os_cor_t);
					}
		        }
		#endif
#endif

	if ((os_ten_r1 > LIMITE_TEN_SUP) || (os_ten_r1 < LIMITE_TEN_INF))
		{
		os_ten_r1 = read_byte(ee_os_ten_r1);
		if ((os_ten_r1 > LIMITE_TEN_SUP) || (os_ten_r1 < LIMITE_TEN_INF))
			{
			os_ten_r1 = OFF_SET_TEN_R1;
			write_byte(ee_os_ten_r1, os_ten_r1);
			}
        }
	if ((os_ten_r2 == 0) || (os_ten_r2 == 255))
		{
		os_ten_r2 = read_byte(ee_os_ten_r2);
		if ((os_ten_r2 == 0) || (os_ten_r2 == 255))
			{
			os_ten_r2 = 91;
			write_byte(ee_os_ten_r2, os_ten_r2);
			}
        }
        
	#if (monofasico == false)
		if ((os_ten_s1 > LIMITE_TEN_SUP) || (os_ten_s1 < LIMITE_TEN_INF))
			{
			os_ten_s1 = read_byte(ee_os_ten_s1);
			if ((os_ten_s1 > LIMITE_TEN_SUP) || (os_ten_s1 < LIMITE_TEN_INF))
				{
				os_ten_s1 = OFF_SET_TEN_S1;
				write_byte(ee_os_ten_s1, os_ten_s1);
				}
	        }
		if ((os_ten_t1 > LIMITE_TEN_SUP) || (os_ten_t1 < LIMITE_TEN_INF))
			{
			os_ten_t1 = read_byte(ee_os_ten_t1);
			if ((os_ten_t1 > LIMITE_TEN_SUP) || (os_ten_t1 < LIMITE_TEN_INF))
				{
				os_ten_t1 = OFF_SET_TEN_T1;
				write_byte(ee_os_ten_t1, os_ten_t1);
				}
	        }
		if ((os_ten_s2 == 0) || (os_ten_s2 == 255))
			{
			os_ten_s2 = read_byte(ee_os_ten_s2);
			if ((os_ten_s2 == 0) || (os_ten_s2 == 255))
				{
				os_ten_s2 = 108;
				write_byte(ee_os_ten_s2, os_ten_s2);
				}
	        }
		if ((os_ten_t2 == 0) || (os_ten_t2 == 255))
			{
			os_ten_t2 = read_byte(ee_os_ten_t2);
			if ((os_ten_t2 == 0) || (os_ten_t2 == 255))
				{
				os_ten_t2 = 101;
				write_byte(ee_os_ten_t2, os_ten_t2);
				}
	        }

	        
	#endif

	// offset fator de potencia
	#if (portatil == true)
		#if (se_com_flex ==	true)
			aux_w1 = ee_off_fp_9001g1;
			for (aux_b1 = 0; aux_b1 < NRO_POSI_TABELA_TIPO_PT; aux_b1++)
				{
				if (off_set_fp[aux_b1] > (OFF_SET_FP_R * 2))
					{
					off_set_fp[aux_b1] = read_byte(aux_w1);
					if (off_set_fp[aux_b1] > (OFF_SET_FP_R * 2))
						{
						off_set_fp[aux_b1] = OFF_SET_FP_R;
						write_byte(aux_w1, OFF_SET_FP_R);
						}
					}
				aux_w1++;
		        }

			off_cor_r = off_set_fp[tipo_ponteira];
			if (off_cor_r > (NRO_AMOSTRAS/2))
				{
				aux_w1 = ee_off_fp_9001g1;
				aux_w1 += tipo_ponteira;
				off_cor_r = read_byte(aux_w1);
				off_set_fp[tipo_ponteira] = off_cor_r;
				if (off_cor_r > (NRO_AMOSTRAS/2))
					{
					off_cor_r = OFF_SET_FP_R;
					write_byte(aux_w1, off_cor_r);
					off_set_fp[tipo_ponteira] = off_cor_r;
					}
		    	}
			
		#else
			aux_w1 = ee_off_fp_20;
			for (aux_b1 = 0; aux_b1 < NRO_POSI_TC; aux_b1++)
				{
				if (off_set_fp[aux_b1] > (OFF_SET_FP_R * 2))
					{
					off_set_fp[aux_b1] = read_byte(aux_w1);
					if (off_set_fp[aux_b1] > (OFF_SET_FP_R * 2))
						{
						off_set_fp[aux_b1] = OFF_SET_FP_R;
						write_byte(aux_w1, OFF_SET_FP_R);
						}
					}
				aux_w1++;
		        }

			for (aux_b1=0; aux_b1 < NRO_POSI_TC; aux_b1++)
				{
				if (valor_tc == tabela_tc[aux_b1])
					{
					off_cor_r = off_set_fp[aux_b1];
					break;
					}
				}

			if (off_cor_r > NRO_AMOSTRAS/4)
				{
				aux_w1 = ee_off_fp_20;
				aux_w1 = aux_w1 + aux_b1;
				off_cor_r = read_byte(aux_w1);
				off_set_fp[aux_b1] = off_cor_r;
				if (off_cor_r > NRO_AMOSTRAS/4)
					{
					off_cor_r = OFF_SET_FP_R;
					write_byte(aux_w1, off_cor_r);
					off_set_fp[aux_b1] = off_cor_r;
					}
		    	}

		#endif
	#else
		#if (ade7754 == true)
	
		#else
			if (((off_cor_r > (NRO_AMOSTRAS / 8)) &&  (off_cor_r < (NRO_AMOSTRAS-(NRO_AMOSTRAS / 8)))) || (off_cor_r >= NRO_AMOSTRAS))
				{
				off_cor_r = read_byte(ee_off_cor_r);
				if (((off_cor_r > (NRO_AMOSTRAS / 8)) &&  (off_cor_r < (NRO_AMOSTRAS-(NRO_AMOSTRAS / 8)))) || (off_cor_r >= NRO_AMOSTRAS))
					{
					off_cor_r = OFF_SET_FP_R;
					write_byte(ee_off_cor_r, off_cor_r);
					}
		    	}
		#endif
	
		#if (controlador == true)
			#if (monofasico == true)
				if ( (off_cor_s > ((NRO_AMOSTRAS / 2) - (NRO_AMOSTRAS/8)) ) && (off_cor_s < ((NRO_AMOSTRAS / 4) - (NRO_AMOSTRAS / 8))) )
					{
					off_cor_s = read_byte(ee_off_cor_s);
					if ((off_cor_s > ((NRO_AMOSTRAS / 2) - (NRO_AMOSTRAS/8))) && (off_cor_s < ((NRO_AMOSTRAS / 4) - (NRO_AMOSTRAS / 8))))
						{
						off_cor_s = (NRO_AMOSTRAS / 4);
						write_byte(ee_off_cor_s, off_cor_s);
						}
			    	}
			#else
				if (off_cor_s > NRO_AMOSTRAS)
					{
					off_cor_s = read_byte(ee_off_cor_s);
					if (off_cor_s > NRO_AMOSTRAS)
						{
						off_cor_s = (NRO_AMOSTRAS / 4);
						write_byte(ee_off_cor_s, off_cor_s);
						}
			    	}
			 #endif
			#if (prog_defasagem ==	true)
			    if (defasagem > (nro_posi_tab_defasagem_trafo - 1))
			    	{
	   				defasagem = read_byte(ee_defasagem);
				    if (defasagem > (nro_posi_tab_defasagem_trafo - 1))
				    	{
					    defasagem = posi_tab_defasagem_trafo_default;
					    write_byte(ee_defasagem, posi_tab_defasagem_trafo_default);
					    }
				    }
			#endif
			 
		#else
			if (off_cor_s > NRO_AMOSTRAS)
				{
				off_cor_s = read_byte(ee_off_cor_s);
				if (off_cor_s > NRO_AMOSTRAS)
					{
					off_cor_s = 59;
					write_byte(ee_off_cor_s, off_cor_s);
					}
		    	}
		#endif
	#endif

	#if (portatil == false)
		if ((os_pot_r > LIMITE_POT_SUP) || (os_pot_r < LIMITE_POT_INF))
			{
			os_pot_r = read_byte(ee_os_pot_r);
			if ((os_pot_r > LIMITE_POT_SUP) || (os_pot_r < LIMITE_POT_INF))
				{
				os_pot_r = OFF_SET_POT_R;
				write_byte(ee_os_pot_r, os_pot_r);
				}
	        }
	
		#if (monofasico == false)
			if ((os_pot_s > LIMITE_POT_SUP) || (os_pot_s < LIMITE_POT_INF))
				{
				os_pot_s = read_byte(ee_os_pot_s);
				if (os_pot_s > LIMITE_POT_SUP || (os_pot_s < LIMITE_POT_INF))
					{
					os_pot_s = OFF_SET_POT_S;
					write_byte(ee_os_pot_s, os_pot_s);
					}
		        }
		
			if ((os_pot_t > LIMITE_POT_SUP) || (os_pot_t < LIMITE_POT_INF))
				{
				os_pot_t = read_byte(ee_os_pot_t);
				if (os_pot_t > LIMITE_POT_SUP || (os_pot_t < LIMITE_POT_INF))
					{
					os_pot_t = OFF_SET_POT_T;
					write_byte(ee_os_pot_t, os_pot_t);
					}
		        }
	
		#endif
	#endif
	
	#if (com_regs == true)
		if (forma_reg_cht > 3)
			{
			forma_reg_cht = read_byte(ee_forma_reg_cht);
			if (forma_reg_cht > 3)
				{
				forma_reg_cht = 0;
				write_byte(ee_forma_reg_cht, 0);
				}
			}  

		erro=1;
		#if (controlador == false)
			{
			for (aux_b1=0; aux_b1 < 21; aux_b1++)
				{
				if (intervalo_reg == tabela_intervalo_reg[aux_b1])
					{
					erro=0;
					break;
					}
				}
			if (erro==1)
				{
				intervalo_reg =  read_word(ee_intervalo_reg);
				for (aux_b1=0; aux_b1 < NRO_POSI_INTERVALO; aux_b1++)
					{
					if (intervalo_reg == tabela_intervalo_reg[aux_b1])
						{
						erro=0;
						break;
						}
					}
				if (erro==1)
					{
					intervalo_reg = INTERVALO_REG_DEFAULT;		
					write_word(ee_intervalo_reg, INTERVALO_REG_DEFAULT);
					}
				}
			}
		#else
			{
			intervalo_reg = INTERVALO_REG_DEFAULT;		
			}
		#endif
		

	#endif

	#if (st5x == false)
		erro = 1;
		#if (portatil == true)	
			{
			#if (st9600r == true)
				#if (teste_baud_115	== true)
			  		set_uart_speed (57200, modbus);
				#else
				  	set_uart_speed (19200, modbus);
				#endif	
			#else
			  	set_uart_speed (19200, modbus);
			#endif	
				
			}
		#else
			for (aux_b1 = 0; aux_b1 < NRO_POSI_BAUD; aux_b1++)
				{
				if (baud_rate == tabela_baud[aux_b1])
					{
				  	seta_baud_rate();
					erro = 0;
					break;
					}
				}
			if (erro == 1)
				{
				baud_rate =  read_word(ee_baud_rate);
				for (aux_b1 = 0; aux_b1 < NRO_POSI_BAUD; aux_b1++)
					{
					if (baud_rate == tabela_baud[aux_b1])
						{
						erro = 0;
						break;
						}
					}
				if (erro == 1)
					{
					baud_rate =  tabela_baud[3];
					write_byte(ee_baud_rate, baud_rate);
				  	seta_baud_rate();
					}
				}
		#endif
		endereco =  read_byte(ee_endereco);
		if ((endereco == 0) || (endereco > 248))
			{
			endereco = 1;
			write_byte(ee_endereco, endereco);
			}
	#endif
	#if (home_system == true)
		endereco =  read_byte(ee_endereco);
		if (endereco == 255)
			{
			endereco = 100;
			write_byte(ee_endereco, endereco);
			}
	#endif

	#if (st8500c == true)
		#if (com_tc == true)
		 	if (intervalo_integra != 15)
		 		{
			 	intervalo_integra = 15;
			 	write_byte(ee_intervalo_integra, 15);
			 	}
		#endif
	#endif
	#if (CONTROLADOR == false)
		intervalo_integra = valida_byte(intervalo_integra, ee_intervalo_integra, 0, 60, 15);
	#endif	
	#if (CONTROLADOR == true) || (st_prog == true)
		#if (st8500c == false)
			#if (com_rep == true)
				cor_minima_rep = valida_word(cor_minima_rep, ee_cor_minima_rep, 0, 9999, 0);
			#endif
			cor_minima = valida_byte(cor_minima, ee_cor_minima, 0, 50, 2);
			com_des_ten_a = valida_byte(com_des_ten_a, ee_com_des_ten_a, 0, 50, 0);
			com_des_ten_b = valida_byte(com_des_ten_b, ee_com_des_ten_b, 0, 50, 0);
			com_des_chtt = valida_byte(com_des_chtt, ee_com_des_chtt, 0, 50, 0);
			com_des_chtc = valida_byte(com_des_chtc, ee_com_des_chtc, 0, 50, 0);
			com_des_fp_ind_cap = valida_byte(com_des_fp_ind_cap, ee_com_des_fp_ind_cap, 80, (98+(100-set_point)), 100);
		#endif

		#if (st8500c == true)
			for (aux_b1 = 0; aux_b1 < NRO_MAXIMO_CARGAS; aux_b1++)
				{
				carga[aux_b1] = valida_byte(carga[aux_b1], (ee_carga_1 + aux_b1), 0, MAXIMA_CARGA, 100);
				}
			vali_nro_cargas();   	
			valida_max_kw();
		#else
			if (banco_capacitor[0] > 250)
				{
				banco_capacitor[0] = read_byte(ee_banco_capacitor_1);
				if (banco_capacitor[0] > 250)
					{
					banco_capacitor[0] = 5;
					write_byte(ee_banco_capacitor_1,5);
					}
				}
			vali_nro_bancos_capacitor();	    	
			valida_min_max_kvar();
		#endif

		
		#if (st8500c == true) 
			tempo_aciona = valida_byte(tempo_aciona, ee_tempo_aciona, 5, 240, 30);				//mínimo alterado de 30s para 5s
			tempo_desaciona = valida_byte(tempo_desaciona, ee_tempo_desaciona, 5, 240, 30);		//mínimo alterado de 30s para 5s
			aux_w1 = 0;
			for (aux_b1 = 0; aux_b1 < 13; aux_b1++)
				{
				dem_cont_ponta[aux_b1] = valida_word(dem_cont_ponta[aux_b1], (ee_dem_cont_ponta + aux_w1), 0, CARGA_INSTALADA_MAX, NRO_MAXIMO_CARGAS * 100);
				dem_cont_fora_ponta[aux_b1] = valida_word(dem_cont_fora_ponta[aux_b1], (ee_dem_cont_fora_ponta + aux_w1), 0, CARGA_INSTALADA_MAX, NRO_MAXIMO_CARGAS * 100);
				aux_w1 += 2;
				}
			carga_programada = valida_word(carga_programada, ee_carga_programada, 0, CARGA_INSTALADA_MAX, MAXIMA_CARGA_TOTAL);

			#if (com_rep == true)
				fat_conv_ativa = valida_word(fat_conv_ativa, ee_fat_conv_ativa, 1, 9999, 1000);
				fat_conv_reativa = valida_word(fat_conv_reativa, ee_fat_conv_reativa, 1, 9999, 1000);
				protocolo_REP = valida_byte(protocolo_REP, ee_protocolo_REP, 0, 3, 0);
			#endif
			

			dia_inicio_pc = valida_byte(dia_inicio_pc, ee_dia_inicio_pc, 1, 31, 1);
			mes_inicio_pc = valida_byte(mes_inicio_pc, ee_mes_inicio_pc, 1, 12, 5);
			dia_final_pc = valida_byte(dia_final_pc, ee_dia_final_pc, 1, 31, 30);
			mes_final_pc = valida_byte(mes_final_pc, ee_mes_final_pc, ee_mes_inicio_pc, 12, 11);
	
			if ((mes_final_pc == mes_inicio_pc) || (mes_final_pc < mes_inicio_pc))
				{
				mes_final_pc = read_byte(ee_mes_final_pc);
				mes_inicio_pc = read_byte(ee_mes_inicio_pc);
				if ((mes_final_pc == mes_inicio_pc) || (mes_final_pc < mes_inicio_pc))
					{
					if (mes_inicio_pc != 12)
						{
						mes_final_pc = 11;
						}
					else
						{
						mes_final_pc = 11;
						mes_inicio_pc = 5;
						}
					write_byte(ee_mes_inicio_pc, mes_inicio_pc);
					write_byte(ee_mes_final_pc, mes_final_pc);
					}
				}

			tipo_controle_demanda = valida_byte(tipo_controle_demanda, ee_tipo_controle_demanda, 0, 1, 0);

			for (aux_b1 = 0; aux_b1 < NRO_MAXIMO_CARGAS; aux_b1++)
				{
				if ((forma_controle[aux_b1] != 'D' ) && (forma_controle[aux_b1] != 'H'))
					{
					forma_controle[aux_b1] = read_byte(ee_forma_controle + aux_b1);
					if ((forma_controle[aux_b1] != 'D' ) && (forma_controle[aux_b1] != 'H'))
						{
						forma_controle[aux_b1] = 'D';
						write_byte(ee_forma_controle + aux_b1, 'D');
						}
					}
				hora_liga_controle[aux_b1] = valida_byte(hora_liga_controle[aux_b1], (ee_hora_liga_controle + aux_b1), 0, 23, 18);
				minuto_liga_controle[aux_b1] = valida_byte(minuto_liga_controle[aux_b1], (ee_minuto_liga_controle + aux_b1), 0, 59, 0);
				hora_desliga_controle[aux_b1] = valida_byte(hora_desliga_controle[aux_b1], (ee_hora_desliga_controle + aux_b1), 0, 23, 21);
				minuto_desliga_controle[aux_b1] = valida_byte(minuto_desliga_controle[aux_b1], (ee_minuto_desliga_controle + aux_b1), 0, 59, 0);
				}
			if ((modo_saidas != MODO_INVERTIDO) && (modo_saidas != MODO_NORMAL))
				{
				modo_saidas = read_byte(ee_modo_saidas);
				if ((modo_saidas != MODO_INVERTIDO) && (modo_saidas != MODO_NORMAL))
					{
					modo_saidas = MODO_NORMAL;
					write_byte(ee_modo_saidas, MODO_NORMAL);
					}
				}
		#else
			tempo_aciona = valida_byte(tempo_aciona, ee_tempo_aciona, 0, 240, 30);
			tempo_desaciona = valida_byte(tempo_desaciona, ee_tempo_desaciona, 0, 240, 5);
			#if (com_rep == true)
				fat_conv_ativa = valida_word(fat_conv_ativa, ee_fat_conv_ativa, 1, 9999, 1000);
				fat_conv_reativa = valida_word(fat_conv_reativa, ee_fat_conv_reativa, 1, 9999, 1000);
				protocolo_REP = valida_byte(protocolo_REP, ee_protocolo_REP, 0, 3, 0);
			#endif
		#endif


		#if (st8500c == true)
			#define tempo_rmaximo	240
			#define tempo_rdefault	60
			
			for (aux_b1 = 0; aux_b1 < nro_cargas; aux_b1++)
				{
				if ((tempo_repouso[aux_b1] > tempo_rmaximo) || (tempo_repouso[aux_b1] < tempo_aciona))
					{
					tempo_repouso[aux_b1] = read_byte(ee_tempo_repouso_1 + aux_b1);
					if ((tempo_repouso[aux_b1] > tempo_rmaximo) || (tempo_repouso[aux_b1] < tempo_aciona))
						{
						tempo_repouso[aux_b1] = tempo_rdefault;
						write_byte((ee_tempo_repouso_1 + aux_b1), tempo_rdefault);
						}
					}
				}
		#else

			if (sequencia > NRO_SEQUENCIAS)
				{
				sequencia =	read_byte(ee_sequencia);
				if (sequencia > NRO_SEQUENCIAS)
					{
					sequencia = 1;
					write_byte(ee_sequencia, 1);
					gera_sequencia_valor_bancos();
					}
				}
				
			gera_sequencia_valor_bancos();
		
			#define tempo_rmaximo	240
			#define tempo_rdefault	180
			
			#if (st_prog == false)
				for (aux_b1 = 0; aux_b1 < nro_bancos_capacitor; aux_b1++)
					{
					if ((tempo_repouso[aux_b1] > tempo_rmaximo) || (tempo_repouso[aux_b1] < tempo_aciona))
						{
						tempo_repouso[aux_b1] = read_byte(ee_tempo_repouso_1 + aux_b1);
						if ((tempo_repouso[aux_b1] > tempo_rmaximo) || (tempo_repouso[aux_b1] < tempo_aciona))
							{
							tempo_repouso[aux_b1] = tempo_rdefault;
							write_byte((ee_tempo_repouso_1 + aux_b1), tempo_rdefault);
							}
						}
					}
			#endif
		#endif
		
	    	
	#endif

	ala_fp_ind = valida_byte(ala_fp_ind, ee_ala_fp_ind, 80, 100, 100);
	ala_fp_cap = valida_byte(ala_fp_cap, ee_ala_fp_cap, 80, 100, 100);
	ala_ten_a = valida_byte(ala_ten_a, ee_ala_ten_a, 0, 20, 0);
	ala_ten_b = valida_byte(ala_ten_b, ee_ala_ten_b, 0, 30, 0);
	
	#if (st8500c == false)
		ala_sc = valida_byte(ala_sc, ee_ala_sc, 0, 150, 0);
//		ala_subc = valida_byte(ala_subc, ee_ala_subc, 0, 50, 0);
		ala_subc = valida_byte(ala_subc, ee_ala_subc, 0, 100, 0);		//Implementado em 29/09/09 por solicitação de cliente.
		ala_skw = valida_byte(ala_skw, ee_ala_skw, 0, 150, 0);
		ala_chtt = valida_byte(ala_chtt, ee_ala_chtt, 0, 50, 0);
		ala_chtc = valida_byte(ala_chtc, ee_ala_chtc, 0, 50, 0);
	#endif
// valida programa horario
	#if (com_regs == true)
		#if (portatil == true)
			if (registro > 1)
				{
			 	registro = read_byte(ee_registro);
				if ((registro != 0) && (registro != 1))
					{
					registro = 1;
					write_byte(ee_registro, 1);
					}
				}
			
			if (prog_time > 1)
				{
			 	prog_time = read_byte(ee_prog_time);
				if ((prog_time > 1))
					{
					prog_time = 0;
					write_byte(ee_prog_time, 1);
					}
				}
	
			if (hora_liga > 23)
				{
				hora_liga = read_byte(ee_hora_liga);
				if (hora_liga > 23)
					{
					hora_liga = 0;
					write_byte(ee_hora_liga, 0);
					}
				}
			if (hora_desliga > 23)
				{
				hora_desliga = read_byte(ee_hora_desliga);
				if (hora_desliga > 23)
					{
					hora_desliga = 23;
					write_byte(ee_hora_desliga, 0);
					}
				}

			if (minuto_liga > 59)
				{
				minuto_liga = read_byte(ee_minuto_liga);
				if (minuto_liga > 59)
					{
					minuto_liga = 0;
					write_byte(ee_minuto_liga, 0);
					}
				}
			if (minuto_desliga > 59)
				{
				minuto_desliga = read_byte(ee_minuto_desliga);
				if (minuto_desliga > 59)
					{
					minuto_desliga = 59;
					write_byte(ee_minuto_desliga, 0);
					}
				}

			if (dia_liga > 31)
				{
				dia_liga == read_byte(ee_dia_liga);
				if (dia_liga > 31)
					{
					dia_liga = 1;
					write_byte(ee_dia_liga, 1);
					}
				}
			if (dia_desliga > 31)
				{
				dia_desliga == read_byte(ee_dia_desliga);
				if (dia_desliga > 31)
					{
					dia_desliga = 31;
					write_byte(ee_dia_desliga, 1);
					}
				}

			if (fila_circular > 1)
				{
			 	fila_circular = read_byte(ee_fila_circular);
				if ((fila_circular != 0) && (fila_circular != 1))
					{
					fila_circular = 1;
					write_byte(ee_fila_circular, 1);
					}
				}
		
			#if (com_menu == true)
				if (qmenu != 5)
					{
			#endif
				if (dia_liga == dia_desliga)
					{
					if (hora_liga == hora_desliga)
						{
						if (minuto_liga == minuto_desliga)
							{
							if (prog_time == 1)
								{
								prog_time = 0;
								write_byte(ee_prog_time,0);
								}
							}
						}
					}
			#if (com_menu == true)
					}		
			#endif
		#endif
		

	#endif

	if (tipo_ligacao > 3)
		{
	 	tipo_ligacao = read_byte(ee_tipo_ligacao);
		if ((tipo_ligacao > 3))
			{
			tipo_ligacao = 0;
			write_byte(ee_tipo_ligacao, 0);
			}
		}


	#if (st_prog == true)
		tipo_ligacao = 0;
	#endif

	#if (st8500c == true)
		ala_demanda_ativa = valida_byte(ala_demanda_ativa, ee_ala_demanda_ativa, 0, 20, 10);
	#else
		#if (com_alarme_demanda == true)
			ala_demanda_ativa = valida_word(ala_demanda_ativa, ee_ala_demanda_ativa, 0, 9999, 0);
		#endif
	#endif


	#if (funcao_505 == false)
		modo_funca = 1;
	#endif
		
	modo_funca = valida_byte(modo_funca, ee_modo_funca, 0, 3, 1);

	erro = 0;
	if (hora_ponta >= hora_final_ponta)
		{
		hora_ponta = read_byte(ee_hora_ponta);
		hora_final_ponta = read_byte(ee_hora_final_ponta);
		if (hora_ponta >= hora_final_ponta)
			{
			erro = 1;
			}
		}
	if (hora_ponta > 23)
		{
		hora_ponta = read_byte(ee_hora_ponta);
		if (hora_ponta > 23)
			{
			erro = 1;
			}
		}
	if (hora_final_ponta > 23)
		{
		hora_final_ponta = read_byte(ee_hora_final_ponta);
		if (hora_final_ponta > 23)
			{
			erro = 1;
			}
		}
	if (minuto_ponta > 59)
		{
		minuto_ponta = read_byte(ee_minuto_ponta);
		if (minuto_ponta > 59)
			{
			erro = 1;
			}
		}
	if (minuto_final_ponta > 59)
		{
		minuto_final_ponta = read_byte(ee_minuto_final_ponta);
		if (minuto_final_ponta > 59)
			{
			erro = 1;
			}
		}
	if (erro == 1)
		{
		hora_ponta = 18;
		hora_final_ponta = 21;
		minuto_ponta = 0;
		minuto_final_ponta = 0;
		write_byte(ee_hora_ponta, 18);
		write_byte(ee_hora_final_ponta, 21);
		write_byte(ee_minuto_ponta, 30);
		write_byte(ee_minuto_final_ponta, 30);
		}

	#if (st_prog == true)
		tipo_ligacao = 0;
	#endif


	calcula_checksum_vars();

	calcula_fundo_escala_corrente();

    	
}


void assume_defaults(void)
	{
		set_point = 95;
		write_byte(ee_set_point, set_point);
		ten_nomi = 220;
		write_word(ee_ten_nomi, ten_nomi);
		valor_tc = 500;		
		#if (tc_fixo == true)
			#if (portatil == true)
				busca_mul_tc();
			#else
				calcula_mul_tc();
			#endif
		#endif
	
		#if (portatil == true)
			#if (se_com_flex == true)
				write_byte(ee_tipo_ponteira, 2);	//Alicate 1000A Minipa
			#else
				write_word(ee_valor_tc, 500);
			#endif
		#else
			write_word(ee_valor_tc, 500);
		#endif
		valor_tp = 1;		
		write_word(ee_valor_tp, 1);
		#if (portatil == true)	
			#if (se_com_flex == true)
				// ST9001G1
				os_cor_pt_r[0] = OFF_SET_COR_R_9001G1;
				write_byte(ee_os_cor_r_9001g1, OFF_SET_COR_R_9001G1);
				os_cor_pt_s[0] = OFF_SET_COR_S_9001G1;
				write_byte(ee_os_cor_s_9001g1, OFF_SET_COR_S_9001G1);
				os_cor_pt_t[0] = OFF_SET_COR_T_9001G1;
				write_byte(ee_os_cor_t_9001g1, OFF_SET_COR_T_9001G1);
				// ST9001G2
				os_cor_pt_r[1] = OFF_SET_COR_R_9001G2;
				write_byte(ee_os_cor_r_9001g2, OFF_SET_COR_R_9001G2);
				os_cor_pt_s[1] = OFF_SET_COR_S_9001G2;
				write_byte(ee_os_cor_s_9001g2, OFF_SET_COR_S_9001G2);
				os_cor_pt_t[1] = OFF_SET_COR_T_9001G2;
				write_byte(ee_os_cor_t_9001g2, OFF_SET_COR_T_9001G2);
				// ST9002G1
				os_cor_pt_r[2] = OFF_SET_COR_R_9002G1;
				write_byte(ee_os_cor_r_9002g1, OFF_SET_COR_R_9002G1);
				os_cor_pt_s[2] = OFF_SET_COR_S_9002G1;
				write_byte(ee_os_cor_s_9002g1, OFF_SET_COR_S_9002G1);
				os_cor_pt_t[2] = OFF_SET_COR_T_9002G1;
				write_byte(ee_os_cor_t_9002g1, OFF_SET_COR_T_9002G1);
				// ST9003G1
				os_cor_pt_r[3] = OFF_SET_COR_R_9003G1;
				write_byte(ee_os_cor_r_9003g1, OFF_SET_COR_R_9003G1);
				os_cor_pt_s[3] = OFF_SET_COR_S_9003G1;
				write_byte(ee_os_cor_s_9003g1, OFF_SET_COR_S_9003G1);
				os_cor_pt_t[3] = OFF_SET_COR_T_9003G1;
				write_byte(ee_os_cor_t_9003g1, OFF_SET_COR_T_9003G1);
				// ST9004G1
				os_cor_pt_r[4] = OFF_SET_COR_R_9004G1;
				write_byte(ee_os_cor_r_9004g1, OFF_SET_COR_R_9004G1);
				os_cor_pt_s[4] = OFF_SET_COR_S_9004G1;
				write_byte(ee_os_cor_s_9004g1, OFF_SET_COR_S_9004G1);
				os_cor_pt_t[4] = OFF_SET_COR_T_9004G1;
				write_byte(ee_os_cor_t_9004g1, OFF_SET_COR_T_9004G1);
				// ST9005G1
				os_cor_pt_r[5] = OFF_SET_COR_R_9005G1;
				write_byte(ee_os_cor_r_9005g1, OFF_SET_COR_R_9005G1);
				os_cor_pt_s[5] = OFF_SET_COR_S_9005G1;
				write_byte(ee_os_cor_s_9005g1, OFF_SET_COR_S_9005G1);
				os_cor_pt_t[5] = OFF_SET_COR_T_9005G1;
				write_byte(ee_os_cor_t_9005g1, OFF_SET_COR_T_9005G1);
				// ST9005G2
				os_cor_pt_r[6] = OFF_SET_COR_R_9005G2;
				write_byte(ee_os_cor_r_9005g2, OFF_SET_COR_R_9005G2);
				os_cor_pt_s[6] = OFF_SET_COR_S_9005G2;
				write_byte(ee_os_cor_s_9005g2, OFF_SET_COR_S_9005G2);
				os_cor_pt_t[6] = OFF_SET_COR_T_9005G2;
				write_byte(ee_os_cor_t_9005g2, OFF_SET_COR_T_9005G2);
				// ST9005G3
				os_cor_pt_r[7] = OFF_SET_COR_R_9005G3;
				write_byte(ee_os_cor_r_9005g3, OFF_SET_COR_R_9005G3);
				os_cor_pt_s[7] = OFF_SET_COR_S_9005G3;
				write_byte(ee_os_cor_s_9005g3, OFF_SET_COR_S_9005G3);
				os_cor_pt_t[7] = OFF_SET_COR_T_9005G3;
				write_byte(ee_os_cor_t_9005g3, OFF_SET_COR_T_9005G3);
				// ST9005G4
				os_cor_pt_r[8] = OFF_SET_COR_R_9005G4;
				write_byte(ee_os_cor_r_9005g4, OFF_SET_COR_R_9005G4);
				os_cor_pt_s[8] = OFF_SET_COR_S_9005G4;
				write_byte(ee_os_cor_s_9005g4, OFF_SET_COR_S_9005G4);
				os_cor_pt_t[8] = OFF_SET_COR_T_9005G4;
				write_byte(ee_os_cor_t_9005g4, OFF_SET_COR_T_9005G4);
				// ST9005G5
				os_cor_pt_r[9] = OFF_SET_COR_R_9005G5;
				write_byte(ee_os_cor_r_9005g5, OFF_SET_COR_R_9005G5);
				os_cor_pt_s[9] = OFF_SET_COR_S_9005G5;
				write_byte(ee_os_cor_s_9005g5, OFF_SET_COR_S_9005G5);
				os_cor_pt_t[9] = OFF_SET_COR_T_9005G5;
				write_byte(ee_os_cor_t_9005g5, OFF_SET_COR_T_9005G5);
				// ST9006G1
				os_cor_pt_r[10] = OFF_SET_COR_R_9006G1;
				write_byte(ee_os_cor_r_9006g1, OFF_SET_COR_R_9006G1);
				os_cor_pt_s[10] = OFF_SET_COR_S_9006G1;
				write_byte(ee_os_cor_s_9006g1, OFF_SET_COR_S_9006G1);
				os_cor_pt_t[10] = OFF_SET_COR_T_9006G1;
				write_byte(ee_os_cor_t_9006g1, OFF_SET_COR_T_9006G1);
				// ST9006G2
				os_cor_pt_r[11] = OFF_SET_COR_R_9006G2;
				write_byte(ee_os_cor_r_9006g2, OFF_SET_COR_R_9006G2);
				os_cor_pt_s[11] = OFF_SET_COR_S_9006G2;
				write_byte(ee_os_cor_s_9006g2, OFF_SET_COR_S_9006G2);
				os_cor_pt_t[11] = OFF_SET_COR_T_9006G2;
				write_byte(ee_os_cor_t_9006g2, OFF_SET_COR_T_9006G2);
				// ST9006G3
				os_cor_pt_r[12] = OFF_SET_COR_R_9006G3;
				write_byte(ee_os_cor_r_9006g3, OFF_SET_COR_R_9006G3);
				os_cor_pt_s[12] = OFF_SET_COR_S_9006G3;
				write_byte(ee_os_cor_s_9006g3, OFF_SET_COR_S_9006G3);
				os_cor_pt_t[12] = OFF_SET_COR_T_9006G3;
				write_byte(ee_os_cor_t_9006g3, OFF_SET_COR_T_9006G3);
				// ST9006G4
				os_cor_pt_r[13] = OFF_SET_COR_R_9006G4;
				write_byte(ee_os_cor_r_9006g4, OFF_SET_COR_R_9006G4);
				os_cor_pt_s[13] = OFF_SET_COR_S_9006G4;
				write_byte(ee_os_cor_s_9006g4, OFF_SET_COR_S_9006G4);
				os_cor_pt_t[13] = OFF_SET_COR_T_9006G4;
				write_byte(ee_os_cor_t_9006g4, OFF_SET_COR_T_9006G4);
				// ST9006G5
				os_cor_pt_r[14] = OFF_SET_COR_R_9006G5;
				write_byte(ee_os_cor_r_9006g5, OFF_SET_COR_R_9006G5);
				os_cor_pt_s[14] = OFF_SET_COR_S_9006G5;
				write_byte(ee_os_cor_s_9006g5, OFF_SET_COR_S_9006G5);
				os_cor_pt_t[14] = OFF_SET_COR_T_9006G5;
				write_byte(ee_os_cor_t_9006g5, OFF_SET_COR_T_9006G5);
				// ST9007G1
				os_cor_pt_r[15] = OFF_SET_COR_R_9007G1;
				write_byte(ee_os_cor_r_9007g1, OFF_SET_COR_R_9007G1);
				os_cor_pt_s[15] = OFF_SET_COR_S_9007G1;
				write_byte(ee_os_cor_s_9007g1, OFF_SET_COR_S_9007G1);
				os_cor_pt_t[15] = OFF_SET_COR_T_9007G1;
				write_byte(ee_os_cor_t_9007g1, OFF_SET_COR_T_9007G1);
				// ST9007G2
				os_cor_pt_r[16] = OFF_SET_COR_R_9007G2;
				write_byte(ee_os_cor_r_9007g2, OFF_SET_COR_R_9007G2);
				os_cor_pt_s[16] = OFF_SET_COR_S_9007G2;
				write_byte(ee_os_cor_s_9007g2, OFF_SET_COR_S_9007G2);
				os_cor_pt_t[16] = OFF_SET_COR_T_9007G2;
				write_byte(ee_os_cor_t_9007g2, OFF_SET_COR_T_9007G2);
				// ST9008G1
				os_cor_pt_r[17] = OFF_SET_COR_R_9008G1;
				write_byte(ee_os_cor_r_9008g1, OFF_SET_COR_R_9008G1);
				os_cor_pt_s[17] = OFF_SET_COR_S_9008G1;
				write_byte(ee_os_cor_s_9008g1, OFF_SET_COR_S_9008G1);
				os_cor_pt_t[17] = OFF_SET_COR_T_9008G1;
				write_byte(ee_os_cor_t_9008g1, OFF_SET_COR_T_9008G1);
	
			#elif (viercon == true)			
				// 30
				os_cor_pt_r[0] = OFF_SET_COR_R_20;
				write_byte(ee_os_cor_r_20, OFF_SET_COR_R_20);
				os_cor_pt_s[0] = OFF_SET_COR_S_20;
				write_byte(ee_os_cor_r_20, OFF_SET_COR_S_20);
				os_cor_pt_t[0] = OFF_SET_COR_T_20;
				write_byte(ee_os_cor_t_20, OFF_SET_COR_T_20);
				// 300
				os_cor_pt_r[1] = OFF_SET_COR_R_200;
				write_byte(ee_os_cor_r_200, OFF_SET_COR_R_200);
				os_cor_pt_s[1] = OFF_SET_COR_S_200;
				write_byte(ee_os_cor_r_200, OFF_SET_COR_S_200);
				os_cor_pt_t[1] = OFF_SET_COR_T_200;
				write_byte(ee_os_cor_t_200, OFF_SET_COR_T_200);
				// 3000
				os_cor_pt_r[2] = OFF_SET_COR_R_300;
				write_byte(ee_os_cor_r_300, OFF_SET_COR_R_300);
				os_cor_pt_s[2] = OFF_SET_COR_S_300;
				write_byte(ee_os_cor_r_300, OFF_SET_COR_S_300);
				os_cor_pt_t[2] = OFF_SET_COR_T_300;
				write_byte(ee_os_cor_t_300, OFF_SET_COR_T_300);
			#else
				// 20
				os_cor_pt_r[0] = OFF_SET_COR_R_20;
				write_byte(ee_os_cor_r_20, OFF_SET_COR_R_20);
				os_cor_pt_s[0] = OFF_SET_COR_S_20;
				write_byte(ee_os_cor_r_20, OFF_SET_COR_S_20);
				os_cor_pt_t[0] = OFF_SET_COR_T_20;
				write_byte(ee_os_cor_t_20, OFF_SET_COR_T_20);
				// 200
				os_cor_pt_r[1] = OFF_SET_COR_R_200;
				write_byte(ee_os_cor_r_200, OFF_SET_COR_R_200);
				os_cor_pt_s[1] = OFF_SET_COR_S_200;
				write_byte(ee_os_cor_r_200, OFF_SET_COR_S_200);
				os_cor_pt_t[1] = OFF_SET_COR_T_200;
				write_byte(ee_os_cor_t_200, OFF_SET_COR_T_200);
				// 300
				os_cor_pt_r[2] = OFF_SET_COR_R_300;
				write_byte(ee_os_cor_r_300, OFF_SET_COR_R_300);
				os_cor_pt_s[2] = OFF_SET_COR_S_300;
				write_byte(ee_os_cor_r_300, OFF_SET_COR_S_300);
				os_cor_pt_t[2] = OFF_SET_COR_T_300;
				write_byte(ee_os_cor_t_300, OFF_SET_COR_T_300);
				// 600
				os_cor_pt_r[3] = OFF_SET_COR_R_600;
				write_byte(ee_os_cor_r_600, OFF_SET_COR_R_600);
				os_cor_pt_s[3] = OFF_SET_COR_S_600;
				write_byte(ee_os_cor_r_600, OFF_SET_COR_S_600);
				os_cor_pt_t[3] = OFF_SET_COR_T_600;
				write_byte(ee_os_cor_t_600, OFF_SET_COR_T_600);
				// 1000
				os_cor_pt_r[4]= OFF_SET_COR_R_1000;
				write_byte(ee_os_cor_r_1000, OFF_SET_COR_R_1000);
				os_cor_pt_s[4] = OFF_SET_COR_S_1000;
				write_byte(ee_os_cor_r_1000, OFF_SET_COR_S_1000);
				os_cor_pt_t[4] = OFF_SET_COR_T_1000;
				write_byte(ee_os_cor_t_1000, OFF_SET_COR_T_1000);
				// 1500
				os_cor_pt_r[5]= OFF_SET_COR_R_1500;
				write_byte(ee_os_cor_r_1500, OFF_SET_COR_R_1500);
				os_cor_pt_s[5] = OFF_SET_COR_S_1500;
				write_byte(ee_os_cor_r_1500, OFF_SET_COR_S_1500);
				os_cor_pt_t[5] = OFF_SET_COR_T_1500;
				write_byte(ee_os_cor_t_1500, OFF_SET_COR_T_1500);
				#if (ponteira_kyoritsu == true)
				#else
					// 2000
					os_cor_pt_r[6]= OFF_SET_COR_R_2000;
					write_byte(ee_os_cor_r_2000, OFF_SET_COR_R_2000);
					os_cor_pt_s[6] = OFF_SET_COR_S_2000;
					write_byte(ee_os_cor_r_2000, OFF_SET_COR_S_2000);
					os_cor_pt_t[6] = OFF_SET_COR_T_2000;
					write_byte(ee_os_cor_t_2000, OFF_SET_COR_T_2000);
					// 3000
					os_cor_pt_r[7]= OFF_SET_COR_R_3000;
					write_byte(ee_os_cor_r_3000, OFF_SET_COR_R_3000);
					os_cor_pt_s[7] = OFF_SET_COR_S_3000;
					write_byte(ee_os_cor_r_3000, OFF_SET_COR_S_3000);
					os_cor_pt_t[7] = OFF_SET_COR_T_3000;
					write_byte(ee_os_cor_t_3000, OFF_SET_COR_T_3000);
					// 6000
					os_cor_pt_r[8]= OFF_SET_COR_R_6000;
					write_byte(ee_os_cor_r_6000, OFF_SET_COR_R_6000);
					os_cor_pt_s[8] = OFF_SET_COR_S_6000;
					write_byte(ee_os_cor_r_6000, OFF_SET_COR_S_6000);
					os_cor_pt_t[8] = OFF_SET_COR_T_6000;
					write_byte(ee_os_cor_t_6000, OFF_SET_COR_T_6000);
				#endif
			#endif
			
		#else
			os_cor_r = OFF_SET_COR_R;
			write_byte(ee_os_cor_r, os_cor_r);
			os_cor_s = OFF_SET_COR_S;
			write_byte(ee_os_cor_r, os_cor_s);
			os_cor_t = OFF_SET_COR_T;
			write_byte(ee_os_cor_t, os_cor_t);
		#endif	
		
		os_ten_r1 = OFF_SET_TEN_R1;
		write_byte(ee_os_ten_r1, os_ten_r1);
		os_ten_s1 = OFF_SET_TEN_S1;
		write_byte(ee_os_ten_s1, os_ten_s1);
		os_ten_t1 = OFF_SET_TEN_T1;
		write_byte(ee_os_ten_t1, os_ten_t1);
	
		#if (ade7754 == true)
			
		#else
			off_cor_r = OFF_SET_FP_R;
			write_byte(ee_off_cor_r, off_cor_r);
		#endif
		#if (controlador == true)
			forma_reg_cht = 1;
		#else
			forma_reg_cht = 1;
		#endif
		write_byte(ee_forma_reg_cht, 1);
		#if (home_system == true)
			baud_rate =  19200;
			write_byte(ee_baud_rate, baud_rate);
			endereco = 100;
			write_byte(ee_endereco, 100);
		#else
			baud_rate =  tabela_baud[3];
			write_byte(ee_baud_rate, baud_rate);
			endereco = 1;
			write_byte(ee_endereco, 1);
		#endif
		#if (controlador == false)
			intervalo_reg = INTERVALO_REG_DEFAULT;		
			write_word(ee_intervalo_reg, INTERVALO_REG_DEFAULT);
		#else
			intervalo_reg = INTERVALO_REG_DEFAULT;		
			write_word(ee_intervalo_reg, INTERVALO_REG_DEFAULT);
		#endif		
		intervalo_integra = 15;
		aux_intervalo_integra = 15;
		write_byte(ee_intervalo_integra, 15);
	
		ala_fp_ind = 85;
		write_byte(ee_ala_fp_ind, 85);
		ala_fp_cap = 85;
		write_byte(ee_ala_fp_cap, 85);
		ala_ten_a = 0;
		write_byte(ee_ala_ten_a, 0);
		ala_ten_b = 0;
		write_byte(ee_ala_ten_b, 0);
		ala_sc = 100;
		write_byte(ee_ala_sc, 100);
		ala_subc = 0;
		write_byte(ee_ala_subc, 0);
		ala_chtt = 0;
		write_byte(ee_ala_chtt, 0);
		ala_chtc = 0;
		write_byte(ee_ala_chtc, 0);	
		#if (com_alarme_demanda == true)
			ala_demanda_ativa = 0;
	//		write_word(ee_ala_demanda_ativa, 0);
		#endif
	    	
	    registro = 0;
		write_byte(ee_registro, 1);
		#if (portatil == true)
			prog_time = 0;
			write_byte(ee_prog_time, 0);
			hora_liga = 0;
			write_byte(ee_hora_liga, 0);
			hora_desliga = 23;
			write_byte(ee_hora_desliga, 23);
			minuto_liga = 0;
			write_byte(ee_minuto_liga, 0);
			minuto_desliga = 59;
			write_byte(ee_minuto_desliga, 59);
			dia_liga = 1;
			write_byte(ee_dia_liga, 1);
			dia_desliga = 31;
			write_byte(ee_dia_desliga, 31);
			fila_circular = 1;
			write_byte(ee_fila_circular, 1);
		#endif
		tipo_ligacao = 0;
		write_byte(ee_tipo_ligacao, 0);
	
		#if (controlador == true) || (st_prog == true)
			#if (st8500c == true)
				nro_cargas = NRO_MAXIMO_CARGAS / 2;
				write_byte(ee_nro_cargas, NRO_MAXIMO_CARGAS / 2);
				max_kw = MAXIMA_CARGA;
		 		write_word(ee_max_kw, MAXIMA_CARGA);
				min_kw = 5;
		 		write_byte(ee_min_kw, 5);
			#else
				nro_bancos_capacitor = NRO_MAXIMO_BANCOS_CAPACITOR / 2;
				write_byte(ee_nro_bancos_capacitor, NRO_MAXIMO_BANCOS_CAPACITOR / 2);
				max_kvar = 0;
		 		write_byte(ee_max_kvar,0);
				min_kvar = 5;
		 		write_byte(ee_min_kvar, 5);
		 	#endif
			sequencia = 1;
			calcular_bancos = 1;
	 		write_byte(ee_sequencia, 1);
			tempo_aciona = 30;
	 		write_byte(ee_tempo_aciona, 30);
			tempo_desaciona = 5;
	 		write_byte(ee_tempo_desaciona, 5);
			cor_minima = 2;
	 		write_byte(ee_cor_minima, 2);
	 		#if (com_rep == true)
	 			cor_minima_rep = 0;
	 			write_word(ee_cor_minima_rep, 0);
	 		#endif
			com_des_fp_ind_cap = 100;
	 		write_byte(ee_com_des_fp_ind_cap, 100);
			com_des_ten_a = 0;
	 		write_byte(ee_com_des_ten_a, 0);
			com_des_ten_b = 0;
	 		write_byte(ee_com_des_ten_b, 0);
			com_des_chtt = 0;
	 		write_byte(ee_com_des_chtt, 0);
			com_des_chtc = 0;
	 		write_byte(ee_com_des_chtc, 0);
	 		
			#if (st8500c == true)
				for (aux_b1 = 0; aux_b1 < NRO_MAXIMO_CARGAS; aux_b1++)
					{
					addr = ee_carga_1 + aux_b1;
					carga[aux_b1] = 100;
			 		write_byte(addr, 100);
		
					addr = ee_tempo_repouso_1 + aux_b1;
					tempo_repouso[aux_b1] = 180;
			 		write_byte(addr, 180);
					}
			#else
				for (aux_b1 = 0; aux_b1 < NRO_MAXIMO_BANCOS_CAPACITOR; aux_b1++)
					{
					calcular_bancos = 1;
					
					addr = ee_banco_capacitor_1 + aux_b1;
					banco_capacitor[aux_b1] = 5;
			 		write_byte(addr, 5);
		
					addr = ee_tempo_repouso_1 + aux_b1;
					tempo_repouso[aux_b1] = 180;
			 		write_byte(addr, 180);
					}
			#endif
				
		#endif
		
		#if (com_rep == true)
			if (modo_rep > NRO_MODOS_REP)
				{
				modo_rep = read_byte(ee_modo_rep);
				if (modo_rep > NRO_MODOS_REP)
					{
					#if (st8500c == true)
						modo_rep = 1;
						write_byte(ee_modo_rep, 1);
					#else
						modo_rep = 0;
						write_byte(ee_modo_rep, 0);
					#endif
					}
				}
				
			write_word(ee_fat_conv_ativa, 1000);
			write_word(ee_fat_conv_reativa,1000);
			
		#endif
	
		calcula_checksum_vars();
	    
	}
	
void fixa_parametros(void)
	{
		#if (portatil == true)
			#if (se_com_flex == true)
				os_cor_pt_r[0] = OFF_SET_COR_R_9001G1;
				os_cor_pt_s[0] = OFF_SET_COR_S_9001G1;
				os_cor_pt_t[0] = OFF_SET_COR_T_9001G1;
				// ST9001G2
				os_cor_pt_r[1] = OFF_SET_COR_R_9001G2;
				os_cor_pt_s[1] = OFF_SET_COR_S_9001G2;
				os_cor_pt_t[1] = OFF_SET_COR_T_9001G2;
				// ST9002G1
				os_cor_pt_r[2] = OFF_SET_COR_R_9002G1;
				os_cor_pt_s[2] = OFF_SET_COR_S_9002G1;
				os_cor_pt_t[2] = OFF_SET_COR_T_9002G1;
				// ST9003G1
				os_cor_pt_r[3] = OFF_SET_COR_R_9003G1;
				os_cor_pt_s[3] = OFF_SET_COR_S_9003G1;
				os_cor_pt_t[3] = OFF_SET_COR_T_9003G1;
				// ST9004G1
				os_cor_pt_r[4] = OFF_SET_COR_R_9004G1;
				os_cor_pt_s[4] = OFF_SET_COR_S_9004G1;
				os_cor_pt_t[4] = OFF_SET_COR_T_9004G1;
				// ST9005G1
				os_cor_pt_r[5] = OFF_SET_COR_R_9005G1;
				os_cor_pt_s[5] = OFF_SET_COR_S_9005G1;
				os_cor_pt_t[5] = OFF_SET_COR_T_9005G1;
				// ST9005G2
				os_cor_pt_r[6] = OFF_SET_COR_R_9005G2;
				os_cor_pt_s[6] = OFF_SET_COR_S_9005G2;
				os_cor_pt_t[6] = OFF_SET_COR_T_9005G2;
				// ST9005G3
				os_cor_pt_r[7] = OFF_SET_COR_R_9005G3;
				os_cor_pt_s[7] = OFF_SET_COR_S_9005G3;
				os_cor_pt_t[7] = OFF_SET_COR_T_9005G3;
				// ST9005G4
				os_cor_pt_r[8] = OFF_SET_COR_R_9005G4;
				os_cor_pt_s[8] = OFF_SET_COR_S_9005G4;
				os_cor_pt_t[8] = OFF_SET_COR_T_9005G4;
				// ST9005G5
				os_cor_pt_r[9] = OFF_SET_COR_R_9005G5;
				os_cor_pt_s[9] = OFF_SET_COR_S_9005G5;
				os_cor_pt_t[9] = OFF_SET_COR_T_9005G5;
				// ST9006G1
				os_cor_pt_r[10] = OFF_SET_COR_R_9006G1;
				os_cor_pt_s[10] = OFF_SET_COR_S_9006G1;
				os_cor_pt_t[10] = OFF_SET_COR_T_9006G1;
				// ST9006G2
				os_cor_pt_r[11] = OFF_SET_COR_R_9006G2;
				os_cor_pt_s[11] = OFF_SET_COR_S_9006G2;
				os_cor_pt_t[11] = OFF_SET_COR_T_9006G2;
				// ST9006G3
				os_cor_pt_r[12] = OFF_SET_COR_R_9006G3;
				os_cor_pt_s[12] = OFF_SET_COR_S_9006G3;
				os_cor_pt_t[12] = OFF_SET_COR_T_9006G3;
				// ST9006G4
				os_cor_pt_r[13] = OFF_SET_COR_R_9006G4;
				os_cor_pt_s[13] = OFF_SET_COR_S_9006G4;
				os_cor_pt_t[13] = OFF_SET_COR_T_9006G4;
				// ST9006G5
				os_cor_pt_r[14] = OFF_SET_COR_R_9006G5;
				os_cor_pt_s[14] = OFF_SET_COR_S_9006G5;
				os_cor_pt_t[14] = OFF_SET_COR_T_9006G5;
				// ST9007G1
				os_cor_pt_r[15] = OFF_SET_COR_R_9007G1;
				os_cor_pt_s[15] = OFF_SET_COR_S_9007G1;
				os_cor_pt_t[15] = OFF_SET_COR_T_9007G1;
				// ST9007G2
				os_cor_pt_r[16] = OFF_SET_COR_R_9007G2;
				os_cor_pt_s[16] = OFF_SET_COR_S_9007G2;
				os_cor_pt_t[16] = OFF_SET_COR_T_9007G2;
				// ST9008G1
				os_cor_pt_r[17] = OFF_SET_COR_R_9008G1;
				os_cor_pt_s[17] = OFF_SET_COR_S_9008G1;
				os_cor_pt_t[17] = OFF_SET_COR_T_9008G1;
	//		
			#elif (viercon == true)	
				// 30
				os_cor_pt_r[0] = OFF_SET_COR_R_20;
				os_cor_pt_s[0] = OFF_SET_COR_S_20;
				os_cor_pt_t[0] = OFF_SET_COR_T_20;
				// 300
				os_cor_pt_r[1] = OFF_SET_COR_R_200;
				os_cor_pt_s[1] = OFF_SET_COR_S_200;
				os_cor_pt_t[1] = OFF_SET_COR_T_200;
				// 3000
				os_cor_pt_r[2] = OFF_SET_COR_R_300;
				os_cor_pt_s[2] = OFF_SET_COR_S_300;
				os_cor_pt_t[2] = OFF_SET_COR_T_300;
			#else
				// 20
				os_cor_pt_r[0] = OFF_SET_COR_R_20;
				os_cor_pt_s[0] = OFF_SET_COR_S_20;
				os_cor_pt_t[0] = OFF_SET_COR_T_20;
				// 200
				os_cor_pt_r[1] = OFF_SET_COR_R_200;
				os_cor_pt_s[1] = OFF_SET_COR_S_200;
				os_cor_pt_t[1] = OFF_SET_COR_T_200;
				// 300
				os_cor_pt_r[2] = OFF_SET_COR_R_300;
				os_cor_pt_s[2] = OFF_SET_COR_S_300;
				os_cor_pt_t[2] = OFF_SET_COR_T_300;
				// 600
				os_cor_pt_r[3] = OFF_SET_COR_R_600;
				os_cor_pt_s[3] = OFF_SET_COR_S_600;
				os_cor_pt_t[3] = OFF_SET_COR_T_600;
				// 1000
				os_cor_pt_r[4]= OFF_SET_COR_R_1000;
				os_cor_pt_s[4] = OFF_SET_COR_S_1000;
				os_cor_pt_t[4] = OFF_SET_COR_T_1000;
				// 1500
				os_cor_pt_r[5]= OFF_SET_COR_R_1500;
				os_cor_pt_s[5] = OFF_SET_COR_S_1500;
				os_cor_pt_t[5] = OFF_SET_COR_T_1500;
				#if (ponteira_kyoritsu == true)
				#else
					// 2000
					os_cor_pt_r[6]= OFF_SET_COR_R_2000;
					os_cor_pt_s[6] = OFF_SET_COR_S_2000;
					os_cor_pt_t[6] = OFF_SET_COR_T_2000;
					// 3000
					os_cor_pt_r[7]= OFF_SET_COR_R_3000;
					os_cor_pt_s[7] = OFF_SET_COR_S_3000;
					os_cor_pt_t[7] = OFF_SET_COR_T_3000;
					// 6000
					os_cor_pt_r[8]= OFF_SET_COR_R_6000;
					os_cor_pt_s[8] = OFF_SET_COR_S_6000;
					os_cor_pt_t[8] = OFF_SET_COR_T_6000;
				#endif
			#endif
		#else
		
			os_cor_r = OFF_SET_COR_R;
			os_cor_s = OFF_SET_COR_S;
			os_cor_t = OFF_SET_COR_T;
		
		#endif	
		os_ten_r1 = OFF_SET_TEN_R1;
		os_ten_s1 = OFF_SET_TEN_S1;
		os_ten_t1 = OFF_SET_TEN_T1;
	
	#if (ade7754 == true)
	
	#else
		off_cor_r = OFF_SET_FP_R;
	//	off_cor_s = OFF_SET_FP_S;
	//	off_cor_t = OFF_SET_FP_S;
	
	#endif    	
		calcula_checksum_vars();
	 
	
	}

/* Fim st_vali */
