/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: st_CALC                                                        *
; Funcao: MODULO ROTINAS DE CALCULOS   									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */

/* calculo do kvar requerido */	    
/* pot_req_x = potencia_reativa - srq(((potencia_ativa / setpoint) ^2)) - ( potencia_ativa ^ 2))  */

#if (monofasico == false)
	void kvar_req_tri(char);
#endif


void kvar_requerido(char fase)
{
/* pot_req_x = potencia_reativa - srq(((potencia_ativa / setpoint) ^2)) - ( potencia_ativa ^ 2))  */
	#if (monofasico == true)
		word aux_w4;
		#if (portatil == false)
			if (cor_min == true)
				{
				return;
				}
		#endif
		pot_exec_r = 0;
		pot_req_r = 0;
		if (com_des_fp_ind_cap < 100)
			{
			if (pot_reativa_r == 0)
				{
				return;
				}
			}
		if (fator_pot_r > 0 )
			{
			aux_l3 = (word)(fator_pot_r);
			aux_l3 = (aux_l3 * 100);
			aux_w4 = (word)(aux_l3 / 1024);
			#if (controlador == true)
				if (com_des_fp_ind_cap >= 100)	// > 100 indica que é desliganento em indutivo
					{
					if (fator_pot_r == 1024)
						{
						aux_w4 = 100;
						goto calcula_excedente_10;
						}
					else
						{
						pot_exec_r = pot_reativa_r;
						return;
						}
					}
				else
					{ // desligamento entre 1.00 e 0.80 capacitivo
					if (aux_w4 >= com_des_fp_ind_cap)
						{
						return;
						}
					}
			#else
				if (aux_w4 >= set_point)
					{
					return;
					}
			#endif
			
			}
		else
			{
// FP INDUTIVO			
			aux_l3 = (word)(fator_pot_r * (-1));
			aux_l3 = (aux_l3 * 100);
			aux_w4 = (word)(aux_l3 / 1024);
calcula_excedente_10:	
			aux_set_point = 100 - (com_des_fp_ind_cap - 100);
// Aauxw4 com o valor do fator de potencia X 100)
			if (aux_w4 >= set_point)
				{
// maior ou igual a setpoint, então vamos ver se temos o excedente					
				#if (controlador == true)
// verifica se desçigamento é dentro de FP indutivo
					if (com_des_fp_ind_cap >= 100)	// > 100 indica que é desliganento em indutivo
						{
						if (aux_w4 <= aux_set_point)
							{					
/// menor que o set-point de desligamento, entã dentro da histerese. excedente e requerido = 0								
							return;			// dentro da hsiterese
							}
						else
							{
// fator de potencia acima do set-point de desligamento, calcula o excedente	
							aux_l1 = pot_ativa_r;
							aux_l3 = pot_reativa_r;
							aux_l2 = aux_l1;
						    aux_l1 = (aux_l1 * 100);
						    aux_l1 = aux_l1 / com_des_fp_ind_cap;	
						    aux_l1 = aux_l1 * aux_l1;
    						aux_l2 = aux_l2 * aux_l2;
    						aux_l1 = (int32)(sqrtx(aux_l1 - aux_l2));
							aux_w1 = (word)((aux_l3 - aux_l1));	
							if (bit_test(aux_w1, 15) == true)
								{
								aux_w1 = ~aux_w1 + 1;
								}
							pot_exec_r = aux_w1;
							return;	
							}
						}
				#else
					return;
				#endif
				}
			}
		
		aux_l1 = pot_ativa_r;
		aux_l3 = pot_reativa_r;
		aux_l2 = aux_l1;
	    aux_l1 = (aux_l1 * 100);
		
		if (fator_pot_r > 0 )
			{
			#if (controlador == true)
			    aux_l1 = aux_l1 / com_des_fp_ind_cap;	
			#else
			    aux_l1 = aux_l1 / set_point;	
			#endif
			
			}
		else
			{
			#if (com_rep == true)
				if (modo_rep == 1)
					{
					if (aux_w4 >= set_point)
						{
					    aux_l1 = aux_l1 / 100;	
						}
					else
						{
					    aux_l1 = aux_l1 / set_point;	
						}
					}
				else
					{
				    aux_l1 = aux_l1 / set_point;	
				    }
			#else
			    aux_l1 = aux_l1 / set_point;	
		    #endif
		    }
	    aux_l1 = aux_l1 * aux_l1;
	    aux_l2 = aux_l2 * aux_l2;
	    aux_l1 = (int32)(sqrtx(aux_l1 - aux_l2));
	
		aux_w1 = (word)((aux_l3 - aux_l1));	

		if (valor_tp != 1)
			{
			aux_w1 = (int16)(aux_w1 * valor_tp);
			}
		
		if (fator_pot_r > 0 )
			{
			pot_exec_r = aux_w1;
			}
		else
			{
			#if (com_rep == true)
				if (modo_rep == 1)
					{
					if (aux_w4 >= set_point)
						{
						pot_exec_r = aux_w1;
						}
					else
						{
						pot_req_r = aux_w1;
						}
					}
				else
					{
					pot_req_r = aux_w1;
					}
			#else
				pot_req_r = aux_w1;
			#endif
			}

	#else
		kvar_req_tri(fase);
	#endif	
		
}



#if (monofasico == false)
	void kvar_req_tri(char fase)
	{
		#if (st8500c == true)
			word pot_ativa;
			word pot_reativa;
			word pot_exec;
			word pot_req;
			word aux_w4;
			signed word fator_pot_fase;
			pot_exec = 0;
			pot_req = 0;
			pot_reativa = pot_reativa_tot;
			pot_ativa = pot_ativa_tot;
			fator_pot_fase = fator_pot;
			
			if (pot_reativa == 0)
				{
				goto kvar_req_tri_retorna;
				}
			if (fator_pot_fase > 0)
				{
				#if (com_tc == true)
					pot_exec = pot_reativa;
				#else
					pot_exec = pot_reativa * 32;
				#endif
				goto kvar_req_tri_retorna;
				}
			aux_l3 = (word)(fator_pot_fase * (-1));
			aux_l3 = (aux_l3 * 100);
			aux_w4 = (word)(aux_l3 / 1024);
			if (aux_w4 >= 92)
				{
				goto kvar_req_tri_retorna;
				}
		
			aux_l1 = pot_ativa;
			aux_l3 = pot_reativa;
			aux_l2 = aux_l1;
		   	aux_l1 = (aux_l1 * 100);
		
		    aux_l1 = aux_l1 / 92;	
		   	aux_l1 = aux_l1 * aux_l1;
		   	aux_l2 = aux_l2 * aux_l2;
		   	aux_l1 = (int32)(sqrtx(aux_l1 - aux_l2));
			
			aux_w1 = (word)((aux_l3 - aux_l1));	
			#if (com_tc == true)
				pot_req = aux_w1;
			#else
				pot_req = aux_w1 * 32;
			#endif
					
		
		#else
			word pot_ativa;
			word pot_reativa;
			word pot_exec;
			word pot_req;
			word aux_w4;
			signed word fator_pot_fase;
			
			#if (controlador == true)
				if (cor_min == true)
					{
					return;
					}
			#endif
			pot_exec = 0;
			pot_req = 0;
			#if (com_rep == true)
				#if (st8300c == true)
					if (modo_rep == true)
						{
						if (fase =='R')
							{
							pot_reativa = pot_reativa_r * 3;
							pot_ativa = pot_ativa_r * 3;
							fator_pot_fase = fator_pot_r;
							}
						if ((fase == 'S') || (fase == 'T'))
							{
							pot_exec = pot_exec_r * 3;
							pot_req = pot_req_r * 3;
							goto kvar_req_tri_retorna;
							}	
						}
					else
						{
						if (fase =='R')
							{
							pot_reativa = pot_reativa_r;
							pot_ativa = pot_ativa_r;
							fator_pot_fase = fator_pot_r;
							}
						else if (fase =='S')
							{
							pot_reativa = pot_reativa_s;
							pot_ativa = pot_ativa_s;
							fator_pot_fase = fator_pot_s;
							}
						else
							{
							pot_reativa = pot_reativa_t;
							pot_ativa = pot_ativa_t;
							fator_pot_fase = fator_pot_t;
							}
						}
				#endif
			#else
				if (fase =='R')
					{
					pot_reativa = pot_reativa_r;
					pot_ativa = pot_ativa_r;
					fator_pot_fase = fator_pot_r;
					}
				else if (fase =='S')
					{
					pot_reativa = pot_reativa_s;
					pot_ativa = pot_ativa_s;
					fator_pot_fase = fator_pot_s;
					}
				else
					{
					pot_reativa = pot_reativa_t;
					pot_ativa = pot_ativa_t;
					fator_pot_fase = fator_pot_t;
					}
			#endif
			
				if (pot_reativa == 0)
					{
					#if (controlador == true)
						if (com_des_fp_ind_cap < 100)
							{
							goto kvar_req_tri_retorna;
							}
					#else
						goto kvar_req_tri_retorna;
					#endif
				}
		
			if (fator_pot_fase > 0 )
				{
				aux_l3 = (word)(fator_pot_fase);
				aux_l3 = (aux_l3 * 100);
				aux_w4 = (word)(aux_l3 / 1024);
				#if (controlador == true)
					if (com_des_fp_ind_cap >= 100)
						{
						if (fator_pot_r == 1024)
							{
							aux_w4 = 100;
							goto calcula_excedente_10;
							}
						else
							{
							pot_exec = pot_reativa;
							goto kvar_req_tri_retorna;
							}
						}
					else
						{
						if (aux_w4 >= com_des_fp_ind_cap)
							{
							goto kvar_req_tri_retorna;
							}
						}
				#else
					if (aux_w4 >= set_point)
						{
						goto kvar_req_tri_retorna;
						}
				#endif
				}
			else
				{
				aux_l3 = (word)(fator_pot_fase * (-1));
				aux_l3 = (aux_l3 * 100);
				aux_w4 = (word)(aux_l3 / 1024);
			calcula_excedente_10:
				#if (controlador == true)
					aux_set_point = 100 - (com_des_fp_ind_cap - 100);
				#endif
				if (aux_w4 >= set_point)
					{
					#if (controlador == true)
						if (com_des_fp_ind_cap >= 100)
							{
							if (aux_w4 <= aux_set_point)
								{
								goto kvar_req_tri_retorna;
								}
							else
								{
								aux_l1 = pot_ativa;
								aux_l3 = pot_reativa;
								aux_l2 = aux_l1;
		   						aux_l1 = (aux_l1 * 100);
		   						aux_l1 = aux_l1 / com_des_fp_ind_cap;
		   						aux_l1 = aux_l1 * aux_l1;
		   						aux_l2 = aux_l2 * aux_l2;
		   						aux_l1 = (int32)(sqrtx(aux_l1 - aux_l2));
		   						aux_w1 = (word)((aux_l3 - aux_l1));
		   						if (bit_test(aux_w1, 15) == true)
		   							{
			   						aux_w1 = ~aux_w1 + 1;
			   						}
			   					pot_exec = aux_w1;
								goto kvar_req_tri_retorna;
								}
							}
					#else
						goto kvar_req_tri_retorna;
					#endif
					}
				}
		
			aux_l1 = pot_ativa;
			aux_l3 = pot_reativa;
			aux_l2 = aux_l1;
		   	aux_l1 = (aux_l1 * 100);
		
			#if (controlador == true)
				if (fator_pot_fase > 0)
					{
				    aux_l1 = aux_l1 / com_des_fp_ind_cap;	
					}
				else
					{
					#if (com_rep == true)
						if (modo_rep == 1)
							{
							if (aux_w4 >= set_point)
								{
								aux_l1 = aux_l1 / 100;
								}
							else
								{
							    aux_l1 = aux_l1 / set_point;	
							    }
							}
						else
							{
						    aux_l1 = aux_l1 / set_point;	
							}
					#else
					    aux_l1 = aux_l1 / set_point;	
					#endif
					}
			#else	
			    aux_l1 = aux_l1 / set_point;	
			#endif
		   	aux_l1 = aux_l1 * aux_l1;
		   	aux_l2 = aux_l2 * aux_l2;
		   	aux_l1 = (int32)(sqrtx(aux_l1 - aux_l2));
			
			aux_w1 = (word)((aux_l3 - aux_l1));	
		
			if (valor_tp != 1)
				{
				aux_w1 = (int16)(aux_w1 * valor_tp);
				}
		
			
			if (fator_pot_fase > 0)
				{
				pot_exec = aux_w1;
				}
			else
				{
				#if (com_rep == true)
					if (modo_rep == 1)
						{
						if (aux_w4 >= set_point)
							{
							pot_exec = aux_w1;
							}
						else
							{
							pot_req = aux_w1;
						    }
						}
					else
						{
						pot_req = aux_w1;
						}
				#else
					pot_req = aux_w1;
				#endif
				}
					
		
		#endif
				
kvar_req_tri_retorna:
		#if (st8500c == true)
			{
			pot_exec_r = pot_exec;
			pot_req_r = pot_req;
			pot_exec_r = pot_exec_r / 3;
			pot_req_r = pot_req_r / 3;
			pot_exec_s = pot_exec_r;
			pot_req_s = pot_req_r;
			pot_exec_t = pot_exec_r;
			pot_req_t = pot_req_r;
			}
		#else
			#if (com_rep == true)
				#if (st8300c == true)
					if (modo_rep == true)
						{
						pot_exec_r = pot_exec;
						pot_req_r = pot_req;
						pot_exec_r = pot_exec_r / 3;
						pot_req_r = pot_req_r / 3;
						pot_exec_s = pot_exec_r;
						pot_req_s = pot_req_r;
						pot_exec_t = pot_exec_r;
						pot_req_t = pot_req_r;
						}
					else
						{
						if (fase =='R')
							{
							pot_exec_r = pot_exec;
							pot_req_r = pot_req;
							}
						else if (fase =='S')
							{
							pot_exec_s = pot_exec;
							pot_req_s = pot_req;
							}
						else
							{
							pot_exec_t = pot_exec;
							pot_req_t = pot_req;
							}
						}
				#else
					if (fase =='R')
						{
						pot_exec_r = pot_exec;
						pot_req_r = pot_req;
						}
					else if (fase =='S')
						{
						pot_exec_s = pot_exec;
						pot_req_s = pot_req;
						}
					else
						{
						pot_exec_t = pot_exec;
						pot_req_t = pot_req;
						}
				#endif
			#else
				if (fase =='R')
					{
					pot_exec_r = pot_exec;
					pot_req_r = pot_req;
					}
				else if (fase =='S')
					{
					pot_exec_s = pot_exec;
					pot_req_s = pot_req;
					}
				else
					{
					pot_exec_t = pot_exec;
					pot_req_t = pot_req;
					}
			#endif
		#endif
	}
#endif

///  antigo agora sem uso
/*
void kvar_req_old(char fase)
{
		if (fase =='R')
			{
			#if (controlador == true)
				if (cor_min == true)
					{
					return;
					}
			#endif
			pot_exec_r = 0;
			pot_req_r = 0;
			if (pot_reativa_r == 0)
				{
				return;
				}
			if (fator_pot_r > 0 )
				{
				aux_l3 = (word)(fator_pot_r);
				aux_l3 = (aux_l3 * 100);
				aux_w1 = (word)(aux_l3 / 1024);
				#if (controlador == true)
					if (aux_w1 >= com_des_fp_ind_cap)
						{
						return;
						}
				#else
					if (aux_w1 >= set_point)
						{
						return;
						}
				#endif
				}
			else
				{
				aux_l3 = (word)(fator_pot_r * (-1));
				aux_l3 = (aux_l3 * 100);
				aux_w1 = (word)(aux_l3 / 1024);
				if (aux_w1 >= set_point)
					{
					return;
					}
				}
			}
		#if (monofasico == false)
			else if (fase =='S')
				{
				#if (controlador == true)
					if (cor_min == true)
						{
						return;
						}
				#endif
				pot_exec_s = 0;
				pot_req_s = 0;
				if (pot_reativa_s == 0)
					{
					return;
					}
				if (fator_pot_s > 0 )
					{
					aux_l3 = (word)(fator_pot_s);
					aux_l3 = (aux_l3 * 100);
					aux_w1 = (word)(aux_l3 / 1024);
					#if (controlador == true)
						if (aux_w1 >= com_des_fp_cap)
							{
							return;
							}
					#else
						if (aux_w1 >= set_point)
							{
							return;
							}
					#endif
					}
				else
					{
					aux_l3 = (word)(fator_pot_s * (-1));
					aux_l3 = (aux_l3 * 100);
					aux_w1 = (word)(aux_l3 / 1024);
					if (aux_w1 >= set_point)
						{
						return;
						}
					}
				}
			else 
				{
				#if (controlador == true)
					if (cor_min == true)
						{
						return;
						}
				#endif
				pot_exec_t = 0;
				pot_req_t = 0;
				if (pot_reativa_t == 0)
					{
					return;
					}
				if (fator_pot_t > 0 )
					{
					aux_l3 = (word)(fator_pot_t);
					aux_l3 = (aux_l3 * 100);
					aux_w1 = (word)(aux_l3 / 1024);
					#if (controlador == true)
						if (aux_w1 >= com_des_fp_cap)
							{
							return;
							}
					#else
						if (aux_w1 >= set_point)
							{
							return;
							}
					#endif
					}
				else
					{
					aux_l3 = (word)(fator_pot_t * (-1));
					aux_l3 = (aux_l3 * 100);
					aux_w1 = (word)(aux_l3 / 1024);
					if (aux_w1 >= set_point)
						{
						return;
						}
					}
				}
		#endif

		if (fase =='R')
			{
			aux_l1 = pot_ativa_r;
			aux_l3 = pot_reativa_r;
			}
		#if (monofasico == false)
			else if (fase =='S')
				{
				aux_l1 = pot_ativa_s;
				aux_l3 = pot_reativa_s;
				}
			else 
				{
				aux_l1 = pot_ativa_t;
				aux_l3 = pot_reativa_t;
				}
		#endif
		
		aux_l2 = aux_l1;
	    aux_l1 = (aux_l1 * 100);

		#if (controlador == true)
			if (fase =='R')
				{
				if (fator_pot_r > 0)
					{
				    aux_l1 = aux_l1 / com_des_fp_ind_cap;	
					}
				else
					{
				    aux_l1 = aux_l1 / set_point;	
					}
				}
			#if (monofasico == false)
				else if (fase =='S')
					{
					if (fator_pot_s > 0)
						{
					    aux_l1 = aux_l1 / com_des_fp_cap;	
						}
					else
						{
					    aux_l1 = aux_l1 / set_point;	
						}
					}
				else 
					{
					if (fator_pot_t > 0)
						{
					    aux_l1 = aux_l1 / com_des_fp_cap;	
						}
					else
						{
					    aux_l1 = aux_l1 / set_point;	
						}
					}
			#endif
		#else	
		    aux_l1 = aux_l1 / set_point;	
		#endif
	    aux_l1 = aux_l1 * aux_l1;
	    aux_l2 = aux_l2 * aux_l2;
	    aux_l1 = (int32)(sqrtx(aux_l1 - aux_l2));
	
		aux_w1 = (word)((aux_l3 - aux_l1));	

		if (valor_tp != 1)
			{
			aux_w1 = (int16)(aux_w1 * valor_tp);
			}

	
		if (fase =='R')
			{
			if (fator_pot_r > 0)
				{
				pot_exec_r = aux_w1;
				}
			else
				{
				pot_req_r = aux_w1;
				}
			}
		#if (monofasico == false)
			else if (fase =='S')
				{
				if (fator_pot_s > 0)
					{
					pot_exec_s = aux_w1;
					}
				else
					{
					pot_req_s = aux_w1;
					}
				}
			else 
				{
				if (fator_pot_t > 0)
					{
					pot_exec_t = aux_w1;
					}
				else
					{
					pot_req_t = aux_w1;
					}
				}
		#endif
}
*/
