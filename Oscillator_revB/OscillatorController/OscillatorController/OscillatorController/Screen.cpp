#include "Screen.h"
/**
 * Screen implementation
 * 
 * This class handles all screen manipulations
 */

Screen::Screen() {

}

void Screen::init(Control *obj) {
	ctrlPtr = obj;

	lcd = *new UTFT(CTE32HR,38,39,40,41);
	lcd.InitLCD();
	extern uint8_t BigFont[];
	extern uint8_t SmallFont[];
	
	menu.init(&lcd, SmallFont, BigFont, ctrlPtr->paramsPtr);
	
	lcd.clrScr();
	menu.drawMenus();
	menu.drawValues();
}

void Screen::display() {
	if(ctrlPtr->menuChanged){
		menu.drawMenus();
		menu.drawValues();
		ctrlPtr->menuChanged = false;
	}
}