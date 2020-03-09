
#include <proc/p32mk1024gpe100.h>

#include "spi.h"

#define CS LATBbits.LATB9


void spi_init() {
    
    TRISBbits.TRISB9 = 0;//TRISBCLR = 0x0200; //SS2 = OUT
    TRISBbits.TRISB7 = 0;//TRISBCLR = 0x0080; //SDO2 = OUT
    TRISBbits.TRISB6 = 0;//RPB6- SCK Output
   
    ANSELA = 0;
    ANSELB = 0;
   
    RPB9R = 0b00100; //SS2
    RPB7R = 0b00100; //SDO2
    SDI2R = 0b1101; //RPA14
   
    TRISAbits.TRISA14 = 1 ; // RA14 as Input  TRISAbits.TRISA14 = 1;//
   
    //set Default values
    LATBbits.LATB9 = 1 ; //SS2 =1
    /* SPIxCON CONFIG   */
    //int rdta ;
    
    
   
    //rdta = SPI2BUF ;
    SPI2STATCLR = 0x40; 
//    SPI2CONbits.MODE16 = 0;
//    SPI2CONbits.MODE32 = 0; // 8 bit mode
//    SPI2CONbits.SSEN = 0; // slave select controlled by port fxn
//    SPI2CONbits.CKP = 0; // idle state is low level  active state is high level
//    SPI2CONbits.CKE = 0; // clock edge select low to high selected
//    SPI2CONbits.SMP = 0 ;
//    SPI2CONbits.MCLKSEL = 0; // PBclk2 is used by Baudrate gen
    SPI2CONbits.MSTEN = 1; // master mode enable selected
    SPI2CONbits.ON = 1 ;
     SPI2BRG = 31 ;        // Baudrate = 1MHZ : FPBCLK2 / 2 (SPI2BRG +1)
    //CS = 1 ;
    
}

void spi_TxString(uint8_t* str)
{
    
}

char WriteReadSPI(uint8_t c)
{
    //while (!SPI2STATbits.SPITBE) ;
    CS = 0 ;                         // Set the chip select low
    SPI2BUF = c ;                    // Write to buffer for transmission
    while (!SPI2STATbits.SPIRBF) ;   // Wait for transfer to be completed
    CS = 1 ;                         // Set the chip select back high
    return SPI2BUF ;                 // Return the received value
}

void spi_TxChar(uint8_t ch)
{
    while(SPI2STATbits.SPITBE);    // Wait while TX buffer is empty
    SPI2BUF = ch ; 
    while(SPI2STATbits.SPITBF) ;//SPI2BUF = 0 ;
    SPI2BUF = 0 ;
}

char spi_Rxchar()
{
    while(!SPI2STATbits.SPIRBF) ; // wait while rx buffer is full
    return SPI2BUF ; 
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

