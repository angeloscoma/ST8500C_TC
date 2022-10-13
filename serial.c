//***********************************************************************
// Empresa: Sultech Sistemas Eletrônicos								*
// Modulo: Inicial														*
// Função: Definição das Interrupções Seriais							*
// Responsável: Edison Valério Nunes Junior								*
// Modificado: Edison Valério Nunes Junior								*
// Inicio: 02/07/2012													*
// Revisão: Edison Valério Nunes Junior									*
//***********************************************************************

#INT_RDA
void serial(void){
	led_rx = 1;
	comuni_busy = 5;
	time_out_modbus = 4;
	buf_rx[ptrrx++] = getc(modbus);   
	numbrx++;
	if(numbrx == 8){
		aux_b1 = 0;
	}
	if (ptrrx >= TAM_RX){
		ptrrx = 0;
		numbrx = 0;
	}
}

#if (com_rep == true)
	#INT_RDA2
	void serial2(void){
	 	buf_rec_rep[nbyte_rep++] = getc(rep);
		led_rx = ~led_rx;
		time_out_rec_rep = 3;		//15;

		if(nbyte_rep > 55){
			aux_b1 = 0;
		}
	}
#endif

