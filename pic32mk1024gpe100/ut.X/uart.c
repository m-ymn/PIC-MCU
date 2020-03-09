
#include "s1.h"
#include <xc.h>
#include <stdlib.h>
#include "config.h"
#include <string.h>


uint8_t txMessage[50] ;
uint8_t dta[6] ;
uint8_t fmsg[] = "Connected to microcontroller\n\r" ;
uint8_t f2msg[] = "Enter 4 Digit PIN\n\r" ;
uint8_t pass[] = "4514" ;


int main ()
{
    Uart_init() ;
    SendString(fmsg) ;
    while(1)
    {
    SendString(f2msg) ;
    ReadString(dta, sizeof(dta));
    if(strcmp(dta,pass) == 0)
    {
        SendString("UNLOCK SUCCESS\n\r") ;
        PORTG = 1<<13 ; // GREEN PIN_13 LED ON
        PORTGbits.RG12 = 0 ; //RED LED
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





    
    


