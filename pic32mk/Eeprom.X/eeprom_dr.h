/* 
 * File:   eeprom_dr.h
 * Author: Admin
 *
 * Created on September 19, 2019, 12:04 PM
 */

#ifndef EEPROM_DR_H
#define	EEPROM_DR_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <xc.h>

#define EEKEY1 0xEDB7
#define EEKEY2 0x1248
    

void EEInitialize(void) ;
int data_EEPROM_read(unsigned int ee_addr, uint32_t *ee_data) ;
int data_EEPROM_write(unsigned int ee_addr, uint32_t ee_data) ;
void delay_ms(int i) ;
    



#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_DR_H */

