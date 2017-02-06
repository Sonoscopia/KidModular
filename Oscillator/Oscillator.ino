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
#define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Encoder.h>
#include "avr/pgmspace.h"
//#include "avr/interrupt.h"
#include "Waveforms.h"
#include <UTFT.h>
#include "Screen.h"

/************************************ DEFINITIONS ***********************************************************/
#define DEBUG 1

// Routine Rates
//#define AUDIO_RATE 31373
#define CTRL_RATE 32 // 64Hz
#define SCRN_RATE 240 // 480Hz

// Audio Interrupts
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))

// NOTE: pins 4, 9, 10 & 13 ARE DISABLED !!!!
// Audio Pins 
#define AUDIO_OUT 10
// CV Pins
#define GATEPIN 8
#define PITCHPIN 0 // analog port A0 
// Controls - Buttons
#define MODEPIN 14 
#define ENC1B 18
#define ENC2B 17
#define ENC3B 16
#define ENC4B 15
// Controls - Encoders 
#define ENC1L 2
#define ENC1R 3
#define ENC2L 5
#define ENC2R 6
#define ENC3L 7
#define ENC3R 11
#define ENC4L 44
#define ENC4R 46
// LED
#define LED 12

/************************************ CLASS OBJECTS *********************************************************/
// LCD Screen
UTFT LCD(CTE32HR,38,39,40,41);
extern uint8_t BigFont[];
Screen screen(LCD, BigFont);
// Controls - Mode Button
boolean mode=0, _m=1, m; 
// Controls - Encoder 1
Encoder enc1(ENC1L, ENC1R);
byte e1val = -1, _e1val;
boolean e1but, _e1but = false; // button
// Controls - Encoder 2
Encoder enc2(ENC2L, ENC2R);
byte e2val = -1, _e2val;
boolean e2but, _e2but = false; // button
// Controls - Encoder 3
Encoder enc3(ENC3L, ENC3R);
byte e3val = -1, _e3val;
boolean e3but, _e3but = false; // button
// Controls - Encoder 4
Encoder enc4(ENC4L, ENC4R);
byte e4val = -1, _e4val;
boolean e4but, _e4but = false; // button

/************************************ VARIABLES *************************************************************/
// Audio 
double dfreq, _dfreq=0; // freq must be a double!!!
// const double refclk=31372.549;  // =16MHz / 510 (8bit PWM mode takes 510 clocks to cycle)
//const double refclk=41830.065; // same speed for 12MHz clock ????
const double refclk=31376.6;      // measured
// variables used inside interrupt service declared as voilatile
volatile uint_fast8_t icnt;      // increment0 inside interrupt (used for audio sample udpate)
volatile uint_fast16_t icnt1;    // increment1 inside interrupt (used for control update)
volatile uint_fast16_t icnt2;    // increment2 inside interrupt (used for screen update)
volatile boolean zcross = 0; // trigger for audio control operations 
volatile uint_fast32_t phaccu;   // pahse accumulator
volatile uint_fast32_t tword_m;  // dds tuning word m
// Audio params - frequency
const float freqMul[] = {0.1, 1, 2, 5, 10, 20, 50, 100}; // frequency multipliers
uint_fast8_t fMul = 1; 
// Audio params - envelope (ADSR)
const float atkMul[] = { 1, 2, 5, 10, 20, 50, 100, 250}; // attack multipliers
uint_fast8_t aMul = 1;
const float dcyMul[] = { 1, 2, 5, 10, 20, 50, 100, 250}; // attack multipliers
uint_fast8_t dMul = 1;
const float susMul[] = { 1, 2, 5, 10, 20, 50 }; // attack multipliers
uint_fast8_t sMul = 1;
const float relMul[] = { 1, 2, 5, 10, 20, 50, 100, 250}; // attack multipliers
uint_fast8_t rMul = 1;
uint_fast16_t atk=100, dcy=100, rel=250; // max time = 2^16 * 1/refclk = 2seconds
uint_fast8_t sus=127; // min=0 max=255
uint_fast16_t ecnt=0; // envelope counter
uint_fast8_t estg=0; // envelope stage 0-atk, 1-decay, 2-sus, 3-rel
// Audio params - selected waveform 

uint_fast8_t *waveform = tri256;
// Routine speed calcs 
const uint16_t control_rate = (1.f/CTRL_RATE) / (1/refclk); // in audio samples = sample rate(hz) / control rate (hz)
boolean ctrlTrigger = false; 
const uint16_t screen_rate = (1.f/SCRN_RATE) / (1/refclk); // in audio samples = sample rate(hz) / screen rate (hz)
boolean scrnTrigger = false;

/************************************ SETUP ****************************************************************/
void setup()
{
  if(DEBUG) {
    Serial.begin(9600);
    Serial.print("Control Rate in samples: ");
    Serial.println(control_rate);
    Serial.print("Screen Rate in samples: ");
    Serial.println(screen_rate);
  }
  // Init LCD
  screen.init(&mode, waveform); 
  // Set Pins
  pinMode(MODEPIN, INPUT_PULLUP);
  pinMode(ENC1B, INPUT_PULLUP);
  pinMode(ENC2B, INPUT_PULLUP);
  pinMode(ENC3B, INPUT_PULLUP);
  pinMode(ENC4B, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  pinMode(AUDIO_OUT, OUTPUT); // pin11= PWM  output / frequency output (pin10 on MEGA)
  pinMode(GATEPIN, OUTPUT);
  
  // Setup Audio Timer
  Setup_timer2();

  // disable interrupts to avoid timing distortion
  cbi (TIMSK0,TOIE0);              // disable Timer0 !!! delay() is now not available
  sbi (TIMSK2,TOIE2);              // enable Timer2 Interrupt

  dfreq=1000.0;                    // initial output frequency = 1000.o Hz
  _dfreq = dfreq;
  tword_m=pow(2,32)*dfreq/refclk;  // calulate DDS new tuning word
  
  screen.setFrequency(&dfreq, &fMul);
}

/************************************ LOOP *****************************************************************/
void loop()
{
  
while(1) {
     if(DEBUG){ 
       Serial.println(mode);
     }
     
     readEncoders(); // encoders must be called as fast as possible
      
     // UPDATE SCREEN (runs at SCRN_RATE)
     if(scrnTrigger){ 
       screen.drawDisplay();
       scrnTrigger = false;
     }
     // UPDATE CONTROL (runs at CTRL_RATE)
     if(ctrlTrigger){
       updateControls();
       screen.drawParams();
       ctrlTrigger = false; 
     }
     // UPDATE FREQUENCY (runs when table index = 0)
     if (zcross && dfreq != _dfreq) { // if phase=0 and freq. changes
        dfreq = _dfreq;         // read Poti on analog pin 0 to adjust output frequency from 0..1023 Hz
        // !!!INTERRUPT!!! TO CHANGE FREQUENCY
        cbi (TIMSK2,TOIE2);              // disble Timer2 Interrupt
        tword_m=pow(2,32)*dfreq/refclk;  // calulate DDS new tuning word
        sbi (TIMSK2,TOIE2);              // enable Timer2 Interrupt
  
        zcross=false; // reset zero-crossing 
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
  OCR2A=pgm_read_byte_near(waveform + icnt);    
  
  if(icnt == 0){ // trigger at beginning of table read
    zcross=true;
  } 
  if(icnt1++ > control_rate){  // at CTRL_RATE(64Hz) = 490 
    icnt1=0;
    ctrlTrigger = true;
  }
  if(icnt2++ > screen_rate){ 
    icnt2=0;
    scrnTrigger = true;
  }
}

/************************************ UPDATE CONTROLS *****************************************************/
void readEncoders(){
  // Encoder 1
  _e1val = enc1.read() << 2; // extend readings to improve readibility 
    if(e1val > _e1val){ 
      if(mode) atk -= atkMul[aMul]; 
      else _dfreq -= freqMul[fMul];
      e1val = _e1val;  // update
    }
    if(e1val < _e1val) {
      if(mode) atk += atkMul[aMul]; 
      else _dfreq += freqMul[fMul];
      e1val = _e1val; // update
    }
}

void updateControls(){
  // Mode - Button
  m = digitalRead(MODEPIN);
  if(m < 1 && m != _m){
    mode = !mode;
  }
  _m = m;
  
  // Encoder 1 - Button
  e1but = digitalRead(ENC1B);
  if(e1but < 1 && e1but != _e1but){
    fMul++;
    if(fMul > 7) fMul=0;
  } 

  _e1but = e1but;
}
