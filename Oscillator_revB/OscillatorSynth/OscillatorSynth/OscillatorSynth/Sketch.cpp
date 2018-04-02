/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */

#define bit_get(p,m) ((p) & (m))
#define bit_set(p,m) ((p) |= (m))
#define bit_clear(p,m) ((p) &= ~(m))
#define BIT(x)(0x01 << (x))
#define reconstruct(l, u) (l | (u << 8)) // make int from two bytes

//#include "MozziGuts.h"
//#include "Oscil.h" // oscillator template
//#include "tables/sin2048_int8.h" // sine table for oscillator
#include "twi_nonblock.h"

//Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin(SIN2048_DATA);

// use #define for CONTROL_RATE, not a constant
#define CONTROL_RATE 512 // powers of 2 please
#define I2C_ADDRESS 8 
byte message[3] = {0, 0, 0}; 
byte menu, paramAddr;
int val;

void setup(){
  initialize_twi_nonblock();
  //startMozzi(CONTROL_RATE); // set a control rate of 64 (powers of 2 please)
  //aSin.setFreq(440); // set the frequency
  Serial.begin(9600);
 }

/*void updateControl(){
	
	//if(menu == 0 && paramAddr == 1) aSin.setFreq(val); // set the frequency
}*/
/*
int updateAudio(){
  return aSin.next(); // return an int signal centred around 0
}*/


void loop(){
	//audioHook(); // required here
	
	//message[0] = B10000000; 
	byte _error = twi_initiateReadFrom(I2C_ADDRESS, 3);
	byte _length;
	//delay(100); 
	
	_length = twi_readMasterBuffer(message, 3);	
	
	//delay(100);
	
	/*Serial.print(message[0]);
	Serial.print(" ");
	Serial.print(message[1]);
	Serial.print(" ");
	Serial.println(message[2]);
	*/
	
	//Serial.println(_length);
	if( !bit_get(message[0], BIT(7)) ){ // if bit num 7 == 0 then there is data
		menu = message[0] & 0x0F;
		Serial.print(menu);
		Serial.print(" ");
		paramAddr = message[0] >> 4;
		Serial.print(paramAddr);
		Serial.print(" ");
		val = reconstruct(message[1], message[2]);
		Serial.println(val);
	}
	
}
