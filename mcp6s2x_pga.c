
//Driver file for Microchip 6s281/2/6/8 channel PGA amplifiers 
//Devices can operate in mode 0,0  and mode 1,1 this driver file is for mode 0,0 
//Date 9-12-04 
//Refer to the data sheet for more information and Microchips AN248 application note 
//Instruction register must be accessed first to select either the Gain register or the channel select register 
//data is sent as a 16 bit word 

// Definitions 
//Gain 
#define gain1 0b0100000000000000   	// Gain of 1 
#define gain2 0b0100000000000001   	// Gain of 2 
#define gain4 0b0100000000000010   	// Gain of 4 
#define gain5 0b0100000000000011    // Gain of 5 
#define gain8 0b0100000000000100    // Gain of 8 
#define gain10 0b0100000000000101   // Gain of 10 
#define gain16 0b0100000000000110   // Gain of 16 
#define gain32 0b0100000000000111   // Gain of 32 
//Channels 
#define channel0 0b0100000100000000 // channel 0 
//#define channel1 0b0100000100000001 // channel 1 
//#define channel2 0b0100000100000010 // channel 2 
//#define channel3 0b0100000100000011 // channel 3 
//#define channel4 0b0100000100000100 // channel 4 
//#define channel5 0b0100000100000101 // channel 5 
//#define channel6 0b0100000100000110 // channel 6 
//#define channel7 0b0100000100000111 // channel 7   //don't need these if using only the 6s281 single channel 

//Data format is as follows the first byte in the word (0b01000000<--register select bit) this is automatically 
//sent to the pga instruction register 
//0b01000000 =gain register select / 0b01000001 =channel register select", 
// 
//the second half of the word is then automatically re-directed to either the channel select 
//or gain select register 
//=================================================== 
// definitions for "instructions" 
//#define PrgGain 0b01000000 // instruction for gain register 
//#define PrgChannel 0b01000001 // instruction for channel register 
//#define PrgShdn 0b00100000 // instruction to shutdown PGA 

//Select your own pins for the interface 

//=================================================== 
//These PGA's require a 16 bit word as stated above 

void pga_gain_set(int16 gain_data, char canal) 
{ 
	int8 data_count; 
	output_bit(PGA_SCLK,0);   //make sure clock is idling low set this up in intialisation routine as well 
	if (canal == 4)
		{
		output_bit(CS_PGA4,0);   // select PGA set high in initialisation routine! 
		}
	else if (canal == 3)
		{
		output_bit(CS_PGA3,0);   // select PGA set high in initialisation routine! 
		}
	else if (canal == 2)
		{
		output_bit(CS_PGA2,0);   // select PGA set high in initialisation routine! 
		}
	else
		{
		output_bit(CS_PGA1,0);   // select PGA set high in initialisation routine! 
		}
	delay_us(1); 
	for(data_count=0;data_count<16;data_count++) 
		{ 
		output_bit(PGA_DO,shift_left(&gain_data,2,0)); 
		output_bit(PGA_SCLK,1);    //clk in the data 
		delay_us(1); 
		output_bit(PGA_SCLK,0); 
		} 
	output_bit(PGA_SCLK,0);   //make sure clock is idling low 
	if (canal == 4)
		{
		output_bit(CS_PGA4,1);   // deselect PGA at this ponit this will implement the changes 
		}
	else if (canal == 3)
		{
		output_bit(CS_PGA3,1);   // deselect PGA at this ponit this will implement the changes 
		}
	else if (canal == 2)
		{
		output_bit(CS_PGA2,1);   // deselect PGA at this ponit this will implement the changes 
		}
	else
		{
		output_bit(CS_PGA1,1);   // deselect PGA at this ponit this will implement the changes 
		}
	
                  // in either channel selection or gain selection 
}       

//copy of above for channel selection 
void pga_chan_set(int16 chan_data, char canal) 
{ 
	int8 data_count; 
	output_bit(PGA_SCLK,0);   //make sure clock is idling low set this up in intialisation routine as well 
	if (canal == 4)
		{
		output_bit(CS_PGA4,0);   // select PGA set high in initialisation routine! 
		}
	else if (canal == 3)
		{
		output_bit(CS_PGA3,0);   // select PGA set high in initialisation routine! 
		}
	else if (canal == 2)
		{
		output_bit(CS_PGA2,0);   // select PGA set high in initialisation routine! 
		}
	else
		{
		output_bit(CS_PGA1,0);   // select PGA set high in initialisation routine! 
		}
	delay_us(1); 
	for(data_count=0;data_count<16;data_count++) 
		{ 
		output_bit(PGA_DO,shift_left(&chan_data,2,0)); 
		output_bit(PGA_SCLK,1);    //clk in the data 
		delay_us(1); 
		output_bit(PGA_SCLK,0); 
		} 
	output_bit(PGA_SCLK,0);   //make sure clock is idling low 
	if (canal == 4)
		{
		output_bit(CS_PGA4,1);   // deselect PGA at this ponit this will implement the changes 
		}
	else if (canal == 3)
		{
		output_bit(CS_PGA3,1);   // deselect PGA at this ponit this will implement the changes 
		}
	else if (canal == 2)
		{
		output_bit(CS_PGA2,1);   // deselect PGA at this ponit this will implement the changes 
		}
	else
		{
		output_bit(CS_PGA1,1);   // deselect PGA at this ponit this will implement the changes 
                  // in either channel selection or gain selection 
        }
}       
