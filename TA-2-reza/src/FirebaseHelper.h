#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
// #include <FirebaseArduino.h>
#include <list>

class FirebaseHelper
{
private:
    const char *ssid;
    const char *password;
    std::string sensorId;
    std::list<std::string> neighbors;
    std::list<std::string> others;
    bool isReconnectingWifi;
    os_timer_t myTimer; // timer, software interrupt

    /**
     * Mode: 
     * -1 = Auto
     * 0 = Off
     * 1 = On
     */
    int getBypassMode();
    bool isRoot();           // is current sensor a root (sensor is always on)
    bool isNeighborLampOn(); // is other neighbor lamp turned on
    bool isSensorOn();       // is current sensor should be On
    std::list<std::string> getNeighbor();
    std::list<std::string> getOther();

public:
    FirebaseHelper(const char *ssid, const char *password, std::string sensorId);

    void setIsLampOn(bool isLampOn);     // set status of current
    void setIsSensorOn(bool isSensorOn); // to override value
    void setNeighborSensor();            // set other sensor status

    void firebaseConnect();
    void setupTimedCheckData();
    void maintainConnection(); // run this funtion on loop
};