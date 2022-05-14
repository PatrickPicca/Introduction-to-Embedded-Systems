/* William Picca wpicc001@ucr.edu
 * Lab Section: 001
 * Assignment: Lab #2 Exercise #4
 * Exercise Description:
 *
 * I acknowledge all content contained herein, excluding
 * template or example code, is my own original work.
 *
 * Demo Link: https://youtu.be/z1JSxJpS6uQ
 */


#define GREEN 2
#define RED 3

enum States {OFF, LeftOn, RightOn, BothOff} state;

void setup() 
{

  // LED Setup
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  digitalWrite(GREEN, LOW);
  digitalWrite(RED, LOW);
  
  // BUTTON SETUP
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);

}

void loop() 
{
  Tick();
  delay(500);
}

void Tick()
{
  switch(state){ // Transition States
    case LeftOn:
      if(digitalRead(A0) == HIGH)
      {
        state = OFF;
      }
    break;
    case RightOn:
      if(digitalRead(A1) == HIGH)
      {
        state = OFF;
      }
    break;
    case BothOff:
      if(digitalRead(A0) == HIGH && digitalRead(A1) == HIGH)
      {
        state = OFF;
      }
    break;
    case OFF:
      if(digitalRead(A0) == LOW && digitalRead(A1) == HIGH)
      {
        state = RightOn; 
      }
      if(digitalRead(A0) == HIGH && digitalRead(A1) == LOW)
      {
        state = LeftOn; 
      }
      if(digitalRead(A0) == LOW && digitalRead(A1) == LOW)
      {
        state = BothOff; 
      }
    break;

    default:
      break;
  }


  switch(state){ // Action States
    case LeftOn:
      digitalWrite(GREEN, HIGH);
      digitalWrite(RED, LOW);
      break;
    case RightOn:
      digitalWrite(GREEN, LOW);
      digitalWrite(RED, HIGH);
      break;
    case BothOff:
      digitalWrite(GREEN, LOW);
      digitalWrite(RED, LOW);
      break;
    case OFF:
      digitalWrite(GREEN, LOW);
      digitalWrite(RED, LOW);
      break;

    default:
      break;
  }
}
