// PseudoCode (Arduino MEGA)
#include <UTFT.h>
#include "Controls.h"
#include "Screen.h"

#define DEBUG 1

params_t params = {0, 0, 220.f, 0, 2.f}; 
Controls controls;
// screen
UTFT lcd(CTE32HR,38,39,40,41);
extern uint8_t BigFont[]; 
extern uint8_t SmallFont[]; 
Screen screen(lcd, BigFont, SmallFont);


void setup(){
  if(DEBUG) Serial.begin(9600);
  //setI2C();
  controls.init(&params);  
  screen.init(&params); // setup screen 
}

void loop(){
  controls.update();
  //sendI2C();
  // update screen
  if(controls.menuChanged) screen.updateMenu();  
  screen.draw(); // render screen   
}
