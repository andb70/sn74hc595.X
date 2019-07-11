/*
 *      Author:     Andrea Biasutti
 *      Date:       July 5th 2019
 * 
 *      Subject:    TSIOT - Interconnessione di DEVICE
 * 
 */
#pragma config FPLLIDIV = DIV_2 // PLL Input Divider (1x Divider)
#pragma config FPLLMUL = MUL_20 // PLL Multiplier (24x Multiplier)
#pragma config UPLLIDIV = DIV_2 // USB PLL Input Divider (12x Divider)
#pragma config UPLLEN = OFF // USB PLL Enable (Disabled and Bypassed)
#pragma config FPLLODIV = DIV_1 // System PLL Output Clock Divider (PLL Divide by 256)
// DEVCFG1
#pragma config FNOSC = PRIPLL // Oscillator Selection Bits (Primary Osc w/PLL (XT+,HS+,EC+PLL))
#pragma config FSOSCEN = ON // Secondary Oscillator Enable (Enabled)
#pragma config IESO = ON // Internal/External Switch Over (Enabled)
#pragma config POSCMOD = HS // Primary Oscillator Configuration (HS osc mode)
#pragma config OSCIOFNC = ON // CLKO Output Signal Active on the OSCO Pin (Enabled)
#pragma config FPBDIV = DIV_8 // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/8)
#pragma config FCKSM = CSDCMD // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
#pragma config WDTPS = PS1048576 // Watchdog Timer Postscaler (1:1048576)
#pragma config FWDTEN = OFF // Watchdog Timer Enable (WDT Disabled (SWDTEN Bit Controls))
// DEVCFG0
#pragma config DEBUG = OFF // Background Debugger Enable (Debugger is disabled)
#pragma config ICESEL = ICS_PGx2 // ICE/ICD Comm Channel Select (ICE EMUC2/EMUD2 pins shared with PGC2/PGD2)
#pragma config PWP = OFF // Program Flash Write Protect (Disable)
#pragma config BWP = OFF // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF // Code Protect (Protection Disabled)

#include <p32xxxx.h> // Include PIC32 specifics header file
#include <plib.h> // Include the PIC32 Peripheral Library
#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "shift595.h"
#include "../display7s.X/display7s.h"
#include "../timers1.X/timers.h"

// HEARTBEAT led: toggle every seconds
// on board YELLOW
#define heartbeatLedToggle()    LATDbits.LATD1 = !LATDbits.LATD1

// CON5 D8
#define StatusLedSet(state)     LATBbits.LATB13 = state
#define StatusLedToggle()       LATBbits.LATB13 = !LATBbits.LATB13
void initLeds();

int i = 0;

/******************************************************************************/
void initGlobals();

int main() {

    // initialize timer service
    initTimers();
    // Initialize port pins to be used with display
    initShift595();
    initLeds();
    // initialize port pins to be used with leds
    initGlobals();

    // if using reset bit
#ifdef SHIFT_SRCLR_EN
    SHIFT_SRCLR = 1;
    for (i = 0; i < 80000; i++);
    SHIFT_SRCLR = 0;
#endif
    
    while (1) {
        // read input
        checkTimers();
        // manage the execution frequency
        shiftdata595(display7s[i]);
        if (heartbeat())
        {
            heartbeatLedToggle();
            if (i++ ==16)
                i = 0;
        }

    }
    return 1;
}

/******************************************************************************/
// SERVICES



/******************************************************************************/
// FUNCTION

/******************************************************************************/
// INITIALIZATION FUNCTIONS

// initialize ports used with leds

void initLeds() {
    mJTAGPortEnable(0); // Disable JTAG
    PORTSetPinsDigitalOut(IOPORT_B, BIT_13); // RED led @ D8
    PORTSetPinsDigitalOut(IOPORT_D, BIT_1); //  YELLOW led on-board
    PORTSetPinsDigitalOut(IOPORT_G, BIT_6); //  GREEN  led on-board    
}

void initGlobals() {
    // default state: all off
    LATB = 0;
    LATD = 0;
    LATG = 0;
}