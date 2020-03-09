/* 
 * File:   newmain.c
 * Author: Admin
 *
 * Created on August 27, 2019, 11:06 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "config.h"

void delay(void)
 {
    int i ;
    for(i=0; i<100000; i++) ;
 }
    
int main(){
    
    TRISCbits.TRISC6 = 0 ; // pin12 of port G as output
    TRISCbits.TRISC7 = 0 ;
    while(1)
    {
        delay() ;
        PORTC |= 1<<6 ; // PIN_12 LED ON
        PORTCbits.RC7 = 0 ;  // PIN_13 LED OFF
        delay() ;
        PORTC &= 0<<6 ;       
        PORTCbits.RC7 = 1 ;
    }
    
    return 0 ;
}
