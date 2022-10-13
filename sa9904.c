/*
 *	     Module : SA9904.c
 *              pjt : mtb
 *      description : Re-use of morten project's module, 
 *                    utilises PIC's native SPI hardware
 *
 *              ver : 1.0.1
 *	         log:
 *			1.0.1 _df 21-11-2001 moved com_spi.c's code to this module
 *			1.0   _df 26-10-2001 init coding
 *
 */


#define slong signed int32 	//some short-cuts
#define sint  signed int16
#define uint  unsigned int16
#define uchar unsigned char

//the next fcn returns x to the power of y
#define LIMIT 0x00FFFFFF 		//upperlimit for 24 bits 
long powerof(uint x,uint y)
{
  	unsigned char i;
  	int32 total;

    if (y==0)
    	{
	    return 1;		//else calculate
	    }
    total=x;
    for (i=1;i<y;i++)
    	{
	    total*=x;
	    }
    total &= LIMIT;
  	return(total);
 }


void cs_on(void)
{
	output_low(SA9904_CLK);	//=OFF;
	output_high(SA9904_CS);	// = ON; 	//lift 9904's chip select

}
void cs_off(void)
{
	output_low(SA9904_CS); 	//= OFF	//drop chip select
	output_high(SA9904_CLK);	//=OFF;
}


void WR_SA9904(char addr)
{
	char x;
   	output_high(SA9904_CLK);
   	delay_cycles(1);
   	output_low(SA9904_CLK);
   	delay_cycles(1);
	output_high(SA9904_DIN);
   	delay_cycles(1);
   	output_high(SA9904_CLK);
   	delay_cycles(1);
	for (x = 0; x < 8; x++)
		{
	   	output_low(SA9904_CLK);
   		output_bit(SA9904_DIN,shift_left(&addr,1,0));
	   	output_high(SA9904_CLK);
		}

}


unsigned char RD_SA9904(void) 
{
   	char char_read = 0;
	char x;
   	output_high(SA9904_CLK);	
	for (x = 0; x < 8; x++)
		{
	   	output_low(SA9904_CLK);
   		shift_left(&char_read,1,input(SA9904_DOUT));
	   	output_high(SA9904_CLK);	
		}

   	return(char_read);
}



int32 le_sa9904(char address)		//read 24bit register
{
	int32 dado;				//the spi return variable
	unsigned char in[3];				//buffer for received bytes

   	 					//SA9904's chip select high
	output_low(SA9904_DIN);
	output_low(SA9904_CLK);	//=OFF;
	output_high(SA9904_CS);		// = ON; 	//lift 9904's chip select
   
   	WR_SA9904(address | 0x80);		//tx 10 of the read command <10A5A4 A3A2A1A0>


//----- rx bytes --------------
// <<0,1,2 -> MSB ... LSB>>
//-----------------------------
	in[0] = RD_SA9904();
	in[1] = RD_SA9904();
	in[2] = RD_SA9904();

	output_low(SA9904_CS); 	//= OFF	//drop chip select

	dado = make32(0,in[0],in[1],in[2]);


	return(dado);
}



void le_grandezas_sames(void)
{
	KW_R_SAMES = le_sa9904(0);	
	KVAR_R_SAMES = le_sa9904(1);	
	VR_SAMES = le_sa9904(2);	
	HZ_SAMES = le_sa9904(3);	

	KW_S_SAMES = le_sa9904(4);	
	KVAR_S_SAMES = le_sa9904(5);	
	VS_SAMES = le_sa9904(6);	

	KW_T_SAMES = le_sa9904(8);	
	KVAR_T_SAMES = le_sa9904(9);	
	VT_SAMES = le_sa9904(10);	

}
