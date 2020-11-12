
#pragma config FOSC = INTIO67
#pragma config WDTEN = OFF, LVP = OFF
#include "pic18f45k20_Config.h"
//#include "pic18f45k20.h"
#include "stdio.h"
#include <xc.h>


void main (void)
{
     TRISD = 0b00000000;  // PORTD bits 7:0 are all outputs (0)
     LATD = 0;
     OSC_freq();
     Timer_0();
    interrups_initial();
      //T0CON = 0b00000001;
     //void interrups_initial(void);
       //INTCONbits.TMR0IF = 1;
     //void Timer_0(void);
     T0CONbits.TMR0ON = 1;           // start timer
     if (OSCCONbits.IRCF2 ==0 && OSCCONbits.IRCF1 == 1 &&  OSCCONbits.IRCF0==1 )
        {
        LATDbits.LATD1 = 1;
        }
     
    while (1)
    {
       
        LATDbits.LATD7 = ~LATDbits.LATD7; // toggle LATD
        while (INTCONbits.TMR0IF == 0);
        if (INTCONbits.TMR0IF== 1 ) // in 8 bit mode timer goes from 0 to 255
        LATDbits.LATD3 = 1;
        INTCONbits.TMR0IF = 0;          // Reset Timer flag
    }
        T0CONbits.TMR0ON = 0;           // turn off timer
    
    
    }
       
//A timer uses the frequency of the internal clock, and generates delay.
