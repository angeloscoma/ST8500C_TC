/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_COMU                                                        *
; Funcao: MODULO gerencialde comunicação rs232/485						 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */
  

void busca_qcht(void);


/* alteracao versao 1.03 solicitado pela Gestal */ 		 	 
/*
 		 else if ((addr_regs_modbus >= 900) && (addr_regs_modbus <= 999))
*/
void tx_regs_gestal(void)
{
	 switch(addr_regs_modbus)
	 	{
	 	case 901:
	 		{
	 		 data1_int = tensao_r;
	 		 break;
	 		}
	 	case 902:
	 		{
			#if (monofasico == true)
				data1_int = 0;
			#else
		 		 data1_int = tensao_s;
			#endif
	 		 break;
	 		}
	 	case 903:
	 		{
			#if (monofasico == true)
				data1_int = 0;
			#else
		 		 data1_int = tensao_t;
			#endif
	 		 break;
	 		}
	 	case 904:
	 		{
	 		 data1_int = corrente_r;
	 		 break;
	 		}
	 	case 905:
	 		{
			#if (monofasico == true)
				data1_int = 0;
			#else
		 		 data1_int = corrente_s;
			#endif
	 		 break;
	 		}
	 	case 906:
	 		{
			#if (monofasico == true)
				data1_int = 0;
			#else
		 		 data1_int = corrente_t;
			#endif
	 		 break;
	 		}
	 	case 907:
	 		{
	 		 data1_int = fator_pot_r;
	 		 break;
	 		}
	 	case 908:
	 		{
			#if (monofasico == true)
				data1_int = 0;
			#else
		 		 data1_int = fator_pot_s;
			#endif
	 		 break;
	 		}
	 	case 909:
	 		{
			#if (monofasico == true)
				data1_int = 0;
			#else
		 		 data1_int = fator_pot_t;
			#endif
	 		 break;
	 		}
	 	case 910:
	 		{
			#if (monofasico == true)
				data1_int = 0;
			#else
		 		 data1_int = fator_pot;
			#endif
	 		 break;
	 		}
	 	case 911:
	 		{
	 		 data1_int = pot_ativa_r;
	 		 break;
	 		}
	 	case 912:
	 		{
			#if (monofasico == true)
				data1_int = 0;
			#else
		 		 data1_int = pot_ativa_s;
			#endif
	 		 break;
	 		}
	 	case 913:
	 		{
			#if (monofasico == true)
				data1_int = 0;
			#else
		 		 data1_int = pot_ativa_t;
			#endif
	 		 break;
	 		}
	 	case 914:
	 		{
			#if (monofasico == true)
				data1_int = 0;
			#else
		 		 data1_int = (word)(((pot_ativa_r + pot_ativa_s + pot_ativa_t) / 32 ) >> 16);
			#endif
	 		 break;
	 		}
	 	case 915:
	 		{
			#if (monofasico == true)
				data1_int = 0;
			#else
		 		 data1_int = (word)((pot_ativa_r + pot_ativa_s + pot_ativa_t) / 32 );
			#endif
	 		 break;
	 		}
	 	case 916:
	 		{
	 		 data1_int = pot_reativa_r;
	 		 break;
	 		}
	 	case 917:
	 		{
			#if (monofasico == true)
				data1_int = 0;
			#else
		 		 data1_int =  pot_reativa_s;
			#endif
	 		 break;
	 		}
	 	case 918:
	 		{
			#if (monofasico == true)
				data1_int = 0;
			#else
		 		 data1_int = pot_reativa_t;
			#endif
	 		 break;
	 		}
	 	case 919:
	 		{
			#if (monofasico == true)
				data1_int = 0;
			#else
		 		 data1_int = (word)(((pot_reativa_r + pot_reativa_s + pot_reativa_t) / 32) >> 16);
			#endif
	 		 break;
	 		}
	 	case 920:
	 		{
			#if (monofasico == true)
				data1_int = 0;
			#else
		 		 data1_int = (word)((pot_reativa_r + pot_reativa_s + pot_reativa_t) / 32);
			#endif
	 		 break;
	 		}
	 	case 921:
	 		{
	 		 data1_int = pot_aparente_r;
	 		 break;
	 		}
	 	case 922:
	 		{
			#if (monofasico == true)
				data1_int = 0;
			#else
		 		 data1_int = pot_aparente_s;
			#endif
	 		 break;
	 		}
	 	case 923:
	 		{
			#if (monofasico == true)
				data1_int = 0;
			#else
		 		 data1_int = pot_aparente_t;
			#endif
	 		 break;
	 		}
	 	case 924:
	 		{
			#if (monofasico == true)
				data1_int = 0;
			#else
		 		 data1_int = (word)(((pot_aparente_r + pot_aparente_s + pot_aparente_t) / 32) >> 16);
			#endif
	 		 break;
	 		}
	 	case 925:
	 		{
			#if (monofasico == true)
				data1_int = 0;
			#else
		 		 data1_int = (word)((pot_aparente_r + pot_aparente_s + pot_aparente_t) / 32);
			#endif
	 		 break;
	 		}
	 	case 926:
	 		{
	 		 data1_int = frequencia;
	 		 break;
	 		}
	 	case 927:
	 		{
	 		 data1_int = tensao_rs;
	 		 break;
	 		}
	 	case 928:
	 		{
			#if (monofasico == true)
				data1_int = 0;
			#else
		 		 data1_int = tensao_st;
			#endif
	 		 break;
	 		}
	 	case 929:
	 		{
			#if (monofasico == true)
				data1_int = 0;
			#else
		 		 data1_int = tensao_rt;
			#endif
	 		 break;
	 		}
//      de 930 a 989  transmite conteudos harmonicos
	 	case 990:
	 		{
	 		 data1_int = valor_tp;
	 		 break;
	 		}
	 	case 991:
	 		{
			#if (monofasico == true)
				data1_int = 0;
			#else
		 		data1_int = tensao_tri;
			#endif
	 		break;
	 		}
	 	case 992:
	 		{
			#if (monofasico == true)
				data1_int = 0;
			#else
		 		data1_int = corrente_tri;
			#endif
	 		break;
	 		}
	 	case 993:
	 		{
	 		data1_int = valor_tc;		//temperatura;
	 		break;
	 		}
	 	case 994:
	 		{
#if (com_cht == true)
	 		data1_int = passo_cht;		//temperatura;
#else
			data1_int = 0;
#endif
	 		break;
	 		}
	 	case 995:
	 		{
#if (com_cht == true)
	 		data1_int = qcht;		//temperatura;
#else
			data1_int = 0;
#endif
	 		break;
	 		}
	 	
	 	 default:
	 		{   
	 		if ((addr_regs_modbus >= 930) && (addr_regs_modbus <= 939))
	 		 	{
				#if (com_cht == true)
		 		 	 aux_b4 = addr_regs_modbus - 930;   
		 		 	 busca_qcht();		/* entrada e saida  em i	*/
	 		 	 	data1_int = CHT_tr[aux_b4];
				#else
					data1_int = 0;
				#endif
				}
	 		else if ((addr_regs_modbus >= 940) && (addr_regs_modbus <= 949))
	 		 	{
				#if (com_cht == true)
					#if (monofasico == false)				 
			 		 	 aux_b4 = addr_regs_modbus - 940;
		 			 	 busca_qcht();		/* entrada e saida em i	*/
		 			 	 data1_int = CHT_ts[aux_b4];
					#else
						data1_int = 0;
					#endif
				#else
					data1_int = 0;
				#endif
				}
	 		else if ((addr_regs_modbus >= 950) && (addr_regs_modbus <= 959))
	 		 	{
				#if (com_cht == true)
					#if (monofasico == false)
			 		 	 aux_b4 = addr_regs_modbus - 950;
		 			 	 busca_qcht();		/* entrada e saida em i	*/
		 			 	 data1_int = CHT_tt[aux_b4];
					#else
						data1_int = 0;
					#endif
				#else
					data1_int = 0;
				#endif
				}
	 		else if ((addr_regs_modbus >= 960) && (addr_regs_modbus <= 969))
	 		 	{
				#if (com_cht == true)
	 		 	 	aux_b4 = addr_regs_modbus - 960;
	 		 	 	busca_qcht();		/* entrada e saida em i	*/
	 		 	 	data1_int = CHT_cr[aux_b4];
				#else
					data1_int = 0;
				#endif
				}
	 		else if ((addr_regs_modbus >= 970) && (addr_regs_modbus <= 979))
	 		 	{
				#if (com_cht == true)
					#if (monofasico == false)
		 		 		aux_b4 = addr_regs_modbus - 970;
	 			 	 	busca_qcht();		/* entrada e saida em i	*/
	 			 	 	data1_int = CHT_cs[aux_b4];
					#else
					 	data1_int = 0;
					#endif
				#else
					data1_int = 0;
				#endif
				}
	 		else if ((addr_regs_modbus >= 980) && (addr_regs_modbus <= 989))
	 		 	{
				#if (com_cht == true)
					#if (monofasico == false)
			 		 	 aux_b4 = addr_regs_modbus - 980;
		 			 	 busca_qcht();		/* entrada e saida em i	*/
		 			 	 data1_int = CHT_ct[aux_b4];
					#else
						data1_int = 0;
					#endif
				#else
					data1_int = 0;
				#endif
				}
	 	 	else
	 	 		{
	 	    	erro_mod = 1;
	 			qerro_mod = 2;
	 			data1_int = 0;
	 			}
	 		}
	 	}


}


void busca_qcht(void)
{	 		 	 
 	 if (aux_b4 == 0)
 	 	{
 	 	aux_b4 = 0;
 	 	}
 	 else if (aux_b4 == 1)
 	 	{
 	 	aux_b4 = 3;
 	 	}
 	 else if (aux_b4 == 2)
 	 	{
 	 	aux_b4 = 5;
 	 	}
 	 else if (aux_b4 == 3)
 	 	{
 	 	aux_b4 = 7;
 	 	}
 	 else if (aux_b4 == 4)
 	 	{
 	 	aux_b4 = 9;
 	 	}
 	 else if (aux_b4 == 5)
 	 	{
 	 	aux_b4 = 11;
 	 	}
 	 else if (aux_b4 == 6)
 	 	{
 	 	aux_b4 = 13;
 	 	}
 	 else if (aux_b4 == 7)
 	 	{
 	 	aux_b4  = 15;
 	 	}
 	 else if (aux_b4 == 8)
 	 	{
 	 	aux_b4 = 17;
 	 	}
 	 else
 	 	{
 	 	aux_b4 = 19;
 	 	}
}	 		 	 
	 		 	 
