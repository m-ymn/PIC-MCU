

#include "pid_1.h"



void PID2(double* Input, double* Output, double* Setpoint,
        double Kp, double Ki, double Kd, int POn, int ControllerDirection)
{
    myOutput = Output;
    myInput = Input;
    mySetpoint = Setpoint;
    inAuto = FALSE;

    SetOutputLimits2(0, 130);				//default output limit corresponds to
												//the arduino pwm limits

    SampleTime2 = 1;							//default Controller Sample Time is 0.1 seconds

    SetControllerDirection2(ControllerDirection);
    SetTunings2(Kp, Ki, Kd, POn);

    lastTime2 = millis2()-SampleTime2;
}

/* Compute() **********************************************************************
 *     This, as they say, is where the magic happens.  this function should be called
 *   every time "void loop()" executes.  the function will decide for itself whether a new
 *   pid Output needs to be computed.  returns true when the output is computed,
 *   false when nothing has been done.
 **********************************************************************************/
BOOL Compute2()
{
   if(!inAuto) return FALSE;
   unsigned long now = millis2();
   unsigned long timeChange = (now - lastTime2);
   if(timeChange>=SampleTime2)
   {
      /*Compute all the working error variables*/
      double input = *myInput;
      double error = *mySetpoint - input;
      double dInput = (input - lastInput2);
      outputSum2+= (ki * error);

      /*Add Proportional on Measurement, if P_ON_M is specified*/
      if(!pOnE) outputSum2-= kp * dInput;

      if(outputSum2 > outMax2) outputSum2= outMax2;
      else if(outputSum2 < outMin2) outputSum2= outMin2;

      /*Add Proportional on Error, if P_ON_E is specified*/
	   double output;
      if(pOnE) output = kp * error;
      else output = 0;

      /*Compute Rest of PID Output*/
      output += outputSum2 - kd * dInput;

	    if(output > outMax2) output = outMax2;
      else if(output < outMin2) output = outMin2;
	    *myOutput = output;

      /*Remember some variables for next time*/
      lastInput2 = input;
      lastTime2 = now;
	    return TRUE;
   }
   else return FALSE;
}

/* SetTunings(...)*************************************************************
 * This function allows the controller's dynamic performance to be adjusted.
 * it's called automatically from the constructor, but tunings can also
 * be adjusted on the fly during normal operation
 ******************************************************************************/
void SetTunings2(double Kp, double Ki, double Kd, int POn)
{
   if (Kp<0 || Ki<0 || Kd<0) return;

   pOn = POn;
   pOnE = POn == P_ON_E;

   dispKp = Kp; dispKi = Ki; dispKd = Kd;

   double SampleTimeInSec = ((double)SampleTime2)/1000;
   kp = Kp;
   ki = Ki * SampleTimeInSec;
   kd = Kd / SampleTimeInSec;

  if(controllerDirection ==REVERSE)
   {
      kp = (0 - kp);
      ki = (0 - ki);
      kd = (0 - kd);
   }
}

/* SetSampleTime(...) *********************************************************
 * sets the period, in Milliseconds, at which the calculation is performed
 ******************************************************************************/
void SetSampleTime2(int NewSampleTime)
{
   if (NewSampleTime > 0)
   {
      double ratio  = (double)NewSampleTime
                      / (double)SampleTime2;
      ki *= ratio;
      kd /= ratio;
      SampleTime2 = (unsigned long)NewSampleTime;
   }
}

/* SetOutputLimits(...)****************************************************
 *     This function will be used far more often than SetInputLimits.  while
 *  the input to the controller will generally be in the 0-1023 range (which is
 *  the default already,)  the output will be a little different.  maybe they'll
 *  be doing a time window and will need 0-8000 or something.  or maybe they'll
 *  want to clamp it from 0-125.  who knows.  at any rate, that can all be done
 *  here.
 **************************************************************************/
void SetOutputLimits2(double Min, double Max)
{
   if(Min >= Max) return;
   outMin2 = Min;
   outMax2 = Max;

   if(inAuto)
   {
	   if(*myOutput > outMax2) *myOutput = outMax2;
	   else if(*myOutput < outMin2) *myOutput = outMin2;

	   if(outputSum2 > outMax2) outputSum2= outMax2;
	   else if(outputSum2 < outMin2) outputSum2= outMin2;
   }
}

/* SetMode(...)****************************************************************
 * Allows the controller Mode to be set to manual (0) or Automatic (non-zero)
 * when the transition from manual to auto occurs, the controller is
 * automatically initialized
 ******************************************************************************/
void SetMode2(int Mode)
{
    BOOL newAuto = (Mode == AUTOMATIC);
    if(newAuto && !inAuto)
    {  /*we just went from manual to auto*/
        Initialize2();
    }
    inAuto = newAuto;
}

/* Initialize()****************************************************************
 *	does all the things that need to happen to ensure a bumpless transfer
 *  from manual to automatic mode.
 ******************************************************************************/
void Initialize2()
{
   outputSum2 = *myOutput;
   lastInput2 = *myInput;
   if(outputSum2 > outMax2) outputSum2 = outMax2;
   else if(outputSum2 < outMin2) outputSum2 = outMin2;
}

/* SetControllerDirection(...)*************************************************
 * The PID will either be connected to a DIRECT acting process (+Output leads
 * to +Input) or a REVERSE acting process(+Output leads to -Input.)  we need to
 * know which one, because otherwise we may increase the output when we should
 * be decreasing.  This is called from the constructor.
 ******************************************************************************/
void SetControllerDirection2(int Direction)
{
   if(inAuto && Direction !=controllerDirection)
   {
	    kp = (0 - kp);
      ki = (0 - ki);
      kd = (0 - kd);
   }
   controllerDirection = Direction;
}

/* Status Funcions*************************************************************
 * Just because you set the Kp=-1 doesn't mean it actually happened.  these
 * functions query the internal state of the PID.  they're here for display
 * purposes.  this are the functions the PID Front-end uses for example
 ******************************************************************************/
//double GetKp(){ return  dispKp; }
//double GetKi(){ return  dispKi;}
//double GetKd(){ return  dispKd;}
//int GetMode(){ return  inAuto ? AUTOMATIC : MANUAL;}
//int GetDirection(){ return controllerDirection;}


unsigned long millis2()
{
    return (_CP0_GET_COUNT()/12000) ;   
}