class Actuator
{
private:
    int relayPin;
    int sensorPin;

public:
    Actuator(int relayPin, int sensorPin);

    void setLamp(bool status);
    void setSensor(bool status);
};