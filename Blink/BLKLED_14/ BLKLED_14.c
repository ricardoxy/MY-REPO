
//NAME    Bit7      Bit6      Bit5   Bit4   Bit3   Bit2   Bit1   Bit0   //Value on POR,BOR
//INTCON  GIE/GIEH  PEIE/GIEL TMR0IE INT0IE RBIE   TMR0IF INT0IF RBIF 57
//PIR1    PSPIF(1)  ADIF      RCIF   TXIF   SSPIF  CCP1IF TMR2IF TMR1IF 60
//PIE1    PSPIE(1)  ADIE      RCIE   TXIE   SSPIE  CCP1IE TMR2IE TMR1IE 60
//IPR1    PSPIP(1)  ADIP      RCIP   TXIP   SSPIP  CCP1IP TMR2IP TMR1IP 60
//RCSTA   SPEN      RX9       SREN   CREN   ADDEN  FERR   OERR   RX9D 59
//TXREG   EUSART Transmit Register 59
//TXSTA   CSRC      TX9       TXEN   SYNC   SENDB  BRGH   TRMT   TX9D 59
//BAUDCON ABDOVF    RCIDL     DTRXP  CKTXP  BRG16  ?      WUE    ABDEN 59
//SPBRGH  EUSART Baud Rate Generator Register, High Byte 59
//SPBRG   EUSART Baud Rate Generator Register, Low Byte 59
//RCREG   EUSART Receive Register   0000 0000 59, 234

 // INTCON: INTERRUPT CONTROL REGISTER - pg116
  //NAME       Bit7      Bit6      Bit5    Bit4    Bit3   Bit2   Bit1   Bit0   //Value on POR,BOR // Value on otherResets(1)
  //RCON       IPEN      SBOREN(1) ?       RI      TO     PD     POR(2) BOR     0q-1 11q0
  //INTCON     GIE/GIEH  PEIE/GIEL TMR0IE  INT0IE  RBIE   TMR0IF INT0IF RBIF    0000 000x         0000 000u uuuu uuuu(1)
  //INTCON2    RBPU      INTEDG0   INTEDG1 INTEDG2 ?      TMR0IP ?      RBIP    1111 -1-1         1111 -1-1 uuuu -u-u(1)
  //INTCON3    INT2IP    INT1IP    ?       INT2IE  INT1IE ?      INT2IF INT1IF  11-0 0-00         11-0 0-00 uu-u u-uu(1)
  //       ***REGISTERS ASSOCIATED WITH PARALLEL SLAVE PORT
  //PIR1       PSPIF(1)  ADIF     RCIF     TXIF    SSPIF  CCP1IF TMR2IF TMR1IF  0000 0000         0000 0000
  //PIE1       PSPIE(1)  ADIE     RCIE     TXIE    SSPIE  CCP1IE TMR2IE TMR1IE  0000 0000         0000 0000
  //IPR1       PSPIP(1)  ADIP     RCIP     TXIP    SSPIP  CCP1IP TMR2IP TMR1IP  1111 1111         1111 1111
  //     ***REGISTERS ASSOCIATED WITH TIMER3 AS A TIMER/COUNTER
  //PIR2       OSCFIF    C1IF     C2IF     EEIF    BCLIF  HLVDIF TMR3IF CCP2IF  0000 0000         0000 0000
  //PIE2       OSCFIE    C1IE     C2IE     EEIE    BCLIE  HLVDIE TMR3IE CCP2IE  0000 0000         0000 0000
  //IPR2       OSCFIP    C1IP     C2IP     EEIP    BCLIP  HLVDIP TMR3IP CCP2IP  1111 1111         1111 1111



#pragma config FOSC = INTIO67
#pragma config WDTEN = OFF, LVP = OFF
#include "pic18f45k20_Config.h"
#include "pic18f45k20.h"
#include "xc.h"
        

void sendchar(unsigned char A);
void __interrupt()   ISR(void){
        INTCONbits.GIEH = 0;
  
    if (PIR1bits.RCIF ==1)
    {
        LATBbits.LB2 = ~LATBbits.LB2;
        PIR1bits.RCIF =0;
    }
   
         INTCONbits.GIEH = 1;
 }

//void __interrupt() low_priority low_ISR(void)
 // {
       //INTCONbits.GIEH = 0;
     
  //   if (INTCON3bits.INT1IF == 1)
   // {
   //     LATBbits.LB5 = ~LATBbits.LB5;
   //     INTCON3bits.INT1IF = 0;
   // }
  
    //  INTCONbits.GIEH = 1;
    
 // }
void main (){
    
   volatile unsigned char string[]= { 'z', 'x','y'} ;
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
    
    
     /// interrupts set
        RCONbits.IPEN=1;    // enable  priority levels on interrups
        PIR1bits.RCIF = 0;  //RCIF: EUSART Receive Interrupt Flag bit
                            // 1 = The EUSART receive buffer, RCREG, is full (cleared when RCREG is read)
                            //0 = The EUSART receive buffer is empty
        PIE1bits.RCIE = 1;  //RCIE: EUSART Receive Interrupt Enable bit
                            //1 = Enables the EUSART receive interrupt
                            //0 = Disables the EUSART receive interrupt
        
        PIR1bits.TXIF = 0;  //TXIF: EUSART Transmit Interrupt Flag bit
                            //1 = The EUSART transmit buffer, TXREG, is empty (cleared when TXREG is written)
                            //0 = The EUSART transmit buffer is full
        PIE1bits.TXIE = 1;  //TXIE: EUSART Transmit Interrupt Enable bit
                            //1 = Enables the EUSART transmit interrupt
                            //0 = Disables the EUSART transmit interrupt
        
        //INTCON3bits.INT1IE=1;// enables INT1 external interrupt
       // INTCON3bits.INT1IP=0; // low priority set INT1 external int. priority
       // INTCON2bits.INTEDG1=1; // interrupt on rising edge
                
       // INTCONbits.INT0IE=1;   // pg 102  Enables the INT0 external interrupt
       // INTCON2bits.INTEDG0=1 ;// interrupt on the rising  edge
      
        INTCONbits.PEIE = 1; //
                              //When IPEN = 0:
                             //1 = Enables all unmasked peripheral interrupts
                             //0 = Disables all peripheral interrupts
                             //When IPEN = 1:
                             //1 = Enables all low priority interrupts
                             //0 = Disables all low priority interrupts
        INTCONbits.GIEH = 1; //global interrupt enable bit
        INTCONbits.GIEL = 1; // global interrupt low prio. enable bit
   
                             // When IPEN = 0:
                             //1 = Enables all unmasked interrupts
                             //0 = Disables all interrupts including peripherals
                             //When IPEN = 1:
                             //1 = Enables all high priority interrupts
                             //0 = Disables all interrupts including low priority.
   
      while (1){
        for (i=0; i<3;i++)
        {
            sendchar(string[i]);
        }
      // while (TXSTAbits.TRMT==0);
      // TXREG = string[i];// one element character from the array will be put in data
      // then we place this ascii char insdie TXREGISTER
      // how do we know if the char is transmitet ??
      // we check for interrup flag bit in reg pir1 in bit txif
      // while (TXSTAbits.TRMT==0);
      //while (PIR1bits.TXIF == 0);// if not true or 1 come out of loop  go to delay
       
                            
        TMR0=0;
        while (TMR0<3000);
             }
     // while (1);// makes the all string cycle to repeat
     
}
    

void sendchar(unsigned char A){
   
       while (TXSTAbits.TRMT==0){
       TXREG = A;
       }
 }






