#include "ST7735_TEE.h"
TEE_ST7735 lcd(9, 10, 11, 12, 13);
char firstsec[60]={'0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','8','9'};
char nextsec[60]={'0','0','0','0','0','0','0','0','0','0','1','1','1','1','1','1','1','1','1','1','2','2','2','2','2','2','2','2','2','2','3','3','3','3','3','3','3','3','3','3','4','4','4','4','4','4','4','4','4','4','5','5','5','5','5','5','5','5','5','5'};
char real_firstsec[10]={'0','1','2','3','4','5','6','7','8','9'};
char real_nextsec[6]={'0','1','2','3','4','5'};
char firsthrs[24]={'0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','8','9','0','1','2','3'};
char nexthrs[24]={'0','0','0','0','0','0','0','0','0','0','1','1','1','1','1','1','1','1','1','1','2','2','2','2'};
char datechar[10]="0123456789";
String inString = "";
long timeset,hrsset,minset,dateset;

void setup() {
  Serial.begin(9600);
  lcd.init(lcd.VERTICAL);
  pinMode(5,INPUT);
  pinMode(4,INPUT);
  pinMode(3,INPUT);
  digitalWrite(5,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(3,HIGH);
  while (!Serial) {
    ;
  }
  
  //TFT Intro
  lcd.fillScreen(BLACK);
  lcd.drawRect(3,3,122,154,WHITE);
  lcd.drawRect(8,8,112,144,WHITE);
  lcd.drawString(22,45,"Input time at ",WHITE,1);
  lcd.drawString(22,65,"Serial Monitor",WHITE,1);
  lcd.drawString(32,85,"in term of",WHITE,1);
  lcd.drawString(46,105,"DDHHMM",WHITE,1);
  
  //Program Intro
  Serial.println("Set Date & Time :");
}
void showclock() {
  delay(1000);
  lcd.fillScreen(BLACK);
  lcd.drawRect(3,3,122,154,WHITE);
  lcd.drawRect(8,8,112,144,WHITE);
  lcd.drawChar(58,90,':',WHITE,2);
  lcd.drawChar(32,120,datechar[dateset/10],BLUE,1);
  lcd.drawChar(38,120,datechar[dateset%10],BLUE,1);
  lcd.drawString(44,120," OCT 2019",BLUE,1);
  for(int e=0;e<24;e++) {
      lcd.drawChar(34,40,nexthrs[e],RED,5);
      for(int d=0;d<24;d++) {
      lcd.drawChar(66,40,firsthrs[d],RED,5);
        for(int c=0;c<60;c++) {
          lcd.drawChar(36,90,nextsec[c],GREEN,2);
          //for(int b=0;b<60;b++) {
            lcd.drawChar(48,90,firstsec[c],GREEN,2);
            for(int a=0;a<6;a++) {
              lcd.drawChar(68,90,real_nextsec[a],WHITE,2);
              for(int i=0;i<10;i++) {
                long timer;
                timer=millis();
                lcd.drawChar(80,90,real_firstsec[i],WHITE,2);
                //Serial.println(millis());
                while(millis()<timer+979) {
                  if(digitalRead(4)==LOW) {
                    Serial.println("Break");
                    break;
                  }
                }
                //delay(979); //Set Speed
                lcd.fillRect(80,90,10,14,BLACK);
              }
              lcd.fillRect(68,90,10,14,BLACK);
            }
            lcd.fillRect(48,90,10,14,BLACK);
          //}
          lcd.fillRect(36,90,10,14,BLACK);
        }
        lcd.fillRect(66,40,25,35,BLACK);
      }
      lcd.fillRect(34,40,25,35,BLACK);
  }
}
void loop() {
  // Read serial input:
  while (Serial.available() > 0) {
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char and add it to the string:
      inString += (char)inChar;
    }
    // if you get a newline, print the string, then the string's value:
    if (inChar == '\n') {
      Serial.print("Value:");
      Serial.println(inString.toInt());
      timeset=inString.toInt();
      //Array running
      //Serial.println(timeset);
      dateset=timeset/10000;
      timeset=timeset-(dateset*10000);
      hrsset=timeset/100;
      minset=timeset%100;
      Serial.print("DATE:");
      Serial.println(dateset);
      Serial.print("HRS:");
      Serial.println(hrsset);
      Serial.print("MIN:");
      Serial.println(minset);
      for(int i=0;i<minset;i++) {
        char temp=firstsec[0];
        //Serial.println(temp);
        for(int j=0;j<59;j++) {
          firstsec[j]=firstsec[j+1];
        }
        firstsec[59]=temp;
      }
      for(int i=0;i<minset;i++) {
        char temp=nextsec[0];
        //Serial.println(temp);
        for(int j=0;j<59;j++) {
          nextsec[j]=nextsec[j+1];
        }
        nextsec[59]=temp;
      }
      for(int i=0;i<hrsset;i++) {
        char temp=firsthrs[0];
        //Serial.println(temp);
        for(int j=0;j<23;j++) {
          firsthrs[j]=firsthrs[j+1];
        }
        firsthrs[23]=temp;
      }
      for(int i=0;i<hrsset;i++) {
        char temp=nexthrs[0];
        //Serial.println(temp);
        for(int j=0;j<23;j++) {
          nexthrs[j]=nexthrs[j+1];
        }
        nexthrs[23]=temp;
      }
      showclock();
      // clear the string for new input:
      inString = "";
    }
    //showclock();
  }
}
