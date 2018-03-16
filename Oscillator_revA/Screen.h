#ifndef SCREEN_H
#define SCREEN_H

#include <UTFT.h>

#define WIDTH 479
#define HEIGHT 319
#define ZERO 0
#define BUFSIZE 60
#define COLOR VGA_RED

class Screen{
  public:
  // functions
  Screen(); // default constructor
  Screen(UTFT _lcd, uint8_t font[]);
  void init(boolean *m, prog_uchar *_table);
  void drawDisplay();
  void drawParams();
  // setters
  void setFrequency(double *f, uint8_t *mul); // only needs to be called on setup()
  void setMode(boolean *m); // only needs to be called on setup();
  void setADSR(uint16_t *a, uint16_t *d, uint8_t *s, uint16_t *r); // only needs to be called on setup();
  void setWaveform(prog_uchar *_table);
  // variables
  uint8_t sig; // oscillator signal sample
  
  
  private:
  // functions
  void drawFrames(); //  
  void drawScopeLabels(); // mode1=scope, mode0=envelope
  void drawEnvLabels();
  void drawScope();
  void drawEnvelope();
  void printFrequency();
  void printFreqMul();
  // objects
  UTFT mLCD;
  uint8_t *mFont;
  boolean *mMode, pMode; // current mode and previous mode
  prog_uchar *mTable;
  double *mFreq; // frequency (and others) are pointers so there is no need to set/update
  uint8_t *fMuli; // freq. mult. index
  
  // variables
  uint16_t x, y, _y; // x-y and previous positions
  float head; // head to read buffer
};

#endif 
