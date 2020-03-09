/* 
 * File:   newmain.c
 * Author: Admin
 *
 * Created on September 10, 2019, 11:45 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "pwm.h"
#include "config_1.h"

#define SYS_FREQ 24000000    // 24MHZ
/*
 * @main
 */
int main() {
   
//    TRISCbits.TRISC6 = 0;
    //TRISCbits.TRISC7 = 0 ;
//    
//    LATCbits.LATC6 = 1 ;
    //LATCbits.LATC7 = 0 ; 
//    
//    pwm_init() ;
//    cntr();
//    cntr2();
//    
//    T2CONbits.ON = 1 ; // start timer 
//    OC7CONbits.ON = 0 ;
//    OC4CONbits.ON = 1 ; // start OP CMP 
//    delay_ms(200) ;
//    OC7RS = 0 ;
//    while(1){
//        do
//    {  //LATCbits.LATC7 = 1 ;
//        
//        
//        OC4RS = 100; 
//        //delay_ms(1) ;
//        
//        delay_np(2);
//        OC4RS = 0 ;
//       // delay_ms(1) ;
//        
//        delay_np(2); 
//        
//    }
//        while((TMR6<96) && (TMR5<96)) ;
//    
//    TMR6 = 0 ;
//    TMR5 = 0 ;
//    OC4RS = 0 ;
//    delay_ms(1000) ;
//    
  //  }
    pwm_init() ;
        cntr();
        cntr2();
    while(1)
    {
    dc_run(1, 1, 100, 96) ;
    delay_ms(1000) ;
    //dc_run(0,0,0,0) ;
    dc_run(1,0,100,96) ;
    delay_ms(1000) ;
    }//dc_run(0,0,0,0) ;
    return 1 ;
}

void cntr()
{
    ANSELAbits.ANSA0 = 0 ;
    TRISAbits.TRISA0 = 1 ; // input
    T6CKR = 0b0000 ; // AO selewcted as encoder input
    
    T6CONbits.TCKPS = 0b000 ; // turn timer off and set prescaller to 1:256
    T6CONbits.TCS = 1 ;
    TMR6 = 0;
    PR6 = 0xFFFF ;//0xFFFF;
    T6CONbits.ON = 1 ; // start timer  
   // while(TMR6 != PR6) ;
   // T6CONCLR = 0x8000 ;  //Stop timer)
}

void cntr2()
{
    ANSELBbits.ANSB0 = 0 ;
    TRISBbits.TRISB0 = 1 ; // input
    T5CKR = 0b0010 ; // BO selewcted as encoder input
    
    T5CONbits.TCKPS = 0b000 ; // turn timer off and set prescaller to 1:256
    T5CONbits.TCS = 1 ;
    TMR5 = 0;
    PR5 = 0xFFFF ;//0xFFFF;
    T5CONbits.ON = 1 ; // start timer  
   // while(TMR6 != PR6) ;
   // T6CONCLR = 0x8000 ;  //Stop timer)
}

inline void delay_np(int i)
{
    int j ;
    for(j=0;j<i;j++)
    {
        Nop();
    }
}

void delay_us(unsigned int us)
{
    // Convert microseconds us into how many clock ticks it will take
	us *= SYS_FREQ / 1000000 / 2; // Core Timer updates every 2 ticks
       
    _CP0_SET_COUNT(0); // Set Core Timer count to 0
    
    while (us > _CP0_GET_COUNT()); // Wait until Core Timer count reaches the number we calculated earlier
}

void delay_ms(int ms)
{
    delay_us(ms * 1000);
}

