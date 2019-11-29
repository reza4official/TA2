class Reader
{
private:
    int relayPin;
    int sensorPin;
    
    int readSensor();

public:
    Reader(int relayPin, int sensorPin);

    void setLamp(bool status);
    void setSensor(bool status);
};