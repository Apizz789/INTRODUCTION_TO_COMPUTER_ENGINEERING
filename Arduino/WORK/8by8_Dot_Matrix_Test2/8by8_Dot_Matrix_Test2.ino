#include "LedControl.h"
#define B1 10
#define B2 11

LedControl lc=LedControl(9,11,13,10);// Pins: DIN,CLK,CS, # of Display connected


//FOR DEBOUNCE BUTTON A
int currentButtonStateA = LOW;
int previousButtonStateA = LOW;
//FOR DEBOUNCE BUTTON B
int currentButtonStateB = LOW;
int previousButtonStateB = LOW;

bool checkB1=1;
bool checkB2=1;

// Put values in arrays
byte invader1a[] =
{
B00000000, 
B01100000,
B00110000,
B00011000,
B00001100,
B00011000,
B00110000,
B00000000
};

byte invader1b[] =
{
B00000000, 
B00000000,
B01100110,
B00111100,
B00111100,
B01100110,
B00000000,
B00000000
};


void setup()
{
  Serial.begin(9600);
lc.shutdown(0,false); // Wake up displays
lc.shutdown(1,false);
lc.setIntensity(0,1); // Set intensity levels
lc.setIntensity(1,1);
lc.clearDisplay(0); // Clear Displays
lc.clearDisplay(1);
pinMode(B1,INPUT_PULLUP);
pinMode(B2,INPUT_PULLUP);
}
// Take values in Arrays and Display them
void sinvader1a()
{
for (int i = 0; i < 8; i++)
{
lc.setRow(0,i,invader1a[i]);
}
}

void sinvader1b()
{
for (int i = 0; i < 8; i++)
{
lc.setRow(0,i,invader1b[i]);
}
}

void loop()
{
 
  //Control 1
  currentButtonStateA=digitalRead(B1);
  if ((currentButtonStateA != previousButtonStateA) && previousButtonStateA == HIGH){
      checkB1=!checkB1;
      Serial.println("B1 Pressed");
      sinvader1a();
      delay(500);
  }
  previousButtonStateA = currentButtonStateA;
  //Control 2
  currentButtonStateB=digitalRead(B2);
  if ((currentButtonStateB != previousButtonStateB) && previousButtonStateB == HIGH){
      checkB2=!checkB2;
      Serial.println("B2 Pressed");
      sinvader1b();
      delay(500);
  }
  previousButtonStateB = currentButtonStateB;

if(digitalRead(B1)==LOW) {
  sinvader1a();
  Serial.println("B1");
}
if(digitalRead(B2)==LOW) sinvader1b();
}
