/* 
 * File:   keypad.h
 * Author: Admin
 *
 * Created on September 4, 2019, 2:10 PM
 */

#ifndef KEYPAD_H
#define	KEYPAD_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#define HIGH 1
#define LOW 0

#define R_0  PORTGbits.RG6 
#define R_1  PORTAbits.RA0
#define R_2  PORTAbits.RA11
#define R_3  PORTEbits.RE8
#define C_0  PORTEbits.RE9
#define C_1  PORTBbits.RB0
#define C_2  PORTFbits.RF9
#define C_3  PORTFbits.RF10

#define sbt(b) (1UL << (b))    // set bit
#define rbt(b)  (0UL << (b))   // reset bit

#define PG  PORTG
#define PA  PORTA
#define PB  PORTB
#define PC  PORTC
#define PE  PORTE
    
    
void key_init() ;
int key_pressed() ;

char get_char() ;

void ReadKString(char *string, int length) ;


#ifdef	__cplusplus
}
#endif

#endif	/* KEYPAD_H */

