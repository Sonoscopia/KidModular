#include "aClass.h"

RGB color = {255, 127, 63}; 

aClass c; 

void setup() {
  Serial.begin(9600);
  c.printColor(&color);
}

void loop() {
}

