/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: st95ROTA                                                        *
; Funcao: MODULO ROTINAS             									 *
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 30/08/2000                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;**********************************************************************  */
  
#include "st95vars.h"
 #include "st95e2p.h"
#include "c:\arch\io51.h"
#include "c:\arch\math.h"
#include "st95port.h"
#include "st95time.h"


/* Rot_Comum de integracao do Demanda TCS  */
/*#include "bit.h"*/
/*#include "def.h"*/

/* variaveis não volateis com copia na e2prom ou no relogio */
/* variaveis NO INIT */
xdata unsigned int	fat_conv_ativa;
xdata unsigned int	fat_conv_reativa_ind;
xdata unsigned int	fat_conv_reativa_cap;

xdata unsigned char tipo_fp;
xdata unsigned char tipo_fp_men;
xdata unsigned char tipo_fp_men_ant;
xdata unsigned char ctl_on;
xdata unsigned char em_alerta;
xdata int tmp_falta;
xdata int tmp_espera;

xdata unsigned int	int_ativa[15 + 1];
xdata unsigned int	int_reativa[15 + 1];
xdata unsigned char	char_reativa[15 + 1];

xdata unsigned char	erro_rep;


xdata unsigned char	dia_ini_per_seco;
xdata unsigned char	mes_ini_per_seco;
xdata unsigned char	dia_fim_per_seco;
xdata unsigned char	mes_fim_per_seco;

xdata unsigned char	hora_ini_ponta_seca;		/* ainda nao usados */
xdata unsigned char	min_ini_ponta_seca;         /*  "				*/
xdata unsigned char	hora_ini_ponta_umida;       /*  "               */
xdata unsigned char	min_ini_ponta_umida;        /* idem 			*/

xdata unsigned int  demanda_maxima;
xdata unsigned int	max_dem_ponta_seca;
xdata unsigned int	max_dem_ponta_umida;
xdata unsigned int	max_dem_fora_ponta_seca;
xdata unsigned int	max_dem_fora_ponta_umida;

xdata unsigned char	fat_pot_prog;
xdata unsigned char	fat_pot_off;
xdata unsigned char	periodo;
xdata unsigned char	periodo_ant;
xdata unsigned char	media_fat_potencia;
xdata unsigned char	media_fat_potencia_ant;
xdata unsigned char	fat_potencia;

xdata unsigned int	maior_dem_ati_ponta;
xdata unsigned int	maior_dem_rea_ponta;
xdata unsigned int	maior_dem_ati_fora_ponta;
xdata unsigned int	maior_dem_rea_fora_ponta;
xdata unsigned int	maior_dem_ati_ponta_ant;
xdata unsigned int	maior_dem_rea_ponta_ant;
xdata unsigned int	maior_dem_ati_fora_ponta_ant;
xdata unsigned int	maior_dem_rea_fora_ponta_ant;
xdata unsigned int	dem_ativa;
xdata unsigned int	dem_reativa;
xdata unsigned int	dem_projetada;
xdata unsigned int  dem_proj_reat;
xdata unsigned long	consumo_ati;
xdata unsigned long	consumo_rea;
xdata unsigned long	consumo_ati_ant;
xdata unsigned long	consumo_rea_ant;


/* variaveis voláteis */

xdata unsigned char	fatura_rep;
xdata unsigned char	fim_interv_reat_rep;
xdata unsigned char	tarif_cap_rep;
xdata unsigned char	tarif_ind_rep;
xdata unsigned char	posto_tarif_rep;
xdata unsigned char	tipo_tarif_rep;
xdata unsigned int	seg_falt_rep;
xdata unsigned int	puls_c1_rep;
xdata unsigned int	puls_c2_rep;
xdata unsigned char mes_ant;

xdata unsigned int	puls_c1_rep_ant;
xdata unsigned int	puls_c2_rep_ant;
xdata unsigned char	num_int_ant;
xdata unsigned char	num_int;

xdata unsigned int	e_ativa;
xdata unsigned int	e_reativa;
xdata unsigned int	e_ativa_ant;	/* Utilizado no le paral.   */
xdata unsigned int	e_reativa_ant;


xdata unsigned char	timer_integra;

xdata unsigned char	nao_inicializado;
xdata unsigned char ponta_ck;
xdata unsigned char	dia_ult_esc;
xdata unsigned char	mes_ult_esc;
xdata unsigned char	ano_ult_esc;
xdata unsigned char	hora_ult_esc;
xdata unsigned char	min_ult_esc;


xdata unsigned long	val_ativa;
xdata unsigned long val_reativa;
xdata unsigned long val_rea_ind;
xdata unsigned long val_rea_cap;
xdata unsigned int	pont_dados;

xdata unsigned long fp_ativa;
xdata unsigned long fp_reativa;



extern void tx_lfcr(void); 


extern void cont_carga(unsigned char, unsigned int);
extern void liga_prox_cap(void);
extern void desliga_prox_cap(void);

extern  void    desl_alarme(unsigned char);

extern void wrword_dallas_ram(void);
extern void rdword_dallas_ram(void);
extern void salva_byte_e2prom(void);
extern void salva_word_e2prom(void);
extern void salva_long_e2prom(void);
extern void grava_registros(void);

void trat_rep(void);
unsigned char tst_msg_rep(void);
void desmonta_msg_rep(void);
void trat_msg_rep(void);

			
void	ve_integra(void);
void    faz_int_minuto(unsigned char);
void    reposicao(void);
void    Pega_maior_dem(void);
void    fecha_periodo(void);
void    verifik_ponta(void);
void    verifik_carga(void);
unsigned char   calc_fat_pot(unsigned long ativa, unsigned long reativa);
void salva_15_em_15(void);



extern unsigned int tx_xx(unsigned char,unsigned int);
extern unsigned int tx_xxx(unsigned char,unsigned int);
extern unsigned int tx_xxxxx(unsigned int,unsigned int);
extern unsigned int tx_lqx(unsigned long,unsigned char,unsigned char,unsigned char,unsigned int);
extern void calc_check_tx(void);


/* Trat. mens. rx p/ serial do REP.  DEMANDA TCS */



void trat_rep()
{
/*
	if (rec_rep_ok) 
		{		/* seta o bit quando do rx de 8 bytes */
		rec_rep_ok = 0;
		if (tst_msg_rep() == V) 
			{
			desmonta_msg_rep();
			trat_msg_rep();
	    	}
		}
*/
		
}

xdata unsigned char check_rep;

unsigned char tst_msg_rep()
{
	y = 0;	/* y=teste */
	for (x=0; x<8; x++) 
		{
		y ^= buf_rec_rep[x];
		}
	check_rep = y;
	if (y != 0xff)
		{
		return(V);
/*	    return(F);*/
	    }
	return(V);
}

void desmonta_msg_rep()
{
	fatura_rep          = (buf_rec_rep[1] & 0x10) >> 4;
	fim_interv_reat_rep = (buf_rec_rep[1] & 0x20) >> 5;
	tarif_cap_rep       = (buf_rec_rep[1] & 0x40) >> 6;
	tarif_ind_rep       = (buf_rec_rep[1] & 0x80) >> 7;
	posto_tarif_rep     = (buf_rec_rep[2] & 0x0f);
	tipo_tarif_rep      = (buf_rec_rep[2] & 0xf0) >> 4;
	seg_falt_rep = (unsigned int)buf_rec_rep[0] | ((unsigned int)(buf_rec_rep[1] & 0x0f) << 8);
	puls_c1_rep  = (unsigned int)buf_rec_rep[3] | ((unsigned int)(buf_rec_rep[4] & 0x7f) << 8);
	puls_c2_rep  = (unsigned int)buf_rec_rep[5] | ((unsigned int)(buf_rec_rep[6] & 0x7f) << 8);
}


void trat_msg_rep()
{
	
	if (mes != mes_ant && fatura_rep == 1) 
		{
	    mes_ant = mes;
	    reposicao();
		}
	switch (posto_tarif_rep) 
		{
	    case 0x01:
			periodo = EM_PONTA;
			break;
	    case 0x02:
			periodo = FORA_DE_PONTA;
			break;
		}
		
	i = 900 - seg_falt_rep;
	num_int = i / 60;
	
	timer_integra = num_int;

	if (num_int != num_int_ant) 
		{
	    if (puls_c1_rep > puls_c1_rep_ant)
	    	{
			e_ativa = puls_c1_rep - puls_c1_rep_ant;
			}
		else 
			{
			e_ativa = puls_c1_rep;
			}
		puls_c1_rep_ant = puls_c1_rep;
		if (puls_c2_rep > puls_c2_rep_ant)
			{
			e_reativa = puls_c2_rep - puls_c2_rep_ant;
			}
		else
			{
			e_reativa = puls_c2_rep;
			}
		puls_c2_rep_ant = puls_c2_rep;
		faz_int_minuto(num_int);
		num_int_ant = num_int;
		}
		
		
}


void ve_integra()
{
	if (timer_integra > (16)) 
		{
		erro_rep |= ER_PULSO_M_16;
		}
	timer_integra = 0;
}



void faz_int_minuto(unsigned char parte)
{
	xdata unsigned long extra2;
	xdata unsigned long extra1; 

	atualizar=1;
	/* Se o timer ja passou dos 15 minutos e ainda nao veio o pulso
	   de integracao, come‡a a fazer as proximas integra‡oes.  */
	if (parte > 14) 
		{
	    parte -= 15;
	    }


    int_ativa[parte] = e_ativa;
    
	addr = ee_int_ativa+(parte*2);
	data1_int =  e_ativa;
	salva_word_e2prom();
    
	int_reativa[parte] = e_reativa;

	addr = ee_int_reativa+(parte*2);
	data1_int =  e_reativa;
	salva_word_e2prom();
	
	char_reativa[parte] = IND;
	e_reativa = 0; 
	e_ativa = 0;
	val_ativa = 0L; 
	val_reativa = 0L;
	val_rea_ind = 0L; 
	val_rea_cap = 0L;
	for (x = 0; x < parte; x++) 
		{
		 val_ativa += int_ativa[x];
		 if (char_reativa[x] == CAP) 
		 	{
			 val_rea_cap += int_reativa[x];
			}
		 else 
			{
			 val_rea_ind += int_reativa[x];
			}
		}
		
	if (val_rea_ind > val_rea_cap) 
		{
		val_reativa = (val_rea_ind - val_rea_cap);
		tipo_fp = IND;
		}
	else 
		{
		if (val_rea_ind < val_rea_cap) 
			{
			val_reativa = (val_rea_cap - val_rea_ind);
			tipo_fp = CAP;
			}
		else 
			{ 
			val_reativa = 0L;
			tipo_fp = UNIT;
			}
		}
	val_ativa += (int_ativa[parte] * (NUM_INT - parte));
	if (char_reativa[parte] == CAP) 
		{
		val_rea_cap += (int_reativa[parte] * (NUM_INT - parte));
		}
	else 
		{
		val_rea_ind += (int_reativa[parte] * (NUM_INT - parte));
		}
	extra1 = (int_reativa[parte] * (NUM_INT - parte));
	if (char_reativa[parte] == tipo_fp) 
		{
		val_reativa += extra1;
		}
	else 
		{
		if (val_reativa > extra1) 
			{
			val_reativa -= extra1;
			}
		else 
			{
			if (val_reativa < extra1) 
				{
				val_reativa = (extra1 - val_reativa);
				tipo_fp = char_reativa[parte];
				}
			else 
				{
				val_reativa = 0L;
				tipo_fp = UNIT;
				}
			}
		}
	dem_projetada = (unsigned int)(((long)val_ativa * fat_conv_ativa) / 1000L);
	if (tipo_fp == IND) 
		{
		dem_proj_reat = (unsigned int)((val_reativa * fat_conv_reativa_ind) / 1000L);
		}
	else
		{
		dem_proj_reat = (unsigned int)((val_reativa * fat_conv_reativa_cap) / 1000L);
		}
							/* Calculo do fator potencia */
	extra2 = int_reativa[parte] * 100; /* elevo n§ de pulsos em 100 Vzz */
	if (tipo_fp == IND) 
		{
		fp_reativa = (((long)extra2 * fat_conv_reativa_ind) / 1000L);
		}
	else 
		{
		fp_reativa = (((long)extra2 * fat_conv_reativa_cap) / 1000L);
		}
	fp_ativa = (((long)int_ativa[parte] * fat_conv_ativa) / 10L); 
	/* estou fazendo o calculo 100 x acima p/ nao perder as casas decimais */ 
	if (int_reativa[parte]==0)
		{
		fator_pot = 100;
		}
	else
		{
		fator_pot = calc_fat_pot(fp_ativa, fp_reativa);
		}
	ctl_on=1;
	if (ctl_on==1) 
		{ /* Se o controle estiver habilitado */
		if (tipo_fp == IND) 
			{
			if (fator_pot >= fat_pot_off)
				{  /* So desliga cap. se maior */
				desliga_prox_cap();
				}
			else 
				{
				if (fator_pot < fat_pot_prog)  /* So liga cap. se menor */ 
					{
					liga_prox_cap();
					}
				}
			}
		else 
			{
			desliga_prox_cap();
			}
		verifik_carga(); /* liga ou desliga as cargas em funcao da demanda. */
		}
	else if (fator_pot > 70) 
		{
		ctl_on = 1;				/* Habilita novamente o controle do sistema */ 
		em_alerta = 90;
		tmp_falta = tmp_espera * 60;
		}


 		
	ptrtx=0;
/*	for (x=0; x<15;x++)
		{
		ptrtx=tx_xxxxx(int_ativa[x],ptrtx);
		}
	tx_lfcr();	
	for (x=0; x<15;x++)
		{
		ptrtx=tx_xxxxx(int_reativa[x],ptrtx);
		}
	tx_lfcr();	*/
	buf_tx[ptrtx++]='P';
	ptrtx=tx_xx(parte,ptrtx);
	ptrtx=tx_xxx(fator_pot,ptrtx);
	ptrtx=tx_lqx(val_ativa,7,0,0,ptrtx);
	ptrtx=tx_lqx(val_reativa,7,0,0,ptrtx);
	ptrtx=tx_lqx(consumo_ati,10,0,0,ptrtx);
	ptrtx=tx_lqx(consumo_rea,10,0,0,ptrtx);
	tx_aciona=0;
	calc_check_tx();
 	
	
	/* A cada 15 min. faz o fechamento (parte = 14) que pode ser chamado pelo
	   pulso de integracao externo ou pela passagem do temporizador interno
	   (timer_integra) que subt. o ext. no caso da falta ou perda de sinal */
	if (parte == 14) 
		{
		fecha_periodo();
		}
}


void fecha_periodo()    /* rotinas que sao executadas a cada 15 minutos */
{                       /* no fechamento do intervalo de integracao     */
	dem_ativa = dem_projetada;
	dem_reativa = dem_proj_reat;
	dem_projetada = 0;
	dem_proj_reat = 0;
	Pega_maior_dem();	  /* verifica se a dem atual superou a maior do mes */
	consumo_ati += (((long)dem_ativa * 1000L) / 4L);
	consumo_rea += (((long)dem_reativa * 1000L) / 4L);
	
	tipo_fp_men = tipo_fp;
	tipo_fp = UNIT;
	media_fat_potencia = calc_fat_pot(consumo_ati / 1000L, consumo_rea /1000L);
	for (x = 0; x < 15; x++) 
		{
		int_ativa[x] = 0;             /* zera os acumuladores de pulsos */

		addr = ee_int_ativa+(x*2);
		data1_int =  0;
		salva_word_e2prom();
		
		int_reativa[x] = 0;
		
		addr = ee_int_reativa+(x*2);
		data1_int =  0;
		salva_word_e2prom();
		
		}
			
	verifik_ponta(); 		 /*  verifica se estamos na ponta umida ou seca */
		
	buf_dados[posi_codigo] = codigo_int_rep;
	grava_registros();

	salva_15_em_15();
	
}

  
void verifik_ponta() /* Em funcao das datas de inicio e fim do periodo seco */
{                    /* enquadra data atual ajust. 'ponta_ck' como V ou F   */ 
	if (mes_ini_per_seco < mes_fim_per_seco) 
		{
		if (mes_ini_per_seco <= mes && mes <= mes_fim_per_seco) 
			{
			if (mes == mes_ini_per_seco) 
				{
				if (dia < dia_ini_per_seco) 
					{
					 ponta_ck = F;
					}
				else
					{
					 ponta_ck = V;
					}
				}
			if (mes == mes_fim_per_seco) 
				{
				if (dia > dia_fim_per_seco) 
					{
					ponta_ck = F;
					}
				else
					{
					ponta_ck = V;
					}
				}
			if (mes_ini_per_seco < mes && mes < mes_fim_per_seco)
				{
				ponta_ck = V;
				}
			}
		else 
			{
			ponta_ck = F;
			}
		}
	else 
		{
		if (mes_ini_per_seco <= mes || mes <= mes_fim_per_seco) 
			{
			if (mes == mes_ini_per_seco) 
				{
				if (dia < dia_ini_per_seco) 
					{
					ponta_ck = F;
					} 
				else
					{
					ponta_ck = V;
					}
				}
			if (mes == mes_fim_per_seco) 
				{
				if (dia > dia_fim_per_seco) 
					{
					ponta_ck = F;
					}
				else
					{
					ponta_ck = V;
					}
				}
			if (mes_ini_per_seco < mes || mes < mes_fim_per_seco)	
				{
				ponta_ck = V;
				}
			}
		else 
			{
			ponta_ck = F;
			}
		}
}

void verifik_carga()    /* Faz o controle das cargas em funcao do periodo */
{                       /* seco ou umido, ponta ou fora_ponta */

	if (ponta_ck == V) 
		{
		if (periodo == EM_PONTA) 
			{
			demanda_maxima = max_dem_ponta_seca;
			if (dem_projetada > max_dem_ponta_seca)
				{
				cont_carga(ACIMA, dem_projetada - max_dem_ponta_seca);
				}
			else 
				{
				cont_carga(ABAIXO, max_dem_ponta_seca - dem_projetada);
				}
			}
		else 
			{
			demanda_maxima = max_dem_fora_ponta_seca;
			if (dem_projetada > max_dem_fora_ponta_seca)
				{
				cont_carga(ACIMA, dem_projetada - max_dem_fora_ponta_seca);
				}
			else 
				{
				cont_carga(ABAIXO, max_dem_fora_ponta_seca - dem_projetada);
				}
			}
		}
	else 
		{
		 if (periodo == EM_PONTA) 
		 	{
			demanda_maxima = max_dem_ponta_umida;
			 if (dem_projetada > max_dem_ponta_umida)
			 	{
				 cont_carga(ACIMA, dem_projetada - max_dem_ponta_umida);
				}
			 else
			 	{
				 cont_carga(ABAIXO, max_dem_ponta_umida - dem_projetada);
				}
		 	}
		 else 
		 	{
			demanda_maxima = max_dem_fora_ponta_umida;
			 if (dem_projetada > max_dem_fora_ponta_umida)
			 	{
				 cont_carga(ACIMA, dem_projetada - max_dem_fora_ponta_umida);
				 }
			 else
			 	{
				 cont_carga(ABAIXO, max_dem_fora_ponta_umida - dem_projetada);
				 }
		 	}
		}
}

void Pega_maior_dem()
{
	unsigned char estado;

    if (periodo == periodo_ant) /* se nao houve alteracao do periodo */
    	{
		estado = periodo;
		}
	else 
		{                      /* se houve, considera o intervalo anterior */
		estado = periodo_ant;   /* (ultimos 15 minutos) ainda como sendo do */
		periodo_ant = periodo;  /* periodo anterior.                                            */
		}
	if (estado == FORA_DE_PONTA) 
		{
		if (dem_ativa > maior_dem_ati_fora_ponta)
			{
			maior_dem_ati_fora_ponta = dem_ativa;
			}
		if (dem_reativa > maior_dem_rea_fora_ponta)
			{
			maior_dem_rea_fora_ponta = dem_reativa;
			}
		}
	else 
		{
		if (dem_ativa > maior_dem_ati_ponta)
			{
			maior_dem_ati_ponta = dem_ativa;
			}
		if (dem_reativa > maior_dem_rea_ponta)
			{
			maior_dem_rea_ponta = dem_reativa;
			}
		}
}


void reposicao()  /* Se ocorreu mudanca de mes guarda os dados atuais como  */
{                 /* registros anteriores e reseta as variaveis de trabalho */
	maior_dem_ati_ponta_ant = maior_dem_ati_ponta;/* valores do mes passado */
	maior_dem_rea_ponta_ant = maior_dem_rea_ponta;
	maior_dem_ati_ponta = 0;              /* zera valores do mes que inicia */
	maior_dem_rea_ponta = 0;
	maior_dem_ati_fora_ponta_ant = maior_dem_ati_fora_ponta; /* mes passado */
	maior_dem_rea_fora_ponta_ant = maior_dem_rea_fora_ponta;
	maior_dem_ati_fora_ponta = 0;         /* zera valores do mes que inicia */
	maior_dem_rea_fora_ponta = 0;
	media_fat_potencia_ant = media_fat_potencia;  /* valores do mes passado */
	consumo_ati_ant = consumo_ati;
	consumo_rea_ant = consumo_rea;
	tipo_fp_men_ant = tipo_fp_men;
	media_fat_potencia = 0;               /* zera valores do mes que inicia */
	tipo_fp_men = UNIT;
	consumo_ati = 0L;
	consumo_rea = 0L;
	
/* salva reposicao */	
	salva_15_em_15();

}


void salva_15_em_15(void)
{
	addr=ee_maior_dem_ati_ponta_ant;
	data1_int=maior_dem_ati_ponta_ant;
	salva_word_e2prom();

	addr=ee_maior_dem_rea_ponta_ant;
	data1_int=maior_dem_rea_ponta_ant;
	salva_word_e2prom();
	
	addr=ee_maior_dem_ati_fora_ponta_ant;
	data1_int=maior_dem_ati_fora_ponta_ant;
	salva_word_e2prom();

	addr=ee_maior_dem_rea_fora_ponta_ant;
	data1_int=maior_dem_rea_fora_ponta_ant;
	salva_word_e2prom();

	addr=ee_media_fat_potencia_ant;
	data1=media_fat_potencia_ant;
	salva_byte_e2prom();

	addr=ee_consumo_ati_ant;
	l=consumo_ati_ant;
	salva_long_e2prom();

	addr=ee_consumo_rea_ant;
	l=consumo_rea_ant;
	salva_long_e2prom();

	addr=ee_consumo_ati;
	l=consumo_ati;
	salva_long_e2prom();

	addr=ee_consumo_rea;
	l=consumo_rea;
	salva_long_e2prom();

}			

unsigned char calc_fat_pot(unsigned long fig_ati, unsigned long fig_rea)
{
	unsigned char ext;
	double ativa_2, reativa_2; 
	double ativa, reativa;
	ativa = fig_ati; 
	reativa = fig_rea;
	ativa_2 = (ativa * ativa * 100);
	reativa_2 = (reativa * reativa * 100);
	ext = (unsigned char)(((ativa * 1000)) / ((sqrt((double)(ativa_2 + reativa_2)))) );
	return(ext);
}




