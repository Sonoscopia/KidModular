#include "EncoderHandler.h"

/**
 * EncoderHandler implementation
 * 
 * This class provides additional functionality to the Encoder library
 */

EncoderHandler::EncoderHandler(){
	pos[0] = 0; //new position
	pos[1] = 0; //old position
	bMul = 1.f;
	nMul = 0.25f; 
}

void EncoderHandler::init(Encoder* e, byte bP) {
	enc = e; 
	bPin = bP;
	pinMode(bPin, INPUT_PULLUP);
}

void EncoderHandler::setMul(float bM, float nM) {
	bMul = bM;
	nMul = nM*0.25;
}

void EncoderHandler::setValue(float* v, float min, float max) {
	button = digitalRead(bPin);
	//Serial.println(enc->read());
	
	pos[0] = enc->read();
	if(pos[0]>pos[1]){
		*v += returnMul(button);
		pos[1] = pos[0];
		changed = true;
		Serial.print("val: ");
		Serial.println(*v);
	}
	if(pos[0]<pos[1]){
		*v -= returnMul(button);
		pos[1] = pos[0];
		changed = true;
		Serial.print("val: ");
		Serial.println(*v);
	}
	//changed = false; // --> set from outside (where?)
	
}
void EncoderHandler::setValue(byte* v, byte min, byte max) {

}

float EncoderHandler::returnMul(boolean m){ // mode, bMul, nMul
	if(m) return nMul;
	else return bMul;
}

