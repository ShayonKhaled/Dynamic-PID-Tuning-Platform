#ifndef PID_CONTROL_H
#define PID_CONTROL_H

// Function prototype for computing PID control
float computePID(float setpoint, float currentSpeed);

// Function to reset PID terms (optional, for dynamic reinitialization)
void resetPID();

#endif // PID_CONTROL_H
