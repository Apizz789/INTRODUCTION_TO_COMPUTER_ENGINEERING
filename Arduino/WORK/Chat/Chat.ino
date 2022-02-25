///////////// Assignment 5 /////////////////
////////////////// ตัวรับ ////////////////////
#include <SoftwareSerial.h>
#include "LedControl.h"
#include "FontLEDClock.h"
LedControl lc = LedControl(3, 5, 4, 4);
SoftwareSerial chat(10, 11); // RX, TX

int text;
int ka, n, i, j;
int x1;     //= a / 100;
int y10;    //= (a / 10) % 10;
int z100;   //= a % 10;

byte num[10][8] = {0x7c, 0x44, 0x44, 0x44, 0x44, 0x44, 0x7c, 0x00,
                   0x40, 0x40, 0x40, 0x40, 0x40, 0x60, 0x40, 0x00,
                   0x7c, 0x04, 0x04, 0x7c, 0x40, 0x40, 0x7c, 0x00,
                   0x78, 0x40, 0x40, 0x78, 0x40, 0x40, 0x78, 0x00,
                   0x40, 0x40, 0x40, 0x7c, 0x44, 0x44, 0x44, 0x00,
                   0x7c, 0x40, 0x40, 0x7c, 0x04, 0x04, 0x7c, 0x00,
                   0x7c, 0x44, 0x44, 0x7c, 0x04, 0x04, 0x7c, 0x00,
                   0x10, 0x10, 0x10, 0x20, 0x40, 0x40, 0x7c, 0x00,
                   0x7c, 0x44, 0x44, 0x7c, 0x44, 0x44, 0x7c, 0x00,
                   0x7c, 0x40, 0x40, 0x7c, 0x44, 0x44, 0x7c, 0x00
                  };

void setup()
{
  Serial.begin(9600);
  chat.begin(9600);
  delay(1000);
  for (int i = 0; i < 4; i++)
  {
    lc.shutdown(i, false); // Wake up displays
    lc.setIntensity(i, 5);  // Set intensity levels
    lc.clearDisplay(i);   // Clear Displays
  }

}
void loop()
{
  ka = 0;

  String data = "";
  while (chat.available())
  {
    data += (char)chat.read();

    Serial.print(ka);
    clear_display();
  }
  int i = 0;
  while (data[i]) {
    if(data[i] == '-'){
      // print - 
    }
    print_normal_char(i * 8+5, 1, data[i]);
    i++;
  }
Serial.println();

}
void plot (uint8_t x, uint8_t y, uint8_t value) {

  //select which matrix depending on the x coord
  uint8_t address;
  if (x >= 0 && x <= 7)   {
    address = 3;
  }
  if (x >= 8 && x <= 15)  {
    address = 2;
    x = x - 8;
  }
  if (x >= 16 && x <= 23) {
    address = 1;
    x = x - 16;
  }
  if (x >= 24 && x <= 31) {
    address = 0;
    x = x - 24;
  }

  if (value == 1) {
    lc.setLed(address, y, x, true);
  } else {
    lc.setLed(address, y, x, false);
  }
}

//clear screen
void clear_display() {
  for (uint8_t address = 0; address < 4; address++) {
    lc.clearDisplay(address);
  }
}

void print_normal_char(uint8_t x, uint8_t y, char c)
{

  uint8_t dots;
  if (c >= 'A' && c <= 'Z' ) {
    c &= 0x1F;  // A-Z maps to 1-26
  }
  else if (c >= 'a' && c <= 'z') {
    c = (c - 'a') + 41;  // A-Z maps to 41-67
  }
  else if (c >= '0' && c <= '9') {
    c = (c - '0') + 31;
  }
  else if (c == ' ') {
    c = 0;  // space
  }
  else if (c == '.') {
    c = 27;  // full stop
  }
  else if (c == '\'') {
    c = 28;  // single quote mark
  }
  else if (c == ':') {
    c = 29;  // clock_mode selector arrow
  }
  else if (c == '>') {
    c = 30;  // clock_mode selector arrow
  }
  else if (c >= -80 && c <= -67) {
    c *= -1;
  }

  for (uint8_t col = 0; col < 5; col++) {
    dots = pgm_read_byte_near(&myfont[c][col]);
    for (uint8_t row = 0; row < 7; row++) {
      if (dots & (64 >> row)) {   // only 7 rows.
        plot(x + col, y + row, 1);
      } else {
        plot(x + col, y + row, 0);
      }
    }
  }
}
