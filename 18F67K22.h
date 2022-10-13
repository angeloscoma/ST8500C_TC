//////// Standard Header file for the PIC18F67K22 device ////////////////
#device PIC18F67K22
#nolist
//////// Program memory: 65536x16  Data RAM: 4095  Stack: 31
//////// I/O: 53   Analog Pins: 20
//////// Data EEPROM: 1024
//////// C Scratch area: 00   ID Location: 200000
//////// Fuses: VREGSLEEP_SW,VREGSLEEP,INTRC_LP,INTRC_HP,SOSC_LOW,SOSC_DIG
//////// Fuses: SOSC_HIGH,NOXINST,XINST,LP,XT,HSH,HSM,ECH,ECH_IO,RC,RC_IO
//////// Fuses: INTRC_IO,INTRC,ECM,ECM_IO,ECL,ECL_IO,NOPLLEN,PLLEN,NOFCMEN
//////// Fuses: FCMEN,NOIESO,IESO,PUT,NOPUT,NOBROWNOUT,BROWNOUT_SW
//////// Fuses: BROWNOUT_NOSL,BROWNOUT,BORV30,BORV27,BORV20,BORV18,BORM_LOW
//////// Fuses: BORM_MED,BORM_HIGH,ZPBORM,NOWDT,WDT_NOSLEEP,WDT_SW,WDT,WDT1
//////// Fuses: WDT2,WDT4,WDT8,WDT16,WDT32,WDT64,WDT128,WDT256,WDT512
//////// Fuses: WDT1024,WDT2048,WDT4096,WDT8192,WDT16384,WDT32768,WDT65536
//////// Fuses: WDT131072,WDT262144,WDT524288,WDT1048576,RTCOSC_INT
//////// Fuses: RTCOSC_T1,CCP2B3,CCP2C1,MSSPMSK5,MSSPMSK7,NOMCLR,MCLR
//////// Fuses: NOSTVREN,STVREN,BBSIZ1K,BBSIZ2K,DEBUG,NODEBUG,PROTECT
//////// Fuses: NOPROTECT,CPB,NOCPB,CPD,NOCPD,WRT,NOWRT,WRTC,NOWRTC,WRTB
//////// Fuses: NOWRTB,WRTD,NOWRTD,EBTR,NOEBTR,EBTRB,NOEBTRB
//////// 
////////////////////////////////////////////////////////////////// I/O
// Discrete I/O Functions: SET_TRIS_x(), OUTPUT_x(), INPUT_x(),
//                         PORT_x_PULLUPS(), INPUT(),
//                         OUTPUT_LOW(), OUTPUT_HIGH(),
//                         OUTPUT_FLOAT(), OUTPUT_BIT()
// Constants used to identify pins in the above are:

#define PIN_A0  31744
#define PIN_A1  31745
#define PIN_A2  31746
#define PIN_A3  31747
#define PIN_A4  31748
#define PIN_A5  31749
#define PIN_A6  31750
#define PIN_A7  31751

#define PIN_B0  31752
#define PIN_B1  31753
#define PIN_B2  31754
#define PIN_B3  31755
#define PIN_B4  31756
#define PIN_B5  31757
#define PIN_B6  31758
#define PIN_B7  31759

#define PIN_C0  31760
#define PIN_C1  31761
#define PIN_C2  31762
#define PIN_C3  31763
#define PIN_C4  31764
#define PIN_C5  31765
#define PIN_C6  31766
#define PIN_C7  31767

#define PIN_D0  31768
#define PIN_D1  31769
#define PIN_D2  31770
#define PIN_D3  31771
#define PIN_D4  31772
#define PIN_D5  31773
#define PIN_D6  31774
#define PIN_D7  31775

#define PIN_E0  31776
#define PIN_E1  31777
#define PIN_E2  31778
#define PIN_E3  31779
#define PIN_E4  31780
#define PIN_E5  31781
#define PIN_E6  31782
#define PIN_E7  31783

#define PIN_F1  31785
#define PIN_F2  31786
#define PIN_F3  31787
#define PIN_F4  31788
#define PIN_F5  31789
#define PIN_F6  31790
#define PIN_F7  31791

#define PIN_G0  31792
#define PIN_G1  31793
#define PIN_G2  31794
#define PIN_G3  31795
#define PIN_G4  31796
#define PIN_G5  31797

////////////////////////////////////////////////////////////////// Useful defines
#define FALSE 0
#define TRUE 1

#define BYTE int8
#define BOOLEAN int1

#define getc getch
#define fgetc getch
#define getchar getch
#define putc putchar
#define fputc putchar
#define fgets gets
#define fputs puts

////////////////////////////////////////////////////////////////// Control
// Control Functions:  RESET_CPU(), SLEEP(), RESTART_CAUSE()
// Constants returned from RESTART_CAUSE() are:

#define WDT_TIMEOUT       7    
#define MCLR_FROM_SLEEP  11    
#define MCLR_FROM_RUN    15    
#define NORMAL_POWER_UP  12    
#define BROWNOUT_RESTART 14    
#define WDT_FROM_SLEEP   3     
#define RESET_INSTRUCTION 0    

////////////////////////////////////////////////////////////////// Timer 0
// Timer 0 (AKA RTCC)Functions: SETUP_COUNTERS() or SETUP_TIMER_0(),
//                              SET_TIMER0() or SET_RTCC(),
//                              GET_TIMER0() or GET_RTCC()
// Constants used for SETUP_TIMER_0() are:
#define T0_INTERNAL   0
#define T0_EXT_L_TO_H 32
#define T0_EXT_H_TO_L 48

#define T0_DIV_1      8
#define T0_DIV_2      0
#define T0_DIV_4      1
#define T0_DIV_8      2
#define T0_DIV_16     3
#define T0_DIV_32     4
#define T0_DIV_64     5
#define T0_DIV_128    6
#define T0_DIV_256    7

#define T0_OFF        0x80  

#define T0_8_BIT      0x40  

#define RTCC_INTERNAL   0      // The following are provided for compatibility
#define RTCC_EXT_L_TO_H 32     // with older compiler versions
#define RTCC_EXT_H_TO_L 48
#define RTCC_DIV_1      8
#define RTCC_DIV_2      0
#define RTCC_DIV_4      1
#define RTCC_DIV_8      2
#define RTCC_DIV_16     3
#define RTCC_DIV_32     4
#define RTCC_DIV_64     5
#define RTCC_DIV_128    6
#define RTCC_DIV_256    7
#define RTCC_OFF        0x80  
#define RTCC_8_BIT      0x40  

// Constants used for SETUP_COUNTERS() are the above
// constants for the 1st param and the following for
// the 2nd param:

////////////////////////////////////////////////////////////////// WDT
// Watch Dog Timer Functions: SETUP_WDT() or SETUP_COUNTERS() (see above)
//                            RESTART_WDT()
// WDT base is 4ms
//
#define WDT_ON        0x100
#define WDT_OFF       0

////////////////////////////////////////////////////////////////// Timer 1
// Timer 1 Functions: SETUP_TIMER_1, GET_TIMER1, SET_TIMER1
// Constants used for SETUP_TIMER_1() are:
//      (or (via |) together constants from each group)
#define T1_DISABLED         0
#define T1_INTERNAL         0x07
#define T1_EXTERNAL         0x87
#define T1_EXTERNAL_SYNC    0x83
#define T1_FOSC             0x47

#define T1_ENABLE_SOSC		0x08

#define T1_DIV_BY_1         0
#define T1_DIV_BY_2         0x10
#define T1_DIV_BY_4         0x20
#define T1_DIV_BY_8         0x30

#define T1_GATE           0x8000
#define T1_GATE_INVERTED  0xC000
#define T1_GATE_TOGGLE    0xA000
#define T1_GATE_SINGLE    0x9000
#define T1_GATE_TIMER2    0x8100
#define T1_GATE_COMP1     0x8200
#define T1_GATE_COMP2     0x8300

////////////////////////////////////////////////////////////////// Timer 2
// Timer 2 Functions: SETUP_TIMER_2, GET_TIMER2, SET_TIMER2
// Constants used for SETUP_TIMER_2() are:
#define T2_DISABLED         0
#define T2_DIV_BY_1         4
#define T2_DIV_BY_4         5
#define T2_DIV_BY_16        6

////////////////////////////////////////////////////////////////// Timer 3
// Timer 3 Functions: SETUP_TIMER_3, GET_TIMER3, SET_TIMER3
// Constants used for SETUP_TIMER_3() are:
//      (or (via |) together constants from each group)
#define T3_DISABLED         0
#define T3_INTERNAL         0x07
#define T3_EXTERNAL         0x87
#define T3_EXTERNAL_SYNC    0x83
#define T3_FOSC             0x47

#define T3_ENABLE_SOSC		0x08

#define T3_DIV_BY_1         0
#define T3_DIV_BY_2         0x10
#define T3_DIV_BY_4         0x20
#define T3_DIV_BY_8         0x30

#define T3_GATE           0x8000
#define T3_GATE_INVERTED  0xC000
#define T3_GATE_TOGGLE    0xA000
#define T3_GATE_SINGLE    0x9000
#define T3_GATE_TIMER4    0x8100
#define T3_GATE_COMP1     0x8200
#define T3_GATE_COMP2     0x8300

////////////////////////////////////////////////////////////////// Timer 4
// Timer 4 Functions: SETUP_TIMER_4, GET_TIMER4, SET_TIMER4
// Constants used for SETUP_TIMER_4() are:
#define T4_DISABLED         0
#define T4_DIV_BY_1         4
#define T4_DIV_BY_4         5
#define T4_DIV_BY_16        6

////////////////////////////////////////////////////////////////// Timer 5
// Timer 5 Functions: SETUP_TIMER_5, GET_TIMER5, SET_TIMER5
// Constants used for SETUP_TIMER_5() are:
//      (or (via |) together constants from each group)
#define T5_DISABLED         0
#define T5_INTERNAL         0x07
#define T5_EXTERNAL         0x87
#define T5_EXTERNAL_SYNC    0x83
#define T5_FOSC             0x47

#define T5_ENABLE_SOSC		0x08

#define T5_DIV_BY_1         0
#define T5_DIV_BY_2         0x10
#define T5_DIV_BY_4         0x20
#define T5_DIV_BY_8         0x30

#define T5_GATE           0x8000
#define T5_GATE_INVERTED  0xC000
#define T5_GATE_TOGGLE    0xA000
#define T5_GATE_SINGLE    0x9000
#define T5_GATE_TIMER6    0x8100
#define T5_GATE_COMP1     0x8200
#define T5_GATE_COMP2     0x8300

////////////////////////////////////////////////////////////////// Timer 6
// Timer 6 Functions: SETUP_TIMER_6, GET_TIMER5, SET_TIMER5
// Constants used for SETUP_TIMER_6() are:
//      (or (via |) together constants from each group)
#define T6_DISABLED         0
#define T6_DIV_BY_1         4
#define T6_DIV_BY_4         5
#define T6_DIV_BY_16        6

////////////////////////////////////////////////////////////////// Timer 7
// Timer 7 Functions: SETUP_TIMER_7, GET_TIMER7, SET_TIMER7
// Constants used for SETUP_TIMER_7() are:
//      (or (via |) together constants from each group)
#define T7_DISABLED         0
#define T7_INTERNAL         0x07
#define T7_EXTERNAL         0x87
#define T7_EXTERNAL_SYNC    0x83
#define T7_FOSC             0x47

#define T7_ENABLE_SOSC		0x08

#define T7_DIV_BY_1         0
#define T7_DIV_BY_2         0x10
#define T7_DIV_BY_4         0x20
#define T7_DIV_BY_8         0x30

#define T7_GATE           0x8000
#define T7_GATE_INVERTED  0xC000
#define T7_GATE_TOGGLE    0xA000
#define T7_GATE_SINGLE    0x9000
#define T7_GATE_TIMER8    0x8100
#define T7_GATE_COMP1     0x8200
#define T7_GATE_COMP2     0x8300

////////////////////////////////////////////////////////////////// Timer 8
// Timer 8 Functions: SETUP_TIMER_8, GET_TIMER8, SET_TIMER8
// Constants used for SETUP_TIMER_8() are:
//      (or (via |) together constants from each group)
#define T8_DISABLED         0
#define T8_DIV_BY_1         4
#define T8_DIV_BY_4         5
#define T8_DIV_BY_16        6

////////////////////////////////////////////////////////////////// Timer 10
// Timer 10 Functions: SETUP_TIMER_10, GET_TIMER10, SET_TIMER10
// Constants used for SETUP_TIMER_10() are:
//      (or (via |) together constants from each group)
#define T10_DISABLED         0
#define T10_DIV_BY_1         4
#define T10_DIV_BY_4         5
#define T10_DIV_BY_16        6

////////////////////////////////////////////////////////////////// Timer 12
// Timer 12 Functions: SETUP_TIMER_12, GET_TIMER12, SET_TIMER12
// Constants used for SETUP_TIMER_12() are:
//      (or (via |) together constants from each group)
#define T12_DISABLED         0
#define T12_DIV_BY_1         4
#define T12_DIV_BY_4         5
#define T12_DIV_BY_16        6

////////////////////////////////////////////////////////////////// RTC
// RTC Functions: setup_rtc(), setup_rtc_alarm(), rtc_read(),
//                rtc_write(), rtc_alarm_read(), rtc_alarm_write()
// Structure used in read and write functions (pass pointer):
typedef struct {
   int8 tm_year;
   int8 tm_yday;  // Not used by built in functions
   int8 tm_mday;
   int8 tm_mon;
   int8 tm_hour;
   int8 tm_wday;
   int8 tm_sec;
   int8 tm_min;
   int8 tm_isdst; // Not used by built in functions
} rtc_time_t;
//
// Constants used in setup_rtc() are:  // Second param is calibration
#define RTC_ENABLE           0x8000
#define RTC_DISABLE          0
#define RTC_OUTPUT_SOURCE    0x20400
#define RTC_OUTPUT_SECONDS   0x10400
#define RTC_OUTPUT_ALARM     0x00400
//
// Constants used in setup_rtc_alarm() first param are:
#define RTC_ALARM_ENABLE     0x80
#define RTC_ALARM_DISABLE    0
#define RTC_CHIME_ENABLE     0x40
#define RTC_CHIME_DISABLE    0
// Constants used in setup_rtc_alarm() second param are:  // Third param is repeat#
#define RTC_ALARM_HALFSECOND 0x00
#define RTC_ALARM_SECOND     0x04
#define RTC_ALARM_10_SECONDS 0x08
#define RTC_ALARM_MINUTE     0x0C
#define RTC_ALARM_10_MINUTES 0x10
#define RTC_ALARM_HOUR       0x14
#define RTC_ALARM_DAY        0x18
#define RTC_ALARM_WEEK       0x1C
#define RTC_ALARM_MONTH      0x20
#define RTC_ALARM_YEAR       0x24

////////////////////////////////////////////////////////////////// CCP
// CCP Functions: SETUP_CCPx, SET_PWMx_DUTY
// CCP Variables: CCP_x, CCP_x_LOW, CCP_x_HIGH
// Constants used for SETUP_CCPx() are:
#define CCP_OFF                         0
#define CCP_CAPTURE_FE                  4
#define CCP_CAPTURE_RE                  5
#define CCP_CAPTURE_DIV_4               6
#define CCP_CAPTURE_DIV_16              7
#define CCP_COMPARE_SET_ON_MATCH        8
#define CCP_COMPARE_CLR_ON_MATCH        9
#define CCP_COMPARE_INT                 0xA
#define CCP_COMPARE_INT_AND_TOGGLE      0x2       
#define CCP_COMPARE_RESET_TIMER         0xB
#define CCP_PWM                         0xC
#define CCP_PWM_PLUS_1                  0x1c  
#define CCP_PWM_PLUS_2                  0x2c
#define CCP_PWM_PLUS_3                  0x3c
//#define CCP_USE_TIMER3                0x100  OBSOLETE, SEE TIMER-3     
#word   CCP_1       =                   getenv("SFR:CCPR1L")
#byte   CCP_1_LOW   =                   getenv("SFR:CCPR1L")
#byte   CCP_1_HIGH  =                   getenv("SFR:CCPR1H")
// The following are used to select the Timer source for the CCP/ECCP
// The first timer is the timer used when in CAPTURE or COMPARE mode
// The second timer is the timer used when in PWM mode
#define CCP_USE_TIMER1_AND_TIMER2       0x0000 //used for CCP 1 2 3 4 5 6 7 8 9 10 
#define CCP_USE_TIMER3_AND_TIMER4       0x0100 //used for CCP 1 2 3 4
#define CCP_USE_TIMER3_AND_TIMER6       0x0200 //used for CCP 1 2 3 4
#define CCP_USE_TIMER3_AND_TIMER8       0x0300 //used for CCP 1 2 3
#define CCP_USE_TIMER3_AND_TIMER10      0x0400 //used for CCP 1 2 
#define CCP_USE_TIMER3_AND_TIMER12      0x0500 //used for CCP 1 
#define CCP_USE_TIMER5_AND_TIMER4       0x0100 //used for CCP 5 7
#define CCP_USE_TIMER5_AND_TIMER2       0x0100 //used for CCP 6
#define CCP_USE_TIMER5_AND_TIMER6       0x0200 //used for CCP 7
#define CCP_USE_TIMER5_AND_TIMER8       0x0300 //used for CCP 7
#define CCP_USE_TIMER7_AND_TIMER4       0x0100 //used for CCP 8 9 
#define CCP_USE_TIMER7_AND_TIMER6       0x0200 //used for CCP 8 
#define CCP_USE_TIMER7_AND_TIMER2       0x0100 //used for CCP 10 

// The following should be used with the ECCP unit only (or these in)
#define CCP_PWM_H_H                     0x0c
#define CCP_PWM_H_L                     0x0d
#define CCP_PWM_L_H                     0x0e
#define CCP_PWM_L_L                     0x0f

#define CCP_PWM_FULL_BRIDGE             0x40
#define CCP_PWM_FULL_BRIDGE_REV         0xC0
#define CCP_PWM_HALF_BRIDGE             0x80

#define CCP_SHUTDOWN_ON_COMP1           0x100000
#define CCP_SHUTDOWN_ON_COMP2           0x200000
#define CCP_SHUTDOWN_ON_COMP            0x300000
#define CCP_SHUTDOWN_ON_INT0            0x400000
#define CCP_SHUTDOWN_ON_COMP1_INT0      0x500000
#define CCP_SHUTDOWN_ON_COMP2_INT0      0x600000
#define CCP_SHUTDOWN_ON_COMP_INT0       0x700000

#define CCP_SHUTDOWN_AC_L               0x000000
#define CCP_SHUTDOWN_AC_H               0x040000
#define CCP_SHUTDOWN_AC_F               0x080000

#define CCP_SHUTDOWN_BD_L               0x000000
#define CCP_SHUTDOWN_BD_H               0x010000
#define CCP_SHUTDOWN_BD_F               0x020000


#define CCP_PULSE_STEERING_A            0x01000000
#define CCP_PULSE_STEERING_B            0x02000000
#define CCP_PULSE_STEERING_C            0x04000000
#define CCP_PULSE_STEERING_D            0x08000000
#define CCP_PULSE_STEERING_SYNC         0x10000000
#define CCP_COMPLEMENTARY_AB            0x43000000  
#define CCP_COMPLEMENTARY_AC            0x85000000  
#define CCP_COMPLEMENTARY_AD            0xC9000000  

#word   CCP_2       =                   getenv("SFR:CCPR2L")
#byte   CCP_2_LOW   =                   getenv("SFR:CCPR2L")
#byte   CCP_2_HIGH  =                   getenv("SFR:CCPR2H")
#word   CCP_3       =                   getenv("SFR:CCPR3L")
#byte   CCP_3_LOW   =                   getenv("SFR:CCPR3L")
#byte   CCP_3_HIGH  =                   getenv("SFR:CCPR3H")
#word   CCP_4       =                   getenv("SFR:CCPR4L")
#byte   CCP_4_LOW   =                   getenv("SFR:CCPR4L")
#byte   CCP_4_HIGH  =                   getenv("SFR:CCPR4H")
#word   CCP_5       =                   getenv("SFR:CCPR5L")
#byte   CCP_5_LOW   =                   getenv("SFR:CCPR5L")
#byte   CCP_5_HIGH  =                   getenv("SFR:CCPR5H")
#word   CCP_6       =                   getenv("SFR:CCPR6L")
#byte   CCP_6_LOW   =                   getenv("SFR:CCPR6L")
#byte   CCP_6_HIGH  =                   getenv("SFR:CCPR6H")
#word   CCP_7       =                   getenv("SFR:CCPR7L")
#byte   CCP_7_LOW   =                   getenv("SFR:CCPR7L")
#byte   CCP_7_HIGH  =                   getenv("SFR:CCPR7H")
#word   CCP_8       =                   getenv("SFR:CCPR8L")
#byte   CCP_8_LOW   =                   getenv("SFR:CCPR8L")
#byte   CCP_8_HIGH  =                   getenv("SFR:CCPR8H")
#word   CCP_9       =                   getenv("SFR:CCPR9L")
#byte   CCP_9_LOW   =                   getenv("SFR:CCPR9L")
#byte   CCP_9_HIGH  =                   getenv("SFR:CCPR9H")
#word   CCP_10      =                   getenv("SFR:CCPR10L")
#byte   CCP_10_LOW  =                   getenv("SFR:CCPR10L")
#byte   CCP_10_HIGH =                   getenv("SFR:CCPR10H")

////////////////////////////////////////////////////////////////// PSP
// PSP Functions: SETUP_PSP, PSP_INPUT_FULL(), PSP_OUTPUT_FULL(),
//                PSP_OVERFLOW(), INPUT_D(), OUTPUT_D()
// PSP Variables: PSP_DATA
// Constants used in SETUP_PSP() are:
#define PSP_ENABLED                     0x10
#define PSP_DISABLED                    0

#byte  PSP_DATA=    0xF83               

////////////////////////////////////////////////////////////////// SPI
// SPI Functions: SETUP_SPI, SPI_WRITE, SPI_READ, SPI_DATA_IN
// Constants used in SETUP_SPI() are:
#define SPI_DISABLED             0x00
#define SPI_MASTER               0x20
#define SPI_SLAVE                0x24
#define SPI_SCK_IDLE_HIGH        0x10
#define SPI_SCK_IDLE_LOW         0x00
#define SPI_CLK_DIV_4            0x00
#define SPI_CLK_DIV_16           0x01
#define SPI_CLK_DIV_64           0x02
#define SPI_CLK_T2               0x03
#define SPI_SS_DISABLED          0x01

#define SPI_XMIT_L_TO_H          0x4000
#define SPI_XMIT_H_TO_L          0x0000

#define SPI_SAMPLE_AT_MIDDLE     0x0000
#define SPI_SAMPLE_AT_END        0x8000

//The following are provided for compatibility
#define SPI_L_TO_H       SPI_SCK_IDLE_LOW
#define SPI_H_TO_L       SPI_SCK_IDLE_HIGH

////////////////////////////////////////////////////////////////// UART
// Constants used in setup_uart() are:
// FALSE - Turn UART off
// TRUE  - Turn UART on
#define UART_ADDRESS           2
#define UART_DATA              4
#define UART_AUTODETECT        8
#define UART_AUTODETECT_NOWAIT 9
#define UART_WAKEUP_ON_RDA     10
#define UART_SEND_BREAK        13
////////////////////////////////////////////////////////////////// COMP
// Comparator Variables: C1OUT, C2OUT, C3OUT
// Constants used in setup_comparator() are:
//
#define NC_NC_NC_NC     0x040404
#define NC_NC           0x040404

//Pick one constant for COMP1
#define CP1_F5_F6		0x000080
#define CP1_F3_F6		0x000082
#define CP1_VBG_F6		0x000083
#define CP1_F5_VREF		0x000084
#define CP1_F3_VREF		0x000086
#define CP1_VBG_VREF	0x000087
//Optionally OR with any of the following
#define CP1_OUT_ON_F2	0x000040
#define CP1_INVERT		0x000020
#define CP1_INT_L2H		0x000008
#define CP1_INT_H2L		0x000010

//Pick one constant for COMP2
#define CP2_F3_F4       0x008000
#define CP2_VBG_F4      0x008300
#define CP2_F3_VREF     0x008400
#define CP2_VBG_VREF    0x008700
//Optionally OR with any of the following
#define CP2_OUT_ON_F1   0x004000
#define CP2_INVERT      0x002000
#define CP2_INT_L2H     0x000800
#define CP2_INT_H2L     0x001000

//Pick one constant for COMP3
#define CP3_G3_G2       0x800000
#define CP3_G4_G2       0x810000
#define CP3_F3_G2       0x820000
#define CP3_VBG_G2      0x830000
#define CP3_G3_VREF     0x840000
#define CP3_G4_VREF     0x850000
#define CP3_F3_VREF     0x860000
#define CP3_VBG_VREF    0x870000
//Optionally OR with any of the following
#define CP3_OUT_ON_G1   0x400000
#define CP3_INVERT      0x200000
#define CP3_INT_L2H     0x080000
#define CP3_INT_H2L     0x100000

#bit C1OUT = 0xFB4.5
#bit C2OUT = 0xFB4.6
#bit C3OUT = 0xFB4.7

////////////////////////////////////////////////////////////////// VREF
// Constants used in setup_vref() are:
//
#define VREF_LOW  0xA0
#define VREF_HIGH 0x80
#define VREF_EXT   0x10  // Range for ref gen VREF- to VREF+
#define VREF_FVR   0x8000
// Or (with |) the above with a number 0-15

////////////////////////////////////////////////////////////////// VREF
// Constants used in setup_low_volt_detect() are:
//
#define LVD_LVDIN   0x1F
#define LVD_45 0x1E
#define LVD_42 0x1D
#define LVD_40 0x1C
#define LVD_38 0x1B
#define LVD_36 0x1A
#define LVD_35 0x19
#define LVD_33 0x18
#define LVD_30 0x17
#define LVD_28 0x16
#define LVD_27 0x15
#define LVD_25 0x14
#define LVD_24 0x13
#define LVD_23 0x12
#define LVD_22 0x11
#define LVD_21 0x10

#define LVD_TRIGGER_BELOW 0
#define LVD_TRIGGER_ABOVE 0x80


////////////////////////////////////////////////////////////////// INTERNAL RC
// Constants used in setup_oscillator() are:
#define OSC_31250      0x8000
#define OSC_PLL_ON     0x4000
#define OSC_PLL_OFF    0
#define OSC_31KHZ      0
#define OSC_250KHZ     0x10
#define OSC_500KHZ     0x20
#define OSC_1MHZ       0x30
#define OSC_2MHZ       0x40
#define OSC_4MHZ       0x50
#define OSC_8MHZ       0x60
#define OSC_16MHZ      0x70
// The following may be OR'ed in with the above using |
#define OSC_SOSC       1
#define OSC_INTRC      2
#define OSC_NORMAL     0
// The following may be OR'ed in with the above using |
#define OSC_IDLE_MODE  0x80
// The following may be OR'ed in with the above using |
#define OSC_MFINTRC_ON 0x10000  //MF-INTOSC used instead of HF-INTOSC for 500KHZ, 250KHZ and 31KHZ operating frequencies.
#define OSC_SOSC_ON    0x80000
// A second optional parameter may be used with this part to fine
// tune the speed (signed int,-32 to 31)
// Result may be (ignore all other bits)
#define OSC_STATE_STABLE 4
#define OSC_STATE_PRIMARY_RUNNING 8


////////////////////////////////////////////////////////////////// ADC
// ADC Functions: SETUP_ADC(), SETUP_ADC_PORTS() (aka SETUP_PORT_A),
//                SET_ADC_CHANNEL(), READ_ADC()
// Constants used for SETUP_ADC() are:
#define ADC_OFF               0           // ADC Off
#define ADC_CLOCK_DIV_2   0x100
#define ADC_CLOCK_DIV_4    0x04
#define ADC_CLOCK_DIV_8    0x01
#define ADC_CLOCK_DIV_16   0x05
#define ADC_CLOCK_DIV_32   0x02
#define ADC_CLOCK_DIV_64   0x06
#define ADC_CLOCK_INTERNAL 0x07           // Internal 2-6us
// The following may be OR'ed in with the above using |
#define ADC_TAD_MUL_0      0x00
#define ADC_TAD_MUL_2      0x08
#define ADC_TAD_MUL_4      0x10
#define ADC_TAD_MUL_6      0x18
#define ADC_TAD_MUL_8      0x20
#define ADC_TAD_MUL_12     0x28
#define ADC_TAD_MUL_16     0x30
#define ADC_TAD_MUL_20     0x38

// Constants used in SETUP_ADC_PORTS() are:
// First argument:
// OR together desired pins
#define sAN0     0x00000100     //| A0
#define sAN1     0x00000200     //| A1
#define sAN2     0x00000400     //| A2
#define sAN3     0x00000800     //| A3
#define sAN4     0x00001000     //| A5
#define sAN5     0x00002000     //| F7
#define sAN6     0x00004000     //| F1
#define sAN7     0x00008000     //| F3
#define sAN8     0x00010000     //| F3
#define sAN9     0x00020000     //| F4
#define sAN10    0x00040000     //| F5
#define sAN11    0x00080000     //| F6
#define sAN16    0x01000000     //| G4
#define sAN17    0x02000000     //| G3
#define sAN18    0x04000000     //| G2
#define sAN19    0x08000000     //| G1
#define NO_ANALOGS           0  // None
#define ALL_ANALOG  0x0F0FFF00  // A0 A1 A2 A3 A5 F7 F1 F2 F3 F4 F5 F6 G4 G3 G2 G1 

// Optional Second argument:
#define VSS_VDD           0x00     //| Range 0-Vdd
#define VSS_VREF          0x10     //| Range 0-VrefH
#define VSS_2V048         0x20     //| Range 0-2.048V
#define VSS_4V096         0x30     //| Range 0-4.096V
#define VREF_VDD          0x08     //| Range VrefL-Vdd
#define VREF_VREF         0x18     //| Range VrefL-VrefH
#define VREF_2V048        0x28     //| Range VrefL-2.048V
#define VREF_4V096        0x38     //| Range Vrefl-4.096V

// Constants used for second parameter of SET_ADC_CHANNEL() (first parameter is Analog Positive Channel)
#define VSS      0xFF //Analog Negative Channel connected to Vss

// Constants used in READ_ADC() are:
#define ADC_START_AND_READ     7   // This is the default if nothing is specified
#define ADC_START_ONLY         1
#define ADC_READ_ONLY          6

////////////////////////////////////////////////////////////////// INT
// Interrupt Functions: ENABLE_INTERRUPTS(), DISABLE_INTERRUPTS(),
//                      CLEAR_INTERRUPT(), INTERRUPT_ACTIVE(),
//                      EXT_INT_EDGE()
//
// Constants used in EXT_INT_EDGE() are:
#define L_TO_H              0x40
#define H_TO_L                 0
// Constants used in ENABLE/DISABLE_INTERRUPTS() are:
#define GLOBAL                    0xF2C0
#define PERIPH                    0xF240
#define INT_RTCC                  0x00F220
#define INT_TIMER0                0x00F220
#define INT_TIMER1                0x009D01
#define INT_TIMER2                0x009D02
#define INT_TIMER3                0x00A002
#define INT_EXT_L2H               0x5000F210
#define INT_EXT_H2L               0x6000F210
#define INT_EXT                   0x00F210
#define INT_EXT1_L2H              0x5001F008
#define INT_EXT1_H2L              0x6001F008
#define INT_EXT1                  0x00F008
#define INT_EXT2_L2H              0x5002F010
#define INT_EXT2_H2L              0x6002F010
#define INT_EXT2                  0x00F010
#define INT_RB                    0x00FFF208
#define INT_PSP                   0x009D80
#define INT_AD                    0x009D40
#define INT_RDA                   0x009D20
#define INT_TBE                   0x009D10
#define INT_SSP                   0x009D08
#define INT_BUSCOL                0x00A008
#define INT_RDA2                  0x00A320
#define INT_TBE2                  0x00A310
#define INT_OSCF                  0x00A080
#define INT_HLVD                  0x00A004
#define INT_EXT3_L2H              0x5003F020
#define INT_EXT3_H2L              0x6003F020
#define INT_EXT3                  0x00F020
#define INT_CCP1                  0x00A302
#define INT_CCP2                  0x00A304
#define INT_RTC                   0x00A301
#define INT_CTMU                  0x00A308
#define INT_TMR1G                 0x009D04
#define INT_TMR3G                 0x00A001
#define INT_BUSCOL2               0x00A010
#define INT_SSP2                  0x00A020
#define INT_TMR5G                 0x00A380
#define INT_CCP3                  0x00B601
#define INT_CCP4                  0x00B602
#define INT_CCP5                  0x00B604
#define INT_CCP6                  0x00B608
#define INT_CCP7                  0x00B610
#define INT_CCP8                  0x00B620
#define INT_CCP9                  0x00B640
#define INT_CCP10                 0x00B680
#define INT_TIMER4                0x00B901
#define INT_TIMER5                0x00B902
#define INT_TIMER6                0x00B904
#define INT_TIMER7                0x00B908
#define INT_TIMER8                0x00B910
#define INT_TIMER10               0x00B920
#define INT_TIMER12               0x00B940
#define INT_TMR7G                 0x00B980
#define INT_COMP1                 0x006001
#define INT_COMP2                 0x006002
#define INT_COMP3                 0x006004
#define INT_EEPROM                0x006010

#list
