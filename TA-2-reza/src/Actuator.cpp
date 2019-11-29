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
  digitalWrite(relayPin, isOn ? HIGH : LOW);
  runTurnOffTimer();
}

void Actuator::runTurnOffTimer()
{
  // reset timer first then
  // if timer goes off
  setLamp(false);
}

void Actuator::setSensor(bool isOn)
{
  digitalWrite(sensorPin, isOn ? HIGH : LOW);
}