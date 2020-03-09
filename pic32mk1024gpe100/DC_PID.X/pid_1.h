/* 
 * File:   pid.h
 * Author: Admin
 *
 * Created on November 6, 2019, 5:10 PM
 */

#ifndef PID_1_H
#define	PID_1_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <GenericTypeDefs.h>
#include <xc.h>


  //Constants used in some of the functions below
  #define AUTOMATIC	1
  #define MANUAL	0
  #define DIRECT  0
  #define REVERSE  1
  #define P_ON_M 0
  #define P_ON_E 1

  //commonly used functions **************************************************************************
   void PID2(double*, double*, double*,        // * constructor.  links the PID to the Input, Output, and 
        double, double, double, int, int);//   Setpoint.  Initial tuning parameters are also set here.
                                          //   (overload for specifying proportional mode)

//    PID(double*, double*, double*,        // * constructor.  links the PID to the Input, Output, and 
//        double, double, double, int);     //   Setpoint.  Initial tuning parameters are also set here
	
    void SetMode2(int Mode);               // * sets PID to either Manual (0) or Auto (non-0)

    BOOL Compute2();                       // * performs the PID calculation.  it should be
                                          //   called every time loop() cycles. ON/OFF and
                                          //   calculation frequency can be set using SetMode
                                          //   SetSampleTime respectively

    void SetOutputLimits2(double, double); // * clamps the output to a specific range. 0-255 by default, but
										                      //   it's likely the user will want to change this depending on
										                      //   the application
	


  //available but not commonly used functions ********************************************************
//    void SetTunings(double, double,       // * While most users will set the tunings once in the 
//                    double);         	    //   constructor, this function gives the user the option
                                          //   of changing tunings during runtime for Adaptive control
    void SetTunings2(double, double,       // * overload for specifying proportional mode
                    double, int);         	  

	void SetControllerDirection2(int);	  // * Sets the Direction, or "Action" of the controller. DIRECT
										  //   means the output will increase when error is positive. REVERSE
										  //   means the opposite.  it's very unlikely that this will be needed
										  //   once it is set in the constructor.
    void SetSampleTime2(int);              // * sets the frequency, in Milliseconds, with which 
                                          //   the PID calculation is performed.  default is 100
										  
unsigned long millis2() ;								  
										  
  //Display functions ****************************************************************
//	double GetKp();						  // These functions query the pid for interal values.
//	double GetKi();						  //  they were created mainly for the pid front-end,
//	double GetKd();						  // where it's important to know what is actually 
//	int GetMode();						  //  inside the PID.
//	int GetDirection();					  //


	void Initialize2();
	
	double dispKp;				// * we'll hold on to the tuning parameters in user-entered 
	double dispKi;				//   format for display purposes
	double dispKd;				//
    
	double kp;                  // * (P)roportional Tuning Parameter
    double ki;                  // * (I)ntegral Tuning Parameter
    double kd;                  // * (D)erivative Tuning Parameter

	int controllerDirection;
	int pOn;

    double *myInput;              // * Pointers to the Input, Output, and Setpoint variables
    double *myOutput;             //   This creates a hard link between the variables and the 
    double *mySetpoint;           //   PID, freeing the user from having to constantly tell us
                                  //   what these values are.  with pointers we'll just know.
			  
	unsigned long lastTime2;
	double outputSum2, lastInput2;

	unsigned long SampleTime2;
	double outMin2, outMax2;
	BOOL inAuto, pOnE;

   



#ifdef	__cplusplus
}
#endif

#endif	/* PID_H */

