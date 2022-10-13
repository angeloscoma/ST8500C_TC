/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_COMU                                                        *
; Funcao: MODULO gerencialde comunicação rs232/485						 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */
  

void modbus_funcao17(void)
{
	char ptrtx_old;
	char aux1;
	char buf_nro[4];

	#if (controlador == true)
		salva_contadores();
	#endif

	buf_nro[0] = read_byte(ee_nro_1);
	buf_nro[1] = read_byte(ee_nro_2);
	buf_nro[2] = read_byte(ee_nro_3);
	buf_nro[3] = read_byte(ee_nro_4);
	
	ptrtx_old = ptrtx;
  	ptrtx = ptrtx + 1;
    nro_pontos_modbus = 0;
//								  012345678901234567890
//								  0         10  14
//		const char cequipo[22] = "ST5000T-V3.16-0001.C";
         
	existe = false;     
    while(TRUE)
       	{
       	data1 = cequipo[nro_pontos_modbus];
       	if (data1 == '@') 
       		{
			if ((buf_nro[0] > ('0'- 1)) && (buf_nro[0] < ('9' + 1)))
				{
				if ((buf_nro[1] > ('0'- 1)) && (buf_nro[1] < ('9' + 1)))
					{
					if ((buf_nro[2] > ('0'- 1)) && (buf_nro[2] < ('9' + 1)))
						{
						if ((buf_nro[3] > ('0'- 1)) && (buf_nro[3] < ('9' + 1)))
							{
							buf_tx[ptrtx++] = '-';
							nro_pontos_modbus++;
							existe = true;
						    for (aux1 = 0; aux1 < 4; aux1++)
       							{
								buf_tx[ptrtx++] = buf_nro[aux1];
								nro_pontos_modbus++;
       							}
							}
						}
					}
				}
			if (existe == false)
				{
				buf_tx[ptrtx++] = '-';
				nro_pontos_modbus++;
			    for (aux1 = 0; aux1 < 4; aux1++)
					{
			       	data1 = cequipo[nro_pontos_modbus];
					buf_tx[ptrtx++] = data1;
					nro_pontos_modbus++;
					}

				}
       		}
		else
			{
	       	if (data1 == 0) 
    	   		{
				break;
				}
			buf_tx[ptrtx++] = data1;
			nro_pontos_modbus++;
			}
       	}

    for (aux1 = 0; aux1 < 9; aux1++)
       	{
		buf_tx[ptrtx++] = cdata[aux1];
		nro_pontos_modbus++;
       	}
    for (aux1 = 0; aux1 < 8; aux1++)
       	{
		buf_tx[ptrtx++] = ctime[aux1];
		nro_pontos_modbus++;
       	}

    	
    data1_int = ptrtx;
    ptrtx = ptrtx_old;
    ptrtx_old = data1_int;
	data1 = nro_pontos_modbus;		/* monta nro de pontos */
	buf_tx[ptrtx++] = data1;
    ptrtx = ptrtx_old;
                    
	crc_modbus =  crc16(buf_tx, ptrtx, 'M');
	data1_int = crc_modbus;
	poe_word_buftx();
	dispara_tx();
					
}


	 
