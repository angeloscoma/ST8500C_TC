/*;***********************************************************************
; Empresa: SULTECH SISTEMAS ELETRÔNICOS                                  *
; Modulo: CP_WS                                                        *
; Funcao: MODULO Interrupçoes   						 *
; 		Conversor de protocolo MP400 / Modbus/RTU                        *
;		By Sultech For AGST
; Responsavel: VAGNER SANTOS											 *
; Modificado ; VAGNER SANTOS                                             *
; Inicio: 06/06/2003                                                     *
; Revisao: RENGAV ARIERREF SOD SOTNAS                                    *
;*************************************************************************/

#define rd  	PIN_E0

#define PGD		PIN_B7

#define CA0		PIN_F3

#define CS_DISP   PIN_G0
#define direcao   PIN_F7
#define direcao2  PIN_C0


#define MCP3208_CLK  PIN_F6
#define MCP3208_DOUT PIN_F5
#define MCP3208_DIN  PIN_F4
#define MCP3208_CS   PIN_C1


// DEFINE I/O

#define CSIO1		PIN_E0
#define CSIO2		PIN_E1
#define CSIO3		PIN_E2
#define CSIO4		PIN_E3
#define CSIO5		PIN_E4
#define CSIO6		PIN_E5
#define CSIO7		PIN_E6
#define CSIO8		PIN_E7


struct DEF_ENTRADA1
{
	short ED1 : 1;
	short ED2 : 1;
	short ED3 : 1;
	short ED4 : 1;
	short ED5 : 1;
	short ED6 : 1;
	short ED7 : 1;
	short ED8 : 1;
}ENTRADA1;

struct DEF_ENTRADA2
{
	short ED9 : 1;
	short ED10 : 1;
	short ED11 : 1;
	short ED12 : 1;
	short ED13 : 1;
	short ED14 : 1;
	short ED15 : 1;
	short ED16 : 1;
}ENTRADA2;

struct DEF_ENTRADA3
{
	short ED17 : 1;
	short ED18 : 1;
	short ED19 : 1;
	short ED20 : 1;
	short ED21 : 1;
	short ED22 : 1;
	short ED23 : 1;
	short ED24 : 1;
}ENTRADA3;

struct DEF_ENTRADA4
{
	short ED25 : 1;
	short ED26 : 1;
	short ED27 : 1;
	short ED28 : 1;
	short ED29 : 1;
	short ED30 : 1;
	short ED31 : 1;
	short ED32 : 1;
}ENTRADA4;

struct DEF_SAIDA1
{
	short SD1 : 1;
	short SD2 : 1;
	short SD3 : 1;
	short SD4 : 1;
	short SD5 : 1;
	short SD6 : 1;
	short SD7 : 1;
	short SD8 : 1;
}SAIDA1;

struct DEF_SAIDA2
{
	short SD9 : 1;
	short SD10 : 1;
	short SD11 : 1;
	short SD12 : 1;
	short SD13 : 1;
	short SD14 : 1;
	short SD15 : 1;
	short SD16 : 1;
}SAIDA2;

#define LAMP_R SAIDA1.SD1
#define IND1_R SAIDA1.SD2
#define IND2_R SAIDA1.SD3
#define CAP1_R SAIDA1.SD4
#define CAP2_R SAIDA1.SD5
#define LAMP_S SAIDA1.SD6
#define IND1_S SAIDA1.SD7
#define IND2_S SAIDA1.SD8
#define CAP1_S SAIDA2.SD9
#define CAP2_S SAIDA2.SD10
#define LAMP_T SAIDA2.SD11
#define IND1_T SAIDA2.SD12
#define IND2_T SAIDA2.SD13
#define CAP1_T SAIDA2.SD14
#define CAP2_T SAIDA2.SD15
#define CTR_MT SAIDA2.SD16

#define RELE1	ENTRADA1.ED1
#define RELE2	ENTRADA1.ED2
#define RELE3	ENTRADA1.ED3
#define RELE4	ENTRADA1.ED4
#define RELE5	ENTRADA1.ED5
#define RELE6	ENTRADA1.ED6
#define RELE7	ENTRADA1.ED7
#define RELE8	ENTRADA1.ED8

#define RELE9	ENTRADA2.ED9
#define RELE10	ENTRADA2.ED10
#define RELE11	ENTRADA2.ED11
#define RELE12	ENTRADA2.ED12
#define RELE13	ENTRADA2.ED13
#define RELE14	ENTRADA2.ED14
#define RELE15	ENTRADA2.ED15
#define RELE16	ENTRADA2.ED16



//  PINOS NÃO USADOS
#define RST_AD 		 PIN_G3
#define CS_AD2		 PIN_G3
#define CS_AD3		 PIN_G3

//#if (chip_cs5460a == true)
	#define CS5460A_CLK  PIN_G3
	#define CS5460A_DOUT PIN_G3 
	#define CS5460A_DIN  PIN_G3
	#define CS5460A_CS_R PIN_G3
	#define CS5460A_CS_S PIN_G3	//PIN_E6
	#define CS5460A_CS_T PIN_G3	//PIN_E7
	#define CS5460A_RST	 PIN_G3
//#endif

//equates de pinos controle do relógio
#define RTC_SCLK PIN_G3
#define RTC_IO   PIN_G3
#define RTC_RST  PIN_G3

#define FLASH_CLK  PIN_G3
#define FLASH_SI   PIN_G3
#define FLASH_SO   PIN_G3
#define FLASH1_CE  PIN_G3
#define FLASH2_CE  PIN_G3
#define FLASH3_CE  PIN_G3
#define FLASH4_CE  PIN_G3
#define FLASH_HOLD PIN_G3
#define FLASH_WP   PIN_G3


#define CA1			PIN_G3


#define alarme 		PIN_G3
