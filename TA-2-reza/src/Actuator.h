class Actuator
{
private:
    int relayPin;
    int sensorPin;
    int lampOnDuration;

public:
    Actuator(int sensorPin, int relayPin, int lampOnDuration);

    void setLamp(bool status);
    void setSensor(bool status);
};