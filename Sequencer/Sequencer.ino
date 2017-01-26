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
// SEQUENCER
#define MAXSTEPS 8

/************************************ CLASS OBJECTS *********************************************************/
// LCD
UTFT LCD(CTE32HR,38,39,40,41);

/************************************ VARIABLES *************************************************************/
// Sequencer
byte bpm; // beats-per-minute
byte curStep; // current step 
byte numSteps; // selected number of steps
byte pitch[MAXSTEPS]; // array with pitch of each step 
byte dur[MAXSTEPS]; // array with duration of each step
// LCD

/************************************ SETUP *****************************************************************/
void setup()
{
  // LCD setup - uses delay() and therefore must go before any interrupts
  LCD.InitLCD();
  
}

/************************************ LOOP ******************************************************************/
void loop()
{
  
  
}

/************************************ SEQUENCER FUNCTIONS ***************************************************/


/************************************** LCD FUNCTIONS *******************************************************/

