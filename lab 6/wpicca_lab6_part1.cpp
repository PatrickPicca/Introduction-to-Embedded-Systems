/* William Picca wpicc001@ucr.edu
 * Lab Section: 001
 * Assignment: Lab #6 Exercise #1
 * Exercise Description:
 *
 * I acknowledge all content contained herein, excluding
 * template or example code, is my own original work.
 *
 * Demo Link: https://youtu.be/kaDWMcnTwvQ
 */


const int b0 = 2;
const int b1 = 3;
const int b2 = 4;
const int b3 = 5;
const int b4 = 6;
const int b5 = 7;
const int b6 = 8;
const int b7 = 9;

typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);
} task;

const unsigned short tasksNum = 1;
task tasks[tasksNum];

enum left_States { left_start, left_release };
int TickFct_leftLed(int state) 
{ 
  switch(state){ // Transition States
    
    case left_start:   //Go to release state
      state = left_release;
    break;
    
    default:
      break;
  }
  switch(state){ // Action States
    case left_start:
      break;
    
    case left_release:
          writeToB(1);
          delay(100);
          writeToB(2);
          delay(100);
          writeToB(4);
          delay(100);
          writeToB(8);
          delay(100);  
        writeToB(16);
          delay(100); 
          writeToB(32);
          delay(100);
          writeToB(64);
          delay(100);
          writeToB(128);
          delay(100); 
        writeToB(0);
          delay(100); 
    break;

    default:
      break;
  }
  return state; 
}

void setup() 
{
  // LED Setup
  pinMode(b0, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(b3, OUTPUT);
  pinMode(b4, OUTPUT);
  pinMode(b5, OUTPUT);
  pinMode(b6, OUTPUT);
  pinMode(b7, OUTPUT);
  
    unsigned char i = 0;
  tasks[i].state = left_start;
  tasks[i].period = 500;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &TickFct_leftLed;
}
void writeToB(unsigned char temp)
{
  resetB();
  if ((temp>>7) & 0x01){digitalWrite(b7,HIGH);}
  if ((temp>>6) & 0x01){digitalWrite(b6,HIGH);}
  if ((temp>>5) & 0x01){digitalWrite(b5,HIGH);}
  if ((temp>>4) & 0x01){digitalWrite(b4,HIGH);}
  if ((temp>>3) & 0x01){digitalWrite(b3,HIGH);}
  if ((temp>>2) & 0x01){digitalWrite(b2,HIGH);}
  if ((temp>>1) & 0x01){digitalWrite(b1,HIGH);}
  if (temp & 0x01){digitalWrite(b0,HIGH);}
}
void resetB()
{
  digitalWrite(b7,LOW);
  digitalWrite(b6,LOW);
  digitalWrite(b5,LOW);
  digitalWrite(b4,LOW);
  digitalWrite(b3,LOW);
  digitalWrite(b2,LOW);
  digitalWrite(b1,LOW);
  digitalWrite(b0,LOW);
}
void loop() 
{
  unsigned char i;
  for (i = 0; i < tasksNum; ++i) {
    if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elapsedTime = millis(); // Last time this task was ran
    }
  }
  delay(500);
}

void TickFct_BlinkLed()
{
  /*
  switch(theStates){ // Transition States
    
    case bl_start:   //Go to release state
      theStates = release;
    break;
    
    default:
      break;
  }
  switch(theStates){ // Action States
    case bl_start:
      break;
    case release:
          writeToB(1);
          delay(100);
          writeToB(2);
          delay(100);
          writeToB(4);
          delay(100);
          writeToB(8);
          delay(100);
          writeToB(16);
          delay(100);
          writeToB(32);
          delay(100);
          writeToB(64);
          delay(100);
          writeToB(128);
          delay(100);       
    break;
    default:
      break;
  }*/
}
