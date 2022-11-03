//
// Created by Simon Goller on 31.05.22.
//

#include "Pump.hpp"
#include "LCD.hpp"

Pump *Pump::pumpInstance = 0;

Pump *Pump::getInstance() {
    if (!pumpInstance) {
        pumpInstance = new Pump;
    }
    return pumpInstance;
}

void Pump::init(int pin) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
    this->pin = pin;
    isOn = false;
}

void Pump::activate() {
    isOn = true;
    digitalWrite(pin, LOW);
}

void Pump::deactivate() {
    isOn = false;
    digitalWrite(pin, HIGH);
}

bool Pump::getState() {
    return isOn;
}

void Pump::checkForTime() {
    Calendar *calendar = Calendar::getInstance();
    Mode *mode = Mode::getInstance();
    Clock *clock = Clock::getInstance();
    WaterTank *waterTank = WaterTank::getInstance();

    // automatic mode is activated
    if (mode->getIsAutomaticMode()) {
        for (int i = 0; i < calendar->getSlotAmount(); i++) {
            // if the current time is equal to a start time in the time plan and
            // the pump is currently turned off, then turn the pump on
            if (clock->getHours() == calendar->getPumpTime(i).getStartHours() &&
                clock->getMinutes() == calendar->getPumpTime(i).getStartMinutes() &&
                clock->getSeconds() == 0 && !isOn) {
                activate();
            }

            // if the current time is equal to an end time in the time plan and
            // the pump is currently turned on, then turn the pump off
            if (clock->getHours() == calendar->getPumpTime(i).getEndHours() &&
                clock->getMinutes() == calendar->getPumpTime(i).getEndMinutes() &&
                clock->getSeconds() == 0 && isOn) {
                deactivate();
            }
        }
    }

    // if the water tank is currently filled or drained the pump is turned off
    if ((waterTank->getOutletState() || waterTank->getInletState()) && isOn) {
        deactivate();

        if (LCD::getInstance()->getMenu() == CURRENT_STATS_MENU) {
            LCD::getInstance()->printMenu();
        }
    }
}



