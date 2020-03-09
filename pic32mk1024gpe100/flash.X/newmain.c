/* 
 * File:   newmain.c
 * Author: Admin
 *
 * Created on September 25, 2019, 3:50 PM
 */

#include "config.h"
#include "flash_drvr.h"
#include "s1.h"
#include <string.h>

int main() {
    TRISGbits.TRISG12 = 0 ;
    uint8_t add[9] ;
    char data[5] = "star" ;
    Uart_init() ;
    
    SendString("Connected to Microcontroller\n\r") ;
    SendString("start address is 0x1d060000\n\r") ;
   
    uint32_t addr = 0x1d060010 ;
    while(strcmp(data,"stop"))
    {
    SendString("Enter data\n\r") ;
    ReadString(&data,5) ;  // reads 5 chars
   
    SendString("E12345\n\r") ;
    uint32_t val = atoi(data) ;  // converts char to int
    
    NVMWriteWord(addr,val ) ; // stores data in hex values
    
    SendString("NVM DONE \n\r") ;
    addr += 4 ;
    }
    
    SendString("flash Write done\n\r") ;
    //NVMWriteWord((addr-4),0xFF) ;
    
    
    

    return 0 ;
}

