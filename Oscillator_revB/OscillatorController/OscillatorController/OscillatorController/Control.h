#ifndef _CONTROL_H
#define _CONTROL_H

#include "Arduino.h"
#include "Rotary.h"
#include "EncoderHandler.h"
#include "Parameters.h"
#include "GLOBALS.h"

class Control: public EncoderHandler, public Parameters {
public: 
	EncoderHandler enc1h;
    EncoderHandler enc2h;
    EncoderHandler enc3h;
    EncoderHandler enc4h;
    boolean menuChanged;
    boolean paramsChanged;
    params_t* paramsPtr;
    
    Control();
    
    void init(params_t *p);  
    void read();
	void updateParameters(); // update params according to cur. menu

private: 
	Rotary* enc1;
	Rotary* enc2;
	Rotary* enc3;
	Rotary* enc4;
	boolean button[2]; // menu button
    void readButton(); // read menu button
    void incMenu(); // increment menu
	void setEncoders(); // set encoders according to current menu
	params_t sendI2C(params_t *p);
    void storePreset();
    void loadPreset();
};

#endif //_CONTROL_H