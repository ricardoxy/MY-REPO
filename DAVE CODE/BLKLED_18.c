
#pragma config FOSC = INTIO67
#pragma config WDTEN = OFF, LVP = OFF
#include "pic18f45k20_Config.h"
#include "pic18f45k20.h"
#include "xc.h"
# define N  20

void sendchar(unsigned char A);
void FROMTERMINAL_char(unsigned char B);
void delay_ms(int delay_time);
volatile unsigned char rx_data[N] = {0};
volatile unsigned char valid_data = 0;


void __interrupt()  ISR(void)
{
    
    unsigned int j;
   
    if (PIR1bits.RCIF==1)  {
        PIE1bits.RCIE =0;
//      for (j=0; j< (N-1) ;j++)                   {
        rx_data[0] = RCREG;
//
           if(rx_data[j]== 'a' && RCREG== 'a') {
               LATDbits.LATD1 = 1;
                delay_ms(100);
               LATDbits.LATD1 = 0;
                 delay_ms(100);
                                               }
//                                                }
        valid_data = 1;
        PIR1bits.RCIF= 0;  //we clear the receive interrupt flag set it back to empty
                           // 1 = The EUSART receive buffer, RCREG, is full (cleared when RCREG is read)
                           //0 = The EUSART receive buffer is empty
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
  Timer_0(); // T0CON
  OSC_freq();
  void delay_ms(int delay_time);
 // T0CONbits.TMR0ON = 1;  // start timer
  // OSCCONbits.IRCF2 =1;
  // OSCCONbits.IRCF1 =0;    //111 is 16MHZ
  // OSCCONbits.IRCF0 =1;    // 101 is 4 MHZ
  TRISB = 0xF0; // RBO to RB3 are out put port
  LATD =  0xF0; // all led off
  TRISD = 0b00000000;
  TRISBbits.RB0 = 1; // is made as input   switch
  ANSELHbits.ANS12 = 0; // set RB0 to digital
  //TRISCbits.RC6 = 0; // TX is made as output   TX/CK
                       // SPBRG= 25;
  // TRISCbits.RC7 = 1;//RX is made as input      RX/DT
                       //TXSTA= 0b00100000;
  TXSTAbits.TXEN =1;//Enable Data tranmission on RC6 pin
  TXSTAbits.SYNC=0;// 0 enable ASYNCh mode
  TXSTAbits.BRGH=0; // low speed
    
  ////////////////////////////////////////////////////////////////////////////////////
    
  TRISCbits.RC6 = 1; // TX is made as input  TX/CK
                       // SPBRG= 25;
                       // 1 = input    0= output
                       //That means RC6 is a transmit pin
  TRISCbits.RC7 = 1; //RX is made as output      RX/DT
                      //TXSTA= 0b00100000;
                      // 1 = input    0= output   PG 248 DATA SHEET
                      //RC7 is used to receiving data
                      // Before using these pins for serial communication,
                      // we should set direction control registers of these
                      //********pins to logic high.**************
                      // Although the receiver pin should be set as digital input and transmitter pin as an output
                      //But the UART module will set these pins
                      //input to output automatically according to requirement.
    
    
   // RCSTA =0b10010000 or 0x90 / Enables UART Communication PORT
  RCSTAbits.SPEN=1;// bit7  SPEN: Serial Port Enable bit
                     //1 = Serial port enabled (configures RX/DT and TX/CK pins as serial port pins)
                     //0 = Serial port disabled (held in Reset)
    
  //RCSTAbits.RX9 =0;//bit 6 RX9: 9-bit Receive Enable bit
                     //1 = Selects 9-bit reception
                     //0 = Selects 8-bit reception

 //RCSTAbits.SREN =0; //bit 5 SREN: Single Receive Enable bit
                     //Asynchronous mode:
                     //Don?t care
                     //Synchronous mode ? Master:
                     //1 = Enables single receive
                     //0 = Disables single receive
                     //This bit is cleared after reception is complete.
                     //Synchronous mode ? Slave
                      //Don?t care

 RCSTAbits.CREN = 1; //bit 4 CREN: Continuous Receive Enable bit
                        //Asynchronous mode:
                        //1 = Enables receiver
                        //0 = Disables receiver
                        //Synchronous mode:
                        //1 = Enables continuous receive until enable bit CREN is cleared (CREN overrides SREN)
                        //0 = Disables continuous receive
                    
  //RCSTAbits.ADDEN = 1;//bit 3 ADDEN: Address Detect Enable bit
                        //Asynchronous mode 9-bit (RX9 = 1):
                        //1 = Enables address detection, enable interrupt and load the receive buffer when RSR<8> is set
                        //0 = Disables address detection, all bytes are received and ninth bit can be used as parity bit
                        //Asynchronous mode 8-bit (RX9 = 0):
                        //Don?t care
    
  //RCSTAbits.FERR = 0;//bit 2 FERR: Framing Error bit
                        //1 = Framing error (can be updated by reading RCREG register and receive next valid byte)
                        //0 = No framing error

  //RCSTAbits.OERR = 0; //bit 1 OERR: Overrun Error bit
                        //1 = Overrun error (can be cleared by clearing bit CREN)
                        //0 = No overrun error

  //RCSTAbits.RX9D =0; //bit 0 RX9D: Ninth bit of Received Data
                        //This can be address/data bit or a parity bit and must be calculated by user firmware.
    
  //////////////////////////////////////////////////////////////////////////
    
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
         RCONbits.IPEN=  0; // enable  priority levels on interrups
         PIR1bits.RCIF = 0; //RCIF: EUSART Receive Interrupt Flag bit  (RC1IF per email)
                            //1 = The EUSART receive buffer, RCREG, is full (cleared when RCREG is read)
                            //0 = The EUSART receive buffer is empty
         /****************/
         PIE1bits.RCIE = 1;  //RCIE: EUSART Receive Interrupt Enable bit
                            //1 = Enables the EUSART receive interrupt
                            //0 = Disables the EUSART receive interrupt
        
        //PIR1bits.TXIF = 1;  //TXIF: EUSART Transmit Interrupt Flag bit
                            //1 = The EUSART transmit buffer, TXREG, is empty (cleared when TXREG is written)
                            //0 = The EUSART transmit buffer is full
        //PIE1bits.TXIE = 1;  //TXIE: EUSART Transmit Interrupt Enable bit
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
        INTCONbits.PEIE = 1;
    
    
    
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
      //while (1)   {
        //for (i=0; i<6;i++) {
          // sendchar(string[i]);
            // delay_ms(300); }
             //      }
        
     
     
    }
    

          

void sendchar(unsigned char A){
   
   while (TXSTAbits.TRMT==0);    // TRMT: Transmit Shift Register Status bit
                                  //1 = TSR empty
                                  //0 = TSR full
      
   TXREG = A;                    //EUSART Transmit Register
                                 //TXREG USART Transmit Register: It holds the data that the
                                //transmitter device wants to send to a receiver device.
   
      }






