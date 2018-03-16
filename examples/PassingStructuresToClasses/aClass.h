#ifndef ACLASS_H
#define ACLASS_H

#include "Arduino.h"
#include "MyStruct.h"

class aClass{
  public:
    aClass();
    void printColor(struct RGB *s);
    void randomColor();
    void passStruct(struct RGB *s);
    RGB *mRGB;
};
#endif
