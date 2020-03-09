/* 
 * File:   newmain.c
 * Author: Admin
 *
 * Created on August 16, 2019, 12:29 PM
 */


#include <xc.h>
#include "config.h"
#include <stdint.h>



#define led_ON  1
#define led_OFF  0

#define HIGH 1 
#define LOW 0



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
        T1CONCLR = 0x8000 ;  
}


int main() 
{
    ANSELGbits.ANSG11 = 0 ;
    TRISGbits.TRISG12 = 0 ;  // digital output
    TRISGbits.TRISG11 = 1 ; // digital input
    int btn_st = 0 ;
    int pre_btn_st  = 0 ;
    btn_st = PORTGbits.RG11 ;
    
    while(1)
    {
        btn_st = PORTGbits.RG11 ;
        if(btn_st != pre_btn_st)
        {
            if(btn_st == 0)
            {
                PORTGbits.RG12 = 1  ;
            }
            else if (btn_st == 1)
            {
                PORTGbits.RG12 = 0  ;
            }
            delay_ms(50) ;
        pre_btn_st = btn_st ;
        }
        
    }
    return 0 ;
}

