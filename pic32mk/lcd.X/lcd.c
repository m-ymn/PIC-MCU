#include "lcd.h"


void lcd_init()
{
    ANSELGbits.ANSG6 = 0 ;
    ANSELAbits.ANSA0 = 0 ;
    ANSELAbits.ANSA11 = 0 ;  // digital
    ANSELEbits.ANSE8 = 0 ;
    ANSELEbits.ANSE9 = 0 ;  // digital 
    ANSELBbits.ANSB0 = 0 ;
    
    
    TRISG = rbt(6) ;
    TRISA = rbt(0) ;
    TRISA = rbt(11) ;   // setting pins as op
    TRISE = rbt(8) ;
    TRISE = rbt(9) ;
    TRISB = rbt(0) ;
    delay_ms(15) ;
    
    EN = LOW ;    // pulldown EN & RS pin low
    RS = LOW ;
    write4bits(0x03);
    delay_ms(4); // wait min 4.1ms

    // second try
    write4bits(0x03);
    delay_ms(4); // wait min 4.1ms
    
    // third go!
    write4bits(0x03); 
    //delay_ms(1);
    write4bits(0x02);       // finally, set to 4-bit interface
   
    lcd_cmd(0x28) ; // function set  4bit interface 2 line display 
    lcd_cmd(0x0C) ; // display ON CURSOR OFF BLINKING OFF
                // 0x0E  Cursor ON , blinking OFF   
    lcd_cmd(0x01) ;  // display clear
    delay_ms(5) ;
   
    //lcd_cmd(0x06); // entry mode set
    lcd_set_Cursor(1,3) ;
    lcd_String("**Hello CHIDA!**") ;
    lcd_set_Cursor(2,5) ; //lcd_cmd(0xC0) ;  // set to next line 
    lcd_String("  **  ") ;
    //while(1 );
}

void lcd_set_Cursor(char a, char b)
{
    char temp ;
    if(a == 1)
    {
      temp = 0x80 + b - 1; //80H is used to move the cursor
      lcd_cmd(temp); //Set Row     
    }
    else if(a == 2)
    {
        temp = 0xC0 + b - 1;
        lcd_cmd(temp); //Set  
    }
}

void lcd_String(char *a)
{
    int i;
    for(i=0;a[i]!='\0';i++)
       lcd_write(a[i]);  //Split the string using pointers and call the Char function 
}

void lcd_write(uint8_t value)
{
    RS = HIGH ;
    write4bits(value>>4) ;
    write4bits(value) ;
}

void lcd_cmd(uint8_t value)
{
    RS = LOW ; // RS to lOW
    write4bits(value>>4) ;
    write4bits(value) ;
}

void write4bits(uint8_t value) {
    int i ;
    //for ( i = 0; i < 4; i++) 
    //{
        D4 = (value>>0) & 0x01 ;   //*Dport[i] =  ((value >> i) & 0x01) << Dpin[i] ;
        D5 = (value>>1) & 0x01 ;   // g6 , A0 , a11 ,E8
        D6 = (value>>2) & 0x01  ;
        D7 = (value>>3) & 0x01  ;
    //}

    pulseEnable();
}

void pulseEnable(void) {
  EN = LOW ;
  //delay_ms(1);    
  EN = HIGH ;
  delay_ms(4);    // enable pulse must be >450ns
  EN =  LOW ;
  //delay_ms(10);   // commands need > 37us to settle
}

void delay_ms(int i)
{
    float DLY = (23.4375*i); // SYSclk is 12MHZ PBCLK is sysclk/2 = 6MHZ
                              //Prescalar is 6MHZ / 256 = 23437.5                  
    T1CONbits.TCKPS = 0x3; // turn timer off and set prescaller to 1:256
    TMR1 = 0;
    PR1 = DLY ;//0xFFFF;
    T1CONSET = 0x8000; // start timer        
    //while (TMR1 < DLY) ; //wait 
    //T1CONCLR = 0x8000; // stop timer
    while(TMR1 != PR1) ;
    T1CONCLR = 0x8000 ;  //Stop timer
}