//
// Created by Simon Goller on 07.06.22.
//

#include "Clock.hpp"
Clock *Clock::clockInstance = 0;

Clock *Clock::getInstance() {
    if(!clockInstance) {
        clockInstance = new Clock;
    }
    return clockInstance;
}

void Clock::init() {
    Wire.begin(); //start i2c (required for connection)
    DS3231_init(DS3231_INTCN); //register the ds3231 (DS3231_INTCN is the default address)
}

int Clock::getSeconds() {
    DS3231_get(&time);
    return time.sec;
}

int Clock::getMinutes() {
    DS3231_get(&time);
    return time.min;
}

int Clock::getHours() {
    DS3231_get(&time);
    return time.hour;
}

int Clock::getDay() {
    DS3231_get(&time);
    return time.mday;
}

int Clock::getMonth() {
    DS3231_get(&time);
    return time.mon;
}

int Clock::getYear() {
    DS3231_get(&time);
    return time.year;
}
