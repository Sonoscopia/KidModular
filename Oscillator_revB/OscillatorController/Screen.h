#ifndef SCREEN_H
#define SCREEN_H

#include "Arduino.h"
#include <UTFT.h>

class Screen{ 
  public: 
    // METHODS
    Screen(); // default constructor
    Screen(UTFT _lcd, uint8_t _f[]); // default constructor
    void init(); // initialize screen
    void updateMenu();
    void draw(); // render screen
    
    // ATTRIBUTES
    
  private:
    // METHODS
    void drawTopMenu();
    
    // ATTRIBUTES
    UTFT mLCD; // my UTFT object
    uint8_t *mFont; 
    int width;
    // top menu variables
    byte menuHeight, menuWidth;
    byte menuStroke;  
    const String label[5];
    boolean isSelected[5];
    byte menuInc; 
    boolean menuChange; 
};
#endif
