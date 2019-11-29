class Reader
{
private:
    int sensorPin;

    int readSensor();

public:
    Reader(int sensorPin);

    void setSensor(bool status);
};