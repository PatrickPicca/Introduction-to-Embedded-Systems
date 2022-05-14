/* William Picca wpicc001@ucr.edu
 * Lab Section: 001
 * Assignment: Lab #5 Exercise #2
 * Exercise Description:
 *
 * I acknowledge all content contained herein, excluding
 * template or example code, is my own original work.
 *
 * Demo Link: https://youtu.be/4t26hLKw6NA
 */

#include <Servo.h>

// C++ code
//
Servo theServo;
int val;

enum States {start} state;

void setup()
{
  Serial.begin(9600);
  
  
  theServo.attach(3);
  state = start;
}

void loop()
{
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
      val = analogRead(A0);          //Read and save analog value from potentiometer
      val = map(val, 0, 1023, 0, 180); //Map value 0-1023 to 0-255 (PWM)
      Serial.println(val);
    
      theServo.write(val);
    
    break;

    default:
      break;
  }
}
