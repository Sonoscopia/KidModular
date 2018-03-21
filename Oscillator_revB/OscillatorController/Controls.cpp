#include "Controls.h"

Controls::Controls(){ // default constructor
  menu_button[0] = 1; // new value
  menu_button[1] = 1; // previous value
  encoder2 = *new EncoderHandle(1.f, 100.f);
}

void Controls::init(params_t *p){
  mParams = p;
  pinMode(MENUPIN, INPUT_PULLUP); // set menu button
  //encoder1.init(&Encoder(ENC1L, ENC1R), ENC1B);
  //encoder2.init(&Encoder(ENC2L, ENC2R), ENC2B);
  //encoder3.init(&Encoder(ENC3L, ENC3R), ENC3B);
  //encoder4.init(&Encoder(ENC4L, ENC4R), ENC4B);
}

void Controls::update(){
  readMenu();
  readEncoders();
  delay(50); // improves readibility ?
}

void Controls::updateTopMenu(){
  // increment menu
  mParams->selectedMenu++;
  if(mParams->selectedMenu > 4) mParams->selectedMenu =0; 
}

void Controls::readMenu(){
  menuChanged = false;
  menu_button[0] = digitalRead(MENUPIN);
  if(menu_button[0]== 0 && menu_button[0] != menu_button[1]){
    //Serial.println("menu change");
    //Serial.println(selectedMenu);
    updateTopMenu();
    menuChanged = true; 
  }
  menu_button[1] = menu_button[0];
}

void Controls::readEncoders(){
  //encoder1.setVal(mParams->oscWave);
  //if (mParams->oscWave > 3) mParams->oscWave = 0;
  //if (mParams->oscWave < 0) mParams->oscWave = 3;
  
  
  encoder2.setVal(&mParams->oscFreq);
  if (mParams->oscFreq > 12543) mParams->oscWave = 32;
  if (mParams->oscFreq < 32) mParams->oscWave = 12543; 
  Serial.println(mParams->oscFreq);
}
