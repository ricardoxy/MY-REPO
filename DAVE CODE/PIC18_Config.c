/* PIC18 Config Code File
 * File:   PIC18_config.c
 * Author: David Emerson
 *         davemers@iupui.edu
 *         ECE696
 *
 * Created on: July 15, 2014
 *
 * This file was created to configure the PIC18F44K22 device.
 *
 * Compiler: XC8, v1.31
 * MPLAB IDE: X, v2.10
 */

/********************************INCLUDES**************************************/
#include <xc.h>
#include <stdlib.h>
#include "PIC18_Config.h"


// configure oscillator routine
void init_OSC(void)
{
    // OSCCON: OSCILLATOR CONTROL REGISTER - pg32
    OSCCONbits.IDLEN = 1;       // Device enters Idle mode on SLEEP instruction
    OSCCONbits.IRCF = 7;        // HFINTOSC - (16 MHz)
    OSCCONbits.SCS = 0;         // Primary clock (determined by FOSC<3:0> in CONFIG1H)

    // OSCCON2: OSCILLATOR CONTROL REGISTER 2 - pg33
    OSCCON2bits.MFIOSEL = 0;    // MFINTOSC is not used
    OSCCON2bits.SOSCGO = 0;     // Secondary oscillator is shut off
    OSCCON2bits.PRISD = 1;      // Oscillator drive circuit on

    // OSCTUNE: OSCILLATOR TUNING REGISTER - pg37
    OSCTUNEbits.INTSRC = 0;     // 31.25 kHz device clock derived directly from LFINTOSC
    OSCTUNEbits.PLLEN = 1;      // PLL enabled

    // WDTCON: WATCHDOG TIMER CONTROL REGISTER - pg367
    WDTCONbits.SWDTEN = 0;      // WDT is turned off

}   // end init_OSC

// condifure interrupts routine
void init_Ints(void)
{
    // RCON: RESET CONTROL REGISTER - pg60
    RCONbits.IPEN = 1;          // Enable priority levels on interrupts

    // INTCON: INTERRUPT CONTROL REGISTER - pg116
    INTCONbits.GIE_GIEH = 1;    // Enables all unmasked interrupts
    INTCONbits.PEIE_GIEL = 1;   // Enables all unmasked peripheral interrupts

    // PIE1: PERIPHERAL INTERRUPT ENABLE (FLAG) REGISTER 1 - pg124
    PIE1bits.RC1IE = 1;         // EUSART1 Receive Interrupt Enabled
    
    // IPR1: PERIPHERAL INTERRUPT PRIORITY REGISTER 1 - pg128
    IPR1bits.RC1IP = 1;         // EUSART1 Receive Interrupt = High priority

    // PIR1: PERIPHERAL INTERRUPT REQUEST (FLAG) REGISTER 1 - pg119
    PIR1bits.RC1IF = 0;         // clear interrupt flag

}   // end init_Interrputs

// configure timer routine
void init_Timers(void)
{
    // Timer modules configured assuming a 64MHz OSC Clock and a 16MHz
    // instruction Cycle Clock

    // TIMER0 MODULE - pg159
    T0CONbits.T08BIT = 1;     // Timer0 is configured as an 8-bit timer/counter
    T0CONbits.T0CS = 0;       // Internal instruction cycle clock (CLKOUT)
    T0CONbits.T0SE = 0;       // Not used
    T0CONbits.PSA = 0;        // Timer0 prescaler is assigned
    T0CONbits.T0PS = 6;       // 1:128 prescale value
    T0CONbits.TMR0ON = 1;     // Enables Timer0

    TMR0 = 0;                   // set counter to zero

    // TIMER1 MODULE - pg159
    T1CONbits.TMR1CS = 0;       // Timer1 clock source is instruction clock (FOSC/4)
    T1CONbits.T1CKPS = 3;       // 1:8 Prescale value
    T1CONbits.T1SOSCEN = 0;     // Dedicated Secondary oscillator circuit disabled
    T1CONbits.T1RD16 = 1;       // Enables register read/write of Timer1 in one 16-bit operation
    T1CONbits.TMR1ON = 1;       // Stops Timer1, turn on when needed

    T1GCONbits.TMR1GE = 0;      // Timer1 counts regardless of Timer1 gate function


}   // end init_Timers

// configure UART1 routine
void init_UART1(void)
{
    // UART module is configured assuming a 64MHz OSC Clock and a 16MHz
    // instruction Cycle Clock

    // TXSTA1: TRANSMIT STATUS AND CONTROL REGISTER - pg277
    TXSTA1bits.CSRC = 0;        // Asynchronous mode: Don't care
    TXSTA1bits.TX9 = 0;         // 8-bit transmission
    TXSTA1bits.TXEN = 1;        // Transmit enabled
    TXSTA1bits.SYNC = 0;        // Asynchronous mode
    TXSTA1bits.SENDB = 0;       // Sync Break transmission completed
    TXSTA1bits.BRGH = 1;        // Low speed

    // RCSTA1: RECEIVE STATUS AND CONTROL REGISTER - pg278
    RCSTA1bits.SPEN = 1;        // Serial port enabled (configures RXx/DTx and TXx/CKx pins as serial port pins)
    RCSTA1bits.RX9 = 0;         // 8-bit reception
    RCSTA1bits.SREN = 0;        // Asynchronous mode: Don't care
    RCSTA1bits.CREN = 1;        // Enables receiver
    RCSTA1bits.ADDEN = 0;       // Don't care

    // BAUDCON1: BAUD RATE CONTROL REGISTER - pg279
    BAUDCON1bits.DTRXP = 0;     // Receive data (RX1) is not inverted (active-high)
    BAUDCON1bits.CKTXP = 0;     // Idle state for transmit (TX1) is high
    BAUDCON1bits.BRG16 = 1;     // 8-bit Baud Rate Generator
    BAUDCON1bits.WUE = 0;       // Receiver is operating normally
    BAUDCON1bits.ABDEN = 0;     // Auto-Baud Detect mode is disabled

    // Baud Rate Generator
    //SPBRGH1 = 0x03;             // Set baud rate for 19200 bps
    //SPBRG1 = 0x40;              // Actual baud rate: 19207; error = 0.04%
    SPBRGH1 = 0x00;             // Set baud rate for 115,200 bps
    SPBRG1 = 0x8A;               // Actual baud rate: 115,110; error: -0.08%

    // ANSELC ? PORTC ANALOG SELECT REGISTER - pg155
    ANSELC = 0x00;              // All Port C pins set to digital control

}   // end init_UART1

// cofigure UART2 routine
void init_UART2(void)
{
    // UART module is configured assuming a 64MHz OSC Clock and a 16MHz
    // instruction Cycle Clock
    
    // TXSTA2: TRANSMIT STATUS AND CONTROL REGISTER - pg277
    TXSTA2bits.CSRC = 0;        // Asynchronous mode: Don't care
    TXSTA2bits.TX9 = 0;         // 8-bit transmission
    TXSTA2bits.TXEN = 1;        // Transmit enabled
    TXSTA2bits.SYNC = 0;        // Asynchronous mode
    TXSTA2bits.SENDB = 0;       // Sync Break transmission completed
    TXSTA2bits.BRGH = 1;        // Low speed

    // RCSTA2: RECEIVE STATUS AND CONTROL REGISTER - pg278
    RCSTA2bits.SPEN = 1;        // Serial port enabled (configures RXx/DTx and TXx/CKx pins as serial port pins)
    RCSTA2bits.RX9 = 0;         // 8-bit reception
    RCSTA2bits.SREN = 0;        // Asynchronous mode: Don't care
    RCSTA2bits.CREN = 1;        // Enables receiver
    RCSTA2bits.ADDEN = 0;       // Don?t care

    // BAUDCON2: BAUD RATE CONTROL REGISTER - pg279
    BAUDCON2bits.DTRXP = 0;     // Receive data (RX2) is not inverted (active-high)
    BAUDCON2bits.CKTXP = 0;     // Idle state for transmit (TX2) is high
    BAUDCON2bits.BRG16 = 1;     // 8-bit Baud Rate Generator
    BAUDCON2bits.WUE = 0;       // Receiver is operating normally
    BAUDCON2bits.ABDEN = 0;     // Auto-Baud Detect mode is disabled

    // Baud Rate Generator
    SPBRGH2 = 0x06;             // Set baud rate for 9600
    SPBRG2 = 0x82;              // Actual baud rate: 9615; error = 0.16%

    // ANSELD ? PORTD ANALOG SELECT REGISTER - pg155
    ANSELD = 0x00;              // All Port D pins set to digital control

}   // end init_UART2
