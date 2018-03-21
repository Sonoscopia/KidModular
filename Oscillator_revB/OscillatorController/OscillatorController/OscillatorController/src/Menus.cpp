/* 
* Menu.cpp
*
* Created: 19-03-2018 23:46:03
* Author: tiago
*/
#include "Menus.h"

Menus::Menus() // default constructor
{
	tWidth = WIDTH/TLABELS; // 96px
	bWidth = WIDTH/BLABELS; // 120px
	height = HEIGHT/8; // 40px
}
Menus::~Menus() // default destructor
{
}
void Menus::passObjects(UTFT *obj, uint8_t *sF, uint8_t *bF, params_t *p){
	mLCD = obj;
	sFont = sF;
	bFont = bF;
	paramsPtr = p;
}

void Menus::draw(){
	drawBottomMenu();
	drawTopMenu();
}

void Menus::drawTopMenu(){
	mLCD->setFont(bFont); // set font
	// draw outer rect
	mLCD->setColor(COLOR);
	mLCD->fillRect(ORIGIN, ORIGIN, WIDTH, height);

	
	// draw inner rects and labels
	for(int i = 0; i < 5; i++){
		if (i != paramsPtr->menu){ // print all but selected
			mLCD->setColor(BKGCOLOR);
			//              start X                 start Y        end X                      end Y
			mLCD->fillRect( (tWidth*i)+STROKEWEIGHT, STROKEWEIGHT, (tWidth*(i+1))-STROKEWEIGHT, height-STROKEWEIGHT );
			mLCD->setColor(COLOR);
			mLCD->setBackColor(BKGCOLOR);
			mLCD->print(tmLabels[i], (tWidth*i)+STROKEWEIGHT, 10);
		}
		else{ // print selected
			mLCD->setColor(BKGCOLOR);
			mLCD->setBackColor(COLOR);
			mLCD->print(tmLabels[i], (tWidth*i)+STROKEWEIGHT, 10);
		}
	}
}

void Menus::drawBottomMenu(){
	mLCD->setFont(sFont); // set font
	// draw outer rect
	mLCD->setColor(COLOR);
	mLCD->fillRect(ORIGIN, HEIGHT-height, WIDTH, HEIGHT);
	// draw inner rects
	mLCD->setColor(BKGCOLOR);
	for(int i = 0; i < BLABELS; i++){
		//              start X                  start Y                     end X                        end Y
		mLCD->fillRect( (bWidth*i)+STROKEWEIGHT, HEIGHT-height+STROKEWEIGHT, (bWidth*(i+1))-STROKEWEIGHT, HEIGHT-STROKEWEIGHT );
	}
	// draw labels
	switch(paramsPtr->menu){
		case 0:
			drawBottomLabels(oscLabels);
		break;
		case 1:
			drawBottomLabels(filLabels);
		break;
		case 2:
			drawBottomLabels(envLabels);
		break;
		case 3:
			drawBottomLabels(fxLabels);
		break;
		case 4:
		// draw settings
		break;
		default:
		break;
	}
	
}

void Menus::drawBottomLabels(const String s[4]){
	for(int i = 0; i < BLABELS; i++){
		mLCD->setColor(COLOR);
		mLCD->setBackColor(BKGCOLOR);
		mLCD->print(s[i], (bWidth*i)+STROKEWEIGHT+2, HEIGHT-height+14);
	}
}
