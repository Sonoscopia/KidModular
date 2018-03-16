#ifndef ENCODERHANDLE_H
#define ENCODERHANDLE_H

#include "Arduino.h"
#include <Encoder.h> 

class EncoderHandle{
  public:
    EncoderHandle(); //default constructor
    EncoderHandle(float bm, float nm); // (button multiplier, normal mutliplier)
    void init(Encoder *e, byte bp);
    // multiplier functions 
    void setButtonMultiplier(float m);
    void setNormalMultiplier(float m);
    float inc(boolean b); // increment value
    float dec(boolean b); // decrement value 
    void setVal(float *f); // read encoder and set passed variable
    boolean changed; 

  private:     
    Encoder *enc; 
    byte bPin; 
    long pos[2];
    boolean button;
    float bMult, nMult;
};

#endif 
