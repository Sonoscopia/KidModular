#include "Screen.h"

const String fMul[8] = {"0.1", "1  ", "2  ", "5  ", "10 ", "20 ", "50 ", "100"}; // frequency multipliers
//const String fMul[] = {"1/24", "1/12", "1/8 ", "1/6 ", "1/4 ", "1/3 ", "1/2 ", "2   "}; // frequency multipliers


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
  // Static draws 
  drawFrames();
  drawLabels();
}

void Screen::drawFrames(){
  // TOP
  mLCD.setColor(COLOR);
  mLCD.fillRect(0, HEIGHT-66, 117, HEIGHT-46);
  mLCD.fillRect(120, HEIGHT-66, 237, HEIGHT-46);
  mLCD.fillRect(240, HEIGHT-66, 357, HEIGHT-46);
  mLCD.fillRect(360, HEIGHT-66, WIDTH, HEIGHT-46);
  // MIDDLE
  mLCD.setColor(COLOR);
  mLCD.drawRect(0, HEIGHT-44, 117, HEIGHT-24);
  mLCD.drawRect(120, HEIGHT-44, 237, HEIGHT-24);
  mLCD.drawRect(240, HEIGHT-44, 357, HEIGHT-24);
  mLCD.drawRect(360, HEIGHT-44, WIDTH, HEIGHT-24);
  // BOTTOM
  mLCD.setColor(COLOR);
  mLCD.fillRect(0, HEIGHT-22, 117, HEIGHT-2);
  mLCD.fillRect(120, HEIGHT-22, 237, HEIGHT-2);
  mLCD.fillRect(240, HEIGHT-22, 357, HEIGHT-2);
  mLCD.fillRect(360, HEIGHT-22, WIDTH, HEIGHT-2);
}

void Screen::drawLabels(){
  // TOP
  mLCD.setBackColor(COLOR);
  mLCD.setColor(VGA_BLACK);
  mLCD.print("Freq", 2, HEIGHT-63);
  mLCD.print("FX", 122, HEIGHT-63);
  mLCD.print("Filter", 242, HEIGHT-63);
  mLCD.print("Res", 362, HEIGHT-63);
  // MIDDLE
  mLCD.setBackColor(VGA_BLACK);
  mLCD.setColor(COLOR);
  mLCD.print("x ", 2, HEIGHT-43);
  mLCD.print("x ", 122, HEIGHT-43);
  mLCD.print("x ", 242, HEIGHT-43);
  mLCD.print("x ", 362, HEIGHT-43);
}

void Screen::printFreq(double _freq){
  mLCD.setBackColor(COLOR);
  mLCD.setColor(VGA_BLACK);
  mLCD.printNumI((int)_freq, 2, HEIGHT-20);
}

void Screen::printFreqMul(uint8_t _index){
  mLCD.setBackColor(VGA_BLACK);
  mLCD.setColor(COLOR);
//  if(_index > 0) mLCD.printNumI(freqMul[_index], 2, HEIGHT-43);
//  else mLCD.print("0.1", 2, HEIGHT-43);
  mLCD.print(fMul[_index], 18, HEIGHT-43);
}

void Screen::drawScope(prog_uchar *_table, double _freq){
  // Draw buffer according to frequency
  //clear
  mLCD.setColor(VGA_BLACK);
  mLCD.drawLine(x, ZERO, x, HEIGHT-68);
  // draw signal
  head+= _freq/BUFSIZE;
  if(head > 255) head = 0;
  y = 220 - pgm_read_byte_near(_table + (int)head) * 0.75; 
  mLCD.setColor(COLOR);
  if(x > 0) mLCD.drawLine(x-1,_y, x, y);
  _y = y;

  // reset
  if(x++ > WIDTH) {
    x=ZERO;
  }
}
