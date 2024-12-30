#include "config.h"

volatile int P_count = 0, I_count = 0, D_count = 0, setpoint_count = 0;
volatile int P_lastState = 0, I_lastState = 0, D_lastState = 0, setpoint_lastState = 0;
extern short currentSpeed = 0;
float pVal = 0.0, iVal = 0.0, dVal = 0.0, setpointVal = 0.0;
bool showText = false;
