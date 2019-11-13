#pragma once

#include "../core/artifacts/Binary.hpp"
#include "../core/artifacts/Sensor.hpp"
#include <Bounce2.h>

using namespace Core;

namespace Light {


    class Button :
            public Binary,
            public Sensor {
    private:
        const OffineSensorData *sensorData;
        Binary *output;
        Bounce debouncer;

    public:
        Button();

        Button(const OffineSensorData *sensorData, Binary *output);

        void setEnabled(bool enabled);

        void read();

        void setup();

        virtual String toString();
    };

    Button::Button() {

    }

    Button::Button(const OffineSensorData *sensorData, Binary *output) {
        this->sensorData = sensorData;
        this->output = output;
#ifdef MY_DEBUG
        Serial.print(F("Button::"));
        Serial.println(this->toString());
#endif
    }


    void Button::setEnabled(bool enabled) {

        if (enabled) {
#ifdef MY_DEBUG
            Serial.print(F("Button::setEnabled("));
            Serial.print(this->toString());
            Serial.println(F(")"));
#endif
            output->toggle();
        }
    }

    void Button::read() {
        setEnabled(false);

        if (debouncer.update()) {
            int value = debouncer.read();
            if (value == LOW) {
                setEnabled(true);
            }
        }
    }

    void Button::setup() {
#ifdef MY_DEBUG
        Serial.print(F("Button::setup("));
        Serial.print(toString());
        Serial.println(F(")"));
#endif
        pinMode((*sensorData).pin, INPUT_PULLUP);
        debouncer.attach((*sensorData).pin);
        debouncer.interval(5);
    }


    String Button::toString() {
        String result = F("Button(PIN:");
        result.concat((*sensorData).pin);
        result.concat(F(", "));

        result.concat(output->toString());

        result.concat(F(")"));
        return result;
    }
}