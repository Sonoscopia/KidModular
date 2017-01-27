/*
KidModular - OSCILLATOR 
by Tiago Angelo (aka p1nho)

Built with: 
Arduino 1.0.5 (on Arduino MEGA2560)
Stripped out version of UTFT Library v.2.82 (12 Jul 2016) by Henning Karlsen
Audio ouput using Direct Digital Synthesis method from an example by Martin Nawrath
*/

/************************************ INCLUDED LIBS & HEADERS ***********************************************/
#include "avr/pgmspace.h"
#include "Wavetables.h"
#include <UTFT.h>

/************************************ DEFINITIONS ***********************************************************/
// Audio
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
// MEGA=pin10 UNO=pin11 
#define AUDIOPIN 10

/************************************ CLASS OBJECTS *********************************************************/
// LCD
UTFT LCD(CTE32HR,38,39,40,41);

/************************************ VARIABLES *************************************************************/
// Audio
byte sig; // curent signal value
double dfreq;
// const double refclk=31372.549;  // =16MHz / 510
const double refclk=31376.6;      // measured
// variables used inside interrupt service declared as voilatile
volatile byte icnt;              // var inside interrupt
volatile byte icnt1;             // var inside interrupt
volatile byte c4ms;              // counter incremented all 4ms
volatile unsigned long phaccu;   // pahse accumulator
volatile unsigned long tword_m;  // dds tuning word m

// LCD
unsigned int xPos = 0;
byte scopeBuf[478]; 
/************************************ SETUP *****************************************************************/
void setup()
{
  // LCD setup - uses delay() and therefore must go before any interrupts
  LCD.InitLCD();
  
  // Audio setup
  pinMode(AUDIOPIN, OUTPUT); // output / frequency output
  Setup_timer2();
  // disable interrupts to avoid timing distortion
  cbi (TIMSK0,TOIE0);              // disable Timer0 !!! delay() is now not available
  sbi (TIMSK2,TOIE2);              // enable Timer2 Interrupt
  dfreq=1000.0;                    // initial output frequency = 1000.o Hz
  tword_m=pow(2,32)*dfreq/refclk;  // calulate DDS new tuning word 
}

/************************************ LOOP ******************************************************************/
void loop()
{
  // LCD clear
  //LCD.fillScr(VGA_RED);
  
  // LCD - Oscilloscope
  oscilloscope();
  
  
  // Audio
  while(1) {
     if (c4ms > 250) {                 // timer / wait for a full second
      c4ms=0;
      dfreq=analogRead(0);             // read Poti on analog pin 0 to adjust output frequency from 0..1023 Hz

      cbi (TIMSK2,TOIE2);              // disble Timer2 Interrupt
      tword_m=pow(2,32)*dfreq/refclk;  // calulate DDS new tuning word
      sbi (TIMSK2,TOIE2);              // enable Timer2 Interrupt 
    }
  }


  
}

/************************************ AUDIO FUNCTIONS *******************************************************/
// timer2 setup
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

// Timer2 Interrupt Service at 31372,550 KHz = 32uSec
// this is the timebase REFCLOCK for the DDS generator
// FOUT = (M (REFCLK)) / (2 exp 32)
// runtime : 8 microseconds ( inclusive push and pop)
ISR(TIMER2_OVF_vect) {

  phaccu=phaccu+tword_m; // soft DDS, phase accu with 32 bits
  icnt=phaccu >> 24;     // use upper 8 bits for phase accu as frequency information
                         // read value fron ROM sine table and send to PWM DAC
  sig = pgm_read_byte_near(sine256 + icnt);
  OCR2A= sig;   
  // fill scope buffer
  scopeBuf[xPos] = sig - 160;
  xPos++;
  if (xPos > 478){ 
    xPos = 0;
  }
  
  if(icnt1++ == 125) {  // increment variable c4ms all 4 milliseconds
    c4ms++;
    icnt1=0;
   }   
}

/************************************** LCD FUNCTIONS *******************************************************/
void oscilloscope(){
  LCD.fillScr(VGA_RED); // clear screen
  LCD.setColor(VGA_WHITE); // set wave color
  for(int i = 1; i < 478; i++){
    //drawLine(x1, y1, x2, y2);
    LCD.drawLine(i-1, scopeBuf[i-1], i, scopeBuf[i]);
  }
}
