#include "Menu.h"

/**
 * Menu implementation
 * 
 * This class draws the upper menu as well as the bottom labels and associated parameters
 */


Menu::Menu() {
	tWidth = (WIDTH+1)/TLABELS; // 96px
	bWidth = (WIDTH+1)/BLABELS; // 120px
	height = HEIGHT/8; // 40px
}

void Menu::init(UTFT* u, uint8_t* sF, uint8_t* bF, params_t* p) {
	//Serial.println(p->oscFreq);
	paramsPtr = p;
	mLCD = u;
	sFont = sF;
	bFont = bF;
}

void Menu::drawMenus(){
	drawBottomMenu();
	drawTopMenu();
}

void Menu::drawTopMenu() {
	mLCD->setFont(bFont); // set font
	// draw outer rect
	mLCD->setColor(COLOR);
	mLCD->fillRect(ORIGIN, ORIGIN, WIDTH, height);


	// draw inner rects and labels
	for(int i = 0; i < TLABELS; i++){
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

void Menu::drawBottomMenu() {
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
			drawBottomLabels(settLabels);
		break;
		default:
		break;
	}
}
void Menu::drawBottomLabels(const String s[4]){
	for(int i = 0; i < BLABELS; i++){
		mLCD->setColor(COLOR);
		mLCD->setBackColor(BKGCOLOR);
		mLCD->print(s[i], (bWidth*i)+STROKEWEIGHT+2, HEIGHT-height+14);
	}
}
void Menu::drawValues() {
	byte i = 0;
	mLCD->setFont(sFont);
	mLCD->setColor(COLOR);
	mLCD->setBackColor(BKGCOLOR);
	switch(paramsPtr->menu){
		case 0:
			mLCD->print(waveNames[paramsPtr->oscWave], ((bWidth*i)+STROKEWEIGHT)+(bWidth/2), HEIGHT-height+14);
			i++;
			mLCD->printNumF(paramsPtr->oscFreq, 1, ((bWidth*i)+STROKEWEIGHT)+(bWidth/2), HEIGHT-height+14);
			i++;
			mLCD->print(waveNames[paramsPtr->lfoWave], ((bWidth*i)+STROKEWEIGHT)+(bWidth/2), HEIGHT-height+14);
			i++;
			mLCD->printNumF(paramsPtr->lfoFreq, 1, ((bWidth*i)+STROKEWEIGHT)+(bWidth/2), HEIGHT-height+14);
		break;
		case 1:
			mLCD->printNumI(paramsPtr->filType, ((bWidth*i)+STROKEWEIGHT)+(bWidth/2), HEIGHT-height+14);
			i++;
			mLCD->printNumF(paramsPtr->filFreq, 1, ((bWidth*i)+STROKEWEIGHT)+(bWidth/2), HEIGHT-height+14);
			i++;
			mLCD->printNumI(paramsPtr->filRes, ((bWidth*i)+STROKEWEIGHT)+(bWidth/2), HEIGHT-height+14);
			i++;
			mLCD->printNumI(paramsPtr->filLfo, ((bWidth*i)+STROKEWEIGHT)+(bWidth/2), HEIGHT-height+14);
		break;
		case 2:
			mLCD->printNumF(paramsPtr->envAtk, 1, ((bWidth*i)+STROKEWEIGHT)+(bWidth/2), HEIGHT-height+14);
			i++;
			mLCD->printNumF(paramsPtr->envDcy, 1, ((bWidth*i)+STROKEWEIGHT)+(bWidth/2), HEIGHT-height+14);
			i++;
			mLCD->printNumI(paramsPtr->envSus, ((bWidth*i)+STROKEWEIGHT)+(bWidth/2), HEIGHT-height+14);
			i++;
			mLCD->printNumF(paramsPtr->envRel, 1, ((bWidth*i)+STROKEWEIGHT)+(bWidth/2), HEIGHT-height+14);
		break;
		case 3:
			mLCD->printNumI(paramsPtr->fxType, ((bWidth*i)+STROKEWEIGHT)+(bWidth/2), HEIGHT-height+14);
			i++;
			mLCD->printNumI(paramsPtr->fxAmt, ((bWidth*i)+STROKEWEIGHT)+(bWidth/2), HEIGHT-height+14);
			i++;
			mLCD->printNumI(paramsPtr->fxParam, ((bWidth*i)+STROKEWEIGHT)+(bWidth/2), HEIGHT-height+14);
			i++;
			mLCD->printNumI(paramsPtr->fxLfo, ((bWidth*i)+STROKEWEIGHT)+(bWidth/2), HEIGHT-height+14);
		break;
		case 4:
			mLCD->printNumI(paramsPtr->inPitch, ((bWidth*i)+STROKEWEIGHT)+(bWidth/2), HEIGHT-height+14);
			i++;
			mLCD->printNumI(paramsPtr->inEnv, ((bWidth*i)+STROKEWEIGHT)+(bWidth/2), HEIGHT-height+14);
			i++;
			mLCD->printNumI(paramsPtr->filEnv, ((bWidth*i)+STROKEWEIGHT)+(bWidth/2), HEIGHT-height+14);
			i++;
			mLCD->printNumI(paramsPtr->preset, ((bWidth*i)+STROKEWEIGHT)+(bWidth/2), HEIGHT-height+14);
		break;
		default:
		break;
	}
}