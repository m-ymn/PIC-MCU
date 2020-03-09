/* 
 * File:   newmain.c
 * Author: Admin
 *
 * Created on September 9, 2019, 2:57 PM
 */
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "adc.h"
/*
 * 
 */
int main() {

    TRISGbits.TRISG12 = 0; // output
    adc_init() ;     // AD1CHS<16:19> controls which analog pin goes to the ADC
 
    while(1)
    {
        ADCCON1bits.ON = 1;   
        ADCCON3bits.SAMP = 1 ; 
        //delay_ms(10) ;
        ADCCON3bits.RQCNVRT = 1 ;   // Begin sampling
        ADCCON3bits.SAMP = 0 ;
        while(!ADCDSTAT1bits.ARDY20) ;      // wait until acquisition is done

        delay_ms(50) ;                   // wait until conversion done
        uint16_t i = ADCDATA20 ;      // result stored in ADCdata
        if (i > 2045 )
        {
            PORTG |= 1<<12 ;
            //delay_ms(1000) ;
        }
        else if (i < 2045)
        {       
            PORTG = 0 ;
        }
    
    }
    
    
    return 1 ;
}

