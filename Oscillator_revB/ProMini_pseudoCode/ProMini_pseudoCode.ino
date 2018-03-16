// PseudoCode (Arduino Pro Mini)

Oscil osc;
byte oscWave;
int oscFreq; 
Oscil lfo;
byte lfoWave; 
int lfoFreq;
ADSR envelope;  
int adsr[] = {0, 0, 0, 0}; // {atk, dcy, sus, rel} parameters
byte ampEnv; // envelope amount
StateVariable svf; 
Filter filter[] = {0, 0, 0}; // {mode, freq, Q}
byte filterEnv; // filter envelope amount
FX fx = {0, 0, 0}; // {type, depth, parameter}
char output; 

setup(){
  setupMozzi(); 
  startI2C();
}

updateControl(){
  readI2C(); // read I2C from slave and update controls  
  setLFO(); // set LFO Wave and Freq
  setOscWave(); // set oscillator wave
  setEnvelope(); // set envelope parameters 
  setFilter();
  setFX(); 
}

updateAudio(){
  updateOscFreq();
  updateFilter();
  updateOutput(); 
  return output; 
}


