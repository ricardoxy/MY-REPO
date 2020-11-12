
#pragma config FOSC = INTIO67
 #pragma config WDTEN = OFF, LVP = OFF
//#include "../lib/../c90/xc8debug.h"
 #include "pic18f45k20_Config.h"
#include "pic18f45k20.h"
#include "xc.h"
        
void sendchar(unsigned char A);

void main (void){
    
   unsigned char string[]= { 'A', 'B','C'} ;
   int i ;
  // char a;

   
     
      
      
     OSC_freq();
     Timer_0();
     T0CONbits.TMR0ON = 1;  // start timer
   // OSCCONbits.IRCF2 =1;
   // OSCCONbits.IRCF1 =0;    //111 is 16MHZ
   // OSCCONbits.IRCF0 =1;    // 101 is 4 MHZ
    
    TRISB = 0xF0; // RBO to RB3 are out put port
    LATD = 0xF0; // all leds off
   
    TRISCbits.RC6 = 0; // TX is made as output   TX/CK
    // SPBRG= 25;
    TRISCbits.RC7 = 1; //RX is made as input      RX/DT
     //TXSTA= 0b00100000;
    TXSTAbits.TXEN =1;// enable transmition
    TXSTAbits.SYNC=0;// 0 enable ASYNCh mode
    TXSTAbits.BRGH=0; // low speed
    RCSTAbits.SPEN=1; // enable serial pins
    BAUDCONbits.BRG16= 1; // 16 bit baud rate mode
            // fosc/16(value+1 )= baudrate
            // SPBRG = Fosc/(16x9600) -1
            // SPBRG = (4MHZ/ (16x9600)) -1  =25
            // 9600 baud rate value is 25
            //// SPBRG = (16MHZ/ (16x9600)) -1  =103.1
    SPBRG= 25;
        // SPBRGH= 0;
        /////// now we will transmit one character a time using for loop
      while (1){
        for (i=0; i<3;i++){
            sendchar(string[i]);
            
      // while (TXSTAbits.TRMT==0);
      // TXREG = string[i];// one element character from the array will be put in data
       
         // then we place this ascii char insdie TXREGISTER
       // how do we know if the char is transmitet ??
        // we check for interrup flag bit in reg pir1 in bit txif
       // while (TXSTAbits.TRMT==0);
       //while (PIR1bits.TXIF == 0);// if not true or 1 come out of loop  go to delay
       
                            }
         
         TMR0=0;
        while (TMR0<3000);
   
             }
     // while (1);// makes the all string cycle to repeat
          
       
}
    

void sendchar(unsigned char A){
   
     while (TXSTAbits.TRMT==0);
       TXREG = A;
             
   
 }





