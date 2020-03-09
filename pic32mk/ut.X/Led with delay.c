
#include <xc.h>
#include"config.h"
#include <stdlib.h>


void delay(void)
 {
    int i ;
    for(i=0; i<100000; i++) ;
 }
    
int main(){
    
    TRISGbits.TRISG12 = 0 ; // pin12 of port G as output
    TRISGbits.TRISG13 = 0 ;
    while(1)
    {
        delay() ;
        PORTG |= 1<<12 ; // PIN_12 LED ON
        PORTGbits.RG13 = 0 ;  // PIN_13 LED OFF
        delay() ;
        PORTG &= 0<<12 ;       
        PORTGbits.RG13 = 1 ;
    }
    
    return 0 ;
}