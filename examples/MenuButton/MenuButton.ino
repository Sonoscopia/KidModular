// TEST MENU BUTTON 
#define MENUPIN 14
boolean button[] = {1, 1}; // {new, old} 

void setup() {
  Serial.begin(9600);
  pinMode(MENUPIN, INPUT_PULLUP);
}

void loop() {
  button[0] = digitalRead(MENUPIN); 
  if(button[0]== 0 && button[0] !=button[1]){
    Serial.println("button pressed");
    delay(50);   
  }
  button[1] = button[0];
}
