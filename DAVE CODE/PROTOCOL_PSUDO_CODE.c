ERP time code for this week
opiniton on degree
self eval submition to who


nderstand how to read wave diagram?
do we need to writee in the eeprom erasable?
do we need full half duxplex coms?
do we need continues data back to back?
do i need to create structs ?


#pragma config FOSC = INTIO67
#pragma config WDTEN = OFF, LVP = OFF
#include "pic18f45k20_Config.h"
#include "pic18f45k20.h"
#include "xc.h"
# define N  20

void sendchar(unsigned char A);
volatile unsigned char rx_data[N] = {0};
volatile unsigned char valid_data = 0;

// TO iniate protocol we create a function that will write and read data
//*** void write_data ( char slave_address , char address_high , char address_low, char Eedata)
//*** void read_data(   char slave_address , char address_high,  char address_low)
// slave address at the end also includes the read write byte
// Eedata is the data to be written in eeprom adress  // in our case RCREG
 


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
    
    //// we write data inside main
    //*** void write_data ( char slave_address , char address_high , char address_low, char Eedata)
    //*** void write_data(  0x80                , 0x12              , 0x34       , 0x78)
    
    
    // add delay
    
    //*** void read_data(   char slave_address , char address_high,  char address_low)
    //*** void read_data(   ......             ,            ..... ,       .....      )
    }


// outside main we place writte funtion
//**void write_data ( char slave_address,char address_high,char address_low,char Eedata){

//SSPCON2bits.sen = 1 ;    //  this initiates the start condition / comunitcation
                           //  the start condition is autamtically clear by hardware
//while (SEN);             // we check that SEN start conditon is true
//PIR1bits.SSPIF = 0 ;     // clear the interrup flag

//*** SSPBUF will contain adress bityes and data bytes**
//SSPBUF = slave_address;  // we place the slave_address value in sspbuf
//while (!SSPIF);          // when 1= not ack wait for ack sspif is set every 9th clock cycle
// PIR1bits.SSPIF= 0 ;     // clear the interrup flag
//    if (SSPCON2bits.ACKSTAT){
//    SSPCON2bits.PEN= 1    // initiate stop condition
//    while(PEN)            // while PEN is high and then...
//    return;              }// ...exit write (no ack)

// SSPBUF= address_high    // place the address high in the sspbuf
// while (!SSPIF);         // wait for ack
// PIR1bits.SSPIF = 0 ;    // clear the interrup flag
//    if (SSPCON2bits.ACKSTAT){
//    SSPCON2bits.PEN= 1    // initiate stop condition
//    while(PEN)            // while PEN is high and then...
//    return;              }// ...exit write (no ack)

//SSPBUF= address_low;     // place the address low in the sspbuf
// while (!SSPIF);         // wait for ack
// PIR1bits.SSPIF = 0 ;    // clear the interrup flag
//    if (SSPCON2bits.ACKSTAT){
//    SSPCON2bits.PEN= 1    // initiate stop condition
//    while(PEN);            // while PEN is high and then...
//    return;              }// ...exit write (no ack)                                       }


//*** void read_data(   char slave_address , char address_high,  char address_low)    {
// char TempData;   // temporary holder for data byte

// SSPCON2bits.SEN = 1 ;  // initiate start condition
// while (SEN);            // wait for start conditon to complete
// PIR1bits. SSPIF = 0;   //Clear SSP interrup flag

// SSPUF = slave_address;    // send the slave address and R/W bit
// while (!SSPIF);          // wait for ack   SSPIF is set every 9th cycle
// PIR1bits. SSPIF =0;      // clear SSP interrup flag
// if (SSPCON2bits.ACKSTAT){
// SSPCON2bits.PEN = 1;         // initiate stop condiition
// while (PEN);                 // wait for star condition to complete
// return (0xFF);           }   // EXit read (no Ack)

// SSPUF = address_high;      // send the EEprom address high
// while (!SSPIF);           // wait for ack   SSPIF is set every 9th cycle
// PIR1bits. SSPIF =0;       // clear SSP interrup flag
// if (SSPCON2bits.ACKSTAT){
// SSPCON2bits.PEN = 1;         // initiate stop condiition
// while (PEN);                 // wait for star condition to complete
// return (0xFF);           }   // EXit read (no Ack)

// SSPUF = address_low;      // send the EEprom address high
// while (!SSPIF);           // wait for ack   SSPIF is set every 9th cycle
// PIR1bits. SSPIF =0;       // clear SSP interrup flag
// if (SSPCON2bits.ACKSTAT){
// SSPCON2bits.PEN = 1;         // initiate stop condiition
// while (PEN);                 // wait for star condition to complete
// return (0xFF);           }   // EXit read (no Ack)


///*******restart condition
// SSPCON2bits.RSEN=1;        // initiate restar condition
// while (RESEN);             // wait for restart condition to complete
// PIR1bits.SSPIF=0;           // clear the SSP interrup flag

// SSPBUF =(slave_address+1);  // send the slave address and R/W bit = 1
// while (!SSPIF);              // wait for ack.  SSPIF is set every 9th cycle
// PIR1bits.SSPIF = 0 ;         // CLear the SSP interrupt flag
// if (SSPCON2bits. ACKSTAT){
// SSPICON2bits.PEN=1;          // initiate stop condition
// while (PEN);                 // wait for condition to complete
// return (0xFF);               //  Exit read no ack


//SSPCON2bits.RCEN = 1         // Recieve the Data byte from slave
//while( !SSPSTAbits.BF)       // wiat for recived to complete
// TempData= SSPBUF;           // Save the data byte

// SSPCON2bits.ACKDT = 1;     // prepare to send NACK=not acknoledge
// SSPCON2bits.ACKEN = 1;     // Initiate NACK to EEPROM
// while (ACKEN);             // wait for NACK to complete

// SSPCON2bit.PEN =1 // initiate stop condtion
// while (PEN);      // wait for stop condtion to complete
// return TempData;  // return data byte value




    
void sendchar(unsigned char A) {
   
   while (TXSTAbits.TRMT==0);    // TRMT: Transmit Shift Register Status bit
                                  //1 = TSR empty
                                  //0 = TSR full
      
   TXREG = A;                    //EUSART Transmit Register
                                 //TXREG USART Transmit Register: It holds the data that the
                                //transmitter device wants to send to a receiver device.
   
                                }







