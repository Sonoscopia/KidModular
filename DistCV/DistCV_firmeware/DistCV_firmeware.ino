/* KID MODULAR - DistCV v0.1 
 *  a project by Sonoscopia
 *  developed by Tiago Ângelo (aka p1nh0) - 15.06.2017
 * 
 */

#include <NewPing.h>

#define TRIGGER_PIN  12 
#define ECHO_PIN     11 
#define MAX_DISTANCE 100 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define POT1 0
#define POT2 1
#define CVOUT 9
#define RED 5
#define GREEN 6 

byte mMin, mMax, dist, cv; 

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  pinMode(CVOUT, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
}

void loop() {
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Ping: ");
  dist = sonar.ping_cm();
  Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");

  // read pots
  mMin = analogRead(POT1);
  mMax = analogRead(POT2);

  cv = map(dist, 0, MAX_DISTANCE, mMin, mMax);
  analogWrite(CVOUT, cv);
}
