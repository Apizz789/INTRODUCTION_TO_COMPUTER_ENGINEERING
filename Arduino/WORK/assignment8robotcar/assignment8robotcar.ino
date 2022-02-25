   
int enA = 10;
int in1 = 9;
int in2 = 8;
// motor two
int enB = 5;
int in3 = 7;
int in4 = 6;
int speedA=100;
int speedB=120;

void setup()
{
 
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

}
void movestraight(){
  analogWrite(enA,speedA);
analogWrite(enB,speedB);
digitalWrite(in1,HIGH);
digitalWrite(in2,LOW);


digitalWrite(in3,HIGH);
digitalWrite(in4,LOW);

  
}
void turnleft(){
  analogWrite(enA,speedA);
analogWrite(enB,speedB);
digitalWrite(in1,HIGH);
digitalWrite(in2,LOW);


digitalWrite(in3,LOW);
digitalWrite(in4,HIGH);

  
}
void stopcar(){
    analogWrite(enA,0);
analogWrite(enB,0);
  digitalWrite(in1,LOW);
digitalWrite(in2,LOW);


digitalWrite(in3,LOW);
digitalWrite(in4,LOW);

}
void loop()
{
movestraight();
delay(1500);
stopcar();
delay(1000);
turnleft();
delay(340);
stopcar();
delay(1000);



}
