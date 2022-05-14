/* William Picca wpicc001@ucr.edu
 * Lab Section: 001
 * Assignment: Lab #5 Exercise #1
 * Exercise Description:
 *
 * I acknowledge all content contained herein, excluding
 * template or example code, is my own original work.
 *
 * Demo Link: https://youtu.be/DfqIy2a4iZw
 */

#include <Servo.h>

// C++ code
//
const int b0 = 2;
const int b1 = 3;
const int b2 = 4;
const int b3 = 5;
const int b4 = 6;
const int b5 = 7;
const int b6 = 8;
const int b7 = 9;
Servo theServo;
int val;

enum States {start} state;

void setup()
{
  pinMode(b0, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(b3, OUTPUT);
  pinMode(b4, OUTPUT);
  pinMode(b5, OUTPUT);
  pinMode(b6, OUTPUT);
  pinMode(b7, OUTPUT);
  Serial.begin(9600);
  
  
  theServo.attach(10);
  state = start;
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
    break;
    default:
      break;
  }


  switch(state){ // Action States

    case start:
      val = analogRead(A1);          //Read and save analog value from potentiometer
      val = map(val, 0, 1023, 0, 128); //Map value 0-1023 to 0-255 (PWM)
      Serial.println(val);
      writeToB(val);
    break;

    default:
      break;
  }
}
