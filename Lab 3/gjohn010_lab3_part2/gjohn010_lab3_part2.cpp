//Lab 3 Exercise 2
//Link to demo: https://youtube.com/shorts/8Yzr1J1LMko 

enum States{INIT, Active, Reset} SM1_state = INIT;
int X_button = 8;
int Y_button = 9;


// Array of Output Pin variables, set to the pins being used
const int b_size = 4;
const int b[b_size] = {2, 3, 4, 5};
int count = 0;

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
            state = Active;
        break;
      case Active: 
         if ((digitalRead(X_button) == HIGH) && (value > 6)) {
          state = Active;
         }
         else if ((digitalRead(Y_button) == LOW) && (value > 6)) {
            state = Active;
         }
         else if (value <= 6) {
          state = Reset;
         }
        break;
      case Reset: 
         if ((digitalRead(X_button) == HIGH) && (value > 6)) {
          state = Active;
         }
         else if ((digitalRead(Y_button) == LOW) && (value > 6)) {
            state = Active;
         }
         if (value <= 6) {
          state = Reset;
         } 
      default:
        break;
    }
    switch(state){ // State Action
      case INIT:
         //State Action
        break;
      case Active:
      
        if(digitalRead(X_button) == true) {
          count = count + 1;
          while(digitalRead(X_button) == true) {}
      }
      if (digitalRead(Y_button) == false) {
          count = count - 1;
          while(digitalRead(Y_button) == false) {}
      }
        
        if (count > 4) {
        count = 0;
      }
      if (count < 0) {
        count = 4;
      }
      for (int i = 0; i < count; i++){
        digitalWrite(b[i], HIGH);
        for (int j = 4; j > (count - 1); j--){ //pin is 0-3, so count is from 1-4 instead of 0-4
            digitalWrite(b[i], LOW);
        }
      }
      
        break;
      
      case Reset:
        for (int i = 0; i < b_size; i++){
          digitalWrite(b[i], LOW);
        }
        count = 0;
        break;
      
      default:
        break;
    }
   
    return state;
}
void loop(){ 
  
    ///Default arduino function
    // We have to cast the return value of the tick function to type States
    SM1_state = (States)SM1_Tick(SM1_state);
    
}
