#include <Arduino.h>
#include <Reader.h>
#include <Firebase.h>
#include <Actuator.h>

#define sensorId "sensor1"
#define sensorPin 13
#define relayPin 2

Firebase firebase(sensorId);
Reader reader(sensorPin);
Actuator actuator(sensorPin, relayPin);

/** constant */
int baudRate = 9600; // input baud rate hz

/** initiate prerequisite */
void setup()
{
  Serial.begin(baudRate);
  // firebase.setupConnection(); // setup WiFi connection
  // reader.setupSensor();
}

/** main loops */
void loop()
{
  firebase.maintainConnection();
}