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
			enc1h.setMulN_u8t(LOMUL_U8T, LOMUL_U8T);
			enc2h.setMul_u16t(LOMUL_U16T, HIMUL_U16T);
			enc3h.setMulN_u8t(LOMUL_U8T, LOMUL_U8T);
			enc4h.setMul_u16t(LFOLOMUL_U16T, LFOHIMUL_U16T);
		break;
		
		case 1: // Filter
			enc1h.setMulN_u8t(LOMUL_U8T, MEDMUL_U8T);
			enc2h.setMul_u16t(LOMUL_U16T, HIMUL_U16T);
			enc3h.setMulN_u8t(LOMUL_U8T, MEDMUL_U8T);
			enc4h.setMulN_s8t(LOMUL_S8T, MEDMUL_S8T);
		break;
		
		case 2: // Envelope
			enc1h.setMul_u16t(LOMUL_U16T, HIMUL_U16T);
			enc2h.setMul_u16t(LOMUL_U16T, HIMUL_U16T);
			enc3h.setMulN_u8t(LOMUL_U8T, HIMUL_U8T);
			enc4h.setMul_u16t(LFOLOMUL_U16T, HIMUL_U16T);
		break;
		
		case 3: // Fx
			enc1h.setMulN_u8t(LOMUL_U8T, MEDMUL_U8T);
			enc2h.setMulN_u8t(LOMUL_U8T, MEDMUL_U8T);
			enc3h.setMulN_u8t(LOMUL_U8T, MEDMUL_U8T);
			enc4h.setMulN_s8t(LOMUL_S8T, LOMUL_S8T);
		break;
		
		case 4: // Settings
			enc1h.setMulN_s8t(LOMUL_S8T, MEDMUL_S8T);
			enc2h.setMulN_u8t(LOMUL_U8T, MEDMUL_U8T);
			enc3h.setMulN_s8t(LOMUL_S8T, MEDMUL_S8T);
			enc4h.setMulN_u8t(LOMUL_U8T, MEDMUL_U8T);
		break;
		
		default:
		break;
	}
}

void Control::updateParameters(){
	switch(paramsPtr->menu){
		case 0:
			enc1h.setValue_u8t(&paramsPtr->oscWave, OWMIN, OWMAX);
			enc2h.setValue_u16t(&paramsPtr->oscFreq, OFMIN, OFMAX);
			enc3h.setValue_u8t(&paramsPtr->lfoWave, LWMIN, LWMAX);
			enc4h.setValue_u16t(&paramsPtr->lfoFreq, LFMIN, LFMAX);
		break;
		
		case 1:
			enc1h.setValue_u8t(&paramsPtr->filType, FTMIN, FTMAX);
			enc2h.setValue_u16t(&paramsPtr->filFreq, FFMIN, FFMAX);
			enc3h.setValue_u8t(&paramsPtr->filRes, FRMIN, FRMAX);
			enc4h.setValue_s8t(&paramsPtr->filLfo, FLMIN, FLMAX);
		break;
		
		case 2:
			enc1h.setValue_u16t(&paramsPtr->envAtk, EAMIN, EAMAX);
			enc2h.setValue_u16t(&paramsPtr->envDcy, EDMIN, EDMAX);
			enc3h.setValue_u8t(&paramsPtr->envSus, ESMIN, ESMAX);
			enc4h.setValue_u16t(&paramsPtr->envRel, ERMIN, ERMAX);
		break;
		
		case 3:
			enc1h.setValue_u8t(&paramsPtr->fxType, FXTMIN, FXTMAX);
			enc2h.setValue_u8t(&paramsPtr->fxAmt, FXAMIN, FXAMAX);
			enc3h.setValue_u8t(&paramsPtr->fxParam, FXPMIN, FXPMAX);
			enc4h.setValue_s8t(&paramsPtr->fxLfo, FXLMIN, FXLMAX);
		break;
		
		case 4:
			enc1h.setValue_s8t(&paramsPtr->inPitch, IPMIN, IPMAX);
			enc2h.setValue_u8t(&paramsPtr->inEnv, IEMIN, IEMAX);
			enc3h.setValue_s8t(&paramsPtr->filEnv, FEMIN, FEMAX);
			enc4h.setValue_u8t(&paramsPtr->preset, PRMIN, PRMAX);
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