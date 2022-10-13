/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_INTS                                                        *
; Funcao: MODULO Interrupçoes 					  						 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 06/06/2003                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/



#INT_EXT // FAST
void int_externa0(void)
{
	// TRATAMENTO DA INTERRUPÇÃO EXTERNA 0(TENSAO) //
	ler_senoide = 1;
		
	// obtem a fase entre tensao e corrente	
	distancia_fase = cont_fase;
		
}


#INT_EXT1 // FAST
void int_externa1(void)
{
	
	cont_fase = 0;
		
}


#INT_EXT2 // FAST
void int_externa2(void)			// NESTA INTERRUPÇÃO VÃO SER LIDOS TODOS OS VALORES DO SA9904
{
	if (med_ten_ok == false)
		{
		if (sincro == true)
			{
			KW_R_SAMES = le_sa9904(0);
			KVAR_R_SAMES = le_sa9904(1);
			soma_efi_tr += le_sa9904(2);
			HZ_SAMES = le_sa9904(3);
			
			#if (monofasico == false)
				KW_S_SAMES = le_sa9904(4);
				KVAR_S_SAMES = le_sa9904(5);
				soma_efi_ts += le_sa9904(6);
				KW_T_SAMES = le_sa9904(8);
				KVAR_T_SAMES = le_sa9904(9);
				soma_efi_tt += le_sa9904(10);
			#endif
//r		
			if (KW_R_SAMES > KW_R_SAMES_OLD)
				{
				KW_R = (int32)(KW_R_SAMES - KW_R_SAMES_OLD);
				}
			else
				{
				KW_R = (int32)(KW_R_SAMES_OLD - KW_R_SAMES);
				}
			if (KVAR_R_SAMES > KVAR_R_SAMES_OLD)
				{
				KVAR_R = (int32)(KVAR_R_SAMES - KVAR_R_SAMES_OLD);
				}
			else
				{
				KVAR_R = (int32)(KVAR_R_SAMES_OLD - KVAR_R_SAMES);
				}
			#if (monofasico == false)
//s				
				if (KW_S_SAMES > KW_S_SAMES_OLD)
					{
					KW_S = (int32)(KW_S_SAMES - KW_S_SAMES_OLD);
					}
				else
					{
					KW_S = (int32)(KW_S_SAMES_OLD - KW_S_SAMES);
					}
				if (KVAR_S_SAMES > KVAR_S_SAMES_OLD)
					{
					KVAR_S = (int32)(KVAR_S_SAMES - KVAR_S_SAMES_OLD);
					}
				else
					{
					KVAR_S = (int32)(KVAR_S_SAMES_OLD - KVAR_S_SAMES);
					}
//t
				if (KW_T_SAMES > KW_T_SAMES_OLD)
					{
					KW_T = (int32)(KW_T_SAMES - KW_T_SAMES_OLD);
					}
				else
					{
					KW_T = (int32)(KW_T_SAMES_OLD - KW_T_SAMES);
					}
				if (KVAR_T_SAMES > KVAR_T_SAMES_OLD)
					{
					KVAR_T = (int32)(KVAR_T_SAMES - KVAR_T_SAMES_OLD);
					}
				else
					{
					KVAR_T = (int32)(KVAR_T_SAMES_OLD - KVAR_T_SAMES);
					}
			#endif	
		
			soma_kw_r +=  KW_R;
			soma_kvar_r += KVAR_R;
			#if (monofasico == false)
				soma_kw_s +=  KW_S;
				soma_kvar_s += KVAR_S;
				soma_kw_t +=  KW_T;
				soma_kvar_t += KVAR_T;
			#endif
		
			conta_media_ten++;
			if (conta_media_ten >= 16)
				{
				med_ten_ok = true;
				sincro = false;
				}
			}
		else
			{
			sincro = true;
			KW_R_SAMES = le_sa9904(0);
			KVAR_R_SAMES = le_sa9904(1);
			#if (monofasico == false)
				KW_S_SAMES = le_sa9904(4);
				KVAR_S_SAMES = le_sa9904(5);
				KW_T_SAMES = le_sa9904(8);
				KVAR_T_SAMES = le_sa9904(9);
			#endif				
			}
			
		KW_R_SAMES_OLD = KW_R_SAMES;
		KVAR_R_SAMES_OLD = KVAR_R_SAMES;
		#if (monofasico == false)
			KW_S_SAMES_OLD = KW_S_SAMES;
			KVAR_S_SAMES_OLD = KVAR_S_SAMES;
			KW_T_SAMES_OLD = KW_T_SAMES;
			KVAR_T_SAMES_OLD = KVAR_T_SAMES;
		#endif
		}
		
		
}


