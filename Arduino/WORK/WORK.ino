#define bottonONE 13
#define bottonTWO 12 
#define bottonTHR 11
#define ledONE 7
#define ledTWO 6
#define ledTHR 5

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
  digitalWrite(ledONE,!digitalRead(bottonONE)); 
  digitalWrite(ledTWO,!digitalRead(bottonTWO));
  digitalWrite(ledTHR,!digitalRead(bottonTHR));
}
