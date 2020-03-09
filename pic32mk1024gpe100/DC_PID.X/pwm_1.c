

#include <proc/p32mk1024gpe100.h>

#include "pwm_1.h"
#define SYS_FREQ 48000000

inline void delay_np(int i) ;


void pwm_init()
{ 
    ANSELC = 0 ;
    ANSELB = 0 ;
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
  
    RPC7R = 0b00110 ; // oc 7
    TRISCbits.TRISC7 = 0 ;
    OC7CON = 0x0 ;
    OC7CONbits.ON = 0 ;
    OC7CONbits.OCM = 0b110 ; // pwm with no fault selected
    OC7CONbits.OC32 = 1; // 16bit timer 
    OC7CONbits.OCTSEL = 0; //timer 2 selected
    OC7R = 0 ; 
    
    RPB6R = 0b00110 ; // oc 5
    TRISBbits.TRISB6 = 0 ;
    OC5CON = 0x0 ;
    OC5CONbits.ON = 0 ;
    OC5CONbits.OCM = 0b110 ; // pwm with no fault selected
    OC5CONbits.OC32 = 1; // 16bit timer 
    OC5CONbits.OCTSEL = 1; //timer 3 selected
    //OC5R = 20 ; 
    
    RPB7R = 0b00101 ; // oc 1
    TRISBbits.TRISB7 = 0 ;
    OC1CON = 0x0 ;
    OC1CONbits.ON = 0 ;
    OC1CONbits.OCM = 0b110 ; // pwm with no fault selected
    OC1CONbits.OC32 = 1; // 16bit timer 
    OC1CONbits.OCTSEL = 1; //timer 3 selected
    //OC1R = 20 ; 
    
    /*   TIMER 2 init*/
    T2CONbits.TCKPS = 0b100;  // prescalar to 1:4
    T2CONbits.T32 = 1 ;
    TMR2 = 0;
    PR2 = 300 ;  // SYSclk is 24MHZ PBCLK is sysclk/2 = 12MHZ = 0.083 us
    //T2CONbits.ON = 1 ;  // pr2+1 = 50/0.083(Timer clk prd) *4(prescalar)
                            // 1/20khz = 50 us 
     
     /*   TIMER 3 init*/
    T3CONbits.TCKPS = 0b100;  // prescalar to 1:4
    T3CONbits.T32 = 1 ;
    TMR3 = 0;
    PR3 = 300 ;  // SYSclk is 24MHZ PBCLK is sysclk/2 = 12MHZ = 0.083 us
    //T2CONbits.ON = 1 ;  // pr2+1 = 50/0.083(Timer clk prd) *4(prescalar)
                            // 1/20khz = 50 us 
    T3CONbits.ON = 1 ; // start timer 
    //T2CONbits.ON = 1 ; // start timer
   
    OC5CONbits.ON = 1 ; // start OP CMP
    OC1CONbits.ON = 1 ; // start OP CMP
}


void dc_run(uint8_t run, uint32_t spd)
{   
    if (run == 1)
    {
          // Clockwise 
        OC1RS = 0 ; 
        T3CONbits.ON = 1 ; // start timer 
        OC5CONbits.ON = 1 ; // start OP CMP
        OC5RS = spd;               
        delay_np(1);        
    }
    else{
        OC5RS = 0 ;
        TMR3 = 0 ;
    }
}

void dc_run_CC(uint8_t run, uint32_t spd)
{   
           // Counter.CLKWISE
    if (run == 1)
    {
        OC5RS = 0 ;
        T3CONbits.ON = 1 ; // start timer 
        OC1CONbits.ON = 1 ; // start OP CMP
        OC1RS = spd;              
        delay_np(1);                               
    }  
    else{
        OC1RS = 0 ;
        TMR3 = 0 ;
    }
}  
 

void pwmOut(int out) {                               
  if (out > 20) {                         // if REV > encoderValue motor move in forward direction.    
    dc_run( 1, abs(out)) ;                         // calling motor to move forward
  }
  if (out < -20) {
    dc_run_CC( 1, abs(out)) ;                             // calling motor to move reverse
  }
  else if(out == 0){
      dc_run(0,0) ;
        dc_run_CC(0,0) ;
  }
}




void ISR_config(){
//    ANSELAbits.ANSA0 = 0 ;
//    TRISAbits.TRISA0 = 0 ;
    ANSELE = 0 ;
    ANSELB = 0 ;
    ANSELA = 0 ; // digital 
//    TRISGbits.TRISG12 = 0 ;  // output
//    TRISGbits.TRISG13 = 0 ; 
    TRISAbits.TRISA0 = 1 ;  //input
    TRISEbits.TRISE8 = 1 ;  //input
  // TRISBbits.TRISB0 = 1 ;  //input
   // TRISBbits.TRISB1 = 1 ;  //input
    
    CNCONAbits.EDGEDETECT = 1 ; //CNSTATx is used to notify the change
    CNCONEbits.EDGEDETECT = 1 ; //CNSTATx is used to notify the change
   // CNCONBbits.EDGEDETECT = 1 ; //CNSTATx is used to notify the change
    //CNSTATFbits.CNSTATF12 = 1 ;
    //CNFFbits.CNFF12 = 1 ;
 
    CNPUAbits.CNPUA0 = 1 ; // pullup on
    CNPUEbits.CNPUE8 = 1 ;
   // CNPUBbits.CNPUB0 = 1 ;
   // CNPUBbits.CNPUB1 = 1 ;
    CNCONAbits.ON = 1 ;  //
    CNENAbits.CNIEA0 = 1 ; // +ve edge detection
 
    CNCONBbits.ON = 1 ;
   // CNENBbits.CNIEB0 = 1 ; // +ve edge detection
   // CNENBbits.CNIEB1 = 1 ;  // B0,B1
    
    CNCONEbits.ON = 1 ;  //
    CNENEbits.CNIEE8 = 1 ; // +ve edge detection
    
    CNNEAbits.CNNEA0 = 1 ;  // Negative edge
    CNNEEbits.CNNEE8 = 1 ;  // Negative edge
   // CNNEBbits.CNNEB0 = 1 ;  // Negative edge B0
   // CNNEBbits.CNNEB1 = 1 ;  // Negative edge B1
    
    IFS1bits.CNAIF = 0 ; //reset int flag
    IPC11bits.CNAIP = 4 ; // set it priority
    IPC11bits.CNAIS = 0;  // set it sub priority
    IEC1bits.CNAIE = 0 ; // enable int from port F
    IEC1bits.CNAIE = 1 ;
    
    IFS1bits.CNEIF = 0 ; //reset int flag
    IPC12bits.CNEIP = 4 ; // set it priority
    IPC12bits.CNEIS = 1;  // set it sub priority
    IEC1bits.CNEIE = 0 ; // enable int from port E
    IEC1bits.CNEIE = 1 ;
    
    IFS1bits.CNBIF = 0 ; //reset int flag
    IPC11bits.CNBIP = 4 ; // set it priority
    IPC11bits.CNBIS = 0;  // set it sub priority
    IEC1bits.CNBIE = 0 ; // enable int from port B
    IEC1bits.CNBIE = 1 ;
    
    INTCONSET = _INTCON_MVEC_MASK; // multi vectored mask
    //LATAbits.LATA0 = 1 ;
    
    __builtin_enable_interrupts();
   
}

    
inline void delay_np(int i)
{
    int j ;
    for(j=0;j<i;j++)
    {
        Nop();
    }
}


//void delay_ms(float i)
//{
//    float DLY = (46.875*i); // SYSclk is 12MHZ PBCLK is sysclk/2 = 6MHZ
//                              //Prescalar is 6MHZ / 256 = 23437.5                  
//    T1CONbits.TCKPS = 0x3; // turn timer off and set prescaller to 1:256
//    TMR1 = 0;
//    PR1 = DLY ;//0xFFFF;
//    T1CONSET = 0x8000; // start timer        
//    //while (TMR1 < DLY) ; //wait 
//    //T1CONCLR = 0x8000; // stop timer
//    while(TMR1 != PR1) ;
//    T1CONCLR = 0x8000 ;  //Stop timer
//}

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