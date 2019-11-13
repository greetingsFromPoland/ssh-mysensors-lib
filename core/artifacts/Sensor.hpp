#pragma once

#include <MySensors.h>
namespace Core { 

    class Sensor {
    private:
    public:
        virtual void read();

        virtual void presentSensor();

        virtual void setup();

        virtual void recieve(const MyMessage &message);

        virtual String toString();
    };

    void Sensor::read() {
    }

    void Sensor::presentSensor() {
    }

    void Sensor::setup() {
    }

    // String Sensor::toString() {
    //     return F("virtual Sensor::toString");
    // }

    void Sensor::recieve(const MyMessage &message) {
    }


    struct StandardSensorData {
    public:
        const uint8_t pin;
        const uint8_t sensorId;
    };
    struct OffineSensorData {
    public:
        const uint8_t pin;
    };


    struct RemoteSensorData {
    public:
        const uint8_t sensorId;
        const uint8_t nodeId;
    };

    struct VirtualSensorData {
    public:
        const uint8_t sensorId;
    };

}
