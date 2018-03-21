/* 
* Control.h
*
* Created: 19-03-2018 19:47:28
* Author: tiago
*/
#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "Arduino.h"
#include "GLOBALS.h"
#include "Parameters.h"

class Control : public Parameters
{
//variables
public:
	boolean menuChange; 
private:
	params_t *paramsPtr;
	boolean button[2] = {1, 1};
	
//functions
public:
	Control();
	Control(params_t *p);
	~Control();
	//void changeParameters();
	void read();
	
protected:
private:
	Control( const Control &c );
	Control& operator=( const Control &c );
	void readMButton();
	void incrementMenu();

};
#endif
