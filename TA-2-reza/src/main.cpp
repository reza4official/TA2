#include <Arduino.h>
#include <Reader.h>
#include <Firebase.h>
#include <Actuator.h>

Firebase firebase;
Reader reader;
Actuator actuator;

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