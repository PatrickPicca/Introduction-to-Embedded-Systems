/* William Picca wpicc001@ucr.edu
 * Lab Section: 001
 * Assignment: Lab #4 Exercise #2
 * Exercise Description:
 *
 * I acknowledge all content contained herein, excluding
 * template or example code, is my own original work.
 *
 * Demo Link: https://youtu.be/b_tu6-bxWO8 
 */


const int b2 = 5;
const int b3 = 6;
const int b4 = 7;
bool pressed;

enum States {start, led1, led2, led3, pausepress, pauserelease} state;

void setup() 
{

  state = start;
  
  // LED Setup
  pinMode(b2, OUTPUT);
  digitalWrite(b2, LOW);
  
  pinMode(b3, OUTPUT);
  digitalWrite(b3, LOW);
  
  pinMode(b4, OUTPUT);
  digitalWrite(b4, LOW);
  
  // BUTTON SETUP
  pinMode(A0, INPUT_PULLUP);
  
  
  pressed = false;

}

void loop() 
{
  Tick();
  delay(300);
}

void Tick()
{
  switch(state){ // Transition States
    
    case start:
      state = led1;
    break;
    case led1:
        state = led2;
      if(digitalRead(A0) == HIGH)
            state = pausepress;
    break;
    case led2:
      state = led3;
      if(digitalRead(A0) == HIGH)
            state = pausepress;
    break;
    case led3:
      state = led1;
      if(digitalRead(A0) == HIGH)
            state = pausepress;
    break;
    case pausepress:
      if(digitalRead(A0) == LOW)
            state = pauserelease;
    break;
    case pauserelease:
      if(digitalRead(A0) == HIGH)
            state = start;
    break;


    default:
      break;
  }


  switch(state){ // Action States
    case led1:
        digitalWrite(b2, LOW);
      digitalWrite(b3, LOW);
      digitalWrite(b4, HIGH);
      break;
    case led2:
        digitalWrite(b2, LOW);
      digitalWrite(b3, HIGH);
      digitalWrite(b4, LOW);
      break;
    case led3:
        digitalWrite(b2, HIGH);
      digitalWrite(b3, LOW);
      digitalWrite(b4, LOW);
      break;
    case pausepress:
      break;
    case pauserelease:
      break;

    default:
      break;
  }
}
