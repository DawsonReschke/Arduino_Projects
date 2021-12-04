/*
 * -> Dawson Reschke <- 
 * 
 * This sketch is a simple timer using the built in delay function. 
 * Components required: 
 * rotary encoder,
 * 20x4 LCD,
 * Small Speaker,
 * 
 * 
 * States to keep track of: 
 *  Button State: The button changes the set time from mins - secs, then changes from time set to countdown
 *  Rotary State: the counter variable should control the time set functionality 
 *  Countdown State: once the timer has started the countdown will begin. Once the countdown hits 0:0 alert, then go back to setting time. 
 *  Alarm State: Once the timer has ended the alarm will go off. once the button is pressed again the alarm will be over.
 */

#include <LiquidCrystal_I2C.h>
#include<Wire.h>

LiquidCrystal_I2C lcd(0x27,20,4); 

#define SW 2 // button pin, interrupt pin
#define CLK 4
#define DT 5
#define ALARMPIN 6

// button state managment: 
volatile boolean BUTTONPRESSED = false; // once the button is pressed, the program will react based on the state
volatile unsigned long LASTPRESS = 1500; // must use long here, other wise the software debouncing will eventually fail
volatile int BUTTONSTATE = -1; // 0 : setting minutes, 1 : setting seconds, 2 : timer active
volatile int interruptCounter = 0; 


// rotary state managment: 
boolean lastCLK  = false; // we use the two to determine the direction of the rotary
boolean currentCLK = false; 
int counter = 0; // this var is used for debugging 

// countdown state managment: 
int minutes = 0; // the minute count on the timer.
int seconds = 2; // second count 

// alarm state managment: 
boolean isAlarmActive = false; // true once alarm is active

//LCD Strings
String LCDStrings[] = {"Setting Minutes: ", "Setting Seconds: ", "Time Left: "}; 

void setup(){
  // init Serial
  Serial.begin(9600); 
  //init LCD 
  lcd.init(); 
  lcd.backlight(); 
  
  pinMode(SW, INPUT_PULLUP); // button is active low so we must apply a pull up resistor 
  attachInterrupt(digitalPinToInterrupt(SW),interruptHandler,FALLING); // attach interrupt to the SW pin
  pinMode(CLK,INPUT); 
  pinMode(DT,INPUT); 
  // the first time that you call rotaryUpdate the states of the rotary are unknown, so you get either a positive or negative rotation
  rotaryUpdate(); 
  BUTTONSTATE = 0; 
}

// INTERRUPT HANDLER
void interruptHandler(){ // check to see if the interrupt has happened within the last 500 milliseconds to avoid bouncing in the button
  if(millis() - LASTPRESS > 500){
    interruptCounter ++; 
    BUTTONPRESSED = true; 
    LASTPRESS = millis(); 
  }
}

void ADD(){ // in the ADD & SUB methods, there should be some restraints (no neg)
  if(BUTTONSTATE == 0){
    minutes = minutes < 59 ? minutes + 1 : 0;
  }else{
    seconds = seconds < 59 ? seconds + 1 : 0;  
  }
}

void SUB(){
  if(BUTTONSTATE == 0){
    minutes = minutes > 0 ? minutes - 1 : 59; 
  }else{
    seconds = seconds > 0 ? seconds - 1 : 59; 
  }
}

void lcdUpdate(){ // this method should print the current time (minutes : seconds) to the LCD / in debugMode Serialprint
  String minuteString = minutes < 10 ? "0" + String(minutes) : String(minutes);
  String secondString = seconds < 10 ? "0" + String(seconds) : String(seconds); 
  String settingState = LCDStrings[BUTTONSTATE];
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print(settingState); 
  lcd.setCursor(0,1); 
  lcd.print(minuteString + ":" + secondString); 
//  Serial.println(settingState); 
//  Serial.print(minuteString); 
//  Serial.print(":"); 
//  Serial.println(secondString); 
}

boolean rotaryUpdate(){ // returns true if a change occures 
  boolean changed = false; 
  currentCLK = digitalRead(CLK); 
  // first we check to see if the state of the CLK pin has changed
  // if it has we want to record only once so we check if it is high.
  // it will go HIGH and LOW but we only want to update ONCE.
  if(currentCLK != lastCLK && currentCLK == 1){ 
    changed = true;
    // if DT is LOW and CLK is HIGH the rotary was turned CCW
    // else CW 
    if(digitalRead(DT) != currentCLK){
      SUB(); 
    }else{
      ADD(); 
    }
  }
  lastCLK = currentCLK; 
  return changed; 
}

// this method is called once BUTTONSTATE = 2 , this method should countdown and keep track of alarm state
void updateTimer(){
  seconds--; 
  isAlarmActive = minutes == 0 && seconds == 0; 
  if(seconds == 0){
    seconds = 59; 
    minutes --;
  }
  if(isAlarmActive) alarm(); 
}

void alarm(){ // reset isAlarmActive on button press
  Serial.println("alarm active"); 
  while(!BUTTONPRESSED){
    // do some alarm stuff
    digitalWrite(ALARMPIN,HIGH); 
    delay(500); 
    digitalWrite(ALARMPIN,LOW); 
    delay(500); 
  }
  // after the alarm is done, reset all of the states
  BUTTONPRESSED = false; 
  BUTTONSTATE = 0; 
  minutes = 0; 
  seconds = 30; 
  isAlarmActive = false; 
  delay(500); 
}

void loop(){
//  Serial.println(BUTTONSTATE); 
  if(BUTTONPRESSED){ // here is one location where we need to manage the state of the button
    BUTTONSTATE = BUTTONSTATE < 2 ? BUTTONSTATE + 1 : 0; 
    BUTTONPRESSED = false; 
    Serial.println("an interrupt has occured"); 
  }
  if(BUTTONSTATE == 0){ // setting the minutes 
    // here we want to print to the LCD if the user input changes 
    if(rotaryUpdate()){
      lcdUpdate(); 
    }
  }else if(BUTTONSTATE == 1){ // setting the seconds
    if(rotaryUpdate()){
      lcdUpdate(); 
    }
  }else{ // the timer is active
    delay(1000); 
    lcdUpdate(); 
    updateTimer(); 
  }
}
