// TEST MENU BUTTON 
#define MENUPIN 14

void setup() {
  Serial.begin(9600);
  pinMode(MENUPIN, INPUT_PULLUP);
}

void loop() {
  Serial.println(digitalRead(MENUPIN));
}
