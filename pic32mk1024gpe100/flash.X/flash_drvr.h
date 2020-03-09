/* 
 * File:   flash_drvr.h
 * Author: Admin
 *
 * Created on September 25, 2019, 3:50 PM
 */

#ifndef FLASH_DRVR_H
#define	FLASH_DRVR_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>
#include <xc.h>
    
//void fsh_init();
unsigned int NVMUnlock (unsigned int nvmop) ;    
unsigned int NVMWriteWord (void* address, uint32_t data);
void NVM_Qword_write(void* address) ;
unsigned int NVMWriteRow (void* address, unsigned int* rowbuff) ;
void delay_ms(int i) ;


#ifdef	__cplusplus
}
#endif

#endif	/* FLASH_DRVR_H */

