#ifndef SCREEN_H
#define SCREEN_H

#include <UTFT.h>

#define WIDTH 479
#define HEIGHT 319
#define ZERO 0

class Screen{
  public:
  // functions
  Screen(); // default constructor
  Screen(UTFT _lcd, uint8_t font[]);
  void init();
  void drawScope(prog_uchar *_table, double _freq);
  // objects
  UTFT mLCD;
  uint8_t *mFont; 
  uint8_t sig; // oscillator signal sample
  
  private:
  // Scope Variables
  uint16_t x, y, _y; // x-y and previous positions
  float head; // head to read buffer
};

#endif 
