
#include "s1.h"
#include <xc.h>
#include <stdlib.h>
#include "config.h"
#include <string.h>
#include <sys/attribs.h>


uint8_t txMessage[50] ;
uint8_t dta[6] ;
uint8_t fmsg[] = "Connected to microcontroller\n\r" ;


int main ()
{
    Uart_init() ;
    SendString(fmsg) ;
    
    IEC1bits.U3RXIE = 1;
    IPC15bits.U3RXIP = 3 ;     // TX int config
    IPC15bits.U3RXIS = 0 ;
    
   // IEC2bits.U3TXIE = 1 ;
   // IPC16bits.U3TXIP = 4 ;      // RX int config
   // IPC16bits.U3TXIS = 0 ;
    
    IFS1bits.U3RXIF = 0 ;
    IFS2bits.U3TXIF = 0 ;
    
    U3STAbits.URXEN = 1 ;
    INTCONSET = _INTCON_MVEC_MASK; // multi vectored mask
    __builtin_enable_interrupts();
    
    
    
    while(1) ;
    
    return 1;
}



void __ISR(_UART3_RX_VECTOR, ipl3auto) utRx_ithandler(void)
{
    U3STAbits.URXEN = 1 ;
    //uint8_t dta[20] ;
    SendString("Interrupt RX occured\n\r") ;
    //SendString(dta) ;
    ReadString(dta, sizeof(dta));
    
    IFS1bits.U3RXIF = 0 ;
}

void __ISR(_UART3_TX_VECTOR, ipl4auto) utTx_ithandler(void)
{
    //U3STAbits.UTXEN = 1 ;
    SendString("Interrupt TX occured\n\r") ;
    //U3STAbits.URXEN = 0 ;
    IFS2bits.U3TXIF = 0 ;
}

