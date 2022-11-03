//
// Created by Simon Goller on 07.06.22.
//

#ifndef POOLCONTROLLER_CONSTANTPINS_HPP
#define POOLCONTROLLER_CONSTANTPINS_HPP

enum pin {
    LED_ERROR = 38,
    BEEPER = 40,

    SALT_MASTER = 37,
    INVERT = 39,
    CELL_SOCKET = 41,

    TANK_FULL = 24,
    TANK_EMPTY = 26,
    TANK_INLET = 43,
    TANK_OUTLET = 45,

    TEMP_SENSOR = 11,
    SWITCH_MANUAL = 22,
    PUMP = 35
};

#endif //POOLCONTROLLER_CONSTANTPINS_HPP
