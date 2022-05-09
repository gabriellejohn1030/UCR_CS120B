//Lab 2 Exercise 2
//Link to demo: https://youtube.com/shorts/r2GPIc2qbqg?feature=share  

// Array of Output Pin variables, set to the pins being used
//const int b_size = 4;
//const int b[b_size] = {2, 3, 4, 5};
int count;
bool buttonHeld;
const int PULLDOWN = 8;
const int PULLUP = 9;
const int LEDpins[4] = {2,3,4,5};



int digitalReadHelper() {
    int xButton = digitalRead(PULLDOWN);
    int yButton = digitalRead(PULLUP);
  
    if(xButton == true) {
        count = count + 1;
      while(digitalRead(PULLDOWN) == true) {}
    }
    if (yButton == false) {
        count = count - 1;
      while(digitalRead(PULLUP) == false) {}
    }
 
}
void setup() {
  
  for (int i = 0; i < 4; i++) {
    pinMode(LEDpins[i], OUTPUT);
  }
        
  
   pinMode(PULLDOWN, INPUT); //pulldown
   pinMode(PULLUP, INPUT_PULLUP); //pullup
   Serial.begin(9600); //always need this
   
}

void loop() {
  
  if (count > 4) {
    count = 0;
  }
  if (count < 0) {
    count = 4;
  }
  
  for (int i = 0; i < count; i++){
    digitalWrite(LEDpins[i], HIGH);
    for (int j = 4; j > (count - 1); j--){ //pin is 0-3, so count is from 1-4 instead of 0-4
      digitalWrite(LEDpins[i], LOW);
    }
  }
 
  
  digitalReadHelper();
}
