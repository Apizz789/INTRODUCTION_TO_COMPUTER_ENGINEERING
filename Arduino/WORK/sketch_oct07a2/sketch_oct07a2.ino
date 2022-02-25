#include "LedControl.h"
LedControl lc = LedControl(13, 10, 11, 1); // DIN, CLK, CS, NUMBER_OF_LED
const byte PIN_ANALOG_X = 0;
const byte PIN_ANALOG_Y = 1;
const byte Button_A = 2;
const byte Button_B = 3;
const byte Button_C = 4;
const byte Button_D = 5;
const byte Button_E = 6;
const byte Button_F = 7;
const byte Button_K = 8;

int i, randomnumber, star_position, high = 7;
unsigned long Debounce;

void Check_Button_Debug(int);
void Set_Up_Pin(void);
void Scene_Start(void);
void Ship_and_Position(int, int);
int Check_Button(int);
void Delete_Ship_and_Position(int, int);
void Star(int);
int random_number(void);
void Move(int, int);
void Debug(int);


void setup()
{

  Serial.begin(9600);
  Set_Up_Pin();
  int devices = lc.getDeviceCount();
  for (int address = 0; address < devices; address++)
  {
    lc.shutdown(address, false);
    lc.setIntensity(address, 8);
    lc.clearDisplay(address);
  }
}

void loop()
{
  int y = 3, x = 0, GameSpeed = 80, i = 0, j = 0, check = 0;
  int k = 1, star_staus = 1;
  int Game_Time = 0;

  //---------- Set Start Scence ----------\\  
  Ship_and_Position(0, 3);
  lc.setColumn(1, 7, 0xFF);


  while (k == 1)
  {

    if (star_staus == 0)
    {
      star_position = random_number();
      Star(star_position);
      star_staus = 1;
    }

    if (Game_Time % 3 == 0 && Game_Time != 0)
    {

      Move(star_position, 7 - high + 1);
      if (7 - high == 0)
      {

        star_staus = 0;

      }
      high = high % 7;
      high++;
      if (7 - high + 1 == 1)
      {
        check = 1;
      }
    }
    Debug(Game_Time); // Print Value
    Check_Button_Debug(Game_Time);


    y = y - Check_Button(y);
    Ship_and_Position(x, y);
    Delete_Ship_and_Position(x, y);

    if (check == 1)
    {
      check = 0;
      if (star_position == y)
      {

        lc.setLed(3, i++, j, true);
        if (i == 8)
        {
          i = 0;
          j++;
        }
      }

    }

    delay(100);

    Game_Time = Game_Time % GameSpeed;
    Game_Time++;
  }

}

void Set_Up_Pin(void)
{

  pinMode(Button_A, INPUT);
  digitalWrite(Button_A, HIGH);

  pinMode(Button_B, INPUT);
  digitalWrite(Button_B, HIGH);

  pinMode(Button_C, INPUT);
  digitalWrite(Button_C, HIGH);

  pinMode(Button_D, INPUT);
  digitalWrite(Button_D, HIGH);

  pinMode(Button_E, INPUT);
  digitalWrite(Button_E, HIGH);

  pinMode(Button_F, INPUT);
  digitalWrite(Button_F, HIGH);

  pinMode(Button_K, INPUT);
  digitalWrite(Button_K, HIGH);

}

void Check_Button_Debug(int Game_Time)
{

  if (Game_Time % 5 == 0)
  {
    Serial.print("x:");
    Serial.print(analogRead(PIN_ANALOG_X));
    Serial.print(" ");

    Serial.print("y:");
    Serial.print(analogRead(PIN_ANALOG_Y));
    Serial.print(" ");

    Serial.print("A:");
    Serial.print(digitalRead(Button_A));
    Serial.print(" ");

    Serial.print("B:");
    Serial.print(digitalRead(Button_B));
    Serial.print(" ");

    Serial.print("C:");
    Serial.print(digitalRead(Button_C));
    Serial.print(" ");

    Serial.print("D:");
    Serial.print(digitalRead(Button_D));
    Serial.print(" ");

    Serial.print("E:");
    Serial.print(digitalRead(Button_E));
    Serial.print(" ");

    Serial.print("F:");
    Serial.print(digitalRead(Button_F));
    Serial.print(" ");

    Serial.print("K:");
    Serial.print(digitalRead(Button_K));
    Serial.print(" ");

    Serial.println();

  }
}

void Scene_Start(void)
{

  lc.setColumn(0, 0, 0xFF);
  lc.setRow(0, 0, 0xFF);
  //lc.setLed(int addr, int row, int col, boolean state);


}

void Ship_and_Position(int x, int y)
{

  lc.setLed(x, 0, y, true);

}

void Delete_Ship_and_Position(int x, int y)
{

  for (i = 1; i < 7; i++)
  {
    lc.setLed(x, 0, y - i, false);

  }
  for (i = 1; i < 7; i++)
  {
    lc.setLed(x, 0, y + i, false);

  }

}

int Check_Button(int y)
{

  if (digitalRead(Button_D) == 0 && y < 7 && digitalRead(Button_B) == 1 )
  {

    return -1;

  }
  if (digitalRead(Button_B) == 0 && y > 0 && digitalRead(Button_D) == 1 )
  {
    return 1;
  }
  return 0;
}

void Star(int Star_Position)
{

  lc.setLed(0, 7, Star_Position, true);

}

void Move(int star_position, int high)
{

  if (high > 0)
  {
    lc.setLed(0, high, star_position, false);
  }
  if (high > 1)
  {
    lc.setLed(0, --high, star_position, true);
  }

}

int random_number(void)
{

  randomSeed(analogRead(5));
  int r;
  r = random(1, 7);
  return r;

}

void Debug(int Game_Time)
{

  if (Game_Time % 50 == 0)
  {
    Serial.print(" This is Star Position = ");
    Serial.println(star_position);
    Serial.print(" This is seed ");
    Serial.println(analogRead(5));
    Serial.print(" This is Game Time = ");
    Serial.println(Game_Time);

  }

}
