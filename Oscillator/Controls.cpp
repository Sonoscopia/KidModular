#include "Controls.h"

//Controls::Controls(){
//  // default constructor
//}
Controls::Controls(Encoder *_enc1) {
  mEnc1 = _enc1;
  e1prev = 255;
  
  position = -999; 
}

/*
Controls::Controls( //pins for 4encoder+button and a single button
    uint8_t _enc1L, uint8_t _enc1R, uint8_t _enc1B,
    uint8_t _enc2L, uint8_t _enc2R, uint8_t _enc2B,
    uint8_t _enc3L, uint8_t _enc3R, uint8_t _enc3B,
    uint8_t _enc4L, uint8_t _enc4R, uint8_t _enc4B,
    uint8_t _bPin) 
{
    
}
*/

//void Controls::readEncoders(){
//  // read encoder1
//  e1new = mEnc1->read();
//  if (e1new != e1prev) {
//    e1prev = e1new;
//    val = e1prev;
//  }
//}

void Controls::readEncoders(){
  newPos = mEnc1->read();
     if (newPos != position) {
       position = newPos;
       Serial.print("encoder val: ");
       Serial.println(position);
     }
}
