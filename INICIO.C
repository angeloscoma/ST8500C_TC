/* INICIALIZAÇÃO BÁSICA PARA MICROCONTROLADOR MICROCHIP */


#include <18F6720.H>						// DEFINE O MICROCONTROLADOR
#device *=16 ADC=8							// DEFINE TIPO DE MICRO  E RETORNO DA ROTINA DO AD- 8(BITS) PARA O PROJETO DIGIDRIVE  PODE IR ATÉ 10BITS
#use delay(clock=24000000, restart_wdt)		// DEFINE O USO E O CLOCK PARA A ROTINA DE DELAY
#fuses HS,WDT128,NOPROTECT,PUT,BROWNOUT, NOLVP	// DEFINE OS FUXIVEIS DE CONFIGIRAÇÃO DO MICRO, TEMO QUE DAR UMA OLHADA NA DOCUMENTAÇÃO PARA VER O QUE TEM QUE SER 												//FEITO PARA DOWNLOAD DE PROGRAMA VIA SERIAL.


#use rs232(baud=19200, xmit=PIN_C6, rcv=PIN_C7, restart_wdt, parity=N, bits=8, errors, stream = SERIAL1)  

#use rs232(baud=19200, xmit=PIN_G1, rcv=PIN_G2, restart_wdt, parity=N, bits=8, errors, stream = SERIAL2)  

#define INTS_PER_SECOND (100)
	
#define valor_timer1  (65536 - 30000)			// 10 milisegundo
									// (0,010/(8/24000000)) = 30000
									// calculo: 65536-30000
#use standard (B)
#use standard (C)
#use standard (D)
#use standard (E)
#use standard (G)

//#include gerais


// define pinagem
#define cs_rel	pin_c0
#define clk		pin_c3
#define so		pin_c4
#define s1		pin_c5

#define men1	pin_e0
#define men2	pin_e1
#define alarme	pin_e2
#define bloqueio pin_e3


#define direcao1_485	pin_??
#define direcao2_485	pin_??


#zero_ram
void main(void)
{
	// INICIALIZA I/O
				//   76543210
		set_tris_b(0b11111111);
		set_tris_c(0b10100110);
		set_tris_d(0b11111111);
		set_tris_e(0x11110000);
		set_tris_f(0b11111111);
		set_tris_g(0b11111000);


// define funcionamento do temporizador 1 
	setup_timer_1(T1_INTERNAL|T1_DIV_BY_2);
	set_timer1(valor_timer1);
	enable_interrupts(INT_TIMER1);

// define funcionamento do temporizador 1   - SEM FOR USADO
	setup_timer_3(T1_INTERNAL|T3_DIV_BY_2);
	set_timer3(valor_timer3_2_60HZ);
	enable_interrupts(INT_TIMER3);


// define funcionamento da uart 1 e 2
	set_uart_speed(19200, SERIAL1);
	set_uart_speed(19200, SERIAL2);
	
// habilita interrupções serial  
//( neste caso só estamos habilitando a recepção, mas pode ser habilitada tambem a transmissão em outra interrupção
	enable_interrupts(INT_RDA);
	enable_interrupts(INT_RDA2);
	
// habilita interrupções externas
	ext_int_edge(0,H_TO_L);
	enable_interrupts(INT_EXT);
	ext_int_edge(1,H_TO_L);
	enable_interrupts(INT_EXT1);
	ext_int_edge(2,H_TO_L);
	enable_interrupts(INT_EXT2);
	ext_int_edge(3,H_TO_L);
	enable_interrupts(INT_EXT3);
	

// define funcionamento da watchdog 
	setup_wdt(WDT_ON);
	restart_wdt();
	
// define o funcionamento do AD
	setup_adc_ports(ALL_ANALOG | VSS_VDD);
	setup_adc(ADC_CLOCK_INTERNAL);

// libera todas a interrupções
	enable_interrupts(GLOBAL);


	while(1)
		{
		restart_wdt();
		}
	
}






//  INTERRUPÇÕES
#INT_TIMER1 // FAST  							//a cada ???? ms
void temporizador(void)
{   
	set_timer1(valor_timer1);
}



#INT_TIMER3  // FAST //a cada ???? ms
void temporizador3(void)
{   
	set_timer3(valor_timer3);

}




#INT_RDA
void serial_1(void)
{
	buf_rx[ptrrx++] = getc(SERIAL1);   
	numbrx++;
	if (ptrrx >= TAM_RX)
		{
		ptrrx = 0;
		numbrx = 0;
		}
}

#INT_RDA2
void serial_2(void)
{
	buf_rx2[ptrrx2++] = getc(SERIAL2);   
	numbrx2++;
	if (ptrrx2 >= TAM_RX2)
		{
		ptrrx2 = 0;
		numbrx2 = 0;
		}
}


#INT_EXT 
void int_externa0(void)
{
}

#INT_EXT1 
void int_externa1(void)
{
}

#INT_EXT2 
void int_externa2(void)
{
}

#INT_EXT3 
void int_externa3(void)
{
}



