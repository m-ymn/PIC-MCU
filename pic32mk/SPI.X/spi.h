/* 
 * File:   spi.h
 * Author: Admin
 *
 * Created on September 16, 2019, 11:22 AM
 */

#ifndef SPI_H
#define	SPI_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdlib.h>
#include <stdint.h>


    
    
    
void spi_init() ;
void delay_ms(int i) ;
void spi_TxString(uint8_t* str) ;
char WriteReadSPI(uint8_t c) ;

    
    


#ifdef	__cplusplus
}
#endif

#endif	/* SPI_H */

