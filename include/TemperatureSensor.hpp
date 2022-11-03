//
// Created by Simon Goller on 28.06.22.
//
#include "ConstantPins.hpp"
#include "../.pio/libdeps/megaatmega2560/OneWire/OneWire.h"
#include "../.pio/libdeps/megaatmega2560/DallasTemperature/DallasTemperature.h"

#ifndef POOLCONTROLLER_TEMPERATURESENSOR_HPP
#define POOLCONTROLLER_TEMPERATURESENSOR_HPP


/**
 * Class used to determine the current temperature
 * of the water inside of the pool
 */
class TemperatureSensor {

private:
    // static instance of TemperatureSensor
    static TemperatureSensor *temperatureSensorInstance;
    // the current temperature of the water
    float temperature;
    // setup a oneWire instance to communicate with any OneWire devices
    OneWire oneWire;

    DallasTemperature tempSensor;

    /**
     * private Constructor
     * so no objects can be created
     */
    TemperatureSensor() {};

public:
    /**
     * get the static instance of TemperatureSensor
     * @return the static instance
     */
    static TemperatureSensor *getInstance();

    /**
     * initialize the temperature sensor
     * @param pin which is used to read the pump
     */
    void init(int pin);

    /**
     * get the current temperature of the pool
     * @return the current temperature as int
     */
    float getTemperature();

};

#endif //POOLCONTROLLER_TEMPERATURESENSOR_HPP
