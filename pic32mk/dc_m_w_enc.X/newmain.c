/* 
 * File:   newmain.c
 * Author: Admin
 *
 * Created on October 3, 2019, 3:36 PM
 */
#include "config.h"
#include <xc.h>
#include "dc_w_fb.h"
#include "pid.h"

volatile int cnt;
void cntr(int i) ;


int main() {
    //enc_init() ;
    
    pid_init();          // initialize the PID instance
    pid_setpoint(192);    // The "goal" the PID controller tries to "reach"
    pid_tune(1, 1, 1);    // Tune the PID, arguments: kP, kI, kD
    pid_limit(0, 300);    // Limit the PID output between 0 and 255, this is important to get rid of integral windup!
    cntr(10000) ;
    uint16_t E_value = 0 ;
    dc_init() ;
    //while(E_value < 1920)
    //{   
        
        uint16_t output ;
        //dc_run(1, 0, 400) ;
        //delay_ms(20) ;
        //dc_run(1, 0, output) ;
        //cntr(96) ;
        //dc_run(0,0,0) ;
//        do{
//            E_value = TMR6 ;
            output = pid_compute(E_value) ;
            dc_run(1, 0, 300) ;
            delay_ms(30) ;
//        }while(TMR6 < setPoint ) ;
        //int i ;
        //for(i=0;i<1000000;i++) ;
        //delay_ms(10) ;

        //cnt = 0 ;
//        dc_run(1, 1, 500) ;
//        cntr(96) ;
//        //while(cnt<=192) ;
//        dc_run(0,0,0) ;
//        delay_ms(1000) ;
//    }
        //delay_ms(10000) ;
    dc_run(0,0,0) ;
    //delay_ms(1000) ;
    
    return 1;
}

void cntr(int i)
{
    ANSELAbits.ANSA0 = 0 ;
    T6CKR = 0000 ; // AO selewcted as encoder input
    TRISAbits.TRISA0 = 1 ; // input
    T6CONbits.TCKPS = 0b000 ; // turn timer off and set prescaller to 1:256
    T6CONbits.TCS = 1 ;
    TMR6 = 0;
    PR6 = i ;//0xFFFF;
    T6CONSET = 0x8000 ; // start timer  
   // while(TMR6 != PR6) ;
   // T6CONCLR = 0x8000 ;  //Stop timer)
}

/*void __ISR(_CHANGE_NOTICE_A_VECTOR, ipl4auto) Achangehandler(void)
{
    //LATGbits.LATG13 = 1 ;  // GREEN
    cnt += 1 ;
//    if (CNSTATAbits.CNSTATA0)
//    {
//        LATGbits.LATG13 = 0 ;  // GREEN        
//    }
//    if (CNFAbits.CNFA0)
//    {
//         LATGbits.LATG13 = 1 ;  // GREEN       
//    }
//    LATGbits.LATG13 = 0 ;  // GREEN
    IFS1bits.CNAIF = 0 ;     // clear int flag
    CNFAbits.CNFA0 = 0 ;  // clear interrupt
}*/

