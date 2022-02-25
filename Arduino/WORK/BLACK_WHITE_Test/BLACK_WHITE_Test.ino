int value[5];

void setup() {
  Serial.begin(9600);
}

void loop() {
  value[0]=analogRead(0);
  value[1]=analogRead(1);
  value[2]=analogRead(2);
  value[3]=analogRead(3);
  value[4]=analogRead(4);
  if(value[0]>360) Serial.print("WHITE");
  else Serial.print("BLACK");
  Serial.print(" ");
  if(value[1]>420) Serial.print("WHITE");
  else Serial.print("BLACK");
  Serial.print(" ");
  if(value[2]>800) Serial.print("WHITE");
  else Serial.print("BLACK");
  Serial.print(" ");
  if(value[3]>350) Serial.print("WHITE");
  else Serial.print("BLACK");
  Serial.print(" ");
  if(value[4]>400) Serial.println("WHITE");
  else Serial.println("BLACK");
  
  delay(300);
}
