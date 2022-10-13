/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_COMU                                                        *
; Funcao: MODULO gerencialde comunicação rs232/485						 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */
  

//void le_endereco(void);
//void le_nro_pontos(void);

void modbus_funcao01(void)
{
	char ptrtx_old;
	char bits1, bits2, bits3, bits4, bits5 ;

	bits1 = 0;
	bits2 = 0;
	bits3 = 0;
	bits4 = 0;
	bits5 = 0;
	if (tem_alarme == 1)
		{
		bits1 = 0b00000100;
		}
	shift_left(&bits2, 1, erro);				//0
	shift_left(&bits2, 1, tem_ocor);			//1
	shift_left(&bits2, 1, tem_alarme);			//2
	shift_left(&bits2, 1, 0);					//3
	shift_left(&bits2, 1, tem_erro);			//4
#if (portatil == true)
	shift_left(&bits2, 1, existe_local);		//5
	shift_left(&bits2, 1, digitou_texto);		//6
#else
	shift_left(&bits2, 1, 0);		//5
	shift_left(&bits2, 1, 0);		//6
#endif
	shift_left(&bits2, 1, tem_comando_alarme);	//7

	shift_left(&bits3, 1, fp_ind);
	shift_left(&bits3, 1, fp_cap);
	#if (monofasico == true)
		shift_left(&bits3, 1, ten_a_r);
		shift_left(&bits3, 1, 0);
		shift_left(&bits3, 1, 0);
		shift_left(&bits3, 1, ten_b_r);
		shift_left(&bits3, 1, 0);
		shift_left(&bits3, 1, 0);
	#else
		shift_left(&bits3, 1, ten_a_r);
		shift_left(&bits3, 1, ten_a_s);
		shift_left(&bits3, 1, ten_a_t);
		shift_left(&bits3, 1, ten_b_r);
		shift_left(&bits3, 1, ten_b_s);
		shift_left(&bits3, 1, ten_b_t);
	#endif

	shift_left(&bits4, 1, chtt_a);
	shift_left(&bits4, 1, chtc_a);
	#if (monofasico == true)
		shift_left(&bits4, 1, cor_a_r);
		shift_left(&bits4, 1, 0);
		shift_left(&bits4, 1, 0);
		shift_left(&bits4, 1, cor_b_r);
		shift_left(&bits4, 1, 0);
		shift_left(&bits4, 1, 0);
	#else
		shift_left(&bits4, 1, cor_a_r);
		shift_left(&bits4, 1, cor_a_s);
		shift_left(&bits4, 1, cor_a_t);
		shift_left(&bits4, 1, cor_b_r);
		shift_left(&bits4, 1, cor_b_s);
		shift_left(&bits4, 1, cor_b_t);
	#endif

	#if (monofasico == true)
		shift_left(&bits5, 1, sentido_r);
		shift_left(&bits5, 1, 0);
		shift_left(&bits5, 1, 0);
		shift_left(&bits5, 1, ffase_r);
		shift_left(&bits5, 1, 0);
		shift_left(&bits5, 1, 0);
		shift_left(&bits5, 1, 0);
		shift_left(&bits5, 1, 0);
	#else
		shift_left(&bits5, 1, sentido_r);
		shift_left(&bits5, 1, sentido_s);
		shift_left(&bits5, 1, sentido_t);
		shift_left(&bits5, 1, ffase_r);
		shift_left(&bits5, 1, ffase_s);
		shift_left(&bits5, 1, ffase_t);
		shift_left(&bits5, 1, 0);
		shift_left(&bits5, 1, 0);
	#endif

  	erro_mod = 0;
	qerro_mod = 0;

	le_endereco();
	le_nro_pontos();
                    
  	ptrtx_old = ptrtx;
  	ptrtx++;

    aux_b2 = 1+(char)((nro_pontos_modbus / 8));
	if (addr_regs_modbus == 0)
		{
	    erro_mod = 1;
		qerro_mod = 2;
		}
    aux_b4 = addr_regs_modbus - 1;
	aux_b3 = nro_pontos_modbus;
	if (erro_mod == 0)
		{
		existe = 0;			    
		for (aux_b1 = 0; aux_b1 < aux_b2; aux_b1++)
			{
			switch(addr_regs_modbus)
				{
		 	    case 1:
		 	    	{
		 	    	existe = 1;
					data1 = bits1;
					break;
		 	    	}
		 	    case 2:
		 	    	{
		 	    	existe = 1;
	 	    		data1 = bits2;	/* le byte */
					break;
		 	    	}
		 	    case 3:
		 	    	{
		 	    	existe = 1;
	 	    		data1 = bits3;		/* le byte */
					break;
		 	    	}
		 	    case 4:
		 	    	{
		 	    	existe = 1;
	 	    		data1 = bits4;		/* le byte */
					break;
		 	    	}
		 	    case 5:
		 	    	{
		 	    	existe = 1;
	 	    		data1 = bits5;		/* le byte */
					break;
		 	    	}
				#if (controlador == true)		 	    	
			 	    case 6:
			 	    	{
		 		    	existe = 1;
	 	    			data1 = SAIDA2;		/* le byte */
						break;
			 	    	}
			 	    case 7:
		 		    	{
			 	 	   	existe = 1;
	 	    			data1 = SAIDA3;		/* le byte */
						break;
		 		    	}
		 		#endif
			 	default:
			 		{
	 				data1 = 0;
			 		}
			 	}
			if (existe == 1)
				{	
 	    		if ( aux_b3 > 8 )			
 	    			{                   /* se tem mais de 8 bits a serem transmitidos,*/
 	    			 aux_b3 = aux_b3 - 8;			/* apenas tira 8 de aux_b3 */
 	    			}
 	    		else
 	    			{
 	    			 data1 = data1 >> (8 - aux_b3);		/* se são menos de 8 bits , volta para mantar aux_b3 bits */
 	    			}
				}			
			else
				{
				data1 = 0;
				}

			poe_byte_buftx();
			addr_regs_modbus++;
			
			if (erro_mod == 1)
				{
				break;
				}
			}    
    	}
	buf_tx[ptrtx_old] = 1+(char)((nro_pontos_modbus / 8));  /* monta nro de pontos */

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


