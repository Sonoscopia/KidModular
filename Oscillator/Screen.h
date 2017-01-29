#ifndef SCREEN_H
#define SCREEN_H

#include <UTFT.h>

class Screen{
  public:
  // functions
  Screen(); // default constructor
  Screen(UTFT _lcd, uint8_t font[]);
  void init();
  // objects
  UTFT mLCD;
  uint8_t *mFont; 
  
  private:
  
};

#endif 
