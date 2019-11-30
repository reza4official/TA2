#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <FirebaseArduino.h>
#include <FirebaseHelper.h>

#define FIREBASE_HOST "light-control-fe6f8.firebaseio.com"
#define FIREBASE_AUTH "VrkBz0o2te1yZFSy7AaoHKMJcbtFLKsd832G0T9y"
const String ROOT = "configuration/";

FirebaseHelper::FirebaseHelper(const String ssid, const String password, String sensorId, int firebaseFetchInterval)
{
    FirebaseHelper::ssid = ssid;
    FirebaseHelper::password = password;
    FirebaseHelper::sensorId = sensorId;
    FirebaseHelper::firebaseFetchInterval = firebaseFetchInterval;
    isReconnectingWifi = true;
}

void FirebaseHelper::fetchNeighborKey()
{
    for (size_t i = 0; i < neighborsCount; i++)
    {
        /* code */
    }
}
void FirebaseHelper::fetchOtherKey()
{
    for (size_t i = 0; i < otherCount; i++)
    {
        /* code */
    }
}

bool FirebaseHelper::queryNeighborLamp()
{
    return false;
}

/** get node state from firebase */
void FirebaseHelper::fetchNodeData()
{
    int neighborsCount = Firebase.getInt(ROOT + sensorId + "/neighbors_count");
    fetchNeighborKey();
    int otherCount = Firebase.getInt(ROOT + sensorId + "/others_count");
    fetchOtherKey();

    int bypassMode = Firebase.getInt(ROOT + sensorId + "/bypassMode");
    bool isRoot = Firebase.getBool(ROOT + sensorId + "/isRoot");
    bool isSensorOn = Firebase.getBool(ROOT + sensorId + "/isSensorOn");
    bool isLampOn = Firebase.getBool(ROOT + sensorId + "/isLampOn");
    bool isNeighborLampOn = queryNeighborLamp();
}

void FirebaseHelper::setIsLampOn(bool isLampOn)
{
    Firebase.setBool(ROOT + sensorId + "/isLampOn", isLampOn);
}

void FirebaseHelper::setIsSensorOn(bool isSensorOn)
{
    Firebase.setBool(ROOT + sensorId + "/isSensorOn", isSensorOn);
}

void FirebaseHelper::setNeighborSensors()
{
    return;
}

void FirebaseHelper::setupTimedCheckData(ETSTimerFunc *fn)
{
    os_timer_setfn(&myTimer, fn, NULL);                                      // set interrupt callback
    os_timer_arm(&myTimer, firebaseFetchInterval /*s*/ * 1000 /*ms*/, true); // setup timer, sample every 5s
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