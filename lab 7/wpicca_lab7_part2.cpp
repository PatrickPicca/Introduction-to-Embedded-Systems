/* William Picca wpicc001@ucr.edu
 * Lab Section: 001
 * Assignment: Lab #7 Exercise #2
 * Exercise Description:
 *
 * I acknowledge all content contained herein, excluding
 * template or example code, is my own original work.
 *
 * Demo Link: https://youtu.be/vjdZPmMZhF8 
 */



#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);



unsigned char playerRow;
unsigned char speed = 0;
unsigned char timeUntilObstacleSpawn = 15;
unsigned char score;
String rowOne = "";
String rowTwo = "";
String display = "Distance: ";
char playerSymbol = 'O';
char crashSymbol = 'G';
char obstacleSymbol = 'H';

char topRowPositions[] = {playerSymbol,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',obstacleSymbol};
char bottomRowPositions[]  = {' ',' ',' ',' ',' ',' ',' ',obstacleSymbol,' ',' ',' ',' ',' ',' ',' ',' '};

int randomRow;
unsigned char cnt;
unsigned char var;


typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);
} task;

const unsigned short tasksNum = 1;
task tasks[tasksNum];



void resetMap()
{
  for (int x = 0; x < 16; x++){
    topRowPositions[x] = ' ';
  }
  for (int x = 0; x < 16; x++){
    bottomRowPositions[x] = ' ';
  }
  topRowPositions[0] = playerSymbol;
}




enum theStates { start, play, lost, displayScore };

int TickFct_display(int state) 
{
  switch(state){ // Transition States
    
    case start:
      tasks[0].period = 250;
      state = play;
      
    break;
    case play:
    
      if (topRowPositions[0] == crashSymbol || bottomRowPositions[0] == crashSymbol)
        {
          state = lost;
        }
      else //If the player has not crashed
        {
          if (digitalRead(A2) == HIGH) //Move player to bottom row
          {
            topRowPositions[0] = ' ';
            bottomRowPositions[0] = playerSymbol;
          }
          else if (digitalRead(A0) == HIGH) //Move player to top row
          {
            topRowPositions[0] = playerSymbol;
            bottomRowPositions[0] = ' ';
          }
      }
      if (digitalRead(A1) == HIGH)
        {
          state = start;
          resetMap();
          score = 0;
          cnt = 0;
          var = 0;
          timeUntilObstacleSpawn = 15;
        }
    break;
    case lost:
      
    if (var >= 30)
          state = displayScore;
      if (digitalRead(A1) == HIGH)
        {
          state = start;
          resetMap();
          score = 0;
          cnt = 0;
          var = 0;
          timeUntilObstacleSpawn = 15;
        }
    break;
    case displayScore:
      if (digitalRead(A1) == HIGH)
        {
          state = start;
          resetMap();
          score = 0;
          cnt = 0;
          var = 0;
          timeUntilObstacleSpawn = 15;
        }
    break;
    default:
    
    break;
  }
  
  
  switch(state){ // Action Stat
    case start:
    break;
    
    
    
    case play:
      
      //Score keeps track of score but also acts as a timer.
      score++;
      speed ++;
      if (tasks[0].period > 50 && speed > 10)
        {
            speed  = 0;
        tasks[0].period = tasks[0].period - 25;
        }
    
    
    
      //checks for any obstacles. If found, moves it to the next leftmost position for the top row. 
      for (int i = 0; i < 16; i++){
      if (topRowPositions[i] == obstacleSymbol)
            {
              if ((i-1) == 0 && topRowPositions[i-1] == playerSymbol) //If next symbol is the player, replaces player with crash
              {
                topRowPositions[i-1] = crashSymbol;
                topRowPositions[i] = ' ';
              }
              else if ((i-1) != 0 && topRowPositions[i-1] == ' ') //If next symbol empty, replaces empty with obstacle
              {
                topRowPositions[i-1] = obstacleSymbol;
                topRowPositions[i] = ' ';
              }
              else  //If next symbol is before the leftmost spot, replace current spot with empty
              { 
                 topRowPositions[i] = ' ';
              }
            }
        }
      //checks for any obstacles. If found, moves it to the next leftmost position for the bottom row. 
      for (int x = 0; x < 16; x++){
      if (bottomRowPositions[x] == obstacleSymbol)
            {
              if ((x-1) == 0 && bottomRowPositions[x-1] == playerSymbol) //If next symbol is the player, replaces player with crash
              {
                bottomRowPositions[x-1] = crashSymbol;
                bottomRowPositions[x] = ' ';
              }
              else if ((x-1) != 0 && bottomRowPositions[x-1] == ' ') //If next symbol empty, replaces empty with obstacle
              {
                bottomRowPositions[x-1] = obstacleSymbol;
                bottomRowPositions[x] = ' ';
              }
              else  //If next symbol is before the leftmost spot, replace current spot with empty
              { 
                 bottomRowPositions[x] = ' ';
              }
            }
        }
    
      cnt++;
      if (cnt >= timeUntilObstacleSpawn) //Spawns another obstacle
        {
          cnt = 0;
          if (timeUntilObstacleSpawn >= 5)
            timeUntilObstacleSpawn --;
          randomRow = random(0,2);
          if (randomRow == 0)
            topRowPositions[15] = obstacleSymbol;
          if (randomRow == 1)
            bottomRowPositions[15] = obstacleSymbol;
        }
    
    
      lcd.setCursor(0, 0);
        lcd.print(topRowPositions);
      lcd.setCursor(0, 1);
        lcd.print(bottomRowPositions);
    break;
    case lost:
    
      var++;
        
    break;
    
    case displayScore:
      lcd.setCursor(0, 0);
      lcd.print("                ");
      lcd.setCursor(0, 0);
        lcd.print(display + score);
      lcd.setCursor(0, 1);
        lcd.print("                ");
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
  
//  lcd.setCursor(0, 0);
//  lcd.print(rowPositions[0]);
//  lcd.setCursor(0, 1);
//  lcd.print(rowPositions[1]);
  
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  
  unsigned char i = 0;
  tasks[i].state = start;
  tasks[i].period = 250;
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
  delay(25);
}
 
