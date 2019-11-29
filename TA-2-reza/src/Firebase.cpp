#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <FirebaseArduino.h>
std::string nodeId = "light-001";

#define FIREBASE_HOST "light-control-fe6f8.firebaseio.com"
#define FIREBASE_AUTH "VrkBz0o2te1yZFSy7AaoHKMJcbtFLKsd832G0T9y"
#define WIFI_SSID "Razer WiFi"
#define WIFI_PASSWORD "01454765"

/** established connection to firebase */
void firebaseConnect()
{
    // Serial.println("connecting to firebase");
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

/** get node state from firebase */
void readNodeData()
{
    // sensorActive = Firebase.getBool("nodes/" + nodeId + "/active");
    // isOverrided = Firebase.getBool("nodes/" + nodeId + "/bypass");
}