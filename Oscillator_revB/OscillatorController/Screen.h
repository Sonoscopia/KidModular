#ifndef SCREEN_H
#define SCREEN_H

#include "Arduino.h"
#include <UTFT.h>
#include "Controls.h"

class Screen{ 
  public: 
    // METHODS
    Screen(); // default constructor
    Screen(UTFT _lcd, uint8_t _f[]); // default constructor
    void init(params_t *p); // initialize screen
    void updateMenu();
    void draw(); // render screen
    
    // ATTRIBUTES
    
  private:
    // METHODS
    void drawTopMenu();
    void drawBottomMenu();
    void oscilMenu();
    
    // ATTRIBUTES
    UTFT mLCD; // my UTFT object
    uint8_t *mFont; 
    int width;
    // top menu variables
    byte menuHeight, menuWidth;
    byte menuStroke;  
    const String label[5];
    boolean isSelected[5]; 
    boolean menuChange;

    params_t *mParams;
     
    String waveforms[4] = {"SINE", "SQR", "TRI", "SAW"};
};
#endif
