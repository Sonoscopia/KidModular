struct RGB{
  byte r;
  byte g;
  byte b; 
};

RGB color = {255, 127, 63}; 

void setup() {
  Serial.begin(9600);
  printColor(&color);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void printColor(struct RGB *s){
  Serial.println(s->r);
  Serial.println(s->g);
  Serial.println(s->b);
}
