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
int32 write_word_flash(int32 Dst, int16 valor);
void Auto_Add_IncA(int32 Dst, char valor);
void Auto_Add_IncB(int32 Dst, char valor);
void flash_erase(int32 Dst);
void sector_flash_erase(int32 Dst);
void Block_Erase(int32 Dst);
void Wait_Busy(int32 Dst);
void Wait_Busy_AAI(int32 Dst);
void WREN_Check(int32 Dst);
void WREN_AAI_Check(int32 Dst);
void desprotege_flash(int32 Dst);


char byte_flash;
char ID_register_flash;
char status_register_flash;

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
void send_byte_flash(char out)
{
	char i;
	for (i = 0; i < 8; i++)
		{
	   	output_bit(FLASH_SI,shift_left(&out,1,0));
		output_high(FLASH_CLK);				/* toggle clock high */
		output_low(FLASH_CLK);				/* toggle clock low */
		}
}

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
char get_byte_flash(){
	char i;
	char in;
	in = 0;
	for (i = 0; i < 8; i++){
   		shift_left(&in,1,input(FLASH_SO));
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
void FLASH_CE_High(){
	output_high(FLASH_CE);				/* set FLASH_CE high */
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
	setup_spi(SPI_MASTER | SPI_L_TO_H | SPI_CLK_DIV_16);
	output_low(FLASH_CLK);				/* toggle clock low */
	output_low(FLASH_CE);				/* clear FLASH_CE low */
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
char Read_Status_Register(int32 Dst){
	FLASH_CE_Low(Dst);					/* enable device */
	spi_write(0x05);
	setup_spi(SPI_MASTER | SPI_L_TO_H | SPI_CLK_DIV_16);
	status_register_flash = spi_read(0);
	FLASH_CE_High();				/* disable device */
	if ((status_register_flash & 0x0c)!= 0){
		desprotege_flash(Dst);
		FLASH_CE_Low(Dst);					/* enable device */
		spi_write(0x05);
		setup_spi(SPI_MASTER | SPI_L_TO_H | SPI_CLK_DIV_16);
		status_register_flash = spi_read(0);
		FLASH_CE_High();				/* disable device */
	}
	if ((status_register_flash & 0x0c)== 0x0c){
		while(1){
				
		}
	}
	return(status_register_flash);
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
	WREN_Check(Dst);

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
char Read_ID(int32 Dst, char ID_addr)
{
	FLASH_CE_Low(Dst);			/* enable device */

	spi_write(0x90);			// send read ID command (90h or ABh) 
   	spi_write(0x00);			/* send address */
	spi_write(0x00);			/* send address */
	spi_write(ID_addr);			/* send address - either 00H or 01H */
	setup_spi(SPI_MASTER | SPI_L_TO_H | SPI_CLK_DIV_16);
	ID_register_flash = spi_read(0);		/* receive byte */
	FLASH_CE_High();				/* disable device */
	return(ID_register_flash);
}


/************************************************************************/
/* procedure:	read_byte_flash											*/
/*																		*/		
/* This procedure reads one address of the device.  It will return the 	*/
/* byte read in variable valor.											*/
/*																		*/
/*																		*/
/*																		*/
/* Input:			/													*/
/*		Dst:	Destination Address 000000H - 07FFFFH					*/
/*      																*/
/*																		*/
/* Returns:																*/
/*		valor															*/
/*																		*/
/************************************************************************/
char read_byte_flash(int32 Dst) 
{
	FLASH_CE_Low(Dst);								/* enable device */
	spi_write(0x03); 						/* read command */
	spi_write(make8(Dst, 2));	/* send 3 address bytes */
	spi_write(make8(Dst, 1));
	spi_write(make8(Dst, 0));
	setup_spi(SPI_MASTER | SPI_L_TO_H | SPI_CLK_DIV_16);
	byte_flash = spi_read(0);
	FLASH_CE_High();							/* disable device */
	return(byte_flash);								/* return one byte read */
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
int32 write_word_flash(int32 Dst, int16 valor)
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

	spi_write(make8(Dst, 2));	/* send 3 address bytes */
	spi_write(make8(Dst, 1));
	spi_write(make8(Dst, 0));

//	spi_write(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
//	spi_write(((Dst & 0xFFFF) >> 8));
//	spi_write(Dst & 0xFF);

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

	spi_write(make8(Dst, 2));	/* send 3 address bytes */
	spi_write(make8(Dst, 1));
	spi_write(make8(Dst, 0));

//	spi_write(((Dst & 0xFFFFFF) >> 16)); 	/* send 3 address bytes */
//	spi_write(((Dst & 0xFFFF) >> 8));
//	spi_write(Dst & 0xFF);

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


#if (teste_cht_vag == true)
	void printa_status_erase(char qerase, int32 Dst)
		{
		#if (com_485 == true)
			output_high(direcao);
			delay_ms(1);
		#endif	
		printf("Apagando:%u: %u, %u, %lu, ", endereco, qerase, rotina, Dst);
		printf("\r\n");
		#if (com_485 == true)
			delay_ms(2);
			output_low(direcao);
		#endif
		}
#endif	


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
	#if (teste_cht_vag == true)
		printa_status_erase(0, Dst);
	#endif	
	
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

	spi_write(make8(Dst, 2));	/* send 3 address bytes */
	spi_write(make8(Dst, 1));
	spi_write(make8(Dst, 0));

//	spi_write(((Dst & 0xFFFFFF) >> 16)); 	/* send 3 address bytes */
//	spi_write(((Dst & 0xFFFF) >> 8));
//	spi_write(Dst & 0xFF);

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

	spi_write(make8(Dst, 2));	/* send 3 address bytes */
	spi_write(make8(Dst, 1));
	spi_write(make8(Dst, 0));

//	spi_write(((Dst & 0xFFFFFF) >> 16)); 	/* send 3 address bytes */
//	spi_write(((Dst & 0xFFFF) >> 8));
//	spi_write(Dst & 0xFF);

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
		
	while ((Read_Status_Register(Dst) & 0x01) == 0x01)	/* waste time until not busy */
		{
		delay_us(10);
		Read_Status_Register(Dst);
		}
		
}


	
//	char aux;
//#if feira
//	return;
//#endif	
//  time_out = 2;
//	aux = Read_Status_Register(Dst) & 0x01;
////	aux = Read_Status_Register(Dst) & 0x03;
//	while (aux == 0x01)	/* waste time until not busy */
////	while (aux == 0x03)	/* waste time until not busy */
//		{
////		aux = Read_Status_Register(Dst) & 0x03;
//		aux = Read_Status_Register(Dst) & 0x01;
//		if (time_out == 0)
//			{
//			break;
//			}
//		}
//
//
//void Wait_Busy()
//{
//while ((Read_Status_Register() & 0x03) == 0x03)
//Read_Status_Register(); /* waste time until not busy */
//}

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
	status_register_flash = Read_Status_Register(Dst);
	while(1)		/* verify that WEL bit is set */
		{		
		status_register_flash = Read_Status_Register(Dst);
		if ((status_register_flash & 0x02) != 0x02)
			{
			FLASH_CE_Low(Dst);				/* enable device */
			spi_write(0x06);		/* send WREN command */
			FLASH_CE_High();			/* disable device */
			}
		else
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
char AAI_check_flash;
void WREN_AAI_Check(int32 Dst)
{
	AAI_check_flash = Read_Status_Register(Dst);	/* read the status register */
	if (AAI_check_flash != 0x42)				/* verify that AAI and WEL bit is set */
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

void exibe_erro_memoria(char mem, char status){
exibe_erro_memoria_de_novo:
	while(true){
		status = read_ID(0, 1);
		if (status == 0x44){			// verifica se memoria está na placa
			break;
		}
		else{
			delay_ms(1000);
			goto exibe_erro_memoria_de_novo;
		}
	}
}

void Le_Hardware(void){
	//1)identifica que e quantas memorias existem
	//informa no display a configuracao do hardware
	desprotege_flash(0);
	if (read_ID(0, 1) == 0x44){			// verifica se memoria 1 está na placa
		desprotege_flash(0);
	}
	else{
		exibe_erro_memoria(1, read_ID(0, 1));
	}
}
