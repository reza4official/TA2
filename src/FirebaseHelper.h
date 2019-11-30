#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <list>

#define MAXIMUM_SENSOR_COUNT 10

class FirebaseHelper
{
private:
    String ssid;
    String password;
    String sensorId;
    int firebaseFetchInterval;
    String neighbors[MAXIMUM_SENSOR_COUNT];
    String others[MAXIMUM_SENSOR_COUNT];
    int neighborsCount = 0;
    int otherCount = 0;
    bool isReconnectingWifi;
    os_timer_t myTimer; // timer, software interrupt

    void fetchNeighborKey();
    void fetchOtherKey();
    bool queryNeighborLamp(); // read neighbor status then update `isNeighborLampOn` field

public:
    FirebaseHelper(String ssid, String password, String sensorId, int firebaseFetchInterval);

    /**
     * Mode: 
     * -1 = Auto
     * 0 = Off
     * 1 = On
     */
    int bypassMode;
    bool isRoot;           // is current sensor a root (sensor is always on)
    bool isNeighborLampOn; // is other neighbor lamp turned on
    bool isSensorOn;       // is current sensor should be On
    bool isLampOn;         // is current lamp is still on

    void fetchNodeData();                // readData from server
    void setIsLampOn(bool isLampOn);     // set status of current
    void setIsSensorOn(bool isSensorOn); // to override value
    void setNeighborSensors();           // set other sensor status

    void setupTimedCheckData(ETSTimerFunc *fn);
    void firebaseConnect();
    void maintainConnection(); // run this funtion on loop
};