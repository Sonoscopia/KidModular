#include "EncoderHandle.h"

EncoderHandle::EncoderHandle(){ // default constructor 
   pos[0] = 0; // new val
   pos[1] = 0; // old val
   nMult = 0.25f;
   bMult = 0.25;
   changed = true; // set variable upon instantiation 
}

EncoderHandle::EncoderHandle(float bm, float nm){ // default constructor 
   pos[0] = 0; // new val
   pos[1] = 0; // old val
   bMult = bm;
   nMult = nm*0.25;
   changed = true; 
}

void EncoderHandle::init(Encoder *e, byte bp){
  enc = e;
  bPin = bp;
  pinMode(bPin, INPUT_PULLUP);
}

void EncoderHandle::setVal(float *f){
  changed = false; 
  button = digitalRead(bPin);
  pos[0] = enc->read();
  if(pos[0]>pos[1]){
      *f += inc(button);
      pos[1] = pos[0];
      changed = true; 
  }
  if(pos[0]<pos[1]){
    *f -= dec(button);
    pos[1] = pos[0];
    changed = true;
  } 
}

float EncoderHandle::inc(boolean m){ // mode, bMul, nMul
  if(m) return nMult;
  else return bMult; 
}

float EncoderHandle::dec(boolean m){ // mode, bMul, nMul
  if(m) return nMult;
  else return bMult;
}
