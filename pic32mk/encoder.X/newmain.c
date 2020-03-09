/* 
 * File:   newmain.c
 * Author: Admin
 *
 * Created on October 1, 2019, 3:54 PM
 */
#include "config.h"
#include "inc_enc_drv.h"

int cnt ;

int main() {
    cnt = 0 ;
    enc_init() ;
    
    
    TRISGbits.TRISG12 = 0 ;
    TRISGbits.TRISG13 = 0 ;
//    if (cnt > 96)
//        LATGbits.LATG12 = 1 ; 
    
    while(1){
        if (cnt > 96)
        LATGbits.LATG12 = 1  ;
    }
    return 1 ;
}

//void __ISR(_CHANGE_NOTICE_G_VECTOR, ipl3auto) Gchangehandler(void)
//{
//    LATGbits.LATG12 = 1 ;   // RED
//    
//    if (CNSTATGbits.CNSTATG6)
//    {
//        // *pcnt += 1 ;       // +ve edge detection
//    }
//    if (CNFGbits.CNFG6)
//    {
//           //*pcnt++ ;     // -ve edge detection
//    }
//    //LATGbits.LATG12 = 0 ;
//    IFS1bits.CNGIF = 0 ;     // clear int flag
//}

void __ISR(_CHANGE_NOTICE_A_VECTOR, ipl4auto) Achangehandler(void)
{
    //LATGbits.LATG13 = 1 ;  // GREEN
    cnt += 1 ;
    if (CNSTATAbits.CNSTATA0)
    {
        LATGbits.LATG13 = 0 ;  // GREEN        
    }
    if (CNFAbits.CNFA0)
    {
         LATGbits.LATG13 = 1 ;  // GREEN       
    }
    LATGbits.LATG13 = 0 ;  // GREEN
    IFS1bits.CNAIF = 0 ;     // clear int flag
    CNFAbits.CNFA0 = 0 ;  // clear interrupt
}