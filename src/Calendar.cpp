//
// Created by Simon Goller on 13.06.22.
//

#include "Calendar.hpp"

Calendar *Calendar::calendarInstance = 0;

Calendar *Calendar::getInstance() {
    if(!calendarInstance) {
        calendarInstance = new Calendar;
    }
    return calendarInstance;
}

void Calendar::init() {

    for (int i = 0; i < slotAmount; i++) {
        int *initArray1 = new int[4]{0, 0, 0, 0};
        int *initArray2 = new int[4]{0, 0, 0, 0};
        int *initArray3 = new int[4]{0, 0, 0, 0};
        int *initArray4 = new int[4]{0, 0, 0, 0};

        pumpTimes[i] = Time(initArray1, initArray2);
        saltMasterTimes[i] = Time(initArray3, initArray4);
    }
}

void Calendar::reInit() {
    Time *newPumpTimes = new Time[slotAmount];
    Time *newSaltMasterTimes = new Time[slotAmount];

    for (int i = 0; i < slotAmount; i++) {
        int *initArray1 = new int[4]{0, 0, 0, 0};
        int *initArray2 = new int[4]{0, 0, 0, 0};
        int *initArray3 = new int[4]{0, 0, 0, 0};
        int *initArray4 = new int[4]{0, 0, 0, 0};

        newPumpTimes[i] = Time(initArray1, initArray2);
        newSaltMasterTimes[i] = Time(initArray3, initArray4);
    }

    for (int i = 0; i < oldSlotAmount; i++) {
        newPumpTimes[i] = pumpTimes[i];
        newSaltMasterTimes[i] = saltMasterTimes[i];
    }

    pumpTimes = newPumpTimes;
    saltMasterTimes = newSaltMasterTimes;
}

void Calendar::setSlotAmount(int amount) {
    oldSlotAmount = slotAmount;
    slotAmount = amount;
}

int Calendar::getSlotAmount() {
    return slotAmount;
}

Time Calendar::getPumpTime(int slot) {
    return pumpTimes[slot];
}

Time Calendar::getSaltMasterTime(int slot) {
    return saltMasterTimes[slot];
}

void Calendar::updatePump(int slot) {
    pumpTimes[slot].update();
}

void Calendar::updateSaltMaster(int slot) {
    saltMasterTimes[slot].update();
}
