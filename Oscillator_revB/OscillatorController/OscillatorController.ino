// PseudoCode (Arduino MEGA)
#include <UTFT.h>
#include "Parameters.h"
#include "Screen.h"
#include "Controls.h"

#define DEBUG 0


// Screen variables and objects
UTFT lcd(CTE32HR,38,39,40,41);
extern uint8_t BigFont[]; 
Screen screen(lcd, BigFont);
// Control object
Controls controls;

void setup(){
  if(DEBUG) Serial.begin(9600);
  //setI2C();
  controls.init();  
  screen.init(); // setup screen 
}

void loop(){
  controls.update();
  //sendI2C();
  // update screen
  if(controls.menuChanged) screen.updateMenu();  
  screen.draw(); // render screen   
}
