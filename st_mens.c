/* mensagem.c
	area para definicao de mensagens
*/

/*                    1234567890123456789012345678901 */
//							   
//code char mdata[] ="ST5030T-V1.04@0001.A-2711030922";

const char csultech[30] = "Sultech";

const char cdata[]=__DATE__;			//10
const char ctime[]=__TIME__;			//9

#if (com_rep == true)
		const char cequipo[22] = "ST8500C-V2.XX@0001.A";
#endif
#if (com_tc == true)
		const char cequipo[22] = "ST8500C-V2.XX@0001.B";

#endif




