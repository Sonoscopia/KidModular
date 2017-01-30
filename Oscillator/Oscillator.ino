/*
KidModular - OSCILLATOR 
by Tiago Angelo (aka p1nho)

Built with: 
Arduino 1.0.5 (on Arduino MEGA2560)
Stripped out version of UTFT Library v.2.82 (12 Jul 2016) by Henning Karlsen
Audio ouput using Direct Digital Synthesis method from an example by Martin Nawrath
 * KHM 2009 /  Martin Nawrath
 * Kunsthochschule fuer Medien Koeln
 * Academy of Media Arts Cologne
*/

/************************************ INCLUDED LIBS & HEADERS ***********************************************/
#include "avr/pgmspace.h"
#include "avr/interrupt.h"
#include "Waveforms.h"
#include <UTFT.h>
#include "Screen.h"

/************************************ DEFINITIONS ***********************************************************/
// Audio Interrupts
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
// Audio Pins 
#define AUDIO_OUT 10

/************************************ CLASS OBJECTS *********************************************************/
// LCD Screen
UTFT LCD(CTE32HR,38,39,40,41);
extern uint8_t BigFont[];
Screen screen(LCD, BigFont);
/************************************ VARIABLES *************************************************************/
// Audio 
double dfreq, _dfreq=0; // freq must be a double!!!
uint_fast16_t updateCount;
// const double refclk=31372.549;  // =16MHz / 510 (8bit PWM mode takes 510 clocks to cycle)
//const double refclk=41830.065; // same speed for 12MHz clock ????
const double refclk=31376.6;      // measured
// variables used inside interrupt service declared as voilatile
volatile uint_fast8_t icnt;      // var inside interrupt
volatile uint_fast8_t icnt1;     // var inside interrupt
volatile boolean trigger = 0; // trigger for audio control operations 
volatile uint_fast32_t phaccu;   // pahse accumulator
volatile uint_fast32_t tword_m;  // dds tuning word m

/************************************ SETUP ****************************************************************/
void setup()
{
  pinMode(AUDIO_OUT, OUTPUT); // pin11= PWM  output / frequency output (pin10 on MEGA)
  // Init LCD
  screen.init(); 
  
  // Setup Audio Timer
  Setup_timer2();

  // disable interrupts to avoid timing distortion
  cbi (TIMSK0,TOIE0);              // disable Timer0 !!! delay() is now not available
  sbi (TIMSK2,TOIE2);              // enable Timer2 Interrupt

  dfreq=1000.0;                    // initial output frequency = 1000.o Hz
  _dfreq = dfreq;
  tword_m=pow(2,32)*dfreq/refclk;  // calulate DDS new tuning word
 

}

/************************************ LOOP *****************************************************************/
void loop()
{
  
while(1) {
    
     // Update Control 
     if(updateCount++ > 4191){ // run every ?ms 
        _dfreq = analogRead(0);
        updateCount = 0;
        screen.drawScope(sine256, dfreq);
     }
     // update frequency
     if (trigger && dfreq != _dfreq) { // if phase=0 and freq. changes
        
        dfreq = _dfreq;         // read Poti on analog pin 0 to adjust output frequency from 0..1023 Hz
        
        cbi (TIMSK2,TOIE2);              // disble Timer2 Interrupt
        tword_m=pow(2,32)*dfreq/refclk;  // calulate DDS new tuning word
        sbi (TIMSK2,TOIE2);              // enable Timer2 Interrupt
        
        trigger=false; // reset trigger 
      } 
   }
}

/************************************ AUDIO FUNCTIONS *******************************************************/
// Timer2 Setup
// set prscaler to 1, PWM mode to phase correct PWM,  16000000/510 = 31372.55 Hz clock
void Setup_timer2() {

// Timer2 Clock Prescaler to : 1
  sbi (TCCR2B, CS20);
  cbi (TCCR2B, CS21);
  cbi (TCCR2B, CS22);

  // Timer2 PWM Mode set to Phase Correct PWM
  cbi (TCCR2A, COM2A0);  // clear Compare Match
  sbi (TCCR2A, COM2A1);

  sbi (TCCR2A, WGM20);  // Mode 1  / Phase Correct PWM
  cbi (TCCR2A, WGM21);
  cbi (TCCR2B, WGM22);
}

//******************************************************************
// Timer2 Interrupt Service at 31372,550 KHz = 32uSec
// this is the timebase REFCLOCK for the DDS generator
// FOUT = (M (REFCLK)) / (2 exp 32)
// runtime : 8 microseconds ( inclusive push and pop)
ISR(TIMER2_OVF_vect) {

  phaccu=phaccu+tword_m; // soft DDS, phase accu with 32 bits
  icnt=phaccu >> 24;     // use upper 8 bits for phase accu as frequency information
                         // read value fron ROM sine table and send to PWM DAC
  OCR2A=pgm_read_byte_near(sine256 + icnt);    

  if(icnt == 0){ // trigger updateControl at beginning of table read
    trigger=true;
  }
  
}

