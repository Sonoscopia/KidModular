#include "EncoderHandler.h"

/**
 * EncoderHandler implementation
 * 
 * This class provides additional functionality to the Encoder library
 */

EncoderHandler::EncoderHandler(){
	
}

void EncoderHandler::init(Encoder* e, byte bP) {
	enc = e; 
}

void EncoderHandler::setMul(float bM, float nM) {
	
}

void EncoderHandler::setValue(float* v, float min, float max) {
	//Serial.println(enc->read());
	Serial.println(enc->read());
}

void EncoderHandler::setValue(byte* v, byte min, byte max) {

}