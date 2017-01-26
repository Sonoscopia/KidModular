// simple (real-time) sinewave refresh and draw 

// test LCD screen dimensions with 2 pots connected on A0 and A1 (x, y)

#include <UTFT.h>

int px=0, x=1;
float py=0, y=0;
float sinewave;
float inc = 0.1;

UTFT lcd(CTE32HR,38,39,40,41);

void setup(){
  Serial.begin(9600);
  lcd.InitLCD(LANDSCAPE);
  lcd.clrScr();
}

void loop(){
  if(Serial.available() > 0){
    inc = Serial.parseFloat();
    Serial.println(inc);
  }
  
  // draw sine behind
  lcd.setColor(VGA_RED);
  sinewave+= inc; 
  if(sinewave>6.28) sinewave = 0.f;
  py = y;
  y = 160-(sin(sinewave) * 80.f);
  
  x++;
  if(x > 479) x = 0;
  px = x-1;  
  lcd.drawLine(px, py, x, y);
  
  //clear vertical line ahead
  lcd.setColor(VGA_BLACK);
  if(x<1) lcd.drawLine(0, 0, 0, 319);
  lcd.drawLine(x+1, 0, x+1, 319);
  
  delay(5);
}
