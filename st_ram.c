/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: CP_INTS                                                        *
; Funcao: MODULO Interrupçoes   						 *
; 		Conversor de protocolo MP400 / Modbus/RTU                        *
;		By Sultech For AGST
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 06/06/2003                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/


char le_byte_ram(int16 adress)
{
	char caracter;
	#use fast_io(B)
	#use fast_io(E)
	#use fast_io(G)
	
	output_d(adress++);
	output_low(add1);
	output_high(add1);

	output_d(adress);
	output_low(add0);
	output_high(add0);
	
	output_high(wr);
	output_low(rd);
	output_low(xram);
	caracter = input_d();
	output_high(xram);
	output_high(rd);

	#use standard_io(B)
	#use standard_io(E)
	#use standard_io(G)
	
	return(caracter);

}

int16 le_word_ram(int16 adress)
{
	data1_int = le_byte_ram(adress++);
	data1 = le_byte_ram(adress);
	data1_int = (data1_int << 8 ) | data1;
	return (data1_int);
	
}	

void write_byte_ram(int16 adress, char dado)
{
	#use fast_io(B)
	#use fast_io(E)
	#use fast_io(G)

	output_d(adress++);
	output_low(add1);
	output_high(add1);

	output_d(adress);
	output_low(add0);
	output_high(add0);

	output_high(rd);
	output_low(wr);
	output_low(xram);

	output_d(dado);
	output_high(xram);
	output_high(rd);

	#use standard_io(B)
	#use standard_io(E)
	#use standard_io(G)
	
}
	
void write_word_ram(int16 adress,int16 dado)
{
	char aux_1;
	aux_1 = dado >> 8;	
	write_byte_ram(adress++, aux_1);
	aux_1 = dado;
	write_byte_ram(adress, aux_1);
}

void write_long_ram(int16 adress, int32 dado)
{
	char aux_1;
	aux_1 = dado >> 24;	
	write_byte_ram(adress++, aux_1);
	aux_1 = dado >> 16;	
	write_byte_ram(adress++, aux_1);
	aux_1 = dado >> 8;	
	write_byte_ram(adress++, aux_1);
	aux_1 = dado;
	write_byte_ram(adress, aux_1);
}

int32 le_long_ram(int16 adress)
{
	int32 aux_l1;
	return(aux_l1);
}

