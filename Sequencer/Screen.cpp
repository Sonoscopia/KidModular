#include "Screen.h"

Screen::Screen() {
  // default constructor
}

Screen::Screen(UTFT _lcd, uint8_t font[]) {
  // pass class objects
  mLCD = _lcd; 
  mFont = font; 
}

void Screen::init(){
  mLCD.InitLCD();
  mLCD.setFont(mFont);
  mLCD.fillScr(VGA_BLACK); // set background color
  
  // Init Variables
  // center position to draw geometric shapes (circFrame)
  center[0] = WIDTH/2 + 30;
  center[1] = HEIGHT/2; 
  // BPM Text
  bpmText = String("BPM = 120");
  
  // Call initial functions
  drawLabels();
  drawCircFrame(); 
}

void Screen::drawLabels(){ // draw fixed text labels 
  mLCD.setColor(VGA_BLUE); // set used color 
  mLCD.print("BPM: ", 2, 2);
  mLCD.print("Size: ", 2, HEIGHT/2-8);
  mLCD.print("Dur: ", 2, HEIGHT-18);
}

void Screen::drawCircFrame(){ // draw circular frame to enclose geometric shpaes
  mLCD.setColor(VGA_GRAY);
  mLCD.drawCircle(center[0], center[1], RADIUS);
  mLCD.setColor(VGA_BLUE);
}

void Screen::printBPM(uint16_t _bpm){
  if(_bpm > 99) mLCD.print(String(_bpm), 64, 2);
  else {
    mLCD.print(String(_bpm), 64, 2);
    mLCD.print(" ", 96, 2);
  }
}

void Screen::printSize(uint8_t _numSteps){ // display number of steps
  mLCD.printNumI(_numSteps, 80, HEIGHT/2-8);
}

void Screen::printDur(uint8_t _dur[], uint8_t _stepEdit){ // display step durations
  mLCD.printNumI(_stepEdit+1, 64, HEIGHT-18); // print select step for edit
  mLCD.print("-", 80, HEIGHT-18); // separator
  if(_dur[_stepEdit]>9){ // display selected step duration
    mLCD.printNumI(_dur[_stepEdit], 96, HEIGHT-18);
  }
  else { // if dur < 0 print a leading '0'
    mLCD.print("0", 96, HEIGHT-18);
    mLCD.printNumI(_dur[_stepEdit], 112, HEIGHT-18);
  }
}

void Screen::drawShape(uint8_t _numSteps){
    // clear screen portion
    mLCD.setColor(VGA_BLACK);
    mLCD.fillCircle(center[0], center[1], RADIUS-2);
    drawCircFrame();
    
  switch(_numSteps){
    case 1:
      mLCD.fillCircle(center[0], center[1], STEPRADIUS);
    break;
    
    case 2: 
      mLCD.drawLine(center[0] - RADIUS*0.5, center[1]+RADIUS*0.5,center[0] + RADIUS*0.5, center[1]-RADIUS*0.5);
      mLCD.fillCircle(center[0] - RADIUS*0.5, center[1]+RADIUS*0.5, STEPRADIUS); // bottom-left
      mLCD.fillCircle(center[0] + RADIUS*0.5, center[1]-RADIUS*0.5, STEPRADIUS); // top-right
    break;
      
    case 3: 
      mLCD.drawLine(center[0] - RADIUS*0.5, center[1]+RADIUS*0.5, center[0] + RADIUS*0.5, center[1]+RADIUS*0.5);
      mLCD.drawLine(center[0] + RADIUS*0.5, center[1]+RADIUS*0.5, center[0], center[1]-RADIUS*0.5);
      mLCD.drawLine(center[0], center[1]-RADIUS*0.5, center[0] - RADIUS*0.5, center[1]+RADIUS*0.5);
      mLCD.fillCircle(center[0] - RADIUS*0.5, center[1]+RADIUS*0.5, STEPRADIUS); // bottom-left
      mLCD.fillCircle(center[0] + RADIUS*0.5, center[1]+RADIUS*0.5, STEPRADIUS); // bottom-right
      mLCD.fillCircle(center[0], center[1]-RADIUS*0.5, STEPRADIUS); // top-center
    break;
    
    case 4: 
      mLCD.setColor(VGA_BLUE);
      mLCD.drawLine(center[0] - RADIUS*0.5, center[1]+RADIUS*0.5, center[0] + RADIUS*0.5, center[1]+RADIUS*0.5);
      mLCD.drawLine(center[0] - RADIUS*0.5, center[1]-RADIUS*0.5, center[0] + RADIUS*0.5, center[1]-RADIUS*0.5);
      mLCD.drawLine(center[0] - RADIUS*0.5, center[1]-RADIUS*0.5, center[0] - RADIUS*0.5, center[1]+RADIUS*0.5);
      mLCD.drawLine(center[0] + RADIUS*0.5, center[1]-RADIUS*0.5, center[0] + RADIUS*0.5, center[1]+RADIUS*0.5);
      mLCD.fillCircle(center[0] - RADIUS*0.5, center[1]+RADIUS*0.5, STEPRADIUS); // bottom-left
      mLCD.fillCircle(center[0] + RADIUS*0.5, center[1]+RADIUS*0.5, STEPRADIUS); // bottom-right
      mLCD.fillCircle(center[0] - RADIUS*0.5, center[1]-RADIUS*0.5, STEPRADIUS); // top-left
      mLCD.fillCircle(center[0] + RADIUS*0.5, center[1]-RADIUS*0.5, STEPRADIUS); // top-right
    break;
      
    case 5:
      mLCD.drawLine(center[0] - RADIUS*0.4, center[1]+RADIUS*0.5, center[0] + RADIUS*0.4, center[1]+RADIUS*0.5);
      mLCD.drawLine(center[0] + RADIUS*0.4, center[1]+RADIUS*0.5, center[0] + RADIUS*0.65, center[1]-RADIUS*0.3);
      mLCD.drawLine(center[0] + RADIUS*0.65, center[1]-RADIUS*0.3, center[0], center[1]-RADIUS*0.7);
      mLCD.drawLine(center[0], center[1]-RADIUS*0.7, center[0] - RADIUS*0.65, center[1]-RADIUS*0.3);
      mLCD.drawLine(center[0] - RADIUS*0.65, center[1]-RADIUS*0.3, center[0] - RADIUS*0.4, center[1]+RADIUS*0.5);
      mLCD.fillCircle(center[0] - RADIUS*0.4, center[1]+RADIUS*0.5, STEPRADIUS); // bottom-left
      mLCD.fillCircle(center[0] + RADIUS*0.4, center[1]+RADIUS*0.5, STEPRADIUS); // bottom-right
      mLCD.fillCircle(center[0] + RADIUS*0.65, center[1]-RADIUS*0.3, STEPRADIUS); // top-right
      mLCD.fillCircle(center[0], center[1]-RADIUS*0.7, STEPRADIUS); // top-center
      mLCD.fillCircle(center[0] - RADIUS*0.65, center[1]-RADIUS*0.3, STEPRADIUS); // top-left 
    break;
    
    case 6: 
      mLCD.drawLine(center[0] - RADIUS*0.65, center[1]+RADIUS*0.3, center[0], center[1]+RADIUS*0.7);
      mLCD.drawLine(center[0], center[1]+RADIUS*0.7, center[0] + RADIUS*0.65, center[1]+RADIUS*0.3);
      mLCD.drawLine(center[0] + RADIUS*0.65, center[1]+RADIUS*0.3, center[0] + RADIUS*0.65, center[1]-RADIUS*0.3);
      mLCD.drawLine(center[0] + RADIUS*0.65, center[1]-RADIUS*0.3, center[0], center[1]-RADIUS*0.7);
      mLCD.drawLine(center[0], center[1]-RADIUS*0.7, center[0] - RADIUS*0.65, center[1]-RADIUS*0.3);
      mLCD.drawLine(center[0] - RADIUS*0.65, center[1]-RADIUS*0.3, center[0] - RADIUS*0.65, center[1]+RADIUS*0.3);
      mLCD.fillCircle(center[0] - RADIUS*0.65, center[1]+RADIUS*0.3, STEPRADIUS); // bottom-left
      mLCD.fillCircle(center[0], center[1]+RADIUS*0.7, STEPRADIUS); // bottom-center
      mLCD.fillCircle(center[0] + RADIUS*0.65, center[1]+RADIUS*0.3, STEPRADIUS); // bottom-right
      mLCD.fillCircle(center[0] + RADIUS*0.65, center[1]-RADIUS*0.3, STEPRADIUS); // top-right
      mLCD.fillCircle(center[0], center[1]-RADIUS*0.7, STEPRADIUS); // top-center
      mLCD.fillCircle(center[0] - RADIUS*0.65, center[1]-RADIUS*0.3, STEPRADIUS); // top-left
      break;
     
    case 7:
      mLCD.fillCircle(center[0] - RADIUS*0.3, center[1]+RADIUS*0.7, STEPRADIUS); // bottom-left
      mLCD.fillCircle(center[0] + RADIUS*0.3, center[1]+RADIUS*0.7, STEPRADIUS); // bottom-right
      mLCD.fillCircle(center[0] + RADIUS*0.65, center[1]+RADIUS*0.25, STEPRADIUS); // middle-right
      mLCD.fillCircle(center[0] + RADIUS*0.55, center[1]-RADIUS*0.35, STEPRADIUS); // top-right
      mLCD.fillCircle(center[0], center[1]-RADIUS*0.7, STEPRADIUS); // top-center
      mLCD.fillCircle(center[0] - RADIUS*0.55, center[1]-RADIUS*0.35, STEPRADIUS); // top-left
      mLCD.fillCircle(center[0] - RADIUS*0.65, center[1]+RADIUS*0.25, STEPRADIUS); // middle-left
      mLCD.drawLine(center[0] - RADIUS*0.3, center[1]+RADIUS*0.7, center[0] + RADIUS*0.3, center[1]+RADIUS*0.7);
      mLCD.drawLine(center[0] + RADIUS*0.3, center[1]+RADIUS*0.7, center[0] + RADIUS*0.65, center[1]+RADIUS*0.25);
      mLCD.drawLine(center[0] + RADIUS*0.65, center[1]+RADIUS*0.25, center[0] + RADIUS*0.55, center[1]-RADIUS*0.35);
      mLCD.drawLine(center[0] + RADIUS*0.55, center[1]-RADIUS*0.35, center[0], center[1]-RADIUS*0.7);
      mLCD.drawLine(center[0], center[1]-RADIUS*0.7, center[0] - RADIUS*0.55, center[1]-RADIUS*0.35);
      mLCD.drawLine(center[0] - RADIUS*0.55, center[1]-RADIUS*0.35, center[0] - RADIUS*0.65, center[1]+RADIUS*0.25);
      mLCD.drawLine(center[0] - RADIUS*0.65, center[1]+RADIUS*0.25, center[0] - RADIUS*0.3, center[1]+RADIUS*0.7);
    break;
    
    case 8: 
      mLCD.fillCircle(center[0] - RADIUS*0.3, center[1]+RADIUS*0.7, STEPRADIUS); // bottom-left
      mLCD.fillCircle(center[0] + RADIUS*0.3, center[1]+RADIUS*0.7, STEPRADIUS); // bottom-right
      mLCD.fillCircle(center[0] + RADIUS*0.65, center[1]+RADIUS*0.25, STEPRADIUS); // middleDown-right
      mLCD.fillCircle(center[0] + RADIUS*0.65, center[1]-RADIUS*0.25, STEPRADIUS); // middleUp-right
      mLCD.fillCircle(center[0] + RADIUS*0.3, center[1]-RADIUS*0.7, STEPRADIUS); // top-right
      mLCD.fillCircle(center[0] - RADIUS*0.3, center[1]-RADIUS*0.7, STEPRADIUS); // top-left
      mLCD.fillCircle(center[0] - RADIUS*0.65, center[1]-RADIUS*0.25, STEPRADIUS); // middleUp-left 
      mLCD.fillCircle(center[0] - RADIUS*0.65, center[1]+RADIUS*0.25, STEPRADIUS); // middleDown-left
      
      mLCD.drawLine(center[0] - RADIUS*0.3, center[1]+RADIUS*0.7, center[0] + RADIUS*0.3, center[1]+RADIUS*0.7);
      mLCD.drawLine(center[0] + RADIUS*0.3, center[1]+RADIUS*0.7, center[0] + RADIUS*0.65, center[1]+RADIUS*0.25);
      mLCD.drawLine(center[0] + RADIUS*0.65, center[1]+RADIUS*0.25, center[0] + RADIUS*0.65, center[1]-RADIUS*0.25);
      mLCD.drawLine(center[0] + RADIUS*0.65, center[1]-RADIUS*0.25, center[0] + RADIUS*0.3, center[1]-RADIUS*0.7);
      mLCD.drawLine(center[0] + RADIUS*0.3, center[1]-RADIUS*0.7, center[0] - RADIUS*0.3, center[1]-RADIUS*0.7);
      mLCD.drawLine(center[0] - RADIUS*0.3, center[1]-RADIUS*0.7, center[0] - RADIUS*0.65, center[1]-RADIUS*0.25);
      mLCD.drawLine(center[0] - RADIUS*0.65, center[1]-RADIUS*0.25, center[0] - RADIUS*0.65, center[1]+RADIUS*0.25);
      mLCD.drawLine(center[0] - RADIUS*0.65, center[1]+RADIUS*0.25, center[0] - RADIUS*0.3, center[1]+RADIUS*0.7);
    
    default:
    break;
  }
}


