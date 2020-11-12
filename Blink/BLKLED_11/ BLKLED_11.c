
#pragma config FOSC = INTIO67
 #pragma config WDTEN = OFF, LVP = OFF
 
#include "pic18f45k20.h"
#include "xc.h"

void main (void){
    
   // OSCCONbits.IRCF2 =1;
   // OSCCONbits.IRCF1 =1;    //111 is 16MHZ
    //OSCCONbits.IRCF0 =1;    // 101 is 4 MHZ
    
    TRISB = 0xF0; // RBO to RB3 are out put port
    LATD = 0xF0; // all leds off
   
    TRISCbits.RC6 = 1; // TX is made as output   TX/CK
    TRISCbits.RC7 = 0; //RX is made as input      RX/DT
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
        SPBRG= 207;
       // SPBRGH= 0;
        while (1)
        {
            TXREG= 'C'; //0X41;
            //break;
            while (TXSTAbits.TRMT!=0);
            //break;
       
        }
        
        
    
}






