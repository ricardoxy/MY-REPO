/*
 * File:   main.c
 *
 * Created on January 26, 2013, 14:12 PM */
#pragma config FOSC = INTIO67
#pragma config WDTEN = OFF, LVP = OFF

#include "pic18f45k20.h"
#include   <assert.h> <complex.h> <ctype.h>
#include <errno.h> <fenv.h> <float.h>
#include <inttypes.h> <iso646.h> <limits.h>
////#include <locale.h> <math.h>  <setjmp.h>
////#include <signal.h>  <stdarg.h> <stdbool.h>
#include <stdint.h> <stddef.h> <stdio.h>
#include <stdlib.h> <string.h> <tgmath.h>
#include <time.h> <wchar.h> <wctype.h>
#define SCALE_FACTOR_TIME 10

#define BTN_IGNORE_FACTOR 10
 
void delay(int time);
 
void delay(int time) {
   int counter = 0;
   for (counter = 0; counter<time; counter++);
}
 
void main(void) {
   int mytime = 0;
   int dir = 0;
int ignorebutton = 0;
  // TRISA = 0x1; // set potentiometer at porta as input
  // ANSELbits.ANS0 = 1; // set RA0 to analog (=1, 0 = digital)
  // ADCON0bits.ADON = 1; // activate A/D unit
 // TRISB = 0x1; // set bit0 of portb to input because there is the push button at RB0
  // ANSELHbits.ANS12 = 0; // set RB0 to digital (=0, 1= analog)
  TRISD = 0b00000000; // all bits of portd are set 0 as output
  // PORTD = 0; // deactivate all led's
//PORTD = 0b10000001; //LED 7
//PORTD = 0b01000000;//LED 6  NUMBER 4 AND 0   DECIMAL 64   IN HEX PORTD =0X40
//PORTD = 0b00100000;// LED 5  NUMBER 2 AND 0  DECIMAL 32  IN HEX PORTD =0X20
//PORTD = 0b00010000;// LED 4 NUMBER 1 AND 0  DECIMAL 16  IN HEX PORTD =0X10
//PORTD = 0b00001000;//LED 3 NUMBER 0 AND 8 DECIMAL 8      IN HEX PORTD =0X08
//PORTD = 0b00000100;//LED 2 NUMBER 0 AND 4  DECIMAL 4   IN HEX  PORTD = 0X04
//PORTD = 0b00000010;//LED 1 NUMBER 0 AND 2 DECIMAL 2       IN HEX PORTD =0X02
//PORTD = 0b00000001;//LED 0 NUMBER 0 AND 1 DECMMAL 1       IN HEX PORTD =0X01

// TURN ON LED 7 AND LED 0 --- PORTD= 0b10000001;
 //PORTD = 0b00000110;

   while (1) {
       ADCON0bits.GO_DONE = 1; // start A/D convert from potentiometer
      while(ADCON0bits.GO_DONE!= 0) // wait till A/D convert done
      //mytime = ADRESH * SCALE_FACTOR_TIME; // copy A/D result (high part) to time variable
      // mytime = ADRESH * SCALE_FACTOR_TIME;
       if (PORTBbits.RB0 == 0 )//&& ignorebutton == 0)
      {
          LATDbits.LATD5 = ~LATDbits.LATD5; // toggle LATD
          // ignorebutton = BTN_IGNORE_FACTOR;
       }

      if (PORTBbits.RB0 == 0 ){
          //&& ignorebutton == 0) { //check if button is pressed (=0, 1= not pressed)
         dir = dir ^ 1; // toggle direction
         // ignorebutton = BTN_IGNORE_FACTOR; // start to ignore button for a moment
                                                  }
       else (ignorebutton > 0);
             ignorebutton--;// decrease ignore value of button
       if (dir == 1)  {// check direction variable
           PORTD = PORTD>>1; // move set led to right
           if (PORTD == 0) {
                           PORTD = 0x80;
                           }
                         }
       
     //  else
     //           PORTD = PORTD<<1; // move set led to left
     //           if (PORTD == 0) {
      //                           PORTD = 0x01;
      //                          }
                
       delay(1000); // wait for the value read from potentiometer
  
    
                      }
   }
  
  
  


