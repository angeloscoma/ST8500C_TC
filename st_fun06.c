/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_COMU                                                        *
; Funcao: MODULO gerencialde comunicação rs232/485						 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */


void modbus_funcao06(void)
{
	erro_mod = 0;
	qerro_mod = 0;
	le_endereco();
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

	if (erro_mod == 0)
		{
		buf_tx[ptrtx++] = 2;		// monta nro de pontos 
 		le_data_mod();				// le dado a ser escrito 
		wr_byte_regs_modbus();		// escreve dado na e2prom ou na ram
		data1_int = data_modbus;
		if (erro_mod==0)
			{
			poe_word_buftx();             			 				/* poe dado no buffer */
			}
		valida_programa();
		}
		
 	if (erro_mod == 1)
 		{
		buf_tx[1] = buf_tx[1] | 0x80;
		buf_tx[2] = qerro_mod;
		ptrtx = 3;
 		}
//	else
//		{
//		ptrtx =0;
//		buf_tx[ptrtx++] = addr_modbus;
//		buf_tx[ptrtx++] = 6;
//		buf_tx[ptrtx++] = addr_regs_modbus >> 8;
//		buf_tx[ptrtx++] = addr_regs_modbus;
//		buf_tx[ptrtx++] = data1_int >> 8;
//		buf_tx[ptrtx++] = data1_int;
//		}

					
	crc_modbus = crc16(buf_tx, ptrtx, 'M');
	data1_int = crc_modbus;
	poe_word_buftx();
	dispara_tx();
	
	calcula_checksum_vars() ;

}

	 
