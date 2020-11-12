
#pragma config FOSC = INTIO67
 #pragma config WDTEN = OFF, LVP = OFF
 
#include "pic18f45k20.h"

unsigned char LED_Display;
typedef enum { LEFT2RIGHT,
               RIGHT2LEFT} LEDDirections;
typedef enum {FALSE, TRUE} BOOL;
#define Switch_Pin      PORTBbits.RB0
#define DetectsInARow   5
void main (void)
{
    LEDDirections Direction = RIGHT2LEFT;
    BOOL SwitchPressed = FALSE;
   
    LED_Display = 1;            // initialize
   
    // Init I/O
    TRISD = 0b00000000;  // PORTD bits 7:0 are all outputs (0)
    LATD = 0;
   
     //INTCON2bits.RBPU = 0;       // enable PORTB internal pullups
    // WPUBbits.WPUB0 = 1;         // enable pull up on RB0
    //ANSELH = 0x00;              // AN8-12 are digital inputs (AN12 on RB0)
                                // RB0 is showing on AN12 on the high side so we set ASENLH
   // TRISBbits.TRISB0 = 1;       // PORTB bit 0 (connected to switch) is input (1)
   
    // Init Timer
     OSCCONbits.IRCF2 =1;
     OSCCONbits.IRCF1 =1;
     OSCCONbits.IRCF0 =1;
    T0CONbits.TMR0ON = 0;   //bit7   // 1 = Enables Timer0
                                     // 0 = Stops Timer0
    T0CONbits.T08BIT = 0;   //bit 6  // 1 = Timer0 is configured as an 8-bit timer/counter
                                     // 0= Timer0 is configured as a 16-bit timer/counter
    T0CONbits.T0CS = 0;     //bit 5   // if zero fosc is/4
                                      // 1 = Transition on T0CKI pin
                                      // 0 = Internal instruction cycle clock (CLKOUT)
      T0CONbits.T0SE = 0;              //bit 4  // Not used
                                     // 1 = Increment on high-to-low transition on T0CKI pin
                                     // 0 = Increment on low-to-high transition on T0CKI pin
    T0CONbits.PSA = 1;               //bit 3  // Timer0 pre scaler is assigned
                                     // 1 = TImer0 prescaler is NOT assigned. Timer0 clock input bypasses prescaler.
                                     // 0 = Timer0 prescaler is assigned. Timer0 clock input comes from prescaler output
              
    INTCONbits.TMR0IF = 1;          // clear roll-over interrupt flag
    
    
     T0CON = 0b00000111;             // 0b00001000 no prescale - increments every instruction clock
    //T0CON = 0b00000001;           // prescale 1:4 - four times the delay.
    
                                    // #7 111 = 1:256 prescale value
                                    // #6 110 = 1:128 prescale value
                                    // #5 101 = 1:64  prescale value
                                    // #4 100 = 1:32  prescale value
                                    // #3 011 = 1:16  prescale value
                                    // #2 010 = 1:8   prescale value
                                    // #1 001 = 1:4   prescale value
                                    // #0 000 = 1:2   prescale value
    TMR0H = 0;                      // clear timer - always write upper byte first
    TMR0L = 0;
    
   // OSCCON<6:4>
   // TMR0H= 0xB3; // INSERT RELOAD VALUE -Timer0 Register, High Byte
   // TMR0L= 0xB4;// Timer0 Register, Low Byte
    T0CONbits.TMR0ON = 1;           // start timer
   
    while (1)
    {
   
        if (Direction == LEFT2RIGHT)
        {
            LED_Display <<= 1;          // rotate display by 1 from 0 to 7
            if (LED_Display == 0)
                LED_Display = 1;        // rotated bit out, so set bit 0
        }
        if (Direction == RIGHT2LEFT)
        {
            LED_Display >>= 1;          // rotate display by 1 from 7 to 0
            if (LED_Display == 0)
                LED_Display = 0x80;     // rotated bit out, so set bit 7
        }
   
        LATD = LED_Display;         // output LED_Display value to PORTD LEDs
   
        do
        { // poll the switch while waiting for the timer to roll over.
            if (Switch_Pin == 1)
            { // look for switch released.
                SwitchPressed = FALSE;
            }
            else if (SwitchPressed == FALSE) // && (Switch_Pin == 0) due to if-else
            { // switch was just pressed
                SwitchPressed = TRUE;
                // change  direction
                if (Direction == LEFT2RIGHT)
                    Direction = RIGHT2LEFT;
                else
                    Direction = LEFT2RIGHT;
            }
   
        } while (INTCONbits.TMR0IF == 0);
   
        // Timer expired
        INTCONbits.TMR0IF = 0;          // Reset Timer flag
   
    }
       
}  
