#ifndef CAN_COMM_H
#define CAN_COMM_H

#include <mcp_can.h>
#include <SPI.h>

// Declare the MCP_CAN object
extern MCP_CAN CAN0;

// Function prototypes
void initCAN();  // Initialize the CAN module
bool sendCANMessage(unsigned long id, byte data[], byte len); // Send a CAN message
short receiveRPM();
#endif // CAN_COMM_H
