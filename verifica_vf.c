/*Software Drivers

SST25VF512 512 Kbit(64K x 8) Serial Flash Memory
SST25VF010 1 Mbit(128K x 8) Serial Flash Memory
SST25VF020 2 Mbit(256K x 8) Serial Flash Memory
SST25VF040 4 Mbit(512K x 8) Serial Flash Memory

April 30th, 2002

ABOUT THE SOFTWARE
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


Device Communication Protocol(pinout related) functions:

Functions                    		Function
------------------------------------------------------------------
init					Initializes clock to set up mode 0.
Send_Byte_Flash			Sends one byte using FLASH_SI pin to send and 
						shift out 1-bit per clock rising edge
Get_Byte_Flash			Receives one byte using FLASH_SO pin to receive and shift 
						in 1-bit per clock falling edge
FLASH_CE_High			Sets Chip Enable pin of the serial flash to high
FLASH_CE_Low			Clears Chip Enable of the serial flash to low
Hold					Clears Hold pin to make serial flash hold
Unhold					Unholds the serial flash
WP						Clears WP pin to make serial flash write protected
UnWP					Disables write protection pin

Note:  The pin names of the 25VFxxx are used in this application note. The associated test code
will not compile unless these pinouts (FLASH_CLK, FLASH_SI, FLASH_SO, FLASH_SO, FLASH_CE, WP, Hold) are pre-defined on your
software which should reflect your hardware interfaced. 	 


Device Operation Instruction functions:

Functions                    		Function
------------------------------------------------------------------
Read_Status_Register	Reads the status register of the serial flash
Flash_EWSR				Enables the Write Status Register
Flash_WRSR				Performs a write to the status register
WREN					Write enables the serial flash
WRDI					Write disables the serial flash
Read_ID					Reads the manufacturer ID and device ID
Read					Reads one byte from the serial flash and returns byte
Read_Cont				Reads multiple bytes
Byte_Program			Program one byte to the serial flash
Auto_Add_IncA			Initial Auto Address Increment process
Auto_Add_IncB			Successive Auto_Address_Increment process after AAI initiation
Chip_Erase				Erases entire serial flash
Sector_Erase			Erases one sector (4 KB) of the serial flash
Block_Erase				Erases one block (32 KB) of the serial flash
Wait_Busy				Polls status register until busy bit is low
Wait_Busy_AAI			Polls status register until busy bit is low for AAI programming
WREN_Check				Checks to see if WEL is set
WREN_AAI_Check			Checks to see if WEL and AAI mode is set



"C" LANGUAGE DRIVERS

/********************************************************************/
/* Copyright Silicon Storage Technology, Inc. (SST), 1994-2002	    */
/* Example "C" language Driver of 25VFXXX Serial Flash		    	*/
/* Aaron Forward, Silicon Storage Technology, Inc.                  */
/*                                                                  */
/* Revision 1.0, April 30th, 2002			  	    				*/   
/*                                                                  */
/********************************************************************/


//#include <stdio.h>
//#include <stdlib.h>


/* Function Prototypes */

void init();
void Send_Byte_Flash(unsigned char out);
unsigned char Get_Byte_Flash();
void FLASH_CE_High();
void FLASH_CE_Low();
void Hold();
void Unhold();
void WP();
void UnWP();
unsigned char Read_Status_Register();
void Flash_EWSR();
void Flash_WRSR(byte);
void WREN();
void WRDI();
unsigned char Read_ID(ID_addr);
unsigned char Read(unsigned long Dst);
void Read_Cont(unsigned long Dst, unsigned long no_bytes);
void Byte_Program(unsigned long Dst, unsigned char aux_b1);
void Auto_Add_IncA(unsigned long Dst, unsigned char aux_b1);
void Auto_Add_IncB(unsigned char aux_b1);
void Chip_Erase();
void Sector_Erase(unsigned long Dst);
void Block_Erase(unsigned long Dst);
void Wait_Busy();
void Wait_Busy_AAI();
void WREN_Check();
void WREN_AAI_Check();


unsigned char upper_128[128];		// global array to store read data 	- idata
										// to upper RAM area from 80H - FFH 

/************************************************************************/
/* PROCEDURE: init														*/
/*																		*/
/* This procedure initializes the FLASH_CLK to low. Must be called  	*/
/* prior to setting up mode 0.											*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Output:																*/
/*		FLASH_CLK														*/
/************************************************************************/
void init()
{
	output_low (FLASH_CLK);	/* set clock to low initial state */
}

/************************************************************************/
/* PROCEDURE: Send_Byte_Flash											*/
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
void Send_Byte_Flash(unsigned char out)
{
	
	unsigned char i = 0;
	for (i = 0; i < 8; i++){
		if ((out & 0x80) == 0x80){		/* check if MSB is high */
			output_high (FLASH_SI);
			}
		else{
			output_low(FLASH_SI);		/* if not, set to low */
			}
		output_high(FLASH_CLK);			/* toggle clock high */
		out = (out << 1);				/* shift 1 place for next bit */
		output_low(FLASH_CLK);			/* toggle clock low */
	}


}

/************************************************************************/
/* PROCEDURE: Get_Byte_Flash											*/
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
unsigned char Get_Byte_Flash()
{
	unsigned char i = 0, in = 0, temp = 0;
	for (i = 0; i < 8; i++){
		in = (in << 1);					/* shift 1 place to the left or shift in 0 */
		temp = FLASH_SO;				/* save input */
		output_high(FLASH_CLK);			/* toggle clock high */
		if (temp == 1){					/* check to see if bit is high */
			in = in | 0x01;				/* if high, make bit high */
			output_low(FLASH_CLK);		/* toggle clock low */
			}
		}
	return in;
}

/************************************************************************/
/* PROCEDURE: FLASH_CE_High												*/
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
	output_high(FLASH_CE);		/* set FLASH_CE high */
}


/************************************************************************/
/* PROCEDURE: FLASH_CE_Low												*/
/*																		*/
/* This procedure drives the FLASH_CE of the device to low.  			*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Output:																*/
/*		FLASH_CE														*/
/************************************************************************/
void FLASH_CE_Low() 
{	
	output_low(FLASH_CE);		/* clear FLASH_CE low */
}



/************************************************************************/
/* PROCEDURE: Hold()													*/
/*																		*/
/* This procedure clears the Hold pin to low.							*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Output:																*/
/*		Hold															*/
/************************************************************************/
void Hold()
{
	output_low(Flash_Hold);		/* clear Hold pin */
}

/************************************************************************/
/* PROCEDURE: Unhold()													*/
/*																		*/
/* This procedure sets the Hold pin to high.							*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Output:																*/
/*		Hold															*/
/************************************************************************/
void Unhold()
{
	output_high(Flash_Hold);	/* set Hold pin */
}

/************************************************************************/
/* PROCEDURE: WP()														*/
/*																		*/
/* This procedure clears the WP pin to low.								*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Output:																*/
/*		WP																*/
/************************************************************************/
void WP()
{
	output_low(Flash_WP);		/* clear WP pin */
}

/************************************************************************/
/* PROCEDURE: UnWP()													*/
/*																		*/
/* This procedure sets the WP pin to high.								*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Output:																*/
/*		WP																*/
/************************************************************************/
void UnWP()
{
	output_high(Flash_WP);		/* set WP pin */
}

/************************************************************************/
/* PROCEDURE: Read_Status_Register										*/
/*																		*/
/* This procedure read the status register and returns the byte.		*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Returns:																*/
/*		byte															*/
/************************************************************************/
unsigned char Read_Status_Register()
{
	unsigned char aux_b1 = 0;
	FLASH_CE_Low();				/* enable device */
	Send_Byte_Flash(0x05);		/* send RDSR command */
	aux_b1 = Get_Byte_Flash();	/* receive byte */
	FLASH_CE_High();			/* disable device */
	return aux_b1;
}

/************************************************************************/
/* PROCEDURE: Flash_EWSR												*/
/*																		*/
/* This procedure Enables Write Status Register.  						*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void Flash_EWSR()
{
	FLASH_CE_Low();				/* enable device */
	Send_Byte_Flash(0x50);		/* enable writing to the status register */
	FLASH_CE_High();			/* disable device */
}

/************************************************************************/
/* PROCEDURE: Flash_WRSR												*/
/*																		*/
/* This procedure writes a byte to the Status Register.					*/
/*																		*/
/* Input:																*/
/*		byte															*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void Flash_WRSR(aux_b1)
{
	FLASH_CE_Low();				/* enable device */
	Send_Byte_Flash(0x01);		/* select write to status register */
	Send_Byte_Flash(aux_b1);		/* data that will change the status of BPx 
								or BPL (only bits 2,3,7 can be written) */
	FLASH_CE_High();			/* disable the device */
}

/************************************************************************/
/* PROCEDURE: WREN														*/
/*																		*/
/* This procedure enables the Write Enable Latch.						*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void WREN()
{
	FLASH_CE_Low();				/* enable device */
	Send_Byte_Flash(0x06);		/* send WREN command */
	FLASH_CE_High();			/* disable device */
}

/************************************************************************/
/* PROCEDURE: WRDI														*/
/*																		*/
/* This procedure disables the Write Enable Latch.						*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void WRDI()
{
	FLASH_CE_Low();				/* enable device */
	Send_Byte_Flash(0x04);		/* send WRDI command */
	FLASH_CE_High();			/* disable device */
}


/************************************************************************/
/* PROCEDURE: Read_ID													*/
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
/*		byte:	ID1														*/
/************************************************************************/
unsigned char Read_ID(ID_addr)
{
	unsigned char aux_b1;
	FLASH_CE_Low();				/* enable device */
	Send_Byte_Flash(0x90);		/* send read ID command (90h or ABh) */
   	Send_Byte_Flash(0x00);		/* send address */
	Send_Byte_Flash(0x00);		/* send address */
	Send_Byte_Flash(ID_addr);	/* send address - either 00H or 01H */
	aux_b1 = Get_Byte_Flash();	/* receive byte */
	FLASH_CE_High();			/* disable device */
	return aux_b1;
}


/************************************************************************/
/* PROCEDURE:	Read													*/
/*																		*/		
/* This procedure reads one address of the device.  It will return the 	*/
/* byte read in variable byte.											*/
/*																		*/
/* Input:																*/
/*		Dst:	Destination Address 000000H - 07FFFFH					*/
/*      																*/
/*																		*/
/* Returns:																*/
/*		byte															*/
/************************************************************************/
unsigned char Read(unsigned long Dst){
	unsigned char aux_b1;
	FLASH_CE_Low();								/* enable device */
	Send_Byte_Flash(0x03); 						/* read command */
	Send_Byte_Flash((Dst & 0xFFFFFF) >> 16);	/* send 3 address bytes */
	Send_Byte_Flash((Dst & 0xFFFF) >> 8);
	Send_Byte_Flash(Dst & 0xFF);
	aux_b1 = Get_Byte_Flash();
	FLASH_CE_High();							/* disable device */
	return aux_b1;								/* return one byte read */
}

/************************************************************************/
/* PROCEDURE:	Read_Cont												*/
/*																		*/		
/* This procedure reads multiple addresses of the device and stores		*/
/* data into 128 byte buffer. Maximum byte that can be read is 128 bytes*/
/*																		*/
/* Input:																*/
/*		Dst:		Destination Address 000000H - 07FFFFH				*/
/*      no_bytes	Number of bytes to read	(max = 128)					*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/*																		*/
/************************************************************************/
void Read_Cont(unsigned long Dst, unsigned long no_bytes)
{
	unsigned long i = 0;
	FLASH_CE_Low();								/* enable device */
	Send_Byte_Flash(0x03); 						/* read command */
	Send_Byte_Flash(((Dst & 0xFFFFFF) >> 16)); 	/* send 3 address bytes */
	Send_Byte_Flash(((Dst & 0xFFFF) >> 8));
	Send_Byte_Flash(Dst & 0xFF);
	for (i = 0; i < no_bytes; i++){				/* read until no_bytes is reached */
		upper_128[i] = Get_Byte_Flash();		/* receive byte and store at address 80H - FFH */
	}
	FLASH_CE_High();							/* disable device */
}



/************************************************************************/
/* PROCEDURE:	Byte_Program											*/
/*																		*/
/* This procedure programs one address of the device.					*/
/* Assumption:  Address being programmed is already erased and is NOT	*/
/* block protected.														*/
/*																		*/
/* Input:																*/
/*		Dst:		Destination Address 000000H - 07FFFFH				*/
/*		byte:		byte to be programmed								*/
/*      																*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void Byte_Program(unsigned long Dst, unsigned char aux_b1)
{
	FLASH_CE_Low();								/* enable device */
	Send_Byte_Flash(0x02); 						/* send Byte Program command */
	Send_Byte_Flash(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	Send_Byte_Flash(((Dst & 0xFFFF) >> 8));
	Send_Byte_Flash(Dst & 0xFF);
	Send_Byte_Flash(aux_b1);						/* send byte to be programmed */
	FLASH_CE_High();							/* disable device */
}

/************************************************************************/
/* PROCEDURE:	Auto_Add_IncA											*/
/*																		*/
/* This procedure programs consecutive addresses of the device.  This  	*/
/* is used to to start the AAI process.  It should be followed by 		*/
/* Auto_Add_IncB.														*/
/* Assumption:  Address being programmed is already erased and is NOT	*/
/*		block protected.												*/
/*																		*/
/* Note: Only RDSR command can be executed once in AAI mode.	 		*/
/* 	 Use WRDI to exit AAI mode unless AAI is programming the last		*/
/*	 address or last address of unprotected block, which 				*/
/*	 automatically exits AAI mode.										*/
/*																		*/
/* Input:																*/
/*		Dst:		Destination Address 000000H - 07FFFFH				*/
/*		byte:		byte to be programmed								*/
/*      																*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void Auto_Add_IncA(unsigned long Dst, unsigned char aux_b1)
{
	FLASH_CE_Low();								/* enable device */
	Send_Byte_Flash(0xAF);						/* send AAI command */
	Send_Byte_Flash(((Dst & 0xFFFFFF) >> 16)); 	/* send 3 address bytes */
	Send_Byte_Flash(((Dst & 0xFFFF) >> 8));
	Send_Byte_Flash(Dst & 0xFF);
	Send_Byte_Flash(aux_b1);						/* send byte to be programmed */
	FLASH_CE_High();								/* disable device */
}

/************************************************************************/
/* PROCEDURE:	Auto_Add_IncB											*/
/*																		*/
/* This procedure programs consecutive addresses of the device.  This  	*/
/* is used after Auto_Address_IncA.										*/
/* Assumption:  Address being programmed is already erased and is NOT	*/
/*		block protected.												*/
/*																		*/
/* Note: Only RDSR command can be executed once in AAI mode.	 		*/
/* 	 Use WRDI to exit AAI mode unless AAI is programming the last		*/
/*	 address or last address of unprotected block, which 				*/
/*	 automatically exits AAI mode.										*/
/*																		*/
/* Input:																*/
/*																		*/
/*		byte:		byte to be programmed								*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void Auto_Add_IncB(unsigned char aux_b1)
{
	FLASH_CE_Low();				/* enable device */
	Send_Byte_Flash(0xAF);		/* send AAI command */
	Send_Byte_Flash(aux_b1);		/* send byte to be programmed */
	FLASH_CE_High();				/* disable device */
}


/************************************************************************/
/* PROCEDURE: Chip_Erase												*/
/*																		*/
/* This procedure erases the entire Chip.								*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void Chip_Erase()
{
	FLASH_CE_Low();				/* enable device */
	Send_Byte_Flash(0x60);		/* send Chip Erase command */
	FLASH_CE_High();				/* disable device */
}

/************************************************************************/
/* PROCEDURE: Sector_Erase												*/
/*																		*/
/* This procedure Sector Erases the Chip.								*/
/*																		*/
/* Input:																*/
/*		Dst:		Destination Address 000000H - 07FFFFH				*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void Sector_Erase(unsigned long Dst)
{
	FLASH_CE_Low();								/* enable device */
	Send_Byte_Flash(0x20);						/* send Sector Erase command */
	Send_Byte_Flash(((Dst & 0xFFFFFF) >> 16)); 	/* send 3 address bytes */
	Send_Byte_Flash(((Dst & 0xFFFF) >> 8));
	Send_Byte_Flash(Dst & 0xFF);
	FLASH_CE_High();								/* disable device */
}

/************************************************************************/
/* PROCEDURE: Block_Erase												*/
/*																		*/
/* This procedure Block Erases the Chip.								*/
/*																		*/
/* Input:																*/
/*		Dst:		Destination Address 000000H - 07FFFFH				*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void Block_Erase(unsigned long Dst)
{
	FLASH_CE_Low();								/* enable device */
	Send_Byte_Flash(0x52);						/* send Block Erase command */
	Send_Byte_Flash(((Dst & 0xFFFFFF) >> 16)); 	/* send 3 address bytes */
	Send_Byte_Flash(((Dst & 0xFFFF) >> 8));
	Send_Byte_Flash(Dst & 0xFF);
	FLASH_CE_High();								/* disable device */
}

/************************************************************************/
/* PROCEDURE: Wait_Busy													*/
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
void Wait_Busy()
{
	while (Read_Status_Register() == 0x03)	/* waste time until not busy */
		Read_Status_Register();
}

/************************************************************************/
/* PROCEDURE: Wait_Busy_AAI												*/
/*																		*/
/* This procedure waits until device is no longer busy for AAI mode.	*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void Wait_Busy_AAI()
{
	while (Read_Status_Register() == 0x43)	/* waste time until not busy */
		Read_Status_Register();
}

/************************************************************************/
/* PROCEDURE: WREN_Check												*/
/*																		*/
/* This procedure checks to see if WEL bit set before program/erase.	*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void WREN_Check()
{
	unsigned char aux_b1;
	aux_b1 = Read_Status_Register();	/* read the status register */
	if (aux_b1 != 0x02){				/* verify that WEL bit is set */
		while(1){
									/* option: insert a display to view error on LED? */
		}
	}
}

/************************************************************************/
/* PROCEDURE: WREN_AAI_Check											*/
/*																		*/
/* This procedure checks for AAI and WEL bit once in AAI mode.			*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void WREN_AAI_Check()
{
	unsigned char aux_b1;
	aux_b1 = Read_Status_Register();	/* read the status register */
	if (aux_b1 != 0x42){				/* verify that AAI and WEL bit is set */
		while(1){
									/* option: insert a display to view error on LED? */
		}
	}
}

