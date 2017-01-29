/*
KidModular - SEQUENCER 
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
  2) on encoder button use bitwise operator ^1 for the toggle/switch button
  3) move controls to a class and average potentiometer variables
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
#define MAXSTEPS 8
#define RADIUS 140 // gemetric shapes radius
#define STEPRADIUS 8 // step circle radius
// Controls
#define BPMPIN 8
#define NSTEPSPIN 9
#define ENCL 2 // encoder Left
#define ENCR 3 // encoder Right
#define ENCB 4 // encoder button
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
uint16_t bpm = 120;
float stepTime; 
uint8_t numSteps = 1;
uint8_t curStep = 0;
uint8_t stepEdit = 0;
uint8_t pitch[MAXSTEPS]; 
uint8_t dur[] = {50, 50, 50, 50, 50, 50, 50, 50};
// Encoder
byte button, _button; 
long encVal, _encVal = -1; 

void setup(void){
  if(DEBUG) Serial.begin(9600);
  
  // set pins
  for (int i = 5; i < 12; i++){
    // LEDS pins 5~11
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH); // turn off
  }
  pinMode(44, OUTPUT); // LED 8 - pin44 ??
  digitalWrite(44, HIGH); // turn off  
  pinMode(12, OUTPUT); // PITCH CV OUT pin12
  pinMode(13, OUTPUT); // GATE CV OUT pin13 
  
  // Init LCD
//  lcd.InitLCD();
//  lcd.setFont(BigFont);
//  lcd.fillScr(VGA_BLACK);
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
    if(DEBUG) Serial.println(curStep);
  interrupts();
  
  delayMicroseconds(6000); // latency = 8ms (remember 0.75ms is equivalent to 1ms)
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

/************************************** UPDATE CONTROLS *****************************************************/
void updateControls(){
  // Potentiometers
  bpm = (analogRead(BPMPIN) >> 3) + 40; // from 40 to 167 bpm
  stepTime = 60000.f / bpm;
  stepTime = 60000 / bpm; 
  numSteps = (analogRead(NSTEPSPIN) >> 7) + 1; // from 1 to 8 steps 
  for(int i = 0; i < 8; i++){
    pitch[i] = analogRead(i) >> 3; // from 0 to 127
  }
  
  // Encoder 
  button = digitalRead(ENCB);
  if(button < 1 && button != _button){
    stepEdit++;
    if(stepEdit > numSteps) stepEdit = 1; 
  } 
  _button = button;
  
  encVal = encoder.read() >> 2;
  if (encVal > _encVal){ 
    dur[stepEdit]+=2;
    if(dur[stepEdit] > 99) dur[stepEdit] = 0;
  }
  if(encVal < _encVal){
    dur[stepEdit]-=2;
    if(dur[stepEdit] < 0) dur[stepEdit] = 99;
  }
  _encVal = encVal;
}
