void setup() 
{
pinMode(13,INPUT); 
Serial.begin(9600);
}

void loop() {
delay(300);
 Serial.println( digitalRead(13));

}
