// Encoder example 3
// Similar to example 2 but cleaning up to class EncoderHandle
#include <Encoder.h>
#include "EncoderHandle.h"
#define ENC1L 2
#define ENC1R 3
#define ENC1B 18
Encoder enc1(ENC1L, ENC1R);
EncoderHandle encoder1(1., 10.);  

float myVal = 0;

void setup() {
  Serial.begin(9600);
  encoder1.init(&enc1, ENC1B);
}

void loop() {
  encoder1.setVal(&myVal);
  if(encoder1.changed) Serial.println(myVal);
}
