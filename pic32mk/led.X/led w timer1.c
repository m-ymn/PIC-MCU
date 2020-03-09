
#include "config_1.h"
#include <stdlib.h>
#include <sys/attribs.h>
#include <xc.h>



unsigned long millis() ;
unsigned long st_Mil ;  //some global variables available anywhere in the program
unsigned long cnt_Mil ;

int main(){
   // timer_init() ;
    
    st_Mil = millis() ;
    int period = 1000 ;
    
    ANSELA = 0 ; //PIN_14 of PORTA as DIGITAL
    TRISAbits.TRISA0 = 0 ; // PIN_14 of PORTA as OUTPUT
    TRISGbits.TRISG13 = 0 ; //
    TRISGbits.TRISG12 = 0 ; 
    while(1)
    {
        //delay_ms(1000) ;  // 1000ms delay
        cnt_Mil = millis() ;
        if(cnt_Mil - st_Mil >= period)
        {
        //PORTAbits.RA14 = 1 ; // PIN14 of PORTA as DIGITAL 1
        PORTGbits.RG13 ^= 1 ;
        PORTGbits.RG12 ^= 1 ;
        PORTAbits.RA0 ^= 1 ;
        st_Mil = cnt_Mil ;
        }
        //delay_ms(1000) ;   //500ms delay
       // PORTAbits.RA14 = 0 ;  
//        else if(cnt_Mil - st_Mil >= period/2)
//        {
//        PORTGbits.RG13 = 1 ;
//        PORTGbits.RG12 = 0 ;
//        //st_Mil = cnt_Mil ;
//        }
    }
    
    return 0 ;
}


unsigned long millis()
{
    return (_CP0_GET_COUNT()/12000) ;   
}


//volatile unsigned long timer0_millis = 0;
//
//void __ISR(_TIMER_1_VECTOR,  ipl3auto) Timer1Handler(void) ;
//
//Timer1Handler()
//{
//    IFS0bits.T1IF = 0 ; // Clear the timer interrupt status flag
//    unsigned long m = timer0_millis;
//    
//    TMR1 = 0x0;
//    PR1 = (22.4375*1);  // 1milli second
//    T1CONSET = 0x8000; // Start the timer
//    m += 1 ;
//    timer0_millis = m ;  
//}
//
//void timer_init()
//{
//    T1CON = 0x0; // Stop the timer and clear the control register,
//    T1CONbits.TCKPS = 0x3;// prescaler at 1:256,internal clock source
//    TMR1 = 0x0; // Clear the timer register
//    PR1 = (23.4375*1); // Load the period register minus 1 
//    
//    IPC1bits.T1IP = 3 ; // Set priority level = 3
//    IPC1bits.T1IS = 1 ; // Set subpriority level = 1
//    IEC0bits.T1IE = 1 ; // Enable timer interrupts
//    INTCONSET = _INTCON_MVEC_MASK;
//    __builtin_enable_interrupts();
//    T1CONSET = 0x8000; // Start the timer
//    
//}
//
//unsigned long millis()
//{
//	unsigned long m;
//	unsigned int saved_state;
//    saved_state = __builtin_get_isr_state();
//    __builtin_disable_interrupts();
//	// disable interrupts while we read timer0_millis or we might get an
//	// inconsistent value (e.g. in the middle of a write to timer0_millis)
//	
//	m = timer0_millis;
//	__builtin_set_isr_state(saved_state);
//    //__builtin_enable_interrupts();
//	return m;
//}