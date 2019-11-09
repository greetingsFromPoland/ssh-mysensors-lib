#ifndef _LIGHT_BUTTON_
#define _LIGHT_BUTTON_

#include "Lamp.hpp"
#include <MySensors.h>
#include <Arduino.h>
#include <Bounce2.h>

class LightButton {
private:
    uint8_t pin;
    Lamp **lamps;
    uint8_t lampsSize;
    Bounce debouncer;
    Lamp *lamp;

    void onClick();

public:
    LightButton();

    LightButton(uint8_t pin, Lamp *lapmps[], uint8_t lampsSize);

    LightButton(const SensorData &sensorData, Lamp *lapmps[], uint8_t lampsSize);

    LightButton(const SensorData &sensorData, Lamp *lamp);

    void run();

    void setup();

    String toString();
};


LightButton::LightButton() {
    this->debouncer = Bounce();
}

LightButton::LightButton(uint8_t pin, Lamp *lapmps[], uint8_t lampsSize) {
    this->lamps = lapmps;
    this->lampsSize = lampsSize;
    this->pin = pin;
    this->debouncer = Bounce();
}

LightButton::LightButton(const SensorData &sensorData, Lamp *lapmps[], uint8_t lampsSize) {
    this->lamps = lapmps;
    this->lampsSize = lampsSize;
    this->pin = sensorData.pin;
    this->debouncer = Bounce();
}

LightButton::LightButton(const SensorData &sensorData, Lamp *lamp) {
    this->pin = sensorData.pin;
    this->lamp = lamp;
    this->lampsSize = 1;
    this->debouncer = Bounce();
}

String LightButton::toString() {
    String result = F("Button(lampsCount:");
    result.concat(lampsSize);
    result.concat(F(", Lamps: "));

    for (uint8_t i = 0; i < lampsSize; i++) {
        result.concat(lamps[i]->toString());
        if (i + 1 < lampsSize) {
            result.concat(F(", "));
        }
    }

    result.concat(F(")"));

    return result;

}

void LightButton::run() {
    if (debouncer.update()) {
        int value = debouncer.read();
        if (value == LOW) {
            onClick();
        }
    }
}

void LightButton::setup() {
    pinMode(pin, INPUT_PULLUP);
    debouncer.attach(pin);
    debouncer.interval(5);
}

void LightButton::onClick() {
#ifdef MY_DEBUG
    Serial.print(F("LightButton::onClick(pin:"));
    Serial.print(pin);
    Serial.print(F(", lampsSize: "));
    Serial.print(lampsSize);
    Serial.println(F(")"));
#endif

    if (lampsSize == 1) {
        lamp->toggle();
    } else {
        for (uint8_t i = 0; i < lampsSize; i++) {
            lamps[i]->toggle();
        }
    }

}

#endif