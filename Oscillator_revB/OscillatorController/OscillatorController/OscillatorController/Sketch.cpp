#include <Arduino.h> // needed in Atmel Studio only
#include "TimerOne.h"
void encoderISR();
//#define ENCODER_DO_NOT_USE_INTERRUPTS

#include "Parameters.h"
#include "Control.h"
#include "Screen.h"

#define DEBUG 0

Parameters parameters;
Control control; 
Screen screen; 

void setup() {
	if(DEBUG) Serial.begin(115200);
	control.init(&(parameters.data));
	screen.init(&control);
	Timer1.initialize(1000); // set a timer of length 1000 microseconds (or 0.001 sec - or 1000Hz)
	Timer1.attachInterrupt( encoderISR );
}

void loop() {
	control.read();
	Timer1.detachInterrupt();
	screen.display();
	Timer1.attachInterrupt(encoderISR);
}

void encoderISR(){
	control.updateParameters();
}