/* William Picca wpicc001@ucr.edu
 * Lab Section: 001
 * Assignment: Lab #2 Exercise #2
 * Exercise Description:
 *
 * I acknowledge all content contained herein, excluding
 * template or example code, is my own original work.
 *
 * Demo Link: https://youtu.be/2RhNXmyEEtQ
 */


// C++ code
//
const int b0 = 2;
const int b1 = 3;
int a = 0x00;
int a0, a1, a2, a3;
void setup()
{
  pinMode(b0, OUTPUT);
  pinMode(b1, OUTPUT);
  Serial.begin(9600);
}

void readData()
{
  if(Serial.available()){
    a = Serial.parseInt();
  }
  a3 = (a >> 3) & 0x01;
  a2 = (a >> 2) & 0x01;
  a1 = (a >> 1) & 0x01;
  a0 = (a >> 0) & 0x01;
}

void resetB()
{
  digitalWrite(b1,LOW);
  digitalWrite(b0,LOW);
}

void writeToB(unsigned char temp)
{
  if ((temp>>1) & 0x01){digitalWrite(b1,HIGH);}
  if (temp & 0x01){digitalWrite(b0,HIGH);}
}

void loop()
{
  readData();
  resetB();
  // write code here
  
  if (a1 == a3 && a0 == a2)
  {
    digitalWrite(b1,HIGH);
    digitalWrite(b0,HIGH);
  }
  if (a1 > a3 || (a1 == a3 && a0 > a2)) //Leading bit a1 is greater than leading bit a3,
                      //or they are the same and the next bit a0 is 
                      //greater than a2
  {
  digitalWrite(b1,LOW);
    digitalWrite(b0,HIGH);
  }
  if (a3 > a1 || (a1 == a3 && a2 > a0))
  {
    digitalWrite(b1,HIGH);
  digitalWrite(b0,LOW);
  }
  
  delay(200);
}
