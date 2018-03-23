#ifndef _MENU_H
#define _MENU_H

#include "Arduino.h"
#include "UTFT.h"
#include "Parameters.h"
#include "GLOBALS.h"

class Menu: public Parameters {
public: 
    
    Menu();

    void init(UTFT* u, uint8_t* sF, uint8_t* bF, params_t* p);
    void drawMenus();
    void drawValues();
private: 
    UTFT* mLCD;
    uint8_t* sFont;
    uint8_t* bFont;
    params_t* paramsPtr;
	byte tWidth, bWidth, height;
	
	void drawTopMenu();
	void drawBottomMenu();
	void drawBottomLabels(const String s[4]);
	void displayOsc();
	void displayFil();
	void displayEnv();
	void displayFX();
	void displaySett();
};

#endif //_MENU_H