#include <SoftwareSerial.h>
String inputString = ""; // a string to hold incoming data
SoftwareSerial mySerial(10, 11); // SoftwareSerial(rxPin, txPin)
void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(4800);
  Serial.println("Hello World");
  // set the data rate for the SoftwareSerialport
  mySerial.begin(4800); // recommentlow speed
  mySerial.println("Software Serial->Hello, world?");
//  attachInterrupt(interrupt, ISR, mode) interrupt-> 1(pin3)
  //attachInterrupt(1, SoftwareSerialEvent, FALLING);
}


void loop() 
{
  serialEvent1();
  SoftwareSerialEvent();
}

void serialEvent1()
{
  while (Serial.available()) // recheck serial is available
  {
    char inChar = (char)Serial.read(); // get the new byte:
//    
    inputString += inChar; // add it to the inputString:
    if (inChar == '\r') // check received 'enter' (0x0D)
    {
      
      mySerial.print("TX from Software serial -> ");
      mySerial.println(inputString);
      inputString = "";
    }
  }
}
void SoftwareSerialEvent()
{
  if (mySerial.available()) // test this condition by connecting pin rxsoftware with pin'0'(Rx)
  {
    Serial.print((char)mySerial.read());
  }
}
