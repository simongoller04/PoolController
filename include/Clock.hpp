//
// Created by Simon Goller on 07.06.22.
//

#include <Wire.h>
#include "../lib/ds3231FS-1.1.1/ds3231.h"

#ifndef POOLCONTROLLER_CLOCK_HPP
#define POOLCONTROLLER_CLOCK_HPP

class Clock {

private:
    // static instance of Clock
    static Clock *clockInstance;
    // time struct storing all the time values
    ts time;

    /**
     * private Constructor
     * so no objects can be created
     */
    Clock() {};

public:

    /**
     * get the static singleton Instance of Clock
     * @return the static Instance of Clock
     */
    static Clock *getInstance();

    /**
     * initialize the clock
     */
    void init();

    /**
     * provides the current seconds of the clock
     * @return int representing the seconds
     */
    int getSeconds();

    /**
     * provides the current minutes of the clock
     * @return int representing the minutes
     */
    int getMinutes();

    /**
     * provides the current hours of the clock
     * @return int representing the hours
     */
    int getHours();

    /**
     * provides the current month of the clock
     * @return int representing the month
     */
    int getDay();

    /**
     * provides the current month of the clock
     * @return int representing the month
     */
    int getMonth();

    /**
     * provides the current year of the clock
     * @return int representing the year
     */
    int getYear();
};

// 23.06.2022 11:36:00
//    t.hour = 11;
//    t.min = 37;
//    t.sec = 0;
//    t.year = 2022;
//    t.mon = 6;
//    t.mday = 23;
//    t.wday = 4;
//    t.yday = 174;
//    t.isdst = 20;
//    t.year_s = 22;

#endif //POOLCONTROLLER_CLOCK_HPP
