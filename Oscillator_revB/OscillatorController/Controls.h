#ifndef CONTROLS_H
#define CONTROLS_H

#include "Arduino.h"

// PIN definitions
#define MENUPIN 14

class Controls{
  public:
    // METHODS
    Controls();
    void init();
    void update();
    // ATTRIBUTES
    boolean menuChanged; // trigger function once when menu button is pressed

  private: 
    // METHODS
    
    // ATTRIBUTES
    boolean menu_button[2];
    
        
};
#endif
