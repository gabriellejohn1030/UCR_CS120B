//Lab 5 Exercise 3
//Link to demo: 

enum States{INIT, S0, S1, S2, S3, S4} SM1_state;
enum States1{start, code} SM2_state;
int period = 500;
unsigned long lastRan;
int x;

// Array of Output Pin variables, set to the pins being used
const int b_size = 4;
const int b[b_size] = {8, 9, 10, 11};
const int xAxis = A0; // Recall that A0 is really a number under the hood.
const int yAxis = A1;
//const int light_pattern_size = 5;
//const char light_pattern[light_pattern_size] = {0x00, 0x01, 0x03, 0x07, 0x0F};
const char sound_pattern_size = 5;
const double sound_pattern[sound_pattern_size] = {293.66, 493.88, 329.63, 261.63, 440.00}; // D4, D4,
double arr_a[10] = {1,1,2,2,3,3,4,4,5,5};
double arr_b[10];


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

boolean array_cmp(double *a, double *b, double len_a, double len_b){
      int n;

      // if their lengths are different, return false
      if (len_a != len_b) return false;

      // test each element to be the same. if not, return false
      for (n=0;n<len_a;n++) if (a[n]!=b[n]) return false;

      //ok, if we have not returned yet, they are equal :)
      return true;
}

int SM1_Tick(int state){
    //Read thing
    switch(state){ // State transitions
      case INIT:
          if (analogRead(yAxis) > 950){
            state = S0;
          }
          if (analogRead(yAxis) < 50){
            state = S1;
          }
          if (analogRead(xAxis) < 200){
            state = S2;
          }
           if (analogRead(xAxis) > 900){
            state = S3;
          }
          if (digitalRead(joystick) == 0){
            state = S4;
          }
        break;
      case S0: //up
          if (analogRead(yAxis) > 950){
            state = S0;
          }
          if (analogRead(yAxis) < 50){
            state = S1;
          }
          if (analogRead(xAxis) < 200){
            state = S2;
          }
           if (analogRead(xAxis) > 900){
            state = S3;
          }
          if (digitalRead(joystick) == 0){
            state = S4;
          }
        break;
      case S1: //down
          if (analogRead(yAxis) > 950){
            state = S0;
          }
          if (analogRead(yAxis) < 50){
            state = S1;
          }
          if (analogRead(xAxis) < 200){
            state = S2;
          }
           if (analogRead(xAxis) > 900){
            state = S3;
          }
          if (digitalRead(joystick) == 0){
            state = S4;
          }
          break;
      case S2: //left
          if (analogRead(yAxis) > 950){
            state = S0;
          }
          if (analogRead(yAxis) < 50){
            state = S1;
          }
          if (analogRead(xAxis) < 200){
            state = S2;
          }
           if (analogRead(xAxis) > 900){
            state = S3;
          }
          if (digitalRead(joystick) == 0){
            state = S4;
          }
          break;
      case S3: //right
          if (analogRead(yAxis) > 950){
            state = S0;
          }
          if (analogRead(yAxis) < 50){
            state = S1;
          }
          if (analogRead(xAxis) < 200){
            state = S2;
          }
           if (analogRead(xAxis) > 900){
            state = S3;
          }
          if (digitalRead(joystick) == 0){
            state = S4;
          }
          break;
      case S4: //click
          if (analogRead(yAxis) > 950){
            state = S0;
          }
          if (analogRead(yAxis) < 50){
            state = S1;
          }
          if (analogRead(xAxis) < 200){
            state = S2;
          }
           if (analogRead(xAxis) > 900){
            state = S3;
          }
          if (digitalRead(joystick) == 0){
            state = S4;
          }
          break;
    }
    switch(state){ // State Action
      case INIT:
        break;
      case S0:
        tone(buzzer, sound_pattern[0]); 
        break;
      case S1:
        tone(buzzer, sound_pattern[1]); 
        break;
      case S2:
        tone(buzzer, sound_pattern[2]); 
        break;
      case S3:
        tone(buzzer, sound_pattern[3]); 
        break;
      case S4:
        tone(buzzer, sound_pattern[4]); 
        break;       
    }

    return state;
}

int SM2_Tick(int state){

  switch(state) {
    case start:
      if(array_cmp(arr_a, arr_b, 10, 10) == true) {
         state = code;
      }
      else {
        state = start;
      }
      break;
    case code:
       state = start;
       break;
        
  }

  switch(state) {
    case start:
     
     for(int i = 0; i < 11; i++) {
        if (analogRead(yAxis) > 950){
            arr_b[i] = 1;
        }
          if (analogRead(yAxis) < 50){
            arr_b[i] = 2;
          }
          if (analogRead(xAxis) < 200){
            arr_b[i] = 3;
          }
           if (analogRead(xAxis) > 900){
            arr_b[i] = 4;
          }
          if (digitalRead(joystick) == 0){
            arr_b[i] = 5;
          }
     }
     break;
     case code:
        tone(buzzer, sound_pattern[0]);
        tone(buzzer, sound_pattern[0]);
        tone(buzzer, sound_pattern[1]);
        tone(buzzer, sound_pattern[1]);
        tone(buzzer, sound_pattern[2]);
        tone(buzzer, sound_pattern[2]);
        tone(buzzer, sound_pattern[3]);
        tone(buzzer, sound_pattern[3]);
        tone(buzzer, sound_pattern[4]);
        tone(buzzer, sound_pattern[4]);

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
      //SM1_state = (States)SM1_Tick(SM1_state); 
      SM2_state = (States1)SM2_Tick(SM2_state);       
      lastRan = millis();   
     }  
}
