#define bottonONE 13
#define bottonTWO 12
#define bottonTHR 11
#define ledONE 7
#define ledTWO 6
#define ledTHR 5
#define F LOW
#define T HIGH
long t=0;


void setup();
{ 
  pinMode(bottonONE,INPUT_PULLUP);
  pinMode(bottonTWO,INPUT_PULLUP);
  pinMode(bottonTHR,INPUT_PULLUP);
  pinMode(ledONE,OUTPUT);
  pinMode(ledTWO,OUTPUT);
  pinMode(ledTHR,OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int readSwitchA=digitalRead(bottonONE);
  int readSwitchB=digitalRead(bottonTWO);
  int readSwitchC=digitalRead(bottonTHR);

///////////////////////////////////////////////////////////////////////////////////////////////
  Serial.println(readSwitchA);
  if(readSwitchA == F && millis()-t>500)  //เเดงจ้าาาาา
  {
    t = millis();
     while(readSwitchA==F && millis()-t>500); delay(300);
     if(digitalRead(ledONE)== F )
     {
      digitalWrite(ledONE,T);
     }
     else
     {
      digitalWrite(ledONE,F);
     }
  } 
   if (readSwitchA == T && millis()-t>2700)
  {
    digitalWrite(ledONE,F);
  }
///////////////////////////////////////////////////////////////////////////////////////////////
  Serial.println(readSwitchC);
  if(readSwitchC == F && millis()-t>500)  //เขียวจ้าาาาา
  {
    t = millis();
    while(readSwitchC ==F && millis()-t>500);
     if(digitalRead(ledTHR)==HIGH)
     {
      digitalWrite(ledTHR,F);
     }
     else
     {
      digitalWrite(ledTHR,T);
     }
  }
   if (readSwitchC == T && millis()-t>2700)
  {
    digitalWrite(ledTHR,F);
  }
///////////////////////////////////////////////////////////////////////////////////////////////
  Serial.println(readSwitchB);
  if(readSwitchB == F && millis()-t>500)  //เหลืองจ้าาาาา
  {
    t = millis();
    while(readSwitchB ==F && millis()-t>500);
     if(digitalRead(ledTWO)==HIGH)
     {
      digitalWrite(ledTWO,F);
     }
     else
     {
      if (digitalRead(ledONE)==HIGH)
      {
        digitalWrite(ledTWO,F);
      }
      if (digitalRead(ledTHR)==HIGH)
      {
        digitalWrite(ledTWO,F);
      }
      else (digitalRead(ledONE)==HIGH);
      {
       digitalWrite(ledTWO,T); 
      delay(500);
      digitalWrite(ledTWO,F);
      delay(550);
      digitalWrite(ledTWO,T); 
      }
      
     }
  }
   if (readSwitchB == T && millis()-t>2000)
  {
    digitalWrite(ledTWO,F);
  }
   
  
}
