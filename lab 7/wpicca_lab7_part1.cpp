/* William Picca wpicc001@ucr.edu
 * Lab Section: 001
 * Assignment: Lab #7 Exercise #1
 * Exercise Description:
 *
 * I acknowledge all content contained herein, excluding
 * template or example code, is my own original work.
 *
 * Demo Link: https://youtu.be/hZqVAgS2l04 
 */



#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


unsigned char cnt;
unsigned char var;
String rowOne = "";
String rowTwo = "";

typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);
} task;

const unsigned short tasksNum = 1;
task tasks[tasksNum];

enum theStates { start, press, release, reset };

int TickFct_display(int state) 
{
  switch(state){ // Transition States
    
    case start:
      state = release;
      
    break;
    case press:
      if (digitalRead(A0) == LOW && digitalRead(A1) == LOW && digitalRead(A2) == LOW && digitalRead(A3) == LOW && digitalRead(A4) == LOW)
        {
          state = release;
        }
      else
         Serial.println("Currently a button is still pressed.");
    break;
    case reset:
      if ((digitalRead(A0) == HIGH && digitalRead(A1) == HIGH) || (digitalRead(A0) == HIGH && digitalRead(A2) == HIGH) 
                 || (digitalRead(A0) == HIGH && digitalRead(A3) == HIGH) || (digitalRead(A1) == HIGH && digitalRead(A2) == HIGH)
                 || (digitalRead(A1) == HIGH && digitalRead(A3) == HIGH) || (digitalRead(A2) == HIGH && digitalRead(A3) == HIGH))
        {
          
      }
      else if (digitalRead(A0) == LOW && digitalRead(A1) == LOW && digitalRead(A2) == LOW && digitalRead(A3) == LOW && digitalRead(A4) == LOW)
        {
          state = release;
        }
      else
         Serial.println("A button is still being pressed that should be let go.");
    break;
    case release:
      //First 4 if statements check for last and any other button pressed.
      if (digitalRead(A0) == HIGH && digitalRead(A4) == HIGH)
        {
          cnt ++;
          if (cnt > 16)
            {
              rowTwo += 'A';
              lcd.setCursor(0, 1);
              lcd.print(rowTwo);
            }
            else
            {
              rowOne += 'A';
              lcd.setCursor(0, 0);
              lcd.print(rowOne);
            }
          state = press;
        }
      else if (digitalRead(A1) == HIGH && digitalRead(A4) == HIGH)
        {
          cnt ++;
          if (cnt > 16)
            {
              rowTwo += 'B';
              lcd.setCursor(0, 1);
              lcd.print(rowTwo);
            }
            else
            {
              rowOne += 'B';
              lcd.setCursor(0, 0);
              lcd.print(rowOne);
            }
          state = press;
        }
      else if (digitalRead(A2) == HIGH && digitalRead(A4) == HIGH)
        {
          cnt ++;
          if (cnt > 16)
            {
              rowTwo += 'C';
              lcd.setCursor(0, 1);
              lcd.print(rowTwo);
            }
            else
            {
              rowOne += 'C';
              lcd.setCursor(0, 0);
              lcd.print(rowOne);
            }
          state = press;
        }
      else if (digitalRead(A3) == HIGH && digitalRead(A4) == HIGH)
        {
          cnt ++;
          if (cnt > 16)
            {
              rowTwo += 'D';
              lcd.setCursor(0, 1);
              lcd.print(rowTwo);
            }
            else
            {
              rowOne += 'D';
              lcd.setCursor(0, 0);
              lcd.print(rowOne);
            }
          state = press;
        }
      //Checks if any 2 buttons other than final are presses, clearing the LCD if held for 1 second.
      else if ((digitalRead(A0) == HIGH && digitalRead(A1) == HIGH) || (digitalRead(A0) == HIGH && digitalRead(A2) == HIGH) 
                 || (digitalRead(A0) == HIGH && digitalRead(A3) == HIGH) || (digitalRead(A1) == HIGH && digitalRead(A2) == HIGH)
                 || (digitalRead(A1) == HIGH && digitalRead(A3) == HIGH) || (digitalRead(A2) == HIGH && digitalRead(A3) == HIGH))
        {
          state = reset;
          /*
          rowOne = "";
          rowTwo = "";
          lcd.setCursor(0, 0);
          lcd.print("                ");
          lcd.setCursor(0, 1);
          lcd.print("                ");
          cnt = 0;
          */
        //  state = press;
        }
      //Checks if just first button is pressed
      else if (digitalRead(A0) == HIGH)
        {
          cnt ++;
          if (cnt > 16)
            {
              rowTwo += 'a';
              lcd.setCursor(0, 1);
              lcd.print(rowTwo);
            }
            else
            {
              rowOne += 'a';
              lcd.setCursor(0, 0);
              lcd.print(rowOne);
            }
          state = press;
        }
      else if (digitalRead(A1) == HIGH)
        {
          cnt ++;
          if (cnt > 16)
            {
              rowTwo += 'b';
              lcd.setCursor(0, 1);
              lcd.print(rowTwo);
            }
            else
            {
              rowOne += 'b';
              lcd.setCursor(0, 0);
              lcd.print(rowOne);
            }
          state = press;
        }
      else if (digitalRead(A2) == HIGH)
        {
          cnt ++;
          if (cnt > 16)
            {
              rowTwo += 'c';
              lcd.setCursor(0, 1);
              lcd.print(rowTwo);
            }
            else
            {
              rowOne += 'c';
              lcd.setCursor(0, 0);
              lcd.print(rowOne);
            }
          state = press;
        }
      else if (digitalRead(A3) == HIGH)
        {
          cnt ++;
          if (cnt > 16)
            {
              rowTwo += 'd';
              lcd.setCursor(0, 1);
              lcd.print(rowTwo);
            }
            else
            {
              rowOne += 'd';
              lcd.setCursor(0, 0);
              lcd.print(rowOne);
            }
          state = press;
        }
    break;
    default:
    
    break;
  }
  
  
  switch(state){ // Action Stat
    case start:
    break;
    
    
    
    case press:
    break;
    case reset:
      var++;
      if (var >= 10)
        {
        rowOne = "";
          rowTwo = "";
          lcd.setCursor(0, 0);
          lcd.print("                ");
          lcd.setCursor(0, 1);
          lcd.print("                ");
          cnt = 0;
          var = 0;
        }
    break;
    
    case release:
    
    
    break;
    
    
    
    
    default:
    
    break;
  }
  
  return state;
}

void setup() {
  
  Serial.begin(9600);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  
  unsigned char i = 0;
  tasks[i].state = start;
  tasks[i].period = 100;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &TickFct_display;
  
  
  cnt = 0;
  var = 0;
}

void loop() {
  
  // set the cursor to column 0, line 1
        // (note: line 1 is the second row, since counting begins with 0):
  //      lcd.setCursor(0, 1);
        // print the number of seconds since reset:
  //      lcd.print(millis() / 1000);
  
  // write code here
  unsigned char i;
  for (i = 0; i < tasksNum; ++i) {
    if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elapsedTime = millis(); // Last time this task was ran
    }
  }
  delay(100);
}
 
