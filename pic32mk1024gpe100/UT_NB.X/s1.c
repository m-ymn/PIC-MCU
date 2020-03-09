



#include "s1.h"
#include <sys/attribs.h>

void Uart_init()
{
    ANSELD = 0 ;
    ANSELB = 0 ;
    ANSELA = 0 ;
   // TRISCbits.TRISC6 = 0;   //op
  //  TRISCbits.TRISC7 = 1 ;  //in
   // PMD5bits.U3MD = 0;      //UART3 Enable
   // TRISBbits.TRISB7 = 0 ; // pin12 of port G as output
   // TRISBbits.TRISB6 = 1 ;
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
    U4STAbits.URXISEL = 0 ;    // rx int sel has atleast 1 char
    
  
    U4STAbits.UTXEN = 1 ;  //TX EN
    U4STAbits.URXEN = 1 ;   // RX EN
   
}

void uart_int()
{
    IFS2bits.U4RXIF = 0 ;
    IFS2bits.U4TXIF = 0 ;
    IPC16bits.U4RXIP = 4 ;
    IPC16bits.U4RXIS = 1 ;
    IPC16bits.U4TXIP = 4 ;
    IPC16bits.U4TXIS = 1 ;
    
    IEC2bits.U4RXIE = 1 ; 
    IEC2bits.U4TXIE = 1 ;
    
    INTCONbits.MVEC = 1 ;
    __builtin_enable_interrupts() ;
}


void SendString(char *string)
{
     
   //int i = 0;
     
   //U4STAbits.UTXEN = 1;                // Make sure transmitter is enabled
     
   while(*string)
    {
        //while(U4STAbits.UTXBF);         // Wait while buffer is full
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



void SendChar(char c)
{
    U4STAbits.UTXEN = 1;                // Make sure transmitter is enabled
    // while(CTS)                       // Optional CTS use
    while(U4STAbits.UTXBF);             // Wait while buffer is full
    U4TXREG = c;                        // Transmit character
    //U3STAbits.UTXEN = 0 ;
}

char ReadChar(void)
{
    //PORTDbits.RD15 = 0;                // Optional RTS use
    while(!U4STAbits.URXDA);             // Wait for information to be received
    //PORTDbits.RD15 = 1;
    return U4RXREG;                      // Return received character
}
void __ISR(_UART4_RX_VECTOR, ipl4auto) URx_ISR(void) ;
void __ISR(_UART4_TX_VECTOR, ipl4auto) Utx_ISR(void) ;


void URx_cb(uint8_t *data)
{
    //*datbuf = U4RXREG ;
    //while(U4STAbits.UTXBF);
    //U4TXREG = 'r' ;
    U4TXREG = *data ;
    //p_datbuf++ ;
   // if(p_datbuf == (&dat_buf[256]))    // buffer full check
     //   SendString("buffer full\n\r"); // not checked
}

void URx_ISR()
{ 
    //SendString("\n\rRX ISR\n\r") ;
    IFS2bits.U4RXIF = 0 ;
    //while(!U4STAbits.URXDA); 
    isr_cb U_cb = URx_cb ;
    U_cb(&U4RXREG) ;
    
        
}
void Utx_ISR()
{
    //SendString("\n\rTX ISR\n\r") ;
    IFS2bits.U4TXIF = 0 ;
    
}