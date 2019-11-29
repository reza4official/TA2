#include <Arduino.h>
#include <Reader.h>
#include <Firebase.h>
// #include <Actuator.h>

/** CONFIG VARIABLE*/
const int baudRate = 9600;
const char *sensorId = "sensor1";
const int sensorPin = 13;
const int relayPin = 2;
const int lampOnDuration = 5; // in minute

Firebase firebase(sensorId);
Reader reader(sensorPin);
// Actuator actuator(sensorPin, relayPin, lampOnDuration);

ICACHE_RAM_ATTR void onMotionDetected()
{
  Serial.println("-----------");
  Serial.println("terjadi pergerakan di " + String(sensorId));
  firebase.setNeighborSensor();
  Serial.println("-----------");
}

void onDataChange() {

}

/** initiate prerequisite */
void setup()
{
  Serial.begin(baudRate);
  Serial.println("-----------");
  Serial.println("after setup");
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