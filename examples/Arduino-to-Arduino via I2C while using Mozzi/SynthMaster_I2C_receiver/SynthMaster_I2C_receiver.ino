/*  Example playing a sinewave at a frequency given by another Arduino (see SlaveController_sender.ino)
    using Mozzi sonification library.
  
    Demonstrates the use of Oscil to play a wavetable and non-blocking I2C communication from another Arduino
    
    Circuit: Audio output on digital pin 9 on a Uno or similar, or
    [connect SDA, SCL and GND between Arduinos]
    DAC/A14 on Teensy 3.1, or 
    check the README or http://sensorium.github.com/Mozzi/
  
    Mozzi help/discussion/announcements:
    https://groups.google.com/forum/#!forum/mozzi-users
  
    Tim Barrass 2012, CC by-nc-sa.
    (slightly modified by p1nh0)
*/
#include <twi_nonblock.h> 
#include <MozziGuts.h>
#include <Oscil.h> // oscillator template
#include <tables/sin2048_int8.h> // sine table for oscillator

// use: Oscil <table_size, update_rate> oscilName (wavetable), look in .h file of table #included above
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin(SIN2048_DATA);

// use #define for CONTROL_RATE, not a constant
#define CONTROL_RATE 64 // powers of 2 please
#define I2C_ADDRESS 8 
uint8_t val[] = {0}; 

void setup(){
  startMozzi(CONTROL_RATE); // set a control rate of 64 (powers of 2 please)
  aSin.setFreq(440); // set the frequency
  initialize_twi_nonblock();
}


void updateControl(){
  // put changing controls in here
  byte read = twi_readFromBlocking(I2C_ADDRESS, val, 1);
  aSin.setFreq(val[0]<<2); // set the frequency
}


int updateAudio(){
  return aSin.next(); // return an int signal centred around 0
}


void loop(){
  audioHook(); // required here
}



