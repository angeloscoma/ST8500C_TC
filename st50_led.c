/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: st50_led                                                        *
; Funcao: MODULO ROTINAS             									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */
  



//short led;


void trata_status_led(void)
{
	switch(status_flags)
	{
		case 1:
			{
			if ((ten_a_r == 1) || (ten_a_s == 1) || (ten_a_t == 1))
				{
       			status_led = 1;
       			}
       		else
       			{
       			status_flags++;
       			}
       		break;
       		}
		case 2:
			{
			if ((ten_b_r == 1) || (ten_b_s == 1) || (ten_b_t == 1))
				{
       			status_led = 2;
       			}
       		else
       			{
       			status_flags++;
       			}
       		break;
       		}
		case 3:
			{
			if ((cor_a_r == 1) || (cor_a_s == 1) || (cor_a_t == 1))
				{
       			status_led = 3;
       			}
       		else
       			{
       			status_flags++;
       			}
       		break;
       		}
		case 4:
			{
			if (chtt_a == 1)
				{
       			status_led = 4;
       			}
       		else
       			{
       			status_flags++;
       			}
       		break;
       		}
		case 5:
			{
			if (chtc_a == 1)
				{
       			status_led = 5;
       			}
       		else
       			{
       			status_flags++;
       			}
       		break;
       		}
		case 6:
			{
			if (sentido_r == 1)
				{
       			status_led = 6;
       			}
       		else
       			{
       			status_flags++;
       			}
       		break;
       		}
		case 7:
			{
			if (sentido_s == 1)
				{
       			status_led = 7;
       			}
       		else
       			{
       			status_flags++;
       			}
       		break;
       		}
		case 8:
			{
			if (sentido_t == 1)
				{  
       			status_led = 8;
       			}
       		else
       			{
       			status_flags++;
       			}
       		break;
       		}
		case 9:
			{
			if (fp_ind == 1)
				{  
       			status_led = 9;
       			}
       		else
       			{
       			status_flags++;
       			}
       		break;
       		}
		case 10:
			{
			if (fp_cap == 1)
				{  
       			status_led = 10;
       			}
       		else
       			{
       			status_flags++;
       			}
       		break;
       		}
		case 11:
			{
			if ((cor_b_r == 1) || (cor_b_s == 1) || (cor_b_t == 1))
				{
       			status_led = 11;
       			}
       		else
       			{
       			status_flags++;
       			}
       		break;
       		}
		case 12:
			{
			if ((ffase_r == 1) || (ffase_s == 1) || (ffase_t == 1))
				{
       			status_led = 12;
       			}
       		else
       			{
       			status_flags++;
       			}
       		break;
       		}
		case 13:
			{
			if (tem_comando_alarme == 1)
				{
				if (tem_alarme == 1)
					{
					status_led = 13;
					}
	       		else
    	   			{
       				status_flags++;
       				}
				}
       		else
       			{
       			status_flags++;
       			}
       		break;
			}
		case 14:
			{
			if (erro_freq == 1)
				{  
       			status_led = 14;
       			}
       		else
       			{
       			status_flags++;
       			}
       		break;
       		}

	 	default:
 			{
			status_flags = 1;
			status_led = 0;
	 		}
       } 
}


void trata_led(void)
{
	if (nro_pisca_led == 0)
		{
		nro_pisca_led = status_led * 2;

//			#if (com_485 == true)
//				output_high(direcao);
//				delay_ms(1);
//			#endif
//       	fprintf(modbus,"\r\n:%u ; %u; %u; %u\r\n", nro_pisca_led, status_led, time_led, status_flags);
//			#if (com_485 == true)
//				output_low(direcao);
//				delay_ms(1);
//			#endif
		
		}
	
}


