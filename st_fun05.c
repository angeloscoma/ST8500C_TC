/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_fun05                                                        *
; Funcao: MODULO gerencial de funções 05 modbus					 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */


void modbus_funcao05(void)
{
	le_endereco();
	le_forcedata();

    erro_mod = 0;
	qerro_mod = 0;

	data1_int = addr_regs_modbus;
 	poe_word_buftx();
				 	
	data1_int = force_data_modbus;
 	poe_word_buftx();

	#if (st5x == true)
		if (force_data_modbus == 0x1010)
			{
			switch(addr_regs_modbus)
				{
		 	    case 0:
		 	    	{
					if (bloqueio_gravacao == 67)
						{
						bloqueio_gravacao = 0;
						}
					else
						{
						bloqueio_gravacao = 67;
						}
					write_byte(ee_bloqueio_gravacao, bloqueio_gravacao);
					break;
					}
			 	default:
			 		{
		 		    erro_mod = 1;
		 			qerro_mod = 2;
			 		}
				}
			}
		else if (force_data_modbus == 0xff00)
	#else
		if (force_data_modbus == 0xff00)
	#endif
		{
		switch(addr_regs_modbus)
			{
	 	    case 0:  		/* reset equipamento */
	 	    	{
				crc_modbus =  crc16(buf_tx, ptrtx, 'M');
				data1_int = crc_modbus;
				poe_word_buftx();
				dispara_tx();
				var_mem = 0;
				while(1)
					{
					reset_cpu();
					}
	 	    	}
                break;
	 	    case 1:
	 	    	{
				#if (com_regs == true)
		 	    	if (registro == 0)
		 	    		{
						registro = 1;
						write_byte(ee_registro, registro);
						grava_registros(reg_inicio);
						#if (portatil == true)
							calcula_autonomia();
							encerra_menus();
						#endif
			 	 	   }
				#endif			 	    
			 	break;
		 	    }
	 	    case 2:
	 	    	{
				#if (com_regs == true)
		 	    	if (registro == 1)
		 	    		{
						grava_registros(reg_final);
						registro = 0;
						write_byte(ee_registro, registro);
						#if (portatil == true)
							calcula_autonomia();
							encerra_menus();
						#endif
			 	    	}
				#endif			 	    
			 	break;
		 	    }
		 	#if (st8500c == true)
		 		case 9:
		 			{
			 		if (fprintar == true)
			 			{
				 		fprintar = false;
				 		}
				 	else
				 		{
					 	fprintar = true;
						output_high(direcao);
						delay_ms(1);
						printf("Printar REP TRUE!!!\r\n");
						delay_ms(1);
						output_low(direcao);
					 	}
					 break;
			 		}
		 	#endif
	 	    case 10:
	 	    	{
				#if (com_regs == true)
	 	    		apaga_registros();
				#endif	 	    	
	            break;
	 	    	}
	 	    case 100:
	 	    	{
				#if (com_regs == true)
					apaga_ocorrencias();
				#endif				
	 	    	break;
	 	    	}
	 	    case 1000:
		    	{
				#if (com_regs == true)
					#if (com_cht == true)
		 	    		apaga_cht();
					#endif
				#endif
	 	    	break;
	 	    	}
	 	    case 1001:
	 	    	{
				#if (com_consumo == true) && (st8500c == false)
	 	    		zera_consumo();
				#elif (st8500c == true)
					#if (com_tc == true)
						#if (com_rep == true)
							if (modo_rep == true)
								{
				 	    		zera_consumo_rep();
								}
							else
								{
				 	    		zera_consumo();
								}
						#else
			 	    		zera_consumo();
						#endif
					#else
	 	    			zera_consumo_rep();
	 	    		#endif
				#endif	 	    	
	 	    	break;
	 	    	}
	 	    case 999:
	 	    	{
    	 	    assume_defaults();	
	 	    	break;
	 	    	}
	 	    case 1010:
	 	    	{
	 	    	output_high(alarme);
	 	    	tem_alarme = 1;
				tem_comando_alarme = 1;
				#if (st5x == true)
					fled_alarme = 0;
					status_flags = 13;
				#endif		
	 	    	break;
	 	    	}
	 	    #if (controlador == true)
				#if (DESLIGA_F5 == true)
			 	    case 1011:		//1
			 	    case 1012:		//2
			 	    case 1013:		//3
			 	    case 1014:		//4
			 	    case 1015:		//5
			 	    case 1016:		//6
			 	    case 1017:		//7
			 	    case 1018:		//8
			 	    case 1019:		//9
			 	    case 1020:		//10
			 	    case 1021:		//11
			 	    case 1022:		//12
			 	    case 1023:		//13
			 	    case 1024:		//14
			 	    case 1025:		//15
			 	    case 1026:		//16
			 	    	{
				 	    aux_b1 = addr_regs_modbus - 1011;
				 	    #if (st8500c == true)
				 	    	aux_tempo_repouso[aux_b1] = 0;
							ligar_carga(aux_b1);		
				 	    #else
							banco_disponivel[aux_b1]= true;
							if (aux_b1 >= nro_bancos_capacitor)
								{
								aux_tempo_repouso[aux_b1] = 0;
								}
							ligar_banco(aux_b1);		
						#endif
						break;
				 	    }
			 	    case 1031:		//1
			 	    case 1032:		//2
			 	    case 1033:		//3
			 	    case 1034:		//4
			 	    case 1035:		//5
			 	    case 1036:		//6
			 	    case 1037:		//7
			 	    case 1038:		//8
			 	    case 1039:		//9
			 	    case 1040:		//10
			 	    case 1041:		//11
			 	    case 1042:		//12
			 	    case 1043:		//13
			 	    case 1044:		//14
			 	    case 1045:		//15
			 	    case 1046:		//16
			 	    	{
				 	    aux_b1 = addr_regs_modbus - 1031;
				 	    #if (st8500c == true)
							desligar_carga(aux_b1);		
				 	    #else
							desligar_banco(aux_b1);		
						#endif
						break;
				 	    }
				#endif
			#endif
	 	    case 1101:
	 	    case 1110:
	 	    case 1111:
	 	    case 2001:
	 	    case 2002:
	 	    	{
	 	    	break;
	 	    	}
	 	    case 2000:
	 	    	{
				#if (chip_cs5460a == true)
					inc_off_set_fp_cs5460a('R');
				#elif (ade7754 == true)
					inc_fase_fp_7754('R');
				#else
					#if (portatil == TRUE)
						ajusta_off_set_fp();
					#else
						if (distancia_fase == NRO_AMOSTRAS)
							{
							distancia_fase = 0;
							}
						off_cor_r = distancia_fase;
						write_byte(ee_off_cor_r, off_cor_r);
					#endif
				#endif
	 	    	break;
	 	    	}
			#if (chip_cs5460a == true)
		 	    case 2001:
		 	    	{
					inc_off_set_fp_cs5460a('S');
	 	    		break;
					}
	 	    	case 2002:
	 	    		{
					inc_off_set_fp_cs5460a('T');
	 	    		break;
					}
			#endif
	 	    case 2003:
	 	    case 2006:
	 	    	{
				#if (chip_cs5460a == true)
					inc_ganho_v_cs5460a('R');
				#else
					#if (portatil == true)
						if (tipo_ligacao == 0)
							{
							os_ten_r1++;
							write_byte(ee_os_ten_r1, os_ten_r1);
							}
						else
							{
							os_ten_r1++;
							write_byte(ee_os_ten_r1, os_ten_r1);
							}
					#else
						os_ten_r1++;
						write_byte(ee_os_ten_r1, os_ten_r1);
					#endif
				#endif
	 	    	break;
				}
	 	    case 2004:
	 	    case 2007:
	 	    	{
				#if (chip_cs5460a == true)
					inc_ganho_v_cs5460a('S');
				#else
					#if (portatil == true)
						if (tipo_ligacao == 0)
							{
							os_ten_s1++;
							write_byte(ee_os_ten_s1, os_ten_s1);
							}
						else
							{
							os_ten_s1++;
							write_byte(ee_os_ten_s1, os_ten_s1);
							}
					#else
						os_ten_s1++;
						write_byte(ee_os_ten_s1, os_ten_s1);
					#endif
				#endif
	 	    	break;
				}
	 	    case 2005:
	 	    case 2008:
	 	    	{
				#if (chip_cs5460a == true)
					inc_ganho_v_cs5460a('T');
				#else
					#if (portatil == true)
						if (tipo_ligacao == 0)
							{
							os_ten_t1++;
							write_byte(ee_os_ten_t1, os_ten_t1);
							}
						else
							{
							os_ten_r1++;
							write_byte(ee_os_ten_t1, os_ten_t1);
							}
					#else
						os_ten_r1++;
						write_byte(ee_os_ten_t1, os_ten_t1);
					#endif
				#endif
	 	    	break;
				}
	 	    case 2009:
	 	    	{
				#if (portatil == true)
					ajusta_off_set_cor_r(1);
				#else		 	    	
					#if (chip_cs5460a == true)
						inc_ganho_i_cs5460a('R');
					#else
						os_cor_r++;
						write_byte(ee_os_cor_r, os_cor_r);
					#endif
				#endif				

	 	    	break;
				}
	 	    case 2010:
	 	    	{
				#if (portatil == true)
					ajusta_off_set_cor_s(1);
				#else		 	    	
					#if (chip_cs5460a == true)
						inc_ganho_i_cs5460a('S');
					#else
						os_cor_s++;
						write_byte(ee_os_cor_s, os_cor_s);
					#endif
				#endif				
	 	    	break;
				}
	 	    case 2011:
	 	    	{
				#if (portatil == true)
					ajusta_off_set_cor_t(1);
				#else		 	    	
					#if (chip_cs5460a == true)
						inc_ganho_i_cs5460a('T');
					#else
						os_cor_t++;
						write_byte(ee_os_cor_t, os_cor_t);
					#endif
				#endif				
	 	    	break;
				}
			#if (chip_cs5460a == true)
				case 2012:
					{
					inc_tbc_register('R');
		 	    	break;
					}
				case 2013:
					{
					inc_tbc_register('S');
		 	    	break;
					}
				case 2014:
					{
					inc_tbc_register('T');
		 	    	break;
					}
		 	    case 2015:
		 	    	{
					inc_pulse_rate_cs5460a('R');
		 	    	break;
					}
		 	    case 2016:
		 	    	{
					inc_pulse_rate_cs5460a('S');
		 	    	break;
					}
		 	    case 2017:
		 	    	{
					inc_pulse_rate_cs5460a('T');
		 	    	break;
					}
			#endif
			case 2050:
				{
				#if (portatil == true)
					ajusta_off_set_pot_r(1);
				#else		 	    	
					os_pot_r++;
					write_byte(ee_os_pot_r, os_pot_r);
				#endif
				break;
				}
			case 2051:
				{
				#if (portatil == true)
					ajusta_off_set_pot_s(1);
				#else		 	    	
					os_pot_s++;
					write_byte(ee_os_pot_s, os_pot_s);
				#endif
				break;
				}
			case 2052:
				{
				#if (portatil == true)
					ajusta_off_set_pot_t(1);
				#else		 	    	
					os_pot_t++;
					write_byte(ee_os_pot_t, os_pot_t);
				#endif
				break;
				}
				
			#if (chip_cs5460a == true)
				case 3000:				// calibra off_set DC e AC de tensao corrente   
				write_word(ee_reg_cfnum, reg_cfnum);				{

				output_low(CS5460A_CS_R);
				output_low(CS5460A_CS_S);
				output_low(CS5460A_CS_T);
				write_cs5460_byte(I_dc_calibra_offset);
				output_high(CS5460A_CS_R);
				output_high(CS5460A_CS_S);
				output_high(CS5460A_CS_T);

				time_out = 1;
				while(1)
					{
					aux_cs5460_l = read_cs5460(status_cs5460a,'R');	
					if (bit_test(datah,7))
						{
						break;
						}
					if (time_out == 0)
						{
						break;
						}
					}

				output_low(CS5460A_CS_R);
				output_low(CS5460A_CS_S);
				output_low(CS5460A_CS_T);
				write_cs5460_byte(V_dc_calibra_offset);
				output_high(CS5460A_CS_R);
				output_high(CS5460A_CS_S);
				output_high(CS5460A_CS_T);

				time_out = 1;
				while(1)
					{
					aux_cs5460_l = read_cs5460(status_cs5460a,'R');	
					if (bit_test(datah,7))
						{
						break;
						}
					if (time_out == 0)
						{
						break;
						}
					}

				output_low(CS5460A_CS_R);
				output_low(CS5460A_CS_S);
				output_low(CS5460A_CS_T);
				write_cs5460_byte(start_conversions);
				output_high(CS5460A_CS_R);
				output_high(CS5460A_CS_S);
				output_high(CS5460A_CS_T);
				delay_ms(1000);

				aux_cs5460_l = read_cs5460(I_dc_offset,'R');
				write_byte(ee_I_dc_offset_h, datah);
				write_byte(ee_I_dc_offset_m, datam);
				write_byte(ee_I_dc_offset_l, datal);

				aux_cs5460_l = read_cs5460(V_dc_offset,'R');
				write_byte(ee_V_dc_offset_h, datah);
				write_byte(ee_V_dc_offset_m, datam);
				write_byte(ee_V_dc_offset_l, datal);


				break;
				}
			case 3001:				// calibra ganho DC de tensao
				{

				output_low(CS5460A_CS_R);
				output_low(CS5460A_CS_S);
				output_low(CS5460A_CS_T);
				write_cs5460_byte(I_ac_calibra_offset);
				output_high(CS5460A_CS_R);
				output_high(CS5460A_CS_S);
				output_high(CS5460A_CS_T);

				time_out = 1;
				while(1)
					{
					aux_cs5460_l = read_cs5460(status_cs5460a,'R');	
					if (bit_test(datah,7))
						{
						break;
						}
					if (time_out == 0)
						{
						break;
						}
					}

				output_low(CS5460A_CS_R);
				output_low(CS5460A_CS_S);
				output_low(CS5460A_CS_T);
				write_cs5460_byte(V_ac_calibra_offset);
				output_high(CS5460A_CS_R);
				output_high(CS5460A_CS_S);
				output_high(CS5460A_CS_T);

				time_out = 1;
				while(1)
					{
					aux_cs5460_l = read_cs5460(status_cs5460a,'R');	
					if (bit_test(datah,7))
						{
						break;
						}
					if (time_out == 0)
						{
						break;
						}
					}

				output_low(CS5460A_CS_R);
				output_low(CS5460A_CS_S);
				output_low(CS5460A_CS_T);
				write_cs5460_byte(start_conversions);
				output_high(CS5460A_CS_R);
				output_high(CS5460A_CS_S);
				output_high(CS5460A_CS_T);
				delay_ms(1000);

				aux_cs5460_l = read_cs5460(I_ac_offset,'R');
				write_byte(ee_I_ac_offset_h, datah);
				write_byte(ee_I_ac_offset_m, datam);
				write_byte(ee_I_ac_offset_l, datal);

				aux_cs5460_l = read_cs5460(V_ac_offset,'R');
				write_byte(ee_V_ac_offset_h, datah);
				write_byte(ee_V_ac_offset_m, datam);
				write_byte(ee_V_ac_offset_l, datal);


				break;
				}

			case 3002:				// calibra ganho DC de corrente   
				{
				break;
				}

			case 3003:
				{
				break;
				}
			case 3004:
				{
				break;
				}

			case 3005:				// calibra off_set DC e AC de tensao  
				{
				
				write_cs5460(V_ac_offset, 0, 'R');
				for (aux_b4 = 0; aux_b4< 250; aux_b4++)
					{
					aux_ten_l = read_cs5460(V_rms,'R');
					aux_l1 = aux_ten_l >> 8;
					if (aux_l1 > 10)
						{
						aux_cs5460_l = read_cs5460(V_ac_offset,'R');	
						aux_cs5460_l = aux_cs5460_l - 10;
						}
					else
						{
						break;
						}
					write_cs5460(V_ac_offset, aux_cs5460_l, 'R');

					output_low(CS5460A_CS_R);
					write_cs5460_byte(start_conversions);
					output_high(CS5460A_CS_R);
					delay_ms(1000);

					output_high(direcao);
					delay_ms(1);
					aux_cs5460_l = read_cs5460(V_ac_offset,'R');	
					printf(" Tensao=%lu,; AC_Off_set_V=%lu", (aux_ten_l >> 8), aux_cs5460_l);
					printf("\r\n");
					delay_ms(2);
					output_low(direcao);
					}

				aux_cs5460_l = read_cs5460(V_dc_offset,'R');
				write_byte(ee_V_dc_offset_h, datah);
				write_byte(ee_V_dc_offset_m, datam);
				write_byte(ee_V_dc_offset_l, datal);

				aux_cs5460_l = read_cs5460(V_ac_offset,'R');
				write_byte(ee_V_ac_offset_h, datah);
				write_byte(ee_V_ac_offset_m, datam);
				write_byte(ee_V_ac_offset_l, datal);

				break;
				}

			case 3006:				// calibra off_set DC e AC de corrente
				{
				
				write_cs5460(I_ac_offset, 0, 'R');
				for (aux_b4 = 0; aux_b4< 250; aux_b4++)
					{
					aux_cor_l = read_cs5460(I_rms,'R');
					aux_l1 = aux_cor_l >> 8;
					if (aux_l1 > 10)
						{
						aux_cs5460_l = read_cs5460(I_ac_offset,'R');	
						aux_cs5460_l = aux_cs5460_l - 10;
						}
					else
						{
						break;
						}
					write_cs5460(I_ac_offset, aux_cs5460_l, 'R');

					output_low(CS5460A_CS_R);
					write_cs5460_byte(start_conversions);
					output_high(CS5460A_CS_R);
					delay_ms(1000);

					output_high(direcao);
					delay_ms(1);
					aux_cs5460_l = read_cs5460(I_ac_offset,'R');	
					printf(" Corrente=%lu,; AC_Off_set_I=%lu", (aux_cor_l >> 8), aux_cs5460_l);
					printf("\r\n");
					delay_ms(2);
					output_low(direcao);
					}

				aux_cs5460_l = read_cs5460(I_dc_offset,'R');
				write_byte(ee_I_dc_offset_h, datah);
				write_byte(ee_I_dc_offset_m, datam);
				write_byte(ee_I_dc_offset_l, datal);

				aux_cs5460_l = read_cs5460(I_ac_offset,'R');
				write_byte(ee_I_ac_offset_h, datah);
				write_byte(ee_I_ac_offset_m, datam);
				write_byte(ee_I_ac_offset_l, datal);

				break;
				}

			case 3007:				// calibra off_set DC e AC de corrente
				{
				for (aux_b4 = 0; aux_b4< 5; aux_b4++)
					{
					aux_ener_l = read_cs5460(E_register, 'R');
					if (aux_ener_l != 0)
						{
						if (datah & 0x80)
							{
							aux_cs5460_l = read_cs5460(P_offset, 'R');	
							aux_cs5460_l = aux_cs5460_l + 100;
							aux_cs5460_l++;
							write_cs5460(P_offset, aux_cs5460_l, 'R');
							}
						else
							{
							aux_cs5460_l = read_cs5460(P_offset, 'R');	
							aux_cs5460_l = aux_cs5460_l - 100;
							aux_cs5460_l--;
							write_cs5460(P_offset, aux_cs5460_l, 'R');
							}
						}
					else
						{
						break;
						}
					output_low(CS5460A_CS_R);
					write_cs5460_byte(start_conversions);
					output_high(CS5460A_CS_R);
					delay_ms(1000);

					output_high(direcao);
					delay_ms(1);
					printf(" E_register=%lu,; P_Off_set=%lu",  read_cs5460(E_register,'R'),  read_cs5460(P_offset,'R'));
					printf("\r\n");
					delay_ms(2);
					output_low(direcao);
					}

				aux_cs5460_l = read_cs5460(P_offset,'R');
				write_byte(ee_P_offset_h, datah);
				write_byte(ee_P_offset_m, datam);
				write_byte(ee_P_offset_l, datal);

				break;
				}

			case 3008:
				{
				inc_off_set_fp_cs5460a('R');
				break;
				}

			case 3009:
				{
				dec_off_set_fp_cs5460a('R');
				break;
				}

			case 3900:
				{
				tx_config_cs55460('R');
				break;
				}
			case 3901:
				{
				tx_config_cs55460('S');
				break;
				}
			case 3902:
				{
				tx_config_cs55460('T');
				break;
				}
			case 3903:
				{
				output_high(direcao);
				delay_ms(1);
				for (aux_b4 = 0;aux_b4 <= NRO_AMOSTRAS_CHT; aux_b4++)
					{
					printf("%lu", read_word_cs5460(V_register,'R'));
					printf("\r\n");
					delay_us(130);
					}
				printf("\r\n");
				delay_ms(2);
				output_low(direcao);
				break;
				}
			case 3999:
				{
				
				output_high(direcao);
				delay_ms(1);
				aux_cs5460_l = read_cs5460(V_dc_offset,'R');	
				printf(" Vdc_Off_set_V=%lu", aux_cs5460_l);
				aux_cs5460_l = read_cs5460(V_ac_offset,'R');	
				printf("; Vac_Off_set_V=%lu", aux_cs5460_l);
				aux_cs5460_l = read_cs5460(V_gain,'R');	
				printf("; V_Ganho=%lu", aux_cs5460_l);
				printf("\r\n");
				delay_ms(2);
				output_low(direcao);
				break;
				}
			#endif

			#if (st5x == true)
		 	    case 6779:
		 	    	{
					if (bloqueio_gravacao == 67)
						{
						bloqueio_gravacao = 0;
						}
					else
						{
						bloqueio_gravacao = 67;
						}
					write_byte(ee_bloqueio_gravacao, bloqueio_gravacao);
					break;
					}
			#endif
			
			case 8000:{
//				GravarRegistrosTest();
				teste_memoria();
			 	break;
			}			

			#if (controlador == true)
				case 9000:
					{
					apaga_tempos();
					break;
					}
			#endif

			#if (ade7754 == true)
		 	    case 9990:
		 	    	{
					reg_cfnum = read_word(ee_reg_cfnum);
					reg_cfnum++;
					write_word(ee_reg_cfnum, reg_cfnum);
					break;
					}
		 	    case 9991:
		 	    	{
					reg_cfdem = read_word(ee_reg_cfdem);
					reg_cfdem++;
					write_word(ee_reg_cfdem, reg_cfdem);
					break;
					}
		 	    case 9992:
		 	    	{
					os_pot_r = read_byte(xee_os_pot_r);
					os_pot_r++;
					write_byte(xee_os_pot_r, os_pot_r);
					acao_ade7754 = 0;
					break;
					}
		 	    case 9993:
		 	    	{
					os_pot_s = read_byte(xee_os_pot_s);
					os_pot_s++;
					write_byte(xee_os_pot_s, os_pot_s);
					acao_ade7754 = 0;
					break;
					}
		 	    case 9994:
		 	    	{
					os_pot_t = read_byte(xee_os_pot_t);
					os_pot_t++;
					write_byte(xee_os_pot_r, os_pot_t);
					acao_ade7754 = 0;
					break;
					}
			#endif
	 	    case 9999:
	 	    	{
				#if (com_regs == true)
					apaga_memoria();
				#endif
			 	break;
		 	    }
		 	 default:
		 		{
	 		    erro_mod = 1;
	 			qerro_mod = 2;
		 		}
	 		}
	 	}
	else if (force_data_modbus == 0x00ff)
		{
		switch(addr_regs_modbus)
			{
	 	    case 1:
	 	    	{
				#if (com_regs == true)
		 	    	if (registro == 0)
		 	    		{
						registro = 1;
						write_byte(ee_registro, registro);
						grava_registros(reg_inicio);
						#if (portatil == true)
							calcula_autonomia();
							encerra_menus();
						#endif
				 	    }
				#endif
			 	break;
		 	    }
	 	    case 2:
	 	    	{
				#if (com_regs == true)
			 	    if (registro == 1)
			 	    	{
						grava_registros(reg_final);
						registro = 0;
						write_byte(ee_registro, registro);
						#if (portatil == true)
							calcula_autonomia();
							encerra_menus();
						#endif
				 	    }
				#endif
			 	break;
		 	    }
	 	    case 1010:
	 	    	{
	 	    	output_low(alarme);
	 	    	tem_alarme = 0;
				tem_comando_alarme = 1;
				#if (st5x == true)
					fled_alarme = 1;
				#endif		
	 	    	break;
	 	    	}
	 	    #if (controlador == true)
				#if (DESLIGA_F5 == true)
			 	    case 1011:		//1
			 	    case 1012:		//2
			 	    case 1013:		//3
			 	    case 1014:		//4
			 	    case 1015:		//5
			 	    case 1016:		//6
			 	    case 1017:		//7
			 	    case 1018:		//8
			 	    case 1019:		//9
			 	    case 1020:		//10
			 	    case 1021:		//11
			 	    case 1022:		//12
			 	    case 1023:		//13
			 	    case 1024:		//14
			 	    case 1025:		//15
			 	    case 1026:		//16
			 	    	{
				 	    aux_b1 = addr_regs_modbus - 1011;
				 	    #if (st8500c == true)
							desligar_carga(aux_b1);		
				 	    #else
							desligar_banco(aux_b1);		
						#endif
						break;
				 	    }
				#endif
			#endif
	 	    	
	 	    case 2000:
	 	    	{
				#if (chip_cs5460a == true)
						dec_off_set_fp_cs5460a('R');
				#elif (ade7754 == true)
						dec_fase_fp_7754('R');
				#else
					#if (portatil == TRUE)
						ajusta_off_set_fp();
					#else
						off_cor_r = distancia_fase;
						write_byte(ee_off_cor_r, off_cor_r);
					#endif
				#endif
	 	    	break;
	 	    	}
			#if (chip_cs5460a == true)
		 	    case 2001:
		 	    	{
					dec_off_set_fp_cs5460a('S');
	 		    	break;
					}
		 	    case 2002:
		 	    	{
					dec_off_set_fp_cs5460a('T');
		 	    	break;
					}
			#else
		 	    case 2001:
		 	    case 2002:
		 	    	{
		 	    	break;
					}
			#endif
	 	    case 2003:
	 	    case 2006:
	 	    	{
				#if (chip_cs5460a == true)
					dec_ganho_v_cs5460a('R');
				#else
					os_ten_r1--;
					write_byte(ee_os_ten_r1, os_ten_r1);
				#endif
	 	    	break;
				}
	 	    case 2004:
	 	    case 2007:
	 	    	{
				#if (chip_cs5460a == true)
					dec_ganho_v_cs5460a('S');
				#else
					os_ten_s1--;
					write_byte(ee_os_ten_s1, os_ten_s1);
				#endif
	 	    	break;
				}
	 	    case 2005:
	 	    case 2008:
	 	    	{
				#if (chip_cs5460a == true)
					dec_ganho_v_cs5460a('T');
				#else
					os_ten_t1--;
					write_byte(ee_os_ten_t1, os_ten_t1);
				#endif
	 	    	break;
				}
	 	    case 2009:
	 	    	{
				#if (portatil == true)
					ajusta_off_set_cor_r(-1);
				#else		 	    	
					#if (chip_cs5460a == true)
						dec_ganho_i_cs5460a('R');
					#else
						os_cor_r--;
						write_byte(ee_os_cor_r, os_cor_r);
					#endif
				#endif				
	 	    	break;
				}
	 	    case 2010:
	 	    	{
				#if (portatil == true)
					ajusta_off_set_cor_s(-1);
				#else		 	    	
					#if (chip_cs5460a == true)
						dec_ganho_i_cs5460a('S');
					#else
						os_cor_s--;
						write_byte(ee_os_cor_s, os_cor_s);
					#endif
				#endif				
	 	    	break;
				}
	 	    case 2011:
	 	    	{
				#if (portatil == true)
					ajusta_off_set_cor_t(-1);
				#else		 	    	
					#if (chip_cs5460a == true)
						dec_ganho_i_cs5460a('T');
					#else
						os_cor_t--;
						write_byte(ee_os_cor_t, os_cor_t);
					#endif
				#endif				
	 	    	break;
				}
			case 2012:
				#if (chip_cs5460a == true)
					{
					dec_tbc_register('R');
		 	    	break;
					}
				case 2013:
					{
					dec_tbc_register('S');
		 	    	break;
					}
				case 2014:
					{
					dec_tbc_register('T');
		 	    	break;
					}
		 	    case 2015:
		 	    	{
					dec_pulse_rate_cs5460a('R');
		 	    	break;
					}
		 	    case 2016:
		 	    	{
					dec_pulse_rate_cs5460a('S');
		 	    	break;
					}
		 	    case 2017:
		 	    	{
					dec_pulse_rate_cs5460a('T');
		 	    	break;
					}
	
			#endif

			case 2050:
				{
				#if (portatil == true)
					ajusta_off_set_pot_r(-1);
				#else		 	    	
					os_pot_r--;
					write_byte(ee_os_pot_r, os_pot_r);
				#endif
				
				#if (ade7754 == true)
					acao_ade7754 = 0;
				#endif
				break;
				}
			case 2051:
				{
				#if (portatil == true)
					ajusta_off_set_pot_s(-1);
				#else		 	    	
					os_pot_s--;
					write_byte(ee_os_pot_s, os_pot_s);
				#endif

				#if (ade7754 == true)
					acao_ade7754 = 0;
				#endif
				break;
				}
			case 2052:
				{
				#if (portatil == true)
					ajusta_off_set_pot_t(-1);
				#else		 	    	
					os_pot_t--;
					write_byte(ee_os_pot_t, os_pot_t);
				#endif

				#if (ade7754 == true)
					acao_ade7754 = 0;
				#endif
				break;
				}
			#if (st5x == true)
		 	    case 6779:
		 	    	{
					if (bloqueio_gravacao == 67)
						{
						bloqueio_gravacao = 0;
						}
					else
						{
						bloqueio_gravacao = 67;
						}
					write_byte(ee_bloqueio_gravacao, bloqueio_gravacao);
					break;
					}
			#endif

			case 8000:{
//				GravarRegistrosTest();
				teste_memoria();
			 	break;
			}

			#if (controlador == true)
				case 9000:
					{
					apaga_tempos();
					break;
					}
			#endif


			#if (ade7754 == true)
		 	    case 9990:
		 	    	{
					reg_cfnum = read_word(ee_reg_cfnum);
					reg_cfnum--;
					write_word(ee_reg_cfnum, reg_cfnum);
					break;
					}
		 	    case 9991:
		 	    	{
					reg_cfdem = read_word(ee_reg_cfdem);
					reg_cfdem--;
					write_word(ee_reg_cfdem, reg_cfdem);
					break;
					}
			#endif
			#if (com_regs == true)
	 	    	case 9999:
	 	    		{
					apaga_memoria();
				 	break;
		 		    }
			#endif
		 	 default:
		 		{
	 		    erro_mod = 1;
	 			qerro_mod = 2;
		 		}
	 		}
		}

 	if (erro_mod == 1)
 		{
		buf_tx[1] = buf_tx[1] | 0x80;
		buf_tx[2] = qerro_mod;
		ptrtx = 3;
 		}
		
	crc_modbus =  crc16(buf_tx, ptrtx, 'M');
	data1_int = crc_modbus;
	poe_word_buftx();
	dispara_tx();
}

