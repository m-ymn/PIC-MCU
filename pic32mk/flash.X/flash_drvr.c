

#include "flash_drvr.h"

//void fsh_init()
//{
//    //NVMWriteWord(0x1d00F800, 14) ;
//    //NVM_Qword_write(0x1d060008) ;
//    //uint16_t rowbuff[256]; // example is for a 512 word row size. 
//    int x; // loop counter
//    for (x = 0; x < (sizeof(rowbuff) / sizeof (uint16_t)); x++)
//    {
//        rowbuff[x] = x;
//        //rowbuff[x+1] = 'B' ;
//        //x++ ;
//    }
//   // NVMWriteRow (0x1d060000, rowbuff) ;
//    
//}



unsigned int NVMUnlock (unsigned int nvmop)
{
    unsigned int status;
    // Suspend or Disable all Interrupts
    __builtin_disable_interrupts() ;
    // Enable Flash Write/Erase Operations and Select
    // Flash operation to perform
    
    NVMCONbits.NVMOP = nvmop;
    delay_ms(500) ;
    NVMCONbits.WREN = 1 ;
    delay_ms(100) ;
    // Write Keys
    //NVMKEY = 0x0 ;
    NVMKEY = 0xAA996655 ;
    NVMKEY = 0x556699AA ;
    //delay_ms(50) ;
    
    // Start the operation using the Set Register
   // NVMCONbits.WREN = 1 ;
    NVMCONSET = 1<<15 ; // set WR bit
    
    // Wait for operation to complete
    while(NVMCONbits.WR);
    // Disable future Flash Write/Erase operations
    NVMCONbits.WREN = 0;
    // Restore Interrupts
    
    return (NVMCON & 0x3000) ;
}

void NVM_Qword_write(void* address)
{
    NVMADDR = (unsigned int) address ;
    NVMDATA0 = 0x11111111; // value written to 0x1D008000
    NVMDATA1 = 0x22222222; // value written to 0x1D008004
    NVMDATA2 = 0x33333333; // value written to 0x1D008008
    NVMDATA3 = 0x44444444; // value written to 0x1D00800C
    
    NVMUnlock (0x2);  // 0x2 is for Qword
    
}

unsigned int NVMWriteWord (void* address, uint32_t data)
{
    unsigned int res;
    // Load data into NVMDATA register
    NVMDATA0 = data;
    // Load address to program into NVMADDR register
    NVMADDR = (unsigned int) address;
    // Unlock and Write Word
    res = NVMUnlock (0x1);
    // Return Result
    return res;
}

unsigned int NVMWriteRow (void* address,unsigned int* rowbuff)
{
    
    NVMADDR = (uint32_t)address; // row physical address
    // set source address. Must be converted to a physical address.
    NVMSRCADDR = (unsigned int)((int)rowbuff & 0x1FFFFFFF);// define Flash operation
    
    NVMUnlock(0x3);// 0x3 for row programming
    
    while(NVMCONbits.WR);// Disable future Flash Write/Erase operations
    
    NVMCONbits.WREN = 0;// Check Error Status
    //if(NVMCON & 0x3000)// mask for WRERR and LVDERR bits{ // process errors}

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
