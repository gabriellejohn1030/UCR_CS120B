//Lab 5 Exercise 1
//Link to demo: https://youtube.com/shorts/M9mBcJhCPBw

enum States{INIT, S0, S1, S2, S3, S4, P0, P1, P2, P3, P4, P5} SM1_state;
int period = 500;
unsigned long lastRan;
int count = 0;
int x = 0;


// Array of Output Pin variables, set to the pins being used
const int b_size = 4;
const int b[b_size] = {8, 9, 10, 11};
//const int xAxis = A0; // Recall that A0 is really a number under the hood.
const int light_pattern_size = 5;
const char light_pattern[light_pattern_size] = {0x00, 0x01, 0x03, 0x07, 0x0F};
const char sound_pattern_size = 5;
const double sound_pattern[sound_pattern_size] = {293.66, 493.88, 329.63, 261.63, 440.00}; // D4, D4,


const int buzzer = 3; //pin for buzzer
const int joystick = 2; //pin for joystick

//const int xAxis_median = 100; // Adjust this if needed

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

int SM1_Tick(int state){
    //Read thing
    switch(state){ // State transitions
      case INIT:
          if (digitalRead(joystick) == 1){
            state = S0;
          }
          else {
            state = P0;
          } 
        break;
      case S0:
          if (digitalRead(joystick) == 1){
                state = S1;
            }
            else {
             state = P1;
            }
       
        break;
      case S1:
            if (digitalRead(joystick) == 1){
                state = S2;
            }
            else {
             state = P2;
            }

        break;
      case S2:
        if(digitalRead(joystick) == 1){
            state = S3;
        }
        else {
          state = P3;
        }
        break;
      case S3:
       if(digitalRead(joystick) == 1){
                state = INIT;
        }
        else {
          state = P4;
        }
      case S4:
        if(digitalRead(joystick) == 1){
                state = INIT;
        }
        else {
          state = P4;
        }
        break;
      case P0:
        while (digitalRead(joystick) == 0 && x == 0) {
          state = P0;
        }
          state = S0;
        break;
      case P1:
        while (digitalRead(joystick) == 0 && x == 1) {
          state = P1;
        }
 
          state = S1;
        
        break;
       case P2:
        while (digitalRead(joystick) == 0 && x == 2) {
          state = P2;
        }
     
          state = S2;

        break;
       case P3:
        while (digitalRead(joystick) == 0 && x == 3) {
          state = P3;
        }
          state = S3;
        break;
       case P4:
          while (digitalRead(joystick) == 0 && x == 4) {
          state = P4;
        }
   
          state = INIT;
        break;
    }
    switch(state){ // State Action
      case INIT:
         resetBuffer();
         writeBuffer(light_pattern[0]);
         tone(buzzer, sound_pattern[0]);
         x = 0;
        break;
      case S0:
        resetBuffer();
        writeBuffer(light_pattern[1]); 
        tone(buzzer, sound_pattern[1]);
        x = 1;
        break;
         //State Action
        break;
      case S1:
        resetBuffer();
        writeBuffer(light_pattern[2]);
        tone(buzzer, sound_pattern[2]);
        x = 2;
        break;
      case S2:
        resetBuffer();
        writeBuffer(light_pattern[3]);
        tone(buzzer, sound_pattern[3]);
        x = 3;
        break;
      case S3:
        resetBuffer();
        writeBuffer(light_pattern[4]);
        tone(buzzer, sound_pattern[4]);
        x = 4;
       break;
      case P0:
        resetBuffer();
        writeBuffer(light_pattern[0]);
        noTone(buzzer);
        break;
      case P1:
        resetBuffer();
        writeBuffer(light_pattern[1]);
        noTone(buzzer);
        break;
      case P2:
        resetBuffer();
        writeBuffer(light_pattern[2]);
        noTone(buzzer);
        break;
      case P3: 
        resetBuffer();
        writeBuffer(light_pattern[3]);
        noTone(buzzer);
        break;
      case P4:
        resetBuffer();
        writeBuffer(light_pattern[3]);
        noTone(buzzer);
        break;
    }

    return state;
}


void setup() {
    // OUTPUT is a defined macro in Arduino!
    for(int i = 0; i < b_size; i++)
        {
            pinMode(b[i], OUTPUT);
        }
    // We will also read from the serial monitor
    Serial.begin(9600);
    pinMode(joystick, INPUT_PULLUP);
    lastRan = 0;
    
}

void loop() {https://youtu.be/uhGnunRV43s
    if ((millis() - lastRan) > period) {     
      SM1_state = (States)SM1_Tick(SM1_state);        
      lastRan = millis();   
     }  
}
