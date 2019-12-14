#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <list>

// typedef void (*voidFuncPtr)(void);

class Reader
{
private:
    int sensorPin;
    int SensorFetchInterval;
    os_timer_t myTimer; // timer, software interrupt

public:
    Reader(int sensorPin);
    Reader(int SensorFetchInterval);

    void setSensor(bool isOn);
    void setOnMotionDetected(ETSTimerFunc *fn);
};