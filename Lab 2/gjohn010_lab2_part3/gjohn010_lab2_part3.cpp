//Lab 2 Exercise 3
//Link to demo: https://youtube.com/shorts/zKI96WksCcc 

// Array of Output Pin variables, set to the pins being used
const int b_size = 4;
const int b[b_size] = {2, 3, 4, 5};
bool xButton;
bool yButton;



bool digitalReadHelper() {
    digitalRead(8);
    digitalRead(9);

    if(digitalRead(8) == true) {
        xButton = true;
        yButton = true;
    } 
    if (digitalRead(9) == false) {
        xButton = false;
        yButton = false;
    }
 
}
void setup() {
  
   for (int i = 0; i < b_size; i++){
     pinMode(b[i], OUTPUT);
   }
   pinMode(8, INPUT);
   pinMode(9, INPUT_PULLUP);
   Serial.begin(9600); //always need this
   
}

void loop() {
  
  int value = analogRead(A1);
  //Serial.println(xButton);
  //Serial.println(yButton);
  
  if (xButton == true && yButton == true){
    if (value <= 6){
      for (int i = 0; i < b_size; i++){
        digitalWrite(b[i], LOW);
      }
    } 
    else if (value > 6) {
      for (int i = 0; i < b_size; i++){
        digitalWrite(b[i], HIGH);
      }
    }
  }
  if (xButton == false && yButton == false){
    if (value >= 6 && value <= 200){
      for (int i = 0; i < b_size; i++){
        digitalWrite(b[i], HIGH);
      }
    } 
    if (value > 200 && value <= 550){
      for (int i = 0; i < (b_size - 2); i++){
        digitalWrite(b[i], HIGH);
      }
      for (int i = 2; i < b_size; i++){
        digitalWrite(b[i], LOW);
      }
    } 
    if (value > 550 && value <= 679){
      for (int i = 0; i < b_size; i++){
        digitalWrite(b[i], LOW);
      }
    }
  }
digitalReadHelper();
}
