

#include "inc_enc_drv.h"


void enc_init()
{
    ANSELGbits.ANSG6 = 0 ;  // digital 
    ANSELAbits.ANSA0 = 0 ;
    
    TRISGbits.TRISG6 = 1 ;   
    TRISAbits.TRISA0 = 1 ;   //input
    
    CNCONGbits.EDGEDETECT = 1 ; //CNSTATx is used to notify the change
    CNCONAbits.EDGEDETECT = 1 ;
    
    CNNEGbits.CNNEG6 = 0 ;  // Negative edge
    CNENGbits.CNIEG6 = 1 ; // +ve edge detection
    CNPUGbits.CNPUG6 = 1 ; // pullup on
    
    CNNEAbits.CNNEA0 = 0 ;  // Negative edge
    CNENAbits.CNIEA0 = 1 ; // +ve edge detection
    CNPUAbits.CNPUA0 = 1 ; // pullup on
    
    CNCONGbits.ON = 1 ;   // change notice on 
    CNCONAbits.ON = 1 ;
    
    IFS1bits.CNGIF = 0 ; // reset int flag
    IPC12bits.CNGIP = 3 ; // set it priority
    IPC12bits.CNGIS = 0;  // set it sub priority
    IEC1bits.CNGIE = 0 ;
    IEC1bits.CNGIE = 1 ;  // enable int from port G
    
    IFS1bits.CNAIF = 0 ; // reset int flag
    IPC11bits.CNAIP = 4 ; // set it priority
    IPC11bits.CNAIS = 0;  // set it sub priority     
    IEC1bits.CNAIE = 0 ;
    IEC1bits.CNAIE = 1 ;  // enable int from port A
    
    INTCONSET = _INTCON_MVEC_MASK; // multi vectored mask
    __builtin_enable_interrupts();
    
}


