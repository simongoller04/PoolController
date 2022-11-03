//
// Created by Simon Goller on 23.06.22.
//

#include "Mode.hpp"
#include "Pump.hpp"
#include "SaltMaster.hpp"

Mode *Mode::modeInstance = 0;

Mode *Mode::getInstance() {
    if (!modeInstance) {
        modeInstance = new Mode;
    }
    return modeInstance;
}

void Mode::toggleIsSummerMode() {
    if (isSummerMode) {
        isSummerMode = false;
    }
    else {
        isSummerMode = true;
    }

    Pump::getInstance()->deactivate();
    SaltMaster::getInstance()->deactivate();
}

void Mode::toggleIsAutomaticMode() {
    if (isAutomaticMode) {
        isAutomaticMode = false;
    }
    else {
        isAutomaticMode = true;
    }

    Pump::getInstance()->deactivate();
    SaltMaster::getInstance()->deactivate();
}

bool Mode::getIsAutomaticMode() {
    return isAutomaticMode;
}

bool Mode::getIsSummerMode() {
    return isSummerMode;
}
