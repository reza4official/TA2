#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <list>

class FirebaseHelper
{
private:
    const char *ssid;
    const char *password;
    std::string sensorId;
    int firebaseFetchInterval;
    std::list<std::string> neighbors;
    std::list<std::string> others;
    bool isReconnectingWifi;
    os_timer_t myTimer; // timer, software interrupt

    std::list<std::string> getNeighbor();
    std::list<std::string> getOther();
    void queryNeighborLamp(); // read neighbor status then update `isNeighborLampOn` field

public:
    FirebaseHelper(const char *ssid, const char *password, std::string sensorId, int firebaseFetchInterval);

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

    void fetchNodeData();                // readData from server
    void setIsLampOn(bool isLampOn);     // set status of current
    void setIsSensorOn(bool isSensorOn); // to override value
    void setNeighborSensors();           // set other sensor status

    void firebaseConnect();
    void setupTimedCheckData(ETSTimerFunc *fn);
    void maintainConnection(); // run this funtion on loop
};