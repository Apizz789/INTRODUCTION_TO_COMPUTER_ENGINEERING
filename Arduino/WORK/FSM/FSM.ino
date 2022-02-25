#define LED_F_R 7
#define LED_F_Y 6
#define LED_F_G 5

#define LED_S_R 10
#define LED_S_Y 9
#define LED_S_G 8

#define HM_R 12
#define HM_G 11

#define F_Button 2
#define S_Button 3
#define HM_Button 4
//----------------------------------------//
#define goF 0
#define waitF 1

#define goS 2
#define waitS 3

#define waitHM 7
#define goHM 4
#define goHM1 5
#define goHM2 6

struct State {
  unsigned long ST_Out; // 6-bit pattern to street output
  unsigned long Time; // delay in ms units
  unsigned long Next[8];
}; // next state for inputs 0,1,2,3
typedef const struct State SType;

SType FSM[8] =
{                      // 000   001   010    011    100   101    110    111
  {B00110001, 1000,     {goF , waitF, waitF, waitF , goF, waitF , waitF, waitF}}, //0 F
  {0xF1, 500,           {waitF,  goHM , goS , goS, goF , goHM,  goS, goS}}, //1 wait F1
  
  {0x85, 1000,          {goS,  waitS, goS, waitS, waitS, waitS , waitS, waitS}}, //2 S
  {0x9D, 500,           {waitS , goHM , goS , goHM , goF , goHM , goF , goHM}}, //3 waitS 9D

  {0x92, 500,           {goHM, goHM , goHM1, goHM1, goHM1, goHM1 , goHM1, goHM1}}, // WALK
  
  {B10010000, 500,      {goHM2, goHM2 , goHM2 , goHM2 , goHM2 , goHM2, goHM2, goHM2}}, //5 KAPIB
  {0x92, 500,           {waitHM , waitHM , waitHM  , waitHM , waitHM , waitHM,  waitHM , waitHM}}, //6
  
  {0x90, 500,           {goF , goHM  , goS , goS , goF, goF, goF , goF}} //7
  
};

unsigned long S = 0; // index to the current state
void setup() 
{
  
  pinMode(LED_F_R, OUTPUT);
  pinMode(LED_F_Y, OUTPUT);
  pinMode(LED_F_G, OUTPUT);
  pinMode(F_Button, INPUT_PULLUP);
  pinMode(LED_S_R, OUTPUT);
  pinMode(LED_S_Y, OUTPUT);
  pinMode(LED_S_G, OUTPUT);
  pinMode(S_Button, INPUT_PULLUP);
  pinMode(HM_R, OUTPUT);
  pinMode(HM_G, OUTPUT);
  pinMode(HM_Button, INPUT_PULLUP);
  Serial.begin(9600);
  
}
int input, inputF, inputS, inputW;
void loop()
{
  digitalWrite(LED_F_G,   FSM[S].ST_Out &    B10000000);
  digitalWrite(LED_F_Y, !(FSM[S].ST_Out &    B01000000));
  digitalWrite(LED_F_R,   FSM[S].ST_Out &    B00100000);

  digitalWrite(LED_S_G,    FSM[S].ST_Out &   B00010000);
  digitalWrite(LED_S_Y,  !(FSM[S].ST_Out &   B00001000));
  digitalWrite(LED_S_R,    FSM[S].ST_Out &   B00000100);

  digitalWrite(HM_G, !(FSM[S].ST_Out &       B00000010));
  digitalWrite(HM_R, !(FSM[S].ST_Out &       B00000001));
  delay(FSM[S].Time);
  
  if(S != waitF && S != waitS && S != goHM1 && S != waitHM && S != goHM2  )
  {
  input = 0 ;
  inputF = !digitalRead(F_Button);
  inputS = !digitalRead(S_Button);
  inputW = !digitalRead(HM_Button);
  input = inputF * 4 + inputS * 2 + inputW;
  }
  Serial.println(input);
  S = FSM[S].Next[input];
}
