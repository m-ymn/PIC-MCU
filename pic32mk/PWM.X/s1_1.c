



#include "s1_1.h"


void Uart_init()
{
    int i = 0;
    ANSELB = 0 ;
    TRISBbits.TRISB7 = 0;   //op
    TRISBbits.TRISB6 = 1 ;  //in
    PMD5bits.U5MD = 0;      //UART3 Enable
    TRISGbits.TRISG12 = 0 ; // pin12 of port G as output
    TRISGbits.TRISG13 = 0 ;
    SYSKEY = 0x00000000;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    CFGCONbits.IOLOCK = 0 ;
    RPB7R = 0b00001 ; //RPB7R selected as U1TX
    U1RXR = 0b0000 ; // U1RX pin selected on pin RPB6
    SYSKEY = 0x33333333 ;
    
    while(U1MODEbits.ACTIVE);
    
    U1MODEbits.CLKSEL = 01;   // SYS CLK Selected
    U1MODEbits.PDSEL = PDSEL_DATA_8BITS_EVENPARITY;
    U1MODEbits.STSEL = STSEL_STOPBITS_1;
    U1BRG = BRG_VALUE;
    U1MODEbits.UEN = 0b00 ;
    U1TXREG = 0 ;
    U1MODEbits.ON = 1;
    
    //U3STAbits.UTXISEL = 0b11 ;  // tx int sel
    //U5STAbits.URXISEL = 0b01 ;    // rx int sel
    
   
    
    U1STAbits.UTXEN = 1 ;  //TX EN
    U1STAbits.URXEN = 1 ;   // RX EN
//    U5TXREG = 'a' ;
    delay_ms(100) ;
}


void SendString(char *string)
{
      
     
     
                 // Make sure transmitter is enabled
     
   while(*string)
    {
        while(U1STAbits.UTXBF);         // Wait while buffer is full
        U1TXREG = *string;              // Transmit one character
        //delay_ms(1);
        string++;                       // Go to next character in string
    }
   
   //U3STAbits.UTXEN = 0; //TX disabled
}

void ReadString(char *string, int length)
{  
    int count = length;
     
    do
    {
        *string = ReadChar();               // Read in character
        SendChar(*string);                  // Echo character
         
        if(*string == 0x7F && count>length) // Backspace conditional
        {
            length++;
            string--;
            continue;
        }
         
        if(*string == '\r')                 // End reading if enter is pressed
            break;
         
        string++;
        length--;
         
    }while(length>1);
     
    *string = '\0';                         // Add null terminator
}

void SendChar(char c)
{
    U1STAbits.UTXEN = 1;                // Make sure transmitter is enabled
    // while(CTS)                       // Optional CTS use
    while(U1STAbits.UTXBF);             // Wait while buffer is full
    U1TXREG = c;                        // Transmit character
    //U3STAbits.UTXEN = 0 ;
}

char ReadChar(void)
{
    //PORTDbits.RD15 = 0;                // Optional RTS use
    while(!U1STAbits.URXDA);             // Wait for information to be received
    //PORTDbits.RD15 = 1;
    return U1RXREG;                      // Return received character
}

void SendNUM(uint8_t c)
{
    U1STAbits.UTXEN = 1;                // Make sure transmitter is enabled
    // while(CTS)                       // Optional CTS use
    while(U1STAbits.UTXBF);             // Wait while buffer is full
    U1TXREG = c;                        // Transmit character
    //U3STAbits.UTXEN = 0 ;
}
