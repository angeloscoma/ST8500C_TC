/*////////////////// Driver for CS5460A - CIRRUS   ////////////////////////
////																	////
////																	////
////																	////
////////////////////////////////////////////////////////////////////////////
////        (C) Copyright 2004 Sultech Sistemas Eletrônicos Ltda        ////
////	By Vagner Santos 												////
////////////////////////////////////////////////////////////////////////////
*/

// Definição de endereços dos variaveis do CS5460a
#define config_cs5460a		0		// congiguration register
#define I_dc_offset			2		// current channel DC offset register
#define I_gain				4		// current channel gain register
#define	V_dc_offset			6		// voltage channel DC offset register
#define V_gain				8		// voltage channel gain register
#define cycle_count			10		// number of A/D cycles per computation cycle
#define pulse_rate			12		// used to set the energy-to-pulse ratio on EOUT(and EDIR).
#define I_register			14		// instantaneous current register (most recent current sample).
#define V_register			16		// instantaneous voltage register (most recent voltage sample).
#define P_register			18		// instanteneous Power register (most recent power sample).
#define E_register			20		// Energy register (computed over latest computation cycle).
#define I_rms				22		// RMS current register (computed over latest computation cycle).
#define V_rms				24		// RMS voltage register (computed over latest computation cycle).
#define TBC_register		26		// timebase calibration register.
#define P_offset			28		// Power offset register.
#define Status_cs5460a		30		// Status register.
#define I_ac_offset			32		// Current channel AC offset register
#define V_ac_offset			34		// Voltage channel AC offset register
#define mask_cs5460a		52		// Mask register.
#define ctrl_cs5460a		56		// Control register.

// definicoes para o cs5460B
#define I_ac_offset_B		2		// Current channel AC offset register
#define V_ac_offset_B		6		// Voltage channel AC offset register


// definições de inicialização
#define start_conversions	0b11101000		// Start conversion, 0b1110c000  - c = 1  Continuos computation cycles
#define SYNC0_command		0b11111110
#define SYNC1_command		0b11111111
#define Power_up_halt		0b11100000	
#define Power_down_standby	0b11001000
#define Power_down_sleep	0b11010000

//								0b110VIRGO
//									     O=>	0=Normal; 1=perform offset calibration
//									    G=> 	0=Normal; 1=perform gain calibration
//									   R=>		0=DC; 1=AC
//									  I=>		1=current channel
//									 V=>		1=voltage channel
#define I_dc_calibra_offset		0b11001001
#define I_ac_calibra_offset		0b11001101
#define V_dc_calibra_offset		0b11010001
#define V_ac_calibra_offset		0b11010101

#define I_dc_calibra_ganho		0b11001010
#define I_ac_calibra_ganho		0b11001110
#define V_dc_calibra_ganho		0b11010010
#define V_ac_calibra_ganho		0b11010110
#define calibra_V_I_dc_offset 	0b11011001
#define calibra_V_I_ac_offset 	0b11011101
#define caliba_V_ganho			0b11010010
#define caliba_I_ganho			0b11001010

// variaveis em e2prom
#define ee_config_cs5460a_h		ini_ee_cs5460 + 0		// congiguration register
#define ee_config_cs5460a_m		ini_ee_cs5460 + 1		// congiguration register
#define ee_config_cs5460a_l		ini_ee_cs5460 + 2		// congiguration register
#define ee_I_dc_offset_h		ini_ee_cs5460 + 3		// current channel DC offset register
#define ee_I_dc_offset_m		ini_ee_cs5460 + 4		// current channel DC offset register
#define ee_I_dc_offset_l		ini_ee_cs5460 + 5		// current channel DC offset register
#define ee_I_gain_h_R			ini_ee_cs5460 + 6		// current channel gain register
#define ee_I_gain_m_R			ini_ee_cs5460 + 7		// current channel gain register
#define ee_I_gain_l_R			ini_ee_cs5460 + 8		// current channel gain register
#define	ee_V_dc_offset_h		ini_ee_cs5460 + 9		// voltage channel DC offset register
#define	ee_V_dc_offset_m		ini_ee_cs5460 + 10		// voltage channel DC offset register
#define	ee_V_dc_offset_l		ini_ee_cs5460 + 11		// voltage channel DC offset register
#define ee_V_gain_h_R			ini_ee_cs5460 + 12		// voltage channel gain register
#define ee_V_gain_m_R			ini_ee_cs5460 + 13		// voltage channel gain register
#define ee_V_gain_l_R			ini_ee_cs5460 + 14		// voltage channel gain register
#define ee_cycle_count_h		ini_ee_cs5460 + 15		// number of A/D cycles per computation cycle
#define ee_cycle_count_m		ini_ee_cs5460 + 16		// number of A/D cycles per computation cycle
#define ee_cycle_count_l		ini_ee_cs5460 + 17		// number of A/D cycles per computation cycle
#define ee_pulse_rate_h			ini_ee_cs5460 + 18		// used to set the energy-to-pulse ratio on EOUT(and EDIR).
#define ee_pulse_rate_m			ini_ee_cs5460 + 19		// used to set the energy-to-pulse ratio on EOUT(and EDIR).
#define ee_pulse_rate_l			ini_ee_cs5460 + 20		// used to set the energy-to-pulse ratio on EOUT(and EDIR).
#define ee_TBC_register_h		ini_ee_cs5460 + 21		// timebase calibration register.
#define ee_TBC_register_m		ini_ee_cs5460 + 22		// timebase calibration register.
#define ee_TBC_register_l		ini_ee_cs5460 + 23		// timebase calibration register.
#define ee_P_offset_h			ini_ee_cs5460 + 24		// Power offset register.
#define ee_P_offset_m			ini_ee_cs5460 + 25		// Power offset register.
#define ee_P_offset_l			ini_ee_cs5460 + 26		// Power offset register.
#define ee_I_ac_offset_h		ini_ee_cs5460 + 27		// current channel AC offset register
#define ee_I_ac_offset_m		ini_ee_cs5460 + 28		// current channel AC offset register
#define ee_I_ac_offset_l		ini_ee_cs5460 + 29		// current channel AC offset register
#define	ee_V_ac_offset_h		ini_ee_cs5460 + 30		// voltage channel AC offset register
#define	ee_V_ac_offset_m		ini_ee_cs5460 + 31		// voltage channel AC offset register
#define	ee_V_ac_offset_l		ini_ee_cs5460 + 32		// voltage channel AC offset register
#define ee_V_gain_h_S			ini_ee_cs5460 + 33		// voltage channel gain register
#define ee_V_gain_m_S			ini_ee_cs5460 + 34		// voltage channel gain register
#define ee_V_gain_l_S			ini_ee_cs5460 + 35		// voltage channel gain register
#define ee_V_gain_h_T			ini_ee_cs5460 + 36		// voltage channel gain register
#define ee_V_gain_m_T			ini_ee_cs5460 + 37		// voltage channel gain register
#define ee_V_gain_l_T			ini_ee_cs5460 + 38		// voltage channel gain register
#define ee_I_gain_h_S			ini_ee_cs5460 + 39		// current channel gain register
#define ee_I_gain_m_S			ini_ee_cs5460 + 40		// current channel gain register
#define ee_I_gain_l_S			ini_ee_cs5460 + 41		// current channel gain register
#define ee_I_gain_h_T			ini_ee_cs5460 + 42		// current channel gain register
#define ee_I_gain_m_T			ini_ee_cs5460 + 43		// current channel gain register
#define ee_I_gain_l_T			ini_ee_cs5460 + 44		// current channel gain register

// definicão da interrupçao
#define mask_cs5460h		0b10010011
#define mask_cs5460m		0b11110000
#define mask_cs5460l		0b00111000



// definiçoes de funçoes

void write_cs5460_byte(char data_byte) 
{
   	output_low(CS5460A_CLK);
// 0   	
   	output_bit(CS5460A_DIN,shift_left(&data_byte,1,0));
   	output_high(CS5460A_CLK);
   	output_low(CS5460A_CLK);
// 1   	
   	output_bit(CS5460A_DIN,shift_left(&data_byte,1,0));
   	output_high(CS5460A_CLK);
   	output_low(CS5460A_CLK);
// 2   	
   	output_bit(CS5460A_DIN,shift_left(&data_byte,1,0));
   	output_high(CS5460A_CLK);
   	output_low(CS5460A_CLK);
// 3   	
   	output_bit(CS5460A_DIN,shift_left(&data_byte,1,0));
   	output_high(CS5460A_CLK);
   	output_low(CS5460A_CLK);
// 4   	
   	output_bit(CS5460A_DIN,shift_left(&data_byte,1,0));
   	output_high(CS5460A_CLK);
   	output_low(CS5460A_CLK);
// 5   	
   	output_bit(CS5460A_DIN,shift_left(&data_byte,1,0));
   	output_high(CS5460A_CLK);
   	output_low(CS5460A_CLK);
// 6   	
   	output_bit(CS5460A_DIN,shift_left(&data_byte,1,0));
   	output_high(CS5460A_CLK);
   	output_low(CS5460A_CLK);
// 7   	
   	output_bit(CS5460A_DIN,shift_left(&data_byte,1,0));
   	output_high(CS5460A_CLK);
   	output_low(CS5460A_CLK);
   	output_high(CS5460A_DIN);
   		
}


char read_cs5460_byte(void) 
{
   	char data_byte;
// 0   	
   	output_high(CS5460A_DIN);
   	shift_left(&data_byte,1,input(CS5460A_DOUT));
   	output_high(CS5460A_CLK);
   	output_low(CS5460A_CLK);
// 1   	
   	shift_left(&data_byte,1,input(CS5460A_DOUT));
   	output_high(CS5460A_CLK);
   	output_low(CS5460A_CLK);
// 2   	
   	shift_left(&data_byte,1,input(CS5460A_DOUT));
   	output_high(CS5460A_CLK);
   	output_low(CS5460A_CLK);
// 3   	
   	shift_left(&data_byte,1,input(CS5460A_DOUT));
   	output_high(CS5460A_CLK);
   	output_low(CS5460A_CLK);
// 4   	
   	shift_left(&data_byte,1,input(CS5460A_DOUT));
   	output_high(CS5460A_CLK);
   	output_low(CS5460A_CLK);
// 5   	
   	shift_left(&data_byte,1,input(CS5460A_DOUT));
   	output_high(CS5460A_CLK);
   	output_low(CS5460A_CLK);
// 6   	
   	shift_left(&data_byte,1,input(CS5460A_DOUT));
   	output_high(CS5460A_CLK);
   	output_low(CS5460A_CLK);
// 7   	
   	shift_left(&data_byte,1,input(CS5460A_DOUT));
   	output_high(CS5460A_CLK);
   	output_low(CS5460A_CLK);

	return(data_byte);
}

int32 read_cs5460(char endereco, char fase) 
{
  	output_low(CS5460A_DIN);
   	output_low(CS5460A_CLK);
 	if (fase == 'R')
		{
		output_low(CS5460A_CS_R);
		}
	else if (fase == 'S')
		{
		output_low(CS5460A_CS_S);
		}
	else
		{
		output_low(CS5460A_CS_T);
		}
	write_cs5460_byte(endereco);
	datah = read_cs5460_byte(); 
	datam = read_cs5460_byte(); 
	datal = read_cs5460_byte(); 

	output_high(CS5460A_CS_R);
	output_high(CS5460A_CS_S);
	output_high(CS5460A_CS_T);

   	return(make32(datah, datam, datal));

}

int16 read_word_cs5460(char endereco, char fase) 
{
  	output_low(CS5460A_DIN);
   	output_low(CS5460A_CLK);
 	if (fase == 'R')
		{
		output_low(CS5460A_CS_R);
		}
	else if (fase == 'S')
		{
		output_low(CS5460A_CS_S);
		}
	else
		{
		output_low(CS5460A_CS_T);
		}
	write_cs5460_byte(endereco);
	datah = read_cs5460_byte(); 
	datam = read_cs5460_byte(); 

	output_high(CS5460A_CS_R);
	output_high(CS5460A_CS_S);
	output_high(CS5460A_CS_T);

   	return(make16(datah, datam));

}

void write_cs5460(int32 endereco, int32 data_int32, char fase)
{
  	output_low(CS5460A_DIN);
   	output_low(CS5460A_CLK);
 	if(fase == 'R')
		{
		output_low(CS5460A_CS_R);
		}
	else if (fase == 'S')
		{
		output_low(CS5460A_CS_S);
		}
	else
		{
		output_low(CS5460A_CS_T);
		}
	endereco = endereco | 0b01000000;
	write_cs5460_byte(endereco);
	write_cs5460_byte(data_int32 >> 16); 
	write_cs5460_byte(data_int32 >> 8); 
	write_cs5460_byte(data_int32); 

	output_high(CS5460A_CS_R);
	output_high(CS5460A_CS_S);
	output_high(CS5460A_CS_T);

}

// inicializa cs5460, trem de pulsos de power-up.
void reset_cs5460(void)
{
	output_high(CS5460A_CS_R);
	output_high(CS5460A_CS_S);
	output_high(CS5460A_CS_T);
	output_low(CS5460A_RST);
	delay_us(10);
	output_high(CS5460A_RST);
	delay_us(10);
	output_low(CS5460A_RST);
	delay_us(10);
	output_high(CS5460A_RST);
	delay_ms(100);
 	write_cs5460(config_cs5460a, 0x00000081, 'R' );
 	write_cs5460(config_cs5460a, 0x00000081, 'S' );
 	write_cs5460(config_cs5460a, 0x00000081, 'T' );
}


void inic_cs5640(void)
{
 	write_cs5460(0XFF, 0x00FFFFFE, 'R' );
 	write_cs5460(0XFF, 0x00FFFFFE, 'S' );
 	write_cs5460(0XFF, 0x00FFFFFE, 'T' );
}


void start_cs5460(void)
{
// fase R
	output_low(CS5460A_CS_R);
	output_low(CS5460A_CS_S);
	output_low(CS5460A_CS_T);
	write_cs5460_byte(start_conversions);
	output_high(CS5460A_CS_R);
	output_high(CS5460A_CS_S);
	output_high(CS5460A_CS_T);

}

// configura cs5460 apartir de dados em e2prom.
void config_cs5460(void)
{
/*
	output_high(direcao);
	delay_ms(1);
	printf("Configurando cs5460!!!!\r\n");
	delay_ms(2);
	output_low(direcao);
*/

// default em andamento:
//  i_ac_offset = 0xfffff6
//  V_ac_offset = 0xfffff6
//  P_offset = 0x00002d
//  condig = 0x


/*	write_byte(ee_I_dc_offset_h, 0x00);
	write_byte(ee_I_dc_offset_m, 0x00);
	write_byte(ee_I_dc_offset_l, 0x00);

	write_byte(ee_V_dc_offset_h, 0x00);
	write_byte(ee_V_dc_offset_m, 0x00);
	write_byte(ee_V_dc_offset_l, 0x00);

	write_byte(ee_I_gain_h, 0x40);
	write_byte(ee_I_gain_m, 0x00);
	write_byte(ee_I_gain_l, 0x00);

	write_byte(ee_V_gain_h, 0x40);
	write_byte(ee_V_gain_m, 0x00);
	write_byte(ee_V_gain_l, 0x00);
*/

//FASE R
	

// current channel AC offset register
	datah = read_byte(ee_I_ac_offset_h);
	datam = read_byte(ee_I_ac_offset_m);
	datal = read_byte(ee_I_ac_offset_l);
	aux_l1 = make32(datah,datam,datal);
	write_cs5460(I_ac_offset, aux_l1, 'R');

// voltage channel AC offset register
	datah = read_byte(ee_V_ac_offset_h);
	datam = read_byte(ee_V_ac_offset_m);
	datal = read_byte(ee_V_ac_offset_l);
	aux_l1 = make32(datah,datam,datal);
	write_cs5460(V_ac_offset, aux_l1, 'R');

	datah = read_byte(ee_P_offset_h);
	datam = read_byte(ee_P_offset_m);
	datal = read_byte(ee_P_offset_l);
	aux_l1 = make32(datah,datam,datal);
	write_cs5460(P_offset, aux_l1, 'R');

// current channel DC offset register
	datah = read_byte(ee_I_dc_offset_h);
	datam = read_byte(ee_I_dc_offset_m);
	datal = read_byte(ee_I_dc_offset_l);
	aux_l1 = make32(datah,datam,datal);
	write_cs5460(I_dc_offset, aux_l1, 'R');


// voltage channel DC offset register
	datah = read_byte(ee_V_dc_offset_h);
	datam = read_byte(ee_V_dc_offset_m);
	datal = read_byte(ee_V_dc_offset_l);
	aux_l1 = make32(datah,datam,datal);
	write_cs5460(V_dc_offset, aux_l1, 'R');


// current channel gain register
	datah = read_byte(ee_I_gain_h_R);
	datam = read_byte(ee_I_gain_m_R);
	datal = read_byte(ee_I_gain_l_R);
	aux_l1 = make32(datah,datam,datal);
	write_cs5460(I_gain, aux_l1, 'R');


// voltage channel gain register
	datah = read_byte(ee_V_gain_h_R);
	datam = read_byte(ee_V_gain_m_R);
	datal = read_byte(ee_V_gain_l_R);
	aux_l1 = make32(datah,datam,datal);
	write_cs5460(V_gain, aux_l1, 'R');

//FASE S
// current channel AC offset register
	datah = read_byte(ee_I_ac_offset_h);
	datam = read_byte(ee_I_ac_offset_m);
	datal = read_byte(ee_I_ac_offset_l);
	aux_l1 = make32(datah,datam,datal);
	write_cs5460(I_ac_offset, aux_l1, 'S');

// voltage channel AC offset register
	datah = read_byte(ee_V_ac_offset_h);
	datam = read_byte(ee_V_ac_offset_m);
	datal = read_byte(ee_V_ac_offset_l);
	aux_l1 = make32(datah,datam,datal);
	write_cs5460(V_ac_offset, aux_l1, 'S');

	datah = read_byte(ee_P_offset_h);
	datam = read_byte(ee_P_offset_m);
	datal = read_byte(ee_P_offset_l);
	aux_l1 = make32(datah,datam,datal);
	write_cs5460(P_offset, aux_l1, 'S');

// current channel DC offset register
	datah = read_byte(ee_I_dc_offset_h);
	datam = read_byte(ee_I_dc_offset_m);
	datal = read_byte(ee_I_dc_offset_l);
	aux_l1 = make32(datah,datam,datal);
	write_cs5460(I_dc_offset, aux_l1, 'S');


// voltage channel DC offset register
	datah = read_byte(ee_V_dc_offset_h);
	datam = read_byte(ee_V_dc_offset_m);
	datal = read_byte(ee_V_dc_offset_l);
	aux_l1 = make32(datah,datam,datal);
	write_cs5460(V_dc_offset, aux_l1, 'S');


// current channel gain register
	datah = read_byte(ee_I_gain_h_S);
	datam = read_byte(ee_I_gain_m_S);
	datal = read_byte(ee_I_gain_l_S);
	aux_l1 = make32(datah,datam,datal);
	write_cs5460(I_gain, aux_l1, 'S');


// voltage channel gain register
	datah = read_byte(ee_V_gain_h_S);
	datam = read_byte(ee_V_gain_m_S);
	datal = read_byte(ee_V_gain_l_S);
	aux_l1 = make32(datah,datam,datal);
	write_cs5460(V_gain, aux_l1, 'S');


//FASE T
// current channel AC offset register
	datah = read_byte(ee_I_ac_offset_h);
	datam = read_byte(ee_I_ac_offset_m);
	datal = read_byte(ee_I_ac_offset_l);
	aux_l1 = make32(datah,datam,datal);
	write_cs5460(I_ac_offset, aux_l1, 'T');

// voltage channel AC offset register
	datah = read_byte(ee_V_ac_offset_h);
	datam = read_byte(ee_V_ac_offset_m);
	datal = read_byte(ee_V_ac_offset_l);
	aux_l1 = make32(datah,datam,datal);
	write_cs5460(V_ac_offset, aux_l1, 'T');

	datah = read_byte(ee_P_offset_h);
	datam = read_byte(ee_P_offset_m);
	datal = read_byte(ee_P_offset_l);
	aux_l1 = make32(datah,datam,datal);
	write_cs5460(P_offset, aux_l1, 'T');

// current channel DC offset register
	datah = read_byte(ee_I_dc_offset_h);
	datam = read_byte(ee_I_dc_offset_m);
	datal = read_byte(ee_I_dc_offset_l);
	aux_l1 = make32(datah,datam,datal);
	write_cs5460(I_dc_offset, aux_l1, 'T');


// voltage channel DC offset register
	datah = read_byte(ee_V_dc_offset_h);
	datam = read_byte(ee_V_dc_offset_m);
	datal = read_byte(ee_V_dc_offset_l);
	aux_l1 = make32(datah,datam,datal);
	write_cs5460(V_dc_offset, aux_l1, 'T');


// current channel gain register
	datah = read_byte(ee_I_gain_h_T);
	datam = read_byte(ee_I_gain_m_T);
	datal = read_byte(ee_I_gain_l_T);
	aux_l1 = make32(datah,datam,datal);
	write_cs5460(I_gain, aux_l1, 'T');


// voltage channel gain register
	datah = read_byte(ee_V_gain_h_T);
	datam = read_byte(ee_V_gain_m_T);
	datal = read_byte(ee_V_gain_l_T);
	aux_l1 = make32(datah,datam,datal);
	write_cs5460(V_gain, aux_l1, 'T');

/*
	output_high(direcao);
	delay_ms(1);
	printf("Passo 01-OK!!!!\r\n");
	delay_ms(2);
	output_low(direcao);
*/

/*
	output_high(direcao);
	delay_ms(1);
	printf("Passo 02-OK!!!!\r\n");
	delay_ms(2);
	output_low(direcao);
*/
config_cs5460_10:

// congiguration register

	datah = read_byte(ee_config_cs5460a_h);
	datam = read_byte(ee_config_cs5460a_m);
	datal = read_byte(ee_config_cs5460a_l);
	aux_l1 = make32(datah,datam,datal);

	write_cs5460(config_cs5460a, aux_l1, 'R');
	write_cs5460(config_cs5460a, aux_l1, 'S');
	write_cs5460(config_cs5460a, aux_l1, 'T');

	write_cs5460(mask_cs5460a, 0x00900000, 'R');
	write_cs5460(mask_cs5460a, 0x00900000, 'S');
	write_cs5460(mask_cs5460a, 0x00900000, 'T');
/*
	output_high(direcao);
	delay_ms(1);
	printf("Passo 03-OK!!!!\r\n");
	delay_ms(2);
	output_low(direcao);
*/
//	goto config_cs5460_20;

// number of A/D cycles per computation cycle
	write_cs5460(cycle_count, 0x00000fa0, 'R');			// 4000
	write_cs5460(cycle_count, 0x00000fa0, 'S');			// 4000
	write_cs5460(cycle_count, 0x00000fa0, 'T');			// 4000
// timebase calibration register.
	write_cs5460(TBC_register, 0x007fffff, 'R');		// 007fffff = unitário
	write_cs5460(TBC_register, 0x007fffff, 'S');		// 007fffff = unitário
	write_cs5460(TBC_register, 0x00800000, 'R');		// 007fffff = unitário
														// 0083126c = 1.024
// used to set the energy-to-pulse ratio on EOUT(and EDIR).
// voltage channel gain register
	datah = read_byte(ee_pulse_rate_h);
	datam = read_byte(ee_pulse_rate_m);
	datal = read_byte(ee_pulse_rate_l);
	aux_l1 = make32(datah,datam,datal);

	write_cs5460(pulse_rate, aux_l1, 'R');			//0x000fa000 = default
	write_cs5460(pulse_rate, aux_l1, 'S');			//0x000fa000 = default
	write_cs5460(pulse_rate, aux_l1, 'T');			//0x000fa000 = default
														//0x000003c0 = 30
														//0x000000a0 = 5	
	write_cs5460(ctrl_cs5460a, 0x00000051, 'R');		
	write_cs5460(ctrl_cs5460a, 0x00000051, 'S');		
	write_cs5460(ctrl_cs5460a, 0x00000051, 'T');		


config_cs5460_20:
	start_cs5460();			// dispara conversoes

//	ext_int_edge(2,H_TO_L);
//	enable_interrupts(INT_EXT2);
/*
	output_high(direcao);
	delay_ms(1);
	printf("Reset cs5460!!!!\r\n");
	delay_ms(2);
	output_low(direcao);
*/
}														

void calibra_cs5460(void)
{

}


void tx_config_cs55460(char fase)
{
	output_high(direcao);
	delay_ms(1);
	printf("\r\n");
	printf("*********************************************************\r\n");
	printf("Configurações CS5460A, FASE %c\r\n", fase);
	aux_cs5460_l = read_cs5460(config_cs5460a,fase);	
	printf("Config register:%Lx \r\n", aux_cs5460_l);
	aux_cs5460_l = read_cs5460(status_cs5460a,fase);	
	write_cs5460(status_cs5460a, aux_cs5460_l, fase);	
	printf("status register: %Lx, %Lx  \r\n", aux_cs5460_l, status_cs5460_l);
	aux_cs5460_l = read_cs5460(mask_cs5460a,fase);	
	printf("Mask register:%Lx  \r\n", aux_cs5460_l);
	aux_cs5460_l = read_cs5460(ctrl_cs5460a,fase);	
	printf("Control register:%Lx \r\n", aux_cs5460_l);

	aux_cs5460_l = read_cs5460(I_dc_offset,fase);	
	printf("Corrente: DC_off_set:%Lx", aux_cs5460_l);
	aux_cs5460_l = read_cs5460(I_ac_offset,fase);	
	printf("; AC_off_set:%Lx", aux_cs5460_l);
	aux_cs5460_l = read_cs5460(I_gain,fase);	
	printf("; I_Ganho:%Lx", aux_cs5460_l);
	aux_cs5460_l = read_cs5460(I_rms,fase);	
	printf("; Corrente:%Lx", aux_cs5460_l);
	printf("\r\n");

	aux_cs5460_l = read_cs5460(V_dc_offset,fase);	
	printf("Tensão: DC_off_set:%Lx", aux_cs5460_l);
	aux_cs5460_l = read_cs5460(V_ac_offset,fase);	
	printf("; AC_off_set:%Lx", aux_cs5460_l);
	aux_cs5460_l = read_cs5460(V_gain,fase);	
	printf("; V_Ganho:%Lx", aux_cs5460_l);
	aux_cs5460_l = read_cs5460(V_rms,fase);	
	printf("; tensão:%Lx", aux_cs5460_l);
	printf("\r\n");

	aux_cs5460_l = read_cs5460(pulse_rate,fase);	
	printf("Power: Pulse_rate:%Lx",aux_cs5460_l);
	aux_cs5460_l = read_cs5460(P_offset,fase);	
	printf("; P_off_set:%Lx", aux_cs5460_l);
	aux_cs5460_l = read_cs5460(cycle_count,fase);	
	printf("; Cycle Count:%Lx", aux_cs5460_l);
	aux_cs5460_l = read_cs5460(TBC_register,fase);	
	printf("; Time base:%Lx", aux_cs5460_l);
	printf("\r\n");
				
	printf("Medidas elétricas FASE %c\r\n", fase);
	aux_cs5460_l = read_cs5460(V_rms,fase);	
	printf("Tensão:%lu, %Lx\r\n", aux_cs5460_l, aux_cs5460_l);
	aux_cs5460_l = read_cs5460(I_rms,fase);	
	printf("Corrente:%lu, %Lx\r\n", aux_cs5460_l, aux_cs5460_l);
	aux_cs5460_l = read_cs5460(E_register,fase);	
	printf("Energia:%lu, %Lx\r\n", aux_cs5460_l, aux_cs5460_l);
	printf("aux_ener_l:%lu, %Lx\r\n", aux_ener_l, aux_ener_l);
	printf("pot_ativa_r:%lu, %Lx\r\n", pot_ativa_r, pot_ativa_r);
				
				
	printf("\r\n");
	printf("*********************************************************\r\n");
	delay_ms(2);
	output_low(direcao);
}



void grava_config_cs5460a(char fase)
{
	datah = datah & 0xFE;
	aux_cs5460_l = make32(0x00, datah, datam, datal);

	write_cs5460(config_cs5460a, aux_cs5460_l, fase);

	write_byte(ee_config_cs5460a_h, datah);
	write_byte(ee_config_cs5460a_m, datam);		//0x10);
	write_byte(ee_config_cs5460a_l, datal);		//0x61);

	output_high(direcao);
	delay_ms(1);
	printf(" Config cs5460a fase %c=%lx,%lx ", fase, read_cs5460(config_cs5460a,fase), aux_cs5460_l);
	aux_cs5460_l = read_cs5460(E_register,fase);	
	printf("Energia:%lu, %Lx\r\n", aux_cs5460_l, aux_cs5460_l);
	printf("\r\n");
	delay_ms(2);
	output_low(direcao);
}

void inc_off_set_fp_cs5460a(char fase)
{
	aux_cs5460_l = read_cs5460(config_cs5460a, fase);
	datah++;
	datah++;
	grava_config_cs5460a(fase);
}

void dec_off_set_fp_cs5460a(char fase)
{
	aux_cs5460_l = read_cs5460(config_cs5460a, fase);
	datah--;
	grava_config_cs5460a(fase);
}

void inc_tbc_register(char fase)
{
	aux_cs5460_l = read_cs5460(TBC_register, fase);
	aux_cs5460_l++;
	write_cs5460(TBC_register, aux_cs5460_l, fase);		// 007fffff = unitário
	aux_cs5460_l = read_cs5460(TBC_register, fase);

	write_byte(ee_TBC_register_h, datah);
	write_byte(ee_TBC_register_m, datam);
	write_byte(ee_TBC_register_l, datal);

	output_high(direcao);
	delay_ms(1);
	printf(" TBC Register fase %c=%lx,%lx ", fase, read_cs5460(TBC_register, fase), aux_cs5460_l);
	aux_cs5460_l = read_cs5460(E_register,fase);	
	printf("Energia:%lu, %Lx\r\n", aux_cs5460_l, aux_cs5460_l);
	printf("\r\n");
	delay_ms(2);
	output_low(direcao);
}

void dec_tbc_register(char fase)
{
	aux_cs5460_l = read_cs5460(TBC_register, fase);
	aux_cs5460_l--;
	write_cs5460(TBC_register, aux_cs5460_l, fase);		// 007fffff = unitário
	aux_cs5460_l = read_cs5460(TBC_register, fase);

	write_byte(ee_TBC_register_h, datah);
	write_byte(ee_TBC_register_m, datam);
	write_byte(ee_TBC_register_l, datal);

	output_high(direcao);
	delay_ms(1);
	printf(" TBC Register fase %c=%lx,%lx ", fase, read_cs5460(TBC_register, fase), aux_cs5460_l);
	aux_cs5460_l = read_cs5460(E_register,fase);	
	printf("Energia:%lu, %Lx\r\n", aux_cs5460_l, aux_cs5460_l);
	printf("\r\n");
	delay_ms(2);
	output_low(direcao);
}


void grava_pulse_rate_cs5460a(char fase)
{

	write_cs5460(pulse_rate, aux_cs5460_l, fase);

	aux_cs5460_l = read_cs5460(pulse_rate, fase);
	write_byte(ee_pulse_rate_h, datah);
	write_byte(ee_pulse_rate_m, datam);
	write_byte(ee_pulse_rate_l, datal);

	output_high(direcao);
	delay_ms(1);
	aux_cs5460_l = read_cs5460(pulse_rate, fase);
	printf("Power: Pulse_rate:%Lx",aux_cs5460_l);
	printf("\r\n");
	delay_ms(2);
	output_low(direcao);
}

void inc_pulse_rate_cs5460a(char fase)
{
	aux_cs5460_l = read_cs5460(pulse_rate, fase);
	aux_cs5460_l++;
	grava_pulse_rate_cs5460a(fase);
}

void dec_pulse_rate_cs5460a(char fase)
{
	aux_cs5460_l = read_cs5460(pulse_rate, fase);
	aux_cs5460_l--;
	grava_pulse_rate_cs5460a(fase);
}


void grava_ganho_v_cs5460a(char fase)
{
	write_cs5460(V_gain, aux_cs5460_l, fase);

	aux_cs5460_l = read_cs5460(V_gain, fase);
	if (fase == 'R')
		{
		write_byte(ee_V_gain_h_R, datah);
		write_byte(ee_V_gain_m_R, datam);
		write_byte(ee_V_gain_l_R, datal);
		}
	else if (fase == 'S')
		{
		write_byte(ee_V_gain_h_S, datah);
		write_byte(ee_V_gain_m_S, datam);
		write_byte(ee_V_gain_l_S, datal);
		}
	else
		{
		write_byte(ee_V_gain_h_T, datah);
		write_byte(ee_V_gain_m_T, datam);
		write_byte(ee_V_gain_l_T, datal);
		}
}

void inc_ganho_v_cs5460a(char fase)
{
	aux_cs5460_l = read_cs5460(V_gain, fase);
	aux_cs5460_l++;
	grava_ganho_v_cs5460a(fase);

}

void dec_ganho_v_cs5460a(char fase)
{
	aux_cs5460_l = read_cs5460(V_gain, fase);
	aux_cs5460_l--;
	grava_ganho_v_cs5460a(fase);
}

void grava_ganho_i_cs5460a(char fase)
{
	write_cs5460(I_gain, aux_cs5460_l, fase);

	aux_cs5460_l = read_cs5460(I_gain, fase);
	if (fase == 'R')
		{
		write_byte(ee_I_gain_h_R, datah);
		write_byte(ee_I_gain_m_R, datam);
		write_byte(ee_I_gain_l_R, datal);
		}
	else if (fase == 'S')
		{
		write_byte(ee_I_gain_h_S, datah);
		write_byte(ee_I_gain_m_S, datam);
		write_byte(ee_I_gain_l_S, datal);
		}
	else
		{
		write_byte(ee_I_gain_h_T, datah);
		write_byte(ee_I_gain_m_T, datam);
		write_byte(ee_I_gain_l_T, datal);
		}
}

void inc_ganho_i_cs5460a(char fase)
{
	aux_cs5460_l = read_cs5460(I_gain, fase);
	aux_cs5460_l++;
	grava_ganho_v_cs5460a(fase);

}

void dec_ganho_i_cs5460a(char fase)
{
	aux_cs5460_l = read_cs5460(I_gain, fase);
	aux_cs5460_l--;
	grava_ganho_v_cs5460a(fase);
}
