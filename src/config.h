#ifndef CONFIG_H
#define CONFIG_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

// LCD configuration
#define lcdColumn 20
#define lcdRow 4
#define lcdAddress 0x27

// Declare the LCD object for global access
extern LiquidCrystal_I2C lcd;

// Encoder pin definitions
#define encoderPA 35
#define encoderPB 32
#define encoderIA 25
#define encoderIB 33
#define encoderDA 27
#define encoderDB 26
#define encoderSetpointA 39
#define encoderSetpointB 34


#define canCsPin 5
#define canInt 15


// Declare global variables
extern volatile int P_count, I_count, D_count, setpoint_count;
extern volatile int P_lastState, I_lastState, D_lastState, setpoint_lastState;
extern short currentSpeed;

extern float pVal, iVal, dVal, setpointVal;
extern bool showText;

#endif 
