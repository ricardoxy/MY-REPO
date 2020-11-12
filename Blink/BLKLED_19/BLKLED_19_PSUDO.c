
#pragma config FOSC = INTIO67
#pragma config WDTEN = OFF, LVP = OFF
#include "pic18f45k20_Config.h"
#include "pic18f45k20.h"
#include "xc.h"




/////*****PACKET COMMUNICATION*********///

// NOTE we must conncet to device TTY.USBserial-..., set baud rate

// we are going to communicate by sending and receiving data packets
// we will send a instruction packet from computer to microcontroller to motor
// we will receive an instruction packet form motor to microcontroller to computer
 
// First instruction packet it has

// the header is the initiation or start of the packet
// Header1 0xFF  Header2 0xFF Header3 0xFD total of 3 bytes
 
// Next is a Reserve byte which is part of the header

// Next is the Packet ID  (01) this the device that would receive that packet  at 1 byte
// IF set to broad cast 0XFE
// ID this means motor is connected
// and we will not get a return a status packet

// Length of packet this is divided into Low and high
// Length includes size of instruction- parameters- CRC
// Length is = number of parameter plus 3

// for CRC we can check sum = (ID +length) 1 byte + 8 bytes

// for return packet we follow simillar steps


struct INSTRUCTION_PACKET {
    char  header1;
    char  header2;
    char  header3;
    char  reserved;
    char  packet_ID;
    char  length1;
    char  length2;
    char  instruction ;
    char  parameter [];
    short CRC ;
                         }

struct STATUS_PACKET {
    char header1;
    char header2;
    char header3;
    char reserved;
    char packet_ID;
    char instruction;
    char err;
    int  parameter;
    short  CRC [256];
                       };
  //  Place values in the parameters
   int main(){
     struct  INSTRUCTION_PACKET   P1;
     P1.header1     = (0x..);
     P1.header2     = (0x..);
     P1.header3     = (0x..);
     P1.packet_ID   = (0x..);
     P1.length1     = (0x..);
     P1.length2     = (0x..);
     P1.instruction = {(0x..)};
     P1.parameter [0] ={};
     
    // Create specific delay
             
    //  check for for return packet
     
     //If err = 0x01   it fail to process the sent instruction
     //If err = 0x02   undifine instruction has been used
     //IF err = 0x03   a CRC error packets sent do not match
                                 }                  
