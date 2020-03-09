
#include "config_1.h"
#include "pid.h"
#include "s1.h"
//#include "pwm.h"
#include "pwm.h"
#include <sys/attribs.h>
#include <proc/p32mk1024gpe100.h>


//#define MotEnable 6 //Motor Enamble pin Runs on PWM signal
//#define MotFwd  4  // Motor Forward pin
//#define MotRev  7 // Motor Reverse pin
#define ENC_A_RD PORTAbits.RA0
#define ENC_B_RD PORTEbits.RE8

#define ENC_A2_RD PORTBbits.RB0
#define ENC_B2_RD PORTBbits.RB1

//String readString; //This while store the user input data

//int encoderPin1 = 2; //Encoder Output 'A' must connected with intreput pin 
//int encoderPin2 = 3; //Encoder Otput 'B' must connected with intreput pin 

volatile int lastEncoded = 0, lastEncoded2 = 0; // Here updated value of encoder store.
volatile long encoderValue = 0,encoderValue2 = 0; // Raw encoder value
//int PPR = 384;  // Encoder Pulse per revolution.
//int angle = 360; // Maximum degree of motion.
//int REV = 0;          // Set point REQUIRED ENCODER VALUE
//int lastMSB = 0;
//int lastLSB = 0;
double kp = 1, ki = 7, kd = 0.025;             // modify for optimal performance
double input = 0, output = 0, setpoint = 0;

double kp2 = 7, ki2 = 240, kd2 = 0.017;             // modify for optimal performance
double input2 = 0, output2 = 0, setpoint2 = 0;

//long mapPlus1(long x, long in_min, long in_max, long out_min, long out_max) ;
void ISR_config() ;
void pwmOut(int out) ;

void setup()
{
    PID(&input, &output, &setpoint, kp, ki, kd, P_ON_E,1);
   // PID2(&input2, &output2, &setpoint2, kp2, ki2, kd2, DIRECT,1);
    //Uart_init() ;
    pwm_init() ;
    ISR_config() ;
    //SetMode(AUTOMATIC);   //set PID in Auto mode
    //SetSampleTime(1);  // refresh rate of PID controller
    //SetOutputLimits(-60, 60); // 
//    SetMode2(AUTOMATIC);   //set PID in Auto mode
//    SetSampleTime2(1);  // refresh rate of PID controller
//    SetOutputLimits2(-60, 60); // 
}

void main()
{
    uint8_t ch ;
    setup() ;
    char len[5] ;
    char* a[5] ;
    int t ; 
//    SendString("\n\rUART Connected\n\r") ;
//    while(1)
//    {
//        SendString("======Operations=====\n\r") ;
//        SendString("1. Homing\n\r") ;
//        SendString("2. Draw a line\n\r") ;
//        SendString("3. Read current Position\n\r") ;
//        SendString("4. Quit\n\r") ;
//        SendString("Enter your choice: ") ;
//        ReadString(&ch,1);
//        switch(ch)
//        {
//            case '1' : SendString("\n\rHoming...\n\r");
//                homing(0.5,0) ;
//            break ;
//            case '2' : SendString("\n\rEnter line Length in no. of turns\n\r") ;
//            ReadString(&len,sizeof(len)) ;
//            t = atoi(len); 
//            pos_inp(t,220) ;
//            break ;
//            case '3' : 
//            ltoa(&a,encoderValue,10);
//            SendString("\n\r") ;
//            SendString(a) ;
//            break ;
//        }
//    }
    custom(10,150) ;
    
}

void custom(int t, int spd)
{
    char snum[10] ;
    float s1 , s2 ;
    setpoint = encoderValue + (384*t) ;  
    s1 = (384*t*0.10) + encoderValue ;
    s2 = (384*t*0.92) + encoderValue ;
    do{
                        //PID while work to achive this value consider as SET value
        input = encoderValue ;           // data from encoder consider as a Process value
        if (t>0 && input > s1)
            pwmOut(-0.6*spd ) ;
        if ( t> 0 && input < s2)
            pwmOut(-0.3*spd) ;
//       if (t<0 && input < s1)
//            SetOutputLimits(-0.8*spd , 0.8*spd) ;
//        if ( t<0 && input > s2)
//           SetOutputLimits(-0.3*spd, 0.3*spd) ;
        //else
           // SetOutputLimits(-spd,spd) ;
        //while(!Compute()) ;                // calculate new output
        //{ pwmOut(spd); }  
    }while(input <= setpoint) ;
    //encoderValue = 0 ;
     pwmOut(0) ;
}


void pos_inp(int t,int spd)
{ 
    char snum[10] ;
    float s1 , s2 ;
    setpoint = encoderValue + (384*t);   
    s1 = (384*t*0.10) + encoderValue ;
    s2 = (384*t*0.985) + encoderValue ;
   
    //dis = setpoint - encoderValue ;
    do{
                        //PID while work to achive this value consider as SET value
        input = encoderValue ;           // data from encoder consider as a Process value
       // if (t>0 && input < s1)
          //  SetOutputLimits(-0.8*spd , 0.8*spd) ;
        //if ( t> 0 && input > s2)
           //SetOutputLimits(-0.3*spd, 0.3*spd) ;
       //if (t<0 && input > s1)
          //  SetOutputLimits(-0.8*spd , 0.8*spd) ;
        //if ( t<0 && input < s2)
           //SetOutputLimits(-0.3*spd, 0.3*spd) ;
      //  else
            SetOutputLimits(-spd,spd) ;
        while(!Compute()) ;                // calculate new output
        pwmOut(output);  
    }while(input != setpoint) ;
    //encoderValue = 0 ;
     //pwmOut(0) ;
}



long mapPlus1(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min + 1) / (in_max - in_min + 1) + out_min;
}
  
void homing(float power, uint8_t dir){
    int out ;
    volatile long pre_enc ;
    if (dir == 0) out = (power*300) ;
    if(dir == 1) out = -(power*300) ;
    do
    {   pre_enc = encoderValue ;
        pwmOut(out) ;  // left or right
        delay_ms(40) ;
    }while(pre_enc != encoderValue) ;
    pwmOut(0) ;
     encoderValue = 0; // detected limit is now -70 to (if a soft limit is set like rubber motor would always try to push if zer0)
   pos_inp(10,180) ;
}


void __ISR((_CHANGE_NOTICE_A_VECTOR ), ipl4auto) A1changehandler(void)
{

    int MSB = ENC_A_RD ; //MSB = most significant bit
    int LSB = ENC_B_RD ; //LSB = least significant bit
    int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
    int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value
    if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
    if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;
    lastEncoded = encoded; //store this value for next time
    CNFAbits.CNFA0 = 0 ;  // clear status register
    IFS1bits.CNAIF = 0 ;     // clear int flag
}



void __ISR((_CHANGE_NOTICE_E_VECTOR ), ipl4auto) B1changehandler(void)
{
  
    int MSB = ENC_A_RD ; //MSB = most significant bit
    int LSB = ENC_B_RD ; //LSB = least significant bit
    int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
    int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value
    if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
    if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;
    lastEncoded = encoded; //store this value for next time
    CNFEbits.CNFE8 = 0 ;  // clear status register
    IFS1bits.CNEIF = 0 ;     // clear int flag
}