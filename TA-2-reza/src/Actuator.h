class Actuator
{
private:
    int relayPin;
    int sensorPin;

public:
    Actuator(int sensorPin, int relayPin);

    void setLamp(bool status);
    void setSensor(bool status);
};