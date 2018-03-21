/*
 * GLOBALS.h
 *
 * Created: 21-03-2018 00:03:36
 *  Author: tiago
 */ 


#ifndef GLOBALS_H_
#define GLOBALS_H_
#include "Arduino.h"

// HARDWARE
// PIN definitions
#define MENUPIN 14

// SCREEN 
#define WIDTH 480
#define HEIGHT 320
#define ORIGIN 0
#define BKGCOLOR 0x0000 // black
#define COLOR 0xF800 // red
#define STROKEWEIGHT 3

#define TLABELS 5
const String tmLabels[TLABELS] = {"OSC.", "FIL.", "ENV.", "FX", "SETT."};

#define BLABELS 4
const String oscLabels[BLABELS] = {"WAVE:", "FREQ:", "LFO:", "FREQ:"};
const String filLabels[BLABELS] = {"TYPE:", "FREQ:", "RES:", "ENV:"};
const String envLabels[BLABELS] = {"ATK:", "DEC:", "SUS:", "REL:"};	
const String fxLabels[BLABELS] = {"TYPE:", "AMT:", "PARAM:", "LFO:"};

#endif /* GLOBALS_H_ */