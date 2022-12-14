//	/*
//	Software Driver
//	
//	SST25VF080B 8 Mbit(1M x 8) Serial Flash Memory
//	
//	November 4th, 2005, Rev. 1.0
//	
//	ABOUT THE SOFTWARE
//	This application note provides software driver examples for SST25VF080B,
//	Serial Flash. Extensive comments are included in each routine to describe 
//	the function of each routine.  The interface coding uses polling method 
//	rather than the SPI protocol to interface with these serial devices.  The
//	functions are differentiated below in terms of the communication protocols
//	(uses Mode 0) and specific device operation instructions. This code has been 
//	designed to compile using the Keil compiler.
//	
//	
//	ABOUT THE SST25VF080B
//	
//	Companion product datasheets for the SST25VF080B should be reviewed in 
//	conjunction with this application note for a complete understanding 
//	of the device.
//	
//	
//	Device Communication Protocol(pinout related) functions:
//	
//	Functions                    		Function
//	------------------------------------------------------------------
//	init					Initializes clock to set up mode 0.
//	Send_Byte				Sends one byte using SI pin to send and 
//							shift out 1-bit per clock rising edge
//	Get_Byte				Receives one byte using FLASH_SO pin to receive and shift 
//							in 1-bit per clock falling edge
//	Poll_SO					Used in the polling for RY/BY# of SO during AAI programming
//	CE_High					Sets Chip Enable pin of the serial flash to high
//	CE_Low					Clears Chip Enable of the serial flash to low
//	Hold_Low				Clears Hold pin to make serial flash hold
//	Unhold					Unholds the serial flash
//	WP_Low					Clears WP pin to make serial flash write protected
//	UnWP					Disables write protection pin
//	
//	Note:  The pin names of the SST25VF080B are used in this application note. The associated test code
//	will not compile unless these pinouts (FLASH_CLK, FLASH_SI, FLASH_SO, FLASH_CE, FLASH_WP, FLASH_HOLD) are pre-defined on your
//	software which should reflect your hardware interfaced. 	 
//	
//	
//	Device Operation Instruction functions:
//	
//	Functions                    		Function
//	------------------------------------------------------------------
//	Read_Status_Register	Reads the status register of the serial flash
//	EWSR					Enables the Write Status Register
//	WRSR					Performs a write to the status register
//	WREN					Write enables the serial flash
//	WRDI					Write disables the serial flash
//	EBSY					Enable FLASH_SO to output RY/BY# status during AAI programming
//	DBSY					Disable FLASH_SO to output RY/BY# status during AAI programming
//	Read_ID					Reads the manufacturer ID and device ID
//	Jedec_ID_Read			Reads the Jedec ID
//	Read					Reads one byte from the serial flash and returns byte(max of 25 MHz CLK frequency)
//	Read_Cont				Reads multiple bytes(max of 25 MHz CLK frequency)
//	HighSpeed_Read			Reads one byte from the serial flash and returns byte(max of 50 MHz CLK frequency)
//	HighSpeed_Read_Cont		Reads multiple bytes(max of 50 MHz CLK frequency)
//	Byte_Program			Program one byte to the serial flash
//	Auto_Add_IncA			Initial Auto Address Increment process
//	Auto_Add_IncB			Successive Auto_Address_Increment process after AAI initiation
//	Auto_Add_IncA_EBSY		Initial Auto Address Increment process with EBSY
//	Auto_Add_IncB_EBSY		Successive Auto_Address_Increment process after AAI initiation with EBSY and WRDI/DBSY
//	Chip_Erase				Erases entire serial flash
//	Sector_Erase			Erases one sector (4 KB) of the serial flash
//	Block_Erase_32K			Erases 32 KByte block memory of the serial flash
//	Block_Erase_64K			Erases 64 KByte block memory of the serial flash
//	Wait_Busy				Polls status register until busy bit is low
//	Wait_Busy_AAI			Polls status register until busy bit is low for AAI programming
//	WREN_Check				Checks to see if WEL is set
//	WREN_AAI_Check			Checks to see if WEL and AAI mode is set
//	
//	
//
                                                                     
//"C" LANGUAGE DRIVERS 
*/
/********************************************************************/
/* Copyright Silicon Storage Technology, Inc. (SST), 1994-2005	    */
/* Example "C" language Driver of SST25VF080B Serial Flash			*/
/* Conrado Canio, Silicon Storage Technology, Inc.                  */
/*                                                                  */
/* Revision 1.0, November 4th, 2005			  						*/   
/*                                                                  */
/*																	*/
/********************************************************************/

//#include <stdio.h>
//#include <stdlib.h>

/* Function Prototypes */

void init();
void Send_Byte(unsigned char out);
unsigned char Get_Byte();
void Poll_SO();
void CE_High();
void CE_Low();
void Hold_Low();
void Unhold();
void WP_Low();
void UnWP();
unsigned char Read_Status_Register();
void EWSR();
void WRSR(byte);
void WREN();
void WRDI();
void EBSY();
void DBSY();
unsigned char Read_ID(ID_addr);
unsigned long Jedec_ID_Read(); 
unsigned char Read(unsigned long Dst);
//void Read_Cont(unsigned long Dst, unsigned long no_bytes);
unsigned char HighSpeed_Read(unsigned long Dst); 
void HighSpeed_Read_Cont(unsigned long Dst, unsigned long no_bytes);
void Byte_Program(unsigned long Dst, unsigned char byte);
void Auto_Add_IncA(unsigned long Dst, unsigned char byte1, unsigned char byte2);
void Auto_Add_IncB(unsigned char byte1, unsigned char byte2);
void Auto_Add_IncA_EBSY(unsigned long Dst, unsigned char byte1, unsigned char byte2);
void Auto_Add_IncB_EBSY(unsigned char byte1, unsigned char byte2);
void Chip_Erase();
void Sector_Erase(unsigned long Dst);
void Block_Erase_32K(unsigned long Dst);
void Block_Erase_64K(unsigned long Dst);
void Wait_Busy();
void Wait_Busy_AAI();
void WREN_Check();
void WREN_AAI_Check();

void Verify(unsigned char byte, unsigned char cor_byte);

unsigned char idata upper_128[128];		/* global array to store read data */
										/* to upper RAM area from 80H - FFH */

/********************************************************************************/
/* PROCEDURE: init																*/
/*																				*/
/* This procedure initializes the FLASH_CLK to low. Must be called prior to 	*/
/* setting up mode 0.															*/
/*																				*/
/* Input:																		*/
/*		None																	*/
/*																				*/
/* Output:																		*/
/*		FLASH_CLK																*/
/********************************************************************************/
void init()
{
	output_low FLASH_CLK;	/* set clock to low initial state */
}

/************************************************************************/
/* PROCEDURE: Send_Byte													*/
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
void Send_Byte(unsigned char out)
{
	
	unsigned char i = 0;
	for (i = 0; i < 8; i++)
	{
		
		if ((out & 0x80) == 0x80)			/* check if MSB is high */
			output_high FLASH_SI;
		else
			output_low FLASH_SI;			/* if not, set to low */
		output_high FLASH_CLK;				/* toggle clock high */
		out = (out << 1);					/* shift 1 place for next bit */
		output_low FLASH_CLK;				/* toggle clock low */
	}
}

/************************************************************************/
/* PROCEDURE: Get_Byte													*/
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
unsigned char Get_Byte()
{
	unsigned char i = 0, in = 0, temp = 0;
	for (i = 0; i < 8; i++)
	{
		in = (in << 1);					/* shift 1 place to the left or shift in 0 */
		temp = FLASH_SO;				/* save input */
		output_high FLASH_CLK;			/* toggle clock high */
		if (temp == 1)					/* check to see if bit is high */
			in = in | 0x01;				/* if high, make bit high */

		output_low FLASH_CLK;			/* toggle clock low */

	}
	return in;
}

/********************************************************************************/
/* PROCEDURE: Poll_SO															*/
/*																				*/
/* This procedure polls for the FLASH_SO line during AAI programming  			*/
/* waiting for FLASH_SO to transition to 1 which will indicate AAI programming	*/
/* is completed																	*/
/*																				*/
/* Input:																		*/
/*		FLASH_SO																*/
/*																				*/
/* Output:																		*/
/*		None																	*/
/********************************************************************************/
void Poll_SO()
{
	unsigned char temp = 0;
	CE_Low();
    while (temp == 0x00)	/* waste time until not busy */
		temp = FLASH_SO;
	CE_High();
}

/************************************************************************/
/* PROCEDURE: CE_High													*/
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
void CE_High() 
{
	output_high FLASH_CE;				/* set FLASH_CE high */
}

/************************************************************************/
/* PROCEDURE: CE_Low													*/
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
void CE_Low() 
{	
	output_low FLASH_CE;				/* clear FLASH_CE low */
}

/************************************************************************/
/* PROCEDURE: Hold()													*/
/*																		*/
/* This procedure clears the FLASH_HOLD pin to low.						*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Output:																*/
/*		FLASH_HOLD														*/
/************************************************************************/
void Hold_Low()
{
	output_low FLASH_HOLD;			/* clear FLASH_HOLD pin */
}

/************************************************************************/
/* PROCEDURE: Unhold()													*/
/*																		*/
/* This procedure sets the FLASH_HOLD pin to high.						*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Output:																*/
/*		FLASH_HOLD														*/
/************************************************************************/
void Unhold()
{
	output_high FLASH_HOLD;			/* set FLASH_HOLD pin */
}

/************************************************************************/
/* PROCEDURE: WP()														*/
/*																		*/
/* This procedure clears the FLASH_WP pin to low.						*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Output:																*/
/*		FLASH_WP														*/
/************************************************************************/
void WP_Low()
{
	output_low FLASH_WP;				/* clear WP pin */
}

/************************************************************************/
/* PROCEDURE: UnWP()													*/
/*																		*/
/* This procedure sets the FLASH_WP pin to high.						*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Output:																*/
/*		FLASH_WP														*/
/************************************************************************/
void UnWP()
{
	output_high FLASH_WP;				/* set FLASH_WP pin */
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
	unsigned char byte = 0;
	CE_Low();				/* enable device */
	Send_Byte(0x05);		/* send RDSR command */
	byte = Get_Byte();		/* receive byte */
	CE_High();				/* disable device */
	return byte;
}

/************************************************************************/
/* PROCEDURE: EWSR														*/
/*																		*/
/* This procedure Enables Write Status Register.  						*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void EWSR()
{
	CE_Low();				/* enable device */
	Send_Byte(0x50);		/* enable writing to the status register */
	CE_High();				/* disable device */
}

/************************************************************************/
/* PROCEDURE: WRSR														*/
/*																		*/
/* This procedure writes a byte to the Status Register.					*/
/*																		*/
/* Input:																*/
/*		byte															*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void WRSR(byte)
{
	CE_Low();				/* enable device */
	Send_Byte(0x01);		/* select write to status register */
	Send_Byte(byte);		/* data that will change the status of BPx 
								or BPL (only bits 2,3,4,5,7 can be written) */
	CE_High();				/* disable the device */
}

/************************************************************************/
/* PROCEDURE: WREN														*/
/*																		*/
/* This procedure enables the Write Enable Latch.  It can also be used 	*/
/* to Enables Write Status Register.									*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void WREN()
{
	CE_Low();				/* enable device */
	Send_Byte(0x06);		/* send WREN command */
	CE_High();				/* disable device */
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
	CE_Low();				/* enable device */
	Send_Byte(0x04);		/* send WRDI command */
	CE_High();				/* disable device */
}

/************************************************************************/
/* PROCEDURE: EBSY														*/
/*																		*/
/* This procedure enable FLASH_SO to output RY/BY# status during AAI 	*/
/* programming.															*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void EBSY()
{
	CE_Low();				/* enable device */
	Send_Byte(0x70);		/* send EBSY command */
	CE_High();				/* disable device */
}

/********************************************************************************/
/* PROCEDURE: DBSY																*/
/*																				*/
/* This procedure disable FLASH_SO as output RY/BY# status signal during AAI	*/
/* programming.																	*/
/*																				*/
/* Input:																		*/
/*		None																	*/
/*																				*/
/* Returns:																		*/
/*		Nothing																	*/
/********************************************************************************/
void DBSY()
{
	CE_Low();				/* enable device */
	Send_Byte(0x80);		/* send DBSY command */
	CE_High();				/* disable device */
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
/*		byte:	ID1(Manufacture's ID = BFh or Device ID = 8Eh)			*/
/*																		*/
/************************************************************************/
unsigned char Read_ID(ID_addr)
{
	unsigned char byte;
	CE_Low();				/* enable device */
	Send_Byte(0x90);		/* send read ID command (90h or ABh) */
    Send_Byte(0x00);		/* send address */
	Send_Byte(0x00);		/* send address */
	Send_Byte(ID_addr);		/* send address - either 00H or 01H */
	byte = Get_Byte();		/* receive byte */
	CE_High();				/* disable device */
	return byte;
}

/************************************************************************/
/* PROCEDURE: Jedec_ID_Read												*/
/*																		*/
/* This procedure Reads the manufacturer's ID (BFh), memory type (25h)  */
/* and device ID (8Eh).  It will use 9Fh as the JEDEC ID command.    	*/
/* Please see the product datasheet for details.  						*/
/*																		*/
/* Input:																*/
/*		None															*/
/*																		*/
/* Returns:																*/
/*		IDs_Read:ID1(Manufacture's ID = BFh, Memory Type (25h),			*/
/*		 and Device ID (8Eh)											*/
/*																		*/
/************************************************************************/
unsigned long Jedec_ID_Read() 
{
	unsigned long temp;
	
	temp = 0;

	CE_Low();							/* enable device */
	Send_Byte(0x9F);					/* send JEDEC ID command (9Fh) */
    temp = (temp | Get_Byte()) << 8;	/* receive byte */
	temp = (temp | Get_Byte()) << 8;	
	temp = (temp | Get_Byte()); 		/* temp value = 0xBF258E */
	CE_High();							/* disable device */

	return temp;
}

/************************************************************************/
/* PROCEDURE:	Read													*/
/*																		*/		
/* This procedure reads one address of the device.  It will return the 	*/
/* byte read in variable byte.											*/
/*																		*/
/*																		*/
/*																		*/
/* Input:																*/
/*		Dst:	Destination Address 000000H - 0FFFFFH					*/
/*      																*/
/*																		*/
/* Returns:																*/
/*		byte															*/
/*																		*/
/************************************************************************/
unsigned char Read(unsigned long Dst) 
{
	unsigned char byte = 0;	

	CE_Low();								/* enable device */
	Send_Byte(0x03); 						/* read command */
	Send_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	Send_Byte(((Dst & 0xFFFF) >> 8));
	Send_Byte(Dst & 0xFF);
	byte = Get_Byte();
	CE_High();								/* disable device */
	return byte;							/* return one byte read */
}

/************************************************************************/
/* PROCEDURE:	Read_Cont												*/
/*																		*/		
/* This procedure reads multiple addresses of the device and stores		*/
/* data into 128 byte buffer. Maximum byte that can be read is 128 bytes*/
/*																		*/
/* Input:																*/
/*		Dst:		Destination Address 000000H - 0FFFFFH				*/
/*      no_bytes	Number of bytes to read	(max = 128)					*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/*																		*/
/************************************************************************/
void Read_Cont(unsigned long Dst, unsigned long no_bytes)
{
	unsigned long i = 0;
	CE_Low();					/* enable device */
	Send_Byte(0x03); 			/* read command */
	Send_Byte(((Dst & 0xFFFFFF) >> 16)); 	/* send 3 address bytes */
	Send_Byte(((Dst & 0xFFFF) >> 8));
	Send_Byte(Dst & 0xFF);
	for (i = 0; i < no_bytes; i++)		/* read until no_bytes is reached */
	{
		upper_128[i] = Get_Byte();	/* receive byte and store at address 80H - FFH */
	}
	CE_High();					/* disable device */

}

/************************************************************************/
/* PROCEDURE:	HighSpeed_Read											*/
/*																		*/		
/* This procedure reads one address of the device.  It will return the 	*/
/* byte read in variable byte.											*/
/*																		*/
/*																		*/
/*																		*/
/* Input:																*/
/*		Dst:	Destination Address 000000H - 0FFFFFH					*/
/*      																*/
/*																		*/
/* Returns:																*/
/*		byte															*/
/*																		*/
/************************************************************************/
unsigned char HighSpeed_Read(unsigned long Dst) 
{
	unsigned char byte = 0;	

	CE_Low();				/* enable device */
	Send_Byte(0x0B); 		/* read command */
	Send_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	Send_Byte(((Dst & 0xFFFF) >> 8));
	Send_Byte(Dst & 0xFF);
	Send_Byte(0xFF);		/*dummy byte*/
	byte = Get_Byte();
	CE_High();				/* disable device */
	return byte;			/* return one byte read */
}

/************************************************************************/
/* PROCEDURE:	HighSpeed_Read_Cont										*/
/*																		*/		
/* This procedure reads multiple addresses of the device and stores		*/
/* data into 128 byte buffer. Maximum byte that can be read is 128 bytes*/
/*																		*/
/* Input:																*/
/*		Dst:		Destination Address 000000H - 0FFFFFH				*/
/*      no_bytes	Number of bytes to read	(max = 128)					*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/*																		*/
/************************************************************************/
void HighSpeed_Read_Cont(unsigned long Dst, unsigned long no_bytes)
{
	unsigned long i = 0;
	CE_Low();					/* enable device */
	Send_Byte(0x0B); 			/* read command */
	Send_Byte(((Dst & 0xFFFFFF) >> 16)); 	/* send 3 address bytes */
	Send_Byte(((Dst & 0xFFFF) >> 8));
	Send_Byte(Dst & 0xFF);
	Send_Byte(0xFF);			/*dummy byte*/
	for (i = 0; i < no_bytes; i++)		/* read until no_bytes is reached */
	{
		upper_128[i] = Get_Byte();	/* receive byte and store at address 80H - FFH */
	}
	CE_High();				/* disable device */
}

/************************************************************************/
/* PROCEDURE:	Byte_Program											*/
/*																		*/
/* This procedure programs one address of the device.					*/
/* Assumption:  Address being programmed is already erased and is NOT	*/
/* block protected.														*/
/*																		*/
/*																		*/
/*																		*/
/* Input:																*/
/*		Dst:		Destination Address 000000H - 0FFFFFH				*/
/*		byte:		byte to be programmed								*/
/*      																*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/*																		*/
/************************************************************************/
void Byte_Program(unsigned long Dst, unsigned char byte)
{
	CE_Low();					/* enable device */
	Send_Byte(0x02); 			/* send Byte Program command */
	Send_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	Send_Byte(((Dst & 0xFFFF) >> 8));
	Send_Byte(Dst & 0xFF);
	Send_Byte(byte);			/* send byte to be programmed */
	CE_High();					/* disable device */
}

/****************************************************************************/
/* PROCEDURE:	Auto_Add_IncA												*/
/*																			*/
/* This procedure programs consecutive addresses of 2 bytes of data into	*/
/* the device:  1st data byte will be programmed into the initial 			*/
/* address [A23-A1] and with A0 = 0.  The 2nd data byte will be be 			*/
/* programmed into initial address [A23-A1] and with A0  = 1.  This  		*/
/* is used to to start the AAI process.  It should be followed by 			*/
/* Auto_Add_IncB.															*/
/* Assumption:  Address being programmed is already erased and is NOT		*/
/*				block protected.											*/
/*																			*/
/*																			*/
/* Note: Only RDSR command can be executed once in AAI mode with FLASH_SO  	*/
/* 	 disable to output RY/BY# status.  Use WRDI to exit AAI mode 			*/
/*	 unless AAI is programming the last address or last address of			*/
/* 	 unprotected block, which automatically exits AAI mode.					*/
/*																			*/
/* Input:																	*/
/*		Dst:		Destination Address 000000H - 0FFFFFH					*/
/*		byte1:		1st byte to be programmed								*/
/*      byte1:		2nd byte to be programmed								*/
/*																			*/
/* Returns:																	*/
/*		Nothing																*/
/*																			*/
/****************************************************************************/
void Auto_Add_IncA(unsigned long Dst, unsigned char byte1, unsigned char byte2)
{
	CE_Low();					/* enable device */
	Send_Byte(0xAD);			/* send AAI command */
	Send_Byte(((Dst & 0xFFFFFF) >> 16)); 	/* send 3 address bytes */
	Send_Byte(((Dst & 0xFFFF) >> 8));
	Send_Byte(Dst & 0xFF);
	Send_Byte(byte1);			/* send 1st byte to be programmed */	
	Send_Byte(byte2);			/* send 2nd byte to be programmed */
	CE_High();					/* disable device */
}

/************************************************************************/
/* PROCEDURE:	Auto_Add_IncB											*/
/*																		*/
/* This procedure programs consecutive addresses of 2 bytes of data into*/
/* the device:  1st data byte will be programmed into the initial 		*/
/* address [A23-A1] and with A0 = 0.  The 2nd data byte will be be 		*/
/* programmed into initial address [A23-A1] and with A0  = 1.    This  	*/
/* is used after Auto_Address_IncA.										*/
/* Assumption:  Address being programmed is already erased and is NOT	*/
/*				block protected.										*/
/*																		*/
/* Note: Only WRDI and AAI command can be executed once in AAI mode 	*/
/*	 with FLASH_SO enabled as RY/BY# status.  When the device is busy 	*/
/*	 asserting CE# will output the status of RY/BY# on SO.  Use WRDI	*/
/* 	 to exit AAI mode unless AAI is programming the last address or		*/
/*	 last address of unprotected block, which automatically exits 		*/
/*	 AAI mode.															*/
/*																		*/
/* Input:																*/
/*																		*/
/*		byte1:		1st byte to be programmed							*/
/*		byte2:		2nd byte to be programmed							*/
/*      																*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/*																		*/
/************************************************************************/
void Auto_Add_IncB(unsigned char byte1, unsigned char byte2)
{
	CE_Low();					/* enable device */
	Send_Byte(0xAD);			/* send AAI command */
	Send_Byte(byte1);			/* send 1st byte to be programmed */
	Send_Byte(byte2);			/* send 2nd byte to be programmed */
	CE_High();					/* disable device */
}

/************************************************************************/
/* PROCEDURE:	Auto_Add_IncA_EBSY										*/
/*																		*/
/* This procedure is the same as procedure Auto_Add_IncA except that it */
/* uses EBSY and Poll_SO functions to check for RY/BY. It programs 		*/
/* consecutive addresses of the device.  The 1st data byte will be 		*/
/* programmed into the initial address [A23-A1] and with A0 = 0.  The 	*/
/* 2nd data byte will be programmed into initial address [A23-A1] and 	*/
/* with A0  = 1.  This is used to to start the AAI process.  It should  */
/* be followed by Auto_Add_IncB_EBSY.									*/
/* Assumption:  Address being programmed is already erased and is NOT	*/
/*				block protected.										*/
/*																		*/
/*																		*/
/* Note: Only WRDI and AAI command can be executed once in AAI mode 	*/
/* with FLASH_SO enabled as RY/BY# status.  When the device is busy 	*/
/* asserting CE# will output the status of RY/BY# on FLASH_SO.  Use WRDI*/
/* 	 to exit AAI mode unless AAI is programming the last address or		*/
/*	 last address of unprotected block, which automatically exits 		*/
/*	 AAI mode.															*/
/*																		*/
/* Input:																*/
/*		Dst:		Destination Address 000000H - 0FFFFFH				*/
/*		byte1:		1st byte to be programmed							*/
/*      byte1:		2nd byte to be programmed							*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/*																		*/
/************************************************************************/
void Auto_Add_IncA_EBSY(unsigned long Dst, unsigned char byte1, unsigned char byte2)
{
	EBSY();						/* enable RY/BY# status for FLASH_SO in AAI */	

	CE_Low();					/* enable device */
	Send_Byte(0xAD);			/* send AAI command */
	Send_Byte(((Dst & 0xFFFFFF) >> 16)); 	/* send 3 address bytes */
	Send_Byte(((Dst & 0xFFFF) >> 8));
	Send_Byte(Dst & 0xFF);
	Send_Byte(byte1);			/* send 1st byte to be programmed */	
	Send_Byte(byte2);			/* send 2nd byte to be programmed */
	CE_High();					/* disable device */
	
	Poll_SO();					/* polls RY/BY# using FLASH_SO line */

}

/************************************************************************/
/* PROCEDURE:	Auto_Add_IncB_EBSY										*/
/*																		*/
/* This procedure is the same as Auto_Add_IncB except that it uses 		*/
/* Poll_SO to poll for RY/BY#.  It demonstrate on how to use DBSY after	*/
/* AAI programmming is completed.  It programs consecutive addresses of */
/* the device.  The 1st data byte will be programmed into the initial   */
/* address [A23-A1] and with A0 = 0.  The 2nd data byte will be			*/
/* programmed into initial address [A23-A1] and with A0  = 1.  This is 	*/
/* used after Auto_Address_IncA.										*/
/* Assumption:  Address being programmed is already erased and is NOT	*/
/*				block protected.										*/
/*																		*/
/* Note: Only WRDI and AAI command can be executed once in AAI mode 	*/
/* with SO enabled as RY/BY# status.  When the device is busy, 			*/
/* asserting CE# will output the status of RY/BY# on FLASH_SO.  Use WRDI*/
/* to exit AAI mode unless AAI is programming the last address or		*/
/* last address of unprotected block, which automatically exits 		*/
/* AAI mode.															*/
/*																		*/
/* Input:																*/
/*																		*/
/*		byte1:		1st byte to be programmed							*/
/*		byte2:		2nd byte to be programmed							*/
/*      																*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/*																		*/
/************************************************************************/
void Auto_Add_IncB_EBSY(unsigned char byte1, unsigned char byte2)
{
	CE_Low();				/* enable device */
	Send_Byte(0xAD);		/* send AAI command */
	Send_Byte(byte1);		/* send 1st byte to be programmed */
	Send_Byte(byte2);		/* send 2nd byte to be programmed */
	CE_High();				/* disable device */

	Poll_SO();				/* polls RY/BY# using FLASH_SO line */

	WRDI(); 				/* Exit AAI before executing DBSY */
	DBSY();					/* disable FLASH_SO as RY/BY# output if in AAI */
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
	CE_Low();				/* enable device */
	Send_Byte(0x60);		/* send Chip Erase command (60h or C7h) */
	CE_High();				/* disable device */
}

/************************************************************************/
/* PROCEDURE: Sector_Erase												*/
/*																		*/
/* This procedure Sector Erases the Chip.								*/
/*																		*/
/* Input:																*/
/*		Dst:		Destination Address 000000H - 0FFFFFH				*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void Sector_Erase(unsigned long Dst)
{


	CE_Low();					/* enable device */
	Send_Byte(0x20);			/* send Sector Erase command */
	Send_Byte(((Dst & 0xFFFFFF) >> 16)); 	/* send 3 address bytes */
	Send_Byte(((Dst & 0xFFFF) >> 8));
	Send_Byte(Dst & 0xFF);
	CE_High();					/* disable device */
}	

/************************************************************************/
/* PROCEDURE: Block_Erase_32K											*/
/*																		*/
/* This procedure Block Erases 32 KByte of the Chip.					*/
/*																		*/
/* Input:																*/
/*		Dst:		Destination Address 000000H - 0FFFFFH				*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void Block_Erase_32K(unsigned long Dst)
{
	CE_Low();					/* enable device */
	Send_Byte(0x52);			/* send 32 KByte Block Erase command */
	Send_Byte(((Dst & 0xFFFFFF) >> 16)); 	/* send 3 address bytes */
	Send_Byte(((Dst & 0xFFFF) >> 8));
	Send_Byte(Dst & 0xFF);
	CE_High();					/* disable device */
}

/************************************************************************/
/* PROCEDURE: Block_Erase_64K											*/
/*																		*/
/* This procedure Block Erases 64 KByte of the Chip.					*/
/*																		*/
/* Input:																*/
/*		Dst:		Destination Address 000000H - 0FFFFFH				*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void Block_Erase_64K(unsigned long Dst)
{
	CE_Low();					/* enable device */
	Send_Byte(0xD8);			/* send 64KByte Block Erase command */
	Send_Byte(((Dst & 0xFFFFFF) >> 16)); 	/* send 3 address bytes */
	Send_Byte(((Dst & 0xFFFF) >> 8));
	Send_Byte(Dst & 0xFF);
	CE_High();					/* disable device */
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
	unsigned char byte;
	byte = Read_Status_Register();	/* read the status register */
	if (byte != 0x02)		/* verify that WEL bit is set */
	{
		while(1)
			/* add source code or statements for this file */
			/* to compile   			       */
			/* i.e. option: insert a display to view error on LED? */
		 
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
	unsigned char byte;
	byte = Read_Status_Register();	/* read the status register */
	if (byte != 0x42)		/* verify that AAI and WEL bit is set */
	{
		while(1)		
			/* add source code or statements for this file */
			/* to compile   			       */
			/* i.e. option: insert a display to view error on LED? */

	}
}

/************************************************************************/
/* PROCEDURE: Verify													*/
/*																		*/
/* This procedure checks to see if the correct byte has be read.		*/
/*																		*/
/* Input:																*/
/*		byte:		byte read											*/
/*		cor_byte:	correct_byte that should be read					*/
/*																		*/
/* Returns:																*/
/*		Nothing															*/
/************************************************************************/
void Verify(unsigned char byte, unsigned char cor_byte)
{
	if (byte != cor_byte)
	{
		while(1)
			/* add source code or statement for this file */
			/* to compile   			       */
			/* i.e. option: insert a display to view error on LED? */
		
	}
}


int main()
{

return 0;
}
