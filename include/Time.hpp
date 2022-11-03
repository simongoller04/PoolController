//
// Created by Simon Goller on 13.06.22.
//

#ifndef POOLCONTROLLER_TIME_HPP
#define POOLCONTROLLER_TIME_HPP

class Time {
private:
    // int representing the start hours
    int startHours;
    // int representing the start minutes
    int startMinutes;
    // int representing the end hours
    int endHours;
    // int representing the end minutes
    int endMinutes;
    // array which contains the start time of a device (when device is turned on)
    int *startTimeArray;
    // array which contains the end time of a device (when device is turned off)
    int *endTimeArray;

public:
    /**
     * Constructor
     */
    Time() {};

    /**
     * Constructor
     * @param start array with the start time
     * @param end array with the end time
     */
    Time(int *start, int *end);

    /**
     * get the startTime array of the current time object
     * @return a pointer to the array
     */
    int* getStartTimeArray();

    /**
     * get the endTime array of the current time object
     * @return a pointer to the array
     */
    int* getEndTimeArray();

    /**
     * get the start hours
     * @return an int representing the start hours
     */
    int getStartHours();

    /**
     * get the start minutes
     * @return an int representing the start minutes
     */
    int getStartMinutes();

    /**
     * get the end hours
     * @return an int representing the end hours
     */
    int getEndHours();

    /**
     * get the end minutes
     * @return an int representing the end minutes
     */
    int getEndMinutes();

    /**
     * if there is a change in startTimeArray or endTimeArray,
     * then recalculate the int values of startHours, startMinutes,
     * endHours und endMinutes
     */
    void update();

};

#endif //POOLCONTROLLER_TIME_HPP
