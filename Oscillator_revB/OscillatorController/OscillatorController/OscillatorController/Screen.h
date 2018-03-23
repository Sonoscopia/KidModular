#ifndef _SCREEN_H
#define _SCREEN_H

#include "Arduino.h"
#include "Control.h"
#include "UTFT.h"
#include "Parameters.h"
#include "Menu.h"
#include "Window.h"

class Screen: public UTFT, public Menu, public Window {
public: 
    Control* ctrlPtr;
    
    Screen();
    
    void init(Control* obj);
    void display();
private: 
	UTFT lcd;
    Menu menu;
    Window window;
};

#endif //_SCREEN_H