/* 
 * File:   newmain.c
 * Author: Admin
 *
 * Created on September 10, 2019, 11:45 AM
 */
#include "config_1.h"
#include <stdio.h>
#include "pwm.h"


#include <sys/attribs.h>
#include <proc/p32mk1024gpe100.h>



#define HIGH 1
#define LOW 0

#define SYS_FREQ 24000000    // 24MHZ
/*
 * @main
 */
/* GLOBAL DEFS */
uint8_t state, statep , A , B ;
void ISR_config() ;
unsigned long millis();

int main() {
    //cnt =  0 ;
    int cpcnt ;
    cpcnt = millis() ;
    Uart_init() ;
    ISR_config() ; 
    SendString("CONNECTED\n\r") ;
    pwm_init() ;
    delay_ms(200 );
    cnts = 0 ;
   // dc_run(1,120,10) ;
    while(1)
    {
        dc_run(1,220 , 1) ;
//        dc_run(1,220,1) ;
//        dc_run(1,220,1) ;
//        dc_run(1,220,1) ;
        delay_ms(500) ;
        //dc_run(0,0,0,0) ;
        dc_run_CC(1,220,1) ;
//        dc_run_CC(1,220,1) ;
//        dc_run_CC(1,220,1) ;
//        dc_run_CC(1,220,1) ;
        delay_ms(500) ;
        cpcnt = millis() ;
    }//dc_run(0,0,0,0) ;
    return 1 ;
}

unsigned long millis()
{
    return (_CP0_GET_COUNT()/12000) ;   
}

void ISR_config(){
//    ANSELAbits.ANSA0 = 0 ;
//    TRISAbits.TRISA0 = 0 ;
    ANSELE = 0 ;
    ANSELA = 0 ; // digital 
//    TRISGbits.TRISG12 = 0 ;  // output
//    TRISGbits.TRISG13 = 0 ; 
    TRISAbits.TRISA0 = 1 ;  //input
    TRISEbits.TRISE8 = 1 ;  //input
    
    
    CNCONAbits.EDGEDETECT = 1 ; //CNSTATx is used to notify the change
    CNCONEbits.EDGEDETECT = 1 ; //CNSTATx is used to notify the change
    CNSTATFbits.CNSTATF12 = 1 ;
    //CNFFbits.CNFF12 = 1 ;
    
    
    
    //CNPUAbits.CNPUA0 = 0 ; // pullup on
    CNCONAbits.ON = 1 ;  //
    CNENAbits.CNIEA0 = 1 ; // +ve edge detection
    
    CNCONEbits.ON = 1 ;  //
    CNENEbits.CNIEE8 = 1 ; // +ve edge detection
    
    CNNEAbits.CNNEA0 = 1 ;  // Negative edge
    CNNEEbits.CNNEE8 = 1 ;  // Negative edge
    
    IFS1bits.CNAIF = 0 ; //reset int flag
    IPC11bits.CNAIP = 4 ; // set it priority
    IPC11bits.CNAIS = 0;  // set it sub priority
    IEC1bits.CNAIE = 0 ; // enable int from port F
    IEC1bits.CNAIE = 1 ;
    
    IFS1bits.CNEIF = 0 ; //reset int flag
    IPC12bits.CNEIP = 4 ; // set it priority
    IPC12bits.CNEIS = 1;  // set it sub priority
    IEC1bits.CNEIE = 0 ; // enable int from port F
    IEC1bits.CNEIE = 1 ;
    
    INTCONSET = _INTCON_MVEC_MASK; // multi vectored mask
    //LATAbits.LATA0 = 1 ;
    
    __builtin_enable_interrupts();
   
}


void __ISR((_CHANGE_NOTICE_A_VECTOR ), ipl4auto) Achangehandler(void)
{
    cnt++ ;
    CNFAbits.CNFA0 = 0 ;  // clear status register
    IFS1bits.CNAIF = 0 ;     // clear int flag
     

    
}

void __ISR((_CHANGE_NOTICE_E_VECTOR ), ipl5auto) Bchangehandler(void)
{
    cnt++ ;
    CNFEbits.CNFE8 = 0 ;  // clear status register
    IFS1bits.CNEIF = 0 ;     // clear int flag
    
    
    
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

