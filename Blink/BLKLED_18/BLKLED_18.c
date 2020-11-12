
#pragma config FOSC = INTIO67
#pragma config WDTEN = OFF, LVP = OFF
#include "pic18f45k20_Config.h"
#include "pic18f45k20.h"
#include "xc.h"
# define N  20

void sendchar(unsigned char A);
volatile unsigned char rx_data[N] = {0};
volatile unsigned char valid_data = 0;
 


void __interrupt()  ISR(void)
{
    
    unsigned int j;
   
    if (PIR1bits.RCIF==1) {
         
        
        PIE1bits.RCIE= 0;
                 
        rx_data[0] = RCREG;
        
                                                      
        valid_data = 1;
        
        PIR1bits.RCIF= 0;  //we clear the receive interrupt flag set it back to empty
                           }
      
     if (INTCONbits.INT0IF ==1) { // RB0 is to INT0IF
        LATDbits.LATD2 =1;
        delay_ms(100);
        LATDbits.LATD2 =0;
        INTCONbits.INT0IF =0;  // we set it back to empty
                                }
     
 }


void main (void){
    
  volatile unsigned char string[]= { 'H', 'E','L', 'L', 'O', ' '} ;
  unsigned int i;
  
  ///////////////// CONFIGURATIONS///////////////////////////////////
  OSC_freq();          // OSCON
  Timer_0();           // T0CON
  EUSART();            // TXSTA RCSTA BAUDCON
  interrups_initial(); // RCON  INTCON
  
 ////////////////////////// PINS///////////////////////////////////
  TRISB = 0xF0; // RBO to RB3 are out put port
  LATD =  0xF0; // 0 TO 3 led off
  TRISD = 0b00000000;
  TRISBbits.RB0 = 1; // is made as input   switch
  ANSELHbits.ANS12 = 0; // set RB0 to digital
  /////////////////TRASNMIT PINS///////////////////////////////////
  //TRISCbits.RC6 = 0; // TX is made as output   TX/CK
  //TRISCbits.RC7 = 1;//RX is made as input      RX/DT
  ////////////////////RECIVED PINS/////////////////////////////////
  TRISCbits.RC6 = 1; // TX is made as input  TX/CK
                       // SPBRG= 25;
                       // 1 = input    0= output
                       //That means RC6 is a transmit pin
  TRISCbits.RC7 = 1; //RX is made as output      RX/DT
                      //TXSTA= 0b00100000;
                      // 1 = input    0= output   PG 248 DATA SHEET
                      //RC7 is used to receiving data
   
       
       
    
     
    
    
        while(1)
        {
            //sendchar('A');
            LATDbits.LATD6 = 0;
            delay_ms(50);
            LATDbits.LATD6 = 1;
            delay_ms(50);
            
            if(valid_data == 1)
            {
                switch(rx_data[0])
                {
                    case 'a':
                    case 'A':
                        
                        LATDbits.LATD0 = 1;
                        delay_ms(50);
                        LATDbits.LATD0 = 0;
                        delay_ms(50);
                        break;
                        
                        
                        default:
                        break;
                    
                }
                
                
                valid_data = 0;
                PIE1bits.RCIE = 1;
            }
            
        }
         ////// send char hello///////
         //while (1) {
         //for (i=0; i<6;i++) {
         //sendchar(string[i]);
         //delay_ms(300);     }
         //          }
            
    }
    
void sendchar(unsigned char A) {
   
   while (TXSTAbits.TRMT==0);    // TRMT: Transmit Shift Register Status bit
                                  //1 = TSR empty
                                  //0 = TSR full
      
   TXREG = A;                    //EUSART Transmit Register
                                 //TXREG USART Transmit Register: It holds the data that the
                                //transmitter device wants to send to a receiver device.
   
                                }







