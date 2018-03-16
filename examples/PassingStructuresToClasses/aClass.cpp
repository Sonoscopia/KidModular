#include "aClass.h"

aClass::aClass(){ // default constructor
  
}

void aClass::printColor(struct RGB *s){
  Serial.println(s->r);
  Serial.println(s->g);
  Serial.println(s->b);
}

void aClass::passStruct(struct RGB *s){
  mRGB = s;
}

void aClass::randomColor(){
  mRGB->r = random(255);
  mRGB->g = random(255);
  mRGB->b = random(255);
}
   
