/* William Picca wpicc001@ucr.edu
 * Lab Section: 001
 * Assignment: Lab #5 Exercise #4
 * Exercise Description:
 *
 * I acknowledge all content contained herein, excluding
 * template or example code, is my own original work.
 *
 * Demo Link: https://youtu.be/OelhBE0eD8Q 
 */

#include <Servo.h>

// C++ code
//
const int b0 = 2;
int val;
int max;
int min;

enum States {start, on, off} state;

void setup()
{
  pinMode(b0, OUTPUT);
  
  pinMode(A0, INPUT);
  state = start;
  
  max = 40;
  
  
  Serial.begin(9600);
}

void resetB()
{
  digitalWrite(b0,LOW);
}

void writeToB(unsigned char temp)
{
  resetB();

  if (temp & 0x01){digitalWrite(b0,HIGH);}
}

void loop()
{
  resetB();
  // write code here
  
  Tick();
  delay(100);                          //Small delay
  
}


void Tick()
{
  switch(state){ // Transition States
    
    case start:
      state = off;
    break;
    case on:
      if (val >= max)
          state = on;
      else
          state = off;
    break;
    case off:
      if (val >= max)
          state = on;
      else
          state = off;
    break;
    default:
      break;
  }
//123

  switch(state){ // Action States

    case start:
      val = analogRead(A0);          //Read and save analog value from potentiometer
      val = map(val, 0, 1023, 0, 128); //Map value 0-1023 to 0-255 (PWM)
      Serial.println(val);
      writeToB(val);
    break;
    case on:
      val = analogRead(A0);          //Read and save analog value from potentiometer
      val = map(val, 0, 1023, 0, 128); //Map value 0-1023 to 0-255 (PWM)
      Serial.println(val);
      writeToB(val);
    
      digitalWrite(b0,HIGH);
    
    break;
    case off:
      val = analogRead(A0);          //Read and save analog value from potentiometer
      val = map(val, 0, 1023, 0, 128); //Map value 0-1023 to 0-255 (PWM)
      Serial.println(val);
      writeToB(val);
    
    
      digitalWrite(b0,LOW);
    break;

    default:
      break;
  }
}
