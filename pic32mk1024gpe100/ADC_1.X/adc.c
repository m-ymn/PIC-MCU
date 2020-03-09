

#include "adc.h"

void adc_init()
{
    //adc setup
    
    ANSELEbits.ANSE9 = 1; 
    TRISEbits.TRISE9 = 1;   // set RE9 as an input
      
    ADCCON1bits.ON = 0 ; 
    ADCCON1bits.FRACT = 0; //integer format selected
    ADCCON1bits.SIDL = 0;  
   // ADCCON1.FSSCLKEN = sysClk; N/A becoz it is SYSclk
    //ADCCON1.FSPBCLKEN = periClk;
    ADCCON1bits.SELRES = 0b11 ; //  8 bits

    ADCCON3bits.VREFSEL = 0b000 ; // VDD as Vhi
    ADCCON3bits.ADCSEL = 0b11 ; // SYSCLK is selected
    ADCCON3bits.CONCLKDIV = 0 ; // sysclk is Tq

   

    ADCANCONbits.WKUPCLKCNT = 0b0111 ;  // 32767 clk cycles warmup time
    
    // channel config
    
    ADCCON2bits.ADCDIV = 0b0011000 ; // Tad7 = tq/24 = 500k HZ
    ADCCON2bits.SAMC = 0b0000000011 ; // sample time 4 Tad
   // ADCCON2bits.ADCEIS = 0b000 ;  // early int bits
    
    
    ADCCON3bits.ADINSEL = 0b010100 ; //AN20 selected
    
    ADCTRG6bits.TRGSRC20 = 0b00000 ; // No trigger  

    ADCCON1bits.ON = 1;  
    ADCANCONbits.ANEN7 = 1 ;// shared adc 7 enabled
    delay_ms(100) ; 
    ADCCON3bits.DIGEN7 = 1 ; // adc7 enable
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

