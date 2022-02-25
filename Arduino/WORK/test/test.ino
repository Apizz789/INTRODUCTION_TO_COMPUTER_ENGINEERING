void setup() 
{
 pinMode(3,INPUT);
 Serial.begin(9600);

}

void loop() 
{
 delay(300);
Serial.println(analogRead(3));
}
