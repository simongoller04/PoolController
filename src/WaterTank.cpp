//
// Created by Simon Goller on 26.06.22.
//

#include "WaterTank.hpp"

WaterTank *WaterTank::waterTankInstance = 0;

WaterTank *WaterTank::getInstance() {
    if (!waterTankInstance) {
        waterTankInstance = new WaterTank;
    }
    return waterTankInstance;
}

void WaterTank::init(int pinInlet, int pinOutlet) {
    this->pinInlet = pinInlet;
    this->pinOutlet = pinOutlet;

    pinMode(this->pinInlet, OUTPUT);
    digitalWrite(this->pinInlet, HIGH);

    pinMode(this->pinOutlet, OUTPUT);
    digitalWrite(this->pinOutlet, HIGH);
}

bool WaterTank::getLowerSensorState() {
    return lowerSensor.getState();
}

bool WaterTank::getUpperSensorState() {
    return upperSensor.getState();
}

bool WaterTank::checkTime() {
    if (time >= 10000) { // 900000 15 min
        return true;
    }
    return false;
}

void WaterTank::startTime() {
    time = millis();
}

void WaterTank::toggleInlet() {
    int state = 0;
    // fill when sensor is not activated = water level below sensor
    if (!lowerSensor.getState() && !upperSensor.getState() && !isDraining) {
        isFilling = true;
        state = LOW;
    } else {
        isFilling = false;
        state = HIGH;
    }

    digitalWrite(pinInlet, state);
}

void WaterTank::toggleOutlet() {
    int state = 0;
    // drain when both sensor are activated = water level is max
    if (upperSensor.getState() && lowerSensor.getState() && !isFilling) {
        isDraining = true;
        state = LOW;
    } else {
        isDraining = false;
        state = HIGH;
    }
    digitalWrite(pinOutlet, state);
}

void WaterTank::checkState() {
    toggleOutlet();
    toggleInlet();
}

bool WaterTank::getInletState() {
    return isDraining;
}

bool WaterTank::getOutletState() {
    return isFilling;
}


