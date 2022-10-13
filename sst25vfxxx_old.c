/*
software Drivers

SST25VF512 512 Kbit(64K x 8) Serial Flash Memory
SST25VF010 1 Mbit(128K x 8) Serial Flash Memory
SST25VF020 2 Mbit(256K x 8) Serial Flash Memory
SST25VF040 4 Mbit(512K x 8) Serial Flash Memory

April 30th, 2002

ABOUT THE softWARE
This application note provides software driver examples for 25VFxxx,
Serial Flash. Extensive comments are included in each routine to describe 
the function of each routine.  The interface coding uses polling method 
rather than the SPI protocol to interface with these serial devices.  The
functions are differentiated below in terms of the communication protocols
(uses Mode 0) and specific device operation instructions. This code has been 
designed to compile using the Keil compiler.


ABOUT THE 25VFxxx

Companion product datasheets for the 25VFxxx should be reviewed in 
conjunction with this application note for a complete understanding 
of the device.


device Communication Protocol(pinout related) functions:

Functions                    		Function
------------------------------------------------------------------
init					Initializes clock to set up mode 0.
send_byte_flash			Sends one byte using FLASH_SI pin to send and 
						shift out 1-bit per clock rising edge
get_byte_flash			receives one byte using FLASH_SO pin to receive and shift 
						in 1-bit per clock falling edge
FLASH_CE_High			Sets Chip Enable pin of the serial flash to high
FLASH_CE_Low			Clears Chip Enable of the serial flash to low
Hold					Clears Hold pin to make serial flash hold
Unhold					Unholds the serial flash

Note:  The pin names of the 25VFxxx are used in this application note. The associated test code
will not compile unless these pinouts (FLASH_CLK, FLASH_SI, FLASH_SO, FLASH_SO, FLASH_CE,  Hold) are pre-defined on your
software which should reflect your hardware interfaced. 	 


device Operation Instruction functions:

Functions                    		Function
------------------------------------------------------------------
Read_Status_Register	Reads the status register of the serial flash
EWSR					Enables the Write Status Register
WRSR					Performs a write to the status register
WREN					Write enables the serial flash
WRDI					Write disables the serial flash
Read_ID					Reads the manufacturer ID and device ID
read_byte_flash				Reads one byte from the serial flash and returns byte
Read_Cont				Reads multiple bytes
write_byte_flash		Program one byte to the serial flash
Auto_Add_IncA			Initial Auto Address Increment process
Auto_Add_IncB			Successive Auto_Address_Increment process after AAI initiation
flash_erase				Erases entire serial flash
sector_flash_erase		Erases one sector (4 KB) of the serial flash
Block_Erase				Erases one block (32 KB) of the serial flash
Wait_Busy				Polls status register until busy bit is low
Wait_Busy_AAI			Polls status register until busy bit is low for AAI programming
WREN_Check				Checks to see if WEL is set
WREN_AAI_Check			Checks to see if WEL and AAI mode is set



"C" LANGUAGE DRIVERS
*/
/********************************************************************/
/* Copyright FLASH_SIlicon Storage Technology, Inc. (SST), 1994-2002*/
/* Example "C" language Driver of 25VFXXX Serial Flash		    	*/
/* Aaron Forward, FLASH_SIlicon Storage Technology, Inc.            */
/*                                                                  */
/* ReviFLASH_SIon 1.0, April 30th, 2002			     				*/   
/*                                                                  */
/*								    								*/
/********************************************************************/

//#include <stdio.h>
//#include <stdlib.h>


/* Function Prototypes */

void init();
void send_byte_flash(char out);
char get_byte_flash();
void FLASH_CE_High();
void FLASH_CE_Low(int32 Dst);
void Hold();
void Unhold();
char Read_Status_Register(int32 Dst);
void EWSR(int32 Dst);
void WRSR(int32 Dst ,char valor);
void WREN(int32 Dst);
void WRDI(int32 Dst);
char Read_ID(int32 Dst, char ID_addr);
char read_byte_flash(int32 Dst);
//void Read_Cont(int32 Dst, char no_bytes);
void write_byte_flash(int32 Dst, char valor);
int32 write_word_flash(int32 Dst, word valor);
void Auto_Add_IncA(int32 Dst, char valor);
void Auto_Add_IncB(int32 Dst, char valor);
void flash_erase(int32 Dst);
void sector_flash_erase(int32 Dst);
void Block_Erase(int32 Dst);
void Wait_Busy(int32 Dst);
void Wait_Busy_AAI(int32 Dst);
void WREN_Check(int32 Dst);
void WREN_AAI_Check(int32 Dst);


/************************************************************************/
/* procedure: init														*/
/*																		*/
/* This procedure initializes the FLASH_CLK to low. Must be called prior to 	*/
/* setting up mode 0.													*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Output:																*/
/*		FLASH_CLK														*/
/************************************************************************/
void init()
{
	output_low(FLASH_CLK);	/* set clock to low initial state */
}

/************************************************************************/
/* procedure: send_byte_flash											*/
/*																		*/
/* This procedure outputs a byte shifting out 1-bit per clock rising	*/
/* edge on the the FLASH_SI pin(LSB 1st).								*/
/*																		*/
/* Input:																*/
/*		out																*/
/*																		*/
/* Output:																*/
/*		FLASH_SI														*/
/************************************************************************/
//char spi_write_ext(char out)
//void send_byte_flash(char out)
//{
//	char i;
//	for (i = 0; i < 8; i++)
//		{
//	   	output_bit(FLASH_SO,shift_left(&out,1,0));
//		output_high(FLASH_CLK);				/* toggle clock high */
//		output_low(FLASH_CLK);				/* toggle clock low */
//		}
//	return(0);
//	
//}

/************************************************************************/
/* procedure: get_byte_flash											*/
/*																		*/
/* This procedure inputs a byte shifting in 1-bit per clock falling		*/
/* edge on the FLASH_SO pin(LSB 1st).									*/
/*																		*/
/* Input:																*/
/*		FLASH_SO														*/
/*																		*/
/* Output:																*/
/*		None															*/
/************************************************************************/
char spi_read_ext(char x)
//char get_byte_flash()
{
	char i;
	char in;
	in = 0;
	for (i = 0; i < 8; i++)
		{
   		shift_left(&in,1,input(FLASH_SI));
		output_high(FLASH_CLK);		/* toggle clock high */
		output_low(FLASH_CLK);		/* toggle clock low */
		}
	return(in);
}

/************************************************************************/
/* procedure: FLASH_CE_High												*/
/*																		*/
/* This procedure set FLASH_CE = High.									*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Output:																*/
/*		FLASH_CE														*/
/*																		*/
/************************************************************************/
void FLASH_CE_High() 
{
	#if (st5x == true)
		#if (cpu_rev1011 == true)
			spi_ocupada = false;
		#endif
	#endif
	
	output_high(FLASH1_CE);				/* set FLASH_CE high */
	#if (portatil == true)
		output_high(FLASH2_CE);				/* set FLASH_CE high */
		output_high(FLASH3_CE);				/* set FLASH_CE high */
		output_high(FLASH4_CE);				/* set FLASH_CE high */
	#endif
	//			 76543210
	setup_spi(0);
	
}


/************************************************************************/
/* procedure: FLASH_CE_Low												*/
/*																		*/
/* This procedure drives the FLASH_CE of the device to low.  			*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Output:																*/
/*		FLASH_CE														*/
/*																		*/
/************************************************************************/

void FLASH_CE_Low(int32 Dst) 
{	
	#if (st5x == true)
		#if (cpu_rev1011 == true)
			spi_ocupada = true;
		#endif
	#endif
	
	setup_spi(SPI_MASTER | SPI_H_TO_L | SPI_CLK_DIV_64);

	output_low(FLASH_CLK);				/* toggle clock low */

	output_high(FLASH1_CE);				/* clear FLASH_CE high */
	#if (portatil == true)
		output_high(FLASH2_CE);				/* clear FLASH_CE high */
		output_high(FLASH3_CE);				/* clear FLASH_CE high */
		output_high(FLASH4_CE);				/* clear FLASH_CE high */
	#endif
	if (Dst < BANCO_1)
		{
		output_low(FLASH1_CE);				/* clear FLASH_CE low */
		}
	#if (portatil == true)
		else if (Dst < BANCO_2)
			{
			output_low(FLASH2_CE);				/* clear FLASH_CE low */
			}
		else if (Dst < BANCO_3)
			{
			output_low(FLASH3_CE);				/* clear FLASH_CE low */
			}
		else
			{
			output_low(FLASH4_CE);				/* clear FLASH_CE low */
			}
	#endif
	
}


/************************************************************************/
/* procedure: Hold()													*/
/*																		*/
/* This procedure clears the Hold pin to low.							*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Output:																*/
/*		FLASH_HOLD														*/
/************************************************************************/
void Hold()
{
	output_low(FLASH_HOLD);			/* clear Hold pin */
}

/************************************************************************/
/* procedure: Unhold()													*/
/*																		*/
/* This procedure sets the Hold pin to high.							*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Output:																*/
/*		FLASH_HOLD														*/
/************************************************************************/
void Unhold()
{
	output_high(FLASH_HOLD);			/* set Hold pin */
}



/************************************************************************/
/* procedure: Read_Status_Register										*/
/*																		*/
/* This procedure read the status register and returns the byte.		*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Returns:																*/
/*		valor															*/
/************************************************************************/
char Read_Status_Register(int32 Dst)
{
	char valor;
	FLASH_CE_Low(Dst);					/* enable device */
	spi_write(0x05);
	setup_spi(SPI_MASTER | SPI_L_TO_H | SPI_CLK_DIV_64);
	valor = spi_read(0);
	FLASH_CE_High();				/* disable device */
	return(valor);
}

/************************************************************************/
/* procedure: EWSR														*/
/*																		*/
/* This procedure Enables Write Status Register.		  				*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void EWSR(int32 Dst)
{
	FLASH_CE_Low(Dst);				/* enable device */
	spi_write(0x50);
	FLASH_CE_High();			/* disable device */
}

/************************************************************************/
/* procedure: WRSR														*/
/*																		*/
/* This procedure writes a byte to the Status Register.					*/
/*																		*/
/* Input:																*/
/*		valor															*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void WRSR(int32 Dst, char valor)
{
	FLASH_CE_Low(Dst);				/* enable device */
	spi_write(0x01);				/* select write to status register */
	spi_write(valor);				/* data that will change the status of BPx */
									/*or BPL (only bits 2,3,7 can be written) */
	FLASH_CE_High();				/* disable the device */
}

/************************************************************************/
/* procedure: WREN														*/
/*																		*/
/* This procedure enables the Write Enable Latch.						*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void WREN(int32 Dst)
{
	FLASH_CE_Low(Dst);				/* enable device */
	spi_write(0x06);		/* send WREN command */
	FLASH_CE_High();			/* disable device */
}

/************************************************************************/
/* procedure: WRDI														*/
/*																		*/
/* This procedure disables the Write Enable Latch.						*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void WRDI(int32 Dst)
{
	FLASH_CE_Low(Dst);				/* enable device */
	spi_write(0x04);		/* send WRDI command */
	FLASH_CE_High();			/* disable device */
}


/************************************************************************/
/* procedure: Read_ID													*/
/*																		*/
/* This procedure Reads the manufacturer's ID and device ID.  It will 	*/
/* use 90h or ABh as the command to read the ID (90h in this sample).   */
/* It is up to the user to give the last byte ID_addr to determine      */
/* whether the device outputs manufacturer's ID first, or device ID 	*/
/* first.  Please see the product datasheet for details.  Returns ID in */
/* variable byte.														*/
/*																		*/
/* Input:																*/
/*		ID_addr															*/
/*																		*/
/* Returns:																*/
/*		valor:	ID1														*/
/*																		*/
/************************************************************************/
char valor_id;
char Read_ID(int32 Dst, char ID_addr)
{
	char valor;
	FLASH_CE_Low(Dst);					/* enable device */
	spi_write(0x90);			/* send read ID command (90h or ABh) */
   	spi_write(0x00);			/* send address */
	spi_write(0x00);			/* send address */
	spi_write(ID_addr);		/* send address - either 00H or 01H */
	setup_spi(SPI_MASTER | SPI_L_TO_H | SPI_CLK_DIV_64);
	valor = spi_read(0);		/* receive byte */
	valor_id = valor;
	FLASH_CE_High();				/* disable device */

	#if (__DEVICE__ == 6722)
	 	fprintf(modbus,"\r\nID da SST:%u\r\n", valor);
	#endif
	
	return(valor);
}


/************************************************************************/
/* procedure:	read_byte_flash											*/
/*																		*/		
/* This procedure reads one address of the device.  It will return the 	*/
/* byte read in variable valor.											*/
/*																		*/
/*																		*/
/*																		*/
/* Input:																*/
/*		Dst:	Destination Address 000000H - 07FFFFH					*/
/*      																*/
/*																		*/
/* Returns:																*/
/*		valor															*/
/*																		*/
/************************************************************************/
char read_byte_flash(int32 Dst) 
{
	char valor;	

	FLASH_CE_Low(Dst);				/* enable device */
	spi_write(0x03); 				/* write to read command */
	spi_write(make8(Dst, 2));	/* send 3 address bytes */
	spi_write(make8(Dst, 1));
	spi_write(make8(Dst, 0));
	setup_spi(SPI_MASTER | SPI_L_TO_H | SPI_CLK_DIV_64);
	valor = spi_read(0);
	FLASH_CE_High();				/* disable device */
	return(valor);					/* return one byte read */
}

/************************************************************************/
/* procedure:	Read_Cont												*/
/*																		*/		
/* This procedure reads multiple addresses of the device and stores		*/
/* data into 128 byte buffer. Maximum byte that can be read is 128 bytes*/
/*																		*/
/* Input:																*/
/*		Dst:		Destination Address 000000H - 07FFFFH				*/
/*      	no_bytes	Number of bytes to read	(max = 128)				*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/*																		*/
/************************************************************************/
//void Read_Cont(int32 Dst, char no_bytes)
//{
//	char i;
//	FLASH_CE_Low();								/* enable device */
//	send_byte_flash(0x03); 						/* read command */
//	send_byte_flash(((Dst & 0xFFFFFF) >> 16)); 	/* send 3 address bytes */
//	send_byte_flash(((Dst & 0xFFFF) >> 8));
//	send_byte_flash(Dst & 0xFF);
//	for (i = 0; i < no_bytes; i++)				/* read until no_bytes is reached */
//		{
//		buf_dados[i] = get_byte_flash();		/* receive byte and store at address 80H - FFH */
//		}
//	FLASH_CE_High();							/* disable device */
//}




/************************************************************************/
/* procedure:	write_word_flash										*/
/*																		*/
/* This procedure programs one address of the device.					*/
/* Assumption:  Address being programmed is already erased and is NOT	*/
/*		block protected.												*/
/*																		*/
/* Input:																*/
/*		Dst:		Destination Address 000000H - 07FFFFH				*/
/*		valor:		word to be programmed								*/
/*      																*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/*																		*/
/************************************************************************/
int32 write_word_flash(int32 Dst, word valor)
{
	write_byte_flash(Dst++, (char)((valor >> 8)));
	write_byte_flash(Dst++, (char)(valor));
	return(Dst);
}

/************************************************************************/
/* procedure:	write_byte_flash										*/
/*																		*/
/* This procedure programs one address of the device.					*/
/* Assumption:  Address being programmed is already erased and is NOT	*/
/*		block protected.												*/
/*																		*/
/*																		*/
/*																		*/
/* Input:																*/
/*		Dst:		Destination Address 000000H - 07FFFFH				*/
/*		valor:		byte to be programmed								*/
/*      																*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/*																		*/
/************************************************************************/
void write_byte_flash(int32 Dst, char valor)
{
	WREN(Dst);
	FLASH_CE_Low(Dst);								/* enable device */
	spi_write(0x02); 						/* send Byte Program command */
	spi_write(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	spi_write(((Dst & 0xFFFF) >> 8));
	spi_write(Dst & 0xFF);
	spi_write(valor);						/* send byte to be programmed */
	FLASH_CE_High();							/* disable device */
	Wait_Busy(Dst);
}

/************************************************************************/
/* procedure:	Auto_Add_IncA											*/
/*																		*/
/* This procedure programs consecutive addresses of the device.This		*/
/* is used to to start the AAI process.  It should be followed by 		*/
/* Auto_Add_IncB.														*/
/* Assumption:  Address being programmed is already erased and is NOT	*/
/*		block protected.												*/
/*																		*/
/*																		*/
/* Note: Only RDSR command can be executed onFLASH_CE in AAI mode.	 	*/
/* 	 Use WRDI to exit AAI mode unless AAI is programming the last		*/
/*	 address or last address of unprotected block, which 				*/
/*	 automatically exits AAI mode.										*/
/*																		*/
/* Input:																*/
/*		Dst:		Destination Address 000000H - 07FFFFH				*/
/*		valor:		byte to be programmed								*/
/*      																*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/*																		*/
/************************************************************************/
void Auto_Add_IncA(int32 Dst, char valor)
{
	WREN(Dst);
	FLASH_CE_Low(Dst);								/* enable device */
	spi_write(0xAF);						/* send AAI command */
	spi_write(((Dst & 0xFFFFFF) >> 16)); 	/* send 3 address bytes */
	spi_write(((Dst & 0xFFFF) >> 8));
	spi_write(Dst & 0xFF);
	spi_write(valor);						/* send byte to be programmed */
	FLASH_CE_High();							/* disable device */
	Wait_Busy(Dst);
}

/************************************************************************/
/* procedure:	Auto_Add_IncB											*/
/*																		*/
/* This procedure programs consecutive addresses of the device.This		*/
/* is used after Auto_Address_IncA.										*/
/* Assumption:  Address being programmed is already erased and is NOT	*/
/*		block protected.												*/
/*																		*/
/* Note: Only RDSR command can be executed onFLASH_CE in AAI mode.	 	*/
/* 	 Use WRDI to exit AAI mode unless AAI is programming the last		*/
/*	 address or last address of unprotected block, which 				*/
/*	 automatically exits AAI mode.										*/
/*																		*/
/* Input:																*/
/*																		*/
/*		valor:		byte to be programmed								*/
/*      																*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/*																		*/
/************************************************************************/
void Auto_Add_IncB(int32 Dst, char valor)
{
	FLASH_CE_Low(Dst);					/* enable device */
	spi_write(0xAF);			/* send AAI command */
	spi_write(valor);			/* send byte to be programmed */
	FLASH_CE_High();				/* disable device */
	Wait_Busy(Dst);
}


/************************************************************************/
/* procedure: flash_erase												*/
/*																		*/
/* This procedure erases the entire Chip.								*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void flash_erase(int32 Dst)
{
	WREN(Dst);
	FLASH_CE_Low(Dst);					/* enable device */
	spi_write(0x60);					/* send Chip Erase command */
	FLASH_CE_High();					/* disable device */
	Wait_Busy(Dst);
}

/************************************************************************/
/* procedure: sector_flash_erase										*/
/*																		*/
/* This procedure Sector Erases the Chip.								*/
/*																		*/
/* Input:																*/
/*		Dst:		Destination Address 000000H - 07FFFFH				*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void sector_flash_erase(int32 Dst)
{
	WREN(Dst);
	FLASH_CE_Low(Dst);								/* enable device */
	spi_write(0x20);						/* send Sector Erase command */
	spi_write(((Dst & 0xFFFFFF) >> 16)); 	/* send 3 address bytes */
	spi_write(((Dst & 0xFFFF) >> 8));
	spi_write(Dst & 0xFF);
	FLASH_CE_High();							/* disable device */
	Wait_Busy(Dst);
}

/************************************************************************/
/* procedure: Block_Erase												*/
/*																		*/
/* This procedure Block Erases the Chip.								*/
/*																		*/
/* Input:																*/
/*		Dst:		Destination Address 000000H - 07FFFFH				*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void Block_Erase(int32 Dst)
{
	WREN(Dst);
	FLASH_CE_Low(Dst);								/* enable device */
	spi_write(0x52);						/* send Block Erase command */
	spi_write(((Dst & 0xFFFFFF) >> 16)); 	/* send 3 address bytes */
	spi_write(((Dst & 0xFFFF) >> 8));
	spi_write(Dst & 0xFF);
	FLASH_CE_High();							/* disable device */
	Wait_Busy(Dst);
}

/************************************************************************/
/* procedure: Wait_Busy													*/
/*																		*/
/* This procedure waits until device is no longer busy (can be used by	*/
/* Byte-Program, Sector-Erase, Block-Erase, Chip-Erase).				*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void Wait_Busy(int32 Dst)
{
	char aux;
#if feira
	return;
#endif	
    time_out = 2;
	aux = Read_Status_Register(Dst) & 0x01;
	while (aux == 0x01)	/* waste time until not busy */
		{
		aux = Read_Status_Register(Dst) & 0x01;
		if (time_out == 0)
			{
			break;
			}
		}
}

/************************************************************************/
/* procedure: Wait_Busy_AAI												*/
/*																		*/
/* This procedure waits until device is no longer busy for AAI mode.	*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void Wait_Busy_AAI(int32 Dst)
{
#if feira
	return;
#endif	
	while ((Read_Status_Register(Dst) & 0x43) == 0x43)	/* waste time until not busy */
		{
		Read_Status_Register(Dst);
		}
}

/************************************************************************/
/* procedure: WREN_Check												*/
/*																		*/
/* This procedure checks to see if WEL bit set before program/erase.	*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void WREN_Check(int32 Dst)
{
	char valor;
	valor = Read_Status_Register(Dst);			/* read the status register */
	if (valor != 0x02)						/* verify that WEL bit is set */
		{
		while(1)
							/* option: insert a display to view error on LED? */
			{
			break;
			}
		}
}

/************************************************************************/
/* procedure: WREN_AAI_Check											*/
/*																		*/
/* This procedure checks for AAI and WEL bit onFLASH_CE in AAI mode.	*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void WREN_AAI_Check(int32 Dst)
{
	char valor;
	valor = Read_Status_Register(Dst);	/* read the status register */
	if (valor != 0x42)				/* verify that AAI and WEL bit is set */
		{
		while(1)		
									/* option: insert a display to view error on LED? */
			{
			break;
			}
		}
}

/************************************************************************/
/* procedure: DESPROTEGE_FLASH()										*/
/*																		*/
/* Esta funcao desprotege todos os bancos da flash.						*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void desprotege_flash(int32 Dst)
{
	EWSR(Dst);			// habilita escrita no status register
	WRSR(Dst, 2);		// escreve zero no status register, desprotegendo a flash	
}



#if (com_display == true)
	void exibe_erro_memoria(char mem)
		{
exibe_erro_memoria_de_novo:			
		#if (disp_7seg == true)
		#elif (st8610c == true)
		#elif (st8620c == true)
			mensagem(1,129);
		#elif (st8600c == true)
			mensagem(1,129);
		#else
			mensagem(1,107);
			displayp(10,mem,1,0,0);
		#endif
		#if (__DEVICE__ == 6722)
			while(true)
				{
				if (read_ID(BANCO_0, 1) == 0x44)			// verifica se memoria 1 está na placa
					{
					break;
					}
				else
					{
					delay_ms(1000);
					goto exibe_erro_memoria_de_novo;
					}
				}
		#else
			#if (portatil == true)
				while(true)
					{
					if (mem == 1)
						{
						if (read_ID(BANCO_0, 1) == 0x44)			// verifica se memoria 1 está na placa
							{
							break;
							}
						else
							{
							delay_ms(1000);
							goto exibe_erro_memoria_de_novo;
							}
						}
					else if (mem == 2)
						{
						if (read_ID(BANCO_1, 1) == 0x44)			// verifica se memoria 1 está na placa
							{
							break;
							}
						else
							{
							delay_ms(1000);
							goto exibe_erro_memoria_de_novo;
							}
						}
					else if (mem == 3)
						{
						if (read_ID(BANCO_2, 1) == 0x44)			// verifica se memoria 1 está na placa
							{
							break;
							}
						else
							{
							delay_ms(1000);
							goto exibe_erro_memoria_de_novo;
							}
						}
					else if (mem == 4)
						{
						if (read_ID(BANCO_3, 1) == 0x44)			// verifica se memoria 1 está na placa
							{
							break;
							}
						else
							{
							delay_ms(1000);
							goto exibe_erro_memoria_de_novo;
							}
						}
						
					}
			#else
				while(true)
					{
					if (read_ID(BANCO_0, 1) == 0x44)			// verifica se memoria 1 está na placa
						{
						break;
						}
					else
						{
						delay_ms(1000);
						goto exibe_erro_memoria_de_novo;
						}
					}
			#endif
		#endif
		}
#else
	void exibe_erro_memoria(char mem)
		{
			
		}
#endif


void le_hardware(void)
{
	#if feira
		return;
	#endif
	//1)identifica que e quantas memorias existem
	//informa no display a configuracao do hardware
		
	desprotege_flash(BANCO_0);

	if (read_ID(BANCO_0, 1) == 0x44)			// verifica se memoria 1 está na placa
		{
		desprotege_flash(BANCO_0);
		}
	else
		{
		exibe_erro_memoria(1);
		}
	#if (portatil == true)
		if (read_ID(BANCO_1, 1) == 0x44)		// verifica se memoria 2 está na placa
			{
			desprotege_flash(BANCO_1);
			}
		else
			{
			exibe_erro_memoria(2);
			}
		if (read_ID(BANCO_2, 1) == 0x44)		// verifica se memoria 3 está na placa
			{
			desprotege_flash(BANCO_2);
			}
		else
			{
			exibe_erro_memoria(3);
			}
		if (read_ID(BANCO_3, 1) == 0x44)		// verifica se memoria 4 está na placa
			{
			desprotege_flash(BANCO_3);
			}
		else
			{
			exibe_erro_memoria(4);
			}
	#endif
}
