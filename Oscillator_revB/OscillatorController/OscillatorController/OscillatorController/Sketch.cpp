#include <Arduino.h> // needed in Atmel Studio only
#include "TimerOne.h" // DISABLES PINS 11 & 12
void encoderISR();
void requestEvent();
void setMessage(byte p, byte b1, byte b2);

#include "Wire.h"
#include "Parameters.h"
#include "Control.h"
#include "Screen.h"
#include "GLOBALS.h"

#define DEBUG 0

Parameters parameters;
Control control; 
Screen screen; 
byte message[3] = {B10000000, 0, 0};
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
	//delay(45);
}

void encoderISR(){
	control.updateParameters();
}

void requestEvent(){   	
	/* COM format
	1st byte - menu and parameter address relative to encoder
	2nd byte - parameter value
	3nd byte - upper byte if parameter is integer or float* 
	*- float is multiplied by 10? and converted to integer
	*/
	
	byte paramAddr = B10000000; // to signal no COM set first byte 8th bit high 
	byte byte1 = 0;
	byte byte2 = 0;
	setMessage(paramAddr, byte1, byte2);
		
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
			    byte2 = 0; // ensure upper byte is 00000000
				setMessage(paramAddr, byte1, byte2);
				Wire.write(message, 3);
			}	
			if (control.enc2h.changed)
			{
				paramAddr = 0x00; // reset parameter address to send via I2C
				paramAddr = parameters.data.menu | (1 << 4);
				byte1 = get_lowerByte(parameters.data.oscFreq);
				byte2 = get_upperByte(parameters.data.oscFreq); 
				setMessage(paramAddr, byte1, byte2);
				Wire.write(message, 3);
			}
			if (control.enc3h.changed)
			{
				paramAddr = 0x00; // reset parameter address to send via I2C
				paramAddr = parameters.data.menu | (2 << 4);
				byte1 = parameters.data.lfoWave;
				byte2 = 0; // ensure upper byte is 00000000
				setMessage(paramAddr, byte1, byte2);
				Wire.write(message, 3);
			}
			if (control.enc4h.changed)
			{
				paramAddr = 0x00; // reset parameter address to send via I2C
				paramAddr = parameters.data.menu | (3 << 4);
				byte1 = get_lowerByte(parameters.data.lfoFreq); // this is an integer (float * LFOMUL)
				byte2 = get_upperByte(parameters.data.lfoFreq);
				setMessage(paramAddr, byte1, byte2);
				Wire.write(message, 3);
			}
		break;
		
		case 1:
			if (control.enc1h.changed)
			{
				paramAddr = 0x00; // reset parameter address to send via I2C
				paramAddr = parameters.data.menu | (0 << 4);
				byte1 = parameters.data.filType;
				byte2 = 0; // ensure upper byte is 00000000
				setMessage(paramAddr, byte1, byte2);
				Wire.write(message, 3);
			}
			if (control.enc2h.changed)
			{
				paramAddr = 0x00; // reset parameter address to send via I2C
				paramAddr = parameters.data.menu | (1 << 4);
				byte1 = get_lowerByte(parameters.data.filFreq);
				byte2 = get_upperByte(parameters.data.filFreq);
				setMessage(paramAddr, byte1, byte2);
				Wire.write(message, 3);
			}
			if (control.enc3h.changed)
			{
				paramAddr = 0x00; // reset parameter address to send via I2C
				paramAddr = parameters.data.menu | (2 << 4);
				byte1 = parameters.data.filRes;
				byte2 = 0; // ensure upper byte is 00000000
				setMessage(paramAddr, byte1, byte2);
				Wire.write(message, 3);
			}
			if (control.enc4h.changed)
			{
				paramAddr = 0x00; // reset parameter address to send via I2C
				paramAddr = parameters.data.menu | (3 << 4);
				byte1 = get_lowerByte(parameters.data.filLfo); // this is an integer (float * LFOMUL)
				byte2 = 0; // ensure upper byte is 00000000
				setMessage(paramAddr, byte1, byte2);
				Wire.write(message, 3);
			}
		break;
		
		case 2:
			if (control.enc1h.changed)
			{
				paramAddr = 0x00; // reset parameter address to send via I2C
				paramAddr = parameters.data.menu | (0 << 4);
				byte1 = get_lowerByte(parameters.data.envAtk);
				byte2 = get_upperByte(parameters.data.envAtk);
				setMessage(paramAddr, byte1, byte2);
				Wire.write(message, 3);
			}
			if (control.enc2h.changed)
			{
				paramAddr = 0x00; // reset parameter address to send via I2C
				paramAddr = parameters.data.menu | (1 << 4);
				byte1 = get_lowerByte(parameters.data.envDcy);
				byte2 = get_upperByte(parameters.data.envDcy);
				setMessage(paramAddr, byte1, byte2);
				Wire.write(message, 3);
			}
			if (control.enc3h.changed)
			{
				paramAddr = 0x00; // reset parameter address to send via I2C
				paramAddr = parameters.data.menu | (2 << 4);
				byte1 = parameters.data.envSus;
				byte2 = 0; // ensure upper byte is 00000000
				setMessage(paramAddr, byte1, byte2);
				Wire.write(message, 3);
			}
			if (control.enc4h.changed)
			{
				paramAddr = 0x00; // reset parameter address to send via I2C
				paramAddr = parameters.data.menu | (3 << 4);
				byte1 = get_lowerByte(parameters.data.envRel); // this is an integer (float * LFOMUL)
				byte2 = get_upperByte(parameters.data.envRel);
				setMessage(paramAddr, byte1, byte2);
				Wire.write(message, 3);
			}
		break;
		
		case 3:
			if (control.enc1h.changed)
			{
				paramAddr = 0x00; // reset parameter address to send via I2C
				paramAddr = parameters.data.menu | (0 << 4);
				byte1 = get_lowerByte(parameters.data.fxType);
				byte2 = 0; // ensure upper byte is 00000000
				setMessage(paramAddr, byte1, byte2);
				Wire.write(message, 3);
			}
			if (control.enc2h.changed)
			{
				paramAddr = 0x00; // reset parameter address to send via I2C
				paramAddr = parameters.data.menu | (1 << 4);
				byte1 = get_lowerByte(parameters.data.fxAmt);
				byte2 = 0; // ensure upper byte is 00000000
				setMessage(paramAddr, byte1, byte2);
				Wire.write(message, 3);
			}
			if (control.enc3h.changed)
			{
				paramAddr = 0x00; // reset parameter address to send via I2C
				paramAddr = parameters.data.menu | (2 << 4);
				byte1 = parameters.data.fxParam;
				byte2 = 0; // ensure upper byte is 00000000
				setMessage(paramAddr, byte1, byte2);
				Wire.write(message, 3);
			}
			if (control.enc4h.changed)
			{
				paramAddr = 0x00; // reset parameter address to send via I2C
				paramAddr = parameters.data.menu | (3 << 4);
				byte1 = get_lowerByte(parameters.data.fxLfo); // this is an integer (float * LFOMUL)
				byte2 = 0; // ensure upper byte is 00000000
				setMessage(paramAddr, byte1, byte2);
				Wire.write(message, 3);
			}
		break;
		
		case 4:
			if (control.enc1h.changed)
			{
				paramAddr = 0x00; // reset parameter address to send via I2C
				paramAddr = parameters.data.menu | (0 << 4);
				byte1 = get_lowerByte(parameters.data.inPitch);
				byte2 = 0; // ensure upper byte is 00000000
				setMessage(paramAddr, byte1, byte2);
				Wire.write(message, 3);
			}
			if (control.enc2h.changed)
			{
				paramAddr = 0x00; // reset parameter address to send via I2C
				paramAddr = parameters.data.menu | (1 << 4);
				byte1 = get_lowerByte(parameters.data.inEnv);
				byte2 = 0; // ensure upper byte is 00000000
				setMessage(paramAddr, byte1, byte2);
				Wire.write(message, 3);
			}
			if (control.enc3h.changed)
			{
				paramAddr = 0x00; // reset parameter address to send via I2C
				paramAddr = parameters.data.menu | (2 << 4);
				byte1 = parameters.data.filEnv;
				byte2 = 0; // ensure upper byte is 00000000
				setMessage(paramAddr, byte1, byte2);
				Wire.write(message, 3);
			}
			// do not send preset variable, sending preset data on load is a different function
		break;
		
		default:	
		break;
	}
	
	//byte message[3] = {paramAddr, byte1, byte2};
	//Wire.write(message, 3);
}

void setMessage(byte p, byte b1, byte b2){
	message[0] = p;
	message[1] = b1;
	message[2] = b2; 
}