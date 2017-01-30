#ifndef SCREEN_H
#define SCREEN_H

#include <UTFT.h>

#define WIDTH 479
#define HEIGHT 319
#define ZERO 0
#define BUFSIZE 60
#define COLOR VGA_MAROON

class Screen{
  public:
  // functions
  Screen(); // default constructor
  Screen(UTFT _lcd, uint8_t font[]);
  void init();
  void drawScope(prog_uchar *_table, double _freq);
  void printFreq(double _freq);
  void printFreqMul(uint8_t _index);
  
  // objects
  UTFT mLCD;
  uint8_t *mFont; 
  // variables
  uint8_t sig; // oscillator signal sample
  
  
  private:
  // functions
  void drawFrames();  
  void drawLabels(); // mode1=scope, mode0=envelope
  // variables
  uint16_t x, y, _y; // x-y and previous positions
  float head; // head to read buffer

};

#endif 
