#include <Arduino.h>

/* KID MODULAR - DistCV v0.2 
 *  a project by Sonoscopia
 *  developed by Tiago Ângelo (aka p1nh0) - 15.06.2017
 * 
 */

#include "NewPing.h"
#include "TimerOne.h"

void echoCheck();
byte distToByte(byte distance);
byte distanceToCV(byte b);
void controlISR();
void average(int* num, byte samp);

#define TRIGGER_PIN  12 
#define ECHO_PIN     11 
#define MAX_DISTANCE 40 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define POT1 0
#define POT2 1
#define CVOUT 9
#define GREEN 6 

const boolean _DEBUGPOT = false;
const boolean _DEBUGSONAR = true;
const boolean _DEBUGCV = true;
/*byte samples = 10;
byte iter = 0; 
int distSample[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};*/
int dist;
//float distAverage = 0;
byte potL, potR, cv;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
unsigned int pingSpeed = 50; // How frequently are we going to send out a ping (in milliseconds). 50ms = 20 times a second.
unsigned long pingTimer; // Holds the next ping time.

void setup() {
  if(_DEBUGPOT==true || _DEBUGSONAR==true || _DEBUGCV==true) Serial.begin(115200);
  pinMode(CVOUT, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pingTimer = millis(); // Start now.
  Timer1.initialize(2000);
  Timer1.attachInterrupt(controlISR);
}
 
void loop() {
	// SONAR
	if (millis() >= pingTimer) { // pingSpeed milliseconds since last ping, do another ping.
		pingTimer += pingSpeed; // Set the next ping time.
		sonar.ping_timer(echoCheck, MAX_DISTANCE); // Send out the ping, calls "echoCheck" function every 24uS where you can check the ping status.
	}		
	
  /*if(cv > 0) analogWrite(GREEN, map(cv, 0, 255, 113, 153));
  else analogWrite(GREEN, 0);*/
  
  if (_DEBUGSONAR == true)
  {
	  Serial.print("Ping: ");
	  Serial.print(dist); // Ping returned, uS result in ping_result, convert to cm with US_ROUNDTRIP_CM.
	  Serial.println("cm");
  }
  if (_DEBUGPOT==true)
  {
	  Serial.print("min: ");
	  Serial.print(potL);
	  Serial.print("    max: ");
	  Serial.println(potR);
  }
  if(_DEBUGCV==true){
	  Serial.print("CV: ");
	  Serial.println(cv);
  }
  
  if(_DEBUGPOT==true || _DEBUGSONAR==true || _DEBUGCV==true) delay(50);
}

void echoCheck() { // Timer2 interrupt calls this function every 24uS where you can check the ping status.
	if (sonar.check_timer()) {
		dist = sonar.ping_result / US_ROUNDTRIP_CM - 5;
		if(dist<0) dist = 0;
		/*
		dist[iter] = sonar.ping_result / US_ROUNDTRIP_CM - 5;
		if(dist[iter]<0) dist[iter] = 0;
		distAverage = 0; 
		for(int i = 0; i < samples; i++){
			distAverage += dist[i];
		}
		distAverage /= samples;
		
		if(iter<samples) iter++;
		else iter = 0;*/
	}
}

void average(int* num, byte samples){
	
}

byte distToByte(byte distance){
	return distance*(255/MAX_DISTANCE);
} 

byte distanceToCV(byte d){		
	byte dbyte = distToByte(d);
	if( (dbyte >= potL && dbyte <= potR) || (dbyte <= potL && dbyte >= potR) ) { // check if distance is within bounds
		return map(dbyte, 0, 255, potL, potR);
		//return dbyte;
	}
	else{
		return 0; 
	}
}

void controlISR(){
	// running average
	/*distSample[iter] = dist;
	dist = 0;
	for(int i = 0; i < samples; i++){
		dist += distSample[i];
	}
	dist /= samples;
		
	if(iter<samples) iter++;
	else iter = 0;*/
	
	// POTENTIOMETERS
	potL = analogRead(POT1)>>2;
	potR = analogRead(POT2)>>2;
	
	//cv = distanceToCV(distAverage);
	cv = distanceToCV(dist);
	
	analogWrite(CVOUT, cv);
	analogWrite(GREEN, cv);
}