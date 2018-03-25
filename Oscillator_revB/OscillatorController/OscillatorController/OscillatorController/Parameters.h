#ifndef _PARAMETERS_H
#define _PARAMETERS_H

#include "Arduino.h"

class Parameters {
public: 
	Parameters(){};
	
    typedef struct {
		//TODO change unnecessary floats to integers
		// TODO change unsigned values to uint8_t?
		
		uint8_t menu = 0;
		// OSCILLATOR
		uint8_t oscWave = 0;
		float oscFreq = 220.f;
		uint8_t lfoWave = 0;
		float lfoFreq = 4.f;
		// FILTER
		uint8_t filType = 0;
		float filFreq = 12000.f;
		uint8_t filRes = 40;
		int8_t filLfo = 0; // -127 to 127
		// ENVELOPE
		float envAtk = 0.f;
		float envDcy = 200.f;
		uint8_t envSus = 180;
		float envRel = 250;
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