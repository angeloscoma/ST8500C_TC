//-------------------------------------------------
// EEProm routines
//-------------------------------------------------


int16	EEPCrc;
int   EEP_Off;
/*
void EEP_Crc(int8 ch)
{
	int8 i;
	int16 ch16;

	ch16 = ch;
	ch16 = ch << 8;
	EEPCrc = EEPCrc ^ ch16;
	for (i = 0 ; i < 8 ; ++i)
	{
		if (EEPCrc & 0x8000)
		{
			EEPCrc = EEPCrc << 1;
			EEPCrc = EEPCrc ^ 0x1021;
		}
		else
			EEPCrc = EEPCrc << 1;
	}
}
*/

/*************************************/
void calc_eep_crc()
{
   	int  data;
	int8 i,j;
	int16 ch16;

	EEPCrc = 0xFFFF;
   	for( j=EEP_CRCHIGH+1; j<EEP_LASTPAR; j++ )
   		{
      	ch16=data=read_eeprom(EEP_Off+j);

   		ch16 = data << 8;
   		EEPCrc = EEPCrc ^ ch16;
   		for (i = 0 ; i < 8 ; ++i)
   			{
   			if (EEPCrc & 0x8000)
   				{
   				EEPCrc = EEPCrc << 1;
   				EEPCrc = EEPCrc ^ 0x1021;
   				}
   			else
   				{
   				EEPCrc = EEPCrc << 1;
   				}
   			}
   		}
}


/*************************************/
void my_write_eeprom( int adr, int b )
{
   write_eeprom( adr, b );
#if EEP_OFFSET > 0
      write_eeprom( EEP_OFFSET+adr, b );
#endif
   restart_wdt();
}

/*************************************/
void write_eep_crc(int1 block)
{
   	if (!block)
   		{
	  	EEP_Off=0;
	  	}
   	else 
   		{
	   	EEP_Off=EEP_OFFSET;
	   	}

   calc_eep_crc();
   my_write_eeprom( EEP_Off+EEP_CRCLOW,   EEPCrc&0xff );
   my_write_eeprom( EEP_Off+EEP_CRCHIGH, EEPCrc>>8 );
}

/*************************************/
void write_par( int adr, int b )
{
   my_write_eeprom( adr, b );
   write_eep_crc(0);
#if EEP_OFFSET > 0
      write_eep_crc(1);
#endif
}

/*************************************/
int test_eep(int1 block)
{
   int16  crc;

   if (!block)  EEP_Off=0;
   else EEP_Off=EEP_OFFSET;

   calc_eep_crc();
   crc=read_eeprom( EEP_Off );
   crc+=((int16) read_eeprom( EEP_Off+1 )<<8);
   return( crc == EEPCrc );
}
