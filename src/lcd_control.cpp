#include "lcd_control.h"
#include "config.h"

LiquidCrystal_I2C lcd(lcdAddress, lcdColumn, lcdRow);

void initLCD()
{
  lcd.init();
  lcd.backlight();
}

void updateLCD()
{
  lcd.setCursor(0, 0);
  lcd.print("P: ");
  lcd.print(pVal, 4);
  lcd.print("      ");
  lcd.setCursor(12, 0);
  lcd.print("Speed: ");
  lcd.setCursor(12, 1);
  lcd.print("    ");
  lcd.setCursor(0, 1);
  lcd.print("I: ");
  lcd.print(iVal, 4);
  lcd.print("      ");
  // Print Speed
  lcd.setCursor(12, 1);
  lcd.print(currentSpeed);
  lcd.print("    ");
  lcd.setCursor(0, 2);
  lcd.print("D: ");
  lcd.print(dVal, 4);
  lcd.print("      ");
  lcd.setCursor(0, 3);
  lcd.print("Setpoint: ");
  lcd.print(setpointVal);
    lcd.print("      ");
}
