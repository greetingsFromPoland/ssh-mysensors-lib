#pragma once

#include "../core/artifacts/Binary.hpp"
#include "../core/artifacts/Sensor.hpp"
using namespace Core;

namespace Light {


    class Zone :
            public Binary,
            public Sensor {
    private:
        const VirtualSensorData *sensorData;
        Binary **outputs;
        uint8_t outputsSize;
    public:
        Zone();

        Zone(const VirtualSensorData *sensorData, Binary *outputs[], uint8_t outputsSize);

        void setEnabled(bool enabled);

        void presentSensor();

        void recieve(const MyMessage &message);

        String toString();

        void sendCurrentState();
    };

    Zone::Zone() {}

    Zone::Zone(const VirtualSensorData *sensorData, Binary *outputs[], uint8_t outputsSize) {
        this->sensorData = sensorData;
        this->outputs = outputs;
        this->outputsSize = outputsSize;

#ifdef MY_DEBUG
        Serial.print(F("Zone::"));
        Serial.println(this->toString());
#endif
    }

    void Zone::setEnabled(bool enabled) {

#ifdef MY_DEBUG
        Serial.print(F("Zone::setEnabled(new:"));
        Serial.print(enabled);
        Serial.print(", old: ");
        Serial.print(toString());
        Serial.println(F(")"));
#endif

        for (uint8_t i = 0; i < outputsSize; i++) {
            outputs[i]->setEnabled(enabled);
        }

        saveState((*sensorData).sensorId, isEnabled());
        sendCurrentState();
        this->enabled = enabled;
    }

    void Zone::presentSensor() {
#ifdef MY_DEBUG
        Serial.print(F("Zone::presentSensor("));
        Serial.print(toString());
        Serial.println(F(")"));
#endif
        present((*sensorData).sensorId, S_BINARY);

    }

    void Zone::recieve(const MyMessage &message) {
        if (message.type == V_STATUS && message.getBool() != enabled) {
#ifdef MY_DEBUG
            Serial.print(F("Zone::onMessage("));
            Serial.print(toString());
            Serial.println(F(")"));
#endif

            setEnabled(message.getBool());
        }
    }

    String Zone::toString() {
        String result = F("Zone(Enabled:");
        result.concat(isEnabled());
        result.concat(F(", sensorId:"));
        result.concat((*sensorData).sensorId);
        result.concat(F(")"));
        return result;
    }


    void Zone::sendCurrentState() {
#ifdef MY_DEBUG
        Serial.print(F("Zone::sendCurrentState("));
        Serial.print(toString());
        Serial.println(F(")"));
#endif
        static MyMessage updateStateMessage = MyMessage();

        updateStateMessage.clear();
        updateStateMessage.setType(S_BINARY);
        updateStateMessage.setSensor((*sensorData).sensorId);
        updateStateMessage.set(isEnabled());

        send(updateStateMessage);
    }
}