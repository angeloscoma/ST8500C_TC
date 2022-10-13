/* mensagem.c
	area para definicao de mensagens
*/

/*                    1234567890123456789012345678901 */
//							   
//code char mdata[] ="ST5030T-V1.99@0001.A-2711030922";

const char csultech[30] = "Sultech-By Vagner Santos-2004";

const char cdata[]=__DATE__;			//10
const char ctime[]=__TIME__;			//9

#if (st5000t == true)                // 1234567890123456
	#if (home_system == true)
			const char cequipo[22] = "ST5000T-V3.99@0001.H";
	#else
		#if (chip_cs5460a == true)
			const char cequipo[22] = "ST5000T-V3.99@0003.B";
		#endif	
		#if (ad_microchip == true)
			#if (st5000c_rev12 == true)
				const char cequipo[22] = "ST5000T-V3.99@0001.E";
			#else
				const char cequipo[22] = "ST5000T-V3.99@0003.C";
			#endif
		#endif	
		#if (ade7754 == true)
			const char cequipo[22] = "ST5000T-V3.99@0003.D";
		#endif	
	#endif
#endif

#if (st5030t == true)                // 1234567890123456
	#if (chip_cs5460a == true)
		const char cequipo[22] = "ST5030T-V3.99@0003.B";
	#endif	
	#if (ad_microchip == true)
		#if (st5000c_rev12 == true)
			const char cequipo[22] = "ST5000T-V3.99@0001.E";
		#else
			#if (TECNOFLUX == TRUE)
				const char cequipo[22] = "ST5030T-V3.99@0003.T";
			#else
				const char cequipo[22] = "ST5030T-V3.99@0003.C";
			#endif
		#endif
	#endif	
	#if (ade7754 == true)
		const char cequipo[22] = "ST5030T-V3.99@0003.D";
	#endif	
	#if (sames_9904 == true)
		const char cequipo[22] = "ST5030T-V3.99@0003.E";
	#endif	
#endif

#if (st5330t == true)
	const char cequipo[22] = "ST5330T-V1.99@0001.A";
#endif	

#if (st9100r == true)
	const char cequipo[22] = "ST9100R-V5.99@0001.B";
#endif	

#if (st9400r == true)
	const char cequipo[22] = "ST9400R-V2.99@0001.B";
#endif	

#if (st9430r == true)
	const char cequipo[22] = "ST9430R-V2.99@0001.B";
#endif	

#if (st9600r == true)
	#if (st9600e == true)
		const char cequipo[22] = "ST9600R-V4.99@0100.E";
	#else
		#if (chip_cs5460a == true)	//012345678901234567890
			const char cequipo[22] = "ST9600R-V2.99@0104.A";
		#else
			#if ((tc_fixo == true) && (se_com_flex == false))
				const char cequipo[22] = "ST9600R-V3.99@0100.A";
			#elif (se_com_flex == true)
				const char cequipo[22] = "ST9600R-V4.99@0100.A";
			#else
				const char cequipo[22] = "ST9600R-V1.99@0100.A";
			#endif
		#endif
	#endif		
#endif	

#if (st_prog == true)
	const char cequipo[22] = "STPROGR-V1.99@0001.A";
#endif	

#if (st8100C == true)
	#if (bancos_12 == true)
		const char cequipo[22] = "ST8100C-V5.99@0101.H";
	#else
		const char cequipo[22] = "ST8100C-V5.99@0001.G";
	#endif
#endif	
#if (st8200C == true)
	#if (bancos_12 == true)
		const char cequipo[22] = "ST8200C-V5.99@0101.H";
	#else
		const char cequipo[22] = "ST8200C-V5.99@0001.G";
	#endif
#endif	
#if (st8300C == true)
	#if (controle_por_fase == true)
		const char cequipo[22] = "ST8300C-V5.99@0001.I";
	#else
		const char cequipo[22] = "ST8300C-V5.99@0001.G";
	#endif
#endif	
#if (st8500C == true)
	#if (com_rep == true))
		#if (CCA == true)
			const char cequipo[22] = "SD-1600-V1.99@0001.A";
		#else
			const char cequipo[22] = "ST8500C-V1.99@0001.A";
		#endif
	#endif
	#if (com_tc == true))
		const char cequipo[22] = "ST8500C-V1.99@0001.B";
	#endif
#endif	
#if (st9200r == true)
	const char cequipo[22] = "ST9200R-V5.99@0001.N";
#endif	
#if (st9230r == true)
	const char cequipo[22] = "ST9230R-V5.99@0001.N";
#endif	





