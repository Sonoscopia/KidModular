#include <Arduino.h> // needed in Atmel Studio only
#include "GLOBALS.h"
#include "Parameters.h"
#include "Control.h"
#include "Screen.h"

#define DEBUG 1

Parameters parameters;
Control control; 
Screen screen; 

void setup() {
	if(DEBUG) Serial.begin(115200);
	control.init(&(parameters.data));
	screen.init(&control);
	control.read();
}

void loop() {
}
