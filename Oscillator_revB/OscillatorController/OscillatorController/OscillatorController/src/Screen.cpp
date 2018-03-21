/* 
* Screen.cpp
*
* Created: 19-03-2018 22:10:12
* Author: tiago
*/
#include "Screen.h"

Screen::Screen() // default constructor
{
}
Screen::~Screen(){ // default destructor
} 
Screen::Screen(params_t *p, Control *obj){
	paramsPtr = p;
	ctrlPtr = obj;
}

void Screen::init(){
	lcd = *new UTFT(CTE32HR,38,39,40,41);
	lcd.InitLCD();
	extern uint8_t BigFont[];
	bFont = BigFont;
	extern uint8_t SmallFont[];
	sFont = SmallFont;
	menus.passObjects(&lcd, SmallFont, BigFont, paramsPtr);
	lcd.clrScr();
	menus.draw();
}
void Screen::display(){
	/*lcd.setColor(COLOR);
	lcd.setBackColor(BKGCOLOR);
	lcd.setFont(bFont);
	lcd.print( "hello",0, 160);
	lcd.fillRect(240, 160, WIDTH, HEIGHT);*/
	
	if(ctrlPtr->menuChange){
		menus.draw();
		ctrlPtr->menuChange = false;	
	}
}