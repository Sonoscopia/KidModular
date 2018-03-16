// Wire Slave Sender
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Sends data as an I2C/TWI slave device
// Refer to the "Wire Master Reader" example for use with this

// Created 29 March 2006

// This example code is in the public domain.
//mildly changed by p1nh0

#include <Wire.h>
byte val = 127;
void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  //Wire.onRequest(requestEvent); // register event
}

void loop() {
  val = random(255);
  Wire.onRequest(requestEvent); // register event
  delay(250);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  Wire.write(val); // respond with message of 6 bytes
  // as expected by master
}
