/* 
 * File:   pwm.h
 * Author: Admin
 *
 * Created on September 10, 2019, 11:45 AM
 */

#ifndef PWM_H
#define	PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdlib.h>
    

    
void pwm_init();
void delay_ms(int i);
void dc_run(uint8_t run, uint32_t spd) ;
void dc_run_CC(uint8_t run, uint32_t spd) ;
void dc_run2(uint8_t run, uint32_t spd) ;
void dc_run_CC2(uint8_t run, uint32_t spd) ;
void ISR_config();
void pwmOut(int out);
void pwmOut2(int out) ;


#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

