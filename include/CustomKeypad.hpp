//
// Created by Simon Goller on 09.06.22.
//

#include "Arduino.h"
#include "../lib/Keypad/Keypad.h"
#include "LCD.hpp"
#include "Calendar.hpp"

#ifndef POOLCONTROLLER_CUSTOMKEYPAD_HPP
#define POOLCONTROLLER_CUSTOMKEYPAD_HPP

/**
 * this class handles all the button events
 */
class CustomKeypad {
private:
    static const byte ROWS = 4;
    static const byte COLS = 4;

    char hexaKeys[ROWS][COLS] = {
            {'1','2','3','A'},
            {'4','5','6','B'},
            {'7','8','9','C'},
            {'*','0','#','D'}
    };

    byte rowPins[ROWS] = {27,29,31,33};
    byte colPins[COLS] = {28,30,32,34};

public:
    /**
     * Constructor
     */
    CustomKeypad() {};

    /**
     * return the keypad object which can detect button presses
     * @return the keypad object
     */
    Keypad *getKeypad();

    /**
     * handle the different key cases
     * @param key char representing a specific key
     */
    void handleKeyPressed(char key);
};


#endif //POOLCONTROLLER_CUSTOMKEYPAD_HPP
