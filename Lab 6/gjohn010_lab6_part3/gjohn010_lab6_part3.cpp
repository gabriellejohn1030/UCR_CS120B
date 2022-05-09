//Lab 6 Exercise 3
//Link to demo: https://youtube.com/watch/BvCVHK62TqA?feature=share

// Array of Output Pin variables, set to the pins being used
const int b_size = 4;
const int b[b_size] = {8, 9, 10, 11};
const int xAxis = A0; // Recall that A0 is really a number under the hood.
const int yAxis = A1;
const int light_pattern_size = 4;
const char light_pattern[light_pattern_size] = {0x01, 0X02, 0X04, 0x08};
int rand_pattern[4];
unsigned int x;
unsigned int count = 0;
unsigned int counter = 3;
unsigned int i = 0;

const char sound_pattern_size = 5;
const double sound_pattern[sound_pattern_size] = {261.63, 293.66, 369.99, 415.30, 493.88}; // C4, D4

const int buzzer = 3;
const int joystick = 2;

const int xAxis_median_left = 200; // Adjust this if needed
const int xAxis_median_right = 900;
const int yAxis_median_down = 100;
const int yAxis_median_up = 800;


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

enum SM1_States {SM1_INIT, SM1_S0, SM1_S1, SM1_S2, SM1_S3, SM1_S4, SM1_S5, SM1_S6, SM1_S7, SM1_S8};
int SM1_Tick(int state){
    //Read thing
    switch(state){ // State transitions
      case SM1_INIT:
        if(digitalRead(joystick) == 0) { //DO THIS to start game
          state = SM1_S0;
        }
        break; //END
      
      case SM1_S0: //BEGIN handling random sequence
        if(count >= 3) {
          state = SM1_S2; 
        }
        if(count < 3) {
          state = SM1_S1;
        }
        break;
      case SM1_S1:
          state = SM1_S0;
      break;          //END handling random sequence generator
        
      case SM1_S2: //FIRST USER INPUT, i = 0;
        //count = 4;
        if(counter == 0) {
          state = SM1_S7;
        }

        if(rand_pattern[i] == 0) {
          if(analogRead(xAxis) > xAxis_median_right) {
            counter--;
            i++;
            state = SM1_S3;
          }
          if(analogRead(yAxis) > yAxis_median_up) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
          if(analogRead(xAxis) < xAxis_median_left) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
          if (analogRead(yAxis) < yAxis_median_down) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
        }

        if(rand_pattern[i] == 1) {
          if(analogRead(yAxis) < yAxis_median_down) {
            counter--;
            i++;
            state = SM1_S4;
          }
          if(analogRead(yAxis) > yAxis_median_up) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
          if(analogRead(xAxis) < xAxis_median_left) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
          if (analogRead(xAxis) > xAxis_median_right) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
        }

        if(rand_pattern[i] == 2) {
          if(analogRead(yAxis) > yAxis_median_up) {
            counter--;
            i++;
            state = SM1_S5;
          }
          if(analogRead(xAxis) < xAxis_median_left) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
          if (analogRead(xAxis) > xAxis_median_right) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
          if (analogRead(yAxis) < yAxis_median_down) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
        }
          
        if(rand_pattern[i] == 3) {
           if(analogRead(xAxis) < xAxis_median_left) {
              counter--;
              i++;
              state = SM1_S6;
            }
           if (analogRead(xAxis) > xAxis_median_right) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
           if (analogRead(yAxis) > yAxis_median_up) {
              count = 0;
              counter = 3;
              i = 0;
            state = SM1_S0;
          }
          if (analogRead(yAxis) < yAxis_median_down) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
          
           
        }

        if(digitalRead(joystick) == 0) { 
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
        break;
      case SM1_S3: //right
        if(counter == 0) {
          state = SM1_S7;
        }

        if(rand_pattern[i] == 0) {
          if(analogRead(xAxis) > xAxis_median_right) {
            counter--;
            i++;
            state = SM1_S3;
          }
          if(analogRead(yAxis) > yAxis_median_up) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
          if(analogRead(xAxis) < xAxis_median_left) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
          if (analogRead(yAxis) < yAxis_median_down) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
        }

        if(rand_pattern[i] == 1) {
          if(analogRead(yAxis) < yAxis_median_down) {
            counter--;
            i++;
            state = SM1_S4;
          }
          if(analogRead(yAxis) > yAxis_median_up) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
          if(analogRead(xAxis) < xAxis_median_left) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
          if (analogRead(xAxis) > xAxis_median_right) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
        }

        if(rand_pattern[i] == 2) {
          if(analogRead(yAxis) > yAxis_median_up) {
            counter--;
            i++;
            state = SM1_S5;
          }
          if(analogRead(xAxis) < xAxis_median_left) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
          if (analogRead(xAxis) > xAxis_median_right) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
          if (analogRead(yAxis) < yAxis_median_down) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
        }
          
        if(rand_pattern[i] == 3) {
           if(analogRead(xAxis) < xAxis_median_left) {
              counter--;
              i++;
              state = SM1_S6;
            }
           if (analogRead(xAxis) > xAxis_median_right) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
           if (analogRead(yAxis) > yAxis_median_up) {
              count = 0;
              counter = 3;
              i = 0;
            state = SM1_S0;
          }
          if (analogRead(yAxis) < yAxis_median_down) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
          
           
        }
          
        if(digitalRead(joystick) == 0) { 
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
        break;
      case SM1_S4: //down
         if(counter == 0) {
          state = SM1_S7;
        }

        if(rand_pattern[i] == 0) {
          if(analogRead(xAxis) > xAxis_median_right) {
            counter--;
            i++;
            state = SM1_S3;
          }
          if(analogRead(yAxis) > yAxis_median_up) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
          if(analogRead(xAxis) < xAxis_median_left) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
          if (analogRead(yAxis) < yAxis_median_down) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
        }

        if(rand_pattern[i] == 1) {
          if(analogRead(yAxis) < yAxis_median_down) {
            counter--;
            i++;
            state = SM1_S4;
          }
          if(analogRead(yAxis) > yAxis_median_up) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
          if(analogRead(xAxis) < xAxis_median_left) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
          if (analogRead(xAxis) > xAxis_median_right) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
        }

        if(rand_pattern[i] == 2) {
          if(analogRead(yAxis) > yAxis_median_up) {
            counter--;
            i++;
            state = SM1_S5;
          }
          if(analogRead(xAxis) < xAxis_median_left) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
          if (analogRead(xAxis) > xAxis_median_right) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
          if (analogRead(yAxis) < yAxis_median_down) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
        }
          
        if(rand_pattern[i] == 3) {
           if(analogRead(xAxis) < xAxis_median_left) {
              counter--;
              i++;
              state = SM1_S6;
            }
           if (analogRead(xAxis) > xAxis_median_right) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
           if (analogRead(yAxis) > yAxis_median_up) {
              count = 0;
              counter = 3;
              i = 0;
            state = SM1_S0;
          }
          if (analogRead(yAxis) < yAxis_median_down) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
          
           
        }
          
        if(digitalRead(joystick) == 0) { 
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
        break;
      case SM1_S5: //up
         if(counter == 0) {
          state = SM1_S7;
        }

        if(rand_pattern[i] == 0) {
          if(analogRead(xAxis) > xAxis_median_right) {
            counter--;
            i++;
            state = SM1_S3;
          }
          if(analogRead(yAxis) > yAxis_median_up) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
          if(analogRead(xAxis) < xAxis_median_left) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
          if (analogRead(yAxis) < yAxis_median_down) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
        }

        if(rand_pattern[i] == 1) {
          if(analogRead(yAxis) < yAxis_median_down) {
            counter--;
            i++;
            state = SM1_S4;
          }
          if(analogRead(yAxis) > yAxis_median_up) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
          if(analogRead(xAxis) < xAxis_median_left) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
          if (analogRead(xAxis) > xAxis_median_right) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
        }

        if(rand_pattern[i] == 2) {
          if(analogRead(yAxis) > yAxis_median_up) {
            counter--;
            i++;
            state = SM1_S5;
          }
          if(analogRead(xAxis) < xAxis_median_left) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
          if (analogRead(xAxis) > xAxis_median_right) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
          if (analogRead(yAxis) < yAxis_median_down) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
        }
          
        if(rand_pattern[i] == 3) {
           if(analogRead(xAxis) < xAxis_median_left) {
              counter--;
              i++;
              state = SM1_S6;
            }
           if (analogRead(xAxis) > xAxis_median_right) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
           if (analogRead(yAxis) > yAxis_median_up) {
              count = 0;
              counter = 3;
              i = 0;
            state = SM1_S0;
          }
          if (analogRead(yAxis) < yAxis_median_down) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
          
           
        }
          
        if(digitalRead(joystick) == 0) { 
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
        break; 
        
      case SM1_S6: //left
        if(counter == 0) {
          state = SM1_S7;
        }

        if(rand_pattern[i] == 0) {
          if(analogRead(xAxis) > xAxis_median_right) {
            counter--;
            i++;
            state = SM1_S3;
          }
          if(analogRead(yAxis) > yAxis_median_up) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
          if(analogRead(xAxis) < xAxis_median_left) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
          if (analogRead(yAxis) < yAxis_median_down) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
        }

        if(rand_pattern[i] == 1) {
          if(analogRead(yAxis) < yAxis_median_down) {
            counter--;
            i++;
            state = SM1_S4;
          }
          if(analogRead(yAxis) > yAxis_median_up) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
          if(analogRead(xAxis) < xAxis_median_left) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
          if (analogRead(xAxis) > xAxis_median_right) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
        }

        if(rand_pattern[i] == 2) {
          if(analogRead(yAxis) > yAxis_median_up) {
            counter--;
            i++;
            state = SM1_S5;
          }
          if(analogRead(xAxis) < xAxis_median_left) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
          if (analogRead(xAxis) > xAxis_median_right) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
          if (analogRead(yAxis) < yAxis_median_down) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
        }
          
        if(rand_pattern[i] == 3) {
           if(analogRead(xAxis) < xAxis_median_left) {
              counter--;
              i++;
              state = SM1_S6;
            }
           if (analogRead(xAxis) > xAxis_median_right) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
           if (analogRead(yAxis) > yAxis_median_up) {
              count = 0;
              counter = 3;
              i = 0;
            state = SM1_S0;
          }
          if (analogRead(yAxis) < yAxis_median_down) {
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
          
           
        }
          
        if(digitalRead(joystick) == 0) { 
            count = 0;
            counter = 3;
            i = 0;
            state = SM1_S0;
          }
        break;
      case SM1_S7: //WIN STATE
       if(digitalRead(joystick) == 0) {
          count = 0;
          counter = 3;
          i = 0;
          state = SM1_S0;
       }
       else {
        state = SM1_S8;
       }
       break;
      case SM1_S8: //LIGHTS FLASH OFF
       if(digitalRead(joystick) == 0) {
          count = 0;
          counter = 3;
          i = 0;
          state = SM1_S0;
       }
       else {
        state = SM1_S7;
       }
       break;
    }
    switch(state){ // State Action
      case SM1_INIT:
        break;
      case SM1_S0: 
        if (count < 3) {
           resetBuffer();
           x = random(0,4); //get random number from 0-3
           writeBuffer(light_pattern[x]); //outputs value from index 0-3
           rand_pattern[count] = x;
           count++;  
        }
        break;
      case SM1_S1:
        resetBuffer();
        writeBuffer(0x00);
        break;
     case SM1_S2:
        resetBuffer();
        break;
      case SM1_S3: //right
        resetBuffer();
        writeBuffer(0x01);
        break;
       case SM1_S4: //down
        resetBuffer(); 
        writeBuffer(0x02);
        break;
      case SM1_S5: //up
        resetBuffer(); 
        writeBuffer(0x04);
        break;
      case SM1_S6: //left
        resetBuffer();
        writeBuffer(0x08);
        break;
      case SM1_S7: //WIN STATE
        resetBuffer();
        writeBuffer(0x0F);
        break;
      case SM1_S8: //WIN STATE
        resetBuffer();
        writeBuffer(0x00);
        
      break;

    }

    return state;
}

enum SM2_States {SM2_INIT, SM2_S0, SM2_S1, SM2_S2, SM2_S3}; //SECOND TASK DONE
int SM2_Tick(int state){
    switch(state){ // State transitions
      case SM2_INIT:
         //State Transition
            state = SM2_S0;
        break;
      case SM2_S0:
            state = SM2_S1;
        //State Transition
        break;
      case SM2_S1:
            state = SM2_S2;            
        //State Transition
        break;
      case SM2_S2:
          state = SM2_S3;
      break;
      case SM2_S3:
        state = SM2_INIT;
      break;
    }
    switch(state){ // State Action
      case SM2_INIT:
         tone(buzzer, sound_pattern[0]);
        break;
      case SM2_S0:
         tone(buzzer, sound_pattern[1]);
        break;
      case SM2_S1:
         tone(buzzer, sound_pattern[2]);
        break;
      case SM2_S2:
         tone(buzzer, sound_pattern[3]);
        break;
      case SM2_S3:
         tone(buzzer, sound_pattern[4]);
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
  tasks[i].period = 200;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM2_Tick;

  delay_gcd = 100; // GCD

}


void loop() {

  unsigned char i;
  for (i = 0; i < tasksNum; ++i) {
     if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elapsedTime = millis(); // Last time this task was ran
      
     }
   }
  delay(delay_gcd); // GCD.
}
