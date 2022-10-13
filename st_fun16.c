/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_COMU                                                        *
; Funcao: MODULO gerencialde comunicação rs232/485						 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */
  


void modbus_funcao16(void)
{
	char aux_b3;
	le_endereco();
	le_nro_regs();
	le_byte_count();

	erro_mod = 0;
	qerro_mod = 0;
	if (addr_regs_modbus == 0)
		{
	    erro_mod = 1;
		qerro_mod = 2;
		}
	if (bloqueio_gravacao == 67)
		{
	    erro_mod = 1;
		qerro_mod = 2;
		}

	data1_int = addr_regs_modbus;
 	poe_word_buftx();

	data1_int = nro_regs_modbus;
 	poe_word_buftx();

	for (aux_b3 = 0; aux_b3 < nro_regs_modbus; aux_b3++)
		{
 		le_data_mod();								// le dado a ser escrito 
	 	wr_byte_regs_modbus();
		addr_regs_modbus++;
	 	if (erro_mod == 1)
	 		{
	 		break;
		  }
		}
		
	valida_programa();

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


