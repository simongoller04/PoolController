//
// Created by Simon Goller on 31.05.22.
//

#include "Arduino.h"
#include "Mode.hpp"
#include "Calendar.hpp"
#include "Clock.hpp"
#include "WaterTank.hpp"

#ifndef POOLCONTROLLER_PUMP_HPP
#define POOLCONTROLLER_PUMP_HPP


class Pump {

private:
    // the current state of the pump
    bool isOn;
    // the pin to use
    int pin;
    // the static instance of pump
    static Pump *pumpInstance;

    /**
     * private Constructor
     * so no objects can be created
     */
    Pump() {};

public:

    /**
     * initialize the pump
     * @param pin the pin which is used to control the pump
     */
    void init(int pin);

    /**
     * get the static instance of pump
     * @return the static instance of pump
     */
    static Pump *getInstance();

    /**
     * Method which returns if the Pump is currently turned on or not
     * @return a bool representing the state
     */
    bool getState();

    /**
     * activate the pump
     */
    void activate();

    /**
     * deactivate the pump
     */
    void deactivate();

    /**
     * check if the calendar says the pump should be activated or deactivated
     */
    void checkForTime();
};


#endif //POOLCONTROLLER_PUMP_HPP
