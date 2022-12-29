/*
 * Manually track calculated times.
*/

#ifndef NP_SEMESTERPROJEKT_TIMER_H
#define NP_SEMESTERPROJEKT_TIMER_H

#include <iostream>


class Timer {
    //attributes
private:
    float timeInSeconds = 0;

      // getters and setters
public:
    float getTimeInSeconds() const;

    // methods
public:
    void addSeconds(float);
    void printSeconds() const;
};


#endif //NP_SEMESTERPROJEKT_TIMER_H
