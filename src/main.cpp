#include <Arduino.h>
#include "Pump.hpp"
#include "ConstantPins.hpp"
#include "Clock.hpp"
#include "LCD.hpp"
#include "../lib/Keypad/Keypad.h"
#include "CustomKeypad.hpp"
#include "Calendar.hpp"
#include "SaltMaster.hpp"
#include "WaterTank.hpp"
#include "TemperatureSensor.hpp"

// variables
CustomKeypad *customKeypad;
Keypad *keypad;

void setup() {
    // initialize
    Pump::getInstance()->init(PUMP);
    SaltMaster::getInstance()->init(SALT_MASTER);
    LCD::getInstance()->init(0x27, 20, 4);
    Calendar::getInstance()->init();
    WaterTank::getInstance()->init(TANK_INLET, TANK_OUTLET);
    TemperatureSensor::getInstance()->init(TEMP_SENSOR);

    customKeypad = new CustomKeypad();
    keypad = customKeypad->getKeypad();
}

void loop() {
    customKeypad->handleKeyPressed(keypad->getKey());
    Pump::getInstance()->checkForTime();
    SaltMaster::getInstance()->checkForTime();
    WaterTank::getInstance()->checkState();

    // to display the time on the screen
    if (LCD::getInstance()->getMenu() == CLOCK_START_MENU) {
        LCD::getInstance()->printMenu();
        delay(1000);
    }
}


