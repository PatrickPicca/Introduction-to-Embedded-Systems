/* William Picca wpicc001@ucr.edu
 * Lab Section: 001
 * Assignment: Lab #2 Exercise #1
 * Exercise Description:
 *
 * I acknowledge all content contained herein, excluding
 * template or example code, is my own original work.
 *
 * Demo Link: https://youtu.be/z1JSxJpS6uQ
 */

// C++ code
//
const int b0 = 2;
int a = 0x00;
int a0;
void setup()
{
  pinMode(b0, OUTPUT);
  Serial.begin(9600);
}

void readData()
{
  if(Serial.available()){
    a = Serial.parseInt();
  }
  a0 = (a >> 0) & 0x01;
}

void resetB()
{
  digitalWrite(b0,LOW);
}

void writeToB(unsigned char temp)
{
  if (temp & 0x01){digitalWrite(b0,HIGH);}
}

void loop()
{
  readData();
  // write code here
  
  if (a0)
    digitalWrite(b0,HIGH);
  if (!a0)
    digitalWrite(b0,LOW);
  
  delay(200);
}
