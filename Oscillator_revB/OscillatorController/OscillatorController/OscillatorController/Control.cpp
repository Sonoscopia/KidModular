#include "Control.h"

/**
 * Control implementation
 * 
 * This class handles hardware control (except for the LCD which is controlled in the Screen class)
 */

Control::Control() {
	button[0] = 1; // new value
	button[1] = 1; // old value
	menuChanged = false;
	pinMode(MENUPIN, INPUT_PULLUP);
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
	//Serial.println(paramsPtr->oscFreq);
	readButton();
}

void Control::readButton() {
	button[0] = digitalRead(MENUPIN);
	delay(10); // improves readings
	if(button[0]==0 && button[0] != button[1]){
		incMenu();
		menuChanged = true;
	}
	button[1] = button[0];
	//menuChanged = false; // --> set from outside
}

void Control::incMenu() {
	paramsPtr->menu++;
	if (paramsPtr->menu > TABLES-1) paramsPtr->menu=0;
}

void Control::sendI2C() {

}

void Control::storePreset() {

}

void Control::loadPreset() {

}