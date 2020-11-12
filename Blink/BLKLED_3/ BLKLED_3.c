/*
  * File:   main.c
  *
  * Created on January 25, 2013, 18:09 PM */
     
 #pragma config FOSC = INTIO67
 #pragma config WDTEN = OFF, LVP = OFF
 
 #include "pic18f45k20.h"
 
 void delay();
     
 void delay() {
    int counter = 0;
    for (counter = 0; counter<1000; counter++);
 }
 void main(void) {
    int dummy = 0;
    /*init the RA0 as analog input*/
    TRISA = 0x1; // set potentiometer at porta as input
    ANSELbits.ANS0 = 1; // set RA0 to analog (=1, 0 = digital) -> this is important to potentiometer  at RA0
    ADCON0bits.ADON = 1; // activate A/D unit
    /*init the RB0 as digital input*/
    TRISB = 0x1; // set bit0 of portb to input because there is the push button at RB0
    ANSELHbits.ANS12 = 0; // set RB0 to digital (=0, 1= analog) -> this is important to read button at RB0
    /*init the RD0..RD7(PORTD) as digital output*/
    TRISD = 0; // all bits of portd are set 0 as output
    PORTD = 0; // deactivate all led's
 
    while (1) {
       if (PORTBbits.RB0 == 0) { //check if button is pressed (=0, 1= not pressed)
          ADCON0bits.GO_DONE = 1; // start A/D convert
          while(ADCON0bits.GO_DONE != 0); // wait till A/D convert done
          dummy = ADRESH; // copy A/D result (high part) to leds -> dummy variable is only for better debugging
          PORTD = dummy;
       } else {
          PORTD = PORTD<<1; // move set led
          if (PORTD == 0) {
             PORTD = 0x1; // if all led's off activate one
          }
       }
       delay();
    }
 }
 

