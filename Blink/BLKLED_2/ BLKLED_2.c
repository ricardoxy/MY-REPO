
/*
 * File:   main.c
 *
 * Created on January 26, 2013, 14:12 PM */
// use timers register to make a delay
#pragma config FOSC = INTIO67
#pragma config WDTEN = OFF, LVP = OFF

#include "pic18f45k20.h"
//#include <xc.h>

void main (void){
   TRISD = 0;
   LATD = 0;
    //LATDbits.LATD2 = ~LATDbits.LATD2;
   // FOSC = 4MHZ
   //INTERNAL FREQUENCY IS FTIMER = 4MHZ/4 = 1 MHZ EACH TIMER PULSE IS EQUI TO 1US
   // DELAY OF 50 ms WE REUIQRE  50^10*3 PULSES TO EXPIRE = 50000 USECOND PULSES
   // 65536 - 50000 = 15536 IN 16 BIT MODE
  // ************ PAGE 76  ON DATA SHEET *************
   T0CONbits.TMR0ON = 0;   //bit7   // 1 = Enables Timer0
                                    // 0 = Stops Timer0
   T0CONbits.T08BIT = 0;   //bit 6  // 1 = Timer0 is configured as an 8-bit timer/counter
                                    // 0= Timer0 is configured as a 16-bit timer/counter
   T0CONbits.T0CS = 0;     //bit 5  // 1 = Transition on T0CKI pin
                                    // 0 = Internal instruction cycle clock (CLKOUT)
                                    // Internal clock SOURCE (CLKOUT)
                                    // if TOCS is = to 0 then is on timer mode
                                    // if TOCS is = to 1 then is on count mode
                                    // In this mode, Timer0 increments either on every rising or falling edge of pin RA4/T0CKI.
                                    //The incrementing edge is determined by the Timer0 Source Edge
                                    //Select bit, T0SE of the T0CON register; clearing this bit
                                    //selects the rising edge. Restrictions on the external
                                    // clock input are discussed below.
   T0CONbits.T0SE = 0;     //bit 4  // Not used
                                    // 1 = Increment on high-to-low transition on T0CKI pin
                                    // 0 = Increment on low-to-high transition on T0CKI pin
   T0CONbits.PSA = 0;      //bit 3  // Timer0 pre scaler is assigned
  
   INTCONbits.TMR0IF= 0;  //BIT 1  INT0IF: INT0 External Interrupt Flag bit
                          //    1 = The INT0 external interrupt occurred (must be cleared by software)
                          // 0 = The INT0 external interrupt did not occur
   TMR0H=0x3C;  // in dec 60
   //TMR0H= 0x3C; // INSERT RELOAD VALUE -Timer0 Register, High Byte
   //TMR0L= 0xB0;// Timer0 Register, Low Byte
   T0CONbits.T0PS2= 1; // bit 2  most signif
   T0CONbits.T0PS1= 1; // bit 1
   T0CONbits.T0PS0= 0; // bit 0    // 1:128 prescale value
                                   // #7 111 = 1:256 prescale value
                                   // #6 110 = 1:128 prescale value
                                   // #5 101 = 1:64  prescale value
                                   // #4 100 = 1:32  prescale value
                                   // #3 011 = 1:16  prescale value
                                   // #2 010 = 1:8   prescale value
                                   // #1 001 = 1:4   prescale value
                                   // #0 000 = 1:2   prescale value

   
   T0CONbits.TMR0ON = 1;     // Enables Timer0
   
   while(1)
   {
       while(TMR0 <254);
       //while(!INTCONbits.TMR0IF) //wait for timer overflow
          // TMR0H= 0x3C;
           // TMR0L= 0xB0;
            //LATD = ~LATD ;// toggle led
          LATDbits.LATD2 = ~LATDbits.LATD2;
          if (TMR0 == 2000){
              LATDbits.LATD3 = 1;
          }
           if (TMR0> 0){
              LATDbits.LATD4 = ~LATDbits.LATD4;
          }
          
     
           // INTCONbits.TMR0IF = 0;
            TMR0= 0;
   }
        
   
}
