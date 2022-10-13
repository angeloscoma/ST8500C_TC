//////////////////////////////////////////////////////////////////////////
////                               DS1302.C                           ////
////                     Driver for Real Time Clock                   ////
////                                                                  ////
////  rtc_init()                                   Call after power up////
////                                                                  ////
////  rtc_set_datetime(day,mth,year,dow,hour,min)  Set the date/time  ////
////                                                                  ////
////  rtc_get_date(day,mth,year,dow)               Get the date       ////
////                                                                  ////
////  rtc_get_time(hr,min,sec)                     Get the time       ////
////                                                                  ////
////  rtc_write_nvr(address,data1)                  Write to NVR       ////
////                                                                  ////
////  data1 = rtc_read_nvr(address)                 Read from NVR      ////
////                                                                  ////
//////////////////////////////////////////////////////////////////////////
////        (C) Copyright 1996,1997 Custom Computer Services            ////
//// This source code may only be used by licensed users of the CCS C   ////
//// compiler.  This source code may only be distributed to other       ////
//// licensed users of the CCS C compiler.  No other use, reproduction  ////
//// or distribution is permitted without written permission.           ////
//// Derivative programs created using this software in object code     ////
//// form are not restricted in any way.                                ////
////////////////////////////////////////////////////////////////////////////



//equates de controle do relógio
#define ds_controle_w 	0x8e		//10001110b
#define ds_bateria_ini	0xa5		//10100101b
#define ds_libera		0x00		//00000000b
#define ds_proteje		0x80		//10000000b

//;VARIAVEIS DE LEITURA E ESCRITA NO RELOGIO/dallas
//; VARIAVEIS NO CHIP dallas/RELO

#define ds_seg			0x00
#define ds_min			0x01
#define ds_hor			0x02
#define ds_dia			0x03
#define ds_mes			0x04
#define ds_dia_semana	0x05
#define ds_ano			0x06
#define ds_controle		0x07
#define ds_bateria		0x08

// Variáveis na RAM do Relógio

#define ds_ptr_regs			0x0A	//Expandindo tamanho para aumentar  o número de registros possíveis. 4 bytes
#define ds_ptr_regs_high	0x0C	
#define ds_ptr_ocor			0x0E
#define ds_ptr_cht			0x10
//							0x12
#define ds_banco_leitura	0x13
#define ds_banco_escrita	0x14
#define ds_min_funciona		0x15
#define ds_dia_old      	0x16
#define ds_mes_old    		0x17
#define ds_ano_old			0x18
#define ds_hora_old			0x19
#define	ds_minuto_old		0x1a
#define ds_segundo_old		0x1b

//	#define ds_ptr_regs			0x0a
//	#define ds_ptr_ocor			0x0c		
//	#define ds_ptr_cht			0x0e
//	#define ds_banco_leitura	0x10
//	#define ds_banco_escrita	0x11
//	#define ds_min_funciona		0x12
//
//	#define ds_dia_old      0x16	//equ	22
//	#define ds_mes_old    	0x17	//equ	23
//	#define ds_ano_old		0x18	//equ	24
//	#define ds_hora_old		0x19	//equ	25
//	#define	ds_minuto_old	0x1a	//equ	26
//	#define ds_segundo_old	0x1b	//equ	27


char dec_bcd(char dado)
{
	char x;
	x = dado;
	dado = dado / 10;
	swap(dado);
	x = x % 10;
	dado = x + dado;
	return(dado);
}

char bcd_dec(char dado)
{
	char x;
	x = dado;
	dado = dado & 0b11110000;
	swap(dado);
	dado = dado * 10;
	x = x & 0b00001111;
	dado = x + dado;
	return(dado);
}

void write_ds1302_byte(byte cmd)
{
	char aux_b1;
   output_low(RTC_IO);
   output_low(RTC_SCLK);
   for(aux_b1=0; aux_b1<=7; ++aux_b1)
   		{
      	output_bit(RTC_IO, shift_right(&cmd,1,0) );
      	output_high(RTC_SCLK);
      	delay_cycles(2);
      	output_low(RTC_SCLK);
   		}
}

void write_ds1302(byte cmd, byte data1)
{
	#if (st5x == true)
		#if (cpu_rev1011 == true)
			spi_ocupada = true;
		#endif
	#endif

   output_high(RTC_RST);
   write_ds1302_byte(cmd);
   write_ds1302_byte(data1);
   output_low(RTC_RST);
	#if (st5x == true)
		#if (cpu_rev1011 == true)
			spi_ocupada = false;
		#endif
	#endif
   
}

byte read_ds1302(byte cmd)
{
   char data1, aux_b2;
   data1 = 0;
	#if (st5x == true)
		#if (cpu_rev1011 == true)
			spi_ocupada = true;
		#endif
	#endif
   
   output_high(RTC_RST);
   write_ds1302_byte(cmd);

   output_float(RTC_IO);
   for(aux_b2=0; aux_b2<=7; ++aux_b2)
   		{
      	shift_right(&data1,1,input(RTC_IO));
      	output_high(RTC_SCLK);
      	delay_cycles(2);
      	output_low(RTC_SCLK);
   		}
   output_low(RTC_RST);
	#if (st5x == true)
		#if (cpu_rev1011 == true)
			spi_ocupada = false;
		#endif
	#endif

   return(data1);
}

void rtc_init()
{
	#if (st5x == true)
		#if (cpu_rev1011 == true)
			spi_ocupada = true;
		#endif
	#endif
   output_low(RTC_RST);
   output_low(RTC_SCLK);
   write_ds1302(ds_controle_w,0);
   delay_ms(1);
   write_ds1302(0x90,0xa6);
   delay_ms(1);
   data1 = read_ds1302(0x81);
   if((data1 & 0x80)!=0)
   		{
     	write_ds1302(0x80,0);
     	}
}

void rtc_set_datetime()
{
   write_ds1302(0x86,dec_bcd(dia));
   write_ds1302(0x88,dec_bcd(mes));
   write_ds1302(0x8c,dec_bcd(ano));
   write_ds1302(0x84,dec_bcd(hora));
   write_ds1302(0x82,dec_bcd(minuto));
   write_ds1302(0x80,dec_bcd(segundo));
}

void rtc_get_date()
{
   dia = bcd_dec(read_ds1302(0x87));
   mes = bcd_dec(read_ds1302(0x89));
   ano = bcd_dec(read_ds1302(0x8d));
}


void rtc_get_time()
{
   	segundo = bcd_dec(read_ds1302(0x81));
   	minuto = bcd_dec(read_ds1302(0x83));
	hora = bcd_dec(read_ds1302(0x85));
}

void le_calend(void)
{
   char dado;
   segundo = bcd_dec(read_ds1302(0x81));
   dado = bcd_dec(read_ds1302(0x83));
   if (dado != minuto)
		{
   		minuto = dado;
   		viroumin = 1;
		dado = bcd_dec(read_ds1302(0x85));
		if (dado != hora)
			{
			hora = dado;
			virouhora = true;
   			dado = bcd_dec(read_ds1302(0x87));
   			if (dado != dia)
   				{
	   			dia = dado;
	   			viroudia = 1;
				dado = bcd_dec(read_ds1302(0x89));
				if (dado != mes)
					{
					viroumes = 1;
					mes = dado;
					ano = bcd_dec(read_ds1302(0x8d));
					}
				}
			}
		}
}

void rtc_write_nvr(byte address,byte data1)
{
   address = address << 1;
   write_ds1302((address | 0xc0),data1);
}

byte rtc_read_nvr(byte address) 
{
  	address = address << 1;
    return(read_ds1302( (address | 0xc1) ));
}


int16 read_word_nvr(char adress)
{
	data1_int = rtc_read_nvr(adress++); 
	data1 = rtc_read_nvr(adress);
	data1_int = (data1_int << 8 ) | data1;
	return (data1_int);
}

void write_word_nvr(char adress,int16 dado)
{
	char xdado;
	xdado = dado >> 8;	
	rtc_write_nvr(adress++, xdado);
	xdado = dado;
	rtc_write_nvr(adress, xdado);
}

int16 read_byte_nvr(char adress)
{
	return (rtc_read_nvr(adress));
}

void write_byte_nvr(char adress,char dado)
{
	rtc_write_nvr(adress, dado);
}


void wr_segundo_old(void)
{
	rtc_write_nvr(ds_segundo_old,segundo);
}

void wr_tempo_old(void)
{
	rtc_write_nvr(ds_dia_old,dia);
	rtc_write_nvr(ds_mes_old,mes);
	rtc_write_nvr(ds_ano_old,ano);
	rtc_write_nvr(ds_hora_old,hora);
	rtc_write_nvr(ds_minuto_old,minuto);
	
}

