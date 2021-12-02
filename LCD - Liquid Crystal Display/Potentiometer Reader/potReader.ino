/*
 * -> Dawson Reschke <-
 * 
 * This sketch displays analogRead value onto a Liquid Crystal Display
 * 
 * uses : external libs, analog, & I2C.
 */

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,20,4);
const int POT_PIN = A0; 
const float MAP_READ = 0.00488758553; // value used to map the 0-1023 to 0-5 


void setup() {
  pinMode(POT_PIN,INPUT_PULLUP); 
  lcd.init(); 
  updateLCD(); 
}

void updateLCD(){
  int potValue = analogRead(POT_PIN); // returns value from 0-1023
  lcd.clear(); 
  lcd.backlight();   
  lcd.setCursor(0,0); 
  lcd.print("analog read: ");
  lcd.setCursor(0,1); 
  lcd.print(((float)potValue * MAP_READ)); 
  lcd.print("V"); // this data is not exactly accurate
}

void loop() {
  delay(100); // delay because we clear display in updateLCD. If we left delay out the lcd would always be blank. 
  updateLCD(); 
}
