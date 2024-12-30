#include "config.h"
#include "encoder.h"
#include "lcd_control.h"
#include "can_comm.h"
#include "pid_control.h"

#define pidStepSize 0.001
#define setpointStepSize 500

void setup()
{
    Serial.begin(115200);

    initLCD();
    initCAN();


    pinMode(encoderPA, INPUT_PULLUP);
    pinMode(encoderPB, INPUT_PULLUP);
    pinMode(encoderIA, INPUT_PULLUP);
    pinMode(encoderIB, INPUT_PULLUP);
    pinMode(encoderDA, INPUT_PULLUP);
    pinMode(encoderDB, INPUT_PULLUP);
    pinMode(encoderSetpointA, INPUT_PULLUP);
    pinMode(encoderSetpointB, INPUT_PULLUP);
    pinMode(canInt, INPUT);

    attachInterrupt(digitalPinToInterrupt(encoderPA), handlePEncoder, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoderPB), handlePEncoder, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoderIA), handleIEncoder, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoderIB), handleIEncoder, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoderDA), handleDEncoder, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoderDB), handleDEncoder, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoderSetpointA), handleSetpointEncoder, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoderSetpointB), handleSetpointEncoder, CHANGE);


    delay(1000);
    lcd.clear();
    lcd.setCursor(1, 1);
    lcd.print("Dynamic PID Tuning");
    lcd.setCursor(6, 2);
    lcd.print("Platform");
    delay(2000);
    lcd.clear();
}

void loop()
{
    static unsigned long lastUpdate = 0;
    unsigned long currentMillis = millis();

    
    // Read from the designated kP kI kD encoders and multiply them by pidStepSize to allow smaller steps
    pVal = P_count * pidStepSize;
    iVal = I_count * pidStepSize;
    dVal = D_count * pidStepSize;
    setpointVal = setpoint_count * setpointStepSize;

    short rpm = receiveRPM(); //receive RPM from the encoder of the motor
    currentSpeed = (rpm == 0) ? 0 : rpm; //if RPM is not 0, copy the value to currentSpeed

    float controlOutput = computePID(setpointVal, currentSpeed); //Run the setpoint and current speed through the contrl loop

    short controlSpeed = (short)controlOutput; // Cast to short for CAN message

    //sending higher order byte and lower order byte of the speed to the first motor on the CAN Bus.
    byte data[8] = {controlSpeed >> 8, controlSpeed, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; 
    sendCANMessage(0x200, data, 8); //message ID for the first 4 motors is 0x200 according to the DJI C620 manual



    // sending the data in CSV format for the Python program to read
    Serial.print("Setpoint:");
    Serial.print(setpointVal); 
    Serial.print(",RPM:");
    Serial.print(currentSpeed); 
    Serial.print(",PID:");
    Serial.print(controlOutput);
    Serial.print(",P:");
    Serial.print(pVal);
    Serial.print(",I:");
    Serial.print(iVal); 
    Serial.print(",D:");
    Serial.println(dVal); 

    if (currentMillis - lastUpdate >= 100)
    {
        lastUpdate = currentMillis;
        updateLCD(); // update LCD every 100 milliseconds
    }
}