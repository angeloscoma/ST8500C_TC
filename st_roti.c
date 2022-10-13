/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRONICOS                                  *
; Modulo: ROTINAS                               	                     *
; Funcao: MODULO DE ROTINAS DE COMUNICACAO								 *
; 																		 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 01/08/2003                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/
#if (st5x == true)
	word soma_dip_vel;
	char media_dip_vel;
	word res_dip_vel;
#endif	

#if ((controlador == true) || (st92 == true))
	#if (disp_lcd == true)
		void trata_saidas(void);
	#endif
#endif

#if (st5x == true)
	#if (TECNOFLUX == TRUE)
		#define versao_1200	true
	#else
		#define versao_1200	false
	#endif
#else
	#define versao_1200	false
#endif

#if (versao_1200 == true)
	#define vel_4800	1200	//4800
	#define vel_9600	2400	//9600
	#define vel_19200	4800	//19200
	#define vel_38400	9600	//38400

	#define vel_2400	2400	//Estes dois valores existem apenas para completar a rotina 
	#define vel_57600	57600
#else
	#define vel_2400	2400
	#define vel_4800	4800
	#define vel_9600	9600
	#define vel_19200	19200
	#define vel_38400	38400
	#define vel_57600	57600
#endif



void calcula_mul_tc(void)
{
	#if (portatil == true)
		#if (se_com_flex ==	true)
//			mul_tc = (float)(tabela_pt[tipo_ponteira]);
//			mul_tc = (float)(mul_tc/500);
			mul_tc = (float)(tabela_mul_tc[tipo_ponteira]);
		#else
			char aux_bx;
			word aux_wx;
			for (aux_bx = 0; aux_bx < NRO_POSI_TC; aux_bx++)
				{
				aux_wx = tabela_tc[aux_bx];
				if (aux_wx == valor_tc)
					{
					mul_tc = (float)(valor_tc);
					mul_tc = (float)(mul_tc/500);
					break;
					}
				}
		#endif
	#else
		char aux_bx;
		word aux_wx;
		for (aux_bx = 0; aux_bx < NRO_POSI_TC; aux_bx++)
			{
			aux_wx = tabela_tc[aux_bx];
			if (aux_wx == valor_tc)
				{
				mul_tc = (float)(valor_tc);
				mul_tc = (float)(mul_tc/500);
				break;
				}
			}
	#endif
}


word ajusta_leitura(word valor)
{
	return((word)(mul_tc * valor));
}

word ajusta_leitura_baixa(word valor)
{
	valor = valor * 10;
	return((word)(mul_tc * valor));
}

word ajusta_leitura_long(int32 valor)
{
	return((int32)(mul_tc * valor));
}


#if (st_prog == true)
	void inic_rx2()
	{
		ptrrx2 = 0;
		retrx2 = 0;
		numbrx2 = 0;
		numbtx2 = 0;
		ptrtx2 = 0;
		delay_ms(5);
		output_low(direcao2);
	}
	
	
	void dispara_tx2(void)
	{
		output_high(direcao2);
		delay_us(500);
		if (ptrtx2 > TAM_TX2)
			{
			ptrtx2 = 0;
			goto encerra_dispara_tx2;
			}
		numbtx2 = ptrtx2;
		ptrtx2 = 0;
		while(numbtx2 != 0)
			{
			putc(buf_tx2[ptrtx2++], sultech);
			numbtx2--;
			}
	encerra_dispara_tx2:		
		time_out_modbus2 = 6;
		inic_rx2();
		time_out_sultech = INTS_PER_SECOND;
	}
	
	
	char ret_ser2(void)
	{ 
		caracter = 0;
		if (retrx2 != ptrrx2)
			{
			caracter = buf_rx2[retrx2++];
			}
		if (ptrrx2 > TAM_RX2)
			{
			retrx2 = 0;
			}
	  return(caracter);
	}

	void tx2_lfcr (void)
	{
		buf_tx2[ptrtx2++] = CR;
		buf_tx2[ptrtx2++] = LF;
	}
	


	void avanca_retrx(char quant)
	{
		retrx2 = retrx2 + quant;
	}

	word retira_xxx(void)
	{
		word aux_w;
		aux_w = ret_ser2() - '0' ;
		aux_w = aux_w * 100;
		aux_w = aux_w + ((ret_ser2() - '0' ) * 10);
		aux_w = aux_w + ((ret_ser2() - '0' ));
		ret_ser2();
		return(aux_w);
	}

	char retira_xx(void)
	{
		char aux_b;
		aux_b = ret_ser2() - '0' ;
		aux_b = aux_b * 10;
		aux_b = aux_b + ((ret_ser2() - '0' ));
		ret_ser2();
		return(aux_b);
	}

	word retira_xxxx(void)
	{
		word aux_w;
		aux_w = ret_ser2() - '0' ;
		aux_w = aux_w * 1000;
		aux_w = aux_w + ((ret_ser2() - '0' ) * 100);
		aux_w = aux_w + ((ret_ser2() - '0' ) * 10);
		aux_w = aux_w + ((ret_ser2() - '0' ));
		ret_ser2();
		return(aux_w);
	}

	word retira_xxxxx(void)
	{
		word aux_w;
		aux_w = ret_ser2() - '0' ;
		aux_w = aux_w * 10000;
		aux_w = aux_w + ((ret_ser2() - '0' ) * 1000);
		aux_w = aux_w + ((ret_ser2() - '0' ) * 100);
		aux_w = aux_w + ((ret_ser2() - '0' ) * 10);
		aux_w = aux_w + ((ret_ser2() - '0' ));
		ret_ser2();
		return(aux_w);
	}

	word retira_xxx_x_Q5(void)
	{
		word aux_l;
		aux_l = ret_ser2() - '0' ;
		aux_l = aux_l * 1000;
		aux_l = aux_l + ((ret_ser2() - '0' ) * 100);
		aux_l = aux_l + ((ret_ser2() - '0' ) * 10);
		ret_ser2();		// retira o ponto
		aux_l = aux_l + (ret_ser2() - '0' );
		aux_l = aux_l * 32;
		ret_ser2();
		return(word)(aux_l / 10);
	}
	word retira_xxx_x_Q6(void)
	{
		word aux_l;
		aux_l = ret_ser2() - '0' ;
		aux_l = aux_l * 1000;
		aux_l = aux_l + ((ret_ser2() - '0' ) * 100);
		aux_l = aux_l + ((ret_ser2() - '0' ) * 10);
		ret_ser2();		// retira o ponto
		aux_l = aux_l + (ret_ser2() - '0' );
		aux_l = aux_l * 64;
		ret_ser2();
		return(word)(aux_l / 10);
	}
	
	word retira_xxxx_x_q3(void)
	{
		word aux_l;
		aux_l = ret_ser2() - '0' ;
		aux_l = aux_l * 10000;
		aux_l = aux_l + ((ret_ser2() - '0' ) * 1000);
		aux_l = aux_l + ((ret_ser2() - '0' ) * 100);
		aux_l = aux_l + ((ret_ser2() - '0' ) * 10);
		ret_ser2();		// retira o ponto
		aux_l = aux_l + (ret_ser2() - '0' );
		aux_l = aux_l * 8;
		ret_ser2();
		return(word)(aux_l / 10);
	}

	word retira_xxxx_x_q5(void)
	{
		word aux_l;
		aux_l = ret_ser2() - '0' ;
		aux_l = aux_l * 10000;
		aux_l = aux_l + ((ret_ser2() - '0' ) * 1000);
		aux_l = aux_l + ((ret_ser2() - '0' ) * 100);
		aux_l = aux_l + ((ret_ser2() - '0' ) * 10);
		ret_ser2();		// retira o ponto
		aux_l = aux_l + (ret_ser2() - '0' );
		aux_l = aux_l * 32;
		ret_ser2();
		return(word)(aux_l / 10);
	}
	word retira_x_xx_q10(void)
	{
		word aux_l;
		aux_l = ret_ser2() - '0' ;
		aux_l = aux_l * 1000;
		ret_ser2();		// retira o ponto
		aux_l = aux_l + ((ret_ser2() - '0' ) * 100);
		aux_l = aux_l + ((ret_ser2() - '0' ) * 10);
		aux_l = aux_l * 1024;
		ret_ser2();
		return(word)(aux_l / 1000);
	}

#endif

void inic_rx()
{
	enable_interrupts(INT_RDA);
	ptrrx = 0;
	retrx = 0;
	numbrx = 0;
	numbtx = 0;
	ptrtx = 0;
	#if (vel_4800 == 1200)
		delay_ms(20);
	#else
		delay_ms(5);
	#endif
	#if (com_485 == true)
		output_low(direcao);
	#endif	
	#if (st5x==1)
		fled_tx = 1;
		fled_rx = 1;
	#endif
	#if ((controlador == true) || (st92 == true))
		led_rx = 0;
		led_tx = 0;
	#endif
	
}

#if (home_system == false)
	void dispara_tx(void)
	{
		disable_interrupts(INT_RDA);
		if (ptrtx > TAM_TX)
			{
			ptrtx = 0;
			goto encerra_dispara_tx;
			}
		#if (st5x==1)
			fled_tx = 0;
			fled_rx = 1;
		#endif
		#if ((controlador == true) || (st92 == true))
			led_tx = 1;
			led_rx = 0;
			#if (ST8100C == true)
				buf_display[4] = LED;
			#endif
			#if (disp_lcd == true)
				trata_saidas();
			#endif
		#endif
		#if (com_485 == true)
			output_high(direcao);
			#if (vel_4800 == 1200)
				delay_ms(10);
			#else
				delay_us(500);
			#endif
		  	while (time_out_modbus != 0)
		  		{
		  		}
		#endif	
		numbtx = ptrtx;
		ptrtx = 0;
		while(numbtx != 0)
			{
			putc(buf_tx[ptrtx++], modbus);
			numbtx--;
			}
encerra_dispara_tx:
		time_out_modbus = 6;
		inic_rx();
	}
#endif


void tx_lfcr (void){
	buf_tx[ptrtx++] = CR;
	buf_tx[ptrtx++] = LF;
}



char ret_ser(void){
	caracter = 0;
	if (retrx != ptrrx){
		caracter = buf_rx[retrx++];
	}
	if (ptrrx > TAM_RX){
		retrx = 0;
	}
	return(caracter);
}

#if (home_system == false)
	void tx_erro(void){
		ptrtx=0;
		if (erro==1){
			buf_tx[ptrtx++] = 'N';
		}
		buf_tx[ptrtx++] = 'O';
		buf_tx[ptrtx++] = 'K';
		buf_tx[ptrtx++] = CR;
		dispara_tx();
	}
#endif

#if (home_system == false)
	void seta_baud_rate(void)
	{
		#if (controlador == true)
			#if (com_rep == true)
		  		set_uart_speed (2400, rep);
			#endif
		#endif
		#if (st5x == true)
			#if (TECNOFLUX == TRUE)
		  		set_uart_speed (9600, modbus);
			  	return;
			#endif
		#endif
	
		#if (st9600r == true)
			#if (teste_baud_115	== true)
		  		set_uart_speed (57600, modbus);
			  	return;
			#endif	
		#endif	
	
		#if (printa == true)
		  	set_uart_speed (vel_19200, modbus);
			#if (st_prog == true)
				#if (simula_rep == true)
				 	set_uart_speed (vel_2400, sultech);
				#else
				 	set_uart_speed (vel_19200, sultech);
				#endif
			#endif
			return;
		#else
			#if (ad_microchip == true)
				#if (fixa_modb == true)
				  	set_uart_speed (vel_19200, modbus);
					#if (st_prog == true)
						#if (simula_rep == true)
						 	set_uart_speed (vel_2400, sultech);
						#else
						 	set_uart_speed (vel_19200, sultech);
						#endif
					#endif
					return;
				#endif
			#endif
		#endif
	
		if (baud_rate == vel_2400)
			{
			#if (st_prog == true)
				#if (simula_rep == true)
				 	set_uart_speed (vel_2400, sultech);
				#else
				 	set_uart_speed (vel_19200, sultech);
				#endif
			#endif
		  	set_uart_speed(vel_2400, modbus);
			}
		else if (baud_rate == vel_4800)
			{
			#if (st_prog == true)
				#if (simula_rep == true)
				 	set_uart_speed (vel_2400, sultech);
				#else
				 	set_uart_speed (vel_19200, sultech);
				#endif
			#endif
		  	set_uart_speed(vel_4800, modbus);
			}
		else if (baud_rate ==  vel_9600)
			{
			#if (st_prog == true)
				#if (simula_rep == true)
				 	set_uart_speed (vel_2400, sultech);
				#else
				 	set_uart_speed (vel_19200, sultech);
				#endif
			#endif
		  	set_uart_speed(vel_9600, modbus);
			}
		else if (baud_rate ==  vel_19200)
			{
			#if (st_prog == true)
				#if (simula_rep == true)
				 	set_uart_speed (vel_2400, sultech);
				#else
				 	set_uart_speed (vel_19200, sultech);
				#endif
			#endif
		  	set_uart_speed(vel_19200, modbus);
			}
		else if (baud_rate ==  vel_38400)
			{
			#if (st_prog == true)
				#if (simula_rep == true)
				 	set_uart_speed (vel_2400, sultech);
				#else
				 	set_uart_speed (vel_19200, sultech);
				#endif
			#endif
		  	set_uart_speed(vel_38400, modbus);
			}
		else if (baud_rate ==  vel_57600)
			{
			#if (st_prog == true)
				#if (simula_rep == true)
				 	set_uart_speed (vel_2400, sultech);
				#else
				 	set_uart_speed (vel_19200, sultech);
				#endif
			#endif
		  	set_uart_speed(vel_57600, modbus);
			}
		else
			{
		  	set_uart_speed(vel_19200, modbus);
			#if (st_prog == true)
				#if (simula_rep == true)
				 	set_uart_speed (vel_2400, sultech);
				#else
				 	set_uart_speed (vel_19200, sultech);
				#endif
			#endif
			}
	}
#endif	

#if (home_system == true)
	void le_dip_ligacao(void)
	{
		if (media_dip_vel == 4)
			{
			res_dip_vel = soma_dip_vel / 4;
			soma_dip_vel = 0;
			media_dip_vel = 0;
			}
		else if (media_dip_vel > 4)
			{
			soma_dip_vel = 0;
			media_dip_vel = 0;
			return;
			}
		else
			{
			soma_dip_vel += dip_vel;
			media_dip_vel++;
			return;
			}
		if (res_dip_vel < 50)			// 0000
			{
//			baud_rate = vel_4800;
			tipo_ligacao = 0;		// estrela
			}
		else if (res_dip_vel < 85)		// 1000
			{
//			baud_rate = vel_4800;
			tipo_ligacao = 0;		// estrela
			}
		else if (res_dip_vel < 155)		// 0100
			{
//			baud_rate = vel_4800;
			tipo_ligacao = 0;		// delta aberto, por enquanto fica em estrela depois vai para 3
			}
		else if (res_dip_vel < 215)		// 1100
			{
//			baud_rate = vel_4800;
			tipo_ligacao = 0;		// delta 
			}
	//
		else if (res_dip_vel < 285)		// 0010
			{
//			baud_rate = vel_19200;
			tipo_ligacao = 0;		// estrela
			}
		else if (res_dip_vel < 350)		// 1010
			{
//			baud_rate = vel_19200;
			tipo_ligacao = 0;		// estrela
			}
		else if (res_dip_vel < 420)		// 0110
			{
//			baud_rate = vel_19200;
			tipo_ligacao = 0;		// delta aberto, por enquanto fica em estrela depois vai para 3
			}
		else if (res_dip_vel < 480)		// 1110
			{
//			baud_rate = vel_19200;
			tipo_ligacao = 0;		// delta 
			}
	//
		else if (res_dip_vel < 530)		// 0001
			{
//			baud_rate = vel_9600;
			tipo_ligacao = 2;		// // delta aberto, por enquanto fica em estrela depois vai para 3
			}
		else if (res_dip_vel < 600)		// 1001
			{
//			baud_rate = vel_9600;
			tipo_ligacao = 2;		// estrela
			}
		else if (res_dip_vel < 670)		// 0101
			{
//			baud_rate = vel_9600;
			tipo_ligacao = 2;		// delta aberto, por enquanto fica em estrela depois vai para 3
			}
		else if (res_dip_vel < 730)		// 1101
			{
//			baud_rate = vel_9600;
			tipo_ligacao = 2;		// delta 
			}
	//
		else if (res_dip_vel < 780)		// 0011
			{
			baud_rate = vel_38400;
			tipo_ligacao = 0;		// estrela
			}
		else if (res_dip_vel < 850)		// 1011
			{
//			baud_rate = vel_38400;
			tipo_ligacao = 1;		// estrela
			}
		else if (res_dip_vel < 910)		// 0111
			{
//			baud_rate = vel_38400;
			tipo_ligacao = 1;		// delta aberto, por enquanto fica em estrela depois vai para 3
			}
		else if (res_dip_vel < 980)		// 1111
			{
//			baud_rate = vel_38400;
			tipo_ligacao = 1;		// delta 
			}
		else
			{
//			baud_rate = vel_19200;
			tipo_ligacao = 0;		// estrela
			}
	
		#if (controlador == true)
			#if (monofasico == true)
				if (tipo_ligacao == 1)
					{
					off_cor_delta = off_cor_s;
					}
			#else
				if (tipo_ligacao == 2)
					{
					#if (ade7754 == true)
						off_cor_delta = fase_delta;
					#else
						off_cor_delta = off_cor_s;
					#endif
					}
				else
					{
					off_cor_delta = 0;
					}
			#endif
		#else
			if (tipo_ligacao == 2)
				{
				#if (ade7754 == true)
					off_cor_delta = fase_delta;
				#else
//					off_cor_delta = off_cor_s;
				#endif
				}
			else
				{
//				off_cor_delta = 0;
				}
		#endif
	
	 	aux_b1 = read_byte(ee_tipo_ligacao);
		if (aux_b1 != tipo_ligacao)
			{
			write_byte(ee_tipo_ligacao, 0);
			}
	/*		
		#if (com_485 == true)
			output_high(direcao);
			delay_ms(5);
			
			fprintf(modbus,"%lu, %lu, %u",res_dip_vel,baud_rate, tipo_ligacao);
			fprintf(modbus,"\r\n");
			
			delay_ms(5);
			output_low(direcao);
		#endif
	*/		
	}

#endif
#if (st5x == TRUE)
	void le_dip_endereco(void)
	{
		#if (TECNOFLUX == TRUE)
			endereco_nro_serie = ((read_byte(ee_nro_3) -'0') * 10) + (read_byte(ee_nro_4) - '0');
		#endif
	}

	void le_dip_baud_ligacao(void)
	{
		#if (st5000c_rev12 == true)
			if ((input(BAUD0) == FALSE) && (input(BAUD1) == FALSE))
				{
				baud_rate = 38400;
				}
			else if ((input(BAUD0) == TRUE) && (input(BAUD1) == FALSE))
				{
				baud_rate = 19200;
				}
			else if ((input(BAUD0) == FALSE) && (input(BAUD1) == TRUE))
				{
				baud_rate = 9600;
				}
			else 
				{
				baud_rate = 4800;
				
				}
				
			if ((input(LIGA0) == FALSE) && (input(LIGA1) == FALSE))
				{
				tipo_ligacao = 1;		// delta 
				}
			else if ((input(LIGA0) == TRUE) && (input(LIGA1) == FALSE))
				{
				tipo_ligacao = 0;	// estrela
				}
			else if ((input(LIGA0) == FALSE) && (input(LIGA1) == TRUE))
				{
				tipo_ligacao = 2;		// delta aberto
				}
			else 
				{
				tipo_ligacao = 0;	// estrela
				}
			
		#else
			if (media_dip_vel == 4)
				{
				res_dip_vel = soma_dip_vel / 4;
				soma_dip_vel = 0;
				media_dip_vel = 0;
				}
			else if (media_dip_vel > 4)
				{
				soma_dip_vel = 0;
				media_dip_vel = 0;
				return;
				}
			else
				{
				soma_dip_vel += dip_vel;
				media_dip_vel++;
				return;
				}
			if (res_dip_vel < 50)			// 0000
				{
				baud_rate = vel_4800;
				tipo_ligacao = 0;		// estrela
				}
			else if (res_dip_vel < 85)		// 1000
				{
				baud_rate = vel_4800;
				tipo_ligacao = 0;		// estrela
				}
			else if (res_dip_vel < 155)		// 0100
				{
				baud_rate = vel_4800;
				tipo_ligacao = 2;		// delta aberto, por enquanto fica em estrela depois vai para 3
				}
			else if (res_dip_vel < 215)		// 1100
				{
				baud_rate = vel_4800;
				tipo_ligacao = 1;		// delta 
				}
		//
			else if (res_dip_vel < 285)		// 0010
				{
				baud_rate = vel_19200;
				tipo_ligacao = 0;		// estrela
				}
			else if (res_dip_vel < 350)		// 1010
				{
				baud_rate = vel_19200;
				tipo_ligacao = 0;		// estrela
				}
			else if (res_dip_vel < 420)		// 0110
				{
				baud_rate = vel_19200;
				tipo_ligacao = 2;		// delta aberto, por enquanto fica em estrela depois vai para 3
				}
			else if (res_dip_vel < 480)		// 1110
				{
				baud_rate = vel_19200;
				tipo_ligacao = 1;		// delta 
				}
		//
			else if (res_dip_vel < 530)		// 0001
				{
				baud_rate = vel_9600;
				tipo_ligacao = 0;		// estrela
				}
			else if (res_dip_vel < 600)		// 1001
				{
				baud_rate = vel_9600;
				tipo_ligacao = 0;		// estrela
				}
			else if (res_dip_vel < 670)		// 0101
				{
				baud_rate = vel_9600;
				tipo_ligacao = 2;		// delta aberto, por enquanto fica em estrela depois vai para 3
				}
			else if (res_dip_vel < 730)		// 1101
				{
				baud_rate = vel_9600;
				tipo_ligacao = 1;		// delta 
				}
		//
			else if (res_dip_vel < 780)		// 0011
				{
				baud_rate = vel_38400;
				tipo_ligacao = 0;		// estrela
				}
			else if (res_dip_vel < 850)		// 1011
				{
				baud_rate = vel_38400;
				tipo_ligacao = 0;		// estrela
				}
			else if (res_dip_vel < 910)		// 0111
				{
				baud_rate = vel_38400;
				tipo_ligacao = 2;		// delta aberto, por enquanto fica em estrela depois vai para 3
				}
			else if (res_dip_vel < 980)		// 1111
				{
				baud_rate = vel_38400;
				tipo_ligacao = 1;		// delta 
				}
			else
				{
				baud_rate = vel_19200;
				tipo_ligacao = 0;		// estrela
				}

		#endif		
		#if (controlador == true)
			#if (monofasico == true)
				if (tipo_ligacao == 1)
					{
					off_cor_delta = off_cor_s;
					}
			#else
				if (tipo_ligacao == 2)
					{
					#if (ade7754 == true)
						off_cor_delta = fase_delta;
					#else
						off_cor_delta = off_cor_s;
					#endif
					}
				else
					{
					off_cor_delta = 0;
					}
			#endif
		#else
			if (tipo_ligacao == 2)
				{
				#if (ade7754 == true)
					off_cor_delta = fase_delta;
				#else
	//				off_cor_delta = off_cor_s;
				#endif
				}
			else
				{
	//			off_cor_delta = 0;
				}
		#endif
		aux_b1 = read_byte(ee_tipo_ligacao);
		if (aux_b1 != tipo_ligacao)
			{
			write_byte(ee_tipo_ligacao, 0);
			}
		/*		
		#if (com_485 == true)
			output_high(direcao);
			delay_ms(5);
			
			fprintf(modbus,"%lu, %lu, %u",res_dip_vel,baud_rate, tipo_ligacao);
			fprintf(modbus,"\r\n");
			
			delay_ms(5);
			output_low(direcao);
		#endif
		*/		
	#if (home_system == false)
		#if (st5x == true)
			seta_baud_rate();
		#else
			aux_w1 =  read_word(ee_baud_rate);
			if (aux_w1 != baud_rate)
				{
				write_byte(ee_baud_rate, baud_rate);
				seta_baud_rate();
				}
		#endif
	#endif
	}
#endif				

#if (st5x == true)
	void trata_leds_tc(void)
	{
		if (sentido_r == 1)
			{
			fled_tc_r = 0;
			}
		else
			{
			fled_tc_r = 1;
			}
		if (sentido_s == 1)
			{
			fled_tc_s = 0;
			}
		else
			{
			fled_tc_s = 1;
			}
		if (sentido_t == 1)
			{
			fled_tc_t = 0;
			}
		else
			{
			fled_tc_t = 1;
			}
	}
#endif


void zera_soma_reg(void)
{
	soma_reg_tr = 0;
	soma_reg_cr = 0;
	#if (monofasico == false)
		soma_reg_ts = 0;
		soma_reg_tt = 0;
		soma_reg_cs = 0;
		soma_reg_ct = 0;
	#endif
	nro_soma_reg = 0;
}


void soma_reg(void)
{
re_soma_reg:
	#if (monofasico == true)
		soma_reg_tr = (int32)(soma_reg_tr + tensao_r);
	#else
		#if ((com_rep == true) && (GEBRAS == true))
			if (modo_rep == true)
				{
				soma_reg_tr = (int32)(soma_reg_tr + tensao_tri);
				soma_reg_ts = 0;
				soma_reg_tt = 0;
				soma_reg_cr = (int32)(soma_reg_cr + corrente_tri);
				soma_reg_cs = 0;
				soma_reg_ct = 0;
				goto fim_soma_reg;
				}
			else
				{
				if (tipo_ligacao == 0)
					{
					soma_reg_tr = (int32)(soma_reg_tr + tensao_r);
					soma_reg_ts = (int32)(soma_reg_ts + tensao_s);
					soma_reg_tt = (int32)(soma_reg_tt + tensao_t);
					}	
				else
					{
					soma_reg_tr = (int32)(soma_reg_tr + tensao_rs);
					soma_reg_ts = (int32)(soma_reg_ts + tensao_st);
					soma_reg_tt = (int32)(soma_reg_tt + tensao_rt);
					}
				}
		#else
		
			if (tipo_ligacao == 0)
				{
				soma_reg_tr = (int32)(soma_reg_tr + tensao_r);
				soma_reg_ts = (int32)(soma_reg_ts + tensao_s);
				soma_reg_tt = (int32)(soma_reg_tt + tensao_t);
				}	
			else
				{
				soma_reg_tr = (int32)(soma_reg_tr + tensao_rs);
				soma_reg_ts = (int32)(soma_reg_ts + tensao_st);
				soma_reg_tt = (int32)(soma_reg_tt + tensao_rt);
				}
		#endif
	#endif

	if (modo_funca == 3)
		{
		soma_reg_cr = 0;
		#if (monofasico == false)
			soma_reg_cs = 0;
			soma_reg_ct = 0;
		#endif
		}
	else
		{
		soma_reg_cr = (int32)(soma_reg_cr + corrente_r);
		#if (monofasico == false)
			soma_reg_cs = (int32)(soma_reg_cs + corrente_s);
			soma_reg_ct = (int32)(soma_reg_ct + corrente_t);
		#endif
		}
fim_soma_reg:
	nro_soma_reg++;
	if (nro_soma_reg == 0)
		{
		zera_soma_reg();
		}

#if (com_regs == false)
	if (nro_soma_reg == 60)
		{
		zera_soma_reg();
		goto re_soma_reg;
		}
#endif
}



////////////////////////////////////////////////////////////////////////////
//	float sqrt(float x)
////////////////////////////////////////////////////////////////////////////
// Description : returns the square root of x
// Date : N/A
//
float sqrty(float x)
{
   float y, res;
   BYTE *p;

   #ifdef _ERRNO
   if(x < 0)
   {
      errno=EDOM;
   }
   #endif

   if( x<=0.0)
	{
      return(0.0);
	}
   if( x == 0)
	{
      return(0.0);
	}

   y=x;
   p=&y;
   (*p)=(BYTE)((((int16)(*p)) + 127) >> 1);

   do {
      res=y;
      y+=(x/y);
      (*p)--;
   } while(res != y);

   return(res);
}



float sqrtx(float x)
{
   float y, res;
   BYTE *p;

   if(x < 0)
	   	{
		return(0.0);
   		}
   if( x<=0.0)
		{
	    return(0.0);
		}
//   if( x<=1.0)
//		{
//	    return(1.0);
//		}

   y=x;
   p=&y;
   (*p)=(BYTE)((((int16)(*p)) + 127) >> 1);


   do {
      	res=y;
      	y+=(x/y);
      	(*p)--;
//		pulsa_wdt();
	   } 
	while(res != y);


   return(res);
}



long uisqrt32(int32 r) 
{ 
   int32 t,b,c=0; 

   for (b=0x10000000;b!=0;b>>=2) { 
      t = c + b; 
      c >>= 1; 
      if (t <= r) { 
         r -= t; 
         c += b; 
      } 
   } 
   return(c); 
} 


void vrms()
{
   const long NUM_DATA_POINTS = 3000;
   long i;
   int value;
   float voltage;

   printf("Sampling:\r\n");

   setup_port_a( ALL_ANALOG );
   setup_adc( ADC_CLOCK_INTERNAL );
   set_adc_channel( 1 );

   while(TRUE)
   {
      voltage = 0;
      for(i=0; i<NUM_DATA_POINTS; ++i)
      {
         value = Read_ADC();
         voltage += (float)value*(float)value;
      }
      voltage /=2601.0;
      voltage = sqrt(voltage/(NUM_DATA_POINTS));
      printf("\r\nInput =  %f V     %f dB\r\n", voltage, 20*log10(voltage));
   }
}


#if (com_relogio == false)
	void rtc_get_e2p(void)
	{
		dia = read_byte(ee_dia);
		mes = read_byte(ee_mes);
		ano = read_byte(ee_ano);
		hora = read_byte(ee_hora);
		addr = ee_tabela_minuto;
		for (aux_b1 = 0; aux_b1 < 60; aux_b1++)
			{
			minuto = read_byte(addr++);
			if (minuto == 0xff)
				{
				if (addr == 0)
					{
					minuto = 0;
					break;
					}
				else
					{
					addr--;
					minuto = read_byte(addr);
					break;
					}	
				}
			}
			
		if ((dia == 0) || (dia > 31))
			{
			dia = ((cdata[0] -'0') * 10) + (cdata[1]-'0'); 
			}
		if ((mes < 1) || (mes > 12))
			{
			if (cdata[3] == 'a')
				{
				if (cdata[4] == 'b')
					{
					mes = 4;
					}
				else
					{
					mes = 8;
					}
				}
			else if (cdata[3] == 'd')
				{
				mes = 12;
				}
			else if (cdata[3] == 'f')
				{
				mes = 2;
				}
			else if (cdata[3] == 'j')
				{
				if (cdata[4] == 'a')
					{
					mes = 1;
					}
				else if (cdata[5] == 'n')
					{
					mes = 6;
					}
				else
					{
					mes = 7;
					}
				}
			else if (cdata[3] == 'm')
				{
				if (cdata[5] == 'r')
					{
					mes = 3;
					}
				else
					{
					mes = 5;
					}
				}
			else if (cdata[3] == 's')
				{
				mes = 9;
				}
			else if (cdata[3] == 'o')
				{
				mes = 10;
				}
			else
				{
				mes = 11;
				}
			}
		if ((ano < 5) || (ano > 99))
			{
			ano = ((cdata[7] -'0') * 10) + (cdata[8]-'0'); 
			}
		if (hora > 23)
			{
			hora = ((ctime[0] -'0') * 10) + (ctime[1]-'0'); 
			}
		if (minuto > 59)
			{
			minuto = ((ctime[3] -'0') * 10) + (ctime[4]-'0'); 
			}
		if (segundo > 59)
			{
			segundo = ((ctime[6] -'0') * 10) + (ctime[7]-'0'); 
			}
	}
	
	void rtc_wr_e2p(void)
	{
		write_byte(ee_dia, dia);
		write_byte(ee_mes, mes);
		write_byte(ee_ano, ano);
		write_byte(ee_hora, hora);
		write_byte(ee_minuto, minuto);
	}

	void le_calend_int(void)
	{
		if (viroumin == 1)
			{
	   		minuto++;
	   		write_byte(ee_tabela_minuto + minuto, minuto);
	   		write_byte(1 + ee_tabela_minuto + minuto, 0xff);
		   	if (minuto >= 60)
				{
				minuto = 0;
		   		write_byte(ee_tabela_minuto + minuto, minuto);
	 	  		write_byte(1 + ee_tabela_minuto + minuto, 0xff);
				hora++;
				virouhora = 1;
				if (hora >= 24)
					{
					hora = 0;
		   			viroudia = 1;
					dia++;
					if ((mes == 1) || (mes == 3)  || (mes == 5) || (mes == 7) || (mes == 8) || (mes == 10) || (mes == 12))
						{
						if (dia >= 32)
							{
							dia = 1;
							mes++;
							viroumes = 1;
							}
						}
					else if ((mes == 4) || (mes == 6)  || (mes == 9) || (mes == 11))
						{
						if (dia >= 31)
							{
							dia = 1;
							mes++;
							viroumes = 1;
							}
						}
					else 
						{
						if (dia >= 29)
							{
							dia = 1;
							mes++;
							viroumes = 1;
							}
						}
					if (mes > 12)
						{
						ano++;
						mes = 1;
						}
					write_byte(ee_dia, dia);
					write_byte(ee_mes, mes);
					write_byte(ee_ano, ano);
					}
				write_byte(ee_hora, hora);
				}

			
			}
	}
#endif


#if (com_relogio == true)
	//  converte valor do relogio para um long em segundos,
	int32 conv_relogio_long(void)
		{	
		aux_l2 = (int32)(hora);
		aux_w1 = (int16)(minuto);
		aux_l2 = (int32)(aux_l2 * 3600);
		aux_w1 = (int16)(aux_w1 * 60);
		return(int32)(aux_l2 + aux_w1 + segundo);
		}
	
#endif


void salva_programa(void)
{
	programando = 0;
	
	#if (st8500c == true)
		aux_w1 = 0;
		for (aux_b1 = 0; aux_b1 < 12; aux_b1++)
			{
			write_word((ee_dem_cont_ponta + aux_w1),dem_cont_ponta[aux_b1]);
			write_word((ee_dem_cont_fora_ponta + aux_w1),dem_cont_fora_ponta[aux_b1]);
			aux_w1 += 2;
			}
		write_word(ee_carga_programada,carga_programada);

		write_byte(ee_mes_inicio_pc,mes_inicio_pc);
		write_byte(ee_dia_inicio_pc, dia_inicio_pc);
		write_byte(ee_dia_final_pc,dia_final_pc);
		write_byte(ee_mes_final_pc,mes_final_pc);

		#if (com_rep == true)
			write_word(ee_fat_conv_ativa, fat_conv_ativa);
			write_word(ee_fat_conv_reativa, fat_conv_reativa);
			write_byte(ee_protocolo_REP, protocolo_REP);
		#endif

		write_byte(ee_hora_ponta, hora_ponta);
		write_byte(ee_hora_final_ponta, hora_final_ponta);
		write_byte(ee_minuto_ponta, minuto_ponta);
		write_byte(ee_minuto_final_ponta, minuto_final_ponta);

		#if (com_tc == true)		
			write_word(ee_valor_tc, valor_tc);
			write_word(ee_valor_tp, valor_tp);
			tipo_ligacao = 0;
			write_byte(ee_tipo_ligacao, tipo_ligacao);
		#endif
		write_byte(ee_modo_saidas, modo_saidas);
		
	#else
		write_word(ee_ten_nomi, ten_nomi);
		write_word(ee_valor_tp, valor_tp);
		
		write_byte(ee_hora_ponta, hora_ponta);
		write_byte(ee_hora_final_ponta, hora_final_ponta);
		write_byte(ee_minuto_ponta, minuto_ponta);
		write_byte(ee_minuto_final_ponta, minuto_final_ponta);


		#if (com_consumo == true)
			aux_intervalo_integra = intervalo_integra;
		#endif

		aux_b1 = read_byte(ee_modo_funca);
		if (aux_b1 != modo_funca)
			{
			#if (funcao_505 == true)
				inic_tensoes_505();
			#endif
			}
		if (registro == 0)
			{
			write_byte(ee_modo_funca, modo_funca);
			}
	
		write_byte(ee_set_point, set_point);

		#if (com_rep == true)
			write_byte(ee_modo_rep, modo_rep);
			write_byte(ee_protocolo_REP, protocolo_REP);
			write_word(ee_fat_conv_ativa, fat_conv_ativa);
			write_word(ee_fat_conv_reativa, fat_conv_reativa);
		#endif
	
	#endif

	#if (portatil == TRUE)
		{
		endereco = 1;
		baud_rate = vel_19200;
		}
	#endif
	#if (home_system == false)
		write_word(ee_baud_rate, baud_rate);
		seta_baud_rate();
		write_byte(ee_endereco, endereco);
	#endif
	

	#if (controlador == true)
		write_byte(ee_cor_minima, cor_minima);
		#if (com_rep == true)
			write_word(ee_cor_minima_rep, cor_minima_rep);
		#endif
		write_byte(ee_com_des_ten_a, com_des_ten_a);
		write_byte(ee_com_des_ten_b, com_des_ten_b);
		write_byte(ee_com_des_chtt, com_des_chtt);
		write_byte(ee_com_des_chtc, com_des_chtc);
		write_byte(ee_com_des_fp_ind_cap, com_des_fp_ind_cap);
		#if (st8500c == true)
			write_byte(ee_nro_cargas, nro_cargas);
			write_word(ee_max_kw, max_kw);
		#else
			write_byte(ee_nro_bancos_capacitor, nro_bancos_capacitor);
			write_byte(ee_max_kvar, max_kvar);
			write_byte(ee_min_kvar, min_kvar);
		#endif
	
		write_byte(ee_tempo_aciona, tempo_aciona);
		write_byte(ee_tempo_desaciona, tempo_desaciona);
		write_byte(ee_sequencia, sequencia);

		#if (prog_defasagem ==	true)
			write_byte(ee_defasagem, defasagem);
		#endif

		#if (st8500c == true)
			write_byte(ee_tipo_controle_demanda, tipo_controle_demanda);

			aux_w1 = ee_carga_1;
			aux_w2 = ee_tempo_repouso_1;
			for (aux_b1 = 0; aux_b1 < nro_cargas; aux_b1++)
				{
				 write_byte(aux_w1++, carga[aux_b1]);
				 write_byte(aux_w2++, tempo_repouso[aux_b1]);
				 write_byte(ee_forma_controle + aux_b1, forma_controle[aux_b1]);
				 write_byte(ee_hora_liga_controle + aux_b1, hora_liga_controle[aux_b1]);
				 write_byte(ee_minuto_liga_controle + aux_b1, minuto_liga_controle[aux_b1]);
				 write_byte(ee_hora_desliga_controle + aux_b1, hora_desliga_controle[aux_b1]);
				 write_byte(ee_minuto_liga_controle + aux_b1, minuto_desliga_controle[aux_b1]);
				}
		#else			
			aux_w1 = ee_banco_capacitor_1;
			aux_w2 = ee_tempo_repouso_1;
			for (aux_b1 = 0; aux_b1 < nro_bancos_capacitor; aux_b1++)
				{
				 write_byte(aux_w1++, banco_capacitor[aux_b1]);
				 write_byte(aux_w2++, tempo_repouso[aux_b1]);
				}
		#endif
	#endif
	#if (com_regs == true)
		inicializa_regs();
		prox_grava = aux_l2 + intervalo_reg;
	#endif	

	#if (portatil == true)
		#if (se_com_flex == true)
			write_byte(ee_tipo_ponteira, tipo_ponteira);
			atualiza_ganho(tipo_ponteira);
		#else
			write_word(ee_valor_tc, valor_tc);
		#endif
		
	#else
		write_word(ee_valor_tc, valor_tc);
	#endif
	write_word(ee_intervalo_reg, intervalo_reg);
	
	#if (com_menu == true)
		write_byte(ee_idioma, idioma);
	#endif

	write_byte(ee_intervalo_integra, intervalo_integra);
	write_byte(ee_forma_reg_cht, forma_reg_cht);
	write_byte(ee_registro, registro);
	write_byte(ee_ala_fp_ind, ala_fp_ind);
	write_byte(ee_ala_fp_cap, ala_fp_cap);
	write_byte(ee_ala_ten_a, ala_ten_a);
	write_byte(ee_ala_ten_b, ala_ten_b);
	write_byte(ee_ala_sc, ala_sc);
	write_byte(ee_ala_subc, ala_subc);
	#if (com_cht == true)
		write_byte(ee_ala_chtt, ala_chtt);
		write_byte(ee_ala_chtc, ala_chtc);
	#endif
	#if (st8500c == true)
		write_byte(ee_ala_demanda_ativa, ala_demanda_ativa);
	#else
		#if (com_alarme_demanda== true)
			write_word(ee_ala_demanda_ativa, ala_demanda_ativa);
		#endif
	#endif
	
	write_byte(ee_tipo_ligacao, tipo_ligacao);


}

#if (portatil == true)
	void ajusta_off_set_fp(void)
	{						
		#if (se_com_flex ==	true)
			aux_w1 = ee_off_fp_9001g1;
			aux_w1 += tipo_ponteira;
			off_set_fp[tipo_ponteira] = distancia_fase;
			off_cor_r = distancia_fase;
			write_byte(aux_w1, off_cor_r);
		#else
			for (aux_b1 = 0; aux_b1 < NRO_POSI_TC; aux_b1++)
				{
				if (valor_tc == tabela_tc[aux_b1])
					{
					break;
					}
				}
			aux_w1 = ee_off_fp_20;
			aux_w1 = aux_w1 + aux_b1;
			off_set_fp[aux_b1] = distancia_fase;
			off_cor_r = distancia_fase;
			write_byte(aux_w1, off_cor_r);
		#endif
	}

	void ajusta_off_set_cor_r(signed char unidade)
	{
		#if (se_com_flex ==	true)
			aux_w1 = (ee_os_cor_r_9001g1 + tipo_ponteira) * 3;
			os_cor_pt_r[tipo_ponteira] += unidade;
			write_byte(aux_w1, os_cor_pt_r[tipo_ponteira]);
		#else
			aux_w1 = ee_os_cor_r_20;
			for (aux_b1=0; aux_b1 < NRO_POSI_TC; aux_b1++)
				{
				if (valor_tc == tabela_tc[aux_b1])
					{
					os_cor_pt_r[aux_b1] += unidade;
					write_byte(aux_w1, os_cor_pt_r[aux_b1]);
					break;
					}
				aux_w1 += 3;
				}
		#endif
	}

	void ajusta_off_set_cor_s(signed char unidade)
	{
		#if (se_com_flex ==	true)
			aux_w1 = (ee_os_cor_s_9001g1 + tipo_ponteira) * 3;
			os_cor_pt_s[tipo_ponteira] += unidade;
			write_byte(aux_w1, os_cor_pt_s[tipo_ponteira]);
		#else
			aux_w1 = ee_os_cor_s_20;
			for (aux_b1=0; aux_b1 < NRO_POSI_TC; aux_b1++)
				{
				if (valor_tc == tabela_tc[aux_b1])
					{
					os_cor_pt_s[aux_b1] += unidade;
					write_byte(aux_w1, os_cor_pt_s[aux_b1]);
					break;
					}
				aux_w1 += 3;
				}
		#endif
	}

	void ajusta_off_set_cor_t(signed char unidade)
	{
		#if (se_com_flex ==	true)
			aux_w1 = (ee_os_cor_t_9001g1 + tipo_ponteira) * 3;
			os_cor_pt_t[tipo_ponteira] += unidade;
			write_byte(aux_w1, os_cor_pt_t[tipo_ponteira]);
		#else
			aux_w1 = ee_os_cor_t_20;
			for (aux_b1=0; aux_b1 < NRO_POSI_TC; aux_b1++)
				{
				if (valor_tc == tabela_tc[aux_b1])
					{
					os_cor_pt_t[aux_b1] += unidade;
					write_byte(aux_w1, os_cor_pt_t[aux_b1]);
					break;
					}
				aux_w1 += 3;
				}
		#endif
	}

	void ajusta_off_set_pot_r(signed char unidade)
	{
		#if (se_com_flex ==	true)
			aux_w1 = (ee_os_pot_r_9001g1 + tipo_ponteira) * 3;
			os_pot_pt_r[tipo_ponteira]--;
			write_byte(aux_w1, os_pot_pt_r[tipo_ponteira]);
		#else
			aux_w1 = ee_os_pot_r_20;
			for (aux_b1=0; aux_b1 < NRO_POSI_TC; aux_b1++)
				{
				if (valor_tc == tabela_tc[aux_b1])
					{
					os_pot_pt_r[aux_b1]--;
					write_byte(aux_w1, os_pot_pt_r[aux_b1]);
					break;
					}
				aux_w1 += 3;
				}
		#endif
	}

	void ajusta_off_set_pot_s(signed char unidade)
	{
		#if (se_com_flex ==	true)
			aux_w1 = (ee_os_pot_s_9001g1 + tipo_ponteira) * 3;
			os_pot_pt_s[tipo_ponteira]--;
			write_byte(aux_w1, os_pot_pt_s[tipo_ponteira]);
		#else
			aux_w1 = ee_os_pot_s_20;
			for (aux_b1=0; aux_b1 < NRO_POSI_TC; aux_b1++)
				{
				if (valor_tc == tabela_tc[aux_b1])
					{
					os_pot_pt_s[aux_b1]--;
					write_byte(aux_w1, os_pot_pt_s[aux_b1]);
					break;
					}
				aux_w1 += 3;
				}
		#endif
	}

	void ajusta_off_set_pot_t(signed char unidade)
	{
		#if (se_com_flex ==	true)
			aux_w1 = (ee_os_pot_t_9001g1 + tipo_ponteira) * 3;
			os_pot_pt_t[tipo_ponteira]--;
			write_byte(aux_w1, os_pot_pt_t[tipo_ponteira]);
		#else
			aux_w1 = ee_os_pot_t_20;
			for (aux_b1=0; aux_b1 < NRO_POSI_TC; aux_b1++)
				{
				if (valor_tc == tabela_tc[aux_b1])
					{
					os_pot_pt_t[aux_b1]--;
					write_byte(aux_w1, os_pot_pt_t[aux_b1]);
					break;
					}
				aux_w1 += 3;
				}
		#endif
	}

#endif


#if (st92 == true)
	void trata_saidas(void)
	{
	aux_b1 = LED;
	output_low(CS_IO2);
	output_d(aux_b1);
	output_high (CS_IO2);

	output_low(CS_IO4);
	output_d(0b00010000);
	output_high (CS_IO4);

	}
#endif

#if (protocolo_abb == true)
	word converte_abb(int32 grandeza, char tipo)
	{
	if (tipo == 'C')			// Corrente
		{										//abb 		1000A = 16384
		aux_l1 = grandeza;
		aux_l1 = (aux_l1 * 2048) / 500;			// 2048 =  16384 / 8
//		aux_l1 = (aux_l1 * 2048) / (valor_tc/ 100);			// 2048 =  16384 / 8
		return((word)(aux_l1));		
		}
	else if (tipo == 'T')		// Tensao		VABB = ((VQ6 * 16384) / 64) / 254
		{																	
		aux_l1 = grandeza;
		aux_l1 = (aux_l1 * 256) / 254;			// 256 = 16384/ 64
		return((word)(aux_l1));		
		}
	else if (tipo == 'P')		// Potencia
		{
		aux_f1 = grandeza;
		aux_f1 = ((((aux_f1 * 10) / 32) * 16384) / (254 * 5));			// 512 = 16384 / 32
		return((word)(aux_f1));		
		}
	else if (tipo == 'F')		// Fator de Potencia
		{
		if (grandeza > 32768)
			{
			aux_f1 = (65536 - grandeza);
			}
		else
			{
			aux_f1 = grandeza;
			}
		aux_f1 = (aux_f1 / 1024);
		aux_l1 = aux_f1 * 16384;
		return((word)(aux_l1));
		}
	else if (tipo == 'A')		// Angulo
		{
		short sinal;
		if (grandeza > 32768)
			{
			sinal = 1;
			aux_f1 = (65536 - grandeza);
			}
		else
			{
			sinal = 0;
			aux_f1 = grandeza;
			}

		if (addr_regs_modbus == 139)
			{
			if (sentido_r == 1)
				{
				aux_f1 = aux_f1 * -1;
				}
			}
		if (addr_regs_modbus == 140)
			{
			if (sentido_s == 1)
				{
				aux_f1 = aux_f1 * -1;
				}
			}
		if (addr_regs_modbus == 141)
			{
			if (sentido_t == 1)
				{
				aux_f1 = aux_f1 * -1;
				}
			}
		if (addr_regs_modbus == 142)
			{
			//Para FP Total nao consideramos TC Invertido
			}

		aux_f1 = (aux_f1 / 1024);
		aux_f1 = (acos(aux_f1) * 180) / 3.1416;
		aux_f1 = (aux_f1 * 16384) / 360;
		
		if (sinal == 1)
			{
			aux_w1 = aux_f1 + 0x8000;
			}
		else
			{
			aux_w1 = aux_f1;
			}
		return((word)(aux_w1));
		}
	else if (tipo == 'B')
		{
		aux_l1 = (((grandeza / 4) * 8192) / 50);
		return((word)(aux_l1));
		}
	else if (tipo == 'D')		// Demanda
		{
		aux_f1 = grandeza;
		aux_f1 = (((aux_f1 * 10) * 16384) / (254 * 5));
		return((word)(aux_f1));		
		}
	else
		{
		return (0);
		}
	}
#endif

