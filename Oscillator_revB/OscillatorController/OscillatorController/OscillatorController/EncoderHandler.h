#ifndef _ENCODERHANDLER_H
#define _ENCODERHANDLER_H

#include "Arduino.h"
#include "Encoder.h"

class EncoderHandler: public Encoder {
public: 
    boolean changed;

    EncoderHandler();
    
    void init(Encoder* e, byte bP);
    void setMul(float bM, float nM);
    void setValue(float* v, float min, float max);
    void setValue(byte* v, byte min, byte max);

private: 
	Encoder* enc;
    byte bPin;
    float bMul;
    float nMul;
};

#endif //_ENCODERHANDLER_H