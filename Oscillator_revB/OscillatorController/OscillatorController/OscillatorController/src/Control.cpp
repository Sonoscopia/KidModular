/* 
* Control.cpp
*
* Created: 19-03-2018 19:47:28
* Author: tiago
*/
#include "Control.h"

Control::Control() // default constructor
{
}
Control::~Control() // default destructor
{
}
Control::Control(params_t *p){  // pass parameters structure by reference
	paramsPtr = p;
	pinMode(MENUPIN, INPUT_PULLUP);
	menuChange = false;
}

void Control::read(){
	readMButton();
}
void Control::readMButton(){
	button[0] = digitalRead(MENUPIN);
	delay(10); // improves readings
	if(button[0]==0 && button[0] != button[1]){
		incrementMenu();
		menuChange = true;
		Serial.print("menu: ");
		Serial.println(paramsPtr->menu);
	}
	button[1] = button[0];
}
void Control::incrementMenu(){
	paramsPtr->menu++;
	if (paramsPtr->menu > 4) paramsPtr->menu=0;
}
/*
void Control::changeParameters(){
	Serial.println("changing frequency to 30Hz");
	paramsPtr->oscFreq = 30.f;
}*/