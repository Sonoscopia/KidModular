/*
KidModular - SEQUENCER - V.0.1.0 
by Tiago Angelo (aka p1nho)

Built with: 
Arduino 1.0.5 (on Arduino MEGA2560)
Stripped out version of UTFT Library v.2.82 (12 Jul 2016) by Henning Karlsen
Sequencer code based on Rui Penha's "Polissonos" ()
*/

/*
  TO DO: 
  ...to increase efficiency, performance and playability:
  1) replace switch() by if elif 
  2) move controls to a class and average potentiometer variables
  3) use avr code for controls
  4) on encoder button use bitwise operator ^1 for the toggle/switch button
*/

/************************************ INCLUDED LIBS & HEADERS ***********************************************/
#include "TimerFive.h"
#include "avr/pgmspace.h"
#include <UTFT.h>
#include <Encoder.h>
#include "Screen.h"

/************************************ DEFINITIONS ***********************************************************/
#define DEBUG 1

// Sequencer
#define MAXSTEPS 6
#define RADIUS 140 // gemetric shapes radius
#define STEPRADIUS 8 // step circle radius
// Controls
#define BPMPIN 7 // bpm pot
#define NSTEPSPIN 6 // num steps pot
                    // pitch pots from A0 to A5
#define ENCL 8 // encoder Left
#define ENCR 9 // encoder Right
#define ENCB 12 // encoder button
// Control Voltage
#define GATEPIN 11
#define PITCHPIN 10
                // led pins from 2 to 7 
/************************************ CLASS OBJECTS *********************************************************/
// Encoder
Encoder encoder(ENCL, ENCR);
// LCD Screen
UTFT lcd(CTE32HR,38,39,40,41);
extern uint8_t BigFont[];
Screen screen(lcd, BigFont);
/************************************ VARIABLES *************************************************************/
// Sequencer
volatile uint16_t playhead = 0;
uint16_t bpm = 120, pBpm = 120;
float stepTime; 
uint8_t numSteps = 1, pNumSteps;
uint8_t curStep = 0;
uint8_t stepEdit = 0, pStepEdit = 0;
uint8_t pitch[MAXSTEPS]; 
uint8_t dur[] = {50, 50, 50, 50, 50, 50};
uint8_t pDur = 50; 
// Encoder
byte button, _button; 
long encVal, _encVal = -1; 

void setup(void){
  if(DEBUG) Serial.begin(9600);
  
  // set pins
  for (int i = 2; i < 8; i++){
    // LEDS pins 2~7
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH); // turn off
  }
  pinMode(PITCHPIN, OUTPUT); // PITCH CV OUT pin12
  pinMode(GATEPIN, OUTPUT); // GATE CV OUT pin13 
  pinMode(ENCB, INPUT_PULLUP); // Encoder button
  // Init LCD
  screen.init();

  // Init Variables
  stepTime = 60000.f / bpm;
  
  // SET TIMER5 - Sequencer+LEDs
  Timer5.initialize(750); // run every millisecond (in original Arduinos w/ 16MHz clock this value would be 1000)
  // but since this is a fake Arduino w/ a 12MHz clock 0.75ms are equivalent to 1ms
  Timer5.attachInterrupt(runSequence);
}

void loop(void){
  noInterrupts();
  // print stuff here
    if(DEBUG) Serial.println(numSteps);
  interrupts();
  
  delayMicroseconds(6000); // latency = 8ms (remember 0.75ms is equivalent to 1ms)
  // SCREEN DRAWS
  if(numSteps != pNumSteps){
    screen.drawShape(numSteps);
    screen.printSize(numSteps);
    pNumSteps = numSteps; 
  }
  if(bpm != pBpm){
    screen.printBPM(bpm);
    pBpm = bpm;
  }
  if(stepEdit != pStepEdit || dur[stepEdit] != pDur){  
    screen.printDur(dur, stepEdit);
    pStepEdit = stepEdit;
    pDur = dur[stepEdit];
  }
  
  updateControls();
}

/************************************ SEQUENCER FUNCTIONS ***************************************************/
void runSequence(void){
  playhead++;
  if(playhead > stepTime){
    playhead = 0;
    curStep++;
    if(curStep == numSteps) {curStep = 0;}
  }
  // Gate CV output 
  if(playhead < stepTime * dur[curStep] / 100.f){
//    PORTB |= _BV(PB7); // pin13 HIGH
    switch(curStep){
      case 0:
         PORTE &= ~_BV(PE4); // pin2 LOW (common anode, so it's a ON)
      break;
      case 1:
         PORTE &= ~_BV(PE5); // pin3 LOW (common anode, so it's a ON)
      break; 
      case 2:
         PORTG &= ~_BV(PG5); // pin4 LOW (common anode, so it's a ON)
      break;
      case 3:
         PORTE &= ~_BV(PE3); // pin5 LOW (common anode, so it's a ON)
      break;
      case 4:
         PORTH &= ~_BV(PH3); // pin6 LOW (common anode, so it's a ON)
      break;
      case 5:
         PORTH &= ~_BV(PH4); // pin7 LOW (common anode, so it's a ON)
      break;
      default:
      break; 
    }
  } 
  else{
//    PORTB &= ~_BV(PB7); // pin13 LOW
    switch(curStep){
      case 0:
         PORTE |= _BV(PE4); // pin2 LOW (common anode, so it's a ON)
      break;
      case 1:
         PORTE |= _BV(PE5); // pin3 LOW (common anode, so it's a ON)
      break; 
      case 2:
         PORTG |= _BV(PG5); // pin4 LOW (common anode, so it's a ON)
      break;
      case 3:
         PORTE |= _BV(PE3); // pin5 LOW (common anode, so it's a ON)
      break;
      case 4:
         PORTH |= _BV(PH3); // pin6 LOW (common anode, so it's a ON)
      break;
      case 5:
         PORTH |= _BV(PH4); // pin7 LOW (common anode, so it's a ON)
      break;
      default:
      break; 
    }
  }
}

/************************************** UPDATE CONTROLS *****************************************************/
void updateControls(){
  // Potentiometers
  bpm = (analogRead(BPMPIN) >> 1) + 30; // from 30 to 541 bpm
  stepTime = 60000.f / bpm;
  numSteps = (analogRead(NSTEPSPIN) / 171) + 1; // from 1 to 6 steps 
  for(int i = 0; i < 8; i++){
    pitch[i] = analogRead(i) >> 3; // from 0 to 127
  }
  
  
  // Encoder 
  button = digitalRead(ENCB);
  if(button < 1 && button != _button){
    stepEdit++;
    if(stepEdit > numSteps-1) stepEdit = 0;
  } 
  _button = button;
  
  encVal = encoder.read() >> 2;
  if (encVal > _encVal){ 
    dur[stepEdit]+=4;
    if(dur[stepEdit] > 96) {
      dur[stepEdit] = 0;
    }
  }
  if(encVal < _encVal){
    dur[stepEdit]-=4;
    if(dur[stepEdit] > 150){ // dur values are in 0~255 range (unsigned)!!!
      dur[stepEdit] = 96;
    }
  }
  _encVal = encVal;
  
}
