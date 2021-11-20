/*
 * -> Dawson Reschke <-
 * 
 * This simple arduino sketch creates a pulsing LED 
 * When the button is pressed, the LED blinks at twice the speed
 */
 const int LEDPIN = 7; 
 const int BUTTONPIN = 8; 
void setup() {
  // initializing the pins
  pinMode(LEDPIN,OUTPUT);
  pinMode(BUTTONPIN,INPUT_PULLUP); // PULLUP == Pull up resistor 
}

void loop() {
  if(digitalRead(BUTTONPIN) == LOW){
    blink_LED(250); // when the button is pressed delay 250ms
  }else{
    blink_LED(500); // if the button is not pressed blink 500ms
  }
}

void blink_LED(int blink_time){//blink_time : delay time in millis
  digitalWrite(LEDPIN,HIGH); 
  delay(blink_time); 
  digitalWrite(LEDPIN,LOW); 
  delay(blink_time); 
}
