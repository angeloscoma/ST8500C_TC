/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: st95ROTA                                                        *
; Funcao: MODULO ROTINAS             									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */
  

#define printar_rep false


// flags



#define EM_PONTA			00
#define FORA_DE_PONTA		01

/* Valores dos bits de erro.	*/
#define ER_PULSO_M_18	    0x01
#define ER_PULSO_M_16	    0x02
#define ER_PULSO_M_14	    0x04
#define ER_PULSO_M_12	    0x08

/* Tipos de potencia Reativa */
#define IND			0
#define UNIT        1
#define CAP         2


void trat_rep(void);
char tst_msg_rep(void);
void desmonta_msg_rep(void);
void trat_msg_rep(void);

			
void faz_int_minuto(char);
void fecha_periodo(void);


void tx_erro_rep(char erro)
{
	/*
		#if (ST8200C == true)
			if (erro == 6)
				{
//				mensagem(2,147);
				}
		#elif (st8300c == true)
			if (erro == 6)
				{
//				mensagem(2,149);
				}
		#elif (st8100c == true)
			if (erro == 6)
				{
//				mensagem_rola(67, 1);
				}
		#endif
*/
		#if (printar_rep == true)
			#if (com_485 == true)
				output_high(direcao);
				delay_ms(1);
			#endif	
			
			fprintf(modbus,"\l\rREP-%u: ", erro);
			fprintf(modbus,"%u, ",buf_rec_tmp[0]);
			fprintf(modbus,"%u, ",buf_rec_tmp[1]);
			fprintf(modbus,"%u, ",buf_rec_tmp[2]);
			fprintf(modbus,"%u, ",buf_rec_tmp[3]);
			fprintf(modbus,"%u, ",buf_rec_tmp[4]);
			fprintf(modbus,"%u, ",buf_rec_tmp[5]);
			fprintf(modbus,"%u, ",buf_rec_tmp[6]);
			fprintf(modbus,"%u, ",buf_rec_tmp[7]);
			fprintf(modbus," CRC:%u, ",buf_rec_tmp[8]);
			
			switch(erro)
				{
				case 1:
					{
					fprintf(modbus,"\l\rErro pulso 1:%lu, %lu:", puls_c1_rep, puls_c1_rep_ant);
					break;
					}
				case 2:
					{
					fprintf(modbus,"\l\rErro pulso 2:%lu, %lu:", puls_c2_rep, puls_c2_rep_ant);
					break;
					}
				case 3:
				case 4:
					{
					fprintf(modbus,"\l\rErro tempo:%u, %lu, %lu:", erro, seg_falt_rep, seg_falt_rep_ant);
					break;
					}
				case 5:
					{
					fprintf(modbus,"\l\rIntegrou!:%lu, %u, %u", seg_falt_rep, num_int, num_int_ant);
					break;
					}
				case 6:
					{
					fprintf(modbus,"\l\rErro CRC!:%u, %u", buf_rec_tmp[7], buf_rec_tmp[8]);
					break;
					}
				}
		
			#if (com_485 == true)
				delay_ms(1);
				output_low(direcao);
			#endif	
		#endif
}


void inic_rep(void)
{
	nbyte_rep = 0;
	rec_rep_ok = false;

}


void trat_rep(void)
{
	if (rec_rep_ok == true) 
		{		/* seta o bit quando do rx de 8 bytes */
		if (time_out_modo_rep < 5)
			{
			time_out_modo_rep++;			
			time_out_modo_rep++;			
			}
		trat_msg_rep();
		inic_rep();
		}
}


char tst_msg_rep(void)
{
	
	buf_rec_tmp[8] = 0;	
	buf_rec_tmp[8] ^= buf_rec_tmp[0];
	buf_rec_tmp[8] ^= buf_rec_tmp[1];
	buf_rec_tmp[8] ^= buf_rec_tmp[2];
	buf_rec_tmp[8] ^= buf_rec_tmp[3];
	buf_rec_tmp[8] ^= buf_rec_tmp[4];
	buf_rec_tmp[8] ^= buf_rec_tmp[5];
	buf_rec_tmp[8] ^= buf_rec_tmp[6];
	
	buf_rec_tmp[8] = ~buf_rec_tmp[8];


	if (buf_rec_tmp[8] == buf_rec_tmp[7])
		{
		return(true);
	    }
	else
		{
		tx_erro_rep(6);
		}
	return(false);
}



void trat_msg_rep(void)
{

	buf_rec_tmp[8] = 0;	
	buf_rec_tmp[8] ^= buf_rec_tmp[0];
	buf_rec_tmp[8] ^= buf_rec_tmp[1];
	buf_rec_tmp[8] ^= buf_rec_tmp[2];
	buf_rec_tmp[8] ^= buf_rec_tmp[3];
	buf_rec_tmp[8] ^= buf_rec_tmp[4];
	buf_rec_tmp[8] ^= buf_rec_tmp[5];
	buf_rec_tmp[8] ^= buf_rec_tmp[6];

	buf_rec_tmp[8] = ~buf_rec_tmp[8];
	
	if (buf_rec_tmp[8] != buf_rec_tmp[7])
		{
		tx_erro_rep(6);
		return;
		}

	fatura_rep          = (buf_rec_tmp[1] & 0x10) >> 4;
	if (fatura_rep != fatura_rep_old)
		{
		write_byte(ee_fatura_rep, fatura_rep);
		fatura_rep_old = fatura_rep;
		#if (com_regs == true)
			grava_registros(reg_fatura_rep);
		#endif
		}
	
//	fim_interv_reat_rep = (buf_rec_tmp[1] & 0x20) >> 5;
	tarif_cap_rep       = (buf_rec_tmp[1] & 0x40) >> 6;
	tarif_ind_rep       = (buf_rec_tmp[1] & 0x80) >> 7;
//	posto_tarif_rep     = (buf_rec_tmp[2] & 0x0f);
//	tipo_tarif_rep      = (buf_rec_tmp[2] & 0xf0) >> 4;


	seg_falt_rep = make16((buf_rec_tmp[1] & 0x0f),buf_rec_tmp[0]);
	
//	puls_c1_rep_tmp = puls_c1_rep;
//	puls_c2_rep_tmp = puls_c2_rep;
	puls_c1_rep  = make16((buf_rec_tmp[4] & 0x7f),buf_rec_tmp[3]);
	puls_c2_rep  = make16((buf_rec_tmp[6] & 0x7f),buf_rec_tmp[5]);

	switch (seg_falt_rep)
		{
			case 600:
				{
				if ((minuto > 2) && (minuto < 8))
					{
					minuto = 5;
					}
				else if ((minuto > 17) && (minuto < 23))
					{
					minuto = 20;
					}
				else if ((minuto > 32) && (minuto < 38))
					{
					minuto = 35;
					}
				else if ((minuto > 42) && (minuto < 48))
					{
					minuto = 45;
					}
				#if (com_regs == true)
					segundo = 0;
					grava_registros(reg_normal);
					gravou = true;
					#if (com_relogio == true)
					   	write_ds1302(0x82,dec_bcd(minuto));
   						write_ds1302(0x80,dec_bcd(segundo));
					#endif
				#endif
				break;
				}
			case 300:
				{
				if ((minuto > 7) && (minuto < 13))
					{
					minuto = 10;
					}
				else if ((minuto > 22) && (minuto < 28))
					{
					minuto = 25;
					}
				else if ((minuto > 37) && (minuto < 43))
					{
					minuto = 40;
					}
				else if ((minuto > 52) && (minuto < 58))
					{
					minuto = 55;
					}
				#if (com_regs == true)
					segundo = 0;
					grava_registros(reg_normal);
					gravou = true;
					#if (com_relogio == true)
					   	write_ds1302(0x82,dec_bcd(minuto));
   						write_ds1302(0x80,dec_bcd(segundo));
					#endif
				#endif
				break;
				}
			case 0:
				{
				if (minuto < 3)
					{
					minuto = 0;
					}
				else if ((minuto > 12) && (minuto < 18))
					{
					minuto = 15;
					}
				else if ((minuto > 27) && (minuto < 33))
					{
					minuto = 30;
					}
				else if ((minuto > 42) && (minuto < 48))
					{
					minuto = 45;
					}
				#if (com_regs == true)
					segundo = 0;
					grava_registros(reg_normal);
					gravou = true;
					#if (com_relogio == true)
					   	write_ds1302(0x82,dec_bcd(minuto));
   						write_ds1302(0x80,dec_bcd(segundo));
					#endif
				#endif
				break;
				}
		}

	if ((seg_falt_rep > 1) && (seg_falt_rep < 4))
		{
		ultimo_pulso_at = puls_c1_rep;
		ultimo_pulso_reat = puls_c2_rep;
		write_word(ee_ultimo_pulso_at, ultimo_pulso_at);
		write_word(ee_ultimo_pulso_reat, ultimo_pulso_reat);
		ultima_pot_at = pot_ativa_tot;
		ultima_pot_reat = pot_reativa_tot;
		write_word(ee_ultima_pot_at, pot_ativa_tot);
		write_word(ee_ultima_pot_reat, pot_reativa_tot);
		}
	if (seg_falt_rep == 0)
		{
/*			
		segundo = 0;
		if (minuto > 15)
			{
			
			}
		
		*/
		}

	if (tarif_ind_rep_old != tarif_ind_rep)
		{
		time_out_troca_tarifa++;
		if (time_out_troca_tarifa == 10)
			{
			time_out_troca_tarifa = 0;
			fecha_periodo();
			if (tarif_ind_rep == 0)
				{
				#if (st8500c == true)
				#else
					for (aux_b1 = 0; aux_b1 < NRO_MAXIMO_BANCOS_CAPACITOR; aux_b1++)
						{
						desligar_banco(aux_b1);
						}
				#endif
				}
			}
		}
	else
		{
		time_out_troca_tarifa = 0;
		}
	if (time_out_troca_tarifa == 0)
		{
		tarif_ind_rep_old = tarif_ind_rep;
		}


/*
	if (puls_c1_rep < puls_c1_rep_ant)
	   	{
		if (posi_erro1 > 4)
			{
			posi_erro1 = 0;
			}
		buf_pulso1[posi_erro1++] = puls_c1_rep;
		igual = true;
		for (aux_b1 = 0; aux_b1 < 4; aux_b1++)
			{
			if (buf_pulso1[aux_b1] != buf_pulso1[aux_b1+1])
				{
				igual = false;
				break;
				}
			}
		tx_erro_rep(1);
		if (igual == true)
			{
			puls_c1_rep_ant = puls_c1_rep;
			}
		else
			{
			return;
			}
		}
	else
		{
		posi_erro1 = 0;
		}
	if (puls_c2_rep < puls_c2_rep_ant)
	   	{
		if (posi_erro2 > 4)
			{
			posi_erro2 = 0;
			}
		buf_pulso2[posi_erro2++] = puls_c2_rep;
		igual = true;
		for (aux_b1 = 0; aux_b1 < 4; aux_b1++)
			{
			if (buf_pulso2[aux_b1] != buf_pulso2[aux_b1+1])
				{
				igual = false;
				break;
				}
			}
		tx_erro_rep(2);
		if (igual == true)
			{
			puls_c2_rep_ant = puls_c2_rep;
			}
		else
			{
			return;
			}
		}
	else
		{
		posi_erro2 = 0;
		}
	if (seg_falt_rep_ant > 900)
		{
		seg_falt_rep_ant = seg_falt_rep;
		}
	if (seg_falt_rep > seg_falt_rep_ant)
		{
		aux_w1 = seg_falt_rep - seg_falt_rep_ant;
		if (aux_w1 > 60)
			{
			if ((seg_falt_rep < 840) && (seg_falt_rep_ant > 60))
				{
				tx_erro_rep(3);
				return;		
				}
			}
		}
	if (seg_falt_rep < seg_falt_rep_ant)
		{
		aux_w1 = seg_falt_rep_ant - seg_falt_rep;
		if (aux_w1 > 60)
			{
			tx_erro_rep(4);
			return;		
			}
		}

*/

	seg_falt_rep_ant = seg_falt_rep;
	
	switch (posto_tarif_rep) 
		{
	    case 0x01:
			periodo = EM_PONTA;
			break;
	    case 0x02:
			periodo = FORA_DE_PONTA;
			break;
		}
		
	aux_w1 =  (word)(900 - seg_falt_rep);
	num_int = (unsigned char)(aux_w1 / 60);

//	num_int = seg_falt_rep / 60;

	if (num_int != num_int_ant) 
		{
	
		timer_integra = num_int;

		tx_erro_rep(5);

				
	    if (puls_c1_rep > puls_c1_rep_ant)
	    	{
			e_ativa = puls_c1_rep - puls_c1_rep_ant;
			}
	    else if (puls_c1_rep < puls_c1_rep_ant)
	    	{
			e_ativa = e_ativa_ant;
			}
		else
			{
			e_ativa = 0;	//puls_c1_rep;
			}
		e_ativa_ant = e_ativa;
		puls_c1_rep_ant = puls_c1_rep;
			
		if (puls_c2_rep > puls_c2_rep_ant)
			{
			e_reativa = puls_c2_rep - puls_c2_rep_ant;
			}
		else if (puls_c2_rep < puls_c2_rep_ant)
			{
			e_reativa = e_reativa_ant;
			}
		else
			{
			e_reativa = 0;	//puls_c2_rep;
			}

		e_reativa_ant = e_reativa;
		puls_c2_rep_ant = puls_c2_rep;

		#if (printar_rep == true)
			#if (com_485 == true)
				output_high(direcao);
				delay_ms(1);
			#endif	
		
			fprintf(modbus,"\l\rPulsos:%lu/%lu ; %lu/%lu", puls_c1_rep,  ultimo_pulso_at,  puls_c2_rep , ultimo_pulso_reat);
			fprintf(modbus,"\l\rEnergias:%lu(kwh) ;%lu(KVAr)", e_ativa, e_reativa);
			
		
			#if (com_485 == true)
				delay_ms(1);
				output_low(direcao);
			#endif	
		#endif
		faz_int_minuto(num_int);
		num_int_ant = num_int;
			
		}		

		
}




void faz_int_minuto(char parte)
{
	int32 extra2;
	int32 extra1; 
	char x;
	
	atualizar = 1;
	   
	if (parte > 14) 
		{
	    parte = 0;
	    return;
	    }


    int_ativa[parte] = e_ativa;
	int_reativa[parte] = e_reativa;
	if (int_ativa[parte] != 0)
		{
	    int_ativa[0] = e_ativa;
	    }
	if (int_reativa[parte] != 0)
		{
		int_reativa[0] = e_reativa;
		}
	for (x = parte; x < 15; x++) 
		{
		if (int_ativa[parte] != 0)
			{
			int_ativa[x] = int_ativa[parte]; 
			}
		if (int_reativa[parte] != 0)
			{
			int_reativa[x] = int_reativa[parte]; 
			}
		}

	write_word(ee_int_ativa+(parte*2), e_ativa);

	write_word(ee_int_reativa+(parte*2), e_reativa);

	
	fp_ativa = 0;
	fp_reativa = 0;
	
	for (x = 0; x < 15; x++) 
		{
		fp_ativa += (float)(int_ativa[x]); 
		fp_reativa += (float)(int_reativa[x]); 
		}

	fp_ativa = (float)(fp_ativa * kkw);
	fp_reativa = (float)(fp_reativa * kkvar);
		
	aux_f1 = (float)(fp_ativa);
	pot_ativa_tot = (int32)((aux_f1 * 32));
	pot_ativa_r = (word)(pot_ativa_tot / 3);
	#if (monofasico == false)
		pot_ativa_s = pot_ativa_r;
		pot_ativa_t = pot_ativa_r;
	#endif

	aux_f1 = (float)(fp_reativa);
	pot_reativa_tot = (int32)((aux_f1 * 32));
	pot_reativa_r = (word)(pot_reativa_tot / 3);
	#if (monofasico == false)
		pot_reativa_s = pot_reativa_r;
		pot_reativa_t = pot_reativa_r;
	#endif
	

		#if (printar_rep == true)
			#if (com_485 == true)
				output_high(direcao);
				delay_ms(1);
			#endif	
	
			fprintf(modbus,"\l\rAtiva:");
			for (x = 0; x < 15; x++) 
				{
				fprintf(modbus,"%lu, ", int_ativa[x]);
				}
			fprintf(modbus,"\l\rReAtiva:");
			for (x = 0; x < 15; x++) 
				{
				fprintf(modbus,"%lu, ", int_reativa[x]);
				}
			fprintf(modbus,"\l\rPotencias:%f(kwh)/%lu ;%f(KVAr), Sinal:%u", fp_ativa, pot_ativa_r, fp_reativa, tipo_fp);
			aux_f1 = pot_ativa_r;
			aux_f1 = aux_f1 / 32;
			fprintf(modbus,"\l\rPotencias:%f(kwh)", aux_f1);
			aux_f1 = pot_reativa_r;
			aux_f1 = aux_f1 / 32;
			fprintf(modbus," ;%f(kvarh)", aux_f1);

			#if (com_485 == true)
				delay_ms(1);
				output_low(direcao);
			#endif	
		#endif
	

		#if (com_485 == true)
			output_high(direcao);
			delay_ms(1);
		#endif	
	

		#if (com_485 == true)
			delay_ms(1);
			output_low(direcao);
		#endif	
		
		
		if (parte == 15) 
			{
//			fecha_periodo();    /* rotinas que sao executadas a cada 15 minutos */
	    	}

}


	/* A cada 15 min. faz o fechamento (parte = 14) que pode ser chamado pelo
	   pulso de integracao externo ou pela passagem do temporizador interno
	   (timer_integra) que subt. o ext. no caso da falta ou perda de sinal */
void fecha_periodo(void)    /* rotinas que sao executadas a cada 15 minutos */
{                       /* no fechamento do intervalo de integracao     */
	char x;
	
	for (x = 0; x < 15; x++) 
		{
		int_ativa[x] = 0;             /* zera os acumuladores de pulsos */
		write_word(ee_int_ativa+(x*2), 0);
		
		int_reativa[x] = 0;
		write_word(ee_int_reativa+(x*2), 0);
		
		}
}






void recupera_rep(void)
{
	for (aux_b1 = 0; aux_b1 < 15; aux_b1++)
		{
		int_ativa[aux_b1] = read_word(ee_int_ativa+(aux_b1*2));
		int_reativa[aux_b1] = read_word(ee_int_reativa+(aux_b1*2));
		}	
	nbyte_rep = 0;
 	nbit_rep = 0;
	start_rep = 0;
	time_out_rep = 2;
		
}

void zera_rep(void)
{
	for (aux_b1 = 0; aux_b1 < 15; aux_b1++)
		{
		write_word(ee_int_ativa+(aux_b1*2), 0);
		write_word(ee_int_reativa+(aux_b1*2), 0);
		}	
	recupera_rep();
	ultimo_pulso_at = 0;
	ultimo_pulso_reat = 0;
	ultima_pot_at = 0;
	ultima_pot_reat = 0;
		
}
