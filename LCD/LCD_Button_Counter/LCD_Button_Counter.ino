/*
 * -> Dawson Reschke <-
 * 
 * Using a LCD to display the number of times a button was pressed. 
 * 
 * This sketch includes: Interrupts, External Libraries, & I2C (i^2c) communication
 * 
 * I2C uses two pins : scl(Clock) , sda(Data)
 * The two pins on the arduino are (a4:sda),(a5:scl)
 */


#include <LiquidCrystal_I2C.h> // LCD I2C Library. Documentation can be found here : https://github.com/johnrickman/LiquidCrystal_I2C
#include <Wire.h> // Wire lib for I2C comunication.  

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 20 chars and 4 line display

const int BUTTON_PIN = 2; // interrupt pins for arduio UNO : 2,3
volatile int PRESS_COUNT = 0; // the number of times the button is pressed
volatile bool LCD_CHANGE = false; // toggles on when the button is pressed 

void setup() {
  lcd.init(); // initialize LCD 
  lcd.backlight(); // turn on LCD backlight
  pinMode(BUTTON_PIN,INPUT_PULLUP); 
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN),buttonISR,FALLING); 
  updateLCD(); 
}

void loop() {
  if(LCD_CHANGE){ // if interrupt has occured updateLCD
    updateLCD(); 
    LCD_CHANGE = false; 
  }
}

void updateLCD(){
  lcd.clear(); // clear old data
  lcd.backlight(); // turn on LCD backlight
  lcd.setCursor(0,1); // set the LCD cursor to (0,1) :: WHERE THE LCD WILL WRITE
  lcd.print("Button Pressed: "); // print to LCD
  lcd.print(PRESS_COUNT); 
}

void buttonISR(){
  LCD_CHANGE = true; 
  PRESS_COUNT ++;
}
