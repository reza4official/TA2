#include <ESP8266WiFi.h>

class Actuator
{
private:
    int relayPin;
    int sensorPin;
    int lampOnDuration;
    bool isLampOn;
    long lastTimeOn;
    int checkInterval;
    os_timer_t myTimer; // timer, software interrupt

public:
    Actuator(int sensorPin, int relayPin, int lampOnDuration, int checkInterval);

    void setLamp(bool isOn);
    void setSensor(bool isOn);
    void runOffTimer();
    void setupTimedCheckLamp(ETSTimerFunc *fn);
};