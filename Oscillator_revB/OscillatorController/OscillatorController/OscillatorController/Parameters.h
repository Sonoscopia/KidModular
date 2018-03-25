#ifndef _PARAMETERS_H
#define _PARAMETERS_H

#include "Arduino.h"

class Parameters {
public: 
	Parameters(){};
	
    typedef struct {
		//TODO change unnecessary floats to integers
		// TODO change unsigned values to uint8_t
		
		byte menu = 0;
		// OSCILLATOR
		byte oscWave = 0;
		float oscFreq = 220.f;
		byte lfoWave = 0;
		float lfoFreq = 4.f;
		// FILTER
		byte filType = 0;
		float filFreq = 12000.f;
		byte filRes = 40;
		byte filLfo = 0;
		// ENVELOPE
		float envAtk = 0.f;
		float envDcy = 200.f;
		byte envSus = 180;
		float envRel = 250;
		// FX
		byte fxType = 0;
		byte fxAmt = 0;
		byte fxParam = 0;
		byte fxLfo = 0;
		// SETTINGS
		byte inPitch = 255;
		byte inEnv = 0;
		byte filEnv = 0;
		byte preset = 0;
	}params_t;
	
	 params_t data;
};

#endif //_PARAMETERS_H