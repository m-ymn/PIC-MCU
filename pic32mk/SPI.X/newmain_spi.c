/* 
 * File:   newmain_spi.c
 * Author: Admin
 *
 * Created on September 16, 2019, 11:24 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "spi.h"

   

int main() {
    spi_init() ;
    
    TRISGbits.TRISG12 = 0 ;
    char p = WriteReadSPI('b') ;
    
    if (p == 'b'){
        LATGbits.LATG12 = 1 ;
    }

    return 1;
}

