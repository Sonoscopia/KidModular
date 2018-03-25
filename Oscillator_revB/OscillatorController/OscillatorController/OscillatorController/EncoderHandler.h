#ifndef _ENCODERHANDLER_H
#define _ENCODERHANDLER_H

#include "Arduino.h"
#include "Rotary.h"

class EncoderHandler: public Rotary {
public: 
    boolean changed;

    EncoderHandler();
    
    void init(Rotary* r, byte bP);
    //void setMulF(float bM, float nM);
	//void setMulN(byte bM, byte nM);
    //void setValueF(float* v, float min, float max);
    void setMul_u16t(uint16_t bM, uint16_t nM);
	void setMulN_u8t(uint8_t bM, uint8_t nM);
	void setMulN_s8t(int8_t bM, int8_t nM);
	void setValue_u16t(uint16_t* v, uint16_t min, uint16_t max);
	void setValue_u8t(uint8_t* v, uint8_t min, uint8_t max);
	void setValue_s8t(int8_t* v, int8_t min, int8_t max);
	
private: 
	Rotary* enc;
    byte bPin;
    //float bMulF;
    //float nMulF;
	uint16_t bMul_u16t;
	uint16_t nMul_u16t;
	uint8_t bMul_u8t;
	uint8_t nMul_u8t;
	int8_t bMul_s8t;
	int8_t nMul_s8t;
	int bMulN;
	int nMulN;
	unsigned char result;
	boolean button; // is encoder button pressed ? 
	
	//float returnMulF(boolean m);
	uint16_t returnMul_u16t(boolean m);
	uint8_t returnMul_u8t(boolean m);
	int8_t returnMul_s8t(boolean m);
	/*float wrap(float f, float mn, float mx); */
	//float clipF(float f, float mn, float mx);
	uint16_t clip_u16t(uint16_t v, uint16_t mn, uint16_t mx);
	uint8_t clip_u8t(uint8_t v, uint8_t mn, uint8_t mx);
	int8_t clip_s8t(int8_t v, int8_t mn, int8_t mx);	
};

#endif //_ENCODERHANDLER_H