#include "Control.h"

/**
 * Control implementation
 * 
 * This class handles hardware control (except for the LCD which is controlled in the Screen class)
 */

Control::Control() {

}

void Control::init(params_t *p) {
	paramsPtr = p;
	enc1 = new Encoder(ENC1L, ENC1R);
	enc1h.init(enc1, ENC1B);
}

void Control::read() {
	//Serial.println(enc1->read());
	float val = 0.f;
	float* valPtr = &val;
	enc1h.setValue(valPtr, 0.f, 100.f);
}

void Control::readButton() {

}

void Control::incMenu() {

}

void Control::sendI2C() {

}

void Control::storePreset() {

}

void Control::loadPreset() {

}