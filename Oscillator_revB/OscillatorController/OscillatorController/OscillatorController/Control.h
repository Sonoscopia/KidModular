#ifndef _CONTROL_H
#define _CONTROL_H

#include "Arduino.h"
#include "Encoder.h"
#include "EncoderHandler.h"
#include "Parameters.h"
#include "GLOBALS.h"

class Control: public EncoderHandler, public Parameters {
public: 
    Encoder* enc1;
    Encoder* enc2;
    Encoder* enc3;
    Encoder* enc4;
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

private: 
	boolean button[2]; // menu button
    void readButton(); // read menu button
    void incMenu(); // increment menu
	void setEncoders(); // set encoders according to current menu
    void updateParameters(); // update params according to cur. menu
	void sendI2C();
    void storePreset();
    void loadPreset();
};

#endif //_CONTROL_H