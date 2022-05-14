/* William Picca wpicc001@ucr.edu
 * Lab Section: 001
 * Assignment: Lab #3 Exercise #1
 * Exercise Description:
 *
 * I acknowledge all content contained herein, excluding
 * template or example code, is my own original work.
 *
 * Demo Link: https://youtu.be/FlLVWckP-mM 
 */


const int b0 = 5;
const int b1 = 6;

enum States {OFF, ON, OnPress, OffPress} state;

void setup() 
{

  state = ON;
  
  // LED Setup
  pinMode(b0, OUTPUT);
  digitalWrite(b0, HIGH);
  
  pinMode(b1, OUTPUT);
  digitalWrite(b1, LOW);
  
  // BUTTON SETUP
  pinMode(A0, INPUT_PULLUP);

}

void loop() 
{
  Tick();
  delay(500);
}

void Tick()
{
  switch(state){ // Transition States
    case ON:
      if(digitalRead(A0) == HIGH)
      {
        state = OnPress;
      }
    break;
    case OnPress:
      if(digitalRead(A0) != HIGH)
      {
        state = OFF;
      }
    break;
    case OFF:
      if(digitalRead(A0) == HIGH)
      {
        state = OffPress;
      }    
    break;
    case OffPress:
      if(digitalRead(A0) != HIGH)
      {
        state = ON;
      }
    break;
    

    default:
      break;
  }


  switch(state){ // Action States
    case ON:
        digitalWrite(b0, HIGH);
      digitalWrite(b1, LOW);
      break;

    case OFF:
        digitalWrite(b0, LOW);
      digitalWrite(b1, HIGH);
      break;

    default:
      break;
  }
}
