class Actuator
{
private:
    int relayPin;
    int sensorPin;
    int lampOnDuration;

    void runTurnOffTimer();

public:
    Actuator(int sensorPin, int relayPin, int lampOnDuration);

    void setLamp(bool isOn);
    void setSensor(bool isOn);
};