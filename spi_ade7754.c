/*////////////////// Driver for ADE7754			 ////////////////////////
////        (C) Copyright 2004 SULTECH            ////
////////////////////////////////////////////////////////////////////////////
*/

#define WRST7754	0x80
#define RDST7754	0x00


void wr_ade7754(char addr)
{
//1
   	output_high(ADE7754_CLK);
   	output_bit(ADE7754_DIN,shift_left(&addr,1,0));
   	output_low(ADE7754_CLK);

//2
   	output_high(ADE7754_CLK);
   	output_bit(ADE7754_DIN,shift_left(&addr,1,0));
   	output_low(ADE7754_CLK);
//3
   	output_high(ADE7754_CLK);
   	output_bit(ADE7754_DIN,shift_left(&addr,1,0));
   	output_low(ADE7754_CLK);
//4
   	output_high(ADE7754_CLK);
   	output_bit(ADE7754_DIN,shift_left(&addr,1,0));
   	output_low(ADE7754_CLK);
//5
   	output_high(ADE7754_CLK);
   	output_bit(ADE7754_DIN,shift_left(&addr,1,0));
   	output_low(ADE7754_CLK);
//6
   	output_high(ADE7754_CLK);
   	output_bit(ADE7754_DIN,shift_left(&addr,1,0));
   	output_low(ADE7754_CLK);
//7
   	output_high(ADE7754_CLK);
   	output_bit(ADE7754_DIN,shift_left(&addr,1,0));
   	output_low(ADE7754_CLK);
//8
   	output_high(ADE7754_CLK);
   	output_bit(ADE7754_DIN,shift_left(&addr,1,0));
   	output_low(ADE7754_CLK);

	delay_us(4);

}

void wr_ade7754_wave(char addr)
{
//1
   	output_high(ADE7754_CLK);
   	output_bit(ADE7754_DIN,shift_left(&addr,1,0));
   	output_low(ADE7754_CLK);

//2
   	output_high(ADE7754_CLK);
   	output_bit(ADE7754_DIN,shift_left(&addr,1,0));
   	output_low(ADE7754_CLK);
//3
   	output_high(ADE7754_CLK);
   	output_bit(ADE7754_DIN,shift_left(&addr,1,0));
   	output_low(ADE7754_CLK);
//4
   	output_high(ADE7754_CLK);
   	output_bit(ADE7754_DIN,shift_left(&addr,1,0));
   	output_low(ADE7754_CLK);
//5
   	output_high(ADE7754_CLK);
   	output_bit(ADE7754_DIN,shift_left(&addr,1,0));
   	output_low(ADE7754_CLK);
//6
   	output_high(ADE7754_CLK);
   	output_bit(ADE7754_DIN,shift_left(&addr,1,0));
   	output_low(ADE7754_CLK);
//7
   	output_high(ADE7754_CLK);
   	output_bit(ADE7754_DIN,shift_left(&addr,1,0));
   	output_low(ADE7754_CLK);
//8
   	output_high(ADE7754_CLK);
   	output_bit(ADE7754_DIN,shift_left(&addr,1,0));
   	output_low(ADE7754_CLK);

	delay_us(1);

}

char rd_ade7754(void)
{
   	char adl;
   	adl = 0;

// 1   	
   	output_high(ADE7754_CLK);
   	output_low(ADE7754_CLK);
   	shift_left(&adl,1,input(ADE7754_DOUT));
// 2   	
   	output_high(ADE7754_CLK);
   	output_low(ADE7754_CLK);
   	shift_left(&adl,1,input(ADE7754_DOUT));
// 3   	
   	output_high(ADE7754_CLK);
   	output_low(ADE7754_CLK);
   	shift_left(&adl,1,input(ADE7754_DOUT));
// 4   	
   	output_high(ADE7754_CLK);
   	output_low(ADE7754_CLK);
   	shift_left(&adl,1,input(ADE7754_DOUT));
// 5   	
   	output_high(ADE7754_CLK);
   	output_low(ADE7754_CLK);
   	shift_left(&adl,1,input(ADE7754_DOUT));
// 6   	
   	output_high(ADE7754_CLK);
   	output_low(ADE7754_CLK);
   	shift_left(&adl,1,input(ADE7754_DOUT));
// 7   	
   	output_high(ADE7754_CLK);
   	output_low(ADE7754_CLK);
   	shift_left(&adl,1,input(ADE7754_DOUT));
// 8   	
   	output_high(ADE7754_CLK);
   	output_low(ADE7754_CLK);
   	shift_left(&adl,1,input(ADE7754_DOUT));

	delay_us(1);

   	return(adl);
}

int32 le_long_ade7754(char addr)
{
	char byte1,byte2,byte3;
// start
   	output_low(ADE7754_CLK);
	output_high(ADE7754_DIN);
   	output_low(ADE7754_CS);

	wr_ade7754(addr);

	byte1 = rd_ade7754();	
	byte2 = rd_ade7754();	
	byte3 = rd_ade7754();	
// stop
   	output_high(ADE7754_CS);
   	output_low(ADE7754_CLK);

	return(make32(0,byte1,byte2,byte3));
}


word le_xlong_ade7754(char addr)
{
	char byte1,byte2;	//,byte3;
// start
   	output_low(ADE7754_CLK);
	output_high(ADE7754_DIN);
   	output_low(ADE7754_CS);

	wr_ade7754(addr);

	byte1 = rd_ade7754();	
	byte2 = rd_ade7754();	
//	byte3 = rd_ade7754();	
// stop
   	output_high(ADE7754_CS);
   	output_low(ADE7754_CLK);

	return(make16(byte1,byte2));
}

word le_tlong_ade7754(char addr)
{
	char byte1,byte2,byte3;
// start
   	output_low(ADE7754_CLK);
	output_high(ADE7754_DIN);
   	output_low(ADE7754_CS);

	wr_ade7754_wave(addr);

	byte1 = rd_ade7754();	
	byte2 = rd_ade7754();	
	byte3 = rd_ade7754();	
// stop
   	output_high(ADE7754_CS);
   	output_low(ADE7754_CLK);

	return(make16(byte2,byte3));
}

word le_clong_ade7754(char addr)
{
	char byte1,byte2,byte3;
// start
   	output_low(ADE7754_CLK);
	output_high(ADE7754_DIN);
   	output_low(ADE7754_CS);

	wr_ade7754_wave(addr);

	byte1 = rd_ade7754();	
	byte2 = rd_ade7754();	
	byte3 = rd_ade7754();	
// stop
   	output_high(ADE7754_CS);
   	output_low(ADE7754_CLK);

	return(make16(byte1,byte2));
}


word le_word_ade7754(char addr)
{
	char byte1,byte2;
// start
   	output_low(ADE7754_CLK);
	output_high(ADE7754_DIN);
   	output_low(ADE7754_CS);

	wr_ade7754(addr);

	byte1 = rd_ade7754();	
	byte2 = rd_ade7754();	
// stop
   	output_high(ADE7754_CS);
   	output_low(ADE7754_CLK);

	return(make16(byte1,byte2));
}

char le_byte_ade7754(char addr)
{
	char byte1;
// start
   	output_low(ADE7754_CLK);
	output_high(ADE7754_DIN);
   	output_low(ADE7754_CS);

	wr_ade7754(addr);

	byte1 = rd_ade7754();	
// stop
   	output_high(ADE7754_CS);
   	output_low(ADE7754_CLK);

	return(byte1);

}


void salva_word_ade7754(char addr, word valor)
{
// start
   	output_low(ADE7754_CLK);
	output_high(ADE7754_DIN);
   	output_low(ADE7754_CS);

	wr_ade7754(addr | WRST7754);

	wr_ade7754((char)(valor >> 8));
	wr_ade7754((char)(valor));

// stop
   	output_high(ADE7754_CS);
   	output_low(ADE7754_CLK);

//	delay_us(10);
	
}

void salva_byte_ade7754(char addr, char valor)
{
// start
   	output_low(ADE7754_CLK);
	output_high(ADE7754_DIN);
   	output_low(ADE7754_CS);

	wr_ade7754(addr | WRST7754);


	wr_ade7754((char)(valor));

// stop
   	output_high(ADE7754_CS);
   	output_low(ADE7754_CLK);

//	delay_us(10);
	
}
