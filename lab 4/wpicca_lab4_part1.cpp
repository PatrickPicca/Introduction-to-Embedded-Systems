/* William Picca wpicc001@ucr.edu
 * Lab Section: 001
 * Assignment: Lab #4 Exercise #1
 * Exercise Description:
 *
 * I acknowledge all content contained herein, excluding
 * template or example code, is my own original work.
 *
 * Demo Link: https://youtu.be/mzlUp9ZjcKw  
 */


const int b0 = 5;
const int b1 = 6;
const int b2 = 7;

enum States {start, led1, led2, led3, pause} state;

void setup() 
{

  state = start;
  
  // LED Setup
  pinMode(b0, OUTPUT);
  digitalWrite(b0, LOW);
  
  pinMode(b1, OUTPUT);
  digitalWrite(b1, LOW);
  
  pinMode(b1, OUTPUT);
  digitalWrite(b2, LOW);
  
  
}

void loop() 
{
  Tick();
  delay(1000);
}

void Tick()
{
  switch(state){ // Transition States
    
    case start:
      state = led1;
    break;
    case led1:
      state = led2;
    break;
    case led2:
      state = led3;
    break;
    case led3:
      state = led1;
    break;


    default:
      break;
  }


  switch(state){ // Action States
    case led1:
        digitalWrite(b0, LOW);
      digitalWrite(b1, LOW);
      digitalWrite(b2, HIGH);
      break;
    case led2:
        digitalWrite(b0, LOW);
      digitalWrite(b1, HIGH);
      digitalWrite(b2, LOW);
      break;
    case led3:
        digitalWrite(b0, HIGH);
      digitalWrite(b1, LOW);
      digitalWrite(b2, LOW);
      break;

    default:
      break;
  }
}
