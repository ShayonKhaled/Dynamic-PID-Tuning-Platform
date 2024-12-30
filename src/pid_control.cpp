#include "pid_control.h"
#include "config.h"

// Global variables for PID terms
float previousError = 0.0;
float integral = 0.0;

// Define integral windup limits
const float intMin = -125.0;  // Adjust based on your system
const float intMax = 125.0;

// PID control computation function
float computePID(float setpoint, float currentSpeed)
{
    // Compute the error
    float error = setpoint - currentSpeed;

    // Adjust the integral term only if setpoint is not zero
    if (setpoint == 0)
    {
        integral = 0.0;  // Reset integral for a zero setpoint
    }
    else
    {
        integral += error;

        // Clamp the integral to prevent windup
        if (integral > intMax)
            integral = intMax;
        else if (integral < intMin)
            integral = intMin;
    }

    // Compute derivative term
    float derivative = error - previousError;

    // Update previous error
    previousError = error;

    // PID formula: output = Kp * error + Ki * integral + Kd * derivative
    float output = (pVal * error) + (iVal * integral) + (dVal * derivative);

    return output;
}

// Reset PID terms
void resetPID()
{
    previousError = 0.0;
    integral = 0.0;
}
