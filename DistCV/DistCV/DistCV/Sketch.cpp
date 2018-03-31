#include <Arduino.h>

/* KID MODULAR - DistCV v0.2 
 *  a project by Sonoscopia
 *  developed by Tiago Ângelo (aka p1nh0) - 15.06.2017
 * 
 */

#include "NewPing.h"

void echoCheck();
byte distToByte(byte distance);
//byte distanceToCV(byte b);
void control();

#define TRIGGER_PIN  8
#define ECHO_PIN     7 
#define MAX_DISTANCE 30 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define POT1 0
#define POT2 1
#define CVOUT 9
#define GREEN 10 

#define _DEBUGPOT 0
#define _DEBUGSONAR 0
#define _DEBUGCV 0

int dist;
byte potL, potR, cv;

float sumCV; 
byte samples = 5;
byte sampled[] = {0, 0, 0, 0, 0}; 
byte iter = 0; 
byte avrCV; 

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
unsigned int pingSpeed = 50; // How frequently are we going to send out a ping (in milliseconds). 50ms = 20 times a second.
unsigned long pingTimer; // Holds the next ping time.

void setup() {
  if(_DEBUGPOT==true || _DEBUGSONAR==true || _DEBUGCV==true) Serial.begin(115200);
  pinMode(CVOUT, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pingTimer = millis(); // Start now.
}
 
void loop() {
	// SONAR
	if (millis() >= pingTimer) { // pingSpeed milliseconds since last ping, do another ping.
		pingTimer += pingSpeed; // Set the next ping time.
		sonar.ping_timer(echoCheck, MAX_DISTANCE); // Send out the ping, calls "echoCheck" function every 24uS where you can check the ping status.
	}		
	
  
  if (_DEBUGSONAR)
  {
	  Serial.print("Ping: ");
	  Serial.print(dist); // Ping returned, uS result in ping_result, convert to cm with US_ROUNDTRIP_CM.
	  Serial.println("cm");
  }
  if (_DEBUGPOT)
  {
	  Serial.print("min: ");
	  Serial.print(potL);
	  Serial.print("    max: ");
	  Serial.println(potR);
  }
  if(_DEBUGCV){
	  Serial.print("CV: ");
	  Serial.println(avrCV);
  }
  
  control();
   
  delay(50);
}

void echoCheck() { // Timer2 interrupt calls this function every 24uS where you can check the ping status.
	if (sonar.check_timer()) {
		dist = sonar.ping_result / US_ROUNDTRIP_CM - 5;
		if(dist<0) dist = 0;
	}
}

byte distToByte(byte distance){
	return distance*(255/MAX_DISTANCE);
} 

/*byte distanceToCV(byte d){		
	byte dbyte = distToByte(d);
	if( (dbyte >= potL && dbyte <= potR) || (dbyte <= potL && dbyte >= potR) ) { // check if distance is within bounds
		return map(dbyte, 0, 255, potL, potR);
		//return dbyte;
	}
	else{
		return 0; 
	}
}*/

void control(){
  
	// POTENTIOMETERS
	potL = analogRead(POT1)>>2;
	potR = analogRead(POT2)>>2;
	
	//cv = distanceToCV(distAverage);
	//cv = distanceToCV(dist);
	byte distByte = distToByte(dist);
	if(distByte > 0) cv = map(distByte, 0, 255, potL, potR);
	else cv = 0;
	sampled[iter] = cv;
	sumCV = 0;
	for(int i = 0; i < samples; i++){
		sumCV += sampled[i];
	}   
	avrCV = sumCV/samples;
	iter++;
	if(iter > samples) iter = 0; 
  
	analogWrite(CVOUT, avrCV);
	analogWrite(GREEN, avrCV);
}