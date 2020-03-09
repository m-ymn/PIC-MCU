
#include "keypad.h"

char key[4][4] = {{'1','2','3','A'},
               {'4','5','6','B'},
               {'7','8','9','C'},
               {'*','0','#','D'}};


const uint32_t** Rport[] = { (uint32_t)&PG,(uint32_t)&PA,(uint32_t)&PA,(uint32_t)&PE } ;
//char **Cport[] = {&PC,&PB,&PB,&PB} ;
uint8_t Rpin[] = {6,0,11,8} ;
//int Cpin[] = {2,9,6,7} ;

void key_init()
{
    ANSELAbits.ANSA0 = 0 ;
    ANSELAbits.ANSA11 = 0 ;  // digital
    ANSELEbits.ANSE8 = 0 ;
    ANSELGbits.ANSG6 = 0 ;
    
    TRISGbits.TRISG6 = 0 ;
    TRISAbits.TRISA0 = 0 ;    // OUTPUT ROW
    TRISAbits.TRISA11 = 0 ;
    TRISEbits.TRISE8 = 0 ;
    
    ANSELEbits.ANSE9 = 0 ;  // digital 
    ANSELBbits.ANSB0 = 0 ;
    ANSELFbits.ANSF9 = 0 ;
    ANSELFbits.ANSF10 = 0 ;
    
    CNPDEbits.CNPDE9 = 1 ;
    CNPDBbits.CNPDB0 = 1 ;    //pull Down registers 
    CNPDFbits.CNPDF9 = 1 ;
    CNPDFbits.CNPDF10 = 1 ;
    
    TRISEbits.TRISE9 = 1 ;
    TRISBbits.TRISB0 = 1 ;    // INput column
    TRISFbits.TRISF9 = 1 ;
    TRISFbits.TRISF10 = 1 ;
    PA = 0 ;
    PB = 0 ;
    PC = 0 ;
    PE = 0 ;
    PG = 0 ;
}


char get_char()
{
    uint8_t i ;
    char c ;
    do{
        for(i=0;i<4;i++)
        {
            *Rport[i] = sbt(Rpin[i]) ;
            if(C_0 == HIGH)
            {   c = key[i][0] ;
                *Rport[i] = rbt(Rpin[i]) ;
                break ;}
            if(C_1 == HIGH)
            {   c = key[i][1] ;
                *Rport[i] = rbt(Rpin[i]) ;
                break ;}
            if(C_2 == HIGH)
            { c = key[i][2] ;
                *Rport[i] = rbt(Rpin[i]) ;
                break ;}
            if(C_3 == HIGH){
                c = key[i][3] ;
                *Rport[i] = rbt(Rpin[i]) ;
                break ;}
            *Rport[i] = rbt(Rpin[i]) ;
            c = NULL ;
        }
    }while(c == NULL) ;
    
    return c ;
}

void ReadKString(char *string, int length)
{  
    int count = length;
    do
    {
        *string = get_char();               // Read in character
        SendChar('*');                  // Echo character
         
        if(*string == 'B' && count>length) // Backspace conditional
        {
            length++;
            string--;
            continue;
        }
         
        if(*string == '#')                 // End reading if enter is pressed
            break;
         
        string++;
        length--;
        delay_ms(300) ;
         
   // }
    }while(length>1);
    *string = '\0';                         // Add null terminator
}



