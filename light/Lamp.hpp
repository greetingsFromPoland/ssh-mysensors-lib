#pragma once


#include "../core/artifacts/Binary.hpp"
#include "../core/artifacts/Sensor.hpp"
using namespace Core;

namespace Light {


    class Lamp :
            public Binary,
            public Sensor {
    private:
        const StandardSensorData *sensorData;
    public:
        Lamp(/* args */);

        Lamp(const StandardSensorData *sensorData);

        void setEnabled(bool enabled);

        void presentSensor();

        void setup();

        void recieve(const MyMessage &message);

        String toString();

        void sendCurrentState();
    };

    Lamp::Lamp() {}

    Lamp::Lamp(const StandardSensorData *sensorData) {
        this->sensorData = sensorData;
#ifdef MY_DEBUG
        Serial.print(F("Lamp::"));
        Serial.println(this->toString());
#endif
    }

    void Lamp::setEnabled(bool enabled) {

        if (this->enabled != enabled) {
#ifdef MY_DEBUG
            Serial.print(F("Lamp::setEnabled(new:"));
            Serial.print(enabled);
            Serial.print(", old: ");
            Serial.print(toString());
            Serial.println(F(")"));
#endif

            digitalWrite((*sensorData).pin, enabled ? HIGH : LOW);
            saveState((*sensorData).sensorId, enabled);
            sendCurrentState();
            this->enabled = enabled;
        }
    }

    void Lamp::presentSensor() {
#ifdef MY_DEBUG
        Serial.print(F("Lamp::presentSensor("));
        Serial.print(toString());
        Serial.println(F(")"));
#endif

        present((*sensorData).sensorId, S_BINARY);

    }

    void Lamp::setup() {
#ifdef MY_DEBUG
        Serial.print(F("Lamp::setup("));
        Serial.print(toString());
        Serial.println(F(")"));
#endif

        pinMode((*sensorData).pin, OUTPUT);
        enabled = loadState((*sensorData).sensorId);
        digitalWrite((*sensorData).pin, enabled ? HIGH : LOW);
        saveState((*sensorData).sensorId, enabled);
        sendCurrentState();
    }

    void Lamp::recieve(const MyMessage &message) {
        if (message.destination == MY_NODE_ID &&
            message.sensor == (*sensorData).sensorId &&
            message.type == V_STATUS &&
            message.getBool() != enabled) {

#ifdef MY_DEBUG
            Serial.print(F("Lamp::onMessage("));
            Serial.print(toString());
            Serial.println(F(")"));
#endif

            setEnabled(message.getBool());
        }
    }

    String Lamp::toString() {
        String result = F("Lamp(Enabled:");
        result.concat(enabled);
        result.concat(F(", pin:"));
        result.concat((*sensorData).pin);
        result.concat(F(", sensorId:"));
        result.concat((*sensorData).sensorId);
        result.concat(F(")"));
        return result;
    }


    void Lamp::sendCurrentState() {
#ifdef MY_DEBUG
        Serial.print(F("Lamp::sendCurrentState("));
        Serial.print(toString());
        Serial.println(F(")"));
#endif
        static MyMessage updateStateMessage = MyMessage();

        updateStateMessage.clear();
        updateStateMessage.setType(S_BINARY);
        updateStateMessage.setSensor((*sensorData).sensorId);
        updateStateMessage.set(enabled);

        send(updateStateMessage);
    }

}
