#ifndef CONTROLS_H
#define CONTROLS_H

#include "Arduino.h"
#include "Parameters.h"
#include "EncoderHandle.h"

// PIN definitions
#define MENUPIN 14
// Controls - Buttons
#define MODEPIN 14 
#define ENC1B 18
#define ENC2B 17
#define ENC3B 16
#define ENC4B 15
// Controls - Encoders 
#define ENC1L 2
#define ENC1R 3
#define ENC2L 5
#define ENC2R 6
#define ENC3L 7
#define ENC3R 11
#define ENC4L 44
#define ENC4R 46

class Controls : public EncoderHandle{
  public:
    // METHODS
    Controls();
    void init(params_t *p);
    void update();
    // ATTRIBUTES
    boolean menuChanged; // trigger function once when menu button is pressed
    //encoders
    EncoderHandle encoder1, encoder2, encoder3, encoder4;
  private: 
    // METHODS
    void updateTopMenu();
    void readMenu();
    void readEncoders();
    // ATTRIBUTES
    params_t *mParams;
    boolean menu_button[2];
          
};
#endif
