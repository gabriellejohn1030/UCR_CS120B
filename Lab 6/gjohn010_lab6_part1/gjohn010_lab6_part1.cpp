//Lab 6 Part 1
//Link to demo: https://youtube.com/watch/uvO61bDSLiA?feature=share

// Array of Output Pin variables, set to the pins being used
const int b_size = 4;
const int b[b_size] = {8, 9, 10, 11};
const int xAxis = A0; // Recall that A0 is really a number under the hood.
const int yAxis = A1; 
const int light_pattern_size = 2;
const char light_pattern[light_pattern_size] = {0x00, 0x0F};



const char sound_pattern_size = 5;
const double sound_pattern[sound_pattern_size] = {261.63, 329.69, 392.00, 440.00, 493.88}; // UP, DOWN, LEFT, RIGHT, CLICK
const char code_size = 10;
const double code[code_size] = {261.63, 261.63, 329.69, 329.69, 392.00, 392.00, 440.00, 440.00, 493.88, 493.88}; //right code
unsigned char count = 0;
unsigned char j = 0;

const int buzzer = 3; //pin #
const int joystick = 2; //pin #

const int xAxis_median_left = 100; // Adjust this if needed
const int xAxis_median_right = 900;
const int yAxis_median_down = 100;
const int yAxis_median_up = 900;


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


typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);
    
} task;

int delay_gcd;
const unsigned short tasksNum = 2;
task tasks[tasksNum];

enum SM1_States {SM1_INIT, SM1_S0, SM1_S1, SM1_S2, SM1_S3, SM1_S4};
int SM1_Tick(int state){
    //Read thing
    switch(state){ // State transitions
      case SM1_INIT: //up
      j = count;
      if (j < 10) {
           if((analogRead(yAxis) > yAxis_median_up)) {//correct
              count = count + 1;
              state = SM1_S0;
              
           }
           if((analogRead(yAxis) < yAxis_median_down) && ((j < 2) || (j > 3))) {//incorrect
              count = 0;
              state = SM1_S1;
              
           }
           if ((analogRead(xAxis) < xAxis_median_left) && ((j < 4) || (j > 5))) {//incorrect
              count = 0;
              state = SM1_S2;
              
           }
           if((analogRead(xAxis) > xAxis_median_right) && ((j < 6) || (j > 7))) {//incorrect
               count = 0;
              state = SM1_S3;
             
           }
           if(digitalRead(joystick) == 0 && (j < 8)) {//incorrect
              count = 0;
              state = SM1_INIT;
              
           }
      }
         
        break;
      case SM1_S0: //up, down
      j = count;
      if (j < 10) {
           if((analogRead(yAxis) > yAxis_median_up) && (j < 2)) { //correct
              count = count + 1;
              state = SM1_S0;
              
           }
           if((analogRead(yAxis) > yAxis_median_up) && (j > 1)) { //incorrect
              count = 0;
              state = SM1_S0;
              
           }
           if((analogRead(yAxis) < yAxis_median_down) && ((j > 1) && (j < 4))) {//correct, between 2&3
              count = count + 1;
              state = SM1_S1;
              
           }
           if((analogRead(yAxis) < yAxis_median_down) && ((j < 2) || (j > 3))) {//incorrect, less than 2 and more than 3
              count = 0;
              state = SM1_S1;
              
           }
           if ((analogRead(xAxis) < xAxis_median_left) && ((j < 4) || (j > 5))) {//incorrect, less than 4 and greater than 6
              count = 0;
              state = SM1_S2;
              
           }
           if((analogRead(xAxis) > xAxis_median_right) && ((j < 6) || (j > 7))) {//incorrect,less than 6 and greater than 7
              count = 0;
              state = SM1_S3;
              
           }
           if(digitalRead(joystick) == 0 && (j < 8)) {//incorrect, less than 8 
              count = 0;
              state = SM1_INIT;
              
           }
      }
        break;
      case SM1_S1: //down, left
      j = count;
      if (j < 10) {
           if((analogRead(yAxis) > yAxis_median_up) && (j > 2)) { //incorrect, greater than 2
              count = 0;
              state = SM1_S0;
              
           }
           if((analogRead(yAxis) < yAxis_median_down) && ((j > 1) && (j < 4))) {//correct, index 2&3
              count = count + 1;
              state = SM1_S1;
              
           }
           if((analogRead(yAxis) < yAxis_median_down) && ((j < 2) || (j > 3))) {//incorrect, less than 2 and greater than 3
              count = 0;
              state = SM1_S1;
              
           }
           if ((analogRead(xAxis) < xAxis_median_left) && ((j > 3) && (j < 6))) {//correct, index 4&5
              count = count + 1;
              state = SM1_S2;
              
           }
           if((analogRead(xAxis) > xAxis_median_right) && ((j < 6) || (j > 7))) {//incorrect, less than 6 and greater than 7
              count = 0;
              state = SM1_S3;
              
           }
           if(digitalRead(joystick) == 0 && (j < 8)) {//incorrect, needs to be 8&9
              count = 0;
              state = SM1_INIT;
              
           }
      }
         break;
      case SM1_S2: //left, right
        j = count;
        if (j < 10) {
           if((analogRead(yAxis) > yAxis_median_up) && (j > 2)) { //incorrect, greater than 2
              count = 0;
              state = SM1_S0;
              
           }
           if((analogRead(yAxis) < yAxis_median_down) && ((j < 2) || (j > 3))) {//incorrect, less than 2 and greater than 3
              count = 0;
              state = SM1_S1;
              
           }
           if ((analogRead(xAxis) < xAxis_median_left) && ((j > 3) && (j < 6))) {//correct, index 4&5
              count = count + 1;
              state = SM1_S2;
              
           }
           if ((analogRead(xAxis) < xAxis_median_left) && ((j < 4) || (j > 5))) {//incorrect, less than 4, greater than 5
              count = 0;
              state = SM1_S2;
              
           }
           if((analogRead(xAxis) > xAxis_median_right) && ((j < 6) || (j > 7))) {//incorrect, less than 6 and greater than 7
              count = 0;
              state = SM1_S3;
              
           }
           if((analogRead(xAxis) > xAxis_median_right) && ((j > 5) && (j < 8))) {//correct, index 6&7
              count++;
              state = SM1_S3;
              
           }
           if(digitalRead(joystick) == 0 && (j < 8)) {//incorrect, needs to be 8&9
              count = 0;
              state = SM1_INIT;
              
           }
      }
         break;
      case SM1_S3: //right,click
        j = count;
        if (j < 10) {
           if((analogRead(yAxis) > yAxis_median_up) && (j > 2)) { //incorrect, greater than 2
              count = 0;
              state = SM1_S0;
              
           }
           if((analogRead(yAxis) < yAxis_median_down) && ((j < 2) || (j > 3))) {//incorrect, less than 2 and greater than 3
              count = 0;
              state = SM1_S1;
              
           }
           if ((analogRead(xAxis) < xAxis_median_left) && ((j < 4) || (j > 5))) {//incorrect, less than 4, greater than 5
              count = 0;
              state = SM1_S2;
              
           }
           if((analogRead(xAxis) > xAxis_median_right) && ((j < 6) || (j > 7))) {//incorrect, less than 6 and greater than 7
              count = 0;
              state = SM1_S3;
              
           }
           if((analogRead(xAxis) > xAxis_median_right) && ((j > 5) && (j < 8))) {//correct, index 6&7
              count = count + 1;
              state = SM1_S3;
              
           }
           if(digitalRead(joystick) == 0 && (j < 8)) {//incorrect, less than 8
              count = 0;
              state = SM1_INIT;
              
           }
           if(digitalRead(joystick) == 0 && (j > 7)) {//correct, index 8&9
              count = count + 1;
              state = SM1_S4;
              
           }
      }
         break;
      case SM1_S4: //click
         j = count;
         if (j < 10) {
           if((analogRead(yAxis) > yAxis_median_up) && (j > 2)) { //incorrect, greater than 2
              count = 0;
              state = SM1_S0;
              
           }
           if((analogRead(yAxis) < yAxis_median_down) && ((j < 2) || (j > 3))) {//incorrect, less than 2 and greater than 3
              count = 0;
              state = SM1_S1;
              
           }
           if ((analogRead(xAxis) < xAxis_median_left) && ((j < 4) || (j > 5))) {//incorrect, less than 4, greater than 5
              count = 0;
              state = SM1_S2;
              
           }
           if((analogRead(xAxis) > xAxis_median_right) && ((j < 6) || (j > 7))) {//incorrect, less than 6 and greater than 7
              count = 0;
              state = SM1_S3;
              
           }
           if(digitalRead(joystick) == 0 && (j < 8)) {//incorrect, less than 8
              count = 0;
              state = SM1_INIT;
              
           }
           if(digitalRead(joystick) == 0 && (j > 7)) {//correct, index 8&9
              count = count + 1;
              state = SM1_S4;
              
           }
      }
         break;
    }
    switch(state){ // State Action
      case SM1_INIT:
        noTone(buzzer);
        break;
      case SM1_S0: //up
        tone(buzzer, sound_pattern[0]);
        if(analogRead(yAxis) < yAxis_median_up) {
          noTone(buzzer);
        }
        break;
      case SM1_S1: //down
        tone(buzzer, sound_pattern[1]);
        if(analogRead(yAxis) > yAxis_median_down) {
          noTone(buzzer);
        }
        break;
      case SM1_S2: //left
        tone(buzzer, sound_pattern[2]);
        if(analogRead(xAxis) > xAxis_median_left) {
          noTone(buzzer);
        }
        break;
      case SM1_S3: //right
        tone(buzzer, sound_pattern[3]);
        if(analogRead(xAxis) < xAxis_median_right) {
          noTone(buzzer);
        }
        break;
      case SM1_S4: //click
        tone(buzzer, sound_pattern[4]);
        if(digitalRead(joystick) == 1) {
          noTone(buzzer);
        }
        break;
    }

    return state;
}

enum SM2_States {SM2_INIT, SM2_S0, SM2_S1, SM2_S2, SM2_S3, SM2_S4, SM2_S5, SM2_S6, SM2_S7, SM2_S8, SM2_S9};
int SM2_Tick(int state){
    //Read thing
    switch(state){ // State transitions
      case SM2_INIT:
      if(count >= 10) {
            state = SM2_S0;
      }
      if(count == 0) {
        state = SM1_INIT;
      }
       break;
      case SM2_S0:
           if(digitalRead(joystick) == 0) {
            count = 0;
            state = SM2_INIT;
         
           }
           else {
            state = SM2_S1;
           }
       break;
      case SM2_S1:
        if(digitalRead(joystick) == 0) {
            count = 0;
            state = SM2_INIT;
         
           }
           else {
            state = SM2_S2;
           }
       break;
      case SM2_S2:
        if(digitalRead(joystick) == 0) {
            count = 0;
            state = SM2_INIT;
         
           }
           else {
            state = SM2_S3;
           }
       break;
      case SM2_S3:
        if(digitalRead(joystick) == 0) {
            count = 0;
            state = SM2_INIT;
         
           }
           else {
            state = SM2_S4;
           }
       break;
      case SM2_S4:
        if(digitalRead(joystick) == 0) {
            count = 0;
            state = SM2_INIT;
         
           }
           else {
            state = SM2_S5;
           }
       break;
      case SM2_S5:
        if(digitalRead(joystick) == 0) {
            count = 0;
            state = SM2_INIT;
         
           }
           else {
            state = SM2_S6;
           }
       break;
      case SM2_S6:
        if(digitalRead(joystick) == 0) {
            count = 0;
            state = SM2_INIT;
         
           }
           else {
            state = SM2_S7;
           }
       break;
      case SM2_S7:
        if(digitalRead(joystick) == 0) {
            count = 0;
            state = SM2_INIT;
         
           }
           else {
            state = SM2_S8;
           }
       break;
      case SM2_S8:
        if(digitalRead(joystick) == 0) {
            count = 0;
            state = SM2_INIT;
         
           }
           else {
            state = SM2_S9;
           }
       break;
      case SM2_S9:
        if(digitalRead(joystick) == 0) {
            count = 0;
            state = SM2_INIT;
         
           }
           else {
            state = SM2_S0;
           }
       break;
       
    }
    switch(state){ // State Action
      case SM2_INIT:
        break;
      case SM2_S0:
         tone(buzzer, code[0]);
         break;
      case SM2_S1:
        tone(buzzer, code[1]);
        break;
      case SM2_S2:
        tone(buzzer, code[2]);
        break;
      case SM2_S3:
        tone(buzzer, code[3]);
        break;
      case SM2_S4:
        tone(buzzer, code[4]);
        break;
      case SM2_S5:
        tone(buzzer, code[5]);
        break;
      case SM2_S6:
        tone(buzzer, code[6]);
        break;
      case SM2_S7:
        tone(buzzer, code[7]);
        break;
      case SM2_S8:
        tone(buzzer, code[8]);
        break;
      case SM2_S9:    
        tone(buzzer, code[9]);   
        break;          
    }

    return state;
}



void setup() {
    //some set up (Default Arduino Function)

    // LEDs
    for(int i = 0; i < b_size; i++)
    {
        pinMode(b[i], OUTPUT);
    }
    Serial.begin(9600);
    pinMode(joystick, INPUT_PULLUP);


  unsigned char i = 0;
  tasks[i].state = SM1_INIT;
  tasks[i].period = 500;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM1_Tick;
  i++;
  tasks[i].state = SM2_INIT;
  tasks[i].period = 250;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM2_Tick;

  delay_gcd = 250; // GCD

}


void loop() {
  // put your main code here, to run repeatedly:

  Serial.print("Count: ");
  Serial.print(count);
  Serial.print("\n");
  Serial.print("j count: ");
  Serial.print(j);
  Serial.print("\n");

  
  unsigned char i;
  for (i = 0; i < tasksNum; ++i) {
     if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elapsedTime = millis(); // Last time this task was ran
      
     }
   }
  delay(delay_gcd); // GCD.
}
