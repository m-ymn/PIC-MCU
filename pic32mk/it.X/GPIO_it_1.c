/* 
 * File:   newmain.c
 * Author: Admin
 *
 * Created on August 29, 2019, 3:21 PM
 */

// SYSCLK 24MHZ

#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <sys/attribs.h> 


#define sbt(b) (1UL << (b))
#define rbt(b)  (0UL << (b))



int cnt ;



int main() {
    
//    ANSELAbits.ANSA0 = 0 ;
//    TRISAbits.TRISA0 = 0 ;
    cnt = 0 ;
    ANSELAbits.ANSA0 = 0 ; // digital 
    TRISGbits.TRISG12 = 0 ;  // output
    TRISGbits.TRISG13 = 0 ; 
    TRISAbits.TRISA0 = 1 ;  //input
    
    CNCONAbits.EDGEDETECT = 1 ; //CNSTATx is used to notify the change
   // CNSTATFbits.CNSTATF12 = 1 ;
    //CNFFbits.CNFF12 = 1 ;
    
    CNNEAbits.CNNEA0 = 0 ;  // Negative edge
    CNENAbits.CNIEA0 = 1 ; // +ve edge detection
    //CNPUAbits.CNPUA0 = 1 ; // pullup on
    CNCONAbits.ON = 1 ;  //
    IFS1bits.CNAIF = 0 ; //reset int flag
    IPC11bits.CNAIP = 3 ; // set it priority
    IPC11bits.CNAIS = 0;  // set it sub priority
    IEC1bits.CNAIE = 0 ; // enable int from port F
    IEC1bits.CNAIE = 1 ;
    
    INTCONSET = _INTCON_MVEC_MASK; // multi vectored mask
    //LATAbits.LATA0 = 1 ;
    
    __builtin_enable_interrupts();
    
    
    
    while(1) {
        if (cnt >192) {
            LATG = sbt(12) ;
            
        }
    }

    return 1;
}

void __ISR((_CHANGE_NOTICE_A_VECTOR ), ipl3auto) changehandler(void)
{
    //int i ;
    
    //PORTG ^= sbt(12) ;
    //PORTG ^= sbt(13) ;
    //LATA ^= sbt(0) ;
    cnt++ ; 
    //for(i=0;i<100000;i++) ;
    //*port[0] = rbt(12) ;      // ?n? = Vector Number, see data sheet
    IFS1bits.CNAIF = 0 ;     // clear int flag
    CNFAbits.CNFA0 = 0 ;  // clear status register
}
/*void shift(int pos,int bit,int num)
{
    switch(num)
    {
        case 1: PORTA=bit<<pos;
        break;
        case 2: PORTB=bit<<pos;
        break;
        case 3: PORTC=bit<<pos;
        break;
        case 4: PORTE=bit<<pos;
        break;
        case 5: PORTG=bit<<pos;
        break;
        
    }
}*/
