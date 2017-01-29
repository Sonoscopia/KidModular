#ifndef SCREEN_H
#define SCREEN_H

#include "Arduino.h"
#include <UTFT.h>

#define WIDTH 480
#define HEIGHT 320
#define RADIUS 140 // gemetric shapes radius
#define STEPRADIUS 8 // step circle radius

class Screen {
public: 
  // functions
  Screen(); // default constructor
  Screen(UTFT _lcd, uint8_t font[]);
  void init();
  void printBPM(uint16_t _bpm);
  void printSize(uint8_t _numSteps);
  void printDur(uint8_t _dur[], uint8_t _stepEdit);
  void drawShape(uint8_t _numSteps);
  // objects
  UTFT mLCD;
  uint8_t *mFont; 
  // variables
  uint16_t center[2];
  String bpmText;

private:
  // functions
  void drawLabels(); // draw initial parameter labels
  void drawCircFrame(); // draw circular frame where geometric shapes are drawn

  
};

#endif
