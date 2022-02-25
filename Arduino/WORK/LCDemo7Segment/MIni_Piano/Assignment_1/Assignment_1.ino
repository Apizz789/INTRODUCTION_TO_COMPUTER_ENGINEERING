#define R 7
#define Y 6
#define G 5
#define B1 13
#define B2 12
#define B3 11
#define T true
#define F false
#define H HIGH
#define L LOW
unsigned long t1, t2, t3 , tY, tY1, tLast = 0 ;
bool stR = F, stG = F , stY = F,stateY = F;

//----------------------------------------------------------------------------------------------------------------//
void setup()
{
  pinMode(R, OUTPUT);
  pinMode(Y, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B1, INPUT_PULLUP);
  pinMode(B2, INPUT_PULLUP);
  pinMode(B3, INPUT_PULLUP);
  Serial.begin(9600);
}
bool lastR = true, lastY = true , lastG = true;
bool RS1 = true, RS2 = true, RS3 = true;
//----------------------------------------------------------------------------------------------------------------//
void loop()
{
  int btR = digitalRead(B1);
  int btY = digitalRead(B2);
  int btG = digitalRead(B3);

  if (lastR && !btR)
  {
    RS1 = false;
    Serial.println("RS1");
  }
  else
  {
    RS1 = true;
  }
  
  if (lastG && !btG)
  {
    RS3 = false;
  }
  else
  {
    RS3 = true;
    Serial.println("RS3");
  }
  if (lastY == T && btY == F)
  { 
    tY = millis();
    if (stR == F && stG == F && stY == F)
      stY = T;
  }
  
  lastR = btR;
  lastY = btY;
  lastG = btG;
  delay(100);
  
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // RED LIGHT //

  if (RS1 == L && millis() - t1 > 500)
  {
    t1 = millis();
    if (digitalRead(R) == L)
    {
      digitalWrite(R, H);
      t1 = millis();
      stR = T;
    }
    else 
    {
      digitalWrite(R, L);
      stR = F;
    }
  }
  if (RS1 == H && millis() - t1 > 3000) 
  {
    digitalWrite(R, L);
    stR = F;
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // GREEN LIGHT //

  if (RS3 == L )
  {
    
    if (digitalRead(G) == L && stR == F )
    {
      t3 = millis();
      digitalWrite(G, H);
      stG = T;
    }
    else if (digitalRead(G) == T && stR == F )
    {
      t3 = millis();
      digitalWrite(G, L);
      stG = F;
    }
  }
  if (RS3 == H && millis() - t3 > 3000)
  {
    digitalWrite(G, L);
    stG = F;
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // YELLOW LIGHT //

  if (stY&&millis() - tY <= 2100)
  {
    if (millis() - tY1 > 500)
    {
      tY1 = millis();
      digitalWrite(Y,!digitalRead(Y));
    }
  }
  else {
    stY = F;
  }

}
