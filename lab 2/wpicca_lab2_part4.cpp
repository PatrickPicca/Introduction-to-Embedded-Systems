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


#define GREEN 5
#define A 2

enum States {OFF, ON} state;

void setup() 
{

  // LED Setup
  pinMode(GREEN, OUTPUT);
  digitalWrite(GREEN, LOW);
  
  // BUTTON SETUP
  pinMode(A, INPUT_PULLUP);

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
      if(digitalRead(A) == HIGH)
      {
        state = OFF;
      }
    break;

    case OFF:
      if(digitalRead(A) == LOW)
      {
        state = ON;
      }    
    break;

    default:
      break;
  }


  switch(state){ // Action States
    case ON:
      digitalWrite(GREEN, HIGH);
      break;

    case OFF:
      digitalWrite(GREEN, LOW);
      break;

    default:
      break;
  }
}
