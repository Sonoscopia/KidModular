/*
 * Example using the Rotary library, dumping integers to the serial
 * port. The integers increment or decrement depending on the direction
 * of rotation.
 *
 * This example uses polling rather than interrupts.
 */

#include <Rotary.h>
#include <TimerOne.h>
#include <UTFT.h> 

// Rotary encoder is wired with the common to ground and the two
// outputs to pins 5 and 6.
#define ENC1L 2 // Encoders (rotary)
#define ENC1R 3
#define ENC2L 4
#define ENC2R 5
#define ENC3L 6
#define ENC3R 7
#define ENC4L 8
#define ENC4R 9

Rotary rotary1 = Rotary(ENC1L, ENC1R);
Rotary rotary2 = Rotary(ENC2L, ENC2R);
Rotary rotary3 = Rotary(ENC3L, ENC3R);
Rotary rotary4 = Rotary(ENC4L, ENC4R);

// Counter that will be incremented or decremented by rotation.
int counter[4] = {0, 0, 0, 0};
byte result[4] = {0, 0, 0, 0};

UTFT myGLCD(CTE32HR,38,39,40,41);

void setup() {
  Serial.begin(9600);

  Timer1.initialize(1000); // set a timer of length 1000 microseconds (or 0.001 sec - or 1000Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
  Timer1.attachInterrupt( encoderISR ); // attach the service routine here
  
  myGLCD.InitLCD();
  myGLCD.clrScr();
}

void loop() {
  myGLCD.setColor(random(255), random(255), random(255));
  myGLCD.fillRect(120, 120, 240, 240);
  //delay(45);
}

void encoderISR(){
  unsigned char result = rotary1.process();
  if (result == DIR_CW) {
    counter[0]++;
    Serial.print("e1: ");
    Serial.println(counter[0]);
  } else if (result == DIR_CCW) {
    counter[0]--;
    Serial.print("e1: ");
    Serial.println(counter[0]);
  }
  
  result = rotary2.process();
  if (result == DIR_CW) {
    counter[1]++;
    Serial.print("e2: ");
    Serial.println(counter[1]);
  } else if (result == DIR_CCW) {
    counter[1]--;
    Serial.print("e2: ");
    Serial.println(counter[1]);
  }
  
  result = rotary3.process();
  if (result == DIR_CW) {
    counter[2]++;
    Serial.print("e3: ");
    Serial.println(counter[2]);
  } else if (result == DIR_CCW) {
    counter[2]--;
    Serial.print("e3: ");
    Serial.println(counter[2]);
  }
  result = rotary4.process();
  if (result == DIR_CW) {
    counter[3]++;
    Serial.print("e4: ");
    Serial.println(counter[3]);
  } else if (result == DIR_CCW) {
    counter[3]--;
    Serial.print("e4: ");
    Serial.println(counter[3]);
  }
}


