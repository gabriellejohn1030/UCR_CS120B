//Lab 5 Exercise 2
//Link to demo: https://youtube.com/shorts/BLo8kTPcpcA

enum States{INIT, S0, S1, S2, S3} SM1_state;
int period = 100;
unsigned long lastRan;


// Array of Output Pin variables, set to the pins being used
const int b_size = 4;
const int b[b_size] = {8, 9, 10, 11};
const int xAxis = A0; // Recall that A0 is really a number under the hood.
const int yAxis = A1;
const int light_pattern_size = 5;
const char light_pattern[light_pattern_size] = {0x00, 0x01, 0x03, 0x07, 0x0F};
const char sound_pattern_size = 5;
const double sound_pattern[sound_pattern_size] = {293.66, 493.88, 329.63, 261.63, 440.00}; // D4, D4,


const int buzzer = 3; //pin for buzzer
const int joystick = 2; //pin for joystick
bool joyVal;

const int xAxis_median = 100; // Adjust this if needed

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
          if (analogRead(xAxis) < 200){
            state = S0;
          }
        break;
      case S0:
          if (analogRead(xAxis) > 900){
            state = S1;
          }
      case S1:
          if (analogRead(yAxis) > 950){
            state = S2;
          }
      case S2:
          if (analogRead(yAxis) < 50){
            state = S3;
          }
      case S3:
          if(digitalRead(joystick) == 0) {
            state = INIT;
          }
    }
    switch(state){ // State Action
      case INIT:
         resetBuffer();
         writeBuffer(0x00);
        break;
      case S0:
        resetBuffer();
        writeBuffer(0x01); 
        break;
      case S1:
        resetBuffer();
        writeBuffer(0x03); 
        break;
      case S2:
        resetBuffer();
        writeBuffer(0x07); 
        break;
      case S3:
        resetBuffer();
        writeBuffer(0x0F); 
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

void loop() {

  
    if ((millis() - lastRan) > period) {     
      SM1_state = (States)SM1_Tick(SM1_state);        
      lastRan = millis();   
     }  
}
