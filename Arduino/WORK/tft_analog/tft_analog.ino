#include "ST7735_TEE.h"
TEE_ST7735 lcd {9, 10, 11, 12, 13};
#define SKYBLUE 0x169A
#define COOKIERED 0xFD1E
int sec = 10;
int mins = 59;
int dis_hrs = 0;
int hrs = 23;
int dat = 5;
int day = 7;
int mon = 11;
int yrs = 19;
int val = 0;
int timer1_counter;
String input;

void setup() 
{
  pinMode(6, OUTPUT);
  Serial.begin(9600);
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  timer1_counter = 3036;
  TCNT1 = timer1_counter; // preload timer
  TCCR1B |= (1 << CS12); // 256 prescaler
  TIMSK1 |= (1 << TOIE1); // enable timer overflow interrupt
  interrupts(); // enable all interrupts
  lcd.init(lcd.VERTICAL);
  lcd.fillScreen(COOKIERED);
  lcd.fillCircle(64, 60, 50, SKYBLUE);
  lcd.drawCircle(64, 60, 50, WHITE);
  lcd.drawCircle(64, 60, 49, WHITE);
  lcd.drawCircle(64, 60, 48, WHITE);
  
  sec = 0;
}
ISR(TIMER1_OVF_vect) // interrupt service routine
{
  TCNT1 = timer1_counter; // preload timer
  sec++;

}

void loop() 
{
  lcd.drawChar(100, 55, '3', BLACK, 2);
  lcd.drawChar(60, 90, '6', BLACK, 2);
  lcd.drawChar(20, 55, '9', BLACK, 2);
  lcd.drawString(56, 18, "12", BLACK, 2);
 noTone(6);

  if (sec > 59 || sec < 0) {
    sec = 0;
    mins++;
  }
  if (mins > 59 || mins < 0) {
    mins = 0;
     music();
    noTone(6);
    hrs++;
  }
  if (hrs > 23 || hrs < 0) {
    hrs = 0;
    dat++;
    day++;
  }
  if (mon == 1 || mon == 3 || mon == 5 || mon == 7 || mon == 8 || mon == 10 || mon == 12) {
    if (day > 31 || day < 1) {
      day = 1;
      mon++;
    }
  }
  if (mon == 4 || mon == 6 || mon == 9 || mon == 11) {
    if (day > 30 || day < 1) {
      day = 1;
      mon++;
    }
  }
  if (mon == 2) {
    if (day > 28 || day < 1) {
      day = 1;
      mon++;
    }
  }
  if (mon > 12 || mon < 0) {
    mon = 1;
    yrs++;
  }
  if (Serial.available() > 0) {
    input = Serial.readStringUntil('\n'); //INPUT : DD MM YY HH MM SS D
    day = (input[0] - '0') * 10 + (input[1] - '0');
    mon = (input[3] - '0') * 10 + (input[4] - '0');
    yrs = (input[6] - '0') * 10 + (input[7] - '0');
    hrs = (input[9] - '0') * 10 + (input[10] - '0');
    mins = (input[12] - '0') * 10 + (input[13] - '0');
    sec = (input[15] - '0') * 10 + (input[16] - '0');
    dat = (input[18] - '0');
  }
  if (day / 10 == 0)
  {
    lcd.fillRect(12, 135, 10, 14, COOKIERED);
    lcd.drawString(12, 135, "0", WHITE, 2);
  }
  else if (day / 10 == 1)
  {
    lcd.fillRect(12, 135, 10, 14, COOKIERED);
    lcd.drawString(12, 135, "1", WHITE, 2);
  }
  else if (day / 10 == 2)
  {
    lcd.fillRect(12, 135, 10, 14, COOKIERED);
    lcd.drawString(12, 135, "2", WHITE, 2);
  }
  else if (day / 10 == 3)
  {
    lcd.fillRect(12, 135, 10, 14, COOKIERED);
    lcd.drawString(12, 135, "3", WHITE, 2);
  }


  if (day % 10 == 0)
  {
    lcd.fillRect(26, 135, 10, 14, COOKIERED);
    lcd.drawString(26, 135, "0", WHITE, 2);
  }
  else if (day % 10 == 1)
  {
    lcd.fillRect(26, 135, 10, 14, COOKIERED);
    lcd.drawString(26, 135, "1", WHITE, 2);
  }
  else if (day % 10 == 2)
  {
    lcd.fillRect(26, 135, 10, 14, COOKIERED);
    lcd.drawString(26, 135, "2", WHITE, 2);
  }
  else if (day % 10 == 3)
  {
    lcd.fillRect(26, 135, 10, 14, COOKIERED);
    lcd.drawString(26, 135, "3", WHITE, 2);
  }
  else if (day % 10 == 4)
  {
    lcd.fillRect(26, 135, 10, 14, COOKIERED);
    lcd.drawString(26, 135, "4", WHITE, 2);
  }
  else if (day % 10 == 5)
  {
    lcd.fillRect(26, 135, 10, 14, COOKIERED);
    lcd.drawString(26, 135, "5", WHITE, 2);
  }
  else if (day % 10 == 6)
  {
    lcd.fillRect(26, 135, 10, 14, COOKIERED);
    lcd.drawString(26, 135, "6", WHITE, 2);
  }
  else if (day % 10 == 7)
  {
    lcd.fillRect(26, 135, 10, 14, COOKIERED);
    lcd.drawString(26, 135, "7", WHITE, 2);
  }
  else if (day % 10 == 8)
  {
    lcd.fillRect(26, 135, 10, 14, COOKIERED);
    lcd.drawString(26, 135, "8", WHITE, 2);
  }
  else if (day % 10 == 9)
  {
    lcd.fillRect(26, 135, 10, 14, COOKIERED);
    lcd.drawString(26, 135, "9", WHITE, 2);
  }
  
  if (hrs > 12) dis_hrs = hrs - 12;
  else dis_hrs = hrs;
  if (dat == 1) {
    lcd.fillRect(47, 115, 34, 14, COOKIERED);
    lcd.drawString(47, 115, "SUN", WHITE, 2);
  }
  else if (dat == 2) {
    lcd.fillRect(47, 115, 34, 14, COOKIERED);
    lcd.drawString(47, 115, "MON", WHITE, 2);
  }
  else if (dat == 3) {
    lcd.fillRect(47, 115, 34, 14, COOKIERED);
    lcd.drawString(47, 115, "TUE", WHITE, 2);
  }
  else if (dat == 4) {
    lcd.fillRect(47, 115, 34, 14, COOKIERED);
    lcd.drawString(47, 115, "WED", WHITE, 2);
  }
  else if (dat == 5) {
    lcd.fillRect(47, 115, 34, 14, COOKIERED);
    lcd.drawString(47, 115, "THU", WHITE, 2);
  }
  else if (dat == 6) {
    lcd.fillRect(47, 115, 34, 14, COOKIERED);
    lcd.drawString(47, 115, "FRI", WHITE, 2);
  }
  else if (dat == 7) {
    lcd.fillRect(47, 115, 34, 14, COOKIERED);
    lcd.drawString(47, 115, "SAT", WHITE, 2);
  }

  if (mon == 1) {
    lcd.fillRect(47, 135, 34, 14, COOKIERED);
    lcd.drawString(47, 135, "JAN", WHITE, 2);
  }
  else if (mon == 2) {
    lcd.fillRect(47, 135, 34, 14, COOKIERED);
    lcd.drawString(47, 135, "FEB", WHITE, 2);
  }
  else if (mon == 3) {
    lcd.fillRect(47, 135, 34, 14, COOKIERED);
    lcd.drawString(47, 135, "MAR", WHITE, 2);
  }
  else if (mon == 4) {
    lcd.fillRect(47, 135, 34, 14, COOKIERED);
    lcd.drawString(47, 135, "APR", WHITE, 2);
  }
  else if (mon == 5) {
    lcd.fillRect(47, 135, 34, 14, COOKIERED);
    lcd.drawString(47, 135, "MAY", WHITE, 2);
  }
  else if (mon == 6) {
    lcd.fillRect(47, 135, 34, 14, COOKIERED);
    lcd.drawString(47, 135, "JUN", WHITE, 2);
  }
  else if (mon == 7) {
    lcd.fillRect(47, 135, 34, 14, COOKIERED);
    lcd.drawString(47, 135, "JUL", WHITE, 2);
  }
  else if (mon == 8) {
    lcd.fillRect(47, 135, 34, 14, COOKIERED);
    lcd.drawString(47, 135, "AUG", WHITE, 2);
  }
  else if (mon == 9) {
    lcd.fillRect(47, 135, 34, 14, COOKIERED);
    lcd.drawString(47, 135, "SEP", WHITE, 2);
  }
  else if (mon == 10) {
    lcd.fillRect(47, 135, 34, 14, COOKIERED);
    lcd.drawString(47, 135, "OCT", WHITE, 2);
  }
  else if (mon == 11) {
    lcd.fillRect(47, 135, 34, 14, COOKIERED);
    lcd.drawString(47, 135, "NOV", WHITE, 2);
  }
  else if (mon == 12) {
    lcd.fillRect(47, 135, 34, 14, COOKIERED);
    lcd.drawString(47, 135, "DEC", WHITE, 2);
  }

  if (yrs / 10 == 0)
  {
    lcd.fillRect(92, 135, 22, 14, COOKIERED);
    lcd.drawString(92, 135, "0", WHITE, 2);
  }
  else if (yrs / 10 == 1)
  {
    lcd.fillRect(92, 135, 22, 14, COOKIERED);
    lcd.drawString(92, 135, "1", WHITE, 2);
  }
  else if (yrs / 10 == 2)
  {
    lcd.fillRect(92, 135, 22, 14, COOKIERED);
    lcd.drawString(92, 135, "2", WHITE, 2);
  }
  else if (yrs / 10 == 3)
  {
    lcd.fillRect(92, 135, 22, 14, COOKIERED);
    lcd.drawString(92, 135, "3", WHITE, 2);
  }
  else if (yrs / 10 == 4)
  {
    lcd.fillRect(92, 135, 22, 14, COOKIERED);
    lcd.drawString(92, 135, "4", WHITE, 2);
  }
  else if (yrs / 10 == 5)
  {
    lcd.fillRect(92, 135, 22, 14, COOKIERED);
    lcd.drawString(92, 135, "5", WHITE, 2);
  }
  else if (yrs / 10 == 6)
  {
    lcd.fillRect(92, 135, 22, 14, COOKIERED);
    lcd.drawString(92, 135, "6", WHITE, 2);
  }
  else if (yrs / 10 == 7)
  {
    lcd.fillRect(92, 135, 22, 14, COOKIERED);
    lcd.drawString(92, 135, "7", WHITE, 2);
  }
  else if (yrs / 10 == 8)
  {
    lcd.fillRect(92, 135, 22, 14, COOKIERED);
    lcd.drawString(92, 135, "8", WHITE, 2);
  }
  else if (yrs / 10 == 9)
  {
    lcd.fillRect(92, 135, 22, 14, COOKIERED);
    lcd.drawString(92, 135, "9", WHITE, 2);
  }



  if (yrs % 10 == 0)
  {
    lcd.fillRect(104, 135, 22, 14, COOKIERED);
    lcd.drawString(104, 135, "0", WHITE, 2);
  }
  else if (yrs % 10 == 1)
  {
    lcd.fillRect(104, 135, 22, 14, COOKIERED);
    lcd.drawString(104, 135, "1", WHITE, 2);
  }
  else if (yrs % 10 == 2)
  {
    lcd.fillRect(104, 135, 22, 14, COOKIERED);
    lcd.drawString(104, 135, "2", WHITE, 2);
  }
  else if (yrs % 10 == 3)
  {
    lcd.fillRect(104, 135, 22, 14, COOKIERED);
    lcd.drawString(104, 135, "3", WHITE, 2);
  }
  else if (yrs % 10 == 4)
  {
    lcd.fillRect(104, 135, 22, 14, COOKIERED);
    lcd.drawString(104, 135, "4", WHITE, 2);
  }
  else if (yrs % 10 == 5)
  {
    lcd.fillRect(104, 135, 22, 14, COOKIERED);
    lcd.drawString(104, 135, "5", WHITE, 2);
  }
  else if (yrs % 10 == 6)
  {
    lcd.fillRect(104, 135, 22, 14, COOKIERED);
    lcd.drawString(104, 135, "6", WHITE, 2);
  }
  else if (yrs % 10 == 7)
  {
    lcd.fillRect(104, 135, 22, 14, COOKIERED);
    lcd.drawString(104, 135, "7", WHITE, 2);
  }
  else if (yrs % 10 == 8)
  {
    lcd.fillRect(104, 135, 22, 14, COOKIERED);
    lcd.drawString(104, 135, "8", WHITE, 2);
  }
  else if (yrs % 10 == 9)
  {
    lcd.fillRect(104, 135, 22, 14, COOKIERED);
    lcd.drawString(104, 135, "9", WHITE, 2);
  }

  lcd.drawLine(64, 60, 25 * cos((dis_hrs * 30 + 270) * 0.0174533) + 64, 25 * sin((dis_hrs * 30 + 270) * 0.0174533) + 60, GREEN);
  lcd.drawLine(64, 60, 30 * cos((mins * 6 + 270) * 0.0174533) + 64, 30 * sin((mins * 6 + 270) * 0.0174533) + 60, WHITE);
  lcd.drawLine(64, 60, 35 * cos((sec * 6 + 270) * 0.0174533) + 64, 35 * sin((sec * 6 + 270) * 0.0174533) + 60, RED);
  delay(750);
  lcd.drawLine(64, 60, 35 * cos((sec * 6 + 270) * 0.0174533) + 64, 35 * sin((sec * 6 + 270) * 0.0174533) + 60, SKYBLUE);
  lcd.drawLine(64, 60, 30 * cos((mins * 6 + 270) * 0.0174533) + 64, 30 * sin((mins * 6 + 270) * 0.0174533) + 60, SKYBLUE);
  lcd.drawLine(64, 60, 25 * cos((dis_hrs * 30 + 270) * 0.0174533) + 64, 25 * sin((dis_hrs * 30 + 270) * 0.0174533) + 60, SKYBLUE);

}
void music()
{
  for (int h = 0; h < 2; h++)
  {
    tone(6, 587);
    delay(100);
    tone(6, 587);
    delay(100);
    tone(6, 659);
    delay(100);
    tone(6, 659);
    delay(100);
    tone(6, 349);
    delay(100);
    tone(6, 349);
    delay(100);
    tone(6, 440);
    delay(100);
    tone(6, 494);
    delay(100);
    tone(6, 494);
    delay(100);
    tone(6, 587);
    delay(100);
    tone(6, 587);
    delay(100);
    tone(6, 494);
    delay(100);
  }
}
