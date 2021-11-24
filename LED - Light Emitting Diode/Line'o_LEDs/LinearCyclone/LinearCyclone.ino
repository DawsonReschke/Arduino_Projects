/*
 * -> Dawson Reschke <-
 * 
 * Cyclone Linear Replica
 */

const int OUTPUTPINS[] = {13,12,11,10,9,8,7,6,5,4,3};
const int BUTTONPIN = 2;
const int POTPIN = A0;

int NEXT_LED_FRAMECOUNT = -1; 
int CURRENT_LED_INDEX = 0; 
int FRAMECOUNT = 0; 

void setup() {
  int len = sizeof(OUTPUTPINS) / sizeof(OUTPUTPINS[0]); 
  for(int i = 0; i < len; i++){
    pinMode(OUTPUTPINS[i],OUTPUT);
  }
  pinMode(BUTTONPIN,INPUT_PULLUP);
  pinMode(POTPIN,INPUT); 
}

void loop() {
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
  int len = sizeof(OUTPUTPINS)/sizeof(OUTPUTPINS[0]); 
  digitalWrite(OUTPUTPINS[CURRENT_LED_INDEX],LOW); 
  CURRENT_LED_INDEX = CURRENT_LED_INDEX < len ? CURRENT_LED_INDEX + 1 : 0;
  digitalWrite(OUTPUTPINS[CURRENT_LED_INDEX],HIGH); 
}
