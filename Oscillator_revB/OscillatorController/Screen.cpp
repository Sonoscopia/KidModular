#include "Screen.h"

Screen::Screen(){ // default constructor  
}

Screen::Screen(UTFT _lcd, uint8_t _bF[], uint8_t _sF[]){ // default constructor  
  mLCD = _lcd;
  bigFont = _bF;
  smallFont = _sF;
  // top menus: Wave+LFO, Filter, Envelope, FX, Settings
  label[0] = {"OSCIL"};
  label[1] = {"FILT."};
  label[2] = {"ENV."};
  label[3] = {"FX"};
  label[4] = {"SETT."};
  isSelected[0] = true; // default "WAVE" menu selected at instantiation 
  isSelected[1] = false;
  isSelected[2] = false;
  isSelected[3] = false;
  isSelected[4] = false;
  menuChange = true; // enable menu draw upon instantiation
  valueChange = true; // enable param values draw upon instantiation
}
void Screen::init(params_t *p){
  mParams = p;
  
  mLCD = UTFT(CTE32HR,38,39,40,41); // instantiate UTFT object
  mLCD.InitLCD(); // init screen
  mLCD.clrScr(); // clear screen (black background)
  width = mLCD.getDisplayXSize()-1; // display width
  height = mLCD.getDisplayYSize()-1; // display height
  //menuWidth = width / sizeof(menu); // top menu width -> this gives a wrong value! (dont know why)
  topMenuWidth = 480 / 5; // top menu width 96px
  bottomMenuWidth = 480 / 4; // bottom menu width 120px
  menuHeight = 40; // top menu height in px
  menuStroke = 3; // stroke weight in px 
}

void Screen::draw(){
  drawMenus();
}

void Screen::drawMenus(){
   if(menuChange){
      drawTopMenu();
      drawBottomMenu();
      drawValues();
      menuChange = false;
   }
   if(valueChange){
     drawValues();
     valueChange = false;  
   }
}

void Screen::updateMenu(){
  for(int i = 0; i < 5; i++){ // set all to false
    isSelected[i] = false;
  }
  isSelected[mParams->selectedMenu] = true; // then set selected menu
  menuChange = true; 
}

void Screen::drawTopMenu(){
  mLCD.setFont(bigFont); // set font 
      // draw outer rect
      mLCD.setColor(VGA_RED);
      mLCD.fillRect(0, 0, width, menuHeight);
      
      // draw inner rects and labels
      for(int i = 0; i < 5; i++){
        if (isSelected[i]<1){ // print all but selected
          mLCD.setColor(VGA_BLACK);
          //              start X                     start Y     end X                            end Y
          mLCD.fillRect( (topMenuWidth*i)+menuStroke, menuStroke, (topMenuWidth*(i+1))-menuStroke, menuHeight-menuStroke );
          mLCD.setColor(VGA_RED);
          mLCD.setBackColor(VGA_BLACK);
          mLCD.print(label[i], (topMenuWidth*i)+menuStroke, 10); 
        }
        else{ // print selected
          mLCD.setColor(VGA_BLACK);
          mLCD.setBackColor(VGA_RED);
          mLCD.print(label[i], (topMenuWidth*i)+menuStroke, 10); 
        } 
  }
}

void Screen::drawBottomMenu(){
      mLCD.setFont(smallFont); // set font 
      // draw outer rect
      mLCD.setColor(VGA_RED);
      mLCD.fillRect(0, height-menuHeight, width, height);
      // draw inner rects
      mLCD.setColor(VGA_BLACK);
      for(int i = 0; i < 4; i++){
        //              start X                        start Y                       end X                               end Y
        mLCD.fillRect( (bottomMenuWidth*i)+menuStroke, height-menuHeight+menuStroke, (bottomMenuWidth*(i+1))-menuStroke, height-menuStroke );
      }
      // draw labels
      for(int i = 0; i < 4; i++){
        mLCD.setColor(VGA_RED);
        mLCD.setBackColor(VGA_BLACK);
        mLCD.print(oscilLabels[i], (bottomMenuWidth*i)+menuStroke+2, height-menuHeight+14); 
      }
}

void Screen::drawValues(){
  // draw values
  int i = 0;
  mLCD.setColor(VGA_RED);
  mLCD.setBackColor(VGA_BLACK);
  mLCD.print(waveforms[mParams->oscWave], ((bottomMenuWidth*i)+menuStroke)+(bottomMenuWidth/2), height-menuHeight+14);
  i++;
  mLCD.printNumF(mParams->oscFreq, 1, ((bottomMenuWidth*i)+menuStroke)+(bottomMenuWidth/2), height-menuHeight+14);
  i++;
  mLCD.print(waveforms[mParams->lfoWave], ((bottomMenuWidth*i)+menuStroke)+(bottomMenuWidth/2), height-menuHeight+14);
  i++;
  mLCD.printNumF(mParams->lfoFreq, 1, ((bottomMenuWidth*i)+menuStroke)+(bottomMenuWidth/2), height-menuHeight+14);
  //mLCD.print(oscilLabels[i], (bottomMenuWidth*i)+menuStroke+2, height-menuHeight+14); 
}

