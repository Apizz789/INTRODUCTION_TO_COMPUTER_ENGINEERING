#include "LedControl.h"
LedControl lc = LedControl(11, 13, 12, 4); // CLK,DIN,CS,Number of LED Module
uint8_t intensity = 1;
unsigned long delaytime = 50; // time to updates of the display
int timer1_counter, n;
int sec = 0 , mi = 0  , hour = 0, set_alarm = 0;
int set_mi, set_hour, set_sec;
int tsec, tmi, thour;
float numX;
int numX1;
int isSetAlarm = 0;

////// First Second ///////
byte spi0[8] = { B01111100, B01000100, B01000100, B01000100, B01000100, B01000100, B01000100, B01111100};
byte spi1[8] = { B00110000, B01010000, B00010000, B00010000, B00010000, B00010000, B00010000, B01111100};
byte spi2[8] = { B00111000, B01000100, B00000100, B00001000, B00010000, B00100000, B01000000, B01111100};
byte spi3[8] = { B01111100, B00000100, B00000100, B00000100, B00111100, B00000100, B00000100, B01111100};
byte spi4[8] = { B00001100, B00010100, B00100100, B01000100, B01111100, B00000100, B00000100, B00000100};
byte spi5[8] = { B01111100, B01000000, B01000000, B01000000, B01111100, B00000100, B00000100, B01111100};
byte spi6[8] = { B01111100, B01000000, B01000000, B01000000, B01111100, B01000100, B01000100, B01111100};
byte spi7[8] = { B01111100, B00000100, B00001000, B00010000, B00010000, B00010000, B00010000, B00010000};
byte spi8[8] = { B01111100, B01000100, B01000100, B01000100, B01111100, B01000100, B01000100, B01111100};
byte spi9[8] = { B01111100, B01000100, B01000100, B01000100, B01111100, B00000100, B00000100, B01111100};
/////// Third Fouth ///////
byte spi_0[8] = { B00111110, B00100010, B00100010, B00100010, B00100010, B00100010, B00100010, B00111110};
byte spi_1[8] = { B00011000, B00101000, B00001000, B00001000, B00001000, B00001000, B00001000, B00111110};
byte spi_2[8] = { B00011100, B00100010, B00000010, B00000100, B00001000, B00010000, B00100000, B00111110};
byte spi_3[8] = { B00111110, B00000010, B00000010, B00000010, B00011110, B00000010, B00000010, B00111110};
byte spi_4[8] = { B00000110, B00001010, B00010010, B00100010, B00111110, B00000010, B00000010, B00000010};
byte spi_5[8] = { B00111110, B00100000, B00100000, B00100000, B00111110, B00000010, B00000010, B00111110};
byte spi_6[8] = { B00111110, B00100000, B00100000, B00100000, B00111110, B00100010, B00100010, B00111110};
byte spi_7[8] = { B00111110, B00000010, B00000100, B00001000, B00001000, B00001000, B00001000, B00001000};
byte spi_8[8] = { B00111110, B00100010, B00100010, B00100010, B00111110, B00100010, B00100010, B00111110};
byte spi_9[8] = { B00111110, B00100010, B00100010, B00100010, B00111110, B00000010, B00000010, B00111110};
/////// Dot ///////
byte dot1[8] = { B00000001, B00000001, B00000000, B00000001, B00000001, B00000000, B00000001, B00000001};
byte dot2[8] = { B10000000, B10000000, B00000000, B10000000, B10000000, B00000000, B10000000, B10000000};
/////// TEXT1 ///////
byte kuy[8] = { B00011000, B00011000, B00011000, B00011000, B00011000, B01111110, B01111110, B01111110};
byte text0[8] = { B01000010, B01000100, B01001000, B01110000, B01100000, B01010000, B01001000, B01000100};
byte text1[8] = { B01000010, B01000010, B01000010, B01000010, B01000010, B01000010, B01000010, B01111110};
byte text2[8] = { B01000100, B01000100, B01000100, B00101000, B00010000, B00010000, B00010000, B00010000};
//------------------------------------------------------------------------------------------------
byte text3[8] = { B00111100, B00001000, B00001000, B00001000, B00001000, B00001000, B01001000, B00110000};
byte text4[8] = { B00011000, B00100100, B01000010, B01000010, B01111110, B01000010, B01000010, B01000010};
byte text5[8] = { B01110000, B01001000, B01000100, B01000100, B01000100, B01000100, B01001000, B01110000};
byte text6[8] = { B01111110, B01000000, B01000000, B01000000, B01111000, B01000000, B01000000, B01111110};
//-------------------------------------------------------------
byte h1[8] = { B00000000, B01100110, B11111111, B11111111, B11111111, B01111110, B00111100, B00011000};
byte arrow[8] = { B00010000, B00001000, B00000100, B01110010, B01110010, B00000100, B00001000, B00010000};

void setup()
{
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(9, OUTPUT);
  Serial.begin(9600);
  for (int i = 0; i < 4; i++)
  { // set up each device
    lc.shutdown(i, false);
    lc.setIntensity(i, 1);
    lc.clearDisplay(i);
  }

  noInterrupts(); // disable all interrupts
  TCCR1A = 0; TCCR1B = 0;
  timer1_counter = 3000; // preload timer 65536-16MHz/256/1Hz
  TCNT1 = timer1_counter; // preload timer
  TCCR1B |= (1 << CS12); // 256 prescaler
  TIMSK1 |= (1 << TOIE1); // enable timer overflow interrupt
  interrupts(); //
}
ISR(TIMER1_OVF_vect) // interrupt service routine
{
  TCNT1 = timer1_counter; // preload timer
  sec++;
  tsec++;
  Serial.print("HOUR :  "); Serial.print(hour); Serial.print("     ");
  Serial.print("MI :  "); Serial.print(mi);   Serial.print("     ");
  Serial.print("SEC :  "); Serial.print(sec); Serial.print("              ");

  Serial.print(set_alarm); Serial.print("     ");

  Serial.print("SET_HOUR :  "); Serial.print(set_hour); Serial.print("     ");
  Serial.print("SET_MI :  "); Serial.print(set_mi); Serial.print("  ");
  Serial.println(numX1);
}

void loop()
{
  
  float xaccel = analogRead(A0);
  unsigned long timevar = millis();
  numX1 = map(avX(), 261.25, 392, 90, 0);
  isSetAlarm = 0;
  alarm();
  //Serial.println("+ + + + + + SET ALARM + + + + + + ");

  if (digitalRead(6) == LOW) // ซ้ายสุด
  {
    hour++;
//    printHour(hour);
    isSetAlarm = 1;
    Serial.println("+ + + + + + HOUR + + + + + +");
  }
  if (digitalRead(7) == LOW) // ปุ่ม 2 นับทางซ้าย
  {
    mi++;
//    printMi(mi);
    isSetAlarm = 1;
    Serial.println("+ + + + + + MI + + + + + +");
  }
//  if (digitalRead(8) == LOW) // ปุ่มกลาง reset
//  {
//    for (int i = 0; i < 4; i++)
//    { // set up each device
//      lc.shutdown(i, false);
//      lc.setIntensity(i, 1);
//      lc.clearDisplay(i);
//    }
//    TTT();
//    JADE();
//    delay(5000);
//    Serial.println("+ + + + + + RESET + + + + + + ");
//  }
  if (digitalRead(5) == LOW) // รองขวา
  {
    mi--;
    Serial.println("+ + + + + + Function + + + + + + ");
  }

  if (digitalRead(10) == LOW) // ขวาสุด
  {
    //    printMi(set_mi);
    //    set_mi--;
    hour--;
    Serial.println("+ + + + + + Function: Timer + + + + + + ");
  }
  timee();
  dot(); //จุด 2 จุด
  ////////////////////////////////////////////////////////////
  if (isSetAlarm) {
    printMi(set_mi);
  }
  else
  {
    printMi(mi);
  }
  ///////////////////////////////////////////
  if (isSetAlarm)
  {
    printHour(set_hour);
  }
  else
  {
    printHour(hour);
  }
}
// ---------------------------------------------------------------------------------------------------------------------------//
void reset()
{
  sec = 0; mi = 0; hour = 0;
  set_sec = 0;  set_mi = 0;  set_hour = 0;
}
void alarm()
{
  if (set_mi == mi && set_hour == hour)
  {
    noTone(9);
    music1();
    noTone(9);
  }
}
void timee()
{

  if (sec >= 60)
  {
    sec = 0;
    mi++; //mi2++;
  }
  if (mi >= 60)
  {
    mi = 0;
    set_mi = 0;
    hour++; //hour2++;
  }
  if (mi < 0)
  {
    mi = 59;
    set_mi = 59;
    hour--;// hour2--;
  }
  if (hour >=0)
  {
    hour++;
    set_hour++;
  }
  if (hour >= 24)
  {
    hour = 0;
    set_hour = 0;
  }
  if (hour < 0)
  {
    hour = 23;
    set_hour = 23;
  }
  //////////////////////////////////////
//  if (set_mi >= 60)
//  {
//    set_mi = 0;
//    set_hour++;
//  }
//  if (set_mi < 0)
//  {
//    set_mi = 59;
//    set_hour--;
//  }
//  if (set_hour >= 60)
//  {
//    set_hour = 0;
//    set_hour++;
//  }
//  if (set_hour < 60)
//  {
//    set_hour = 59;
//    set_hour--;
//  }
}

void settime()
{
  Clear();
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      lc.setLed(j, i, i + 1, 1);
      lc.setLed(j, i, i - 1, 1);
      delay(100);
    }
  }
  love();
  delay(1000);
}

void love()
{
  Clear();
  n = 0;
  b(h1);
  delay(100);
  n = 1;
  b(h1);
  delay(100);
  n = 2;
  b(h1);
  delay(100);
  n = 3;
  b(h1);
  delay(100);
}
void Clear()
{
  for (int i = 0; i < 4; i++)
  {
    lc.clearDisplay(i);
  }
}
void TTT()
{
  music1();
  n = 2;
  b(text0);
  delay(200);
  n = 1;
  b(text1);
  delay(200);
  n = 0;
  b(text2);
  delay(200);
  n = 3;
  b(kuy);
  delay(2000);
  noTone(9);
  reset();
}
void JADE()
{
  n = 0;
  b(text6);
  n = 1;
  b(text5);
  n = 2;
  b(text4);
  n = 3;
  b(text3);
}
void b(byte a[])
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(n, i, a[i]);
  }
}
void dot()
{
  delay(400);
  lc.setColumn(1, 0, B01100110);
  lc.setColumn(2, 7, B01100110);
  delay(400);
}
void music()
{
  for (int h = 0; h < 2; h++)
  {
    tone(9, 587);
    delay(100);
    tone(9, 587);
    delay(100);
    tone(9, 659);
    delay(100);
    tone(9, 659);
    delay(100);
    tone(9, 349);
    delay(100);
    tone(9, 349);
    delay(100);
    tone(9, 440);
    delay(100);
    tone(9, 494);
    delay(100);
    tone(9, 494);
    delay(100);
    tone(9, 587);
    delay(100);
    tone(9, 587);
    delay(100);
    tone(9, 494);
    delay(100);
  }
}
void music1()
{
  for (int i = 0; i < 3; i++)
  {
    tone(9, 587);
    delay(100);
    tone(9, 587);
    delay(100);
  }
}
void XYZ()
{
  //mi = sec;
  if (numX1 <= 50)
  {
    hour++;

  }
  else
  {
    sec = 60;
    //mi++;
  }
}
float avX()   //////////////// การbuffer หาค่าเฉลี่ย
{
  numX = 0;
  for (int i = 0; i < 20; i++)
  {
    numX = numX + analogRead(A1);
  }
  return numX / 20;
}
void printHour(int hour)
{
  if (hour % 10 == 0)
  {
    n = 2;
    b(spi0);
  }
  else if (hour % 10 == 1)
  {
    n = 2;
    b(spi1);
  }
  else if (hour % 10 == 2)
  {
    n = 2;
    b(spi2);
  }
  else if (hour % 10 == 3)
  {
    n = 2;
    b(spi3);
  }
  else if (hour % 10 == 4)
  {
    n = 2;
    b(spi4);
  }
  else if (hour % 10 == 5)
  {
    n = 2;
    b(spi5);
  }
  else if (hour % 10 == 6)
  {
    n = 2;
    b(spi6);
  }
  else if (hour % 10 == 7)
  {
    n = 2;
    b(spi7);
  }
  else if (hour % 10 == 8)
  {
    n = 2;
    b(spi8);
  }
  else if (hour % 10 == 9)
  {
    n = 2;
    b(spi9);
  }
  ///////////////////////////////////////////
  if (hour / 10 == 0)
  {
    n = 3;
    b(spi0);
  }
  else if (hour / 10 == 1)
  {
    n = 3;
    b(spi1);
  }
  else if (hour / 10 == 2)
  {
    n = 3;
    b(spi2);
  }

}
void printMi(int mi) {
  if (mi % 10 == 0)
  {
    n = 0;
    b(spi_0);
  }
  else if (mi % 10 == 1)
  {
    n = 0;
    b(spi_1);
  }
  else if (mi % 10 == 2)
  {
    n = 0;
    b(spi_2);
  }
  else if (mi % 10 == 3)
  {
    n = 0;
    b(spi_3);
  }
  else if (mi % 10 == 4)
  {
    n = 0;
    b(spi_4);
  }
  else if (mi % 10 == 5)
  {
    n = 0;
    b(spi_5);
  }
  else if (mi % 10 == 6)
  {
    n = 0;
    b(spi_6);
  }
  else if (mi % 10 == 7)
  {
    n = 0;
    b(spi_7);
  }
  else if (mi % 10 == 8)
  {
    n = 0;
    b(spi_8);
  }
  else if (mi % 10 == 9)
  {
    n = 0;
    b(spi_9);
  }
  ///////////////////////////////////////////
  if (mi / 10 == 0)
  {
    n = 1;
    b(spi_0);
  }
  else if (mi / 10 == 1)
  {
    n = 1;
    b(spi_1);
  }
  else if (mi / 10 == 2)
  {
    n = 1;
    b(spi_2);
  }
  else if (mi / 10 == 3)
  {
    n = 1;
    b(spi_3);
  }
  else if (mi / 10 == 4)
  {
    n = 1;
    b(spi_4);
  }
  else if (mi / 10 == 5)
  {
    n = 1;
    b(spi_5);
  }
  else if (mi / 10 == 6)
  {
    n = 1;
    b(spi_6);
  }
  else if (mi / 10 == 7)
  {
    n = 1;
    b(spi_7);
  }
  else if (mi / 10 == 8)
  {
    n = 1;
    b(spi_8);
  }
  else if (mi / 10 == 9)
  {
    n = 1;
    b(spi_9);
  }
}
