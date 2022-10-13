/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: ADE7754.H                                                      *
; Funcao: MODULO DEFINICAO DE ENDERCOS DO ADE7754 						 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 18/02/2003                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */
#include "ade7754.h"

signed char off_set_freq;

void le_senoides(void);


char modo_oper;

char passo_ade7754;
char temperatura;
char acao_ade7754;
word reg_cfnum;
word reg_cfdem;


word status_ade7754;
word rstatus_ade7754;

int32 LAENERGY_R;
int32 AENERGY_R;
int32 RAENERGY_R;
int32 LAENERGY_S;
int32 AENERGY_S;
int32 RAENERGY_S;
int32 LAENERGY_T;
int32 AENERGY_T;
int32 RAENERGY_T;

signed word off_set_a_ade7754;
signed word off_set_b_ade7754;
signed word off_set_c_ade7754;
signed word ganho_a_ade7754;
signed word ganho_b_ade7754;
signed word ganho_c_ade7754;
word periodo_ade7754;
int32 tensao_a_rms;
int32 tensao_b_rms;
int32 tensao_c_rms;
int32 corrente_a_rms;
int32 corrente_b_rms;
int32 corrente_c_rms;
char mode_ade7754;
char wmode_ade7754;
word mascara_ade7754;
word ciclos;


short calibrando;


char  le_byte_ade7754(char);
word  le_word_ade7754(char);
int32 le_long_ade7754(char);
word  le_xlong_ade7754(char);
void  salva_byte_ade7754(char, char);
void  salva_word_ade7754(char, word);



void le_variaveis_ade7754(void);
void inicializa_ade7754(void);
void le_offsets_ade7754(void);
void inc_off_set_v(void);
void dec_off_set_v(void);
void inc_ganho_v(void);
void dec_ganho_v(void);
void le_ganhos_ade7754(void);
void inc_off_set_freq(void);
void dec_off_set_freq(void);
void auto_zero(void);
void calibra_wh_r(void);
void calibra_wh_s(void);
void calibra_wh_t(void);


void le_variaveis_ade7754(void)
{
	le_offsets_ade7754();
	le_ganhos_ade7754();
}



void config_ade7754(void)
{
	output_high(ADE7754_CS);
	output_low(ADE7754_RST);
	output_high(ADE7754_RST);

	delay_us(20);

	salva_byte_ade7754(OPMODE, MODO_OPER_ADE7754);
	salva_byte_ade7754(GAIN, GAIN_PGAS);

	salva_byte_ade7754(MMODE, 0x70 );
	salva_word_ade7754(MASK, MASK_ADE7754);

 	rstatus_ade7754 = le_word_ade7754(RSTATUS);


	return;

	salva_byte_ade7754(OPMODE, MODO_OPER_ADE7754);
	salva_byte_ade7754(GAIN, GAIN_PGAS);


/*
	if (fase = 'R')
		{
		calibra_wh_r();
		}
	else if (fase == 'S')
		{
		calibra_wh_s();
		}
	else if (fase == 'S')
		{
		calibra_wh_t();
		}
	else
		{
*/		

// set fase A para acumulador de energia ativa de linha
	salva_byte_ade7754(WATMODE, 0x24);

/*		
		addr_ad = MMODE;
		data_ad1 = MMODE_ADE7754;
		salva_byte_ade7754();
	
		addr_ad = WATMODE;
		data_ad1 = WATMODE_ADE7754;
		salva_byte_ade7754();
*/	
		salva_byte_ade7754(VAMODE, 0x24);
/*
		}
*/

 	salva_word_ade7754(LINECYCLE, 30);

 	salva_word_ade7754(CFNUM, 0x01);

 	salva_word_ade7754(CFDEN, 0x3f);

 	salva_word_ade7754(WDIV, 0x01);

 	salva_word_ade7754(VADIV, 0x01);


/* recarrega parametros */
		
 	off_set_a_ade7754 = read_word(ee_off_set_vrms_a);
 	salva_word_ade7754(AVRMSOS, off_set_a_ade7754);

 	off_set_b_ade7754 = read_word(ee_off_set_vrms_b);
 	salva_word_ade7754(BVRMSOS, off_set_b_ade7754);

 	off_set_c_ade7754 = read_word(ee_off_set_vrms_c);
 	salva_word_ade7754(CVRMSOS, off_set_c_ade7754);

 	ganho_a_ade7754 = read_word(ee_ganho_a_ade7754);
 	salva_word_ade7754(AVGAIN, ganho_a_ade7754);
 	ganho_b_ade7754 = read_word(ee_ganho_b_ade7754);
 	salva_word_ade7754(BVGAIN, ganho_b_ade7754);
 	ganho_c_ade7754 = read_word(ee_ganho_c_ade7754);
 	salva_word_ade7754(CVGAIN, ganho_c_ade7754);

 	status_ade7754 = le_word_ade7754(STATUS);
 	rstatus_ade7754 = le_word_ade7754(RSTATUS);
	mode_ade7754 = le_byte_ade7754(MMODE);
	wmode_ade7754 = le_byte_ade7754(WATMODE);
	mascara_ade7754 = le_word_ade7754(MASK);

}


void le_offsets_ade7754(void)
{
 	off_set_a_ade7754 = le_word_ade7754(AVRMSOS);
 	off_set_b_ade7754 = le_word_ade7754(BVRMSOS);
 	off_set_c_ade7754 = le_word_ade7754(CVRMSOS);

}

void le_ganhos_ade7754(void)
{

 	ganho_a_ade7754 = le_word_ade7754(AVGAIN);
 	ganho_b_ade7754 = le_word_ade7754(BVGAIN);
 	ganho_c_ade7754 = le_word_ade7754(CVGAIN);

}

void inc_off_set_v(void)
{
 	off_set_a_ade7754 = le_word_ade7754(AVRMSOS);
 	off_set_a_ade7754++;
 	salva_word_ade7754(AVRMSOS, off_set_a_ade7754);
	write_word(ee_off_set_vrms_a, off_set_a_ade7754);
 	

}

void dec_off_set_v(void)
{
 	off_set_a_ade7754 = le_word_ade7754(AVRMSOS);
 	off_set_a_ade7754--;
 	salva_word_ade7754(AVRMSOS, off_set_a_ade7754);
	write_word(ee_off_set_vrms_a, off_set_a_ade7754);

}

void inc_ganho_v(void)
{
 	ganho_a_ade7754 = le_word_ade7754(AVGAIN);
 	ganho_a_ade7754++;
 	salva_word_ade7754(AVGAIN, ganho_a_ade7754);
	write_word( ee_ganho_a_ade7754, ganho_a_ade7754);
}

void dec_ganho_v(void)
{
 	ganho_a_ade7754 = le_word_ade7754(AVGAIN);
 	ganho_a_ade7754--;
 	salva_word_ade7754(AVGAIN, ganho_a_ade7754);
	write_word(ee_ganho_a_ade7754, ganho_a_ade7754);
}


void inc_off_set_freq(void)
{

 	off_set_freq = read_byte(ee_off_set_freq);
 	off_set_freq++;
	write_byte(ee_off_set_freq, off_set_freq);

}

void dec_off_set_freq(void)
{
	
 	off_set_freq = read_byte(ee_off_set_freq);
 	off_set_freq--;
	write_byte(ee_off_set_freq, off_set_freq);

}

void auto_zero(void)
{

 	ganho_a_ade7754 = 0;
 	salva_word_ade7754(AVGAIN, 0);
 	ganho_b_ade7754 = 0;
 	salva_word_ade7754(BVGAIN, 0);
 	ganho_c_ade7754 = 0;
 	salva_word_ade7754(CVGAIN, 0);
	off_set_a_ade7754 = 0;
 	salva_word_ade7754(AVRMSOS, 0);
	off_set_b_ade7754 = 0;
 	salva_word_ade7754(BVRMSOS, 0);
	off_set_c_ade7754 = 0;
 	salva_word_ade7754(CVRMSOS, 0);

	write_word(ee_off_set_vrms_a, 0);
	write_word(ee_off_set_vrms_b, 0);
	write_word(ee_off_set_vrms_c, 0);
	write_word(ee_ganho_a_ade7754, 0);
	write_word(ee_ganho_b_ade7754, 0);
	write_word(ee_ganho_c_ade7754, 0);

}



void calibra_wh_r(void)
{
/* set zero crossing fase A para acumuladro de energia ativa de fase  e periodo de medicao da fase A 
		addr 0x0b = 0x10 */
	salva_byte_ade7754( MMODE, 0x10);

/* set fase A para acumulador de energia ativa de linha
		addr 0x0d = 0x024 */
	salva_byte_ade7754(WATMODE, 0x24);

/* a fase A deve ter tensao e corrente  as demais sem tensao e corrente */

/* aguardar a interupcao */
	mode_ade7754 = le_byte_ade7754(MMODE);

	wmode_ade7754 = le_byte_ade7754(WATMODE);

	calibrando = 1;

}

void calibra_wh_s(void)
{
/* set zero crossing fase A para acumuladro de energia ativa de fase  e periodo de medicao da fase A 
		addr 0x0b = 0x10 */

	salva_byte_ade7754( MMODE, 0x21);

/* set fase A para acumulador de energia ativa de linha
		addr 0x0d = 0x012 */
	salva_byte_ade7754(WATMODE, 0x12);

/* a fase A deve ter tensao e corrente  as demais sem tensao e corrente */

/* aguardar a interupcao */
	mode_ade7754 = le_byte_ade7754(MMODE);

	wmode_ade7754 = le_byte_ade7754(WATMODE);

	calibrando = 1;

}
void calibra_wh_t(void)
{
/* set zero crossing fase A para acumuladro de energia ativa de fase  e periodo de medicao da fase A 
		addr 0x0b = 0x10 */
	salva_byte_ade7754( MMODE, 0x42);

/* set fase A para acumulador de energia ativa de linha
		addr 0x0d = 0x024 */
	salva_byte_ade7754(WATMODE, 0x09);

/* a fase A deve ter tensao e corrente  as demais sem tensao e corrente */

/* aguardar a interupcao */
	mode_ade7754 = le_byte_ade7754(MMODE);

	wmode_ade7754 = le_byte_ade7754(WATMODE);

	calibrando = 1;

}


word status_old;
void tx_ade7754(void)
{
	float aux_f1;

	return;

	if (status_old != status_ade7754)
		{
		output_high(direcao);
		delay_ms(2);
		printf(":%lu", status_ade7754);
		printf(",%lu", status_old);
	
		printf("  T:");
		printf("%u", (temperatura - 70));
		aux_f1 = temperatura - 70;
		printf(" %2.2f Graus", aux_f1 / 4);
	
		printf("  F:");
		printf("%lu", periodo_ade7754);
		printf(",%u", frequencia);
		aux_f1 = frequencia;
		printf(" %2.2f Hz", aux_f1 / 4);

		printf("\r\n");
	
		printf("  R-");
		printf("T:%lu", tensao_a_rms);
		printf(" ,%lu", tensao_r);
		aux_f1 = tensao_r;
		printf(" ,%3.2f", aux_f1 / 64);
		printf(" C:%lu", corrente_a_rms);
		printf(" ,%lu", corrente_r);
		aux_f1 = corrente_r;
		printf(" ,%5.2f", aux_f1 / 8);
		aux_f1 = pot_aparente_r;
		printf(" Kva:%4.2f", aux_f1 / 32);
		aux_f1 = pot_ativa_r;
		printf(" Kw:%4.2f", aux_f1 / 32);

//		printf(" ,%lu", LAENERGY_R);
//		printf(" ,%lu", AENERGY_R);
		printf(" ,%lu", RAENERGY_R);

		printf("\r\n");

;	
		printf("  S-");
		printf("T:%lu", tensao_b_rms);
		printf(" ,%lu", tensao_s);
		aux_f1 = tensao_s;
		printf(" ,%3.2f", aux_f1 / 64);
		printf(" C:%lu", corrente_b_rms);
		printf(" ,%lu", corrente_s);
		aux_f1 = corrente_s;
		printf(" ,%5.2f", aux_f1 / 8);
		aux_f1 = pot_aparente_s;
		printf(" Kva:%4.2f", aux_f1 / 32);
		aux_f1 = pot_ativa_s;
		printf(" Kw:%4.2f", aux_f1 / 32);

//		printf(" ,%lu", LAENERGY_S);
//		printf(" ,%lu", AENERGY_S);
		printf(" ,%lu", RAENERGY_S);

		printf("\r\n");
;	
	
		printf("  T-");
		printf("T:%lu", tensao_c_rms);
		printf(" ,%lu", tensao_t);
		aux_f1 = tensao_t;
		printf(" ,%3.2f", aux_f1 / 64);
		printf(" C:%lu", corrente_c_rms);
		printf(" ,%lu", corrente_t);
		aux_f1 = corrente_t;
		printf(" ,%5.2f", aux_f1 / 8);
		aux_f1 = pot_aparente_t;
		printf(" Kva:%4.2f", aux_f1 / 32);
		aux_f1 = pot_ativa_t;
		printf(" Kw:%4.2f", aux_f1 / 32);

//		printf(" ,%lu", LAENERGY_T);
//		printf(" ,%lu", AENERGY_T);
		printf(" ,%lu", RAENERGY_T);

		printf("\r\n");

;	

		printf("  ;%u", mode_ade7754);
		printf(",%u", wmode_ade7754);
		printf(",%u", passo_ade7754);
		printf(",%lu", ciclos);
	
		printf("\r\n");

		delay_ms(2);
		output_low(direcao);
		status_old = status_ade7754;

		}

}



void inc_fase_fp_7754(char fase)
{
	if (fase == 'R')
		{
		fase_r = read_byte(ee_fase_r);
		fase_r++;
		fase_r = fase_r & 0b00011111;
		write_byte(ee_fase_r, fase_r);

		}
	if (fase == 'S')
		{
		}
	else
		{
		}

	acao_ade7754 = 0;

}

void dec_fase_fp_7754(char fase)
{
	if (fase == 'R')
		{
		fase_r = read_byte(ee_fase_r);
		fase_r--;
		fase_r = fase_r & 0b00011111;
		write_byte(ee_fase_r, fase_r);
		}
	if (fase == 'S')
		{
		}
	else
		{
		}

	acao_ade7754 = 0;

}



void inc_ganho_tensao_7754(char fase)
{
	if (fase == 'R')
		{
		os_ten_r1 = read_word(ee_os_ten_r1);
		os_ten_r1++;
		write_word(ee_os_ten_r1, os_ten_r1);
		}
	if (fase == 'S')
		{
		}
	else
		{
		}
	acao_ade7754 = 0;
}
void dec_ganho_tensao_7754(char fase)
{
	if (fase == 'R')
		{
		os_ten_r1 = read_word(ee_os_ten_r1);
		os_ten_r1--;
		write_word(ee_os_ten_r1, os_ten_r1);
		}
	if (fase == 'S')
		{
		}
	else
		{
		}
}


