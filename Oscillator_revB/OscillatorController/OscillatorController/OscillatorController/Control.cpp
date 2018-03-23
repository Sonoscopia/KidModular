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
	enc1h.setMul(1.f, 10.f);
	enc1h.setValue(&paramsPtr->oscFreq, OFMIN, OFMAX);
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