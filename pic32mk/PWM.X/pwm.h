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
    
 uint32_t cnt ;
 
 uint32_t cnts ;
    
void pwm_init();
void delay_ms(float i);
void dc_run(uint8_t run, uint32_t spd,uint8_t turns) ;
void dc_run_CC(uint8_t run, uint32_t spd,uint8_t turns) ;



#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

