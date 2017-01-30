#ifndef CONTROLS_H
#define CONTROLS_H

#include "Arduino.h"
#include "../Encoder/utility/direct_pin_read.h"
#include "../Encoder/utility/interrupt_config.h"
#include "../Encoder/utility/interrupt_pins.h"
#define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Encoder.h>



class Controls {
  public:
    Controls(); // default constructor
    Controls(Encoder *_enc1); // for testing purposes only 
    /*Controls(uint8_t _enc1L, uint8_t _enc1R, uint8_t _enc1B, 
             uint8_t _enc2L, uint8_t _enc2R, uint8_t _enc2B, 
             uint8_t _enc3L, uint8_t _enc3R, uint8_t _enc3B, 
             uint8_t _enc4L, uint8_t _enc4R, uint8_t _enc4B, 
             uint8_t _bPin); // pins for 4encoder+button and a single button
     */
     void readEncoders();
     long position, newPos;
     Encoder *mEnc1;

     
  private:    
    uint_fast8_t e1prev, e1new;
};

#endif
