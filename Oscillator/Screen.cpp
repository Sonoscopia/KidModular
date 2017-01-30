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
  // Init variables
  head = 0;
  y = 0;
}

void Screen::drawScope(prog_uchar *_table, double _freq){
  // Draw buffer according to frequency
  //clear
  mLCD.setColor(VGA_BLACK);
  mLCD.drawLine(x, ZERO, x, HEIGHT);
  // draw signal
  head+= _freq/20;
  if(head > 255) head = 0;
  y = 250 - pgm_read_byte_near(_table + (int)head) * 0.75; 
  mLCD.setColor(VGA_MAROON);
  if(x > 0) mLCD.drawLine(x-1,_y, x, y);
  _y = y;

  // reset
  if(x++ > WIDTH) {
    x=ZERO;
  }
}

