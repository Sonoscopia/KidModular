// Timer interrupts and avr code to make things smoother

#include "TimerFive.h"

#define POT 8 

uint16_t bpm = 120;
float stepTime; 
uint8_t curStep = 0;
volatile uint16_t playhead = 0;
uint8_t dur[] = {50, 50, 50, 50};
uint8_t numSteps = 4;

void setup(void){
  // set pins
  for (int i = 5; i < 14; i++){
    pinMode(i, OUTPUT);
  }
  /*DDRB &= ~(1<<DDB7); // pin13 OUTPUT
  DDRE &= ~(1<<DDE3); // pin5 OUTPUT
  DDRH &= ~(1<<DDH3); // pin6 OUTPUT
  DDRH &= ~(1<<DDH4); // pin7 OUTPUT
  DDRH &= ~(1<<DDH5); // pin8 OUTPUT
  */
  Serial.begin(9600);
  // init variables
  stepTime = 60000.f / bpm;
  
  Timer5.initialize(750); // run every millisecond (in original Arduinos w/ 16MHz clock this value would be 1000)
  // but since this is a fake Arduino w/ a 12MHz clock 0.75ms are equivalent to 1ms
  Timer5.attachInterrupt(runSequence);
}

void loop(void){
  noInterrupts();
  // print stuff here
    Serial.println(bpm);
  interrupts();
  delayMicroseconds(6000); // latency = 8ms
  dur[0] = analogRead(0) / 1024.f * 100;
  bpm = (analogRead(POT)); // from 30 to 157 bpm
  stepTime = 60000.f / bpm;
}

void runSequence(void){
  playhead++;
  if(playhead > stepTime){
    playhead = 0;
    curStep++;
    if(curStep == numSteps) {curStep = 0;}
  }
  // Gate CV output 
  if(playhead < stepTime * dur[curStep] / 100.f){
    PORTB |= _BV(PB7); // pin13 HIGH
    switch(curStep){
      case 0:
         PORTE &= ~_BV(PE3); // pin5 LOW (common anode, so it's a ON)
      break;
      case 1:
         PORTH &= ~_BV(PH3); // pin6 LOW (common anode, so it's a ON)
      break; 
      case 2:
         PORTH &= ~_BV(PH4); // pin7 LOW (common anode, so it's a ON)
      break;
      case 3:
         PORTH &= ~_BV(PH5); // pin8 LOW (common anode, so it's a ON)
      break;
      default:
      break; 
    }
  } 
  else{
    PORTB &= ~_BV(PB7); // pin13 LOW
    switch(curStep){
      case 0:
         PORTE |= _BV(PE3); // pin5 LOW (common anode, so it's a ON)
      break;
      case 1:
         PORTH |= _BV(PH3); // pin6 LOW (common anode, so it's a ON)
      break; 
      case 2:
         PORTH |= _BV(PH4); // pin7 LOW (common anode, so it's a ON)
      break;
      case 3:
         PORTH |= _BV(PH5); // pin8 LOW (common anode, so it's a ON)
      break;
      default:
      break; 
    }
  }
}
