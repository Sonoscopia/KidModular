#include "EncoderHandler.h"

/**
 * EncoderHandler implementation
 * 
 * This class provides additional functionality to the Encoder library
 */

EncoderHandler::EncoderHandler(){
	bMulF = 1.f;
	nMulF = 10.f;
	bMulN = 1;
	nMulN = 4;  
}

void EncoderHandler::init(Rotary* r, byte bP) {
	enc = r; 
	bPin = bP;
	pinMode(bPin, INPUT_PULLUP);
}

void EncoderHandler::setMulF(float bM, float nM) {
	bMulF = bM;
	nMulF = nM;
}

void EncoderHandler::setMulN(byte bM, byte nM) {
	bMulN = bM;
	nMulN = nM;
}

void EncoderHandler::setValueF(float* v, float min, float max) {
	button = digitalRead(bPin);
	
	result = enc->process();
	if(result == DIR_CW){
		*v += returnMulF(button);
		*v = clipF(*v, min, max);
		changed = true;
	}
	if(result == DIR_CCW){
		*v -= returnMulF(button);
		*v = clipF(*v, min, max);
		changed = true;
	}
	//changed = false; // --> set from outside (where?)
}

void EncoderHandler::setValueN(int* v, int min, int max) {
	button = digitalRead(bPin);
	
	result = enc->process();
	if(result == DIR_CW){
		*v += returnMulN(button);
		*v = clipN(*v, min, max);
		changed = true;
	}
	if(result == DIR_CCW){
		*v -= returnMulN(button);
		*v = clipN(*v, min, max);
		changed = true;
	}
	//changed = false; // --> set from outside (where?)
}

void EncoderHandler::setValueN(int8_t* v, int8_t min, int8_t max) {
	button = digitalRead(bPin);
	
	result = enc->process();
	if(result == DIR_CW){
		*v += returnMulN(button);
		*v = clipN(*v, min, max);
		changed = true;
	}
	if(result == DIR_CCW){
		*v -= returnMulN(button);
		*v = clipN(*v, min, max);
		changed = true;
	}
	//changed = false; // --> set from outside (where?)
}

void EncoderHandler::setValueN(uint8_t* v, uint8_t min, uint8_t max) {
	button = digitalRead(bPin);
	
	result = enc->process();
	if(result == DIR_CW){
		*v += returnMulN(button);
		*v = clipN(*v, min, max);
		changed = true;
	}
	if(result == DIR_CCW){
		*v -= returnMulN(button);
		*v = clipN(*v, min, max);
		changed = true;
	}
	//changed = false; // --> set from outside (where?)
}

float EncoderHandler::clipF(float f, float mn, float mx){
	if(f < mn){
		return mn;
	}
	else{
		if(f>mx) return mx;
		else return f;
	}
}

byte EncoderHandler::clipN(byte f, byte mn, byte mx){
	if(f < mn){
		return mn;
	}
	else{
		if(f>mx) return mx;
		else return f;
	}
}

float EncoderHandler::returnMulF(boolean m){ // mode, bMul, nMul
	if(m) return nMulF;
	else return bMulF;
}

float EncoderHandler::returnMulN(boolean m){ // mode, bMul, nMul
	if(m) return nMulN;
	else return bMulN;
}

/*float EncoderHandler::wrap(float f, float mn, float mx){
	if(f < mn) return mx-(mn-f);
	if(f > mx) return mn+(f-mx); 
}*/

