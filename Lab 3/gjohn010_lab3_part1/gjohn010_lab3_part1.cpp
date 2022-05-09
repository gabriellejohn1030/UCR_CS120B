//Lab 3 Exercise 1
//Link to demo: https://youtube.com/shorts/82W6nXY4zlc 

enum States{INIT, S0, S1} SM1_state = INIT;
int X_button = 8;
int Y_button = 9;

// Array of Output Pin variables, set to the pins being used
const int b_size = 4;
const int b[b_size] = {2, 3, 4, 5};

void setup(){
  //some set up (Default Arduino Function)
    pinMode(X_button, INPUT);
  pinMode(Y_button, INPUT_PULLUP);
    // LEDs
    for(int i = 0; i < b_size; i++)
    {
        pinMode(b[i], OUTPUT);
    }
    Serial.begin(9600);
}

// This function takes in the state as an argument & returns the current state
int SM1_Tick(int state){
    //Read thing
  int value = analogRead(A1);
    switch(state){ // State transitions
      case INIT:
         //State Transition
            state = S0;
        break;
      case S0: //Mode 0
         if (digitalRead(X_button) == LOW && digitalRead(Y_button) == LOW) {
          state = S1;
         }
       else {
          state = S0;
         }
        break;
      case S1: //Mode 1
        if (digitalRead(X_button) == HIGH && digitalRead(Y_button) == HIGH){
            state = S0;
        } 
        else {
          state = S1;
        }
         //State Transition
        break;
    }
    switch(state){ // State Action
      case INIT:
         //State Action
        break;
      case S0:
        if (value <= 6){
          for (int i = 0; i < b_size; i++){
            digitalWrite(b[i], LOW);
        }
          //writeBuffer(0x00);
      }  
      else if (value > 6) {
          for (int i = 0; i < b_size; i++){
            digitalWrite(b[i], HIGH);
          }
         // writeBuffer(0x0F);
        }
        break;
      case S1:
        if (value >= 6 && value <= 200){
          for (int i = 0; i < b_size; i++){
            digitalWrite(b[i], HIGH);
          }
          //writeBuffer(0x0F);
       } 
      if (value > 200 && value <= 550){
          for (int i = 0; i < (b_size - 2); i++){
            digitalWrite(b[i], HIGH);
          }
          for (int i = 2; i < b_size; i++){
            digitalWrite(b[i], LOW);
          }
          //writeBuffer(0x03);
      } 
      if (value > 550 && value <= 679){
          for (int i = 0; i < b_size; i++){
            digitalWrite(b[i], LOW);
          }
          //writeBuffer(0x00);
      }
        break;
    }
    return state;
}
void loop(){ 
  
    ///Default arduino function
    // We have to cast the return value of the tick function to type States
    SM1_state = (States)SM1_Tick(SM1_state);
    
}
