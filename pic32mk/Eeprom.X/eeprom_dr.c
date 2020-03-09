
#include <proc/p32mk1024gpe100.h>

#include "eeprom_dr.h"

#define EECMDCFG (0b100)
#define EEBULKERASE (0b011)
#define EEPAGEERASE (0b010)
#define EEWORDPGM (0b001)
#define EEWORDREAD (0b000)

#define EEPROM_NOT_READY 8



void EEInitialize(void) // Basic EEPROM enable and initialization
{ 
    __builtin_disable_interrupts();
    
    CFGCON2bits.EEWS = 0;// 8 = for system clocks < 75MHz 
    
    EECONSET = _EECON_ON_MASK ;

    while (EECONbits.RDY == 0);// Wait until EEPROM is ready (~125 us)

    EECONbits.WREN = 1;// Enable writing to the EEPROM
    EECONbits.CMD = 0b100;// Set the command to Configuration Write

    EEADDR = 0x00;// Addr 0x00 = DEVEE1;
    EEDATA = DEVEE0;
    EEKEY = EEKEY1; // Unlock the EEPROM to enable writing
    EEKEY = EEKEY2;
    EECONSET = _EECON_RW_MASK;
    while (EECONbits.RW); // desired

    EEADDR = 0x04;// Addr 0x04 = DEVEE2;
    EEDATA = DEVEE1;
    EEKEY = EEKEY1; // Unlock the EEPROM to enable writing
    EEKEY = EEKEY2;
    EECONSET = _EECON_RW_MASK;
    while (EECONbits.RW); // desired

    EEADDR = 0x08;// Addr 0x08 = DEVEE3;
    EEDATA = DEVEE2;
    EEKEY = EEKEY1; // Unlock the EEPROM to enable writing
    EEKEY = EEKEY2;
    EECONSET = _EECON_RW_MASK;
    while (EECONbits.RW); // desired

    EEADDR = 0x0C;// Addr 0x08 = DEVEE3;
    EEDATA = DEVEE3;
    EEKEY = EEKEY1; // Unlock the EEPROM to enable writing
    EEKEY = EEKEY2;
    EECONSET = _EECON_RW_MASK;
    while (EECONbits.RW); // desired

    EECONbits.WREN = 0; // Turn off writes.
    
    //__builtin_enable_interrupts();
    
}
int data_EEPROM_read(unsigned int ee_addr, uint32_t *ee_data)
{
    //while (EECONbits.RDY == 0);
    if (EECONbits.RDY == 1) // If Data EEPROM to be ready
    {
        if (EECONbits.RW==0) // If no operation underway
        { // Execute Read Command
            EEADDR = ee_addr & 0xFFC; // Set address on 32-bit boundary
            EECONbits.CMD = EEWORDREAD; // Load CMD<2:0> with
            // Data EEPROM read command
            EECONbits.WREN = 0; // Access for read
            
            EECONSET = _EECON_RW_MASK ;  // Start the operation
            while (EECONbits.RW==1); // Wait until read is complete
            *ee_data = EEDATA; // Read the data
            return EECONbits.ERR;
        }
    }
    return EEPROM_NOT_READY;
}

int data_EEPROM_write(unsigned int ee_addr, uint32_t ee_data)
{
    //while (EECONbits.RDY == 0);
    if (1) // If Data EEPROM to be ready
    {
        if (EECONbits.RW==0) // If no operation underway
        { // Execute Write Command
            EEADDR = ee_addr & 0xFFC; // Load address on a 32-bit boundary
            EECONbits.CMD = EEWORDPGM; // Load CMD<2:0> with write command
            EECONbits.WREN = 1; // Access for write
            EEDATA = ee_data;
            EEKEY = EEKEY1 ; // Write unlock sequence
            EEKEY = EEKEY2 ;
            EECONSET = _EECON_RW_MASK ; // Start the write cycle
            while (EECONbits.RW==1);
            //Wait for write cycle to complete
            // Return ERR<1:0> bits. Zero if no error.
            return EECONbits.ERR;
        }
    }
    return EEPROM_NOT_READY;
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
        T1CONCLR = 0x8000 ;
     
}