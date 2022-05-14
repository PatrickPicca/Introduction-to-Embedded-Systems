/* William Picca wpicc001@ucr.edu
 * Lab Section: 001
 * Assignment: Lab #3 Exercise #4
 * Exercise Description:
 *
 * I acknowledge all content contained herein, excluding
 * template or example code, is my own original work.
 *
 * Demo Link: https://youtu.be/IkSiD2zh5A4  
 */


const int b2 = 4;
int count;
bool next;

enum States {start, LOCKED, FIRST, UNLOCKED, release} state;

void setup() 
{

  state = start;
  count = 1;
  next = false;
  
  // LED Setup
  pinMode(b2, OUTPUT);
  digitalWrite(b2,LOW);

  
  // BUTTON SETUP
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  

}
void resetB()
{
  digitalWrite(b2,LOW);
}
void loop() 
{
  
  Tick();
  
  delay(100);
  
}

void Tick()
{
  switch(state){ // Transition States
    
    case start:   //Start in first count pattern in release.
      state = release;
    break;
    
    case UNLOCKED: 
      if(digitalRead(A0) == LOW && digitalRead(A1) == LOW && digitalRead(A2) == LOW && digitalRead(A3) == HIGH)
      {
        state = LOCKED;
      }    
      else  
      {
        state = UNLOCKED;
      }
    break;
    
    case LOCKED: 
      state = release;
    break;
    
    case FIRST:
      if (digitalRead(A0) == LOW && digitalRead(A1) == LOW && digitalRead(A2) == LOW && digitalRead(A3) == LOW)
      {
         next = false; 
      }
      if (next == true) //Waits for user to let go of button that brought SM to this state.
      {
        
      }
      else
      {
        next = false;
    if(digitalRead(A1) == HIGH)
        {

          state = UNLOCKED;
        }   
        else if (digitalRead(A0) == HIGH || digitalRead(A2) == HIGH)
        {
          state = release;
        }
        else
        {
          state = FIRST;
        }
      }
    
      
    break;
  case release:
      if(digitalRead(A0) == LOW && digitalRead(A1) == LOW && digitalRead(A2) == HIGH && digitalRead(A3) == LOW)   
      {
        state = FIRST;
        next = true;
      }
      else
      {
        
        state = release;
      }
    break;
    
    default:
      break;
  }


  switch(state){ // Action States
    case start:
        
      break;
    case release:
        
      break;

    case LOCKED:
      digitalWrite(b2,LOW);
      break;
    case FIRST:
      break;
    case UNLOCKED:
      digitalWrite(b2,HIGH);
      break;
    
    break;

    default:
      break;
  }
}
