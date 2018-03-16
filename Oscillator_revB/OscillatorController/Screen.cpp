#include "Screen.h"

Screen::Screen(){ // default constructor  
}

Screen::Screen(UTFT _lcd, uint8_t _f[]){ // default constructor  
  mLCD = _lcd;
  mFont = _f;
  // top menus: Wave+LFO, Filter, Envelope, FX, Settings
  label[0] = {"WAVE"};
  label[1] = {"FILT."};
  label[2] = {"ENV."};
  label[3] = {"FX"};
  label[4] = {"SETT."};
  menuInc = 0; 
  isSelected[0] = true; // default "WAVE" menu selected at instantiation 
  isSelected[1] = false;
  isSelected[2] = false;
  isSelected[3] = false;
  isSelected[4] = false;
  menuChange = true; // enable topMenu draw upon instantiation
}

void Screen::init(){
  mLCD = UTFT(CTE32HR,38,39,40,41); // instantiate UTFT object
  mLCD.InitLCD(); // init screen
  mLCD.setFont(mFont); // set font 
  mLCD.clrScr(); // clear screen (black background)
  width = mLCD.getDisplayXSize(); // display width
  //menuWidth = width / sizeof(menu); // top menu width -> this gives a wrong value! (dont know why)
  menuWidth = 480 / 5; // top menu width 96px
  menuHeight = 40; // top menu height in px
  menuStroke = 3; // stroke weight in px 
}

void Screen::draw(){
  drawTopMenu();
}

void Screen::drawTopMenu(){
   if(menuChange){
      // draw outer rect
      mLCD.setColor(VGA_RED);
      mLCD.fillRect(0, 0, width, menuHeight);
      
      // draw inner rects and labels
      for(int i = 0; i < 5; i++){
        if (isSelected[i]<1){ // print all but selected
          mLCD.setColor(VGA_BLACK);
          //              start X                  start Y     end X                 end Y
          mLCD.fillRect( (menuWidth*i)+menuStroke, menuStroke, (menuWidth*(i+1))-menuStroke, menuHeight-menuStroke );
          mLCD.setColor(VGA_RED);
          mLCD.setBackColor(VGA_BLACK);
          mLCD.print(label[i], (menuWidth*i)+menuStroke, 10); 
        }
        else{ // print selected
          mLCD.setColor(VGA_BLACK);
          mLCD.setBackColor(VGA_RED);
          mLCD.print(label[i], (menuWidth*i)+menuStroke, 10); 
        } 
      }
      menuChange = false;
   }
}

void Screen::updateMenu(){
  // increment menu
  menuInc++;
  if(menuInc>4) menuInc =0;
  for(int i = 0; i < 5; i++){ // set all to false
    isSelected[i] = false;
  }
  isSelected[menuInc] = true; // then set selected menu
  menuChange = true; 
 
}
