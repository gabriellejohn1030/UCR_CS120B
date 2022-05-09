//Lab 1 Exercise 2
//Link to demo: https://youtu.be/LDtYBoH-Ndk 

// Array of Output Pin variables, set to the pins being used
//const int b_size = 4;
//const int b[b_size] = {2, 3, 4, 5};
int count;
bool buttonHeld;
const int PULLDOWN = 8;
const int PULLUP = 9;
const int led1 = 2;
const int led2 = 3;
const int led3 = 4;
const int led4 = 5;



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
  
   pinMode(2, OUTPUT);
   pinMode(3, OUTPUT);
   pinMode(4, OUTPUT);
   pinMode(5, OUTPUT);
  
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
  
  if(count == 0) {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  }
  if (count == 1) {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  }
  if (count == 2) {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  }
  if (count == 3) {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
  }
  if (count == 4) {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
  }
  
  digitalReadHelper();
}