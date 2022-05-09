//Lab 4 Exercise 1
//Link to demo: https://youtube.com/shorts/4h0_vNqBx4o

enum States{INIT, L1, L2, L3, L4, P1, P2, P3, P4} SM1_state = INIT;
unsigned long period;
unsigned long lastRan;

// Array of Output Pin variables, set to the pins being used
const int b_size = 4;
const int b[b_size] = {2, 3, 4, 5};
const char count[4] = {0x03, 0x06, 0x0C, 0x0F};
const char count2[4] = {0x05, 0x0A, 0x09, 0x06};
// Output Buffer
int b_buf = 0x00;
// Input Variables

// Reset the Output Buffer. 
void resetBuffer() {
    for(int i = 0; i < b_size; i++) {
        // Note this is an arduino function call to the pins
        digitalWrite(b[i], LOW);
    }
}
// Writes to the buffer. Note this function ORs the current value with the new value
// Note that size is an optional argument with default size the same as the buffer
void writeBuffer(unsigned char b_temp, int size = b_size)
{
    for (int i = (size - 1); i >= 0; i--) {
        if ((b_temp >> i) & 0x01) {
        digitalWrite(b[i], HIGH);
        }
    }
    
}

void setup(){
    // LEDs
    for(int i = 0; i < b_size; i++)
    {
        pinMode(b[i], OUTPUT);
    }
    Serial.begin(9600);
    period = 1000;
    lastRan = 0;
 
}
// This function takes in the state as an argument & returns the current state
int SM1_Tick(int state){
    int value = analogRead(A1);
  
    switch(state){ // State transitions
      case INIT:
         //State Transition
      if (value <= 20) {
            state = P1;
      }
      if (value > 20) {
        state = L1;
      }
        break;
      case L1:          
         if (value <= 20) {
            state = P2;
         }
         if (value > 20) {
          state = L2;
         }
        break;
      case L2: 
         if (value <= 20) {
          state = P3;
         }
         if (value > 20) {
          state = L3;
         }
      break;
      case L3:
        if (value <= 20) {
          state = P4;
         }
         if (value > 20) {
          state = L4;
         }
      break;
      
      case L4:
        state = INIT;
        break;
      
      case P1:
        if (value > 20) {
          state = L2;
        }
        if (value <= 20) {
        state = P2;
        }
        break;
      
      case P2:
        if (value > 20) {
          state = L3;
        }
        if (value <= 20) {
         state = P3;
        }
        break;
      
      case P3:
      if (value > 20) {
        state = L4;
      }
      if (value <= 20) {
        state = P4;
      }
        break;
      
      case P4:
        state = INIT;
        break;
      
      default:
        break;
    }
    switch(state){ // State Action
      
      case INIT:
        resetBuffer();
        break;
      case L1:
        for(int i = 0; i < 1; ++i) {
          writeBuffer(count[i]);
        }
        break;
        
      case L2: 
        resetBuffer();
        for(int i = 1; i < 2; ++i) {
          writeBuffer(count[i]);
        }
        
      break;
      
      case L3:
        resetBuffer();
        for(int i = 2; i < 3; ++i) {
          writeBuffer(count[i]);
        }
      break;
      
      case L4:
        resetBuffer();
        for(int i = 0; i < 4; ++i) {
          writeBuffer(count[i]);
        }
      break;
      
      case P1:
         for(int i = 0; i < 1; ++i) {
          writeBuffer(count2[i]);
        }
      break;
      
      case P2:
        resetBuffer();
        for(int i = 1; i < 2; ++i) {
          writeBuffer(count2[i]);
        }
      break;
      
      case P3:
        resetBuffer();
        for(int i = 2; i < 3; ++i) {
          writeBuffer(count2[i]);
        }
      break;
      case P4:
        resetBuffer();
        for(int i = 3; i < 4; ++i) {
          writeBuffer(count2[i]);
        }
      break;
      
      default:
        break;
    }
   
    return state;
}

void loop(){ 
    ///Default arduino function
    // We have to cast the return value of the tick function to type States
    if ((millis() - lastRan) > period) {
      SM1_state = (States)SM1_Tick(SM1_state);
      lastRan = millis();
    } 

}
