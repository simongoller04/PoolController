//
// Created by Simon Goller on 07.06.22.
//

#include "LCD.hpp"
#include "../lib/Keypad/Keypad.h"
#include "CustomKeypad.hpp"

LCD *LCD::lcdInstance = 0;

void LCD::init(int address, int rows, int columns) {
    lcd = new LiquidCrystal_I2C(address, rows, columns);
    menu = 2;
    position = 1;

    start();
}

LCD *LCD::getInstance() {
    if (!lcdInstance) {
        lcdInstance = new LCD;
    }
    return lcdInstance;
}

void LCD::start () {
    lcd->init();
    lcd->backlight();
    lcd->setCursor(0, 1);
    lcd->print("-- PoolController --");
    lcd->setCursor(0, 2);
    lcd->print("---- Version--1 ----");

    delay(1500);

    lcd->clear();
    printMenu();
}

void LCD::print (String string) {
    lcd->print(string);
}

int LCD::getMenu() {
    return menu;
}

int LCD::getPosition() {
    return position;
}

void LCD::incrementMenu () {
    menu++;
    position = 1;
    printMenu();
}

void LCD::decrementMenu () {
    menu--;
    position = 1;
    printMenu();
}

void LCD::incrementPosition () {
    position++;
    timeArrayPosition = 0;
    printMenu();
}

void LCD::decrementPosition () {
    position--;
    timeArrayPosition = 0;
    printMenu();
}

void LCD::incrementTimeArrayPosition() {
    if (timeArrayPosition <= 3) {
        timeArrayPosition++;
    }
    else {
        timeArrayPosition = 0;
    }
}

void LCD::setNumericValue(int value) {

    if (menu == CALENDAR_PUMP_MENU || menu == CALENDAR_SM_MENU) {

        switch (timeArrayPosition) {
            case 0: {
                // hours at position 0 can not be bigger than 2 and smaller than 0
                if (0 <= value && value <= 2) {
                    timeArray[timeArrayPosition] = value;
                }
                break;
            }

            case 1: {
                // hours at position 0 is smaller than 2
                if (timeArray[0] < 2) {
                    // hours at position 1 can not be bigger than 9 and smaller than 0
                    if (0 <= value && value <= 9) {
                        timeArray[timeArrayPosition] = value;
                    }
                }
                    // hours at position 0 is 2
                else {
                    // hours at position 1 can not be bigger than 4 and smaller than 0
                    if (0 <= value && value <= 3) {
                        timeArray[timeArrayPosition] = value;
                    }
                }
                break;
            }

            case 2: {
                // minutes at position 2 can not be bigger than 5 and smaller than 0
                if (0 <= value && value <= 5) {
                    timeArray[timeArrayPosition] = value;
                }
                break;
            }

            case 3: {
                // minutes at position 3 can not be bigger than 9 and smaller than 0
                if (0 <= value && value <= 9) {
                    timeArray[timeArrayPosition] = value;
                }
                break;
            }
        }
        Calendar::getInstance()->updatePump(slotPosition);
        Calendar::getInstance()->updateSaltMaster(slotPosition);

        printMenu();
    }

    else if (menu == TIME_SLOT_MENU) {
        Calendar::getInstance()->setSlotAmount(value);
        Calendar::getInstance()->reInit();
        printMenu();
    }
}


void LCD::printMenu () {
    lcd->clear();

    if (menu == CLOCK_START_MENU) {
            lcd->clear();
            lcd->print("Time: ");
            lcd->print(static_cast<StringSumHelper &&>(Clock::getInstance()->getHours()));
            lcd->print(":");
            lcd->print(static_cast<StringSumHelper &&>(Clock::getInstance()->getMinutes()));
            lcd->print(":");
            lcd->print(static_cast<StringSumHelper &&>(Clock::getInstance()->getSeconds()));

            lcd->setCursor(0, 1);

            lcd->print("Date: ");
            lcd->print(static_cast<StringSumHelper &&>(Clock::getInstance()->getDay()));
            lcd->print("/");
            lcd->print(static_cast<StringSumHelper &&>(Clock::getInstance()->getMonth()));
            lcd->print("/");
            lcd->print(static_cast<StringSumHelper &&>(Clock::getInstance()->getYear()));
    }

    else if (menu == CURRENT_STATS_MENU) {
        switch (position) {
            case MIN_STATS: {
                incrementPosition();
                break;
            }

            case PUMP_STATS: {
                lcd->print("---Current Stats---");
                lcd->setCursor(0, 1);
                lcd->print(">Pump: ");
                if (Pump::getInstance()->getState()) {
                    lcd->print("ON");
                } else {
                    lcd->print("OFF");
                }

                lcd->setCursor(0, 2);
                lcd->print(" SaltMaster: ");
                if (SaltMaster::getInstance()->getState()) {
                    lcd->print("ON");
                } else {
                    lcd->print("OFF");
                }

                lcd->setCursor(0, 3);
                lcd->print(" Pool Temp.: ");
                lcd->print(TemperatureSensor::getInstance()->getTemperature());
                lcd->print((char)223);
                lcd->print("C");
                break;
            }

            case SALT_MASTER_STATS: {
                lcd->print("---Current Stats---");
                lcd->setCursor(0, 1);
                lcd->print(" Pump: ");
                if (Pump::getInstance()->getState()) {
                    lcd->print("ON");
                } else {
                    lcd->print("OFF");
                }

                lcd->setCursor(0, 2);
                lcd->print(">SaltMaster: ");
                if (SaltMaster::getInstance()->getState()) {
                    lcd->print("ON");
                } else {
                    lcd->print("OFF");
                }

                lcd->setCursor(0, 3);
                lcd->print(" Pool Temp.: ");
                lcd->print(TemperatureSensor::getInstance()->getTemperature());
                lcd->print((char)223);
                lcd->print("C");
                break;
            }

            case POOL_TEMP_STATS: {
                lcd->print("---Current Stats---");
                lcd->setCursor(0, 1);
                lcd->print(" Pump: ");
                if (Pump::getInstance()->getState()) {
                    lcd->print("ON");
                } else {
                    lcd->print("OFF");
                }

                lcd->setCursor(0, 2);
                lcd->print(" SaltMaster: ");
                if (SaltMaster::getInstance()->getState()) {
                    lcd->print("ON");
                } else {
                    lcd->print("OFF");
                }

                lcd->setCursor(0, 3);
                lcd->print(">Pool Temp.: ");
                lcd->print(TemperatureSensor::getInstance()->getTemperature());
                lcd->print((char)223);
                lcd->print("C");
                break;
            }

            case INLET_STATS: {
                lcd->print("---Current Stats---");
                lcd->setCursor(0, 1);
                lcd->print(">Inlet: ");
                if (WaterTank::getInstance()->getLowerSensorState()) {
                    lcd->print("ON");
                } else {
                    lcd->print("OFF");
                }

                lcd->setCursor(0, 2);
                lcd->print(" Outlet: ");
                if (WaterTank::getInstance()->getUpperSensorState()) {
                    lcd->print("ON");
                } else {
                    lcd->print("OFF");
                }

                break;
            }

            case OUTLET_STATS: {
                lcd->print("---Current Stats---");
                lcd->setCursor(0, 1);
                lcd->print(" Inlet: ");
                if (WaterTank::getInstance()->getLowerSensorState()) {
                    lcd->print("ON");
                } else {
                    lcd->print("OFF");
                }

                lcd->setCursor(0, 2);
                lcd->print(">Outlet: ");
                if (WaterTank::getInstance()->getUpperSensorState()) {
                    lcd->print("ON");
                } else {
                    lcd->print("OFF");
                }

                break;
            }

            case MAX_STATS: {
                decrementPosition();
                break;
            }
        }
    }

    else if (menu == AUTOMATIC_MANUAL_MENU) {
        switch (position) {

            case 0: {
                incrementPosition();
                break;
            }
            case 1: {
                lcd->print("-----Chose Mode-----");
                lcd->setCursor(0, 1);
                lcd->print(">Automatic ");

                if (Mode::getInstance()->getIsAutomaticMode()) {
                    lcd->print("*");
                }

                lcd->setCursor(0, 2);
                lcd->print(" Manual ");

                if (!Mode::getInstance()->getIsAutomaticMode()) {
                    lcd->print("*");
                }
                break;
            }

            case 2: {
                lcd->print("-----Chose Mode-----");
                lcd->setCursor(0, 1);
                lcd->print(" Automatic ");

                if (Mode::getInstance()->getIsAutomaticMode()) {
                    lcd->print("*");
                }

                lcd->setCursor(0, 2);
                lcd->print(">Manual ");

                if (!Mode::getInstance()->getIsAutomaticMode()) {
                    lcd->print("*");
                }
                break;
            }

            case 3: {
                decrementPosition();
                break;
            }
        }
    }

    else if (menu == WINTER_SUMMER_MENU) {
        switch (position) {

            case 0: {
                incrementPosition();
                break;
            }
            case 1: {
                lcd->print("-----Chose Mode-----");
                lcd->setCursor(0, 1);
                lcd->print(">Summer ");

                if (Mode::getInstance()->getIsSummerMode()) {
                    lcd->print("*");
                }

                lcd->setCursor(0, 2);
                lcd->print(" Winter ");

                if (!Mode::getInstance()->getIsSummerMode()) {
                    lcd->print("*");
                }
                break;
            }

            case 2: {
                lcd->print("-----Chose Mode-----");
                lcd->setCursor(0, 1);
                lcd->print(" Summer ");

                if (Mode::getInstance()->getIsSummerMode()) {
                    lcd->print("*");
                }

                lcd->setCursor(0, 2);
                lcd->print(">Winter ");

                if (!Mode::getInstance()->getIsSummerMode()) {
                    lcd->print("*");
                }
                break;
            }

            case 3: {
                decrementPosition();
                break;
            }
        }
    }

    else if (menu == TIME_SLOT_MENU) {
            lcd->print("--Calendar Pump/SM--");
            lcd->setCursor(0, 1);
            lcd->print("SET TIME SLOTS: ");
            lcd->print(Calendar::getInstance()->getSlotAmount());
    }

    else if (menu == CALENDAR_PUMP_MENU) {
        switch (position) {
            case 0: {
                if (slotPosition > 0) {
                    slotPosition --;
                    position = 2;
                    printMenu();
                }

                else {
                    position = 1;
                    printMenu();
                }
                break;
            }

            case 1: {
                lcd->print("---Calendar Pump---");
                lcd->setCursor(0, 1);
                lcd->print("SLOT-");
                lcd->print(slotPosition + 1);
                lcd->setCursor(0, 2);
                lcd->print(">Start Time: "); // 14

                // fetch array
                timeArray = Calendar::getInstance()->getPumpTime(slotPosition).getStartTimeArray();

                // print Start Time array
                for (int i = 0; i < 4; i++) {
                    lcd->print(timeArray[i]);
                    if (i == 1) lcd->print(":");
                }

                lcd->setCursor(0, 3);
                lcd->print(" End Time:   ");

                // print End Time array
                for (int i = 0; i < 4; i++) {
                    lcd->print(Calendar::getInstance()->getPumpTime(slotPosition).getEndTimeArray()[i]);
                    if (i == 1) lcd->print(":");
                }
                break;
            }

            case 2: {

                lcd->print("---Calendar Pump---");
                lcd->setCursor(0, 1);
                lcd->print("SLOT-");
                lcd->print(slotPosition + 1);
                lcd->setCursor(0, 2);
                lcd->print(" Start Time: "); // 14

                // print Start Time array
                for (int i = 0; i < 4; i++) {
                    lcd->print(Calendar::getInstance()->getPumpTime(slotPosition).getStartTimeArray()[i]);
                    if (i == 1) lcd->print(":");
                }

                lcd->setCursor(0, 3);
                lcd->print(">End Time:   ");

                // fetch array
                timeArray = Calendar::getInstance()->getPumpTime(slotPosition).getEndTimeArray();

                // print End Time array
                for (int i = 0; i < 4; i++) {
                    lcd->print(timeArray[i]);
                    if (i == 1) lcd->print(":");
                }

                break;
            }

            case 3: {
                if (slotPosition < Calendar::getInstance()->getSlotAmount()-1) {
                    slotPosition ++;
                    position = 1;
                    timeArrayPosition = 0;
                    printMenu();
                }
                else {
                    decrementPosition();
                }
                break;
            }
        }
    }

    else if (menu == CALENDAR_SM_MENU) {
        switch (position) {
            case 0: {
                if (slotPosition > 0) {
                    slotPosition --;
                    position = 2;
                    printMenu();
                }

                else {
                    position = 1;
                    printMenu();
                }
                break;
            }

            case 1: {
                lcd->print("----Calendar SM----");
                lcd->setCursor(0, 1);
                lcd->print("SLOT-");
                lcd->print(slotPosition + 1);
                lcd->setCursor(0, 2);
                lcd->print(">Start Time: "); // 14

                // fetch array
                timeArray = Calendar::getInstance()->getSaltMasterTime(slotPosition).getStartTimeArray();

                // print Start Time array
                for (int i = 0; i < 4; i++) {
                    lcd->print(timeArray[i]);
                    if (i == 1) lcd->print(":");
                }

                lcd->setCursor(0, 3);
                lcd->print(" End Time:   ");

                // print End Time array
                for (int i = 0; i < 4; i++) {
                    lcd->print(Calendar::getInstance()->getSaltMasterTime(slotPosition).getEndTimeArray()[i]);
                    if (i == 1) lcd->print(":");
                }
                break;
            }

            case 2: {
                lcd->print("----Calendar SM----");
                lcd->setCursor(0, 1);
                lcd->print("SLOT-");
                lcd->print(slotPosition + 1);
                lcd->setCursor(0, 2);
                lcd->print(" Start Time: "); // 14

                // print Start Time array
                for (int i = 0; i < 4; i++) {
                    lcd->print(Calendar::getInstance()->getSaltMasterTime(slotPosition).getStartTimeArray()[i]);
                    if (i == 1) lcd->print(":");
                }

                lcd->setCursor(0, 3);
                lcd->print(">End Time:   ");

                // fetch array
                timeArray = Calendar::getInstance()->getSaltMasterTime(slotPosition).getEndTimeArray();

                // print End Time array
                for (int i = 0; i < 4; i++) {
                    lcd->print(timeArray[i]);
                    if (i == 1) lcd->print(":");
                }

                break;
            }

            case 3: {
                if (slotPosition < Calendar::getInstance()->getSlotAmount()-1) {
                    slotPosition ++;
                    position = 1;
                    timeArrayPosition = 0;
                    printMenu();
                }
                else {
                    decrementPosition();
                }
                break;
            }
        }
    }

    else if (menu == MAX_MENU) {
        menu = MAX_MENU - 1;
        printMenu();
    }
    else if (menu == MIN_MENU) {
        menu = MIN_MENU + 1;
        printMenu();
    }
}

void LCD::clear() {
    lcd->clear();
}
