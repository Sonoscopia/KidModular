/*
KidModular - OSCILLATOR 
by Tiago Angelo (aka p1nho)

Built with: 
Arduino 1.0.5
Mozzi v.1.0.2 Aedes australis (2015-05-20:23)
[mozzi_config: STANDARD_PLUS 16384Hz]

*/

/************************************ INCLUDED LIBS & HEADERS ***********************************************/
#include <MozziGuts.h>
#include <Oscil.h> 
/************************************ WAVEFORMS *************************************************************/
#include <tables/sin2048_int8.h> 

/************************************ CLASS OBJECTS *********************************************************/
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin(SIN2048_DATA);


/************************************ DEFINITIONS ***********************************************************/
#define CONTROL_RATE 64 // powers of 2

/************************************ VARIABLES *************************************************************/

/************************************ SETUP *****************************************************************/
void setup(){
  startMozzi(CONTROL_RATE); // set a control rate of 64 (powers of 2 please)
  aSin.setFreq(440); // set the frequency
}

/************************************ CONTROL ***************************************************************/
void updateControl(){
  // put changing controls in here
}

/************************************ AUDIO *****************************************************************/
int updateAudio(){
  return aSin.next(); // return an int signal centred around 0
}

/************************************ LOOP ******************************************************************/
void loop(){
  audioHook(); // required here
}



