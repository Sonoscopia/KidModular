// Let's say we want to send two nibbles in one byte for 
// efficiency purposes

byte menu = 2;
byte paramNum = 1;
int paramAddr = 0x00; 

void setup() {
  Serial.begin(9600);
            //lowest + highest 4bits
  paramAddr = menu   | (paramNum << 4);

  Serial.print("menu: ");
  Serial.println(paramAddr & 0x0F); // access lowest nibble
  Serial.print("paramNum: ");
  Serial.println(paramAddr>>4); // access highest nibble
}

void loop() {
}
