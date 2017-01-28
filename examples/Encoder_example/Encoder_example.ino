/* Encoder Library - Basic Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */

#include <Encoder.h>
#define BUTTONPIN 4
// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEnc(2, 3);
//   avoid using pins with LEDs attached

byte toggle = 0; 
byte button, _button;
int encVal, _encVal = -1;
int val = 50;

void setup() {
  Serial.begin(9600);
  Serial.println("Basic Encoder Test:");
  pinMode(BUTTONPIN, INPUT_PULLUP);
}

void loop() {
  button = digitalRead(BUTTONPIN);
  if(button < 1 && button != _button){
    toggle = !toggle;
    Serial.println(toggle);
  } 
  _button = button;
  
  encVal = myEnc.read() >> 2;
  if (encVal > _encVal){ 
    val++;
    if(val > 99) val = 0;
    Serial.println(val);
  }
  if(encVal < _encVal){
    val--;
    if(val < 0) val = 99;
    Serial.println(val);
  }
  _encVal = encVal;
  
}
