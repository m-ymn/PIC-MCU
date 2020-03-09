/* 
 * File:   newmain.c
 * Author: Admin
 *
 * Created on October 11, 2019, 11:45 AM
 */

#include "config.h"
#include <xc.h>
#include <sys/attribs.h>
#include <stdio.h>
#include <stdlib.h>

int count = 0 ;

int main() {
    
    TRISGbits.TRISG13 = 0 ;
    TRISGbits.TRISG14 = 0 ;
    T1CONbits.TCKPS = 0x3 ;  // 1:256 prescalar
    TMR1 = 0 ;
    PR1 = 100 ;
    T1CONbits.ON = 1 ;
    
    T2CONbits.TCKPS = 0x7 ;  // 1:64 prescalar
    TMR2 = 0 ;
    PR2 = 40 ;
    T2CONbits.ON = 1 ;
    
    IFS0bits.T1IF = 0 ;  // clear interrupt flag
    IPC1bits.T1IP = 1 ;
    IPC1bits.T1IS = 0 ; 
    
    IFS0bits.T2IF = 0 ;  // clear interrupt flag
    IPC2bits.T2IP = 7 ;
    IPC2bits.T2IS = 1 ; 
    
    INTCONbits.MVEC = 0 ;
    
    
    IEC0bits.T1IE = 1 ;
    IEC0bits.T2IE = 1 ;
    __builtin_enable_interrupts();
    while(1) ;

    return 0 ;
}

void __ISR(0,ipl3) T1changehandler(void) ;
//void __ISR(_TIMER_2_VECTOR,ipl7) T2changehandler(void) ;

/*
T1changehandler(void)
{
    // 1. re-enable interrupts immediately (nesting)
    asm volatile ( " ei " );
    // 2. check and serve the highest priority first
    if (IFS0bits.T2IF == 1 )
    {
        count++;
    // clear the flag and exit
        IFS0bits.T2IF = 0 ;
        if(count > 4000 ){
        LATGbits.LATG14 = 1 ;
    }
    } // _T3
    // 3. check and serve the lower priority
    else if (IFS0bits.T1IF == 1)
    {
    // spend a LOT of time here!
        //while( 1);
    // before clearing the flag and exiting
        IFS0bits.T1IF = 0 ;
        if(count > 2000 ){
        LATGbits.LATG13 = 1 ;
    }
    } // _T2
} // Interrupt Handler
*/



/*
T1changehandler(void)
{
    // 3. re-enable interrupts immediately (nesting)
    asm volatile ( " ei " );
// 4. T1 handler code here
    if(count > 4000 ){
        LATGbits.LATG14 = 1 ;
    }
    
    //while( 1);
// 5. clear the flag and exit
    IFS0bits.T1IF = 0 ;
}

T2changehandler(void)
{
      
// 1. T2 handler is responsible for incrementing count
    count++;
    if(count > 2000 ){
       LATGbits.LATG13 = 1 ;
    }
// 2. clear the flag and exit
    IFS0bits.T2IF = 0 ;
 // T2 Interrupt Handler
}*/


