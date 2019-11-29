#include <Arduino.h>
#include <Reader.h>
#include <FirebaseHelper.h>
// #include <Actuator.h>

/** CONFIG VARIABLE*/
const char *ssid = "Razer WiFi";
const char *password = "01454765";
const int baudRate = 9600;
const char *sensorId = "sensor1";
const int sensorPin = 13;
const int relayPin = 2;
const int lampOnDuration = 5; // in minute

FirebaseHelper firebaseHelper(ssid, password, sensorId);
Reader reader(sensorPin);
// Actuator actuator(sensorPin, relayPin, lampOnDuration);

ICACHE_RAM_ATTR void onMotionDetected()
{
  Serial.println("-----------");
  Serial.println("terjadi pergerakan di " + String(sensorId));
  firebaseHelper.setNeighborSensor();
  Serial.println("-----------");
}

void onDataChange()
{
}

/** initiate prerequisite */
void setup()
{
  Serial.begin(baudRate);
  Serial.println("-----------");
  Serial.println("after setup");
  firebaseHelper.firebaseConnect();
  reader.setOnMotionDetected(onMotionDetected);
  // firebase.setOnDataChange();
  // firebase.setupConnection(); // setup WiFi connection
  // reader.setupSensor();
}

/** main loops */
void loop()
{
  // firebase.maintainConnection();
  delay(1000);
}