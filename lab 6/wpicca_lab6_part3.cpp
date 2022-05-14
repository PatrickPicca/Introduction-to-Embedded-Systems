/* William Picca wpicc001@ucr.edu
 * Lab Section: 001
 * Assignment: Lab #6 Exercise #3
 * Exercise Description:
 *
 * I acknowledge all content contained herein, excluding
 * template or example code, is my own original work.
 *
 * Demo Link: https://youtu.be/y17oagYd9ys 
 */

#include <Servo.h>

// C++ code
//

Servo theServo;
int val;
bool first;
bool second;
bool third;

typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);
} task;

const unsigned short tasksNum = 1;
task tasks[tasksNum];


enum theStates { locked, unlocked, rotatingLock, rotatingUnlocked };
int TickFct_deadbolt(int state) 
{ 
  switch(state){ // Transition States
    
    case locked:
    //  state = rotatingUnlocked;
    
      if (digitalRead(A0) == HIGH)
        {
       //   state = rotatingUnlocked;
          first = true;   
          second = false;
          third = false;
        Serial.println("First input!");
        }
      if (first == true && second == false && digitalRead(A1) == HIGH)
        {
       //   state = rotatingUnlocked;
          second = true;     
        Serial.println("Second input!");
        }
          
      if (first == true && second == true && third == false && digitalRead(A2) == HIGH)
        {
       //   state = rotatingUnlocked;
          third = true;     
        Serial.println("Third input!");
        }
      else if (third == true && digitalRead(A1) == HIGH)
        {
          
        }
        if (third == true && digitalRead(A3) == HIGH)
        {
          state = rotatingUnlocked;  
        Serial.println("Unlocked!");
          first = false;   
          second = false;   
          third = false;   
        }
      else if (third == false && digitalRead(A3) == HIGH)
        {
          first = false;   
          second = false;   
          third = false;  
        }
          
    break;
    case unlocked:
      if (digitalRead(A0) == HIGH)
        {
       //   state = rotatingUnlocked;
          first = true;   
          second = false;
          third = false;
        Serial.println("First input!");
        }
      if (first == true && second == false && digitalRead(A1) == HIGH)
        {
       //   state = rotatingUnlocked;
          second = true;     
        Serial.println("Second input!");
        }
          
      if (first == true && second == true && third == false && digitalRead(A2) == HIGH)
        {
       //   state = rotatingUnlocked;
          third = true;     
        Serial.println("Third input!");
        }
      else if (third == true && digitalRead(A1) == HIGH)
        {
          
        }
        if (third == true && digitalRead(A3) == HIGH)
        {
          state = rotatingLock;  
        Serial.println("Locked!");
          first = false;   
          second = false;   
          third = false;   
        }
      else if (third == false && digitalRead(A3) == HIGH)
        {
          first = false;   
          second = false;   
          third = false;  
        }
    break;
    case rotatingLock:
      if (val == 180)
          state = locked;
    break;
    case rotatingUnlocked:
      if (val == 0)
          state = unlocked;
    break;
    default:
      break;
  }


  switch(state){ // Action States

    case locked:
      
    break;
    case unlocked:
      
    break;
    case rotatingLock:
    if (val < 180)
          val+= 10;
      Serial.println(val);
      theServo.write(val);
    break;
    case rotatingUnlocked:
      if (val > 0)
          val-= 10;
        
        Serial.println(val);
        theServo.write(val);
    break;
    default:
      break;
  }
  
  return state;
}

void setup()
{
  Serial.begin(9600);
  
  theServo.attach(3);
  // BUTTON SETUP
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  
  unsigned char i = 0;
  tasks[i].state = locked;
  tasks[i].period = 100;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &TickFct_deadbolt;
  
  first = false;
  second = false;
  third = false;
  val = 180;
  theServo.write(val);
}

void loop()
{
  // write code here
  unsigned char i;
  for (i = 0; i < tasksNum; ++i) {
    if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elapsedTime = millis(); // Last time this task was ran
    }
  }
  delay(100);
}
