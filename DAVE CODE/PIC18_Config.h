/* 
 * File:   PIC18_Config.h
 * Author: Owner
 *
 * Created on July 22, 2014, 9:01 PM
 */

#ifndef PIC18_CONFIG_H
#define	PIC18_CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

/****************************Function Declarations*****************************/
void init_OSC(void);
void init_Ints(void);
void init_Timers(void);
void init_UART1(void);
void init_UART2(void);



#ifdef	__cplusplus
}
#endif

#endif	/* PIC18_CONFIG_H */

