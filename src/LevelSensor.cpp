//
// Created by Simon Goller on 27.06.22.
//

#include "LevelSensor.hpp"

/// ------------------------ UPPER SENSOR ------------------------ ///

UpperSensor::UpperSensor() {
    pinMode(TANK_FULL, INPUT_PULLUP);
    isActivated = false;
}

bool UpperSensor::getState() {
    if (digitalRead(TANK_FULL) == HIGH) {
        isActivated = false;
    }
    else {
        isActivated = true;
    }

    return isActivated;
}

void UpperSensor::toggleState() {
    if (digitalRead(TANK_FULL) == HIGH) {
        isActivated = true;
    } else {
        isActivated = false;
    }
}

/// ------------------------ LOWER SENSOR ------------------------ ///

LowerSensor::LowerSensor() {
    pinMode(TANK_EMPTY, INPUT_PULLUP);
    isActivated = false;
}

bool LowerSensor::getState() {
    if (digitalRead(TANK_EMPTY) == HIGH) {
        isActivated = false;
    } else {
        isActivated = true;
    }

    return isActivated;
}

void LowerSensor::toggleState() {
    if (digitalRead(TANK_EMPTY) == HIGH) {
        isActivated = false;
    } else {
        isActivated = true;
    }
}
