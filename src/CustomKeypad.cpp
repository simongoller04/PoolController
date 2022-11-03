//
// Created by Simon Goller on 09.06.22.
//

#include "CustomKeypad.hpp"

LCD *lcd = LCD::getInstance();

Keypad * CustomKeypad::getKeypad() {
    return new Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
}

void CustomKeypad::handleKeyPressed(char key) {

    switch (key) {
        case 'A': {
            LCD::getInstance()->clear();
            LCD::getInstance()->decrementPosition();
            break;
        }

        case 'B': {
            LCD::getInstance()->clear();
            LCD::getInstance()->incrementPosition();
            break;
        }

        case 'C': {
            LCD::getInstance()->clear();
            LCD::getInstance()->decrementMenu();
            break;
        }

        case 'D': {
            LCD::getInstance()->clear();
            LCD::getInstance()->incrementMenu();
            break;
        }

        case '#': {
//            save
//            LCD::getInstance()->clear();
//            LCD::getInstance()->print("# pressed");
            break;
        }

        case '*': {
            int menu = LCD::getInstance()->getMenu();
            int position = LCD::getInstance()->getPosition();

            switch (menu) {
                case CURRENT_STATS_MENU: {

                    // if automatic mode is deactivated (manual mode activated) the devices can be turned on manually
                    if (!Mode::getInstance()->getIsAutomaticMode() ||
                        (WaterTank::getInstance()->getInletState() ||
                         WaterTank::getInstance()->getOutletState())) {

                        switch (position) {
                            case PUMP_STATS: {
                                if (Pump::getInstance()->getState()) {
                                    Pump::getInstance()->deactivate();
                                }
                                else {
                                    Pump::getInstance()->activate();
                                }
                                lcd->printMenu();
                                break;
                            }

                            case SALT_MASTER_STATS: {
                                if (SaltMaster::getInstance()->getState()) {
                                    SaltMaster::getInstance()->deactivate();
                                }
                                else {
                                    if (Pump::getInstance()->getState()) {
                                        SaltMaster::getInstance()->activate();
                                    }
                                }
                                lcd->printMenu();
                                break;
                            }

                            case POOL_TEMP_STATS: {
                                break;
                            }
                        }
                    }
                    break;
                }
                
                case AUTOMATIC_MANUAL_MENU: {
                    Mode::getInstance()->toggleIsAutomaticMode();
                    LCD::getInstance()->printMenu();
                    break;
                }

                case WINTER_SUMMER_MENU: {
                    Mode::getInstance()->toggleIsSummerMode();
                    LCD::getInstance()->printMenu();
                    break;
                }

                case CALENDAR_PUMP_MENU: {
                    LCD::getInstance()->incrementTimeArrayPosition();
                    break;
                }

                case CALENDAR_SM_MENU: {
                    LCD::getInstance()->incrementTimeArrayPosition();
                    break;
                }
            }

            break;
        }

        case '1': {
            LCD::getInstance()->setNumericValue(1);
            break;
        }

        case '2': {
            LCD::getInstance()->setNumericValue(2);
            break;
        }

        case '3': {
            LCD::getInstance()->setNumericValue(3);
            break;
        }

        case '4': {
            LCD::getInstance()->setNumericValue(4);
            break;
        }

        case '5': {
            LCD::getInstance()->setNumericValue(5);
            break;
        }

        case '6': {
            LCD::getInstance()->setNumericValue(6);
            break;
        }

        case '7': {
            LCD::getInstance()->setNumericValue(7);
            break;
        }

        case '8': {
            LCD::getInstance()->setNumericValue(8);
            break;
        }

        case '9': {
            LCD::getInstance()->setNumericValue(9);
            break;
        }

        case '0': {
            LCD::getInstance()->setNumericValue(0);
            break;
        }
    }
}