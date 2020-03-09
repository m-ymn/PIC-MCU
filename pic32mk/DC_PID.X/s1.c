



#include "s1.h"


void Uart_init()
{
    //int i = 0;
    ANSELB = 0 ;
   // TRISCbits.TRISC6 = 0;   //op
  //  TRISCbits.TRISC7 = 1 ;  //in
   // PMD5bits.U3MD = 0;      //UART3 Enable
    TRISBbits.TRISB7 = 0 ; // pin12 of port G as output
    TRISBbits.TRISB6 = 1 ;
    RPA12R = 0b00010; //RPA12R selected as U4TX
    U4RXR = 0b1101 ; // U4RX pin selected on pin RPd3
    while(U4MODEbits.ACTIVE);
    
    U4MODEbits.CLKSEL = 01;   // SYS CLK Selected
    U4MODEbits.PDSEL = PDSEL_DATA_8BITS_EVENPARITY;
    U4MODEbits.STSEL = STSEL_STOPBITS_1;
    U4BRG = BRG_VALUE;
    U4MODEbits.UEN = 00 ;
    U4MODEbits.ON = 1;
    
    //U3STAbits.UTXISEL = 0b11 ;  // tx int sel
    U4STAbits.URXISEL = 0b01 ;    // rx int sel
    
  // U4TXREG = 'a' ;
    //for(i=0;i<1000;i++) ;
    //U3STAbits.UTXEN = 1 ;  //TX EN
    U4STAbits.URXEN = 1 ;   // RX EN
    
}


void SendString(char *string)
{
     
   //int i = 0;
     
   U4STAbits.UTXEN = 1;                // Make sure transmitter is enabled
     
   while(*string)
    {
        while(U4STAbits.UTXBF);         // Wait while buffer is full
        U4TXREG = *string;              // Transmit one character
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

void SendNUM(uint8_t c)
{
    U4STAbits.UTXEN = 1;                // Make sure transmitter is enabled
    // while(CTS)                       // Optional CTS use
    while(U4STAbits.UTXBF);             // Wait while buffer is full
    U4TXREG = c ;                        // Transmit character
    //U3STAbits.UTXEN = 0 ;
}

void SendChar(char c)
{
    U4STAbits.UTXEN = 1;                // Make sure transmitter is enabled
    // while(CTS)                       // Optional CTS use
    while(U4STAbits.UTXBF);             // Wait while buffer is full
    U4TXREG = c;                        // Transmit character
    //U3STAbits.UTXEN = 0 ;
}

uint8_t ReadNUM(void)
{
    //PORTDbits.RD15 = 0;                // Optional RTS use
    while(!U4STAbits.URXDA);             // Wait for information to be received
    //PORTDbits.RD15 = 1;
    return U4RXREG;                      // Return received character
}

char ReadChar(void)
{
    //PORTDbits.RD15 = 0;                // Optional RTS use
    while(!U4STAbits.URXDA);             // Wait for information to be received
    //PORTDbits.RD15 = 1;
    return U4RXREG;                      // Return received character
}


