#include "can_comm.h"
#include "config.h"

MCP_CAN CAN0(canCsPin);


long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8]; //array for storing received message from 





// Initialize the CAN module
void initCAN() {

    // Initialize MCP2515 at 16MHz, baudrate 500kbps, with default masks and filters
    if (CAN0.begin(MCP_ANY, CAN_1000KBPS, MCP_8MHZ) == CAN_OK) {
        Serial.println("MCP2515 Initialized Successfully!");
    } else {
        Serial.println("Error Initializing MCP2515...");
    }

    // Set CAN to normal mode to enable message transmission
    CAN0.setMode(MCP_NORMAL);
}

// Send a CAN message
bool sendCANMessage(unsigned long id, byte data[], byte len) {
    byte sndStat = CAN0.sendMsgBuf(id, 0, len, data);
    if (sndStat == CAN_OK) {
        //Serial.println("Message Sent Successfully!");
        return true;
    } else {
       // Serial.println("Error Sending Message...");
        return false;
    }
}

short receiveRPM()
{
  if(!digitalRead(canInt))                         // If CAN0_INT pin is low, read receive buffer
  {
    CAN0.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
          short motorSpeedRPM = (rxBuf[2] << 8) | rxBuf[3];
      return motorSpeedRPM;
        
  }
  else {
    currentSpeed = 0;
    return 0;
  }
  }

