

#include "dc_w_fb.h"



void dc_run(uint8_t run, uint8_t dir, uint16_t spd)
{
    if (run == 1)
    {
        
        if (dir == 0)   // Clockwise
        { 
            T3CONbits.ON = 0 ; // stop timer 
            OC4CONbits.ON = 0 ; // stop OP CMP
            
            //RPC6R = 0 ; // RPC6 selected as op compare 10
            OC7RS = spd ;  // speed
            
            //LATCbits.LATC6 = 0;
            T2CONbits.ON = 1 ; // start timer 
            OC7CONbits.ON = 1 ; // start OP CMP
            
        }
        if (dir == 1)   // Counter.CLKWISE
        {
            
            //RPC7R = 0 ; // oc 7
            OC4RS = spd ;
            T2CONbits.ON = 0 ;   // stop timer 
            OC7CONbits.ON = 0 ; // stop OP CMP
            //LATCbits.LATC7 = 0;
            T3CONbits.ON = 1 ;  // start timer 
            OC4CONbits.ON = 1 ; // start OP CMP
                   // speed
        }    
    }
    else if(run == 0)
    {
        RPC6R = 0 ;
        RPC7R = 0 ;
        LATCbits.LATC7 = 1 ;
        LATCbits.LATC6 = 1 ;
        T2CONbits.ON = 0 ;      // start timer 
        OC7CONbits.ON = 0 ;     // start OP CMP
        T3CONbits.ON = 0 ;      // start timer 
        OC4CONbits.ON = 0 ;      // start OP CMP
        
    }
}


void dc_init()
{
    RPC7R = 0b00110 ; // oc 7
    RPC6R = 0b00101 ; // RPC6 selected as op compare 4
    TRISCbits.TRISC6 = 0 ;
    TRISCbits.TRISC7 = 0 ;
    //OC7CONbits.ON = 0 ;
    OC7CONbits.OCM = 0b110 ; // pwm with no fault selected
    OC7CONbits.OC32 = 0; // 16bit timer 
    OC7CONbits.OCTSEL = 0; //timer 2 selected
    //OC7R = 100 ;
    
    OC4CONbits.OCM = 0b110 ; // pwm with no fault selected
    OC4CONbits.OC32 = 0; // 16bit timer 
    OC4CONbits.OCTSEL = 1; //timer 3 selected
    //OC4R = 100 ;
    //OC7R = 100 ;
    //OC7RS = 100 ;
  /*   TIMER init*/

    T2CONbits.TCKPS = 0x3;  // prescalar to 1:256
    TMR2 = 0;
    PR2 = 23.4375*40 ;  // 23.4375*400 = 9375 
    
    T3CONbits.TCKPS = 0x3;  // prescalar to 1:256
    TMR3 = 0;
    PR3 = 23.4375*40 ;  // 23.4375*400 = 9375 


    //T2CONbits.ON = 1 ; // start timer 

    //OC7CONbits.ON = 1 ; // start OP CMP 
    
//    for(i=0;i<1600;i++)
//    {
    //OC7RS = 300 ; // speed or duty cycle
//        //delay_ms(1);
//    }
    //delay_ms(500) ;
    //T2CONbits.ON = 0 ; // stop timer 
    //OC7CONbits.ON = 0 ;
}


void enc_init()
{
//    ANSELGbits.ANSG6 = 0 ;  // digital 
    ANSELAbits.ANSA0 = 0 ;
    
//    TRISGbits.TRISG6 = 1 ;   
    TRISAbits.TRISA0 = 1 ;   //input
    
//    CNCONGbits.EDGEDETECT = 1 ; //CNSTATx is used to notify the change
    CNCONAbits.EDGEDETECT = 1 ;
    
//    CNNEGbits.CNNEG6 = 0 ;  // Negative edge
//    CNENGbits.CNIEG6 = 1 ; // +ve edge detection
//    CNPUGbits.CNPUG6 = 1 ; // pullup on
    
    CNNEAbits.CNNEA0 = 0 ;  // Negative edge
    CNENAbits.CNIEA0 = 1 ; // +ve edge detection
    CNPUAbits.CNPUA0 = 1 ; // pullup on
    
//    CNCONGbits.ON = 1 ;   // change notice on 
    CNCONAbits.ON = 1 ;
    
//    IFS1bits.CNGIF = 0 ; // reset int flag
//    IPC12bits.CNGIP = 3 ; // set it priority
//    IPC12bits.CNGIS = 0;  // set it sub priority
//    IEC1bits.CNGIE = 0 ;
//    IEC1bits.CNGIE = 1 ;  // enable int from port G
    
    IFS1bits.CNAIF = 0 ; // reset int flag
    IPC11bits.CNAIP = 4 ; // set it priority
    IPC11bits.CNAIS = 0;  // set it sub priority     
    IEC1bits.CNAIE = 0 ;
    IEC1bits.CNAIE = 1 ;  // enable int from port A
    
    INTCONSET = _INTCON_MVEC_MASK; // multi vectored mask
    __builtin_enable_interrupts();
    
}

void delay_ms(int i)
{
    float DLY = (23.4375*i); // SYSclk is 12MHZ PBCLK is sysclk/2 = 6MHZ
                              //Prescalar is 6MHZ / 256 = 23437.5                  
    T1CONbits.TCKPS = 0x3; // turn timer off and set prescaller to 1:256
    TMR4 = 0;
    PR4 = DLY ;//0xFFFF;
    T4CONSET = 0x8000; // start timer        
    //while (TMR1 < DLY) ; //wait 
    //T1CONCLR = 0x8000; // stop timer
    while(TMR4 != PR4) ;
    T4CONCLR = 0x8000 ;  //Stop timer
}
