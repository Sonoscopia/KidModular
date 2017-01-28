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
#define STEPRADIUS 8 // step circle radius
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
  center[0] = WIDTH/2 + 30;
  center[1] = HEIGHT/2;
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
  drawShape();
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

void drawShape(){
  if(numSteps != _numSteps){
    lcd.setColor(VGA_BLACK);
    lcd.fillCircle(center[0], center[1], RADIUS-2);
  }
  switch(numSteps){
    case 1:
      lcd.setColor(VGA_BLUE);
      lcd.fillCircle(center[0], center[1], STEPRADIUS);
    break;
    
    case 2: 
      lcd.setColor(VGA_BLUE);
      lcd.drawLine(center[0] - RADIUS*0.5, center[1]+RADIUS*0.5,center[0] + RADIUS*0.5, center[1]-RADIUS*0.5);
      lcd.fillCircle(center[0] - RADIUS*0.5, center[1]+RADIUS*0.5, STEPRADIUS); // bottom-left
      lcd.fillCircle(center[0] + RADIUS*0.5, center[1]-RADIUS*0.5, STEPRADIUS); // top-right
    break;
      
    case 3: 
      lcd.setColor(VGA_BLUE);
      lcd.drawLine(center[0] - RADIUS*0.5, center[1]+RADIUS*0.5, center[0] + RADIUS*0.5, center[1]+RADIUS*0.5);
      lcd.drawLine(center[0] + RADIUS*0.5, center[1]+RADIUS*0.5, center[0], center[1]-RADIUS*0.5);
      lcd.drawLine(center[0], center[1]-RADIUS*0.5, center[0] - RADIUS*0.5, center[1]+RADIUS*0.5);
      lcd.fillCircle(center[0] - RADIUS*0.5, center[1]+RADIUS*0.5, STEPRADIUS); // bottom-left
      lcd.fillCircle(center[0] + RADIUS*0.5, center[1]+RADIUS*0.5, STEPRADIUS); // bottom-right
      lcd.fillCircle(center[0], center[1]-RADIUS*0.5, STEPRADIUS); // top-center
    break;
    
    case 4: 
      lcd.setColor(VGA_BLUE);
      lcd.drawLine(center[0] - RADIUS*0.5, center[1]+RADIUS*0.5, center[0] + RADIUS*0.5, center[1]+RADIUS*0.5);
      lcd.drawLine(center[0] - RADIUS*0.5, center[1]-RADIUS*0.5, center[0] + RADIUS*0.5, center[1]-RADIUS*0.5);
      lcd.drawLine(center[0] - RADIUS*0.5, center[1]-RADIUS*0.5, center[0] - RADIUS*0.5, center[1]+RADIUS*0.5);
      lcd.drawLine(center[0] + RADIUS*0.5, center[1]-RADIUS*0.5, center[0] + RADIUS*0.5, center[1]+RADIUS*0.5);
      lcd.fillCircle(center[0] - RADIUS*0.5, center[1]+RADIUS*0.5, STEPRADIUS); // bottom-left
      lcd.fillCircle(center[0] + RADIUS*0.5, center[1]+RADIUS*0.5, STEPRADIUS); // bottom-right
      lcd.fillCircle(center[0] - RADIUS*0.5, center[1]-RADIUS*0.5, STEPRADIUS); // top-left
      lcd.fillCircle(center[0] + RADIUS*0.5, center[1]-RADIUS*0.5, STEPRADIUS); // top-right
    break;
      
    case 5:
      lcd.setColor(VGA_BLUE);
      lcd.drawLine(center[0] - RADIUS*0.4, center[1]+RADIUS*0.5, center[0] + RADIUS*0.4, center[1]+RADIUS*0.5);
      lcd.drawLine(center[0] + RADIUS*0.4, center[1]+RADIUS*0.5, center[0] + RADIUS*0.65, center[1]-RADIUS*0.3);
      lcd.drawLine(center[0] + RADIUS*0.65, center[1]-RADIUS*0.3, center[0], center[1]-RADIUS*0.7);
      lcd.drawLine(center[0], center[1]-RADIUS*0.7, center[0] - RADIUS*0.65, center[1]-RADIUS*0.3);
      lcd.drawLine(center[0] - RADIUS*0.65, center[1]-RADIUS*0.3, center[0] - RADIUS*0.4, center[1]+RADIUS*0.5);
      lcd.fillCircle(center[0] - RADIUS*0.4, center[1]+RADIUS*0.5, STEPRADIUS); // bottom-left
      lcd.fillCircle(center[0] + RADIUS*0.4, center[1]+RADIUS*0.5, STEPRADIUS); // bottom-right
      lcd.fillCircle(center[0] + RADIUS*0.65, center[1]-RADIUS*0.3, STEPRADIUS); // top-right
      lcd.fillCircle(center[0], center[1]-RADIUS*0.7, STEPRADIUS); // top-center
      lcd.fillCircle(center[0] - RADIUS*0.65, center[1]-RADIUS*0.3, STEPRADIUS); // top-left 
    break;
    
    case 6: 
      lcd.setColor(VGA_BLUE);
      lcd.drawLine(center[0] - RADIUS*0.65, center[1]+RADIUS*0.3, center[0], center[1]+RADIUS*0.7);
      lcd.drawLine(center[0], center[1]+RADIUS*0.7, center[0] + RADIUS*0.65, center[1]+RADIUS*0.3);
      lcd.drawLine(center[0] + RADIUS*0.65, center[1]+RADIUS*0.3, center[0] + RADIUS*0.65, center[1]-RADIUS*0.3);
      lcd.drawLine(center[0] + RADIUS*0.65, center[1]-RADIUS*0.3, center[0], center[1]-RADIUS*0.7);
      lcd.drawLine(center[0], center[1]-RADIUS*0.7, center[0] - RADIUS*0.65, center[1]-RADIUS*0.3);
      lcd.drawLine(center[0] - RADIUS*0.65, center[1]-RADIUS*0.3, center[0] - RADIUS*0.65, center[1]+RADIUS*0.3);
      lcd.fillCircle(center[0] - RADIUS*0.65, center[1]+RADIUS*0.3, STEPRADIUS); // bottom-left
      lcd.fillCircle(center[0], center[1]+RADIUS*0.7, STEPRADIUS); // bottom-center
      lcd.fillCircle(center[0] + RADIUS*0.65, center[1]+RADIUS*0.3, STEPRADIUS); // bottom-right
      lcd.fillCircle(center[0] + RADIUS*0.65, center[1]-RADIUS*0.3, STEPRADIUS); // top-right
      lcd.fillCircle(center[0], center[1]-RADIUS*0.7, STEPRADIUS); // top-center
      lcd.fillCircle(center[0] - RADIUS*0.65, center[1]-RADIUS*0.3, STEPRADIUS); // top-left
      break;
     
    case 7:
      lcd.setColor(VGA_BLUE);
      lcd.fillCircle(center[0] - RADIUS*0.3, center[1]+RADIUS*0.7, STEPRADIUS); // bottom-left
      lcd.fillCircle(center[0] + RADIUS*0.3, center[1]+RADIUS*0.7, STEPRADIUS); // bottom-right
      lcd.fillCircle(center[0] + RADIUS*0.65, center[1]+RADIUS*0.25, STEPRADIUS); // middle-right
      lcd.fillCircle(center[0] + RADIUS*0.55, center[1]-RADIUS*0.35, STEPRADIUS); // top-right
      lcd.fillCircle(center[0], center[1]-RADIUS*0.7, STEPRADIUS); // top-center
      lcd.fillCircle(center[0] - RADIUS*0.55, center[1]-RADIUS*0.35, STEPRADIUS); // top-left
      lcd.fillCircle(center[0] - RADIUS*0.65, center[1]+RADIUS*0.25, STEPRADIUS); // middle-left
      lcd.drawLine(center[0] - RADIUS*0.3, center[1]+RADIUS*0.7, center[0] + RADIUS*0.3, center[1]+RADIUS*0.7);
      lcd.drawLine(center[0] + RADIUS*0.3, center[1]+RADIUS*0.7, center[0] + RADIUS*0.65, center[1]+RADIUS*0.25);
      lcd.drawLine(center[0] + RADIUS*0.65, center[1]+RADIUS*0.25, center[0] + RADIUS*0.55, center[1]-RADIUS*0.35);
      lcd.drawLine(center[0] + RADIUS*0.55, center[1]-RADIUS*0.35, center[0], center[1]-RADIUS*0.7);
      lcd.drawLine(center[0], center[1]-RADIUS*0.7, center[0] - RADIUS*0.55, center[1]-RADIUS*0.35);
      lcd.drawLine(center[0] - RADIUS*0.55, center[1]-RADIUS*0.35, center[0] - RADIUS*0.65, center[1]+RADIUS*0.25);
      lcd.drawLine(center[0] - RADIUS*0.65, center[1]+RADIUS*0.25, center[0] - RADIUS*0.3, center[1]+RADIUS*0.7);
    break;
    
    case 8: 
      lcd.setColor(VGA_BLUE);
      lcd.fillCircle(center[0] - RADIUS*0.3, center[1]+RADIUS*0.7, STEPRADIUS); // bottom-left
      lcd.fillCircle(center[0] + RADIUS*0.3, center[1]+RADIUS*0.7, STEPRADIUS); // bottom-right
      lcd.fillCircle(center[0] + RADIUS*0.65, center[1]+RADIUS*0.25, STEPRADIUS); // middleDown-right
      lcd.fillCircle(center[0] + RADIUS*0.65, center[1]-RADIUS*0.25, STEPRADIUS); // middleUp-right
      lcd.fillCircle(center[0] + RADIUS*0.3, center[1]-RADIUS*0.7, STEPRADIUS); // top-right
      lcd.fillCircle(center[0] - RADIUS*0.3, center[1]-RADIUS*0.7, STEPRADIUS); // top-left
      lcd.fillCircle(center[0] - RADIUS*0.65, center[1]-RADIUS*0.25, STEPRADIUS); // middleUp-left 
      lcd.fillCircle(center[0] - RADIUS*0.65, center[1]+RADIUS*0.25, STEPRADIUS); // middleDown-left
      
      lcd.drawLine(center[0] - RADIUS*0.3, center[1]+RADIUS*0.7, center[0] + RADIUS*0.3, center[1]+RADIUS*0.7);
      lcd.drawLine(center[0] + RADIUS*0.3, center[1]+RADIUS*0.7, center[0] + RADIUS*0.65, center[1]+RADIUS*0.25);
      lcd.drawLine(center[0] + RADIUS*0.65, center[1]+RADIUS*0.25, center[0] + RADIUS*0.65, center[1]-RADIUS*0.25);
      lcd.drawLine(center[0] + RADIUS*0.65, center[1]-RADIUS*0.25, center[0] + RADIUS*0.3, center[1]-RADIUS*0.7);
      lcd.drawLine(center[0] + RADIUS*0.3, center[1]-RADIUS*0.7, center[0] - RADIUS*0.3, center[1]-RADIUS*0.7);
      lcd.drawLine(center[0] - RADIUS*0.3, center[1]-RADIUS*0.7, center[0] - RADIUS*0.65, center[1]-RADIUS*0.25);
      lcd.drawLine(center[0] - RADIUS*0.65, center[1]-RADIUS*0.25, center[0] - RADIUS*0.65, center[1]+RADIUS*0.25);
      lcd.drawLine(center[0] - RADIUS*0.65, center[1]+RADIUS*0.25, center[0] - RADIUS*0.3, center[1]+RADIUS*0.7);
    
    default:
    break;
  }
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



