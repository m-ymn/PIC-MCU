/* 
 * File:   lcd.h
 * Author: Admin
 *
 * Created on September 11, 2019, 2:30 PM
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdlib.h>
#include <stddef.h>
    
#define HIGH  1
#define LOW   0
    
#define D4   LATGbits.LATG6  //PORTGbits.RG6 
#define D5   LATAbits.LATA0  //PORTAbits.RA0
#define D6   LATAbits.LATA11  //PORTAbits.RA11
#define D7   LATEbits.LATE8   //PORTEbits.RE8

#define RS   LATEbits.LATE9  //PORTEbits.RE9
#define EN   LATBbits.LATB0   // PORTBbits.RB0

//#define C_2  PORTFbits.RF9
//#define C_3  PORTFbits.RF10

#define sbt(b) (1UL << (b))    // set bit
#define rbt(b)  (0UL << (b))   // reset bit
   

void lcd_init() ;
void lcd_write(uint8_t value) ;
void lcd_cmd(uint8_t value) ;
void delay_ms(int i) ;
void pulseEnable(void) ;
void write4bits(uint8_t value) ;
void lcd_String(char *a) ;
void lcd_set_Cursor(char a, char b) ;

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

