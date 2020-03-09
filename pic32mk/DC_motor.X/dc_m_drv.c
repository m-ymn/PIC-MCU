

#include "dc_m_drv.h"



void dc_init()
{
    pwm_init() ;
    T2CONbits.ON = 1 ; // start timer 

    OC7CONbits.ON = 1 ; // start OP CMP 
    uint32_t i ;
//    for(i=0;i<1600;i++)
//    {
    OC7RS = 200 ;
//        //delay_ms(1);
//    }
    //delay_ms(500) ;
    //T2CONbits.ON = 0 ; // stop timer 
    //OC7CONbits.ON = 0 ;
}

void pwm_init()
{
    RPG6R = 0b00110 ; // RG6 selected as op compare 7
    TRISGbits.TRISG6 = 0 ;
    //OC7CONbits.ON = 0 ;
    OC7CONbits.OCM = 0b110 ; // pwm with no fault selected
    OC7CONbits.OC32 = 0; // 16bit timer 
    OC7CONbits.OCTSEL = 0; //timer 2 selected
    //OC7R = 100 ;
    //OC7RS = 100 ;

  /*   TIMER 3 init*/

    T2CONbits.TCKPS = 0x3;  // prescalar to 1:256
    TMR2 = 0;
    PR2 = 23.4375*400 ;  // 23.4375*400 = 9375 


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
