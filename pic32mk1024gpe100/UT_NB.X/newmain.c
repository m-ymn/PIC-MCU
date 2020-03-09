/* 
 * File:   newmain.c
 * Author: Admin
 *
 * Created on February 4, 2020, 2:51 PM
 */
#include "config_1.h"
#include "s1.h"
#include <stdio.h>
#include <stdlib.h>

void delay_ms(unsigned int) ;
#define SYS_FREQ 48000000
/*
 * 
 */
int main() {
    ANSELG = 0 ;
    TRISGbits.TRISG12 = 0 ; //output
    
    p_datbuf = dat_buf ;
    
    Uart_init() ;
    uart_int() ;
    SendString("UART") ;
    while(1) 
    {
        LATGbits.LATG12 = 1 ;
        delay_ms(500) ;
        LATGbits.LATG12 = 0 ;
        delay_ms(500) ;
       // U4TXREG = dat_buf[256] ;
        SendString("how r u") ;
             
        
    }
    
    return 0;
}



void delay_ms(unsigned int ms)
{
    // Convert microseconds us into how many clock ticks it will take
	ms *= (SYS_FREQ/2000000)*1000; // Core Timer updates every 2 ticks
       
    _CP0_SET_COUNT(0); // Set Core Timer count to 0
    
    while (ms > _CP0_GET_COUNT()); // Wait until Core Timer count reaches the number we calculated earlier
}