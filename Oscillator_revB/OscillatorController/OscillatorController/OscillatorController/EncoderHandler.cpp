#include "EncoderHandler.h"

/**
 * EncoderHandler implementation
 * 
 * This class provides additional functionality to the Encoder library
 */

EncoderHandler::EncoderHandler(){
	pos[0] = 0; //new position
	pos[1] = 0; //old position
	bMulF = 1.f;
	nMulF = 0.25f;
	bMulN = 1;
	nMulN = 4;  
}

void EncoderHandler::init(Encoder* e, byte bP) {
	enc = e; 
	bPin = bP;
	pinMode(bPin, INPUT_PULLUP);
}

void EncoderHandler::setMulF(float bM, float nM) {
	bMulF = bM;
	//nMul = nM*0.25;
	nMulF = nM;
}

void EncoderHandler::setMulN(byte bM, byte nM) {
	bMulN = bM;
	//nMul = nM*0.25;
	nMulN = nM;
}

void EncoderHandler::setValueF(float* v, float min, float max) {
	button = digitalRead(bPin);
	
	pos[0] = enc->read();
	
	if(pos[0]>pos[1]){
		Serial.print("encoder pos: ");
		Serial.println(pos[0]);
		*v += returnMulF(button);
		*v = clipF(*v, min, max);
		pos[1] = pos[0];
		changed = true;
		Serial.print("enc val: ");
		Serial.println(*v);
	}
	if(pos[0]<pos[1]){
		Serial.print("encoder pos: ");
		Serial.println(pos[0]);
		*v -= returnMulF(button);
		*v = clipF(*v, min, max);
		pos[1] = pos[0];
		changed = true;
		Serial.print("enc val: ");
		Serial.println(*v);
	}
	//changed = false; // --> set from outside (where?)
}

void EncoderHandler::setValueN(byte* v, byte min, byte max) {
	button = digitalRead(bPin);
	
	pos[0] = enc->read();
	if(pos[0]>pos[1]){
		Serial.print("encoder pos: ");
		Serial.println(pos[0]);
		*v += returnMulN(button);
		*v = clipN(*v, min, max);
		pos[1] = pos[0];
		changed = true;
		Serial.print("enc val: ");
		Serial.println(*v);
	}
	if(pos[0]<pos[1]){
		Serial.print("encoder pos: ");
		Serial.println(pos[0]);
		*v -= returnMulN(button);
		*v = clipN(*v, min, max);
		pos[1] = pos[0];
		changed = true;
		Serial.print("enc val: ");
		Serial.println(*v);
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

