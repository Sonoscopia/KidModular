/* 
* Parameters.h
*
* Created: 19-03-2018 19:33:54
* Author: tiago
*/
#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__

#include "Arduino.h"

class Parameters
{
//variables
public:
	typedef struct  
	{
		byte menu = 0; // OSC+LFO, FILTER, ENV, FX, SETTINGS
		byte oscWave = 0;
		float oscFreq = 220.f;
		byte lfoWave = 0;
		float lfoFreq = 4.f;
		byte filType = 0;
		float filFreq = 12000.f;
		byte filRes = 30;
		byte filEnv = 0;
		byte filLfo = 0;
		float envAtt = 0.f;
		float envDcy = 200.f;
		byte envSus = 200;
		float envRel = 1000.f;
		byte fx = 0;
		byte fxAmt = 0;
		byte fxParam = 0;
		byte fxLfo = 0;
		int ctrlRate = 64;
		byte pitchIn = 255;
		byte envAmp = 255; 
	}params_t;
	params_t data; 
	
protected:
private:

//functions
public:
	Parameters();
	~Parameters();
protected:
private:
	Parameters( const Parameters &c );
	Parameters& operator=( const Parameters &c );
};
#endif
