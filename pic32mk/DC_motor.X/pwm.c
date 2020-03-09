

#include <proc/p32mk1024gpe100.h>

#include "pwm.h"


void pwm_init()
{
    RPG6R = 0b00110 ; // RG6 selected as op compare 7
    TRISGbits.TRISG6 = 0 ;
    OC7CONbits.ON = 0 ;
    OC7CONbits.OCM = 0b110 ; // pwm with no fault selected
    OC7CONbits.OC32 = 0; // 16bit timer 
    OC7CONbits.OCTSEL = 0; //timer 2 selected
    OC7R = 100 ;
    OC7RS = 100 ;

  /*   TIMER 3 init*/

    T2CONbits.TCKPS = 0x3;  // prescalar to 1:256
    TMR2 = 0;
    PR2 = 23.4375*400 ;  


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
