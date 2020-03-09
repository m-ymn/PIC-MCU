/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes

void delay_np(uint32_t i) ;
// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main ( void )
{   ANSELG  = 0 ;
    TRISGbits.TRISG12 = 0 ;
    TRISGbits.TRISG13 = 0 ;
    /* Initialize all modules */
    SYS_Initialize ( NULL );  // eeprom init
    uint32_t addr = 2020 ;
    
    EEPROM_WordWrite(addr+=3 , 0xFFFFDEAD) ;
//    delay_np(9999) ;
//    delay_np(9999) ;
   
    EEPROM_WordWrite(addr+=3 , 0xFFCDDEAD) ;
    //delay_np(9999) ;
    //delay_np(9999) ;
    uint8_t arr[100] ;
  // EEPROM_WordWrite(addr++ , 0xABDCDEED) ;
   // delay_np(9999) ;delay_np(9999) ;
  //  EECONbits.ON = 0 ;
    uint32_t j = 0 ; 
    int i, k = 0;
    for(i=2020 ; i<2026;i++)
    {
        EEPROM_WordRead(i,&j);
        //delay_np(9999);
        
        arr[k] = ((j>>24) & 0xFF); //extract fourth byte MSB
        k++ ;
        arr[k] = ((j>>16) & 0xFF); //extract third byte
        k++ ;
        arr[k] = ((j>>8) & 0xFF); //extract second byte
        k++ ;
        arr[k] = (j & 0xFF); //extract first byte LSB
        k++ ;
        if (j == 0xFFCDDEAD)   
        {
            LATGbits.LATG12 = 1 ;
        }
        if (j == 0xFFFFDEAD)
        {
            LATGbits.LATG13 = 1 ;
        }  
    }  
    return 1 ;
}

void delay_np(uint32_t i)
 { 
    uint32_t j ;
    for(j = 0 ; j<i; j++)
    {
        Nop() ;
        Nop() ;
        Nop() ;
    }
}

/*******************************************************************************
 End of File
*/

