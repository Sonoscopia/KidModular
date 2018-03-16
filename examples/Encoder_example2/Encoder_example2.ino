// Encoder example 2
// this code makes fines adjustments when pressing the button and moving the knob
// and larger adjustments when moving the knob without pressing the button
#include <Encoder.h>
#define ENC1L 2
#define ENC1R 3
#define ENC1B 18
Encoder enc1(ENC1L, ENC1R);
boolean button[] = {1, 1}; // {new, old}
long pos[] = {0, 0, -999}; // {new, old}
float val = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ENC1B, INPUT_PULLUP);
}

void loop() {
  button[0] = digitalRead(ENC1B);
  if (button[0]== 0 && button[0] !=button[1]){
    Serial.println("button");
    delay(50);
  }
  button[1] = button[0];

  pos[0] = enc1.read();
  if(!button[0]){ //if button is pressed
    if(pos[0]>pos[1]){
      val++;
      pos[1] = pos[0];
      Serial.println(val);
    }
    if(pos[0]<pos[1]){
      val--;
      pos[1] = pos[0];
      Serial.println(val);  
    } 
  }
  else{
    if(pos[0]>pos[1]){
      val+=2.5;
      pos[1] = pos[0];
      Serial.println(val);
    }
    if(pos[0]<pos[1]){
      val-=2.5;
      pos[1] = pos[0];
      Serial.println(val);
    } 
  }
}
