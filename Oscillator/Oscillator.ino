/*
 *
 * DDS Sine Generator mit ATMEGS 168
 * Timer2 generates the  31250 KHz Clock Interrupt
 *
 * KHM 2009 /  Martin Nawrath
 * Kunsthochschule fuer Medien Koeln
 * Academy of Media Arts Cologne

 */

#include "avr/pgmspace.h"
#include <UTFT.h>
#include "Wavetables.h"

#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))

UTFT myGLCD(CTE32HR,38,39,40,41);

int ledPin = 13;                 // LED pin 7
int testPin = 7;
int t2Pin = 6;
byte bb;

double dfreq;
// const double refclk=31372.549;  // =16MHz / 510
const double refclk=31376.6;      // measured

// variables used inside interrupt service declared as voilatile
volatile byte icnt;              // var inside interrupt
volatile byte icnt1;             // var inside interrupt
volatile byte c4ms;              // counter incremented all 4ms
volatile unsigned long phaccu;   // pahse accumulator
volatile unsigned long tword_m;  // dds tuning word m

void setup()
{
  // Setup the LCD
  myGLCD.InitLCD();
  
  pinMode(ledPin, OUTPUT);      // sets the digital pin as output
//  Serial.begin(115200);        // connect to the serial port
//  Serial.println("DDS Test");

  pinMode(6, OUTPUT);      // sets the digital pin as output
  pinMode(7, OUTPUT);      // sets the digital pin as output
  // pin10 on ArduinoMEGA
  pinMode(10, OUTPUT);     // pin11= PWM  output / frequency output

  Setup_timer2();

  // disable interrupts to avoid timing distortion
  cbi (TIMSK0,TOIE0);              // disable Timer0 !!! delay() is now not available
  sbi (TIMSK2,TOIE2);              // enable Timer2 Interrupt

  dfreq=1000.0;                    // initial output frequency = 1000.o Hz
  tword_m=pow(2,32)*dfreq/refclk;  // calulate DDS new tuning word 
  
  
}
void loop()
{
  myGLCD.fillScr(VGA_RED);
  
  while(1) {
     if (c4ms > 250) {                 // timer / wait fou a full second
      c4ms=0;
      dfreq=analogRead(0);             // read Poti on analog pin 0 to adjust output frequency from 0..1023 Hz

      cbi (TIMSK2,TOIE2);              // disble Timer2 Interrupt
      tword_m=pow(2,32)*dfreq/refclk;  // calulate DDS new tuning word
      sbi (TIMSK2,TOIE2);              // enable Timer2 Interrupt 

//      Serial.print(dfreq);
//      Serial.print("  ");
//      Serial.println(tword_m);
    }

//   sbi(PORTD,6); // Test / set PORTD,7 high to observe timing with a scope
//   cbi(PORTD,6); // Test /reset PORTD,7 high to observe timing with a scope
  }
  
 }
//******************************************************************
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

//******************************************************************
// Timer2 Interrupt Service at 31372,550 KHz = 32uSec
// this is the timebase REFCLOCK for the DDS generator
// FOUT = (M (REFCLK)) / (2 exp 32)
// runtime : 8 microseconds ( inclusive push and pop)
ISR(TIMER2_OVF_vect) {

//  sbi(PORTD,7);          // Test / set PORTD,7 high to observe timing with a oscope

  phaccu=phaccu+tword_m; // soft DDS, phase accu with 32 bits
  icnt=phaccu >> 24;     // use upper 8 bits for phase accu as frequency information
                         // read value fron ROM sine table and send to PWM DAC
  OCR2A=pgm_read_byte_near(sine256 + icnt);    

  if(icnt1++ == 125) {  // increment variable c4ms all 4 milliseconds
    c4ms++;
    icnt1=0;
   }   

// cbi(PORTD,7);            // reset PORTD,7
}
