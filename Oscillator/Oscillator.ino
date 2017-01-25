/*
KidModular - OSCILLATOR 
by Tiago Angelo (aka p1nho)

Built with: 
Arduino 1.0.5 (on Arduino MEGA2560)
Mozzi v.1.0.2 Aedes australis (2015-05-20:23)
[mozzi_config: STANDARD_PLUS 16384Hz]
UTFT v.2.82 (12 Jul 2016)
*/

/************************************ INCLUDED LIBS & HEADERS ***********************************************/
#include <UTFT.h>
#include <MozziGuts.h>
#include <Oscil.h>
/************************************ WAVEFORMS *************************************************************/
#include <tables/sin2048_int8.h> 

/************************************ CLASS OBJECTS *********************************************************/
UTFT myGLCD(CTE32HR,38,39,40,41); // define pins for ArduinoMEGA
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin(SIN2048_DATA);

/************************************ DEFINITIONS ***********************************************************/
#define CONTROL_RATE 64 // powers of 2

/************************************ VARIABLES *************************************************************/

/************************************ SETUP *****************************************************************/
void setup(){  
  // Audio Setup
  startMozzi(CONTROL_RATE); // set a control rate of 64 (powers of 2 please)
  aSin.setFreq(880); // set the frequency
  
  // LCD Setup
  pauseMozzi(); //enable delay() function
  myGLCD.InitLCD();
  unPauseMozzi();
}

/************************************ CONTROL ***************************************************************/
void updateControl(){ // put changing controls in here
  // Clear Screen
  //myGLCD.clrScr(); //-> WATCH OUT: this causes strange behaviour in audio
//  myGLCD.setColor(255, 0, 0);
//  myGLCD.fillRect(0, 0, 480, 320);
  myGLCD.fillScr(VGA_BLUE);
}

/************************************ AUDIO *****************************************************************/
int updateAudio(){

  return aSin.next(); // return an int signal centred around 0
}

/************************************ LOOP ******************************************************************/
void loop(){
  audioHook(); // required here
}



