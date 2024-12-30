#ifndef LCD_CONTROL_H
#define LCD_CONTROL_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
extern LiquidCrystal_I2C lcd;
// Function prototypes
void initLCD();
void updateLCD();


#endif
