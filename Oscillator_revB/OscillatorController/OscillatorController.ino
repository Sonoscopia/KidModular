// Oscillator Controller code (Arduino MEGA)
#include <UTFT.h>
#include <Encoder.h>
#include "Controls.h"
#include "Screen.h"

#define DEBUG 1

params_t params = {0, 0, 220.f, 0, 2.f}; 
Controls controls;
Encoder enc1(ENC1L, ENC1R), enc2(ENC2L, ENC2R), enc3(ENC3L, ENC3R), enc4(ENC4L, ENC4R);

// screen
UTFT lcd(CTE32HR,38,39,40,41);
extern uint8_t BigFont[]; 
extern uint8_t SmallFont[]; 
Screen screen(lcd, BigFont, SmallFont);


void setup(){
  if(DEBUG) Serial.begin(9600);
  //setI2C();
  controls.init(&params);  
  controls.encoder2.init(&enc2, ENC2B);
  screen.init(&params); // setup screen 
}

void loop(){
  controls.update();
  //sendI2C();
  // update screen
  if(controls.menuChanged) screen.updateMenu();  
  screen.draw(); // render screen   
}
