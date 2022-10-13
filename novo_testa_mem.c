//***********************************************************************
// Empresa: Sultech Sitemas Eletrônicos									*
// Projeto: ST8500C														*
// Modulo: Teste da Menória												*
// Função: Testar o funcionamento da memória.							*
// Responsável: Ângelo													*
// Inicio: 03/10/2022													*
//***********************************************************************

int8 x;
const char valor_t[2]= {'A','5'};
char retorno=0;
int32 fim_mem = 0x0FFFFF;
int32 end_mem = 0;

void teste_memoria(void){
	nro_erro_mem =0;
	testando_memoria =1;
	mensagem(1,175);
	mensagem(2,176);
		for (x=0; x<2; x++){
		apaga_memoria();
		lcd_gotoxy(14,1);
		wr_lcd(1,valor_t[x]);
		for(end_mem=0;end_mem<fim_mem+1;end_mem++){
			write_byte_flash(end_mem,valor_t[x]);
			displaypl(22,end_mem,7);
		}
		for(end_mem=0;end_mem<fim_mem+1;end_mem++){
			retorno=read_byte_flash(end_mem);
			if(retorno!= valor_t[x])
				nro_erro_mem++;
			displaypl(22,end_mem,7);
		}
	}
	apaga_memoria();
	mensagem(2,177);
	displaypl(22,nro_erro_mem,7);	
	testando_memoria = 0;
}