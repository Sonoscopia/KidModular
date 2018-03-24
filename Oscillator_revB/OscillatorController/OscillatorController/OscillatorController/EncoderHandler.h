#ifndef _ENCODERHANDLER_H
#define _ENCODERHANDLER_H

#include "Arduino.h"
#include "Rotary.h"

class EncoderHandler: public Rotary {
public: 
    boolean changed;

    EncoderHandler();
    
    void init(Rotary* r, byte bP);
    void setMulF(float bM, float nM);
	void setMulN(byte bM, byte nM);
    void setValueF(float* v, float min, float max);
    void setValueN(byte* v, byte min, byte max);

private: 
	Rotary* enc;
    byte bPin;
    float bMulF;
    float nMulF;
	byte bMulN;
	byte nMulN;
	unsigned char result;
	boolean button; // is encoder button pressed ? 
	
	float returnMulF(boolean m);
	float returnMulN(boolean m);
	/*float wrap(float f, float mn, float mx); */
	float clipF(float f, float mn, float mx);
	byte clipN(byte b, byte mn, byte mx);
};

#endif //_ENCODERHANDLER_H