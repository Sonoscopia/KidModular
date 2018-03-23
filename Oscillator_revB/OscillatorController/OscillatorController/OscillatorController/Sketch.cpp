#include <Arduino.h> // needed in Atmel Studio only

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
	control.read();
}

void loop() {
	control.read();
	screen.display();
}
