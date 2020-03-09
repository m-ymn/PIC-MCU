/* 
 * File:   s1.h
 * Author: Admin
 *
 * Created on August 29, 2019, 12:26 PM
 */

#ifndef S1_H
#define	S1_H

#ifdef	__cplusplus
extern "C" {
#endif

    
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>





#define CLK_FREQUENCY 12000000  // 12MHZ Sys CLK
//#define TICK_FREQUENCY 100
#define D_BAUD_RATE 9600
#define PDSEL_DATA_8BITS_EVENPARITY 0
#define STSEL_STOPBITS_1 0
//#define TICK_PERIOD (CLK_FREQUENCY/(256*TICK_FREQUENCY))
#define BRG_VALUE ((CLK_FREQUENCY/D_BAUD_RATE)/16)-1
    

    
void Uart_init() ;
void SendString(char *string) ;
void ReadString(char *string, int length) ;
char ReadChar(void) ;
void SendChar(char c) ;
void delay_ms(int i) ;



#ifdef	__cplusplus
}
#endif

#endif	/* S1_H */

