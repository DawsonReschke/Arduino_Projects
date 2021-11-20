/*
 * -> Dawson Reschke <-
 * 
 * Simple arduino sketch where pressing the button toggles the state
 * of the LED using an interrupt. 
 */

const int BUTTON_PIN = 3; //pin on arduino board for the button
const int LED_PIN = 7;
volatile boolean LED_STATE = true; // volatile means stored in external memory, and can be accessed from any scope

void setup() {
  pinMode(BUTTON_PIN,INPUT_PULLUP); 
  pinMode(LED_PIN,OUTPUT); 
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), toggleLED ,FALLING); 
}

void toggleLED(){
  LED_STATE = !LED_STATE; 
}

void loop() {
  digitalWrite(LED_PIN,LED_STATE ? HIGH : LOW); // turns led on || off 
}
