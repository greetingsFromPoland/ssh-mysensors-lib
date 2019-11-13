#pragma once

#include "Sensor.hpp"
#include "Controller.hpp"
namespace Core { 

class Module {
protected:
    Sensor **sensors;
    Controller **controllers;
    uint8_t sensorsCount = 0;
    uint8_t controllersCount = 0;
public:
    Module();

    Module(Sensor *sensors[], uint8_t sensorsCount, Controller *controllers[], uint8_t controllersCount);

    void read();

    void execute();

    void presentSensors();

    void setup();

    void receive(const MyMessage &message);

    void setTime(uint8_t timeStamp);

    String toString();
};


Module::Module() {

}

Module::Module(Sensor *sensors[], uint8_t sensorsCount, Controller *controllers[], uint8_t controllersCount) {
    this->sensors = sensors;
    this->sensorsCount = sensorsCount;
    this->controllers = controllers;
    this->controllersCount = controllersCount;
#ifdef MY_DEBUG
    Serial.print(F("Module::"));
    Serial.print(toString());
    Serial.println(F(")"));
#endif
}

void Module::read() {
    for (uint8_t i = 0; i < sensorsCount; i++) {
        sensors[i]->read();
        wait(WATI_IN_MODULE_LOOP);
    }
}

void Module::execute() {
    for (uint8_t i = 0; i < controllersCount; i++) {
        controllers[i]->execute();
        wait(WATI_IN_MODULE_LOOP);
    }
}

void Module::presentSensors() {
#ifdef MY_DEBUG
    Serial.println(F("Module::presentSensors()"));
#endif
    for (uint8_t i = 0; i < sensorsCount; i++) {
        sensors[i]->presentSensor();
    }
}

void Module::setup() {
#ifdef MY_DEBUG
    Serial.println(F("Module::setup()"));
#endif
    for (uint8_t i = 0; i < sensorsCount; i++) {
        sensors[i]->setup();
    }
}

void Module::receive(const MyMessage &message) {
#ifdef MY_DEBUG
    Serial.print(F("Module::receive(sender: "));
    Serial.print(message.sender);
    Serial.print(F(", destination: "));
    Serial.print(message.destination);
    Serial.print(F(", sensor: "));
    Serial.print(message.sensor);
    Serial.print(F(", type: "));
    Serial.print(message.type);
    Serial.println(F(")"));
#endif
    for (uint8_t i = 0; i < sensorsCount; i++) {
        sensors[i]->recieve(message);
    }

}

String Module::toString() {
    String result = F("Module(sensorsCount:");
    result.concat(sensorsCount);
    result.concat(F(", controllersCount:"));
    result.concat(controllersCount);
    result.concat(F(")"));
    return result;
}

void Module::setTime(uint8_t timeStamp) {

}

}