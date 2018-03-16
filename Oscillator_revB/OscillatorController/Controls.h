#ifndef CONTROLS_H
#define CONTROLS_H

#include "Arduino.h"
#include "Parameters.h"

// PIN definitions
#define MENUPIN 14

class Controls{
  public:
    // METHODS
    Controls();
    void init(params_t *p);
    void update();
    // ATTRIBUTES
    boolean menuChanged; // trigger function once when menu button is pressed

  private: 
    // METHODS
    void updateTopMenu();
    // ATTRIBUTES
    params_t *mParams;
    boolean menu_button[2];        
};
#endif
