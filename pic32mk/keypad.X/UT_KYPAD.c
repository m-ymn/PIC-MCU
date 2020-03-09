/* 
 * File:   newmain.c
 * Author: Admin
 *
 * Created on September 4, 2019, 1:33 PM
 */
#include "keypad.h"
#include <xc.h>
#include <stdlib.h>
#include "config.h"
#include <string.h>
#include "s1.h"
#include <sys/attribs.h>

uint8_t txMessage[50] ;
uint8_t dta[5] ;
uint8_t fmsg[] = "Connected to microcontroller\n\r" ;
uint8_t f2msg[] = "Enter 4 Digit PIN\n\r" ;
uint8_t pass[] = "4514" ;

int main() {
    Uart_init() ;
    SendString(fmsg) ;
    
    TRISGbits.TRISG12 = 0 ;  // output
    key_init() ;
    while(1)
    {
    SendString(f2msg) ;  // send enter pin
    ReadKString(dta, sizeof(dta));
    //while(dta[4] != '#' ) ;
    if(strcmp(dta,pass) == 0)
    {
        SendString("UNLOCK SUCCESS\n\r") ;
        PORTG = 1<<13 ; // GREEN PIN_13 LED ON
        PORTGbits.RG12 = 0 ; //RED LED
        delay_ms(1000) ;
    }
    else
    {
        SendString("Invalid PASS\n\r") ;
        PORTGbits.RG13 = 0 ;
        PORTGbits.RG12 = 1 ;
        delay_ms(1000) ;
        PORTGbits.RG12 = 0 ;
        
    }
    }
    
    
    
    return 1;
}

