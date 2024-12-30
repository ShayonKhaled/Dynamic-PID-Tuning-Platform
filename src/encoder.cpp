#include "encoder.h"
#include "config.h"

void IRAM_ATTR handlePEncoder()
{
  // read the state of the encoder pins
  int A = digitalRead(encoderPA);
  int B = digitalRead(encoderPB);
  int currentState = (A << 1) | B;

  // check if the encoder is rotating clockwise
  if ((P_lastState == 0b00 && currentState == 0b01) ||
      (P_lastState == 0b01 && currentState == 0b11) ||
      (P_lastState == 0b11 && currentState == 0b10) ||
      (P_lastState == 0b10 && currentState == 0b00))
  {
    P_count++;
  }
  // check if the encoder is rotating counterclockwise
  else if ((P_lastState == 0b00 && currentState == 0b10) ||
           (P_lastState == 0b10 && currentState == 0b11) ||
           (P_lastState == 0b11 && currentState == 0b01) ||
           (P_lastState == 0b01 && currentState == 0b00))
  {
    P_count--;
  }
  // update the last state
  P_lastState = currentState;
}

void IRAM_ATTR handleIEncoder()
{
  // read the state of the encoder pins
  int A = digitalRead(encoderIA);
  int B = digitalRead(encoderIB);
  int currentState = (A << 1) | B;

  // check if the encoder is rotating clockwise
  if ((I_lastState == 0b00 && currentState == 0b01) ||
      (I_lastState == 0b01 && currentState == 0b11) ||
      (I_lastState == 0b11 && currentState == 0b10) ||
      (I_lastState == 0b10 && currentState == 0b00))
  {
    I_count++;
  }
  // check if the encoder is rotating counterclockwise
  else if ((I_lastState == 0b00 && currentState == 0b10) ||
           (I_lastState == 0b10 && currentState == 0b11) ||
           (I_lastState == 0b11 && currentState == 0b01) ||
           (I_lastState == 0b01 && currentState == 0b00))
  {
    I_count--;
  }
  // update the last state
  I_lastState = currentState;
}

void IRAM_ATTR handleDEncoder()
{
  // read the state of the encoder pins
  int A = digitalRead(encoderDA);
  int B = digitalRead(encoderDB);
  int currentState = (A << 1) | B;

  // check if the encoder is rotating clockwise
  if ((D_lastState == 0b00 && currentState == 0b01) ||
      (D_lastState == 0b01 && currentState == 0b11) ||
      (D_lastState == 0b11 && currentState == 0b10) ||
      (D_lastState == 0b10 && currentState == 0b00))
  {
    D_count++;
  }
  // check if the encoder is rotating counterclockwise
  else if ((D_lastState == 0b00 && currentState == 0b10) ||
           (D_lastState == 0b10 && currentState == 0b11) ||
           (D_lastState == 0b11 && currentState == 0b01) ||
           (D_lastState == 0b01 && currentState == 0b00))
  {
    D_count--;
  }
  // update the last state
  D_lastState = currentState;
}

void IRAM_ATTR handleSetpointEncoder()
{
    // read the state of the encoder pins
    int A = digitalRead(encoderSetpointA);
    int B = digitalRead(encoderSetpointB);
    int currentState = (A << 1) | B;

    // check if the encoder is rotating clockwise
    if ((setpoint_lastState == 0b00 && currentState == 0b01) ||
        (setpoint_lastState == 0b01 && currentState == 0b11) ||
        (setpoint_lastState == 0b11 && currentState == 0b10) ||
        (setpoint_lastState == 0b10 && currentState == 0b00))
    {
        // increment only if below the upper limit
        if (setpoint_count < 9000)
        {
            setpoint_count++;
        }
        else {return;}
    }
    // check if the encoder is rotating counterclockwise
    else if ((setpoint_lastState == 0b00 && currentState == 0b10) ||
             (setpoint_lastState == 0b10 && currentState == 0b11) ||
             (setpoint_lastState == 0b11 && currentState == 0b01) ||
             (setpoint_lastState == 0b01 && currentState == 0b00))
    {
        // decrement only if above the lower limit
        if (setpoint_count > 0)
        {
            setpoint_count--;
        }
        else {return;}
    }

    // update the last state
    setpoint_lastState = currentState;
}
