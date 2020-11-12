
#pragma config FOSC = INTIO67
 #pragma config WDTEN = OFF, LVP = OFF
 
#include "pic18f45k20.h"


void main (void)
{
    
  //  LED_Display = 1;            // initialize
   
    // Init I/O
    TRISD = 0b00000000;  // PORTD bits 7:0 are all outputs (0)
    LATD = 0;
   
     //INTCON2bits.RBPU = 0;       // enable PORTB internal pullups
    // WPUBbits.WPUB0 = 1;         // enable pull up on RB0
    //ANSELH = 0x00;              // AN8-12 are digital inputs (AN12 on RB0)
                                // RB0 is showing on AN12 on the high side so we set ASENLH
   // TRISBbits.TRISB0 = 1;       // PORTB bit 0 (connected to switch) is input (1)
   //111 = 16 MHz (HFINTOSC drives clock directly)
   //110 = 8 MHz
   //101 = 4 MHz
   //100 = 2 MHz16
   //011 = 1 MHz(3)
   //010 = 500 kHz
   //001 = 250 kHz
   //000 = 31 kHz (from either HFINTOSC/512 or LFINTOSC directly)(2)
     
    OSCCONbits.IRCF2 =0;    //011 1MHZ
    OSCCONbits.IRCF1 =1;    //111 is 16MHZ
    OSCCONbits.IRCF0 =1;    // 101 is 4 MHZ
    
   // T0CONbits.TMR0ON = 0;   //bit7   // 1 = Enables Timer0
                                     // 0 = Stops Timer0
   // T0CONbits.T08BIT = 0;   //bit 6  // 1 = Timer0 is configured as an 8-bit timer/counter
                                     // 0= Timer0 is configured as a 16-bit timer/counter
  //  T0CONbits.T0CS = 0;     //bit 5   // if zero fosc is/4
                                      // 1 = Transition on T0CKI pin
                                      // 0 = Internal instruction cycle clock (CLKOUT)
  //  T0CONbits.T0SE = 0;              //bit 4  // Not used
                                     // 1 = Increment on high-to-low transition on T0CKI pin
                                     // 0 = Increment on low-to-high transition on T0CKI pin
  //  T0CONbits.PSA = 0;               //bit 3  // Timer0 pre scaler is assigned
                                     // 1 = TImer0 prescaler is NOT assigned. Timer0 clock input bypasses prescaler.
                                     // 0 = Timer0 prescaler is assigned. Timer0 clock input comes from prescaler output
              
   // INTCONbits.TMR0IF = 1;          // clear roll-over interrupt flag
    
    
     T0CON = 0b00000001;             // 0b00001000 no prescale - increments every instruction clock
    //T0CON = 0b00000000;           // prescale 1:4 - four times the delay.
    
                                    // #7 111 = 1:256 prescale value
                                    // #6 110 = 1:128 prescale value
                                    // #5 101 = 1:64  prescale value
                                    // #4 100 = 1:32  prescale value  16  sec delay
                                    // #3 011 = 1:16  prescale value  8 sec   4 on   4 off
                                    // #2 010 = 1:8   prescale value  4 sec  delay   2 on   2 off
                                    // #1 001 = 1:4   prescale value  one second delay per pulse full cycle is 2 seconds
                                    // #0 000 = 1:2   prescale value  with 1MHZ  and this pre we get 1/2 sec delay full cycle one second
    //TMR0H = 0;                      // clear timer - always write upper byte first
   // TMR0L = 0;
    
    INTCONbits.TMR0IF = 1;          // clear roll-over interrupt flag
   // OSCCON<6:4>
   // TMR0H= 0xB3; // INSERT RELOAD VALUE -Timer0 Register, High Byte
   // TMR0L= 0xB4;// Timer0 Register, Low Byte
   T0CONbits.TMR0ON = 1;           // start timer
   
    
     if (OSCCONbits.IRCF2 ==0 && OSCCONbits.IRCF1 == 1 &&  OSCCONbits.IRCF0==1 )
        {
        LATDbits.LATD1 = 1;
        }
      
    
    while (1)
    {
       // INTCONbits.TMR0IF = 0;          // Reset Timer flag
       
       
      // while ( LATDbits.LATD7!=0);
       
        LATDbits.LATD7 = ~LATDbits.LATD7; // toggle LATD
        while (INTCONbits.TMR0IF == 0);
       //
        
         if (INTCONbits.TMR0IF== 1 ) // in 8 bit mode timer goes from 0 to 255
        
           LATDbits.LATD3 = 1;
           
           
        
        
        // Timer expired
         INTCONbits.TMR0IF = 0;          // Reset Timer flag
    }
      T0CONbits.TMR0ON = 0;           // turn off timer
     // INTCONbits.TMR0IF = 0;          // Reset Timer flag
    if (INTCONbits.TMR0IF== 0 ) // in 8 bit mode timer goes from 0 to 255
        
           LATDbits.LATD6 = 1;
    }
       
//A timer uses the frequency of the internal clock, and generates delay.
