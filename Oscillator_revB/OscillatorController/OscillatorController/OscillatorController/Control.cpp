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
}

void Control::read() {
	Serial.println(paramsPtr->oscFreq);
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