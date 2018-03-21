/* 
* InterfaceClass.h
*
* Created: 21-03-2018 00:49:58
* Author: tiago
*/


#ifndef __INTERFACECLASS_H__
#define __INTERFACECLASS_H__


class InterfaceClass
{
//functions
public:
	virtual ~InterfaceClass(){}
	virtual void Method1() = 0;
	virtual void Method2() = 0;

}; //InterfaceClass

#endif //__INTERFACECLASS_H__
