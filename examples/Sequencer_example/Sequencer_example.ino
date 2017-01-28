#define V 32
#define LED 5
#define POT 0 
#define GATEOUT 13

byte bpm = 120;
int stepTime; 
byte curStep = 0;
int playhead = 0;
byte dur[] = {50, 50, 50, 50};
byte numSteps = 4;

void setup(){
  pinMode(LED, OUTPUT);
  pinMode(13, OUTPUT);
  stepTime = 60000.f / bpm;
}

void loop(){
  runSequence();
  delayMicroseconds(750); // in a genuine Arduino with a 16MHz crystal oscillator the delay should be 1ms
  // but on fake Arduinos with 12MHz oscillator the delay should be 0.75ms to have an accurrate clock running once every millisecond
}

void runSequence(){
  playhead++;
  if(playhead > stepTime){
    playhead = 0;
    curStep++;
    if(curStep == numSteps) {curStep = 0;}
  }
  // Gate CV output 
  if(playhead < stepTime * dur[curStep] / 100.f){
    digitalWrite(GATEOUT, HIGH);
    analogWrite(curStep+LED, 255-V);
  } 
  else{
    digitalWrite(GATEOUT, LOW);
    analogWrite(curStep+LED, 255-LOW);
 }
 
 dur[0] = analogRead(0) / 1024.f * 100;
 bpm = (analogRead(8) >> 3) + 30; // from 30 to 157 bpm
 stepTime = 60000.f / bpm;
}
