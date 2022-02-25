///////// Assignment 4 /////////

#include <LedControl.h>
const byte PIN_ANALOG_X = 0;
const byte PIN_ANALOG_Y = 1;
//dinเทา clkดำ csขาว
LedControl lc = LedControl(12, 11, 10, 1);

unsigned long long RandTime = 500;

unsigned long delayTime = 200;
int StarX[10], StarY[10] = { -2, -2, -2, -2, -2, -2, -2, -2, -2, -2};
//int nam[8]={0,1,2,3,4,5,6,7};
int Hp = 8;
int x = 3, y = 0;
int point;

void setup()
{
  for (int i = 2; i < 9; i++)
  {
    pinMode(i, INPUT);
    digitalWrite(i, HIGH);
    Serial.begin(9600);
  }
  lc.shutdown(0, false); // Wake up displays
  lc.setIntensity(0, 1);  // Set intensity levels
  lc.clearDisplay(0);   // Clear Displays
  Draw_Hp();
  pinMode(9, OUTPUT);
  }

void music1()
{
  for (int h = 0; h < 6; h++)
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

void music2()
{
  for (int i = 0; i < 3; i++)
  {
    tone(9, 587);
    delay(100);
    tone(9, 587);
    delay(100);
  }
}

void RanStar()
{
  randomSeed(millis()+6);
  int n = random() % 6 + 1;
  for (int i = 0; i < 10; i++)
  {
    if (StarY[i] == -2)
    {
      StarX[i] = n;
      StarY[i] = 8;
      lc.setLed(0, StarX[i], StarY[i], 1);
      break;
    }
  }
}

void Draw_Hp()
{
  switch (Hp)
  {
    //        col row
    case 7 :
      lc.setRow(0, 0, B11111111);
      lc.setRow(0, 7, B11111111);
      break;
    case 6 :
      lc.setRow(0, 0, B11111110);
      lc.setRow(0, 7, B11111110);
      break;
    case 5 :
      lc.setRow(0, 0, B11111100);
      lc.setRow(0, 7, B11111100);
      break;
    case 4 :
      lc.setRow(0, 0, B11111000);
      lc.setRow(0, 7, B11111000);
      break;
    case 3 :
      lc.setRow(0, 0, B11110000);
      lc.setRow(0, 7, B11110000);
      break;
    case 2 :
      lc.setRow(0, 0, B11100000);
      lc.setRow(0, 7, B11100000);
      break;
    case 1 :
      lc.setRow(0, 0, B11000000);
      lc.setRow(0, 7, B11000000);
      break;
    case 0 :
      lc.setRow(0, 0, B10000000);
      lc.setRow(0, 7, B10000000);
      break;
  }
}
void MoveStar()
{
  for (int i = 0; i < 10; i++)
  {
    if (StarY[i] != -2)
    {

      lc.setLed(0, StarX[i], StarY[i], 0);
      StarY[i]--;


      lc.setLed(0, StarX[i], StarY[i], 1);
      if (StarY[i] == 0 && StarX[i] != x)
      {
        Hp--;
        lc.shutdown(0, true);
        Draw_Hp();
        lc.shutdown(0, false);
        delay(200);
        music2();
        Serial.println(Hp);
        Serial.println("////////////////////////////////////////////////////////////");
      }
    }
    point++;
    Serial.println(point);
  }
}

void Draw_Ship()
{
  lc.setLed(0, x, y, 1);
}

void lose()
{
  Clear();
  lc.setColumn(0, 7, B00111100);
  lc.setColumn(0, 6, B01000010);
  lc.setColumn(0, 5, B10100101);
  lc.setColumn(0, 4, B10000001);
  lc.setColumn(0, 3, B10011001);
  lc.setColumn(0, 2, B10100101);
  lc.setColumn(0, 1, B01000010);
  lc.setColumn(0, 0, B00111100);
}
void win()
{
  Clear();
  for (int i = 0; i < 8; i++)
  {
    lc.setLed(0, i, i + 1, 1);
    lc.setLed(0, i, i - 1, 1);
    delay(300);
  } 
  love(); 
}

void love()
{
  Clear();
  lc.setColumn(0, 0, B00011000);
  lc.setColumn(0, 1, B00111100);
  lc.setColumn(0, 2, B01111110);
  lc.setColumn(0, 3, B11111111);
  lc.setColumn(0, 4, B11111111);
  lc.setColumn(0, 5, B11111111);
  lc.setColumn(0, 6, B01100110);
  lc.setColumn(0, 7, B00000000);
}
void reset()
{
  Clear();
  x = 3, y = 0;
  Hp = 8;
  point = 0;
}
void Clear()
{
  lc.clearDisplay(0);
}
void loop() {
  MoveStar();
  Draw_Ship();
  noTone(9);
  if (point == 2000)
  {
    win();
    delay(3000);
    reset();
  }
  if (Hp == 0)
  {
    lose();
    delay(1000);
    music1();
    noTone(3);
    reset();
  }
  if (analogRead(PIN_ANALOG_X) < 480)
  {
    if (x > 1) x--;
    {
      lc.setLed(0, x + 1, y, 0);
      lc.setLed(0, x, y, 1);
    }
  }

  if (analogRead(PIN_ANALOG_X) > 550)
  {
    if (x < 6) x++;
    {
      lc.setLed(0, x - 1, y, 0);
      lc.setLed(0, x, y, 1);
    }
  }
  delay(100);
  if (millis() - RandTime > 1000)
  {
    RanStar();
    RandTime = millis();
  }
  RandTime++;
}
