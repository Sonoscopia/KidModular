#ifndef _PARAMETERS_H
#define _PARAMETERS_H

#include "Arduino.h"

class Parameters {
public: 
	Parameters(){};
	
    typedef struct {
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
		byte filterLfo = 0;
		// ENVELOPE
		float envAtt = 0.f;
		float envDcy = 200.f;
		byte envSus = 180;
		float envRel = 250;
		// FX
		byte fxType = 0;
		byte fxAmt = 0;
		byte fxParam = 0;
		byte fxLfo = 0;
		// SETTINGS
		byte inEnv = 0;
		byte inPitch = 255;
		byte envFil = 0;
		byte preset = 0;
	}params_t;
	
	 params_t data;
};

#endif //_PARAMETERS_H