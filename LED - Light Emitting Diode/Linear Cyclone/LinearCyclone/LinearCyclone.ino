/*
   -> Dawson Reschke <-

   Cyclone Linear Replica
*/

const int OUTPUTPINS[] = {13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3};
const int len = sizeof(OUTPUTPINS) / sizeof(OUTPUTPINS[0]); // in C++ there is not .length for arrays. so we must use this sizeof tech
const int BUTTONPIN = 2;
const int POTPIN = A1;

volatile boolean BUTTON_PRESSED = false;

int NEXT_LED_FRAMECOUNT = -1;
int CURRENT_LED_INDEX = 0; 
int FRAMECOUNT = 0;

void setup() {
  // assign all required pins as output pins
  for (int i = 0; i < len; i++) {
    pinMode(OUTPUTPINS[i], OUTPUT);
  }
  pinMode(BUTTONPIN, INPUT_PULLUP);
  // asigning the button pin to call interruptHandler on the falling edge. 
  attachInterrupt(digitalPinToInterrupt(BUTTONPIN), interruptHandler, FALLING);
}

void loop() {
  if (BUTTON_PRESSED) {
    evaluate();
    BUTTON_PRESSED = false;
  }
  updateNextFramecount();
  if (FRAMECOUNT < NEXT_LED_FRAMECOUNT) {
    FRAMECOUNT++;
  } else {
    FRAMECOUNT = 0;
    nextLED();
  }
}

// here is where we handle the pot input. NEXT_LED_FRAMECOUNT is the speed controller of the program
void updateNextFramecount() {
  int x = analogRead(POTPIN);
  NEXT_LED_FRAMECOUNT = (int)map(x, 0, 1023, 250, 1000);
}

// write the current led to low and the next led to high
void nextLED() {
  digitalWrite(OUTPUTPINS[CURRENT_LED_INDEX], LOW);
  CURRENT_LED_INDEX = CURRENT_LED_INDEX < len ? CURRENT_LED_INDEX + 1 : 0;
  digitalWrite(OUTPUTPINS[CURRENT_LED_INDEX], HIGH);
}

// writes active to the index pin for the amount of time specified 
void writePin(int index, boolean active, int milliseconds) {
  digitalWrite(OUTPUTPINS[index], active);
  delay(milliseconds);
  digitalWrite(OUTPUTPINS[index], !active);
}

void evaluate() {
  // write all pins to LOW
  for (int i = 0; i < len; i++) {
    digitalWrite(OUTPUTPINS[i], LOW);
  }
  // check if the player has won or lost
  bool hasWon = CURRENT_LED_INDEX == (len / 2);

  // if the game is won blink the red LED 3 times
  if (hasWon) {
    for (int i = 0; i < 3; i++) {
      writePin(len / 2, true, 200);
      delay(200);
    }
    // if the player lost blink the red led 5 times
  } else {
    for (int i = 0; i < 5; i++) {
      writePin(len / 2, true, 200);
      delay(200);
    }
  }
}


void interruptHandler() { // after the button is pressed the program should recognize a win or a loss.
  BUTTON_PRESSED = true;
}
