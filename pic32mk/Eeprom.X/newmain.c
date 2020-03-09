/* 
 * File:   newmain.c
 * Author: Admin
 *
 * Created on September 19, 2019, 12:51 PM
 */

#include <proc/p32mk1024gpe100.h>
#include <cp0defs.h>
#include <xc.h>
#include "config.h"
#include "eeprom_dr.h"


int main() {
    TRISGbits.TRISG12 = 0 ;
    uint32_t addr = 0 ;
    EEInitialize() ;
     
    data_EEPROM_write(addr++ , 0xFFFF) ;
    delay_ms(100) ;
    data_EEPROM_write(addr++ , 0xFFCD) ;
    delay_ms(100) ;
    data_EEPROM_write(addr++ , 0xABDC) ;
    delay_ms(100) ;
  //  EECONbits.ON = 0 ;
    uint32_t j ; 
    int i ;
    for(i=0 ; i<4097;i++)
    {
        data_EEPROM_read(i,&j);
        delay_ms(10);
        //data_EEPROM_write(0x0, 0) ;

        if ((j == 0xFFFF) ||( j==0xFFCD) || (j==0xABDC ))
        {
            LATGbits.LATG12 = 1 ;
            delay_ms(500) ;
            LATGbits.LATG12 = 0 ;
        }     
        }
    i++ ;
    data_EEPROM_read(i,&j);
    i++ ;
    data_EEPROM_read(i,&j) ;
    }
    
    



