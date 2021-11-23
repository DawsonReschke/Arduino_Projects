/*
 * -> Dawson Reschke <-
 * 
 * Simple arduino sketch using an LED and a potentiometer. The pot is used to control the rate at which the LED flashes.  
 */

const int POT_PIN = A0; 
const int LED_PIN = 7; 

void setup() {
 pinMode(POT_PIN,INPUT_PULLUP); 
 pinMode(LED_PIN, OUTPUT);  
}

void loop() {
  blinkLED(analogRead(POT_PIN)); // analogRead returns (int) 0 - 1023
}

void blinkLED(int val){
  digitalWrite(LED_PIN,HIGH); 
  delay(val); 
  digitalWrite(LED_PIN,LOW); 
  delay(val); 
}
