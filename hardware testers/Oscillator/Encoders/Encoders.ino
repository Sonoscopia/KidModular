// TEST ENCODERS
#include <Encoder.h>

// Encoders 
#define ENC1L 2
#define ENC1R 3
#define ENC2L 5
#define ENC2R 6
#define ENC3L 7
#define ENC3R 11
#define ENC4L 44
#define ENC4R 46
Encoder enc1(ENC1L, ENC1R);
Encoder enc2(ENC2L, ENC2R);
Encoder enc3(ENC3L, ENC3R);
Encoder enc4(ENC4L, ENC4R);
long oldPositions[4] = {-999, -999, -999, -999};

// Encoders Buttons 
#define ENC1B 18
#define ENC2B 17
#define ENC3B 16
#define ENC4B 15
boolean buttons[4] = {1, 1, 1, 1}; 

void setup() {
  Serial.begin(9600);
  pinMode(ENC1B, INPUT_PULLUP);
  pinMode(ENC2B, INPUT_PULLUP);
  pinMode(ENC3B, INPUT_PULLUP);
  pinMode(ENC4B, INPUT_PULLUP);
}

void loop() {
  // PRINT BUTTONS 
  for (int i = 0; i < 4; i++){
    buttons[i] = digitalRead(ENC1B-i);
    if (buttons[i] < 1){
      Serial.print("button");
      Serial.println(i+1);
    }  
  }
  // PRINT ENCODERS
  for (int i = 0; i < 4; i++){
    long newPosition; 
    switch(i){
      case 0:
        newPosition = enc1.read();
        printEncoderVal(newPosition, i);
      break;
      case 1:
        newPosition = enc2.read();
        printEncoderVal(newPosition, i);
      break;
      case 2:
        newPosition = enc3.read();
        printEncoderVal(newPosition, i);
      break;
      case 3:
        newPosition = enc4.read();
        printEncoderVal(newPosition, i);
      break; 
      
      default:break;
    }  
  }
}

void printEncoderVal(long newP, int i){
  if (newP != oldPositions[i]) {
    oldPositions[i] = newP;
    Serial.print("Encoder");
    Serial.print(i+1);
    Serial.print(" ");
    Serial.println(newP);
  }
}
