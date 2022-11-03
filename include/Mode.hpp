//
// Created by Simon Goller on 23.06.22.
//

#ifndef POOLCONTROLLER_MODE_HPP
#define POOLCONTROLLER_MODE_HPP

class Mode {
private:
    // static instance of Mode
    static Mode *modeInstance;
    // gives information about whether summer mode is selected or not
    bool isSummerMode = true;
    // gives information about whether automatic mode is selected or not
    bool isAutomaticMode = true;

    /**
     * private Constructor
     * so that no objects can be created
     */
    Mode() {};

public:
    /**
     * get the static singleton Instance of Mode
     * @return the static Instance of Mode
     */
    static Mode* getInstance();

    /**
     * check if the summer mode is on or off
     * @return the bool isSummerMode
     */
    bool getIsSummerMode();

    /**
     * check if the automatic mode is on or off
     * @return the bool isAutomaticMode
     */
    bool getIsAutomaticMode();

    /**
     * changes the isSummerMode bool to the opposite
     */
    void toggleIsSummerMode();

    /**
     * changes the isAutomaticMode bool to the opposite
     */
    void toggleIsAutomaticMode();

};
#endif //POOLCONTROLLER_MODE_HPP
