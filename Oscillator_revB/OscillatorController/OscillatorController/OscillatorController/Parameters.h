#ifndef _PARAMETERS_H
#define _PARAMETERS_H

#include "Arduino.h"

class Parameters {
public: 
	Parameters(){};
	
    typedef struct {
		//TODO change unnecessary floats to integers
				
		uint8_t menu = 0;
		// OSCILLATOR
		uint8_t oscWave = 0;
		int oscFreq = 220.f;
		uint8_t lfoWave = 0;
		float lfoFreq = 4.f;
		// FILTER
		uint8_t filType = 0;
		int filFreq = 12000.f;
		uint8_t filRes = 40;
		int8_t filLfo = 0; // -127 to 127
		// ENVELOPE
		int envAtk = 0.f;
		int envDcy = 200.f;
		uint8_t envSus = 180;
		int envRel = 250;
		// FX
		uint8_t fxType = 0;
		uint8_t fxAmt = 0;
		uint8_t fxParam = 0;
		int8_t fxLfo = 0; // -127 to 127
		// SETTINGS
		int8_t inPitch = 127; // -127 to 127
		uint8_t inEnv = 0;
		int8_t filEnv = 0; // -127 to 127
		uint8_t preset = 0;
	}params_t;
	
	 params_t data;
};

#endif //_PARAMETERS_H