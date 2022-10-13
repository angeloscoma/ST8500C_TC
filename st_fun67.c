/*;******************************************************************
; Empresa: SULTECH SISTEMAS ELETRONICOS								*
; Modulo: ST_COMU													*
; Funcao: MODULO gerencialde comunicacao rs232/485					*
; Responsavel: VAGNER SANTOS										*
; Modificado ; VAGNER SANTOS										*
; Inicio: 30/08/2000												*
; Revisao: RENGAV ARIERREF SOD SOTNAS								*
;********************************************************************/
  

void modbus_funcao67(void)
{
	erro_mod = 0;
	qerro_mod = 0;
	le_endereco();
	le_nro_pontos();
	buf_tx[ptrtx++] = nro_pontos_modbus;	/* monta nro de pontos */;

	if (addr_regs_modbus == 0)
		{
		erro_mod = 1;
		qerro_mod = 2;
		}
	if (erro_mod == 0)
		{
		existe = 0;
		for (aux_b1 = 0; aux_b1 < nro_pontos_modbus; aux_b1++)
 			{
	 		if (erro_mod == 1)
	 			{
		 		break;
		 		}
		 	//le_byte_regs_modbus();
		 	switch(addr_regs_modbus)
		 		{
			 	case 58:	//Corrente Primaria Parte Alta. Total nao pode exceder 4 digitos.
			 		{
				 	data1_int = valor_tc >> 8;
				 	break;
				 	}
			 	case 59:	//Corrente Primaria Parte Baixa. Total nao pode exceder 4 digitos.
			 		{
//				 	data1_int = 5;
				 	data1_int = valor_tc;
				 	break;
				 	}
			 	case 60:	//Expoente de base dois. A corrente primaria e multiplicada por este valor para exibicao no aplicativo.
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 61:	//Tensao Primaria Parte Alta. Total nao pode exceder 4 digitos.
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 62:	//Tensao Primaria Parte Baixa. Total nao pode exceder 4 digitos.
			 		{
				 	data1_int = ten_nomi;
				 	break;
				 	}
			 	case 63:	//Expoente de base dois. A tensao primaria e multiplicada por este valor para exibicao no aplicativo. 
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 64:	//Numeros de casas decimais para corrente. Para exibicao em "Ler Configuracao".
			 		{
				 	if (valor_tc > 999)
				 		{
					 	data1_int = 0;
						}
				 	else if (valor_tc > 99)
				 		{
					 	data1_int = 1;
						}
				 	else if (valor_tc > 9)
				 		{
					 	data1_int = 2;
						}
					else
						{
						data1_int = 3;
						}
				 	break;
				 	}
			 	case 65:	//Numeros de casas decimais para tensao. Para exibicao em "Ler Configuracao".
			 		{
				 	data1_int = 1;
				 	break;
				 	}
			 	case 66:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 67:
			 		{
				 	data1_int = 95;
				 	break;
				 	}
			 	case 68:
			 		{
				 	data1_int = 95;
				 	break;
				 	}
			 	case 69:	//Corrente Secundaria Parte Alta. Em "Caracteristicas do Instrumento".
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 70:	//Corrente Secundaria Parte Baixa. Em "Caracteristicas do Instrumento".
			 		{
				 	data1_int = 5;
				 	break;
				 	}
			 	case 71:	//Expoente de base dois. A corrente secundaria e multiplicada por este valor para exibicao.
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 72:	//Tensao Secundaria Parte Alta
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 73:	//Tensao Secundaria Parte Baixa
			 		{
				 	data1_int = ten_nomi;
				 	break;
				 	}
			 	case 74:	//Expoente de base dois. A tensao secundaria e multiplicada por este valor para exibicao no aplicativo.
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 75:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 76:	//Campo de Energia:	1 = 999,999 kWh; 2 = 9999,99 kWh; 3 = 99999,9 kWh; 4 = 999999 kWh;
			 		{						//	5 = 9999,99 MWh; 6 = 99999,9 MWh; 7 = 999999 MWh; 8 = 9999,99 GWh;
				 	data1_int = 4;
				 	break;
				 	}
			 	case 77:	//Numero do Produto Parte Alta
			 		{
				 	data1_int = 19;
				 	break;
				 	}
			 	case 78:	//Numero do Produto Parte Baixa
			 		{
				 	data1_int = 136;
				 	break;
				 	}
			 	case 79:	//Tensao de Calibracao Parte Alta.
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 80:	//Tensao de Calibracao Parte Baixa.
			 		{
				 	data1_int = ten_nomi;
				 	break;
				 	}
			 	case 81:	//Expoente de base dois. A tensao de calibracao e multiplicada por este valor para exibicao.
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 82:	//Valor do divisor da taxa de comunicacao - Baud Rate
			 		{
				 	data1_int = 1;
				 	break;
				 	}
			 	case 83:	//Endereco na Rede Modbus
			 		{
				 	data1_int = endereco;
				 	break;
				 	}
			 	case 84:	//Numero de Serie Parte Alta
			 		{
					buf_tmp[0] = read_byte(ee_nro_1);
					buf_tmp[1] = read_byte(ee_nro_2);
					buf_tmp[2] = read_byte(ee_nro_3);
					buf_tmp[3] = read_byte(ee_nro_4);
					ascbin1();
					data1_int = data1_int >> 8;
				 	break;
				 	}
			 	case 85:	//Numero de Serie Parte Baixa
			 		{
					buf_tmp[0] = read_byte(ee_nro_1);
					buf_tmp[1] = read_byte(ee_nro_2);
					buf_tmp[2] = read_byte(ee_nro_3);
					buf_tmp[3] = read_byte(ee_nro_4);
					ascbin1();
				 	break;
				 	}
			 	case 86:	//Ano de Fabricacao Parte Alta
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 87:	//Ano de Fabricacao Parte Baixa
			 		{
				 	data1_int = ((cdata[7] -'0') * 10) + (cdata[8]-'0');
				 	break;
				 	}
			 	case 88:	//Mes de Fabricacao
			 		{
					if (cdata[3] == 'a') 
						{ 
						if (cdata[4] == 'b') 
							{ 
							data1_int = 4; 
							}
						else
							{ 
							data1_int = 8; 
							} 
						}
					else if (cdata[3] == 'd') 
						{
						data1_int = 12; 
						} 
					else if (cdata[3] == 'f') 
						{
						data1_int = 2; 
						}
					else if (cdata[3] == 'j') 
						{
						if (cdata[4] == 'a') 
							{
							data1_int = 1; 
							}
						else if (cdata[5] == 'n') 
							{
							data1_int = 6; 
							}
						else
							{
							data1_int = 7; 
							}
						}
					else if (cdata[3] == 'm') 
						{ 
						if(cdata[5] == 'r') 
							{
							data1_int = 3; 
							}
						else 
							{
							data1_int = 5; 
							}
						}
					else if (cdata[3] == 's') 
						{
						data1_int = 9; 
						}
					else if (cdata[3] == 'o') 
						{
						data1_int = 10; 
						}
					else 
						{
						data1_int = 11; 
						}
				 	break;
				 	}
			 	case 89:
			 		{
				 	data1_int = 3;
				 	break;
				 	}
			 	case 90:
			 		{
				 	data1_int = 42;
				 	break;
				 	}
			 	case 91:
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 92:
			 		{
				 	data1_int = 91;
				 	break;
				 	}
			 	case 93:
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 94:
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 95:	//Baud Rate parte alta
			 		{
				 	data1_int = ((baud_rate / 10) >> 8);
				 	break;
				 	}
			 	case 96:	//Baud Rate parte baixa
			 		{
				 	data1_int = (baud_rate / 10);
				 	break;
				 	}
			 	case 97:
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 98:
			 		{
				 	data1_int = 6;
				 	break;
				 	}
			 	case 99:
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 100:
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 101:
			 		{
				 	data1_int = 1;
				 	break;
				 	}
			 	case 102:
			 		{
				 	data1_int = 129;
				 	break;
				 	}
			 	case 103:	//Valor do Pulso Wh Parte Alta.
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 104:	//Valor do Pulso Wh Parte Baixa.
			 		{
				 	data1_int = 1;
				 	break;
				 	}
			 	case 105:	//Expoente de base dois. O Valor do Pulso Wh e multiplicado por este valor para exibicao.
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 106:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 107:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 108:	//Tipo de Rede:		1 = Trifasica Equilibrada com Neutro 3 TC's;
			 		{						//	2 = Trifasica Desequilibrada sem Neutro 2 TC's
				 	data1_int = 1;			//	3 = Trifasica Equilibrada 1 TC's
				 	break;					//	4 = Monofasica
				 	}
			 	case 109:
			 		{
				 	data1_int = 1;
				 	break;
				 	}
			 	case 110:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 111:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 112:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 113:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 114:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 115:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 116:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 117:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 118:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 119:
			 		{
				 	data1_int = 255;	//supondo
				 	break;
				 	}
			 	case 120:
			 		{
				 	data1_int = 255;	//supondo
				 	break;
				 	}
			 	case 121:
			 		{
				 	data1_int = 255;	//supondo
				 	break;
				 	}
			 	case 122:
			 		{
				 	data1_int = 255;	//supondo
				 	break;
				 	}
			 	case 123:
			 		{
				 	data1_int = 2;
				 	break;
				 	}
			 	case 124:
			 		{
				 	data1_int = 2;
				 	break;
				 	}
			 	case 125:
			 		{
				 	data1_int = 2;
				 	break;
				 	}
			 	case 126:
			 		{
				 	data1_int = 5;
				 	break;
				 	}
			 	case 127:
			 		{
				 	data1_int = 6;
				 	break;
				 	}
			 	case 128:
			 		{
				 	data1_int = 7;
				 	break;
				 	}
			 	case 129:
			 		{
				 	data1_int = 1;
				 	break;
				 	}
			 	case 130:
			 		{
				 	data1_int = 2;
				 	break;
				 	}
			 	case 131:
			 		{
				 	data1_int = 3;
				 	break;
				 	}
			 	case 132:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 133:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 134:
			 		{
				 	data1_int = 84;
				 	break;
				 	}
			 	case 135:
			 		{
				 	data1_int = 16;
				 	break;
				 	}
			 	case 136:
			 		{
				 	data1_int = 6;
				 	break;
				 	}
/*			 	case 137:
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 138:
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 139:
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 140:
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 141:
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 142:
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 143:
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 144:
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 145:
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 146:
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 147:
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 148:
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 149:
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 150:
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 151:
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 152:
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 153:
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 154:
			 		{
				 	data1_int = 0;
				 	break;
				 	}*/
			 	case 155:	//Tempo de Integracao Parte Alta. Calculo: Valor Transmitido = (tempo_integracao * 2) * 60 segundos)
			 		{
				 	data1_int = intervalo_integra;
				 	data1_int = make8((data1_int * 120), 1);
				 	break;
				 	}
			 	case 156:	//Tempo de Integracao Parte Baixa.
			 		{
				 	data1_int = intervalo_integra;
				 	data1_int = (data1_int * 120);
				 	break;
				 	}
			 	case 157:	//Expoente de base dois. O tempo de integracao e multiplicado por este valor para exibicao.
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 158:
			 		{
				 	data1_int = 85;
				 	break;
				 	}
			 	case 159:
			 		{
				 	data1_int = 170;
				 	break;
				 	}
			 	case 160:
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 161:
			 		{
				 	data1_int = 1;
				 	break;
				 	}
			 	case 162:
			 		{
				 	data1_int = 5;
				 	break;
				 	}
			 	case 163:
			 		{
				 	data1_int = 31;
				 	break;
				 	}
			 	case 164:
			 		{
				 	data1_int = 20;
				 	break;
				 	}
			 	case 165:
			 		{
				 	data1_int = 9;
				 	break;
				 	}
			 	case 166:
			 		{
				 	data1_int = 15;
				 	break;
				 	}
			 	case 167:
			 		{
				 	data1_int = 24;
				 	break;
				 	}
			 	case 168:
			 		{
				 	data1_int = 34;
				 	break;
				 	}
			 	case 169:
			 		{
				 	data1_int = 35;
				 	break;
				 	}
			 	case 170:
			 		{
				 	data1_int = 39;
				 	break;
				 	}
			 	case 171:
			 		{
				 	data1_int = 2;
				 	break;
				 	}
			 	case 172:
			 		{
				 	data1_int = 6;
				 	break;
				 	}
			 	case 173:
			 		{
				 	data1_int = 28;
				 	break;
				 	}
			 	case 174:
			 		{
				 	data1_int = 21;
				 	break;
				 	}
			 	case 175:
			 		{
				 	data1_int = 10;
				 	break;
				 	}
			 	case 176:
			 		{
				 	data1_int = 16;
				 	break;
				 	}
			 	case 177:
			 		{
				 	data1_int = 27;
				 	break;
				 	}
			 	case 178:
			 		{
				 	data1_int = 14;
				 	break;
				 	}
			 	case 179:
			 		{
				 	data1_int = 25;
				 	break;
				 	}
			 	case 180:
			 		{
				 	data1_int = 26;
				 	break;
				 	}
			 	case 181:
			 		{
				 	data1_int = 3;
				 	break;
				 	}
			 	case 182:
			 		{
				 	data1_int = 7;
				 	break;
				 	}
			 	case 183:
			 		{
				 	data1_int = 29;
				 	break;
				 	}
			 	case 184:
			 		{
				 	data1_int = 22;
				 	break;
				 	}
			 	case 185:
			 		{
				 	data1_int = 11;
				 	break;
				 	}
			 	case 186:
			 		{
				 	data1_int = 17;
				 	break;
				 	}
			 	case 187:
			 		{
				 	data1_int = 19;
				 	break;
				 	}
			 	case 188:
			 		{
				 	data1_int = 32;
				 	break;
				 	}
			 	case 189:
			 		{
				 	data1_int = 33;
				 	break;
				 	}
			 	case 190:
			 		{
				 	data1_int = 40;
				 	break;
				 	}
			 	case 191:
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 192:
			 		{
				 	data1_int = 15;
				 	break;
				 	}
			 	case 193:
			 		{
				 	data1_int = 32;
				 	break;
				 	}
			 	case 194:
			 		{
				 	data1_int = 32;
				 	break;
				 	}
			 	case 195:
			 		{
				 	data1_int = 32;
				 	break;
				 	}
			 	case 196:
			 		{
				 	data1_int = 70;
				 	break;
				 	}
			 	case 197:
			 		{
				 	data1_int = 82;
				 	break;
				 	}
			 	case 198:
			 		{
				 	data1_int = 69;
				 	break;
				 	}
			 	case 199:
			 		{
				 	data1_int = 81;
				 	break;
				 	}
			 	case 200:
			 		{
				 	data1_int = 85;
				 	break;
				 	}
			 	case 201:
			 		{
				 	data1_int = 69;
				 	break;
				 	}
			 	case 202:
			 		{
				 	data1_int = 78;
				 	break;
				 	}
			 	case 203:
			 		{
				 	data1_int = 67;
				 	break;
				 	}
			 	case 204:
			 		{
				 	data1_int = 73;
				 	break;
				 	}
			 	case 205:
			 		{
				 	data1_int = 65;
				 	break;
				 	}
			 	case 206:
			 		{
				 	data1_int = 32;
				 	break;
				 	}
			 	case 207:
			 		{
				 	data1_int = 32;
				 	break;
				 	}
			 	case 208:
			 		{
				 	data1_int = 32;
				 	break;
				 	}
			 	case 209:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 210:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 211:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 212:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 213:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 214:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 215:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 216:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 217:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 218:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 219:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 220:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 221:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 222:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 223:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 224:
			 		{
				 	data1_int = 233;
				 	break;
				 	}
			 	case 225:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 226:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 227:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 228:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 229:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 230:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 231:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 232:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 233:
			 		{
				 	data1_int = 128;
				 	break;
				 	}
			 	case 234:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 235:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 236:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 237:
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 238:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 239:	//Indicacao de Saidas Analogicas: 1 = Sem Saidas; 2 = 4 Saidas de Tensao; 3 = 4 Saidas de Corrente
			 		{
				 	data1_int = 1;
				 	break;
				 	}
			 	case 240:
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 241:
			 		{
				 	data1_int = 1;
				 	break;
				 	}
			 	case 242:
			 		{
				 	data1_int = 255;
				 	break;
				 	}
			 	case 243:
			 		{
				 	data1_int = 85;
				 	break;
				 	}
			 	case 244:
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 245:
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 246:
			 		{
				 	data1_int = 1;
				 	break;
				 	}
			 	case 247:
			 		{
				 	data1_int = 0;
				 	break;
				 	}
			 	case 248:
			 		{
				 	data1_int = 0;
				 	break;
				 	}
				default:
					{
					data1_int = 0;
					}
				}
		 	addr_regs_modbus++; 
		 	data1 = data1_int;
			poe_byte_buftx();
 			}
	 	}
 	if (erro_mod == 1)
 		{
		buf_tx[1] = buf_tx[1] | 0x80;
		buf_tx[2] = qerro_mod;
		ptrtx = 3;
 		}
 	
	crc_modbus =  crc16(buf_tx, ptrtx) ;
	data1_int = crc_modbus;
	poe_word_buftx();
	dispara_tx();
}


void modbus_funcao66(void)
{
	erro_mod = 0;
	qerro_mod = 0;
	le_endereco();
	le_nro_pontos();
	buf_tx[ptrtx++] = nro_pontos_modbus;	/* monta nro de pontos */;

	if (addr_regs_modbus == 0)
		{
		erro_mod = 1;
		qerro_mod = 2;
		}
	if (erro_mod == 0)
		{
		existe = 0;
		for (aux_b1 = 0; aux_b1 < nro_pontos_modbus; aux_b1++)
 			{
	 		if (erro_mod == 1)
	 			{
		 		break;
		 		}
		 	switch(addr_regs_modbus)
		 		{
			 	case 2903:
			 		{
				 	data1_int = 3;
				 	break;
				 	}
			 	case 2904:
			 		{
				 	data1_int = 2;
				 	break;
				 	}
			 	case 2905:
			 		{
				 	data1_int = 2;
				 	break;
				 	}
			 	case 2906:
			 		{
				 	data1_int = 2;
				 	break;
				 	}
			 	case 2907:
			 		{
				 	data1_int = 5;
				 	break;
				 	}
			 	case 2908:
			 		{
				 	data1_int = 6;
				 	break;
				 	}
			 	case 2909:
			 		{
				 	data1_int = 7;
				 	break;
				 	}
			 	case 2910:
			 		{
				 	data1_int = 31;
				 	break;
				 	}
			 	case 2911:
			 		{
				 	data1_int = 28;
				 	break;
				 	}
			 	case 2912:
			 		{
				 	data1_int = 3;
				 	break;
				 	}
			 	default:
			 		{
				 	data1_int = 0;
				 	}
			 	}
		 	addr_regs_modbus++; 
		 	data1 = data1_int;
			poe_byte_buftx();
 			}
	 	}

 	if (erro_mod == 1)
 		{
		buf_tx[1] = buf_tx[1] | 0x80;
		buf_tx[2] = qerro_mod;
		ptrtx = 3;
 		}
 	
	crc_modbus =  crc16(buf_tx, ptrtx) ;
	data1_int = crc_modbus;
	poe_word_buftx();
	dispara_tx();
}

	 
