// Array of Output Pin variables, set to the pins being used
//const int b_size = 4;
//const int b[b_size] = {2, 3, 4, 5};
int count;
bool buttonHeld;
const char PULLDOWN = 8;
const char PULLUP = 9;


int digitalReadHelper(int button) {
    if(digitalRead(button) == HIGH) {
		return HIGH;
      	
    }
    else if (digitalRead(button) == LOW) {
      	return HIGH
    }
  else {
    	return LOW;
  }
 
}
void setup() {
  
   pinMode(2, OUTPUT);
   pinMode(3, OUTPUT);
   pinMode(4, OUTPUT);
   pinMode(5, OUTPUT);
  
   pinMode(PULLDOWN, INPUT); //pulldown
   pinMode(PULLUP, INPUT_PULLUP); //pullup
   
}

void loop() {
  
  if(digitalReadHelper(PULLDOWN) == HIGH && !buttonHeld) {
		count++;
    	buttonHeld = true;
  }
  if(digitalReadHelper(PULLUP) == LOW && !buttonHeld) {
    	count--;
    	buttonHeld = true;
  }
  if((digitalReadHelper(PULLDOWN) == LOW) && (digitalReadHelper(PULLUP) == LOW)){
     buttonHeld = false;
  }
  
  if (count > 4) {
    count = 0;
  }
  if (count < 4) {
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
    
}