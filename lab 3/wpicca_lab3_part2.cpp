/* William Picca wpicc001@ucr.edu
 * Lab Section: 001
 * Assignment: Lab #3 Exercise #2
 * Exercise Description:
 *
 * I acknowledge all content contained herein, excluding
 * template or example code, is my own original work.
 *
 * Demo Link: https://youtu.be/61qWvVKORBA 
 */


const int b0 = 2;
const int b1 = 3;
const int b2 = 4;
const int b3 = 5;
const int b4 = 6;
const int b5 = 7;
const int b6 = 8;
const int b7 = 9;
int count;
bool next;

enum States {start, release, press} state;

void setup() 
{

  state = start;
  count = 1;
  next = false;
  
  // LED Setup
  pinMode(b0, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(b3, OUTPUT);
  pinMode(b4, OUTPUT);
  pinMode(b5, OUTPUT);
  pinMode(b6, OUTPUT);
  pinMode(b7, OUTPUT);

  
  // BUTTON SETUP
  pinMode(A0, INPUT_PULLUP);

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
void loop() 
{
  
  Tick();
  resetB();
  delay(100);
}

void Tick()
{
  switch(state){ // Transition States
    
    case start:   //Start in first count pattern in release.
      state = release;
    break;
    
    case press: 
      if(digitalRead(A0) == HIGH)   //If button is still pressed stay pressed
      {
        state = press;
      }    
      else if (digitalRead(A0) == LOW)   //If button is released go to release.
      {
        next = false;
        state = release;
      }
    break;
    
  case release:
      if(digitalRead(A0) == HIGH)   //If button has been pressed go to pressed.
      {
        state = press;
      }
      else if (digitalRead(A0) == LOW)   //If button stays not pressed go to release.
        state = release;
    break;
    
    default:
      break;
  }


  switch(state){ // Action States
    case start:
        
      break;

    case press:
      if (next == false)
        {
          next = true;
          if (count == 5)
            count = 1;
          else
            count ++;
        }
    
      break;
    
    case release:
      if (count == 1)
        {
          writeToB(1);
          delay(100);
          writeToB(2);
          delay(100);
          writeToB(4);
          delay(100);
          writeToB(8);
          delay(100);
          writeToB(16);
          delay(100);
          writeToB(32);
          delay(100);
          writeToB(64);
          delay(100);
          writeToB(128);
          delay(100);
        }        

      if (count == 2)
        {
          
          writeToB(2);
          delay(200);
          writeToB(8);
          delay(200);
          writeToB(32);
          delay(200);
          writeToB(128);
          delay(200);
        }
      if (count == 3)
        {
          writeToB(128);
          delay(100);
          writeToB(64);
          delay(100);
          writeToB(32);
          delay(100);
          writeToB(16);
          delay(100);
          writeToB(8);
          delay(100);
          writeToB(4);
          delay(100);
          writeToB(2);
          delay(100);
          writeToB(1);
          delay(100);
        }
      if (count == 4)
        {
          
          writeToB(64);
          delay(200);
          writeToB(16);
          delay(200);
          writeToB(4);
          delay(200);
          writeToB(1);
          delay(200);
        }
      if (count == 5)
        {
          writeToB(1);
          delay(100);
          writeToB(128);
          delay(100);
          writeToB(2);
          delay(100);
          writeToB(64);
          delay(100);
          writeToB(4);
          delay(100);
          writeToB(32);
          delay(100);
          writeToB(8);
          delay(100);
          writeToB(16);
          delay(100);
        }
    break;

    default:
      break;
  }
}
