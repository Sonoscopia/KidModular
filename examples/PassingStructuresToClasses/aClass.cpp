#include "aClass.h"

aClass::aClass(){ // default constructor
  
}

void aClass::printColor(struct RGB *s){
  Serial.println(s->r);
  Serial.println(s->g);
  Serial.println(s->b);
}
