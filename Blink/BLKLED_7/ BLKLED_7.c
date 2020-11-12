/*
 * File:   main.c
 *
 * Created on January 26, 2013, 14:12 PM */

#pragma config FOSC = INTIO67, FCMEN = OFF, IESO = OFF // CONFIG1H
#pragma config PWRT = OFF, BOREN = SBORDIS, BORV = 30 // CONFIG2L
#pragma config WDTEN = OFF, WDTPS = 32768 // CONFIG2H
#pragma config MCLRE = OFF,LPT1OSC = OFF, PBADEN = ON, CCP2MX = PORTC // CONFIG3H
#pragma config STVREN = ON, LVP = OFF, XINST = OFF // CONFIG4L
#pragma config CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF // CONFIG5L
#pragma config CPB = OFF, CPD = OFF // CONFIG5H
#pragma config WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF // CONFIG6L
#pragma config WRTB = OFF, WRTC = OFF, WRTD = OFF // CONFIG6H
#pragma config EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF // CONFIG7L
#pragma config EBTRB = OFF // CONFIG7H





#include "pic18f45k20.h"

void delay(int time);
 
void delay(int time) {
   int counter = 0;
   for (counter = 0; counter<time; counter++);
   
}

void main (void)
{
int LED_Number = 0;// initialize
TRISD = 0b00000000;// PORTD bits 7:0 are all outputs (0)
int LED_LookupTable[8] = {0b00000001,0b00000010,0b00000100,0b00001000,0b00010000,0b00100000,0b01000000,0b10000000};
while (1)
{
//use lookup table to output one LED on based on LED_Number value
PORTD = LED_LookupTable[LED_Number];
LED_Number = LED_Number + 1;
//LED_Number++;// rotate display by 1
if (LED_Number == 7)
LED_Number = 1;// go back to LED 0.
//else if (LED_Number == 2)
//LED_Number = 0;// go back to LED 0.

delay(1000);// Delay 50 x 1000 = 50,000 cycles; 200ms @ 1MHz

}
}
