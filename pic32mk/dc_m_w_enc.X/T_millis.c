

#include "T_millis.h"

void __ISR(_TIMER_1_VECTOR,  ipl3auto ) Timer1Handler(void) ;
volatile unsigned long timer0_millis = 0;

void timer_init()
{
    T1CON = 0x0; // Stop the timer and clear the control register,
    T1CONbits.TCKPS = 0x3;// prescaler at 1:256,internal clock source
    TMR1 = 0x0; // Clear the timer register
    PR1 = (22.4375*1); // Load the period register minus 1 
    
    IPC1bits.T1IP = 3 ; // Set priority level = 3
    IPC1bits.T1IS = 1 ; // Set subpriority level = 1
    IEC0bits.T1IE = 1 ; // Enable timer interrupts
    INTCONSET = _INTCON_MVEC_MASK;
    __builtin_enable_interrupts();
    T1CONSET = 0x8000; // Start the timer
    
}



Timer1Handler(void)
{
    IFS0bits.T1IF = 0 ; // Clear the timer interrupt status flag
    unsigned long m = timer0_millis;
    
    TMR1 = 0x0;
    PR1 = (22.4375*1);  // 1milli second
    T1CONSET = 0x8000; // Start the timer
    m += 1 ;
    timer0_millis = m ;  
}

unsigned long millis()
{
	unsigned long m;
	unsigned int saved_state;
    saved_state = __builtin_get_isr_state();
    __builtin_disable_interrupts();
	// disable interrupts while we read timer0_millis or we might get an
	// inconsistent value (e.g. in the middle of a write to timer0_millis)
	
	m = timer0_millis;
	__builtin_set_isr_state(saved_state);
    //__builtin_enable_interrupts();
	return m;
}