
#ifndef _SENSOR_DATA_
#define _SENSOR_DATA_


struct VurtualSensorData {
public:
    const uint8_t sensorId;
};

struct SensorData {
public:
    const uint8_t pin;
    const uint8_t sensorId;
};

struct OffineSensorData {
public:
    const uint8_t pin;
};

#endif