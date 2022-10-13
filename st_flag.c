/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: CP_MAIN                                                        *
; Funcao: MODULO PRINCIPAL DE CONTROLE CP_4000   						 *
; 		Conversor de protocolo MP400 / Modbus/RTU                        *
;		By Sultech For AGST
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 06/06/2003                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/

short testando_memoria = 0;
#if (com_regs == true)
	short gravar_cht;
	short memoria_full;
#endif
short med_ten_ok;
short calc_ten_ok;
short ler_calend;
	
short virou_250ms;
short virou_500ms;
short virou_750ms;
short virouseg;
short viroumin;
short virouhora;
short viroudia;
short viroumes;
short morder_t1;
short morder_t3;
short morder_calc;
short ler_senoide;
short ler_ad;
short ler_ad_t3;
short calculando_vref;
short gravou;

short lendo_cht;
short ponto_segundo;
short pisca_minuto;
//short ativo;
short calcular_frequencia;
short calculando_freq;
short freq_50hz;

short erro_mod;
short existe;

short sel_sequencia;
short sel_seq_tab;
short limpa_ocor;
short apaga_banco;

short erro;
short tem_ocor;
short tem_alarme;
short fsentido_r;
short sentido_r;
short fp_ind;
short fp_cap;
short ten_a_r;
short ten_b_r;
short cor_a_r;
short chtt_a;
short chtc_a;
short ffase_r;
short cor_b_r;
short dem_ati;
short cor_baixa_r;
short tem_comando_alarme;
short tem_erro;
short erro_freq;

short zero_r;
short ajuste_relogio;

short em_status;

#if (CONTROLADOR == true) || (st_prog == true)
//	short faltou_energia;
	short tudo_desligado;
	short tudo_ligado;
	short com_manual;
	short des_ten_a;
	short des_ten_b;
	short des_chtt;
	short des_chtc;
	short des_fp_ind;
	short cor_min_r;

	short saturou_kw;
	short saturou_kvar;

	#if (st8500c == true)
		short ligou_carga;
		short desligou_carga;
		short fprintar;
	#else
		short ligou_banco;
		short desligou_banco;
	#endif		
	
	short MENU_FIXO;

	short cor_min;
	short sentido;
	short calcular_bancos;
	short falta_capacitor;
	
#endif

#if (monofasico == false)
	short sentido_s;
	short sentido_t;
	short ten_a_s;
	short ten_a_t;
	short ten_b_s;
	short ten_b_t;
	short cor_a_s;
	short cor_a_t;
	short ffase_s;
	short ffase_t;
	short cor_b_s;
	short cor_b_t;
	short cor_baixa_s;
	short cor_baixa_t;
	#if (CONTROLADOR == true)
		short cor_min_s;
		short cor_min_t;
	#endif
	short fsentido_s;
	short fsentido_t;
#endif



#if (st5x == true)
	short ler_dips;
#endif

short programando;


#if (com_menu == true)
	short exibiu;
	short piscar;
	short pisca;
	short tecla_up_down;  		/* tecla up e down pressionadas */
	short tecla_reset_up;		/* tecla up e reset pressionadas */
	short tecla_enter_down;  	/* tecla enter e down pressionadas */
	short tecla_enter_reset;	/* tecla enter e reset pressionadas */
	short tecla_up;				/* tecla up pressionada */
	short tecla_down;			/* tecla down pressionada */
	short enter_low;
	short tecla_enter;			/* tecla enter pressionada */
	short tecla_reset;			/* tecla reset pressionada */
	short ha_tecla;				// indica que tem tecla pressionada
	short exibiu_erro;			// indica que alguma mensagem de erro foi exibida
	short exibiu_erro_menu;		// indica que exibiu um erro qd qmenu != 0,  em outras telas.
	short teclou_enter;			// indica que tecla enter foi pressionada
	short exibir_menu;
	short tecla_up_down_reset;

	short rolando;
	short ja_rolou;

#endif

#if portatil == true
	#if (versao_pci_st96 >= 5)
		short ajustar_ponteira;
	#endif
	short digitando_texto;  
	short digitou_texto;
	short existe_local;
	short escolha_ponteira;
	short recarrega_ponteira;
#endif


#if (chip_cs5460a == true)
	short ler_cs5460;
#endif

#if (ade7754 == true)
	short lendo_kw;
	short aguarda_kw;
	short leu_senoide;
	short abre_leitura_cht;
	short lendo_tensao;
	short med_ten_ok_r;
	short med_ten_ok_s;
	short med_ten_ok_t;
#endif

#if (st_prog == true)
	short equip_mono;
	short equip_bi;
	short equip_tri;
	short protocolo;  
	short calibrando;
#endif


#if (st5x == true)
	#if (cpu_rev1011 == true)
		short spi_ocupada;
	#endif
#endif

short sincro;
//#if (st5x == true)
//	#if (TECNOFLUX == true)
//		short fled_ok;
//		short fled_tx;
//		short fled_rx;
//		short fled_alarme;
//		short fled_tc_r;
//		short fled_tc_s;
//		short fled_tc_t;
//		short fled_erro;
//	#endif
//#endif
#if (com_rep == true)
	short rec_rep_ok;
	short atualizar;
	short start_rep;
	short status_bit;
#endif

short ferro_rep;

short em_repouso;

short minuto_hora_ponta;
