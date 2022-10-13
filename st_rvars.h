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

/* Definicao das variaveis	em ram  extern */
#define ram_retardo_alarmes	2
char ram_codigo_cht;
char ram_codigo;
char ram_codigo_old;
//char ram_ptr_buf_ocor;
//char ram_ptr_ocor;
//char ram_ptr_regs;
#define ram_ptr_cht		10

#define ram_soma_reg_tr		20		// tamanho 4
#define ram_soma_reg_ts		24
#define ram_soma_reg_tt		28
#define ram_soma_reg_cr		32
#define ram_soma_reg_cs		36
#define ram_soma_reg_ct		40

#define ram_buf_dem_ativa 		200
#define ram_buf_dem_aparente	260

#define ram_que_ocor	100		// tamanho nro_ocorrencia;
#define ram_que_ocor_0	101
#define ram_que_ocor_1	102
#define ram_que_ocor_2	103
#define ram_que_ocor_3	104
#define ram_que_ocor_4	105
#define ram_que_ocor_5	106
#define ram_que_ocor_6	107
#define ram_que_ocor_7	108
#define ram_que_ocor_8	109
#define ram_que_ocor_9	110
#define ram_que_ocor_10	111
#define ram_que_ocor_11	111

