/* William Picca wpicc001@ucr.edu
 * Lab Section: 001
 * Assignment: Lab #2 Exercise #6
 * Exercise Description:
 *
 * I acknowledge all content contained herein, excluding
 * template or example code, is my own original work.
 *
 * Demo Link: https://youtu.be/z1JSxJpS6uQ
 */


#define GREEN 8

const int b0 = 2;
const int b1 = 3;
const int b2 = 4;
const int b3 = 5;
const int b4 = 6;
const int b5 = 7;
int a = 0x00;
int a0, a1, a2, a3, a4, a5, a6;

void setup() 
{

  // LED Setup
  pinMode(GREEN, OUTPUT);
  digitalWrite(GREEN, HIGH);

  pinMode(b0, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(b3, OUTPUT);
  pinMode(b4, OUTPUT);
  pinMode(b5, OUTPUT);
  Serial.begin(9600);
}

void readData()
{
  if(Serial.available()){
    a = Serial.parseInt();
  }
  a6 = (a >> 6) & 0x01;
  a5 = (a >> 5) & 0x01;
  a4 = (a >> 4) & 0x01;
  a3 = (a >> 3) & 0x01;
  a2 = (a >> 2) & 0x01;
  a1 = (a >> 1) & 0x01;
  a0 = (a >> 0) & 0x01;
}
void resetFuel(){
  digitalWrite(b5,LOW);
  digitalWrite(b4,LOW);
  digitalWrite(b3,LOW);
  digitalWrite(b2,LOW);
  digitalWrite(b1,LOW);
  digitalWrite(b0,LOW);
}

void updateFuel(unsigned char temp)
{
    resetFuel();
  
  if (a == 1 || a == 2){
    digitalWrite(b5,HIGH);
  }
  if (a == 3 || a == 4){
    digitalWrite(b5,HIGH);
    digitalWrite(b4,HIGH);
  }
  if (a == 5 || a == 6){
    digitalWrite(b5,HIGH);
    digitalWrite(b4,HIGH);
    digitalWrite(b3,HIGH);
  }
  if (a >= 7 && a <= 9){
    digitalWrite(b5,HIGH);
    digitalWrite(b4,HIGH);
    digitalWrite(b3,HIGH);
    digitalWrite(b2,HIGH);
  }
  if (a >= 10 && a <= 12){
    digitalWrite(b5,HIGH);
    digitalWrite(b4,HIGH);
    digitalWrite(b3,HIGH);
    digitalWrite(b2,HIGH);
    digitalWrite(b1,HIGH);
  }
  if (a >= 13 && a <= 15){
    digitalWrite(b5,HIGH);
    digitalWrite(b4,HIGH);
    digitalWrite(b3,HIGH);
    digitalWrite(b2,HIGH);
    digitalWrite(b1,HIGH);
    digitalWrite(b0,HIGH);
  }
}

void loop() 
{
  readData();
  updateFuel(a);
  if (a < 5)
    digitalWrite(GREEN,HIGH);
  else
    digitalWrite(GREEN,LOW);
  delay(500);
  
}
