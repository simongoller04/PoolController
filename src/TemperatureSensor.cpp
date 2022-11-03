//
// Created by Simon Goller on 28.06.22.
//

#include "TemperatureSensor.hpp"

TemperatureSensor *TemperatureSensor::temperatureSensorInstance = 0;

TemperatureSensor *TemperatureSensor::getInstance() {
    if (!temperatureSensorInstance) {
        temperatureSensorInstance = new TemperatureSensor;
    }
    return temperatureSensorInstance;
}

float TemperatureSensor::getTemperature() {
    tempSensor.requestTemperatures();
    temperature = tempSensor.getTempCByIndex(0);
    return temperature;
}

void TemperatureSensor::init(int pin) {
    oneWire = OneWire(pin);
    tempSensor = DallasTemperature(&oneWire);
    tempSensor.begin();
}