//
// Created by Simon Goller on 25.06.22.
//

#include "SaltMaster.hpp"
#include "LCD.hpp"

SaltMaster *SaltMaster::saltMasterInstance = 0;

SaltMaster *SaltMaster::getInstance() {
    if (!saltMasterInstance) {
        saltMasterInstance = new SaltMaster;
    }
    return saltMasterInstance;
}

void SaltMaster::init(int pin) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
    this->pin = pin;
    isOn = false;
}

void SaltMaster::activate() {
    isOn = true;
    digitalWrite(pin, LOW);
}

void SaltMaster::deactivate() {
    isOn = false;
    digitalWrite(pin, HIGH);
}

bool SaltMaster::getState() {
    return isOn;
}

void SaltMaster::checkForTime() {
    Calendar *calendar = Calendar::getInstance();
    Mode *mode = Mode::getInstance();
    Clock *clock = Clock::getInstance();
    Pump *pump = Pump::getInstance();

    if (mode->getIsAutomaticMode()) {
        for (int i = 0; i < calendar->getSlotAmount(); i++) {
            // if the current time is equal to a start time in the time plan and
            // the pump is currently turned on and
            // the salt master is currently turned off, then turn the slat master on
            if (clock->getHours() == calendar->getSaltMasterTime(i).getStartHours() &&
                clock->getMinutes() == calendar->getSaltMasterTime(i).getStartMinutes() &&
                clock->getSeconds() == 0 && pump->getState() && !isOn) {
                activate();
            }

            // if the current time is equal to an end time in the time plan and
            // the salt master is currently turned on, then turn the salt master off
            if (clock->getHours() == calendar->getSaltMasterTime(i).getEndHours() &&
                clock->getMinutes() == calendar->getSaltMasterTime(i).getEndMinutes() &&
                clock->getSeconds() == 0 && isOn) {
                deactivate();
            }
        }
    }

    // always deactivate if the pump is turned off
    if (!pump->getState() && isOn) {
        deactivate();

        if (LCD::getInstance()->getMenu() == CURRENT_STATS_MENU) {
            LCD::getInstance()->printMenu();
        }
    }
}