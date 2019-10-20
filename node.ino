#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "light-control-fe6f8.firebaseio.com"
#define FIREBASE_AUTH "VrkBz0o2te1yZFSy7AaoHKMJcbtFLKsd832G0T9y"
#define WIFI_SSID "Razer WiFi"
#define WIFI_PASSWORD "01454765"

/** constant */
const string nodeId = 'light-001';
const int relayPin = 2; // pin for the RELAY
const int pirPin = 13;  // input pin (for PIR sensor)
const int port = 9600;  // input port

/** declare inputs */
bool motionDetected;
bool sensorActive;
bool isOverrided;

/** log message to console */
void log(string message)
{
  Serial.println("-- " + message + " --");
}

/** established connection to firebase */
void firebaseConnect()
{
  log("connecting to firebase");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

/** get node state from firebase */
void readNodeData()
{
  sensorActive = Firebase.getBool("nodes/" + nodeId + "/active");
  isOverrided = Firebase.getBool("nodes/" + nodeId + "/override");
}

/** get sensor data */
void readSensorData()
{
  int in = digitalRead(pirPin); // read from motion sensor
  motionDetected = in == 1 ? true : false;
  log(motionDetected ? 'motion detected' : 'no motion detected')
}

/** switch light */
void toggleSwitch(bool isOn)
{
  digitalWrite(relayPin, isOn ? HIGH : LOW);
}

/** initiate prerequisite */
void setup()
{
  /** set I/O */
  pinMode(relayPin, OUTPUT); // declare relayPin as output
  pinMode(pirPin, INPUT);    // declare pirPin as input
  digitalWrite(relayPin, 0);

  Serial.begin(port);
  Serial.print("connecting to port " + port);

  /** wait until connected to wifi */
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("...");
    delay(500);
  }
  Serial.print("connection established");

  /** start connection to firebase instance */
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

/** main loops */
void loop()
{
  /** check firebase connection */
  if (Firebase.failed())
  {
    log('firebase connection stalled');
    firebaseConnect();
    return;
  }

  /** get node data from firebase */
  readNodeData();
  readSensorData();

  toggleSwitch(isOverrided || (sensorActive && motionDetected));

  delay(1000);
}