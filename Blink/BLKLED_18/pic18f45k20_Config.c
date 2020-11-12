/*Config Code File
 * File:   PIC18_config.c
 * Author: Ricardo Munoz
 *
 *
 * Created on: Aug 18, 2020
 *
 * This file was created to configure the pic18f45k20 device.
 *
 * Compiler: XC8
 * MPLAB IDE: X
 */

/********************************INCLUDES**************************************/
//#include "pic18f45k20.h"
#include "pic18f45k20_Config.h"

 #include <xc.h>
//#include <stdio.h>

//SUMMARY OF REGISTERS ASSOCIATED WITH CLOCK SOURCES                       //Power on reset Brown out reset
//NAME       Bit7     Bit6      Bit5   Bit4   Bit3   Bit2   Bit1   Bit0    //Value on POR, BOR // Value on otherResets(1)
//CONFIG1H   IESO     FCMEN     ?      ?      FOSC3  FOSC2  FOSC1  FOSC0     ?                    ?
//INTCON     GIE/GIEH PEIE/GIEL TMR0IE INT0IE RBIE   TMR0IF INT0IF RBIF      0000 000x            0000 000x
//OSCCON     IDLEN    IRCF2     IRCF1  IRCF0  OSTS   IOFS   SCS1   SCS0      0011 q000            0011 q000
//OSCTUNE    INTSRC   PLLEN     TUN5   TUN4   TUN3   TUN2   TUN1   TUN0      0000 0000            000u uuuu
//PIE2       OSCFIE   C1IE      C2IE   EEIE   BCLIE  HLVDIE TMR3IE CCP2IE    0000 0000            0000 0000
//PIR2       OSCFIF   C1IF      C2IF   EEIF   BCLIF  HLVDIF TMR3IF CCP2IF    0000 0000            0000 0000
//IPR2       OSCFIP   ?         ?      ?      ?      ?      ?      ?         1111 1111            1111 1111

// OSCCON: OSCILLATOR CONTROL REGISTER pg 29
//The OSCCON register (Register 2-1) controls several
// aspects of the device clock?s operation, both in full
// power operation and in power-managed modes.
// configure oscillator routine

void OSC_freq (void)
{
    OSCCON = 0b01010000;
  
 //OSCCONbits.IDLEN = 0;       // Bit 7
                               //if 1 = Device enters **Idle** mode on SLEEP instruction
                               //if 0 = Device enters **Sleep** mode on SLEEP instruction
    
 //OSCCONbits.IRCF2 = 1;       // Bit 6 (HFINTOSC 16MHz  drives clock directly)
 //OSCCONbits.IRCF1 = 0;       // Bit 5
 //OSCCONbits.IRCF0 = 1;       // Bit 4
                                
                                // 111 = 16 MHz (HFINTOSC drives clock directly)
                                // 110 = 8 MHz
                                // 101 = 4 MHz
                                // 100 = 2 MHz
                           //***// 011 = 1 MHz if nothing is selected 1MHZ is selected by default (3)
                                // 010 = 500 kHz
                                // 001 = 250 kHz
                                // 000 = 31 kHz (from either HFINTOSC/512 or LFINTOSC directly)(2)
    
 //   OSCCONbits.OSTS =0;         // Bit 3
                                // 1 = Device is running from the clock defined by FOSC<2:0> of the CONFIG1 register
                                // 0 = Device is running from the internal oscillator (HFINTOSC or LFINTOSC)
                                //
  //  OSCCONbits.IOFS =0;         // Bit 2
                                // 1 = HFINTOSC frequency is stable
                                // 0 = HFINTOSC frequency is not stable
                                   
    
 //   OSCCONbits.SCS1 = 0;         // Bit 1 *********************
 //   OSCCONbits.SCS0 = 0;         // Bit 0
                                 // 1x = Internal oscillator block
                                 // 01 = Secondary (Timer1) oscillator
                                 // 00 = Primary clock (determined by CONFIG1H[FOSC<3:0>]).
                  

                                // OSCTUNE: OSCILLATOR TUNING REGISTER - pg33
                                // OSCTUNE is responsible for tuning the frequency within a range of +/-12 percent
                                // on the selected frequency.
    //OSCTUNEbits.INTSRC = 0;     // Bit 7
                                // if 1 = 31.25 kHz device clock derived from 16 MHz HFINTOSC source (divide-by-512 enabled)
                                // if 0 = 31 kHz device clock derived directly from LFINTOSC internal oscillator
   
    
    
   // OSCTUNEbits.PLLEN = 0;      // Frequency Multiplier PLL for HFINTOSC Enable bit
                                // 1 = PLL enabled for HFINTOSC (8 MHz and 16 MHz only)
                                // 0 = PLL disabled
    
    
}


//******************************************************************************************************************//
// interrupts
// internal interrus timers ad conveter serial io eeprom  low volt detectoion module
// ITCON register usually deals with EXTERNAL interrups
// PIR PIE IPR deals with interal interrups
// each interrupt source has 3 bits to control opertaion
// first flag bit indicates a interrup occur
// second a bit allows for interrupt to the address vector when set
// third bit selects high or low priority
                               // RCON: RESET CONTROL REGISTER - pg 51
                               // Device Reset events are tracked through the RCON
                               // register (Register 4-1). The lower five bits of the register indicate
                               // that a specific Reset event has occurred. In
                               // most cases, these bits can only be cleared by the event
                               // and must be set by the application after the event
                               // There are ten registers which are used to control
                               // interrupt operation. These registers are:
                               //  ? RCON
                               //  ? INTCON
                               //  ? INTCON2
                               //  ? INTCON3
                               //  ? PIR1, PIR2
                               //  ? PIE1, PIE2
                               //  ? IPR1, IPR2
  // INTCON: INTERRUPT CONTROL REGISTER - pg116
  //NAME       Bit7      Bit6      Bit5    Bit4    Bit3   Bit2   Bit1   Bit0   //Value on POR,BOR // Value on otherResets(1)
  //RCON       IPEN      SBOREN(1) ?       RI      TO     PD     POR(2) BOR     0q-1 11q0
  //INTCON     GIE/GIEH  PEIE/GIEL TMR0IE  INT0IE  RBIE   TMR0IF INT0IF RBIF    0000 000x         0000 000u uuuu uuuu(1)
  //INTCON2    RBPU      INTEDG0   INTEDG1 INTEDG2 ?      TMR0IP ?      RBIP    1111 -1-1         1111 -1-1 uuuu -u-u(1)
  //INTCON3    INT2IP    INT1IP    ?       INT2IE  INT1IE ?      INT2IF INT1IF  11-0 0-00         11-0 0-00 uu-u u-uu(1)
  //       ***REGISTERS ASSOCIATED WITH PARALLEL SLAVE PORT
  //PIR1       PSPIF(1)  ADIF     RCIF     TXIF    SSPIF  CCP1IF TMR2IF TMR1IF  0000 0000         0000 0000
  //PIE1       PSPIE(1)  ADIE     RCIE     TXIE    SSPIE  CCP1IE TMR2IE TMR1IE  0000 0000         0000 0000
  //IPR1       PSPIP(1)  ADIP     RCIP     TXIP    SSPIP  CCP1IP TMR2IP TMR1IP  1111 1111         1111 1111
  //     ***REGISTERS ASSOCIATED WITH TIMER3 AS A TIMER/COUNTER
  //PIR2       OSCFIF    C1IF     C2IF     EEIF    BCLIF  HLVDIF TMR3IF CCP2IF  0000 0000         0000 0000
  //PIE2       OSCFIE    C1IE     C2IE     EEIE    BCLIE  HLVDIE TMR3IE CCP2IE  0000 0000         0000 0000
  //IPR2       OSCFIP    C1IP     C2IP     EEIP    BCLIP  HLVDIP TMR3IP CCP2IP  1111 1111         1111 1111

void interrups_initial(void)
{
    PIR1bits.RCIF = 0; //RCIF: EUSART Receive Interrupt Flag bit  (RC1IF per email)
                            //1 = The EUSART receive buffer, RCREG, is full (cleared when RCREG is read)
                            //0 = The EUSART receive buffer is empty
    PIE1bits.RCIE = 1;  //RCIE: EUSART Receive Interrupt Enable bit
                            //1 = Enables the EUSART receive interrupt
                            //0 = Disables the EUSART receive interrupt
  //RCON = 0b00011100; ??
 // RCON register sets up the goblal priority for all interrups
    

    RCONbits.IPEN = 0;          // Bit 7 pg 52
                                // IPEN: Interrupt Priority Enable bit
                                // 1 = Enable priority levels on interrupts
                                // 0 = Disable priority levels on interrupts (PIC16CXXX Compatibility mode)
    
    
  //  RCONbits.SBOREN = 0;        // bit 6 SBOREN: BOR Software Enable bit(1)
                                // If BOREN<1:0> = 01:
                                // 1 = BOR is enabled
                                // 0 = BOR is disabled
                                // If BOREN<1:0> = 00, 10 or 11:
                                // Bit is disabled and read as ?0?.
       
                                // Bit 5 Unimplemented: Read as ?0?
        
   // RCONbits.RI= 1;             // Bit 4 RI: RESET Instruction Flag bit
                                // 1 = The RESET instruction was not executed (set by firmware or Power-on Reset)
                                // 0 = The RESET instruction was executed causing a device Reset (must be set in
                                //firmware after a code-executed Reset occurs)
                             
  //  RCONbits.RI= 1;             // Bit 3 TO: Watchdog Time-out Flag bit
                                // 1 = Set by power-up, CLRWDT instruction or SLEEP instruction
                                // 0 = A WDT time-out occurred
   
  //  RCONbits.PD= 1;             // Bit 2 PD: Power-down Detection Flag bit
                                // 1 = Set by power-up or by the CLRWDT instruction
                                // 0 = Set by execution of the SLEEP instruction
  
   // RCONbits.POR= 0;            // bit 1 POR: Power-on Reset Status bit(2)
                                //  1 = No Power-on Reset occurred
                                // 0 = A Power-on Reset occurred (must be set in software after a Power-on Reset occurs)
   
  //  RCONbits.BOR= 0;            // bit 0 BOR: Brown-out Reset Status bit(3)
                                // 1 = A Brown-out Reset has not occurred (set by firmware only
                                // 0 = A Brown-out Reset occurred (must be set by firmware after a POR or Brown-out
                                // Reset occurs)
    ///*****************INTCON************************************//
    //INTCONbits.INT0IF = 0;//INT0IF: INT0 External Interrupt Flag bit
                              //1 = The INT0 external interrupt occurred (must be cleared by software)
                              //0 = The INT0 external interrupt did not occur
     //INTCONbits.INT0IE=1;   // pg 102  Enables the INT0 external interrupt
    INTCON2bits.INTEDG0=1 ;// interrupt on the rising  edge
    INTCONbits.GIE = 1; //global interrupt enable bit
    INTCONbits.PEIE = 1;
 ///*****************INTCON************************************//
  //  INTCONbits.GIE_GIEH = 0;    // Bit 7  Enables all unmasked interrupts  these are relate to  RCONbits.IPEN when enable
                                // When IPEN = 0:   PG 109
                                // 1 = Enables all unmasked interrupts
                                // 0 = Disables all interrupts including peripherals
                                // When IPEN = 1:
                                // 1 = Enables all high priority interrupts
                                // 0 = Disables all interrupts including low priority.
    
   // INTCONbits.PEIE_GIEL = 0;   // Bit 6 Enables all unmasked peripheral interrupts
                                // When IPEN = 0:
                                // 1 = Enables all unmasked peripheral interrupts
                                // 0 = Disables all peripheral interrupts
                                // When IPEN = 1:
                                // 1 = Enables all low priority interrupts
                                // 0 = Disables all low priority interrupts

  //  INTCONbits.TMR0IE = 0;      // Bit 5 TMR0 Overflow Interrupt Enable bit
                                //1 = Enables the TMR0 overflow interrupt
                                //0 = Disables the TMR0 overflow interrupt
    
   INTCONbits.INT0IE = 1;      // Bit 4 INT0 External Interrupt Enable bit
                                //1 = Enables the INT0 external interrupt
                                //0 = Disables the INT0 external interrupt
   
  //  INTCONbits.RBIE = 0;        // Bit 3 RB Port Change Interrupt Enable bit
                                //1 = Enables the RB port change interrupt
                                //0 = Disables the RB port change interrup
    
   // INTCONbits.TMR0IF = 1;      // Bit 2 TMR0 Overflow Interrupt Flag bit *******************************************
                                //1 = TMR0 register has overflowed (must be cleared by software)
                                //0 = TMR0 register did not overflow
    
    INTCONbits.INT0IF = 1;      // Bit 1 INT0 External Interrupt Flag bit
                                //1 = The INT0 external interrupt occurred (must be cleared by software)
                                // 0 = The INT0 external interrupt did not occur
    
   // INTCONbits.RBIF= 0;         // Bit 0 RB Port Change Interrupt Flag bit(1)
                                //1 = At least one of the RB<7:4> pins changed state (must be cleared by software)
                                //0 = None of the RB<7:4> pins have changed state
  



}




//********************************************************************************************************//
    
    //TIMER pg 58, 155  // T0CON: TIMER0 CONTROL REGISTER
    //NAME        Bit7      Bit6      Bit5    Bit4    Bit3   Bit2   Bit1   Bit0   //Value on POR,BOR
    //TMR0H       Timer0 Register, High Byte                                        0000 0000
    //TMR0L       Timer0 Register, Low Byte                                         xxxx xxxx
    //T0CON       TMR0ON    T08BIT    T0CS    T0SE    PSA    T0PS2  T0PS1  T0PS0    1111 1111

void Timer_0(void)
{
    T0CON = 0b10000001;
               

   // T0CONbits.TMR0ON = 0;      // Bit 7 Enables Timer0  Timer0 On/Off Control bit*********
                               //  1 = Enables Timer0
                               //  0 = Stops Timer0
   // T0CONbits.T08BIT = 0;      // Bit 6 Timer0 8-bit/16-bit Control bit
                               //  1 = Timer0 is configured as an 8-bit timer/counter
                               //  0 = Timer0 is configured as a 16-bit timer/counter
   // T0CONbits.T0CS = 0;        // Bit 5  Timer0 Clock Source Select bit ******************
                               //  1 = Transition on T0CKI pin
                               //  0 = Internal instruction cycle clock (CLKOUT)
   // T0CONbits.T0SE = 0;        // Bit 4  Timer0 Source Edge Select bit
                               //  1 = Increment on high-to-low transition on T0CKI pin
                               //  0 = Increment on low-to-high transition on T0CKI pin
  //  T0CONbits.PSA =0;         // Bit 3  Timer0 Prescaler Assignment bit
                               // 1 = TImer0 prescaler is NOT assigned. Timer0 clock input bypasses prescaler.
                               // 0 = Timer0 prescaler is assigned. Timer0 clock input comes from prescaler output
    
    
   // T0CONbits.T0PS2 = 0;       // Bit 2-0  Timer0 Prescaler Select bits
   // T0CONbits.T0PS1 = 0;
   // T0CONbits.T0PS0 = 1;
                               // 111 = 1:256 prescale value
                               // 110 = 1:128 prescale value
                               // 101 = 1:64 prescale value
                               // 100 = 1:32 prescale value
                               // 011 = 1:16 prescale value
                               // 010 = 1:8 prescale value
                               // 001 = 1:4 prescale value one second delay per pulse full cycle is 2 seconds
                               // 000 = 1:2 prescale value with 1MHZ  and this pre we get 1/2 sec delay full cycle one second
    
}
     

//*****TIMER 1 pg 58, 157
//NAME        Bit7     Bit6      Bit5    Bit4    Bit3    Bit2   Bit1   Bit0   //Value on POR,BOR
//TMR1H       Timer1 Register, High Byte                                        xxxx xxxx
//TMR1L       Timer1 Register, Low Bytes                                        xxxx xxxx
//T1CON       RD16     T1RUN     T1CKPS1 T1CKPS0 T1OSCEN T1SYNC TMR1CS TMR1ON   0000 0000

void Timer_1(void){
    
    T1CONbits.RD16 = 0;    // Bit 7 RD16: 16-bit Read/Write Mode Enable bit
                           // 1 = Enables register read/write of TImer1 in one 16-bit operation
                           // 0 = Enables register read/write of Timer1 in two 8-bit operations
    
    T1CONbits.T1RUN = 0;   // Bit 6  Timer1 System Clock Status bit
                           // 1 = Main system clock is derived from Timer1 oscillator
                           // 0 = Main system clock is derived from another source
   
    T1CONbits.T1CKPS1 = 0; // Bit 5 <1:0>: Timer1 Input Clock Prescale Select bits
    T1CONbits.T1CKPS0 = 0; // Bit 4
                           // 11 = 1:8 Prescale value
                           // 10 = 1:4 Prescale value
                           // 01 = 1:2 Prescale value
                           // 00 = 1:1 Prescale value
    
    T1CONbits.T1OSCEN = 0; // Bit 3  Timer1 Oscillator Enable bit
                           // 1 = Timer1 oscillator is enabled
                           // 0 = Timer1 oscillator is shut off
    
    T1CONbits.T1SYNC = 0;  // Bit 2  Timer1 External Clock Input Synchronization Select bit
                           // When TMR1CS = 1:
                           // 1 = Do not synchronize external clock input
                           // 0 = Synchronize external clock input
                           // When TMR1CS = 0:
                           // This bit is ignored. Timer1 uses the internal clock when TMR1CS = 0.
    
    
    T1CONbits.TMR1CS = 0;  // Bit 1 : Timer1 Clock Source Select bit
                           // 1 = External clock from pin RC0/T1OSO/T13CKI (on the rising edge)
                           // 0 = Internal clock (FOSC/4)
   
    T1CONbits.TMR1ON = 0;  // Bit 0 Timer1 On bit
                           // 1 = Enables Timer1
                           // 0 = Stops Timer1
}


//*****TIMER 2 pg 58, 167
//NAME        Bit7      Bit6      Bit5     Bit4     Bit3     Bit2   Bit1    Bit0     //Value on POR,BOR
//TMR2        Timer2 Register                                                           0000 0000
//PR2         Timer2 Period Register                                                    1111 1111
//T2CON       ?         T2OUTPS3  T2OUTPS2 T2OUTPS1 T2OUTPS0 TMR2ON T2CKPS1 T2CKPS0    -000 0000

void Timer_2(void){
    
    //T2CONbits.U = 0;         // Bit 7 Unimplemented read as zero
    T2CONbits.T2OUTPS3 = 0;    // Bit 6
    T2CONbits.T2OUTPS2 = 0;    // Bit 5
    T2CONbits.T2OUTPS1 = 0;    // Bit 4
    T2CONbits.T2OUTPS0 = 0;    // Bit 3   Timer2 Output Postscale Select bits 6,5,4,3
                               //0000 = 1:1 Postscale
                               //0001 = 1:2 Postscale
                               //?
                               //?
                               //?
                               //1111 = 1:16 Postscale
    
    T2CONbits.TMR2ON = 0;        // Bit 2 Timer2 On bit
                               // 1 = Timer2 is on
                               // 0 = Timer2 is off
    
    
    T2CONbits.T2CKPS1 = 0;    // Bit 1
    T2CONbits.T2CKPS0 = 0;    // Bit 0   Timer2 Clock Prescale Select bits 1,0
                           // 00 = Prescaler is 1
                           // 01 = Prescaler is 4
                           // 1x = Prescaler is 16
}


//*****TIMER 3 pg 59, 169
//NAME        Bit7      Bit6    Bit5    Bit4    Bit3   Bit2   Bit1   Bit0   //Value on POR,BOR
//TMR3H       Timer3 Register, High Byte                                      xxxx xxxx
//TMR3L       Timer3 Register, Low Byte                                       xxxx xxxx
//T3CON       RD16      T3CCP2  T3CKPS1 T3CKPS0 T3CCP1 T3SYNC TMR3CS TMR3ON   0000 0000
void Timer_3(void){
    
    T3CONbits.RD16 = 0;    // Bit 7
                           // 1 = Enables register read/write of Timer3 in one 16-bit operation
                           // 0 = Enables register read/write of Timer3 in two 8-bit operations
    
    
    T3CONbits.T3CCP2 = 0;  // Bit 6
    T3CONbits.T3CCP1 = 0;  // Bit 3   Timer3 and Timer1 to CCPx Enable bits 6 and 3
                           // 1x = Timer3 is the capture/compare clock source for CCP1 and CP2
                           // 01 = Timer3 is the capture/compare clock source for CCP2 and
                           // Timer1 is the capture/compare clock source for CCP1
                           // 00 = Timer1 is the capture/compare clock source for CCP1 and CP2
    
    T3CONbits.T3CKPS1 = 0; // Bit 5
    T3CONbits.T3CKPS0 = 0; // Bit 4  Timer3 Input Clock Prescale Select bits  5 and 4
                           // 11 = 1:8 Prescale value
                           // 10 = 1:4 Prescale value
                           // 01 = 1:2 Prescale value
                           // 00 = 1:1 Prescale value
    
    T3CONbits.T3SYNC = 0;  // Bit 2 Timer3 External Clock Input Synchronization Control bit
                           // (Not usable if the device clock comes from Timer1/Timer3.)
                           // When TMR3CS = 1:
                           // 1 = Do not synchronize external clock input
                           // 0 = Synchronize external clock input
                           // When TMR3CS = 0:
                           // This bit is ignored. Timer3 uses the internal clock when TMR3CS = 0.
    
    T3CONbits.TMR3CS = 0;  // Bit 1  Timer3 Clock Source Select bit
                           // 1 = External clock input from Timer1 oscillator or T13CKI
                           // (on the rising edge after the first falling edge)
                           // 0 = Internal clock (FOSC/4)
    
    T3CONbits.TMR3ON = 0;  // Bit 0 Timer3 On bit
                           // 1 = Enables Timer3
                           // 0 = Stops Timer3
}


    
    
//*************************************************************************************
//EUSART link to timer2 // REGISTERS ASSOCIATED WITH ASYNCHRONOUS TRANSMISSION

//NAME    Bit7      Bit6      Bit5   Bit4   Bit3   Bit2   Bit1   Bit0   //Value on POR,BOR
//INTCON  GIE/GIEH  PEIE/GIEL TMR0IE INT0IE RBIE   TMR0IF INT0IF RBIF 57
//PIR1    PSPIF(1)  ADIF      RCIF   TXIF   SSPIF  CCP1IF TMR2IF TMR1IF 60
//PIE1    PSPIE(1)  ADIE      RCIE   TXIE   SSPIE  CCP1IE TMR2IE TMR1IE 60
//IPR1    PSPIP(1)  ADIP      RCIP   TXIP   SSPIP  CCP1IP TMR2IP TMR1IP 60
//RCSTA   SPEN      RX9       SREN   CREN   ADDEN  FERR   OERR   RX9D 59
//TXREG   EUSART Transmit Register 59
//TXSTA   CSRC      TX9       TXEN   SYNC   SENDB  BRGH   TRMT   TX9D 59
//BAUDCON ABDOVF    RCIDL     DTRXP  CKTXP  BRG16  ?      WUE    ABDEN 59
//SPBRGH  EUSART Baud Rate Generator Register, High Byte 59
//SPBRG   EUSART Baud Rate Generator Register, Low Byte 59
//RCREG   EUSART Receive Register   0000 0000 59, 234


// The operation of the EUSART module is controlled
// through three registers:  pg 236

//? Transmit Status and Control (TXSTA)
//? Receive Status and Control (RCSTA)
//? Baud Rate Control (BAUDCON)

//NAME    Bit7      Bit6      Bit5   Bit4   Bit3   Bit2   Bit1   Bit0   //Value on POR,BOR
//TXSTA   CSRC      TX9       TXEN   SYNC   SENDB  BRGH   TRMT   TX9D     0000 0010
//RCSTA   SPEN      RX9       SREN   CREN   ADDEN  FERR   OERR   RX9D     0000 000x
//BAUDCON ABDOVF    RCIDL     DTRXP  CKTXP  BRG16  ?      WUE    ABDEN    0100 0-00

// instruction Cycle Clock


// The EUSART receiver is enabled for asynchronous
// operation by configuring the following three control bits:
// ? CREN = 1
// ? SYNC = 0
// ? SPEN = 1

void EUSART(void)
{
   TXSTA =  0b00100000;
   RCSTA =  0b10010000;
   BAUDCON =0b00001000;
   SPBRG= 25;
   //TXSTA: TRANSMIT STATUS AND CONTROL REGISTER - pg244
   
    
  //  TXSTAbits.CSRC = 0;       // Bit 7  Asynchronous mode:
                                // Don?t care
                                // Synchronous mode:
                                // 1 = Master mode (clock generated internally from BRG)
                                // 0 = Slave mode (clock from external source)
    
  //  TXSTAbits.TX9 = 0;          // Bit 6    9-bit Transmit Enable bit
                                // 1 = Selects 9-bit transmission
                                // 0 = Selects 8-bit transmission
    
  //  TXSTAbits.TXEN = 1;         // Bit 5 Transmit enabled   bit****************************
                                // 1 = Transmit enabled
                                // 0 = Transmit disabled
    
  //  TXSTAbits.SYNC = 0;         // Bit 4 EUSART Mode Select bit
                                // 1 = Synchronous mode
                                // 0 = Asynchronous mode
    
  //  TXSTAbits.SENDB = 0;        // Bit 3 Send Break Character bit
                                // Asynchronous mode:
                                // 1 = Send Sync Break on next transmission (cleared by hardware upon completion)
                                // 0 = Sync Break transmission completed
                                // Synchronous mode:
                                // Don?t care
    
  //  TXSTAbits.BRGH = 0;         // Bit 2  High Baud Rate Select bit
                                // Asynchronous mode:
                                // 1 = High speed
                                // 0 = Low speed
                                // Synchronous mode:
                                // Unused in this mode
    
   // TXSTAbits.TRMT = 1;         // Bit 1  Transmit Shift Register Status bit
                                // 1 = TSR empty
                                // 0 = TSR full
    
  //  TXSTAbits.TX9D = 0;         // Bit 0 Ninth bit of Transmit Data
                                //Can be address/data bit or a parity bit.
                                //SREN/CREN overrides TXEN in Sync mode

    
    //**********************RCSTA =0b10010000**************************//
   // RCSTA1: RECEIVE STATUS AND CONTROL REGISTER - pg245
    
 //   RCSTAbits.SPEN = 1;      // Bit 7 Serial port enabled
                               // 1 = Serial port enabled (configures RX/DT and TX/CK pins as serial port pins)
                               // 0 = Serial port disabled (held in Reset)
    
 //   RCSTAbits.RX9 = 0;         // Bit 6  9-bit Receive Enable bit
                               // 1 = Selects 9-bit reception
                               // 0 = Selects 8-bit reception
    
  //  RCSTAbits.SREN = 0;        // Bit 5 Single Receive Enable bit
                               // Asynchronous mode:
                               // Don?t care
                               // Synchronous mode ? Master:
                               // 1 = Enables single receive
                               // 0 = Disables single receive
                               // This bit is cleared after reception is complete.
                               // Synchronous mode ? Slave
                               // Don?t care
    
  // RCSTAbits.CREN = 1;        // Bit 4  Continuous Receive Enable bit
                               // Asynchronous mode:
                               // 1 = Enables receiver
                               // 0 = Disables receiver
                               // Synchronous mode:
                               // 1 = Enables continuous receive until enable bit CREN is cleared (CREN overrides SREN)
                               // 0 = Disables continuous receive
                                
  //  RCSTAbits.ADDEN = 0;     // Bit 3 Address Detect Enable bit
                               // Asynchronous mode 9-bit (RX9 = 1):
                               //  1 = Enables address detection, enable interrupt and
                               //load the receive buffer when RSR<8> is set
                               // 0 = Disables address detection, all bytes are received and
                               //ninth bit can be used as parity bit
                               // Asynchronous mode 8-bit (RX9 = 0):
                               // Don?t care
    
  //  RCSTAbits.FERR = 0;       // Bit 2  Framing Error bit
                               // 1 = Framing error (can be updated by reading RCREG register and receive next valid byte)
                               // 0 = No framing error
    
  //  RCSTAbits.OERR = 0;      // Bit 1  Overrun Error bit
                               // 1 = Overrun error (can be cleared by clearing bit CREN)
                               // 0 = No overrun error
    
  //  RCSTAbits.RX9D = 0;      // Bit 0  Ninth bit of Received Data
                               //This can be address/data bit or a parity bit and
                               //must be calculated by user firmware
    

    //********************** BAUDCON =0b00101000;**************************//
    // BAUDCON: BAUD RATE CONTROL REGISTER - pg246
    //BAUDCONbits.ABDOVF = 0;     // Bit 7 Auto-Baud Detect Overflow bit
                                // Asynchronous mode:
                                // 1 = Auto-baud timer overflowed
                                // 0 = Auto-baud timer did not overflow
                                // Synchronous mode:
                                // Don?t care
    
   // BAUDCONbits.RCIDL = 0;     // Bit 6 Receive Idle Flag bit
                               // Asynchronous mode:
                               // 1 = Receiver is Idle
                               // 0 = Start bit has been detected and the receiver is active
                               // Synchronous mode:
                               // Don?t care
    
  //  BAUDCONbits.DTRXP = 1;   // Bit 5 Data/Receive Polarity Select bit
                               // Asynchronous mode:
                               // 1 = Receive data (RX) is inverted (active-low)
                               // 0 = Receive data (RX) is not inverted (active-high)
                               // Synchronous mode:
                               // 1 = Data (DT) is inverted (active-low)
                               // 0 = Data (DT) is not inverted (active-high)
    
   // BAUDCONbits.CKTXP = 0;   // Bit 4 Clock/Transmit Polarity Select bit
                               // Asynchronous mode:
                               // 1 = Idle state for transmit (TX) is low
                               // 0 = Idle state for transmit (TX) is high
                               // Synchronous mode:
                               // 1 = Data changes on the falling edge of the clock and is sampled on the rising edge of the clock
                               // 0 = Data changes on the rising edge of the clock and is sampled on the falling edge of the clock
        
   // BAUDCONbits.BRG16 = 1;   // Bit 3 16-bit Baud Rate Generator bit
                               // 1 = 16-bit Baud Rate Generator is used (SPBRGH:SPBRG)
                               // 0 = 8-bit Baud Rate Generator is used (SPBRG)
    
    //BAUDCONbits.Unimplemented = 0; // Bit 2 unimplemented read as zero
    
    
    
   // BAUDCONbits.WUE = 0;       // Bit 1  Wake-up Enable bit
                               // Asynchronous mode:
                               // 1 = Receiver is waiting for a falling edge. No character will be
                               // received but RCIF will be set on the falling
                               // edge. WUE will automatically clear on the rising edge.
                               // 0 = Receiver is operating normally
                               // Synchronous mode:
                               // Don?t care
        
 //   BAUDCONbits.ABDEN = 0;     // Bit 0  Auto-Baud Detect Enable bit
                               // Asynchronous mode:
                               // 1 = Auto-Baud Detect mode is enabled (clears when auto-baud is complete)
                               // 0 = Auto-Baud Detect mode is disabled
                               // Synchronous mode:
                               // Don?t care

    // Baud Rate Generator
    // SPBRGH EUSART Baud Rate Generator Register, High Byte 59
    // SPBRG EUSART Baud Rate Generator Register, Low Byte 59
    // SPBRG = 0;
    // when   BAUDCONbits.BRG16= 1; // 16 bit baud rate mode
         // fosc/16(value+1 )= baudrate
         // SPBRG = Fosc/(16x9600) -1
         // you can change the Fosc by setting OSCCONbits.IRCF
         // SPBRG = (4MHZ/ (16x9600)) -1  =25
         // 9600 baud rate value is 25
         // SPBRG = (@16MHZ/ (16x9600)) -1  =103.1
}

   void delay_ms(int delay_time)
{
    int idx;
    for(idx=0; idx<delay_time;++idx)
    {
       // T0CONbits.TMR0ON = 0;
        TMR0 = 0;
        while(TMR0 < 1000);
    }

    
}





