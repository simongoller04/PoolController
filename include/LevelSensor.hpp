//
// Created by Simon Goller on 31.05.22.
//
#include "Arduino.h"
#include "ConstantPins.hpp"

#ifndef POOLCONTROLLER_LEVELSENSOR_HPP
#define POOLCONTROLLER_LEVELSENSOR_HPP

/**
 * abstract Class to implement Sensors
 */
class LevelSensor {
private:

protected:
    // gives information if the sensor is currently activated or not
    bool isActivated;


public:
    /**
     * Constructor
     */
    LevelSensor(){};

    /**
     * get the current state of the sensor
     * @return the current state
     */
    virtual bool getState() = 0;

    /**
     * invert the current state
     */
    virtual void toggleState() = 0;
};


/**
 * LowerSensor inherits form LevelSensor
 */
class LowerSensor : public LevelSensor {
private:

public:
    LowerSensor();
    bool getState() override;
    void toggleState() override;

};


/**
 * UpperSensor inherits from LevelSensor
 */
class UpperSensor : public LevelSensor {
private:

public:
    UpperSensor();
    bool getState() override;
    void toggleState() override;
};

#endif //POOLCONTROLLER_LEVELSENSOR_HPP
