#include "EncoderHandler.h"

/**
 * EncoderHandler implementation
 * 
 * This class provides additional functionality to the Encoder library
 */

EncoderHandler::EncoderHandler(){
	bMul_u16t = 1;
	nMul_u16t = 10;
	bMul_u8t = 1;
	nMul_u8t = 10;
	bMul_s8t = 1;
	nMul_s8t = 10; 
}

void EncoderHandler::init(Rotary* r, byte bP) {
	enc = r; 
	bPin = bP;
	pinMode(bPin, INPUT_PULLUP);
}

/*void EncoderHandler::setMulF(float bM, float nM) {
	bMulF = bM;
	nMulF = nM;
}*/

void EncoderHandler::setMul_u16t(uint16_t bM, uint16_t nM) {
	bMul_u16t = bM;
	nMul_u16t = nM;
}

void EncoderHandler::setMulN_u8t(uint8_t bM, uint8_t nM) {
	bMul_u8t = bM;
	nMul_u8t = nM;
}

void EncoderHandler::setMulN_s8t(int8_t bM, int8_t nM) {
	bMul_s8t = bM;
	nMul_s8t = nM;
}

/*void EncoderHandler::setValueF(float* v, float min, float max) {
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
}*/

void EncoderHandler::setValue_u16t(uint16_t* v, uint16_t min, uint16_t max) {
	button = digitalRead(bPin);
	
	result = enc->process();
	if(result == DIR_CW){
		*v += returnMul_u16t(button);
		*v = clip_u16t(*v, min, max);
		changed = true;
	}
	if(result == DIR_CCW){
		*v -= returnMul_u16t(button);
		*v = clip_u16t(*v, min, max);
		changed = true;
	}
	//changed = false; // --> set from outside (where?)
}

void EncoderHandler::setValue_s8t(int8_t* v, int8_t min, int8_t max) {
	button = digitalRead(bPin);
	
	result = enc->process();
	if(result == DIR_CW){
		*v += returnMul_s8t(button);
		*v = clip_s8t(*v, min, max);
		changed = true;
	}
	if(result == DIR_CCW){
		*v -= returnMul_s8t(button);
		*v = clip_s8t(*v, min, max);
		changed = true;
	}
	//changed = false; // --> set from outside (where?)
}

void EncoderHandler::setValue_u8t(uint8_t* v, uint8_t min, uint8_t max) {
	button = digitalRead(bPin);
	result = enc->process();
	if(result == DIR_CW){
		*v += returnMul_u8t(button);
		*v = clip_u8t(*v, min, max);
		changed = true;
	}
	if(result == DIR_CCW){
		*v -= returnMul_u8t(button);
		*v = clip_u8t(*v, min, max);
		changed = true;
	}
	//changed = false; // --> set from outside (where?)
}

/*float EncoderHandler::clipF(float f, float mn, float mx){
	if(f < mn){
		return mn;
	}
	else{
		if(f>mx) return mx;
		else return f;
	}
}*/

uint16_t EncoderHandler::clip_u16t(uint16_t v, uint16_t mn, uint16_t mx){
	if(v < mn){
		return mn;
	}
	else{
		if(v>mx) return mx;
		else return v;
	}
}

uint8_t EncoderHandler::clip_u8t(uint8_t v, uint8_t mn, uint8_t mx){
	if(v < mn){
		return mn;
	}
	else{
		if(v>mx) return mx;
		else return v;
	}
}

int8_t EncoderHandler::clip_s8t(int8_t v, int8_t mn, int8_t mx){
	if(v < mn){
		return mn;
	}
	else{
		if(v>mx) return mx;
		else return v;
	}
}

/*float EncoderHandler::returnMulF(boolean m){ // mode, bMul, nMul
	if(m) return nMulF;
	else return bMulF;
}*/

uint16_t EncoderHandler::returnMul_u16t(boolean m){ // mode, bMul, nMul
	if(m) return nMul_u16t;
	else return bMul_u16t;
}

uint8_t EncoderHandler::returnMul_u8t(boolean m){ // mode, bMul, nMul
	if(m) return nMul_u8t;
	else return bMul_u8t;
}

int8_t EncoderHandler::returnMul_s8t(boolean m){ // mode, bMul, nMul
	if(m) return nMul_s8t;
	else return bMul_s8t;
}

/*float EncoderHandler::wrap(float f, float mn, float mx){
	if(f < mn) return mx-(mn-f);
	if(f > mx) return mn+(f-mx); 
}*/

