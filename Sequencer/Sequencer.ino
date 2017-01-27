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

/************************************ DEFINITIONS ***********************************************************/
#define DEBUG 0
#define WIDTH 480
#define HEIGHT 320
// SEQUENCER
#define MAXSTEPS 8
#define RADIUS 140 // gemetric shapes radius
// CONTROLS
#define BPMPIN 0
#define NSTEPSPIN 1
/************************************ CLASS OBJECTS *********************************************************/
// LCD
UTFT lcd(CTE32HR,38,39,40,41);
extern uint8_t BigFont[];

/************************************ VARIABLES *************************************************************/
// Sequencer
byte bpm = 120, _bpm = 120; // beats-per-minute
byte curStep; // current step 
byte numSteps, _numSteps; // selected number of steps
byte pitch[MAXSTEPS]; // array with pitch of each step 
byte dur[MAXSTEPS]; // array with duration of each step
// LCD
unsigned int center[2];
String bpmText = String("BPM = 120"); 

/************************************ SETUP *****************************************************************/
void setup()
{
  if(DEBUG) Serial.begin(9600);
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
  printSteps();
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

void printSteps(){
  if(numSteps != _numSteps){
    lcd.setColor(VGA_BLUE);
    lcd.printNumI(numSteps, 80, HEIGHT/2-8);
    _numSteps = numSteps; 
  }
}

void printDur(){

}
/************************************** UPDATE CONTROLS *****************************************************/
void updateControls(){
  bpm = (analogRead(BPMPIN) >> 3) + 30; // from 30 to 157 bpm
  numSteps = (analogRead(NSTEPSPIN) >> 7) + 1; // from 1 to 8 steps 
}
