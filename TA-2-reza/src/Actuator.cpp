#include <Arduino.h>
#include <Actuator.h>

Actuator::Actuator(int sensorPin, int relayPin, int lampOnDuration)
{
  Actuator::sensorPin = sensorPin;
  Actuator::relayPin = relayPin;
  Actuator::lampOnDuration = lampOnDuration;
}

void Actuator::setLamp(bool isOn)
{
  Actuator::lastTimeOn = millis();
  Actuator::isLampOn = isOn;
  digitalWrite(relayPin, isOn ? HIGH : LOW);
}

void Actuator::runTimerLoop()
{
  long passedTime = (millis() - lastTimeOn) / (60 /*second*/ * 1000 /*miliis*/);
  if (passedTime >= lampOnDuration)
  {
    setLamp(false);
  }
}

void Actuator::setSensor(bool isOn)
{
  digitalWrite(sensorPin, isOn ? HIGH : LOW);
}