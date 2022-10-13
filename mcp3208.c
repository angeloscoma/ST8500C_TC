/*////////////////// Driver for MCP3208 A/D Converter ////////////////////////
////																	////
////  adc_init()                                Call after power up		////
////																	////
////  value = read_analog_mcp( canal, mode )	Read an analog canal	////
////											0 through 7 and select	////
////											differential (0) or		////
////											single (1) mode			////
////																	////
////  value = read_analog( canal )			Read an analog canal		////
////											0 through 7 in	single	////
////									mode							////
////																	////
////																	////
////////////////////////////////////////////////////////////////////////////
////        (C) Copyright 1996,1997 Custom Computer Services            ////
//// This source code may only be used by licensed users of the CCS C   ////
//// compiler.  This source code may only be distributed to other       ////
//// licensed users of the CCS C compiler.  No other use, reproduction  ////
//// or distribution is permitted without written permission.           ////
//// Derivative programs created using this software in object code     ////
//// form are not restricted in any way.                                ////
////////////////////////////////////////////////////////////////////////////
*/

#define canal_0 0b00000000
#define canal_1 0b00100000
#define canal_2 0b01000000
#define canal_3 0b01100000
#define canal_4 0b10000000
#define canal_5 0b10100000
#define canal_6 0b11000000
#define canal_7 0b11100000
//				  ||||| -- D0
//				  ||||---- D1
//				  |||----- D2
//				  ||------ Single/Diff
//				  |------- Start


void write_adc_byte(char data_byte) 
{
// 1   	
   	output_low(MCP3208_CLK);
	output_high(MCP3208_DIN);
   	output_high(MCP3208_CLK);
// 2   	
   	output_low(MCP3208_CLK);
	output_high(MCP3208_DIN);
   	output_high(MCP3208_CLK);
// 3   	
   	output_low(MCP3208_CLK);
   	output_bit(MCP3208_DIN,shift_left(&data_byte,1,0));
   	output_high(MCP3208_CLK);
// 4   	
   	output_low(MCP3208_CLK);
   	output_bit(MCP3208_DIN,shift_left(&data_byte,1,0));
   	output_high(MCP3208_CLK);
// 5   	
   	output_low(MCP3208_CLK);
   	output_bit(MCP3208_DIN,shift_left(&data_byte,1,0));
   	output_high(MCP3208_CLK);
// 6   	
   	output_low(MCP3208_CLK);
	output_low(MCP3208_DIN);
   	output_high(MCP3208_CLK);
// 7   	
   	output_low(MCP3208_CLK);
	output_low(MCP3208_DIN);
   	output_high(MCP3208_CLK);
   	output_low(MCP3208_CLK);
   		
}

/*
      output_low(MCP3208_CLK);
      if((data_byte & 1)==0)
			output_low(MCP3208_DIN);
      else
			output_high(MCP3208_DIN);
      data_byte=data_byte>>1;
      delay_us(50);
      output_high(MCP3208_CLK);
      delay_us(50);
*/


long int le_canal_0_teste(void)
{
// chip select	
   	output_low(MCP3208_DIN);
   	output_low(MCP3208_CLK);
   	output_low(MCP3208_CS);
  	
// escreve comando de selecao de canal e start
// 1   	
	output_high(MCP3208_DIN);
   	output_high(MCP3208_CLK);
   	delay_cycles(2);
// 2   	
   	output_low(MCP3208_CLK);
   	delay_cycles(2);
   	output_high(MCP3208_CLK);
   	delay_cycles(2);
// 3   	canal
   	output_low(MCP3208_CLK);
	output_low(MCP3208_DIN);
   	output_high(MCP3208_CLK);
   	delay_cycles(2);
// 4   	canal
   	output_low(MCP3208_CLK);
   	delay_cycles(2);
   	output_high(MCP3208_CLK);
// 5   	canal
   	output_low(MCP3208_CLK);
   	delay_cycles(2);
   	output_high(MCP3208_CLK);
   	delay_cycles(2);
// 6   	
   	output_low(MCP3208_CLK);
   	delay_cycles(2);
   	output_high(MCP3208_CLK);
   	delay_cycles(2);
// 7   	
   	output_low(MCP3208_CLK);
   	delay_cycles(2);
   	output_high(MCP3208_CLK);
   	delay_cycles(2);
   	output_low(MCP3208_CLK);
	
//	return(read_mcp());
	return(0);

}

long int le_canal_0(void)
{
// chip select	
   	output_low(MCP3208_DIN);
   	output_low(MCP3208_CLK);
   	output_low(MCP3208_CS);
//   	delay_cycles(2);
  	
// escreve comando de selecao de canal e start
// 1   	
	output_high(MCP3208_DIN);
   	output_high(MCP3208_CLK);
// 2   	
   	output_low(MCP3208_CLK);
   	output_high(MCP3208_CLK);
// 3   	canal
   	output_low(MCP3208_CLK);
	output_low(MCP3208_DIN);
   	output_high(MCP3208_CLK);
// 4   	canal
   	output_low(MCP3208_CLK);
   	output_high(MCP3208_CLK);
// 5   	canal
   	output_low(MCP3208_CLK);
   	output_high(MCP3208_CLK);
// 6   	
   	output_low(MCP3208_CLK);
   	output_high(MCP3208_CLK);
// 7   	
   	output_low(MCP3208_CLK);
   	output_high(MCP3208_CLK);
   	output_low(MCP3208_CLK);
	
	return(read_mcp());

}

long int le_canal_1(void)
{
// chip select	
   	output_low(MCP3208_DIN);
   	output_low(MCP3208_CLK);
   	output_low(MCP3208_CS);
  	
// escreve comando de selecao de canal e start
// 1   	
	output_high(MCP3208_DIN);
   	output_high(MCP3208_CLK);
// 2   	
   	output_low(MCP3208_CLK);
   	output_high(MCP3208_CLK);
// 3   	canal
   	output_low(MCP3208_CLK);
	output_low(MCP3208_DIN);
   	output_high(MCP3208_CLK);
// 4   	canal
   	output_low(MCP3208_CLK);
   	output_high(MCP3208_CLK);
// 5   	canal
   	output_low(MCP3208_CLK);
	output_high(MCP3208_DIN);
   	output_high(MCP3208_CLK);
// 6   	
   	output_low(MCP3208_CLK);
	output_low(MCP3208_DIN);
   	output_high(MCP3208_CLK);
// 7   	
   	output_low(MCP3208_CLK);
   	output_high(MCP3208_CLK);
   	output_low(MCP3208_CLK);
	
	return(read_mcp());

}

long int le_canal_2(void)
{
// chip select	
   	output_low(MCP3208_DIN);
   	output_low(MCP3208_CLK);
   	output_low(MCP3208_CS);
  	
// escreve comando de selecao de canal e start
// 1   	
	output_high(MCP3208_DIN);
   	output_high(MCP3208_CLK);
// 2   	
   	output_low(MCP3208_CLK);
   	output_high(MCP3208_CLK);
// 3   	canal
   	output_low(MCP3208_CLK);
	output_low(MCP3208_DIN);
   	output_high(MCP3208_CLK);
// 4   	canal
   	output_low(MCP3208_CLK);
	output_high(MCP3208_DIN);
   	output_high(MCP3208_CLK);
// 5   	canal
   	output_low(MCP3208_CLK);
	output_low(MCP3208_DIN);
   	output_high(MCP3208_CLK);
// 6   	
   	output_low(MCP3208_CLK);
   	output_high(MCP3208_CLK);
// 7   	
   	output_low(MCP3208_CLK);
   	output_high(MCP3208_CLK);
   	output_low(MCP3208_CLK);
	
	return(read_mcp());

}

long int le_canal_3(void)
{
// chip select	
   	output_low(MCP3208_DIN);
   	output_low(MCP3208_CLK);
   	output_low(MCP3208_CS);
  	
// escreve comando de selecao de canal e start
// 1   	
	output_high(MCP3208_DIN);
   	output_high(MCP3208_CLK);
// 2   	
   	output_low(MCP3208_CLK);
   	output_high(MCP3208_CLK);
// 3   	canal
   	output_low(MCP3208_CLK);
	output_low(MCP3208_DIN);
   	output_high(MCP3208_CLK);
// 4   	canal
   	output_low(MCP3208_CLK);
	output_high(MCP3208_DIN);
   	output_high(MCP3208_CLK);
// 5   	canal
   	output_low(MCP3208_CLK);
	output_high(MCP3208_DIN);
   	output_high(MCP3208_CLK);
// 6   	
   	output_low(MCP3208_CLK);
	output_low(MCP3208_DIN);
   	output_high(MCP3208_CLK);
// 7   	
   	output_low(MCP3208_CLK);
   	output_high(MCP3208_CLK);
   	output_low(MCP3208_CLK);
	
	return(read_mcp());

}

long int le_canal_4(void)
{
// chip select	
   	output_low(MCP3208_DIN);
   	output_low(MCP3208_CLK);
   	output_low(MCP3208_CS);
  	
// escreve comando de selecao de canal e start
// 1   	
	output_high(MCP3208_DIN);
   	output_high(MCP3208_CLK);
// 2   	
   	output_low(MCP3208_CLK);
   	output_high(MCP3208_CLK);
// 3   	canal
   	output_low(MCP3208_CLK);
	output_high(MCP3208_DIN);
   	output_high(MCP3208_CLK);
// 4   	canal
   	output_low(MCP3208_CLK);
	output_low(MCP3208_DIN);
   	output_high(MCP3208_CLK);
// 5   	canal
//   	delay_cycles(1);					// em 19/05/06
   	output_low(MCP3208_CLK);
//   	delay_cycles(1);					// em 19/05/06
   	output_high(MCP3208_CLK);
//   	delay_cycles(1);					// em 19/05/06
// 6   	
   	output_low(MCP3208_CLK);
//   	delay_cycles(1);					// em 19/05/06
   	output_high(MCP3208_CLK);
//   	delay_cycles(1);					// em 19/05/06
// 7   	
   	output_low(MCP3208_CLK);
//   	delay_cycles(1);					// em 19/05/06
   	output_high(MCP3208_CLK);
//   	delay_cycles(1);					// em 19/05/06
   	output_low(MCP3208_CLK);
	
	return(read_mcp());
}

long int le_canal_5(void)
{
// chip select	
   	output_low(MCP3208_DIN);
   	output_low(MCP3208_CLK);
   	output_low(MCP3208_CS);
  	
// escreve comando de selecao de canal e start
// 1   	
	output_high(MCP3208_DIN);
   	output_high(MCP3208_CLK);
// 2   	
   	output_low(MCP3208_CLK);
   	output_high(MCP3208_CLK);
// 3   	canal
   	output_low(MCP3208_CLK);
	output_high(MCP3208_DIN);
   	output_high(MCP3208_CLK);
// 4   	canal
   	output_low(MCP3208_CLK);
	output_low(MCP3208_DIN);
   	output_high(MCP3208_CLK);
// 5   	canal
   	output_low(MCP3208_CLK);
	output_high(MCP3208_DIN);
   	output_high(MCP3208_CLK);
// 6   	
   	output_low(MCP3208_CLK);
	output_low(MCP3208_DIN);
   	output_high(MCP3208_CLK);
// 7   	
   	output_low(MCP3208_CLK);
   	output_high(MCP3208_CLK);
   	output_low(MCP3208_CLK);
	
	return(read_mcp());

}

long int le_canal_6(void)
{
// chip select	
   	output_low(MCP3208_DIN);
   	output_low(MCP3208_CLK);
   	output_low(MCP3208_CS);
  	
// escreve comando de selecao de canal e start
// 1   	
	output_high(MCP3208_DIN);
   	output_high(MCP3208_CLK);
// 2   	
   	output_low(MCP3208_CLK);
   	output_high(MCP3208_CLK);
// 3   	canal
   	output_low(MCP3208_CLK);
	output_high(MCP3208_DIN);
   	output_high(MCP3208_CLK);
// 4   	canal
   	output_low(MCP3208_CLK);
	output_high(MCP3208_DIN);
   	output_high(MCP3208_CLK);
// 5   	canal
   	output_low(MCP3208_CLK);
	output_low(MCP3208_DIN);
   	output_high(MCP3208_CLK);
// 6   	
   	output_low(MCP3208_CLK);
   	output_high(MCP3208_CLK);
// 7   	
   	output_low(MCP3208_CLK);
   	output_high(MCP3208_CLK);
   	output_low(MCP3208_CLK);
	
	return(read_mcp());

}

long int le_canal_7(void)
{
// chip select	
   	output_low(MCP3208_DIN);
   	output_low(MCP3208_CLK);
   	output_low(MCP3208_CS);
  	
// escreve comando de selecao de canal e start
// 1   	
	output_high(MCP3208_DIN);
   	output_high(MCP3208_CLK);
// 2   	
   	output_low(MCP3208_CLK);
   	output_high(MCP3208_CLK);
// 3   	canal
   	output_low(MCP3208_CLK);
	output_high(MCP3208_DIN);
   	output_high(MCP3208_CLK);
// 4   	canal
   	output_low(MCP3208_CLK);
	output_high(MCP3208_DIN);
   	output_high(MCP3208_CLK);
// 5   	canal
   	output_low(MCP3208_CLK);
	output_high(MCP3208_DIN);
   	output_high(MCP3208_CLK);
// 6   	
   	output_low(MCP3208_CLK);
	output_low(MCP3208_DIN);
   	output_high(MCP3208_CLK);
// 7   	
   	output_low(MCP3208_CLK);
   	output_high(MCP3208_CLK);
   	output_low(MCP3208_CLK);
	
	return(read_mcp());

}


long int read_mcp_old(void) 
{
   	char adl;
   	char adh;

   	adh = 0;
   	adl = 0;
// 11   	
   	output_high(MCP3208_CLK);
   	delay_cycles(1);
   	shift_left(&adh,1,input(MCP3208_DOUT));
   	output_low(MCP3208_CLK);
// 10  	
   	output_high(MCP3208_CLK);
   	delay_cycles(1);
   	shift_left(&adh,1,input(MCP3208_DOUT));
   	output_low(MCP3208_CLK);
// 9  	
   	output_high(MCP3208_CLK);
   	delay_cycles(1);
   	shift_left(&adh,1,input(MCP3208_DOUT));
   	output_low(MCP3208_CLK);
// 8  	
   	output_high(MCP3208_CLK);
   	delay_cycles(1);
   	shift_left(&adh,1,input(MCP3208_DOUT));
   	output_low(MCP3208_CLK);
// 7
   	output_high(MCP3208_CLK);
   	delay_cycles(1);
   	shift_left(&adl,1,input(MCP3208_DOUT));
   	output_low(MCP3208_CLK);
// 6
   	output_high(MCP3208_CLK);
   	delay_cycles(1);
   	shift_left(&adl,1,input(MCP3208_DOUT));
   	output_low(MCP3208_CLK);
// 5
   	output_high(MCP3208_CLK);
   	delay_cycles(1);
   	shift_left(&adl,1,input(MCP3208_DOUT));
   	output_low(MCP3208_CLK);
// 4
   	output_high(MCP3208_CLK);
   	delay_cycles(1);
   	shift_left(&adl,1,input(MCP3208_DOUT));
   	output_low(MCP3208_CLK);
// 3
   	output_high(MCP3208_CLK);
   	delay_cycles(1);
   	shift_left(&adl,1,input(MCP3208_DOUT));
   	output_low(MCP3208_CLK);
// 2
   	output_high(MCP3208_CLK);
   	delay_cycles(1);
   	shift_left(&adl,1,input(MCP3208_DOUT));
   	output_low(MCP3208_CLK);
// 1
   	output_high(MCP3208_CLK);
   	delay_cycles(1);
   	shift_left(&adl,1,input(MCP3208_DOUT));
   	output_low(MCP3208_CLK);
// 0
   	output_high(MCP3208_CLK);
   	delay_cycles(1);
   	shift_left(&adl,1,input(MCP3208_DOUT));
   	output_low(MCP3208_CLK);

   	output_high(MCP3208_CS);

   	return(make16(adh,adl));

}


long int read_mcp(void) 
{
   	char adl;
   	char adh;

   	adh = 0;
   	adl = 0;
// 11   	
   	output_high(MCP3208_CLK);
   	shift_left(&adh,1,input(MCP3208_DOUT));
   	output_low(MCP3208_CLK);
//   	delay_cycles(1);
// 10  	
   	output_high(MCP3208_CLK);
   	shift_left(&adh,1,input(MCP3208_DOUT));
   	output_low(MCP3208_CLK);
//   	delay_cycles(1);
// 9  	
   	output_high(MCP3208_CLK);
   	shift_left(&adh,1,input(MCP3208_DOUT));
   	output_low(MCP3208_CLK);
//   	delay_cycles(1);
// 8  	
   	output_high(MCP3208_CLK);
   	shift_left(&adh,1,input(MCP3208_DOUT));
   	output_low(MCP3208_CLK);
//   	delay_cycles(1);
// 7
   	output_high(MCP3208_CLK);
   	shift_left(&adl,1,input(MCP3208_DOUT));
   	output_low(MCP3208_CLK);
//   	delay_cycles(1);
// 6
   	output_high(MCP3208_CLK);
   	shift_left(&adl,1,input(MCP3208_DOUT));
   	output_low(MCP3208_CLK);
//   	delay_cycles(1);
// 5
   	output_high(MCP3208_CLK);
   	shift_left(&adl,1,input(MCP3208_DOUT));
   	output_low(MCP3208_CLK);
//   	delay_cycles(1);
// 4
   	output_high(MCP3208_CLK);
   	shift_left(&adl,1,input(MCP3208_DOUT));
   	output_low(MCP3208_CLK);
//   	delay_cycles(1);
// 3
   	output_high(MCP3208_CLK);
   	shift_left(&adl,1,input(MCP3208_DOUT));
   	output_low(MCP3208_CLK);
//   	delay_cycles(1);
// 2
   	output_high(MCP3208_CLK);
   	shift_left(&adl,1,input(MCP3208_DOUT));
   	output_low(MCP3208_CLK);
//   	delay_cycles(1);
// 1
   	output_high(MCP3208_CLK);
   	shift_left(&adl,1,input(MCP3208_DOUT));
   	output_low(MCP3208_CLK);
//   	delay_cycles(1);
// 0
   	output_high(MCP3208_CLK);
   	shift_left(&adl,1,input(MCP3208_DOUT));
   	output_low(MCP3208_CLK);

   	output_high(MCP3208_CS);

   	return(make16(adh,adl));

}

long int read_analog_mcp(BYTE canal) 
{
   	char adl;
   	int16 adh;

	#if (feira == 1)
	   	output_high(MCP3208_CS);
		return(0);
	#endif

   	adh = 0;
   	adl = 0;

   	output_low(MCP3208_DIN);
   	output_low(MCP3208_CLK);
   	output_low(MCP3208_CS);
   	
// escreve comando de selecao de canal e start
// 1   	
   	output_low(MCP3208_CLK);
	output_high(MCP3208_DIN);
   	output_high(MCP3208_CLK);
// 2   	
   	output_low(MCP3208_CLK);
	output_high(MCP3208_DIN);
   	output_high(MCP3208_CLK);
// 3   	
   	output_low(MCP3208_CLK);
   	output_bit(MCP3208_DIN,shift_left(&canal,1,0));
   	output_high(MCP3208_CLK);
// 4   	
   	output_low(MCP3208_CLK);
   	output_bit(MCP3208_DIN,shift_left(&canal,1,0));
   	output_high(MCP3208_CLK);
// 5   	
   	output_low(MCP3208_CLK);
   	output_bit(MCP3208_DIN,shift_left(&canal,1,0));
   	output_high(MCP3208_CLK);
// 6   	
   	output_low(MCP3208_CLK);
	output_low(MCP3208_DIN);
   	output_high(MCP3208_CLK);
// 7   	
   	output_low(MCP3208_CLK);
	output_low(MCP3208_DIN);
   	output_high(MCP3208_CLK);
   	output_low(MCP3208_CLK);

// 11   	
   	output_high(MCP3208_CLK);
   	shift_left(&adh,1,input(MCP3208_DOUT));
   	output_low(MCP3208_CLK);
// 10  	
   	output_high(MCP3208_CLK);
   	shift_left(&adh,1,input(MCP3208_DOUT));
   	output_low(MCP3208_CLK);
// 9  	
   	output_high(MCP3208_CLK);
   	shift_left(&adh,1,input(MCP3208_DOUT));
   	output_low(MCP3208_CLK);
// 8  	
   	output_high(MCP3208_CLK);
   	shift_left(&adh,1,input(MCP3208_DOUT));
   	output_low(MCP3208_CLK);
// 7
   	output_high(MCP3208_CLK);
   	shift_left(&adl,1,input(MCP3208_DOUT));
   	output_low(MCP3208_CLK);
// 6
   	output_high(MCP3208_CLK);
   	shift_left(&adl,1,input(MCP3208_DOUT));
   	output_low(MCP3208_CLK);
// 5
   	output_high(MCP3208_CLK);
   	shift_left(&adl,1,input(MCP3208_DOUT));
   	output_low(MCP3208_CLK);
// 4
   	output_high(MCP3208_CLK);
   	shift_left(&adl,1,input(MCP3208_DOUT));
   	output_low(MCP3208_CLK);
// 3
   	output_high(MCP3208_CLK);
   	shift_left(&adl,1,input(MCP3208_DOUT));
   	output_low(MCP3208_CLK);
// 2
   	output_high(MCP3208_CLK);
   	shift_left(&adl,1,input(MCP3208_DOUT));
   	output_low(MCP3208_CLK);

// 1
   	output_high(MCP3208_CLK);
   	shift_left(&adl,1,input(MCP3208_DOUT));
   	output_low(MCP3208_CLK);

// 0
   	output_high(MCP3208_CLK);
   	shift_left(&adl,1,input(MCP3208_DOUT));
   	output_low(MCP3208_CLK);

   	output_low(MCP3208_DOUT);

   	output_high(MCP3208_CS);

   	return((adh << 8)|adl);
}


long int read_analog( BYTE channel )	// Auto specifies single mode
{
	return read_analog_mcp( channel);
}

