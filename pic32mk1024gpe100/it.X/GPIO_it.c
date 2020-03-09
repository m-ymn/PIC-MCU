/* 
 * File:   newmain.c
 * Author: Admin
 *
 * Created on August 29, 2019, 3:21 PM
 */
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <sys/attribs.h> 


#define sbt(b) (1UL << (b))
#define rbt(b)  (0UL << (b))

#define PG  PORTG
#define PA  PORTA
#define PB  PORTB
#define PC  PORTC

typedef struct p
{
   // char a = PORTGbits.RG12
uint32_t B0:1;
uint32_t B1:1;
uint32_t B2:1;
uint32_t B3:1;
uint32_t B4:1;
uint32_t B5:1;
uint32_t B6:1;
uint32_t B7:1;
uint32_t B8:1;
uint32_t B9:1;
uint32_t B10:1;
uint32_t B11:1;
uint32_t B12:1;
uint32_t B13:1;
uint32_t B14:1;
uint32_t B15:1;
} POR ;

char **port[] = {&PG,&PG} ;


int cnt ;



int main() {
    
    ANSELAbits.ANSA0 = 0 ;
    TRISAbits.TRISA0 = 0 ;

    ANSELFbits.ANSF12 = 0 ; // digital 
    TRISGbits.TRISG12 = 0 ;  // output
    TRISGbits.TRISG13 = 0 ; 
    TRISFbits.TRISF12 = 1 ;  //input
    
    CNCONFbits.EDGEDETECT = 1 ; //CNSTATx is used to notify the change
   // CNSTATFbits.CNSTATF12 = 1 ;
    //CNFFbits.CNFF12 = 1 ;
    
    CNNEFbits.CNNEF12 = 1 ;  // Negative edge
    CNENFbits.CNIEF12 = 1 ; // +ve edge detection
    //CNPUFbits.CNPUF12 = 1 ; // pullup on
    CNCONFbits.ON = 1 ;  //
    IFS1bits.CNFIF = 0 ; //reset int flag
    IPC12bits.CNFIP = 3 ; // set it priority
    IPC12bits.CNFIS = 0;  // set it sub priority
    IEC1bits.CNFIE = 0 ; // enable int from port F
    IEC1bits.CNFIE = 1 ;
    
    INTCONSET = _INTCON_MVEC_MASK; // multi vectored mask
    LATAbits.LATA0 = 1 ;
    
    __builtin_enable_interrupts();
    
    
    
    while(1) {
        if (cnt == 10)
            LATG = sbt(12) ;
                    
    }

    return 1;
}

void __ISR(_CHANGE_NOTICE_F_VECTOR, ipl3auto) changehandler(void)
{
    //int i ;
    
    //PORTG ^= sbt(12) ;
    //PORTG ^= sbt(13) ;
    LATA ^= sbt(0) ;
    cnt++ ; 
    //for(i=0;i<100000;i++) ;
    //*port[0] = rbt(12) ;      // ?n? = Vector Number, see data sheet
    IFS1bits.CNFIF = 0 ;     // clear int flag
    CNFFbits.CNFF12 = 0 ;  // clear interrupt
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
