/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>
/*End of auto generated code by Atmel studio */

/*
  OscillatorControl is part of KidModular project by Sonoscopia.pt
  KidModular-Oscillator is a semi-modular oscillator
  This sketch manages the display and input hardware sending data via I2C to a Arduino Pro Mini which is responsible
  for the sound synthesis. 
*/
#include "src/Parameters.h"
#include "src/Control.h"
#include "src/Screen.h"

Parameters parameters; 
Control control(&(parameters.data));
Screen screen(&(parameters.data), &control); 

void setup() {
  /*Serial.begin(9600);
  Serial.println("hello");*/
  
  
  //Serial.println(parameters.data.oscFreq);
  //control.changeParameters();
  //Serial.println(parameters.data.oscFreq);
  screen.init();
  delay(500);
  screen.display();
}

void loop() {
	control.read();
	screen.display();
}
