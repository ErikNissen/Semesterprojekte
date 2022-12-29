//
// Created by alexn on 26.11.2022.
//

#include "Timer.h"

//  getters and setters
float Timer::getTimeInSeconds() const {
    return timeInSeconds;
}

// methods

void Timer::addSeconds(float _seconds) {
    timeInSeconds += _seconds;
}

void Timer::printSeconds() const {
    std::cout << "Timer at " << timeInSeconds << " seconds." << std::endl;
}


