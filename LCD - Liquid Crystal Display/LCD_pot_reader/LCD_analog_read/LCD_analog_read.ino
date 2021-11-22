#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,20,4);
const int POT_PIN = A0; 
const float MAP_READ = 0.00488758553; 


void setup() {
  pinMode(POT_PIN,INPUT_PULLUP); 
  lcd.init(); 
  updateLCD(); 
  Serial.begin(9600); 
}

void updateLCD(){
  int potValue = analogRead(POT_PIN); // returns value from 0-1023
  Serial.println(potValue); 
  lcd.clear(); 
  lcd.backlight();   
  lcd.setCursor(0,0); 
  lcd.print("analog read: ");
  lcd.setCursor(0,1); 
  lcd.print(((float)potValue * MAP_READ)); 
  lcd.print("V"); 
}

void loop() {
  delay(100); 
  updateLCD(); 
}
