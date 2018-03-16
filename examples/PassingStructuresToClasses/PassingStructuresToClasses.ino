#include "aClass.h"

RGB color = {255, 127, 63}; 

aClass c; 

void setup() {
  Serial.begin(9600);
  //c.printColor(&color);
  c.passStruct(&color);
  c.randomColor();
  Serial.println(color.r);
  Serial.println(color.g);
  Serial.println(color.b);
}

void loop() {
}

