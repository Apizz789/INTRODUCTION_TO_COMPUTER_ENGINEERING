#define bottonONE 13
#define bottonTWO 12
#define bottonTHR 11
#define ledONE 7
#define ledTWO 6
#define ledTHR 5
#define F LOW
#define T HIGH
long T1,T2,T3=0;


void setup()
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
  //Serial.println(readSwitchA);
  if(readSwitchA == F && millis()-t1>500)  //เเดงจ้าาาาา
  {
     t1 = millis();
     while(readSwitchA==F &&readSwitchC==F && millis()-t>500); 
     if(digitalRead(ledONE)== F)
     {
      digitalWrite(ledONE,T);
      delay(100);
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
  if(readSwitchC == F && millis()-T1>500)  //เขียวจ้าาาาา
  {
    t2 = millis();
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
  if(readSwitchA == F && readSwitchC == F && millis()-T2>500)  //เหลืองจ้าาาาา
  {
    t3 = millis();
    while(readSwitchB ==F && millis()-t>500);
     if(digitalRead(ledTWO)==HIGH)
     {
      digitalWrite(ledTWO,F);
     }
     else
     {
      if (digitalRead(ledONE)==LOW)
      {
        digitalWrite(ledTWO,F);
      }
      if (digitalRead(ledTHR)==LOW)
      {
        digitalWrite(ledTWO,F);
      }
      else (digitalRead(ledONE)==HIGH);
      {
      digitalWrite(ledTWO,T); 
      delay(600);
      digitalWrite(ledTWO,F);
      delay(450);
      digitalWrite(ledTWO,T); 
      }
      
     }
  }
   if (readSwitchB == T && millis()-T3>2000)
  {
    digitalWrite(ledTWO,F);
  }
   
  
}
