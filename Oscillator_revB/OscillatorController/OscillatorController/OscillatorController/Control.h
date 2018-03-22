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
    //EncoderHandler* enc2h;
    //EncoderHandler* enc3h;
    //EncoderHandler* enc4h;
    boolean menuChange;
    boolean paramsChanged;
    params_t* paramsPtr;
    
    Control();
    
    void init(params_t *p);  
    void read();

private: 
    void readButton();
    void incMenu();
    void sendI2C();
    void storePreset();
    void loadPreset();
};

#endif //_CONTROL_H