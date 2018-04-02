/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */
void degugI2C();
#define _DEBUG 0

#define bit_get(p,m) ((p) & (m))
#define bit_set(p,m) ((p) |= (m))
#define bit_clear(p,m) ((p) &= ~(m))
#define BIT(x)(0x01 << (x))
#define reconstruct(l, u) (l | (u << 8)) // make int from two bytes

#include "MozziGuts.h"
#include "ADSR.h"
#include "StateVariable.h"
#include "Oscil.h"
#include "tables/sin2048_int8.h"
#include "tables/square_no_alias_2048_int8.h"
#include "tables/triangle2048_int8.h"
#include "tables/saw2048_int8.h" 
#include "twi_nonblock.h"

#define CONTROL_RATE 64 // powers of 2 please
#define I2C_ADDRESS 8

#define LFOMUL 100.f

const int8_t* waves[4] = {SIN2048_DATA, SQUARE_NO_ALIAS_2048_DATA, TRIANGLE2048_DATA, SAW2048_DATA }; 
Oscil <2048, AUDIO_RATE> osc;
Oscil <2048, AUDIO_RATE> lfo;
StateVariable <LOWPASS> svf; // can be LOWPASS, BANDPASS, HIGHPASS or NOTCH
ADSR <CONTROL_RATE, AUDIO_RATE> env;
byte fxType, fxAmt, fxParam, lfoFx;
byte inPitch, inEnv, envFil, lfoFil; 
byte curPreset, prevPreset; 

int filterFreq; 

// I2C variables
byte message[3] = {0, 0, 0}; 
byte menu, paramAddr;
int val;

void setup(){
  initialize_twi_nonblock();
  startMozzi(CONTROL_RATE); 
  // set default levels; 
  osc.setFreq(220);
  lfo.setFreq(4.f);
  svf.setCentreFreq(8000);	
  svf.setResonance(40);
  env.setAttackLevel(255);
  env.setAttackTime(0);
  env.setDecayTime(200);
  env.setSustainLevel(180);
  env.setReleaseLevel(0);
  env.setReleaseTime(250);
  // set I2C
  byte _error = twi_initiateReadFrom(I2C_ADDRESS, 3);
  if(_DEBUG) Serial.begin(9600);
 }

void updateControl(){
	twi_continueReadFrom();	
	byte _length = twi_readMasterBuffer(message, 3);
	if( message[0] > 0 ){ // if there is data
		menu = (message[0] & 0x0F)-1;
		paramAddr = message[0] >> 4;
		val = reconstruct(message[1], message[2]);
		degugI2C();
	}
	switch(menu){
		case 0: // OSCILLATOR params
			if(paramAddr == 0) osc.setTable(waves[val]);
			if(paramAddr == 1) osc.setFreq(val);
			if(paramAddr == 2) lfo.setTable(waves[val]);
			if(paramAddr == 3) lfo.setFreq(val/LFOMUL);
		break;
		case 1: // FILTER params
			//if(paramAddr == 0)
			if(paramAddr == 1) filterFreq = val;
			if(paramAddr == 2) svf.setResonance(val);
			if(paramAddr == 3) lfoFil = val;
		break;
		case 2: // ENVELOPE params
			if(paramAddr == 0) env.setAttackTime(val);
			if(paramAddr == 1) env.setDecayTime(val);
			if(paramAddr == 2) env.setSustainLevel(val);
			if(paramAddr == 3) env.setReleaseTime(val);			
		break;
		case 3: // FX params 
			/*if(paramAddr==0)
			if(paramAddr==1)
			if(paramAddr==2)
			if(paramAddr==3)*/
		break;
		case 4: 
			if(paramAddr==0) inPitch = val;
			if(paramAddr==1) inEnv = val;
			if(paramAddr==2) envFil = val;
		default:
		break;
	}
	
}

int updateAudio(){ 
  svf.setCentreFreq(filterFreq + (lfoFil*lfo.next()) );
  //(envelope.next() * aOscil.next())>>8
  return svf.next(osc.next())>>3; // return an int signal centred around 0
}


void loop(){
	audioHook(); // required here
}

void degugI2C(){
	if(_DEBUG){
		Serial.print(menu);
		Serial.print(" ");
		Serial.print(paramAddr);
		Serial.print(" ");
		Serial.print(val);
		Serial.println(" ");	
	}
}