#include <iBotC.h>
int RGB_color ;
int find_color ;
void track0()
{
  while (true)
  {
    int s0 = sensor0();
    int s1 = sensor1();
    int s2 = sensor2();
    int s3 = sensor3();

    if (s0 == 1 && s1 == 1 && s2 == 1 && s3 == 0)
    {
      Lchk();
    }
    else if (s0 == 0 && s1 == 1 && s2 == 1 && s3 == 1)
    {
      Rchk();
    }
    else if (s0 == 0 && s1 == 0 && s2 == 0 && s3 == 1 || s0 == 0 && s1 == 0 && s2 == 1 && s3 == 1)
    {
      motor(200, 50, 100);
    }
    else if (s0 == 1 && s1 == 0 && s2 == 0 && s3 == 0 || s0 == 1 && s1 == 1 && s2 == 0 && s3 == 0)
    {
      motor(50, 200, 100);
    }
    else if (s0 == 1 && s1 == 1 && s2 == 1 && s3 == 1)
    {
      motor(0, 0);
      break;
    }
    else if (s0 == 0 && s1 == 0 && s2 == 0 && s3 == 0)
    {
      motor(-150, -150);
    }
    else if (s0 == 0 && s1 == 1 && s2 == 1 && s3 == 0)
    {
      motor(100, 100, 100);
    }
    else if (s0 == 0 && s1 == 0 && s2 == 1 && s3 == 0)
    {
      motor(200, 100, 100);
    }
    else if (s0 == 0 && s1 == 1 && s2 == 0 && s3 == 0)
    {
      motor(100, 200, 100);
    }
  }
}
void track()
{
  while (true)
  {
    int s0 = sensor0();
    int s1 = sensor1();
    int s2 = sensor2();
    int s3 = sensor3();

    if (s0 == 1 && s3 == 1)
    {
      motor(0, 0);
      break;
    }
    if (s0 == 0 && s1 == 0 && s2 == 0 && s3 == 0 || s0 == 1 && s1 == 1 && s2 == 0 && s3 == 0 || s0 ==  0 && s1 == 0 && s2 == 1 && s3 == 1)
    {
      motor(-150, -150, 125);
    }
    if (s0 == 0 && s1 == 1 && s2 == 1 && s3 == 0 || s0 == 1 && s1 == 1 && s2 == 1 && s3 == 0 || s0 == 0 && s1 == 1 && s2 == 1 && s3 == 1 )
    {
      motor(130, 130, 125);
    }
    if (s0 == 0 && s1 == 0 && s2 == 1 && s3 == 0)
    {
      motor(200, 100, 125);
    }
    if (s0 == 0 && s1 == 1 && s2 == 0 && s3 == 0)
    {
      motor(100, 200, 125);
    }
    if (s0 == 1 && s1 == 0 && s2 == 0 && s3 == 0 ) {
      motor(80, 200, 225);
    }
    if (s0 ==  0 && s1 == 0 && s2 == 0 && s3 == 1 ) {
      motor(200, 80, 225);
    }

  }
}

void Rchk()
{
  motor(150, 150, 200);
  motor(100, -100, 350);
  while (true)
  {
    int s0 = sensor0();
    int s1 = sensor1();
    int s2 = sensor2();
    int s3 = sensor3();

    motor(150, -150);
    if (s2 == 1) {
      motor(100, 150, 200);
      motor(0, 0);
      break;
    }
  }
}

void Lchk()
{
  motor(150, 150, 200);
  motor(-100, 100, 350);
  while (true)
  {
    int s0 = sensor0();
    int s1 = sensor1();
    int s2 = sensor2();
    int s3 = sensor3();

    motor(-150, 150);
    if (s1 == 1 && s2 == 1) {
      (150, 100, 200);
      motor(0, 0);
      break;
    }
  }
}
int Utlchk()
{
  int u;
  int distance;
  distance = ultraSonic();
  if (distance <= 15)
  {
    u = 1;
  }
  else
  {
    u = 2;
  }
  return (u);
}
void kick() {
  motor(200, 200, 1000);
  motor(-150, -150, 700);
}
void setup()
{
  iBotC();
  waitButton();
  track();
  if (Utlchk() == 1)
  {
    beep();
    Rchk();
    track();
    beep();
    Lchk();
    track();
    beep();
    motor(150, 150, 250);
    track();
  }
  else if ( Utlchk() == 2)
  { beep();
    motor(150, 150, 250);
    track();
    beep();
    Rchk();
    track();
    beep();
    Lchk();
    track();
  }
  led("Magenta");
  kick();
  Rchk();
  track();
  motor(150, 150, 500);
  motor(0, 0);
  scancolor();
  Lchk();
  track0();
  motor(150, 150, 500);
  motor(0, 0, 500);
  color_is();
  Rchk();
  track();
  if (RGB_color == color_is)
  {
    kick();

  }
  Rchk();
  track();
  motor(150, 150, 500);
  motor(0, 0, 500);
  color_is();
  if (RGB_color == color_is)
  {
    Lchk();
    kick();
    Rchk();
  }
  track();
  motor(150, 150, 500);
  motor(0, 0, 500);
  color_is();
  if (RGB_color == color_is)
  {
    Lchk();
    kick();
    Rchk();
  }
  track();
  motor(150, 150, 500);
  motor(0, 0, 500);
  color_is();
  if (RGB_color == color_is)
  {
    Lchk();
    kick();
    Rchk();
  }
  track();
  motor(150, 150, 500);
  motor(0, 0, 500);
  color_is();
  if (RGB_color == color_is)
  {
    Lchk();
    kick();
    Rchk();
  }
}
void scancolor() {
  String scan = readColor();

  if (scan == "Red")
  {
    led("Red");
    RGB_color = 1;
  }
  if (scan == "Yellow")
  {
    led("Yellow");
    RGB_color = 2;
  }
  if (scan == "Green")
  {
    led("Green");
    RGB_color = 3;
  }
}
void  color_is() {
  String scan = readColor();

  if (scan == "Red")
  {
    led("Red");
    find_color = 1;
  }
  if (scan == "Yellow")
  {
    led("Yellow");
    find_color = 2;
  }
  if (scan == "Green")
  {
    led("Green");
    find_color = 3;
  }
}

void loop()
{

}
