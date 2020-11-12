/* PIC18 Config Code File
* File:   PIC18_config.h
* Author: Ricardo Munoz
*
*
* Created on: Aug 18, 2020
*
* This file was created to configure the pic18f45k20 device.
*
* Compiler: XC8
* MPLAB IDE: X
*/



#ifndef pic18f45k20_Config_H
#define pic18f45k20_Config_H

//#include "pic18f45k20.h"
//#include <xc.h>

#ifdef    __cplusplus
 //extern "C" {
#endif
     

/****************************Function Declarations*****************************/
void OSC_freq(void);
void interrups_initial(void);
void Timer_0(void);
void Timer_1(void);
void Timer_2(void);
void Timer_3(void);
void EUSART(void);

 

#ifdef    __cplusplus
// }
 #endif
#endif /* __cplusplus */
