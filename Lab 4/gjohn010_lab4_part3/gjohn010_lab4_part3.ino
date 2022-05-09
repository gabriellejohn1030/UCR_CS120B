//Lab 4 Exercise 3
//Link to demo: https://youtube.com/shorts/lPCp4OtH1wc

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
       state = L1;
      break;
      case L1:          
        state = L2; 
      break;
      case L2: 
        state = INIT;
         
      break;
      
      default:
        break;
    }
    switch(state){ // State Action
      
      case INIT:
        resetBuffer();
        writeBuffer(0x01);
        if(value > 20) {
          digitalWrite(b[3], HIGH);
        }
        else {
          digitalWrite(b[3], LOW);
        }
        break;
      case L1:
        resetBuffer();
        writeBuffer(0x02);
        if(value > 20) {
          digitalWrite(b[3], HIGH);
        }
        else {
          digitalWrite(b[3], LOW);
        }
     break;
        
      case L2: 
        resetBuffer();
        writeBuffer(0x04);
        if(value > 20) {
          digitalWrite(b[3], HIGH);
        }
        else {
          digitalWrite(b[3], LOW);
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
