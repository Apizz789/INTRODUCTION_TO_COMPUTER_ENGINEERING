/// Assignment 2 Mini piano ///
int note[250]; // เก็บโน๊ต
int index = 1; // จำนวนโน็ตตัวที่ n
int timenote[250]; // บันทึกเวลาระหว่างโน็ต
int timecount = 0; // ตัวนับเวลา
long debo = 0; // ตัวหน่วงเวลา

void setup()
{
  for (int i = 0; i < 5; i++) // record and reset
  {
    pinMode(i + 3, INPUT_PULLUP);
  }
  for (int i = 5; i < 12; i++) // DoReMiSolaTe
  {
    pinMode(i, INPUT_PULLUP);
  }
  pinMode(2, OUTPUT); // Speaker
  Serial.begin(9600);
}

void loop()
{
  if (digitalRead(3) == LOW) // ปุ่ม Reset
  {
    delay(150);
    Serial.println("RESET");
    //index++;
    for (int r = 1; r <= 250; r++)
    {
      note[r] = 0;
      timenote[r] = 0;
    }
    index = 0;
  }

  if (digitalRead(4) == LOW) // ปุ่ม Play
  {
    for (int r = 1; r <= index + 1; r++)
    {
      tone(2, note[r], 250);
      Serial.println("PLAY");
      delay(timenote[r + 1]);
    }
    noTone(2);
  }

  if (millis() - debo > 100 )
  {
    if (digitalRead(5) == LOW)
    {
      note[index] = 262;
      timenote[index] = millis() - timecount;
      timecount = millis() + 1;
      tone(2, 262, 150); // เสียงโด
      Serial.println("DO");
      index++;
    }
    if (digitalRead(6) == LOW)
    {
      note[index] = 294;
      timenote[index] = millis() - timecount;
      timecount = millis() + 1;
      tone(2, 294, 150); // เสียงเร
      Serial.println("RE");
      index++;
    }
    if (digitalRead(7) == LOW)
    {
      note[index] = 330;
      timenote[index] = millis() - timecount;
      timecount = millis() + 1;
      tone(2, 330, 150); // เสียงมี
      Serial.println("MI");
      index++;
    }
    if (digitalRead(8) == LOW)
    {
      note[index] = 349;
      timenote[index] = millis() - timecount;
      timecount = millis() + 1;
      tone(2, 349, 150); // เสียงฟา
      Serial.println("FA");
      index++;
    }
    if (digitalRead(9) == LOW)
    {
      note[index] = 392;
      timenote[index] = millis() - timecount;
      timecount = millis() + 1;
      tone(2, 392, 150); // เสียงซอล
      Serial.println("SOL");
      index++;
    }
    if (digitalRead(10) == LOW)
    {
      note[index] = 440;
      timenote[index] = millis() - timecount;
      timecount = millis() + 1;
      tone(2, 440, 150); // เสียงลา
      Serial.println("LA");
      index++;
    }
    if (digitalRead(11) == LOW)
    {
      note[index] = 494;
      timenote[index] = millis() - timecount;
      timecount = millis() + 1;
      tone(2, 494, 150); // เสียงที
      Serial.println("TE");
      index++;
    }
    debo = millis();
  }
}
