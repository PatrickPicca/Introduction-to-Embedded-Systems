/* William Picca wpicc001@ucr.edu
 * Lab Section: 001
 * Assignment: Lab #4 Exercise #4
 * Exercise Description: 
 *
 * I acknowledge all content contained herein, excluding
 * template or example code, is my own original work.
 *
 * Demo Link: https://youtu.be/dp7LG3E508Q 
 */

#include <stdlib.h>
#include <time.h>

// srand(time(NULL));

const int b0 = 2;
const int b1 = 3;
const int b2 = 4;
const int b3 = 5;
const int b4 = 6;
int timer = rand() % 4;
int count;    //Keeps track of the 1000ms timer to select a new LED to make bright.
int counting = 0; //Keeps track of the 500ms time limit to press the correct button.
bool next;

enum States {before, start, lost, chosenstate, play} state;

void setup() 
{
  state = before;
  next = false;
  
  // LED Setup
  pinMode(b0, OUTPUT);
  digitalWrite(b4,LOW);
  pinMode(b1, OUTPUT);
  digitalWrite(b4,LOW);
  pinMode(b2, OUTPUT);
  digitalWrite(b4,LOW);
  pinMode(b3, OUTPUT);
  digitalWrite(b4,LOW);
  pinMode(b4, OUTPUT);
  digitalWrite(b4,LOW);

  // BUTTON SETUP
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  
  // generating();
  count = 0;
}
void resetB()
{
  digitalWrite(b0,LOW);
  digitalWrite(b1,LOW);
  digitalWrite(b2,LOW);
  digitalWrite(b3,LOW);
}
void loop() 
{
  Tick();
  delay(100);
}
void generating()
{
       timer = rand() % 5; //Random() call to generate 1 of 4 LEDs to make bright.
       if (timer == 0)
       {
          resetB();
            digitalWrite(b0,HIGH);  
       }
       else if (timer == 1)
       {
          resetB();
            digitalWrite(b1,HIGH);  
       }
       else if (timer == 2)
       {
          resetB();
            digitalWrite(b2,HIGH);  
       }
       else if (timer == 3)
       {
          resetB();
            digitalWrite(b3,HIGH);  
       }
}

void Tick()
{
  switch(state){ // Transition States
    
    case before:   //Continues to generate randomly until user hits currently lit button.
      if((digitalRead(A0) == HIGH && timer == 0)
           || (digitalRead(A1) == HIGH && timer == 1) 
           || (digitalRead(A2) == HIGH && timer == 2)
           || (digitalRead(A3) == HIGH && timer == 3))
        {
          state = chosenstate;
        }
      else 
        {
          state = before;
        }
    break;
    
    
    
    
    
    case start: 
      state = play;
    break;
    
    
    case play: 
      counting ++;
      if((digitalRead(A0) == HIGH && timer == 0)
           || (digitalRead(A1) == HIGH && timer == 1) 
           || (digitalRead(A2) == HIGH && timer == 2)
           || (digitalRead(A3) == HIGH && timer == 3))
        {
          state = chosenstate;
          counting = 0;
        }
      else
          state = play;
        
      if (counting > 10)
          state = lost;
    break;
    
    case chosenstate:
      state = play;
    break;
    
    default:
      break;
  }

//start, lost, chosenstate, random
  switch(state){ // Action States
    
    case before:
      count ++;
      if (count == 10) //Every 10 ticks, generate new LED.
      {
         count = 0;
         generating();
        }
      break; 
    case start:   
      break;
    case lost:
        resetB();
      digitalWrite(b4,HIGH);
      break;

    case chosenstate:
      break;
    
    
    case play:
         if (digitalRead(A0) == HIGH && timer == 0)
         {
               resetB();
              digitalWrite(b1,HIGH);  
              timer = 1;
         }
         else if (digitalRead(A1) == HIGH && timer == 1)
         {
               resetB();
              digitalWrite(b2,HIGH);
            timer = 2;
         }
         else if (digitalRead(A2) == HIGH && timer == 2)
         {
              resetB();
              digitalWrite(b3,HIGH);
            timer = 3;
         }
         else if (digitalRead(A3) == HIGH && timer == 3)
         {
              resetB();
              digitalWrite(b0,HIGH);  
            timer = 0;
         }    
      break;

    default:
      break;
  }
}
