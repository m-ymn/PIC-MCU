/* 
 * File:   pid.h
 * Author: Admin
 *
 * Created on October 8, 2019, 11:08 AM
 */

#ifndef PID_H
#define	PID_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include "T_millis.h"
    
    
double Kp;
double Ki;
double Kd;
double divisor;
double minOut;
double maxOut;
double setPoint;
double output;
double lastErr;
double errSum;

unsigned long lastTime;

void pid_init() ;
double pid_compute(double sensor) ;
double constrain(double in,double min, double max);
void pid_setpoint(double nsp);
void pid_tune(double _Kp, double _Ki, double _Kd);
void pid_limit(double min, double max);

#ifdef	__cplusplus
}
#endif

#endif	/* PID_H */

