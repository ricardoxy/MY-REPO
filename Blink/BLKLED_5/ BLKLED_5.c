/** C O N F I G U R AT I O N B I T S ******************************/
     
 #pragma config FOSC = INTIO67
 #pragma config WDTEN = OFF, LVP = OFF
 
 #include "pic18f45k20.h"
//#include "delays.h"
#define multi 10

//** D E C L A R A T I O N S *******************************************/
 void delay(int time);
  
 void delay(int time) {
    int counter = 0;
    for (counter = 0; counter<time; counter++);
 }
  

void main (void)
 


{
    int dtime = 0;
    
   TRISA = 0x1; // set potentiometer at porta as input
   ANSELbits.ANS0 = 0; // set RA0 pin to analog by setting to 1  (=1, 0 = digital)
    // bits. is only for one port terminal or one bit
    // in this case ANSELbits.ANS0 the 0 is zero port terminal  and is initialize to input (1)
   ADCON0bits.ADON = 1; // activate A/D unit
   //int dir = 0;
//TRISD = 0b00000000;// PORTD bit 7 to output (0); bits 6:0 are inputs (1)125
TRISDbits.TRISD3= 0; // all bits of portd are set 0 as output
//LATDbits.LATD6 = 0;// Set LAT register bit 7 to turn on LED
//TRISDbits.TRISD5= 10;
//PORTD = 0b10000001;//LED 7 NUMBER 8 AND 0   DECIMAL 128    IN HEX PORTD =0X80

//PORTD = 0b01000000;//LED 6 NUMBER 4 AND 0   DECIMAL 64   IN HEX PORTD =0X40
//PORTD = 0b00100000;// LED 5  NUMBER 2 AND 0  DECIMAL 32  IN HEX PORTD =0X20
//PORTD = 0b00010000;// LED 4 NUMBER 1 AND 0  DECIMAL 16  IN HEX PORTD =0X10
//PORTD = 0b00001000;//LED 3 NUMBER 0 AND 8 DECIMAL 8      IN HEX PORTD =0X08
//PORTD = 0b00000100;//LED 2 NUMBER 0 AND 4  DECIMAL 4   IN HEX  PORTD = 0X04
//PORTD = 0b00000010;//LED 1 NUMBER 0 AND 2 DECIMAL 2       IN HEX PORTD =0X02
//PORTD = 0b00000001;LED 0 NUMBER 0 AND 1 DECMMAL 1       IN HEX PORTD =0X01

// TURN ON LED 7 AND LED 0 --- PORTD= 0b10000001;
  //PORTD = 0b00000110;

//ADCON0 - A/D Control Register 0; determines the behavior of the A/D
//ADCON1 - A/D Control Register 1; determines the configuration of the PORTA and PORTE and how the result of conversion of A/D will be store
//ADRESH - A/D Result High Register
//ADRESL - A/D Result Low Register
PORTDbits.RD3 = 0;



while (1){
    ADCON0bits.GO_DONE = 1;
        // start A/D convert from potentiometer
        //ADCON0bits.GO_DONE=1; //do A/D measurement
     LATDbits.LATD3 =1;
    //TRISDbits.TRISD3= 0;
    while(ADCON0bits.GO_DONE != 0); // wait till A/D convert done
    dtime = ADRESH * multi; // copy A/D result (high part) to time variable
   // LATDbits.LATD5 = ~LATDbits.LATD5; // toggle LATD
    // LAT is to set led D is to digital
    // .LATX or in this case .LAT5 sets the corresponding pin to hight RD5
    //  ~ bit wise operator ones complements or turn one in to zero or vice versa for indivil. bits
   
    // LATDbits.LATD = ~LATDbits.LATD5;
}
delay (dtime);// Delay 50 x 1000 = 50,000 cycles; 200ms @ 1MHz
}


