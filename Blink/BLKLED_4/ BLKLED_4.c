/*
 * File:   main.c
 *
 * Created on January 26, 2013, 14:12 PM */


#pragma config FOSC = INTIO67
#pragma config WDTEN = OFF, LVP = OFF

#include "pic18f45k20.h"
 
#define SCALE_FACTOR_TIME 10
#define BTN_IGNORE_FACTOR 10
 
void delay(int time);
 
void delay(int time) {
   int counter = 0;
   for (counter = 0; counter<time; counter++);
}
 
void main(void) {
   int dtime = 0;
   int dir = 0;
   int ignorebutton = 0;
   //
   // TRIS is to set  the PORTS as 1 for input  0 output
   // there port A for analog example TRISA
   // there is port B for button  example TRISB
   // there is port D for digitial example TRISD
   // nothing with go in or out till you make it using port or lat ?
   // TRISX  ris is resistor and X is port
   TRISA = 0x1; // set potentiometer at porta as input
   ANSELbits.ANS0 = 1; // set RA0 pin to analog by setting to 1  (=1, 0 = digital)
   // bits. is only for one port terminal or one bit
   // in this case ANSELbits.ANS0 the 0 is zero port terminal  and is initialize to input (1)
   ADCON0bits.ADON = 1; // activate A/D unit
  TRISB = 0x1; // set bit0 of portb to input because there is the push button at RB0
  
   ANSELHbits.ANS12 = 0; // set RB0 to digital (=0, 1= analog)
  TRISD = 0; // all bits of portd are set 0 as output
   PORTD = 0; // deactivate all led's  //in the port D
   // once tris direction has been stablish we set the port to read or write data
//PORTBbits.RB0 the .RB0 allows to read or write data to only one pin in this case zero
   // PORTBbits.RB0 == 0  in this case is comparing only  port 0 is out put or high
// to write to all ports we can use PORTX = 0xFF;
   // there are 3 resistor related to each port
   // one resistor for TRIS //one for resistor PORT one for resistor  LAT
   // latch resistor we can use port or latch
   // ADRESH
   //  ADRESL and ADRESH are registers used to store the end result of an analog to digital converstion ADC
   // These registers end up storing the analog value reading
   // the reason there are 2 registers for the ADC process is  because
   // PIC micro controller typically perform 10 bit ADC conversion or higher
   // ADCON is a register
   // ADCON0bits.ADON=1; //turns on A/D
    // ADCON0bits.GO_DONE = 1
   while (1) {
       ADCON0bits.GO_DONE = 1; // start A/D convert from potentiometer
       //ADCON0bits.GO_DONE=1; //do A/D measurement
       while(ADCON0bits.GO_DONE != 0); // wait till A/D convert done
       dtime = ADRESH * SCALE_FACTOR_TIME; // copy A/D result (high part) to time variable
       if (PORTBbits.RB0 == 0 && ignorebutton == 0) { //check if button is pressed (=0, 1= not pressed)
            dir = dir ^ 1; // toggle direction
            ignorebutton = BTN_IGNORE_FACTOR; // start to ignore button for a moment
        }
        if (ignorebutton > 0) ignorebutton--; // decrease ignore value of button
       if (dir == 1) { // check direction variable
            PORTD = PORTD>>1; // move set led to right
           if (PORTD == 0) {
                PORTD = 0x80;
            }
       }  else  {
            PORTD = PORTD<<1; // move set led to left
           if (PORTD == 0) {
                PORTD = 0x01;
            }
        }
       delay(dtime); // wait for the value read from potentiometer
    }
}

