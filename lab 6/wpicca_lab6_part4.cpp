/* William Picca wpicc001@ucr.edu
 * Lab Section: 001
 * Assignment: Lab #6 Exercise #4
 * Exercise Description:
 *
 * I acknowledge all content contained herein, excluding
 * template or example code, is my own original work.
 *
 * Demo Link: https://youtu.be/S1GXzucmDms
 */

#include <Servo.h>

// C++ code
//

Servo theServo;
int val;
bool first;
bool second;
bool third;
bool fourth;
int max;
int light;
const int b0 = 2;

typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);
} task;

const unsigned short tasksNum = 2;
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
          fourth = false;
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
        if (third == true && fourth == false && digitalRead(A3) == HIGH)
        {
          fourth = true;   
        //  state = rotatingUnlocked;  
          Serial.println("set fourth to true!");
        }
      if  (fourth == true && digitalRead(A4) == HIGH)
        {
          state = rotatingUnlocked;  
        Serial.println("Unlocked!");
          first = false;   
          second = false;   
          third = false; 
          fourth = false;
        }
          
    break;
    case unlocked:
      if (digitalRead(A0) == HIGH)
        {
       //   state = rotatingUnlocked;
          first = true;   
          second = false;
          third = false; 
          fourth = false;
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
        if (third == true && fourth == false && digitalRead(A3) == HIGH)
        {
          fourth = true;   
        //  state = rotatingUnlocked;  
          Serial.println("set fourth to true!");
        }
      if  (fourth == true && digitalRead(A4) == HIGH)
        {
          state = rotatingLock;  
        Serial.println("Unlocked!");
          first = false;   
          second = false;   
          third = false; 
          fourth = false;
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

enum theLight { lightStart, lightOn, lightOff };
int TickFct_light(int state) 
{ 
  switch(state){ // Transition States
    
    case lightStart:
      state = lightOff;
    break;
    case lightOn:
      if (light >= max)
          state = lightOff;
      else
          state = lightOn;
    break;
    case lightOff:
      if (light >= max)
          state = lightOff;
      else
          state = lightOn;
    break;
    default:
      break;
  }

  switch(state){ // Action States

    case lightStart:
      light = analogRead(A5);          //Read and save analog value from potentiometer
      light = map(light, 0, 1023, 0, 128); //Map value 0-1023 to 0-255 (PWM)
    break;
    case lightOn:
      light = analogRead(A5);          //Read and save analog value from potentiometer
      light = map(light, 0, 1023, 0, 128); //Map value 0-1023 to 0-255 (PWM)
      digitalWrite(b0,HIGH);
    
    break;
    case lightOff:
      light = analogRead(A5);          //Read and save analog value from potentiometer
      light = map(light, 0, 1023, 0, 128); //Map value 0-1023 to 0-255 (PWM)
    
      digitalWrite(b0,LOW);
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
  pinMode(A4, INPUT_PULLUP);
  
  //Photoresistor
  pinMode(A0, INPUT);
  
  //LED
  pinMode(b0, OUTPUT);
  
  unsigned char i = 0;
  tasks[i].state = locked;
  tasks[i].period = 100;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &TickFct_deadbolt;
  i++;
  tasks[i].state = lightStart;
  tasks[i].period = 100;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &TickFct_light;
  
  first = false;
  second = false;
  third = false;
  fourth = false;
  val = 180;
  theServo.write(val);
  max = 40;
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
