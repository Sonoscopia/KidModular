#include "Menu.h"

/**
 * Menu implementation
 * 
 * This class draws the upper menu as well as the bottom labels and associated parameters
 */


Menu::Menu() {

}

void Menu::init(UTFT* u, uint8_t* sF, uint8_t* bF, params_t* p) {
	//Serial.println(p->oscFreq);
	paramsPtr = p;
	mLCD = u;
	sFont = sF;
	bFont = bF;
}

void Menu::drawMenus(){
	mLCD->setColor(COLOR);
	mLCD->fillRect(120, 120, WIDTH, HEIGHT);
}

void Menu::drawTopMenu() {

}

void Menu::drawBottomMenu() {

}

void Menu::drawValues() {

}