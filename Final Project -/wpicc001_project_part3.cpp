/* William Picca wpicc001@ucr.edu
 * Lab Section: 001
 * Assignment: Final Project
 * Exercise Description:
 *
 * I acknowledge all content contained herein, excluding
 * template or example code, is my own original work.
 *
 * Demo Link: 
 */



#include <LiquidCrystal.h>
#include <IRremote.h>


const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; //Pins for LCD
const int trig = 13, echo = 6; //Pins for ultrasonic sensor
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
long duration; //variable for the duration of sound wave travel
int theDistance; //variable for the distance measurement
bool trigToggle; //Toggles triggering the sensor

unsigned char score;
String display = "Distance: ";
String thescore = "Score: ";


#define ONE 0xF30CFF00
#define TWO 0xE718FF00
#define THREE 0xA15EFF00


const int b2 = 7; //In charge of remote
unsigned char remoteInput; //Recieves and stores input from remote.
IRrecv IR(7);
unsigned long temp;

unsigned char buzzer; //buzzer = 10 at exact tumble. buzzer = 20 for victory. buzzer = 0 when lost
int buzzerFrequency;
unsigned char buzzerPeriod;
unsigned char buzzerWaits;
unsigned char buzzerdistance;

unsigned char cnt;
unsigned char var;
unsigned char distance;
unsigned char tumbleAt;   //Will be raplced by ultrasonic sensor
unsigned char lockValue;  //Value the tumbleAt must reach to display lockValue
bool buttonPress;



typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);
} task;

const unsigned short tasksNum = 2;
task tasks[tasksNum];


enum theStates { start, generateLock, play, correctLock, lost, win };

int TickFct_display(int state) 
{
  switch(state){ // Transition States
    
    case start:        //When remote is implemented start state will go to menu state insteadl
      state = generateLock;
      digitalWrite(trig, LOW);
      lcd.clear();
    break;
    
    
    case generateLock:
    
      state = play;
      tumbleAt = 0;
    
    break;
    
    case play:
    
    
      if (tumbleAt == lockValue)
          state = correctLock;
    
        if (trigToggle == true)
        {
          digitalWrite(trig, HIGH);
          trigToggle = false;
        }
        else
        {
            digitalWrite(trig, LOW);
            trigToggle = true;
            duration = pulseIn(echo, HIGH);
            theDistance = duration * 0.034 / 2;
            Serial.print("Distance: ");
          Serial.println(theDistance);
          
            tumbleAt = theDistance;
        }
    
      if (IR.decode()) 
        {
            if (buttonPress == false)
            {
                Serial.println("A button has been pressed!");
                state = lost;
                tumbleAt = 0;
                buttonPress = true;
                
            }
            else 
              buttonPress = true;
          
          IR.resume();
      }
      else
            buttonPress = false;
    
    break;
    
    case correctLock:
      
      if (tumbleAt != lockValue)
          state = play;
    
    
    
      if (IR.decode()) 
        {
            if (buttonPress == false)
            {
                score ++;
                state = generateLock;
                tumbleAt = 0;
                buttonPress = true;
                
            }
            else
              buttonPress = true;
          
          IR.resume();
          
          
            if (score >= 3)
              state = win;
          
      }
      else
            buttonPress = false;
    
    
    
        if (trigToggle == true)
        {
            digitalWrite(trig, HIGH);
            trigToggle = false;
        }
        else
        {
            digitalWrite(trig, LOW);
            trigToggle = true;
            duration = pulseIn(echo, HIGH);
            theDistance = duration * 0.034 / 2;
          
        //    Serial.print("Distance: ");
        //  Serial.println(theDistance);
          
            tumbleAt = theDistance;
        }
    
    break;
    
    case lost:
      if (digitalRead(A3) == HIGH && buttonPress == false)
        {
          state = start;
          score = 0;
          buttonPress = true;
        }
      else
            buttonPress = false;
      
    break;
    
    case win:
    
      distance = 10;
      if (digitalRead(A3) == HIGH && buttonPress == false)
        {
          state = start;
          score = 0;
          buttonPress = true;
        }
      else if (IR.decode())
        {
               buttonPress = true;
        }
      else
          buttonPress = false;
        
    
    break;
    
    
    default:
    break;
  }
  
  
  switch(state){ // Action Stat
    case start:
    break;
    
    case generateLock: //
      
      lockValue = random(3,13) + 1;    //values 4-13
      if (tumbleAt < lockValue)
                distance =  lockValue - tumbleAt;
      if (tumbleAt > lockValue)
                distance =  tumbleAt - lockValue;
    
    
    
      lcd.setCursor(0, 0);
      lcd.print(thescore + score);
      
    
      
    break;
    
    
    case play:
      buzzer = 0;
      
      if (!IR.decode()) 
        {
          buttonPress = false; 
        }
    
      distance =  lockValue - tumbleAt;
        if (tumbleAt < lockValue)
             distance =   lockValue - tumbleAt;
      if (tumbleAt > lockValue)
                distance =  tumbleAt - lockValue;
    
    
      lcd.setCursor(0, 0);
      lcd.print(thescore + score);
      
  //    lcd.setCursor(0, 0);
  //    Serial.println(thescore + score);
    
    break;
    
    case correctLock:
    
       buzzer = 10;
    
      if (!IR.decode())
        {
          buttonPress = false; 
        }
    
      distance =  lockValue - tumbleAt;
        if (tumbleAt < lockValue)
             distance =   lockValue - tumbleAt;
      if (tumbleAt > lockValue)
                distance =  tumbleAt - lockValue;
    
    
      lcd.setCursor(0, 0);
      lcd.print(thescore + score);
    
    break;
    
    case lost:
    
      buzzer = 0;
      distance = 4;
    
      lcd.setCursor(0, 0);
      lcd.print("    You Lost!");
      lcd.setCursor(0, 1);
      lcd.print(thescore + score);
    
    
    break;
    
    case win:
      buzzer = 20;
      
    
      lcd.setCursor(0, 0);
      lcd.print("    You Picked");
      lcd.setCursor(0, 1);
      lcd.print("     the Lock!");
        
        
    break;
    
    default:
    break;
  }
  
  return state;
}




enum buzzerStates { start2, wait, atTumble, victoryBuzz};

int TickFct_buzzer(int state) 
{
  switch(state){ // Transition States
    
    case start2:  
      state = wait;
    break;
    case wait:  //buzzer is 0
      
      buzzerdistance = distance;
      if (buzzer == 10)
            state = atTumble;
    
    
    break;
    case atTumble: //buzzer is at 10
      if (buzzer == 0)
            state = wait;
      if (buzzer == 20)
            state = victoryBuzz;
    break;
    case victoryBuzz: //buzzer is 20
      if (buzzerWaits == 7)
        {
          state = start;
          buzzer = 0;
        }
    break;
    
    default:
    break;
  }
  switch(state){ // Action States
    case start2:  
      
    break;
    case wait:  
    
      buzzerdistance = distance;
      if (buzzerdistance == 3)
          buzzerFrequency = 50;
      if (buzzerdistance == 2)
          buzzerFrequency = 100;
      if (buzzerdistance == 1)
          buzzerFrequency = 200;
      if (buzzerdistance == 0)
          buzzerFrequency = 300;
      //Plays buzzer when the correct tumble is reached but not confirmed
      if (buzzerdistance > 3)
        {
          
        }
      else
        {
          if (buzzerPeriod == 0)  
          {
              tone(10, buzzerFrequency, 500);
              buzzerPeriod++;
          }
          else if (buzzerPeriod != 0)
          {
              buzzerPeriod++;
               if (buzzerPeriod >= (2 * (1+buzzerdistance)) )
                 buzzerPeriod = 0;
          }
        }
    
    
    
    break;
    case atTumble:
    
      buzzerdistance = distance;
      if (buzzerdistance == 0)
          buzzerFrequency = 300;
      //Plays buzzer when the correct tumble is reached but not confirmed
      if (buzzerPeriod == 0)  
        {
          tone(10, buzzerFrequency, 500);
            buzzerPeriod++;
        }
      else if (buzzerPeriod != 0)
        {
            buzzerPeriod++;
           if (buzzerPeriod >= (2 * (1+buzzerdistance)))
               buzzerPeriod = 0;
        }
    break;
    
    
    case victoryBuzz: 
      buzzerWaits ++; 
      if (buzzerWaits == 1)
        tone(10, 250, 500);
      if (buzzerWaits == 3)
        tone(10, 500, 500);
      if (buzzerWaits == 5)
        tone(10, 750, 500);
    break;
    
    
    default:
    break;
  }
  return state;
}








void setup() {
  
  Serial.begin(9600);
  
  // set up the LCD's number of columns and rows:
  lcd.clear();
  lcd.begin(16, 2);
  
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  

  pinMode(trig, OUTPUT); 
  pinMode(echo, INPUT);
  
  unsigned char i = 0;
  tasks[i].state = start;
  tasks[i].period = 250;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &TickFct_display;
  i++;
  tasks[i].state = start2;
  tasks[i].period = 500;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &TickFct_buzzer;
  
  cnt = 0;
  var = 0;
  score = 0;
  buttonPress = false;
  buzzerPeriod = 0;
  buzzerWaits = 0;
  
  trigToggle = false;
  IR.enableIRIn();// Start the receiver
}



void loop() {
  

  
//  tone(10, 500, 500);   //Buzzer pin 10 at 500khz for 500ms
  
  
  unsigned char i;
  for (i = 0; i < tasksNum; ++i) {
    if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elapsedTime = millis(); // Last time this task was ran
    }
  }
  delay(50);
  
  
  
}
 
