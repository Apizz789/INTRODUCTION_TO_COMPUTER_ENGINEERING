// motor one
int enA = 13;
int in1 = 12;
int in2 = 11;
int in3 = 10;
int in4 = 9;
int enB = 8;

void setup()
{
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop()
{
  //mtA
  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
  delay(100);
  //mtB
  digitalWrite(in3, 1);
  digitalWrite(in4, 0 );
  delay(115);
  
  analogWrite(enA, 204);
  analogWrite(enB, 180);
}
void motor()
{
  // this function will run the motors in both directions at a fixed speed
  // turn on motor A
  digitalWrite(in1, HIGH);
  digitalWrite(in3, 1);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 200); // Speed Control
  delay(2000);
  // now change motor directions
  digitalWrite(in1, LOW);
  digitalWrite(in3, LOW);
  delay(2000);
  // now turn off motors
  digitalWrite(in1, LOW);
}

void motor1()
{
  // this function will run the motors in both directions at a fixed speed
  // turn on motor A
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 200); // Speed Control
  delay(2000);
  // now change motor directions
  digitalWrite(in3, 1);
  digitalWrite(in4, 0);
  delay(2000);
  // now turn off motors
  digitalWrite(in3, 1);
}
