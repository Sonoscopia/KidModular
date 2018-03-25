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
	enc1 = new Rotary(ENC1L, ENC1R);
	enc1h.init(enc1, ENC1B);
	enc2 = new Rotary(ENC2L, ENC2R);
	enc2h.init(enc2, ENC2B);
	enc3 = new Rotary(ENC3L, ENC3R);
	enc3h.init(enc3, ENC3B);
	enc4 = new Rotary(ENC4L, ENC4R);
	enc4h.init(enc4, ENC4B);
	setEncoders();
}

void Control::read() {
	readButton();
	//updateParameters(); -> this is called in the main sketch via ISR
}

void Control::readButton() {
	button[0] = digitalRead(MENUPIN);
	delay(10); // improves readings
	if(button[0]==0 && button[0] != button[1]){
		incMenu();
		menuChanged = true;
		setEncoders();
		//sendI2C(paramsPtr->menu); 
	}
	button[1] = button[0];
	//menuChanged = false; // --> set from outside
}

void Control::incMenu() {
	paramsPtr->menu++;
	if (paramsPtr->menu > TLABELS-1) paramsPtr->menu=0;
}

void Control::setEncoders(){
	switch(paramsPtr->menu){
		case 0: // Oscillator
			enc1h.setMulN(1, 1);
			enc2h.setMulF(1.f, 20.f);
			enc3h.setMulN(1, 1);
			enc4h.setMulF(0.1f, 2.f);
		break;
		
		case 1: // Filter
			enc1h.setMulN(1, 5);
			enc2h.setMulF(1.f, 20.f);
			enc3h.setMulN(1, 5);
			enc4h.setMulN(1, 5);
		break;
		
		case 2: // Envelope
			enc1h.setMulF(1.f, 20.f);
			enc2h.setMulF(1.f, 20.f);
			enc3h.setMulN(1, 5);
			enc4h.setMulF(1.f, 20.f);
		break;
		
		case 3: // Fx
			enc1h.setMulN(1, 5);
			enc2h.setMulN(1, 5);
			enc3h.setMulN(1, 5);
			enc4h.setMulN(1, 5);
		break;
		
		case 4: // Settings
			enc1h.setMulN(1, 5);
			enc2h.setMulN(1, 5);
			enc3h.setMulN(1, 5);
			enc4h.setMulN(1, 1);
		break;
		
		default:
		break;
	}
}

void Control::updateParameters(){
	switch(paramsPtr->menu){
		case 0:
			enc1h.setValueN(&paramsPtr->oscWave, OWMIN, OWMAX);
			enc2h.setValueF(&paramsPtr->oscFreq, OFMIN, OFMAX);
			enc3h.setValueN(&paramsPtr->lfoWave, LWMIN, LWMAX);
			enc4h.setValueF(&paramsPtr->lfoFreq, LFMIN, LFMAX);
		break;
		
		case 1:
			enc1h.setValueN(&paramsPtr->filType, FTMIN, FTMAX);
			enc2h.setValueF(&paramsPtr->filFreq, FFMIN, FFMAX);
			enc3h.setValueN(&paramsPtr->filRes, FRMIN, FRMAX);
			enc4h.setValueN(&paramsPtr->filLfo, FLMIN, FLMAX);
		break;
		
		case 2:
			enc1h.setValueF(&paramsPtr->envAtk, EAMIN, EAMAX);
			enc2h.setValueF(&paramsPtr->envDcy, EDMIN, EDMAX);
			enc3h.setValueN(&paramsPtr->envSus, ESMIN, ESMAX);
			enc4h.setValueF(&paramsPtr->envRel, ERMIN, ERMAX);
		break;
		
		case 3:
			enc1h.setValueN(&paramsPtr->fxType, FXTMIN, FXTMAX);
			enc2h.setValueN(&paramsPtr->fxAmt, FXAMIN, FXAMAX);
			enc3h.setValueN(&paramsPtr->fxParam, FXPMIN, FXPMAX);
			enc4h.setValueN(&paramsPtr->fxLfo, FXLMIN, FXLMAX);
		break;
		
		case 4:
			enc1h.setValueN(&paramsPtr->inPitch, IPMIN, IPMAX);
			enc2h.setValueN(&paramsPtr->inEnv, IEMIN, IEMAX);
			enc3h.setValueN(&paramsPtr->filEnv, FEMIN, FEMAX);
			enc4h.setValueN(&paramsPtr->preset, PRMIN, PRMAX);
		break;
		
		default:
		break;
	}
}

/*params_t Control::sendI2C() {

}*/

void Control::storePreset() {

}

void Control::loadPreset() {

}