#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "light-control-fe6f8.firebaseio.com"
#define FIREBASE_AUTH "VrkBz0o2te1yZFSy7AaoHKMJcbtFLKsd832G0T9y"
#define WIFI_SSID "Quiznos Indonesia"
#define WIFI_PASSWORD "quiznoscafe"

/** constant */
String nodeId = "light-001";
int relayPin = 2; // pin for the RELAY
int pirPin = 13;  // input pin (for PIR sensor)
int baud = 9600;  // input baud

/** declare inputs */
bool motionDetected;
bool sensorActive;
bool isOverrided;

/** log message to console */
void log(String message)
{
  Serial.println("-- " + message + " --");
}

/** established connection to firebase */
void connect()
{
  log("connecting to firebase");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

/** maintain firebase connection */
void maintainConnection()
{
  if (Firebase.failed())
  {
    log('firebase connection stalled');
    connect();
    return;
  }
}

/** get node state from firebase */
void readNodeData()
{
  sensorActive = Firebase.getBool("nodes/" + nodeId + "/active");
  isOverrided = Firebase.getBool("nodes/" + nodeId + "/bypass");
}

/** get sensor data */
void readSensorData()
{
  int in = digitalRead(pirPin); // read from motion sensor
  motionDetected = in == 1 ? true : false;
  log(motionDetected ? "motion detected" : "motion not detected");
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

  Serial.begin(baud);
  Serial.print("connecting to baud " + baud);

  /** wait until connected to wifi */
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("...");
    delay(500);
  }
  Serial.print("connection established");

  /** start connection to firebase instance */
  connect()
}

/** main loops */
void loop()
{
  /** check firebase connection */
  maintainConnection();

  /** get node data from firebase */
  readNodeData();
  readSensorData();

  /** switch light on/off */
  toggleSwitch(isOverrided || (sensorActive && motionDetected));

  delay(100);
}