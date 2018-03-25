#ifndef _GLOBALS_H
#define _GLOBALS_H

#include "Arduino.h"

#define bit_get(p,m) ((p) & (m))
#define bit_set(p,m) ((p) |= (m))
#define bit_clear(p,m) ((p) &= ~(m))
#define BIT(x)(0x01 << (x))
//class GLOBALS {
//public: 
    // HARDWARE (pins 11&12 are disabled because of Timer1)
	const byte MENUPIN = 14;
    const byte ENC1L = 2;
    const byte ENC1R = 3;
	const byte ENC1B = 18;
    const byte ENC2L = 4;
    const byte ENC2R = 5;
    const byte ENC2B = 17;
    const byte ENC3L = 6;
    const byte ENC3R = 7;
    const byte ENC3B = 16;
    const byte ENC4L = 8;
    const byte ENC4R = 9;
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
	const String waveNames[NUMWAVES] = {"SIN", "SQR", "TRI", "SAW"};
    const byte NUMFX = 8;
	const String fxNames[NUMFX] = {"OFF, >>, <<, AND, OR, NOR, XAND, XOR"};
	// SYNTH 
	const uint8_t OWMIN = 0;
    const uint8_t OWMAX = NUMWAVES-1; 
    const uint16_t OFMIN = 30;
    const uint16_t OFMAX = 8000;
    const uint8_t LWMIN = 0;
    const uint8_t LWMAX = NUMWAVES-1;
    const float LFMIN = 0.001;
    const float LFMAX = 48.f;
    const uint8_t FTMIN = 0;
    const uint8_t FTMAX = 255; 
    const int FFMIN = 30.f;
    const int FFMAX = 12000.f;
	const uint8_t FRMIN = 0;
	const uint8_t FRMAX = 255;
	const int8_t FLMIN = -127;
	const int8_t FLMAX = 127;
    const uint16_t EAMIN = 0;
    const uint16_t EAMAX = 6000;
    const uint16_t EDMIN = 0;
    const uint16_t EDMAX = 6000;
	const uint8_t ESMIN = 0;
	const uint8_t ESMAX = 255; 
    const uint16_t ERMIN = 0;
    const uint16_t ERMAX = 6000;
    const uint8_t FXTMIN = 0;
    const uint8_t FXTMAX = NUMFX-1;
    const uint8_t FXAMIN = 0;
	const uint8_t FXAMAX = 255;
	const uint8_t FXPMIN = 0;
	const uint8_t FXPMAX = 255;
	const int8_t FXLMIN = -127;
	const int8_t FXLMAX = 127;
	const int8_t IPMIN = -127;
	const int8_t IPMAX = 127;
	const uint8_t IEMIN = 0;
	const uint8_t IEMAX = 255;
	const int8_t FEMIN = -127;
	const int8_t FEMAX = 127;
	const uint8_t PRMIN = 0;
    const uint8_t PRMAX = 15;
//};

#endif //_GLOBALS_H