/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRONICOS                                  *
; Modulo: ST_FUNC                                                        *
; Funcao: MODULO gerencial funcoes de comunicacao modbus				 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */
  
#define comandos_teste	true

/* variaveis do protocolo modbus */
#if (portatil == true)
	void busca_os_cor_pt_r(char);
	void busca_os_cor_pt_s(char);
	void busca_os_cor_pt_t(char);
	void busca_os_pot_pt_r(char);
	void busca_os_pot_pt_s(char);
	void busca_os_pot_pt_t(char);
#endif



void poe_word_buftx(void)
{
	buf_tx[ptrtx++] = data1_int >> 8;
	buf_tx[ptrtx++] = data1_int;
}

void poe_byte_buftx(void)
{
	buf_tx[ptrtx++] = data1;
}


word le_word_buf_modbus(void)
{
	char datal = 0;
	char datah = 0;
	if (retrx!=ptrrx)
		{
		datah = ret_ser();
		if (retrx!=ptrrx)
			{
			datal = ret_ser();
			}
		}
	return(make16(datah, datal));

}

void le_forcedata(void)
{
	force_data_modbus = le_word_buf_modbus();
}

void le_endereco(void)
{
	addr_regs_modbus = le_word_buf_modbus();
}

void le_nro_regs(void)
{
	nro_regs_modbus = le_word_buf_modbus();;
}

void le_nro_pontos(void)
{
	nro_pontos_modbus = le_word_buf_modbus();
	if (nro_pontos_modbus > 124)
		{
		nro_pontos_modbus = 124;
		}
}

void le_byte_count(void)
{
	data_count_modbus=0;
	if (retrx!=ptrrx)
		{
		addr_modbus = ret_ser();
		}
	data_count_modbus = data1;
}

void le_data_mod(void)
{
	data_modbus = le_word_buf_modbus();;
}


void le_byte_regs_modbus(void)
{
	data1_int = 0;
	 switch(addr_regs_modbus)
	 	{
	 	case 1:
	 		{
	 		 data1_int = ten_nomi;
	 		 break;
	 		}
	 	case 2:
	 		{
			#if (tc_fixo == true)
				#if (st94 == false) || (st92 == false)
					busca_mul_tc();
				#else
					calcula_mul_tc();
				#endif
			#endif
			#if (portatil == true)
				#if (se_com_flex == true)
			 		 data1_int = tipo_ponteira;
				#else
			 		 data1_int = valor_tc;
				#endif
			#else
		 		 data1_int = valor_tc;
	 		 #endif
	 		 break;
	 		}
	 	case 3:
	 		{
	 		 data1_int = set_point;
	 		 break;
	 		}
	 	case 4:
	 		{
	 		 data1_int = endereco;
	 		 break;
	 		}
	 	case 5:
	 		{
	 		 data1_int = intervalo_reg;
	 		 break;
	 		}
	 	case 6:
	 		{
	 		 data1_int = intervalo_integra;
	 		 break;
	 		}
	 	case 7:
	 		{
	 		 data1_int = ala_fp_ind;
	 		 break;
	 		}
	 	case 8:
	 		{
	 		 data1_int = ala_fp_cap;
	 		 break;
	 		}
	 	case 9:
	 		{
	 		 data1_int = ala_ten_a;
	 		 break;
	 		}
	 	case 10:
	 		{
	 		 data1_int = ala_ten_b;
	 		 break;
	 		}
	 	case 11:
	 		{
	 		 data1_int = ala_sc;
	 		 break;
	 		}
	 	case 12:
	 		{
	 		 data1_int = ala_chtt;
	 		 break;
	 		}
		#if (com_regs == 1)
			case 13:
	 			{
				#if (com_relogio == false)
			 		data1_int = read_word(ee_ptr_regs);
					data1_int = (word)(data1_int -((word)(data1_int / nro_registros_por_banco)* nro_registros_por_banco));
				#else
			 		data1_int = read_word_nvr(ds_ptr_regs);
//					data1_int = (word)(data1_int -((word)(data1_int / nro_registros_por_banco)* nro_registros_por_banco));
				#endif
		 		 break;
	 			}
	 		case 14:
	 			{
				#if (com_relogio == false)
				 	data1_int = read_byte(ee_ptr_ocor);
			 	#else
				 	data1_int = read_word_nvr(ds_ptr_ocor);
			 	#endif
		 		 break;
	 			}
 			case 15:
	 			{
				#if (com_relogio == false)
				 	data1_int = read_word(ee_ptr_cht);
			 	#else
				 	data1_int = read_word_nvr(ds_ptr_cht);
				#endif
				if (forma_reg_cht == 0)
					{
					if (data1_int >  limite_chts)
						{
						data1_int = 0;
						#if (com_relogio == true)
							write_word_nvr(ds_ptr_cht, 0);
						#else
							write_word(ee_ptr_cht, 0);
						#endif
						}
					}
		 		break;
	 			}
	 		case 16:
	 			{
	 			 data1_int = forma_reg_cht;
	 		 	break;
	 			}
	 	#endif
 		case 17:
	 		{
	 		 data1_int = valor_tp;
	 		 break;
	 		}
 		case 18:
	 		{
	 		 data1_int = baud_rate;
	 		 break;
	 		}
 		case 19:
	 		{
	 		 data1_int = ala_chtc;
	 		 break;
	 		}
		#if (com_regs == true)
 			case 20:
	 			{
				#if (com_relogio == false)
		 		 	data1_int = read_byte(ee_banco_escrita);
		 		 #else
		 		 	data1_int = read_byte_nvr(ds_banco_escrita);
		 		 #endif
		 		 break;
	 			}
 			case 21:
	 			{
				#if (com_relogio == false)
			 		 data1_int = read_byte(ee_banco_leitura);
			 	#else
			 		 data1_int = read_byte_nvr(ds_banco_leitura);
			 	#endif
	 			 break;
	 			}
		#endif
	 	case 22:
	 		{
	 		 data1_int = dia;
	 		 break;
	 		}
	 	case 23:
	 		{
	 		 data1_int = mes;
	 		 break;
	 		}
	 	case 24:
	 		{
	 		 data1_int = ano;
	 		 break;
	 		}
	 	case 25:
	 		{
	 		 data1_int = hora;
	 		 break;
	 		}
	 	case 26:
	 		{
	 		 data1_int = minuto;
	 		 break;
	 		}
	 	case 27:
	 		{
	 		 data1_int = segundo;
	 		 break;
	 		}
		case 28:
			{
	 		 data1_int = ala_subc;
	 		 break;
	 		 }
		#if (portatil == true)
			case 29:
				{
				data1_int = dia_liga;
				break;
				}		 	
			case 30:
				{
				data1_int = hora_liga;
				break;
				}		 	
			case 31:
				{
				data1_int = minuto_liga;
				break;
				}		 	
			case 32:
				{
				data1_int = dia_desliga;
				break;
				}		 	
			case 33:
				{
				data1_int = hora_desliga;
				break;
				}		 	
			case 34:
				{
				data1_int = minuto_desliga;
				break;
				}
			case 35:
				{
				data1_int = prog_time;
				break;
				}		 	
			case 36:
				{
				data1_int = fila_circular;
				break;
				}
		#endif
			case 37:
				{
				data1_int = hora_ponta;
				break;
				}
			case 38:
				{
				data1_int = minuto_ponta;
				break;
				}
			case 39:
				{
				data1_int = hora_final_ponta;
				break;
				}
			case 40:
				{
				data1_int = minuto_final_ponta;
				break;
				}
		case 41:
			{
			data1_int = tipo_ligacao;
			break;
			}
		#if (com_regs == 1)
		 	case 42:
		 		{
 				if (modo_funca == 2)
					{
			 		data1_int = nro_bancos_modo2;
					}	
				else if (modo_funca == 3)
					{
	 				data1_int = nro_bancos_modo3;
					}	
				else
					{
		 			data1_int = nro_bancos;
					}
		 		break;
			 	}
		#endif
		#if (com_regs == 1)
		 	case 43:
	 			{
				if (modo_funca == 2)
					{
				 	data1_int = nro_registros_por_banco2;
					}
				else
					{
			 		data1_int = nro_registros_por_banco;
					}
			 	break;
			 	}
		#endif
		case 44:
			{
			#if (com_regs == true)
		 		data1_int = nro_modos;
		 	#endif
	 		break;
		 	}
		case 45:
	 		{
			#if (ST8100C == true)
				data1_int = 1;
			#else
			 	data1_int = modo_funca;		
			 #endif
		 	break;
		 	}
		case 46:
	 		{
		 	#if (com_regs == true)
				#if (ST8100C == true)
					data1_int = 1;
				#else
				 	if (registro == 1)
						{
						data1_int = 1;
						}
					else
						{
						data1_int = 0;
						}
				#endif
			#else
				data1_int = 0;
			#endif
		 	break;
		 	}
		case 47:
			{
			#if (com_menu == true)
				data1_int = idioma;
			#else
				data1_int = 0;
			#endif
			break;
			}
		case 48:
			{
	 		 data1_int = ala_skw;
	 		 break;
	 		 }
		#if (com_alarme_demanda == true)
		 	case 49:
		 		{
			 	data1_int = ala_demanda_ativa;
			 	break;
			 	}
		#endif
		#if (com_regs == true)
			case 50:
				{
				data1_int = limite_ocorrencias;
				break;
				}
			case 51:
				{
				data1_int = limite_chts;
				break;
				}
			case 52:
				{
				data1_int = addr_inicio_coleta_regs;
				break;
				}
			case 53:
				{
				data1_int = addr_inicio_coleta_ocor;
				break;
				}
			case 54:
				{
				data1_int = addr_inicio_coleta_cht;
				break;
				}
		#endif
		#if (st5x==true)		
			#if (com_saida_pulsos == true)
				case 55:
					{
					data1_int = const_saida_kw;
					break;
					}
				case 56:
					{
					data1_int = const_saida_kvar;
					break;
					}
				case 57:
					{
					data1_int = qual_variavel_pulsa;
					break;
					}
			#endif
		#endif
		
		#if (protocolo_abb == true)
			case 58:
				{
				data1_int = 0;
				break;
				}
			case 80:
				{
				data1_int = 5000;	// Valor de Corrente Primario ou de Indicacao
				break;
				}
			case 81:
				{
				data1_int = 3;	// Numero de Casas decimais para Corrente (0,1,2,3)
				break;
				}
			case 82:
				{
				data1_int = 0;	// Grandeza de medicao de Corrente: (0)_ (3)k
				break;
				}
			case 83:
				{
				data1_int = 2540;	// Valor de Tensao Primario ou de Indicacao
				break;
				}
			case 84:
				{
				data1_int = 1;	// Numero de Casas decimais para Tensao (0,1,2,3)
				break;
				}
			case 85:
				{
				data1_int = 0;	// Grandeza de medicao de Tensao: (0)_ (3)k
				break;
				}
			case 86:
				{
				data1_int = 1269;	// Valor de Potencia Primario ou de Indicacao
				break;
				}
			case 87:
				{
				data1_int = 3;	// Numero de Casas decimais para Potencia (0,1,2,3)
				break;
				}
			case 88:
				{
				data1_int = 3;	// Grandeza de medicao de Potencia: 0(_) 3(k) 6(M)
				break;
				}
			case 89:
				{
				data1_int = 3;	// Tipo de Rede: 1(monofasico) 3(trifasico)
				break;
				}
			case 94:
				{
				data1_int = 0;	// Formato da Word: 00(bit de sinal), 01(complemento de 2)
				break;
				}
			case 97:
				{
				data1_int = 1;	//Campo de Energia: 1,2,3,4,5,6,7 e 8
				break;
				}
			case 100:
				{
				data1_int = converte_abb(tensao_r, 'T');
				break;
				}
			#if (monofasico == false)
				case 101:
					{
					data1_int = converte_abb(tensao_s, 'T');
					break;
					}
				case 102:
					{
					data1_int = converte_abb(tensao_t, 'T');
					break;
					}
			#endif
			case 103:
				{
				data1_int = converte_abb(tensao_r, 'T');
				break;
				}
			#if (monofasico == false)
				case 104:
					{
					data1_int = converte_abb(tensao_s, 'T');
					break;
					}
				case 105:
					{
					data1_int = converte_abb(tensao_t, 'T');
					break;
					}
//									case 103:		//Enviamos apenas tensao de fase porque o aplicativo ABB multiplica por 1,73.
//										{
//										data1_int = converte_abb(tensao_rs, 'T');
//										break;
//										}
//									#if (monofasico == false)
///										case 104:
//											{
//											data1_int = converte_abb(tensao_st, 'T');
//											break;
//											}
//										case 105:
//											{
//											data1_int = converte_abb(tensao_rt, 'T');
//											break;
//											}
			#endif
			case 106:
				{
				data1_int = converte_abb(corrente_r, 'C');
				break;
				}
			#if (monofasico == false)
				case 107:
					{
					data1_int = converte_abb(corrente_s, 'C');
					break;
					}
				case 108:
					{
					data1_int = converte_abb(corrente_t, 'C');
					break;
					}
			#endif
			case 109:
				{
				aux_l1 = corrente_r;
				#if (monofasico == false)
					aux_l1 += corrente_s;
					aux_l1 += corrente_t;
				#else
					aux_l1 += (aux_l1 * 3);
				#endif
				data1_int = converte_abb(aux_l1, 'C');
				break;
				}
			case 110:
				{
				data1_int = converte_abb(pot_ativa_r, 'P');
				break;
				}
			#if (monofasico == false)
				case 111:
					{
					data1_int = converte_abb(pot_ativa_s, 'P');
					break;
					}
				case 112:
					{
					data1_int = converte_abb(pot_ativa_t, 'P');
					break;
					}
			#endif			
			case 113:
				{
				aux_l1 = pot_ativa_r;
				#if (monofasico == false)
					aux_l1 += pot_ativa_s;
					aux_l1 += pot_ativa_t;
					aux_l1 = (aux_l1 / 3);
				#endif
				data1_int = converte_abb(aux_l1, 'P');
				break;
				}
			case 114:
				{
				data1_int = converte_abb(pot_reativa_r, 'P');
				break;
				}
			#if (monofasico == false)
				case 115:
					{
					data1_int = converte_abb(pot_reativa_s, 'P');
					break;
					}
				case 116:
					{
					data1_int = converte_abb(pot_reativa_t, 'P');
					break;
					}
			#endif			
			case 117:
				{
				aux_l1 = pot_reativa_r;
				#if (monofasico == false)
					aux_l1 += pot_reativa_s;
					aux_l1 += pot_reativa_t;
					aux_l1 = (aux_l1 / 3);
				#endif
				data1_int = converte_abb(aux_l1, 'P');
				break;
				}
			case 118:
				{
				data1_int = converte_abb(pot_aparente_r, 'P');
				break;
				}
			#if (monofasico == false)
				case 119:
					{
					data1_int = converte_abb(pot_aparente_s, 'P');
					break;
					}
				case 120:
					{
					data1_int = converte_abb(pot_aparente_t, 'P');
					break;
					}
			#endif			
				
			case 121:
				{
				aux_l1 = pot_aparente_r;
				#if (monofasico == false)
					aux_l1 += pot_aparente_s;
					aux_l1 += pot_aparente_t;
					aux_l1 = (aux_l1 / 3);
				#endif
				data1_int = converte_abb(aux_l1, 'P');
				break;
				}
			case 122:
				{
				data1_int = converte_abb(fator_pot_r, 'F');
				break;
				}
			case 123:
				{
				#if (monofasico == false)
					data1_int = converte_abb(fator_pot_s, 'F');
				#else
					data1_int = converte_abb(1024, 'F');
				#endif
				break;
				}
			case 124:
				{
				#if (monofasico == false)
					data1_int = converte_abb(fator_pot_t, 'F');
				#else
					data1_int = converte_abb(1024, 'F');
				#endif
				break;
				}

			case 125:
				{
				#if (monofasico == true)
					fator_pot = fator_pot_r;
				#endif
					
				data1_int = converte_abb(fator_pot, 'F');
				break;
				}
			case 126:
				{
				data1_int = converte_abb(frequencia, 'B');
				break;
				}
			#if (com_consumo == true)
				case 127:
					{
					data1_int = consumo_ati / 1000;
					break;
					}
				case 128:
					{
					aux_l1 = consumo_ati / 1000;
					data1_int = consumo_ati - (aux_l1 * 1000);
					break;
					}
				case 129:
					{
					data1_int = 0;									// nao existe wh
					break;
					}
				case 130:
					{
					data1_int = consumo_reati / 1000;
					break;
					}
				case 131:
					{
					aux_l1 = consumo_reati / 1000;
					data1_int = consumo_reati - (aux_l1 * 1000);
					break;
					}
				case 132:
					{
					data1_int = 0;								// nao existe varh
					break;
					}
			#endif
			case 139:
				{
				data1_int = converte_abb(fator_pot_r, 'A');
				break;
				}
			case 140:
				{
				data1_int = converte_abb(fator_pot_s, 'A');
				break;
				}
			case 141:
				{
				data1_int = converte_abb(fator_pot_t, 'A');
				break;
				}
			case 142:
				{
				#if (monofasico == true)
					fator_pot = fator_pot_r;
				#endif
				data1_int = converte_abb(fator_pot, 'A');
				break;
				}
			case 146:
				{
				data1_int = converte_abb((dem_ativa / 3),'D');
				break;
				}
			case 147:
				{
				data1_int = converte_abb((dem_reativa / 3),'D');
				break;
				}
			case 148:
				{
				data1_int = converte_abb((dem_aparente / 3), 'D');
				break;
				}
		#endif
	 	case 2000:
	 		{
			#if (portatil == true)
				#if (se_com_flex == true)
					off_cor_r = off_set_fp[tipo_ponteira];
				#else
					for (aux_b4=0; aux_b4 < NRO_POSI_TC; aux_b4++)
						{
						if (valor_tc == tabela_tc[aux_b4])
							{
							break;
							}
						}
					off_cor_r = off_set_fp[aux_b4];
				#endif
			#endif
			#if (ade7754 == true)
				data1_int = fase_r;
			#else
	 			data1_int = off_cor_r;
			#endif
			break;
	 		}
		 	case 2001:
	 			{
				#if (ade7754 == true)
					data1_int = 0;
				#else
	 				data1_int = off_cor_s;
				#endif
				break;
		 		}
	 	#if (monofasico == false)
	 		case 2002:
	 			{
				#if (ade7754 == true)
					data1_int = fase_t;
				#else
					data1_int = defasagem;
				#endif
				break;
	 			}
	 	#endif
	 	case 2003:
	 		{
	 		data1_int = os_ten_r1;
			break;
	 		}
	 	#if (monofasico == false)
		 	case 2004:
	 			{
	 			data1_int = os_ten_s1;
				break;
		 		}
	 		case 2005:
	 			{
	 			data1_int = os_ten_t1;
				break;
	 			}
	 	#endif
	 	case 2006:
	 		{
	 		data1_int = os_ten_r2;
			break;
	 		}
	 	#if (monofasico == false)
		 	case 2007:
	 			{
	 			data1_int = os_ten_s2;
				break;
		 		}
		 	case 2008:
	 			{
	 			data1_int = os_ten_t2;
				break;
	 			}
	 	#endif
	 	case 2009:
	 		{
	 		data1_int = os_cor_r;
			break;
	 		}
	 	#if (monofasico == false)
		 	case 2010:
	 			{
	 			data1_int = os_cor_s;
				break;
		 		}
	 		case 2011:
	 			{
	 			data1_int = os_cor_t;
				break;
	 			}
	 	#endif
		#if (portatil == true)
			#if (se_com_flex == true)
			 	case 2012:
			 		{
					busca_os_cor_pt_r(tipo_ponteira);
					break;
			 		}
			 	case 2013:
			 		{
					busca_os_cor_pt_s(tipo_ponteira);
					break;
			 		}
			 	case 2014:
			 		{
					busca_os_cor_pt_t(tipo_ponteira);
					break;
			 		}
			 #endif
		#endif	 		

		case 2050:
			{
			#if (portatil == true)
				#if (se_com_flex == true)
					data1_int = os_pot_pt_r[tipo_ponteira];
				#else
					for (aux_b4=0; aux_b4 < NRO_POSI_TC; aux_b4++)
						{
						if (valor_tc == tabela_tc[aux_b4])
							{
							break;
							}
						}
					data1_int = os_pot_pt_r[aux_b4];
				#endif
			#else
	 			data1_int = os_pot_r;
			#endif
			break;
			}

	 	#if (monofasico == false)
			case 2051:
				{
				#if (portatil == true)
					#if (se_com_flex == true)
						data1_int = os_pot_pt_s[tipo_ponteira];
					#else
						for (aux_b4=0; aux_b4 < NRO_POSI_TC; aux_b4++)
							{
							if (valor_tc == tabela_tc[aux_b4])
								{
								break;
								}
							}
						data1_int = os_pot_pt_s[aux_b4];
					#endif
				#else
		 			data1_int = os_pot_s;
				#endif
				break;
				}
			case 2052:
				{
				#if (portatil == true)
					#if (se_com_flex == true)
						data1_int = os_pot_pt_t[tipo_ponteira];
					#else
						for (aux_b4=0; aux_b4 < NRO_POSI_TC; aux_b4++)
							{
							if (valor_tc == tabela_tc[aux_b4])
								{
								break;
								}
							}
						data1_int = os_pot_pt_t[aux_b4];
					#endif
				#else
		 			data1_int = os_pot_t;
				#endif
				break;
				}
		#endif

		#if (portatil == true)
			#if (se_com_flex == true)
			 	case 2053:
			 		{
					busca_os_pot_pt_r(tipo_ponteira);
					break;
			 		}
			 	case 2054:
			 		{
					busca_os_pot_pt_s(tipo_ponteira);
					break;
			 		}
			 	case 2055:
			 		{
					busca_os_pot_pt_t(tipo_ponteira);
					break;
			 		}
/*			 	case 2056:
			 		{
					busca_os_pot_pt_r(tipo_ponteira);
					break;
			 		}
			 	case 2057:
			 		{
					busca_os_pot_pt_s(tipo_ponteira);
					break;
			 		}
			 	case 2058:
			 		{
					busca_os_pot_pt_t(tipo_ponteira);
					break;
			 		}
			 	case 2059:
			 		{
					busca_os_pot_pt_r(tipo_ponteira);
					break;
			 		}
			 	case 2060:
			 		{
					busca_os_pot_pt_s(tipo_ponteira);
					break;
			 		}
			 	case 2061:
			 		{
					busca_os_pot_pt_t(tipo_ponteira);
					break;
			 		}*/
			#else
				case 2053:
					{
					busca_os_pot_pt_r(0);
					break;
					}
				case 2054:
					{
					busca_os_pot_pt_s(0);
					break;
					}
				case 2055:
					{
					busca_os_pot_pt_t(0);
					break;
					}
				case 2056:
					{
					busca_os_pot_pt_r(1);
					break;
					}
				case 2057:
					{
					busca_os_pot_pt_s(1);
					break;
					}
				case 2058:
					{
					busca_os_pot_pt_t(1);
					break;
					}
				case 2059:
					{
					busca_os_pot_pt_r(2);
					break;
					}
				case 2060:
					{
					busca_os_pot_pt_s(2);
					break;
					}
				case 2061:
					{
					busca_os_pot_pt_t(2);
					break;
					}
		//
				case 2062:
					{
					busca_os_pot_pt_r(3);
					break;
					}
				case 2063:
					{
					busca_os_pot_pt_s(3);
					break;
					}
				case 2064:
					{
					busca_os_pot_pt_t(3);
					break;
					}
		//
				case 2065:
					{
					busca_os_pot_pt_r(4);
					break;
					}
				case 2066:
					{
					busca_os_pot_pt_s(4);
					break;
					}
				case 2067:
					{
					busca_os_pot_pt_t(4);
					break;
					}
		//
				case 2068:
					{
					busca_os_pot_pt_r(5);
					break;
					}
				case 2069:
					{
					busca_os_pot_pt_s(5);
					break;
					}
				case 2070:
					{
					busca_os_pot_pt_t(5);
					break;
					}
		//
				case 2071:
					{
					busca_os_pot_pt_r(6);
					break;
					}
				case 2072:
					{
					busca_os_pot_pt_s(6);
					break;
					}
				case 2073:
					{
					busca_os_pot_pt_t(6);
					break;
					}
		//
				case 2074:
					{
					busca_os_pot_pt_r(7);
					break;
					}
				case 2075:
					{
					busca_os_pot_pt_s(7);
					break;
					}
				case 2076:
					{
					busca_os_pot_pt_t(7);
					break;
					}
		//
				case 2077:
					{
					busca_os_pot_pt_r(8);
					break;
					}
				case 2078:
					{
					busca_os_pot_pt_s(8);
					break;
					}
				case 2079:
					{
					busca_os_pot_pt_t(8);
					break;
					}
			 #endif
		#endif
	 	case 2080:
	 		{
//		 	calcula_vref_cr();
		 	break;
		 	}
		#if (monofasico == false)
		 	case 2081:
		 		{
//		 		calcula_vref_cs();
			 	break;
			 	}
		 	case 2082:
		 		{
//		 		calcula_vref_ct();
			 	break;
			 	}
		 #endif
		 case 2083:
		 	{
			 data1_int = vreftr;
			 break;
			 }
		 case 2084:
		 	{
			 data1_int = vrefcr;
			 break;
			 }
		#if (monofasico == false)
			 case 2085:
			 	{
				 data1_int = vrefcs;
				 break;
				 }
			 case 2086:
			 	{
				 data1_int = vrefct;
				 break;
				 }
		#endif
	
		#if (ade7754 == true)
		 	case 2080:
		 		{
		 		data1_int = CFNUM_R;
				break;
		 		}
		 	case 2081:
		 		{
		 		data1_int = CFNUM_S;
				break;
		 		}
		 	case 2082:
		 		{
		 		data1_int = CFNUM_T;
				break;
		 		}
		#endif


//      reservado entre 2100 e 2300 para parametros dos controladores de fator de potencia(200 partametros)
		#if (controlador == true) || (st_prog == true)
			case 2100:
				{
				#if (st8500c == true)
					data1_int = nro_cargas;
				#else
					data1_int = nro_bancos_capacitor;
				#endif
				break;
				}
			case 2101:
				{
				#if (st8500c == true)
					data1_int = max_kw;
				#else
					data1_int = max_kvar;
				#endif
				break;
				}
			case 2102:
				{
				#if (st8500c == true)
					data1_int = min_kw;
				#else
					data1_int = min_kvar;
				#endif
				break;
				}
			case 2103:
				{
				data1_int = sequencia;
				break;
				}
			case 2104:
				{
				data1_int = tempo_aciona;
				break;
				}
			case 2105:
				{
				#if (com_rep == true)
					if (modo_rep == 1)
						{
						data1_int = cor_minima_rep;
						}
					else
						{
						data1_int = cor_minima;
						}
				#else
					data1_int = cor_minima;
				#endif
				break;
				}
			case 2106:
				{
				data1_int = com_des_fp_ind_cap;
				break;
				}
			case 2107:
				{
				data1_int = com_des_ten_a;
				break;
				}
			case 2108:
				{
				data1_int = com_des_chtt;
				break;
				}
			case 2109:
				{
				data1_int = com_des_chtc;
				break;
				}
			case 2110:
			case 2111:
			case 2112:
			case 2113:
			case 2114:
			case 2115:
			case 2116:
			case 2117:
			case 2118:
			case 2119:
			case 2120:
			case 2121:
			case 2122:
			case 2123:
			case 2124:
			case 2125:
				{
				aux_b4 = addr_regs_modbus - 2110;
				#if (st8500c == true)
					data1_int = carga[aux_b4];
				#else
					data1_int = banco_capacitor[aux_b4];
				#endif
				break;	
				}
			case 2126:
			case 2127:
			case 2128:
			case 2129:
			case 2130:
			case 2131:
			case 2132:
			case 2133:
			case 2134:
			case 2135:
			case 2136:
			case 2137:
			case 2138:
			case 2139:
			case 2140:
			case 2141:
				{
				aux_b4 = addr_regs_modbus - 2126;
				data1_int = tempo_repouso[aux_b4];
				break;	
				}
			case 2142:
				{
		 		 data1_int = tempo_desaciona;
	 			 break;
				}
		#endif
		#if (st8500c == true)
			#if (com_tc == true)
				case 2143:
				case 2144:
					{
			 		 data1_int = 0;
		 			 break;
					}
				case 2145:
					{
					data1_int = valor_tc;
					break;
					}
				case 2146:
					{
					data1_int = valor_tp;
					break;
					}
			#endif
		#endif
		#if (com_rep == true)
			case 2143:
				{
		 		 data1_int = NRO_MODOS_MEDICAO;
	 			 break;
				}
			case 2144:
				{
		 		 data1_int = modo_rep;
	 			 break;
				}
			case 2145:
				{
				data1_int = fat_conv_ativa;
				break;
				}
			case 2146:
				{
				data1_int = fat_conv_reativa;
				break;
				}
		#endif
		#if (st8500c == true)
			case 2150:
			case 2151:
			case 2152:
			case 2153:
			case 2154:
			case 2155:
			case 2156:
			case 2157:
			case 2158:
			case 2159:
			case 2160:
			case 2161:
			case 2162:
			case 2163:
			case 2164:
			case 2165:
				{
				aux_b4 = addr_regs_modbus - 2150;
				data1_int = forma_controle[aux_b4];
				break;	
				}
			case 2170:
			case 2171:
			case 2172:
			case 2173:
			case 2174:
			case 2175:
			case 2176:
			case 2177:
			case 2178:
			case 2179:
			case 2180:
			case 2181:
			case 2182:
			case 2183:
			case 2184:
			case 2185:
				{
				aux_b4 = addr_regs_modbus - 2170;
				data1_int = hora_liga_controle[aux_b4];
				break;	
				}
			case 2190:
			case 2191:
			case 2192:
			case 2193:
			case 2194:
			case 2195:
			case 2196:
			case 2197:
			case 2198:
			case 2199:
			case 2200:
			case 2201:
			case 2202:
			case 2203:
			case 2204:
			case 2205:
				{
				aux_b4 = addr_regs_modbus - 2190;
				data1_int = minuto_liga_controle[aux_b4];
				break;	
				}
			case 2210:
			case 2211:
			case 2212:
			case 2213:
			case 2214:
			case 2215:
			case 2216:
			case 2217:
			case 2218:
			case 2219:
			case 2220:
			case 2221:
			case 2222:
			case 2223:			
			case 2224:
			case 2225:
				{
				aux_b4 = addr_regs_modbus - 2210;
				data1_int = hora_desliga_controle[aux_b4];
				break;	
				}
			case 2230:
			case 2231:
			case 2232:
			case 2233:
			case 2234:
			case 2235:
			case 2236:
			case 2237:
			case 2238:
			case 2239:
			case 2240:
			case 2241:
			case 2242:
			case 2243:			
			case 2244:
			case 2245:
				{
				aux_b4 = addr_regs_modbus - 2230;
				data1_int = minuto_desliga_controle[aux_b4];
				break;	
				}
				
			case 2250:
				{
				data1_int = tipo_controle_demanda;
				break;
				}
			case 2251:
				{
				data1_int = dem_cont_ponta[mes - 1];
				break;
				}
			case 2252:
				{
				data1_int = dem_cont_fora_ponta[mes - 1];
				break;
				}
			case 2253:
				{
				data1_int = 0;			//Area Livre
				break;
				}
			case 2254:
				{
				data1_int = 0;			// Area Livre
				break;
				}
			case 2255:
				{
				data1_int = carga_programada;
				break;
				}
			case 2256:
				{
				data1_int = dia_inicio_pc;
				break;
				}
			case 2257:
				{
				data1_int = mes_inicio_pc;
				break;
				}
			case 2258:
				{
				data1_int = dia_final_pc;
				break;
				}
			case 2259:
				{
				data1_int = mes_final_pc;
				break;
				}
			case 2260:
			case 2261:
			case 2262:
			case 2263:
			case 2264:
			case 2265:
			case 2266:
			case 2267:
			case 2268:
			case 2269:
			case 2270:
			case 2271:
				{
				aux_b4 = addr_regs_modbus - 2260;
				data1_int = dem_cont_ponta[aux_b4];
				break;
				}
			case 2272:
			case 2273:
			case 2274:
			case 2275:
			case 2276:
			case 2277:
			case 2278:
			case 2279:
			case 2280:
			case 2281:
			case 2282:
			case 2283:
				{
				aux_b4 = addr_regs_modbus - 2272;
				data1_int = dem_cont_fora_ponta[aux_b4];
				break;
				}
				
		#endif				

		case 2300:{
			data1_int = com_des_ten_b;
			break;
		}
		
		#if (comandos_teste == true)
			case 2998:
				{
				data1_int = cruza_ten;
				break;
				}
			case 2999:
				{
				data1_int = cruza_cor;
				break;
				}
		 	case 3000:
		 		{
			 	data1_int = freq_tmp1;
			 	break;
			 	}
		 	case 3001:
		 		{
			 	data1_int = nro_ints_old;
			 	break;
			 	}
		 	case 3002:
		 		{
			 	data1_int = freq_tmp;
			 	break;
			 	}
		 	case 3003:
		 		{
			 	data1_int = distancia_fase;
			 	break;
			 	}
		 	case 3004:
		 		{
			 	data1_int = cont_fase;
		     	break;
			 	}
		 	case 3005:
		 		{
			 	data1_int = vreftr;
		     	break;
			 	}
			case 3006:
				{
				data1_int = nro_soma_vref;
				break;
				}
			case 3007:
				{
				data1_int = soma_vref >> 16;
				break;
				}
			case 3008:
				{
				data1_int = soma_vref;
				break;
				}
			case 3009:
				{
				data1_int = 0;
				break;
				}
			case 3010:
				{
				#if (com_regs == true)
					#if (ST8100C == true)
						data1_int = 0;
					#else	
						data1_int = Read_Status_Register(BANCO_0);
					#endif
				#else
					data1_int = 0;
				#endif			
				break;
				}
			case 3011:
				{
				#if (com_regs == true)
					#if (ST8100C == true)
						data1_int = 0;
					#else
						data1_int = Read_ID(BANCO_0, 0);
					#endif
				#else
					data1_int = 0;
				#endif			
				break;
				}
			case 3012:
				{
				#if (com_regs == true)
					#if (ST8100C == true)
						data1_int = 0;
					#else
						data1_int = Read_ID(BANCO_0, 1);
					#endif
				#else
					data1_int = 0;
				#endif			
				break;
				}
			case 3013:
				{
				data1_int = soma_efi_kvar_r >> 16;
				break;
				}
			case 3014:
				{
				data1_int = soma_efi_kvar_r;
				break;
				}
			case 3015:
				{
				data1_int = soma_efi_pr >> 16;
				break;
				}
			case 3016:
				{
				data1_int = soma_efi_pr;
				break;
				}
			case 3017:
				{
				data1_int = soma_efi_p_tmp >> 16;
				break;
				}
			case 3018:
				{
				data1_int = soma_efi_p_tmp;
				break;
				}
		#endif
		#if (chip_cs5460a == true)
			case 3014:
				{
	//			calcula_tensao_corrente();
				aux_ten_l = read_cs5460(V_rms,'R') ;
				data1_int = aux_ten_l >> 16;
				break;
				}
			case 3015:
				{
				data1_int = aux_ten_l;
				break;
				}
			case 3016:
				{
				aux_cor_l = read_cs5460(I_rms,'R');
				data1_int = aux_cor_l >> 16;
				break;
				}
			case 3017:
				{
				data1_int = aux_cor_l;
				break;
				}
			case 3018:
				{
				aux_pot_l = read_cs5460(E_register,'R');
				data1_int = aux_pot_l >> 16;
				break;
				}
			case 3019:
				{
				data1_int = aux_pot_l;
				break;
				}

	
			case 3020:
				{
				aux_cs5460_l = read_cs5460(config_cs5460a,'R');
				data1_int = aux_cs5460_l >> 16;
				break;
				}
			case 3021:
				{
				data1_int = aux_cs5460_l;
				break;
				}
			case 3022:
				{
				aux_cs5460_l = read_cs5460(I_dc_offset,'R');
				data1_int = aux_cs5460_l >> 16;
				break;
				}
			case 3023:
				{
				data1_int = aux_cs5460_l;
				break;
				}
			case 3024:
				{
				aux_cs5460_l = read_cs5460(I_gain,'R');
				data1_int = aux_cs5460_l >> 16;
				break;
				}
			case 3025:
				{
				data1_int = aux_cs5460_l;
				break;
				}
			case 3026:
				{
				aux_cs5460_l = read_cs5460(V_dc_offset,'R');
				data1_int = aux_cs5460_l >> 16;
				break;
				}
			case 3027:
				{
				data1_int = aux_cs5460_l;
				break;
				}
			case 3028:
				{
				aux_cs5460_l = read_cs5460(V_gain,'R');
				data1_int = aux_cs5460_l >> 16;
				break;
				}
			case 3029:
				{
				data1_int = aux_cs5460_l;
				break;
				}
			case 3030:
				{
				aux_cs5460_l = read_cs5460(cycle_count,'R');
				data1_int = aux_cs5460_l >> 16;
				break;
				}
			case 3031:
				{
				data1_int = aux_cs5460_l;
				break;
				}
			case 3032:
				{
				aux_cs5460_l = read_cs5460(pulse_rate,'R');
				data1_int = aux_cs5460_l >> 16;
				break;
				}
			case 3033:
				{
				data1_int = aux_cs5460_l;
				break;
				}
			case 3034:
				{
				aux_cs5460_l = read_cs5460(TBC_register,'R');
				data1_int = aux_cs5460_l >> 16;
				break;
				}
			case 3035:
				{
				data1_int = aux_cs5460_l;
				break;
				}
			case 3036:
				{
				aux_cs5460_l = read_cs5460(P_offset,'R');
				data1_int = aux_cs5460_l >> 16;
				break;
				}
			case 3037:
				{
				data1_int = aux_cs5460_l;
				break;
				}
			case 3038:
				{
				aux_cs5460_l = read_cs5460(Status_cs5460a,'R');
				data1_int = aux_cs5460_l >> 16;
				status_cs5460h = datah;
				status_cs5460m = datam;
				status_cs5460l = datal;
				break;
				}
			case 3039:
				{
				data1_int = aux_cs5460_l;
				break;
				}
			case 3040:
				{
				aux_cs5460_l = read_cs5460(I_ac_offset,'R');
				data1_int = aux_cs5460_l >> 16;
				break;
				}
			case 3041:
				{
				data1_int = aux_cs5460_l;
				break;
				}
			case 3042:
				{
				aux_cs5460_l = read_cs5460(V_ac_offset,'R');
				data1_int = aux_cs5460_l >> 16;
				break;
				}
			case 3043:
				{
				data1_int = aux_cs5460_l;
				break;
				}
			case 3044:
				{
				aux_cs5460_l = read_cs5460(mask_cs5460a,'R');
				data1_int = aux_cs5460_l >> 16;
				break;
				}
			case 3045:
				{
				data1_int = aux_cs5460_l;
				break;
				}
			case 3046:
				{
				aux_cs5460_l = read_cs5460(ctrl_cs5460a,'R');
				data1_int = aux_cs5460_l >> 16;
				break;
				}
			case 3047:
				{
				data1_int = aux_cs5460_l;
				break;
				}
			
		#endif


		case 9005:
			{
			buf_tmp[0] = read_byte(ee_nro_1);
			buf_tmp[1] = read_byte(ee_nro_2);
			buf_tmp[2] = read_byte(ee_nro_3);
			buf_tmp[3] = read_byte(ee_nro_4);
			ascbin1();
			break;
			}

		#if (ade7754 == true)
	 	    case 9990:
	 	    	{
				data1_int = read_word(ee_reg_cfnum);
				break;
				}
	 	    case 9991:
	 	    	{
				data1_int = read_word(ee_reg_cfdem);
				break;
				}
	 	    case 9992:
	 	    	{
				data1_int = RAENERGY_R;
				break;
				}
	 	    case 9993:
	 	    	{
				data1_int = RAENERGY_S;
				break;
				}
	 	    case 9994:
	 	    	{
				data1_int = RAENERGY_T;
				break;
				}
		#endif


	 	 default:
	 		{
	 		data1_int = 0;
	 		}
	 	} 
}	 	


	 
void le_word_vars_modbus(void)
{   
	data1_int = 0;
	 switch(addr_regs_modbus)
	 	{
	 	case 1:
	 		{
		 	#if (monofasico == true)
		 		 data1_int = tensao_r;
		 	#else
				if ((tipo_ligacao == 0) || (tipo_ligacao == 2))
					{
			 		 data1_int = tensao_r;
					}
				else
					{
			 		 data1_int = tensao_rs;
					}
			#endif
	 		 break;
	 		}
		#if (monofasico == false)
			#if (padrao_referencia == true)
			 	case 2:
			 	case 3:{
					if ((tipo_ligacao == 0) || (tipo_ligacao == 2)){
				 		data1_int = tensao_r;
						}
					else{
				 		data1_int = tensao_rs;
						}
			 		break;
		 			}
			#else
			 	case 2:
		 			{
					if ((tipo_ligacao == 0) || (tipo_ligacao == 2))
						{
				 		 data1_int = tensao_s;
						}
					else
						{
				 		 data1_int = tensao_st;
						}
			 		 break;
		 		}
			 	case 3:
		 			{
					if ((tipo_ligacao == 0) || (tipo_ligacao == 2))
						{
				 		 data1_int = tensao_t;
						}
					else
						{
				 		 data1_int = tensao_rt;
						}
			 		 break;
		 			}
		 	#endif
	 	#endif
	 	case 4:
	 		{
	 		 data1_int = corrente_r;
	 		 break;
	 		}
		#if (monofasico == false)
			#if (padrao_referencia == true)
			 	case 5:
			 	case 6:{
					data1_int = corrente_r;
			 		break;
		 			}
			#else
				case 5:
		 			{
			 		data1_int = corrente_s;
			 		break;
		 			}
				case 6:
		 			{
			 		data1_int = corrente_t;
			 		break;
		 			}
		 	#endif
	 	#endif
	 	case 7:
	 		{
	 		 data1_int = fator_pot_r;
	 		 break;
	 		}
		#if (monofasico == false)
			#if (padrao_referencia == true)
			 	case 8:
			 	case 9:
			 	case 10:{
					data1_int = fator_pot_r;
			 		break;
		 			}
			#else
				case 8:{
			 		data1_int = fator_pot_s;
			 		break;
		 			}
				case 9:{
			 		data1_int = fator_pot_t;
			 		break;
		 			}
			 	case 10:{
					data1_int = fator_pot;
					break;
		 			}
		 	#endif
	 	#endif
	 	case 11:
	 		{
			#if (monofasico == true)
				#if (com_rep == true)
					if (modo_rep == 1)
						{
				 		 data1_int = pot_ativa_tot;
		 				}
		 			else
		 				{
				 		 data1_int = pot_ativa_r;
			 			}
			 	#else
			 		 data1_int = pot_ativa_r;
			 	#endif
		 	#else
		 		 data1_int = pot_ativa_r;
		 	#endif
	 		 break;
	 		}
		#if (monofasico == false)
			#if (padrao_referencia == true)
			 	case 12:
			 	case 13:
			 	case 14:
			 	case 15:{
					data1_int = pot_ativa_r;
			 		break;
		 			}
			#else
			 	case 12:{
					data1_int = pot_ativa_s;
					break;
		 			}
			 	case 13:{
					data1_int = pot_ativa_t;
					break;
		 			}
		 		case 14:{
					aux_l1 = pot_ativa_r;
					aux_l1 += pot_ativa_s;
					aux_l1 += pot_ativa_t;
					data1_int = (word)((aux_l1 / 32) >> 16);
					break;
		 			}
			 	case 15:{
					aux_l1 = pot_ativa_r;
					aux_l1 += pot_ativa_s;
					aux_l1 += pot_ativa_t;
					data1_int = (word)(aux_l1 / 32);
					break;
		 			}
		 	#endif
	 	#endif
	 	case 16:
	 		{
			#if (monofasico == true)
				#if (com_rep == true)
					if (modo_rep == 1)
						{
				 		 data1_int = pot_reativa_tot;
		 				}
		 			else
		 				{
				 		 data1_int = pot_reativa_r;
			 			}
			 	#else
			 		 data1_int = pot_reativa_r;
			 	#endif
		 	#else
		 		 data1_int = pot_reativa_r;
		 	#endif
	 		 break;
	 		}
		#if (monofasico == false)
			#if (padrao_referencia == true)
			 	case 17:
			 	case 18:
			 	case 19:
			 	case 20:{
					data1_int = pot_reativa_r;
			 		break;
		 			}
			#else
			 	case 17:{
					data1_int = pot_reativa_s;
					break;
					}
				case 18:{
			 		data1_int = pot_reativa_t;
			 		break;
		 			}
			 	case 19:{
			 		aux_l1 = pot_reativa_r;
			 		aux_l1 += pot_reativa_s;
			 		aux_l1 += pot_reativa_t;
			 		data1_int = (word)((aux_l1 / 32) >> 16);
			 		break;
			 		}
		 		case 20:{
			 		aux_l1 = pot_reativa_r;
			 		aux_l1 += pot_reativa_s;
			 		aux_l1 += pot_reativa_t;
			 		data1_int = (word)(aux_l1 / 32);
					break;
		 			}
		 	#endif
	 	#endif
	 	case 21:
			{
			#if (monofasico == true)
				#if (com_rep == true)
					if (modo_rep == 1)
						{
				 		 data1_int = pot_aparente_tot;
		 				}
		 			else
		 				{
				 		 data1_int = pot_aparente_r;
			 			}
			 	#else
			 		 data1_int = pot_aparente_r;
			 	#endif
		 	#else
		 		 data1_int =  pot_aparente_r;
		 	#endif
	 		 break;
	 		}
		#if (monofasico == false)
			#if (padrao_referencia == true)
			 	case 22:
			 	case 23:
			 	case 24:
			 	case 25:{
					data1_int = pot_aparente_r;
			 		break;
		 			}
			#else
			 	case 22:
		 			{
			 		 data1_int =  pot_aparente_s;
			 		 break;
		 			}
		 		case 23:
			 		{
			 		 data1_int =  pot_aparente_t;
					 break;
		 			}
			 	case 24:
			 		{
			 		aux_l1 = pot_aparente_r;
			 		aux_l1 += pot_aparente_s;
			 		aux_l1 += pot_aparente_t;
			 		 data1_int = (word)((aux_l1 / 32) >> 16);
			 		 break;
		 			}
		 		case 25:
			 		{
			 		aux_l1 = pot_aparente_r;
			 		aux_l1 += pot_aparente_s;
			 		aux_l1 += pot_aparente_t;
					data1_int = (word)(aux_l1 / 32);
					break;
		 			}
		 		#endif
	 	#endif
	 	case 26:
	 		{
	 		 data1_int = frequencia;
	 		 break;
	 		}
		#if (com_consumo == true) 
		 	case 27:
	 			{
				#if (st5x == true)
		 			 data1_int = (int16)(consumo_ati >> 16);
				#elif (st92 == true)
		 			 data1_int = (int16)(consumo_ati >> 16);
				#elif (st94 == true)
		 			 data1_int = (int16)(consumo_ati >> 16);
				#else
		 			 data1_int = (int16)(consumo_ati >> 16);
				#endif
		 		break;
	 			}
		 	case 28:
	 			{
				#if (st5x == true)
		 		 	data1_int =  consumo_ati;
				#elif (st92 == true)
		 		 	data1_int =  consumo_ati;
				#elif (st94 == true)
		 		 	data1_int =  consumo_ati;
				#else
		 		 	data1_int = consumo_ati;
				#endif
		 		break;
	 			}
		 	case 29:
	 			{
	 			 data1_int =  dem_ativa;
	 		 	break;
		 		}
	 		case 30:
	 			{
	 			 data1_int = (int16)(consumo_reati >> 16);
				break;
	 			}
		 	case 31:
	 			{
	 			 data1_int = consumo_reati;
		 		break;
	 			}
		 	case 32:
	 			{
	 			 data1_int =  dem_reativa;
	 		 	break;
		 		}
	 		case 33:
	 			{
	 		 	data1_int =  dem_media_ativa;
		 		break;
	 			}
	 		case 34:
		 		{
	 			 data1_int =  dem_maxima_ativa;
	 			break;
	 			}
		 	case 35:
	 			{
	 			 data1_int =  dem_media_aparente;
		 		break;
	 			}
		 	case 36:
	 			{
	 			 data1_int =  dem_maxima_aparente;
		 		break;
	 			}
	 	#elif (st8500c == true)
		 	case 27:
	 			{
	 			data1_int = (int16)(consumo_ati >> 16);
		 		break;
	 			}
		 	case 28:
	 			{
	 		 	data1_int = consumo_ati;
		 		break;
	 			}
		 	case 29:
	 			{
	 			data1_int =  dem_ativa;
	 		 	break;
		 		}
	 		case 30:
	 			{
				data1_int = (int16)(consumo_reati >> 16);
				break;
	 			}
		 	case 31:
	 			{
	 			data1_int = consumo_reati;
		 		break;
	 			}
		 	case 32:
	 			{
	 			data1_int =  dem_reativa;
	 		 	break;
		 		}
	 		case 33:
	 			{
	 		 	data1_int =  dem_media_ativa;
		 		break;
	 			}
	 		case 34:
		 		{
	 			data1_int =  dem_maxima_ativa;
	 			break;
	 			}
		 	case 35:
	 			{
	 			data1_int =  dem_media_aparente;
		 		break;
	 			}
		 	case 36:
	 			{
	 			data1_int =  dem_maxima_aparente;
		 		break;
	 			}
	 	#endif
 		case 37:
 			{
			#if (monofasico == true)
				data1_int = pot_req_r;
			#else
				aux_l1 = pot_req_r;
				aux_l1 += pot_req_s;
				aux_l1 += pot_req_t;
		 		data1_int =  aux_l1 / 32 ;
			#endif
	 		break;
	 		}
	 	case 38:
	 		{
			#if (monofasico == true)
				data1_int = pot_exec_r;
			#else
				aux_l1 = pot_exec_r;
				aux_l1 += pot_exec_s;
				aux_l1 += pot_exec_t;
		 		data1_int =  aux_l1 / 32;
			#endif
	 		break;
	 		}
		#if (com_consumo == true)
		 	case 39:
	 			{
	 			data1_int =  dem_maxima_ativa_ant;
	 		 	break;
		 		}
		 	case 40:
	 			{
	 			data1_int =  dem_maxima_aparente_ant;
	 		 	break;
		 		}
		#endif
	 	case 41:
	 		{
	 		data1_int = tensao_rs;
	 		break;
	 		}
		#if (monofasico == false)
		 	case 42:
	 			{
		 		data1_int = tensao_st;
		 		break;
	 			}
	 		case 43:
	 			{
		 		data1_int = tensao_rt;
		 		break;
	 			}
	 	#endif
	 	case 44:
	 		{
	 		data1_int = tensao_rs_na_alta;
	 		break;
	 		}
		#if (monofasico == false)
		 	case 45:
	 			{
		 		data1_int = tensao_st_na_alta;
		 		break;
	 			}
		 	case 46:
	 			{
		 		data1_int = tensao_rt_na_alta;
		 		break;
	 			}
	 		case 47:
	 			{
		 		data1_int = tensao_tri;
		 		break;
	 			}
	 		case 48:
	 			{
		 		data1_int =  corrente_tri;
		 		break;
	 			}
	 	#endif
		case 49:
			{
			data1_int = status_equipamento_H;
			break;
			}
		case 50:
			{
			data1_int = status_equipamento_L;
			break;
			}
		#if (ST92 == true)
		 	case 51:
		 		{
		 		 data1_int = cor_maxima_r;
		 		 break;
		 		}
		 	case 52:
		 		{
		 		 data1_int = cor_maxima_s;
		 		 break;
		 		}
		 	case 53:
		 		{
		 		 data1_int = cor_maxima_t;
		 		 break;
		 		}
		 	case 54:
		 		{
		 		 data1_int = pot_ativa_max_r;
		 		 break;
		 		}
		 	case 55:
		 		{
		 		 data1_int = pot_ativa_max_r;
		 		 break;
		 		}
		 	case 56:
		 		{
		 		 data1_int = pot_ativa_max_r;
		 		 break;
		 		}
		 #endif
	 		
	 		

		#if (chip_cs5460a == true)
			case 70:
				{
		 		data1_int = nro_kw_r << 5;
				break;
				}
		#endif
	 		
	 	 default:
	 		{
	 		data1_int = 0;
	 		break;
	 		}
	 	}
}	    

void wr_byte_regs_modbus(void)
{   
	addr = 0;
	data1_int = data_modbus;
	data1 = data_modbus;
	 switch(addr_regs_modbus)
	 	{
	 	case 1:
	 		{
	 		 addr = ee_ten_nomi;
	 		 ten_nomi = data1_int;
	 		 break;
	 		}
	 	case 2:
	 		{
		 	#if (portatil == true)
			 	#if (se_com_flex == true)
					#if (versao_pci_st96 >= 6)
						time_out_troca_ponteira = 10;
					#endif
					recarrega_ponteira = true;
					addr = ee_tipo_ponteira;
					tipo_ponteira = data1;
					valor_tc = tabela_pt[tipo_ponteira];
					busca_mul_tc();
		 			goto salva_byte;
			 	#else
			 		addr = ee_valor_tc;
			 		valor_tc = data1_int;
		 		#endif
		 	#else
		 		addr = ee_valor_tc;
		 		valor_tc = data1_int;
				#if (tc_fixo == true)
					#if (st94 == false) || (st92 == false)
						busca_mul_tc();
					#else
						calcula_mul_tc();
					#endif
				#endif
	 		#endif
	 		 break;
	 		}
	 	case 3:
	 		{
	 		 addr = ee_set_point;
	 		 set_point = data1_int;
	 		 goto salva_byte;
             break;
	 		}
	 	case 4:
	 		{
	 		 addr = ee_endereco;
	 		 endereco = data1_int;
	 		 goto salva_byte;
             break;
	 		}
	 	case 5:
	 		{
	 		 addr = ee_intervalo_reg;
	 		 intervalo_reg = data1_int;
	 		 break;
	 		}
	 	case 6:
	 		{
	 		 addr = ee_intervalo_integra;
	 		 intervalo_integra = data1_int;
	 		 goto salva_byte;
             break;
	 		}
	 	case 7:
	 		{
	 		 addr = ee_ala_fp_ind;
 	 		 ala_fp_ind = data1_int;
	 		 goto salva_byte;
             break;
	 		}
	 	case 8:
	 		{
	 		 addr = ee_ala_fp_cap;
 	 		 ala_fp_cap = data1_int;
	 		 goto salva_byte;
             break;
	 		}
	 	case 9:
	 		{
	 		 addr = ee_ala_ten_a;
 	 		 ala_ten_a = data1_int;
	 		 goto salva_byte;
             break;
	 		}
	 	case 10:
	 		{
	 		 addr = ee_ala_ten_b;
 	 		 ala_ten_b = data1_int;
	 		 goto salva_byte;
             break;
	 		}
	 	case 11:
	 		{
	 		 addr = ee_ala_sc;
 	 		 ala_sc = data1_int;
	 		 goto salva_byte;
             break;
	 		}
	 	case 12:
	 		{
	 		 addr = ee_ala_chtt;
 	 		 ala_chtt = data1_int;
	 		 goto salva_byte;
             break;
	 		}
		#if (com_regs == true)
	 		case 13:{
				#if (com_relogio == true)
	 		 		addr = ds_ptr_regs;
					goto salva_word_nvr;
                    break;
				#else
	 		 		addr = ee_ptr_regs;
					break;
				#endif
	 		}
	 		case 14:{
				#if (com_relogio == true)
	 			 	addr = ds_ptr_ocor;
					goto salva_byte_nvr;
                    break;
				#else
					addr = ee_ptr_rocor;
					break;
				#endif
	 		}
 			case 15:{
				#if (com_relogio == true)
	 			 	addr = ds_ptr_cht;
					goto salva_byte_nvr;
				#else
					addr = ee_ptr_cht;
				#endif
                    break;
	 		}
	 		case 16:{
	 			addr = ee_forma_reg_cht;
 	 		 	forma_reg_cht = data1_int;
	 	 		goto salva_byte;
                break;
	 		}
	 	#endif
 		case 17:
	 		{
	 		 addr = ee_valor_tp;
	 		 valor_tp = data1_int;
	 		 break;
	 		}
 		case 18:
	 		{
	 		 addr = ee_baud_rate;
	 		 baud_rate = data1_int;
	 		 break;
	 		}
 		case 19:
	 		{
	 		 addr = ee_ala_chtc;
 	 		 ala_chtc = data1_int;
	 		 goto salva_byte;
             break;
	 		}
		#if (com_regs == true)
	 		case 20:{
				#if (com_relogio == true)
	 				addr = ds_banco_escrita;
		 		 	goto salva_byte_nvr;
				#else
					addr = ee_banco_escrita;
			 		goto salva_byte;
				#endif
                    break;
	 		}
 			case 21:{
				#if (com_relogio == true)
	 			 	addr = ds_banco_leitura;
	 				goto salva_byte_nvr;
				#else
					addr = ee_banco_leitura;
			 		goto salva_byte;
				#endif
                    break;
			 	}
		#endif
	 	case 22:
	 		{
	 		 dia = data1;
	 		 goto salva_calend;
             break;
	 		}
	 	case 23:
	 		{
	 		 mes = data1;
	 		 goto salva_calend;
             break;
	 		}
	 	case 24:
	 		{
	 		 ano = data1;
	 		 goto salva_calend;
             break;
	 		}
	 	case 25:
	 		{
	 		 hora = data1;
	 		 goto salva_calend;
             break;
	 		}
	 	case 26:
	 		{
	 		 minuto = data1;
	 		 goto salva_calend;
             break;
	 		}
 		case 27:
	 		{
	 		 segundo = data1;
	 		 goto salva_calend;
             break;
	 		}
	 	case 28:
	 		{
	 		 addr = ee_ala_subc;
 	 		 ala_subc = data1_int;
	 		 goto salva_byte;
             break;
		 	}
		#if (portatil == true)
			case 29:
				{
		 		 addr = ee_dia_liga;
		 		 dia_liga = data1;
		 		 goto salva_byte;
                 break;
				}		 	
			case 30:
				{
		 		 addr = ee_hora_liga;
		 		 hora_liga = data1;
		 		 goto salva_byte;
                 break;
				}		 	
			case 31:
				{
		 		 addr = ee_minuto_liga;
		 		 minuto_liga = data1;
		 		 goto salva_byte;
                 break;
				}		 	
			case 32:
				{
		 		 addr = ee_dia_desliga;
		 		 dia_desliga = data1;
		 		 goto salva_byte;
                 break;
				}		 	
			case 33:
				{
		 		 addr = ee_hora_desliga;
		 		 hora_desliga = data1;
		 		 goto salva_byte;
                 break;
				}		 	
			case 34:
				{
		 		 addr = ee_minuto_desliga;
		 		 minuto_desliga = data1;
		 		 goto salva_byte;
                 break;
				}
			case 35:
				{
		 		 addr = ee_prog_time;
		 		 prog_time = data1;
		 		 goto salva_byte;
                 break;
				}		 	
			case 36:
				{
		 		 addr = ee_fila_circular;
		 		 fila_circular = data1;
		 		 goto salva_byte;
                 break;
				}
		#endif
		case 37:
			{
	 		 addr = ee_hora_ponta;
	 		 hora_ponta = data1;
	 		 goto salva_byte;
             break;
			}
		case 38:
			{
			 addr = ee_minuto_ponta;
	 		 minuto_ponta = data1;
	 		 goto salva_byte;
             break;
			}
		case 39:
			{
	 		 addr = ee_hora_final_ponta;
	 		 hora_final_ponta = data1;
	 		 goto salva_byte;
             break;
			}
		case 40:
			{
	 		 addr = ee_minuto_final_ponta;
	 		 minuto_final_ponta = data1;
	 		 goto salva_byte;
             break;
			}
		case 41:
			{
	 		 addr = ee_tipo_ligacao;
	 		 tipo_ligacao = data1;
	 		 goto salva_byte;
             break;
			}
	 	case 42:
	 		{
				break;
		 	}
	 	case 43:
	 		{
				break;
		 	}
		case 44:
	 		{
			goto salva_prog_flash;
            break;
		 	}
		case 45:
	 		{
			if (modo_funca != data1)
				{
				#if (funcao_505 == true)
					inic_tensoes_505();
				#endif
				}
	 		 addr = ee_modo_funca;
	 		 modo_funca = data1;
	 		 goto salva_byte;
             break;
		 	}
		case 46:
			{
			goto salva_prog_flash;
            break;
			}
		case 47:
			{
			#if (com_menu == true)
	 		 	addr = ee_idioma;
		 		 idioma = data1;
	 			 goto salva_byte;
			#else
				goto salva_prog_flash;
			#endif
                break;
			}
		case 48:
			{
	 		 addr = ee_ala_skw;
	 		 ala_skw = data1;
	 		 goto salva_byte;
             break;
			}
		#if (com_alarme_demanda == true)
			case 49:
				{
				addr = ee_ala_demanda_ativa;
			 	ala_demanda_ativa = data1_int;
			 	#if (st8500c == true)
		 		 	goto salva_byte;
//			 	#else
			 	#endif
				break;
			 	}
		#endif
/*		#if (st5x==true)		
			#if (com_saida_pulsos == true)
				case 55:
					{
					addr = ee_const_saida_kw;
					const_saida_kw = data1_int ;
					break;
					}
				case 56:
					{
					addr = ee_const_saida_kvar;
					const_saida_kvar = data1_int ;
					break;
					}
				case 57:
					{
					addr = ee_qual_variavel_pulsa;
					qual_variavel_pulsa = data1_int ;
		 		 	goto salva_byte;
                    break;
					}
			#endif					
		#endif												*/

			
//		#if (controlador == true)
			case 98:			
				{
		 		 addr = 0;
				aux_tempo_repouso[data1] = 0;
				#if (st8500c == true)
					ligar_carga(data1);
				#else
					ligar_banco(data1);
				#endif
				break;
				}
			case 99:			
				{
		 		 addr = 0;
				#if (st8500c == true)
					desligar_carga(data1);
				#else
					desligar_banco(data1);
				#endif
				break;
				}
//		#endif
	 	case 2000:
	 		{
			#if (portatil == 1)
				#if (se_com_flex == true)
					aux_w1 = ee_off_fp_9001g1;
					aux_w1 += tipo_ponteira;
		 			addr = aux_w1;
		 			off_cor_r = data1_int;
					off_set_fp[aux_b4] = data1_int;
					recarrega_ponteira = true;
				#else
					aux_w1 = ee_off_fp_20;
					for (aux_b4 = 0; aux_b4 < NRO_POSI_TC; aux_b4++)
						{
						if (valor_tc == tabela_tc[aux_b4])
							{
							break;
							}
						aux_w1++;
						}
		 			addr = aux_w1;
		 			off_cor_r = data1_int;
					off_set_fp[aux_b4] = data1_int;
				#endif
	 			goto salva_byte;
			#else
				#if (ade7754 == true)
		 			addr = ee_fase_r;
		 			fase_r = data1_int;
			 		goto salva_byte;
				#else
		 			addr = ee_off_cor_r;
			 		off_cor_r = data1_int;
			 		goto salva_byte;
				#endif
                    break;
			#endif
	 		}
	 	case 2001:
	 		{
			#if (ade7754 == true)
	 			addr = ee_fase_s;
		 		fase_s = data1_int;
	 			goto salva_byte;
			#else
	 			addr = ee_off_cor_s;
		 		off_cor_s = data1_int;
	 			goto salva_byte;
			#endif
                break;
	 		}
	 	case 2002:
	 		{
			#if (ade7754 == true)
	 			addr = ee_fase_t;
		 		fase_t = data1_int;
	 			goto salva_byte;
			#else
				#if (portatil == false)
		 			addr = ee_defasagem;
			 		defasagem = data1_int;
		 			goto salva_byte;
		 		#endif
			#endif
			break;
	 		}
	 	case 2003:
	 		{
	 		addr = ee_os_ten_r1;
	 		os_ten_r1 = data1_int;
 			goto salva_byte;
            break;
	 		}
	 	case 2006:
	 		{
	 		addr = ee_os_ten_r2;
	 		os_ten_r2 = data1_int;
 			goto salva_byte;
            break;
	 		}
	 	#if (monofasico == false)
		 	case 2004:
	 			{
	 			addr = ee_os_ten_s1;
		 		os_ten_s1 = data1_int;
 				goto salva_byte;
                break;
	 			}
		 	case 2005:
	 			{
	 			addr = ee_os_ten_t1;
		 		os_ten_t1 = data1_int;
 				goto salva_byte;
                break;
	 			}
	 		case 2007:
	 			{
	 			addr = ee_os_ten_s2;
		 		os_ten_s2 = data1_int;
 				goto salva_byte;
                break;
	 			}
	 		case 2008:
	 			{
	 			addr = ee_os_ten_t2;
		 		os_ten_t2 = data1_int;
 				goto salva_byte;
                break;
	 			}
	 	#else
		 	case 2004:
	 		case 2005:
	 		case 2007:
	 		case 2008:
	 			{
	 			addr = 0;
 				goto salva_byte;
                break;
	 			}
	 	#endif
		#if (portatil == true)
			#if (se_com_flex == true)
				case 2009:
					{
					aux_w1 = ee_os_cor_r_9001g1;
					addr = aux_w1 + (tipo_ponteira * 3);
					data_modbus = data1_int;
					recarrega_ponteira = true;
		 			goto salva_byte;
                    break;
					}
				case 2010:
					{
					aux_w1 = ee_os_cor_s_9001g1;
					addr = aux_w1 + (tipo_ponteira * 3);
					data_modbus = data1_int;
					recarrega_ponteira = true;
		 			goto salva_byte;
                    break;
					}
				case 2011:
					{
					aux_w1 = ee_os_cor_t_9001g1;
					addr = aux_w1 + (tipo_ponteira * 3);
					data_modbus = data1_int;
					recarrega_ponteira = true;
		 			goto salva_byte;
                    break;
					}
			#else
				case 2009:
					{
					#if (se_com_flex == true)
						#error colocar tratamento por ponteira
					#else
						aux_w1 = ee_os_cor_r_20;
						for (aux_b1=0; aux_b1 < NRO_POSI_TC; aux_b1++)
							{
							if (valor_tc == tabela_tc[aux_b1])
								{
								addr = aux_w1;
								os_cor_pt_r[aux_b1] = data1;
								write_byte(aux_w1, os_cor_pt_r[aux_b1]);
								break;
								}
							aux_w1 += 3;
							}
						data_modbus = data1_int;
						goto salva_prog_flash_10;
					#endif
                        break;
					}
				case 2010:
					{
					#if (se_com_flex == true)
						#error colocar tratamento por ponteira
					#else
						aux_w1 = ee_os_cor_s_20;
						for (aux_b1=0; aux_b1 < NRO_POSI_TC; aux_b1++)
							{
							if (valor_tc == tabela_tc[aux_b1])
								{
								addr = aux_w1;
								os_cor_pt_s[aux_b1] = data1;
								write_byte(aux_w1, os_cor_pt_s[aux_b1]);
								break;
								}
							aux_w1 += 3;
							}
						data_modbus = data1_int;
						goto salva_prog_flash_10;
					#endif
                        break;
					}
				case 2011:
					{
					#if (se_com_flex == true)
						#error colocar tratamento por ponteira
					#else
						aux_w1 = ee_os_cor_t_20;
						for (aux_b1=0; aux_b1 < NRO_POSI_TC; aux_b1++)
							{
							if (valor_tc == tabela_tc[aux_b1])
								{
								addr = aux_w1;
								os_cor_pt_t[aux_b1] = data1;
								write_byte(aux_w1, os_cor_pt_t[aux_b1]);
								break;
								}
							aux_w1 += 3;
							}
						data_modbus = data1_int;
						goto salva_prog_flash_10;
					#endif
                        break;
					}
			#endif
		#else
		 	case 2009:
		 		{
		 		addr = ee_os_cor_r;
	 			os_cor_r = data1_int;
	 			goto salva_byte;
                break;
		 		}
		 	case 2010:
		 		{
		 		addr = ee_os_cor_s;
	 			os_cor_s = data1_int;
	 			goto salva_byte;
                break;
		 		}
		 	case 2011:
		 		{
		 		addr = ee_os_cor_t;
	 			os_cor_t = data1_int;
	 			goto salva_byte;
                break;
		 		}
		#endif
		#if (portatil == true)
			#if (se_com_flex == true)
			#else
				// 20
			 	case 2012:
			 		{
			 		addr = ee_os_cor_r_20;
			 		os_cor_pt_r[0] = data1_int;
		 			goto salva_byte;
                    break;
			 		}
			 	case 2013:
			 		{
			 		addr = ee_os_cor_s_20;
			 		os_cor_pt_s[0] = data1_int;
		 			goto salva_byte;
                    break;
			 		}
			 	case 2014:
			 		{
			 		addr = ee_os_cor_t_20;
			 		os_cor_pt_t[0] = data1_int;
		 			goto salva_byte;
                    break;
			 		}
				// 200
			 	case 2015:
			 		{
			 		addr = ee_os_cor_r_200;
			 		os_cor_pt_r[1] = data1_int;
		 			goto salva_byte;
                    break;
			 		}
			 	case 2016:
			 		{
			 		addr = ee_os_cor_s_200;
			 		os_cor_pt_s[1] = data1_int;
		 			goto salva_byte;
                    break;
			 		}
			 	case 2017:
			 		{
			 		addr = ee_os_cor_t_200;
			 		os_cor_pt_t[1] = data1_int;
		 			goto salva_byte;
                    break;
			 		}
		
				// 300
			 	case 2018:
			 		{
			 		addr = ee_os_cor_r_300;
			 		os_cor_pt_r[2] = data1_int;
		 			goto salva_byte;
                    break;
			 		}
			 	case 2019:
			 		{
			 		addr = ee_os_cor_s_300;
			 		os_cor_pt_s[2] = data1_int;
		 			goto salva_byte;
                    break;
			 		}
			 	case 2020:
			 		{
			 		addr = ee_os_cor_t_300;
			 		os_cor_pt_t[2] = data1_int;
		 			goto salva_byte;
                    break;
			 		}
				// 600
				#if (viercon == true)
				#else
				 	case 2021:
				 		{
				 		addr = ee_os_cor_r_600;
				 		os_cor_pt_r[3] = data1_int;
			 			goto salva_byte;
                        break;
				 		}
				 	case 2022:
				 		{
				 		addr = ee_os_cor_s_600;
				 		os_cor_pt_s[3] = data1_int;
			 			goto salva_byte;
                        break;
				 		}
				 	case 2023:
				 		{
				 		addr = ee_os_cor_t_600;
				 		os_cor_pt_t[3] = data1_int;
			 			goto salva_byte;
                        break;
				 		}
					// 1000
				 	case 2024:
				 		{
				 		addr = ee_os_cor_r_1000;
				 		os_cor_pt_r[4] = data1_int;
			 			goto salva_byte;
                        break;
				 		}
				 	case 2025:
				 		{
				 		addr = ee_os_cor_s_1000;
				 		os_cor_pt_s[4] = data1_int;
			 			goto salva_byte;
                        break;
				 		}
				 	case 2026:
				 		{
				 		addr = ee_os_cor_t_1000;
				 		os_cor_pt_t[4] = data1_int;
			 			goto salva_byte;
                        break;
				 		}
					// 1500
				 	case 2027:
				 		{
				 		addr = ee_os_cor_r_1500;
				 		os_cor_pt_r[5] = data1_int;
			 			goto salva_byte;
                        break;
				 		}
				 	case 2028:
				 		{
				 		addr = ee_os_cor_s_1500;
				 		os_cor_pt_s[5] = data1_int;
			 			goto salva_byte;
                        break;
				 		}
				 	case 2029:
				 		{
				 		addr = ee_os_cor_t_1500;
				 		os_cor_pt_t[5] = data1_int;
			 			goto salva_byte;
                        break;
				 		}
				 #endif
				#if (ponteira_kyoritsu == true)
				#else
					#if (viercon == true)
					#else
						// 2000
					 	case 2030:
					 		{
					 		addr = ee_os_cor_r_2000;
					 		os_cor_pt_r[6] = data1_int;
				 			goto salva_byte;
                            break;
					 		}
					 	case 2031:
					 		{
					 		addr = ee_os_cor_s_2000;
					 		os_cor_pt_s[6] = data1_int;
				 			goto salva_byte;
                            break;
					 		}
					 	case 2032:
					 		{
					 		addr = ee_os_cor_t_2000;
					 		os_cor_pt_t[6] = data1_int;
				 			goto salva_byte;
                            break;
					 		}
						// 3000
					 	case 2033:
					 		{
					 		addr = ee_os_cor_r_3000;
					 		os_cor_pt_r[7] = data1_int;
				 			goto salva_byte;
                            break;
					 		}
					 	case 2034:
					 		{
					 		addr = ee_os_cor_s_3000;
					 		os_cor_pt_s[7] = data1_int;
				 			goto salva_byte;
                            break;
					 		}
					 	case 2035:
					 		{
					 		addr = ee_os_cor_t_3000;
					 		os_cor_pt_t[7] = data1_int;
				 			goto salva_byte;
                            break;
					 		}
						// 6000
					 	case 2036:
					 		{
					 		addr = ee_os_cor_r_6000;
					 		os_cor_pt_r[8] = data1_int;
				 			goto salva_byte;
                            break;
					 		}
					 	case 2037:
					 		{
					 		addr = ee_os_cor_s_6000;
					 		os_cor_pt_s[8] = data1_int;
				 			goto salva_byte;
                            break;
					 		}
					 	case 2038:
					 		{
					 		addr = ee_os_cor_t_6000;
					 		os_cor_pt_t[8] = data1_int;
				 			goto salva_byte;
                            break;
					 		}
					 #endif
				#endif
			 	case 2039:
			 		{
			 		addr = ee_off_fp_20;
			 		off_set_fp[0] = data1_int;
		 			goto salva_byte;
                    break;
			 		}
			 	case 2040:
			 		{
			 		addr = ee_off_fp_200;
			 		off_set_fp[1] = data1_int;
		 			goto salva_byte;
                    break;
			 		}
			 	case 2041:
			 		{
			 		addr = ee_off_fp_300;
			 		off_set_fp[2] = data1_int;
			 		goto salva_byte;
                    break;
			 		}
			 	#if (viercon == true)
			 	#else
				 	case 2042:
				 		{
				 		addr = ee_off_fp_600;
				 		off_set_fp[3] = data1_int;
				 		goto salva_byte;
                        break;
				 		}
				 	case 2043:
				 		{
				 		addr = ee_off_fp_1000;
				 		off_set_fp[4] = data1_int;
				 		goto salva_byte;
                        break;
				 		}
				 	case 2044:
				 		{
				 		addr = ee_off_fp_1500;
				 		off_set_fp[5] = data1_int;
				 		goto salva_byte;
				 		}
				 #endif
				#if (ponteira_kyoritsu == true)
				#else
					#if (viercon == true)
					#else
					 	case 2045:
					 		{
					 		addr = ee_off_fp_2000;
					 		off_set_fp[6] = data1_int;
					 		goto salva_byte;
					 		}
					 	case 2046:
					 		{
					 		addr = ee_off_fp_3000;
					 		off_set_fp[7] = data1_int;
					 		goto salva_byte;
					 		}
					 	case 2047:
					 		{
					 		addr = ee_off_fp_6000;
					 		off_set_fp[8] = data1_int;
					 		goto salva_byte;
					 		}
					 #endif
				 #endif
			 #endif
		#endif

	 	case 2050:
	 		{
			#if (portatil == true)
				#if (se_com_flex == true)
					addr = ee_os_pot_r_9001g1;
			 		addr += (tipo_ponteira * 3);	
			 		os_pot_r = data1_int;
					os_pot_pt_r[tipo_ponteira] = data1_int;
					recarrega_ponteira = true;
				#else
					aux_w1 = ee_os_pot_r_20;
					for (aux_b4=0; aux_b4 < NRO_POSI_TC; aux_b4++)
						{
						if (valor_tc == tabela_tc[aux_b4])
							{
							break;
							}
						aux_w1 += 3;
						}
			 		addr = aux_w1;
			 		os_pot_r = data1_int;
					os_pot_pt_r[aux_b4] = data1_int;
				#endif
			#else
		 		addr = ee_os_pot_r;
		 		os_pot_r = data1_int;
			#endif
	 		goto salva_byte;
            break;
	 		}
	 	case 2051:
	 		{
			#if (portatil == true)
				#if (se_com_flex == true)
					addr = ee_os_pot_s_9001g1;
			 		addr += (tipo_ponteira * 3);	
			 		os_pot_s = data1_int;
					os_pot_pt_s[tipo_ponteira] = data1_int;
					recarrega_ponteira = true;
				#else
					aux_w1 = ee_os_pot_s_20;
					for (aux_b4=0; aux_b4 < NRO_POSI_TC; aux_b4++)
						{
						if (valor_tc == tabela_tc[aux_b4])
							{
							break;
							}
						aux_w1 += 3;
						}
			 		addr = aux_w1;
			 		os_pot_s = data1_int;
					os_pot_pt_s[aux_b4] = data1_int;
				#endif
			#else
		 		addr = ee_os_pot_s;
		 		os_pot_s = data1_int;
			#endif
	 		goto salva_byte;
            break;
	 		}
	 	case 2052:
	 		{
			#if (portatil == true)
				#if (se_com_flex == true)
					addr = ee_os_pot_t_9001g1;
			 		addr += (tipo_ponteira * 3);	
			 		os_pot_t = data1_int;
					os_pot_pt_t[tipo_ponteira] = data1_int;
					recarrega_ponteira = true;
				#else
					aux_w1 = ee_os_pot_t_20;
					for (aux_b4=0; aux_b4 < NRO_POSI_TC; aux_b4++)
						{
						if (valor_tc == tabela_tc[aux_b4])
							{
							break;
							}
						aux_w1 += 3;
						}
			 		addr = aux_w1;
			 		os_pot_t = data1_int;
					os_pot_pt_t[aux_b4] = data1_int;
				#endif
			#else
		 		addr = ee_os_pot_t;
		 		os_pot_t = data1_int;
			#endif
	 		goto salva_byte;
            break;
	 		}


		#if (portatil == true)
			#if (se_com_flex == true)
				case 2053:
				case 2054:
				case 2055:
				case 2056:
				case 2057:
				case 2058:
				case 2059:
				case 2060:
				case 2061:
				case 2062:
				case 2063:
				case 2064:
				case 2065:
				case 2066:
				case 2067:
				case 2068:
				case 2069:
				case 2070:
				case 2071:
				case 2072:
				case 2073:
				case 2074:
				case 2075:
				case 2076:
				case 2077:
				case 2078:
				case 2079:
				case 2080:
				case 2081:
				case 2082:
				case 2083:
				case 2084:
				case 2085:
				case 2086:
				case 2087:
				case 2088:
				case 2089:
				case 2090:
				case 2091:
				case 2092:
				case 2093:
				case 2094:
				case 2095:
				case 2096:
				case 2097:
				case 2098:
				case 2099:
				case 2100:
				case 2101:
				case 2102:
				case 2103:
				case 2104:
				case 2105:
				case 2106:
					{
					break;
					}
			#else
				// 20
			 	case 2053:
			 		{
			 		addr = ee_os_pot_r_20;
			 		os_pot_pt_r[0] = data1_int;
			 		goto salva_byte;
			 		}
			 	case 2054:
			 		{
			 		addr = ee_os_pot_s_20;
			 		os_pot_pt_s[0] = data1_int;
			 		goto salva_byte;
			 		}
			 	case 2055:
			 		{
			 		addr = ee_os_pot_t_20;
			 		os_pot_pt_t[0] = data1_int;
			 		goto salva_byte;
			 		}
				// 200
			 	case 2056:
			 		{
			 		addr = ee_os_pot_r_200;
			 		os_pot_pt_r[1] = data1_int;
			 		goto salva_byte;
			 		}
			 	case 2057:
			 		{
			 		addr = ee_os_pot_s_200;
			 		os_pot_pt_s[1] = data1_int;
			 		goto salva_byte;
			 		}
			 	case 2058:
			 		{
			 		addr = ee_os_pot_t_200;
			 		os_pot_pt_t[1] = data1_int;
			 		goto salva_byte;
			 		}
				// 300
			 	case 2059:
			 		{
			 		addr = ee_os_pot_r_300;
			 		os_pot_pt_r[2] = data1_int;
			 		goto salva_byte;
			 		}
			 	case 2060:
			 		{
			 		addr = ee_os_pot_s_300;
			 		os_pot_pt_s[2] = data1_int;
			 		goto salva_byte;
			 		}
			 	case 2061:
			 		{
			 		addr = ee_os_pot_t_300;
			 		os_pot_pt_t[2] = data1_int;
			 		goto salva_byte;
			 		}
				// 600
				#if (viercon == true)
				#else
				 	case 2062:
				 		{
				 		addr = ee_os_pot_r_600;
				 		os_pot_pt_r[3] = data1_int;
				 		goto salva_byte;
				 		}
				 	case 2063:
				 		{
				 		addr = ee_os_pot_s_600;
				 		os_pot_pt_s[3] = data1_int;
				 		goto salva_byte;
				 		}
				 	case 2064:
				 		{
				 		addr = ee_os_pot_t_600;
				 		os_pot_pt_t[3] = data1_int;
				 		goto salva_byte;
				 		}
					// 1000
				 	case 2065:
				 		{
				 		addr = ee_os_pot_r_1000;
				 		os_pot_pt_r[4] = data1_int;
				 		goto salva_byte;
				 		}
				 	case 2066:
				 		{
				 		addr = ee_os_pot_s_1000;
				 		os_pot_pt_s[4] = data1_int;
				 		goto salva_byte;
				 		}
				 	case 2067:
				 		{
				 		addr = ee_os_pot_t_1000;
				 		os_pot_pt_t[4] = data1_int;
				 		goto salva_byte;
				 		}
					// 1500
				 	case 2068:
				 		{
				 		addr = ee_os_pot_r_1500;
				 		os_pot_pt_r[5] = data1_int;
				 		goto salva_byte;
				 		}
				 	case 2069:
				 		{
				 		addr = ee_os_pot_s_1500;
				 		os_pot_pt_s[5] = data1_int;
				 		goto salva_byte;
				 		}
				 	case 2070:
				 		{
				 		addr = ee_os_pot_t_1500;
				 		os_pot_pt_t[5] = data1_int;
				 		goto salva_byte;
				 		}
				 #endif
				#if (ponteira_kyoritsu == true)
				#elif (viercon == true)
				#else
					// 2000
				 	case 2071:
				 		{
				 		addr = ee_os_pot_r_2000;
				 		os_pot_pt_r[6] = data1_int;
				 		goto salva_byte;
				 		}
				 	case 2072:
				 		{
				 		addr = ee_os_pot_s_2000;
				 		os_pot_pt_s[6] = data1_int;
				 		goto salva_byte;
				 		}
				 	case 2073:
				 		{
				 		addr = ee_os_pot_t_2000;
				 		os_pot_pt_t[6] = data1_int;
				 		goto salva_byte;
				 		}
					// 3000
				 	case 2074:
				 		{
				 		addr = ee_os_pot_r_3000;
				 		os_pot_pt_r[7] = data1_int;
				 		goto salva_byte;
				 		}
				 	case 2075:
				 		{
				 		addr = ee_os_pot_s_3000;
				 		os_pot_pt_s[7] = data1_int;
				 		goto salva_byte;
				 		}
				 	case 2076:
				 		{
				 		addr = ee_os_pot_t_3000;
				 		os_pot_pt_t[7] = data1_int;
				 		goto salva_byte;
				 		}
					// 6000
				 	case 2077:
				 		{
				 		addr = ee_os_pot_r_6000;
				 		os_pot_pt_r[8] = data1_int;
				 		goto salva_byte;
				 		}
				 	case 2078:
				 		{
				 		addr = ee_os_pot_s_6000;
				 		os_pot_pt_s[8] = data1_int;
				 		goto salva_byte;
				 		}
				 	case 2079:
				 		{
				 		addr = ee_os_pot_t_6000;
				 		os_pot_pt_t[8] = data1_int;
				 		goto salva_byte;
				 		}
				 #endif
			 #endif
		#endif

//      reservado entre 2100 e 2300 para parametros dos controladores de fator de potencia(200 partametros)
		#if (controlador == true)|| (st_prog == true)
			case 2100:
				{
				#if (st8500c == true)
					addr = ee_nro_cargas;
					nro_cargas = data1_int;
				#else
					addr = ee_nro_bancos_capacitor;
					nro_bancos_capacitor = data1_int;
				#endif
		 		goto salva_byte;
                break;
				}
			case 2101:
				{
				#if (st8500c == true)
					addr = ee_max_kw;
					max_kw = data1_int;
					break;
				#else
					addr = ee_max_kvar;
					max_kvar = data1_int;
			 		goto salva_byte;
				#endif
				}
			case 2102:
				{
				#if (st8500c == true)
					addr = ee_min_kw;
					min_kw = data1_int;
				#else
					addr = ee_min_kvar;
					min_kvar = data1_int;
				#endif
		 		goto salva_byte;
                break;
				}
			case 2103:
				{
				addr = ee_sequencia;
				sequencia = data1_int;
				calcular_bancos = 1;
		 		goto salva_byte;
                break;
				}
				
			case 2104:
				{
				addr = ee_tempo_aciona;
				tempo_aciona = data1_int;
		 		goto salva_byte;
                break;
				}
			case 2105:
				{
				#if (com_rep == true)
					if (modo_rep == 1)
						{
						addr = ee_cor_minima_rep;
						cor_minima_rep = data1_int;
						break;
						}
					else
						{
						addr = ee_cor_minima;
						cor_minima = data1_int;
				 		goto salva_byte;
                        break;
						}
				#else
					addr = ee_cor_minima;
					cor_minima = data1_int;
			 		goto salva_byte;
			 	#endif
                    break;
				}
			case 2106:
				{
				addr = ee_com_des_fp_ind_cap;
				com_des_fp_ind_cap = data1_int;
		 		goto salva_byte;
                break;
				}
			case 2107:
				{
				addr = ee_com_des_ten_a;
				com_des_ten_a = data1_int;
		 		goto salva_byte;
                break;
				}
			case 2108:
				{
				addr = ee_com_des_chtt;
				com_des_chtt = data1_int;
		 		goto salva_byte;
                break;
				}
			case 2109:
				{
				addr = ee_com_des_chtc;
				com_des_chtc = data1_int;
		 		goto salva_byte;
                break;
				}
			case 2110:
			case 2111:
			case 2112:
			case 2113:
			case 2114:
			case 2115:
			case 2116:
			case 2117:
			case 2118:
			case 2119:
			case 2120:
			case 2121:
			case 2122:
			case 2123:
			case 2124:
			case 2125:
				{
				#if (st8500c == true)
					aux_b4 = addr_regs_modbus - 2110;
					addr = ee_carga_1 + aux_b4;
					carga[aux_b4] = data1_int;
				#else
					calcular_bancos = 1;
					aux_b4 = addr_regs_modbus - 2110;
					addr = ee_banco_capacitor_1 + aux_b4;
					banco_capacitor[aux_b4] = data1_int;
				#endif					
		 		goto salva_byte;
                break;
				}
			case 2126:
			case 2127:
			case 2128:
			case 2129:
			case 2130:
			case 2131:
			case 2132:
			case 2133:
			case 2134:
			case 2135:
			case 2136:
			case 2137:
			case 2138:
			case 2139:
			case 2140:
			case 2141:
				{
				aux_b4 = addr_regs_modbus - 2126;
				addr = ee_tempo_repouso_1 + aux_b4;
				tempo_repouso[aux_b4] = data1_int;
		 		goto salva_byte;
                break;
				}
			case 2142:
				{
	 			 addr = ee_tempo_desaciona;
	 		 	 tempo_desaciona = data1;
		 		 goto salva_byte;
                 break;
				}
		#endif
		#if (st8500c == true)
			#if (com_tc == true)
				case 2145:
					{
		 			 addr = ee_valor_tc;
		 		 	 valor_tc = data1_int;
		 		 	 break;
					}
				case 2146:
					{
		 			 addr = ee_valor_tp;
		 		 	 valor_tp = data1_int;
		 		 	 break;
					}
			#endif
		#endif
		#if (com_rep == true)
			case 2144:
				{
	 			 addr = ee_modo_rep;
	 		 	 modo_rep = data1;
		 		 goto salva_byte;
                 break;
				}
			case 2145:
				{
	 			 addr = ee_fat_conv_ativa;
	 		 	 fat_conv_ativa = data1_int;
	 		 	 break;
				}
			case 2146:
				{
	 			 addr = ee_fat_conv_reativa;
	 		 	 fat_conv_reativa = data1_int;
	 		 	 break;
				}
		#endif

		#if (st8500c == true)
			case 2150:
			case 2151:
			case 2152:
			case 2153:
			case 2154:
			case 2155:
			case 2156:
			case 2157:
			case 2158:
			case 2159:
			case 2160:
			case 2161:
			case 2162:
			case 2163:
			case 2164:
			case 2165:
				{
				aux_b4 = addr_regs_modbus - 2150;
				forma_controle[aux_b4] = data1_int;
				addr = ee_forma_controle + aux_b4;
		 		goto salva_byte;
                break;
				}
			case 2170:
			case 2171:
			case 2172:
			case 2173:
			case 2174:
			case 2175:
			case 2176:
			case 2177:
			case 2178:
			case 2179:
			case 2180:
			case 2181:
			case 2182:
			case 2183:
			case 2184:
			case 2185:
				{
				aux_b4 = addr_regs_modbus - 2170;
				hora_liga_controle[aux_b4] = data1_int;
				addr = ee_hora_liga_controle + aux_b4;
		 		goto salva_byte;
                break;
				}
			case 2190:
			case 2191:
			case 2192:
			case 2193:
			case 2194:
			case 2195:
			case 2196:
			case 2197:
			case 2198:
			case 2199:
			case 2200:
			case 2201:
			case 2202:
			case 2203:
			case 2204:
			case 2205:
				{
				aux_b4 = addr_regs_modbus - 2190;
				minuto_liga_controle[aux_b4] = data1_int;
				addr = ee_minuto_liga_controle + aux_b4;
		 		goto salva_byte;break;
				}
			case 2210:
			case 2211:
			case 2212:
			case 2213:
			case 2214:
			case 2215:
			case 2216:
			case 2217:
			case 2218:
			case 2219:
			case 2220:
			case 2221:
			case 2222:
			case 2223:			
			case 2224:
			case 2225:
				{
				aux_b4 = addr_regs_modbus - 2210;
				hora_desliga_controle[aux_b4] = data1_int;
				addr = ee_hora_desliga_controle + aux_b4;
		 		goto salva_byte;break;
				}
			case 2230:
			case 2231:
			case 2232:
			case 2233:
			case 2234:
			case 2235:
			case 2236:
			case 2237:
			case 2238:
			case 2239:
			case 2240:
			case 2241:
			case 2242:
			case 2243:			
			case 2244:
			case 2245:
				{
				aux_b4 = addr_regs_modbus - 2230;
				minuto_desliga_controle[aux_b4] = data1_int;
				addr = ee_minuto_desliga_controle + aux_b4;
		 		goto salva_byte;break;
				}
			case 2250:
				{
				tipo_controle_demanda = data1_int;
				addr = ee_tipo_controle_demanda;
				goto salva_byte;break;
				}
			case 2251:
				{
				dem_cont_ponta[mes - 1] = data1_int;
				addr = ee_dem_cont_ponta;
				break;
				}
			case 2252:
				{
				dem_cont_fora_ponta[mes - 1] = data1_int;
				addr = ee_dem_cont_fora_ponta;
				break;
				}
			case 2253:
			case 2254:
				{
				addr = 0;
				goto salva_byte;break;
				}
			case 2255:
				{
				carga_programada = data1_int;
				addr = ee_carga_programada;
				break;
				}
			case 2256:
				{
				dia_inicio_pc = data1_int;
				addr = ee_dia_inicio_pc;
				goto salva_byte;break;
				}
			case 2257:
				{
				mes_inicio_pc = data1_int;
				addr = ee_mes_inicio_pc;
				goto salva_byte;break;
				}
			case 2258:
				{
				dia_final_pc = data1_int;
				addr = ee_dia_final_pc;
				goto salva_byte;break;
				}
			case 2259:
				{
				mes_final_pc = data1_int;
				addr = ee_mes_final_pc;
				goto salva_byte;break;
				}
			
			case 2260:
			case 2261:
			case 2262:
			case 2263:
			case 2264:
			case 2265:
			case 2266:
			case 2267:
			case 2268:
			case 2269:
			case 2270:
			case 2271:
				{
				aux_b4 = addr_regs_modbus - 2260;
				dem_cont_ponta[aux_b4] = data1_int;
				addr = ee_dem_cont_ponta + (aux_b4 * 2);
				break;
				}
			case 2272:
			case 2273:
			case 2274:
			case 2275:
			case 2276:
			case 2277:
			case 2278:
			case 2279:
			case 2280:
			case 2281:
			case 2282:
			case 2283:
				{
				aux_b4 = addr_regs_modbus - 2272;
				dem_cont_fora_ponta[aux_b4] = data1_int;
				addr = ee_dem_cont_fora_ponta + (aux_b4 * 2);
				break;
				}
		#endif				

		case 2300:{
			addr = ee_com_des_ten_a;
			com_des_ten_a = data1_int;
	 		goto salva_byte;break;
		}

		#if (chip_cs5460a == true)
			case 3032:
				{
				aux_cs5460_l = 0x00014fb2;
				aux_cs5460_l = aux_cs5460_l * 2;
				write_cs5460(pulse_rate, aux_cs5460_l, 'R');
				aux_cs5460_l = read_cs5460(pulse_rate, 'R');
				write_byte(ee_pulse_rate_h, datah);
				write_byte(ee_pulse_rate_m, datam);
				write_byte(ee_pulse_rate_l, datal);
				goto salva_prog_flash;break;
				}
		#endif

		case 9000:
			{
			goto salva_prog_flash;break;
			}

		case 9005:
			{
			binasc2(data1_int);
			write_byte(ee_nro_1, buf_tmp[1]);
			write_byte(ee_nro_2, buf_tmp[2]);
			write_byte(ee_nro_3, buf_tmp[3]);
			write_byte(ee_nro_4, buf_tmp[4]);
			data_modbus = data1_int;
			goto salva_prog_flash_10;break;
			}

		#if (ade7754 == true)
	 	    case 9990:
	 	    	{
		 		 addr = ee_reg_cfnum;
				 reg_cfnum = data1_int;
				 break;
				}
	 	    case 9991:
	 	    	{
		 		 addr = ee_reg_cfdem;
				 reg_cfdem = data1_int;
				break;
				}
		#endif
	 	default:
	 		{
	 	    erro_mod = 1;
	 		qerro_mod = 2;
	 		data1_int = 0;
	 		addr = 0;
	 		return;
	 		}
	 	} 
	write_word(addr, data1_int);
	data_modbus = read_word(addr);
	return;
	
salva_prog_flash:
	data_modbus = 0;
salva_prog_flash_10:
	return;
	
salva_byte:
	write_byte(addr, data1);
	data_modbus = read_byte(addr);
	return;

salva_byte_nvr:
#if (com_relogio == true)
	write_byte_nvr(addr, data1);
	data_modbus = read_byte_nvr(addr);
#endif
	return;
salva_word_nvr:
#if (com_relogio == true)
	write_word_nvr(addr, data1_int);
	data_modbus = read_word_nvr(addr);
#endif
	return;
	
salva_calend:
	ajuste_relogio = 0;
#if (com_relogio == true)
	data_modbus = data1_int;
	rtc_set_datetime();
#else
	data_modbus = data1_int;
	rtc_wr_e2p();
#endif
	return;
}	 	



void busca_os_cor_pt_r(char indice)
{
	#if (portatil == TRUE)
		data1_int = os_cor_pt_r[indice];
	#else
		data1_int = os_cor_r;
	#endif	
}
void busca_os_cor_pt_s(char indice)
{
	#if (portatil == TRUE)
		data1_int = os_cor_pt_s[indice];
	#else
		data1_int = os_cor_s;
	#endif	
}
void busca_os_cor_pt_t(char indice)
{
	#if (portatil == TRUE)
		data1_int = os_cor_pt_t[indice];
	#else
		data1_int = os_cor_t;
	#endif	
}

void busca_os_pot_pt_r(char indice)
{
	#if (portatil == TRUE)
		data1_int = os_pot_pt_r[indice];
	#else
		data1_int = os_pot_r;
	#endif	
}
void busca_os_pot_pt_s(char indice)
{
	#if (portatil == TRUE)
		data1_int = os_pot_pt_s[indice];
	#else
		data1_int = os_pot_s;
	#endif	
}
void busca_os_pot_pt_t(char indice)
{
	#if (portatil == TRUE)
		data1_int = os_pot_pt_t[indice];
	#else
		data1_int = os_pot_t;
	#endif	
}
	
