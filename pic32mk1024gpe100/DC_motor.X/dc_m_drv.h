/* 
 * File:   dc_m_drv.h
 * Author: Admin
 *
 * Created on September 27, 2019, 6:31 PM
 */

#ifndef DC_M_DRV_H
#define	DC_M_DRV_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdint.h>
    
    
void dc_init() ;
void pwm_init() ;
void delay_ms(int i) ;


#ifdef	__cplusplus
}
#endif

#endif	/* DC_M_DRV_H */

