#ifndef _GLOBALS_H
#define _GLOBALS_H

#include "Arduino.h"

//class GLOBALS {
//public: 
    // HARDWARE
	const byte MENUPIN = 14;
    const byte ENC1L = 2;
    const byte ENC1R = 3;
	const byte ENC1B = 18;
    const byte ENC2L = 5;
    const byte ENC2R = 6;
    const byte ENC2B = 17;
    const byte ENC3L = 7;
    const byte ENC3R = 11;
    const byte ENC3B = 16;
    const byte ENC4L = 44;
    const byte ENC4R = 46;
    const byte ENC4B = 15;
    // SCREEN
	const int WIDTH = 479;
    const int HEIGHT = 319;
    const byte ORIGIN = 0;
    const int BKGCOLOR = 0x0000;
    const int COLOR = 0xF800;
    const byte STROKEWEIGHT = 3;
    
	const byte TLABELS = 5;
    const String tmLabels[TLABELS] = {"OSC.", "FIL.", "ENV.", "FX", "SETT."};
    const byte BLABELS = 4;
    const String oscLabels[BLABELS] = {"WAVE:", "FREQ:", "LFO:", "FREQ:"};
    const String filLabels[BLABELS] = {"TYPE:", "FREQ:", "RES:", "LFO:"};
    const String envLabels[BLABELS] = {"ATK:", "DEC:", "SUS:", "REL:"};
    const String fxLabels[BLABELS] = {"TYPE:", "AMT:", "PARAM:", "LFO:"};
	const String settLabels[BLABELS] = {"IN>PITCH:", "IN>ENV:", "ENV>FIL:", "PRESET:"};
    const byte NUMWAVES = 4; 
	const String waveNames[NUMWAVES] = {"SINE", "SQR", "TRI", "SAW"};
    const byte NUMFX = 8;
	const String fxNames[NUMFX] = {"OFF, >>, <<, AND, OR, NOR, XAND, XOR"};
	// SYNTH 
	const byte OWMIN = 0;
    const byte OWMAX = NUMWAVES-1; 
    const float OFMIN = 30.f;
    const float OFMAX = 12000.f;
    const byte LWMIN = 0;
    const byte LWMAX = NUMWAVES-1;
    const float LFMIN = 0.001;
    const float LFMAX = 48.f;
    const byte FTMIN = 0;
    const byte FTMAX = 255; 
    const float FFMIN = 30.f;
    const float FFMAX = 12000.f;
    const float EAMIN = 0.f;
    const float EAMAX = 6000.f;
    const float EDMIN = 0.f;
    const float EDMAX = 6000.f;
    const float ERMIN = 0.f;
    const float ERMAX = 6000.f;
    const byte FXTMIN = 0;
    const byte FXTMAX = NUMFX-1;
    const byte PRMIN = 0;
    const byte PRMAX = 15;
//};

#endif //_GLOBALS_H