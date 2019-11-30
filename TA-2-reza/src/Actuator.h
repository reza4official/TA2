class Actuator
{
private:
    int relayPin;
    int sensorPin;
    int lampOnDuration;
    bool isLampOn;
    long lastTimeOn;


public:
    Actuator(int sensorPin, int relayPin, int lampOnDuration);

    void setLamp(bool isOn);
    void setSensor(bool isOn);
    void runTimerLoop();
};