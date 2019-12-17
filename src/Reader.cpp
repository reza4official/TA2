#include <Arduino.h>
#include <Reader.h>
#include <ESP8266WiFi.h>

Reader::Reader(int sensorPin, int SensorFetchInterval)
{
    Reader::sensorPin = sensorPin;
    pinMode(sensorPin, INPUT_PULLUP);
    Reader::SensorFetchInterval = SensorFetchInterval;
}

void Reader::setSensor(bool isOn)
{
    digitalWrite(sensorPin, isOn ? HIGH : LOW);
}

void Reader::setupTimedCheckSensor(ETSTimerFunc *fn)
{
    os_timer_setfn(&myTimer, fn, NULL);                                      // set interrupt callback
    os_timer_arm(&myTimer, SensorFetchInterval /*s*/ * 1000 /*ms*/, true); // setup timer, sample every 5s
}

// void Reader::setOnMotionDetected()
// {

// }
// void Reader::setOnMotionDetected(voidFuncPtr onMotionDetected)
// {
//     attachInterrupt(digitalPinToInterrupt(sensorPin), onMotionDetected, RISING);
// }