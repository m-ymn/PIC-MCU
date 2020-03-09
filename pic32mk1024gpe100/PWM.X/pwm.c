

#include <proc/p32mk1024gpe100.h>

#include "pwm.h"
#include "s1_1.h"

inline void delay_np(int i) ;


void pwm_init()
{
    
    
    RPC6R = 0b00101 ; // RPC6 selected as op compare 4
    //RPG12R = 0b00101 ; // RG12 selected as op compare 3
    //TRISGbits.TRISG12 = 0;
   // CNPDCbits.CNPDC6 = 1 ;
    TRISCbits.TRISC6 = 0 ;
    OC4CON = 0x0 ;
    OC4CONbits.OCM = 0b110 ; // pwm with no fault selected
    OC4CONbits.OC32 = 1; // 16bit timer 
    OC4CONbits.OCTSEL = 0; //timer 2 selected
    OC4R = 0 ;
    //OC3RS = 100 ;

  /*   TIMER 2 init*/

    
    
    RPC7R = 0b00110 ; // oc 7
    TRISCbits.TRISC7 = 0 ;
    OC7CON = 0x0 ;
    OC7CONbits.ON = 0 ;
    OC7CONbits.OCM = 0b110 ; // pwm with no fault selected
    OC7CONbits.OC32 = 1; // 16bit timer 
    OC7CONbits.OCTSEL = 0; //timer 2 selected
    OC7R = 0 ; 
    
    T2CONbits.TCKPS = 0b011;  // prescalar to 1:4
    T2CONbits.T32 = 1 ;
    TMR2 = 0;
    PR2 = 300 ;  // SYSclk is 24MHZ PBCLK is sysclk/2 = 12MHZ = 0.083 us
    //T2CONbits.ON = 1 ;  // pr2+1 = 50/0.083(Timer clk prd) *4(prescalar)
                            // 1/20khz = 50 us 
}


void dc_run(uint8_t run, uint32_t spd,uint8_t turns)
{   
    if (run == 1)
    {
          // Clockwise 
            OC4RS = 0 ;
            
            //OC4CONbits.ON = 0 ; // stop OP CMP
            T2CONbits.ON = 1 ; // start timer 
            OC7CONbits.ON = 1 ; // start OP CMP
            //RPC6R = 0 ; // RPC6 selected as op compare 10
            //OC7RS = spd ;  // speed
            cnt = 1 ;
            
            do
            {  //LATCbits.LATC7 = 1 ;
                
                OC7RS = spd; 
                
//                if(spd > 180)
//                 {
//                     spd -= 20;
//                     OC7RS = spd ;
//                 }
                delay_np(1);
                
                OC7RS = 0 ;
                 
                //delay_np(1); 
                
                
            }while(cnt != (96*turns)) ;
             OC7RS = 0 ;
            TMR2 = 0 ;
            
            //cnts += cnt ;
            cnt = 1 ; 
            //cnts = cnt ; 
           // OC7CONbits.ON = 0 ; // start OP CMP
            //T2CONbits.ON = 0 ; // start timer
           //OC7RS = 0 ;
           //SendNUM(51) ;
            
    }
}

void dc_run_CC(uint8_t run, uint32_t spd,uint8_t turns)
{   
           // Counter.CLKWISE
    if (run == 1)
    {
            OC7RS = 0 ;
            //OC7CONbits.ON = 0 ; // stop OP CMP
            T2CONbits.ON = 1 ; // start timer 
            OC4CONbits.ON = 1 ; // start OP CMP
            //RPC6R = 0 ; // RPC6 selected as op compare 10
            //OC7RS = spd ;  // speed
            //cnts = cnt ;
            cnt = 1 ;
            
            do
            {  //LATCbits.LATC7 = 1 ;
                OC4RS = spd;
                 
//                 if(spd > 160)
//                 {
//                     spd -= 20 ;
//                     OC4RS = spd ;
//                 }
                delay_np(1);
                   
                OC4RS = 0 ;
                 
                //delay_np(1);       
            }while(cnt != (96*turns)) ;
            OC4RS = 0 ;
            TMR2 = 0 ;
             
            //cnts += cnt ;
            cnt = 1 ; 
            
            //T2CONbits.ON = 0 ; // start timer 
            //OC4CONbits.ON = 0 ; // start OP CMP
            //OC4RS = 0 ;
            
            
    }  
}  
    
    
inline void delay_np(int i)
{
    int j ;
    for(j=0;j<i;j++)
    {
        Nop();
    }
}


void delay_ms(float i)
{
    float DLY = (46.875*i); // SYSclk is 12MHZ PBCLK is sysclk/2 = 6MHZ
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

