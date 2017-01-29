#include "Screen.h"

Screen::Screen() {
  // default constructor
}

Screen::Screen(UTFT _lcd, uint8_t font[]) {
  // pass class objects
  mLCD = _lcd; 
  mFont = font; 
}

void Screen::init(){
  mLCD.InitLCD();
  mLCD.setFont(mFont);
  mLCD.fillScr(VGA_BLACK); // set background color
}
