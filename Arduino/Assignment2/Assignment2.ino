
bool seg[7][8]=
{
  {true,false,false,true,true,true,true},   {false,false,true,false,false,true,false}, //1-2
  {false,false,false,false,true,true,false},{true,false,false,true,true,false,false},  //3-4
  {false,true,false,false,true,false,false},{false,true,false,false,false,false,false} //5-6
};
int beginN =0;
int a=0,i=0,j=0;
int r;

void transition1();

void setup() //กำหนด pinmode ของ 7SM (pin2-pin8 และ Switch (pin9-pin10)
{
  for(int i=0;i<7;i++)
  pinMode(i+2,OUTPUT);
  
  for(int i=10;i<12;i++)
  pinMode(i,INPUT_PULLUP);

  pinMode(9,OUTPUT); //Y
  pinMode(12,OUTPUT); //R
  pinMode(13,OUTPUT); //G

  pinMode(1,OUTPUT);
  
  
 // Serial.begin(9600);
}
void nonmusic()
{
  noTone(1);
}
void music()
{
  for (int h=0;h<3;h++)
  {
    tone(1,500);
    delay(1000);
    tone(1,200);
    delay(1000);
  }
  
}
void music1()
{
  for (int h=0;h<6;h++)
  {
    tone(1,587);
    delay(100);
    tone(1,587);
    delay(100);
    tone(1,659);
    delay(100);
    tone(1,659);
    delay(100);
    tone(1,349);
    delay(100);
    tone(1,349);
    delay(100);
    tone(1,440);
    delay(100);
    tone(1,494);
    delay(100);
    tone(1,494);
    delay(100);
    tone(1,587);
    delay(100);
    tone(1,587);
    delay(100);
    tone(1,494);
    delay(100);
  }
}
void ligh()
{
  digitalWrite(9,HIGH);
  delay(100);
  digitalWrite(12,HIGH);
  delay(100);
  digitalWrite(13,HIGH);
  delay(100);
}
void loop1()
{
  light1(1,1,1); delay(100);
  light1(0,1,0); delay(100);
  light1(0,0,1); delay(100);
  light1(0,1,0); delay(100);
  light1(1,0,0); delay(100);
  light1(0,1,0); delay(100);
  light1(0,0,0); delay(100); 
}
void loophyper()
{
  for (int p=0 ;p<3;p++)
  {
    loop1();
  }
}
void light1 (bool x,bool y,bool z)
{
  if (x==1) digitalWrite(9,HIGH);
  if (x==0) digitalWrite(9,LOW);
  if (y==1) digitalWrite(12,HIGH);
  if (y==0) digitalWrite(12,LOW);
  if (z==1) digitalWrite(13,HIGH);
  if (z==0) digitalWrite(13,LOW);
}
void transition1() 
{
  for(int a=2;a<9;a++)
  {
    digitalWrite(a,HIGH);
    delay(50);
  }
  for(int a=2;a<9;a++)
  {
    digitalWrite(a,LOW);
    delay(50);
  }
  delay(50);
}

void randomN()
{ 
  randomSeed(analogRead(1));
  r=random(1,3);
 // Serial.println(r);
  if(r==beginN)
  { 
  win();
  }
  else lose();
  Serial.println("Again");
}
void bt1()
 {
     transition1();
     int i=0;
      for (i;i<7;i++)
       {
        digitalWrite(i+2,seg[j][i]);
       }
       delay(300);
      if(j<5)
        {j++;}
       else j=0;
  }
void show(int a)
 {
     
     int i=0;
      for (i;i<7;i++)
       {
        digitalWrite(i+2,seg[a-1][i]);
       }
       delay(300);   
  }

  void win()
    {
    show(r);
    Serial.println("WINNNNN");
    loophyper();
    music1();
    delay(500);
    digitalWrite(13,LOW);
    nonmusic();
    }

  void lose()
   {
    ligh();
    transition1();
    transition1();
    show(r);
    digitalWrite(12,LOW);
    music();
    nonmusic();
    Serial.println("LOSEEEE");
   }
   
void loop() 
{

  if (digitalRead(10) == 0) // ปุ่ม A
  {
    a = beginN % 6 + 1;
    bt1();
    beginN++;
  }
    
   if (digitalRead(11) == 0) // ปุ่ม B
   {
       
       randomN();
      Serial.println(r);
   }
}
