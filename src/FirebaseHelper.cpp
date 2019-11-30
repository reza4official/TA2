// #include <Arduino.h>
// #include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <FirebaseArduino.h>
#include <FirebaseHelper.h>

#define FIREBASE_HOST "light-control-fe6f8.firebaseio.com"
#define FIREBASE_AUTH "VrkBz0o2te1yZFSy7AaoHKMJcbtFLKsd832G0T9y"

FirebaseHelper::FirebaseHelper(const char *ssid, const char *password, std::string sensorId)
{
    FirebaseHelper::ssid = ssid;
    FirebaseHelper::password = password;
    FirebaseHelper::sensorId = sensorId;
    isReconnectingWifi = true;
}

// std::list<std::string> FirebaseHelper::getNeighbor()
// {
//     return nullptr;
// }
// std::list<std::string> FirebaseHelper::getOther()
// {
//     return nullptr;
// }

int FirebaseHelper::getBypassMode()
{
    return 1;
}
bool FirebaseHelper::isRoot()
{
    return false;
}

bool FirebaseHelper::isNeighborLampOn()
{
    return false;
}
bool FirebaseHelper::isSensorOn()
{
    return false;
}

/** get node state from firebase */
// void readNodeData(void *pArg)
// {
//     // sensorActive = Firebase.getBool("nodes/" + nodeId + "/active");
//     // isOverrided = Firebase.getBool("nodes/" + nodeId + "/bypass");
//     return;
// }

void FirebaseHelper::setIsLampOn(bool isLampOn)
{
    return;
}

void FirebaseHelper::setIsSensorOn(bool isSensorOn)
{
    return;
}

void FirebaseHelper::setNeighborSensor()
{
}

void FirebaseHelper::setupTimedCheckData()
{
    os_timer_setfn(&myTimer, readNodeData, NULL);         // set interrupt callback
    os_timer_arm(&myTimer, 10 /*s*/ * 1000 /*ms*/, true); // setup timer, sample every 5 ms, 200Hz
}

void FirebaseHelper::firebaseConnect()
{
    Serial.print("connecting to WIFI");
    while (WiFi.status() != WL_CONNECTED)
    {
        WiFi.begin(FirebaseHelper::ssid, FirebaseHelper::password); // Begin WiFi connection
        Serial.print(".");
        delay(500);
    }

    Serial.println("connecting to firebase");
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Serial.println("connected to firebase");
    isReconnectingWifi = false;
}

void FirebaseHelper::maintainConnection()
{
    if (WiFi.status() != WL_CONNECTED || Firebase.failed())
    {
        Serial.println("Disconnected: Re-Try on 3s");
        isReconnectingWifi = true;
        firebaseConnect();
        delay(3 /*second*/ * 1000 /*ms*/); // reconnecting after waiting 3 s
    }
    else
    {
        Serial.println("Still Connected...");
    }
}