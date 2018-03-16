#ifndef PARAMETERS_H
#define PARAMETER_H

struct params_t{
  byte selectedMenu;
  byte osc_wave;
  float osc_freq;
  byte lfo_wave;
  float lfo_freq;
  };

//int adsr[4] = {0, 0, 0, 0}; // {atk, dcy, sus, rel} parameters
//byte ampEnv; // envelope amount
//int filter[3] = {0, 0, 0}; // {mode, freq, Q}
//byte filterEnv; // filter envelope amount
//int fx[3] = {0, 0, 0}; // {type, depth, parameter}  

#endif
