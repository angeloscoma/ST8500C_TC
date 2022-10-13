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


// funcoes do relogio
void rtc_init();

// funcoes do ad
long int read_mcp(void) ;
long int le_canal_0(void);
long int le_canal_1(void);
long int le_canal_2(void);
long int le_canal_3(void);
long int le_canal_4(void);
long int le_canal_5(void);
long int le_canal_6(void);
long int le_canal_7(void);
long int read_analog_mcp( byte canal );

// funcoes da e2prom interna
//char read_byte(int16 adress);
//void write_byte(int16 adress,char dado);
//int16 read_word(int16 adress);
//void write_word(int16 adress,int16 dado);

// funcoes diversas
void calcula_checksum_vars (void);
void verifica_checksum_vars (void);
void calcula_tensao_corrente(void);



// funcoes do controle de consumo
void zera_consumo(void);
void zera_demandas(void);
void inic_consumo(void);
void grava_consumo_old(void);


void kvar_requerido(char);
void calc_fator_total(void);


#if (com_regs == true)
		// funcoes de tratamento da flahs
		char Read_Status_Register(int32);
		char read_byte_flash(int32);
		char Read_ID(int32, char);
		void desprotege_flash(int32);
		// funcoes do controle de registros
		void tx_ocor_mdb(void);
		void grava_ocorrencias(char);
		void grava_registros(char);
		void grava_cht(char);
		void apaga_ocorrencias(void);
		void apaga_registros(void);
		void apaga_cht(void);
		void zera_chts(void);
		void zera_soma_reg(void);
		void tx_reg_mdb(void);
#endif

#if (portatil == true)
	void calcula_autonomia(void);
#endif
#if (st9600r == true)
	#if (versao_pci_st96 >= 4)
		void atualiza_ganho(char);
		void pga_gain_set(int16, char); 
		void pga_chan_set(int16, char);
	#endif
#endif

#if (com_display == true)
	// funcoes de tratamento do display 
	void limpa_display(void);
	void mensagem(char, char);
	void xprint_display(char, int16,char, char,char, char);
	void print_display(char, int16,char, char,char, char, char);
	void displayp(char, int16,char, char,char);
#endif	

#if (com_menu == true)
	// funcoes do tratamendo dos menus	
	void encerra_menus(void);
	void fim_menu1(void);
#endif

