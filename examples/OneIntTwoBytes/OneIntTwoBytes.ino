// convert int to two bytes
//int16_t integer = 0B0000111100001010;
uint16_t integer = 48653;
byte byte1; // lower
byte byte2; // upper
uint16_t reconstruction; 

void setup() {
  Serial.begin(9600);
  Serial.print("integer val: ");
  Serial.println(integer);

  byte1 = integer & 0xFF;
  Serial.print("lower byte: ");
  Serial.println(byte1);

  byte2 = integer >> 8; 
  Serial.print("upper byte: ");
  Serial.println(byte2);

  reconstruction = byte1 | (byte2 << 8);
  Serial.print("reconstruction: ");
  Serial.println(reconstruction);
}

void loop() {

}
