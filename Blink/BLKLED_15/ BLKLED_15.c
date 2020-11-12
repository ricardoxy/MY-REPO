
#pragma config FOSC = INTIO67
 #pragma config WDTEN = OFF, LVP = OFF
//#include "../lib/../c90/xc8debug.h"
 #include "pic18f45k20_Config.h"
#include "pic18f45k20.h"
#include "xc.h"

volatile int TBD;
void sendchar(unsigned char A);
void delay_ms(int delay_time);

void __interrupt()  ISR(void){
       INTCONbits.GIE = 0;
  
   if (PIR1bits.RCIF==1)  // if zero buffer  is full
    {// desable interrupt here
        LATDbits.LATD7 = 0;
          delay_ms(10);
          LATDbits.LATD7 = 1;
       //LATDbits.LATD2 = ~LATDbits.LATD2;
       PIR1bits.RCIF= 0;  // we set it back to empty
       
    }
       //INTCONbits.GIEH = 1;
   // puti in RX data in the ISR
     //RCREG   EUSART Receive Register   0000 0000 59, 234
                             
       if ( INTCONbits.INT0IF ==1) //
       {
           ////
          LATDbits.LATD2 = 1;
          delay_ms(1000);
       //LATDbits.LATD2 = ~LATDbits.LATD2;
          INTCONbits.INT0IF = 0;  // we set it back to empty
       }
      INTCONbits.GIE = 1;
      // enable interrupt here
   
                             }




void main (void){
    
  volatile unsigned char string[]= { 'H', 'E','L', 'L', 'O', ' '} ;
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
    TRISD = 0b00000000;
    TRISBbits.RB0 = 1; // is made as input   switch
     ANSELHbits.ANS12 = 0; // set RB0 to digital
    //TRISCbits.RC6 = 1; // TX is made as output   TX/CK
    // SPBRG= 25;
   // TRISCbits.RC7 = 1; //RX is made as input      RX/DT
     //TXSTA= 0b00100000;
    TXSTAbits.TXEN =1;// enable transmition
    TXSTAbits.SYNC=0;// 0 enable ASYNCh mode
    TXSTAbits.BRGH=0; // low speed
    RCSTAbits.SPEN=1; // enable serial pins
    RCSTAbits.CREN = 1; // enables reciver if one
    BAUDCONbits.BRG16= 1; // 16 bit baud rate mode
            // fosc/16(value+1 )= baudrate
            // SPBRG = Fosc/(16x9600) -1
            // SPBRG = (4MHZ/ (16x9600)) -1  =25
            // 9600 baud rate value is 25
            //// SPBRG = (16MHZ/ (16x9600)) -1  =103.1
    SPBRG= 25;
        // SPBRGH= 0;
        /////// now we will transmit one character a time using for loop
    
      /// interrupts set
         RCONbits.IPEN=  1; // enable  priority levels on interrups
         PIR1bits.RCIF = 0; //RCIF: EUSART Receive Interrupt Flag bit  (RC1IF per email)
                            // 1 = The EUSART receive buffer, RCREG, is full (cleared when RCREG is read)
                            //0 = The EUSART receive buffer is empty
        PIE1bits.RCIE = 1;  //RCIE: EUSART Receive Interrupt Enable bit
                            //1 = Enables the EUSART receive interrupt
                            //0 = Disables the EUSART receive interrupt
        
       /// PIR1bits.TXIF = 1;  //TXIF: EUSART Transmit Interrupt Flag bit
                            //1 = The EUSART transmit buffer, TXREG, is empty (cleared when TXREG is written)
                            //0 = The EUSART transmit buffer is full
       /// PIE1bits.TXIE = 0;  //TXIE: EUSART Transmit Interrupt Enable bit
                            //1 = Enables the EUSART transmit interrupt
                            //0 = Disables the EUSART transmit interrupt
        
      // INTCON3bits.INT1IE=1;// enables INT1 external interrupt
      // INTCON3bits.INT1IP=0; // low priority set INT1 external int. priority
       // INTCON2bits.INTEDG1=1; // interrupt on rising edge
                
        INTCONbits.INT0IF = 0;//INT0IF: INT0 External Interrupt Flag bit
                              //1 = The INT0 external interrupt occurred (must be cleared by software)
                              //0 = The INT0 external interrupt did not occur
        INTCONbits.INT0IE=1;   // pg 102  Enables the INT0 external interrupt
        INTCON2bits.INTEDG0=1 ;// interrupt on the rising  edge
      
      ////  INTCONbits.PEIE =1; //
                              //When IPEN = 0:
                             //1 = Enables all unmasked peripheral interrupts
                             //0 = Disables all peripheral interrupts
                             //When IPEN = 1:
                             //1 = Enables all low priority interrupts
                             //0 = Disables all low priority interrupts
        INTCONbits.GIE = 1; //global interrupt enable bit
       //INTCONbits.GIEL = 1; // global interrupt low prio. enable bit
   
                             // When IPEN = 0:
                             //1 = Enables all unmasked interrupts
                             //0 = Disables all interrupts including peripherals
                             //When IPEN = 1:
                             //1 = Enables all high priority interrupts
                             //0 = Disables all interrupts including low priority.
   
    
    
    
    
      while (1){
        for (i=0; i<6;i++){
            sendchar(string[i]);
            
      // while (TXSTAbits.TRMT==0);
      // TXREG = string[i];// one element character from the array will be put in data
       
         // then we place this ascii char insdie TXREGISTER
       // how do we know if the char is transmitet ??
        // we check for interrup flag bit in reg pir1 in bit txif
       // while (TXSTAbits.TRMT==0);
       //while (PIR1bits.TXIF == 0);// if not true or 1 come out of loop  go to delay
       
                            }
         
       //  TMR0=0;
       // (TMR0<3000);
        delay_ms(300);
   
             }
     // while (1);// makes the all string cycle to repeat
          
}
        
    

void sendchar(unsigned char A){
   
    while (TXSTAbits.TRMT==0);
      TXREG = A;
             
   
 }



   void delay_ms(int delay_time)
{
    int idx;
    for(idx=0; idx<delay_time;++idx)
    {
       // T0CONbits.TMR0ON = 0;
        TMR0 = 0;
        while(TMR0 < 1000);
    }

    
}

