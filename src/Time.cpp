//
// Created by Simon Goller on 13.06.22.
//

#include "Time.hpp"

Time::Time(int *start, int *end) {
    startTimeArray = start;
    endTimeArray = end;

    startHours = 0;
    startMinutes = 0;
    endHours = 0;
    endMinutes = 0;
}

int *Time::getStartTimeArray() {
    return startTimeArray;
}

int *Time::getEndTimeArray() {
    return endTimeArray;
}

void Time::update() {
    startHours = startTimeArray[0] * 10 + startTimeArray[1];
    startMinutes = startTimeArray[2] * 10 + startTimeArray[3];

    endHours = endTimeArray[0] * 10 + endTimeArray[1];
    endMinutes = endTimeArray[2] * 10 + endTimeArray[3];
}

int Time::getStartHours() {
    return startHours;
}

int Time::getStartMinutes() {
    return startMinutes;
}

int Time::getEndHours() {
    return endHours;
}

int Time::getEndMinutes() {
    return endMinutes;
}
