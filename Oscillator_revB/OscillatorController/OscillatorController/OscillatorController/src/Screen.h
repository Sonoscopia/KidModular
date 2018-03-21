/* 
* Screen.h
*
* Created: 19-03-2018 22:10:12
* Author: tiago
*/
#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "Arduino.h"
#include "GLOBALS.h"
#include "Parameters.h"
#include "Control.h"
#include "UTFT.h"
#include "Menus.h"

class Screen : public Parameters, public Control, public UTFT, public Menus
{
//variables
private:
	//objects
	params_t *paramsPtr; // parameters struct
	Control *ctrlPtr; 
	UTFT lcd; // lcd object
	uint8_t *bFont, *sFont; // fonts
	Menus menus;
	
//functions
public:
	Screen();
	~Screen();
	Screen(params_t *p, Control *obj);
	void init();
	void display();
private:
	Screen( const Screen &c );
	Screen& operator=( const Screen &c );
};
#endif
