// test LCD screen dimensions with 2 pots connected on A0 and A1 (x, y)

#include <UTFT.h>
#define DEBUG 0


int x, y;

UTFT lcd(CTE32HR,38,39,40,41);

void setup(){
  lcd.InitLCD();
  if(DEBUG)Serial.begin(9600);
  lcd.fillScr(VGA_BLACK);
}

void loop(){
  x = analogRead(A0);
  y = analogRead(A1);
  
  if(DEBUG){
    Serial.print("x: ");
    Serial.print(x);
    Serial.print(" | y: ");
    Serial.println(y);
  }
  
  
//  lcd.fillScr(VGA_BLACK);
  //lcd.clrScr();
  lcd.setColor(VGA_GREEN);
  lcd.fillRect(0, 0, x, y);
  
  delay(50);
}
