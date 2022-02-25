#include "ST7735_TEE.h"
TEE_ST7735 lcd(9, 10, 11, 12, 13); //Arduino csk,sda,A0,rst,cs
int sec = 0;
int minite = 0;
int hour = 0;
int val = 0;
int day = 1;
int days=1;
int mon=1;
int year=19;
int timer1_counter;

String input;

void setup() {
  // put your setup code here, to run once:
  
  lcd.init(lcd.VERTICAL);
  noInterrupts(); // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  timer1_counter = 3036; // preload timer 65536-16MHz/256/1Hz
  TCNT1 = timer1_counter; // preload timer
  TCCR1B |= (1 << CS12); // 256 prescaler
  TIMSK1 |= (1 << TOIE1); // enable timer overflow interrupt
  interrupts(); // enable all interrupts
  Serial.begin(9600);
  lcd.fillScreen(BLACK);
  lcd.fillRect(0, 0, 160, 30, RED);
  lcd.fillRect(0, 30, 160, 20, WHITE);
  lcd.fillRect(0, 50, 160, 60, BLUE);
  lcd.fillRect(0, 110, 160, 20, WHITE);
  lcd.fillRect(0, 130, 160, 30, RED);
  sec = 0;


}
ISR(TIMER1_OVF_vect) // interrupt service routine
{
  TCNT1 = timer1_counter; // preload timer
  sec++;

}

void loop() {
  // put your main code here, to run repeatedly:
  if (sec >= 60||sec<0)
  {
    sec = 0;
    minite++;
  }
  if (minite >= 60||minite<0)
  {
    minite = 0;
    hour++;
  }
  if (hour >= 24||hour<0)
  {
    hour = 0;
    day++;
    days++;
    lcd.fillRect(0, 0, 160, 30, RED);
    lcd.fillRect(0, 130, 160, 30, RED);
  }
  if(day>7 || day<0)
  {
    day=1;
  }
  
  if (Serial.available() > 0)
  {
    input = Serial.readStringUntil('\n');
    days = (input[0] - '0') * 10 + (input[1] - '0');
    mon = (input[3] - '0') * 10 + (input[4] - '0');
    year = (input[6] - '0') * 10 + (input[7] - '0');
    hour = (input[9] - '0') * 10 + (input[10] - '0');
    minite = (input[12] - '0') * 10 + (input[13] - '0');
    sec = (input[15] - '0') * 10 + (input[16] - '0');
    day = (input[18] - '0');
    
    lcd.fillRect(0, 0, 160, 30, RED);
    lcd.fillRect(0, 30, 160, 20, WHITE);
    lcd.fillRect(0, 50, 160, 60, BLUE);
    lcd.fillRect(0, 110, 160, 20, WHITE);
    lcd.fillRect(0, 130, 160, 30, RED);
  }
  Date();
  lcd.drawString(90, 78, ".", WHITE, 2);
  lcd.drawString(39, 70, ":", WHITE, 3);

  if (sec % 10 == 0)
  {
    
    lcd.drawString(115, 78, "0", WHITE, 2);
  }
  else if (sec % 10 == 1)
  {
    lcd.drawString(115, 78, "1", WHITE, 2);
  }
  else if (sec % 10 == 2)
  {
    lcd.drawString(115, 78, "2", WHITE, 2);
  }
  else if (sec % 10 == 3)
  {
    lcd.drawString(115, 78, "3", WHITE, 2);
  }
  else if (sec % 10 == 4)
  {
    lcd.drawString(115, 78, "4", WHITE, 2);
  }
  else if (sec % 10 == 5)
  {
    lcd.drawString(115, 78, "5", WHITE, 2);

  }
  else if (sec % 10 == 6)
  {
    lcd.drawString(115, 78, "6", WHITE, 2);
  }
  else if (sec % 10 == 7)
  {
    lcd.drawString(115, 78, "7", WHITE, 2);
  }
  else if (sec % 10 == 8)
  {
    lcd.drawString(115, 78, "8", WHITE, 2);
  }
  else if (sec % 10 == 9)
  {
    lcd.drawString(115, 78, "9", WHITE, 2);
  }
  /////////////////////////////////////////////
  if (sec / 10 == 0)
  {
    lcd.drawString(102, 78, "0", WHITE, 2);
  }
  else if (sec / 10 == 1)
  {
    lcd.drawString(102, 78, "1", WHITE, 2);
  }
  else if (sec / 10 == 2)
  {
    lcd.drawString(102, 78, "2", WHITE, 2);
  }
  else if (sec / 10 == 3)
  {
    lcd.drawString(102, 78, "3", WHITE, 2);
  }
  else if (sec / 10 == 4)
  {
    lcd.drawString(102, 78, "4", WHITE, 2);
  }
  else if (sec / 10 == 5)
  {
    lcd.drawString(102, 78, "5", WHITE, 2);
  }
  else if (sec / 10 == 6)
  {
    lcd.drawString(102, 78, "6", WHITE, 2);
  }
  else if (sec / 10 == 7)
  {
    lcd.drawString(102, 78, "7", WHITE, 2);
  }
  else if (sec / 10 == 8)
  {
    lcd.drawString(102, 78, "8", WHITE, 2);
  }
  else if (sec / 10 == 9)
  {
    lcd.drawString(102, 78, "9", WHITE, 2);
  }






  ////////////////////////////////
  if (minite % 10 == 0)
  {
    lcd.drawString(75, 70, "0", WHITE, 3);
  }
  else if (minite % 10 == 1)
  {
    lcd.drawString(75, 70, "1", WHITE, 3);
  }
  else if (minite % 10 == 2)
  {
    lcd.drawString(75, 70, "2", WHITE, 3);
  }
  else if (minite % 10 == 3)
  {
    lcd.drawString(75, 70, "3", WHITE, 3);
  }
  else if (minite % 10 == 4)
  {
    lcd.drawString(75, 70, "4", WHITE, 3);
  }
  else if (minite % 10 == 5)
  {
    lcd.drawString(75, 70, "5", WHITE, 3);
  }
  else if (minite % 10 == 6)
  {
    lcd.drawString(75, 70, "6", WHITE, 3);
  }
  else if (minite % 10 == 7)
  {
    lcd.drawString(75, 70, "7", WHITE, 3);
  }
  else if (minite % 10 == 8)
  {
    lcd.drawString(75, 70, "8", WHITE, 3);
  }
  else if (minite % 10 == 9)
  {
    lcd.drawString(75, 70, "9", WHITE, 3);
  }
  /////////////////////////////////////////////
  if (minite / 10 == 0)
  {
    lcd.drawString(57, 70, "0", WHITE, 3);
  }
  else if (minite / 10 == 1)
  {
    lcd.drawString(57, 70, "1", WHITE, 3);
  }
  else if (minite / 10 == 2)
  {
    lcd.drawString(57, 70, "2", WHITE, 3);
  }
  else if (minite / 10 == 3)
  {
    lcd.drawString(57, 70, "3", WHITE, 3);
  }
  else if (minite / 10 == 4)
  {
    lcd.drawString(57, 70, "4", WHITE, 3);
  }
  else if (minite / 10 == 5)
  {
    lcd.drawString(57, 70, "5", WHITE, 3);
  }
  else if (minite / 10 == 6)
  {
    lcd.drawString(57, 70, "6", WHITE, 3);
  }
  else if (minite / 10 == 7)
  {
    lcd.drawString(57, 70, "7", WHITE, 3);
  }
  else if (minite / 10 == 8)
  {
    lcd.drawString(57, 70, "8", WHITE, 3);
  }
  else if (minite / 10 == 9)
  {
    lcd.drawString(57, 70, "9", WHITE, 3);
  }

  ///////////////////////////////////////////////////////////
  if (hour / 10 == 0)
  {
    lcd.drawString(3, 70, "0", WHITE, 3);
  }
  else if (hour / 10 == 1)
  {
    lcd.drawString(3, 70, "1", WHITE, 3);
  }
  else if (hour / 10 == 2)
  {
    lcd.drawString(3, 70, "2", WHITE, 3);
  }


  if (hour % 10 == 0)
  {
    lcd.drawString(21, 70, "0", WHITE, 3);
  }
  else if (hour % 10 == 1)
  {
    lcd.drawString(21, 70, "1", WHITE, 3);
  }
  else if (hour % 10 == 2)
  {
    lcd.drawString(21, 70, "2", WHITE, 3);
  }
  else if (hour % 10 == 3)
  {
    lcd.drawString(21, 70, "3", WHITE, 3);
  }
  else if (hour % 10 == 4)
  {
    lcd.drawString(21, 70, "4", WHITE, 3);
  }
  else if (hour % 10 == 5)
  {
    lcd.drawString(21, 70, "5", WHITE, 3);
  }
  else if (hour % 10 == 6)
  {
    lcd.drawString(21, 70, "6", WHITE, 3);
  }
  else if (hour % 10 == 7)
  {
    lcd.drawString(21, 70, "7", WHITE, 3);
  }
  else if (hour % 10 == 8)
  {
    lcd.drawString(21, 70, "8", WHITE, 3);
  }
  else if (hour % 10 == 9)
  {
    lcd.drawString(21, 70, "9", WHITE, 3);
  }

  delay(700);
  lcd.fillRect(3, 70, 125, 25 , BLUE);
  days_7();
  


}

void days_7(void) {
  if (day == 1) {
    lcd.drawString(30, 140, "Monday", YELLOW, 2);
  }
  else if (day == 2) {
    lcd.drawString(25, 140, "Tuesday", BLACK, 2);
  }
  else if (day == 3) {
    lcd.drawString(12, 140, "Wednesday", GREEN, 2);
  }
  else if (day == 4) {
    lcd.drawString(18, 140, "Thursday", BLACK, 2);
  }
  else if (day == 5) {
    lcd.drawString(30, 140, "Friday", MAGENTA, 2);
  }
  else if (day == 6) {
    lcd.drawString(18, 140, "Saturday", CYAN, 2);
  }
  else if (day == 7) {
    lcd.drawString(33, 140, "Sunday", BLACK, 2);
  }
  
}
void Date() {
  if(days>31&& (mon==1 || mon==3 || mon==5 || mon==7 || mon==8 || mon==10 || mon==12))
  {
    lcd.fillRect(0, 0, 160, 30, RED);
    days=1;
    mon++;
  }
  else if(days>30 && (mon==4 || mon==6 || mon==9 || mon==11))
  {
    lcd.fillRect(0, 0, 160, 30, RED);
    days=1;
    mon++;
  }
  else if(days>28 && mon==2 && (year%4==0))
  {
    lcd.fillRect(0, 0, 160, 30, RED);
    days=1;
    mon++;
  }
  else if(days>29 && mon==2 && (year%4!=0))
  {
    lcd.fillRect(0, 0, 160, 30, RED);
    days=1;
    mon++;
  }


  if(mon>12)
  {
    mon=1;
    year++;
  }

 lcd.drawString(44, 12, "/", WHITE, 2);
 lcd.drawString(80, 12, "/", WHITE, 2);


  
  if (days / 10 == 0)
  {
    lcd.drawString(20, 12, "0", WHITE, 2);
  }
  else if (days / 10 == 1)
  {
    lcd.drawString(20, 12, "1", WHITE, 2);
  }
  else if (days / 10 == 2)
  {
    lcd.drawString(20, 12, "2", WHITE, 2);
  }
  else if (days / 10 == 3)
  {
    lcd.drawString(20, 12, "3", WHITE, 2);
  }


  if (days % 10 == 0)
  {
    lcd.drawString(32, 12, "0", WHITE,2);
  }
  else if (days % 10 == 1)
  {
    lcd.drawString(32, 12, "1", WHITE, 2);
  }
  else if (days % 10 == 2)
  {
    lcd.drawString(32, 12, "2", WHITE, 2);
  }
  else if (days % 10 == 3)
  {
    lcd.drawString(32, 12, "3", WHITE, 2);
  }
  else if (days % 10 == 4)
  {
    lcd.drawString(32, 12, "4", WHITE, 2);
  }
  else if (days % 10 == 5)
  {
    lcd.drawString(32, 12, "5", WHITE, 2);
  }
  else if (days % 10 == 6)
  {
    lcd.drawString(32, 12, "6", WHITE, 2);
  }
  else if (days % 10 == 7)
  {
    lcd.drawString(32, 12, "7", WHITE, 2);
  }
  else if (days % 10 == 8)
  {
    lcd.drawString(32, 12, "8", WHITE, 2);
  }
  else if (days % 10 == 9)
  {
    lcd.drawString(32, 12, "9", WHITE, 2);
  }
  ////////////////////////////////////////
  if (mon / 10 == 0)
  {
    lcd.drawString(56, 12, "0", WHITE, 2);
  }
  else if (mon / 10 == 1)
  {
    lcd.drawString(56, 12, "1", WHITE, 2);
  }
  else if (mon / 10 == 2)
  {
    lcd.drawString(56, 12, "2", WHITE, 2);
  }


  if (mon % 10 == 0)
  {
    lcd.drawString(68, 12, "0", WHITE,2);
  }
  else if (mon % 10 == 1)
  {
    lcd.drawString(68, 12, "1", WHITE, 2);
  }
  else if (mon % 10 == 2)
  {
    lcd.drawString(68, 12, "2", WHITE, 2);
  }
  else if (mon % 10 == 3)
  {
    lcd.drawString(68, 12, "3", WHITE, 2);
  }
  else if (mon % 10 == 4)
  {
    lcd.drawString(68, 12, "4", WHITE, 2);
  }
  else if (mon % 10 == 5)
  {
    lcd.drawString(68, 12, "5", WHITE, 2);
  }
  else if (mon % 10 == 6)
  {
    lcd.drawString(68, 12, "6", WHITE, 2);
  }
  else if (mon % 10 == 7)
  {
    lcd.drawString(68, 12, "7", WHITE, 2);
  }
  else if (mon % 10 == 8)
  {
    lcd.drawString(68, 12, "8", WHITE, 2);
  }
  else if (mon % 10 == 9)
  {
    lcd.drawString(68, 12, "9", WHITE, 2);
  }
  ///////////////////////////////////////////////
  if (year / 10 == 0)
  {
    lcd.drawString(92, 12, "0", WHITE, 2);
  }
  else if (year / 10 == 1)
  {
    lcd.drawString(92, 12, "1", WHITE, 2);
  }
  else if (year / 10 == 2)
  {
    lcd.drawString(92, 12, "2", WHITE, 2);
  }
  else if (year / 10 == 3)
  {
    lcd.drawString(92, 12, "3", WHITE, 2);
  }
  else if (year / 10 == 4)
  {
    lcd.drawString(92, 12, "4", WHITE, 2);
  }
  else if (year / 10 == 5)
  {
    lcd.drawString(92, 12, "5", WHITE, 2);
  }
  else if (year / 10 == 6)
  {
    lcd.drawString(92, 12, "6", WHITE, 2);
  }
  else if (year / 10 == 7)
  {
    lcd.drawString(92, 12, "7", WHITE, 2);
  }
  else if (year / 10 == 8)
  {
    lcd.drawString(92, 12, "8", WHITE, 2);
  }
  else if (year / 10 == 9)
  {
    lcd.drawString(92, 12, "9", WHITE, 2);
  }



  
  if (year % 10 == 0)
  {
    lcd.drawString(104, 12, "0", WHITE, 2);
  }
  else if (year % 10 == 1)
  {
    lcd.drawString(104, 12, "1", WHITE, 2);
  }
  else if (year % 10 == 2)
  {
    lcd.drawString(104, 12, "2", WHITE, 2);
  }
  else if (year % 10 == 3)
  {
    lcd.drawString(104, 12, "3", WHITE, 2);
  }
  else if (year % 10 == 4)
  {
    lcd.drawString(104, 12, "4", WHITE, 2);
  }
  else if (year % 10 == 5)
  {
    lcd.drawString(104, 12, "5", WHITE, 2);
  }
  else if (year % 10 == 6)
  {
    lcd.drawString(104, 12, "6", WHITE, 2);
  }
  else if (year % 10 == 7)
  {
    lcd.drawString(104, 12, "7", WHITE, 2);
  }
  else if (year % 10 == 8)
  {
    lcd.drawString(104, 12, "8", WHITE, 2);
  }
  else if (year % 10 == 9)
  {
    lcd.drawString(104, 12, "9", WHITE, 2);
  }
}
