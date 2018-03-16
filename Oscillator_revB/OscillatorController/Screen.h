#ifndef SCREEN_H
#define SCREEN_H

#include "Arduino.h"
#include <UTFT.h>
#include "Controls.h"

class Screen{ 
  public: 
    // METHODS
    Screen(); // default constructor
    Screen(UTFT _lcd, uint8_t _bF[], uint8_t _sF[]); // default constructor
    void init(params_t *p); // initialize screen
    void updateMenu();
    void draw(); // render screen
    
    // ATTRIBUTES
    
  private:
    // METHODS
    void drawMenus();
    void drawTopMenu();
    void drawBottomMenu();
    void drawValues();
    
    // ATTRIBUTES
    UTFT mLCD; // my UTFT object
    uint8_t *bigFont, *smallFont; 
    int width, height;
    // top menu variables
    byte menuHeight, topMenuWidth, bottomMenuWidth, menuStroke;  
    const String label[5];
    boolean isSelected[5]; 
    boolean menuChange, valueChange;

    params_t *mParams;
     
    String waveforms[4] = {"SINE", "SQR", "TRI", "SAW"};
    String oscilLabels[4] = {"OSC:", "Freq:", "LFO:", "Freq:"};
};
#endif
