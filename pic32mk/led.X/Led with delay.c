
#include <xc.h>
#include"config.h"
#include <stdlib.h>
#define SYS_FREQ 24000000

void delay(void)
 {
    int i ;
    for(i=0; i<100000; i++) ;
 }

//void delay_us(unsigned int us)
//{
//    // Convert microseconds us into how many clock ticks it will take
//	us *= SYS_FREQ / 1000000 / 2; // Core Timer updates every 2 ticks
//       
//    _CP0_SET_COUNT(0); // Set Core Timer count to 0
//    
//    while (us > _CP0_GET_COUNT()); // Wait until Core Timer count reaches the number we calculated earlier
//}
//
//void delay_ms(int ms)
//{
//    delay_us(ms * 1000);
//}
//    
int main(){
    
    TRISGbits.TRISG12 = 0 ; // pin12 of port G as output
    TRISGbits.TRISG13 = 0 ;
    TRISAbits.TRISA0 = 0 ;
    ANSELA = 0 ;
    //LATAbits.A14 = 1 ;
    while(1)
    {
        
        delay_ms(1000) ;
        //while(TMR1 != 0) ;
        LATAbits.LATA0 = 1 ;
        PORTG |= 1<<12 ; // PIN_12 LED ON
        PORTGbits.RG13 = 0 ;  // PIN_13 LED OFF
        
    
        delay_ms(1000) ;
        LATAbits.LATA0 = 0 ;
        PORTG &= 0<<12 ;       
        PORTGbits.RG13 = 1 ;
    }
    
    return 0 ;
}

void delay_ms(int i)
 {
     float DLY = (46.875*i); // SYSclk is 12MHZ PBCLK is sysclk/2 = 6MHZ
                              //Prescalar is 6MHZ / 256 = 23437.5                  
     T2CONbits.TCKPS = 0b111; // turn timer off and set prescaller to 1:256
     T2CONbits.T32 = 1 ;
     TMR2 = 0;
     PR2 = DLY ;//0xFFFF;
        T2CONSET = 0x8000; // start timer        
        //while (TMR1 < DLY) ; //wait 
        //T1CONCLR = 0x8000; // stop timer
        while(TMR2 != PR2) ;
        T1CONCLR = 0x8000 ;  
}