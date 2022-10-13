//***********************************************************************
// Empresa: Sultech Sitemas Eletrônicos									*
// Projeto: ST5200T														*
// Modulo: Teste da Menória												*
// Função: Testar o fncionamento da memória.							*
// Responsável: Rafael Calai								*
// Inicio: 19/09/2016													*
//***********************************************************************

void GravarRegistrosTest(void){
	char err_grava;
	int32 aux_l1;
	nro_erro_mem = 0;
	testando_memoria = 1;
	
	mensagem(1,175);
	mensagem(2,176);
	apaga_memoria();

	for (aux_w1 = 0; aux_w1 < limite_registros/7; aux_w1++){	 
		aux_l1 = (int32)(aux_w1);						// Buscamos a posição de registro.
		aux_l1 = (int32)(aux_l1 * 224);					// Convertemos em posição de memória da flash externa.
		for (aux_b1 = 0; aux_b1 < 224; aux_b1++){		// Salvando no buffer da flash.	
			write_byte_flash(aux_l1++,'A');
		}
		lcd_gotoxy(14,2);
		wr_lcd(1,'A');
		aux_f1 = aux_l1/7905;
		displaypl(22,aux_f1,3);
	}
	for (aux_w1 = 0; aux_w1 < limite_registros/7; aux_w1++){	 
		aux_l1 = (int32)(aux_w1);						// Buscamos a posição de registro.
		aux_l1 = (int32)(aux_l1 * 224);					// Convertemos em posição de memória da flash externa.
		for (aux_b1 = 0; aux_b1 < 224; aux_b1++){		// Lendo no buffer da flash.
			err_grava = read_byte_flash(aux_l1++);			
			if (err_grava != 'A')
				nro_erro_mem++;	
		}															
		nro_erro_mem2 = nro_erro_mem/7905;
		displaypl(30,nro_erro_mem2,3);	//62
		aux_f1 = aux_l1/7905;
		displaypl(22,aux_f1,3);
	}
	mensagem(2,176);
	apaga_memoria();
	for (aux_w1 = 0; aux_w1 < limite_registros/7; aux_w1++){	 
		aux_l1 = (int32)(aux_w1);						// Buscamos a posição de registro.
		aux_l1 = (int32)(aux_l1 * 224);					// Convertemos em posição de memória da flash externa.
		for (aux_b1 = 0; aux_b1 < 224; aux_b1++){		// Salvando no buffer da flash.	
			write_byte_flash(aux_l1++,'5');
		}
		lcd_gotoxy(14,2);
		wr_lcd(1,'5');
		aux_f1 = aux_l1/7905;
		displaypl(22,aux_f1,3);
	}
	for (aux_w1 = 0; aux_w1 < limite_registros/7; aux_w1++){	 
		aux_l1 = (int32)(aux_w1);						// Buscamos a posição de registro.
		aux_l1 = (int32)(aux_l1 * 224);					// Convertemos em posição de memória da flash externa.
		for (aux_b1 = 0; aux_b1 < 224; aux_b1++){		// Lendo no buffer da flash.
			err_grava = read_byte_flash(aux_l1++);			
			if (err_grava != '5')
				nro_erro_mem++;	
		}															
		nro_erro_mem2 = nro_erro_mem/7905;
		displaypl(30,nro_erro_mem2,3);	//62
		aux_f1 = aux_l1/7905;
		displaypl(22,aux_f1,3);
	}
	apaga_memoria();
	mensagem(1,177);
	testando_memoria = 0;
}




	
