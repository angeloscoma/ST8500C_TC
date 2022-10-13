/*;**********************************************************************
; Empresa: SULTECH SISTEMAS ELETRONICOS									*
; Modulo: ST_E2P														*
; Funcao:	MODULO DE E2PROM											*
; 			REGISTRADOR ST9600R											*
; Responsavel: VAGNER SANTOS											*
; Modificado ; VAGNER SANTOS											*
; Inicio: 06/06/2003													*
; Revisao: RENGAV ARIERREF SOD SOTNAS									*
;************************************************************************/

/* rotinas de tratamento da e2prom */

char read_byte(int16 adress)
{
	return (read_eeprom(adress));
}

void write_byte(int16 adress,char dado)
{
	write_eeprom(adress,dado);
}


int16 read_word(int16 adress)
{
	char datah, datal;
	datah = read_eeprom(adress++);
	datal = read_eeprom(adress);
	return (make16(datah, datal));
}

void write_word(int16 adress,int16 dado)
{
	char xw;
	xw = dado >> 8;	
	write_eeprom(adress++, xw);
	xw = dado;
	write_eeprom(adress, xw);
}

void write_long(int16 adress,int32 dado)
{
	write_eeprom(adress++,(dado >> 24));
	write_eeprom(adress++,(dado >> 16));
	write_eeprom(adress++,(dado >> 8));
	write_eeprom(adress,dado);
}

int32 read_long(int16 adress)
{
	char data1, data2, data3, data4;
	data1 = read_eeprom(adress++);
	data2 = read_eeprom(adress++);
	data3 = read_eeprom(adress++);
	data4 = read_eeprom(adress);
	return (make32(data1, data2, data3, data4));
}


// Purpose:    Write one bit to internal eeprom
// Inputs:     1) An eeprom address
//             2) The bit position (LSB == 0)
//             3) The bit to write
// Outputs:    None
void write_bit(word address, char bitPosition, short data)
{
   char stored_data;

   stored_data = read_eeprom(address);

   if(data)
	   	{
    	bit_set(stored_data, bitPosition);
   		}
   else
   		{
      	bit_clear(stored_data, bitPosition);
		}

   write_eeprom(address, stored_data);
}

// Purpose:    Read one bit from internal eeprom
// Inputs:     1) An eeprom address
//             2) The bit position (LSB == 0)
// Outputs:    The bit read from internal eeprom
short read_bit(word address, char bitPosition)
{
   return bit_test(read_eeprom(address), bitPosition);
}



	
