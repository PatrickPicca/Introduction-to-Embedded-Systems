/* William Picca wpicc001@ucr.edu
 * Lab Section: 001
 * Assignment: Lab #3 Exercise #3
 * Exercise Description:
 *
 * I acknowledge all content contained herein, excluding
 * template or example code, is my own original work.
 *
 * Demo Link: https://youtu.be/m917uCbuQFQ 
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
int a = 0x00;
int a0, a1, a2, a3, a4, a5, a6, a7;

enum States {start, release, UPpress, DOWNpress, BOTHpress} state;

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
  
  pinMode(A1, INPUT_PULLUP);
  
  a = 7;


}
void readData()
{
  if(Serial.available()){
    a = Serial.parseInt();
  }
  a7 = a >> 7;
  a6 = (a >> 6) & 0x01;
  a5 = (a >> 5) & 0x01;
  a4 = (a >> 4) & 0x01;
  a3 = (a >> 3) & 0x01;
  a2 = (a >> 2) & 0x01;
  a1 = (a >> 1) & 0x01;
  a0 = (a >> 0) & 0x01;
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
  
  delay(100);
  
  resetB();
}

void Tick()
{
  switch(state){ // Transition States
    
    case start:   //Start in first count pattern in release.
      writeToB(a);
      state = release;
    break;
    
    case UPpress: 
      if(digitalRead(A0) == HIGH)   //If up button is still pressed stay pressed
      {
        state = UPpress;
      }    
      else if (digitalRead(A0) == LOW)   //If up button is released go to release.
      {
        next = false;
        state = release;
      }
    break;
    case DOWNpress: 
      if(digitalRead(A1) == HIGH)   //If down button is still pressed stay pressed
      {
        state = DOWNpress;
      }    
      else if (digitalRead(A1) == LOW)   //If down button is released go to release.
      {
        next = false;
        state = release;
      }
    break;
    case BOTHpress: 
      if(digitalRead(A1) == HIGH || digitalRead(A0) == HIGH )   //If down button is still pressed stay pressed
      {
        state = BOTHpress;
      }    
      else if (digitalRead(A1) == LOW && digitalRead(A0) == LOW)   //If down button is released go to release.
      {
        next = false;
        state = release;
      }
    break;
  case release:
      if(digitalRead(A0) == HIGH && digitalRead(A1) == HIGH)   //If both button has been pressed go to pressed.
      {
        state = BOTHpress;
      }
      else if(digitalRead(A0) == HIGH)   //If up button has been pressed go to pressed.
      {
        state = UPpress;
      }
      else if(digitalRead(A1) == HIGH)   //If up button has been pressed go to pressed.
      {
        state = DOWNpress;
      }
      else if (digitalRead(A0) == LOW && digitalRead(A1) == LOW)   //If button stays not pressed go to release.
        state = release;
    break;
    
    default:
      break;
  }


  switch(state){ // Action States
    case start:
        
      break;

    case UPpress:
      if (next == false)
        {
          next = true;
          if (a < 10)
            a++;
        }
      writeToB(a);
      break;
    case DOWNpress:
      if (next == false)
        {
          next = true;
          if (a > 0)
            a--;
        }
      writeToB(a);
      break;
    case BOTHpress:
      if (next == false)
        a = 0;
      writeToB(a);
      break;
    
    case release:
      writeToB(a);
    break;

    default:
      break;
  }
}
