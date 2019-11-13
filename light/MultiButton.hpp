#pragma once

#include "../core/artifacts/Binary.hpp"
#include "../core/artifacts/Sensor.hpp"
#include <Bounce2.h>
using namespace Core;

namespace Light {


    class MultiLightButton :
            public Binary,
            public Sensor {
    private:
        const OffineSensorData *sensorData;
        Binary **outputs;
        uint8_t outputsSize;
        Bounce debouncer;

    public:
        MultiLightButton();

        MultiLightButton(const OffineSensorData *sensorData, Binary *outputs[], uint8_t outputsSize);

        void setEnabled(bool enabled);

        void read();

        void setup();

        virtual String toString();
    };

    MultiLightButton::MultiLightButton() {

    }

    MultiLightButton::MultiLightButton(const OffineSensorData *sensorData, Binary *outputs[], uint8_t outputsSize) {
        this->sensorData = sensorData;
        this->outputs = outputs;
        this->outputsSize = outputsSize;
    }

    void MultiLightButton::setEnabled(bool enabled) {
        for (uint8_t i = 0; i < outputsSize; i++) {
            outputs[i]->toggle();
        }
    }

    void MultiLightButton::read() {
        setEnabled(false);

        if (debouncer.update()) {
            int value = debouncer.read();
            if (value == LOW) {
                setEnabled(true);
            }
        }
    }

    void MultiLightButton::setup() {
        pinMode((*sensorData).pin, INPUT_PULLUP);
        debouncer.attach((*sensorData).pin);
        debouncer.interval(5);
    }


    String MultiLightButton::toString() {
        String result = F("MultiLightButton(PIN:");
        result.concat((*sensorData).pin);

        for (uint8_t i = 0; i < outputsSize; i++) {
            result.concat(outputs[i]->toString());
            result.concat(F(", "));
        }
        result.concat(F(")"));
        return result;
    }
}