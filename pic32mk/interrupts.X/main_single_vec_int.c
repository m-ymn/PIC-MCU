/* 
 * File:   newmain.c
 * Author: Admin
 *
 * Created on October 10, 2019, 11:17 AM
 */
#include "config.h"
#include <xc.h>
#include <sys/attribs.h>
#include <stdio.h>
#include <stdlib.h>


int count ;

int main() {
    
    TRISGbits.TRISG12 = 0 ;
    T1CONbits.TCKPS = 0x3 ;  // 1:256 prescalar
    TMR1 = 0 ;
    PR1 = 10 ;
    T1CONbits.ON = 1 ;
    
    IFS0bits.T1IF = 0 ;  // clear interrupt flag
    IPC1bits.T1IP = 5 ;
    IPC1bits.T1IS = 3 ; 
    INTCONbits.MVEC = 0 ;
    __builtin_enable_interrupts();
    IEC0bits.T1IE = 1 ;
    
    while(1) ;

    return (EXIT_SUCCESS);
}

void __ISR(0,ipl5auto) T1changehandler(void) ;

T1changehandler(void)
{
    count++ ;
    IFS0bits.T1IF = 0 ;  // clear int flag
    if(count > 3000 && count < 10000 )
    {
        LATGbits.LATG12 = 1 ;
    }
    if(count > 10000)
    {
        LATGbits.LATG12 = 0 ;
    }
}

