//
// Created by Simon Goller on 26.06.22.
//

#include "LevelSensor.hpp"
#include "ConstantPins.hpp"
#include "Clock.hpp"

#ifndef POOLCONTROLLER_WATERTANK_HPP
#define POOLCONTROLLER_WATERTANK_HPP

class WaterTank {
private:
    /*+
     * two bools are required because the tank has an upper and a lower sensor
     * 1. if the tank is full both variables need to be true
     * 2. if the tank is empty both variables need to be false
     * 3. if the tank is half full isUpperSensorDetected is false and isLowerSensorDetected is true
     */

    // gives information about if the tank is full
    UpperSensor upperSensor = UpperSensor();
    // gives information about if the tank is empty
    LowerSensor lowerSensor = LowerSensor();
    // static instance of WaterTank
    static WaterTank *waterTankInstance;
    // current state of the inlet
    bool isFilling = false;
    // current state of the outlet
    bool isDraining = false;
    // array which stores the hours and minutes when the outlet was opened
    int *timerOutlet;
    // array which stores the hours and minutes when the inlet was opened
    int *timerInlet;
    // pin used for the inlet
    int pinInlet;
    // pin uses for the outlet
    int pinOutlet;

    unsigned long time;

    /**
     * private Constructor
     * so no objects can be created
     */
    WaterTank() {};

public:
    /**
     * provide the static instance of WaterTank
     * @return the static instance
     */
    static WaterTank *getInstance();

    /**
     * initialize the water tank
     * @param pinInlet
     * @param pinOutlet
     */
    void init(int pinInlet, int pinOutlet);

    /**
     * get the current state of the upper Sensor
     * @return a bool representing the current state
     */
    bool getUpperSensorState();

    /**
     * get the current state of the lower Sensor
     * @return a bool representing the current state
     */
    bool getLowerSensorState();

    /**
     * check if the outlet/inlet needs to be opened/closed
     */
    void checkState();

    /**
     * open/close the outlet
     */
    void toggleOutlet();

    /**
     * open/close the inlet
     */
    void toggleInlet();

    /**
     * get the current state of the inlet
     * @return a bool representing the current state
     */
    bool getInletState();

    /**
     * get the current state of the outlet
     * @return a bool representing the current state
     */
    bool getOutletState();

    /**
     * start a timer
     */
    void startTime();

    /**
     * check if the timer has reached a certain amount an the inlet/outlet need to be closed again
     * @return true if the time is reached/exceeded
     */
    bool checkTime();
};

#endif //POOLCONTROLLER_WATERTANK_HPP
