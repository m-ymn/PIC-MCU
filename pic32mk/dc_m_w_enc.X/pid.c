

#include "pid.h"



void pid_init()
{
    timer_init() ;
    Kp = 1;
    Ki = 1;
    Kd = 1;
    divisor = 10;
}

double pid_compute(double sensor)
{

  // Calculate time difference since last time executed
  unsigned long now = millis();
  double timeChange = (double)(now - lastTime);

  // Calculate error (P, I and D)
  double error = setPoint - sensor;
  errSum += error * timeChange;
  if (1) {
    errSum = constrain(errSum, minOut * 1.1, maxOut * 1.1); 
  }
  double dErr = (error - lastErr) / timeChange;

  // Calculate the new output by adding all three elements together
  double newOutput = (Kp * error + Ki * errSum + Kd * dErr) / divisor;

  // If limit is specifyed, limit the output
 // if (1) {
    output = constrain(newOutput, minOut, maxOut);
  //} 

  // Update lastErr and lastTime to current values for use in next execution
  lastErr = error;
  lastTime = now;

  // Draw the garph if GRAPH mode
//  if (graph == GRAPH) {
//    printGraph(sensor, verbose);
//  }

  // Return the current output
  return output;
}

double constrain(double in,double min, double max)
{
    if((in >= min) && (in <= max))
        return in ;
    else if(in < min)
        return min ;
    else if(in > max)
        return max ;
    
}
    


void pid_setpoint(double nsp)
{
    setPoint = nsp ;
}

void pid_tune(double _Kp, double _Ki, double _Kd)
{
     if (_Kp < 0 || _Ki < 0 || _Kd < 0) 
         return;
    Kp = _Kp;
    Ki = _Ki;
    Kd = _Kd;
}

void pid_limit(double min, double max)
{
    minOut = min;
    maxOut = max;
}




    
    


