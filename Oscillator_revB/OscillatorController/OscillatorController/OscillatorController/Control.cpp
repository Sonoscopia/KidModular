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
	enc2 = new Encoder(ENC2L, ENC2R);
	enc2h.init(enc2, ENC2B);
	enc3 = new Encoder(ENC3L, ENC3R);
	enc3h.init(enc3, ENC3B);
	enc4 = new Encoder(ENC4L, ENC4R);
	enc4h.init(enc4, ENC4B);
}

void Control::read() {
	readButton();
	updateParameters();
}

void Control::readButton() {
	button[0] = digitalRead(MENUPIN);
	delay(10); // improves readings
	if(button[0]==0 && button[0] != button[1]){
		incMenu();
		menuChanged = true;
		setEncoders(); 
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
			enc1h.setMul(1.f, 1.f);
			enc2h.setMul(1.f, 20.f);
			enc3h.setMul(1.f, 1.f);
			enc4h.setMul(0.1f, 2.f);
		break;
		
		case 1: // Filter
			enc1h.setMul(1.f, 5.f);
			enc2h.setMul(1.f, 20.f);
			enc3h.setMul(1.f, 5.f);
			enc4h.setMul(1.f, 5.f);
		break;
		
		case 2: // Envelope
			enc1h.setMul(1.f, 20.f);
			enc2h.setMul(1.f, 20.f);
			enc3h.setMul(1.f, 5.f);
			enc4h.setMul(1.f, 20.f);
		break;
		
		case 3: // Fx
			enc1h.setMul(1.f, 5.f);
			enc2h.setMul(1.f, 5.f);
			enc3h.setMul(1.f, 5.f);
			enc4h.setMul(1.f, 5.f);
		break;
		
		case 4: // Settings
			enc1h.setMul(1.f, 5.f);
			enc2h.setMul(1.f, 5.f);
			enc3h.setMul(1.f, 5.f);
			enc4h.setMul(1.f, 1.f);
		break;
		
		default:
		break;
	}
}

void Control::updateParameters(){
	switch(paramsPtr->menu){
		case 0:
			enc1h.setValue(&paramsPtr->oscWave, OWMIN, OWMAX);
			enc2h.setValue(&paramsPtr->oscFreq, OFMIN, OFMAX);
			enc3h.setValue(&paramsPtr->lfoWave, LWMIN, LWMAX);
			enc4h.setValue(&paramsPtr->lfoFreq, LFMIN, LFMAX);
		break;
		
		case 1:
			enc1h.setValue(&paramsPtr->filType, FTMIN, FTMAX);
			enc2h.setValue(&paramsPtr->filFreq, FFMIN, FFMAX);
			enc3h.setValue(&paramsPtr->filRes, FRMIN, FRMAX);
			enc4h.setValue(&paramsPtr->filLfo, FLMIN, FLMAX);
		break;
		
		case 2:
			enc1h.setValue(&paramsPtr->envAtt, EAMIN, EAMAX);
			enc2h.setValue(&paramsPtr->envDcy, EDMIN, EDMAX);
			enc3h.setValue(&paramsPtr->envSus, ESMIN, ESMAX);
			enc4h.setValue(&paramsPtr->envRel, ERMIN, ERMAX);
		break;
		
		case 3:
			enc1h.setValue(&paramsPtr->fxType, FXTMIN, FXTMAX);
			enc2h.setValue(&paramsPtr->fxAmt, FXAMIN, FXAMAX);
			enc3h.setValue(&paramsPtr->fxParam, FXPMIN, FXPMAX);
			enc4h.setValue(&paramsPtr->fxLfo, FXLMIN, FXLMAX);
		break;
		
		case 4:
			enc1h.setValue(&paramsPtr->inPitch, IPMIN, IPMAX);
			enc2h.setValue(&paramsPtr->inEnv, IEMIN, IEMAX);
			enc3h.setValue(&paramsPtr->filEnv, FEMIN, FEMAX);
			enc4h.setValue(&paramsPtr->preset, PRMIN, PRMAX);
		break;
		
		default:
		break;
	}
}

void Control::sendI2C() {

}

void Control::storePreset() {

}

void Control::loadPreset() {

}