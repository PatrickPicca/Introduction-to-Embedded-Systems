/* William Picca wpicc001@ucr.edu
 * Lab Section: 001
 * Assignment: Lab #1 Exercise #3
 * Exercise Description:
 *
 * I acknowledge all content contained herein, excluding
 * template or example code, is my own original work.
 *
 * Demo Link: https://youtu.be/2cF63CdMUAw 
 */


// C++ code
//
const int b0 = 2;
const int b1 = 3;
const int b2 = 4;
const int b3 = 5;
const int b4 = 6;
const int b5 = 7;
const int b6 = 8;
const int b7 = 9;
int a = 0x00;
int a0, a1, a2, a3, a4, a5, a6, a7;
void setup()
{
  pinMode(b0, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(b3, OUTPUT);
  pinMode(b4, OUTPUT);
  pinMode(b5, OUTPUT);
  pinMode(b6, OUTPUT);
  pinMode(b7, OUTPUT);
  Serial.begin(9600);
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

void writeToB(unsigned char temp)
{
  if ((temp>>7) & 0x01){digitalWrite(b7,HIGH);}
  if ((temp>>6) & 0x01){digitalWrite(b6,HIGH);}
  if ((temp>>5) & 0x01){digitalWrite(b5,HIGH);}
  if ((temp>>4) & 0x01){digitalWrite(b4,HIGH);}
  if ((temp>>3) & 0x01){digitalWrite(b3,HIGH);}
  if ((temp>>2) & 0x01){digitalWrite(b2,HIGH);}
  if ((temp>>1) & 0x01){digitalWrite(b1,HIGH);}
  if (temp & 0x01){digitalWrite(b0,HIGH);}
}

void loop()
{
  readData();
  resetB();
  // write code here
  

  digitalWrite(b0,HIGH);
  digitalWrite(b7,LOW);
  delay(100);
  digitalWrite(b1,HIGH);
  digitalWrite(b0,LOW);
  delay(100);
  digitalWrite(b2,HIGH);
  digitalWrite(b1,LOW);
  delay(100);
  digitalWrite(b3,HIGH);
  digitalWrite(b2,LOW);
  delay(100);
  digitalWrite(b4,HIGH);
  digitalWrite(b3,LOW);
  delay(100);
  digitalWrite(b5,HIGH);
  digitalWrite(b4,LOW);
  delay(100);
  digitalWrite(b6,HIGH);
  digitalWrite(b5,LOW);
  delay(100);
  digitalWrite(b7,HIGH);
  digitalWrite(b6,LOW);
  delay(100);

  
  delay(200);
}
