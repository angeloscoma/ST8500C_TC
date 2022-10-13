/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ST_INTS                                                        *
; Funcao: MODULO Interrupçoes 					  						 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 06/06/2003                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/

#if (st8500c == true)
	#include "st8500c_timer1.c"
#else
	#include "timer1.c"
#endif
#if (sames_9904 == true)
	#include "timer3_sames.c"
	#include "int_ext_sames.c"
#else
	#if (st9230r == true)
		#if (epcos == true)
			#include "timer3_epcos.c"
		#else
			#include "timer3.c"
		#endif
	#elif (st8500c == true)
		#include "st8500c_timer3.c"
	#else
		#include "timer3.c"
	#endif
	#include "int_ext.c"
#endif	
#if (home_system == false)
	#include "serial.c"
#endif


