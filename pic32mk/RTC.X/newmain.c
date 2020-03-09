/* 
 * File:   newmain.c
 * Author: Admin
 *
 * Created on October 14, 2019, 10:51 AM
 */

#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

int main()
{
//and RTCC write is enabled i.e. RTCWREN (RTCCON<3>) =1;*/
    //starting critical sequence
    TRISGbits.TRISG12 = 0 ;
    asm volatile ("di") ;
    SYSKEY = 0xaa996655 ; // write first unlock key to SYSKEY
    SYSKEY = 0x556699aa ; // write second unlock key to SYSKEY
    //RTCCONSET = 0x8; // set RTCWREN in RTCCONSET
    //end critical sequence
    RTCCONbits.RTCWREN = 1 ;
    unsigned long time=0x04150000 ;// set time to 04 hr, 15 min, 33 sec
    unsigned long date=0x06102705 ;// set date to Friday 27 Oct 2006
    RTCCONCLR=0x8000 ; // turn off the RTCC
    while(RTCCONbits.RTCCLKON) ; // wait for clock to be turned off
    RTCCONbits.RTCWREN = 1 ;
    RTCTIME=time ; // safe to update the time
    //delay_ms(10) ;
    RTCDATE=date; // update the date
    //delay_ms(10) ;
    RTCCONSET=0x8000; // turn on the RTCC
    while(!RTCCONbits.RTCCLKON); // wait for clock to be turned on
    RTCCONbits.RTCWREN = 0 ;
    while(RTCTIMEbits.MIN01 != 6) ;  // wait for 1 minute
    LATGbits.LATG12 = 1 ;
    
    
    
    while(1) ;
}


void delay_ms(int i)
{
    float DLY = (23.4375*i); // SYSclk is 12MHZ PBCLK is sysclk/2 = 6MHZ
                              //Prescalar is 6MHZ / 256 = 23437.5                  
    T1CONbits.TCKPS = 0x3; // turn timer off and set prescaller to 1:256
    TMR1 = 0;
    PR1 = DLY ;//0xFFFF;
    T1CONSET = 0x8000; // start timer        
    //while (TMR1 < DLY) ; //wait 
    //T1CONCLR = 0x8000; // stop timer
    while(TMR1 != PR1) ;
    T1CONCLR = 0x8000 ;  //Stop timer
}