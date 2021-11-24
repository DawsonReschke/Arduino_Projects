/*
 * -> Dawson Reschke <-
 * 
 * Cyclone Linear Replica
 */

const int OUTPUTPINS[] = {13,12,11,10,9,8,7,6,5,4,3};
const int len = sizeof(OUTPUTPINS) / sizeof(OUTPUTPINS[0]); // in C++ there is not .length for arrays. so we must use this sizeof tech
const int BUTTONPIN = 2;
const int POTPIN = A0;

volatile boolean BUTTON_PRESSED = false; 

int NEXT_LED_FRAMECOUNT; 
int CURRENT_LED_INDEX;
int FRAMECOUNT;

void setup() {
  NEXT_LED_FRAMECOUNT = -1; 
  CURRENT_LED_INDEX = 0; 
  FRAMECOUNT = 0; 
  for(int i = 0; i < len; i++){
    pinMode(OUTPUTPINS[i],OUTPUT);
  }
  pinMode(BUTTONPIN,INPUT_PULLUP);
  pinMode(POTPIN,INPUT); 
}

void loop() {
  if(BUTTON_PRESSED){
    evaluate(); 
  }
  updateNextFramecount(); 
  if(FRAMECOUNT < NEXT_LED_FRAMECOUNT){
    FRAMECOUNT++; 
  }else{
    FRAMECOUNT = 0; 
    nextLED(); 
  }
}

void updateNextFramecount(){
  int x = analogRead(POTPIN); 
  NEXT_LED_FRAMECOUNT = x;  
}

void nextLED(){
  digitalWrite(OUTPUTPINS[CURRENT_LED_INDEX],LOW); 
  CURRENT_LED_INDEX = CURRENT_LED_INDEX < len ? CURRENT_LED_INDEX + 1 : 0;
  digitalWrite(OUTPUTPINS[CURRENT_LED_INDEX],HIGH); 
}

void evaluate(){
  bool hasWon = CURRENT_LED_INDEX == (len/2);
  // if the game is won blink LEDS individuly
  if(hasWon){
    for(int i = 0; i < 1; i++){
      for(int j = 0; j < len; j++){
        digitalWrite(OUTPUTPINS[j],HIGH); 
        delay(250); 
        digitalWrite(OUTPUTPINS[j],LOW); 
      }
    }
  }else{
     // else blink the leds once then restart
     for(int i = 0; i < len ; i++){
        digitalWrite(OUTPUTPINS[i],HIGH); 
     }
     delay(500); 
     for(int i = 0; i < len; i++){
        digitalWrite(OUTPUTPINS[i],LOW); 
     }
  }
 
}


void interruptHandler(){ // after the button is pressed the program should recognize a win or a loss.
  BUTTON_PRESSED = true; 
}
