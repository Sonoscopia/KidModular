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
	if (ctrlPtr->enc1h.changed
	|| ctrlPtr->enc2h.changed
	|| ctrlPtr->enc3h.changed
	|| ctrlPtr->enc4h.changed )
	{
		menu.drawValues();
		ctrlPtr->enc1h.changed = false;
		ctrlPtr->enc2h.changed = false;
		ctrlPtr->enc3h.changed = false;
		ctrlPtr->enc4h.changed = false;
	}
}