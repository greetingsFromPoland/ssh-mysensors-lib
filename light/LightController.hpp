
#ifndef _LIGHT_CONTROLLER_
#define _LIGHT_CONTROLLER_

#include "LightButton.hpp"

class LightController {
private:
    Lamp **lamps;
    uint8_t lampsSize;
    LightButton **buttons;
    uint8_t buttonsSize;
public:
    LightController();

    LightController(Lamp *lamps[], uint8_t lampsSize, LightButton *buttons[], uint8_t buttonsSize);

    void receive(const MyMessage &message);

    void setup();

    void present();

    void run();

    String toString();
};


LightController::LightController() {

}

LightController::LightController(Lamp *lamps[], uint8_t lampsSize, LightButton *buttons[],
                                 uint8_t buttonsSize) {
    this->lamps = lamps;
    this->buttons = buttons;
    this->lampsSize = lampsSize;
    this->buttonsSize = buttonsSize;

#ifdef MY_DEBUG
    Serial.print(F("LightController::LightController(lampsSize: "));
    Serial.print(lampsSize);
    Serial.print(F(",buttonsSize: "));
    Serial.print(buttonsSize);
    Serial.println(F(")"));
#endif

};

void LightController::present() {
#ifdef MY_DEBUG
    Serial.println(F("LightController::present()"));
#endif

    for (uint8_t i = 0; i < lampsSize; i++) {
        lamps[i]->registerLamp();
    }

};

void LightController::run() {
    for (uint8_t i = 0; i < lampsSize; i++) {
        lamps[i]->run();
    }
    for (uint8_t i = 0; i < buttonsSize; i++) {
        buttons[i]->run();
    }
};

void LightController::setup() {
#ifdef MY_DEBUG
    Serial.print(F("LightController::setup(lampsSize: "));
    Serial.print(this->lampsSize);
    Serial.println(F(")"));
#endif

    for (uint8_t i = 0; i < lampsSize; i++) {
        lamps[i]->setup();
    }
    for (uint8_t i = 0; i < buttonsSize; i++) {
        buttons[i]->setup();
    }
};


void LightController::receive(const MyMessage &message) {
    for (uint8_t i = 0; i < lampsSize; i++) {
        lamps[i]->receive(message);
    }
};

String LightController::toString() {
    String result = F("LightController(lampsSize:");
    result.concat(lampsSize);
    result.concat(F(", buttonsSize:"));
    result.concat(buttonsSize);
    result.concat(F(")"));
    return result;
}


#endif