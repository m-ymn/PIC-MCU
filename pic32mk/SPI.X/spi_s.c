
#include <proc/p32mk1024gpe100.h>

#include "spi.h"

#define CS PORTCbits.RC0


void spi_init() {
    
    ANSELA = 0 ;
    ANSELB = 0 ;
    ANSELC = 0 ;
    ANSELG = 0 ;
    TRISCbits.TRISC0 = 1; // i/p as chip select
    TRISAbits.TRISA1 = 1 ;
    
    /*  Peripheral PORT settings  */ // rpb6 = sck 2
    SDI6R = 0b0101 ;  // RG9 as SDI6/MISO
    RPB0R = 0b10001 ; // SDO6/MOSI
    SCK6R = 0b00 ;  // SCK6r as input at RPA1
    
    /* SPIxCON CONFIG   */

    SPI6CONbits.ON = 0;
   // SPI6BRG = 31;        // Baudrate = 1MHZ : FPBCLK2 / 2 (SPI2BRG +1)
    SPI6CONbits.MODE16 = 0;
    SPI6CONbits.MODE32 = 0; // 8 bit mode
    SPI6CONbits.SSEN = 0; // slave select controlled by port fxn
    SPI6CONbits.CKP = 0; // idle state is low level  active state is high level
    SPI6CONbits.CKE = 0; // clock edge select low to high selected
    SPI6CONbits.SMP = 1 ;
   // SPI6CONbits.MCLKSEL = 0; // PBclk2 is used by Baudrate gen
    SPI6CONbits.MSTEN = 0; // master mode enable selected
    SPI6CONbits.ON = 1 ;
    //CS = 1 ;
    
}


char WriteReadSPI(uint8_t c)
{
    while(CS != 0) ;                        // wait while chip select low
    SPI6BUF = c;                    // Write to buffer for transmission
    while (!SPI6STATbits.SPIRBF);   // Wait for transfer to be completed
    CS = 1;                         // Set the chip select back high
    return SPI6BUF;                 // Return the received value
}





void delay_ms(int i)
 {
     float DLY = (23.4375*i); // SYSclk is 12MHZ PBCLK is sysclk/2 = 6MHZ
                              //Prescalar is 6MHZ / 256 = 23437.5                  
     T1CONbits.TCKPS = 0x3; // turn timer off and set prescaller to 1:256
     TMR1 = 0;
     PR1 = DLY ;//0xFFFF;
    T1CONSET = 0x8000; // start timer        
    //while (TMR1 < DLY) ; //wait 
    //T1CONCLR = 0x8000; // stop timer
    while(TMR1 != PR1) ;
    T1CONCLR = 0x8000 ;  
}

