//
// Created by Simon Goller on 13.06.22.
//

using namespace std;
#include "Time.hpp"

#ifndef POOLCONTROLLER_CALENDAR_HPP
#define POOLCONTROLLER_CALENDAR_HPP

class Calendar {
private:

    // static instance of calendar
    static Calendar *calendarInstance;
    // the amount of time slots the pump and the saltMaster have
    int slotAmount = 5;
    // if slotAmount gets changed save the previous value
    int oldSlotAmount = 0;
    // Array storing the pump time slots
    Time *pumpTimes = new Time[slotAmount];
    // Array storing the saltMaster time slots
    Time *saltMasterTimes = new Time[slotAmount];

    /**
     * Private Constructor
     * so that no objects can be created.
     */
    Calendar() {};

public:

    /**
     * get the static instance of Calendar
     * @return the static instance
     */
    static Calendar* getInstance();

    /**
     * initialize the Calendar
     */
    void init();

    /**
     * if slotAmount gets changed then old time objects
     * get copied into the new pumpTimes Array
     */
    void reInit();

    /**
     * set the amount of time slots the calendar should have
     * @param amount which should be set
     */
    void setSlotAmount(int amount);

    /**
     * get the amount of time slots the calendar has
     * @return the amount of time slots
     */
    int getSlotAmount();

    /**
     * return the time at the position slot of the pumpTimes array
     * @param slot the index
     * @return the Time object
     */
    Time getPumpTime(int slot);

    /**
     * return the time at the position slot of the saltMasterTimes array
     * @param slot the position
     * @return the Time object
     */
    Time getSaltMasterTime(int slot);

    /**
     * update the time object at a specific position in the pumpTimes array
     * @param slot the position
     */
    void updatePump(int slot);

    /**
     * update the time object at a specific position in the slatMasterTimes array
     * @param slot the position
     */
    void updateSaltMaster(int slot);

};
#endif //POOLCONTROLLER_CALENDAR_HPP
