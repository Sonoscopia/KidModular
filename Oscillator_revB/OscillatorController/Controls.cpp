#include "Controls.h"

Controls::Controls(){ // default constructor
  menu_button[0] = 1; // new value
  menu_button[1] = 1; // previous value
}

void Controls::init(){
  pinMode(MENUPIN, INPUT_PULLUP); // set menu button
}

void Controls::update(){
  menuChanged = false;
  menu_button[0] = digitalRead(MENUPIN);
  if(menu_button[0]== 0 && menu_button[0] != menu_button[1]){
    Serial.println("menu change");
    menuChanged = true; 
  }
  menu_button[1] = menu_button[0]; 
  delay(50); // improves readibility 
}

