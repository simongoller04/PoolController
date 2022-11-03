//
// Created by Simon Goller on 07.06.22.
//

#include "Arduino.h"
#include "../lib/LiquidCrystal_I2C-1.1.2/LiquidCrystal_I2C.h"
#include "Calendar.hpp"
#include "Mode.hpp"
#include "Clock.hpp"
#include "Pump.hpp"
#include "SaltMaster.hpp"
#include "TemperatureSensor.hpp"

#ifndef POOLCONTROLLER_LCD_HPP
#define POOLCONTROLLER_LCD_HPP

/**
 * Enum for the current menu state,
 * which menu is currently selected
 */
enum Menu {
    MIN_MENU,
    CLOCK_START_MENU,
    CURRENT_STATS_MENU,
    AUTOMATIC_MANUAL_MENU,
    WINTER_SUMMER_MENU,
    TIME_SLOT_MENU,
    CALENDAR_PUMP_MENU,
    CALENDAR_SM_MENU,
    MAX_MENU
};

/**
 * Enum for the current position inside the CURRENT_STATS_MENU
 */
enum Stats {
    MIN_STATS,
    PUMP_STATS,
    SALT_MASTER_STATS,
    POOL_TEMP_STATS,
    INLET_STATS,
    OUTLET_STATS,
    MAX_STATS
};

/**
 * Singleton Class LCD
 */
class LCD {
private:
    // static instance of LCD
    static LCD *lcdInstance;
    // lcd screen object
    LiquidCrystal_I2C *lcd;
    // the current menu which is selected
    int menu = 0 ;
    // the current position within a menu
    int position = 0;
    // the current position within the time array
    int timeArrayPosition = 0;
    // array which stores the currently selected time array
    int *timeArray;
    // the current time slot which is active
    int slotPosition = 0;

    /**
     * Private constructor
     * so that no objects can be created
     */
    LCD() {};

public:
    /**
     * get the static singleton Instance of LCD
     * @return the static Instance of LCD
     */
    static LCD* getInstance();

    /**
     * initializes the LCD screen
     * @param address of the lcd display
     * @param rows amount of rows the display can show
     * @param columns amount of columns the display can show
     */
    void init(int address, int rows, int columns);

    /**
     * Displays a start Screen
     */
    void start();

    /**
     * Returns the value of menu
     * @return the current menu
     */
    int getMenu();

    /**
     * provides the current position within a menu
     * @return the current position (int)
     */
    int getPosition();

    /**
     * increment the value of timeArrayPosition by 1
     * if <4 is reached start again at 0
     */
    void incrementTimeArrayPosition();

    /**
     * depending on the current menu, values can be replaced
     * @param value int value to be set
     */
    void setNumericValue(int value);

    /**
     * increment the value of menu by 1
     */
    void incrementMenu();

    /**
     * decrement the value of menu by 1
     */
    void decrementMenu();

    /**
     * increment the position within a menu by 1
     */
    void incrementPosition();

    /**
     * decrement the position within a menu by 1
     */
    void decrementPosition();

    /**
     * print the current menu on the lcd screen
     */
    void printMenu();

    /**
     * print the string on the screen
     * @param string the string to be printed
     */
    void print(String string);

    /**
     * clear the screen
     */
    void clear();

    /**
     * set the cursor to a specific position on the screen
     * @param row position top to bottom (0-3)
     * @param column position left to right (0-19)
     */
    void setCursor(int row, int column);
};

#endif //POOLCONTROLLER_LCD_HPP
