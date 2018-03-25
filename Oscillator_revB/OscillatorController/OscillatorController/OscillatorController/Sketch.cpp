#include <Arduino.h> // needed in Atmel Studio only
#include "TimerOne.h"
void encoderISR();
void requestEvent();

#include "Wire.h"
#include "Parameters.h"
#include "Control.h"
#include "Screen.h"
#include "GLOBALS.h"

#define DEBUG 0

Parameters parameters;
Control control; 
Screen screen; 

void setup() {
	if(DEBUG) Serial.begin(57600);
	Wire.begin(8); // 0~7 are reserved
	control.init(&(parameters.data));
	screen.init(&control);
	Timer1.initialize(1000); // set a timer of length 1000 microseconds (or 0.001 sec - or 1000Hz)
	Timer1.attachInterrupt( encoderISR );
}

void loop() {
	control.read();
	Timer1.detachInterrupt();
	Wire.onRequest(requestEvent); // register event
	screen.display(); // screen must be called after i2c calls because screen resets some variables (ex. menuChanged)
	Timer1.attachInterrupt(encoderISR);
}

void encoderISR(){
	control.updateParameters();
}

void requestEvent(){   	
	/* COM format
	1st byte - menu and parameter address relative to encoder
	2nd byte - parameter value
	3nd byte - upper byte if parameter is integer or float* 
	*- float is multiplied by 10 and converted to integer
	*/
	
	byte paramAddr = B10000000; // to signal no COM set first byte 8th bit high 
	byte byte1 = 0;
	byte byte2 = 0;
	
	switch (parameters.data.menu)
	{			
		// Lowest nibble -> menu
		// Highest nibble -> param num (ex: oscWave=0, oscFreq=1, lfoWave=2, lfoFreq=3)
		case 0: 
			if (control.enc1h.changed)
			{
				paramAddr = 0x00; // reset parameter address to send via I2C
				paramAddr = parameters.data.menu | (0 << 4);
				byte1 = parameters.data.oscWave;
			    //byte2 = 0;
			}	
			if (control.enc2h.changed)
			{
				paramAddr = 0x00; // reset parameter address to send via I2C
				paramAddr = parameters.data.menu | (1 << 4);
			}
			if (control.enc3h.changed)
			{
				paramAddr = 0x00; // reset parameter address to send via I2C
				paramAddr = parameters.data.menu | (2 << 4);
			}
			if (control.enc4h.changed)
			{
				paramAddr = 0x00; // reset parameter address to send via I2C
				paramAddr = parameters.data.menu | (3 << 4);
			}
		break;
		
		default:	
		break;
	}
	Wire.write(paramAddr); // send B10000000 if nothing happens
	Wire.write(byte1);
	Wire.write(byte2);
}
