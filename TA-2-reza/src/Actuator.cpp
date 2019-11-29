#include <Arduino.h>

int relayPin = 2;    // pin for the RELAY

/** switch light */
void toggleSwitch(bool isOn)
{
  digitalWrite(relayPin, isOn ? HIGH : LOW);
}