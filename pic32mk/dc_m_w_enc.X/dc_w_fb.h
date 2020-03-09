/* 
 * File:   dc_w_fb.h
 * Author: Admin
 *
 * Created on October 3, 2019, 3:11 PM
 */

#ifndef DC_W_FB_H
#define	DC_W_FB_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <xc.h>
#include <stdint.h>
 

void dc_init() ;
void enc_init();
void delay_ms(int i);
void dc_run(uint8_t run, uint8_t dir, uint16_t spd);


#ifdef	__cplusplus
}
#endif

#endif	/* DC_W_FB_H */

