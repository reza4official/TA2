#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <FirebaseArduino.h>
#include <FirebaseHelper.h>

#define FIREBASE_HOST "light-control-fe6f8.firebaseio.com"
#define FIREBASE_AUTH "VrkBz0o2te1yZFSy7AaoHKMJcbtFLKsd832G0T9y"

void FirebaseHelper::firebaseConnect()
{
    WiFi.begin(FirebaseHelper::ssid, FirebaseHelper::password); // Begin WiFi connection
    Serial.print("connecting");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }

    Serial.println("connecting to firebase");
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Serial.println("connected to firebase");
}

FirebaseHelper::FirebaseHelper(const char *ssid, const char *password, std::string sensorId)
{
    FirebaseHelper::ssid = ssid;
    FirebaseHelper::password = password;
    FirebaseHelper::sensorId = sensorId;
}

std::list<std::string> FirebaseHelper::getNeighbor()
{
}
std::list<std::string> FirebaseHelper::getOther()
{
}

int FirebaseHelper::getBypassMode()
{
}
bool FirebaseHelper::isRoot()
{
}
bool FirebaseHelper::isNeighborLampOn()
{
}
bool FirebaseHelper::isSensorOn()
{
}

/** get node state from firebase */
void readNodeData()
{
    // sensorActive = Firebase.getBool("nodes/" + nodeId + "/active");
    // isOverrided = Firebase.getBool("nodes/" + nodeId + "/bypass");
}

void FirebaseHelper::setIsLampOn(bool isLampOn)
{
}

void FirebaseHelper::setIsSensorOn(bool isSensorOn)
{
}

void FirebaseHelper::setNeighborSensor()
{
}