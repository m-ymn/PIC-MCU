
#include "config.h"
#include <xc.h>

//#define CS LATCbits.LATC0
void SPI2_Dev_Init() ;
void SPI2_PortInit() ;
char SPI2_transfer( char b) ;


void main()
{
    SPI2_PortInit() ;
    
    SPI2_Dev_Init() ;
    
    TRISGbits.TRISG12 = 0 ;
    char p ;
    p = SPI2_transfer('c') ;
    
    if (p == 'c'){
        LATGbits.LATG12 = 1 ;
    }

}

char SPI2_transfer( char b)
{
    while (!SPI2STATbits.SPITBE) ;
    SPI2BUF = b;
   
    while(!SPI2STATbits.SPIRBF);
   
    return SPI2BUF;
}



void SPI2_PortInit() {
   
    TRISBbits.TRISB9 = 0;//TRISBCLR = 0x0200; //SS2 = OUT
    TRISBbits.TRISB7 = 0;//TRISBCLR = 0x0080; //SDO2 = OUT
    TRISBbits.TRISB6 = 0;//RPB6- SCK Output
   
    ANSELA = 0;
    ANSELB = 0;
   
    RPB9R = 0b00100; //SS2
    RPB7R = 0b00100; //SDO2
    SDI2R = 0b1101; //RPA14
   
   TRISASET = 0x4000; // RA14 as Input  TRISAbits.TRISA14 = 1;//
   
    //set Default values
   LATBSET = 0x0200; //SS2 =1
   //LATBbits.LATB9
//    LATBCLR = 0x0080; //SDO2 = 0

}

void SPI2_Dev_Init() {
      int rdata;
//    SPI2BRG = 1;
//    SPI2CON = 0;
//    rdata = SPI2BUF;
//    SPI2STATCLR = 0x0040;
//    SPI2CON = 0x8220;
       
    SPI2CON = 0x0000;
    SPI2BRG = 31;    
    rdata = SPI2BUF;
    SPI2STATCLR = 0x40;  
    SPI2CONbits.MSTEN = 1;
    //SPI2CON |= 0x0400;
    SPI2CONbits.CKE = 1;
    SPI2CONbits.ON = 1;

}
