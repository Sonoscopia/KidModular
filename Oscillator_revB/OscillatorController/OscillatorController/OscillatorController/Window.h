#ifndef _WINDOW_H
#define _WINDOW_H

#include "Arduino.h"
#include "UTFT.h"
#include "Parameters.h"

class Window: public Parameters {
public: 
	Window();
    void init(UTFT* u, uint8_t* sF, uint8_t* bF, params_t* p);
    void drawOscillator();
    void drawFilter();
    void drawEnvelope();
    void drawFx();
    void drawSettings();
private: 
    UTFT* mLCD;
    uint8_t* sFont;
    uint8_t* bFont;
    params_t* paramsPtr;
};

#endif //_WINDOW_H