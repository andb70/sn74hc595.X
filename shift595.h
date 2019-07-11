#ifndef _SHIFT_595_H    /* Guard against multiple inclusion */
#define _SHIFT_595_H


/******************************************************************************/
// SN74HC595    http://www.ti.com/lit/ds/symlink/sn74hc595.pdf
// 8-Bit Shift Registers With 3-State Output Registers
//
//	FNC     PIN     NAME      CONNECT. DESCRIPTION
// -----------------------------------------------------------------------------
//          16      Vcc         Positive supply voltage usually 5v
//          15      Q0          Output Pins
//	SER     14      DS          Serial data input
#define SHIFT_SER           LATGbits.LATG9
#define SHIFT_SER_PORT      IOPORT_G
#define SHIFT_SER_BIT       BIT_9
//	OE      13      OE        GND. Output enable, active low
//	RCLK	12      ST_CP       Storage register clock pin (latch pin)
#define SHIFT_RCLK          LATGbits.LATG8
#define SHIFT_RCLK_PORT     IOPORT_G
#define SHIFT_RCLK_BIT      BIT_8
//	SRCLK	11      SH_CP       Shift register clock pin
#define SHIFT_SRCLK         LATGbits.LATG7
#define SHIFT_SRCLK_PORT    IOPORT_G
#define SHIFT_SRCLK_BIT     BIT_7
//	SRCLR	10      MR        Vcc. Master Reclear, active low
//#define SHIFT_SRCLR_EN      _USING_SHIFT_SRCLR
#ifdef SHIFT_SRCLR_EN
#undef SHIFT_SRCLR_EN
#define SHIFT_SRCLR         LATBbits.LATB14
#define SHIFT_SRCLR_PORT    IOPORT_B
#define SHIFT_SRCLR_BIT     BIT_14
#endif   
//          9       Q7'         Serial Out
//          8       GND         Ground, Vss
//          1-7     Q1 to Q7	Output Pins
//
//        INPUTS            FUNCTION
//  SER	SR	SR	R	
//  SER	CLK	CLR	CLK	OE
//  ________________H_______Outputs QA?QH are disabled.
//  ________________L_______Outputs QA?QH are enabled.
//  ________L_______________ Shift register is cleared.
//  L	R	H	 	        First stage of the shift register goes low.
//  ________________________Other stages store the data of previous stage, respectively.
//  H	R	H	 	        First stage of the shift register goes high.
//  ________________________Other stages store the data of previous stage, respectively.
//   	 	 	R	        Shift-register data is stored in the storage register.
// 
// H:   High
// R:   Raising edge
// X:   Low or High
//
// load the byte as a serial stream
// and store the data
char shiftdata595(unsigned char);

#endif