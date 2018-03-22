#ifndef _CONTROL_H
#define _CONTROL_H

#include "Arduino.h"
#include "Encoder.h"
#include "EncoderHandler.h"
#include "Parameters.h"

class Control: public EncoderHandler, public Parameters {
public: 
    Encoder* enc1;
    EncoderHandler* enc1h;
    Encoder* enc2;
    EncoderHandler* enc2h;
    Encoder* enc3;
    EncoderHandler* enc3h;
    Encoder* enc4;
    EncoderHandler* enc4h;
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