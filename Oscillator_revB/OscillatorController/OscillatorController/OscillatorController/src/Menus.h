/* 
* Menu.h
*
* Created: 19-03-2018 23:46:03
* Author: tiago
*/
#ifndef __MENU_H__
#define __MENUS_H__

#include "Arduino.h"
#include "GLOBALS.h"
#include "Parameters.h"
#include "UTFT.h"

class Menus: private Parameters
{
//variables
private:
	UTFT* mLCD;
	uint8_t *bFont;
	uint8_t *sFont;
	byte tWidth, bWidth, height;
	params_t *paramsPtr;
//functions
public:
	Menus();
	void passObjects(UTFT *obj, uint8_t *sF, uint8_t *bF, params_t *p);
	void draw();
	~Menus();

private:
	void drawTopMenu();
	void drawBottomMenu();
	void drawBottomLabels(const String s[4]);
	Menus( const Menus &c );
	Menus& operator=( const Menus &c );
};
#endif
