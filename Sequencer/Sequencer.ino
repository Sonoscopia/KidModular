/*
KidModular - SEQUENCER 
by Tiago Angelo (aka p1nho)

Built with: 
Arduino 1.0.5 (on Arduino MEGA2560)
Stripped out version of UTFT Library v.2.82 (12 Jul 2016) by Henning Karlsen
Sequencer code based on Rui Penha's "Polissonos" ()
*/

/************************************ INCLUDED LIBS & HEADERS ***********************************************/
#include "avr/pgmspace.h"
#include <UTFT.h>
#include <Encoder.h>
/************************************ DEFINITIONS ***********************************************************/
#define DEBUG 1

#define WIDTH 480
#define HEIGHT 320
// SEQUENCER
#define MAXSTEPS 8
#define RADIUS 140 // gemetric shapes radius
// CONTROLS
#define BPMPIN 0
#define NSTEPSPIN 1
#define ENCL 2 // encoder Left
#define ENCR 3 // encoder Right
#define ENCB 4 // encoder button
/************************************ CLASS OBJECTS *********************************************************/
// LCD
UTFT lcd(CTE32HR,38,39,40,41);
extern uint8_t BigFont[];

// Encoder
Encoder encoder(ENCL, ENCR);
/************************************ VARIABLES *************************************************************/
// Sequencer
byte bpm = 120, _bpm = 120; // beats-per-minute
byte curStep; // current step
byte stepEdit =1; // selected step for editing purposes
byte numSteps, _numSteps; // selected number of steps
byte pitch[MAXSTEPS]; // array with pitch of each step 
byte dur[] = {50, 50, 50, 50, 50, 50, 50, 50}; // array with duration of each step
int playhead; // sequencer playhead in ms
// LCD
unsigned int center[2];
String bpmText = String("BPM = 120"); 
// Encoder
byte button, _button; 
long encVal, _encVal = -1; 
/************************************ SETUP *****************************************************************/
void setup()
{
  if(DEBUG) Serial.begin(9600);
  // manual pin setup
  pinMode(ENCB, INPUT_PULLUP);
  // LCD setup - uses delay() and therefore must go before any interrupts
  lcd.InitLCD();
  lcd.setFont(BigFont);
  lcd.fillScr(VGA_BLACK);
  // center position to draw geometric shapes (circFrame)
  center[0] = WIDTH/2 + 40;
  center[1] = HEIGHT-RADIUS-2;
  drawLabels();
}

/************************************ LOOP ******************************************************************/
void loop()
{
  if(DEBUG){
    Serial.println();
  }
  
  // Controls
  updateControls();
  
  // LCD 
  drawCircFrame();
  printBPM();
  printSize();
  printDur();
}

/************************************ SEQUENCER FUNCTIONS ***************************************************/


/************************************** LCD FUNCTIONS *******************************************************/
void drawLabels(){
  lcd.setColor(VGA_BLUE);
  lcd.print("BPM: ", 2, 2);
  lcd.print("Size: ", 2, HEIGHT/2-8);
  lcd.print("Dur: ", 2, HEIGHT-18);
}

void drawCircFrame(){
  lcd.setColor(VGA_GRAY);
  lcd.drawCircle(center[0], center[1], RADIUS);
}

void printBPM(){
  if(bpm != _bpm){
    lcd.setColor(VGA_BLUE);
    if(bpm > 99) lcd.print(String(bpm), 64, 2);
    else {
      lcd.print(String(bpm), 64, 2);
      lcd.print(" ", 96, 2);
    }
    _bpm = bpm;
  }
}

void printSize(){
  if(numSteps != _numSteps){
    lcd.setColor(VGA_BLUE);
    lcd.printNumI(numSteps, 80, HEIGHT/2-8);
    _numSteps = numSteps; 
  }
}

void printDur(){
  lcd.setColor(VGA_BLUE);
  lcd.printNumI(stepEdit, 64, HEIGHT-18);
  lcd.print("-", 80, HEIGHT-18);
  lcd.printNumI(dur[stepEdit], 96, HEIGHT-18);
}
/************************************** UPDATE CONTROLS *****************************************************/
void updateControls(){
  // Potentiometers
  bpm = (analogRead(BPMPIN) >> 3) + 30; // from 30 to 157 bpm
  numSteps = (analogRead(NSTEPSPIN) >> 7) + 1; // from 1 to 8 steps 
  
  
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



