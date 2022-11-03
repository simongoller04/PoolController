//
// Created by Simon Goller on 25.06.22.
//

#include "Arduino.h"
#include "Mode.hpp"
#include "Calendar.hpp"
#include "Clock.hpp"
#include "Pump.hpp"

#ifndef POOLCONTROLLER_SALZMASTER_HPP
#define POOLCONTROLLER_SALZMASTER_HPP

class SaltMaster {

private:
    // the current state of the SaltMaster
    bool isOn;
    // the pin to use
    int pin;
    // the static instance of SaltMaster
    static SaltMaster *saltMasterInstance;

    /**
     * private Constructor
     * so no objects can be created
     */
    SaltMaster() {};

public:

    /**
     * initialize the SaltMaster
     * @param pin the pin which is used to control the SaltMaster
     */
    void init(int pin);

    /**
     * get the static instance of SaltMaster
     * @return the static instance of SaltMaster
     */
    static SaltMaster *getInstance();

    /**
     * Method which returns if the SaltMaster is currently turned on or not
     * @return a bool representing the state
     */
    bool getState();

    /**
     * activate the SaltMaster
     */
    void activate();

    /**
     * deactivate the SaltMaster
     */
    void deactivate();

    /**
     * check if the calendar says the saltMaster should be activated or deactivated
     */
    void checkForTime();
};

#endif //POOLCONTROLLER_SALZMASTER_HPP
