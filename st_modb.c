/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRONICOS                                  *
; Modulo: ST_COMU                                                        *
; Funcao: MODULO gerencialde comunicacao rs232/485						 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */
  
#include <st_func.c>
#include <st_crc.c>
#include <st_fun01.c>
#include <st_fun03.c>
#include <st_fun04.c>
#include <st_fun05.c>
#include <st_fun06.c>
#include <st_fun17.c>
#include <st_fun16.c>
#if (protocolo_abb == true)
	#include <st_fun67.c>
#endif


void le_slave_addresss(void)
{
	addr_modbus = 255;
	if (retrx != ptrrx)
		{
		addr_modbus = ret_ser();
		}
}

void le_function(void)
{
	funcao_modbus=0;
	if (retrx!=ptrrx)
		{
		funcao_modbus = ret_ser();
		}
}



void trata_modbus(void)
{

	if (retrx == ptrrx)
		{
		return;
		}
	
	if (time_out_modbus == 0)
		{
		if (numbrx == 0)
			{
			return;
			}
		}
	else
		{
		return;
		}
	
	#if (protocolo_abb == true)
		#if (teste_protocolo_abb == true)
			tensao_r = 127 * 64;
			corrente_r = 250 * 8;
			pot_ativa_r = (127 * 200 * 32) / 1000;
			pot_reativa_r = (127 * 100 * 32) / 1000;
			pot_aparente_r = (127 * 250 * 32) / 1000;
			aux_l1 = pot_ativa_r;
			aux_l1 = aux_l1 * 1024;
			fator_pot_r = aux_l1 / pot_aparente_r;
			tensao_rs = 127 * 1.73 * 64;
			#if (monofasico == false)
				tensao_s = 128 * 64;
				tensao_t = 129 * 64;
				corrente_s = 101 * 8;
				corrente_t = 102 * 8;
				
				pot_ativa_s = (128 * 100 * 32) / 1000;
				pot_reativa_s = (128 * 10 * 32) / 1000;
				pot_aparente_s = (128 * 110 * 32) / 1000;
				aux_l1 = pot_ativa_s;
				aux_l1 = aux_l1 * 1024;
				fator_pot_s = aux_l1 / pot_aparente_s;

				pot_ativa_t = (129 * 100 * 32) / 1000;
				pot_reativa_t = (129 * 10 * 32) / 1000;
				pot_aparente_t = (129 * 110 * 32) / 1000;
				aux_l1 = pot_ativa_t;
				aux_l1 = aux_l1 * 1024;
				fator_pot_t = aux_l1 / pot_aparente_t;

				tensao_st = 128 * 1.73 * 64;
				tensao_rt = 129 * 1.73 * 64;

				
			#endif
			#if com_consumo == true)
				consumo_ati++;
				consumo_reati++;
			#endif
			
		#endif
	#endif
	
//	disable_interrupts(INT_RDA);

	le_slave_addresss();
//
#if (portatil == TRUE)
	{
	if (addr_modbus != 187)
		{
		endereco = addr_modbus;
		}
	}
#elif (st_prog == true)
	{
	if (addr_modbus != 187)
		{
		endereco = addr_modbus;
		}
	#if (simula_rep == true)
		endereco = 247;
	#endif		
	
	}
#else
	{
	//  SOMENTE DURANTE OS TESTES DE BANCADA 
	//		
	#if (st5x == true)
		#if (endereco_padrao == true)
			endereco = 187;	
		#else
			#if (TECNOFLUX == TRUE)
				endereco = 100 + endereco_nro_serie;
			#else
				#if (endereco_via_serial == true)
					dip_addr = 1;
					endereco = 1;
				#else
					endereco = dip_addr;	
				#endif
			#endif
		#endif
	#endif
	}
#endif
//		
	#if (st5x == true)
		#if (endereco_padrao == false)			// implementado a partir de 19/11/07 - vagner
			if (addr_modbus == 0)
				{
				addr_modbus = endereco;
				}
		#endif
	#else
		if (addr_modbus == 0)
			{
			addr_modbus = endereco;
			}
	#endif
		
		aux_b1 = buf_rx[0];
		aux_b2 = buf_rx[1];
		aux_b3 = buf_rx[2];
		aux_b4 = buf_rx[3];
		aux_b1 = buf_rx[4];
		aux_b2 = buf_rx[5];
		aux_b3 = buf_rx[6];
		aux_b4 = buf_rx[7];
		aux_b1 = buf_rx[8];
		aux_b2 = buf_rx[9];
		aux_b3 = buf_rx[10];
		aux_b4 = buf_rx[11];
//[001,003,000,001,000,003,084,011,]		
		
	if (addr_modbus == endereco)
		{
		crc_modbus =  crc16(buf_rx, (numbrx - 2), 'M');
		data1_int = buf_rx[numbrx-2];
		data1_int = data1_int << 8;
		data1 = buf_rx[numbrx-1];
		data1_int = data1_int | data1;
		/* ************************************ */								
		/* nao testa check s check = 0xffff */
		#if (portatil == TRUE)
			//		data1_int = crc_modbus;
		#endif
		if (data1_int == 0xffff)
			{
			data1_int = crc_modbus;
			}
/* ************************************ */
		if (data1_int == crc_modbus)
			{
			ptrtx =0;
			buf_tx[ptrtx++] = addr_modbus;		/* monta resposta com endereco */
			le_function();
			buf_tx[ptrtx++] = funcao_modbus;		/* monta resposta com funcao */
			switch(funcao_modbus)
				{
	            case 1:
       		    	{
					modbus_funcao01();
					break;
					}
           		case 3:
           			{
					modbus_funcao03();
					break;
					}
           		case 4:
           			{
					modbus_funcao04();
					break;
					}
				#if (st5x == true)
					#if (padrao_referencia == false)
						 case 5:
							{
							modbus_funcao05();
							break;
							}
						case 6:
							{
							modbus_funcao06();
							break;
							}
						case 16:
						{
						modbus_funcao16();
						break;
						}
					#endif
				#else
					 case 5:
						{
						modbus_funcao05();
						break;
						}
					case 6:
						{
						modbus_funcao06();
						break;
						}     
					case 16:
						{
						modbus_funcao16();
						break;
						}
				#endif
				case 17:
					{
					modbus_funcao17();
					break;
					}
				#if (protocolo_abb == true)
					case 67:
						{
						modbus_funcao67();
						break;
						}
					case 66:
						{
						modbus_funcao66();
						break;
						}
				#endif
				default:
					{
					buf_tx[1] = buf_tx[1] | 0x80;
					buf_tx[2] = 1;
					ptrtx = 3;
					crc_modbus =  crc16(buf_tx, ptrtx, 'M');
					data1_int = crc_modbus;
					poe_word_buftx();   	
					dispara_tx();
					}
				}
			}
		else
			{
/* INCLUIR TRATAMENTO DE ERRO DE CHECKSUM */
			inic_rx();
			}
		}
	else
		{
		inic_rx();			// Se o endereço não é o mesmo.
		}
		
}






