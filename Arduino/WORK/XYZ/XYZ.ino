///////////// Assignment 5 /////////////////
////////////////// ตัวส่ง ////////////////////
#include "SoftwareSerial.h"
SoftwareSerial chat(10, 11); 

float numX;
int numX1;
float numX2;

void setup()
{
Serial.begin(9600);
chat.begin(9600);
}
void loop()
{
  
float xaccel = analogRead(A1);
unsigned long timevar = millis();
numX1=map(avX(),261.25,392,180,0);
Serial.print("  ");
Serial.println(numX1);
Serial.print("  ");
chat.print(numX1);
delay(500);
}


float avX()   //////////////// การbuffer หาค่าเฉลี่ย
{ 
  numX=0;
  for(int i=0;i<20;i++)
  {
    numX=numX+analogRead(A1);
  }
  return numX/20;
}
