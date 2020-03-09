



#include "s1.h"


void Uart_init()
{
    int i = 0;
   // TRISCbits.TRISC6 = 0;   //op
  //  TRISCbits.TRISC7 = 1 ;  //in
   // PMD5bits.U3MD = 0;      //UART3 Enable
    TRISGbits.TRISG12 = 0 ; // pin12 of port G as output
    TRISGbits.TRISG13 = 0 ;
    RPC6R = 0b00001; //RPC6R selected as U3TX
    U3RXR = 0b0101 ; // U3RX pin selected on pin RPC7
    while(U3MODEbits.ACTIVE);
    
    U3MODEbits.CLKSEL = 01;   // SYS CLK Selected
    U3MODEbits.PDSEL = PDSEL_DATA_8BITS_EVENPARITY;
    U3MODEbits.STSEL = STSEL_STOPBITS_1;
    U3BRG = BRG_VALUE;
    U3MODEbits.UEN = 00 ;
    U3MODEbits.ON = 1;
    
    //U3STAbits.UTXISEL = 0b11 ;  // tx int sel
    U3STAbits.URXISEL = 0b01 ;    // rx int sel
    
   //U3TXREG = 'a' ;
    //for(i=0;i<1000;i++) ;
    //U3STAbits.UTXEN = 1 ;  //TX EN
    U3STAbits.URXEN = 1 ;   // RX EN
    
}


void SendString(char *string)
{
     
   //int i = 0;
     
   U3STAbits.UTXEN = 1;                // Make sure transmitter is enabled
     
   while(*string)
    {
        while(U3STAbits.UTXBF);         // Wait while buffer is full
        U3TXREG = *string;              // Transmit one character
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
    U3STAbits.UTXEN = 1;                // Make sure transmitter is enabled
    // while(CTS)                       // Optional CTS use
    while(U3STAbits.UTXBF);             // Wait while buffer is full
    U3TXREG = c;                        // Transmit character
    //U3STAbits.UTXEN = 0 ;
}

void SendChar(char c)
{
    U3STAbits.UTXEN = 1;                // Make sure transmitter is enabled
    // while(CTS)                       // Optional CTS use
    while(U3STAbits.UTXBF);             // Wait while buffer is full
    U3TXREG = c;                        // Transmit character
    //U3STAbits.UTXEN = 0 ;
}

uint8_t ReadNUM(void)
{
    //PORTDbits.RD15 = 0;                // Optional RTS use
    while(!U3STAbits.URXDA);             // Wait for information to be received
    //PORTDbits.RD15 = 1;
    return U3RXREG;                      // Return received character
}

char ReadChar(void)
{
    //PORTDbits.RD15 = 0;                // Optional RTS use
    while(!U3STAbits.URXDA);             // Wait for information to be received
    //PORTDbits.RD15 = 1;
    return U3RXREG;                      // Return received character
}

//void delay_ms(int i)
//{
//     float DLY = (23.4375*i); // SYSclk is 12MHZ PBCLK is sysclk/2 = 6MHZ
//                              //Prescalar is 6MHZ / 256 = 23437.5                  
//     T1CONbits.TCKPS = 0x3; // turn timer off and set prescaller to 1:256
//     TMR1 = 0;
//     PR1 = DLY ;//0xFFFF;
//    T1CONSET = 0x8000; // start timer        
//    //while (TMR1 < DLY) ; //wait 
//    //T1CONCLR = 0x8000; // stop timer
//    while(TMR1 != PR1) ;
//    T1CONCLR = 0x8000 ;  
//}
