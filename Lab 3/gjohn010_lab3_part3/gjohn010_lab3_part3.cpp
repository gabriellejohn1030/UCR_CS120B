//Lab 3 Exercise 3
//Link to demo: https://youtube.com/shorts/iBjXKKExmCg

enum States{INIT, L1, L2} SM1_state = INIT;
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
            state = L1;
        break;
      case L1: 
         if (value > 20) {
          state = L1;
         }
         if (value <= 20) {
            state = L2;
         }
        break;
      case L2: 
         if (value <= 20) {
          state = L2;
         }
         if (value > 20) {
            state = L1;
         } 
      default:
        break;
    }
    switch(state){ // State Action
      case INIT:
         //State Action
        break;
      case L1:
      
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
      
      if (count == 0) {
        for(int i = 0; i < b_size; ++i) {
      digitalWrite(b[i], LOW);
        }
      }
      if (count == 1) {
        for(int i = 0; i < (b_size - 2); ++i) {
          digitalWrite(b[i], HIGH);
        }
        for(int i = 2; i < b_size; ++i) {
          digitalWrite(b[i], LOW);
        }
      }
      if (count == 2) {
        for(int i = 0; i < (b_size - 3); ++i) {
          digitalWrite(b[i], LOW);
        }
        for(int i = 1; i < (b_size - 1); ++i) {
          digitalWrite(b[i], HIGH);
        }
        for(int i = 3; i < b_size; ++i) {
          digitalWrite(b[i], LOW);
        }
      }
      if (count == 3) {
        for(int i = 0; i < (b_size - 2); ++i) {
          digitalWrite(b[i], LOW);
        }
        for (int i = 2; i < b_size; ++i) {
          digitalWrite(b[i], HIGH);
        }
        
      }
      if (count == 4) {
        for(int i = 0; i < (b_size - 3); ++i) {
          digitalWrite(b[i], HIGH);
        }
        for(int i = 1; i < (b_size - 1); ++i) {
          digitalWrite(b[i], LOW);
        }
        for(int i = 3; i < b_size; ++i) {
          digitalWrite(b[i], HIGH);
        }
            
      }
      
      break;
      
      case L2:
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
      
      if (count == 0) {
          for(int i = 0; i < b_size; ++i) {
      digitalWrite(b[i], LOW);
        }
      }
      if (count == 1) {
        digitalWrite(b[0], HIGH);
          digitalWrite(b[1], LOW);
          digitalWrite(b[2], HIGH);
          digitalWrite(b[3], LOW);
      }
      if (count == 2) {
        digitalWrite(b[0], LOW);
          digitalWrite(b[1], HIGH);
          digitalWrite(b[2], LOW);
          digitalWrite(b[3], HIGH);
      }
      if (count == 3) {
        for(int i = 0; i < (b_size - 3); ++i) {
          digitalWrite(b[i], HIGH);
        }
        for(int i = 1; i < (b_size - 1); ++i) {
          digitalWrite(b[i], LOW);
        }
        for(int i = 3; i < b_size; ++i) {
          digitalWrite(b[i], HIGH);
        }
      }
      if (count == 4) {
        for(int i = 0; i < (b_size - 3); ++i) {
          digitalWrite(b[i], LOW);
        }
        for(int i = 1; i < (b_size - 1); ++i) {
          digitalWrite(b[i], HIGH);
        }
        for(int i = 3; i < b_size; ++i) {
          digitalWrite(b[i], LOW);
        }
      }
        //count = 0;
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
